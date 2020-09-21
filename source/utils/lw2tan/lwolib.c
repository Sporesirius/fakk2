//
// lwolib.c: library for loading triangles from a Lightwave triangle file
//

#include <stdio.h>
#include "cmdlib.h"
#include "mathlib.h"
#include "lwolib.h"
#include "qfiles.h"

struct {float p[3];} pnt[MAXPOINTS];
struct {short pl[3];} ply[MAXPOLYS];
char trashcan[18000];
char buffer[1000];
long counter;
union {char c[4];float f;long l;} buffer4;
union {char c[2];short i;} buffer2;
FILE *lwo;
short numpoints, numpolys;
int surfcount;

tridex_t	*ptri;
vec3_t	*pvert;
surf_t	*psurf;


long lflip(long x)
{
	union {char b[4]; long l;} in, out;
	
	in.l = x;
	out.b[0] = in.b[3];
	out.b[1] = in.b[2];
	out.b[2] = in.b[1];
	out.b[3] = in.b[0];
	
	return out.l;
}

float fflip(float x)
{
	union {char b[4]; float l;} in, out;
	
	in.l = x;
	out.b[0] = in.b[3];
	out.b[1] = in.b[2];
	out.b[2] = in.b[1];
	out.b[3] = in.b[0];
	
	return out.l;
}

int sflip(short x)
{
	union {char b[2]; short i;} in, out;
	
	in.i = x;
	out.b[0] = in.b[1];
	out.b[1] = in.b[0];

	return out.i;
}

void skipchunk()
{
	long chunksize;
	
	fread(buffer4.c,4,1,lwo);
    counter-=8;
	chunksize=lflip(buffer4.l);
	fread(trashcan,chunksize,1,lwo);
	counter-=chunksize;
};

void getsurfs()
{
	long chunksize;
	int i,j;

	fread(buffer4.c,4,1,lwo);
   counter-=8;
	chunksize=lflip(buffer4.l);

	counter-=chunksize;
	fread(trashcan,chunksize,1,lwo);
	i=0;
	while (i < chunksize)
	{
		strcpy( psurf[surfcount].name,trashcan+i);
		i=i+strlen( psurf[surfcount].name)+1;
		j=i;
		if((j>>1)<<1 != i) i++;
		if (!strncmp( psurf[surfcount].name,"Vid",3)) strcpy( psurf[surfcount].name, psurf[surfcount].name+17);
		surfcount++;
	}
}

void getpoints()
{
	long chunksize;
	short i,j;

	fread(buffer4.c,4,1,lwo);
   counter-=8;
	chunksize=lflip(buffer4.l);
	counter-=chunksize;
	numpoints=chunksize/12;
   if (numpoints>MAXPOINTS)
      {
		Error("Too many points");
      }
	for (i=0;i<numpoints;i++)
	{
		float temp;
		for (j=0;j<3;j++)
		{
			fread(buffer4.c,4,1,lwo);
			pvert[i][j]=fflip(buffer4.f);
		}
		temp=pvert[i][1];
		pvert[i][1]=pvert[i][2];
		pvert[i][2]=temp;
	}
}

void getpolys(){
	short temp,i,j;
	short polypoints;
	long chunksize;
	
	fread(buffer4.c,4,1,lwo);
   counter -= 8;
	chunksize = lflip(buffer4.l);
	counter -= chunksize;
	numpolys = 0;

	for (i=0;i<chunksize;)
	{
		fread(buffer2.c,2,1,lwo);
		polypoints = sflip(buffer2.i);

		if (polypoints != 3)
         {
   		printf("Not a triangle");
         }

		i+=10;

		for (j=0;j<3;j++)
		   {
			fread(buffer2.c,2,1,lwo);
			temp = sflip(buffer2.i);
			if (j==0) 
            {
				ptri[numpolys].verts[0]=temp;
            } 
         else 
            {
				if (j==1) 
               {
					ptri[numpolys].verts[1]=temp;
               } 
            else 
               {
					ptri[numpolys].verts[2]=temp;
				   }
			   }
		   }

		fread(buffer2.c,2,1,lwo);
		temp = sflip(buffer2.i);

		//ptri[numpolys].id = atoi(surfs[temp-1]);

		//ptri[numpolys].id = numpolys;

		ptri[numpolys].id = temp - 1;
      psurf[ ptri[numpolys].id ].polycount++;

		numpolys++;

		if (numpolys > MAXPOLYS)
         {
   		Error("Too many polygons");
         }
	}
}

void LoadLWOTriangleList (char *filename, tridex_t **pptri, vec3_t **ppvert, int *numtriangles, int *numverts)
{
   surf_t dummysurfs[ MAXSURFACES ];

	surfcount=0;

   memset( &dummysurfs, 0, sizeof( dummysurfs ) );
   psurf = dummysurfs;

	ptri = malloc (MAXTRIANGLES * sizeof(tridex_t));
	if (!ptri) Error("Malloc failed.");
	*pptri = ptri;
	pvert = malloc (MAXPOINTS * sizeof(vec3_t));
	if (!pvert) Error("Malloc failed.");
	*ppvert = pvert;
	
	if ((lwo = fopen(filename, "rb")) == 0) {
		fprintf(stderr,"reader: could not open file '%s'\n", filename);
		exit(0);
	}

	fread(buffer4.c,4,1,lwo);
	fread(buffer4.c,4,1,lwo);
	counter=lflip(buffer4.l)-4;
	fread(buffer4.c,4,1,lwo);
	while(counter>0)
    {
		fread(buffer4.c,4,1,lwo);
		if (!strncmp(buffer4.c,"PNTS",4))
		{
			getpoints();
		} else {
			if (!strncmp(buffer4.c,"POLS",4))
			{
				getpolys();
			} else {
				if (!strncmp(buffer4.c,"SRFS",4))
				{
					getsurfs();
				} else {
					skipchunk();
				}
			}
		}
    }
	fclose(lwo);

	*numtriangles = numpolys;
	*numverts = numpoints;
}

void load_triangles(char *filename, model_info *model)
{
	surfcount=0;

	ptri  = model->triangles;
	pvert = model->verts;
	psurf = model->surfs;
   memset( model->surfs, 0, MAXSURFACES * sizeof(surf_t) );
	
	if ((lwo = fopen(filename, "rb")) == 0) 
	{
		Error("could not open LWO file");
	}

	fread(buffer4.c,4,1,lwo);
	fread(buffer4.c,4,1,lwo);
	counter=lflip(buffer4.l)-4;
	fread(buffer4.c,4,1,lwo);

	while(counter>0)
    {
		fread(buffer4.c,4,1,lwo);
		if (!strncmp(buffer4.c,"PNTS",4))
		{
			getpoints();
		} else {
			if (!strncmp(buffer4.c,"POLS",4))
			{
				getpolys();
			} else {
				if (!strncmp(buffer4.c,"SRFS",4))
				{
					getsurfs();
				} else {
					skipchunk();
				}
			}
		}
    }

	fclose(lwo);

//   printf(" ...loaded %s\n", filename );

	model->number_of_triangles = numpolys;
	model->number_of_verts     = numpoints;
	model->number_of_surfaces  = surfcount;
}



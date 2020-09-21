#include <windows.h>
#include "cmdlib.h"
#include "mathlib.h"
#include "writetan.h"
#include "qfiles.h"

#define NUMVERTEXNORMALS	162

float	avertexnormals[NUMVERTEXNORMALS][3] = {
#include "anorms.h"
};

typedef struct
{
	int		numnormals;
	vec3_t	normalsum;
} vertexnormals_t;

//#define STATIC_STORAGE


#define MAX_BUFFER_SIZE 512000
#define MAX_FRAMES		512
#define MAX_VERTS       4096

#ifdef STATIC_STORAGE
byte			buffer[MAX_BUFFER_SIZE];
vec3_t   	finalverts[MAX_VERTS];
byte        lightnormals[MAX_VERTS];
vertexnormals_t vnorms[MAX_VERTS];
#else
byte			      *buffer;
vec3_t   	      *finalverts;
byte              *lightnormals;
vertexnormals_t   *vnorms;
#endif

/*
================
AllocateStorage
================
*/
int AllocateStorage( void )
   {
   buffer = ( byte * )malloc( MAX_BUFFER_SIZE );
   if (!buffer)
      {
	   MessageBox(NULL,"Could not allocate buffer","ConvertAnimModel",MB_OK);
      return 0;
      }
   finalverts = ( vec3_t * )malloc( MAX_VERTS * sizeof( vec3_t ) );
   if (!finalverts)
      {
	   MessageBox(NULL,"Could not allocate finalverts","ConvertAnimModel",MB_OK);
      return 0;
      }
   lightnormals = ( byte * )malloc( MAX_VERTS * sizeof( byte ) );
   if (!lightnormals)
      {
	   MessageBox(NULL,"Could not allocate lightnormals","ConvertAnimModel",MB_OK);
      return 0;
      }
   vnorms = ( vertexnormals_t * )malloc( MAX_VERTS * sizeof( vertexnormals_t ) );
   if (!vnorms)
      {
	   MessageBox(NULL,"Could not allocate vnorms","ConvertAnimModel",MB_OK);
      return 0;
      }
   return 1;
   }

/*
================
DeallocateStorage
================
*/
void DeallocateStorage( void )
   {
   free( buffer );
   free( finalverts );
   free( lightnormals );
   free( vnorms );
   }

/*
================
ConvertAnim
================
*/
int ConvertAnim( loadanimfile_t * load )
   {
   int i,j,k;
   dsinanim_t     *out;
   dsintriframe_t *frames;
   dsintriframe_t *cur_frame;
   FILE        *modelouthandle;
   byte        *bufptr;
   vec3_t      mins, maxs;
   float       ftemp;

#ifndef STATIC_STORAGE
   if (!AllocateStorage())
      return 0;
#endif
	modelouthandle = SafeOpenWrite (load->name);

   out = (dsinanim_t *)buffer;

   out->ident = SINANIMMODEL_HEADER;
	out->version = SINANIMMODEL_VERSION;

   DeSlashify ( load->name );
   ExtractFileBase( load->name, out->name );
   StripExtension( out->name );

   // store the number of frames
   out->num_frames = load->numframes;

   // store the number of verts
   out->num_xyz = load->frames[0].model.numverts;

   // find the mins and maxs for the entire animation
   ClearBounds( mins, maxs );
   for (i=0;i<load->numframes;i++)
      {
      // add the mins and maxs for each frame
      AddPointToBounds( load->frames[i].model.mins, mins, maxs );
      AddPointToBounds( load->frames[i].model.maxs, mins, maxs );
      }

   // rotate the mins and maxs to point down positive X axis
   ftemp = mins[0];
   mins[0] = -mins[1];
   mins[1] = ftemp;
   ftemp = maxs[0];
   maxs[0] = -maxs[1];
   maxs[1] = ftemp;

	for (j=0 ; j<3 ; j++)
   	{
		out->scale[j] = (maxs[j] - mins[j])/255.0f;
		out->translate[j] = mins[j];
	   }

   // move the bufptr past the initial structure
   bufptr = (byte *)out + sizeof(dsinanim_t);

   // get the offset for the frames
	out->ofs_frames = bufptr - (byte *)out;

   frames = (dsintriframe_t *)bufptr;
   // skip over the structures for all the frames
   bufptr += load->numframes * sizeof( dsintriframe_t );

   for (i=0, cur_frame=frames;i<load->numframes;i++, cur_frame++)
      {
      loadsinglefile_t * single;
      loadfacevertx_t *pfacevert;
      dtrivertx_t * outvert;

      // store pre-rotated
      cur_frame->movedelta[0] = -load->frames[i].delta[1];
      cur_frame->movedelta[1] = load->frames[i].delta[0];
      cur_frame->movedelta[2] = load->frames[i].delta[2];
      cur_frame->frametime = load->frames[i].time;

      // get the mins and maxs for each frame, pre-rotated
      mins[0] = -load->frames[i].model.mins[1];
      mins[1] = load->frames[i].model.mins[0];
      mins[2] = load->frames[i].model.mins[2];

      maxs[0] = -load->frames[i].model.maxs[1];
      maxs[1] = load->frames[i].model.maxs[0];
      maxs[2] = load->frames[i].model.maxs[2];

	   for (j=0 ; j<3 ; j++)
   	   {
		   cur_frame->scale[j] = (maxs[j] - mins[j])/255.0f;
		   cur_frame->translate[j] = mins[j];
	      }

      single = &load->frames[i].model;
      //
      // calculate light normals for all vertices
      //
      memset( &vnorms[0], 0, MAX_VERTS * sizeof( vertexnormals_t ) );
      for (j=0;j<single->numfaces;j++)
         {
		   vec3_t	vtemp1, vtemp2, normal;

         pfacevert = single->faces[j].verts;
		   VectorSubtract (single->verts[pfacevert[0].vertindex].v, single->verts[pfacevert[1].vertindex].v, vtemp1);
		   VectorSubtract (single->verts[pfacevert[2].vertindex].v, single->verts[pfacevert[1].vertindex].v, vtemp2);
		   CrossProduct (vtemp1, vtemp2, normal);

		   VectorNormalize (normal, normal);

   	   // rotate the normal so the model faces down the positive x axis
		   ftemp = normal[0];
		   normal[0] = -normal[1];
		   normal[1] = ftemp;

		   for (k=0 ; k<3 ; k++)
		      {
            int index;

            index = pfacevert[k].vertindex;
            if (index > MAX_VERTS)
               {
     			   MessageBox(NULL,"Too many verts","ConvertAnimModel",MB_OK);
               return 0;
               }
			   VectorAdd (vnorms[index].normalsum, normal, vnorms[index].normalsum);
			   vnorms[index].numnormals++;
            }
         }
      for (j=0;j<single->numverts;j++)
         {
         float * vert;

         if (j > MAX_VERTS)
            {
     		   MessageBox(NULL,"Too many verts","ConvertAnimModel",MB_OK);
            return 0;
            }
         vert = single->verts[j].v;

         finalverts[j][0] = -vert[1];
         finalverts[j][1] = vert[0];
         finalverts[j][2] = vert[2];
         }
      //
      // calculate the vertex normals, match them to the template list, and store the
      // index of the best match
      //
	   for (j=0 ; j<single->numverts ; j++)
	      {
		   vec3_t	v;
		   float	maxdot;
		   int		maxdotindex;
		   int		c;

		   c = vnorms[j].numnormals;
         //
         // do we really care about this?
         //
		   if (!c)
            {
   		   VectorClear( v );
//     			MessageBox(NULL,"Vertex with no triangles","ConvertAnimModel",MB_OK);
//            return 0;
            }
         else
            {
   		   VectorScale (vnorms[j].normalsum, 1.0/c, v);
            }
		   VectorNormalize (v, v);

		   maxdot = -999999.0;
		   maxdotindex = -1;

		   for (k=0 ; k<NUMVERTEXNORMALS ; k++)
		      {
			   float	dot;

			   dot = DotProduct (v, avertexnormals[k]);
			   if (dot > maxdot)
			      {
				   maxdot = dot;
				   maxdotindex = k;
			      }
		      }

		   lightnormals[j] = maxdotindex;
	      }
      //
      // store out the vertices
      //
      cur_frame->ofs_verts = bufptr - (byte *)cur_frame;
      outvert = (dtrivertx_t *)bufptr;
	   for (j=0 ; j<single->numverts ; j++, outvert++)
         {
         float v;

         outvert->lightnormalindex = lightnormals[j];
		   for (k=0 ; k<3 ; k++)
		      {
		      // scale to byte values & min/max check
//			   v = Q_rint ( (finalverts[j][k] - out->translate[k]) / out->scale[k] );
			   v = Q_rint ( (finalverts[j][k] - cur_frame->translate[k]) / cur_frame->scale[k] );

		      // clamp, so rounding doesn't wrap from 255.6 to 0
			   if (v > 255.0)
				   v = 255.0;
			   if (v < 0)
				   v = 0;
			   outvert->v[k] = v;
		      }
         }
      bufptr = (byte *)outvert;
	   }
   // store pre-rotated
   out->totaldelta[0] = -load->totaldelta[1];
   out->totaldelta[1] = load->totaldelta[0];
   out->totaldelta[2] = load->totaldelta[2];

   out->totaltime = load->totaltime;

   // get the end of the file
   out->ofs_end = bufptr - (byte *)out;

   // write out the entire thing
	SafeWrite (modelouthandle, out, out->ofs_end);
   fclose( modelouthandle );

#ifndef STATIC_STORAGE
   DeallocateStorage();
#endif

   return 1;
   }




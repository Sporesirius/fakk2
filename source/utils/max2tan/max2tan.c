//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2tan/max2tan.c               $
// $Revision:: 24                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/25/00 1:49p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2tan/max2tan.c                    $
// 
// 24    6/25/00 1:49p Markd
// fixed frames per second scaling
// 
// 23    6/25/00 12:58p Markd
// fixed bug with adjusting framerate
// 
// 22    6/21/00 3:58p Markd
// added fps support to max2tan
// 
// 21    2/26/00 11:43a Markd
// Added -rotate capability
// 
// 20    10/04/99 3:38p Jimdose
// changed use of true and false to qtrue and qfalse
// 
// 19    8/19/99 3:41p Markd
// Fixed MAX2TAN checking for time date stamp on UV file
// 
// 18    8/17/99 4:27p Jimdose
// added clearxy
// 
// 17    8/11/99 7:19p Jimdose
// added -clearz
// 
// 16    7/30/99 6:36p Markd
// fixed order of loading bug
// 
// 15    7/28/99 11:09a Markd
// Added reverse feature
// 
// 14    7/08/99 7:38p Markd
// Added noorigin flag to max2tan
// 
// 13    6/29/99 5:09p Markd
// Added new UV file format support
// 
// 12    6/29/99 2:40p Markd
// Added UV file time date checking
// 
// 11    6/29/99 2:26p Markd
// Added Z clamping and Z zeroing for models
//
// DESCRIPTION:
// Defines the entry point for the application.
//

#include "cmdlib.h"
#include "mathlib.h"
#include "qfiles.h"
#include "models.h"
#include "scriplib.h"

#define MAXLOADVERTS       2048
#define MAXLOADFACES		   3072
#define MAXMATERIALS		   64
#define MAXSURFACES		   64

typedef struct
   {
   int realindex;
   int valid;
   int id;
   char name[ 64 ];
   } material_t;

char filename[128];
char temp_filename[128];
char dest_filename[128];
char src_filename[128];
vec3_t vertexNormals[TIKI_MAX_TRIANGLES*3];
int  nummaterials = 0;
int  realnumsurfaces = 0;
material_t materials[ MAXMATERIALS ];
int  surf_polycounts[ MAXSURFACES ];
double scale_factor = 1;
float rotate;
qboolean nolod;
qboolean zeroz;
qboolean noclampz;
qboolean clearz;
qboolean clearxy;
qboolean noorigin;
qboolean reverse;
qboolean adjustfps;
float    fps;

#define MAXIGNORE 48
char **ignorelist = NULL;
char originname[ 64 ] = "origin";
int  numignore;

#define FALSE 0
#define TRUE 1



typedef struct
   {
	float	v[3];
   } loadvertx_t;

typedef struct
   {
   int vertindex;
   float s;
   float t;
   } loadfacevertx_t;

typedef struct
   {
   int id;
   loadfacevertx_t verts[3];
   } loadtriangle_t;

typedef struct
   {
   int            numverts;
   int            numfaces;
   loadtriangle_t faces[MAXLOADFACES];
   loadvertx_t    verts[MAXLOADVERTS];
   } loadsinglefile_t;

#define UV_FILE_VERSION 2

int  is_file_valid(char *filename);
void ComputeNormals( loadsinglefile_t * model, animframe_t * anim );
void LoadAnim( char * filename, loadsinglefile_t * load, animframe_t * anim, int * numframes, float * framerate );
void LoadUVFile( char * filename, loadsinglefile_t * load );
void ConvertBase( loadsinglefile_t * base, baseframe_t * bf );

animframe_t animframes[ TIKI_MAX_FRAMES ];
baseframe_t baseframe;

int main ( int argc, char * argv[] )
   {
   float framerate;
	int number_of_frames = 0;
   qboolean force;
   char uvfile[ 1024 ];
   int srctime, desttime, i;
   loadsinglefile_t single;
   loadsinglefile_t base;

   myargc = argc;
   myargv = argv;

	if ( argc < 2 )
	   {
		Error( "lw2tan animname [-uv filename] [-force] [-scale num] [-dest name]\n"
             "                [-ignore filename] [-origin originname] [-reverse]\n"
             "                [-verbose] [-nolod] [-noclampz] [-zeroz] [-noorigin]\n"
             "                [-clearz] [-clearxy] [-rotate angle] [-fps num]\n" );
	   }

   memset( uvfile, 0, sizeof( uvfile ) );

   verbose = qfalse;
   if ( CheckParm( "-verbose" ) )
      {
      verbose = qtrue;
      printf(" Verbose mode enabled.\n" );
      }

   reverse = qfalse;
   if ( CheckParm( "-reverse" ) )
      {
      reverse = qtrue;
      if ( verbose )
         printf(" Animation will be reversed.\n" );
      }

   nolod = qtrue;
   if ( CheckParm( "-nolod" ) )
      {
      nolod = qtrue;
      if ( verbose )
         printf(" No LOD map created.\n" );
      }

   zeroz = qfalse;
   if ( CheckParm( "-zeroz" ) )
      {
      zeroz = qtrue;
      if ( verbose )
         printf(" Delta Z movement will be zeroed.\n" );
      }

   noclampz = qfalse;
   if ( CheckParm( "-noclampz" ) )
      {
      noclampz = qtrue;
      if ( verbose )
         printf(" Delta Z movement will not be clamped.\n" );
      }

   clearz = qfalse;
   if ( CheckParm( "-clearz" ) )
      {
      clearz = qtrue;
      if ( verbose )
         printf(" Delta Z movement will be cleared after vertices are moved.\n" );
      }
   
   clearxy = qfalse;
   if ( CheckParm( "-clearxy" ) )
      {
      clearxy = qtrue;
      if ( verbose )
         printf(" Delta XY movement will be cleared after vertices are moved.\n" );
      }

   noorigin = qfalse;
   if ( CheckParm( "-noorigin" ) )
      {
      noorigin = qtrue;
      if ( verbose )
         printf(" Origin is being ignored.\n" );
      }

   force = qfalse;
   if ( CheckParm( "-force" ) )
      {
      force = qtrue;
      printf(" forced no timecheck performed.\n" );
      }

   adjustfps = qfalse;
   if ( i = CheckParm( "-fps" ) )
      {
      fps = atof( argv[ i + 1 ] );
      adjustfps = qtrue;
      printf(" frames per second set to %.2f.\n", fps );
      }
	// Get file name from the command line

	strcpy(filename, argv[ 1 ]);

   // set the scale if necessary
   if ( i = CheckParm( "-scale" ) )
      {
      scale_factor = atof( argv[ i + 1 ] );
      printf(" scale set at %f.\n", scale_factor );
      }

   rotate = 0;
   // rotate the data set if necessary
   if ( i = CheckParm( "-rotate" ) )
      {
      rotate = atof( argv[ i + 1 ] );
      printf(" rotating the data set by %.2f degrees.\n", rotate );
      }

   // check for uv file
   if ( i = CheckParm( "-uv" ) )
      {
      strcpy( uvfile, argv[ i + 1 ] );
      }

   // see if a new origin was specified
   if ( i = CheckParm( "-origin" ) )
      {
      strcpy( originname, argv[ i + 1 ] );
      printf(" origin set to %s.\n", originname );
      }

   // see if an ignore list is specified
   if ( i = CheckParm( "-ignore" ) )
      {
      ignorelist = malloc( MAXIGNORE * sizeof( char * ) );
      printf(" reading ignore file %s.\n", argv[ i + 1 ] );
      LoadScriptFile( argv[ i + 1 ] );
      while( GetToken( qtrue ) )
         {
         if ( numignore < MAXIGNORE )
            {
            ignorelist[ numignore ] = malloc( 64 );
            strcpy( ignorelist[ numignore++ ], token );
            }
         else
            {
            Error( "MAXIGNORE exceeded.\n" );
            }
         }
      }
   // create destination filename
   // check for dest file
   if ( i = CheckParm( "-dest" ) )
      {
      strcpy( dest_filename, argv[ i + 1 ] );
      }
   else
      {
      strcpy( dest_filename, filename );
      }
   StripExtension( dest_filename );
   strcat( dest_filename, ".tan" );

	// Make sure the ANIM file is really there

   strcpy( src_filename, filename );
   strcat( src_filename, ".anm" );

	if (!is_file_valid(src_filename))
	   {
		Error( "ANM file not found" );
	   }

   // check the time stamps
   srctime = FileTime( src_filename );
   desttime = FileTime( dest_filename );

   // check for version number difference
   if ( !force && desttime > 0 )
      {
      int i;
      FILE * f;

      f = SafeOpenRead( dest_filename );

      // read header
      SafeRead( f, &i, sizeof( i ) );
      if ( i != TIKI_ANIM_IDENT )
         {
         printf(" file identitifier differs, regrabbing.\n" );
         force = qtrue;
         }

      // read version
      SafeRead( f, &i, sizeof( i ) );
      i = LittleLong( i );
      if ( i != TIKI_ANIM_VERSION )
         {
         printf(" version numbers differ, regrabbing.\n" );
         force = qtrue;
         }

      fclose( f );
      }

   if ( srctime > desttime )
      {
      force = qtrue;
      }

	// Load the uv coordinates from the uv file
   if ( strlen( uvfile ) )
      {
      strcpy( temp_filename, uvfile );
      if ( !strstr( temp_filename, "." ) )
         {
         StripExtension( temp_filename );
         strcat( temp_filename, ".uv" );
         }
      }
   else
      {
   	sprintf(temp_filename, "%s.uv", filename);
      }

   srctime = FileTime( temp_filename );

   if ( !force && ( srctime > 0 ) && ( srctime < desttime ) )
      {
      printf(" destination is newer than source, skipping.\n" );
      return 0;
      }

   // clear out the load buffer
   memset( &single, 0, sizeof( single ) );

   // clear out the base buffer
   memset( &base, 0, sizeof( base ) );

   // clear out surf_polycounts
   memset( surf_polycounts, 0, sizeof( surf_polycounts ) );

	if (!is_file_valid(temp_filename))
	   {
		Error( "UV file not found" );
	   }

   LoadUVFile( temp_filename, &single );

   ConvertBase( &single, &baseframe );

   // start processing
   LoadAnim( src_filename, &single, animframes, &number_of_frames, &framerate );

   ConvertAnim
      ( 
      dest_filename, 
      number_of_frames, 
      framerate, 
      qtrue, 
      &baseframe, 
      animframes, 
      originname, 
      nolod, 
      !noclampz, 
      zeroz, 
      clearz,
      clearxy,
      noorigin,
      verbose 
      );

   // Free the ignore list 
   for( i = 0; i < numignore; i++ )
      {
      free( ignorelist[ i ] );
      }
   if ( ignorelist )
      {
      free( ignorelist );
      }

   return 0;
   }


qboolean IgnoreSurface( const char * surfname )
   {
   int i;

   if ( !surfname || !strlen( surfname ) )
      return qfalse;

   for( i = 0; i < numignore; i++ )
      {
      if ( !strcmpi( surfname, ignorelist[ i ] ) )
         return qtrue;
      }
   return qfalse;
   }


void LoadUVFile( char * filename, loadsinglefile_t * load )
   {
   int i;
   int j;
   int version;

   LoadScriptFile( filename );

   // skip over version
   GetToken( qtrue );
   // get version number
   GetToken( qtrue );

   version = atol( token );

   if ( version != UV_FILE_VERSION )
      {
      Error( "UV file %s is out of date, re-export.\n", filename );
      }

   // skip over nummaterials
   GetToken( qtrue );
   // get number of materials
   GetToken( qtrue );

   // get the materials
   realnumsurfaces = 0;
   nummaterials = atol( token );

   for( i = 0; i < nummaterials; i++ )
      {
      // skip over "material"
      GetToken( qtrue );
      // get the id
      GetToken( qtrue );
      // get the material id
      materials[ i ].id = atol( token );
      // get the material name
      GetToken( qtrue );
      strcpy( materials[ i ].name, token );

      if ( !IgnoreSurface( token ) )
         {
         // validate the material
         materials[ i ].valid = qtrue;
         materials[ i ].realindex = realnumsurfaces;
         realnumsurfaces++;
         }
      else
         {
         // invalidate the material
         materials[ i ].valid = qfalse;
         materials[ i ].realindex = -1;
         }
      }
   // skip over numverts
   GetToken( qtrue );
   // get the number of vertices
   GetToken( qtrue );
   load->numverts = atol( token );
   if ( load->numverts > MAXLOADVERTS )
      {
      Error( "Too many verts in %s\n", filename );
      }
   // get the verts
   for( i = 0; i < load->numverts; i++ )
      {
      // get the y
      GetToken( qtrue );
      load->verts[ i ].v[1] = atof( token ) * scale_factor;
      // get the x
      GetToken( qtrue );
      load->verts[ i ].v[0] = -atof( token ) * scale_factor;
      // get the z
      GetToken( qtrue );
      load->verts[ i ].v[2] = atof( token ) * scale_factor;
      }

   // skip over numfaces
   GetToken( qtrue );
   // get the number of faces
   GetToken( qtrue );
   load->numfaces = atol( token );
   if ( load->numfaces > MAXLOADFACES )
      {
      Error( "Too many faces in %s\n", filename );
      }
   // get the faces
   for( i = 0; i < load->numfaces; i++ )
      {
      // get the id
      GetToken( qtrue );
      // get the material id
      load->faces[ i ].id = atol( token );
      // find the material
      for ( j = 0; j < nummaterials; j++ )
         {
         if ( materials[ j ].id == load->faces[ i ].id )
            {
            // set the id to the index of the real surface index
            load->faces[ i ].id = materials[ j ].realindex;
            // add one triangle to this surface
            surf_polycounts[ j ]++;
            break;
            }
         }
      // get the verts
      for( j = 0; j < 3; j++ )
         {
         // get vertindex
         GetToken( qtrue );
         load->faces[ i ].verts[ j ].vertindex = atol( token );
         // get s
         GetToken( qtrue );
         load->faces[ i ].verts[ j ].s = atof( token );
         // get t
         GetToken( qtrue );
         load->faces[ i ].verts[ j ].t = atof( token );
         }
      }
   }

void LoadAnim( char * filename, loadsinglefile_t * load, animframe_t * anim, int * numframes, float * framerate )
   {
   int i, j, k, frameindex, factor;
   int orig_numframes, realframe;
   FILE * in;

   in = SafeOpenRead( filename );

   // read in numframes
   SafeRead( in, numframes, sizeof( *numframes ) );
   // read in framerate
   SafeRead( in, framerate, sizeof( *framerate ) );
   // read in num vertices
   SafeRead( in, &load->numverts, sizeof( load->numverts ) );

   orig_numframes = *numframes;

   if ( adjustfps )
      {
      factor = ( int )( ( *framerate / fps ) + 0.5f );
      if ( factor < 1 )
         factor = 1;
      *framerate /= factor;
      if ( *framerate < 1 )
         {
         *framerate = 1;
         }
      *numframes /= factor;
      if ( *numframes < 1 )
         {
         *numframes = 1;
         }
      }
   else
      {
      factor = 1;
      }

   realframe = 0;

   // read in each frame's data
	for( i = 0; i < *numframes; i++ )
      {
      if ( reverse )
         {
         frameindex = *numframes - 1 - i;
         }
      else
         {
         frameindex = i;
         }
      SafeRead( in, &load->verts, sizeof( loadvertx_t ) * load->numverts );
      anim[ frameindex ].numverts = load->numverts;
      for ( j = 0; j < load->numverts; j ++ )
         {
         anim[ frameindex ].verts[ j ].xyz[ 0 ] = -load->verts[ j ].v[ 1 ] * scale_factor;
         anim[ frameindex ].verts[ j ].xyz[ 1 ] = load->verts[ j ].v[ 0 ] * scale_factor;
         anim[ frameindex ].verts[ j ].xyz[ 2 ] = load->verts[ j ].v[ 2 ] * scale_factor;
         if ( rotate != 0 )
            {
            vec3_t tmp;
            float s, c;

            VectorCopy( anim[ frameindex ].verts[ j ].xyz, tmp );
            s = sin( DEG2RAD( rotate ) );
            c = cos( DEG2RAD( rotate ) );
            anim[ frameindex ].verts[ j ].xyz[ 0 ] = c * tmp[ 0 ] + s * tmp[ 1 ];
            anim[ frameindex ].verts[ j ].xyz[ 1 ] = s * tmp[ 0 ] + c * tmp[ 1 ];
            }
         }
      ComputeNormals( load, &anim[ frameindex ] );

      realframe++;

      //
      // skip over any frames we don't need
      //
      //
      // skip over any frames we might be skipping
      //
      for( k = 1; k < factor; k++ )
         {
         // make sure we don't read past the end of the data
         if ( realframe == orig_numframes )
            break;

         SafeRead( in, &load->verts, sizeof( loadvertx_t ) * load->numverts );

         // increment our realframe
         realframe++;
         }
      }

   fclose( in );
   }


void ConvertBase( loadsinglefile_t * base, baseframe_t * bf )
   {
	int current_face;
   int i, j, k, l, index, surf;
   float s, t;
   int trimap[ TIKI_MAX_TRIANGLES ];
   int numtris;

   bf->numSurfaces = 0;

   // copy the surfaces
   for( surf = 0, i = 0; i < nummaterials; i++ )
      {
      if ( materials[ i ].valid )
         {
         strcpy( bf->surfaces[ surf ].name, materials[ i ].name );
         strcpy( bf->surfaces[ surf ].materialname, materials[ i ].name );
         bf->numSurfaces++;
         surf++;
         }
      }

   // copy over the unique vertices
   for( surf = 0, i = 0; i < nummaterials; i++ )
      {
      // if not included, skip
      if ( !materials[ i ].valid )
         continue;

      // go through and count up the triangles for this surface
      numtris = 0;
      for( current_face = 0 ; current_face < base->numfaces ; current_face++)
         {
         if ( base->faces[ current_face ].id != materials[ i ].realindex )
            continue;
         trimap[ numtris++ ] = current_face;
         }

      // go through each triangle and add each unique vertex
      bf->surfaces[ surf ].numvertices = 0;
      bf->surfaces[ surf ].numtriangles = numtris;
      for( j = 0; j < numtris; j++ )
         {
         for( l = 0; l < 3; l++ )
            {
            index = base->faces[ trimap[ j ] ].verts[ l ].vertindex;
            s = base->faces[ trimap[ j ] ].verts[ l ].s;
            t = base->faces[ trimap[ j ] ].verts[ l ].t;

            // see if it already exists
            for( k = 0; k < bf->surfaces[ surf ].numvertices; k ++ )
               {
					if ( 
                     ( bf->surfaces[ surf ].triverts[ k ].map == index ) &&
                     ( bf->surfaces[ surf ].triverts[ k ].tex[ 0 ] == s ) &&
                     ( bf->surfaces[ surf ].triverts[ k ].tex[ 1 ] == t )
                  )
                  break;
               }
            // if it wasn't found, add it in
            if ( k == bf->surfaces[ surf ].numvertices )
               {
               bf->surfaces[ surf ].triverts[ k ].map = index;
               bf->surfaces[ surf ].triverts[ k ].tex[ 0 ] = s;
               bf->surfaces[ surf ].triverts[ k ].tex[ 1 ] = t;
               // these are only used for lod
               VectorCopy( base->verts[ index ].v, bf->surfaces[ surf ].triverts[ k ].xyz.xyz );

               bf->surfaces[ surf ].numvertices++;
               }
            bf->surfaces[ surf ].triangles[ j ].verts[ l ] = k;
            }
         }
      surf++;
      }
   }

int is_file_valid(char *filename)
{
	FILE *temp_file;
	int valid = qfalse;

	temp_file = fopen(filename, "rb");

	if (temp_file != NULL)
	{
		fclose(temp_file);
		valid = TRUE;
	}

	return valid;
}


void ComputeNormals( loadsinglefile_t * model, animframe_t * anim )
{
	vec3_t faceNormals[ TIKI_MAX_TRIANGLES ];
	vec3_t side0, side1, facenormal;
   float *vert1, *vert2;
	int f, v;

	memset( faceNormals, 0, sizeof( faceNormals ) );
	memset( vertexNormals, 0, sizeof( vertexNormals ) );

	//
	// compute face normals
	//
   for ( f = 0 ; f < model->numfaces ; f++)
	   {
      int a,b,c;

		a = model->faces[ f ].verts[0].vertindex;
		b = model->faces[ f ].verts[1].vertindex;
		c = model->faces[ f ].verts[2].vertindex;

      vert1 = &model->verts[ a ].v[0];
      vert2 = &model->verts[ b ].v[0];
		VectorSubtract( vert1, vert2, side0 );
      vert1 = &model->verts[ c ].v[0];
		VectorSubtract( vert1, vert2, side1 );

		CrossProduct( side0, side1, facenormal );
		VectorNormalize( facenormal, faceNormals[ f ] );
	   }

	//
	// sum vertex normals
	//
	for( v = 0 ; v < model->numverts ; v++)
	{
      for ( f = 0 ; f < model->numfaces ; f++)
		{
         int a,b,c;

		   a = model->faces[ f ].verts[0].vertindex;
		   b = model->faces[ f ].verts[1].vertindex;
		   c = model->faces[ f ].verts[2].vertindex;

			if ( ( a == v ) || ( b == v ) || ( c == v ) )
			{
				vertexNormals[v][0] += faceNormals[f][0];
				vertexNormals[v][1] += faceNormals[f][1];
				vertexNormals[v][2] += faceNormals[f][2];
			}
		}

		VectorNormalize( vertexNormals[v], vertexNormals[v] );
      anim->verts[ v ].normal[ 0 ] = -vertexNormals[ v ][ 1 ];
      anim->verts[ v ].normal[ 1 ] = vertexNormals[ v ][ 0 ];
      anim->verts[ v ].normal[ 2 ] = vertexNormals[ v ][ 2 ];
	}
}



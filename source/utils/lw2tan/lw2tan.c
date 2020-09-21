// lw2tan.cpp : Defines the entry point for the application.
//
#include "cmdlib.h"
#include "mathlib.h"
#include "qfiles.h"
#include "models.h"
#include "lwolib.h"
#include "uv.h"
#include "scriplib.h"

char filename[500];
char temp_filename[500];
char dest_filename[500];
char base_filename[500];
vec3_t vertexNormals[TIKI_MAX_TRIANGLES*3];
double scale_factor = 52.459;

#define MAXIGNORE 48
char **ignorelist;
char originname[ 64 ] = "origin";
int  numignore;
int  realnumsurfaces;
qboolean nolod;
qboolean zeroz;
qboolean noclampz;
float rotate;

#define FALSE 0
#define TRUE 1

int  is_file_valid(char *filename);
void free_model(model_info *model);
int  allocate_model_memory(model_info *model);
void ComputeNormals( model_info * model );
void rotate_model( model_info * model );
void convert_model_to_base( baseframe_t * bf, model_info * base );
void convert_model_to_anim( animframe_t *anim, model_info * model );
qboolean IgnoreSurface( const char * surfname );


animframe_t animframes[ TIKI_MAX_FRAMES ];
baseframe_t baseframe;

int main ( int argc, char * argv[] )
   {
   float framerate;
	model_info model;
	model_info base;
	int number_of_frames = 0;
   qboolean force;
   char uvfile[ 1024 ];
   int srctime, desttime, i;

   myargc = argc;
   myargv = argv;

	if ( argc < 2 )
	   {
		Error( "lw2tan animname [-framerate num] [-uv filename] [-force] [-scale num]\n" 
             "                [-ignore filename] [-origin originname] [-dest name]\n"
             "                [-base filename] [-nolod] [-verbose] [-noclampz] [-zeroz] [-rotate angle]\n");
	   }

   memset( uvfile, 0, sizeof( uvfile ) );

   numignore = 0;
   ignorelist = NULL;

   verbose = qfalse;
   if ( CheckParm( "-verbose" ) )
      {
      verbose = qtrue;
      printf(" Verbose mode enabled.\n" );
      }

   force = qfalse;
   if ( CheckParm( "-force" ) )
      {
      force = qtrue;
      if ( verbose )
         printf(" forced no timecheck performed.\n" );
      }

	// Get file name from the command line

	strcpy(filename, argv[ 1 ]);

   // see if a frame rate was specified
   if ( i = CheckParm( "-framerate" ) )
      {
      framerate = atof( argv[ i + 1 ] );
      if ( verbose )
         printf(" framerate set at %f frames per second.\n", framerate );
      }
   else
      {
      framerate = 10;
      }
   // see if a new origin was specified
   if ( i = CheckParm( "-origin" ) )
      {
      strcpy( originname, argv[ i + 1 ] );
      if ( verbose )
         printf(" origin set to %s.\n", originname );
      }

   // see if an ignore list is specified
   if ( i = CheckParm( "-ignore" ) )
      {
      ignorelist = malloc( MAXIGNORE * sizeof( char * ) );
      if ( verbose )
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

   // set the scale if necessary
   if ( i = CheckParm( "-scale" ) )
      {
      scale_factor = atof( argv[ i + 1 ] );
      if ( verbose )
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
   else
      {
      strcpy( uvfile, filename );
      }
   StripExtension( uvfile );
   strcat( uvfile, ".uv" );

   // check for base frame file
   if ( i = CheckParm( "-base" ) )
      {
      strcpy( base_filename, argv[ i + 1 ] );
      }
   else
      {
      strcpy( base_filename, filename );
      }
   StripExtension( base_filename );
   strcat( base_filename, ".lwo" );

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

	// Determine if this is an animation sequence or just 1 model

	sprintf(temp_filename, "%s001.lwo", filename);

	if (is_file_valid(temp_filename))
		sprintf(temp_filename, "%s001.lwo", filename);	// Animation sequence
	else
		sprintf(temp_filename, "%s.lwo", filename);		// Only 1 LWO file (no animation)

	// Make sure the LWO file is really there

	if (!is_file_valid(temp_filename))
	   {
		Error( "LWO file not found" );
	   }


   // check the time stamps
   srctime = FileTime( temp_filename );
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

   if ( !force && ( srctime < desttime ) )
      {
      srctime = FileTime( base_filename );
      if ( srctime < desttime )
         {
         srctime = FileTime( uvfile );
         if ( srctime < desttime )
            {
            printf(" destination is newer than source, skipping.\n" );
            return 0;
            }
         }
      }

	// Load the triangles from the LWO file

	if (!allocate_model_memory(&model))
   	{
		Error( "Failed to allocate memory for model" );
	   }
	if (!allocate_model_memory(&base))
   	{
		Error( "Failed to allocate memory for base model" );
	   }
   // load the base frame

	load_triangles(base_filename, &base);
   rotate_model( &base );

   ComputeNormals( &base );

	load_uv_coordinates( uvfile, surfcount, base.number_of_triangles, base.triangles, &base.number_of_uv_verts, base.uv_verts);

   if ( surfcount > MAX_ANIM_SURFACES )
      Error( "surfcount > MAX_ANIM_SURFACES\n" );

   // calculate real number of surfaces
   realnumsurfaces = 0;
   for( i = 0; i < base.number_of_surfaces; i++ )
      {
      if ( !IgnoreSurface( base.surfs[ i ].name ) )
         {
         base.surfs[ i ].map = realnumsurfaces;
         realnumsurfaces++;
         }
      else
         {
         base.surfs[ i ].map = -1;
         }
      }
   convert_model_to_base( &baseframe, &base );

#if 0
   // E3 HACK
   // find the tag_torso and tag_head
   if ( !strcmpi( base_filename, "f_edenjulia.lwo" ) )
      {
      for( i = 0; i < baseframe.numSurfaces; i++ )
         {
         if ( !strcmpi( baseframe.surfaces[ i ].name, "tag_torso" ) )
            {
            baseframe.surfaces[ i ].triverts[ 0 ].map = 14;
            baseframe.surfaces[ i ].triverts[ 1 ].map = 12;
            baseframe.surfaces[ i ].triverts[ 2 ].map = 10;
            }
         if ( !strcmpi( baseframe.surfaces[ i ].name, "tag_head" ) )
            {
            baseframe.surfaces[ i ].triverts[ 0 ].map = 13;
            baseframe.surfaces[ i ].triverts[ 1 ].map = 11;
            baseframe.surfaces[ i ].triverts[ 2 ].map = 9;
            }
         if ( !strcmpi( baseframe.surfaces[ i ].name, "tag_weapon" ) )
            {
            baseframe.surfaces[ i ].triverts[ 0 ].map = 6;
            baseframe.surfaces[ i ].triverts[ 1 ].map = 8;
            baseframe.surfaces[ i ].triverts[ 2 ].map = 7;
            }
         if ( !strcmpi( baseframe.surfaces[ i ].name, "tag_weapon_left" ) )
            {
            baseframe.surfaces[ i ].triverts[ 0 ].map = 3;
            baseframe.surfaces[ i ].triverts[ 1 ].map = 5;
            baseframe.surfaces[ i ].triverts[ 2 ].map = 4;
            }
         }
      }
#endif

   // start processing
   while ( 1 )
      {
	   if ( is_file_valid( temp_filename ) )
         {
   		load_triangles(temp_filename, &model);
         rotate_model( &model );

         if ( model.number_of_triangles != base.number_of_triangles )
            {
            Error( "%s has different number of triangles than base %s\n", temp_filename, base_filename );
            }
         if ( model.number_of_verts != base.number_of_verts )
            {
            Error( "%s has different number of vertices than base %s\n", temp_filename, base_filename );
            }
         ComputeNormals( &model );

         convert_model_to_anim( &animframes[ number_of_frames ], &model );

         number_of_frames++;

	      sprintf(temp_filename, "%s%.3d.lwo", filename, number_of_frames+1);
         }
      else
         {
         break;
         }
      }

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
      qfalse, 
      qfalse,
      qfalse,
      verbose 
      );

	// Free the model memory
	free_model(&model);

	// Free the base memory
	free_model(&base);

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

void rotate_model( model_info * model )
   {
   float c, s;
   vec3_t tmp;
   int i;

   for( i = 0; i < model->number_of_verts; i++ )
      {
      VectorCopy( model->verts[ i ], tmp );
      s = sin( DEG2RAD( rotate ) );
      c = cos( DEG2RAD( rotate ) );
      model->verts[ i ][ 0 ] = c * tmp[ 0 ] + s * tmp[ 1 ];
      model->verts[ i ][ 1 ] = s * tmp[ 0 ] + c * tmp[ 1 ];
      }
   }

void convert_model_to_anim( animframe_t *anim, model_info * model )
   {
   int i;

   for( i = 0; i < model->number_of_verts; i++ )
      {
#if 1
      anim->verts[ i ].xyz[ 0 ] = -model->verts[ i ][ 1 ] * scale_factor;
      anim->verts[ i ].xyz[ 1 ] = model->verts[ i ][ 0 ] * scale_factor;
      anim->verts[ i ].xyz[ 2 ] = model->verts[ i ][ 2 ] * scale_factor;

      anim->verts[ i ].normal[ 0 ] = -vertexNormals[ i ][ 1 ];
      anim->verts[ i ].normal[ 1 ] = vertexNormals[ i ][ 0 ];
      anim->verts[ i ].normal[ 2 ] = vertexNormals[ i ][ 2 ];
#else
      anim->verts[ i ].xyz[ 0 ] = model->verts[ i ][ 0 ] * scale_factor;
      anim->verts[ i ].xyz[ 1 ] = model->verts[ i ][ 1 ] * scale_factor;
      anim->verts[ i ].xyz[ 2 ] = model->verts[ i ][ 2 ] * scale_factor;

      anim->verts[ i ].normal[ 0 ] = -vertexNormals[ i ][ 0 ];
      anim->verts[ i ].normal[ 1 ] = vertexNormals[ i ][ 1 ];
      anim->verts[ i ].normal[ 2 ] = vertexNormals[ i ][ 2 ];
#endif
      }
   anim->numverts = model->number_of_verts;
   }


void convert_model_to_base( baseframe_t * bf, model_info * base )
   {
	int current_face;
   int i, j, k, l, index, uvindex, surf;
   int trimap[ TIKI_MAX_TRIANGLES ];
   int numtris;

   bf->numSurfaces = 0;

   // copy the surfaces
   for( i = 0, surf = 0; i < base->number_of_surfaces; i++ )
      {
      if ( base->surfs[ i ].map < 0 )
         continue;

      strcpy( bf->surfaces[ surf ].name, base->surfs[ i ].name );
      strcpy( bf->surfaces[ surf ].materialname, base->surfs[ i ].name );
      bf->numSurfaces++;
      surf++;
      }

   // copy over the unique vertices
   for( i = 0, surf = 0; i < base->number_of_surfaces; i++ )
      {
      // if not included, skip
      if ( base->surfs[ i ].map < 0 )
         continue;

      // go through and count up the triangles for this surface
      numtris = 0;
      for( current_face = 0 ; current_face < base->number_of_triangles ; current_face++)
         {
         if ( base->triangles[ current_face ].id != i )
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
            index = base->triangles[ trimap[ j ] ].verts[ l ];
            uvindex = base->triangles[ trimap[ j ] ].uv_verts[ l ];

            // see if it already exists
            for( k = 0; k < bf->surfaces[ surf ].numvertices; k ++ )
               {
					if ( 
                     ( bf->surfaces[ surf ].triverts[ k ].map == index ) &&
                     ( bf->surfaces[ surf ].triverts[ k ].tex[ 0 ] == base->uv_verts[ uvindex ].u ) &&
                     ( bf->surfaces[ surf ].triverts[ k ].tex[ 1 ] == base->uv_verts[ uvindex ].v )
                  )
                  break;
               }
            // if it wasn't found, add it in
            if ( k == bf->surfaces[ surf ].numvertices )
               {
               bf->surfaces[ surf ].triverts[ k ].map = index;
               bf->surfaces[ surf ].triverts[ k ].tex[ 0 ] = base->uv_verts[ uvindex ].u;
               bf->surfaces[ surf ].triverts[ k ].tex[ 1 ] = base->uv_verts[ uvindex ].v;
               // these are only used for lod
               bf->surfaces[ surf ].triverts[ k ].xyz.xyz[ 0 ] = -base->verts[ index ][ 1 ];
               bf->surfaces[ surf ].triverts[ k ].xyz.xyz[ 1 ] = base->verts[ index ][ 0 ];
               bf->surfaces[ surf ].triverts[ k ].xyz.xyz[ 2 ] = base->verts[ index ][ 2 ];

               bf->surfaces[ surf ].triverts[ k ].xyz.normal[ 0 ] = -vertexNormals[ index ][ 1 ];
               bf->surfaces[ surf ].triverts[ k ].xyz.normal[ 1 ] = vertexNormals[ index ][ 0 ];
               bf->surfaces[ surf ].triverts[ k ].xyz.normal[ 2 ] = vertexNormals[ index ][ 2 ];

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

void free_model(model_info *model)
{	
	if (model->triangles != NULL)
	{
		free(model->triangles);
		model->triangles = NULL;
	}

	if (model->verts != NULL)
	{
		free(model->verts);
		model->verts = NULL;
	}

	if (model->uv_verts != NULL)
	{
		free(model->uv_verts);
		model->uv_verts = NULL;
	}

	if (model->surfs != NULL)
	{
		free(model->surfs);
		model->surfs = NULL;
	}

	model->number_of_triangles = 0;
	model->number_of_verts     = 0;
	model->number_of_uv_verts  = 0;
	model->number_of_surfaces  = 0;
}

int allocate_model_memory(model_info *model)
{
	model->triangles = malloc(MAXTRIANGLES * sizeof(tridex_t));

	if (!model->triangles) 
		return qfalse;

	model->verts = malloc(MAXPOINTS * sizeof(vec3_t));

	if (!model->verts) 
		return qfalse;

	model->uv_verts = malloc(MAXPOINTS * sizeof(uv_t));

	if (!model->uv_verts) 
		return qfalse;

	model->surfs = malloc(MAXSURFACES * sizeof(surf_t));

   memset( model->surfs, 0, MAXSURFACES * sizeof(surf_t) );

	if (!model->surfs) 
		return qfalse;

	return TRUE;
}

void ComputeNormals( model_info * model )
{
	vec3_t faceNormals[ TIKI_MAX_TRIANGLES ];
	vec3_t side0, side1, facenormal;
	int f, v;

	memset( faceNormals, 0, sizeof( faceNormals ) );
	memset( vertexNormals, 0, sizeof( vertexNormals ) );

	//
	// compute face normals
	//
   for ( f = 0 ; f < model->number_of_triangles ; f++)
	   {
      int a,b,c;

		a = model->triangles[ f ].verts[0];
		b = model->triangles[ f ].verts[1];
		c = model->triangles[ f ].verts[2];

		VectorSubtract( model->verts[ a ], model->verts[ b ], side0 );
		VectorSubtract( model->verts[ c ], model->verts[ b ], side1 );

		CrossProduct( side0, side1, facenormal );
		VectorNormalize( facenormal, faceNormals[ f ] );
	   }

	//
	// sum vertex normals
	//
	for( v = 0 ; v < model->number_of_verts ; v++)
	{
      for ( f = 0 ; f < model->number_of_triangles ; f++)
		{
         int a,b,c;

		   a = model->triangles[ f ].verts[0];
		   b = model->triangles[ f ].verts[1];
		   c = model->triangles[ f ].verts[2];

			if ( ( a == v ) || ( b == v ) || ( c == v ) )
			{
				vertexNormals[v][0] += faceNormals[f][0];
				vertexNormals[v][1] += faceNormals[f][1];
				vertexNormals[v][2] += faceNormals[f][2];
			}
		}

		VectorNormalize( vertexNormals[v], vertexNormals[v] );
	}
}



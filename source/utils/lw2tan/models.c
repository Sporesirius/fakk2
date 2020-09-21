#include <assert.h>
#include "cmdlib.h"
#include "mathlib.h"
#include "qfiles.h"
#include "models.h"
#include "tikidata.h"
#include "calclod.h"

//=================================================================

void OrderMesh( int input[][3], int output[][3], int numTris );
static void OrderSurfaces( void );
static void LoadBase( const char *filename );

q3data g_data;

qboolean g_verbose;
qboolean g_optimize;
qboolean g_lod = qtrue;
qboolean g_clampz;
qboolean g_noorigin;
qboolean g_zeroz;
qboolean g_clearz;
qboolean g_clearxy;

// the command list holds counts, the count * 3 xyz, st, normal indexes
// that are valid for every frame
char		g_cddir[1024];
char		g_modelname[1024];


/*
** TIKI_ComputeTagFromTri
*/
void TIKI_ComputeTagFromTri( tikiTagData_t *pTag, const float pTri[3][3], const float pbaseTri[3][3] )
{
	float	len[3];
	float	origlen[3];
	vec3_t	axes[3], sides[3];
	int		longestSide, shortestSide, hypotSide;
	int		origin;
	int		j;
	float	d;

   longestSide = 0;
   shortestSide = 0;
   hypotSide = 0;
   origin = 0;

	memset( axes, 0, sizeof( axes ) );
	memset( sides, 0, sizeof( sides ) );

	//
	// compute sides
	//
	for ( j = 0; j < 3; j++ )
	{
#if 1
		sides[j][0] = pbaseTri[(j+1)%3][0] - pbaseTri[j][0];
		sides[j][1] = pbaseTri[(j+1)%3][1] - pbaseTri[j][1];
		sides[j][2] = pbaseTri[(j+1)%3][2] - pbaseTri[j][2];
#else
		sides[j][0] = pTri[(j+1)%3][0] - pTri[j][0];
		sides[j][1] = pTri[(j+1)%3][1] - pTri[j][1];
		sides[j][2] = pTri[(j+1)%3][2] - pTri[j][2];
#endif

		origlen[ j ] = len[ j ] = ( float ) sqrt( DotProduct( sides[j], sides[j] ) );
	}

#if 0
	if ( len[0] > len[1] && len[0] > len[2] )
	{
		longestSide = 0; shortestSide = 1; origin = 2;
	}
	else if ( len[1] > len[0] && len[1] > len[2] )
	{
		longestSide = 1; shortestSide = 2; origin = 0;
	}
	else if ( len[2] > len[0] && len[2] > len[1] )
	{
		longestSide = 2; shortestSide = 0; origin = 1;
	}
	else
	{
		Error( "invalid tag triangle, must be a right triangle with unequal length sides" );
	}
#endif
	if ( len[0] > len[1] && len[0] > len[2] ) {
		hypotSide = 0;
		origin = 2;
	} else if ( len[1] > len[0] && len[1] > len[2] ) {
		hypotSide = 1;
		origin = 0;
	} else if ( len[2] > len[0] && len[2] > len[1] ) {
		hypotSide = 2;
		origin = 1;
	}
	len[hypotSide] = -1;

	if ( len[0] > len[1] && len[0] > len[2] ) {
		longestSide = 0;
	} else if ( len[1] > len[0] && len[1] > len[2] ) {
		longestSide = 1;
	} else if ( len[2] > len[0] && len[2] > len[1] ) {
		longestSide = 2;
	}
	len[longestSide] = -1;

	if ( len[0] > len[1] && len[0] > len[2] ) {
		shortestSide = 0;
	} else if ( len[1] > len[0] && len[1] > len[2] ) {
		shortestSide = 1;
	} else if ( len[2] > len[0] && len[2] > len[1] ) {
		shortestSide = 2;
	}
	len[shortestSide] = -1;

	//
	// compute sides
	//
	for ( j = 0; j < 3; j++ )
	{
		sides[j][0] = pTri[(j+1)%3][0] - pTri[j][0];
		sides[j][1] = pTri[(j+1)%3][1] - pTri[j][1];
		sides[j][2] = pTri[(j+1)%3][2] - pTri[j][2];
	}

   if ( longestSide == 0 && shortestSide == 1 )
      {
      VectorNegate( sides[ longestSide ] );
      VectorNegate( sides[ shortestSide ] );
      }
   else if ( longestSide == 0 && shortestSide == 2 )
      {
      }
   else if ( longestSide == 1 && shortestSide == 0 )
      {
      }
   else if ( longestSide == 1 && shortestSide == 2 )
      {
      VectorNegate( sides[ longestSide ] );
      VectorNegate( sides[ shortestSide ] );
      }
   else if ( longestSide == 2 && shortestSide == 0 )
      {
      VectorNegate( sides[ longestSide ] );
      VectorNegate( sides[ shortestSide ] );
      }
   else if ( longestSide == 2 && shortestSide == 1 )
      {
      }


	VectorNormalize( sides[longestSide], axes[0] );
	VectorNormalize( sides[shortestSide], axes[1] );

	// project shortest side so that it is exactly 90 degrees to the longer side
	d = DotProduct( axes[1], axes[0] );
	VectorMA( axes[1], -d, axes[0], axes[1] );
	VectorNormalize( axes[1], axes[1] );

	CrossProduct( sides[longestSide], sides[shortestSide], axes[2] );
	VectorNormalize( axes[2], axes[2] );

	pTag->origin[0] = pTri[origin][0];
	pTag->origin[1] = pTri[origin][1];
	pTag->origin[2] = pTri[origin][2];

	VectorCopy( axes[0], pTag->axis[0] );
	VectorCopy( axes[1], pTag->axis[1] );
	VectorCopy( axes[2], pTag->axis[2] );
}

//==============================================================

/*
** MyNormalToLatLong
**
** Lat = 0 at (1,0,0) to 360 (-1,0,0), encoded in 8-bit sine table format
** Lng = 0 at (0,0,1) to 180 (0,0,-1), encoded in 8-bit sine table format
**
** Latitude is encoded in high 8 bits
*/
static unsigned short MyNormalToLatLong( vec3_t normal )
{
	unsigned short ll;

	// check for singularities
	if ( normal[0] == 0 && normal[1] == 0 )
	{
		if ( normal[2] > 0 )
		{
			ll = 0;			// lat = 0, long = 0
		}
		else
		{
			ll = 128;			// lat = 0, long = 128
		}
	}
	else
	{
		unsigned short a, b;

		a = RAD2DEG( atan2( normal[1], normal[0] ) ) * (255.0f / 360.0f );
		a &= 0xff;

		b = RAD2DEG( acos( normal[2] ) ) * ( 255.0f / 360.0f );
		b &= 0xff;

		ll = ( a << 8 ) | b;
	}

	return ll;
}

/*
===============
ClearModel
===============
*/
void ClearModel (void)
{
	int i;

	g_data.type = 0;

	for ( i = 0; i < TIKI_MAX_SURFACES * 2; i++ )
	{
		memset( &g_data.surfData[i].header, 0, sizeof( g_data.surfData[i].header ) );
		memset( &g_data.surfData[i].shaders, 0, sizeof( g_data.surfData[i].shaders ) );
		memset( &g_data.surfData[i].verts, 0, sizeof( g_data.surfData[i].verts ) );
	}

	memset( g_data.tags, 0, sizeof( g_data.tags ) );
	memset( g_data.tagdata, 0, sizeof( g_data.tagdata ) );
	memset( g_data.origins, 0, sizeof( g_data.origins ) );

	for ( i = 0; i < g_data.model.numSurfaces; i++ )
	   {
		int j;

		for ( j = 0; j < g_data.model.numFrames; j++ )
         {
      	if ( g_data.surfData[i].verts[j] )
            {
            free( g_data.surfData[i].verts[j] );
            g_data.surfData[i].verts[j] = NULL;
            }
         }
	   }

	memset (&g_data.model, 0, sizeof(g_data.model));
	memset (g_cddir, 0, sizeof(g_cddir));

	g_modelname[0] = 0;
	g_data.scale_up = 1.0;	
	memset( &g_data.model, 0, sizeof( g_data.model ) );
	VectorCopy (vec3_origin, g_data.adjust);
	g_data.fixedwidth = g_data.fixedheight = 0;
   g_data.originname[ 0 ] = 0;
}

/*
** void WriteModelSurface( FILE *modelouthandle, md3SurfaceData_t *pSurfData )
**
** This routine assumes that the file position has been adjusted
** properly prior to entry to point at the beginning of the surface.
**
** Since surface header information is completely relative, we can't
** just randomly seek to an arbitrary surface location right now.  Is
** this something we should add?
*/
void WriteModelSurface( FILE *modelouthandle, md3SurfaceData_t *pSurfData )
{
	tikiSurface_t	*pSurf = &pSurfData->header;
	md3Shader_t		*pShader = pSurfData->shaders;
	baseVertex_t	*pBaseVertex = pSurfData->baseVertexes;
	float			**verts = pSurfData->verts;

	short xyznormals[TIKI_MAX_VERTS][4];

	float base_st[TIKI_MAX_VERTS][2];
	tikiSurface_t surftemp;

	int f, i, j, k, index;

	if (
         ( strstr( pSurf->name, "tag_" ) == pSurf->name ) ||
		   ( !strcmpi( g_data.originname, pSurf->name ) )
      )
      return;

	//
	// write out the header
	//
	surftemp = *pSurf;
	surftemp.ident = LittleLong( TIKI_ANIM_IDENT );
	surftemp.numFrames = LittleLong( pSurf->numFrames );

   surftemp.minLod = LittleLong( pSurf->minLod );

	surftemp.ofsTriangles = LittleLong( pSurf->ofsTriangles );
	surftemp.numTriangles = LittleLong( pSurf->numTriangles );

   surftemp.ofsCollapseMap = LittleLong( pSurf->ofsCollapseMap );

	surftemp.ofsSt = LittleLong( pSurf->ofsSt );
	surftemp.ofsXyzNormals = LittleLong( pSurf->ofsXyzNormals );
	surftemp.ofsEnd = LittleLong( pSurf->ofsEnd );

	SafeWrite( modelouthandle, &surftemp, sizeof( surftemp ) );

	if ( g_verbose )
	{
		printf( "surface '%s'\n", pSurf->name );
	}

	//
	// write out the triangles
	//
	for ( i = 0 ; i < pSurf->numTriangles ; i++ ) 
	{
		for (j = 0 ; j < 3 ; j++) 
		{
         if ( g_lod )
            {
			   int ivalue = LittleLong( pSurfData->permutationMap[ pSurfData->orderedTriangles[i][j] ] );
			   pSurfData->orderedTriangles[i][j] = ivalue;
            }
         else
            {
            int ivalue = LittleLong( pSurfData->orderedTriangles[i][j] );
            pSurfData->orderedTriangles[i][j] = ivalue;
            }
		}
	}

	SafeWrite( modelouthandle, pSurfData->orderedTriangles, pSurf->numTriangles * sizeof( g_data.surfData[0].orderedTriangles[0] ) );

	if ( g_verbose )
	{
		printf( "\n...num verts: %d\n", pSurf->numVerts );
		printf( "...COLLAPSE MAP\n" );
	}

	//
	// write out the collapse map
	//
	for ( i = 0 ; i < pSurf->numVerts; i++ ) 
	{
		{
         if ( g_lod )
            {
			   int ivalue = LittleLong( pSurfData->collapseMap[i] );
			   pSurfData->collapseMap[i] = ivalue;
            }
         else
            {
			   pSurfData->collapseMap[i] = LittleLong( i );;
            }
		}
	}

	SafeWrite( modelouthandle, pSurfData->collapseMap, pSurf->numVerts * sizeof( g_data.surfData[0].collapseMap[0] ) );

	if ( g_verbose )
	{
		printf( "...TEX COORDINATES\n" );
	}

   //
	// write out the texture coordinates
	//
	for ( i = 0; i < pSurf->numVerts ; i++) {
      if ( g_lod )
         {
         // reorder the verts for lod as we write them out
         index = pSurfData->permutationMap[ i ];
		   base_st[index][0] = LittleFloat( pBaseVertex[i].st[0] );
		   base_st[index][1] = LittleFloat( pBaseVertex[i].st[1] );
		   if ( g_verbose )
			   printf( "......%d: %f,%f\n", i, base_st[index][0], base_st[index][1] );
         }
      else
         {
		   base_st[i][0] = LittleFloat( pBaseVertex[i].st[0] );
		   base_st[i][1] = LittleFloat( pBaseVertex[i].st[1] );
		   if ( g_verbose )
			   printf( "......%d: %f,%f\n", i, base_st[i][0], base_st[i][1] );
         }
	}
	SafeWrite( modelouthandle, base_st, pSurf->numVerts * sizeof(base_st[0]));

	//
	// write the xyz_normal
	//
	if ( g_verbose )
		printf( "...XYZNORMALS\n" );
	for ( f = 0; f < g_data.model.numFrames; f++ )
	{
		for (j=0 ; j< pSurf->numVerts; j++) 
		{
         float fvalue;
			short value;

         if ( g_lod )
            {
            // reorder the verts for lod as we write them out
            index = pSurfData->permutationMap[ j ];
            }
         else
            {
            index = j;
            }
			for (k=0 ; k < 3 ; k++) 
			{
				fvalue = verts[f][j*6+k] - g_data.frames[ f ].offset[ k ];
				value = ( short ) ( fvalue / g_data.frames[ f ].scale[ k ] );
				xyznormals[index][k] = LittleShort( value );
			}
			value = MyNormalToLatLong( &verts[f][j*6+3] );
			xyznormals[index][3] = LittleShort( value );
		}
		SafeWrite( modelouthandle, xyznormals, pSurf->numVerts * sizeof( short ) * 4 );
	}
}

int numRealSurfaces;
/*
** void WriteModelFile( FILE *modelouthandle )
**
** CHUNK			SIZE
** header			sizeof( md3Header_t )
** frames			sizeof( tikiFrame_t ) * numFrames
** tags				sizeof( tikiTag_t ) * numTags + sizeof( tikiTagData_t ) * numFrames * numTags
** surfaces			surfaceSum
*/
void WriteModelFile( FILE *modelouthandle )
{
	int				f, t;
	int				i, j;
	tikiHeader_t		modeltemp;
	long			surfaceSum = 0;
	int				numFrames = g_data.model.numFrames;
   int            ofstemp;
   vec3_t         totaldelta;

   numRealSurfaces = 0 ;
	// compute offsets for all surfaces, sum their total size
	for ( i = 0; i < g_data.model.numSurfaces; i++ )
	{
		if (
            ( strstr( g_data.surfData[i].header.name, "tag_" ) != g_data.surfData[i].header.name ) &&
		      ( strcmpi( g_data.originname, g_data.surfData[i].header.name ) )
         )
		{
			tikiSurface_t *psurf = &g_data.surfData[i].header;

			if ( psurf->numTriangles == 0 || psurf->numVerts == 0 )
				continue;

			//
			// the triangle and vertex split threshold is controlled by a parameter
			// to $base, a la $base blah.3ds 1900, where "1900" determines the number
			// of triangles to split on
			//
			else if ( psurf->numVerts > MAX_SURFACE_VERTS )
			{
				Error( "too many vertices\n" );
			}

			psurf->numFrames = numFrames;

			if ( psurf->numTriangles > MAX_SURFACE_TRIS  ) 
			{
				Error( "too many faces\n" );
			}

			psurf->ofsTriangles = sizeof( tikiSurface_t );

         psurf->ofsCollapseMap = psurf->ofsTriangles + psurf->numTriangles * sizeof( md3Triangle_t );

			psurf->ofsSt = psurf->ofsCollapseMap + psurf->numVerts * sizeof( int );
			psurf->ofsXyzNormals = psurf->ofsSt + psurf->numVerts * sizeof( md3St_t );
			psurf->ofsEnd = psurf->ofsXyzNormals + psurf->numFrames * psurf->numVerts * ( sizeof( short ) * 4 );

			surfaceSum += psurf->ofsEnd;

			numRealSurfaces++;
		}
	}

	g_data.model.ident = TIKI_ANIM_IDENT;
	g_data.model.version = TIKI_ANIM_VERSION;

	g_data.model.ofsFrames = sizeof(tikiHeader_t);
	ofstemp = g_data.model.ofsFrames + numFrames*sizeof(tikiFrame_t);
	for ( t = 0; t < g_data.model.numTags; t++ )
      {
   	g_data.model.ofsTags[ t ] = ofstemp;
      ofstemp += sizeof(tikiTag_t);
      ofstemp += numFrames*sizeof(tikiTagData_t);
      }
	g_data.model.ofsSurfaces = ofstemp;
	g_data.model.ofsEnd = g_data.model.ofsSurfaces + surfaceSum;

   // was it optimized
	//g_data.model.optimized = g_optimize;

   // calculate total delta
   VectorSubtract( g_data.origins[ numFrames - 1 ], g_data.origins[ 0 ], g_data.model.totaldelta );

   // calculate total time
   g_data.model.totaltime = ( float )numFrames / g_data.framerate;

	//
	// write out the model header
	//
	modeltemp = g_data.model;
	modeltemp.ident = LittleLong( modeltemp.ident );
	modeltemp.version = LittleLong( modeltemp.version );
	modeltemp.numFrames = LittleLong( modeltemp.numFrames );
	modeltemp.numTags = LittleLong( modeltemp.numTags );
	modeltemp.numSurfaces = LittleLong( numRealSurfaces );
	modeltemp.ofsFrames = LittleLong( modeltemp.ofsFrames );
	for ( t = 0; t < g_data.model.numTags; t++ )
      {
   	modeltemp.ofsTags[ t ] = LittleLong( modeltemp.ofsTags[ t ] );
      }
	modeltemp.ofsSurfaces = LittleLong( modeltemp.ofsSurfaces );
	modeltemp.ofsEnd = LittleLong( modeltemp.ofsEnd );
	modeltemp.totaltime = LittleFloat( modeltemp.totaltime );
   for ( i = 0; i < 3; i++ )
      {
   	modeltemp.totaldelta[ i ] = LittleFloat( modeltemp.totaldelta[ i ] );
      }

	SafeWrite (modelouthandle, &modeltemp, sizeof(modeltemp));

   // clear out totaldelta
   VectorClear( totaldelta );

	//
	// write out the frames
	//
	for (i=0 ; i < numFrames ; i++) 
	{
		vec3_t tmpVec;
		float maxRadius = 0;

		//
		// compute localOrigin and radius
		//
		for ( j = 0; j < 8; j++ )
		{
			tmpVec[0] = g_data.frames[i].bounds[(j&1)!=0][0];
			tmpVec[1] = g_data.frames[i].bounds[(j&2)!=0][1];
			tmpVec[2] = g_data.frames[i].bounds[(j&4)!=0][2];

			if ( VectorLength( tmpVec ) > maxRadius )
				maxRadius = VectorLength( tmpVec );
		}

		g_data.frames[i].radius = LittleFloat( maxRadius );
		g_data.frames[i].frametime = LittleFloat( g_data.frames[i].frametime );
   	for (j=0 ; j<3 ; j++)
      	{
			g_data.frames[i].scale[j] = ( g_data.frames[i].bounds[1][j] - g_data.frames[i].bounds[0][j] ) / 65535.0f;
			g_data.frames[i].offset[j] = g_data.frames[i].bounds[0][j];
	      }

      // calculate deltas
      if ( i < ( numFrames - 1 ) )
         {
   	   for (j=0 ; j<3 ; j++)
      	   {
			   g_data.frames[i].delta[j] = g_data.origins[ i + 1 ][ j ]  - g_data.origins[ i ][ j ];
            }
         VectorAdd( totaldelta, g_data.frames[ i ].delta, totaldelta );
         }
      else
         {
         // fudge the last frame
         if ( numFrames > 1 )
            {
            VectorScale( totaldelta, 1.0f / ( numFrames - 1 ), g_data.frames[i].delta );
            }
         else
            {
            VectorClear( totaldelta );
            }
         }

		// swap
		for (j=0 ; j<3 ; j++) {
			g_data.frames[i].scale[j] = LittleFloat( g_data.frames[i].scale[j] );
			g_data.frames[i].offset[j] = LittleFloat( g_data.frames[i].offset[j] );
			g_data.frames[i].delta[j] = LittleFloat( g_data.frames[i].delta[j] );
			g_data.frames[i].bounds[0][j] = LittleFloat( g_data.frames[i].bounds[0][j] );
			g_data.frames[i].bounds[1][j] = LittleFloat( g_data.frames[i].bounds[1][j] );
		}
	}
	fseek (modelouthandle, g_data.model.ofsFrames, SEEK_SET);
	SafeWrite( modelouthandle, g_data.frames, numFrames * sizeof(g_data.frames[0]) );

	//
	// write out the tags
	//
	for ( t = 0; t < g_data.model.numTags; t++ )
   	{
	   for (f=0 ; f<g_data.model.numFrames; f++) 
	      {
			g_data.tagdata[t][f].origin[0] = LittleFloat(g_data.tagdata[t][f].origin[0]);
			g_data.tagdata[t][f].origin[1] = LittleFloat(g_data.tagdata[t][f].origin[1]);
			g_data.tagdata[t][f].origin[2] = LittleFloat(g_data.tagdata[t][f].origin[2]);

			for (j=0 ; j<3 ; j++) 
			   {
				g_data.tagdata[t][f].axis[0][j] = LittleFloat(g_data.tagdata[t][f].axis[0][j]);
				g_data.tagdata[t][f].axis[1][j] = LittleFloat(g_data.tagdata[t][f].axis[1][j]);
				g_data.tagdata[t][f].axis[2][j] = LittleFloat(g_data.tagdata[t][f].axis[2][j]);
			   }
		   }
   	fseek( modelouthandle, g_data.model.ofsTags[ t ], SEEK_SET );
		SafeWrite( modelouthandle, &g_data.tags[t], sizeof(tikiTag_t) );
		SafeWrite( modelouthandle, g_data.tagdata[t], g_data.model.numFrames * sizeof(tikiTagData_t) );
   	}

	//
	// fixup the scale and offset parameters
	//
	for (i=0 ; i < numFrames ; i++) 
	   {
		// swap
		for (j=0 ; j<3 ; j++) 
         {
			g_data.frames[i].scale[j] = LittleFloat( g_data.frames[i].scale[j] );
			g_data.frames[i].offset[j] = LittleFloat( g_data.frames[i].offset[j] );
		   }
      }

	//
	// write out the surfaces
	//
	fseek( modelouthandle, g_data.model.ofsSurfaces, SEEK_SET );
	for ( i = 0; i < g_data.model.numSurfaces; i++ )
	{
		WriteModelSurface( modelouthandle, &g_data.surfData[i] );
	}
}


/*
===============
FinishModel
===============
*/
void FinishModel ( void )
{
	FILE		*modelouthandle;
	char		name[1024];

	if (!g_data.model.numFrames)
		return;

	//
	// build generalized triangle strips
	//
	OrderSurfaces();

	sprintf (name, "%s%s", writedir, g_modelname);

	//
	// write the model output file
	//
   if ( g_verbose )
	   printf ("saving to %s\n", name);
	CreatePath (name);
	modelouthandle = SafeOpenWrite (name);

	WriteModelFile (modelouthandle);
	
   if ( g_verbose )
      {
	   printf ("%4d surfaces\n", numRealSurfaces);
	   printf ("%4d frames\n", g_data.model.numFrames);
	   printf ("%4d tags\n", g_data.model.numTags);
	   printf ("file size: %d\n", (int)ftell (modelouthandle) );
	   printf ("---------------------\n");
      }
	
	fclose (modelouthandle);
}

/*
** OrderSurfaces
**
** Reorders triangles in all the surfaces.
*/
static void OrderSurfaces( void )
{
	int s;

	// go through each surface and find best strip/fans possible
	for ( s = 0; s < g_data.model.numSurfaces; s++ )
	{
		int mesh[TIKI_MAX_TRIANGLES][3];
		int i;

		if (
            ( strstr( g_data.surfData[ s ].header.name, "tag_" ) == g_data.surfData[ s ].header.name ) ||
		      ( !strcmpi( g_data.originname, g_data.surfData[ s ].header.name ) )
         )
         continue;

      if ( g_verbose )
         {
   		printf( "\nstripifying surface %16s %d/%d with %d tris\n", g_data.surfData[ s ].header.name, s+1, g_data.model.numSurfaces, g_data.surfData[s].header.numTriangles );
         }

		for ( i = 0; i < g_data.surfData[s].header.numTriangles; i++ )
		{
			mesh[i][0] = g_data.surfData[s].lodTriangles[i][0];
			mesh[i][1] = g_data.surfData[s].lodTriangles[i][1];
			mesh[i][2] = g_data.surfData[s].lodTriangles[i][2];
		}
		if ( g_optimize )
		{
			OrderMesh( mesh,									// input
					   g_data.surfData[s].orderedTriangles,		// output
					   g_data.surfData[s].header.numTriangles );
		}
		else
		{
			memcpy( g_data.surfData[s].orderedTriangles, mesh, sizeof( int ) * 3 * g_data.surfData[s].header.numTriangles );
		}
	}
}


/*
===============================================================

BASE FRAME SETUP

===============================================================
*/

static void BuildBaseFrame( const char *filename, baseframe_t * base )
{
	int i, j, t;

	// calculate the base triangles
	for ( i = 0; i < g_data.model.numSurfaces; i++ )
   	{
		for ( t = 0; t < base->surfaces[ i ].numtriangles; t++ )
         {
         for( j = 0; j < 3; j++ )
            {
            g_data.surfData[ i ].baseTriangles[ t ].v[ j ].index = base->surfaces[ i ].triangles[ t ].verts[ j ];
      		g_data.surfData[ i ].lodTriangles[ t ][ j ] = base->surfaces[ i ].triangles[ t ].verts[ j ];
            }
         }
		strcpy( g_data.surfData[i].header.name, base->surfaces[ i ].name );

		g_data.surfData[i].header.numTriangles = base->surfaces[ i ].numtriangles;
		g_data.surfData[i].header.numVerts = base->surfaces[ i ].numvertices;
      for( j = 0; j < base->surfaces[ i ].numvertices; j++ )
         {
   		g_data.surfData[ i ].baseVertexes[ j ].index = base->surfaces[ i ].triverts[ j ].map;
   		g_data.surfData[ i ].baseVertexes[ j ].st[ 0 ] = base->surfaces[ i ].triverts[ j ].tex[ 0 ];
   		g_data.surfData[ i ].baseVertexes[ j ].st[ 1 ] = base->surfaces[ i ].triverts[ j ].tex[ 1 ];
         VectorCopy( base->surfaces[ i ].triverts[ j ].xyz.xyz, g_data.surfData[ i ].baseVertexes[ j ].xyz );
         VectorCopy( base->surfaces[ i ].triverts[ j ].xyz.normal, g_data.surfData[ i ].baseVertexes[ j ].normal );
         }
      CalculateLOD( &g_data.surfData[i] );
   	}

	//
	// find tags
	//
	for ( i = 0; i < g_data.model.numSurfaces; i++ )
	{
      if (
		      ( strcmpi( g_data.originname, g_data.surfData[ i ].header.name ) ) &&
		      ( strstr( g_data.surfData[ i ].header.name, "tag_" ) == g_data.surfData[ i ].header.name )
         )
		   {
			if ( g_data.surfData[ i ].header.numTriangles != 1 )
			{
				Error( "tag polysets must consist of only one triangle, tag %s", g_data.surfData[ i ].header.name );
			}
         if ( g_verbose )
            {
   			printf( "found tag '%s'\n", g_data.surfData[ i ].header.name );
            }
			g_data.model.numTags++;
		}
	}

}


static void BuildAnimation
   ( 
   const char *filename, 
   baseframe_t * base,
   animframe_t * anim,
   int numFrames, 
   float framerate
   )
   {
	int f, i, j, t, tagcount, index;
	float *frameXyz;
	float *frameNormals;

	g_data.model.numSurfaces = base->numSurfaces;
	g_data.model.numFrames = numFrames;
	if ( g_data.model.numFrames >= TIKI_MAX_FRAMES)
		Error ("model.numFrames >= TIKI_MAX_FRAMES");

	// build base frame
	BuildBaseFrame( filename, base );

	// build animation frames
	for ( f = 0; f < numFrames; f++ )
	   {
		animframe_t    *panim = &anim[f];
		qboolean	      parentTagExists = qfalse;
		tikiTagData_t	tagParent;
		int			   numtags = 0;
		tikiFrame_t		*fr;
		
		fr = &g_data.frames[f];

      // set frame time
      fr->frametime = 1.0f / framerate;
		
      VectorClear( g_data.origins[ f ] );
		
		//
		// find and count tags, locate parent tag
		//
		for ( i = 0; i < g_data.model.numSurfaces; i++ )
		   {
			if (
		         ( !strcmpi( g_data.originname, g_data.surfData[ i ].header.name ) ) ||
		         ( strstr( g_data.surfData[ i ].header.name, "tag_" ) == g_data.surfData[ i ].header.name )
            )

			   {
            // store off origin info
		      if ( !strcmpi( g_data.originname, g_data.surfData[ i ].header.name ) )
               {
					float basetri[3][3];
					float tri[3][3];
					
					if ( parentTagExists )
						Error( "Multiple parent tags not allowed" );
	
               for( j = 0; j < 3; j++ )
                  {
                  index = g_data.surfData[ i ].baseVertexes[ g_data.surfData[ i ].baseTriangles[ 0 ].v[ j ].index ].index;
                  VectorCopy( panim->verts[ index ].xyz, tri[ j ] );
                  }

               for( j = 0; j < 3; j++ )
                  {
                  VectorCopy( g_data.surfData[ i ].baseVertexes[ g_data.surfData[ i ].baseTriangles[ 0 ].v[ j ].index ].xyz, basetri[ j ] );
                  }
					
					TIKI_ComputeTagFromTri( &tagParent, tri, basetri );
					//strcpy( tagParent.name, "origin" );
					//g_data.tags[f][numtags] = tagParent;
					parentTagExists = qtrue;
               if ( g_clampz && tagParent.origin[ 2 ] < 0 )
                  {
                  tagParent.origin[ 2 ] = 0;
                  }            
               if ( g_zeroz )
                  {
                  tagParent.origin[ 2 ] = 0;
                  }           
               if ( g_noorigin )
                  {
                  parentTagExists = qfalse;
                  VectorClear( tagParent.origin );
                  }

               VectorCopy( tagParent.origin, g_data.origins[ f ] );
               if ( g_clearxy )
                  {
                  // subtract forward and side movement from deltas 
                  g_data.origins[ f ][ 0 ] = 0;
                  g_data.origins[ f ][ 1 ] = 0;
                  }
               if ( g_clearz )
                  {
                  g_data.origins[ f ][ 2 ] = 0;
                  }
   				}
				else
   				{
					float basetri[3][3];
					float tri[3][3];
				
               for( j = 0; j < 3; j++ )
                  {
                  index = g_data.surfData[ i ].baseVertexes[ g_data.surfData[ i ].baseTriangles[ 0 ].v[ j ].index ].index;
                  VectorCopy( panim->verts[ index ].xyz, tri[ j ] );
                  }

               for( j = 0; j < 3; j++ )
                  {
                  VectorCopy( g_data.surfData[ i ].baseVertexes[ g_data.surfData[ i ].baseTriangles[ 0 ].v[ j ].index ].xyz, basetri[ j ] );
                  }
					
					TIKI_ComputeTagFromTri( &g_data.tagdata[numtags][f], tri, basetri );
					strcpy( g_data.tags[numtags].name, g_data.surfData[ i ].header.name );
   				numtags++;
	   			}
            }
			}
		
		if ( numtags != g_data.model.numTags )
   		{
			Error( "mismatched number of tags in frame(%d) vs. base(%d)", numtags, g_data.model.numTags );
	   	}
		
		//
		// prepare to accumulate bounds and normals
		//
		ClearBounds( fr->bounds[0], fr->bounds[1] );
		
		//
		// store the frame's vertices in the same order as the base. This assumes the
		// triangles and vertices in this frame are in exactly the same order as in the
		// base
		//

		//
		// parent tag adjust
		//
		if ( parentTagExists ) 
	   	{
			for ( t = 0; t < panim->numverts; t++ )
   			{
				vec3_t tmp;
				
#if 1
				VectorSubtract( panim->verts[ t ].xyz, tagParent.origin, tmp );
				
				panim->verts[ t ].xyz[0] = DotProduct( tmp, tagParent.axis[0] );
				panim->verts[ t ].xyz[1] = DotProduct( tmp, tagParent.axis[1] );
				panim->verts[ t ].xyz[2] = DotProduct( tmp, tagParent.axis[2] );
#else
            VectorCopy( panim->verts[ t ].xyz, tmp );

				panim->verts[ t ].xyz[0] = DotProduct( tmp, tagParent.axis[0] );
				panim->verts[ t ].xyz[1] = DotProduct( tmp, tagParent.axis[1] );
				panim->verts[ t ].xyz[2] = DotProduct( tmp, tagParent.axis[2] );
				VectorSubtract( panim->verts[ t ].xyz, tagParent.origin, panim->verts[ t ].xyz );
#endif
				
				VectorCopy( panim->verts[ t ].normal, tmp );
				panim->verts[ t ].normal[0] = DotProduct( tmp, tagParent.axis[0] );
				panim->verts[ t ].normal[1] = DotProduct( tmp, tagParent.axis[1] );
				panim->verts[ t ].normal[2] = DotProduct( tmp, tagParent.axis[2] );
			   }
		   }
      
		for ( i = 0, tagcount = 0; i < g_data.model.numSurfaces; i++ )
		   {
			int t;

			//
			// compute tag data
			//
			if (
		         ( strcmpi( g_data.originname, g_data.surfData[ i ].header.name ) ) &&
		         ( strstr( g_data.surfData[ i ].header.name, "tag_" ) == g_data.surfData[ i ].header.name )
            )
	   		{
				tikiTag_t *pTag = &g_data.tags[tagcount];
				tikiTagData_t *pTagData = &g_data.tagdata[tagcount][f];
				float tri[3][3];
				float basetri[3][3];
				
				strcpy( pTag->name, g_data.surfData[ i ].header.name );
				
            for( j = 0; j < 3; j++ )
               {
               index = g_data.surfData[ i ].baseVertexes[ g_data.surfData[ i ].baseTriangles[ 0 ].v[ j ].index ].index;
               VectorCopy( panim->verts[ index ].xyz, tri[ j ] );
               }
            for( j = 0; j < 3; j++ )
               {
               VectorCopy( g_data.surfData[ i ].baseVertexes[ g_data.surfData[ i ].baseTriangles[ 0 ].v[ j ].index ].xyz, basetri[ j ] );
               }
				
				TIKI_ComputeTagFromTri( pTagData, tri, basetri );
				tagcount++;
		   	}
			else
			   {
				if ( g_data.surfData[i].verts[f] )
					free( g_data.surfData[i].verts[f] );
				frameXyz = g_data.surfData[i].verts[f] = calloc( 1, sizeof( float ) * 6 * g_data.surfData[i].header.numVerts );
				frameNormals = frameXyz + 3;
				
				for ( t = 0; t < g_data.surfData[ i ].header.numVerts; t++ )
				   {
					int index;
					
               index = g_data.surfData[ i ].baseVertexes[ t ].index;
					frameXyz[t*6+0] = panim->verts[ index ].xyz[0];
					frameXyz[t*6+1] = panim->verts[ index ].xyz[1];
					frameXyz[t*6+2] = panim->verts[ index ].xyz[2];
					frameNormals[t*6+0] =  panim->verts[ index ].normal[0];
					frameNormals[t*6+1] =  panim->verts[ index ].normal[1];
					frameNormals[t*6+2] =  panim->verts[ index ].normal[2];
					AddPointToBounds (&frameXyz[t*6], fr->bounds[0], fr->bounds[1] );
				   }
			   }
		   }
	   }

// set name
	strcpy (g_modelname, filename);
	strcpy (g_data.model.name, g_modelname);

	FinishModel();
	ClearModel();
   }


void ConvertAnim
   ( 
   const char *filename, 
   int numFrames, 
   float framerate, 
   qboolean optimize, 
   baseframe_t * base,
   animframe_t * anim,
   const char *originname,
   qboolean dolod,
   qboolean clampz,
   qboolean zeroz,
   qboolean clearz,
   qboolean clearxy,
   qboolean noorigin,
   qboolean verbose
   )
   {  
	char outfilename[1024];

	ClearModel();

   strcpy( g_data.originname, originname );
   g_lod = dolod;
   g_optimize = optimize;
   g_verbose = verbose;
   g_clampz = clampz;
   g_zeroz = zeroz;
   g_clearz = clearz;
   g_clearxy = clearxy;
   g_noorigin = noorigin;
	g_data.framerate = framerate;
	strcpy( outfilename, filename );
   // create destination filename
   StripExtension( outfilename );
	strcat( outfilename, ".tan" );
	BuildAnimation( outfilename, base, anim, numFrames, framerate );
   }

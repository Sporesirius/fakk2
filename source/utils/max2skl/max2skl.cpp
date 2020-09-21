//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2skl/max2skl.cpp                          $
// $Revision:: 38                                                             $
//     $Date:: 7/24/00 12:08p                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2skl/max2skl.cpp                               $
// 
// 38    7/24/00 12:08p Markd
// remove skipping origin code
// 
// 37    7/20/00 10:53p Markd
// added short offset format
// 
// 36    6/21/00 6:27p Markd
// added variable framerate support to max2skl
// 
// 35    6/16/00 4:15p Markd
// Added more error checking for exceeding max verts
// 
// 34    6/15/00 4:22p Markd
// reverted to original code
// 
// 33    6/15/00 2:58p Markd
// added ignoreflags by default
// 
// 32    6/12/00 4:26p Markd
// Added debugging messages
// 
// 31    6/09/00 6:22p Markd
// Added better error reporting 
// 
// 30    5/05/00 5:10p Jimdose
// x and y relevant commands had to be swapped because of
// ConvertToQuake3Worldspace
// 
// 29    5/05/00 3:58p Markd
// added debugging info
// 
// 28    5/05/00 3:37p Jimdose
// merged code
// added -ignoreflags for disabling keeping of parent bone when no other bone
// with the same flags is available
// 
// 6     5/02/00 5:47p Jimdose
// fixed bug in RemoveUnusedBones
// 
// 5     5/01/00 8:15p Pmack
// catch a crash and added some verbose info on bone removal.
// 
// 27    4/25/00 12:16p Jimdose
// merged changes
// added code to test for verts with no wieghts and set them to an average
// weight
// added -destdir and -uvb
// 
// 26    3/27/00 5:09p Jimdose
// changed check for MAX_BLENDBONES exceeded to MAX_LOADBLENDBONES exceeded
// 
// 3     4/17/00 2:55p Jimdose
// added ConvertToQuake3Worldspace
// added FixMirroredBones
// 
// 25    3/15/00 7:15p Jimdose
// added bounds tests for when adding verts and triangles to surfaces
// 
// 24    3/04/00 12:06p Jimdose
// added zerox and zeroy
// 
// 23    3/03/00 6:07p Jimdose
// added clearx, cleary, and loop commands
// 
// 22    3/03/00 11:21a Jimdose
// added -offset command
// 
// 21    2/26/00 1:31p Jimdose
// added -bones to the list of command line options
// 
// 20    2/01/00 6:37p Jimdose
// Tags were being taken into account when generating bounding boxes for frames
// 
// 19    1/19/00 7:36p Jimdose
// changed default non verbose output
// 
// 18    1/19/00 5:17p Jimdose
// CreateSurfaces now adds a new bone when it finds a tag that is named
// different than a preexisting bone
// ReduceBonesPerVertex now combines blends with same bone number into one on
// each vertex
// 
// 17    1/13/00 6:35p Jimdose
// made RemoveUnusedBones not remove bones with names that begin with "tag_"
// 
// 16    1/13/00 4:19p Jimdose
// fixed RemoveUnusedBones for when bone 0 is not scene root
// 
// 15    1/11/00 7:30p Jimdose
// added boneflags
// 
// 14    1/05/00 11:55a Jimdose
// nolod was incorrectly initialized to true
// no longer set triangle id to be the index of the surface it's on.  This
// caused triangles to sometimes be added to mutilple surfaces.
// 
// 13    11/03/99 3:15p Jimdose
// fixed problems with delta calculation
// 
// 12    10/20/99 2:50p Jimdose
// added CopyBones and -bones parm for animations where the heirarchy is
// different from the base model
// 
// 11    10/20/99 2:02p Jimdose
// fixed bug in SaveAnimation where converting to Q3 worldspace caused a
// roll-pitch swap in the game
// 
// 10    10/18/99 6:07p Jimdose
// changed error message to include filename
// made SaveBaseFrame allow for twice as many surfaces in base model, but only
// allow the normal amount in saved model
// 
// 9     10/14/99 6:37p Jimdose
// added the ability to export MD4 (Quake 3 skeletal) files
// 
// 8     10/11/99 5:50p Jimdose
// added ScaleModel, ReverseAnimation, ReduceBonesPerVertex, and
// RemoveUnusedBones
// 
// 7     10/08/99 7:19p Jimdose
// got tags and deltas working
// 
// 6     10/06/99 12:46p Jimdose
// added ComputeVertexNormals
// 
// 5     10/04/99 7:06p Jimdose
// moved lod to surfaces
// added radius to frames
// read texture coordinates from UV file
// 
// 4     9/27/99 5:01p Jimdose
// fixed some errors in saving animations
// 
// 3     9/27/99 11:39a Jimdose
// changed TIKI_ANIM_IDENT to TIKI_SKEL_ANIM_IDENT
// 
// 2     9/24/99 4:39p Jimdose
// first working version
//
// DESCRIPTION:
// 

#include "max2skl.h"
#include "str.h"
#include "progmesh.h"
#include "uvector3.h"
#include "umatrix.h"
#include "uquat.h"

double   scale_factor;
bool     nolod;
bool     zerox;
bool     zeroy;
bool     zeroz;
bool     noclampz;
bool     clearx;
bool     cleary;
bool     clearz;
bool     loop;
bool     clearxy;
bool     noorigin;
bool     reverse;
bool     force;
bool     baseframe;
bool     md4;
bool     ignoreflags;
bool     adjustfps;
float    fps;
UVector3 modeloffset;

str      originname( "origin" );

extern "C" void OrderMesh( int input[][3], int output[][3], int numTris );
extern "C" int main ( int argc, char * argv[] );

SkelModel::SkelModel()
   {
   memset( &model, 0, sizeof( model ) );
   }

SkelModel::~SkelModel()
   {
   FreeModel();
   }

void SkelModel::FreeModel
   (
   void
   )

   {
   int i;

   for( i = 0; i < model.numframes; i++ )
      {
      delete[] model.anim[ i ].bones;
      }

   delete[] model.verts;
   delete[] model.faces;
   delete[] model.anim;
   delete[] model.bones;
   delete[] model.surfaces;

   memset( &model, 0, sizeof( model ) );
   }

void SkelModel::LoadIgnoreFile
   (
   const char *filename
   )
   
   {
   Script script;

   printf(" reading ignore file %s.\n", filename );

   script.LoadFile( filename );
   while( script.TokenAvailable( true ) )
      {
      ignorelist.AddObject( str( script.GetToken( true ) ) );
      }
   }

bool SkelModel::IgnoreSurface
   (
   const char *name
   )

   {
   int i;

   if ( !name || !strlen( name ) )
      {
      return false;
      }

   for( i = 1; i <= ignorelist.NumObjects(); i++ )
      {
      if ( !ignorelist.ObjectAt( i ).icmp( name ) )
         {
         return true;
         }
      }

   return false;
   }

void SkelModel::LoadSKL
   (
   const char *filename
   )
   
   {
   Script   script;
   int      version;

   FreeModel();

   memset( model.name, 0, sizeof( model.name ) );
   strncpy( model.name, filename, sizeof( model.name ) - 1 );

   VectorClear( model.totaldelta );

   script.LoadFile( filename );
   
   script.Skip( "SKELETON" );
   script.Skip( "VERSION" );
   
   version = script.GetInteger( false );
   if ( version != SKL_VERSION )
      {
      script.Error( "Expecting version %d but found version %d.\n", SKL_VERSION, version );
      }

   LoadSurfaces( script );
   LoadBones( script );
   LoadVerts( script );
   LoadFaces( script );
   LoadFrames( script );

   script.Skip( "END" );
   }

void SkelModel::LoadSurfaces
   (
   Script &script
   )

   {
   int         i;
   surface_t   *surf;
   int         num;

   // skip over nummaterials
   script.Skip( "NUMMATERIALS" );

   // get number of materials
   num = script.GetInteger( false );

   delete[] model.surfaces;
   model.surfaces = new surface_t[ num ];
   memset( model.surfaces, 0, sizeof( surface_t ) * num );

   // get the surfaces
   model.numsurfaces = 0;
   for( i = 0; i < num; i++ )
      {
      // skip over "MATERIAL"
      script.Skip( "MATERIAL" );

      surf = &model.surfaces[ model.numsurfaces ];

      // get the surface id
      surf->id = script.GetInteger( false );

      // get the surface name
      memset( surf->name, 0, MAX_QPATH );
      strncpy( surf->name, script.GetToken( false ), MAX_QPATH - 1 );

      if ( !IgnoreSurface( surf->name ) )
         {
         // add this surface
         model.numsurfaces++;
         }
      }
   }

void SkelModel::LoadBones
   (
   Script &script
   )

   {
   skelBoneName_t *bone;
   int            i;
   int            bonenum;
   str            bonetype;

   script.Skip( "NUMBONES" );
   model.numbones = script.GetInteger( false );

   if ( model.numbones > MAX_BONES )
      {
      script.Error( "Too many bones in model.  Numbones cannot exceed %d.", MAX_BONES );
      }

   delete[] model.bones;
   model.bones = new skelBoneName_t[ model.numbones ];

   bone = model.bones;
   for( i = 0; i < model.numbones; i++, bone++ )
      {
	   bonetype = script.GetToken( true );
      if ( bonetype == "BONE" )
         {
         bone->flags = 0;
         }
      else if ( bonetype == "LEGBONE" )
         {
         bone->flags = TIKI_BONEFLAG_LEG;
         }
      else
         {
         script.Error( "Expecting 'BONE' or 'LEGBONE', but found ", bonetype.c_str() );
         }

      bonenum = script.GetInteger( false );
      if ( bonenum != i )
         {
         script.Error( "Bone number out of sync" );
         }

      bone->parent = script.GetInteger( false );
      if ( ( bone->parent < -1 ) || ( bone->parent >= model.numbones ) )
         {
         script.Error( "Parent bone out of range" );
         }

      memset( bone->name, 0, sizeof( bone->name ) );
      strncpy( bone->name, script.GetRaw(), MAX_QPATH - 1 );
      }
   }

void SkelModel::LoadVerts
   (
   Script &script
   )

   {
   blendvert_t *blend;
   loadvertx_t *vert;
   int         j;
   int         i;
   int         v;

   script.Skip( "NUMVERTS" );
   model.numverts = script.GetInteger( false );

   delete[] model.verts;
   model.verts = new loadvertx_t[ model.numverts ];
   memset( model.verts, 0, sizeof( loadvertx_t ) * model.numverts );

   vert = model.verts;
   for( i = 0; i < model.numverts; i++, vert++ )
      {
      script.Skip( "VERT" );
      v = script.GetInteger( false );
      if ( v != i )
         {
         script.Error( "Vertex number out of sync" );
         }

      vert->index = i;
      vert->texCoords[ 0 ] = 0;
      vert->texCoords[ 1 ] = 0;

      script.Skip( "NORMAL" );
      script.GetVector( model.verts[ i ].normal, false );

      script.Skip( "BONES" );
      vert->numbones = script.GetInteger( false );
      if ( vert->numbones >= MAX_LOADBLENDBONES )
         {
         Error( "Exceeded %d bones on vertex %d\n", MAX_LOADBLENDBONES, i );
         }

      blend = vert->blend;
      for( j = 0; j < vert->numbones; j++, blend++ )
         {
         script.Skip( "BONE" );
         
         blend->bone    = script.GetInteger( false );
         blend->weight  = script.GetFloat( false );
         script.GetVector( blend->offset, false );
         }
      }
   }

void SkelModel::LoadFaces
   (
   Script &script
   )

   {
   loadfacevertx_t *facevert;
   loadtriangle_t  *face;
   int             j;
   int             i;

   script.Skip( "NUMFACES" );
   model.numfaces = script.GetInteger( false );

   delete[] model.faces;
   model.faces = new loadtriangle_t[ model.numfaces ];

   face = model.faces;
   for( i = 0; i < model.numfaces; i++, face++ )
      {
      script.Skip( "TRI" );
      face->id = script.GetInteger( false );

      facevert = face->verts;
      for( j = 0; j < 3; j++, facevert++ )
         {
         facevert->vertindex = script.GetInteger( false );
         if ( ( facevert->vertindex < 0 ) || ( facevert->vertindex >= model.numverts ) )
            {
            script.Error( "Vertex index out of range" );
            }

         facevert->texCoords[ 0 ] = script.GetFloat( false );
         facevert->texCoords[ 1 ] = script.GetFloat( false );
         }
      }
   }

void SkipFrame
   (
   Script &script,
   int numbones
   )
   {
   int j;

   // get frame header
   script.Skip( "FRAME" );
   // skip frame number
   script.GetInteger( false );
   for( j = 0; j < numbones; j++ )
      {
      vec3_t vec;
      script.Skip( "BONE" );
      // skip bone number
      script.GetInteger( false );
      script.Skip( "OFFSET" );
      // skip offset
      script.GetVector( vec, false );
      script.Skip( "X" );
      // skip x
      script.GetVector( vec, false );
      script.Skip( "Y" );
      // skip y
      script.GetVector( vec, false );
      script.Skip( "Z" );
      // skip z
      script.GetVector( vec, false );
      }
   }


void SkelModel::LoadFrames
   (
   Script &script
   )

   {
   loadbone_t  *bone;
   int         k;
   int         j;
   int         i;
   int         frame;
   int         b;
   int         factor;
   int         realframe;
   int         orig_numframes;

   for( i = 0; i < model.numframes; i++ )
      {
      delete[] model.anim[ i ].bones;
      }
   delete[] model.anim;

   script.Skip( "FRAMERATE" );
   model.framerate = script.GetFloat( false );

   script.Skip( "NUMFRAMES" );
   model.numframes = script.GetInteger( false );

   orig_numframes = model.numframes;

   if ( adjustfps )
      {
      factor = ( int )( ( model.framerate / fps ) + 0.5f );
      if ( factor < 1 )
         factor = 1;
      model.framerate /= factor;
      if ( model.framerate < 1 )
         {
         model.framerate = 1;
         }
      model.numframes /= factor;
      if ( model.numframes < 1 )
         {
         model.numframes = 1;
         }
      }
   else
      {
      factor = 1;
      }

   model.anim = new loadframe_t[ model.numframes ];

   realframe = 0;

   for( i = 0; i < model.numframes; i++ )
      {
      script.Skip( "FRAME" );
      frame = script.GetInteger( false ) / factor;
      if ( frame != i )
         {
         script.Error( "Frame number out of sync" );
         }

      model.anim[ i ].bones = new loadbone_t[ model.numbones ];
      bone = model.anim[ i ].bones;

      ClearBounds( model.anim[ i ].bounds[ 0 ], model.anim[ i ].bounds[ 1 ] );

      VectorClear( model.anim[ i ].delta );
      VectorClear( model.anim[ i ].origin );

      for( j = 0; j < model.numbones; j++, bone++ )
         {
         script.Skip( "BONE" );
         b = script.GetInteger( false );
         if ( b != j )
            {
            script.Error( "Bone number out of sync" );
            }

         script.Skip( "OFFSET" );
         script.GetVector( bone->offset, false );

         script.Skip( "X" );
         script.GetVector( bone->matrix[ 0 ], false );

         script.Skip( "Y" );
         script.GetVector( bone->matrix[ 1 ], false );

         script.Skip( "Z" );
         script.GetVector( bone->matrix[ 2 ], false );
         }

      // increment our realframe
      realframe++;

      //
      // skip over any frames we might be skipping
      //
      for( k = 1; k < factor; k++ )
         {
         // make sure we don't read past the end of the data
         if ( realframe == orig_numframes )
            break;

         SkipFrame( script, model.numbones );

         // increment our realframe
         realframe++;

         }
      }
   for( ; realframe < orig_numframes; realframe++ )
      {
      SkipFrame( script, model.numbones );
      }
   }

void SkelModel::CopyBaseModel
   (
   SkelModel &base
   )

   {
   int i;

   // copy the materials
   delete[] model.surfaces;
   model.numsurfaces = base.model.numsurfaces;
   model.surfaces = new surface_t[ model.numsurfaces ];
   memcpy( model.surfaces, base.model.surfaces, sizeof( surface_t ) * model.numsurfaces );

   // get the faces
   if ( model.numfaces != base.model.numfaces )
      {
      Error( "Base model has different number of faces than model %s, re-export.\n", model.name );
      }

   for( i = 0; i < model.numfaces; i++ )
      {
      model.faces[ i ] = base.model.faces[ i ];
      }

   // get the verts
   if ( model.numverts != base.model.numverts )
      {
      Error( "Base model has different number of verts than model %s, re-export.\n", model.name );
      }
   }

void SkelModel::CopyBones
   (
   SkelModel &base
   )

   {
   loadvertx_t    *vert;
   loadframe_t    *frame;
   loadbone_t     framebones[ MAX_BONES ];
   int            bonemap[ MAX_BONES ];
   int            i;
   int            j;

   // get the bones
   if ( model.numbones != base.model.numbones )
      {
      Error( "%s has different number of bones than %s, re-export.\n", base.model.name, model.name );
      }

   // create a mapping to the new bone order
   for( i = 0; i < model.numbones; i++ )
      {
      for( j = 0; j < model.numbones; j++ )
         {
         if ( !str::icmp( model.bones[ i ].name, base.model.bones[ j ].name ) )
            {
            break;
            }
         }

      if ( j == model.numbones )
         {
         Error( "Bone '%s' not found in source model.\n", model.bones[ i ].name );
         }

      bonemap[ i ] = j;
      }

   // copy the bone heirarchy
   memcpy( model.bones, base.model.bones, sizeof( skelBoneName_t ) * model.numbones );

   // fixup the bone indices on the vertices
   vert = model.verts;
   for( i = 0; i < model.numverts; i++, vert++ )
      {
      for( j = 0; j < vert->numbones; j++ )
         {
         vert->blend[ j ].bone = bonemap[ vert->blend[ j ].bone ];
         }      
      }

   // fixup the bone order on the animation
   frame = model.anim;
   for( i = 0; i < model.numframes; i++, frame++ )
      {
      // save off the original frame
      memcpy( framebones, frame->bones, sizeof( loadbone_t ) * model.numbones );

      // store the bones off in the proper order
      for( j = 0; j < model.numbones; j++ )
         {
         frame->bones[ bonemap[ j ] ] = framebones[ j ];
         }
      }
   }

void SkelModel::LoadUVFile
   (
   const char *filename
   )

   {
   int         i;
   int         j;
   int         version;
   Script      script;
   surface_t   *surf;
   int         num;

   script.LoadFile( filename );

   // skip over version
   script.Skip( "version" );

   // get version number
   version = script.GetInteger( false );
   if ( version != UV_FILE_VERSION )
      {
      script.Error( "UV file is out of date, re-export.\n" );
      }

   // skip over nummaterials
   script.Skip( "nummaterials" );

   // get number of materials
   num = script.GetInteger( false );

   delete[] model.surfaces;
   model.surfaces = new surface_t[ num ];
   memset( model.surfaces, 0, sizeof( surface_t ) * num );

   // get the surfaces
   model.numsurfaces = 0;
   for( i = 0; i < num; i++ )
      {
      // skip over "material"
      script.Skip( "material" );

      surf = &model.surfaces[ model.numsurfaces ];

      // get the surface id
      surf->id = script.GetInteger( false );

      // get the surface name
      memset( surf->name, 0, MAX_QPATH );
      strncpy( surf->name, script.GetToken( false ), MAX_QPATH - 1 );

      if ( !IgnoreSurface( surf->name ) )
         {
         // add this surface
         model.numsurfaces++;
         }
      }

   // skip over numverts
   script.Skip( "numverts" );

   // get the number of verts
   num = script.GetInteger( false );
   if ( model.numverts != num )
      {
      script.Error( "UV file has different number of vertices than model %s, re-export.\n", model.name );
      }

   // skip the verts
   for( i = 0; i < model.numverts; i++ )
      {
      // skip the vertex
      script.GetFloat( true );
      script.GetFloat( false );
      script.GetFloat( false );
      }

   // skip over numfaces
   script.Skip( "numfaces" );

   // get the number of faces
   num = script.GetInteger( false );
   if ( model.numfaces != num )
      {
      script.Error( "UV file has different number of faces than model %s, re-export.\n", model.name );
      }

   // get the faces
   for( i = 0; i < model.numfaces; i++ )
      {
      // get the material id
      model.faces[ i ].id = script.GetInteger( true );

      // get the verts
      for( j = 0; j < 3; j++ )
         {
         // get the vertindex
         model.faces[ i ].verts[ j ].vertindex = script.GetInteger( false );

         // get texture coordinates
         model.faces[ i ].verts[ j ].texCoords[ 0 ] = script.GetFloat( false );
         model.faces[ i ].verts[ j ].texCoords[ 1 ] = script.GetFloat( false );
         }
      }
   }

void SkelModel::CreateSurfaces
   (
   void
   )

   {
   int               i;
   int               j;
   int               k;
   int               l;
   surface_t         *surf;
   loadvertx_t       *facevert;
   loadvertx_t       *vert;
   loadtriangle_t    *face;
   int               index;
   vec2_t            texCoords;

   // add the unique verts to each surface
   surf = model.surfaces;
   for( i = 0; i < model.numsurfaces; i++, surf++ )
      {
      surf->numtris = 0;
      surf->numverts = 0;

      // find all the faces that match this surface id
      face = model.faces;
      for( j = 0; j < model.numfaces; j++, face++ )
         {
         if ( surf->id == face->id )
            {
            if ( surf->numtris >= TIKI_MAX_TRIANGLES )
               {
               Error( "Exceeded %d triangles on surface '%s'\n", TIKI_MAX_TRIANGLES, surf->name );
               }

            // go through triangle and add each unique vertex
            for( l = 0; l < 3; l++ )
               {
               index = face->verts[ l ].vertindex;

               facevert = &model.verts[ index ];
               texCoords[ 0 ] = face->verts[ l ].texCoords[ 0 ];
               texCoords[ 1 ] = face->verts[ l ].texCoords[ 1 ];

               // see if it already exists
               vert = surf->verts;
               for( k = 0; k < surf->numverts; k++, vert++ )
                  {
					   if ( ( vert->index == index ) &&
                     ( vert->texCoords[ 0 ] == texCoords[ 0 ] ) &&
                     ( vert->texCoords[ 1 ] == texCoords[ 1 ] ) )
                     {
                     break;
                     }
                  }

               // if it wasn't found, add it in
               if ( k == surf->numverts )
                  {
                  if ( surf->numverts >= TIKI_MAX_VERTS )
                     {
                     Error( "Exceeded %d vertices on surface '%s'\n", TIKI_MAX_VERTS, surf->name );
                     }

                  *vert = model.verts[ index ];
                  vert->index = index;
                  vert->texCoords[ 0 ] = texCoords[ 0 ];
                  vert->texCoords[ 1 ] = texCoords[ 1 ];

                  surf->numverts++;
                  }

               surf->tris[ surf->numtris ][ l ] = k;
               }

            surf->numtris++;
            }
         }

      // initialize the collapse map for this surface
      surf->minLod = surf->numverts;
      for( j = 0; j < surf->numverts; j++ )
         {
         surf->collapseMap[ i ] = i;
         }
      }

   // faces are no longer valid, so delete them
   delete[] model.faces;
   model.faces = NULL;
   }

void SkelModel::CalcFrameBones
   (
   int framenum,
   UMat3 bones[ MAX_BONES ],
   UVector3 offsets[ MAX_BONES ]
   )

   {
   int         i;
   int         parent;
   loadframe_t *frame;
   loadbone_t  *bone;
   UMat3       mat;
   UVector3    offset;

   // do sanity check on the frame number
   if ( ( framenum < 0 ) || ( framenum >= model.numframes ) )
      {
      Error( "Frame %d out of range\n" );
      }

   // get the specified frame
   frame = &model.anim[ framenum ];

   // propogate the bone transformations
   bone = frame->bones;
   for( i = 0; i < model.numbones; i++, bone++ )
      {
      mat.vecs[ 0 ] = bone->matrix[ 0 ];
      mat.vecs[ 1 ] = bone->matrix[ 1 ];
      mat.vecs[ 2 ] = bone->matrix[ 2 ];
      
      offset = bone->offset;

      parent = model.bones[ i ].parent;
      if ( 1 )//parent < 0 )
         {
         bones[ i ] = mat;
         offsets[ i ] = offset;
         }
      else
         {
         assert( parent < i );
         bones[ i ].MultiplyMatrix( mat, bones[ parent ] );
         bones[ parent ].UnprojectVector( offset, offsets[ i ] );
         offsets[ i ] += offsets[ parent ];
         }
      }
   }

void SkelModel::CalcVerts
   (
   vec3_t *outverts,
   UMat3 bones[ MAX_BONES ],
   UVector3 offsets[ MAX_BONES ]
   )

   {
   int         i;
   int         j;
   loadvertx_t *vert;
   blendvert_t *blend;
   UVector3    offset;
   UVector3    temp;

   if ( model.numverts > TIKI_MAX_VERTS )
      {
      Error( "Too many vertices %d out of %d in model %s\n", model.numverts, TIKI_MAX_VERTS, model.name );
      }

   // blend the bones for each vertex to generate the final vertex position
   vert = model.verts;
   for( i = 0; i < model.numverts; i++, vert++ )
      {
      blend = vert->blend;

      // blend all the bones together for this vertex
      offset = UVector3::zero;
      for( j = 0; j < vert->numbones; j++, blend++ )
         {
         bones[ blend->bone ].UnprojectVector( blend->offset, temp );
         offset += ( offsets[ blend->bone ] + temp ) * blend->weight;
         }

      // store off the result in the buffer
      outverts[ i ][ 0 ] = offset[ 0 ];
      outverts[ i ][ 1 ] = offset[ 1 ];
      outverts[ i ][ 2 ] = offset[ 2 ];
      }
   }

void SkelModel::CalcFrame
   (
   int framenum,
   vec3_t *outverts
   )

   {
   UMat3 bones[ MAX_BONES ];
   UVector3 offsets[ MAX_BONES ];

   CalcFrameBones( framenum, bones, offsets );
   CalcVerts( outverts, bones, offsets );
   }

void SkelModel::ComputeVertexNormals
   (
   void
   )

   {
   UMat3       bones[ MAX_BONES ];
   UVector3    offsets[ MAX_BONES ];
   surface_t   *surf;
   UVector3    p;
   int         i;
   int         j;

   CalcFrameBones( 0, bones, offsets );

   surf = model.surfaces;
   for( i = 0; i < model.numsurfaces; i++, surf++ )
      {
      // convert vertices
	   for( j = 0; j < surf->numverts; j++ )
         {
         bones[ surf->verts[ j ].blend[ 0 ].bone ].ProjectVector( surf->verts[ j ].normal, p );
         
         surf->verts[ j ].normal[ 0 ] = p.x;
         surf->verts[ j ].normal[ 1 ] = p.y;
         surf->verts[ j ].normal[ 2 ] = p.z;
         }
	   }
   }

void SkelModel::CalculateLOD
   (
   void
   )

   {
	int	         i;
   int            j;
   int            minresolution;
   float          *vp;
   tridata        td;
   vec3_t         baseVerts[ TIKI_MAX_VERTS ];
   loadvertx_t    newverts[ TIKI_MAX_VERTS ];
   surface_t      *surf;

   CalcFrame( 0, baseVerts );

   surf = model.surfaces;
   for( j = 0; j < model.numsurfaces; j++, surf++ )
      {
      List<Vector>   verts;
      List<tridata>  tris;
      List<int>      permutation;
      List<int>      collapse_map;

      if ( surf->numverts > TIKI_MAX_VERTS )
         {
         Error( "Too many vertices %d out of %d on surface %s in model %s\n", surf->numverts, TIKI_MAX_VERTS, surf->name, model.name );
         }
      // convert vertices
	   for( i = 0; i < surf->numverts; i++ )
         {
		   vp = baseVerts[ surf->verts[ i ].index ];
		   verts.Add( Vector( vp[ 0 ], vp[ 1 ], vp[ 2 ] ) );
	      }

      // convert triangles
      for( i = 0; i < surf->numtris; i++ )
         {
		   td.v[ 0 ] = surf->tris[ i ][ 0 ];
         td.v[ 1 ] = surf->tris[ i ][ 1 ];
         td.v[ 2 ] = surf->tris[ i ][ 2 ];

		   tris.Add( td );
         }

      ProgressiveMesh( verts, tris, collapse_map, permutation, &minresolution );

	   assert( permutation.num == verts.num );
      assert( verts.num == surf->numverts );

      // copy the collapse map
      for( i = 0; i < surf->numverts; i++ )
         {
         surf->collapseMap[ i ] = collapse_map[ i ];
         }

      // reorder the vertices
      for( i = 0; i < surf->numverts; i++ )
         {
         newverts[ permutation[ i ] ] = surf->verts[ i ];
         }
      memcpy( surf->verts, newverts, surf->numverts * sizeof( surf->verts[ 0 ] ) ); 

      // reorder the vertex indices on the triangles
      for( i = 0; i < surf->numtris; i++ )
         {
		   surf->tris[ i ][ 0 ] = permutation[ surf->tris[ i ][ 0 ] ];
         surf->tris[ i ][ 1 ] = permutation[ surf->tris[ i ][ 1 ] ];
         surf->tris[ i ][ 2 ] = permutation[ surf->tris[ i ][ 2 ] ];
         }

      surf->minLod = minresolution;
      }
   }

void SkelModel::CalculateTriStrips
   (
   void
   )

   {
	int         s;
   surface_t   *surf;
	int         mesh[ TIKI_MAX_TRIANGLES ][ 3 ];

	// go through each surface and find best strip/fans possible
   surf = model.surfaces;
	for ( s = 0; s < model.numsurfaces; s++, surf++ )
	   {
      if ( surf->numtris )
         {
         memcpy( mesh, surf->tris, sizeof( mesh[ 0 ] ) * surf->numtris );
         qprintf( "%s(%d):\n", surf->name, surf->id );
		   OrderMesh( mesh, surf->tris, surf->numtris );
         }
	   }
   }

void SkelModel::CalculateBounds
   (
   void
   )

   {
	int	      i;
   int         j;
   int         k;
   int         l;
   int         index;
   vec3_t      baseVerts[ TIKI_MAX_VERTS ];
	vec3_t      tmpVec;
   loadframe_t *frame;
	float       maxRadius;
   float       radius;
   surface_t   *surf;

   frame = model.anim;
   for( i = 0; i < model.numframes; i++, frame++ )
      {
      CalcFrame( i, baseVerts );
      ClearBounds( frame->bounds[ 0 ], frame->bounds[ 1 ] );

      surf = model.surfaces;
		for( j = 0; j < model.numsurfaces; j++, surf++ )
		   {
         if ( str::icmpn( surf->name, "tag_", 4 ) && originname.icmp( surf->name ) )
   			{
            for( l = 0; l < surf->numtris; l++ )
               {
               for( k = 0; k < 3; k++ )
                  {
                  index = surf->verts[ surf->tris[ l ][ k ] ].index;
                  AddPointToBounds( baseVerts[ index ], frame->bounds[ 0 ], frame->bounds[ 1 ] );
                  }
               }
            }
         }

		//
		// compute localOrigin and radius
		//
		maxRadius = 0;
		for( j = 0; j < 8; j++ )
		   {
			tmpVec[ 0 ] = frame->bounds[ ( j & 1 ) != 0 ][ 0 ];
			tmpVec[ 1 ] = frame->bounds[ ( j & 2 ) != 0 ][ 1 ];
			tmpVec[ 2 ] = frame->bounds[ ( j & 4 ) != 0 ][ 2 ];

         radius = VectorLength( tmpVec );
			if ( radius > maxRadius )
            {
				maxRadius = radius;
            }
		   }

		frame->radius = maxRadius;
      }
   }

void SkelModel::ComputeTagFromTri
   (
   loadbone_t *bone,
   const float pTri[ 3 ][ 3 ]
   )

   {
	float	   len[ 3 ];
	vec3_t	axis[ 3 ];
   vec3_t   sides[ 3 ];
	int		longestSide;
   int      shortestSide;
   int      hypotSide;
	int		origin;
	int		j;
	float	   d;

   longestSide    = 0;
   shortestSide   = 0;
   hypotSide      = 0;
   origin         = 0;

	memset( axis, 0, sizeof( axis ) );
	memset( sides, 0, sizeof( sides ) );

	// compute sides
	for( j = 0; j < 3; j++ )
   	{
		sides[ j ][ 0 ] = pTri[ ( j + 1 ) % 3 ][ 0 ] - pTri[ j ][ 0 ];
		sides[ j ][ 1 ] = pTri[ ( j + 1 ) % 3 ][ 1 ] - pTri[ j ][ 1 ];
		sides[ j ][ 2 ] = pTri[ ( j + 1 ) % 3 ][ 2 ] - pTri[ j ][ 2 ];

		len[ j ] = VectorLength( sides[ j ] );
	   }

   if ( len[ 0 ] > len[ 1 ] && len[ 0 ] > len[ 2 ] ) 
      {
		hypotSide = 0;
		origin    = 2;
	   }
   else if ( len[ 1 ] > len[ 0 ] && len[ 1 ] > len[ 2 ] )
      {
		hypotSide = 1;
		origin    = 0;
	   }
   else if ( len[ 2 ] > len[ 0 ] && len[ 2 ] > len[ 1 ] )
      {
		hypotSide = 2;
		origin    = 1;
	   }

	len[ hypotSide ] = -1;

	if ( len[ 0 ] > len[ 1 ] && len[ 0 ] > len[ 2 ] )
      {
		longestSide = 0;
	   }
   else if ( len[ 1 ] > len[ 0 ] && len[ 1 ] > len[ 2 ] )
      {
		longestSide = 1;
	   }
   else if ( len[ 2 ] > len[ 0 ] && len[ 2 ] > len[ 1 ] )
      {
		longestSide = 2;
	   }

	len[ longestSide ] = -1;

	if ( len[ 0 ] > len[ 1 ] && len[ 0 ] > len[ 2 ] )
      {
		shortestSide = 0;
	   }
   else if ( len[ 1 ] > len[ 0 ] && len[ 1 ] > len[ 2 ] )
      {
		shortestSide = 1;
	   }
   else if ( len[ 2 ] > len[ 0 ] && len[ 2 ] > len[ 1 ] )
      {
		shortestSide = 2;
	   }

	len[ shortestSide ] = -1;

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

	VectorNormalize( sides[ longestSide ], axis[ 0 ] );
	VectorNormalize( sides[ shortestSide ], axis[ 1 ] );

	// project shortest side so that it is exactly 90 degrees to the longer side
	d = DotProduct( axis[ 1 ], axis[ 0 ] );
	VectorMA( axis[ 1 ], -d, axis[ 0 ], axis[ 1 ] );

	VectorNormalize( axis[ 1 ], axis[ 1 ] );

	CrossProduct( sides[ longestSide ], sides[ shortestSide ], axis[ 2 ] );
	VectorNormalize( axis[ 2 ], axis[ 2 ] );

   VectorCopy( pTri[ origin ], bone->offset );
   VectorCopy( axis[ 0 ], bone->matrix[ 0 ] );
   VectorCopy( axis[ 1 ], bone->matrix[ 1 ] );
   VectorCopy( axis[ 2 ], bone->matrix[ 2 ] );
   }

void SkelModel::CalculateTags
   (
   void
   )

   {
   loadframe_t *frame;
   surface_t   *surf;
	float       tri[ 3 ][ 3 ];
   int         i;
   int         j;
   int         k;
   int         l;
   vec3_t      baseVerts[ TIKI_MAX_VERTS ];
	int         index;
   int         bestbone;
   float       bestboneweight;
   loadbone_t  parentBone[ TIKI_MAX_FRAMES ];
   UMat3       mat;
   UVector3    off;
   UVector3    t;

	// build animation frames
   frame = model.anim;
	for( i = 0; i < model.numframes; i++, frame++ )
	   {
      CalcFrame( i, baseVerts );

      surf = model.surfaces;
		for( j = 0; j < model.numsurfaces; j++, surf++ )
		   {
         if ( !str::icmpn( surf->name, "tag_", 4 ) )
   			{
            for( k = 0; k < 3; k++ )
               {
               index = surf->verts[ surf->tris[ 0 ][ k ] ].index;
               VectorCopy( baseVerts[ index ], tri[ k ] );
               }

            for( k = 0; k < model.numbones; k++ )
               {
               if ( !str::icmp( model.bones[ k ].name, surf->name ) )
                  {
                  break;
                  }
               }

            if ( k >= model.numbones )
               {
               // no bone with same name found, so create a new one
               // first, find the bone that has the greatest influence over
               // the triangle.  We'll make that one our parent.
               bestbone = -1;  // Default to a root node
               bestboneweight = -1;
               for( k = 0; k < 3; k++ )
                  {
                  index = surf->tris[ 0 ][ k ];
                  for( l = 0; l < surf->verts[ index ].numbones; l++ )
                     {
                     if ( surf->verts[ index ].blend[ l ].weight > bestboneweight )
                        {
                        bestboneweight = surf->verts[ index ].blend[ l ].weight;
                        bestbone = surf->verts[ index ].blend[ l ].bone;
                        }
                     }
                  }

               // create the bone
               k = AddBone( bestbone, surf->name );
               }

				ComputeTagFromTri( &frame->bones[ k ], tri );

            if ( i == ( model.numframes - 1 ) )
               {
               for( l = 0; l < 3; l++ )
                  {
                  mat = *( UMat3 * )frame->bones[ k ].matrix;
                  off = *( UVector3 * )frame->bones[ k ].offset;

                  index = surf->verts[ surf->tris[ 0 ][ l ] ].index;
                  t  = baseVerts[ index ] - off;

                  mat.ProjectVector( t, off );
                  *( UVector3 * )surf->verts[ surf->tris[ 0 ][ l ] ].blend[ 0 ].offset = off;
                  }
               }
            }

         if ( !originname.icmp( surf->name ) )
			   {
            for( k = 0; k < 3; k++ )
               {
               index = surf->verts[ surf->tris[ 0 ][ k ] ].index;
               VectorCopy( baseVerts[ index ], tri[ k ] );
               }

				ComputeTagFromTri( &parentBone[ i ], tri );

            // store off origin info
            if ( noorigin )
               {
               VectorClear( parentBone[ i ].offset );
               }

            if ( !noclampz && parentBone[ i ].offset[ 2 ] < 0 )
               {
               parentBone[ i ].offset[ 2 ] = 0;
               }

            if ( zerox )
               {
               parentBone[ i ].offset[ 0 ] = 0;
               }

            if ( zeroy )
               {
               parentBone[ i ].offset[ 1 ] = 0;
               }

            if ( zeroz )
               {
               parentBone[ i ].offset[ 2 ] = 0;
               }

            VectorCopy( parentBone[ i ].offset, frame->origin );

            if ( clearxy )
               {
               // subtract forward and side movement from deltas 
               frame->origin[ 0 ] = 0;
               frame->origin[ 1 ] = 0;
               }

            if ( clearx )
               {
               frame->origin[ 0 ] = 0;
               }

            if ( cleary )
               {
               frame->origin[ 1 ] = 0;
               }

            if ( clearz )
               {
               frame->origin[ 2 ] = 0;
               }
            }
			}
	   }

   VectorClear( model.totaldelta );

   frame = model.anim;
	for( i = 0; i < model.numframes - 1; i++, frame++ )
	   {
      for( k = 0; k < model.numbones; k++ )
         {
         VectorSubtract( frame->bones[ k ].offset, parentBone[ i ].offset, frame->bones[ k ].offset );
         VectorSubtract( frame->bones[ k ].offset, modeloffset, frame->bones[ k ].offset );
         }

      // calculate deltas
   	for( j = 0; j < 3; j++ )
      	{
			model.anim[ i ].delta[ j ] = model.anim[ i + 1 ].origin[ j ] - model.anim[ i ].origin[ j ];
         }

      VectorAdd( model.totaldelta, model.anim[ i ].delta, model.totaldelta );
      }

   // handle last frame
   for( k = 0; k < model.numbones; k++ )
      {
      VectorSubtract( frame->bones[ k ].offset, parentBone[ i ].offset, frame->bones[ k ].offset );
      VectorSubtract( frame->bones[ k ].offset, modeloffset, frame->bones[ k ].offset );
      }

   // fudge the last frame
   VectorClear( model.anim[ model.numframes - 1 ].delta );
   if ( model.numframes > 1 )
      {
      VectorScale( model.totaldelta, 1.0f / ( model.numframes - 1 ), model.anim[ model.numframes - 1 ].delta );
      }
   else
      {
      VectorClear( model.totaldelta );
      }
   }

void SkelModel::ScaleModel
   (
   float scale
   )

   {
   loadframe_t *frame;
   loadvertx_t *vert;
   loadbone_t  *bone;
   int         i;
   int         j;

   if ( scale == 1.0f )
      {
      return;
      }

   // scale the verts
   vert = model.verts;
   for( i = 0; i < model.numverts; i++, vert++ )
      {
      for( j = 0; j < vert->numbones; j++ )
         {
         VectorScale( vert->blend[ j ].offset, scale, vert->blend[ j ].offset );
         }
      }

   // scale the bone frames
   frame = model.anim;
   for( i = 0; i < model.numframes; i++, frame++ )
      {
      bone = frame->bones;
      for( j = 0; j < model.numbones; j++, bone++ )
         {
         VectorScale( bone->offset, scale, bone->offset );
         }
      }
   }

void SkelModel::ReverseAnimation
   (
   void
   )

   {
   loadframe_t *framelo;
   loadframe_t *framehi;
   loadbone_t  *bone;
   int         num;
   int         i;

   // scale the bone frames
   framelo = model.anim;
   framehi = &model.anim[ model.numframes - 1 ];
   num = model.numframes / 2;
   for( i = 0; i < num; i++, framelo++, framehi-- )
      {
      bone = framelo->bones;
      framelo->bones = framehi->bones;
      framehi->bones = bone;
      }
   }

void SkelModel::ReduceBonesPerVertex
   (
   int maxbones,
   float minweight
   )

   {
   loadvertx_t *vert;
   loadvertx_t v;
   int         i;
   int         j;
   int         k;
   float       totalweight;
   float       singleweight;
   UVector3    singleoffset;
   int         numbones;
   int         numleft;
   int         merge;
   int         numzero;

   numleft = 0;
   numbones = 0;
   merge = 0;

   vert = model.verts;
   for( i = 0; i < model.numverts; i++, vert++ )
      {
      numzero = 0;
      for( j = 0; j < vert->numbones; j++ )
         {
         if ( vert->blend[ j ].weight <= 0 )
            {
            numzero++;
            }
         }

      if ( numzero == vert->numbones )
         {
         printf( "** No valid weights on vertex %d.  Setting to average weight.\n", i );
         for( j = 0; j < vert->numbones; j++ )
            {
            vert->blend[ j ].weight = 1.0f / ( float )vert->numbones;
            }
         }

      numbones += vert->numbones;
      v = *vert;
      vert->numbones = 0;
      totalweight = 0;
      for( j = 0; j < v.numbones; j++ )
         {
         if ( v.blend[ j ].bone == UNUSED_BONE )
            {
            // skip blends with unused bones since we zeroed it out ourselves
            continue;
            }

         // For some reason, Max may report the same bone more than once, so we
         // add up all the blends that have the same bone and combine them into
         // one offset and weight.
         singleweight = v.blend[ j ].weight;
         singleoffset = UVector3( v.blend[ j ].offset ) * v.blend[ j ].weight;
         for( k = j + 1; k < v.numbones; k++ )
            {
            if ( v.blend[ j ].bone == v.blend[ k ].bone )
               {
               singleweight += v.blend[ k ].weight;
               singleoffset += UVector3( v.blend[ k ].offset ) * v.blend[ k ].weight;

               // zero it out so we never use it again
               v.blend[ k ].weight = 0;
               v.blend[ k ].bone   = UNUSED_BONE;
               VectorClear( v.blend[ k ].offset );

               merge++;
               }
            }

         // don't allow zero weight bones, even if the user allows it.
         if ( ( singleweight != 0 ) && ( singleweight > minweight ) )
            {
            singleoffset *= 1 / singleweight;
            
            vert->blend[ vert->numbones ].bone = v.blend[ j ].bone;
            vert->blend[ vert->numbones ].weight = singleweight;
            VectorCopy( singleoffset, vert->blend[ vert->numbones ].offset );

            totalweight += singleweight;
            numleft++;

            vert->numbones++;
            if ( vert->numbones >= maxbones )
               {
               break;
               }
            }
         else
            {
            //printf( "degenerate weight %.2f for bone %s on vertex %d\n", singleweight, model.bones[ v.blend[ j ].bone ].name, i );
            }
         }

      if ( totalweight <= 0 )
         {
         Error( "Invalid totalweight %.2f on vertex %d when reducing number of blended bones, on model %s\n", totalweight, i, model.name );
         }

      if ( vert->numbones < 1 )
         {
         Error( "No bones on vertex %d when reducing number of blended bones, on model %s.\n", i, model.name );
         }

      for( j = 0; j < vert->numbones; j++ )
         {
         vert->blend[ j ].weight /= totalweight;
         }
      }

   if ( verbose )
      {
	   printf( "removed %d weights, %d remain.  merged %d weights.\n", numbones - numleft, numbones, merge );
      }
   }

int SkelModel::AddBone
   (
   int parent,
   const char *name
   )

   {
   skelBoneName_t *oldbonenames;
   skelBoneName_t *bonename;
   loadbone_t     *oldbones;
   loadframe_t    *frame;
   loadbone_t     *bone;
   int            oldbonenum;
   int            i;
   int            j;

   // reallocate the bones
   oldbonenum = model.numbones;
   oldbonenames = model.bones;

   model.numbones++;
   model.bones = new skelBoneName_t[ model.numbones ];

   bonename = model.bones;
   for( i = 0; i < oldbonenum; i++, bonename++ )
      {
      bonename->parent = oldbonenames[ i ].parent;
      bonename->flags = oldbonenames[ i ].flags;
      strcpy( bonename->name, oldbonenames[ i ].name );
      }

   model.bones[ oldbonenum ].parent = parent;
   model.bones[ oldbonenum ].flags = 0;
   strcpy( model.bones[ oldbonenum ].name, name );

   delete[] oldbonenames;

   // reallocate the bone frames
   frame = model.anim;
   for( i = 0; i < model.numframes; i++, frame++ )
      {
      oldbones = frame->bones;
      frame->bones = new loadbone_t[ model.numbones ];
      bone = frame->bones;
      for( j = 0; j < oldbonenum; j++, bone++ )
         {
         VectorCopy( oldbones[ j ].matrix[ 0 ], bone->matrix[ 0 ] );
         VectorCopy( oldbones[ j ].matrix[ 1 ], bone->matrix[ 1 ] );
         VectorCopy( oldbones[ j ].matrix[ 2 ], bone->matrix[ 2 ] );
         VectorCopy( oldbones[ j ].offset,      bone->offset );
         }

      VectorSet( frame->bones[ oldbonenum ].matrix[ 0 ], 1, 0, 0 );
      VectorSet( frame->bones[ oldbonenum ].matrix[ 1 ], 0, 1, 0 );
      VectorSet( frame->bones[ oldbonenum ].matrix[ 2 ], 0, 0, 1 );
      VectorSet( frame->bones[ oldbonenum ].offset,      0, 0, 0 );
   
      delete[] oldbones;
      }

   if ( verbose )
      {
	   printf( "Created new bone %s.  Total bones %d.\n", name, model.numbones );
      }

   return oldbonenum;
   }

void SkelModel::RemoveUnusedBones
   (
   void
   )

   {
   surface_t      *surf;
   loadvertx_t    *vert;
   int            i;
   int            j;
   int            k;
   int            parent;
   int            parent2;
   bool           used[ MAX_BONES ];
   int            newboneindex[ MAX_BONES ];
   int            oldboneindex[ MAX_BONES ];
   int            newparent[ MAX_BONES ];
   int            numused;
   skelBoneName_t *oldbonenames;
   skelBoneName_t *bonename;
   loadbone_t     *oldbones;
   loadbone_t     *bone;
   loadframe_t    *frame;

   memset( used, 0, sizeof( used ) );
   memset( oldboneindex, 0, sizeof( oldboneindex ) );
   memset( newboneindex, 0, sizeof( newboneindex ) );
   memset( newparent, 0, sizeof( newparent ) );
   
   // find all the bones that are used
   surf = model.surfaces;
   for( i = 0; i < model.numsurfaces; i++, surf++ )
      {
//      if ( !originname.icmp( surf->name ) )
//         {
//         // we don't care about the origin once we have grabbed it
//         continue;
//         }
      vert = surf->verts;
      for( j = 0; j < surf->numverts; j++, vert++ )
         {
         for( k = 0; k < vert->numbones; k++ )
            {
            used[ vert->blend[ k ].bone ] = true;
            }
         }
      }

   if ( !ignoreflags )
      {
      // go through the bones and mark any bones that have to be kept
      // so that we don't mistakenly remap any children.  Normally this
      // wouldn't be an issue since we go through the bones parent first,
      // but since we have to keep the parent's flags the same, we have
      // to scan back up the hierarchy, which means we could be remapping
      // a bone index that we shouldn't by mistake.
      for( i = 0; i < model.numbones; i++ )
         {
         if ( !originname.icmp( model.bones[ i ].name ) || !str::icmpn( model.bones[ i ].name, "tag_", 4 ) )
//         if ( !str::icmpn( model.bones[ i ].name, "tag_", 4 ) )
            {
            used[ i ] = true;
            }

         if ( used[ i ] )
            {
            parent = model.bones[ i ].parent;
            while( ( parent != -1 ) && !used[ parent ] )
               {
               parent2 = model.bones[ parent ].parent;

               // when we're collapsing bones, if we remove a parent bone, we can
               // only connect the child to a bone with the same flags as the parent,
               // so if there isn't one available, mark the parent as used.
               if ( ( parent2 == -1 ) || ( model.bones[ parent2 ].flags != model.bones[ parent ].flags ) )
                  {
                  used[ parent ] = true;
                  break;
                  }

               parent = parent2;
               }
            }
         }
      }

   // create the indices to be remapped
   numused = 0;
   for( i = 0; i < model.numbones; i++ )
      {
      if ( used[ i ] )
         {
         parent = model.bones[ i ].parent;
         while( ( parent != -1 ) && !used[ parent ] )
            {
            parent = model.bones[ parent ].parent;
            }

         if ( parent != -1 )
            {
            newparent[ numused ] = newboneindex[ parent ];
            }
         else
            {
            newparent[ numused ] = -1;
            }

         oldboneindex[ numused ] = i;
         newboneindex[ i ] = numused++;
         }
		else
			{
         // if verbose, show which bones are being removed.
			if ( verbose )
				{
				printf( "Bone #%d (%s) unused.\n", i, model.bones[i].name );
				}
			}
      }

   // remap all the bone numbers
   vert = model.verts;
   for( j = 0; j < model.numverts; j++, vert++ )
      {
      for( k = 0; k < vert->numbones; k++ )
         {
         vert->blend[ k ].bone = newboneindex[ vert->blend[ k ].bone ];
         }
      }

   // remap all the bone numbers in the surfaces
   surf = model.surfaces;
   for( i = 0; i < model.numsurfaces; i++, surf++ )
      {
      vert = surf->verts;
      for( j = 0; j < surf->numverts; j++, vert++ )
         {
         for( k = 0; k < vert->numbones; k++ )
            {
            vert->blend[ k ].bone = newboneindex[ vert->blend[ k ].bone ];
            }
         }
      }

   // reallocate the bones
   oldbonenames = model.bones;
   model.bones = new skelBoneName_t[ numused ];
   bonename = model.bones;
   for( i = 0; i < numused; i++, bonename++ )
      {
      bonename->parent = newparent[ i ];
      bonename->flags = oldbonenames[ oldboneindex[ i ] ].flags;
      strcpy( bonename->name, oldbonenames[ oldboneindex[ i ] ].name );
      }
   
   delete[] oldbonenames;

   // reallocate the bone frames
   frame = model.anim;
   for( i = 0; i < model.numframes; i++, frame++ )
      {
      oldbones = frame->bones;
      frame->bones = new loadbone_t[ numused ];
      bone = frame->bones;
      for( j = 0; j < numused; j++, bone++ )
         {
         VectorCopy( oldbones[ oldboneindex[ j ] ].matrix[ 0 ], bone->matrix[ 0 ] );
         VectorCopy( oldbones[ oldboneindex[ j ] ].matrix[ 1 ], bone->matrix[ 1 ] );
         VectorCopy( oldbones[ oldboneindex[ j ] ].matrix[ 2 ], bone->matrix[ 2 ] );
         VectorCopy( oldbones[ oldboneindex[ j ] ].offset,      bone->offset );
         }
   
      delete[] oldbones;
      }

   if ( verbose )
      {
	   printf( "removed %d bones, %d remain\n", model.numbones - numused, numused );
      }

   model.numbones = numused;
#if 0
   for( i = 0; i < model.numbones; i++ )
      {
      char temp[ 1024 ];
      sprintf( temp, "%i %s\n", i, model.bones[ i ].name );
      OutputDebugString( temp );
      }
#endif
   }

void SkelModel::ConvertToQuake3Worldspace
   (
   void
   )

   {
	int			i;
   int         j;
   loadframe_t *frame;
   loadbone_t  *bone;
   UMat3       mat;
   UVector3    offset;

   frame = model.anim;
	for( i = 0; i < model.numframes; i++, frame++ )
	   {
      bone = frame->bones;
      for( j = 0; j < model.numbones; j++, bone++ )
         {
         mat = *( UMat3 * )bone->matrix;

         // convert the orientation to Quake 3 worldspace
         ( *( UMat3 * )bone->matrix ).vecs[ 0 ].x = -mat.vecs[ 0 ][ 1 ];
         ( *( UMat3 * )bone->matrix ).vecs[ 0 ].y = mat.vecs[ 0 ][ 0 ];
         ( *( UMat3 * )bone->matrix ).vecs[ 0 ].z = mat.vecs[ 0 ][ 2 ];

         ( *( UMat3 * )bone->matrix ).vecs[ 1 ].x = -mat.vecs[ 1 ][ 1 ];
         ( *( UMat3 * )bone->matrix ).vecs[ 1 ].y = mat.vecs[ 1 ][ 0 ];
         ( *( UMat3 * )bone->matrix ).vecs[ 1 ].z = mat.vecs[ 1 ][ 2 ];

         ( *( UMat3 * )bone->matrix ).vecs[ 2 ].x = -mat.vecs[ 2 ][ 1 ];
         ( *( UMat3 * )bone->matrix ).vecs[ 2 ].y = mat.vecs[ 2 ][ 0 ];
         ( *( UMat3 * )bone->matrix ).vecs[ 2 ].z = mat.vecs[ 2 ][ 2 ];

         // convert the offset to Quake 3 worldspace
         offset = bone->offset;
         ( *( UVector3 * )bone->offset ).x = -offset.y;
         ( *( UVector3 * )bone->offset ).y = offset.x;
         ( *( UVector3 * )bone->offset ).z = offset.z;
         }
      }
   }

void SkelModel::SaveBaseFrame
   (
   const char *name
   )

   {
	int				i;
   int            j;
   int            k;
	skelHeader_t   modeltemp;
   skelSurface_t  surftemp[ TIKI_MAX_SURFACES * 2 ];
   skelTriangle_t tritemp[ TIKI_MAX_TRIANGLES ];
   int            collapseMap[ TIKI_MAX_VERTS ];
   skelVertex_t   tempvert;
   skelWeight_t   tempweight;
	long			   surfaceSum;
   long           vertSum;
   int            numsurfs;
	FILE		      *modelouthandle;
   surface_t      *insurf;
   skelSurface_t  *outsurf;
   loadvertx_t    *vert;
   skelBoneName_t bonename;

	if ( !model.numframes )
      {
		return;
      }

   if ( model.numsurfaces > TIKI_MAX_SURFACES * 2 )
		{
		Error( "too many surfaces\n" );
		}

	//
	// write the model output file
	//
   printf( "Saving baseframe to %s\n", name );

   strncpy( model.name, name, sizeof( model.name ) - 1 );

   surfaceSum = 0;
   numsurfs = 0;

   memset( surftemp, 0, sizeof( surftemp ) );

	// compute offsets for all surfaces, sum their total size
   insurf = model.surfaces;
   outsurf = surftemp;
   for( i = 0; i < model.numsurfaces; i++, insurf++, outsurf++ )
	   {
		if ( ( insurf->numtris == 0 ) || !str::icmpn( insurf->name , "tag_", 4 ) || !originname.icmp( insurf->name ) )
         {
			continue;
         }

      if ( numsurfs >= TIKI_MAX_SURFACES ) 
		   {
		   Error( "too many surfaces\n" );
		   }

		if ( insurf->numtris > MAX_SURFACE_TRIS ) 
			{
			Error( "too many faces\n" );
			}

      if ( insurf->numverts > TIKI_MAX_VERTS )
         {
         Error( "Too many vertices %d out of %d on surface %s in model %s\n", insurf->numverts, TIKI_MAX_VERTS, insurf->name, model.name );
         }

      // sum the total size of the vertices
      vertSum = 0;
	   for( j = 0; j < insurf->numverts; j++ )
         {
         vertSum += sizeof( skelVertex_t ) + sizeof( skelWeight_t ) * ( insurf->verts[ j ].numbones - 1 );
         }

      strcpy( outsurf->name, insurf->name );

      outsurf->ident          = LittleLong( TIKI_SKEL_IDENT );
      outsurf->numTriangles   = LittleLong( insurf->numtris );
      outsurf->numVerts       = LittleLong( insurf->numverts );
      outsurf->minLod         = LittleLong( insurf->minLod );
		outsurf->ofsTriangles   = sizeof( skelSurface_t );
      outsurf->ofsVerts       = outsurf->ofsTriangles + insurf->numtris * sizeof( skelTriangle_t );
      outsurf->ofsCollapse    = outsurf->ofsVerts + vertSum;
		outsurf->ofsEnd         = outsurf->ofsCollapse + insurf->numverts * sizeof( insurf->collapseMap[ 0 ] );

      surfaceSum += outsurf->ofsEnd;
      outsurf->ofsVerts       = LittleLong( outsurf->ofsVerts );
		outsurf->ofsTriangles   = LittleLong( outsurf->ofsTriangles );
      outsurf->ofsCollapse    = LittleLong( outsurf->ofsCollapse );
      outsurf->ofsEnd         = LittleLong( outsurf->ofsEnd );

      numsurfs++;
	   }

   CreatePath( name );
	modelouthandle = SafeOpenWrite( name );

   // create the header
   strcpy( modeltemp.name, model.name );

   modeltemp.ident         = LittleLong( TIKI_SKEL_IDENT );
	modeltemp.version       = LittleLong( TIKI_SKEL_VERSION );
   modeltemp.numsurfaces   = LittleLong( numsurfs );
   modeltemp.numbones      = LittleLong( model.numbones );

   modeltemp.ofsBones      = sizeof( skelHeader_t );
   modeltemp.ofsSurfaces   = modeltemp.ofsBones + model.numbones * sizeof( skelBoneName_t );
   modeltemp.ofsEnd        = modeltemp.ofsSurfaces + surfaceSum;

   modeltemp.ofsBones      = LittleLong( modeltemp.ofsBones );
   modeltemp.ofsSurfaces   = LittleLong( modeltemp.ofsSurfaces );
   modeltemp.ofsEnd        = LittleLong( modeltemp.ofsEnd );

	//
	// write out the model header
	//
	SafeWrite( modelouthandle, &modeltemp, sizeof( modeltemp ) );

   //
   // write out the bone names
   //
   for( i = 0; i < model.numbones; i++ )
      {
      memset( &bonename, 0, sizeof( bonename ) );

      bonename.flags    = LittleLong( model.bones[ i ].flags );
      bonename.parent   = LittleLong( model.bones[ i ].parent );

      strcpy( bonename.name, model.bones[ i ].name );

      SafeWrite( modelouthandle, &bonename, sizeof( bonename ) );
      }

   //
   // write out the surfaces
   //
   insurf = model.surfaces;
   outsurf = surftemp;
   for( i = 0; i < model.numsurfaces; i++, insurf++, outsurf++ )
      {
		if ( ( insurf->numtris == 0 ) || !str::icmpn( insurf->name , "tag_", 4 ) || !originname.icmp( insurf->name ) )
         {
			continue;
         }

      SafeWrite( modelouthandle, outsurf, sizeof( skelSurface_t ) );

      for( j = 0; j < insurf->numtris; j++ )
         {
         tritemp[ j ].indexes[ 0 ] = LittleLong( insurf->tris[ j ][ 0 ] );
         tritemp[ j ].indexes[ 1 ] = LittleLong( insurf->tris[ j ][ 1 ] );
         tritemp[ j ].indexes[ 2 ] = LittleLong( insurf->tris[ j ][ 2 ] );
         }

      SafeWrite( modelouthandle, tritemp, insurf->numtris * sizeof( skelTriangle_t ) );

      //
      // write out the vertices
      //
      vert = insurf->verts;
	   for( j = 0; j < insurf->numverts; j++, vert++ )
         {
         tempvert.normal[ 0 ] = LittleFloat( vert->normal[ 0 ] );
         tempvert.normal[ 1 ] = LittleFloat( vert->normal[ 1 ] );
         tempvert.normal[ 2 ] = LittleFloat( vert->normal[ 2 ] );

         tempvert.texCoords[ 0 ] = LittleFloat( vert->texCoords[ 0 ] );
         tempvert.texCoords[ 1 ] = LittleFloat( vert->texCoords[ 1 ] );

         tempvert.numWeights = LittleLong( vert->numbones );

         SafeWrite( modelouthandle, &tempvert, sizeof( tempvert ) - sizeof( tempvert.weights ) );

         if ( !vert->numbones )
            {
            Error( "Vertex with no bones found in surface '%s'(%d).\n", insurf->name, insurf->id );
            }

         for( k = 0; k < vert->numbones; k++ )
            {
            tempweight.boneIndex = LittleLong( vert->blend[ k ].bone );
            tempweight.boneWeight = LittleFloat( vert->blend[ k ].weight );
            tempweight.offset[ 0 ] = LittleFloat( vert->blend[ k ].offset[ 0 ] );
            tempweight.offset[ 1 ] = LittleFloat( vert->blend[ k ].offset[ 1 ] );
            tempweight.offset[ 2 ] = LittleFloat( vert->blend[ k ].offset[ 2 ] );

            SafeWrite( modelouthandle, &tempweight, sizeof( tempweight ) );
            }
         }

      //
      // write out the collapse map
      //
      for( j = 0; j < insurf->numverts; j++ )
         {
         collapseMap[ j ] = LittleLong( insurf->collapseMap[ j ] );
         }

      SafeWrite( modelouthandle, collapseMap, insurf->numverts * sizeof( collapseMap[ 0 ] ) );
      }

   if ( verbose )
      {
	   printf( "%4d surfaces\n", model.numsurfaces );
	   printf( "%4d bones\n", model.numbones );
	   printf( "%4d verts\n", model.numverts );
	   printf( "file size: %d\n", ( int )ftell( modelouthandle ) );
	   printf( "---------------------\n" );
      }

	fclose( modelouthandle );
   }

void SkelModel::SaveAnimation
   (
   const char *name
   )

   {
	int				   i, j, k;
	FILE		         *modelouthandle;
   loadframe_t       *frame;
   loadframe_t       outframe;
   loadbone_t        *bone;
   skelBone_t        outbone;
   skelAnimHeader_t  animheader;
   UMat3             mat;
   UMat3             pmat;
   UMat3             outm;
   UVector3          offset;
   UVector3          poffset;
   UVector3          outv;
   int               numframes;

	if ( !model.numframes )
      {
		return;
      }

   numframes = model.numframes;
   if ( loop && ( numframes > 1 ) )
      {
      numframes--;
      }

	//
	// write the model output file
	//
   printf( "Saving animation to %s\n", name );

   strncpy( model.name, name, sizeof( model.name ) - 1 );

	animheader.ident   = TIKI_SKEL_ANIM_IDENT;
	animheader.version = TIKI_SKEL_VERSION;

   memset( animheader.name, 0, sizeof( animheader.name ) );
   strncpy( animheader.name, name, sizeof( animheader.name ) - 1 );

   // calculate total time
   animheader.totaltime = ( float )numframes / model.framerate;
   animheader.frametime = 1.0f / model.framerate;
   animheader.numFrames = numframes;
   animheader.numbones  = model.numbones;

// animheader.framesize = ( sizeof( model.anim[ 0 ] ) - sizeof( model.anim[ 0 ].bones ) + model.numbones * sizeof( loadbone_t ) );
   animheader.ofsFrames = sizeof( animheader );
//	animheader.ofsEnd    = animheader.ofsFrames + numframes * animheader.framesize;

   //
   // figure out if any of our bone offsets change during this animation
   //

	CreatePath( name );
	modelouthandle = SafeOpenWrite( name );

	//
	// write out the model header
	//
	animheader.ident         = LittleLong( animheader.ident );
	animheader.version       = LittleLong( animheader.version );
	animheader.numFrames     = LittleLong( animheader.numFrames );
	animheader.numbones      = LittleLong( model.numbones );
   animheader.totaltime     = LittleFloat( animheader.totaltime );
   animheader.frametime     = LittleFloat( animheader.frametime );
//	animheader.framesize     = LittleLong( animheader.framesize );
	animheader.ofsFrames     = LittleLong( animheader.ofsFrames );
//	animheader.ofsEnd        = LittleLong( animheader.ofsEnd );

   // copy the totaldelta
   animheader.totaldelta[ 0 ] = LittleFloat( model.totaldelta[ 0 ] );
   animheader.totaldelta[ 1 ] = LittleFloat( model.totaldelta[ 1 ] );
   animheader.totaldelta[ 2 ] = LittleFloat( model.totaldelta[ 2 ] );

	SafeWrite( modelouthandle, &animheader, sizeof( animheader ) );

	//
	// write out the frames
	//
   frame = model.anim;
	for( i = 0; i < numframes; i++, frame++ )
	   {
		// swap
		for( j = 0; j < 2; j++ )
         {
         outframe.bounds[ j ][ 0 ] = LittleFloat( frame->bounds[ j ][ 0 ] );
         outframe.bounds[ j ][ 1 ] = LittleFloat( frame->bounds[ j ][ 1 ] );
         outframe.bounds[ j ][ 2 ] = LittleFloat( frame->bounds[ j ][ 2 ] );
         }
      
      outframe.radius = LittleFloat( frame->radius );

      outframe.delta[ 0 ] = LittleFloat( frame->delta[ 0 ] );
      outframe.delta[ 1 ] = LittleFloat( frame->delta[ 1 ] );
      outframe.delta[ 2 ] = LittleFloat( frame->delta[ 2 ] );

      SafeWrite( modelouthandle, outframe.bounds, sizeof( outframe.bounds ) );
      SafeWrite( modelouthandle, &outframe.radius, sizeof( outframe.radius ) );
      SafeWrite( modelouthandle, outframe.delta, sizeof( outframe.delta ) );

      bone = frame->bones;
      for( j = 0; j < model.numbones; j++, bone++ )
         {
         UQuat outQuat;
         UVector3 outVect3;

         if ( model.bones[ j ].parent == -1 )
            {
            outm = *( UMat3 * )bone->matrix;
            outv = bone->offset;
            }
         else
            {
            mat = *( UMat3 * )bone->matrix;
            offset = bone->offset;

            pmat = *( UMat3 * )frame->bones[ model.bones[ j ].parent ].matrix;
            poffset = frame->bones[ model.bones[ j ].parent ].offset;

            offset -= poffset;
            pmat.ProjectVector( offset, outv );

            pmat.Transpose();
            outm = mat * pmat;
            }

         outQuat = outm;
         outVect3 = outv;

		   for( k = 0; k < 4; k++ )
            {
            short tempShort;

            assert( ( outQuat[ k ] <= 1.0f ) && ( outQuat[ k ] >= -1.0f ) );
            tempShort = outQuat[ k ] * TIKI_BONE_QUAT_MULTIPLIER;
            outbone.shortQuat[ k ] = LittleShort( tempShort );
            }

		   for( k = 0; k < 3; k++ )
            {
            short tempShort;

            if ( fabs( outVect3[ k ] ) > TIKI_BONE_OFFSET_MAX_SIGNED_VALUE )
               {
               Error( "Bone offset is too large for data format\n" );
               }
            tempShort = outVect3[ k ] * TIKI_BONE_OFFSET_MULTIPLIER;
            outbone.shortOffset[ k ] = LittleShort( tempShort );
            }

         SafeWrite( modelouthandle, &outbone, sizeof( outbone ) );
         }
      }

   if ( verbose )
      {
	   printf( "%4d frames\n", numframes );
	   printf( "%4d bones\n", model.numbones );
	   printf( "file size: %d\n", ( int )ftell( modelouthandle ) );
	   printf( "---------------------\n" );
      }

	fclose( modelouthandle );
   }

void SkelModel::SaveMD4
   (
   const char *name
   )

   {
	int				   i;
   int               j;
   int               k;
   int               l;
	md4Header_t       modeltemp;
   md4LOD_t          lodtemp;
   md4Surface_t      surftemp[ MD3_MAX_SURFACES ];
   md4Triangle_t     tritemp[ MD3_MAX_TRIANGLES ];
   md4Vertex_t       tempvert;
   md4Weight_t       tempweight;
   int               bonerefs[ MD3_MAX_SURFACES ][ MD4_MAX_BONES ];
   int               numbonerefs[ MD3_MAX_SURFACES ];
	long			      surfaceSum;
   long              vertSum;
   int               numsurfs;
	FILE		         *modelouthandle;
   surface_t         *insurf;
   md4Surface_t      *outsurf;
   loadvertx_t       *vert;
   loadframe_t       *frame;
   loadbone_t        *bone;
   md4Bone_t         outbone;
   md4Frame_t        outframe;
   int               numframes;

	if ( !model.numframes )
      {
		return;
      }

   numframes = model.numframes;
   if ( loop && ( numframes > 1 ) )
      {
      numframes--;
      }

   //
	// write the model output file
	//
   printf( "Saving MD4 to %s\n", name );

   strncpy( model.name, name, sizeof( model.name ) - 1 );

   surfaceSum = 0;
   numsurfs = 0;

   memset( surftemp, 0, sizeof( surftemp ) );

	// compute offsets for all surfaces, sum their total size
   insurf = model.surfaces;
   outsurf = surftemp;
   for( i = 0; i < model.numsurfaces; i++, insurf++, outsurf++ )
	   {
		if ( insurf->numtris == 0 )
         {
			continue;
         }

      if ( numsurfs >= MD3_MAX_SURFACES ) 
		   {
		   Error( "too many surfaces\n" );
		   }

		if ( insurf->numtris > MD3_MAX_TRIANGLES ) 
			{
			Error( "too many faces\n" );
			}

      numbonerefs[ i ] = 0;

      // sum the total size of the vertices
      vertSum = 0;
      vert = insurf->verts;
	   for( j = 0; j < insurf->numverts; j++, vert++ )
         {
         vertSum += sizeof( md4Vertex_t ) + sizeof( md4Weight_t ) * ( vert->numbones - 1 );

         for( k = 0; k < vert->numbones; k++ )
            {
            for( l = 0; l < numbonerefs[ i ]; l++ )
               {
               if ( bonerefs[ i ][ l ] == vert->blend[ k ].bone ) 
                  {
                  break;
                  }
               }

            if ( l == numbonerefs[ i ] )
               {
               bonerefs[ i ][ numbonerefs[ i ]++ ] = vert->blend[ k ].bone;
               }
            }
         }

      strcpy( outsurf->name, insurf->name );
      strcpy( outsurf->shader, "" );

      outsurf->ident             = LittleLong( MD4_IDENT );
      outsurf->shaderIndex       = 0;
      outsurf->ofsHeader         = -1;  // this is calculated from the file position when we save it out
                                 
      outsurf->numVerts          = LittleLong( insurf->numverts );
      outsurf->ofsVerts          = sizeof( md4Surface_t );
                                 
      outsurf->numTriangles      = LittleLong( insurf->numtris );
		outsurf->ofsTriangles      = outsurf->ofsVerts + vertSum;

   	outsurf->numBoneReferences = LittleLong( numbonerefs[ i ] );
	   outsurf->ofsBoneReferences = outsurf->ofsTriangles + insurf->numtris * sizeof( md4Triangle_t );

		outsurf->ofsEnd            = outsurf->ofsBoneReferences + numbonerefs[ i ] * sizeof( bonerefs[ i ][ 0 ] );

      surfaceSum += outsurf->ofsEnd;
      outsurf->ofsHeader         = LittleLong( outsurf->ofsHeader );
      outsurf->ofsVerts          = LittleLong( outsurf->ofsVerts );
		outsurf->ofsTriangles      = LittleLong( outsurf->ofsTriangles );
      outsurf->ofsBoneReferences = LittleLong( outsurf->ofsBoneReferences );
      outsurf->ofsEnd            = LittleLong( outsurf->ofsEnd );

      numsurfs++;
	   }

   CreatePath( name );
	modelouthandle = SafeOpenWrite( name );

   // create the header
   strcpy( modeltemp.name, model.name );

   modeltemp.ident         = LittleLong( MD4_IDENT );
	modeltemp.version       = LittleLong( MD4_VERSION );

   modeltemp.numFrames     = LittleLong( numframes );
   modeltemp.numBones      = LittleLong( model.numbones );
   modeltemp.numLODs       = LittleLong( 1 );               //FIXME -- add support for more than 1 lod

   modeltemp.ofsFrames     = sizeof( md4Header_t );
   modeltemp.ofsLODs       = modeltemp.ofsFrames + ( sizeof( md4Frame_t ) - sizeof( md4Bone_t ) + model.numbones * sizeof( md4Bone_t ) ) * numframes;
   modeltemp.ofsEnd        = modeltemp.ofsLODs + sizeof( md4LOD_t ) + surfaceSum; //FIXME -- add support for more than 1 lod

   modeltemp.ofsFrames     = LittleLong( modeltemp.ofsFrames );
   modeltemp.ofsLODs       = LittleLong( modeltemp.ofsLODs );
   modeltemp.ofsEnd        = LittleLong( modeltemp.ofsEnd );

	//
	// write out the model header
	//
	SafeWrite( modelouthandle, &modeltemp, sizeof( modeltemp ) );

   //
   // write out the frames
   //
   frame = model.anim;
	for( i = 0; i < numframes; i++, frame++ )
	   {
      strcpy( outframe.name, model.name );

		// swap
		for( j = 0; j < 2; j++ )
         {
         outframe.bounds[ j ][ 0 ] = LittleFloat( frame->bounds[ j ][ 0 ] );
         outframe.bounds[ j ][ 1 ] = LittleFloat( frame->bounds[ j ][ 1 ] );
         outframe.bounds[ j ][ 2 ] = LittleFloat( frame->bounds[ j ][ 2 ] );
         }

      outframe.localOrigin[ 0 ] = LittleFloat( ( frame->bounds[ 0 ][ 0 ] + frame->bounds[ 1 ][ 0 ] ) * 0.5 );
      outframe.localOrigin[ 1 ] = LittleFloat( ( frame->bounds[ 0 ][ 1 ] + frame->bounds[ 1 ][ 1 ] ) * 0.5 );
      outframe.localOrigin[ 2 ] = LittleFloat( ( frame->bounds[ 0 ][ 2 ] + frame->bounds[ 1 ][ 2 ] ) * 0.5 );

      outframe.radius = LittleFloat( frame->radius );

      SafeWrite( modelouthandle, &outframe, sizeof( outframe ) - sizeof( md4Bone_t ) );

      bone = frame->bones;
      for( j = 0; j < model.numbones; j++, bone++ )
         {
         outbone.matrix[ 0 ][ 0 ] = LittleFloat( bone->matrix[ 0 ][ 0 ] );
         outbone.matrix[ 1 ][ 0 ] = LittleFloat( bone->matrix[ 0 ][ 1 ] );
         outbone.matrix[ 2 ][ 0 ] = LittleFloat( bone->matrix[ 0 ][ 2 ] );

         outbone.matrix[ 0 ][ 1 ] = LittleFloat( bone->matrix[ 1 ][ 0 ] );
         outbone.matrix[ 1 ][ 1 ] = LittleFloat( bone->matrix[ 1 ][ 1 ] );
         outbone.matrix[ 2 ][ 1 ] = LittleFloat( bone->matrix[ 1 ][ 2 ] );

         outbone.matrix[ 0 ][ 2 ] = LittleFloat( bone->matrix[ 2 ][ 0 ] );
         outbone.matrix[ 1 ][ 2 ] = LittleFloat( bone->matrix[ 2 ][ 1 ] );
         outbone.matrix[ 2 ][ 2 ] = LittleFloat( bone->matrix[ 2 ][ 2 ] );

         outbone.matrix[ 0 ][ 3 ] = LittleFloat( bone->offset[ 0 ] );
         outbone.matrix[ 1 ][ 3 ] = LittleFloat( bone->offset[ 1 ] );
         outbone.matrix[ 2 ][ 3 ] = LittleFloat( bone->offset[ 2 ] );

         SafeWrite( modelouthandle, &outbone, sizeof( outbone ) );
         }
      }

   //
   // write out the LODs
   //
   for( l = 0; l < 1; l++ ) //FIXME -- add support for more than 1 lod
      {
      lodtemp.numSurfaces  = LittleLong( numsurfs );
      lodtemp.ofsSurfaces  = sizeof( lodtemp );
      lodtemp.ofsEnd       = lodtemp.ofsSurfaces + surfaceSum;

      lodtemp.ofsSurfaces  = LittleLong( lodtemp.ofsSurfaces );
      lodtemp.ofsEnd       = LittleLong( lodtemp.ofsEnd );

      SafeWrite( modelouthandle, &lodtemp, sizeof( lodtemp ) );

      //
      // write out the surfaces
      //
      insurf = model.surfaces;
      outsurf = surftemp;
      for( i = 0; i < model.numsurfaces; i++, insurf++, outsurf++ )
         {
		   if ( insurf->numtris == 0 )
            {
			   continue;
            }

         // calculate the offset to the header
         outsurf->ofsHeader = LittleLong( -ftell( modelouthandle ) );

         SafeWrite( modelouthandle, outsurf, sizeof( md4Surface_t ) );

         //
         // write out the vertices
         //
         vert = insurf->verts;
	      for( j = 0; j < insurf->numverts; j++, vert++ )
            {
            tempvert.normal[ 0 ] = LittleFloat( vert->normal[ 0 ] );
            tempvert.normal[ 1 ] = LittleFloat( vert->normal[ 1 ] );
            tempvert.normal[ 2 ] = LittleFloat( vert->normal[ 2 ] );

            tempvert.texCoords[ 0 ] = LittleFloat( vert->texCoords[ 0 ] );
            tempvert.texCoords[ 1 ] = LittleFloat( vert->texCoords[ 1 ] );

            tempvert.numWeights = LittleLong( vert->numbones );

            SafeWrite( modelouthandle, &tempvert, sizeof( tempvert ) - sizeof( tempvert.weights ) );

            if ( !vert->numbones )
               {
               Error( "Vertex with no bones found in surface '%s'(%d).\n", insurf->name, insurf->id );
               }

            for( k = 0; k < vert->numbones; k++ )
               {
               tempweight.boneIndex   = LittleLong( vert->blend[ k ].bone );
               tempweight.boneWeight  = LittleFloat( vert->blend[ k ].weight );
               tempweight.offset[ 0 ] = LittleFloat( vert->blend[ k ].offset[ 0 ] );
               tempweight.offset[ 1 ] = LittleFloat( vert->blend[ k ].offset[ 1 ] );
               tempweight.offset[ 2 ] = LittleFloat( vert->blend[ k ].offset[ 2 ] );

               SafeWrite( modelouthandle, &tempweight, sizeof( tempweight ) );
               }
            }

         //
         // write out the triangles
         //
         for( j = 0; j < insurf->numtris; j++ )
            {
            tritemp[ j ].indexes[ 0 ] = LittleLong( insurf->tris[ j ][ 0 ] );
            tritemp[ j ].indexes[ 1 ] = LittleLong( insurf->tris[ j ][ 1 ] );
            tritemp[ j ].indexes[ 2 ] = LittleLong( insurf->tris[ j ][ 2 ] );
            }

         SafeWrite( modelouthandle, tritemp, insurf->numtris * sizeof( skelTriangle_t ) );

         //
         // write out the bone references
         //
         for( j = 0; j < numbonerefs[ i ]; j++ )
            {
            bonerefs[ i ][ j ] = LittleLong( bonerefs[ i ][ j ] );
            }

         SafeWrite( modelouthandle, bonerefs[ i ], numbonerefs[ i ] * sizeof( bonerefs[ i ][ 0 ] ) );
         }
      }

   if ( verbose )
      {
	   printf( "%4d surfaces\n", model.numsurfaces );
	   printf( "%4d bones\n", model.numbones );
	   printf( "%4d verts\n", model.numverts );
	   printf( "file size: %d\n", ( int )ftell( modelouthandle ) );
	   printf( "---------------------\n" );
      }

	fclose( modelouthandle );
   }

bool is_file_valid
   (
   char *filename
   )

   {
	FILE *temp_file;
	bool valid;
   
   valid = false;

   temp_file = fopen( filename, "rb" );
	if ( temp_file != NULL )
	   {
		fclose( temp_file );
		valid = true;
	   }

	return valid;
   }

int main
   (
   int argc,
   char * argv[]
   )

   {
   SkelModel   skel;
   SkelModel   baseskel;
   char        dest_filename[ 128 ];
   char        src_filename[ 128 ];
   char        uv_filename[ 128 ];
   char        bone_filename[ 128 ];
   bool        use_uv;
   bool        use_bone;
   FILE        *f;
   int         srctime;
   int         desttime;
   int         i;
   int         maxbones;
   float       weightthreshold;

   myargc = argc;
   myargv = argv;

	if ( argc < 2 )
	   {
		Error( "max2skl animname [-uv filename] [-force] [-scale num] [-dest name]\n"
             "                 [-ignore filename] [-origin originname] [-reverse]\n"
             "                 [-verbose] [-nolod] [-noclampz] [-zeroz] [-noorigin]\n"
             "                 [-clearz] [-clearxy] [-baseframe] [-maxbones num]\n"
             "                 [-weightthreshold num] [-md4] [-bones filename]\n"
             "                 [-offset x y z] [-clearx] [-cleary] [-loop]\n"
             "                 [-zerox] [-zeroy] [-uvb filename] [-destdir dirname]\n"
             "                 [-ignoreflags] [-fps num]\n" );
	   }

   verbose = qfalse;
   if ( CheckParm( "-verbose" ) )
      {
      verbose = qtrue;
      printf(" Verbose mode enabled.\n" );
      }

   reverse = false;
   if ( CheckParm( "-reverse" ) )
      {
      reverse = true;
      if ( verbose )
         printf(" Animation will be reversed.\n" );
      }

   nolod = false;
   if ( CheckParm( "-nolod" ) )
      {
      nolod = true;
      if ( verbose )
         printf(" No LOD map created.\n" );
      }

   zerox = false;
   if ( CheckParm( "-zeroy" ) )  // X & Y axis are swapped in Q3
      {
      zerox = true;
      if ( verbose )
         printf(" Delta Y movement will be zeroed.\n" );
      }

   zeroy = false;
   if ( CheckParm( "-zerox" ) )  // X & Y axis are swapped in Q3
      {
      zeroy = true;
      if ( verbose )
         printf(" Delta X movement will be zeroed.\n" );
      }

   zeroz = false;
   if ( CheckParm( "-zeroz" ) )
      {
      zeroz = true;
      if ( verbose )
         printf(" Delta Z movement will be zeroed.\n" );
      }

   noclampz = false;
   if ( CheckParm( "-noclampz" ) )
      {
      noclampz = true;
      if ( verbose )
         printf(" Delta Z movement will not be clamped.\n" );
      }

   loop = false;
   if ( CheckParm( "-loop" ) )
      {
      loop = true;
      if ( verbose )
         printf(" Looping enabled.  Last frame of animation will not be exported.\n" );
      }

   clearz = false;
   if ( CheckParm( "-clearz" ) )
      {
      clearz = true;
      if ( verbose )
         printf(" Delta Z movement will be cleared after vertices are moved.\n" );
      }
   
   clearx = false;
   if ( CheckParm( "-cleary" ) ) // X & Y axis are swapped in Q3
      {
      clearx = true;
      if ( verbose )
         printf(" Delta Y movement will be cleared after vertices are moved.\n" );
      }
   
   cleary = false;
   if ( CheckParm( "-clearx" ) ) // X & Y axis are swapped in Q3
      {
      cleary = true;
      if ( verbose )
         printf(" Delta X movement will be cleared after vertices are moved.\n" );
      }
   
   clearxy = false;
   if ( CheckParm( "-clearxy" ) )
      {
      clearxy = true;
      if ( verbose )
         printf(" Delta XY movement will be cleared after vertices are moved.\n" );
      }

   noorigin = false;
   if ( CheckParm( "-noorigin" ) )
      {
      noorigin = true;
      if ( verbose )
         printf(" Origin is being ignored.\n" );
      }

   force = false;
   if ( CheckParm( "-force" ) )
      {
      force = true;
      printf(" forced no timecheck performed.\n" );
      }

   baseframe = false;
   if ( CheckParm( "-baseframe" ) )
      {
      baseframe = true;
      if ( verbose )
         printf(" Baseframe export.\n" );
      }

   md4 = false;
   if ( CheckParm( "-md4" ) )
      {
      md4 = true;
      if ( verbose )
         printf(" MD4 export.\n" );
      }

   ignoreflags = false;
   if ( CheckParm( "-ignoreflags" ) )
      {
      ignoreflags = true;
      if ( verbose )
         printf(" Ignoring flags when removing bones.\n" );
      }

   // set the maxbones if necessary
   maxbones = MAX_BLENDBONES;
   if ( i = CheckParm( "-maxbones" ) )
      {
      maxbones = atoi( argv[ i + 1 ] );
      if ( verbose )
         printf(" maxbones set at %d.\n", maxbones );
      }

   // set the weightthreshold if necessary
   weightthreshold = 0.01;
   if ( i = CheckParm( "-weightthreshold" ) )
      {
      weightthreshold = atof( argv[ i + 1 ] );
      if ( verbose )
         printf(" weightthreshold set at %f.\n", weightthreshold );
      }

   // set the fps adjustment if necessary
   adjustfps = false;
   if ( i = CheckParm( "-fps" ) )
      {
      adjustfps = true;
      fps = atof( argv[ i + 1 ] );
      if ( verbose )
         printf(" frames per second set at %f.\n", fps );
      }

   // set the scale if necessary
   scale_factor = 1;
   if ( i = CheckParm( "-scale" ) )
      {
      scale_factor = atof( argv[ i + 1 ] );
      if ( verbose )
         printf(" scale set at %f.\n", scale_factor );
      }

   // set the offset if necessary
   modeloffset = Vector( 0, 0, 0 );
   if ( i = CheckParm( "-offset" ) )
      {
      if ( i + 3 >= argc )
         {
         Error( "Not enough arguments for -offset.  Usage: -offset x y z\n" );
         }

       // X & Y axis are swapped in Q3
      modeloffset.x = -atof( argv[ i + 2 ] );
      modeloffset.y = atof( argv[ i + 1 ] );
      modeloffset.z = atof( argv[ i + 3 ] );
      if ( verbose )
         {
         printf(" offset set to (%f %f %f).\n", modeloffset.x, modeloffset.y, modeloffset.z );
         }
      }

   // see if a new origin was specified
   if ( i = CheckParm( "-origin" ) )
      {
      originname = argv[ i + 1 ];
      if ( verbose )
         printf(" origin set to %s.\n", originname.c_str() );
      }

   // see if an ignore list is specified
   if ( i = CheckParm( "-ignore" ) )
      {
      skel.LoadIgnoreFile( argv[ i + 1 ] );
      baseskel.LoadIgnoreFile( argv[ i + 1 ] );
      }

   strcpy( src_filename, argv[ 1 ] );
   strcat( src_filename, ".skl" );

   // check for destination directory
   if ( i = CheckParm( "-destdir" ) )
      {
      sprintf( writedir, "%s", argv[ i + 1 ] );
      qprintf( "Destination directory changed to %s.\n", writedir );
      }

   // create destination filename
   // check for dest file
   if ( i = CheckParm( "-dest" ) )
      {
      sprintf( dest_filename, "%s%s", writedir, argv[ i + 1 ] );
      }
   else
      {
      sprintf( dest_filename, "%s%s", writedir, src_filename );
      }

   StripExtension( dest_filename );
   if ( baseframe )
      {
      strcat( dest_filename, ".skb" );
      }
   else if ( md4 )
      {
      strcat( dest_filename, ".md4" );
      }
   else 
      {
      strcat( dest_filename, ".ska" );
      }

	// Make sure the SKL file is really there
	if ( !is_file_valid( src_filename ) )
	   {
		Error( "File '%s' not found", src_filename );
	   }

   // check the time stamps
   srctime = FileTime( src_filename );
   desttime = FileTime( dest_filename );

   // check for version number difference
   if ( !force && ( desttime > 0 ) )
      {
      f = SafeOpenRead( dest_filename );

      // read header
      SafeRead( f, &i, sizeof( i ) );
      if ( ( baseframe && ( i != TIKI_SKEL_IDENT ) ) ||
         ( !baseframe && ( i != TIKI_SKEL_ANIM_IDENT ) ) )
         {
         printf( " file identitifier differs, regrabbing.\n" );
         force = true;
         }

      // read version
      SafeRead( f, &i, sizeof( i ) );
      i = LittleLong( i );
      if ( i != TIKI_SKEL_VERSION )
         {
         printf( " version numbers differ, regrabbing.\n" );
         force = true;
         }

      fclose( f );
      }

   if ( srctime > desttime )
      {
      force = true;
      }

   // check for uv file
   use_uv = false;
   if ( ( i = CheckParm( "-uv" ) ) || ( i = CheckParm( "-uvb" ) ) )
      {
   	// check the date and time of the uv file
      strcpy( uv_filename, argv[ i + 1 ] );
      if ( !strstr( uv_filename, "." ) )
         {
         StripExtension( uv_filename );
         strcat( uv_filename, ".skl" );
         }
   
      srctime = FileTime( uv_filename  );
      if ( srctime > desttime )
         {
         force = true;
         }

      use_uv = true;
      }

   // check for bone file
   use_bone = false;
   if ( ( i = CheckParm( "-bones" ) ) || ( i = CheckParm( "-uvb" ) ) )
      {
   	// check the date and time of the bones file
      strcpy( bone_filename, argv[ i + 1 ] );
      if ( !strstr( bone_filename, "." ) )
         {
         StripExtension( bone_filename );
         strcat( bone_filename, ".skl" );
         }

      srctime = FileTime( bone_filename  );
      if ( srctime > desttime )
         {
         force = true;
         }

      use_bone = true;
      }

   if ( !force )
      {
      if ( -verbose )
         {
         printf(" destination is newer than source, skipping.\n" );
         }

      return 0;
      }

   skel.LoadSKL( src_filename );

   if ( use_uv )
      {
      // Load the uv coordinates from the uv file
      qprintf( "Grabbing surfaces from %s.\n", uv_filename );
      baseskel.LoadSKL( uv_filename );
      skel.CopyBaseModel( baseskel );
      }
   
   if ( use_bone )
      {
   	// Load the bone names from the bones file
      qprintf( "Merging bones from %s.\n", bone_filename );
      baseskel.LoadSKL( bone_filename );
      skel.CopyBones( baseskel );
      }

   skel.ConvertToQuake3Worldspace();

   skel.ScaleModel( scale_factor );
   if ( reverse )
      {
      skel.ReverseAnimation();
      }

   skel.ReduceBonesPerVertex( maxbones, weightthreshold );

   skel.FixMirroredBones();
   skel.CreateSurfaces();
   skel.CalculateTags();
   skel.RemoveUnusedBones();

   // check if we should create a baseframe or an animation
   if ( baseframe )
      {
      skel.ComputeVertexNormals();

      if ( !nolod )
         {
         skel.CalculateLOD();
         }

      skel.CalculateTriStrips();
      skel.SaveBaseFrame( dest_filename );
      }
   else if ( !md4 )
      {
      skel.CalculateBounds();
      skel.SaveAnimation( dest_filename );
      }
   else
      {
      skel.ComputeVertexNormals();
      skel.CalculateTriStrips();
      skel.CalculateBounds();
      skel.SaveMD4( dest_filename );
      }

   return 0;
   }

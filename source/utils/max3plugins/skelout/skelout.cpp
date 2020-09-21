//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max3plugins/skelout/skelout.cpp              $
// $Revision:: 29                                                             $
//     $Date:: 6/21/00 3:48p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max3plugins/skelout/skelout.cpp                   $
// 
// 29    6/21/00 3:48p Markd
// modified minimum framerate
// 
// 28    1/26/00 10:53a Jimdose
// fixed bug where lower samplerates resulted in slower animations instead of
// faster
// 
// 27    1/19/00 3:30p Jimdose
// added cancel button to progress dialog
// 
// 26    1/15/00 3:47p Jimdose
// put some bounds checks on calls to GetNodeIndex
// 
// 25    1/07/00 6:39p Jimdose
// no longer leaves progress bar up when out of memory
// 
// 24    1/07/00 3:33p Jimdose
// fixed problem with last frame not being exported
// 
// 23    12/13/99 2:18p Jimdose
// changed Error to throw an exception (fixes crash that could occur in some
// situations on exit from Error)
// don't show AnimScale dialog if suppressPrompts is true (allows batch
// processing of exports)
// 
// 22    10/22/99 6:03p Jimdose
// changed vertex type check in GetPhysiqueVertex
// 
// 21    10/18/99 5:16p Jimdose
// made cancel button on framerate dialog cancel export
// fixed calculation of tinc
// changed use of malloc to new
// 
// 20    10/14/99 6:27p Jimdose
// Max 2.5 didn't have Length as a member of Point3
// 
// 19    10/14/99 6:24p Jimdose
// changed GetPhysiqueVertex to account for scaling on bone
// 
// 18    10/12/99 5:10p Jimdose
// print out total frames when converting anim
// 
// 17    10/12/99 12:23p Jimdose
// made changes for Max 3 work with Max 2.5
// 
// 16    10/12/99 12:18p Jimdose
// made work with Max 3
// 
// 15    10/11/99 2:53p Jimdose
// fixed some documentation that was wrong
// 
// 14    10/11/99 1:12p Jimdose
// fixed exporting of bone linked objects
// 
// 13    10/08/99 7:23p Jimdose
// added CollectMaterials
// reordered model format
// 
// 12    10/06/99 12:45p Jimdose
// added GetVertexNormal
// calc vertex normals and smoothing groups
// 
// 11    10/05/99 1:29p Jimdose
// removed unused variable from GetNonRigidVertex
// 
// 10    10/04/99 8:19p Jimdose
// added GetNonRigidVertex
// 
// 9     10/04/99 5:02p Jimdose
// AddObject now accounts for verts and tris on objects that we can't get an
// Export Interface for
// 
// 8     9/24/99 3:28p Jimdose
// added on to material id's so they match with those from UVOUT
// 
// 7     9/07/99 6:42p Jimdose
// moved parent out of anim frames when exporting
// 
// 6     9/07/99 5:47p Jimdose
// added progress bar
// 
// 5     9/07/99 5:38p Jimdose
// 
// 4     9/07/99 3:12p Jimdose
// rewrote for ascii output
// 
// 3     9/03/99 7:12p Jimdose
// working version
// 
// 2     7/30/99 4:23p Jimdose
// working on skel output
// 
// 1     7/19/99 5:15p Jimdose
//
// DESCRIPTION:
// A MAX2 plugin that outputs skeletal animations
// 

#include "skelout.h"
#include <float.h>
#include "dllmain.h"
#include "resource.h"
#include "util.h"
#include "enumobjects.h"

#if (MAX_RELEASE >= 3000)
#pragma comment( lib, "core.lib" )
#pragma comment( lib, "util.lib" )
#pragma comment( lib, "mesh.lib" )
#pragma comment( lib, "geom.lib" )
#pragma comment( lib, "maxutil.lib" )
#endif

SkelOutClassDesc SkelOutDesc;

int     SkelExport::s_startframe;
int     SkelExport::s_stopframe;
double  SkelExport::s_framerate;
double  SkelExport::s_samplerate;
bool    SkelExport::cancel = false;

void Sys_Update
   (
   void
   )

   {
   MSG msg;

   while( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
      {
      if ( GetMessage( &msg, NULL, 0, 0 ) )
         {
         TranslateMessage( &msg );
         DispatchMessage( &msg );
         }
      }
   }

int SkelExport::GetNodeIndex
   (
   INode *node
   )

   {
   int i;
	str name( node->GetName() );

	for( i = 1; i <= bonenames.NumObjects(); i++ )
      {
      if ( !name.icmp( bonenames.ObjectAt( i ) ) )
         {
         return i - 1;
         }
      }
   
   return UNUSED_BONE;
   }

void SkelExport::GetNonRigidVertex
   (
   INode *node,
   loadvertx_t *vert,
   int index
   )

   {
   Point3  p;
   Matrix3 tm;

   vert->numbones = 1;

   vert->blend[ 0 ].bone = GetNodeIndex( node );
   if ( vert->blend[ 0 ].bone == UNUSED_BONE )
      {
      Error( "Found vertex attached to unused bone!" );
      }

   if ( !model.usedbone[ vert->blend[ 0 ].bone ] )
      {
      model.usedbone[ vert->blend[ 0 ].bone ] = true;
      model.numbonesused++;
      }

   // get the world orientation
   tm = node->GetObjTMAfterWSM( interfaceptr->GetTime() );
   p = tm * mesh->verts[ index ];
   
   // get the node orientation
	tm = node->GetNodeTM( interfaceptr->GetTime() );
   p = Inverse( tm ) * p;

   vert->blend[ 0 ].offset[ 0 ] = p.x;
   vert->blend[ 0 ].offset[ 1 ] = p.y;
   vert->blend[ 0 ].offset[ 2 ] = p.z;

   vert->blend[ 0 ].weight = 1.0f;
   }

void SkelExport::GetPhysiqueVertex
   (
   loadvertx_t *vert,
   int index
   )

   {
   IPhyVertexExport        *vexp;
   IPhyBlendedRigidVertex  *v;
   INode                   *bone;
   blendvert_t             *blend;
   Point3                  p;
   int                     n;
   int                     i;
   int                     type;
   Matrix3                 tm;
   Point3                  s;

   vert->numbones = 0;

   vexp = context->GetVertexInterface( index );
   if ( vexp )
      {
      // check if vertex has blending
      type = vexp->GetVertexType();
      if ( type == RIGID_BLENDED_TYPE )
		   {
         v = ( IPhyBlendedRigidVertex * )vexp;

         n = v->GetNumberNodes();
         if ( n > MAX_BLENDBONES )
            { 
            n = MAX_BLENDBONES;
            }

         vert->numbones = n;
         blend = vert->blend;
         for( i = 0; i < n; i++, blend++ )
            {
            bone = v->GetNode( i );
            blend->bone = GetNodeIndex( bone );
            if ( blend->bone == UNUSED_BONE )
               {
               Error( "Found vertex attached to unused bone!" );
               }

            if ( !model.usedbone[ blend->bone ] )
               {
               model.usedbone[ blend->bone ] = true;
               model.numbonesused++;
               }

            // get the bone scaling
            tm = bone->GetNodeTM( interfaceptr->GetTime() );
            s.x = Length( tm.GetRow( 0 ) );
            s.y = Length( tm.GetRow( 1 ) );
            s.z = Length( tm.GetRow( 2 ) );

            // scale the offset and store it in our vertex
            p = v->GetOffsetVector( i );
            blend->offset[ 0 ] = p.x * s.x;;
            blend->offset[ 1 ] = p.y * s.y;;
            blend->offset[ 2 ] = p.z * s.z;;

            blend->weight = v->GetWeight( i );
            }
		   }
		else 
		   {
         vert->numbones = 1;

		   bone = ( ( IPhyRigidVertex * )vexp )->GetNode();

         vert->blend[ 0 ].bone = GetNodeIndex( bone );
         if ( vert->blend[ 0 ].bone == UNUSED_BONE )
            {
            Error( "Found vertex attached to unused bone!" );
            }

         if ( !model.usedbone[ vert->blend[ 0 ].bone ] )
            {
            model.usedbone[ vert->blend[ 0 ].bone ] = true;
            model.numbonesused++;
            }

         // get the bone scaling
         tm = bone->GetNodeTM( interfaceptr->GetTime() );
         s.x = Length( tm.GetRow( 0 ) );
         s.y = Length( tm.GetRow( 1 ) );
         s.z = Length( tm.GetRow( 2 ) );

         // scale the offset and store it in our vertex
         p = ( ( IPhyRigidVertex * )vexp )->GetOffsetVector();
         vert->blend[ 0 ].offset[ 0 ] = p.x * s.x;
         vert->blend[ 0 ].offset[ 1 ] = p.y * s.y;
         vert->blend[ 0 ].offset[ 2 ] = p.z * s.z;
      
         vert->blend[ 0 ].weight = 1.0f;
		   }

      context->ReleaseVertexInterface( vexp );
	   }
   }

Modifier *SkelExport::FindPhysiqueModifier
   (
   INode *nodePtr
   )

   {
   int ModStackIndex;
   Modifier *ModifierPtr;
   IDerivedObject *DerivedObjectPtr;

	// Get object from node. Abort if no object.
	Object *ObjectPtr = nodePtr->GetObjectRef();
	if ( !ObjectPtr ) 
      {
      return NULL;
      }

	// Is derived object ?
	if ( ObjectPtr->SuperClassID() == GEN_DERIVOB_CLASS_ID )
	   {
		// Yes -> Cast.
		DerivedObjectPtr = static_cast< IDerivedObject * >( ObjectPtr );

		// Iterate over all entries of the modifier stack.
		for( ModStackIndex = 0; ModStackIndex < DerivedObjectPtr->NumModifiers(); ModStackIndex++ )
		   {
			// Get current modifier.
			ModifierPtr = DerivedObjectPtr->GetModifier( ModStackIndex );

			// Is this Physique ?
			if ( ModifierPtr->ClassID() == Class_ID( PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B ) )
			   {
				// Yes -> Exit.
				return ModifierPtr;
			   }
		   }
	   }

	// Not found.
	return NULL;
   }

void SkelExport::GetVertexNormal
   (
   int vertindex,
   int smoothingGroup,
   float normal[ 3 ]
   )

   {
   int      numnormals;
   int      i;
   int      num;
   RVertex  *rvert;
   Point3   norm;

   rvert = mesh->getRVertPtr( vertindex );
	numnormals = rvert->rFlags & NORCT_MASK;

	if ( numnormals == 1 )
      {
		norm = rvert->rn.getNormal();
      }
	else
	   {
   	assert( rvert->ern != NULL );

      num = 0;
		for( i = 0; i < numnormals; i++ )
         {
			if ( rvert->ern[ i ].getSmGroup() & smoothingGroup )
            {
            num = i;
				break;
            }
         }

		norm = rvert->ern[ num ].getNormal();
	   }

   normal[ 0 ] = norm.x;
   normal[ 1 ] = norm.y;
   normal[ 2 ] = norm.z;
   }

void SkelExport::AddObject
   (
   Object *obj,
   INode *node
   )

	{
	TriObject         *tri;
   loadvertx_t       *loadvert;
   loadtriangle_t    *loadface;
   loadfacevertx_t   *loadfacevert;
   loadobject_t      *loadobject;
   Point3            normal;
	IPhysiqueExport	*exp;
   Modifier				*modifier;
   int               smoothingGroup;
   int               index;
   int               i;
   int               j;

	context  = NULL;
	exp      = NULL;
   modifier = NULL;
   mesh     = NULL;

   // convert it into a triobject
   tri = ( TriObject * )obj->ConvertToType( interfaceptr->GetTime(), triObjectClassID );
   if ( !tri )
      {
      return;
      }

   // get the mesh
	mesh = &tri->mesh;

   // Ensure that the vertex normals are up-to-date
	mesh->buildNormals();

   loadobject = &model.objects[ model.numobjects ];
   loadobject->startvert = model.numverts;
   loadobject->startface = model.numfaces;

   loadvert = &model.verts[ loadobject->startvert ];
   loadface = &model.faces[ loadobject->startface ];

   // get the name of this node
   strcpy( loadobject->name, node->GetName() );

   // get the number of vertices
   loadobject->numverts = mesh->getNumVerts();

   // get the number of faces
   loadobject->numfaces = mesh->getNumFaces();
   if ( !loadobject->numverts || !loadobject->numfaces )
      {
      return;
      }

   // find out if there are TVerts
   model.hasmapping = ( mesh->getNumTVerts() > 0 );

	// get the Physique modifier for this node
   modifier = FindPhysiqueModifier( node );
   if ( modifier )
	   {
		// get the export interface
	   exp = ( IPhysiqueExport * )modifier->GetInterface( I_PHYINTERFACE );
      if ( exp )
         {
         // get the Context Export Interface for the node
         context = ( IPhyContextExport * )exp->GetContextInterface( node );
         if ( context )
		      {
            // convert all vertices to Rigid 
            context->ConvertToRigid( TRUE );
		      }
		   }
		}

   // if we failed we need to grab the vertices another way
   if ( !context )
      {
      // copy the verts as being attached to a single bone
      for( i = 0; i < loadobject->numverts; i++, loadvert++ )
         {
         UpdateProgressBar( ( float )i / ( float )loadobject->numverts );
         GetNonRigidVertex( node, loadvert, i );

         Sys_Update();
         if ( cancel )
            {
            return;
            }
         }
      }
   else
      {
      // grab the vertices
      for( i = 0; i < loadobject->numverts; i++, loadvert++ )
         {
         UpdateProgressBar( ( float )i / ( float )loadobject->numverts );
	      GetPhysiqueVertex( loadvert, i );

         Sys_Update();
         if ( cancel )
            {
            return;
            }
         }
      }

   // grab the faces
   for( i = 0; i < loadobject->numfaces; i++, loadface++ )
      {
      smoothingGroup = mesh->faces[ i ].getSmGroup();
      normal = mesh->getFaceNormal( i );
      for( j = 0; j < 3; j++ )
         {
         index = mesh->faces[ i ].getVert( j );
         loadvert = &model.verts[ loadobject->startvert + index ];
		   if ( smoothingGroup )
		      {
            GetVertexNormal( index, smoothingGroup, loadvert->normal );
		      }
		   else 
		      {
            loadvert->normal[ 0 ] = normal.x;
            loadvert->normal[ 1 ] = normal.y;
            loadvert->normal[ 2 ] = normal.z;
		      }

         loadfacevert = &loadface->verts[ j ];
         loadfacevert->vertindex = ( mesh->faces[ i ].v[ 2 - j ] + loadobject->startvert );
         if ( model.hasmapping )
            {
            loadfacevert->s = mesh->tVerts[ mesh->tvFace[ i ].t[ 2 - j ] ].x;
            loadfacevert->t = 1.0f - mesh->tVerts[ mesh->tvFace[ i ].t[ 2 - j ] ].y;
            }
         else
            {
            loadfacevert->s = 0.0f;
            loadfacevert->t = 0.0f;
            }
         }

      // UVOUT adds one to material id's, so we must do the same
      loadface->id = mesh->faces[ i ].getMatID() + 1;

      Sys_Update();
      if ( cancel )
         {
         return;
         }
      }

   model.numverts += loadobject->numverts;
   model.numfaces += loadobject->numfaces;
   model.numobjects++;

   // clean up after ourselves
   if ( modifier && exp )
      {
	   exp->ReleaseContextInterface( context );
      modifier->ReleaseInterface( I_PHYINTERFACE, exp );
      }

	context = NULL;
	}

void SkelExport::AddBoneFrame
   (
   Object *obj,
   INode *node
   )

	{
	int         bonenum;
   Matrix3     orientation;
   Point3      origin;
   Point3      row;
   INode       *parent;
   str         name( node->GetName() );
   int         i;
   int         j;

   if ( node->IsRootNode() )
      {
      Error( "Encountered a root node!" );
      }
   
   bonenum = GetNodeIndex( node );
   if ( bonenum > MAX_BONES )
      {
      Error( "Exceeded MAX_BONES!" );
      }

   if ( bonenum == UNUSED_BONE )
      {
      return;
      }

   // get the parent node
	parent = node->GetParentNode();

   // get the node orientation
	orientation = node->GetNodeTM( interfaceptr->GetTime() );
   orientation.NoScale();
	origin = orientation.GetTrans();

	// Get the orienation
   single.bones[ bonenum ].parent = GetNodeIndex( parent );
   for( i = 0; i < 3; i++ )
      {
      single.bones[ bonenum ].offset[ i ] = origin[ i ];

      row = orientation.GetRow( i );
      for( j = 0; j < 3; j++ )
         {
         single.bones[ bonenum ].matrix[ i ][ j ] = row[ j ];
         }
      }
   }

void SkelExport::CollectMaterials
   (
   void
   )

   {
   int i;
   int j;

   model.nummaterials = 0;
	for( i = 0; i < model.numfaces; i++ )
	   {
      for( j = 0; j < model.nummaterials; j++ )
         {
         if ( model.materials[ j ] == model.faces[ i ].id )
            {
            break;
            }
         }

      if ( j == model.nummaterials )
         {
         model.materials[ model.nummaterials++ ] = model.faces[ i ].id;
         }
      }
   }

void SkelExport::SortObjectNames
   (
   Container<int> &sorted
   )

   {
   int i;
   int j;
   int num;
   int smallest;
   Container<int> processed;

   //
   // Sort the object names
   //
   num = objectnames.NumObjects();

   sorted.FreeObjectList();
   sorted.Resize( num );
   processed.Resize( num );

   smallest = 0;
   for( i = 1; i <= num; i++ )
      {
      sorted.AddObject( smallest );
      processed.AddObject( smallest );
      }

   for( i = 1; i <= num; i++ )
      {
      smallest = -1;
      for( j = 1; j <= num; j++ )
         {
         if ( processed.ObjectAt( j ) )
            {
            continue;
            }

         if ( ( smallest < 1 ) || ( strcmpi( objectnames.ObjectAt( j ).c_str(), 
            objectnames.ObjectAt( smallest ).c_str() ) < 0 ) )
            {
            smallest = j;
            }
         }

      sorted.ObjectAt( i ) = smallest;
      processed.ObjectAt( smallest ) = 1;
      }
   }

void SkelExport::SaveAnimFile
   (
   const char *filename, 
   loadframe_t *anim, 
   int numframes, 
   float framerate
   )

   {
   FILE * out;
   int i;
   int j;
   int num;

   out = SafeOpenWrite( filename );

   // write out numframes
   SafeWrite( out, &numframes, sizeof( numframes ) );

   // write out framerate
   SafeWrite( out, &framerate, sizeof( framerate ) );

   // write out num vertices
   SafeWrite( out, &model.numverts, sizeof( model.numverts ) );

   // write out vertices
   for( i = 0; i < model.numverts; i++ )
      {
      SafeWrite( out, &model.verts[ i ].numbones, sizeof( model.verts[ i ].numbones ) );
      SafeWrite( out, &model.verts[ i ].normal, sizeof( model.verts[ i ].normal ) );
      for( j = 0; j < model.verts[ i ].numbones; j++ )
         {
         SafeWrite( out, &model.verts[ i ].blend[ j ], sizeof( model.verts[ i ].blend[ j ] ) );
         }
      }

   // write out num faces
   SafeWrite( out, &model.numfaces, sizeof( model.numfaces ) );

   // write out faces
   SafeWrite( out, model.faces, sizeof( loadtriangle_t ) * model.numfaces );

   // write out num bones
   num = bonenames.NumObjects();
   SafeWrite( out, &num, sizeof( num ) );

   // write out each frame's data
	for( i = 0; i < numframes; i++ )
      {
      SafeWrite( out, &anim[ i ].bones, sizeof( loadbone_t ) * num );
      }

   fclose( out );
   }

void SkelExport::SaveAnimFileText
   (
   const char *filename, 
   loadframe_t *anim, 
   int numframes, 
   float framerate
   )

   {
   FILE           *out;
   int            i;
   int            j;
   int            num;
   blendvert_t    *b;
   loadtriangle_t *tri;
   loadbone_t     *bone;

   out = SafeOpenWriteText( filename );

   // write out header
   fprintf( out, "//////////////////////////////////////////////////////////////////////////\n" );
   fprintf( out, "//\n" );
   fprintf( out, "// Exported by %s, Version %.2f.\n", LONG_DESCRIPTION, VERSION * 0.01f );
   fprintf( out, "//\n" );
   fprintf( out, "//////////////////////////////////////////////////////////////////////////\n\n" );
   fprintf( out, "SKELETON\n" );

   // write out version number
   fprintf( out, "VERSION %d\n\n", SKL_VERSION );

   // export the materials
   fprintf( out, "NUMMATERIALS %d\n", model.nummaterials );
   for( i = 0; i < model.nummaterials; i++ )
      {
      fprintf( out, "MATERIAL %d material%d\n", model.materials[ i ], model.materials[ i ] );
      }

   // separator
   fprintf( out, "\n" );

   // write out bone names
   num = bonenames.NumObjects();
   fprintf( out, "NUMBONES %d\n", num );
   for( i = 1; i <= bonenames.NumObjects(); i++ )
      {
      fprintf( out, "BONE %d %d %s\n", i - 1, anim[ 0 ].bones[ i - 1 ].parent, bonenames.ObjectAt( i ).c_str() );
      }

   // separator
   fprintf( out, "\n" );

   // write out vertices
   fprintf( out, "NUMVERTS %d\n", model.numverts );
   for( i = 0; i < model.numverts; i++ )
      {
      fprintf( out, "VERT %d\n", i );

      fprintf( out, "NORMAL %f %f %f\n", 
         model.verts[ i ].normal[ 0 ], model.verts[ i ].normal[ 1 ], model.verts[ i ].normal[ 2 ] );

      fprintf( out, "BONES %d\n", model.verts[ i ].numbones );

      b = model.verts[ i ].blend;
      for( j = 0; j < model.verts[ i ].numbones; j++, b++ )
         {
         fprintf( out, "BONE %d %f %f %f %f\n", b->bone, b->weight, b->offset[ 0 ], b->offset[ 1 ], b->offset[ 2 ] );
         }
      
      // separator
      fprintf( out, "\n" );
      }

   // write out faces
   // write out num faces
   fprintf( out, "NUMFACES %d\n", model.numfaces );
   tri = model.faces;
   for( i = 0; i < model.numfaces; i++, tri++ )
      {
      fprintf( out, "TRI %d %d %f %f %d %f %f %d %f %f\n", tri->id,
         tri->verts[ 0 ].vertindex, tri->verts[ 0 ].s, tri->verts[ 0 ].t,
         tri->verts[ 1 ].vertindex, tri->verts[ 1 ].s, tri->verts[ 1 ].t,
         tri->verts[ 2 ].vertindex, tri->verts[ 2 ].s, tri->verts[ 2 ].t );
      }

   // separator
   fprintf( out, "\n" );

   // write out framerate
   fprintf( out, "FRAMERATE %f\n", ( float )framerate );

   // write out numframes
   fprintf( out, "NUMFRAMES %d\n", numframes );

   // write out each frame's data
	for( i = 0; i < numframes; i++ )
      {
      // separator
      fprintf( out, "\n" );

      fprintf( out, "FRAME %d\n", i );

      bone = anim[ i ].bones;
      for( j = 0; j < num; j++, bone++ )
         {
         fprintf( out, "BONE %d\n", j );
         fprintf( out, "OFFSET %f %f %f\n", bone->offset[ 0 ], bone->offset[ 1 ], bone->offset[ 2 ] );
         fprintf( out, "X %f %f %f\n", bone->matrix[ 0 ][ 0 ], bone->matrix[ 0 ][ 1 ], bone->matrix[ 0 ][ 2 ] );
         fprintf( out, "Y %f %f %f\n", bone->matrix[ 1 ][ 0 ], bone->matrix[ 1 ][ 1 ], bone->matrix[ 1 ][ 2 ] );
         fprintf( out, "Z %f %f %f\n", bone->matrix[ 2 ][ 0 ], bone->matrix[ 2 ][ 1 ], bone->matrix[ 2 ][ 2 ] );

         // separator
         fprintf( out, "\n" );
         }
      }

   fprintf( out, "END\n" );

   fclose( out );
   }

BOOL CALLBACK SkelExport::StatusDlgProc
   (
   HWND hwndDlg,	// handle to dialog box
   UINT uMsg,	   // message
   WPARAM wParam,	// first message parameter
   LPARAM lParam 	// second message parameter
   )

   {
	switch( uMsg )
      {
      case WM_COMMAND:
         switch( LOWORD( wParam ) )
            {
            case IDCANCEL:
               cancel = true;
               break;
            }

         return FALSE;
         break;
      }

   return FALSE;
   }

BOOL CALLBACK SkelExport::GetAnimScaleDlgProc
   (
   HWND hwndDlg,	// handle to dialog box
   UINT uMsg,	   // message
   WPARAM wParam,	// first message parameter
   LPARAM lParam 	// second message parameter
   )

   {
	HWND  h;
   char  sz[ 128 ];

	switch( uMsg )
      {
	   case WM_INITDIALOG:
         sprintf( sz,"%d", s_startframe );
         SetWindowText( GetDlgItem( hwndDlg, IDC_STARTFRAME ), sz );

         sprintf( sz, "%d", s_stopframe );
         SetWindowText( GetDlgItem( hwndDlg, IDC_STOPFRAME ), sz );

         sprintf( sz, "%.0f", ( float )s_framerate );
         SetWindowText( GetDlgItem( hwndDlg, IDC_FRAMERATE ), sz );

         sprintf( sz, "%.0f", ( float )s_samplerate );
         SetWindowText( GetDlgItem( hwndDlg, IDC_SAMPLERATE ), sz );

         h = GetDlgItem( hwndDlg, IDC_ANIMSCALE );
         SetFocus( h );

         return FALSE;
         break;

      case WM_COMMAND:
         switch( LOWORD( wParam ) )
            {
            case IDOK:
               GetWindowText( GetDlgItem( hwndDlg, IDC_STARTFRAME ), sz, 127 );
               s_startframe = atoi( sz );

               GetWindowText( GetDlgItem( hwndDlg, IDC_STOPFRAME ), sz, 127 );
               s_stopframe = atoi( sz );

               GetWindowText( GetDlgItem( hwndDlg, IDC_FRAMERATE ), sz, 127 );
               s_framerate = atof( sz );

               GetWindowText( GetDlgItem( hwndDlg, IDC_SAMPLERATE ), sz, 127 );
               s_samplerate = atof( sz );

               EndDialog( hwndDlg, 1 );
               break;

            case IDCANCEL:
               EndDialog( hwndDlg, 0 );
               cancel = true;
               break;
            }

         return FALSE;
         break;
      }

   return FALSE;
   }

void SkelExport::GetAnimScale
   (
   void
   )

   {
   s_startframe = startframe;
   s_stopframe  = stopframe;
   s_framerate  = framerate;
   s_samplerate = samplerate;

	DialogBox( hInstance, ( char * )IDD_ANIMSCALE, NULL, SkelExport::GetAnimScaleDlgProc );

   startframe   = s_startframe;
   stopframe    = s_stopframe;
   framerate    = s_framerate;
   samplerate   = s_samplerate;
   }

void SkelExport::ShowProgressBar
   (
   const char *title
   )

   {
   statusDialog = CreateDialog( hInstance, MAKEINTRESOURCE( IDD_STATUSDIALOG ), NULL, SkelExport::StatusDlgProc );
   progressBar = GetDlgItem( statusDialog, IDC_PROGRESS );
   statusText = GetDlgItem( statusDialog, IDC_EXPORTSTATUS );   
   SetWindowText( statusDialog, title );
   }

void SkelExport::UpdateProgressBar
   (
   float percentComplete
   )

   {
   SendMessage( progressBar, PBM_SETPOS, int( percentComplete * 100 ), 0 );
   }

void SkelExport::SetStatusText
   (
   const char *text
   )

   {
   SetWindowText( statusText, text );
   }

void SkelExport::CloseProgressBar
   (
   void
   )

   {
   if ( statusDialog )
      {
      DestroyWindow( statusDialog );
      }
   
   statusDialog = NULL;
   progressBar = NULL;
   statusText = NULL;
   }

#if (MAX_RELEASE >= 3000)
int SkelExport::DoExport( const TCHAR *filename, ExpInterface *ei, Interface *gi, BOOL suppressPrompts, DWORD options )
#elif (MAX_RELEASE >= 2000)
int SkelExport::DoExport( const TCHAR *filename, ExpInterface *ei, Interface *gi, BOOL suppressPrompts )
#else
const BOOL suppressPrompts = false;
int SkelExport::DoExport( const TCHAR *filename, ExpInterface *ei, Interface *gi )
#endif
   {
   int         i;
   int         numframes;
   Interval		animinfo;
   int         totaltics;
	TimeValue	t;
   TimeValue   tinc;
   int         maxframe;
   int         minframe;
   int         frame;
   TimeValue   starttime;
   loadframe_t *anim;
   char        text[ 128 ];

   try
      {
      GetNamesEnumProc     theGetNamesEnumProc;
      GetBoneNamesEnumProc theGetBoneNamesEnumProc;
      GetObjectsEnumProc   theGetObjectsEnumProc;
      GetBonesEnumProc     theGetBonesEnumProc;

      cancel = false;

	   interfaceptr = gi;

      //
      // Get the names of all the objects
      //
      theGetNamesEnumProc.GetNames( &objectnames, ei, interfaceptr );
      theGetBoneNamesEnumProc.GetNames( &bonenames, ei, interfaceptr );

      SortObjectNames( sorted );

	   // Find the number of frames
	   animinfo       = interfaceptr->GetAnimRange();
      startframe     = animinfo.Start() / GetTicksPerFrame();
      stopframe      = animinfo.End() / GetTicksPerFrame();
      minframe       = startframe;
      maxframe       = stopframe;
	   framerate      = GetFrameRate();
      samplerate     = framerate;

      if ( !suppressPrompts )
         {
         GetAnimScale();
         }

      if ( cancel )
         {
         // quit out if the cancel button was pressed
         return TRUE;
         }

      if ( framerate < 2.0f )
         {
         framerate = 2.0f;
         MessageBox( NULL, "Illegal frame rate, setting to 2.0", "DoExport", MB_OK );
         }

      if ( startframe < minframe || startframe > maxframe )
         {
	      MessageBox( NULL, "Illegal Start Frame, setting to 0", "DoExport", MB_OK );
         startframe = 0;
         }

      if ( stopframe < minframe || stopframe > maxframe )
         {
	      MessageBox( NULL, "Illegal Stop Frame, setting to maxframe","DoExport", MB_OK );
         stopframe = maxframe;
         }

      if ( stopframe < startframe )
         {
	      MessageBox( NULL, "Illegal Stop Frame and Start Frame, setting stopframe to startframe", "DoExport", MB_OK );
         stopframe = startframe;
         }

      sprintf( text, "Exporting '%s'", filename );
      ShowProgressBar( text );

      UpdateProgressBar( 0.0f );
      SetStatusText( "Allocating memory..." );

      // get the total time range
      starttime = startframe * GetTicksPerFrame();

      totaltics = ( stopframe - startframe + 1 ) * GetTicksPerFrame();
      numframes = ( int )( ( stopframe - startframe + 1 ) * ( samplerate / framerate ) );

      // get the time increment
      if ( numframes > 1 )
         {
         // doing it this way guarantees that we get the first and last frames
         tinc = ( totaltics + GetTicksPerFrame() - 1 ) / numframes;
         }
      else
         {
         tinc = 0;
         }

      // allocate the data structures
      anim = new loadframe_t[ numframes ];
      if ( !anim )
         {
	      Error( "Could not allocate memory for export" );
         }

      // clear the file holder
      memset( &model, 0, sizeof( loadsinglefile_t ) );

      // mark any tags as being used
      for( i = 1; i <= bonenames.NumObjects(); i++ )
         {
         if ( !model.usedbone[ i ] && !bonenames.ObjectAt( i ).icmpn( "Tag", 3 ) )
            {
            model.usedbone[ i ] = true;
            model.numbonesused++;
            }
         }

      // grab the verts from MAX
      interfaceptr->SetTime( starttime, TRUE );
      for( i = 1; i <= objectnames.NumObjects(); i++ )
         {
         sprintf( text, "Converting object '%s' (%d/%d)...", objectnames.ObjectAt( i ).c_str(), 
            i - 1, objectnames.NumObjects() );
         SetStatusText( text );
         UpdateProgressBar( 0.0f );

         theGetObjectsEnumProc.GetObject( objectnames.ObjectAt( sorted.ObjectAt( i ) ).c_str(), this, ei, interfaceptr );

         Sys_Update();
         if ( cancel )
            {
            delete[] anim;
            CloseProgressBar();

            // quit out if the cancel button was pressed
            return TRUE;
            }
         }

      // get all the material IDs
      CollectMaterials();

	   // Export each frame
	   for( t = starttime, frame = 0; frame < numframes; t += tinc, frame++ )
		   {
         sprintf( text, "Converting frame %d of %d...", frame, numframes );
         SetStatusText( text );

         UpdateProgressBar( ( float )frame / ( float )numframes );

         interfaceptr->SetTime( t, TRUE );

         // clear the file holder
         memset( &single, 0, sizeof( loadframe_t ) );

         // grab the file from MAX
         theGetBonesEnumProc.GetBones( this, ei, interfaceptr );

         anim[ frame ] = single;

         Sys_Update();
         if ( cancel )
            {
            delete[] anim;
            CloseProgressBar();

            // quit out if the cancel button was pressed
            return TRUE;
            }
		   }

      UpdateProgressBar( 1.0f );
      SetStatusText( "Writing file..." );

      // put it into a Anim file
      SaveAnimFileText( filename, anim, numframes, ( float )samplerate );

      delete[] anim;

      CloseProgressBar();
      }
   catch( const char *error )
      {
      if ( error )
         {
         MessageBox( NULL, error, "Error", 0 );
         }

      CloseProgressBar();

      return FALSE;
      }

   return TRUE;
	}

//
// SkelExport module functions follow:
//

SkelExport::SkelExport()
   {
   interfaceptr = NULL;
	}

SkelExport::~SkelExport()
   {
	}

int SkelExport::ExtCount()
   {
	return 1;
	}

//*************
//
//  Extensions supported for import/export modules
//
//*************

const TCHAR *SkelExport::Ext
   (
   int n
   )

   {
	switch( n )
      {
		case 0:
         return _T( EXTENSION );
		}

	return _T( "" );
	}

//*************
//
// Long ASCII description (i.e. "Targa 2.0 Image File")
//
//*************

const TCHAR *SkelExport::LongDesc
   (
   void
   )

   {
   return _T( LONG_DESCRIPTION );
	}

//*************
//
// Short ASCII description (i.e. "Targa")
//
//*************

const TCHAR *SkelExport::ShortDesc
   (
   void
   )
   
   {
   return _T( SHORT_DESCRIPTION );
	}

//*************
//
// ASCII Author name
//
//*************

const TCHAR *SkelExport::AuthorName
   (
   void
   )
   
   {
	return _T( AUTHOR );
	}

//*************
//
// ASCII Copyright message
//
//*************

const TCHAR *SkelExport::CopyrightMessage
   (
   void
   )
   
   {
	return _T( COPYRIGHT );
	}

//*************
//
// Other message #1
//
//*************

const TCHAR *SkelExport::OtherMessage1
   (
   void
   )

   {
	return _T( OTHER_MESSAGE1 );
	}

//*************
//
// Other message #2
//
//*************

const TCHAR *SkelExport::OtherMessage2
   (
   void
   )
   
   {
	return _T( OTHER_MESSAGE2 );
	}

//*************
//
// Version number
//
//*************

unsigned int SkelExport::Version
   (
   void
   )
   
   {
	return VERSION;
	}

//*************
//
// Optional
//
//*************

void SkelExport::ShowAbout
   (
   HWND hWnd
   )
   
   {
 	}

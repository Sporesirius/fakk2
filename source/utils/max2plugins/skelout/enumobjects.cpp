//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max3plugins/skelout/enumobjects.cpp          $
// $Revision:: 4                                                              $
//     $Date:: 1/15/00 3:47p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max3plugins/skelout/enumobjects.cpp               $
// 
// 4     1/15/00 3:47p Jimdose
// I now ignore hidden nodes
// 
// 3     9/07/99 3:12p Jimdose
// rewrote for ascii output
// 
// 2     7/30/99 4:23p Jimdose
// working on skel output
//
// DESCRIPTION:
// 

#include "enumobjects.h"

void GetObjectsEnumProc::GetObject
   (
   str name,
   SkelExport *skel,
   ExpInterface *ei,
   Interface *gi
   )

   {
   interfaceptr = gi;
   m_skel = skel;
   m_name = name.c_str();

   ei->theScene->EnumTree( this );
   }

int GetObjectsEnumProc::callback
   (
   INode *node
   )

   {
   Object *obj;

   if ( node->IsNodeHidden() )
      {
      return TREE_CONTINUE;
      }

   str nodename( node->GetName() );

   obj = node->EvalWorldState( interfaceptr->GetTime() ).obj;
   if (
      obj->IsDeformable() && 
      obj->CanConvertToType( triObjectClassID ) &&
	   nodename.icmpn( "Bip", 3 ) && 
      nodename.icmpn( "Bone", 4 ) && 
      nodename.icmpn( "Dummy", 5 )
      )

      {
      if ( !nodename.icmp( m_name ) )
         {
         m_skel->AddObject( obj, node );
         }
		}

   return TREE_CONTINUE;
	}

void GetNamesEnumProc::GetNames
   (
   Container<str> *names,
   ExpInterface *ei,
   Interface *gi
   )

   {
   objectnames = names;
   interfaceptr = gi;

   ei->theScene->EnumTree( this );
   }

int GetNamesEnumProc::callback
   (
   INode *node
   )

   {
   str      name;
   Object   *obj;
   int      i;
   char     text[ 128 ];

   if ( node->IsNodeHidden() )
      {
      return TREE_CONTINUE;
      }
   
   str nodename( node->GetName() );
   
   obj = node->EvalWorldState( interfaceptr->GetTime() ).obj;

   if (
      obj->IsDeformable() && 
      obj->CanConvertToType( triObjectClassID ) &&
	   nodename.icmpn( "Bip", 3 ) && 
      nodename.icmpn( "Bone", 4 ) && 
      nodename.icmpn( "Dummy", 5 )
      )

      {
      for( i = 1; i <= objectnames->NumObjects(); i++ )
         {
         if ( !strcmpi( objectnames->ObjectAt( i ), nodename ) )
            {
            sprintf( text, "Duplicate object %s.", nodename.c_str() );
	         MessageBox( NULL, text, "GetNamesEnumProc", MB_OK );

            return TREE_CONTINUE;
            }
         }

      objectnames->AddObject( nodename );
		}

   return TREE_CONTINUE;
	}

void GetBoneNamesEnumProc::GetNames
   (
   Container<str> *names,
   ExpInterface *ei,
   Interface *gi
   )

   {
   bonenames = names;
   interfaceptr = gi;

   ei->theScene->EnumTree( this );
   }

int GetBoneNamesEnumProc::callback
   (
   INode *node
   )

   {
   str      name;
   Object   *obj;
   int      i;
   char     text[ 128 ];

   if ( node->IsNodeHidden() )
      {
      return TREE_CONTINUE;
      }

   str nodename( node->GetName() );
   
   obj = node->EvalWorldState( interfaceptr->GetTime() ).obj;

   for( i = 1; i <= bonenames->NumObjects(); i++ )
      {
      if ( !strcmpi( bonenames->ObjectAt( i ), nodename ) )
         {
         sprintf( text, "Duplicate bone %s.", nodename.c_str() );
	      MessageBox( NULL, text, "GetBoneNamesEnumProc", MB_OK );

         // add it to the list anyways so that our number of bones is correct
         break;
         }
      }

   bonenames->AddObject( nodename );

   return TREE_CONTINUE;
	}

void GetBonesEnumProc::GetBones
   (
   SkelExport *skel,
   ExpInterface *ei,
   Interface *gi
   )

   {
   interfaceptr = gi;
   m_skel = skel;

   ei->theScene->EnumTree( this );
   }

int GetBonesEnumProc::callback
   (
   INode *node
   )

   {
   Object *obj;

   if ( node->IsNodeHidden() )
      {
      return TREE_CONTINUE;
      }

   obj = node->EvalWorldState( interfaceptr->GetTime() ).obj;
   m_skel->AddBoneFrame( obj, node );

   return TREE_CONTINUE;
	}

//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/clusterbomb.cpp                    $
// $Revision:: 5                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 6/29/00 2:03p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/clusterbomb.cpp                         $
// 
// 5     6/29/00 2:03p Steven
// Improved cluster bombs a little.
// 
// 4     6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 3     6/08/00 6:26p Aldie
// Put in the explode anim
// 
// 2     6/07/00 4:16p Aldie
// Added clusterbombs, heatseeking, and drunk
//
// DESCRIPTION:
// Clusterbomb

#include "clusterbomb.h"

Event EV_ClusterBomb_Think
   (
   "_think",
   EV_DEFAULT,
   NULL,
   NULL,
   "Clusterbomb think function"
   );
Event EV_ClusterBomb_ClusterModel
   (
   "clustermodel",
   EV_DEFAULT,
   "s",
   "modelname",
   "The model of the bombs that are spawned when the main bomb explodes"
   );
Event EV_ClusterBomb_ClusterCount
   (
   "clustercount",
   EV_DEFAULT,
   "i",
   "count",
   "The number of clusters to spawn"
   );

CLASS_DECLARATION( Projectile, ClusterBomb, NULL )
	{
      { &EV_ClusterBomb_Think,            Think },
      { &EV_ClusterBomb_ClusterCount,     ClusterCount },
      { &EV_ClusterBomb_ClusterModel,     ClusterModel },
		{ NULL, NULL }
	};

ClusterBomb::ClusterBomb
   (
   )

   {
   if ( LoadingSavegame )
      {
      return;
      }

   m_clustercount = 5;
   // Make the clusterbomb think each frame
   PostEvent( EV_ClusterBomb_Think, level.frametime );
   }

void ClusterBomb::Think
   (
   Event *ev
   )

   {
   CancelEventsOfType( EV_ClusterBomb_Think );
   PostEvent( EV_ClusterBomb_Think, level.frametime );

   // Explode if we start moving down
   if ( velocity.z < 0 )
      {
      Explode( NULL );
      }
   }

void ClusterBomb::ClusterModel
   (
   Event *ev
   )

   {
   m_clustermodel = ev->GetString( 1 );
   }

void ClusterBomb::ClusterCount
   (
   Event *ev
   )

   {
   m_clustercount = ev->GetInteger( 1 );
   }

void ClusterBomb::Explode
   (
   Event *ev
   )

   {
   int      i;
   Vector   dir;

   CancelEventsOfType( EV_ClusterBomb_Think );

   // Spawn clusters from the point of explosion
   for ( i=0; i<m_clustercount; i++ )
      {
		dir = velocity;
		dir.normalize();

		dir += Vector( G_CRandom( .25 ), G_CRandom( .25 ), G_CRandom( .25 ) );
		dir.normalize();

      ProjectileAttack( this->origin, dir, this, m_clustermodel, 1.0, velocity.length() );
      }

   velocity = Vector( 0,0,0 );
   setMoveType( MOVETYPE_NONE );
   RandomAnimate( "explode" );

   PostEvent( EV_Remove, 1 );
   }

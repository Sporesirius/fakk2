//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/health.h                           $
// $Revision:: 10                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/10/00 5:09p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/health.h                                $
// 
// 10    7/10/00 5:09p Markd
// Added waterInventoryItem
// 
// 9     6/24/00 7:02p Steven
// Added fall_straight_down parm to hit in healthplant.
// 
// 8     6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 7     5/26/00 7:44p Markd
// 2nd phase save games
// 
// 6     5/25/00 10:01a Steven
// Added velociity to the hit proc.
// 
// 5     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 4     5/23/00 10:19a Steven
// Added healthplant.
// 
// 3     3/13/00 5:18p Aldie
// Made some changes for usable inventory item stuff
// 
// 2     1/06/00 11:30p Jimdose
// removed unused health items
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// Health powerup
// 

#ifndef __HEALTH_H__
#define __HEALTH_H__

#include "g_local.h"
#include "item.h"
#include "sentient.h"
#include "item.h"

class Health : public Item
	{
	public:
      CLASS_PROTOTYPE( Health );

								Health();
		virtual void		PickupHealth( Event *ev );
	};

class HealthPlant : public Health
	{
	public:
		Vector				fall_velocity;

      CLASS_PROTOTYPE( HealthPlant );

								HealthPlant();
		void					Hit( Vector velocity, qboolean fall_straight_down );
		void					SetFallVelocity( Event *ev	);
		void					Touch( Event *ev );
	   virtual void      Archive( Archiver &arc );
	};

inline void HealthPlant::Archive
	(
	Archiver &arc
	)
   {
   Health::Archive( arc );

   arc.ArchiveVector( &fall_velocity );
   }

class HealthInventoryItem : public Item
	{
	public:
      CLASS_PROTOTYPE( HealthInventoryItem );

   void              Use( Event *ev );

	};

class WaterInventoryItem : public Item
	{
	public:
      CLASS_PROTOTYPE( WaterInventoryItem );

   void              Use( Event *ev );

	};

#endif /* health.h */

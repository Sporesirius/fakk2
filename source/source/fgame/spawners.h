//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/spawners.h                         $
// $Revision:: 10                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/22/00 10:35p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/spawners.h                              $
// 
// 10    7/22/00 10:35p Markd
// added spawnchance and spawnitem to func_spawns
// 
// 9     7/10/00 11:54p Markd
// added exit level code
// 
// 8     7/06/00 2:22p Steven
// Fixed spawners getting their angles set correctly.
// 
// 7     6/26/00 8:39p Markd
// Added func_randomspawn
// 
// 6     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 5     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 4     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 3     5/19/00 7:20p Aldie
// Added spawntarget
// 
// 2     3/18/00 2:43p Aldie
// Changed some func_spawn functionality
//
// DESCRIPTION:
// Various spawning entities

#ifndef __SPAWNWERS_H__
#define __SPAWNWERS_H__

#include "g_local.h"
#include "scriptslave.h"

class Spawn : public ScriptSlave
	{
   private:
  		str      modelname;
      str      spawntargetname;
      str      spawntarget;
      str      pickup_thread;
      str      spawnitem;
      float    spawnchance;
      int      attackmode;
   
		void           SetAngleEvent( Event *ev );
      void           SetPickupThread( Event *ev );
      void           ModelName( Event *ev );
      void           SpawnTargetName( Event *ev );
      void           SpawnTarget( Event *ev );
      void           AttackMode( Event *ev );
      void           SetSpawnItem( Event *ev );
      void           SetSpawnChance( Event *ev );

   protected:
      void           SetArgs( SpawnArgs &args );
		virtual void	DoSpawn( Event *ev );

	public:
      CLASS_PROTOTYPE( Spawn );


							Spawn();
	   virtual void   Archive( Archiver &arc );
	};

inline void Spawn::Archive
	(
	Archiver &arc
	)
   {
   ScriptSlave::Archive( arc );

   arc.ArchiveString( &modelname );
   arc.ArchiveString( &spawntargetname );
   arc.ArchiveString( &spawntarget );
   arc.ArchiveString( &pickup_thread );
   arc.ArchiveString( &spawnitem );
   arc.ArchiveFloat( &spawnchance );
   arc.ArchiveInteger( &attackmode );
   }

class RandomSpawn : public Spawn
	{
   private:
      float    min_time;
      float    max_time;

      void           MinTime( Event *ev );
      void           MaxTime( Event *ev );
      void           ToggleSpawn( Event *ev );
      void           Think( Event *ev );

	public:
      CLASS_PROTOTYPE( RandomSpawn );


							RandomSpawn();
	   virtual void   Archive( Archiver &arc );
	};

inline void RandomSpawn::Archive
	(
	Archiver &arc
	)
   {
   Spawn::Archive( arc );

   arc.ArchiveFloat( &min_time );
   arc.ArchiveFloat( &max_time );
   }

class ReSpawn : public Spawn
	{
   protected:
		virtual void	DoSpawn( Event *ev );
 	public:
      CLASS_PROTOTYPE( ReSpawn );
	};

class SpawnOutOfSight : public Spawn
	{
   protected:
		virtual void	DoSpawn( Event *ev );
 	public:
      CLASS_PROTOTYPE( SpawnOutOfSight );
	};

class SpawnChain : public Spawn
	{
   protected:
		virtual void	DoSpawn( Event *ev );
 	public:
      CLASS_PROTOTYPE( SpawnChain );
	};

#endif //__SPAWNWERS_H__

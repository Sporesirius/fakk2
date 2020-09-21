//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/explosion.h                        $
// $Revision:: 10                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 2:17p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/explosion.h                             $
// 
// 10    6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 9     5/26/00 7:44p Markd
// 2nd phase save games
// 
// 8     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 7     4/18/00 4:20p Markd
// added random scale ability to func_explodeobject and func_multiexploder
// 
// 6     4/18/00 4:01p Markd
// fixed up explosions
// 
// 5     2/02/00 7:14p Markd
// Added func_explodeobject and TossObject
// 
// 4     1/12/00 6:13p Jimdose
// added base_velocity and random_velocity
// rewrote CreateExplosion
// 
// 3     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 2     11/01/99 6:12p Steven
// Changed some old attenuation stuff to min dist stuff.
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 6     7/30/99 6:24p Aldie
// Updated weapons and utils to use new methods
// 
// 5     7/30/99 3:00p Steven
// New temporary stuff for gas explosions.
// 
// DESCRIPTION:
// Standard explosion object that is spawned by other entites and not map designers.
// Explosion is used by many of the weapons for the blast effect, but is also used
// by the Exploder and MultiExploder triggers.  These triggers create one or more
// explosions each time they are activated.
// 

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"

class Exploder : public Trigger
	{
	private:
		int	            damage;

		void              MakeExplosion( Event *ev );
      void              SetDmg( Event *ev );

	public:
      CLASS_PROTOTYPE( Exploder );
		
		                  Exploder();
	   virtual void      Archive( Archiver &arc );
	};

inline void Exploder::Archive
	(
	Archiver &arc
	)

   {
   Trigger::Archive( arc );

   arc.ArchiveInteger( &damage );
   }

class MultiExploder : public Trigger
	{
	protected:
		float	         explodewait;
		float	         explode_time;
		float          duration;
		int	         damage;
		float          randomness;

		void           MakeExplosion( Event *ev );
      void           SetDmg( Event *ev );
      void           SetDuration( Event *ev );
      void           SetWait( Event *ev );
      void           SetRandom( Event *ev );

	public:
      CLASS_PROTOTYPE( MultiExploder );

		               MultiExploder();
	   virtual void   Archive( Archiver &arc );
	};

inline void MultiExploder::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.ArchiveFloat( &explodewait );
   arc.ArchiveFloat( &explode_time );
   arc.ArchiveFloat( &duration );
   arc.ArchiveInteger( &damage );
   arc.ArchiveFloat( &randomness );
   }

void CreateExplosion 
   (
   Vector pos, 
   float  damage = 120,
   Entity *inflictor = NULL,
   Entity *attacker = NULL,
   Entity *ignore = NULL,
   const char *explosionModel = NULL,
   float  scale = 1.0f
   );

class ExplodeObject : public MultiExploder
	{
	private:
      Container<str> debrismodels;
      int            debrisamount;
      float          severity;

      void           SetDebrisModel( Event *ev );
      void           SetSeverity( Event *ev );
      void           SetDebrisAmount( Event *ev );
      void           MakeExplosion( Event *ev );

	public:
      CLASS_PROTOTYPE( ExplodeObject );

		               ExplodeObject();
	   virtual void   Archive( Archiver &arc );
	};

inline void ExplodeObject::Archive
	(
	Archiver &arc
	)
   {
   MultiExploder::Archive( arc );

   arc.ArchiveFloat( &severity );
   arc.ArchiveInteger( &debrisamount );
   debrismodels.Archive( arc );
   }

#endif /* explosion.h */

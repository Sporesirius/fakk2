//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/worldspawn.h                       $
// $Revision:: 9                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 7/25/00 11:32p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/worldspawn.h                            $
// 
// 9     7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 8     7/11/00 10:57p Markd
// fixed map naming problem
// 
// 7     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 6     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 5     3/31/00 11:45a Markd
// Added skyportal toggling support
// 
// 4     2/21/00 7:03p Markd
// Added skyalpha support
// 
// 3     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 2     9/28/99 7:13p Markd
// working on documenting worldspawn
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 6     8/15/99 4:42p Markd
// Put in far clipping plane support into worldspawn
//
// DESCRIPTION:
// Base class for worldspawn objects.  This should be subclassed whenever
// a DLL has new game behaviour that needs to be initialized before any other
// entities are created, or before any entity thinks each frame.  Also controls
// spawning of clients.
//

#ifndef __WORLDSPAWN_H__
#define __WORLDSPAWN_H__

#include "entity.h"

class TargetList : public Class
	{
   public:
      CLASS_PROTOTYPE( TargetList );
      Container<Entity *>  list;
      str                  targetname;

		TargetList();
      TargetList( str &tname );
		~TargetList();
      void     AddEntity( Entity * ent );
      void     RemoveEntity( Entity * ent );
      Entity   *GetNextEntity( Entity * ent );
	};

class World : public Entity
	{
   private:
      Container<TargetList *> targetList;
      qboolean                world_dying;
	public:
      CLASS_PROTOTYPE( World );

		               World();
		               ~World();

      str            skipthread;
      float          farplane_distance;
      Vector         farplane_color;
      qboolean       farplane_cull;

      float          sky_alpha;
      qboolean       sky_portal;

      void           FreeTargetList( void );
      TargetList     *GetTargetList( str &targetname );
      void           AddTargetEntity( str &targetname, Entity * ent );
      void           RemoveTargetEntity( str &targetname, Entity * ent );
      Entity         *GetNextEntity( str &targetname, Entity * ent );
      void           SetSoundtrack( Event *ev );
      void           SetGravity( Event *ev );
      void           SetSkipThread( Event *ev );
      void           SetNextMap( Event *ev );
      void           SetMessage( Event *ev );
      void           SetScript( Event *ev );
      void           SetWaterColor( Event *ev );
      void           SetWaterAlpha( Event *ev );
      void           SetLavaColor( Event *ev );
      void           SetLavaAlpha( Event *ev );
      void           SetFarPlane_Color( Event *ev );
      void           SetFarPlane_Cull( Event *ev );
      void           SetFarPlane( Event *ev );
      void           SetSkyAlpha( Event *ev );
      void           SetSkyPortal( Event *ev );
      void           UpdateConfigStrings( void );
      void           UpdateFog( void );
      void           UpdateSky( void );

      virtual void   Archive( Archiver &arc );
	};

inline void World::Archive
	(
	Archiver &arc
	)

	{
   if ( arc.Loading() )
      {
      FreeTargetList();
      }

   Entity::Archive( arc );

   arc.ArchiveString( &skipthread );
   arc.ArchiveFloat( &farplane_distance );
   arc.ArchiveVector( &farplane_color );
   arc.ArchiveBoolean( &farplane_cull );
   arc.ArchiveFloat( &sky_alpha );
   arc.ArchiveBoolean( &sky_portal );
   if ( arc.Loading() )
      {
      UpdateConfigStrings();
      UpdateFog();
      UpdateSky();
      }
	}

typedef SafePtr<World> WorldPtr;
extern WorldPtr world;

#endif /* worldspawn.h */

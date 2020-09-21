//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/doors.h                            $
// $Revision:: 7                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 7/27/00 5:39p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/doors.h                                 $
// 
// 7     7/27/00 5:39p Markd
// put in doorcompletelyclosed
// 
// 6     7/15/00 3:00p Steven
// fixed door locked sound playing constantly when it is an auto open door
// 
// 5     6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 4     5/25/00 7:52p Markd
// 2nd pass save game stuff
// 
// 3     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 2     10/14/99 5:08p Markd
// removed a lot of G_GetMoveDir calls from the initialization code
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// DESCRIPTION:
// Doors are environment objects that slide open when activated by triggers
// or when used by the player.
// 

#ifndef __DOORS_H__
#define __DOORS_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "scriptslave.h"

extern Event EV_Door_TryOpen;
extern Event EV_Door_GoDown;
extern Event EV_Door_GoUp;
extern Event EV_Door_HitBottom;
extern Event EV_Door_HitTop;
extern Event EV_Door_Fire;
extern Event EV_Door_Link;
extern Event EV_Door_SetSpeed;
extern Event EV_Door_Lock;
extern Event EV_Door_Unlock;

class Door;

typedef SafePtr<Door> DoorPtr;

class Door : public ScriptSlave
	{
	protected:
		str			sound_stop;
		str			sound_move;
		str			sound_message;
		str			sound_locked;
      float       lastblocktime;
		float			angle;
		Vector		dir;
      float       diropened;
		int			state;
      int         previous_state;
		int			trigger;
		int			nextdoor;
		DoorPtr		master;
		float			next_locked_time;

      void        SetDir( Event *ev );
		void			OpenEnd( Event *ev );
		void			CloseEnd( Event *ev );
		void			Close( Event *ev );
		void			Open( Event *ev );
		void			DoorUse( Event *ev );
		void			DoorFire( Event *ev );
		void			DoorBlocked( Event *ev );
		void			FieldTouched( Event *ev );
		void			TryOpen( Event *ev );
		void			SpawnTriggerField( Vector fmins, Vector fmaxs );
		qboolean		DoorTouches( Door *e1 );
		void			LinkDoors( Event *ev );	
		void			SetTime( Event *ev );
		void			LockDoor( Event *ev );
		void			UnlockDoor( Event *ev );
      void        SetStopSound( str sound );
      void        SetStopSound( Event *ev );
      void        SetMoveSound( str sound );
      void        SetMoveSound( Event *ev );
      void        SetMessageSound( str sound );
      void        SetMessageSound( Event *ev );
      void        SetLockedSound( str sound );
      void        SetLockedSound( Event *ev );
      void        SetWait( Event *ev );
      void        SetDmg( Event *ev );

	public:
      CLASS_PROTOTYPE( Door );

      qboolean		locked;

						Door();
		qboolean		isOpen( void );
		qboolean		isCompletelyClosed( void );
		qboolean		CanBeOpenedBy( Entity *ent );
	   virtual void Archive( Archiver &arc );
	};

inline void Door::Archive
	(
	Archiver &arc
	)
   {
   ScriptSlave::Archive( arc );

   arc.ArchiveString( &sound_stop );
   arc.ArchiveString( &sound_move );
   arc.ArchiveString( &sound_message );
   arc.ArchiveString( &sound_locked );
   if ( arc.Loading() )
      {
      SetStopSound( sound_stop );
      SetMoveSound( sound_move );
      SetMessageSound( sound_message );
      SetLockedSound( sound_locked );
      }
   arc.ArchiveFloat( &lastblocktime );
   arc.ArchiveFloat( &angle );
   arc.ArchiveVector( &dir );
   arc.ArchiveFloat( &diropened );
   arc.ArchiveInteger( &state );
   arc.ArchiveInteger( &previous_state );
   arc.ArchiveInteger( &trigger );
   arc.ArchiveInteger( &nextdoor );
   arc.ArchiveSafePointer( &master );
   arc.ArchiveBoolean( &locked );
	arc.ArchiveFloat( &next_locked_time );
   }

class RotatingDoor : public Door
	{
	protected:
		float		angle;
      Vector   startangle;
      int      init_door_direction;

	public:
      CLASS_PROTOTYPE( RotatingDoor );

      void           DoOpen( Event *ev );
      void           DoClose( Event *ev );
      void           OpenAngle( Event *ev );
	   virtual void   Archive( Archiver &arc );

					RotatingDoor();
	};

inline void RotatingDoor::Archive
	(
	Archiver &arc
	)
   {
   Door::Archive( arc );

   arc.ArchiveFloat( &angle );
   arc.ArchiveVector( &startangle );
   arc.ArchiveInteger( &init_door_direction );
   }

class SlidingDoor : public Door
	{
	protected:
      float    totalmove;
      float    lip;
      Vector   pos1;
      Vector   pos2;
      float    basespeed;
      Vector   movedir;

	public:
      CLASS_PROTOTYPE( SlidingDoor );

      void     SetMoveDir( Event *ev );
      void     Setup( Event *ev );
      void     SetLip( Event *ev );
      void     SetSpeed( Event *ev );
      void     DoOpen( Event *ev );
      void     DoClose( Event *ev );
	   virtual void Archive( Archiver &arc );

					SlidingDoor();
	};

inline void SlidingDoor::Archive
	(
	Archiver &arc
	)
   {
   Door::Archive( arc );

   arc.ArchiveFloat( &totalmove );
   arc.ArchiveFloat( &lip );
   arc.ArchiveVector( &pos1 );
   arc.ArchiveVector( &pos2 );
   arc.ArchiveVector( &movedir );
   arc.ArchiveFloat( &basespeed );
   }

class ScriptDoor : public Door
	{
	protected:
		ThreadPtr doorthread;
      str      initthreadname;
      str      openthreadname;
      str      closethreadname;
      float    doorsize;
		Vector	startangle;
      Vector   startorigin;
      Vector   movedir;

	public:
      CLASS_PROTOTYPE( ScriptDoor );

      void           SetMoveDir( Event *ev );
      void           DoInit( Event *ev );
      void           DoOpen( Event *ev );
      void           DoClose( Event *ev );
      void           SetOpenThread( Event *ev );
      void           SetCloseThread( Event *ev );
      void           SetInitThread( Event *ev );
	   virtual void   Archive( Archiver &arc );
					      ScriptDoor();
	};

inline void ScriptDoor::Archive
	(
	Archiver &arc
	)
   {
   Door::Archive( arc );

   arc.ArchiveSafePointer( &doorthread );
   arc.ArchiveString( &initthreadname );
   arc.ArchiveString( &openthreadname );
   arc.ArchiveString( &closethreadname );
   arc.ArchiveFloat( &doorsize );
   arc.ArchiveVector( &startangle );
   arc.ArchiveVector( &startorigin );
   arc.ArchiveVector( &movedir );
   }

#endif /* doors.h */

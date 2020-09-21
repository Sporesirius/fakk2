//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/specialfx.h                        $
// $Revision:: 21                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/10/00 6:26p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/specialfx.h                             $
// 
// 21    7/10/00 6:26p Steven
// Fixed archiving of fulcrum and SinkObject.
// 
// 20    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 19    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 18    4/29/00 12:07p Markd
// added active ability to sink objects
// 
// 17    4/24/00 7:16p Markd
// added movesounds to fulcrums
// 
// 16    2/02/00 9:26a Markd
// Added resetsound, resetdelay and sinksound to sinkobject
// 
// 15    2/01/00 6:55p Markd
// Added offset support to func_runthrough
// 
// 14    1/31/00 6:07p Markd
// tweaked func_sinkobject
// 
// 13    1/29/00 4:06p Markd
// Added func_sinkobject
// 
// 12    1/29/00 2:13p Markd
// Added Func_Runthrough entity
// 
// 11    1/12/00 6:14p Jimdose
// removed Sprite class
// 
// 10    1/10/00 6:17p Jimdose
// more code cleanup
// 
// 9     11/15/99 12:43p Markd
// Added variables for limit, resetspeed, dampening etc.
// 
// 8     10/18/99 7:14p Markd
// Fixed fulcrum stuff
// 
// 7     10/18/99 1:59p Aldie
// Lots of fixes for beams and stuff
// 
// 6     10/14/99 7:01p Markd
// Added first run of func_fullcrum
// 
// 5     10/14/99 5:08p Markd
// removed a lot of G_GetMoveDir calls from the initialization code
// 
// 4     10/01/99 6:08p Aldie
// Added some new features to beam system
// 
// 3     9/29/99 4:12p Aldie
// Added beams and fixed some lightmap probs
// 
// 2     9/16/99 4:51p Jimdose
// removed unused variables
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 10    8/26/99 5:58p Markd
// Re-added fx_sprite support
// 
// 9     7/23/99 3:27p Aldie
// 
// DESCRIPTION:
// special effects
// 

#ifndef __SPECIAL_FX_H__
#define __SPECIAL_FX_H__

#include "g_local.h"
#include "scriptslave.h"

class Fulcrum : public ScriptSlave
	{
   private:
      float       resetspeed;
      float       dampening;
      float       limit;
      float       speed;
      qboolean    touched;
      Vector      startangles;
      str         movesound;

	public:
      CLASS_PROTOTYPE( Fulcrum );
                  Fulcrum();

      void        Setup( Event *ev );
      void        SetSpeed( Event *ev );
      void        SetResetSpeed( Event *ev );
      void        SetDampening( Event *ev );
      void        SetLimit( Event *ev );
      void        SetMoveSound( Event *ev );
      void        Reset( Event *ev );
      void        Touched( Event *ev );
      void        Adjust( Event *ev );
      virtual void Archive( Archiver &arc );
	};

inline void Fulcrum::Archive
	(
	Archiver &arc
	)
   {
   ScriptSlave::Archive( arc );

   arc.ArchiveFloat( &resetspeed );
   arc.ArchiveFloat( &dampening );
   arc.ArchiveFloat( &limit );
   arc.ArchiveFloat( &speed );
   arc.ArchiveBoolean( &touched );
   arc.ArchiveVector( &startangles );
   arc.ArchiveString( &movesound );
   }


class RunThrough : public Entity
	{
   private:
      Vector      offset;
      float       speed;
      float       chance;
      float       delay;
      float       lasttriggertime;
      float       lip;
      str         spawnmodel;

      void        SetSpeed( Event *ev );
      void        SetChance( Event *ev );
      void        SetDelay( Event *ev );
      void        SetLip( Event *ev );
      void        SetSpawnModel( Event *ev );
      void        SetOffset( Event *ev );
      void        Touched( Event *ev );
	public:
      CLASS_PROTOTYPE( RunThrough );
                  RunThrough();

      virtual void Archive( Archiver &arc );
	};

inline void RunThrough::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.ArchiveVector( &offset );
   arc.ArchiveFloat( &speed );
   arc.ArchiveFloat( &chance );
   arc.ArchiveFloat( &delay );
   arc.ArchiveFloat( &lasttriggertime );
   arc.ArchiveFloat( &lip );
   arc.ArchiveString( &spawnmodel );
   }

class SinkObject : public ScriptSlave
	{
   private:
      float       resetspeed;
      float       resetdelay;
      float       dampening;
      float       limit;
      float       speed;
      float       delay;
      float       time_touched;
      float       time_reset;
      str         sinksound;
      str         resetsound;
      qboolean    touched;
      qboolean    active;
      Vector      startpos;

	public:
      CLASS_PROTOTYPE( SinkObject );
                  SinkObject();

      void        Setup( Event *ev );
      void        SetSpeed( Event *ev );
      void        SetDelay( Event *ev );
      void        SetResetSpeed( Event *ev );
      void        SetResetDelay( Event *ev );
      void        SetDampening( Event *ev );
      void        SetLimit( Event *ev );
      void        Reset( Event *ev );
      void        Touched( Event *ev );
      void        Adjust( Event *ev );
      void        Fall( Event *ev );
      void        SetResetSound( Event *ev );
      void        SetSinkSound( Event *ev );
      void        MakeActive( Event *ev );
      void        MakeNonActive( Event *ev );
      virtual void Archive( Archiver &arc );
	};

inline void SinkObject::Archive
	(
	Archiver &arc
	)
   {
   ScriptSlave::Archive( arc );

   arc.ArchiveFloat( &resetspeed );
   arc.ArchiveFloat( &resetdelay );
   arc.ArchiveFloat( &dampening );
   arc.ArchiveFloat( &limit );
   arc.ArchiveFloat( &speed );
   arc.ArchiveFloat( &delay );
   arc.ArchiveFloat( &time_touched );
   arc.ArchiveFloat( &time_reset );
   arc.ArchiveString( &sinksound );
   arc.ArchiveString( &resetsound );
   arc.ArchiveBoolean( &touched );
   arc.ArchiveBoolean( &active );
   arc.ArchiveVector( &startpos );
   }

#endif /* specialfx.h */

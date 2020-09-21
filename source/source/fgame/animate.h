//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/animate.h                          $
// $Revision:: 19                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/05/00 3:11p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/animate.h                               $
// 
// 19    6/05/00 3:11p Markd
// fixed HasCommands calls in server
// 
// 18    5/30/00 7:06p Markd
// saved games 4th pass
// 
// 17    5/25/00 7:52p Markd
// 2nd pass save game stuff
// 
// 16    5/24/00 3:13p Markd
// first phase of save/load games
// 
// 15    3/16/00 10:50a Markd
// Fixed some bad syntax in headers that exhibited itself in non-visualc
// compilers
// 
// 14    3/15/00 4:09p Aldie
// Fixed a bug with using weapons, and added some ability to force a state in
// the player
// 
// 13    2/22/00 6:20p Markd
// modified the way that the animation system works so that the animdone event
// is actually played 1 frame before the end of the animation
// 
// 12    2/14/00 5:37p Jimdose
// added ClearLegsAnim
// 
// 11    1/25/00 7:02p Markd
// Fixed viewthing frame reporting
// 
// 10    1/14/00 4:23p Steven
// Added an AnimatePtr type;
// 
// 9     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 8     12/01/99 4:56p Markd
// fixed some reference versus pointer issues with RandomAnimate and NewAnim
// 
// 7     11/18/99 6:26p Steven
// Fixed some tag stuff because CurrentAnim and CurrentFrame had different
// paramters in Entity and Animate which made the virtual stuff not work
// properly.
// 
// 6     11/11/99 5:25p Jimdose
// added separate torso animation
// 
// 5     11/11/99 3:54p Jimdose
// readded separate torso animations
// 
// 4     10/19/99 7:52p Markd
// Removed three part model system
// 
// 3     10/01/99 4:51p Markd
// Made Warning level 4 work on all projects
// 
// 2     9/27/99 6:18p Markd
// Added event documentation
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 18    9/01/99 9:08p Markd
// added animate once support
// 
// 17    8/19/99 6:41p Steven
// Added a stop anim event.
// 
// 16    8/05/99 9:16a Steven
// Added a stop animating at end so that it wouldn't skip to beginning of
// animation again.
// 
// 15    7/15/99 4:15p Markd
// added time output to viewthing
// 
// 14    6/23/99 3:57p Markd
// Added viewthing support
// 
// DESCRIPTION:
// Animate class
// 

#ifndef __ANIMATE_H__
#define __ANIMATE_H__

#include "g_local.h"
#include "entity.h"

extern Event EV_SetFrame;
extern Event EV_StopAnimating;
extern Event EV_Torso_StopAnimating;

#define MINIMUM_DELTA_MOVEMENT 8
#define MINIMUM_DELTA_MOVEMENT_PER_FRAME ( MINIMUM_DELTA_MOVEMENT / 20.0f )

class Animate;

typedef SafePtr<Animate> AnimatePtr;

class Animate : public Entity
	{
   private:
		Event					*animDoneEvent;
		Event					*torso_animDoneEvent;

      float             legs_animtime;
      float             torso_animtime;

      float             legs_starttime;
      float             torso_starttime;

      float             legs_frametime;
      float             torso_frametime;

      int               legs_numframes;
      int               torso_numframes;

      str               currentAnim;

      void              FrameDeltaEvent( Event *ev );
      void              EndAnim( bodypart_t part );
      void              Legs_AnimDoneEvent( Event *ev );
      void              Legs_AnimEvent( Event *ev );
      void              Legs_SetFrameEvent( Event *ev );
      void              Legs_StopAnimating( Event *ev );
      void              Torso_AnimDoneEvent( Event *ev );
      void              Torso_AnimEvent( Event *ev );
      void              Torso_SetFrameEvent( Event *ev );
      void              Torso_StopAnimating( Event *ev );
      void              NewAnimEvent( Event *ev );
	public:

		// Animation variables
      Vector            frame_delta;   // current movement from this frame
      CLASS_PROTOTYPE( Animate );
							   Animate();

		void					RandomAnimate( const char *animname, Event *endevent = NULL, bodypart_t part = legs );
		void					RandomAnimate( const char *animname, Event &endevent, bodypart_t part = legs );
      void              NewAnim( int animnum, bodypart_t part = legs );
      void              NewAnim( int animnum, Event *endevent, bodypart_t part = legs );
      void              NewAnim( int animnum, Event &endevent, bodypart_t part = legs );
      void              SetFrame( int framenum, bodypart_t part = legs, int anim = -1 );
      qboolean          HasAnim( const char *animname );
      Event             *AnimDoneEvent( bodypart_t part = legs );
      void              SetAnimDoneEvent( Event &event, bodypart_t part = legs );
      void              SetAnimDoneEvent( Event *event, bodypart_t part = legs );
      int               NumFrames( bodypart_t part = legs );
      int               NumAnims( void );
      const char        *AnimName( bodypart_t part = legs );
      float             AnimTime( bodypart_t part = legs );

      void              ClearLegsAnim( void );
      void              ClearTorsoAnim( void );

      virtual void      StopAnimating( bodypart_t part = legs );
		virtual void      StopAnimatingAtEnd( bodypart_t part = legs );

      virtual int       CurrentAnim( bodypart_t part = legs );
      virtual int       CurrentFrame( bodypart_t part = legs );

      virtual void      Archive( Archiver &arc );
	};

inline void Animate::RandomAnimate
	(
   const char *animname,
	Event &endevent,
   bodypart_t part
   )
   {
	Event *ev;

	ev = new Event( endevent );
	RandomAnimate( animname, ev, part );
   }

inline int Animate::CurrentAnim
	(
   bodypart_t part
   )
   {
   switch( part )
      {
      case legs:
         return edict->s.anim & ANIM_MASK;
         break;
      case torso:
         return edict->s.torso_anim & ANIM_MASK;
         break;
      default:
         warning( "CurrentAnim", "Unknown body part %d", part );
         return -1;
         break;
      }
   }

inline int Animate::CurrentFrame
	(
   bodypart_t part
   )
   {
   int frame;

   switch( part )
      {
      case legs:
         if ( edict->s.frame & FRAME_EXPLICIT )
            {
            frame = edict->s.frame & FRAME_MASK;
            }
         else
            {
            if ( legs_numframes )
               {
               frame = ( int )( ( float )( ( level.time - legs_starttime ) * legs_numframes ) / legs_animtime + 0.5f );
               while ( frame >= legs_numframes )
                  frame -= legs_numframes;
               }
            else
               {
               frame = 0;
               }
            }
         break;
      case torso:
         if ( edict->s.torso_frame & FRAME_EXPLICIT )
            {
            frame = edict->s.torso_frame & FRAME_MASK;
            }
         else
            {
            if ( torso_numframes )
               {
               frame = ( int )( ( float )( ( level.time - torso_starttime ) * torso_numframes ) / torso_animtime + 0.5f );
               while ( frame >= torso_numframes )
                  frame -= torso_numframes;
               }
            else
               {
               frame = 0;
               }
            }
         break;
      default:
         warning( "CurrentFrame", "Unknown body part %d", part );
         frame = 0;
         break;
      }
   return frame;
   }

inline int Animate::NumFrames
	(
   bodypart_t part
   )
   {
   switch( part )
      {
      case legs:
         return legs_numframes;
         break;
      case torso:
         return torso_numframes;
         break;
      default:
         warning( "NumFrames", "Unknown body part %d", part );
         return 0;
         break;
      }
   }

inline float Animate::AnimTime
	(
   bodypart_t part
   )
   {
   switch( part )
      {
      case legs:
         return legs_animtime;
         break;
      case torso:
         return torso_animtime;
         break;
      default:
         warning( "AnimTime", "Unknown body part %d", part );
         return 0;
         break;
      }
   }

inline int Animate::NumAnims
	(
   void
   )

   {
   return gi.NumAnims( edict->s.modelindex );
   }

inline const char *Animate::AnimName
	(
   bodypart_t part
   )
   {
   switch( part )
      {
      case legs:
         return gi.Anim_NameForNum( edict->s.modelindex, CurrentAnim( part ) );
         break;
      case torso:
         return gi.Anim_NameForNum( edict->s.modelindex, CurrentAnim( part ) );
         break;
      default:
         warning( "AnimName", "Unknown body part %d", part );
         return NULL;
         break;
      }
   }

inline Event * Animate::AnimDoneEvent
	(
   bodypart_t part
   )
   {
   switch( part )
      {
      case legs:
         if ( animDoneEvent )
            return new Event( animDoneEvent );
         else
            return NULL;
         break;
      case torso:
         if ( torso_animDoneEvent )
            return new Event( torso_animDoneEvent );
         else
            return NULL;
         break;
      default:
         warning( "AnimDoneEvent", "Unknown body part %d", part );
         return NULL;
         break;
      }
   }

inline void Animate::Archive
	(
	Archiver &arc
	)

   {
   Entity::Archive( arc );

   arc.ArchiveVector( &frame_delta );
   arc.ArchiveEventPointer( &animDoneEvent );
   arc.ArchiveEventPointer( &torso_animDoneEvent );
   arc.ArchiveFloat( &legs_animtime );
   arc.ArchiveFloat( &torso_animtime );
   arc.ArchiveFloat( &legs_starttime );
   arc.ArchiveFloat( &torso_starttime );
   arc.ArchiveInteger( &legs_numframes );
   arc.ArchiveInteger( &torso_numframes );
   arc.ArchiveFloat( &legs_frametime );
   arc.ArchiveFloat( &torso_frametime );
   arc.ArchiveString( &currentAnim );
   }

#endif /* animate.h */

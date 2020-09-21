//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/earthquake.cpp                     $
// $Revision:: 9                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 7/18/00 3:29p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/earthquake.cpp                          $
// 
// 9     7/18/00 3:29p Markd
// added better caching for sounds in general
// 
// 8     6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 7     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 6     4/30/00 2:46p Markd
// fixed earthquake screwups
// 
// 5     3/21/00 5:05p Markd
// improved earthquakes a lot with a visual effect
// 
// 4     12/11/99 6:44p Markd
// second run-through of q3a merge, got the entire project to build without
// errors or warnings
// 
// 3     11/02/99 5:45p Steven
// Added level wide sound stuff.
// 
// 2     9/29/99 5:18p Steven
// Event formatting.
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 13    8/28/99 11:43a Steven
// Removed global from sound function calls.
// 
// 12    6/11/99 1:23p Phook
// 
// 11    6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 10    6/11/99 12:46p Phook
// EClass color changes
// 
// DESCRIPTION:
// Earthquake trigger causes a localized earthquake when triggered.
// The earthquake effect is visible to the user as the shaking of his screen.
// 
#include "earthquake.h"

#define EARTHQUAKE_NO_RAMPUP   ( 1 << 0 )
#define EARTHQUAKE_NO_RAMPDOWN ( 1 << 1 )
/*****************************************************************************/
/*QUAKED func_earthquake (0 0.25 0.5) (-8 -8 -8) (8 8 8) NO_RAMPUP NO_RAMPDOWN
 Causes an earthquake
"duration" is the duration of the earthquake.  Default is 0.8 seconds.
"magnitude" severity of the quake.  Default 1.0
******************************************************************************/

Event EV_Earthquake_Deactivate
	( 
	"earthquake_deactivate",
	EV_DEFAULT,
   NULL,
   NULL,
   "Stops the earthquake."
	);
Event EV_Earthquake_SetDuration
	( 
	"duration",
	EV_DEFAULT,
   "f",
   "duration",
   "Sets the duration of the earthquake."
	);

Event EV_Earthquake_SetMagnitude
	( 
	"magnitude",
	EV_DEFAULT,
   "f",
   "theMagnitude",
   "Sets the magnitude of the earthquake."
	);

Event EV_Earthquake_Think
	( 
	"_earthquake_think",
	EV_DEFAULT,
   NULL,
   NULL,
   "think function for the earthquake."
	);

CLASS_DECLARATION( Trigger, Earthquake, "func_earthquake" )
	{
      { &EV_Touch,                     NULL },
      { &EV_Trigger_Effect,				Activate },
      { &EV_Earthquake_Deactivate,     Deactivate },
      { &EV_Earthquake_SetDuration,    SetDuration },
      { &EV_Earthquake_SetMagnitude,   SetMagnitude },
      { &EV_Earthquake_Think,          ThinkEvent },
      { NULL, NULL }
   };

Earthquake::Earthquake
   (
   void
   )

	{
   // cache in the quake sound
   CacheResource( "snd_earthquake", this );

   if ( LoadingSavegame )
      {
      return;
      }

	duration = 0.8f;
   magnitude = 1.0f;
   quakeactive = false;

   // make sure it gets sent to the client
	edict->svflags &= ~SVF_NOCLIENT;
	}

void Earthquake::SetDuration
   (
   Event *ev
   )

   {
   duration = ev->GetFloat( 1 );
   }

void Earthquake::SetMagnitude
   (
   Event *ev
   )

   {
   magnitude = ev->GetFloat( 1 );
   }

void Earthquake::Activate
   (
   Event *ev
   )

	{
	float newtime;

   starttime = level.time;
	newtime = duration + level.time;
	if ( newtime > level.earthquake )
		{
		level.earthquake = newtime;
      level.earthquake_magnitude = magnitude;
		}
   quakeactive = true;
	LoopSound( "snd_earthquake", DEFAULT_VOL, LEVEL_WIDE_MIN_DIST );

	PostEvent( EV_Earthquake_Deactivate,duration);
	PostEvent( EV_Earthquake_Think, 0 );
   }

void Earthquake::ThinkEvent
   (
   Event *ev
   )

   {
   float timedelta;

   if ( !quakeactive )
      {
      return;
      }

   timedelta = level.time - starttime;

   // we are in the first half of the earthquake
   if ( timedelta < ( duration * 0.5f ) )
      {
      if ( !( spawnflags & EARTHQUAKE_NO_RAMPUP ) )
         {
         float rampuptime;

         rampuptime = starttime + ( duration * 0.33f );
         if ( level.time < rampuptime )
            {
            float scale;

            scale = ( timedelta ) / ( duration * 0.33f );
            level.earthquake_magnitude = magnitude * scale;
            edict->s.loopSoundVolume = scale;
            }
         else
            {
            level.earthquake_magnitude = magnitude;
            edict->s.loopSoundVolume = 1.0f;
            }
         }
      }
   // we are in the second half of the earthquake
   else
      {
      if ( !( spawnflags & EARTHQUAKE_NO_RAMPDOWN ) )
         {
         float rampdowntime;

         rampdowntime = starttime + ( duration * 0.66f );
         if ( level.time > rampdowntime )
            {
            float scale;

            scale = 1.0f - ( ( level.time - rampdowntime ) / ( duration * 0.33f ) );
            level.earthquake_magnitude = magnitude * scale;
            edict->s.loopSoundVolume = scale;
            }
         else
            {
            level.earthquake_magnitude = magnitude;
            edict->s.loopSoundVolume = 1.0f;
            }
         }
      }

   CancelEventsOfType( EV_Earthquake_Think );
	PostEvent( EV_Earthquake_Think, FRAMETIME );
   }


void Earthquake::Deactivate
   (
   Event *ev
   )

   {
   quakeactive = false;
   level.earthquake = 0;
   level.earthquake_magnitude = 0;
	StopLoopSound();
   // make sure to stop thinking
   CancelEventsOfType( EV_Earthquake_Think );
   }

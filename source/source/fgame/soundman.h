//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/soundman.h                         $
// $Revision:: 11                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/22/00 3:45p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/soundman.h                              $
// 
// 11    6/22/00 3:45p Markd
// fixed a bunch of saved game issues
// 
// 10    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 9     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 8     3/02/00 6:55p Markd
// Added reverb triggers
// 
// 7     1/19/00 10:26a Markd
// added snd globaltranslate command
// 
// 6     1/06/00 11:10p Jimdose
// cleaning up unused code
// 
// 5     12/20/99 4:28p Markd
// Fixed music trigger bugs and music bugs
// 
// 4     12/20/99 3:00p Markd
// fixed more music system bugs
// 
// 3     11/12/99 6:52p Markd
// fixed up sound manager saving and loading
// 
// 2     11/12/99 11:47a Markd
// Added sound manager support and retro-fitted TriggerSpeaker and TriggerMusic
// to work with everything
// 
// 1     11/11/99 10:59a Markd
// 
// DESCRIPTION:
// Sound Manager
// 

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"

class SoundManager : public Listener
   {
   protected:
      int               currentFacet;
      Entity            *current;
      Container<Entity *> soundList;

      void              AddSpeaker( Event *ev );
      void              AddRandomSpeaker( Event *ev );
      void              AddMusicTrigger( Event *ev );
      void              AddReverbTrigger( Event *ev );
      void              Replace( Event *ev );
      void              Delete( Event *ev );
      void              MovePlayer( Event *ev );
      void              Next( Event *ev );
      void              Previous( Event *ev );
      void              ShowingSounds( Event *ev );
      void              Show( Event *ev );
      void              Hide( Event *ev );
      void              Save( Event *ev );
      void              UpdateEvent( Event *ev );
      void              ResetEvent( Event *ev );
      void              GlobalTranslateEvent( Event *ev );
      void              SwitchFacetEvent( Event *ev );
      void              PreviewReverbEvent( Event *ev );
      void              ResetReverbEvent( Event *ev );

      void              Show( void );
      void              UpdateUI( void );
      void              Save( void );
      void              CurrentLostFocus( void );
      void              CurrentGainsFocus( void );
      void              UpdateSpeaker( TriggerSpeaker * speaker );
      void              UpdateRandomSpeaker( RandomSpeaker * speaker );
      void              UpdateTriggerMusic( TriggerMusic * music );
      void              UpdateTriggerReverb( TriggerReverb * reverb );

   public:
      CLASS_PROTOTYPE( SoundManager );

                        SoundManager();
      void              Reset( void );
      void              Load( void );
      void              AddEntity( Entity * ent );
	   virtual void      Archive( Archiver &arc );
   };

inline void SoundManager::Archive
	(
	Archiver &arc
	)

   {
   int               i;
   int               num;
   int               currentFacet;

   Listener::Archive( arc );

   arc.ArchiveInteger( &currentFacet );
   arc.ArchiveObjectPointer( ( Class ** )&current );

   if ( arc.Saving() )
      {
      num = soundList.NumObjects();
      arc.ArchiveInteger( &num );
      }
   else
      {
      soundList.ClearObjectList();
      arc.ArchiveInteger( &num );
      soundList.Resize( num );
      }
   for( i = 1; i <= num; i++ )
      {
      arc.ArchiveObjectPointer( ( Class ** )soundList.AddressOfObjectAt( i ) );
      }
   }

extern SoundManager SoundMan;

#endif /* camera.h */

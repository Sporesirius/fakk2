//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/earthquake.h                       $
// $Revision:: 6                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 3:50p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/earthquake.h                            $
// 
// 6     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 5     6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 4     5/25/00 7:52p Markd
// 2nd pass save game stuff
// 
// 3     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 2     3/21/00 5:05p Markd
// improved earthquakes a lot with a visual effect
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// DESCRIPTION:
// Earthquake trigger causes a localized earthquake when triggered.
// The earthquake effect is visible to the user as the shaking of his screen.
// 

#ifndef __EARTHQUAKE_H__
#define __EARTHQUAKE_H__

#include "g_local.h"
#include "trigger.h"

#define EARTHQUAKE_STRENGTH 50

class Earthquake : public Trigger
	{
	protected:
      float    starttime;
		qboolean quakeactive;
      float    magnitude;
      float    duration;

	public:
      CLASS_PROTOTYPE( Earthquake );

		                  Earthquake();
      void              Activate( Event *ev );
      void              Deactivate( Event *ev );
      void              SetDuration( Event *ev );
      void              SetMagnitude( Event *ev );
      void              ThinkEvent( Event *ev );
      qboolean          EarthquakeActive() { return quakeactive; };
	   virtual void      Archive( Archiver &arc );
	};

inline void Earthquake::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.ArchiveFloat( &starttime );
   arc.ArchiveBoolean( &quakeactive );
   arc.ArchiveFloat( &magnitude );
   arc.ArchiveFloat( &duration );
   }

#endif /* Earthquake.h */

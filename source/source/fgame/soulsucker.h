//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/soulsucker.h                       $
// $Revision:: 6                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 7/14/00 8:28p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/soulsucker.h                            $
// 
// 6     7/14/00 8:28p Aldie
// Added waterfactor to soulsucker
// 
// 5     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 4     5/30/00 7:33p Aldie
// Removed unused code
// 
// 3     5/26/00 6:31p Aldie
// Added alternate fire to soulsucker and bug fix to AmmoAvailable()
// 
// 2     5/22/00 5:13p Aldie
// First version of soulsucker
//
// DESCRIPTION:
// Soulsucker weapon

#ifndef __SOULSUCKER_H__
#define __SOULSUCKER_H__

#include "weapon.h"
#include "weaputils.h"

class Soulsucker : public Weapon
   {
   private:
      float             m_waterfactor;

      void              WaterFactor( Event *ev );
   public:
      CLASS_PROTOTYPE( Soulsucker );
      
                        Soulsucker();
      virtual void      Shoot( Event *ev );
      virtual void      Archive( Archiver &arc );
   };

#endif // __SOULSUCKER_H__

inline void Soulsucker::Archive
	(
	Archiver &arc
	)
   {
   Weapon::Archive( arc );

   arc.ArchiveFloat( &m_waterfactor );
   }
//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/flamethrower.h                     $
// $Revision:: 6                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 3:50p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/flamethrower.h                          $
// 
// 6     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 5     5/26/00 7:44p Markd
// 2nd phase save games
// 
// 4     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 3     5/05/00 5:18p Aldie
// comment
// 
// 2     5/05/00 5:17p Aldie
// Flamethrower
//
// DESCRIPTION:
// Flamethrower weapon

#ifndef __FLAMETHROWER_H__
#define __FLAMETHROWER_H__

#include "weapon.h"
#include "weaputils.h"

class Flamethrower : public Weapon
   {
   private:
      Animate           *m_gas;

   public:
      CLASS_PROTOTYPE( Flamethrower );
      
                        Flamethrower();
      virtual void      Shoot( Event *ev );
	   virtual void      Archive( Archiver &arc );
	};

inline void Flamethrower::Archive
	(
	Archiver &arc
	)
   {
   Weapon::Archive( arc );

   arc.ArchiveObjectPointer( ( Class ** )&m_gas );
   }

#endif // __FLAMETHROWER_H__

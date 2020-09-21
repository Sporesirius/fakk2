//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/fists.h                               $
// $Revision:: 1                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 9/10/99 10:53a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/fists.h                                    $
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// Mutant Hands
// 

#ifndef __FISTS_H__
#define __FISTS_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"

class Fists : public Weapon
	{
	public:
      float             strike_reach;
      float             strike_damage;
      int               meansofdeath;

		CLASS_PROTOTYPE( Fists );
		
								Fists::Fists();
		virtual void		Shoot( Event *ev );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline void Fists::Archive
	(
	Archiver &arc
	)
   {
   Weapon::Archive( arc );

   arc.WriteFloat( strike_reach );
   arc.WriteFloat( strike_damage );
   arc.WriteInteger( meansofdeath );
   }

inline void Fists::Unarchive
	(
	Archiver &arc
	)
   {
   Weapon::Unarchive( arc );

   arc.ReadFloat( &strike_reach );
   arc.ReadFloat( &strike_damage );
   arc.ReadInteger( &meansofdeath );
   }

#endif /* Fists.h */

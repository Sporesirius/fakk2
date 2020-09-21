//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/flashbang.h                        $
// $Revision:: 6                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 5/26/00 7:44p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/flashbang.h                             $
// 
// 6     5/26/00 7:44p Markd
// 2nd phase save games
// 
// 5     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 4     4/15/00 5:18p Aldie
// Added stun events and fixed yet another bug with Ammo and AutoPutaway
// 
// 3     4/07/00 6:00p Aldie
// Added flashing and fixed radius damage for explosions
// 
// 2     4/07/00 4:01p Aldie
// First version
//
// DESCRIPTION:
// Flashbang weapon

#ifndef __FLASHBANG_H__
#define __FLASHBANG_H__

#include "weapon.h"
#include "weaputils.h"

class Flashbang : public Weapon
   {
   public:
      CLASS_PROTOTYPE( Flashbang );
      
                     Flashbang();

      virtual void   SpecialFireProjectile( Vector pos, 
                                            Vector forward,
                                            Vector right,
                                            Vector up,
                                            Entity *owner,
                                            str    projectileModel,
                                            float  charge_fraction
                                          );

   };

class FlashbangProjectile : public Projectile
   {
   private:
      float    stunRadius;
      float    stunTime;

   public:
      CLASS_PROTOTYPE( FlashbangProjectile );
      
      FlashbangProjectile();
      virtual void   Explode( Event *ev );
      void           StunTime( Event *ev );
      void           StunRadius( Event *ev );
	   virtual void   Archive( Archiver &arc );
	};

inline void FlashbangProjectile::Archive
	(
	Archiver &arc
	)
   {
   Projectile::Archive( arc );

   arc.ArchiveFloat( &stunRadius );
   arc.ArchiveFloat( &stunTime );
   }

#endif // __FLASHBANG_H__

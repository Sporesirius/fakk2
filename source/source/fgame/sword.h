//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/sword.h                            $
// $Revision:: 9                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 7/12/00 3:21p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/sword.h                                 $
// 
// 9     7/12/00 3:21p Aldie
// Added alternate modes to sword
// 
// 8     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 7     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 6     3/30/00 2:48p Steven
// Added knockback stuff.
// 
// 5     3/30/00 2:09p Aldie
// Added hitspawn command
// 
// 4     2/04/00 3:11p Aldie
// Changed sword attack method for water usage
// 
// 3     2/03/00 2:56p Aldie
// Sword and water coding
// 
// 2     2/02/00 7:08p Aldie
// Added new sword code and water damage
//
// DESCRIPTION:
// FAKK Swords

#ifndef __SWORD_H__
#define __SWORD_H__

#include "weapon.h"

class Sword : public Weapon
   {
   private:
      int            waterRequired[MAX_FIREMODES];
      float          basicDamage[MAX_FIREMODES];
      float          waterDamage[MAX_FIREMODES];
		float          basicKnockback[MAX_FIREMODES];
      float          waterKnockback[MAX_FIREMODES];
      qboolean       poweractive[MAX_FIREMODES];
      str            hitspawn[MAX_FIREMODES];

      void           SetWaterRequiredEvent( Event *ev );
      void           SetWaterDamageEvent( Event *ev );
      void           SetBasicDamageEvent( Event *ev );
		void           SetWaterKnockbackEvent( Event *ev );
      void           SetBasicKnockbackEvent( Event *ev );
      void           SetHitSpawn( Event *ev );

   public:
      CLASS_PROTOTYPE( Sword );
      
                     Sword();

      void           SetWaterRequired( int amount, firemode_t mode=FIRE_PRIMARY );
      int            GetWaterRequired( firemode_t mode=FIRE_PRIMARY  );
      void           SetBasicDamage( float amount, firemode_t mode=FIRE_PRIMARY  );
      float          GetBasicDamage( firemode_t mode=FIRE_PRIMARY );
      void           SetWaterDamage( float amount, firemode_t mode=FIRE_PRIMARY  );
      float          GetWaterDamage( firemode_t mode=FIRE_PRIMARY );
		float          GetBasicKnockback( firemode_t mode=FIRE_PRIMARY );
		float          GetWaterKnockback( firemode_t mode=FIRE_PRIMARY  );
      void           SetPowerOn( firemode_t mode=FIRE_PRIMARY );
      void           SetPowerOff( firemode_t mode=FIRE_PRIMARY );
      qboolean       GetPowerActive( firemode_t mode=FIRE_PRIMARY );
      void           HitSpawn( Vector origin, firemode_t mode=FIRE_PRIMARY );
	   virtual void Archive( Archiver &arc );
   };

inline void Sword::Archive
	(
	Archiver &arc
	)
   {
   Weapon::Archive( arc );

   arc.ArchiveInteger( &waterRequired[0] );
   arc.ArchiveInteger( &waterRequired[1] );
   arc.ArchiveFloat( &basicDamage[0] );
   arc.ArchiveFloat( &basicDamage[1] );
   arc.ArchiveFloat( &waterDamage[0] );
   arc.ArchiveFloat( &waterDamage[1] );
   arc.ArchiveFloat( &basicKnockback[0] );
   arc.ArchiveFloat( &basicKnockback[1] );
   arc.ArchiveFloat( &waterKnockback[0] );
   arc.ArchiveFloat( &waterKnockback[1] );
   arc.ArchiveBoolean( &poweractive[0] );
   arc.ArchiveBoolean( &poweractive[1] );
   arc.ArchiveString( &hitspawn[0] );
   arc.ArchiveString( &hitspawn[1] );
   }

#endif // __SWORD_H__

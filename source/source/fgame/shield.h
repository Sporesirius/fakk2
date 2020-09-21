//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/shield.h                           $
// $Revision:: 6                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 7/06/00 1:26p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/shield.h                                $
// 
// 6     7/06/00 1:26p Steven
// Made shield impact effect get played at max 4 times a second.
// 
// 5     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 4     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 3     2/20/00 2:56p Aldie
// Added shield impact function
// 
// 2     2/16/00 4:01p Aldie
// Added shield functionality
//
// DESCRIPTION:
// 

#ifndef __SHIELD_H__
#define __SHIELD_H__

#include "weapon.h"

class Shield : public Weapon
   {
   private:
      float    damage_reduction_percentage;

		float		last_impact_time;

      void     DamageReduction( Event *ev );

   public:
      CLASS_PROTOTYPE( Shield );
      
                     Shield();
      
      float          GetDamageReduction( void );
      void           Impact( void );
	   virtual void   Archive(Archiver &arc);
   };

inline void Shield::Archive (Archiver &arc)
   {
   Weapon::Archive( arc );

   arc.ArchiveFloat( &damage_reduction_percentage );
	arc.ArchiveFloat( &last_impact_time );
   }

#endif // __SHIELD_H__

//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/bullet.h                           $
// $Revision:: 1                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 9/10/99 10:53a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/bullet.h                                $
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
//
// DESCRIPTION:
// Base class for all bullet (hitscan) weapons.  Includes definition for shotgun.
// 

#ifndef __BULLET_H__
#define __BULLET_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"

#define MAX_RICOCHETS 10

class BulletWeapon : public Weapon
	{
	protected:
							BulletWeapon();
		virtual void	TraceAttack( Vector start, Vector end, int damage, trace_t *trace, int numricochets, int kick, int dflags, int meansofdeath, qboolean server_effects );
		virtual void	FireBullets( int numbullets, Vector spread, int mindamage, int maxdamage, int dflags, int meansofdeath, qboolean server_effects );
      virtual void   FireTracer( void );

	public:
      CLASS_PROTOTYPE( BulletWeapon );
	};

#endif /* BULLET.h */

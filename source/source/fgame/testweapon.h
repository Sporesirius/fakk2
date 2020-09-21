//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/testweapon.h                       $
// $Revision:: 1                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 9/10/99 10:55a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/testweapon.h                            $
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
//
// DESCRIPTION:
// Weapon for testing view models
// 

#ifndef __TESTWEAPON_H__
#define __TESTWEAPON_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"

class TestWeapon : public Weapon
	{
	public:
		CLASS_PROTOTYPE( TestWeapon );
		
								TestWeapon();
      virtual void		Prethink( void );
      virtual void		Shoot( Event *ev );
      virtual void		Done( Event *ev );
	};

#endif /* testweapon.h */

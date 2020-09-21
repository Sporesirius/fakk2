//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/testweapon.cpp                     $
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
// $Log:: /fakk2_code/fakk2_new/fgame/testweapon.cpp                          $
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// Weapon for testing view models
// 

#include "g_local.h"
#include "testweapon.h"

cvar_t *gun_model;
cvar_t *gun_wmodel;

CLASS_DECLARATION( Weapon, TestWeapon, NULL )
	{
	   { &EV_Weapon_Shoot,			   Shoot },
		{ &EV_Weapon_DoneFiring,	   Done },
		{ NULL, NULL }
	};

TestWeapon::TestWeapon()
	{
	char *wmodel;
	char *model;

	gun_model = gi.cvar ("w_model", "magnum.def", 0 );
	gun_wmodel = gi.cvar ("ww_model", "magnum_w.def", 0 );

	model = gun_model->string;
	wmodel = gun_wmodel->string;

	SetModels( wmodel, model );
	SetAmmo( "Bullet357", 0, 0 );
	SetRank( 0, 0 );

	flags |= FL_PRETHINK;
	}

void TestWeapon::Prethink
	(
	void
	)

	{
	char *wmodel;
	char *model;

	if ( stricmp( gun_model->string, viewmodel.c_str() ) ||
		stricmp( gun_wmodel->string, worldmodel.c_str() ) )
		{
		model = gun_model->string;
		wmodel = gun_wmodel->string;

		SetModels( wmodel, model );
		}
	}

void TestWeapon::Shoot
	(
	Event *ev
	)

	{
	assert( owner );
	if ( !owner )
		{
		return;
		}

	// Long attack since the animation will control it
	NextAttack( 1 );
	}

void TestWeapon::Done
	(
	Event *ev
	)

	{
	NextAttack( 0 );
	Weapon::DoneFiring( ev );
	}

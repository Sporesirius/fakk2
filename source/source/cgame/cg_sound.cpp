//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_sound.cpp                       $
// $Revision:: 4                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 10/29/99 7:24p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_sound.cpp                            $
// 
// 4     10/29/99 7:24p Steven
// Moved sound stuff into snapshot.
// 
// 3     10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// Sound function

#include "cg_local.h"

void CG_ProcessSound( server_sound_t *sound )
	{
	if ( sound->stop_flag )
		{
		cgi.S_StopSound( sound->entity_number, sound->channel );
		}
	else
		{
		cgi.S_StartSound( sound->origin, sound->entity_number, sound->channel, cgs.sound_precache[sound->sound_index], 
				sound->volume, sound->min_dist );
		}
	}

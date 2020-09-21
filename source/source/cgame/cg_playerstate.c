//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_playerstate.c                   $
// $Revision:: 2                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 10/05/99 6:01p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_playerstate.c                        $
// 
// 2     10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// 
// this file acts on changes in a new playerState_t.
// With normal play, this will be done after local prediction, but when
// following another player or playing back a demo, it will be checked
// when the snapshot transitions like all the other entities

#include "cg_local.h"

/*
===============
CG_TransitionPlayerState

===============
*/
void CG_TransitionPlayerState( playerState_t *ps, playerState_t *ops )
   {

   }


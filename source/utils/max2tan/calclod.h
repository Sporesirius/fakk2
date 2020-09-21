//-----------------------------------------------------------------------------
//
//  $Logfile:: /FAKK2/code/game/actor.cpp                        $
// $Revision:: 3                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 2/22/99 5:50p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /FAKK2/code/game/actor.cpp                             $
//
// DESCRIPTION:
// Header file for calclod.cpp
//

#ifndef __CALCLOD_H__
#define __CALCLOD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tikidata.h"

void CalculateLOD
   (
   md3SurfaceData_t *surf
   );

#ifdef __cplusplus
   }
#endif

#endif

//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/crossbow.h                         $
// $Revision:: 4                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 3:50p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/crossbow.h                              $
// 
// 4     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 3     4/08/00 2:49p Aldie
// New crossbow bolt implementation
// 
// 2     4/08/00 11:53a Aldie
// First version
//
// DESCRIPTION:
// Crossbow projectile

#ifndef __CROSSBOW_H__
#define __CROSSBOW_H__

#include "weapon.h"
#include "weaputils.h"

class CrossbowProjectile : public Projectile
   {
   public:
      CLASS_PROTOTYPE( CrossbowProjectile );
      
                        CrossbowProjectile();
      void              Explode( Event *ev );
      void              DoDecal( void );

   };

#endif // __CROSSBOW_H__


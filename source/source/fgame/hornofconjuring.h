//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/hornofconjuring.h                  $
// $Revision:: 3                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 5/31/00 3:02p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/hornofconjuring.h                       $
// 
// 3     5/31/00 3:02p Aldie
// Added vymish
// 
// 2     5/30/00 7:33p Aldie
// First version
//
// DESCRIPTION:
// Horn of Conjruing Weapon

#ifndef __HORNOFCONJURING_H__
#define __HORNOFCONJURING_H__

#include "weapon.h"
#include "weaputils.h"
#include "actor.h"

typedef SafePtr<Actor> ActorPtr;

class HornOfConjuring : public Weapon
   {
   private:
      Container<ActorPtr>  m_creatureList;

   public:
      CLASS_PROTOTYPE( HornOfConjuring );
      
                        HornOfConjuring();
      virtual void      Shoot( Event *ev );
   };

#endif // __HORNOFCONJURING_H__

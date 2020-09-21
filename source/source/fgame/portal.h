//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/portal.h                           $
// $Revision:: 2                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 3:50p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/portal.h                                $
// 
// 2     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
//
// DESCRIPTION:
// 

#ifndef __PORTAL_H__
#define __PORTAL_H__

#include "g_local.h"

class PortalSurface : public Entity
   {
   public:
      CLASS_PROTOTYPE( PortalSurface );
      PortalSurface();

      void LocateCamera( Event *ev );
   };

class PortalCamera : public Entity
   {
   public:
      CLASS_PROTOTYPE( PortalCamera );
      PortalCamera();
      void Roll( Event *ev );
   };

#endif // __PORTAL_H__


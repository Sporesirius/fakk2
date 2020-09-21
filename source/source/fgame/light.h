//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/light.h                            $
// $Revision:: 2                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 10/05/99 7:58p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/light.h                                 $
// 
// 2     10/05/99 7:58p Markd
// Rewrote light documentation
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// Classes for creating and controlling lights.
// 

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "g_local.h"
#include "entity.h"

class Light : public Entity
	{
	public:
      CLASS_PROTOTYPE( Light );
		
								Light();
	};

#endif /* light.h */

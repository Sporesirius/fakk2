//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/edenwater.h                        $
// $Revision:: 2                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 1/18/00 3:11p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/edenwater.h                             $
// 
// 2     1/18/00 3:11p Aldie
// First version of edenwater
//
// DESCRIPTION:
// EdenWater header file


#ifndef __EDENWATER_H__
#define __EDENWATER_H__

#include "g_local.h"
#include "item.h"
#include "sentient.h"
#include "item.h"

class EdenWater : public Item
	{
	public:
      CLASS_PROTOTYPE( EdenWater );

								EdenWater();
		virtual void		PickupEdenWater( Event *ev );
	};

#endif /* edenwater.h */

//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/armor.h                            $
// $Revision:: 2                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 1/06/00 11:08p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/armor.h                                 $
// 
// 2     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// DESCRIPTION:
// Standard armor that prevents a percentage of damage per hit.
// 

#ifndef __ARMOR_H__
#define __ARMOR_H__

#include "item.h" 

class Armor : public Item
	{
	protected:
		virtual void      Setup( const char *model, int amount );
      virtual void      Add( int amount );

	public:
      CLASS_PROTOTYPE( Armor );

                        Armor();

      virtual qboolean  Pickupable( Entity *other );
   };

#endif /* armor.h */

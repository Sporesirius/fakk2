//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/object.h                           $
// $Revision:: 5                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 3:50p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/object.h                                $
// 
// 5     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 4     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 3     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 2     1/27/00 11:35a Markd
// Fixed solid/notsolid client side entities
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 5     8/26/99 5:57p Markd
// Re-added fx_sprite support
// 
// DESCRIPTION:
// Object class
// 

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "g_local.h"
#include "animate.h"
#include "specialfx.h"

class Object : public Animate
	{
	public:
      CLASS_PROTOTYPE( Object );

							   Object();
      void              Killed( Event *ev );
      void              SetAngle( Event *ev );
      void              Setup( Event *ev );
      void              SetAnim( Event *ev );
      void              MakeShootable( Event *ev );
	};

extern Event EV_ThrowObject_Pickup;
extern Event EV_ThrowObject_Throw;

class ThrowObject : public Object
	{
   private:
      int               owner;
      Vector            pickup_offset;
      str               throw_sound;
	public:
      CLASS_PROTOTYPE( ThrowObject );
							   ThrowObject();
      void              Touch(Event *ev);
      void              Throw( Event * ev );
      void              Pickup( Event * ev );
      void              PickupOffset( Event * ev );
      void              ThrowSound( Event * ev );
	   virtual void      Archive( Archiver &arc );
	};

inline void ThrowObject::Archive
	(
	Archiver &arc
	)
   {
   Object::Archive( arc );

   arc.ArchiveInteger( &owner );
   arc.ArchiveVector( &pickup_offset );
   arc.ArchiveString( &throw_sound );
   }

#endif /* object.h */

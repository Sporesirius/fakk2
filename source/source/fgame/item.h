//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/item.h                             $
// $Revision:: 20                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/16/00 10:46a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/item.h                                  $
// 
// 20    7/16/00 10:46a Steven
// Added has_been_looked_at stuff.
// 
// 19    7/10/00 8:09p Markd
// fixed cool item pickup problems
// 
// 18    7/04/00 6:45p Markd
// enhanced cool item features
// 
// 17    7/04/00 2:25p Markd
// added cool cinematic for new objects
// 
// 16    6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 15    6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 14    5/30/00 7:06p Markd
// saved games 4th pass
// 
// 13    5/27/00 5:06p Steven
// Added a GetOwner function.
// 
// 12    5/26/00 7:44p Markd
// 2nd phase save games
// 
// 11    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 10    5/23/00 10:19a Steven
// Made EV_Item_PickupDone visible externally.
// 
// 9     4/11/00 5:32p Markd
// reworked PickupItem code
// 
// 8     3/27/00 4:47p Markd
// added pickup_thread capability to all items
// 
// 7     3/13/00 5:18p Aldie
// Made some changes for usable inventory item stuff
// 
// 6     1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 5     1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 4     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 3     12/02/99 6:53p Aldie
// Changed naming conventions from "both" to "dualhanded"  Also put in the
// inventory renderer for the hud file
// 
// 2     9/29/99 7:43p Markd
// Made items behave better when dropping to floor
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 5     8/27/99 5:07p Steven
// General item work.
// 
// DESCRIPTION:
// Base class for respawnable, carryable objects.
// 

#ifndef __ITEM_H__
#define __ITEM_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "sentient.h"

extern Event EV_Item_Pickup;
extern Event EV_Item_DropToFloor;
extern Event EV_Item_Respawn;
extern Event EV_Item_SetAmount;
extern Event EV_Item_SetMaxAmount;
extern Event EV_Item_RespawnSound;
extern Event EV_Item_DialogNeeded;
extern Event EV_Item_PickupDone;

#define DROPPED_ITEM					0x00008000
#define DROPPED_PLAYER_ITEM		0x00010000

class Item : public Trigger
	{
	protected:
		SentientPtr			owner;
		qboolean				respawnable;
      qboolean          playrespawn;
      qboolean          coolitem;
      qboolean          coolitemforced;
      str               cool_dialog;
      str               cool_anim;
		float					respawntime;
      str               dialog_needed;
      int               item_index;
      str               item_name;
      int               maximum_amount;
		int	            amount;
      str               pickup_thread;
      
		qboolean          no_remove;

		void					ItemTouch( Event *ev );
   
	public:

		qboolean				has_been_looked_at;

      CLASS_PROTOTYPE( Item );

								Item();
								~Item();
		virtual void		PlaceItem( void );
		virtual void		SetOwner( Sentient *ent );
		virtual Sentient*	GetOwner( void );
		void					SetNoRemove( Event *ev );
		virtual void		DropToFloor( Event *ev );
		virtual Item      *ItemPickup( Entity *other, qboolean add_to_inventory = qtrue );
		virtual void		Respawn( Event *ev );
		virtual void		setRespawn( qboolean flag );
		void					setRespawn( Event *ev );
		virtual qboolean	Respawnable( void );
		virtual void		setRespawnTime( float time );
		void					setRespawnTime( Event *ev );
		virtual float		RespawnTime( void );
		void					RespawnDone( Event *ev );
		void					PickupDone( Event *ev );
      virtual int       GetItemIndex( void ) { return item_index; };
      virtual int       getAmount( void );
      virtual void      setAmount( int startamount	);

      virtual int       MaxAmount( void );
      virtual qboolean  Pickupable( Entity *other );
      
      virtual void      setName( const char *i );
      virtual str       getName( void );
      virtual int       getIndex( void );
      virtual void      SetAmountEvent( Event *ev );
      virtual void      SetMaxAmount( Event *ev );
      virtual void      SetItemName( Event *ev );
      virtual void      SetPickupThread( Event *ev );

      virtual void      SetMax( int maxamount );
		virtual void		Add( int num );
      virtual void      Remove( int num );
		virtual qboolean	Use( int amount );
		virtual qboolean	Removable( void );
      virtual void      Pickup( Event *ev );
      virtual qboolean	Drop( void );
      virtual void      RespawnSound( Event *ev );
      virtual void      DialogNeeded( Event *ev );
      virtual str       GetDialogNeeded( void );
		void					Landed( Event *ev );
		void					CoolItemEvent( Event *ev );
		void					ForceCoolItemEvent( Event *ev );
		qboolean				IsItemCool( str * dialog, str * anim, qboolean *force );
		void				   SetCoolItem( qboolean cool, str &dialog, str &anim );
	   virtual void      Archive( Archiver &arc );
	};

inline void Item::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.ArchiveSafePointer( &owner );
   arc.ArchiveBoolean( &respawnable );
   arc.ArchiveBoolean( &playrespawn );
   arc.ArchiveBoolean( &coolitem );
   arc.ArchiveBoolean( &coolitemforced );
   arc.ArchiveString( &cool_dialog );
   arc.ArchiveString( &cool_anim );
   arc.ArchiveFloat( &respawntime );
   arc.ArchiveString( &dialog_needed );
   arc.ArchiveString( &item_name );
   if ( arc.Loading() )
      {
      setName( item_name.c_str() );
      }
   arc.ArchiveInteger( &maximum_amount );
   arc.ArchiveInteger( &amount );
   arc.ArchiveString( &pickup_thread );
   arc.ArchiveBoolean( &no_remove );

	arc.ArchiveBoolean( &has_been_looked_at );
   }


#endif /* item.h */

//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/player_util.cpp                    $
// $Revision:: 20                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/29/00 11:23p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/player_util.cpp                         $
// 
// 20    7/29/00 11:23p Aldie
// Changed to clearfade in SkipCinematic
// 
// 19    7/29/00 4:00p Aldie
// Added autofadein for skipping cinematics
// 
// 18    7/17/00 9:51p Aldie
// Added skipcinematic command which is access by pressing the ESC key
// 
// 17    7/17/00 2:56p Steven
// Fixed a crash with the logfile stuff.
// 
// 16    7/17/00 12:36a Markd
// Made sure to close the log file when exiting a level or shutting down a
// server
// 
// 15    7/16/00 2:09p Aldie
// Changed some of the player logging
// 
// 14    7/14/00 8:21p Aldie
// Added logstats
// 
// 13    7/01/00 6:37p Markd
// added areanum to whatis
// 
// 12    6/17/00 3:48p Aldie
// 
// 11    2/08/00 6:24p Markd
// Added angles printout to whatis
// 
// 10    1/29/00 3:35p Markd
// Added contents to whatis command
// 
// 9     1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 8     1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 7     1/14/00 5:07p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 6     1/11/00 5:53p Steven
// Passed a char * into error function instead of a str.
// 
// 5     1/07/00 8:12p Jimdose
// cleaning up unused code
// 
// 4     1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 3     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 2     12/08/99 7:00p Aldie
// Busting up player a bit and wrote some head tracking code
//
// DESCRIPTION:
// This file is used to hold the utility functions that are issued by the 
// player at the console.  Most of these are developer commands

#include "player.h"
#include "object.h"

//====================
//Player::ActorInfo
//====================
void Player::ActorInfo
	(
	Event *ev
	)

	{
	int num;
	Entity *ent;

	if ( ev->NumArgs() != 1 )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Usage: actorinfo <entity number>\n\"" );
		return;
		}

	num = ev->GetInteger( 1 );
   if ( ( num < 0 ) || ( num >= globals.max_entities ) )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Value out of range.  Possible values range from 0 to %d.\n\"", globals.max_entities );
		return;
		}

	ent = G_GetEntity( num );
   if ( !ent || !ent->isSubclassOf( Actor ) )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Entity not an Actor.\n\"" );
		}
	else
		{
      ( ( Actor * )ent )->ShowInfo();
		}
	}

//====================
//Player::WhatIs
//====================
void Player::WhatIs
	(
	Event *ev
	)

	{
	int num;
	Entity *ent;

	if ( ev->NumArgs() != 1 )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Usage: whatis <entity number>\n\"" );
		return;
		}

	num = ev->GetInteger( 1 );
   if ( ( num < 0 ) || ( num >= globals.max_entities ) )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Value out of range.  Possible values range from 0 to %d.\n\"", globals.max_entities );
		return;
		}

	ent = G_GetEntity( num );
	if ( !ent )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Entity not in use.\n\"", globals.max_entities );
      }
	else
		{
      const char * animname;

      animname = NULL;
      if ( gi.IsModel( ent->edict->s.modelindex ) )
         {
         animname = gi.Anim_NameForNum( ent->edict->s.modelindex, ent->edict->s.anim & ANIM_MASK );
         }

      if ( !animname )
         {
         animname = "( N/A )";
         }

      gi.SendServerCommand( edict-g_entities, "print \""
			"Entity #   : %d\n"
			"Class ID   : %s\n"
			"Classname  : %s\n"
			"Targetname : %s\n"
         "Modelname  : %s\n"
         "Animname   : %s\n"
			"Origin     : ( %f, %f, %f )\n"
			"Angles     : ( %f, %f, %f )\n"
	      "Bounds     : Mins( %.2f, %.2f, %.2f ) Maxs( %.2f, %.2f, %.2f )\n"
         "Velocity   : ( %f, %f, %f )\n"
         "SVFLAGS    : %x\n"
         "Movetype   : %i\n"
         "Solidtype  : %i\n"
         "Contents   : %x\n"
         "Areanum    : %i\n"
         "Parent     : %i\n"
         "Health     : %.1f\n"
         "Max Health : %.1f\n"
         "Edict Owner: %i\n\"",
			num,
         ent->getClassID(),
         ent->getClassname(),
         ent->TargetName(),
         ent->model.c_str(),
         animname,
         ent->origin.x, ent->origin.y, ent->origin.z,
         ent->angles.x, ent->angles.y, ent->angles.z,
         ent->mins.x, ent->mins.y, ent->mins.z, ent->maxs.x, ent->maxs.y, ent->maxs.z,
         ent->velocity.x, ent->velocity.y, ent->velocity.z,
         ent->edict->svflags,
         ent->movetype,
         ent->edict->solid,
         ent->edict->contents,
         ent->edict->areanum,
         ent->edict->s.parent,
         ent->health,
         ent->max_health,
         ent->edict->ownerNum
         );
		}
	}

//====================
//Player::KillEnt
//====================
void Player::KillEnt
	(
   Event * ev
   )

   {
	int num;
	Entity *ent;

	if ( ev->NumArgs() != 1 )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Usage: killent <entity number>\n\"" );
		return;
		}

	num = ev->GetInteger( 1 );
   if ( ( num < 0 ) || ( num >= globals.max_entities ) )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Value out of range.  Possible values range from 0 to %d.\n\"", globals.max_entities );
      return;
		}

	ent = G_GetEntity( num );
   ent->Damage( world, world, ent->max_health + 25, origin, vec_zero, vec_zero, 0, 0, 0 );
   }

//====================
//Player::RemoveEnt
//====================
void Player::RemoveEnt
	(
   Event * ev
   )

   {
	int num;
	Entity *ent;

	if ( ev->NumArgs() != 1 )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Usage: removeent <entity number>\n\"" );
		return;
		}

	num = ev->GetInteger( 1 );
   if ( ( num < 0 ) || ( num >= globals.max_entities ) )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Value out of range.  Possible values range from 0 to %d.\n\"", globals.max_entities );
      return;
		}

	ent = G_GetEntity( num );
   ent->PostEvent( Event( EV_Remove ), 0 );
   }

//====================
//Player::KillClass
//====================
void Player::KillClass
	(
   Event * ev
   )

   {
   int except;
   str classname;
   gentity_t * from;
	Entity *ent;

	if ( ev->NumArgs() < 1 )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Usage: killclass <classname> [except entity number]\n\"" );
		return;
		}

   classname = ev->GetString( 1 );

   except = 0;
   if ( ev->NumArgs() == 2 )
      {
      except = ev->GetInteger( 1 );
      }

   for ( from = this->edict + 1; from < &g_entities[ globals.num_entities ]; from++ )
		{
		if ( !from->inuse )
			{
			continue;
			}

		assert( from->entity );

      ent = from->entity;

      if ( ent->entnum == except )
         {
         continue;
         }

   	if ( ent->inheritsFrom( classname.c_str() ) )
         {
         ent->Damage( world, world, ent->max_health + 25, origin, vec_zero, vec_zero, 0, 0, 0 );
         }
      }
   }

//====================
//Player::RemoveClass
//====================
void Player::RemoveClass
	(
   Event * ev
   )

   {
   int except;
   str classname;
   gentity_t * from;
	Entity *ent;

	if ( ev->NumArgs() < 1 )
		{
	   gi.SendServerCommand( edict-g_entities, "print \"Usage: removeclass <classname> [except entity number]\n\"" );
		return;
		}

   classname = ev->GetString( 1 );

   except = 0;
   if ( ev->NumArgs() == 2 )
      {
      except = ev->GetInteger( 1 );
      }

   for ( from = this->edict + 1; from < &g_entities[ globals.num_entities ]; from++ )
		{
		if ( !from->inuse )
			{
			continue;
			}

		assert( from->entity );

      ent = from->entity;

      if ( ent->entnum == except )
         continue;

   	if ( ent->inheritsFrom( classname.c_str() ) )
         {
         ent->PostEvent( Event( EV_Remove ), 0 );
         }
      }
   }

//====================
//Player::TestThread
//====================
void Player::TestThread
	(
	Event *ev
	)

	{
   const char *scriptfile;
   const char *label = NULL;
   ScriptThread * thread;

	if ( ev->NumArgs() < 1 )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Syntax: testthread scriptfile <label>.\n\"" );
		return;
		}

   scriptfile = ev->GetString( 1 );
   if ( ev->NumArgs() > 1 )
      {
      label = ev->GetString( 2 );
      }

   thread = Director.CreateThread( scriptfile, LEVEL_SCRIPT, label );
   if ( thread )
      {
      // start right away
      thread->StartImmediately();
      }
	}

//====================
//Player::SpawnEntity
//====================
void Player::SpawnEntity
	(
	Event *ev
	)

	{
	Entity		*ent;
   str         name;
	ClassDef		*cls;
   str         text;
   Vector		forward;
	Vector		up;
   Vector		delta;
	Vector		v;
	int			n;
	int			i;
   Event       *e;

   if ( ev->NumArgs() < 1 )
		{
		ev->Error( "Usage: spawn entityname [keyname] [value]..." );
		return;
		}

   name = ev->GetString( 1 );
   if ( !name.length() )
		{
		ev->Error( "Must specify an entity name" );
		return;
		}

   // create a new entity
   SpawnArgs args;

   args.setArg( "classname", name.c_str() );
   args.setArg( "model", name.c_str() );

   cls = args.getClassDef();
   if ( !cls )
      {
      cls = &Entity::ClassInfo;
      }

   if ( !checkInheritance( &Entity::ClassInfo, cls ) )
      {
      ev->Error( "%s is not a valid Entity", name );
      return;
      }

   ent = ( Entity * )cls->newInstance();

   e = new Event( EV_Model );
   e->AddString( name.c_str() );
   ent->PostEvent( e, EV_SPAWNARG );

   angles.AngleVectors( &forward, NULL, &up );
   v = origin + ( forward + up ) * 40;

   e = new Event( EV_SetOrigin );
   e->AddVector( v );
   ent->PostEvent( e, EV_SPAWNARG );

   delta = origin - v;
	v.x = 0;
   v.y = delta.toYaw();
   v.z = 0;

   e = new Event( EV_SetAngles );
   e->AddVector( v );
   ent->PostEvent( e, EV_SPAWNARG );

   if ( ev->NumArgs() > 2 )
		{
		n = ev->NumArgs();
		for( i = 2; i <= n; i += 2 )
			{
         e = new Event( ev->GetString( i ) );
         e->AddToken( ev->GetString( i + 1 ) );
         ent->PostEvent( e, EV_SPAWNARG );
			}
		}

   e = new Event( EV_Anim );
   e->AddString( "idle" );
   ent->PostEvent( e, EV_SPAWNARG );
   }

//====================
//Player::SpawnActor
//====================
void Player::SpawnActor
	(
	Event *ev
	)

	{
	Entity   *ent;
   str      name;
   str      text;
   Vector	forward;
	Vector	up;
   Vector	delta;
	Vector	v;
	int		n;
	int		i;
	ClassDef	*cls;
   Event    *e;

   if ( ev->NumArgs() < 1 )
		{
		ev->Error( "Usage: actor [modelname] [keyname] [value]..." );
		return;
		}

   name = ev->GetString( 1 );
   if ( !name[ 0 ] )
		{
		ev->Error( "Must specify a model name" );
		return;
		}

   if ( !strstr( name.c_str(), ".tik" ) )
      {
      name += ".tik";
      }

   // create a new entity
	SpawnArgs args;

   args.setArg( "model", name.c_str() );

   cls = args.getClassDef();

   if ( cls == &Object::ClassInfo )
      {
      cls = &Actor::ClassInfo;
      }

   if ( !cls || !checkInheritance( &Actor::ClassInfo, cls ) )
      {
      ev->Error( "%s is not a valid Actor", name.c_str() );
      return;
      }
   
   ent = ( Entity * )cls->newInstance();
   e = new Event( EV_Model );
   e->AddString( name.c_str() );
   ent->PostEvent( e, EV_SPAWNARG );

   angles.AngleVectors( &forward, NULL, &up );
   v = origin + ( forward + up ) * 40;

   e = new Event( EV_SetOrigin );
   e->AddVector( v );
   ent->PostEvent( e, EV_SPAWNARG );

   delta = origin - v;
	v = delta.toAngles();

   e = new Event( EV_SetAngle );
   e->AddFloat( v[ 1 ] );
   ent->PostEvent( e, EV_SPAWNARG );

   if ( ev->NumArgs() > 2 )
		{
		n = ev->NumArgs();
		for( i = 2; i <= n; i += 2 )
			{
         e = new Event( ev->GetString( i ) );
         e->AddToken( ev->GetString( i + 1 ) );
         ent->PostEvent( e, EV_SPAWNARG );
			}
		}
   }

void Player::ListInventoryEvent
   (
   Event *ev
   )

   {
   ListInventory();
   }

void Player::GetStateAnims
   (
   Container<const char *> *c
   )

   {
   statemap_Legs->GetAllAnims( c );
   statemap_Torso->GetAllAnims( c );
   }

static fileHandle_t logfile=NULL;

static void OpenPlayerLogFile
   (
   void
   )

   {
   str s,filename;
   
   s = "playlog_";
   s += level.mapname; 
   filename = gi.GetArchiveFileName( s, "log" );
   
   logfile = gi.FS_FOpenFileWrite( filename.c_str() );
   }

void Player::LogStats
   (
   Event *ev
   )

   {
   str s;

   if ( !logfile )
      {
      OpenPlayerLogFile();
      }

	if ( !logfile )
		{
      return;
		}
   
   int b =  AmmoCount( "Bullet" );
   int p =  AmmoCount( "Plasma" );
   int g =  AmmoCount( "Gas" );
   int r =  AmmoCount( "Rocket" );
   int f =  AmmoCount( "Flashbangs" );
   int m =  AmmoCount( "Meteor" );
   int gp = AmmoCount( "Gas Pod" );

   s = va(  "%.2f\t", level.time );
   s += va( "(%.2f %.2f %.2f)\t", origin.x, origin.y, origin.z );
   s += va( "%.2f\t", health );
   s += va( "%.2f\t", water_power );
   s += va( "%d\t%d\t%d\t%d\t%d\t%d\t%d\n", b,p,g,r,f,m,gp );
   
   gi.FS_Write( s, s.length(), logfile );
   gi.FS_Flush( logfile );

   Event *ev1 = new Event( ev );
   PostEvent( ev1, 1 );   
   }

void ClosePlayerLogFile
   (
   void
   )

   {
   if ( logfile )
      {
      gi.FS_FCloseFile( logfile );
		logfile = NULL;
      }
   }

void Player::SkipCinematic
   (
   Event *ev
   )

   {
   if ( level.cinematic && ( world->skipthread.length() > 1 ) ) 
      {
      str skipthread;
      G_ClearFade();

      skipthread = world->skipthread;
      // now that we have executed it, lets kill it so we don't call it again
      world->skipthread = "";
      ExecuteThread( skipthread );
      // reset the roll on our view just in case
      v_angle.z = 0;
      SetViewAngles( v_angle );
      }
   }

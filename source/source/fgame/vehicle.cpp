//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/vehicle.cpp                        $
// $Revision:: 18                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/23/00 8:41p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/vehicle.cpp                             $
// 
// 18    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 17    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 16    4/27/00 4:00p Aldie
// Fix for take command
// 
// 15    4/01/00 3:45p Markd
// added FL_TOUCH_TRIGGERS flag and implementation
// 
// 14    3/21/00 5:06p Markd
// added vehicle support
// 
// 13    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 12    10/19/99 7:53p Markd
// eliminated 3 part model system
// 
// 11    10/12/99 2:23p Markd
// Rewrote camera and player movetype system
// 
// 10    10/07/99 3:00p Steven
// Event formatting.
// 
// 9     10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 8     10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 7     9/30/99 1:49p Aldie
// Documentation of commands
// 
// 6     9/29/99 7:43p Markd
// Made items behave better when dropping to floor
// 
// 5     9/27/99 5:45p Markd
// began documentation and cleanup phase after merge
// 
// 4     9/22/99 4:48p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 3     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 17    8/30/99 2:37p Steven
// Added support for volume and minimum distance for loop sounds.
// 
// 16    8/28/99 11:45a Steven
// Removed global from sound function calls.
// 
// 15    8/18/99 3:29p Jimdose
// added cylindrical collision detection
//
// DESCRIPTION:
// Script controlled Vehicles.
//

#include "g_local.h"
#include "scriptslave.h"
#include "vehicle.h"
#include "player.h"
#include "specialfx.h"
#include "explosion.h"
#include "earthquake.h"
#include "gibs.h"

Event EV_Vehicle_Start
   (
   "start",
	EV_DEFAULT,
   NULL,
   NULL,
   "Initialize the vehicle."
   );
Event EV_Vehicle_Enter
   (
   "enter",
	EV_DEFAULT,
   "eS",
   "vehicle driver_anim",
   "Called when someone gets into a vehicle."
   );
Event EV_Vehicle_Exit
   (
   "exit",
	EV_DEFAULT,
   "e",
   "vehicle",
   "Called when driver gets out of the vehicle."
   );
Event EV_Vehicle_Drivable
   (
   "drivable",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the vehicle drivable"
   );
Event EV_Vehicle_UnDrivable
   (
   "undrivable",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the vehicle undrivable"
   );
Event EV_Vehicle_Jumpable
   (
   "canjump",
   EV_DEFAULT,
   "b",
   "jumpable",
   "Sets whether or not the vehicle can jump"
   );
Event EV_Vehicle_Lock
   (
   "lock",
   EV_DEFAULT,
   NULL,
   NULL,
   "Sets the vehicle to be locked"
   );
Event EV_Vehicle_UnLock
   (
   "unlock",
   EV_DEFAULT,
   NULL,
   NULL,
   "Sets the vehicle to be unlocked"
   );
Event EV_Vehicle_SeatAnglesOffset
   (
   "seatanglesoffset",
   EV_DEFAULT,
   "v",
   "angles",
   "Set the angles offset of the seat"
   );
Event EV_Vehicle_SeatOffset
   (
   "seatoffset",
   EV_DEFAULT,
   "v",
   "offset",
   "Set the offset of the seat"
   );
Event EV_Vehicle_DriverAnimation
   (
   "driveranim",
   EV_DEFAULT,
   "s",
   "animation",
   "Set the animation of the driver to use when the driver is in the vehicle"
   );
Event EV_Vehicle_SetWeapon
   (
   "setweapon",
   EV_DEFAULT,
   "s",
   "weaponname",
   "Set the weapon for the vehicle"
   );
Event EV_Vehicle_SetSpeed
   (
   "vehiclespeed",
   EV_DEFAULT,
   "f",
   "speed",
   "Set the speed of the vehicle"
   );
Event EV_Vehicle_SetTurnRate
   (
   "turnrate",
   EV_DEFAULT,
   "f",
   "rate",
   "Set the turning rate of the vehicle"
   );
Event EV_Vehicle_SteerInPlace
   (
   "steerinplace",
   EV_DEFAULT,
   NULL,
   NULL,
   "Set the vehicle to turn in place"
   );
Event EV_Vehicle_ShowWeapon
   (
   "showweapon",
   EV_DEFAULT,
   NULL,
   NULL,
   "Set the weapon to be show in the view"
   );
CLASS_DECLARATION( ScriptModel, VehicleBase, NULL )
	{
		{ NULL, NULL }
	};

VehicleBase::VehicleBase()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

   takedamage = DAMAGE_NO;
	showModel();
   setSolidType( SOLID_NOT );
	setMoveType( MOVETYPE_NONE );
   setOrigin( localorigin + Vector( "0 0 30") );

   //
   // we want the bounds of this model auto-rotated
   //
   flags |= FL_ROTATEDBOUNDS;

   //
   // rotate the mins and maxs for the model
   //
   setSize( mins, maxs );

	vlink = NULL;
	offset = "0 0 0";

   PostEvent( EV_BecomeNonSolid, EV_POSTSPAWN );
	}

CLASS_DECLARATION( VehicleBase, BackWheels, "script_wheelsback" )
	{
		{ NULL, NULL }
	};

CLASS_DECLARATION( VehicleBase, FrontWheels, "script_wheelsfront" )
	{
		{ NULL, NULL }
	};

CLASS_DECLARATION( VehicleBase, Vehicle, "script_vehicle" )
	{
	   { &EV_Blocked,					         VehicleBlocked },
	   { &EV_Touch,					         VehicleTouched },
	   { &EV_Use,						         DriverUse },
	   { &EV_Vehicle_Start,			         VehicleStart },
	   { &EV_Vehicle_Drivable,		         Drivable },
	   { &EV_Vehicle_UnDrivable,	         UnDrivable },
	   { &EV_Vehicle_Jumpable,	            Jumpable },
	   { &EV_Vehicle_SeatAnglesOffset,     SeatAnglesOffset },
	   { &EV_Vehicle_SeatOffset,           SeatOffset },
	   { &EV_Vehicle_Lock,		            Lock },
	   { &EV_Vehicle_UnLock,	            UnLock },
      { &EV_Vehicle_SetWeapon,            SetWeapon },
      { &EV_Vehicle_DriverAnimation,      DriverAnimation },
      { &EV_Vehicle_SetSpeed,             SetSpeed },
      { &EV_Vehicle_SetTurnRate,          SetTurnRate },
      { &EV_Vehicle_SteerInPlace,         SteerInPlace },
      { &EV_Vehicle_ShowWeapon,           ShowWeaponEvent },
		{ NULL, NULL }
	};

Vehicle::Vehicle()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   takedamage = DAMAGE_YES;
   seatangles = vec_zero;
   driveroffset = vec_zero;
   seatoffset = vec_zero;
	driver = 0;
	lastdriver = 0;
	currentspeed = 0;
	turnangle = 0;
	turnimpulse = 0;
	moveimpulse = 0;
	jumpimpulse = 0;
   conesize = 75;
   hasweapon = false;
   locked = false;
   steerinplace = false;
   drivable = false;
   jumpable = false;
   showweapon = false;
   flags |= FL_DIE_EXPLODE;
   // touch triggers by default
   flags |= FL_TOUCH_TRIGGERS;
   gravity = 1;
   mass = size.length() * 10;

	health      = 1000;
	speed       = 1200;
	maxturnrate = 40.0f;

	PostEvent( EV_Vehicle_Start, FRAMETIME );
	}

void Vehicle::VehicleStart
	(
	Event *ev
	)

	{
	Entity *ent;
	VehicleBase *last;
   Vector   drivemins, drivemaxs;
   float    max;
   float    width,height;
   orientation_t or;

   // become solid
   setSolidType( SOLID_BBOX );

	last = this;

	for( ent = G_NextEntity( NULL ); ent != NULL; ent = G_NextEntity( ent ) )
		{
		if ( ( ent != this ) && ( ent->isSubclassOf( VehicleBase ) ) )
			{
			if ( ( ent->absmax.x >= absmin.x ) && ( ent->absmax.y >= absmin.y ) && ( ent->absmax.z >= absmin.z ) &&
				( ent->absmin.x <= absmax.x ) && ( ent->absmin.y <= absmax.y ) && ( ent->absmin.z <= absmax.z ) )
				{
				last->vlink = ( VehicleBase * )ent;
				last = ( VehicleBase * )ent;
            last->offset = last->origin - origin;
            last->offset = getLocalVector( last->offset );
            last->edict->s.scale *= edict->s.scale;
				}
			}
		}

	last->vlink = NULL;

   //
   // get the seat offset
   //
   if ( GetRawTag( "seat", &or ) )
      {
      driveroffset = Vector( or.origin );
      }
   driveroffset += seatoffset * edict->s.scale;

   SetDriverAngles( angles + seatangles );

   max_health = health;

   //
   // calculate drive mins and maxs
   //
   max = 0;
   if ( fabs( mins[ 0 ] ) > max )
      max = fabs( mins[ 0 ] );
   if ( fabs( maxs[ 0 ] ) > max )
      max = fabs( maxs[ 0 ] );
   if ( fabs( mins[ 1 ] ) > max )
      max = fabs( mins[ 1 ] );
   if ( fabs( maxs[ 1 ] ) > max )
      max = fabs( maxs[ 1 ] );
   drivemins = Vector( -max, -max, mins[ 2 ] ) * edict->s.scale;
   drivemaxs = Vector( max, max, maxs[ 2 ] ) * edict->s.scale;

   width = maxs[ 1 ] - mins[ 1 ];
   height = maxs[ 0 ] - mins[ 0 ];

   maxtracedist = height;

   Corners[ 0 ][ 0 ] = -(width/4);
   Corners[ 0 ][ 1 ] = (height/4);
   Corners[ 0 ][ 2 ] = 0;

   Corners[ 1 ][ 0 ] = (width/4);
   Corners[ 1 ][ 1 ] = (height/4);
   Corners[ 1 ][ 2 ] = 0;

   Corners[ 2 ][ 0 ] = -(width/4);
   Corners[ 2 ][ 1 ] = -(height/4);
   Corners[ 2 ][ 2 ] = 0;

   Corners[ 3 ][ 0 ] = (width/4);
   Corners[ 3 ][ 1 ] = -(height/4);
   Corners[ 3 ][ 2 ] = 0;
   if ( drivable )
      {
      // drop everything back to the floor
      droptofloor( 64 );
      Postthink();
      }
   last_origin = origin;
   setSize( drivemins, drivemaxs );
	}

void Vehicle::Drivable
	(
	Event *ev
	)

	{
	setMoveType( MOVETYPE_NONE );
   drivable = true;
	}

void Vehicle::UnDrivable
	(
	Event *ev
	)

	{
	setMoveType( MOVETYPE_PUSH );
   drivable = false;
	}

void Vehicle::Jumpable
	(
	Event *ev
	)

	{
   jumpable = true;
	}

void Vehicle::Lock
	(
	Event *ev
	)

	{
   locked = true;
	}

void Vehicle::UnLock
	(
	Event *ev
	)

	{
   locked = false;
	}

void Vehicle::SteerInPlace
	(
	Event *ev
	)

	{
   steerinplace = true;
	}

void Vehicle::SeatAnglesOffset
	(
	Event *ev
	)

	{
   seatangles = ev->GetVector( 1 );
	}

void Vehicle::SeatOffset
	(
	Event *ev
	)

	{
   seatoffset = ev->GetVector( 1 );
	}

void Vehicle::SetWeapon
	(
	Event *ev
	)

	{
   showweapon = true;
   hasweapon = true;
   weaponName = ev->GetString( 1 );
	}

void Vehicle::ShowWeaponEvent
	(
	Event *ev
	)

	{
   showweapon = true;
	}

void Vehicle::DriverAnimation
	(
	Event *ev
	)

	{
   driveranim = ev->GetString( 1 );
	}

qboolean Vehicle::HasWeapon
	(
   void
	)

	{
   return hasweapon;
	}

qboolean Vehicle::ShowWeapon
	(
   void
	)

	{
   return showweapon;
	}

void Vehicle::SetDriverAngles
	(
   Vector angles
   )
   {
   int i;

   if ( !driver )
      return;

	for( i = 0; i < 3; i++ )
		{
		driver->client->ps.delta_angles[ i ] = ANGLE2SHORT( angles[ i ] - driver->client->cmd_angles[ i ] );
		}
   }

/*
=============
CheckWater
=============
*/
void Vehicle::CheckWater
   (
   void
   )

   {
	Vector  point;
	int	  cont;
	int	  sample1;
	int	  sample2;
	VehicleBase *v;

   unlink();
	v = this;
	while( v->vlink )
		{
		v = v->vlink;
      v->unlink();
		}

   if ( driver )
      {
      driver->unlink();
      }

   //
   // get waterlevel
   //
	waterlevel = 0;
	watertype = 0;

	sample2 = maxs[ 2 ] - mins[ 2 ];
	sample1 = sample2 / 2;

   point = origin;
   point[ 2 ] += mins[ 2 ];
	cont = gi.pointcontents( point, 0 );

	if ( cont & MASK_WATER )
	   {
		watertype = cont;
		waterlevel = 1;
      point[ 2 ] = origin[ 2 ] + mins[ 2 ] + sample1;
		cont = gi.pointcontents( point, 0 );
		if ( cont & MASK_WATER )
		   {
			waterlevel = 2;
         point[ 2 ] = origin[ 2 ] + mins[ 2 ] + sample2;
			cont = gi.pointcontents( point, 0 );
			if ( cont & MASK_WATER )
            {
				waterlevel = 3;
            }
		   }
	   }

   link();
	v = this;
	while( v->vlink )
		{
		v = v->vlink;
      v->link();
		}

   if ( driver )
      {
      driver->link();
      driver->waterlevel = waterlevel;
      driver->watertype = watertype;
      }
   }

/*
=============
WorldEffects
=============
*/
void Vehicle::WorldEffects
	(
	void
	)

	{
   //
   // Check for earthquakes
   //
   if ( groundentity && ( level.earthquake > level.time ) )
      {
      velocity += Vector
         (
         level.earthquake_magnitude * EARTHQUAKE_STRENGTH * G_CRandom(),
         level.earthquake_magnitude * EARTHQUAKE_STRENGTH * G_CRandom(),
         level.earthquake_magnitude * 1.5f * G_Random()
         );
      }

   //
   // check for lava
   //
   if ( watertype & CONTENTS_LAVA )
      {
      Damage( world, world, 20 * waterlevel, origin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_LAVA );
      }
	}

void Vehicle::DriverUse
	(
	Event *ev
	)

	{
	Event *event;
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( !other || !other->isSubclassOf( Sentient ) )
		{
		return;
		}

	if ( driver )
		{
      int height;
      int ang;
      Vector angles;
      Vector forward;
      Vector pos;
      float ofs;
      trace_t trace;

		if ( other != driver )
			{
			return;
			}

      if ( locked )
         return;

      //
      // place the driver on the ground
      //
      ofs = size.length() * 0.5f;
      for ( height = 0; height < 100; height += 16 )
         {
         for ( ang = 0; ang < 360; ang += 30 )
            {
            angles[ 1 ] = driver->angles[ 1 ] + ang + 90;
         	angles.AngleVectors( &forward, NULL, NULL );
            pos = origin + (forward * ofs);
            pos[2] += height;
      		trace = G_Trace( pos, driver->mins, driver->maxs, pos, NULL, MASK_PLAYERSOLID, false, "Vehicle::DriverUse 1" );
            if ( !trace.startsolid && !trace.allsolid )
               {
               Vector end;

               end = pos;
               end[ 2 ] -= 128;
         		trace = G_Trace( pos, driver->mins, driver->maxs, end, NULL, MASK_PLAYERSOLID, false, "Vehicle::DriverUse 2" );
               if ( trace.fraction < 1.0f )
                  {
                  driver->setOrigin( pos );
                  goto foundpos;
                  }
               }
            }
         }
      return;

foundpos:

		turnimpulse = 0;
		moveimpulse = 0;
		jumpimpulse = 0;

		event = new Event( EV_Vehicle_Exit );
		event->AddEntity( this );
		driver->ProcessEvent( event );
      if ( hasweapon )
         {
         driver->takeItem( weaponName.c_str() );
         }
      if ( drivable )
         {
			StopLoopSound();
			Sound( "snd_dooropen", CHAN_BODY );
			Sound( "snd_stop", CHAN_VOICE );
         driver->setSolidType( SOLID_BBOX );
         }

		driver = NULL;
		}
	else
		{
		driver = ( Sentient * )other;
		lastdriver = driver;

      if ( drivable )
   	   setMoveType( MOVETYPE_VEHICLE );
      if ( hasweapon )
         {
/*
         Weapon *weapon;

         weapon = driver->giveWeapon( weaponName.c_str() );
         if ( weapon )
            {
            driver->ForceChangeWeapon( weapon );
            }
         else
            {
            return;
            }
*/
         }
      if ( drivable )
         {
			Sound( "snd_doorclose", CHAN_BODY );
			Sound( "snd_start", CHAN_VOICE );
         driver->setSolidType( SOLID_NOT );
         }

		event = new Event( EV_Vehicle_Enter );
		event->AddEntity( this );
      if ( driveranim.length() )
         event->AddString( driveranim );
		driver->ProcessEvent( event );

      offset = other->origin - origin;

		flags	|= FL_POSTTHINK;
      SetDriverAngles( angles + seatangles );
		}
	}

qboolean Vehicle::Drive
	(
	usercmd_t *ucmd
	)

	{
	Vector i, j, k;

	if ( !driver || !driver->isClient() )
		{
		return false;
		}

   if ( !drivable )
      {
      driver->client->ps.pm_flags |= PMF_FROZEN;
      ucmd->forwardmove = 0;
      ucmd->rightmove = 0;
      return false;
      }

   driver->client->ps.pm_flags |= PMF_NO_PREDICTION;

	moveimpulse = ( ( float )ucmd->forwardmove ) * 3;
	turnimpulse = ( ( float )-ucmd->rightmove ) * 0.5;
	jumpimpulse = ( ( float )ucmd->upmove * gravity ) / 350;
   if ( ( jumpimpulse < 0 ) || ( !jumpable ) )
      jumpimpulse = 0;

	turnimpulse += 2*angledist( SHORT2ANGLE( ucmd->angles[ 1 ] ) - driver->client->cmd_angles[ 1 ] );

	return true;
	}

void Vehicle::Postthink
	(
	void
	)

	{
	float			turn;
	Vector		i, j, k;
   int         index;
   trace_t     trace;
   Vector      normalsum;
   int         numnormals;
   Vector      temp;
   Vector      pitch;
   Vector      roll;
	VehicleBase *v;
	VehicleBase *last;
   float       drivespeed;


   if ( drivable )
      {
      currentspeed = moveimpulse / 4;

	   turnangle = turnangle * 0.25f + turnimpulse;
	   if ( turnangle > maxturnrate )
		   {
		   turnangle = maxturnrate;
		   }
	   else if ( turnangle < -maxturnrate )
		   {
		   turnangle = -maxturnrate;
		   }
	   else if ( fabs( turnangle ) < 2 )
		   {
		   turnangle = 0;
		   }
      temp[ PITCH ] = 0;
      temp[ YAW ] = angles[ YAW ];
      temp[ ROLL ] = 0;
      temp.AngleVectors( &i, &j, &k );
      j = vec_zero - j;

      //
      // figure out what our orientation is
      //
      numnormals = 0;
      for ( index = 0; index < 4; index++ )
         {
         Vector start, end;
         Vector boxoffset;

         boxoffset = Corners[ index ];
         start = origin + i * boxoffset[0] + j * boxoffset[1] + k * boxoffset[2];
         end = start;
         end[ 2 ] -= maxtracedist;
         trace = G_Trace( start, vec_zero, vec_zero, end, NULL, MASK_SOLID, false, "Vehicle::PostThink Corners" );
         if ( trace.fraction != 1.0f && !trace.startsolid )
            {
            normalsum += Vector( trace.plane.normal );
            numnormals++;
            }
         }
      if ( numnormals > 1 )
         {
         temp = normalsum * ( 1.0f/ numnormals );
         temp.normalize();
         i = temp.CrossProduct( temp, j );
         pitch = i;
         // determine pitch
         angles[ 0 ] = -(pitch.toPitch());
         }

	   turn = turnangle * ( 1.0f / 200.0f );

      if ( groundentity )
         {
         float dot;
         Vector newvel;
         Vector flatvel;

         velocity[ 0 ] *= 0.925f;
         velocity[ 1 ] *= 0.925f;
         flatvel = Vector( orientation[ 0 ] );
         velocity += flatvel * currentspeed;
         flatvel[ 2 ] = 0;
         dot = velocity * flatvel;
	      if ( dot > speed )
		      {
		      dot = speed;
		      }
	      else if ( dot < -speed )
		      {
		      dot = -speed;
		      }
	      else if ( fabs( dot ) < 20.0f )
		      {
		      dot = 0;
		      }
         newvel = flatvel * dot;
         velocity[ 0 ] = newvel[ 0 ];
         velocity[ 1 ] = newvel[ 1 ];
         velocity[ 2 ] += dot * jumpimpulse;

		   avelocity *= 0.05;
         if ( steerinplace )
            {
            if ( dot < 350 )
               dot = 350;
  		      avelocity.y += turn * dot;
            }
         else
            {
  		      avelocity.y += turn * dot;
            }
         }
      else
         {
		   avelocity *= 0.1;
		   }
	   angles += avelocity * level.frametime;
	   setAngles( angles );
      }
   drivespeed = velocity * Vector( orientation[ 0 ] );

   if ( drivable && driver )
      {
		str sound_name;

		if ( currentspeed > 0 )
         sound_name = "snd_forward";
      else if ( currentspeed < 0 )
         sound_name = "snd_backward";
      else
         sound_name = "snd_idle";

		LoopSound( sound_name.c_str() );
      }

	i = Vector( orientation[ 0 ] );
	j = Vector( orientation[ 1 ] );
	k = Vector( orientation[ 2 ] );

	if ( driver )
		{
      Player * player;

      player = ( Player * )( Sentient * )driver;
      player->setOrigin( origin + i * driveroffset[0] + j * driveroffset[1] + k * driveroffset[2] );
      if ( drivable )
         {
         player->velocity = vec_zero;
         player->setAngles( angles );
         player->v_angle = angles;
         }
		}

	last = this;
	while( last->vlink )
		{
		v = last->vlink;
      v->setOrigin( origin + i * v->offset.x + j * v->offset.y + k * v->offset.z );
		v->avelocity = avelocity;
		v->velocity = velocity;
		v->angles[ ROLL ] = angles[ ROLL ];
		v->angles[ YAW ] = angles[ YAW ];
		v->angles[ PITCH ] = (int)( v->angles[ PITCH ] + (drivespeed/4) ) % 360;

		if ( v->isSubclassOf( FrontWheels ) )
			{
			v->angles += Vector( 0, turnangle, 0 );
			}
		v->setAngles( v->angles );

		last = v;
		}

   CheckWater();
   WorldEffects();

   // save off last origin
   last_origin = origin;

	if ( !driver && !velocity.length() && groundentity && !( watertype & CONTENTS_LAVA ) )
		{
		flags &= ~FL_POSTTHINK;
      if ( drivable )
   	   setMoveType( MOVETYPE_NONE );
		}
   }

void Vehicle::VehicleTouched
	(
	Event *ev
	)

	{
	Entity	*other;
	float		speed;
   Vector   delta;
	Vector	dir;

 	other = ev->GetEntity( 1 );
	if ( other == driver )
		{
		return;
		}

   if ( other == world )
      {
      return;
      }

   if ( drivable && !driver )
      {
      return;
      }

   delta = origin - last_origin;
	speed = delta.length();
	if ( speed > 2 )
		{
		Sound( "vehicle_crash", qtrue );
		dir = delta * ( 1 / speed );
      other->Damage( this, lastdriver, speed * 8, origin, dir, vec_zero, speed*15, 0, MOD_VEHICLE );
		}

	}

void Vehicle::VehicleBlocked
	(
	Event *ev
	)

	{
   return;
/*
	Entity	*other;
	float		speed;
   float    damage;
   Vector   delta;
   Vector   newvel;
	Vector	dir;

   if ( !velocity[0] && !velocity[1] )
      return;

	other = ev->GetEntity( 1 );
	if ( other == driver )
		{
		return;
		}
   if ( other->isSubclassOf( VehicleBase ) )
      {
      delta = other->origin - origin;
      delta.normalize();

      newvel = vec_zero - ( velocity) + ( other->velocity * 0.25 );
      if ( newvel * delta < 0 )
         {
         velocity = newvel;
         delta = velocity - other->velocity;
         damage = delta.length()/4;
         }
      else
         {
         return;
         }
      }
   else if ( ( velocity.length() < 350 ) )
      {
      other->velocity += velocity*1.25f;
      other->velocity[ 2 ] += 100;
      damage = velocity.length()/4;
      }
   else
      {
      damage = other->health + 1000;
      }

	// Gib 'em outright
	speed = fabs( velocity.length() );
	dir = velocity * ( 1 / speed );
   other->Damage( this, lastdriver, damage, origin, dir, vec_zero, speed, 0, MOD_VEHICLE, -1, -1, 1.0f );
*/
   }

Sentient *Vehicle::Driver
	(
	void
	)

	{
	return driver;
	}

qboolean Vehicle::IsDrivable
	(
	void
	)

	{
	return drivable;
	}

void Vehicle::SetSpeed
	(
	Event *ev
	)
   {
   speed = ev->GetFloat( 1 );
   }

void Vehicle::SetTurnRate
	(
	Event *ev
	)
   {
   maxturnrate = ev->GetFloat( 1 );
   }


CLASS_DECLARATION( Vehicle, DrivableVehicle, "script_drivablevehicle" )
	{
		{ &EV_Damage,				   Entity::DamageEvent },
		{ &EV_Killed,				   Killed },
		{ NULL, NULL }
	};

DrivableVehicle::DrivableVehicle()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

   drivable = true;
   flags |= FL_DIE_EXPLODE;
	}

void DrivableVehicle::Killed(Event *ev)
   {
   Entity * ent;
   Entity * attacker;
   Vector dir;
   Event * event;
   const char * name;
	VehicleBase *last;

   takedamage = DAMAGE_NO;
   setSolidType( SOLID_NOT );
	hideModel();

	attacker		= ev->GetEntity( 1 );

//
// kill the driver
//
   if ( driver )
      {
      Vector dir;
      SentientPtr sent;
      Event * event;

      velocity = vec_zero;
      sent = driver;
      event = new Event( EV_Use );
      event->AddEntity( sent );
      ProcessEvent( event );
      dir = sent->origin - origin;
      dir[ 2 ] += 64;
      dir.normalize();
      sent->Damage( this, this, sent->health*2, origin, dir, vec_zero, 50, 0, MOD_VEHICLE  );
      }

   if (flags & FL_DIE_EXPLODE)
      {
      CreateExplosion( origin, 150*edict->s.scale, this, this, this );
      }

   if (flags & FL_DIE_GIBS)
      {
      setSolidType( SOLID_NOT );
      hideModel();

      CreateGibs( this, -150, edict->s.scale, 3 );
      }
//
// kill all my wheels
//
	last = this;
	while( last->vlink )
		{
		last->vlink->PostEvent( EV_Remove, 0 );
		last = last->vlink;
		}


//
// kill the killtargets
//
	name = KillTarget();
	if ( name && strcmp( name, "" ) )
		{
		ent = NULL;
		do
			{
			ent = G_FindTarget( ent, name );
			if ( !ent )
				{
				break;
				}
			ent->PostEvent( EV_Remove, 0 );
			}
		while ( 1 );
		}

//
// fire targets
//
	name = Target();
	if ( name && strcmp( name, "" ) )
		{
      ent = NULL;
		do
			{
			ent = G_FindTarget( ent, name );
			if ( !ent )
				{
				break;
				}

			event = new Event( EV_Activate );
			event->AddEntity( attacker );
			ent->ProcessEvent( event );
			}
		while ( 1 );
		}

   PostEvent( EV_Remove, 0 );
   }



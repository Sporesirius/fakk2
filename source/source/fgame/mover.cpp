//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/mover.cpp                          $
// $Revision:: 7                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 5/31/00 10:38a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/mover.cpp                               $
// 
// 7     5/31/00 10:38a Markd
// fixed initialization bug
// 
// 6     5/30/00 7:06p Markd
// saved games 4th pass
// 
// 5     10/01/99 2:42p Markd
// moved all the binding code back into Entity from Mover
// 
// 4     9/20/99 11:43a Markd
// added currentOrigin and currentAngles support to setOrigin and setAngles
// 
// 3     9/17/99 5:32p Jimdose
// added TR_LERP
// 
// 2     9/13/99 3:27p Aldie
// code merge
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 14    6/07/99 12:25p Jimdose
// setAngles now properly updates viewangles when bound
//
// DESCRIPTION:
// Base class for any object that needs to move to specific locations over a
// period of time.  This class is kept separate from most entities to keep
// class size down for objects that don't need such behavior.
//

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "mover.h"

#define MOVE_ANGLES 1
#define MOVE_ORIGIN 2

CLASS_DECLARATION( Trigger, Mover, "mover" )
	{
	   { &EV_MoveDone,         MoveDone },
		{ NULL, NULL }
	};


Mover::Mover()
   {
   edict->s.pos.trType = TR_LERP;
   endevent = NULL;
   }

Mover::~Mover()
	{
	}

void Mover::MoveDone
	(
	Event *ev
	)

	{
   Event * event;
   Vector move;
	Vector amove;

	// zero out the movement
	if ( moveflags & MOVE_ANGLES )
		{
		avelocity = vec_zero;
		amove = angledest - localangles;
		}
	else
		{
		amove = vec_zero;
		}

	if ( moveflags & MOVE_ORIGIN )
		{
		velocity	= vec_zero;
		move = finaldest - localorigin;
		}
	else
		{
		move = vec_zero;
		}

	if ( !G_PushMove( this, move, amove ) )
		{
		// Delay finish till we can move into the final position
		PostEvent( EV_MoveDone, FRAMETIME );
		return;
		}

	//
	// After moving, set origin to exact final destination
	//
	if ( moveflags & MOVE_ORIGIN )
		{
		setOrigin( finaldest );
		}

	if ( moveflags & MOVE_ANGLES )
		{
		localangles = angledest;

		if ( ( localangles.x >= 360 ) || ( localangles.x < 0 ) )
			{
			localangles.x -= ( (int)localangles.x / 360 ) * 360;
			}
		if ( ( localangles.y >= 360 ) || ( localangles.y < 0 ) )
			{
			localangles.y -= ( (int)localangles.y / 360 ) * 360;
			}
		if ( ( localangles.z >= 360 ) || ( localangles.z < 0 ) )
			{
			localangles.z -= ( (int)localangles.z / 360 ) * 360;
			}
		}

   event = endevent;
   endevent = NULL;
	ProcessEvent( event );
	}

/*
=============
MoveTo

calculate self.velocity and self.nextthink to reach dest from
self.origin traveling at speed
===============
*/
void Mover::MoveTo
	(
	Vector	tdest,
	Vector	angdest,
	float		tspeed,
	Event		&event
	)

	{
	Vector vdestdelta;
	Vector angdestdelta;
	float  len;
	float  traveltime;

	assert( tspeed >= 0 );

	if ( !tspeed )
		{
		error( "MoveTo", "No speed is defined!" );
		}

	if ( tspeed < 0 )
		{
		error( "MoveTo", "Speed is negative!" );
		}

	// Cancel previous moves
	CancelEventsOfType( EV_MoveDone );

	moveflags = 0;

   if ( endevent )
      {
      delete endevent;
      }
	endevent = new Event( event );

	finaldest = tdest;
	angledest = angdest;

	if ( finaldest != localorigin )
		{
		moveflags |= MOVE_ORIGIN;
		}
	if ( angledest != localangles )
		{
		moveflags |= MOVE_ANGLES;
		}

   if ( !moveflags )
      {
      // stop the object from moving
      velocity = vec_zero;
      avelocity = vec_zero;

      // post the event so we don't wait forever
   	PostEvent( EV_MoveDone, FRAMETIME );
      return;
      }

	// set destdelta to the vector needed to move
	vdestdelta = tdest - localorigin;
	angdestdelta = angdest - localangles;

	if ( tdest == localorigin )
		{
		// calculate length of vector based on angles
		len = angdestdelta.length();
		}
	else
		{
		// calculate length of vector based on distance
		len = vdestdelta.length();
		}

	// divide by speed to get time to reach dest
	traveltime = len / tspeed;

	// Quantize to FRAMETIME
// E3 HACK
//	traveltime *= ( 1 / FRAMETIME );
//	traveltime = ( float )( (int)traveltime ) * FRAMETIME;
	if ( traveltime < FRAMETIME )
		{
		traveltime = FRAMETIME;
		vdestdelta = vec_zero;
      angdestdelta = vec_zero;
		}

	// scale the destdelta vector by the time spent traveling to get velocity
	if ( moveflags & MOVE_ORIGIN )
		{
		velocity = vdestdelta * ( 1 / traveltime );
		}

	if ( moveflags & MOVE_ANGLES )
		{
		avelocity = angdestdelta * ( 1 / traveltime );
		}

	PostEvent( EV_MoveDone, traveltime );
	}

/*
=============
LinearInterpolate
===============
*/
void Mover::LinearInterpolate
	(
	Vector tdest,
	Vector angdest,
	float time,
	Event &event
	)

	{
	Vector vdestdelta;
	Vector angdestdelta;
	float t;

   if ( endevent )
      {
      delete endevent;
      }
	endevent = new Event( event );
	finaldest = tdest;
	angledest = angdest;

	// Cancel previous moves
	CancelEventsOfType( EV_MoveDone );

	// Quantize to FRAMETIME
//E3 HACK
//	time *= ( 1 / FRAMETIME );
//	time = ( float )( (int)time ) * FRAMETIME;
	if ( time < FRAMETIME )
		{
		time = FRAMETIME;
		}

	moveflags = 0;
	t = 1 / time;
	// scale the destdelta vector by the time spent traveling to get velocity
	if ( finaldest != localorigin )
		{
		vdestdelta = tdest - localorigin;
		velocity = vdestdelta * t;
		moveflags |= MOVE_ORIGIN;
		}

	if ( angledest != localangles )
		{
		angdestdelta = angdest - localangles;
		avelocity = angdestdelta * t;
		moveflags |= MOVE_ANGLES;
		}

	PostEvent( EV_MoveDone, time );
	}


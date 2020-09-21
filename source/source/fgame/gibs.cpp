//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/gibs.cpp                           $
// $Revision:: 25                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 8/10/00 5:45p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/gibs.cpp                                $
// 
// 25    8/10/00 5:45p Steven
// Fixed a way for blood to stay around forever on gibs.
// 
// 24    7/25/00 10:43a Steven
// Made snd_decap louder,
// 
// 23    7/17/00 3:40p Steven
// Removed sv_gore stuff.
// 
// 22    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 21    6/22/00 5:33p Steven
// Fixed the amount of time gib blood spurts stay around.
// 
// 20    6/19/00 4:53p Steven
// Added next_bleed_time to make gibs not bleed as much.
// 
// 19    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 18    4/15/00 11:50a Steven
// Took out default blood names.
// 
// 17    4/14/00 10:36a Steven
// Added blood splat size to gibs.
// 
// 16    4/08/00 3:56p Steven
// Made it so gibs could be damaged and would spurt blood.
// 
// 15    4/04/00 6:54p Steven
// Added random radius to the blood splats.
// 
// 14    4/01/00 1:20p Steven
// Some clean up.
// 
// 13    3/31/00 1:02p Steven
// Fixed a bug in the bloodsplats.
// 
// 12    3/30/00 2:04p Steven
// Added blood splats back in.
// 
// 11    3/22/00 10:36a Steven
// Made blood optional in gibs (started using blood_trail variable).
// 
// 10    3/02/00 6:40p Steven
// Made which blood model to use a parameter to gib.
// 
// 9     1/20/00 6:54p Aldie
// Removed bloodsplats until we do them the right way
// 
// 8     1/12/00 4:31p Steven
// Added new movetype MOVETYPE_GIB.
// 
// 7     1/06/00 7:00p Steven
// Made it so gibs did not have to have a model.
// 
// 6     1/06/00 4:39p Markd
// fixed tiki file name
// 
// 5     1/05/00 6:44p Steven
// Fixed gib blood splats (their origin was being miscalculated).
// 
// 4     9/29/99 5:18p Steven
// Event formatting.
// 
// 3     9/27/99 5:44p Markd
// began documentation and cleanup phase after merge
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 14    9/01/99 8:17p Steven
// Changed gibs to use bspurt2.tik.
// 
// 13    8/28/99 11:44a Steven
// Removed global from sound function calls.
//
// DESCRIPTION:
// Gibs - nuff said

#include "gibs.h"
#include "decals.h"

Event EV_ThrowGib
	(
	"throwgib",
	EV_DEFAULT,
   "eif",
   "ent velocity scale",
   "Throw a gib."
	);

CLASS_DECLARATION( Mover, Gib, "gib" )
	{
      { &EV_ThrowGib,      Throw },
      { &EV_Touch,         Splat },
      { &EV_Stop,          Stop },
		{ &EV_Damage,        Damage },
      { NULL, NULL }
	};

Gib::Gib
	(
	str name,
	qboolean blood_trail,
	str bloodtrailname,
	str bloodspurtname,
	str bloodsplatname,
	float bloodsplatsize,
	float pitch
	)

   {
   setSize("0 0 0", "0 0 0");

	if ( name.length() )
		setModel( name.c_str() );

	setMoveType( MOVETYPE_GIB );
	setSolidType( SOLID_BBOX );
	takedamage = DAMAGE_YES;
   sprayed     = false;
   fadesplat   = true;
   scale       = 2.0f;

	next_bleed_time = 0;

	final_pitch	= pitch;

	if ( blood_trail )
		{
		// Make a blood emitter and bind it to the head
		blood = new Mover;
   
		if ( bloodtrailname.length() )
			blood->setModel( bloodtrailname.c_str() );

		blood->setMoveType( MOVETYPE_BOUNCE );
		blood->setSolidType( SOLID_NOT );
		blood->bind( this );

		// Save the blood spurt name

		if ( bloodspurtname.length() )
			blood_spurt_name = bloodspurtname;

		// Save the blood splat name

		if ( bloodsplatname.length() )
			blood_splat_name = bloodsplatname;

		blood_splat_size = bloodsplatsize;
		}
	else
		{
		blood = NULL;
		}

   Sound( "snd_decap", CHAN_BODY, 1, 300 );
   }

Gib::~Gib()
	{
	if ( blood )
      blood->PostEvent( EV_Remove, 0 );
   blood = NULL;
	}

Gib::Gib()
   {
   if ( LoadingSavegame )
      {
      return;
      }

   setSize("0 0 0", "0 0 0");
   setModel("gib1.def");
	setMoveType( MOVETYPE_GIB );
	setSolidType( SOLID_BBOX );
   sprayed           = 0;
   fadesplat         = true;
   scale             = 2.0f;
   }

void Gib::Stop 
   (
   Event *ev 
   )

   {
   //setSolidType( SOLID_NOT );
   if ( blood )
      blood->PostEvent( EV_Remove, 0 );
   blood = NULL;
   }

void Gib::Splat
	(
	Event *ev
	)

   {
   if ( deathmatch->integer )
      return;

   if ( sprayed > 3 )
      {
      //setSolidType(SOLID_NOT);
      return;
      }

   sprayed++;
   scale -= 0.2;

	// Stop spinning / force to final pitch

	avelocity = vec_zero;

	if ( final_pitch != NO_FINAL_PITCH )
		{
		angles[PITCH] = final_pitch;
		setAngles( angles );
		}

	SprayBlood( origin );
   Sound( "snd_gibhit" );
   }

void Gib::Damage
	(
	Event *ev
	)

   {
   Vector direction;
	Entity *blood;
	Vector dir;

	if ( next_bleed_time > level.time )
		return;
	
   direction = ev->GetVector ( 5 );

	// Spawn a blood spurt

	if ( blood_spurt_name.length() > 0 )
		{
		blood = new Animate;
		blood->setModel( blood_spurt_name.c_str() );

		dir[0] = -direction[0];
		dir[1] = -direction[1];
		dir[2] = -direction[2];

		blood->angles = dir.toAngles();
		blood->setAngles( blood->angles );

		blood->setOrigin( centroid );
		blood->origin.copyTo( blood->edict->s.origin2 );
		blood->setSolidType( SOLID_NOT );

		blood->PostEvent( EV_Remove, 1 );

		next_bleed_time = level.time + 0.5;
		}
   }

void Gib::SprayBlood
	(
	Vector start
	)

   {
   Vector      norm;
	trace_t		trace;
	Vector		trace_end;

	trace_end = velocity;
	trace_end.normalize();
	trace_end *= 1000;
	trace_end += start;

   trace = G_Trace( start, vec_zero, vec_zero, trace_end, this, MASK_SOLID, false, "Gib::SprayBlood" );

	if ( HitSky( &level.impact_trace ) || ( !level.impact_trace.ent ) || ( level.impact_trace.ent->solid != SOLID_BSP ) )
		{
		return;
		}

	// Do a bloodsplat
   if ( blood_splat_name.length() )
		{
		Decal *decal = new Decal;
		decal->setShader( blood_splat_name );
		decal->setOrigin( Vector( trace.endpos ) + ( Vector( level.impact_trace.plane.normal ) * 0.2 ) );
		decal->setDirection( level.impact_trace.plane.normal );
		decal->setOrientation( "random" );
		decal->setRadius( blood_splat_size + G_Random( blood_splat_size ) );
		}
   }

void Gib::ClipGibVelocity
	(
	void
	)

	{
	if (velocity[0] < -400)
		velocity[0] = -400;
	else if (velocity[0] > 400)
		velocity[0] = 400;
	if (velocity[1] < -400)
		velocity[1] = -400;
	else if (velocity[1] > 400)
		velocity[1] = 400;
	if (velocity[2] < 200)
		velocity[2] = 200;	// always some upwards
	else if (velocity[2] > 600)
		velocity[2] = 600;
}

void Gib::SetVelocity
	(
	float damage
	)

   {
   velocity[0] = 100.0 * crandom();
	velocity[1] = 100.0 * crandom();
	velocity[2] = 200.0 + 100.0 * random();

   avelocity = Vector( G_Random( 600 ), G_Random( 600 ), G_Random( 600 ) );

   if ( ( damage < -150 )  && ( G_Random() > 0.95f ) )
      velocity *= 2.0f;
   else if ( damage < -100 )
      velocity *= 1.5f;

   ClipGibVelocity();
   }

void Gib::Throw
	(
	Event *ev
	)

   {
   Entity *ent;

   ent = ev->GetEntity(1);
   setOrigin(ent->centroid);
   origin.copyTo(edict->s.origin2);
   SetVelocity(ev->GetInteger(2));
   edict->s.scale = ev->GetFloat(3);
   PostEvent(EV_FadeOut, 10 + G_Random(5));
   }


void CreateGibs
   (
   Entity * ent,
   float damage,
   float scale,
   int num,
   const char * modelname
   )
   
   {

   }

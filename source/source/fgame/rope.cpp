/*
================================================================
ROPES
================================================================

Copyright (C) 1998 by 2015, Inc.
All rights reserved.

This source is may not be distributed and/or modified without
expressly written permission by 2015, Inc.

NOTES:

Rope piece length can be varied anywhere between 16 and 32.

For the movement dampening values, lower values make fore stiffer movement.
*/

#include "rope.h"
#include "player.h"


/*QUAKED func_rope (0.0 0.25 0.5) ?

The rope is defined by a bounding box.  The top of the box denotes the top of the rope and
the bottom of the rope is denoted by the bottom of the box.  The width of the box determines
the trigger field in which the player will hang on to the rope when grabbing it.

"ropeshader" : Name of the shader to use to render the rope (default is "ropeshader")
*/

Event EV_Rope_Think
   (
   "_rope_think",
   EV_DEFAULT,
   NULL,
   NULL,
   "Utility event to allow the rope to think every frame"
   );

Event EV_Rope_Setup
   (
   "_rope_setup",
   EV_DEFAULT,
   NULL,
   NULL,
   "Utility event to set the rope up for use"
   );

Event EV_Rope_RopeShader
   (
   "ropeshader",
   EV_DEFAULT,
   "s",
   "shader",
   "Set the shader to use on the rope."
   );


CLASS_DECLARATION( ScriptSlave, Rope, "func_rope" )
{
   { &EV_Touch,             Touch },
   { &EV_Rope_Setup,        Setup },
   { &EV_Rope_Think,        RopeThink },
   { NULL, NULL }
};

Rope::Rope()
   {
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

   rider = NULL;
   rider_pos = 1.0f;
   angular_velocity = vec_zero;
   angular_displacement = vec_zero;

   edict->s.eType        = ET_ROPE;
   edict->s.modelindex   = 1; // must be non zero
   SetShader( "ropeshader" );
   edict->s.scale = 1.0f;

   // initiliaze this FREAKING THING!!!!!
   rope_last_grab_time = 0;

	hideModel(); // make sure the base doesn't have a visual model
   Ghost(NULL); // but send it over the net

   edict->s.constantLight = 0;

   // setup the rope after spawning
   PostEvent( EV_Rope_Setup, EV_POSTSPAWN );
   }

void Rope::Setup
   (
   Event * ev
   )

   {
   rope_top = origin;
   rope_top.z += maxs.z;
   rope_bottom = origin;
   rope_bottom.z += mins.z;
   rope_length = Vector( rope_top - rope_bottom ).length();

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_TRIGGER );
   setContents( 0 );

   Update( CalculatePosition( rider_pos ) );
   }

void Rope::SetShader
   (
   str name
   )

   {
   shaderName = name;
   edict->s.surfaces[ 0 ] = gi.imageindex( shaderName );
   }

void Rope::SetShader
   (
   Event *ev
   )

   {
   SetShader( ev->GetString( 1 ) );
   }

void Rope::Update
   (
   Vector midpos
   )
   {
   rope_top.copyTo( edict->s.origin2 );
   midpos.copyTo( edict->s.netorigin );
   edict->s.alpha = ( 1.0f - rider_pos ) * rope_length;
   }

void Rope::Grab
   (
   Player *player,
   float   offset
   )
   {
   if ( player )
      {
      float  dot;
      Vector org;

	   // make sure that rope is infront of player
	   org = origin - player->origin;
      org.z = 0;
      org.normalize();
      dot = org * player->orientation[ 0 ];
      if ( dot > 0.6f )
         {
         player->GrabRope( this );
         rider_offset = offset;
         // offset the player slightly when getting height
         rider_pos = -( player->origin.z + offset + 8 - rope_top.z ) / rope_length;
         rider = player;
         PostEvent( EV_Rope_Think, 0 );
         }
      }
   }

void Rope::Release
   (
   Player * grabber
   )

   {
   if ( !rider || rider != grabber )
      {
      return;
      }

	// take care of grabber first
	grabber->GrabRope( NULL );
	if( !grabber->groundentity )
	   {
      float  length;
		Vector tmpvec;

      length = rope_length * rider_pos;

		tmpvec = Vector(grabber->orientation[0])*100;
		tmpvec.z += 300;
		grabber->velocity.x += tmpvec.x;
		grabber->velocity.y += tmpvec.y;
		grabber->velocity.z += tmpvec.z;

      // add in tangential velocity from the rope
		grabber->velocity.x += angular_velocity[ 0 ] * length;
		grabber->velocity.y += angular_velocity[ 1 ] * length;

      // subtract angular_velocity from the rope
      angular_velocity[ 0 ] -= tmpvec.x / rope_length;
      angular_velocity[ 1 ] -= tmpvec.y / rope_length;
	   }
   rider = NULL;
   //rider_pos = 1.0f;
   rope_last_grab_time = level.time + 1.0f;
   }


bool Rope::CanClimb
   (
   float distance
   )

   {
   Vector start, end, save_displacement;
   float current, newpos, newriderpos;

   // get old position
   current = rope_top.z - ( rider_pos * rope_length );
   start = CalculatePosition( rider_pos );

   // get new position
   newpos = current + distance;
   if ( newpos > rope_top.z || newpos < rope_bottom.z )
      {
      return false;
      }
   newriderpos = rider_pos - distance / rope_length;
   end = CalculatePosition( newriderpos );

   if ( !CanMove( start, end ) )
      {
      return false;
      }

   // check the at rest position as well
   // replace the angular displacement with zero
   save_displacement = angular_displacement;
   angular_displacement = vec_zero;
   start = CalculatePosition( rider_pos );
   end = CalculatePosition( newriderpos );
   // restore the angular displacment
   angular_displacement = save_displacement;
   if ( !CanMove( start, end ) )
      {
      return false;
      }
   return true;
   }

void Rope::Climb
   (
   float distance
   )

   {
   Vector start, end;
   float newriderpos;

   // get old position
   start = CalculatePosition( rider_pos );

   // get new position
   newriderpos = rider_pos - distance / rope_length;
   end = CalculatePosition( newriderpos );

   if ( CanMove( start, end ) )
      {
      rider_pos = newriderpos;
      Move( end );
      }
   }

void Rope::Touch
   (
   Event * ev
   )

   {
   Entity * other;

   if ( rider )
      return;

   // don't allow the player to regrab too soon
   if ( rope_last_grab_time > level.time )
      return;

   other = ev->GetEntity( 1 );

   if ( other->isSubclassOf( Player ) )
      {
      Player * p;

      p = ( Player * )other;

      if ( p->OnRope() )
         {
         warning( "Touch", "rope_grabbed \n");
         return;
         }
      p->TouchRope( this );
      }
   }

Vector Rope::CalculatePosition
   (
   float position
   )
   {
   Vector dir, endpos;

   // convert the angular displacement into a vector
   dir[ 0 ] = sin( angular_displacement[ 0 ] );
   dir[ 1 ] = sin( angular_displacement[ 1 ] );
   dir[ 2 ] = -1;
   dir.normalize();
   endpos = rope_top + dir * position * rope_length;

   return endpos;
   }

Vector Rope::CalculateRiderPosition
   (
   Vector position
   )
   {
   Vector endpos;

   endpos = position;
   endpos.z -= rider_offset;

   return endpos;
   }

bool Rope::CanMove
   (
   Vector start, 
   Vector location
   )

   {
   trace_t trace;

   if ( rider )
      {
      Vector startpos, pos;

      startpos = CalculateRiderPosition( start );
      pos = CalculateRiderPosition( location );
   	trace = G_Trace( startpos, rider->mins, rider->maxs, pos, rider, MASK_DEADSOLID, true, "Rope::CanMove" );
      if ( trace.fraction == 1.0f && !trace.startsolid && !trace.allsolid )
         return true;
      }
   else
      {
   	trace = G_Trace( start, vec_zero, vec_zero, location, this, MASK_DEADSOLID, false, "Rope::CanMove" );
      if ( trace.fraction == 1.0f && !trace.startsolid && !trace.allsolid )
         return true;
      }
   return false;
   }

void Rope::Move
   (
   Vector location
   )

   {
   if ( rider )
      {
      Vector pos;

      pos = CalculateRiderPosition( location );
      rider->setOrigin( pos );
      }
   }

#define ANGULAR_VELOCITY_THRESHOLD 0.01
#define ANGULAR_DISPLACEMENT_THRESHOLD 0.01
#define ANGULAR_DISPLACEMENT_LIMIT 1.5f
#define ANGULAR_SCALE_MAGIC_NUMBER 40
#define ANGULAR_FRICTION 0.99f
#define ANGULAR_FRICTION_NO_RIDER 0.95f
#define ANGULAR_VELOCITY_INPUT_SCALE ( 1.0f / 5.0f )
#define ANGULAR_MAX_INPUT_VELOCITY 0.017f
void Rope::RopeThink
   (
   Event * ev
   )
   {
   Vector original_displacement;

   original_displacement = angular_displacement;
   // add in our movment
   angular_displacement += angular_velocity * level.frametime;

   if ( angular_displacement[ 0 ] > ANGULAR_DISPLACEMENT_LIMIT )
      {
      angular_displacement[ 0 ] = ANGULAR_DISPLACEMENT_LIMIT;
      }
   else if ( angular_displacement[ 0 ] < -ANGULAR_DISPLACEMENT_LIMIT )
      {
      angular_displacement[ 0 ] = -ANGULAR_DISPLACEMENT_LIMIT;
      }
   if ( angular_displacement[ 1 ] > ANGULAR_DISPLACEMENT_LIMIT )
      {
      angular_displacement[ 1 ] = ANGULAR_DISPLACEMENT_LIMIT;
      }
   else if ( angular_displacement[ 1 ] < -ANGULAR_DISPLACEMENT_LIMIT )
      {
      angular_displacement[ 1 ] = -ANGULAR_DISPLACEMENT_LIMIT;
      }

   // we always think if we have a rider
   if ( 
         rider ||
         ( VectorLength( angular_velocity ) > ANGULAR_VELOCITY_THRESHOLD ) ||
         ( VectorLength( angular_displacement ) > ANGULAR_DISPLACEMENT_THRESHOLD )
      )
      {
      Vector endpos;
      float length;

      length = rider_pos * rope_length;

      // add in the players velocity amounts
      if ( rider )
         {
         float impulse[ 2 ];
         // sample velocity
         impulse[ 0 ] = cos( angular_displacement[ 0 ] ) * rider->velocity[ 0 ] * ANGULAR_VELOCITY_INPUT_SCALE / length;
         impulse[ 1 ] = cos( angular_displacement[ 1 ] ) * rider->velocity[ 1 ] * ANGULAR_VELOCITY_INPUT_SCALE / length;

         if ( impulse[ 0 ] > ANGULAR_MAX_INPUT_VELOCITY )
            {
            impulse[ 0 ] = ANGULAR_MAX_INPUT_VELOCITY;
            }
         else if ( impulse[ 0 ] < -ANGULAR_MAX_INPUT_VELOCITY )
            {
            impulse[ 0 ] = -ANGULAR_MAX_INPUT_VELOCITY;
            }
         if ( impulse[ 1 ] > ANGULAR_MAX_INPUT_VELOCITY )
            {
            impulse[ 1 ] = ANGULAR_MAX_INPUT_VELOCITY;
            }
         else if ( impulse[ 1 ] < -ANGULAR_MAX_INPUT_VELOCITY )
            {
            impulse[ 1 ] = -ANGULAR_MAX_INPUT_VELOCITY;
            }

         angular_velocity[ 0 ] += impulse[ 0 ];
         angular_velocity[ 1 ] += impulse[ 1 ];
         // clear out the velocity
         rider->velocity = vec_zero;
         }
      // adjust x and y velocities
      angular_velocity[ 0 ] += ( -sin( angular_displacement[ 0 ] ) * ANGULAR_SCALE_MAGIC_NUMBER * gravity ) / length;
      angular_velocity[ 1 ] += ( -sin( angular_displacement[ 1 ] ) * ANGULAR_SCALE_MAGIC_NUMBER * gravity ) / length;
      // apply some friction to the velocity, more if we have no rider
      if ( rider )
         {
         angular_velocity = angular_velocity * ANGULAR_FRICTION;
         }
      else
         {
         angular_velocity = angular_velocity * ANGULAR_FRICTION_NO_RIDER;
         }

      // if we don't have a rider, try to straighten out the rope again, but only when the rope is
      // sweeping through the origin position
      if ( 
            !rider && 
            ( rider_pos < 1.0f ) && 
            ( VectorLength( angular_displacement ) <= 0.1f ) 
         )
         {
         float newpos;

         // try to straighten out the rope
         newpos = rider_pos + 0.01f;
         if ( newpos > 1.0f )
            newpos = 1.0f;
         endpos = CalculatePosition( newpos );
         if ( CanMove( endpos, endpos ) )
            {
            rider_pos = newpos;
            }
         }


      endpos = CalculatePosition( rider_pos );
      if ( CanMove( endpos, endpos ) )
         {
         Move( endpos );
         }
      else
         {
         // we are blocked so adjust our velocities accordingly
         angular_velocity = -0.5f * angular_velocity;
         // restore our original position
         angular_displacement = original_displacement;
         // re-calculate our endpos
         endpos = CalculatePosition( rider_pos );
         }
      Update( endpos );
/*
      warning( "think", "pos %.2f d x%.4f y%.4f v x%.4f y%.4f\n", 
         rider_pos,
         angular_displacement[ 0 ],
         angular_displacement[ 1 ],
         angular_velocity[ 0 ],
         angular_velocity[ 1 ]
         );
      G_DebugLine( rope_top, endpos, 1, 1, 1, 1 );
*/

      CancelEventsOfType( EV_Rope_Think );
      PostEvent( EV_Rope_Think, FRAMETIME );
      }
   }



// functions used from g_phys.c
void G_CheckVelocity(Entity *ent);
int G_ClipVelocity (Vector& in, Vector& normal, Vector& out, float overbounce);
void G_Impact(Entity *e1, trace_t *trace);

//======================
//main physics functions
//======================
void rope_set_angles
   (
   RopePiece *piece
   )
   
   {
	Vector angvec;

	angvec = piece->prev_piece->origin - piece->origin;

	// helps eliminate an annoying wavering like effect
	if( fabs( angvec.x ) < 0.2 )
		angvec.x = 0;
	if( fabs( angvec.y ) < 0.2 )
		angvec.y = 0;

	piece->angles = angvec.toAngles();
	piece->setAngles( piece->angles );
   }

void G_Physics_Rope
   (
   RopePiece *ent
   )
   
   {
	RopePiece   *piece, *tmpent=NULL;
	Vector      move, tmpvec;
	Vector      old_origin;
	float       f1;
	Vector	   basevel;

	// rope piece movement is done by the base
	if( ent->rope_base )
		return;

	// move rope base if it has a velocity
   if ( ent->velocity != vec_zero )
      {
	   ent->origin += ent->velocity*level.frametime;
	   ent->setOrigin( ent->origin );
      }

   // calc velocities for rope_pieces
	if( ent->rope )
		((RopeBase *)ent)->FixAttachedRope( ent, ent->next_piece );
	else
		((RopeBase *)ent)->RestrictFreeRope( ent->next_piece );

   // do actual movement of rope pieces
	piece = ent->next_piece;

	while( piece )
	   {
      if ( piece->velocity != vec_zero )
         {
	   	piece->groundentity = NULL;
   
		   if( fabs( piece->velocity.x ) < 0.5 )
			   piece->velocity.x = 0;

		   if( fabs( piece->velocity.y ) < 0.5 )
			   piece->velocity.y = 0;

		   old_origin = piece->origin;

		   G_CheckVelocity( piece );

	      // move origin
   	   move = ( piece->velocity + basevel ) * level.frametime;
         piece->setOrigin( piece->origin + move );

		   if ( !piece->edict->inuse )
			   gi.Error( ERR_DROP, "rope_piece removed from game (not a good thing)\n" );
			   
		   piece->moveorg = piece->origin;
		   // keeps piece from getting too far away.
		   move = piece->origin - piece->prev_piece->origin;
		   f1 = ((RopeBase *)ent)->piecelength + 1;
		   
         if( move.length() > f1 )
		      {
			   move.normalize();
			   move *= f1;
			   move += piece->prev_piece->origin;
            piece->setOrigin( move );
		      }
         }

		// move on to next rope_piece
		tmpent   = piece;
		piece    = piece->next_piece;
   	}

	// if the rope is attached to something, restrict it's movement properly
	f1 = ((RopeBase *)ent)->piecelength + 1;
	piece = tmpent;
	while( piece && piece->rope_base )
      {
		if ( piece->rope )
		   {
			if ( piece->attachent )
			   {
				piece->setOrigin(piece->attachent->origin);
			   }
			else if ( piece->next_piece )
			   {
				move = piece->origin - piece->next_piece->origin;
				if ( move.length() > f1 )
				   {
					move.normalize();
					move *= f1;
					move += piece->next_piece->origin;
               piece->setOrigin( move );
				   }
			   }
		   }
		piece = piece->prev_piece;
	   }

	// set the angles now that all the pieces have been moved
	piece = ent->next_piece;
	while( piece )
	   {
		rope_set_angles( piece );
		piece = piece->next_piece;
	   }  
   }


/*================================================================

RopePiece class | main setup stuff

================================================================*/

/*QUAKED func_rope_piece (0.0 0.25 0.5) (-16 -16 -16) (16 16 16) WIGGLE ATT_WIGGLE
Rope Piece - A single piece of a rope

WIGGLE : Makes this piece of the rope wiggle about randomly. Only does this while not attached.

ATT_WIGGLE : Makes this piece of the rope wiggle around even while attached. WIGGLE must also be marked for this to work.

"target" : the "targetname" of the next piece in the rope. This should be blank if it's the last piece in the rope.
If a non-rope_piece entity is targeted, it will attach itself to it.

"targetname" : used for the previous piece in the rope to find and link to this piece of the rope.

"target2" : the targetname of the entity to attach this piece of the rope to.
Any piece of a rope can be attached to something and be triggered at any time to detach it.
Triggering the base of an attached rope will detach all attached points on that rope.

"wigglemove" : the amount of force the random wiggling has. 
    Default = 32

"wiggletime" : number of seconds between each time the rope wiggles.
    Default = 0.5

All other settings are set in the rope's rope_base entity.
*/

Event EV_RopePiece_Setup
   (
   "ropepiece_setup",
   EV_DEFAULT,
   NULL,
   NULL,
   "Set up the rope"
   );
Event EV_RopePiece_WiggleMove
   (
   "wigglemove",
   EV_DEFAULT,
   "f",
   "moveamount",
   "the amount of force the random wiggling has."
   );
Event EV_RopePiece_WiggleTime
   (
   "wiggletime",
   EV_DEFAULT,
   "f",
   "time",
   "number of seconds between each time the rope wiggles."
   );
Event EV_RopePiece_Damage
   (
   "damage",
   EV_DEFAULT,
   "f",
   "damage",
   "amount of damage to cause if rope hits something."
   );
Event EV_RopePiece_Target2
   (
   "target2",
   EV_DEFAULT,
   "s",
   "targetname",
   "Set the target of the rope piece to attach itself to."
   );
Event EV_RopePiece_AttachModel
   (
   "attachmodel",
   EV_DEFAULT,
   "s",
   "modelname",
   "Attach the specified model the this piece of rope"
   );

CLASS_DECLARATION( ScriptSlave, RopePiece, "func_rope_piece" )
{
   { &EV_RopePiece_Setup,        Setup },
   { &EV_Activate,               PieceTriggered },
   { &EV_RopePiece_WiggleTime,   SetWiggleTime },
   { &EV_RopePiece_WiggleMove,   SetWiggleMove },
   { &EV_RopePiece_Damage,       SetDamage },
   { &EV_RopePiece_Target2,      Target2 },
   { &EV_RopePiece_AttachModel,  AttachModelToRope },
   { NULL, NULL }
};

RopePiece::RopePiece()
   {
	setSolidType(SOLID_TRIGGER);
	setMoveType(MOVETYPE_NONE); // movement done by the RopeBase
	takedamage           = DAMAGE_NO;
   edict->s.eType       = ET_MULTIBEAM;
	edict->clipmask      = MASK_SOLID;                        
	wigglemove           = 32;
	wiggletime           = 0.5;
   edict->s.tag_num     = ENTITYNUM_NONE; // Not linked to anything
   edict->s.modelindex  = 1; // must be non zero
	rope                 = ROPE_NONE;
	attachent            = NULL;
   attachmodel          = NULL;

	if(!LoadingSavegame)
		PostEvent(EV_RopePiece_Setup, EV_SETUP_ROPEPIECE );
   }

void RopePiece::AttachModelToRope
   (
   Event *ev
   )

   {
   attachmodel = new Animate;
   attachmodel->setModel( ev->GetString( 1 ) );
   attachmodel->setOrigin( this->origin );
   }

void RopePiece::SetWiggleTime
   (
   Event *ev
   )

   {
   wiggletime = ev->GetFloat( 1 );
   }

void RopePiece::SetWiggleMove
   (
   Event *ev
   )

   {
   wigglemove = ev->GetFloat( 1 );
   }

void RopePiece::Target2
   (
   Event *ev
   )

   {
   target2 = ev->GetString( 1 );
   }

void RopePiece::setOrigin
   (
   Vector org
   )

   {
   // set the origin of the attachment
   Entity::setOrigin( org );

   if ( attachmodel )
      attachmodel->setOrigin( org );
   }

void RopePiece::Setup
   (
   Event *ev
   )

   {
	Vector tmpvec;
	Entity *tmpent;

	if( !Targeted() && !this->isSubclassOf( RopeBase ) )
      {
	   warning( "RopePiece::Setup", "rope_piece without targetname at (%i,%i,%i)\n", (int)origin[0], (int)origin[1], (int)origin[2]);
      PostEvent( EV_Remove, 0 );
      return;
      }

	if(Target() && strcmp(Target(), "") )
	   {
		tmpent = G_FindTarget( 0, Target() );
		if(!tmpent)
		   {
         warning( "RopePiece::Setup", "rope_piece at (%i,%i,%i) can't find its target\n", (int)origin[0], (int)origin[1], (int)origin[2] );
         PostEvent( EV_Remove, 0 );
         return;
		   }

      if ( tmpent == this )
         {
         warning( "RopePiece::Setup", "rope_piece at (%i,%i,%i) is targeting itself\n", (int)origin[0], (int)origin[1], (int)origin[2] );
         PostEvent( EV_Remove, 0 );
         return;
         }

      // Set the tag_num pointing to the child
      this->edict->s.tag_num = tmpent->edict->s.number;

		if( tmpent->isSubclassOf( RopePiece ) )
         {
			next_piece = (RopePiece *)tmpent;
         }
		else
		   {
			next_piece = NULL;
			attachent = tmpent;
			rope = ROPE_ATTACHED;
		   }
	   }

   if ( target2.length() )
      {
      attachent = G_FindTarget( 0, target2 );
      
      if ( !attachent )
         {
			warning( "RopePiece::Setup", "rope_piece at (%i,%i,%i) can't find attach target2\n", (int)origin[0], (int)origin[1], (int)origin[2] );
         return;
         }

      //next_piece = NULL;
      rope = ROPE_ATTACHED;
      }
   }

/*================================================================
RopePiece class | grabber climb and release stuff
================================================================*/

void RopePiece::Detach(void)
{
	qboolean attbelow;

	//only if we're attached to something
	if(!attachent)
		return;

	// adjust all the rope values of this rope's pieces
	// to allow it to move freely and for it to be grabbed.
	attachent = NULL;

	if(next_piece)
	{
		if(next_piece->rope & (ROPE_ATTACHED | ROPE_ABELOW))
			attbelow = true;
		else
			attbelow = false;
	}
	else
	{
		attbelow = false;
	}

	if(attbelow)
	{
		rope = ROPE_ABELOW;
	}
	else
	{
		RopePiece *curr_piece;

		curr_piece = this;
		while(curr_piece)
		{
			curr_piece->rope = ROPE_NONE;
			curr_piece = curr_piece->prev_piece;
		}
	}
}

void RopePiece::PieceTriggered(Event *ev)
{
	Detach();
}

/*================================================================
RopePiece class wiggling, oh my
================================================================*/

void RopePiece::Wiggle(void)
   {
	Vector tmpvec;
	int i;

	if(wiggle_debounce_time > level.time)
		return;

	wiggle_debounce_time = level.time + wiggletime;

	tmpvec = velocity;
	
   for(i = 0; i < 3; i++)
		tmpvec[i] += crandom()*wigglemove;

	rope_base->SetTouchVelocity(tmpvec, this, 1);
   }


/*================================================================

RopeBase class | main setup stuff

================================================================*/

/*QUAKED func_rope_base (0.0 0.25 0.5) (-16 -16 -16) (16 16 16) START_STILL
Rope Base - the main control and top end attachment entity for ropes

This entity is the point to where ropes attach their top end. It's a stationary point entity.
All setting for the whole rope are specified through this entity.
If you want/need to trigger a rope to do something, then this is the entity to trigger.
Trying to trigger a rope_piece will do nothing.

START_STILL : Specifies that the whole rope will be completely stationary untill it is either triggered, or grabbed.

"targetname" : The name that the rope is triggered with.

"target" : The "targetname" of the first rope_piece in the rope.

"piecelength" : The distance between each piece of the rope.
    Default = 24

"piecemodel" : The model to use for the rope pieces.

"ropedampener" : Horizontal velocity dampener for the rope.
	Default = 0.8

"stiffness" : Movement restricter on the amount that the rope can flex and bend. 
Valid values are from -1 (no restriction) to 1 (tried to be perfectly straight.
The position of the first rope piece determines what direction the rope is pushed from the base of the rope.
	Default = -1

"strength" : How strongly a stiff rope goes to position.
    Default = 1;

"attachmodel" : name of a model to attach onto this piece of rope

"ropeshader" : Name of the shader to use to render the rope (default is "ropeshader")
*/

Event EV_RopeBase_Setup
   (
   "ropebase_setup",
   EV_DEFAULT,
   NULL,
   NULL,
   "Set up the rope base"
   );
Event EV_RopeBase_PVSCheck
   (
   "ropebase_pvscheck",
   EV_DEFAULT,
   NULL,
   NULL,
   "Check for the rope in the PVS"
   );
Event EV_RopeBase_Stiffness
   (
   "stiffness",
   EV_DEFAULT,
   "f[-1,1]",
   "stiffness",
   "Movement restricter on the amount that the rope can flex and bend.\n"
   "Valid values are from -1 (no restriction) to 1 (tried to be perfectly straight.\n"
   "The position of the first rope piece determines what direction the rope is pushed from the base of the rope."
   );
Event EV_RopeBase_Strength
   (
   "strength",
   EV_DEFAULT,
   "f",
   "strength",
   "How strongly a stiff rope goes to position."
   );
Event EV_RopeBase_PieceLength
   (
   "piecelength",
   EV_DEFAULT,
   "f",
   "length",
   "The distance between each piece of the rope."
   );
Event EV_RopeBase_RopeDampener
   (
   "ropedampener",
   EV_DEFAULT,
   "f",
   "value",
   "Horizontal velocity dampener for the rope."
   );
Event EV_RopeBase_RopeShader
   (
   "ropeshader",
   EV_DEFAULT,
   "s",
   "shader",
   "Set the shader to use on the rope."
   );

CLASS_DECLARATION(RopePiece, RopeBase, "func_rope_base")
   {
      { &EV_RopeBase_Setup,            Setup },
      { &EV_RopeBase_Stiffness,        SetStiffness },
      { &EV_RopeBase_Strength,         SetStrength },
      { &EV_RopeBase_PieceLength,      SetPieceLength },
      { &EV_RopeBase_RopeDampener,     SetRopeDampener },
      { &EV_RopeBase_RopeShader,       SetShader },
      { &EV_Activate,                  Activate },
      { NULL, NULL }
   };

RopeBase::RopeBase()
{
	str tmpstr;
   float color[3];

	setOrigin(origin);
	setSolidType(SOLID_NOT);
	setMoveType(MOVETYPE_NONE); // till after setup

   edict->s.eType        = ET_MULTIBEAM;
   edict->s.surfaces[0]  = 0xff;
   edict->s.modelindex   = 1; // must be non zero

	piecelength = 24;
	pieceframe = floor(piecelength - 16);

	pieceskin = 0;

	dotlimit = -1;
	strength = 1;

	ropedampener = 0.75;

   SetShader( "ropeshader" );
   edict->s.scale = 1.5;

	hideModel(); // make sure the base doesn't have a visual model
   Ghost(NULL); // but send it over the net

	rope_base = NULL;
	prev_piece = NULL;
	rope = ROPE_NONE;

   color[0] = 0; color[1] = 0; color[2] = 0;
   G_SetConstantLight( &edict->s.constantLight, &color[0],&color[1],&color[2], NULL );

	if(!LoadingSavegame)
	{
		// setup all the pieces of the rope
		PostEvent(EV_RopeBase_Setup, EV_SETUP_ROPEBASE );
	}
}

void RopeBase::SetShader
   (
   str name
   )

   {
   shaderName = name;
   edict->s.surfaces[ 1 ] = gi.imageindex( shaderName );
   }

void RopeBase::SetShader
   (
   Event *ev
   )

   {
   SetShader( ev->GetString( 1 ) );
   }


void RopeBase::SetStiffness
   (
   Event *ev
   )

   {
	dotlimit = ev->GetFloat( 1 );
	
   if(dotlimit < -1)
		dotlimit = -1;
	else if(dotlimit > 1)
		dotlimit = 1;   
   }

void RopeBase::SetStrength
   (
   Event *ev
   )

   {
	strength = ev->GetFloat( 1 );	
   }

void RopeBase::SetPieceLength
   (
   Event *ev
   )

   {
	piecelength = ev->GetFloat( 1 );	
   }

void RopeBase::SetRopeDampener
   (
   Event *ev
   )

   {
   ropedampener = ev->GetFloat( 1 );
	if(ropedampener < 0.001)
		ropedampener = 0.001;
	else if(ropedampener > 1)
		ropedampener = 1;
   }

void RopeBase::Setup(Event *ev) 
{
	RopePiece *lastpiece, *currpiece;
	int num;
	Vector smin, smax, tmpvec;

	if(!strcmp(Target(), ""))
      {
      warning( "RopePiece::Setup", "rope_base without target at (%i,%i,%i)\n", (int)origin[0], (int)origin[1], (int)origin[2]);
      return;
      }

	if(!next_piece)
      {
      warning( "RopePiece::Setup", "rope_base cannot find target at (%i,%i,%i)\n", (int)origin[0], (int)origin[1], (int)origin[2]);
      return;
      }
	
	// set rope direction for stiff ropes
	if(dotlimit)
	{
		ropedir = next_piece->origin - origin;
		ropedir.normalize();
	}

	// set the size for the rope piece's touching box
	smin.x = smin.y = smin.z = -piecelength;
	smax.x = smax.y = smax.z = piecelength;

//set rope piece id numbers for use in various things
	piecenum = 0;

	num = 0;
	currpiece = next_piece;
	lastpiece = this;
	while(currpiece)
	{
		num++;
		currpiece->piecenum = num;

      currpiece->gravity = gravity;
		currpiece->moveorg = currpiece->origin;
		currpiece->setMoveType(MOVETYPE_ROPE);
		currpiece->setSize(smin, smax);
		
      if ( piecemodel.length() )
         currpiece->setModel(piecemodel);
      else
         currpiece->edict->s.modelindex = 1; // must be non zero

		currpiece->edict->s.frame = pieceframe;
		currpiece->edict->s.skinNum = pieceskin;

		currpiece->rope_base = this;
		currpiece->prev_piece = lastpiece;

		tmpvec = lastpiece->origin - currpiece->origin;
		currpiece->angles = tmpvec.toAngles();
		currpiece->setAngles(currpiece->angles);

		lastpiece = currpiece;
		currpiece = currpiece->next_piece;
	}

   // Set the child of the last piece to none
   lastpiece->edict->s.tag_num = ENTITYNUM_NONE;

	// go through the pieces again to set attach flags
	currpiece = lastpiece;
	num = 0;
	while(currpiece)
	{
		// mark all pieces above this as attached
		if(currpiece->rope & ROPE_ATTACHED)
			num = 1;

		if(currpiece->rope == ROPE_NONE && num)
			currpiece->rope = ROPE_ABELOW;

		currpiece = currpiece->prev_piece;
	}

	if(!(spawnflags & ROPE_START_STILL))
	{
		setMoveType(MOVETYPE_ROPE);
	}
}

void RopeBase::Activate(Event *ev)
{
	setMoveType(MOVETYPE_ROPE);

	if(rope == ROPE_ABELOW)
	{
		RopePiece *curr_piece;

		curr_piece = next_piece;
		while(curr_piece)
		{
			curr_piece->Detach();
			curr_piece = curr_piece->next_piece;
		}
	}
}

/*================================================================
RopeBase class | free hanging rope restriction
================================================================*/

void RopeBase::RestrictFreeRope(RopePiece *curr_piece)
{
	Vector ropevec;		// rope piece vector
	Vector velpart;		// velocity component moving to or away from rope piece
	float ropelen;		// length of extended rope
	float f1, f2;		// restrainment forces
	float i1, i2;		// intermediate values
	Vector tmpvec;

	while(curr_piece)
	{
		ropevec = curr_piece->prev_piece->origin - curr_piece->origin;

      if ( fabs( ropevec.z - piecelength ) > 2 )
         {
         // only add in gravity if the piece isn't already oriented downward
	   	// add in velocity from gravity
		   curr_piece->velocity.z -= gravity*sv_gravity->value*level.frametime;
         }

		ropelen = ropevec.length();

		// if location is beyond the rope's reach
		if (ropelen > piecelength)
		{	 
			// inertial dampener to reduce exagerated motion.
			curr_piece->velocity.x *= ropedampener;
			curr_piece->velocity.y *= ropedampener;

			// determine velocity component of rope vector
			i1 = DotProduct(curr_piece->velocity, ropevec);
			i2 = DotProduct(ropevec, ropevec);
			velpart = ropevec*(i1/i2);
		
			// restrainment default force 
			f2 = (ropelen - (piecelength - 3)) * 5;

			// if velocity heading is away from the rope piece
			if (i1 < 0)
			{
				// if rope has streched too much
				if (ropelen > piecelength+32)
				{
					// remove velocity component moving away from rope base
					curr_piece->velocity -= velpart;
				}
				f1 = f2;
			}
			else  // if velocity heading is towards the rope piece
			{
				if (velpart.length() < f2)
					f1 = f2 - velpart.length();
				else		
					f1 = 0;
			}

			if(f1) // applies rope restrainment
			{
				ropevec.normalize();
				curr_piece->velocity += ropevec*f1;
			}
		}

		// stiffen the rope if needed
		if(dotlimit > -1)
		{
			// get direction of destination
			if(curr_piece->prev_piece->rope_base) // rope piece above
			{
				ropevec = curr_piece->prev_piece->origin - curr_piece->prev_piece->prev_piece->origin;
				ropevec.normalize();
			}
			else // rope base above current piece
			{
				ropevec = ropedir;
			}

			// current direction
			tmpvec = curr_piece->prev_piece->origin - curr_piece->origin;
			ropelen = tmpvec.length();
         tmpvec.normalize();

			// get to dot product
			f1 = DotProduct(ropevec, tmpvec);

			if((f1 - 0.2) < dotlimit)
			{
				i1 = DotProduct(curr_piece->velocity, ropevec);
				velpart = ropevec*i1;
				if((f1 + 0.2) < dotlimit)
					f2 = (dotlimit - (f1 + 0.2))*150*strength;
				else if(f1 < dotlimit)
					f2 = (dotlimit - f1)*100*strength;
				else if((f1 - 0.2) < dotlimit)
					f2 = (dotlimit - (f1 - 0.1))*50*strength;
				else
					f2 = (dotlimit - (f1 - 0.2))*20*strength;

				if(i1 < 0)
					curr_piece->velocity -= velpart;
				curr_piece->velocity += ropevec*f2;
			}
		}

		// check if piece is wiggling
		if(curr_piece->spawnflags & PIECE_WIGGLE)
		{
			// if rope is attached, check if we still should wiggle
			if((curr_piece->spawnflags & PIECE_ATTWIGGLE) ||
				!(rope & (ROPE_ATTACHED | ROPE_ABELOW)))
			{
				curr_piece->Wiggle();
			}
		}
		curr_piece = curr_piece->next_piece;
	}
}

/*================================================================
RopeBase class | velocity setting for touching
================================================================*/

void RopeBase::SetTouchVelocity(Vector fullvel, RopePiece *touched_piece, int set_z)
{
	float tmpflt;
	RopePiece *currpiece;

	currpiece = touched_piece;
	while(currpiece->rope_base)
	{
		tmpflt = (float)currpiece->piecenum / (float)touched_piece->piecenum;
		if(set_z)
		{
			currpiece->velocity += fullvel*tmpflt;
		}
		else
		{
			currpiece->velocity.x += fullvel.x*tmpflt;
			currpiece->velocity.y += fullvel.y*tmpflt;
		}

		currpiece = currpiece->prev_piece;
	}
}

/*================================================================
RopeBase class | restrict an attached rope
================================================================*/

void RopeBase::FixAttachedRope(RopePiece *curr_base, RopePiece *curr_piece)
{
	Vector tmpvec;

	while(curr_piece)
	{
		if(curr_piece->rope == ROPE_ATTACHED)
		{
			float max, curr;

			curr_piece->setOrigin(curr_piece->attachent->origin);
			curr_piece->velocity = curr_piece->attachent->velocity;

			// check if the rope's pulled tight
			tmpvec = curr_piece->origin - curr_base->origin;
			curr = tmpvec.length();
			max = (curr_piece->piecenum - curr_base->piecenum)*piecelength;

			if(curr > max)
				StraightenRope(curr_base, curr_piece);
			else
				RestrictGrabbedRope(curr_base, curr_piece);

			if(curr_piece->next_piece)
				curr_base = curr_piece;
		}
		// nothing attached to rest of rope
		else if(!curr_piece->rope)
		{
			RestrictFreeRope(curr_piece);
			return;
		}

		curr_piece = curr_piece->next_piece;
	}
}

void RopeBase::RestrictGrabbedRope(RopePiece *fix_base, RopePiece *grabbed_piece)
{
	RopePiece *curr_piece;
	Vector ropevec;		// rope piece vector
	Vector velpart;		// velocity component moving to or away from rope piece
	float ropelen;		// length of extended rope
	float f1, f2;		// restrainment forces
	float i1, i2;		// intermediate values
	Vector tmpvec;
	trace_t trace;

	//first restrict the rope to the player
	curr_piece = grabbed_piece->prev_piece;
	while(curr_piece != fix_base)
	{
		// add in velocity from gravity
		curr_piece->velocity.z -= gravity*sv_gravity->value*level.frametime;

		ropevec = curr_piece->next_piece->origin - curr_piece->origin;
		ropelen = ropevec.length();

		// if location is beyond the rope's reach
		if (ropelen > piecelength)
		{	 
			// inertial dampener for the free rope's motion.
			curr_piece->velocity.x *= ropedampener;
			curr_piece->velocity.y *= ropedampener;

			// determine velocity component of rope vector
			i1 = DotProduct(curr_piece->velocity, ropevec);
			i2 = DotProduct(ropevec, ropevec);
			velpart = ropevec*(i1 / i2);
		
			// restrainment default force 
			f2 = (ropelen - piecelength) * 5;

			// if velocity heading is away from the rope piece
			if (i1 < 0)
			{
				if (ropelen > piecelength+1)
				{
					// remove velocity component moving away from hook
					curr_piece->velocity -= velpart;
				}
				f1 = f2;
			}
			else  // if velocity heading is towards the rope piece
			{
				if(velpart.length() < f2)
					f1 = f2 - velpart.length();
				else		
					f1 = 0;
			}

			ropevec.normalize();
			if(f1) // applies rope restrainment
				curr_piece->velocity += ropevec*f1;
		}

		// keeps piece from getting too far away.
		if (ropelen > piecelength)
		{
			ropevec.normalize();
			tmpvec = ropevec * piecelength;
			tmpvec = curr_piece->next_piece->origin - tmpvec;
			trace = G_Trace(curr_piece->next_piece->origin, mins, maxs, tmpvec, curr_piece, curr_piece->edict->clipmask, qfalse, "RopeBase::RestrictGrabbedRope");
			curr_piece->setOrigin(trace.endpos);
		}

		curr_piece = curr_piece->prev_piece;
	}

	curr_piece = curr_piece->next_piece;

	// now restrict the rope to the rope base
	while(!(curr_piece->rope & ROPE_ATTACHED))
	{
		ropevec = curr_piece->prev_piece->origin - curr_piece->origin;
		ropelen = ropevec.length();

		// if location is beyond the rope's reach
		if (ropelen > piecelength)
		{	 
			// inertial dampener to reduce exagerated motion.
			curr_piece->velocity.x *= ropedampener;
			curr_piece->velocity.y *= ropedampener;

			// determine velocity component of rope vector
			i1 = DotProduct(curr_piece->velocity, ropevec);
			i2 = DotProduct(ropevec, ropevec);
			velpart = ropevec*(i1/i2);
		
			// restrainment default force 
			f2 = (ropelen - (piecelength - 1)) * 5;

			// if velocity heading is away from the rope piece
			if (i1 < 0)
			{
				// if rope has streched a bit
				if (ropelen > piecelength+32)
				{
					// remove velocity component moving away from rope base
					curr_piece->velocity-= velpart;
				}
				f1 = f2;
			}
			else  // if velocity heading is towards the rope piece
			{
				if(velpart.length() < f2)
					f1 = f2 - velpart.length();
				else		
					f1 = 0;
			}

			ropevec.normalize();
			if(f1) // applies rope restrainment 
				curr_piece->velocity += ropevec*f1;
		}

		// keeps piece from getting too far away.
		if(ropelen > piecelength)
		{
			tmpvec = ropevec;
			tmpvec.normalize();
			tmpvec *= piecelength;
			tmpvec = curr_piece->prev_piece->origin - tmpvec;
			trace = G_Trace( curr_piece->prev_piece->origin, mins, maxs, tmpvec, curr_piece, curr_piece->edict->clipmask, qfalse, "RopeBase::RestrictGrabbedRope");
			curr_piece->setOrigin(trace.endpos);
		}

		// check if piece is wiggling
		if(curr_piece->spawnflags & PIECE_WIGGLE)
		{
			// if rope is attached, check if we still should wiggle
			if((curr_piece->spawnflags & PIECE_ATTWIGGLE) ||
				!(rope & (ROPE_ATTACHED | ROPE_ABELOW)))
			{
				curr_piece->Wiggle();
			}
		}

		curr_piece = curr_piece->next_piece;
	}
}

// for when the player is pulling the rope tight
void RopeBase::StraightenRope(RopePiece *fix_base, RopePiece *grabbed_piece)
{
	RopePiece *curr_piece;
	Vector ropevec, tmpvec;
	int ropelen = 0; //this keeps track of the length position of the current piece
	float tnum, f1, f2;
	float plength;

	//this calculates the vector along which to set the rope pieces
	ropevec = fix_base->origin - grabbed_piece->origin;
	plength = ropevec.length();
   ropevec.normalize();

	tnum = grabbed_piece->piecenum - fix_base->piecenum;
	plength /= tnum;
	curr_piece = grabbed_piece;
	while(curr_piece != fix_base)
	{
		f1 = curr_piece->piecenum - fix_base->piecenum;
		f2 = f1/tnum;
		curr_piece->velocity = grabbed_piece->velocity*f2;
		f2 = 1 - f2;
		curr_piece->velocity += fix_base->velocity*f2;
		tmpvec = grabbed_piece->origin + ropevec*ropelen;
		curr_piece->setOrigin(tmpvec);

		ropelen += plength;

		// check if piece is wiggling
		if(curr_piece->spawnflags & PIECE_WIGGLE)
		{
			// if rope is attached, check if we still should wiggle
			if((curr_piece->spawnflags & PIECE_ATTWIGGLE) ||
				!(rope & (ROPE_ATTACHED | ROPE_ABELOW)))
			{
				curr_piece->Wiggle();
			}
		}
		curr_piece = curr_piece->prev_piece;
	}
}

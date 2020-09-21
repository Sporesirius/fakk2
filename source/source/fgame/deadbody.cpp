//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/deadbody.cpp                       $
// $Revision:: 4                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 12/17/99 6:35p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/deadbody.cpp                            $
// 
// 4     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 3     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 2     9/13/99 4:22p Jimdose
// merge
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
//
// DESCRIPTION:
// Dead body

#include "deadbody.h"
#include "gibs.h"

CLASS_DECLARATION( Sentient, Deadbody, "deadbody" )
	{
      { &EV_Gib,      GibEvent },
      { NULL, NULL }
   };

void Deadbody::GibEvent
   (
   Event *ev
   )

   {
   takedamage = DAMAGE_NO;

   if ( sv_gibs->integer && !parentmode->integer )
      {
      setSolidType( SOLID_NOT );
	   hideModel();

      CreateGibs( this, health, 1.0f, 3 );
      }
   }

void CopyToBodyQueue
   (
   gentity_t *ent
   )

   {
   gentity_t *body;

	// grab a body from the queue and cycle to the next one
   body = &g_entities[ ( int )maxclients->integer + level.body_queue ];
	level.body_queue = ( level.body_queue + 1 ) % BODY_QUEUE_SIZE;

	gi.unlinkentity( ent );
	gi.unlinkentity( body );

   body->s                    = ent->s;
   body->s.number             = body - g_entities;
	body->svflags              = ent->svflags;
   body->solid                = ent->solid;
	body->clipmask             = ent->clipmask;
	body->ownerNum             = ent->ownerNum;
	body->entity->movetype     = ent->entity->movetype;
	body->entity->takedamage   = DAMAGE_YES;
   body->entity->deadflag     = DEAD_DEAD;
   body->s.renderfx           &= ~RF_DONTDRAW;
   body->entity->setOrigin( ent->entity->origin );
   body->entity->setSize(ent->mins,ent->maxs);
   body->entity->link();
//   body->entity->SetGravityAxis( ent->entity->gravaxis );
   }

void InitializeBodyQueue
	(
	void
	)

   {
	int	   	i;
	Deadbody    *body;

   if ( !LoadingSavegame && deathmatch->integer )
      {
	   level.body_queue = 0;
	   for ( i=0; i<BODY_QUEUE_SIZE ; i++ )
	      {
		   body = new Deadbody;
         body->edict->ownerNum = ENTITYNUM_NONE;
         body->edict->s.skinNum = -1;
         body->flags |= (FL_DIE_GIBS|FL_BLOOD);
	      }
      }
   }
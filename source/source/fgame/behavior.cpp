//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/behavior.cpp                       $
// $Revision:: 144                                                            $
//   $Author:: Aldie                                                          $
//     $Date:: 7/30/00 2:21p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/behavior.cpp                           $
// 
// 144   7/30/00 2:21p Aldie
// Fixed a problem in TurnTo allowing it to go forever.
// 
// 143   7/29/00 1:25p Steven
// Took out teleport sound effects (are in effects now).
// 
// 142   7/28/00 9:18p Steven
// Made a couple more fixes to Teleport.
// 
// 141   7/28/00 6:56p Steven
// Added in some teleport effects to TeleportToPosition.
// 
// 140   7/28/00 1:23p Steven
// Fixed entities origin while being dragged by the tr'angular and made player
// make lots of pain sounds when being eaten by a sucknblaugh.
// 
// 139   7/27/00 10:53p Steven
// Made tr'angular do damage over time and made dropping victim much more
// robust.
// 
// 138   7/27/00 10:31a Steven
// Added some effects when the spad body is hit by the ShockWater attack.
// 
// 137   7/26/00 6:44p Steven
// Added some more animations to not break out of for talk.
// 
// 136   7/24/00 8:35p Steven
// Added another animation not to interrupt.
// 
// 135   7/23/00 12:27p Steven
// Changed sucknlaugh to pull entities to its centroid instead of its origin
// and fixed some TeleportToPosition problems.
// 
// 134   7/22/00 8:36p Steven
// Made ghosts do a little bit more damage.
// 
// 133   7/21/00 3:44p Steven
// Fixed burrowattack stuff, improved teleports a lot, and made anything that
// gets digested extinguish fire.
// 
// 132   7/20/00 6:22p Steven
// Made jarts hurt anything that will take damage.
// 
// 131   7/19/00 5:08p Steven
// Added electric water means of death.
// 
// 130   7/18/00 4:26p Steven
// Modified which anims can not be interrupted by talking stuff a little and
// made flyclimb be able to set the speed.
// 
// 129   7/17/00 4:42p Steven
// Added some more animations the talk behavior will not interrupt.
// 
// 128   7/17/00 2:55p Steven
// Fixed it so Jart attack sets directio and position correctly so it can be
// blocked and made ghosts attackable longer and let players target them
// during this time.
// 
// 127   7/16/00 4:36p Steven
// Added new fire means of death.
// 
// 126   7/16/00 2:35p Steven
// Improved camera stuff when watching a talking actor.
// 
// 125   7/13/00 7:29p Steven
// Made entity go back to solid again after being released from the
// tr'angular.
// 
// 124   7/13/00 3:43p Steven
// Added next_think_time to GetCloseToEnemy for simple path finding.
// 
// 123   7/12/00 11:26a Steven
// Added another animation that talk will not get out of, added a
// return_to_original_location bool to investigate, and made ghost stay solid
// longer.
// 
// 122   7/11/00 7:08p Steven
// Made ghosts a little bit slower and not do as much damage.
// 
// 121   7/11/00 9:12a Steven
// Made it so turnto doesn't rely on movedir being correct.
// 
// 120   7/07/00 8:06a Steven
// Improved the investigation behavior to always look towards the noise
// position.
// 
// 119   7/05/00 2:27p Steven
// Improved fleeing behavior a lot.
// 
// 118   7/02/00 5:56p Steven
// Fixed FlyDive a little if hit something in movement and then it has moved
// out of the way when we try the trace.
// 
// 117   7/02/00 5:08p Steven
// Made it so anything in the way when a actor teleports to a specific
// location gets telefragged.
// 
// 116   7/02/00 2:45p Steven
// Fixed player getting removed when the sucknblaugh eats her.
// 
// 115   7/02/00 1:11p Steven
// Changed TeleportToPosition to use named pathnodes instead of hardcoded
// positions.
// 
// 114   6/30/00 3:08p Markd
// fixed rise animation issues
// 
// 113   6/30/00 10:45a Markd
// added MOVETYPE_STATIONARY and revamped some physics
// 
// 112   6/30/00 10:35a Steven
// Added max_pains to Pain behavior.
// 
// 111   6/28/00 4:55p Aldie
// Added a MOD
// 
// 110   6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 109   6/23/00 4:54p Steven
// Removed a chatter function call.
// 
// 108   6/21/00 5:28p Steven
// Improved the Digest behavior (fixed range a little, made gibs look better
// when spit out, and made it chew a little longer).
// 
// 107   6/21/00 4:22p Steven
// Took out some chatter stuff from the idle behavior and moved the direction
// to fly in the Circle behavior to the args.
// 
// 106   6/15/00 6:55p Steven
// Added moving head while talking stuff.
// 
// 105   6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 104   6/13/00 3:06p Steven
// Fixed a problem in the Shock behavior where a beam was being referenced
// after it had been freed.
// 
// 103   6/07/00 5:34p Steven
// Made it so actor would only try to return from investigating for so long,
// added TeleportToPosition and Levitate behaviors.
// 
// 102   6/06/00 2:36p Steven
// Made GetCloseToEnemy not be able to use_nearest_node.
// 
// 101   6/05/00 3:41p Steven
// Adde GotoDeadEnemy.
// 
// 100   6/05/00 12:16p Markd
// fixed sound bug
// 
// 99    6/03/00 5:23p Steven
// Made digest behavior spit out gibs instead of the dead creature.
// 
// 98    6/01/00 5:47p Steven
// Made ghost attack hit a little easier.
// 
// 97    5/27/00 2:31p Steven
// Added FlyCloseToPlayer, added a direction to the shock attack, made the
// actor turn immediately towards the enemy after a teleport, and improved the
// ghost attack a little.
// 
// 96    5/24/00 4:08p Steven
// Added a forever variable to the HeadWatch behavior.
// 
// 95    5/20/00 4:46p Steven
// Improved the Shock behavior.
// 
// 94    5/11/00 11:11a Steven
// Improved the shock attack behaviors a little.
// 
// 93    5/06/00 3:00p Steven
// Added speed to FlyCloseToEnemy and fixed actor's getting stuck on top of
// the player.
// 
// 92    5/05/00 6:23p Steven
// Made it so fire would not cause constant pain in the pain behavior.
// 
// 91    5/05/00 2:14p Steven
// Took out one of the sounds in GhostAttack.
// 
// 90    5/04/00 4:13p Steven
// Fixed the BurrowAttack not hitting triggers and hard coded the BurrowAttack
// to start at a certain height to prevent height errors.
// 
// 89    5/03/00 12:10p Steven
// Made it so the ghost bounces off shields if blocked.
// 
// 88    5/03/00 11:27a Steven
// Added some sounds to the ghost attack and added the spooky ghost attack.
// 
// 87    5/02/00 5:14p Steven
// Fixed the ghost attack so that MeleeAttack could tell what direction the
// attack was coming from.
// 
// 86    5/02/00 3:14p Steven
// Added player watching actors that talk to her.
// 
// 85    4/28/00 5:40p Steven
// Added use_last_known_pos to TurnToEnemy and BurrowAttack and made it so the
// burrowattack could hit solid entities as long as it isn't the world.
// 
// 84    4/25/00 6:19p Steven
// Made it so the digest attack wouldn't eat stationary sentients and tweaked
// the range a little.
// 
// 83    4/25/00 4:21p Steven
// Fixed the ghost spinning in circles around their attack target.
// 
// 82    4/25/00 10:53a Steven
// Fixed a place where the ghost would fade all of the way back in.
// 
// 81    4/25/00 10:12a Steven
// Lots of improvements to the GhostAttack behavior.
// 
// 80    4/24/00 3:12p Steven
// Added allow fail to chase.
// 
// 79    4/20/00 3:37p Steven
// Fixed a bug in HeadWatch, was never getting the current_head_angles
// correctly.
// 
// 78    4/20/00 11:34a Steven
// Changed a range in the ShockWater behavior.
// 
// 77    4/15/00 5:42p Steven
// Made it so the amount of time the sucknblaugh chews on its victim is
// determined by its weight.
// 
// 76    4/15/00 3:39p Steven
// Made it so the pain animation will randomly choose between all available
// pain animations not just the first 2.
// 
// 75    4/13/00 5:34p Steven
// Added the Teleport behavior and the GhostAttack behavior.
// 
// 74    4/12/00 2:39p Steven
// Fixed TorsoTurn turning in circles forever problem (always trying to catch
// up to target).
// 
// 73    4/11/00 4:01p Steven
// Added attack_min_height to MeleeAttack.
// 
// 72    4/08/00 3:53p Steven
// Made headwatch snap head back to the forward position if lost the entity we
// were watching or if resetting the head and the behavior is stopped, took
// out the walking in PickupEntity, and set the actors animation to idle after
// done throwing an entity.
// 
// 71    4/05/00 6:18p Steven
// Added dirt to where the Vymish Mama's burrow legs come out of the ground.
// 
// 70    4/04/00 6:55p Steven
// Made it so HeadWatch doesn't snap to forward at end and if it doesn't have
// an entity to watch moves head back to forward position using max_speed.
// 
// 69    4/01/00 2:39p Steven
// Made it so actor can fly clockwise or counter-clockwise in FlyCircle.
// 
// 68    4/01/00 2:00p Steven
// Added a forever flag to GetCloseToEnemy.
// 
// 67    3/31/00 5:32p Steven
// Made some changes to the Digest behavior so that I could get projectils and
// bullets to bounce off of the Sucknblaugh.
// 
// 66    3/31/00 4:58p Steven
// Changed TurnToEnemy so that if actor is really close don't bother turning
// any more.
// 
// 65    3/30/00 2:03p Steven
// More work on TorsoTurn.
// 
// 64    3/28/00 6:49p Steven
// Lots of improvements to TorsoTurn.
// 
// 63    3/24/00 6:33p Steven
// Fixed an animation issue, made lots of optimizations to flying behaviors
// and ChooseRandomDirection.
// 
// 62    3/20/00 6:08p Steven
// Made sure GetCloseToEnemy gets animdone events (so actor is informed).
// 
// 61    3/17/00 11:49a Steven
// Added jumping stuff.
// 
// 60    3/14/00 12:06p Steven
// Added walkwatch stuff.
// 
// 59    3/11/00 11:36a Steven
// Moved all actor booleans to 1 actor flags variable and made the stopping
// condition for TurnToEnemy a little better.
// 
// 58    3/08/00 6:42p Steven
// Worked on the TorsoTurn behavior some more.
// 
// 57    3/07/00 5:23p Steven
// Tweaked BurrowAttack a little to not spawn in so many dirt and water
// effects.
// 
// 56    3/07/00 11:51a Steven
// Made lots of tweaks to the CircleEnemy behavior.
// 
// 55    3/04/00 11:49a Steven
// Improved the FlyCircle, FlyDive, and FlyClimb behaviors.
// 
// 54    3/03/00 5:26p Steven
// Added fast_bullet stuff.
// 
// 53    3/02/00 11:02a Steven
// Added some tweaks to the digest behavior.
// 
// 52    2/26/00 11:22a Steven
// Added partial immobile flag.
// 
// 51    2/24/00 7:07p Steven
// Made talk so it would not stand up if already sitting and made it so the
// actor always tries to face whoever its talking to.
// 
// 50    2/24/00 5:26p Steven
// Added a max speed parm to head watch and made sure playanim removes any
// anim done events still around when it ends.
// 
// 49    2/23/00 5:19p Steven
// Improved the Wander behavior and improved the ChooseRandomDirection
// function.
// 
// 48    2/23/00 11:57a Steven
// Moved utility behaviors to actor and improved BurrowAttack attack.
// 
// 47    2/21/00 7:00p Steven
// Added a TorsoTurn behavior.
// 
// 46    2/21/00 11:09a Steven
// Fixed some TurnTo issues.
// 
// 45    2/17/00 5:42p Steven
// Moved NearestNode stuff out of Investigate to Actor.
// 
// 44    2/16/00 6:04p Steven
// Tweaked the investigate behavior a lot.
// 
// 43    2/16/00 10:43a Steven
// Added a Pain behavior, made an option for FlyWander to make the actor try
// to fly upwards, and improved the Investigate behavior.
// 
// 42    2/11/00 6:41p Steven
// Improved headwatch a little and added pickup/throw.
// 
// 41    2/09/00 6:48p Steven
// Made it so an actor would stay in talk mode until the player went far
// enough away.
// 
// 40    2/07/00 6:45p Steven
// Made it so the FlyCloseToEnemy behavior doesn't choose a new goal so often.
// 
// 39    2/04/00 1:55p Steven
// Added the talk behavior.
// 
// 38    2/02/00 1:38p Steven
// Added turning animations to TurnTo, added the HeadWatch behavior, cleaned
// up flying code a little more, and improved the Suicide, DragEnemy, and
// ShockWater behaviors.
// 
// 37    1/29/00 5:28p Steven
// Improoved the BurrowAttack and DragEnemy behaviors.
// 
// 36    1/27/00 2:53p Steven
// Improved a lot of the flying code.
// 
// 35    1/26/00 9:51a Steven
// Added a usefult debug message to GotoPathNode.
// 
// 34    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 33    1/21/00 6:45p Steven
// Made flee use chase instead of FollowPath.
// 
// 32    1/19/00 7:08p Steven
// Fixed speed of flying creatures and tweaked BurrowAttack behavior a little.
// 
// 31    1/19/00 12:11p Steven
// Fixed AimAndShoot behavior and improved the TurnToEnemy and BurrowAttack
// behaviors.
// 
// 30    1/14/00 7:36p Steven
// Improved TurnToEnemy behavior a little.
// 
// 29    1/14/00 5:06p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 28    1/14/00 5:02p Steven
// Added gotonextstage and burrowattack behaviors.
// 
// 27    1/13/00 7:07p Steven
// Lots and lots of cleanup.
// 
// 26    1/07/00 8:12p Jimdose
// cleaning up unused code
// 
// 25    1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 24    1/06/00 6:49p Steven
// Cleaned up GetCloseToEnemy.
// 
// 23    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 22    1/05/00 6:43p Steven
// Fixed the start and end point being backwards in a trace command.
// 
// 21    1/05/00 3:07p Jimdose
// fixed inverted pitch in Aim::Evaluate
// 
// 20    12/22/99 5:13p Steven
// Fixed some animation issues, some general clean up, and removed
// FemaleLympAttack.
// 
// 19    12/17/99 5:51p Steven
// Made some temporary fixes to aiming behaviors and added the following
// behaviors : TurnTowardsEnemy, FlyCircle, FlyDive, and FlyClimb.
// 
// 18    12/01/99 3:43p Steven
// Added a land behavior for flying creatures.
// 
// 17    11/24/99 11:05a Steven
// More work on flying.
// 
// 16    11/19/99 2:05p Steven
// Took out some unused code.
// 
// 15    11/19/99 11:33a Steven
// Added new behaviors: CircleEnemy, ShockWater, Shock, and CircleAttack.
// 
// 14    11/12/99 6:24p Steven
// Made state flags available to other part entities.
// 
// 13    11/10/99 6:11p Steven
// Added the FlyCloseToEnemy behavior.
// 
// 12    10/28/99 6:06p Steven
// Improved the drag behavior.
// 
// 11    10/27/99 10:27a Steven
// Added GetNearestEnemy behavior and added more to the DragEnemy behavior.
// 
// 10    10/19/99 7:52p Markd
// Removed three part model system
// 
// 9     10/19/99 7:10p Steven
// Lots of AI work.
// 
// 8     10/11/99 7:50p Steven
// Cleanup.
// 
// 7     10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 6     9/29/99 11:52a Markd
// removed some unused enums and variables form shared headers between cgame
// and fgame
// 
// 5     9/28/99 7:24p Steven
// Event formatting.
// 
// 4     9/22/99 4:47p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 3     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 26    9/02/99 11:33p Jimdose
// fixed bug with sucknblaughs targeting
// 
// 25    9/02/99 4:22p Steven
// Changed when sucknblaugh is solid and when it is not and fixed some aiming
// issues in AimAndShoot behavior.
// 
// 24    9/01/99 8:16p Steven
// Fixed a typo and setting the anim back to idle after the AimAndShoot
// behavior.
// 
// 23    8/31/99 9:21p Steven
// Added fall anim to jump behavior and tweaked digest behavior a little.
// 
// 22    8/31/99 2:43p Steven
// Fixed some spin behavior bugs.
// 
// 21    8/28/99 7:05p Steven
// Made it so the speed of the spinning for the spinner plant was a parameter.
// 
// 20    8/28/99 11:42a Steven
// Added some spinning plant stuff.
// 
// 19    8/27/99 5:05p Steven
// Worked on digest behavior, added spin, and optimized some of the movement.
// 
// 18    8/24/99 11:25a Steven
// Made it so Sucknblaughs don't eat dead creatures.
// 
// 17    8/18/99 3:29p Jimdose
// added cylindrical collision detection
// 
// 16    8/18/99 3:22p Steven
// Added to Digest behavior.
// 
// 15    8/17/99 4:59p Steven
// New digest behavior for the Sucknblaugh plant.
// 
// 14    8/16/99 10:29a Steven
// More general work on AI.
// 
// 13    8/11/99 7:24p Steven
// Redid the AimAndShoot behavior temporarily.
// 
// 12    8/11/99 5:56p Steven
// More general AI work.
// 
// 11    8/06/99 6:39p Aldie
// Started removing concept of currentWeapon
// 
// 10    8/05/99 9:14a Steven
// New AI stuff.
// 
// 9     7/07/99 11:25a Steven
// Added some stuff on the sector pathfinding approach.
//
//
// DESCRIPTION:
// Behaviors used by the AI.
//

#include "g_local.h"
#include "behavior.h"
#include "actor.h"
#include "doors.h"
#include "object.h"
#include "explosion.h"
#include "weaputils.h"
#include "player.h"

Event EV_Behavior_Args
	( 
	"args",
	EV_DEFAULT,
	"SSSSSS",
	"token1 token2 token3 token4 token5 token6",
	"Gives the current behavior arguments."
	);
Event EV_Behavior_AnimDone
	( 
	"animdone",
	EV_DEFAULT,
	NULL,
	NULL,
	"Tells the behavior that the current animation is done, "
	"it is not meant to be called from script."
	);

Vector ChooseRandomDirection( Actor &self, Vector previousdir, float *time, int disallowcontentsmask, qboolean usepitch );

/****************************************************************************

  Behavior Class Definition

****************************************************************************/

CLASS_DECLARATION( Listener, Behavior, NULL )
	{
		{ NULL, NULL }
	};

Behavior::Behavior()
	{
	}

void Behavior::ShowInfo
	(
	Actor &self
	)

	{
   if ( movegoal )
      {
      gi.Printf( "movegoal: ( %f, %f, %f ) - '%s'\n",
         movegoal->origin.x, movegoal->origin.y, movegoal->origin.z, movegoal->targetname.c_str() );
      }
   else
      {
      gi.Printf( "movegoal: NULL\n" );
      }
	}

void Behavior::Begin
	(
	Actor &self
	)

	{
	}

qboolean	Behavior::Evaluate
	(
	Actor &self
	)

	{
	return false;
	}

void Behavior::End
	(
	Actor &self
	)

	{
	}



/****************************************************************************
*****************************************************************************

  General behaviors

*****************************************************************************
****************************************************************************/



/****************************************************************************

  Idle Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Idle, NULL )
	{
		{ NULL, NULL }
	};

void Idle::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nnexttwitch : %f\n", nexttwitch );
	}

void Idle::Begin
	(
	Actor &self
	)

	{
	nexttwitch = level.time + 10 + G_Random( 30 );
	}

qboolean	Idle::Evaluate
	(
	Actor &self
	)

	{
	if ( self.currentEnemy )
		{
		return true;
		}

	if ( nexttwitch < level.time )
		{
		self.chattime += 10;
		self.AddStateFlag( STATE_FLAG_TWITCH );
		return true;
		}
	else
		{
		//self.Chatter( "snd_idle", 1 );
		}

	return true;
	}

void Idle::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  Pain Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Pain, NULL )
	{
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ NULL, NULL }
	};

void Pain::SetPainAnim
	(
	Actor &self,
	int new_pain_type,
	int new_anim_number
	)

	{
	str anim_name;

	// Determine which pain type to play

	if ( new_pain_type == PAIN_SMALL )
		anim_name = "pain_small";
	else
		anim_name = "pain";

	// Try to find the correct anim to play

	anim_name += new_anim_number;

	if ( !self.HasAnim( anim_name.c_str() ) )
		{
		if ( new_pain_type == PAIN_SMALL )
			anim_name = "pain_small1";
		else
			anim_name = "pain1";

		pain_anim_number = 1;
		}

	anim_done = false;

	// Play the animation if we can
	
	if ( !self.HasAnim( anim_name.c_str() ) )
		anim_done = true;
	else
		self.SetAnim( anim_name.c_str(), EV_Actor_NotifyBehavior );
	}

int Pain::GetNumberOfPainAnims
	(
	Actor &self,
	int new_pain_type
	)

	{
	str anim_name;
	str real_anim_name;
	int i;


	// Determine base animation name

	if ( new_pain_type == PAIN_SMALL )
		anim_name = "pain_small";
	else
		anim_name = "pain";

	// Find how many pain animations we have

	for( i = 1 ; i < 10 ; i++ )
		{
		real_anim_name = anim_name + i;

		if ( !self.HasAnim( real_anim_name.c_str() ) )
			return( i - 1 );
		}

	return 9;
	}

void Pain::Begin
	(
	Actor &self
	)

	{
	str anim_name;
	int num_pain_anims;

	num_pain_anims = GetNumberOfPainAnims( self, self.pain_type );

	pain_anim_number = G_Random( num_pain_anims ) + 1;

	// Figure out which type of pain to do

	if ( self.pain_type == PAIN_SMALL )
		SetPainAnim( self, PAIN_SMALL, pain_anim_number );
	else
		SetPainAnim( self, PAIN_BIG, pain_anim_number );

	current_pain_type = self.pain_type;
	number_of_pains   = 1;

	// Make sure we don't have pain any more

	self.state_flags &= ~STATE_FLAG_SMALL_PAIN;
	self.state_flags &= ~STATE_FLAG_IN_PAIN;

	max_pains = G_Random( 4 ) + 4;
	}

void Pain::AnimDone
	( 
	Event *ev
	)
	{
	anim_done = true;
	}

qboolean	Pain::Evaluate
	(
	Actor &self
	)

	{
	str anim_name;

	if ( self.state_flags & STATE_FLAG_SMALL_PAIN )
		{
		// See if we should play another pain animation

		if ( self.means_of_death != MOD_FIRE && self.means_of_death != MOD_ON_FIRE && self.means_of_death != MOD_FIRE_BLOCKABLE )
			{
			if ( self.pain_type == PAIN_SMALL && current_pain_type == PAIN_SMALL && number_of_pains < max_pains )
				{
				pain_anim_number++;

				number_of_pains++;

				SetPainAnim( self, PAIN_SMALL, pain_anim_number );
				}
			else if ( self.pain_type == PAIN_BIG )
				{
				pain_anim_number++;

				current_pain_type = PAIN_BIG;

				SetPainAnim( self, PAIN_BIG, pain_anim_number );
				}
			}

		// Reset pain stuff

		self.state_flags &= ~STATE_FLAG_SMALL_PAIN;
		self.state_flags &= ~STATE_FLAG_IN_PAIN;
		}

	// If the pain animation has finished, then we are done

	if ( anim_done )
		return false;

	return true;
	}

void Pain::End
	(
	Actor &self
	)

	{
	self.bullet_hits = 0;
	}

/****************************************************************************

  Watch Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Watch, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

Watch::Watch()
	{
	turn_speed = 360;
	}

void Watch::SetArgs
	(
	Event *ev
	)

	{
	turn_speed = ev->GetFloat( 1 );
	}

void Watch::Begin
	(
	Actor &self
	)

	{
	ent_to_watch = self.currentEnemy;

	old_turn_speed = self.turnspeed;
	self.turnspeed = turn_speed;
	seek.Begin( self );
	}

qboolean	Watch::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;

	if ( !ent_to_watch )
		return false;

	if ( self.IsEntityAlive( ent_to_watch ) )
		{
		self.angles.AngleVectors( &dir );

		seek.SetTargetPosition( ent_to_watch->centroid );
		seek.SetTargetVelocity( vec_zero );
		seek.SetPosition( self.centroid );
		seek.SetDir( dir );
		seek.Evaluate( self );

		self.Accelerate( seek.steeringforce );
		}

	return true;
	}

void Watch::End
	(
	Actor &self
	)

	{
	self.turnspeed = old_turn_speed;
	seek.End( self );
	}

/****************************************************************************

  Turn Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Turn, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

Turn::Turn()
	{
	turn_speed = 5;
	}

void Turn::SetArgs
	(
	Event *ev
	)

	{
	turn_speed = ev->GetFloat( 1 );
	}

void Turn::Begin
	(
	Actor &self
	)

	{
	}

qboolean	Turn::Evaluate
	(
	Actor &self
	)

	{
	self.angles[YAW] += turn_speed;

	self.setAngles( self.angles );

	return true;
	}

void Turn::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  Aim Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Aim, NULL )
	{		
		{ NULL, NULL }
	};

void Aim::SetTarget
	(
	Entity *ent
	)

	{
	target = ent;
	}

void Aim::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nseek:\n" );
   seek.ShowInfo( self );
   if ( target )
      {
      gi.Printf( "\ntarget : #%d '%s'\n", target->entnum, target->targetname.c_str() );
      }
   else
      {
      gi.Printf( "\ntarget : NULL\n" );
      }
	}

void Aim::Begin
	(
	Actor &self
	)

	{
	seek.Begin( self );
	}

qboolean	Aim::Evaluate
	(
	Actor &self
	)

	{
   Vector dir;
   Vector ang;
   Vector pos;

	if ( !target )
		{
		return false;
		}

   //
   // get my gun pos
   //

	// Fixme ?
   //pos = self.GunPosition();
   //ang = self.MyGunAngles( pos, false );
	pos = self.centroid;
	ang = self.angles;
   ang.AngleVectors( &dir, NULL, NULL );

   seek.SetTargetPosition( target->centroid );
	seek.SetTargetVelocity( target->velocity );
	seek.SetPosition( self.centroid );
   seek.SetDir( dir );
	seek.SetMaxSpeed( 1400 + skill->value * 600 );
	seek.Evaluate( self );

	// Fixme?
	/* if ( ( fabs( seek.steeringforce.y ) > 5 ) && ( self.enemyRange > RANGE_MELEE ) )
		{
		seek.steeringforce.y *= 2;
		} */

	self.Accelerate( seek.steeringforce );
	if ( seek.steeringforce.y < 0.25f )
		{
		// dead on
		return false;
		}

	return true;
	}

void Aim::End
	(
	Actor &self
	)

	{
	seek.End( self );
	}

/****************************************************************************

  TurnTo Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, TurnTo, NULL )
	{
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ NULL, NULL }
	};

TurnTo::TurnTo()
	{
	dir = Vector( 1, 0, 0 );
	mode = 0;
	ent = NULL;
   yaw = 0;
	anim_done = true;
	}

void TurnTo::SetDirection
	(
	float yaw
	)

	{
	Vector ang;

	ang = Vector( 0, yaw, 0 );
	this->yaw = anglemod( yaw );
	ang.AngleVectors( &dir, NULL, NULL );
	dir *= 100;
	mode = 1;
	}

void TurnTo::SetTarget
	(
	Entity *ent
	)

	{
	this->ent = ent;
	mode = 2;
	}

void TurnTo::AnimDone
	(
	Event *ev
	)

	{
	anim_done = true;
	}

void TurnTo::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nseek:\n" );
   seek.ShowInfo( self );

   if ( ent )
      {
      gi.Printf( "\nent: #%d '%s'\n", ent->entnum, ent->targetname.c_str() );
      }
   else
      {
      gi.Printf( "\nent: NULL\n" );
      }

   gi.Printf( "dir: ( %f, %f, %f )\n", dir.x, dir.y, dir.z );
   gi.Printf( "yaw: %f\n", yaw );
   gi.Printf( "mode: %d\n", mode );
	}

void TurnTo::Begin
	(
	Actor &self
	)

	{
	self.SetAnim( "idle" );
	seek.Begin( self );
	}

qboolean	TurnTo::Evaluate
	(
	Actor &self
	)

	{
	Vector delta;
	float ang;
	str anim_name;
	Vector forward;


	switch( mode )
		{
		case 1 :
			ang = angledist( yaw - self.angles.yaw() );
			if ( fabs( ang ) < 1 )
				{
				self.Accelerate( Vector( 0, ang, 0 ) );

				// If turned all the way wait for animation to finish

				if ( anim_done || self.animname == "idle" )
					return false;
				else
					return true;
				}

         seek.SetTargetPosition( self.origin + dir );
			seek.SetTargetVelocity( vec_zero );
			break;

		case 2 :
			if ( !ent )
				{
				return false;
				}

         delta = ent->origin - self.origin;
			yaw = delta.toYaw();

         seek.SetTargetPosition( ent->origin );
			seek.SetTargetVelocity( vec_zero );
			break;

		default :
			return false;
		}

   seek.SetPosition( self.origin );

	self.angles.AngleVectors( &forward );
	seek.SetDir( forward );
	//seek.SetDir( self.movedir );

	seek.SetMaxSpeed( self.movespeed );
	seek.Evaluate( self );

	if ( seek.steeringforce[YAW] > 1 )
		{
		anim_name = "turn_left";
		anim_done = false;
		}
	else if ( seek.steeringforce[YAW] < -1 )
		{
		anim_name = "turn_right";
		anim_done = false;
		}
	else if ( anim_done )
		{
		anim_name = "idle";
		}
	else
		{
		anim_name = self.animname;
		}

	if ( gi.Anim_NumForName( self.edict->s.modelindex, anim_name.c_str() ) != -1 )
		{
		if ( anim_name != self.animname )
			self.SetAnim( anim_name.c_str(), EV_Actor_NotifyBehavior );	
		}
	else
		{
		anim_done = true;
		}

	self.Accelerate( seek.steeringforce );

	return true;
	}

void TurnTo::End
	(
	Actor &self
	)

	{
	seek.End( self );
	self.SetAnim( "idle" );
	}

/****************************************************************************

  HeadWatch Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, HeadWatch, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

HeadWatch::HeadWatch()
	{
	max_speed = 10;
	forever = true;
	}

void HeadWatch::SetArgs
	(
	Event *ev
	)

	{
	ent_to_watch = ev->GetEntity( 1 );

	if ( ev->NumArgs() > 1 )
		max_speed = ev->GetFloat( 2 );

	if ( ev->NumArgs() > 2 )
		forever = ev->GetBoolean( 3 );
	}


void HeadWatch::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void HeadWatch::Begin
	(
	Actor &self
	)

	{
	self.SetControllerTag( ACTOR_HEAD_TAG, gi.Tag_NumForName( self.edict->s.modelindex, "Bip01 Head" ) );

	current_head_angles = self.GetControllerAngles( ACTOR_HEAD_TAG );

	self.SetActorFlag( ACTOR_FLAG_TURNING_HEAD, true );
	}

qboolean	HeadWatch::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;
	Vector angles;
	int tag_num;
	Vector tag_pos;
	Vector angles_diff;
	Vector watch_position;
	Actor *act = NULL;
	Vector change;

	if ( ent_to_watch )
		{
		tag_num = gi.Tag_NumForName( self.edict->s.modelindex, "Bip01 Head" );

		if ( tag_num < 0 )
			return false;

		self.GetTag( "Bip01 Head", &tag_pos );

		if ( ent_to_watch->isSubclassOf( Actor ) )
			act = (Actor *)(Entity *)ent_to_watch;

		if ( act && act->watch_offset != vec_zero )
			{
			MatrixTransformVector( act->watch_offset, ent_to_watch->orientation, watch_position );
			watch_position += ent_to_watch->origin;
			}
		else
			{
			watch_position = ent_to_watch->centroid;
			}

		dir = watch_position - tag_pos;
		angles = dir.toAngles();

		angles_diff = angles - self.angles;
		}
	else
		{
		angles_diff = vec_zero;
		}

	angles_diff[YAW]   = AngleNormalize180( angles_diff[YAW] );
	angles_diff[PITCH] = AngleNormalize180( angles_diff[PITCH] );

	// Make sure we don't turn neck too far

	if ( angles_diff[YAW] < -80 )
		angles_diff[YAW] = -80;
	else if ( angles_diff[YAW] > 80 )
		angles_diff[YAW] = 80;

	if ( angles_diff[PITCH] < -45 )
		angles_diff[PITCH] = -45;
	else if ( angles_diff[PITCH] > 45 )
		angles_diff[PITCH] = 45;

	angles_diff[ROLL] = 0;

	// Make sure we don't change our head angles too much at once

	change = angles_diff - current_head_angles;

	if ( change[YAW] > max_speed )
		angles_diff[YAW] = current_head_angles[YAW] + max_speed;
	else if ( change[YAW] < -max_speed )
		angles_diff[YAW] = current_head_angles[YAW] - max_speed;

	if ( change[PITCH] > max_speed )
		angles_diff[PITCH] = current_head_angles[PITCH] + max_speed;
	else if ( change[PITCH] < -max_speed )
		angles_diff[PITCH] = current_head_angles[PITCH] - max_speed;

	self.SetControllerAngles( ACTOR_HEAD_TAG, angles_diff );
	self.real_head_pitch = angles_diff[PITCH];

	current_head_angles = angles_diff;

	if ( !ent_to_watch && current_head_angles == vec_zero )
		return false;

	if ( !forever && change[YAW] < max_speed && change[YAW] > -max_speed && change[PITCH] < max_speed && change[PITCH] > -max_speed )
		return false;
	
	return true;
	}

void HeadWatch::End
	(
	Actor &self
	)

	{
	// Snap head back into position if we have lost our target or we are doing a resethead

	if ( !ent_to_watch )
		{
		self.SetControllerAngles( ACTOR_HEAD_TAG, vec_zero );
		self.real_head_pitch = 0;
		}

	self.SetActorFlag( ACTOR_FLAG_TURNING_HEAD, false );
	}

/****************************************************************************

  TorsoTurn Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, TorsoTurn, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void TorsoTurn::SetArgs
	(
	Event *ev
	)

	{
	turn_towards_enemy = ev->GetInteger( 1 );
	speed              = ev->GetFloat( 2 );
	forever            = ev->GetInteger( 3 );

	if ( ev->NumArgs() > 3 )
		tag_name = ev->GetString( 4 );

	if ( ev->NumArgs() > 4 )
		tolerance = ev->GetFloat( 5 );
	else
		tolerance = 0;
	}


void TorsoTurn::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void TorsoTurn::Begin
	(
	Actor &self
	)

	{
	Vector controller_angles;

	self.SetControllerTag( ACTOR_TORSO_TAG, gi.Tag_NumForName( self.edict->s.modelindex, "Bip01 Spine1" ) );

	controller_angles = self.GetControllerAngles( ACTOR_TORSO_TAG );

	current_yaw   = controller_angles[YAW];
	current_pitch = controller_angles[PITCH];
	}

qboolean	TorsoTurn::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;
	Vector angles;
	int tag_num;
	float yaw_diff;
	float pitch_diff;
	Vector new_angles;
	float yaw_change;
	float pitch_change;
	Vector tag_pos;
	Vector tag_forward;
	Vector tag_angles;


	tag_num = gi.Tag_NumForName( self.edict->s.modelindex, "Bip01 Spine1" );

	if ( tag_num < 0 )
		return false;

	// Determine the angle we want to go to

	if ( turn_towards_enemy )
		{
		if ( !self.currentEnemy )
			return false;

		if ( tag_name.length() )
			{
			self.GetTag( tag_name.c_str(), &tag_pos, &tag_forward );
			tag_angles = tag_forward.toAngles();
			dir = self.currentEnemy->centroid - tag_pos;
			}
		else
			{
			dir = self.currentEnemy->centroid - self.centroid;
			}

		angles = dir.toAngles();

		yaw_diff   = AngleNormalize180( angles[YAW] - self.angles[YAW] );
		pitch_diff = AngleNormalize180( angles[PITCH] - self.angles[PITCH] );
		}
	else
		{
		yaw_diff   = 0;
		pitch_diff = 0;
		}

	// Determine the angle change

	yaw_change   = AngleNormalize180( yaw_diff - current_yaw );
	pitch_change = AngleNormalize180( pitch_diff - current_pitch );

	if ( tolerance && yaw_change < tolerance && yaw_change > -tolerance && pitch_change < tolerance && pitch_change > -tolerance )
		{
		if ( forever )
			return true;
		else
			return false;
		}

	// Make sure we don't change our torso angles too much at once

	if ( yaw_change > speed )
		yaw_diff = current_yaw + speed;
	else if ( yaw_change < -speed )
		yaw_diff = current_yaw - speed;

	if ( pitch_change > speed )
		pitch_diff = current_pitch + speed;
	else if ( yaw_change < -speed )
		pitch_diff = current_pitch - speed;

	// Determine our new angles

	new_angles[YAW]   = yaw_diff;
	new_angles[PITCH] = pitch_diff;
	new_angles[ROLL]  = 0;

	// Make sure we don't turn too far

	//if ( new_angles[YAW] > 120 || new_angles[YAW] < -120 )
	//	return false;

	if ( new_angles[PITCH] > 45 || new_angles[PITCH] < -45 )
		return false;

	// Set our new angles

	self.SetControllerAngles( ACTOR_TORSO_TAG, new_angles );

	current_yaw = yaw_diff;
	current_pitch = pitch_diff;

	// See if we are turned the correct direction now

	if ( !forever && (yaw_change < speed) && (yaw_change > -speed) && (pitch_change < speed) && (pitch_change > -speed) )
		return false;
	
	return true;
	}

void TorsoTurn::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  GotoPathNode Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, GotoPathNode, NULL )
	{
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

GotoPathNode::GotoPathNode()
	{
	usevec = false;
	movegoal = NULL;
	goal = vec_zero;
	goalent = NULL;
	}

void GotoPathNode::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	if ( ev->IsVectorAt( 2 ) )
		{
		goal = ev->GetVector( 2 );
		usevec = true;
		}
	else
		{
      usevec = false;
		movegoal = AI_FindNode( ev->GetString( 2 ) );
		if ( !movegoal )
			{
			goalent = ev->GetEntity( 2 );
			}
		}

	if ( ev->NumArgs() > 2 )
		entity_to_watch = ev->GetEntity( 3 );
	}

void GotoPathNode::AnimDone
	(
	Event *ev
	)

	{
	turnto.ProcessEvent( EV_Behavior_AnimDone );
	}

void GotoPathNode::SetGoal
	(
	PathNode *node
	)

	{
	usevec = false;
	movegoal = node;
	}

void GotoPathNode::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nturnto:\n" );
   turnto.ShowInfo( self );

   gi.Printf( "\nchase:\n" );
   chase.ShowInfo( self );

   gi.Printf( "\nstate: %d\n", state );
   gi.Printf( "usevec: %d\n", usevec );
   gi.Printf( "time: %f\n", time );
   gi.Printf( "anim: %s\n", anim.c_str() );

   if ( goalent )
      {
      gi.Printf( "\ngoalent: #%d '%s'\n", goalent->entnum, goalent->targetname.c_str() );
      }
   else
      {
      gi.Printf( "\ngoalent: NULL\n" );
      }

   gi.Printf( "goal: ( %f, %f, %f )\n", goal.x, goal.y, goal.z );
	}

void GotoPathNode::Begin
	(
	Actor &self
	)

	{
	Event *ev;

	state = 0;
	chase.Begin( self );
	turnto.Begin( self );
	if ( goalent )
		{
		chase.SetTarget( goalent );
		}
	else if ( movegoal )
      {
      chase.SetGoal( movegoal );
      }
   else
		{
		chase.SetGoalPos( goal );
		}

   // don't check for new paths as often
   chase.SetPathRate( 4 );

	chase.AllowFail( true );

	if ( anim.length() )
		{
		self.SetAnim( anim );
		}

	// Setup head watch stuff

	head_watch.Begin( self );

	ev = new Event( EV_Behavior_Args );
	ev->AddEntity( entity_to_watch );
	head_watch.ProcessEvent( ev );
	}

qboolean	GotoPathNode::Evaluate
	(
	Actor &self
	)

	{
	float yaw;

	if ( !usevec && !goalent && !movegoal )
		{
		gi.DPrintf( "GotoPathNode::No goal\n" );
		return false;
		}

	if ( entity_to_watch )
		head_watch.Evaluate( self );

	switch( state )
		{
		case 0 :
			if ( chase.Evaluate( self ) )
				{
				break;
				}

			state = 1;
			self.SetAnim( "idle" );

			// cascade down to case 1
		case 1 :
			if ( !movegoal )
				{
				return false;
				}

			if ( movegoal->setangles )
				{
            yaw = movegoal->angles.yaw();
				turnto.SetDirection( yaw );
				if ( turnto.Evaluate( self ) )
					{
					break;
					}
				}

			if ( movegoal->animname == "" )
				{
            self.SetAnim( "idle" );
				return false;
				}

			self.SetAnim( movegoal->animname, EV_Actor_FinishedBehavior );
			state = 2;
			break;

		case 2 :
			break;
		}

	return true;
	}

void GotoPathNode::End
	(
	Actor &self
	)

	{
	chase.End( self );
	head_watch.End( self );
	}

/****************************************************************************

  Flee Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Flee, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void Flee::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );
	}

void Flee::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nchase:\n" );
   chase.ShowInfo( self );
	}

void Flee::Begin
	(
	Actor &self
	)

	{
	if ( anim.length() )
		{
		self.SetAnim( anim );
		}

	chase.Begin( self );
	FindFleeNode( self );
	}

void Flee::FindFleeNode
	(  
	Actor &self
	)
	{
	int i;
	PathNode *start_node;
	pathway_t *path;
	PathNode *current_node;
	int max_nodes_to_look_at;
	int nodes_looked_at;
	qboolean found;

	
	// Get closest node

	start_node = PathManager.NearestNode( self.origin, &self );

	// Find a random node that is connected to this node

	found = false;

	if ( start_node )
		{
		max_nodes_to_look_at = G_Random( 5 ) + 10;
		nodes_looked_at = 0;
		current_node = start_node;

		while( !found )
			{
			nodes_looked_at++;

			if ( nodes_looked_at >= max_nodes_to_look_at && current_node != start_node )
				{
				found = true;
				flee_node = current_node;
				}

			if ( current_node->numChildren == 0 )
				break;

			path = &current_node->Child[ (int)G_Random( current_node->numChildren ) ];
			current_node = AI_GetNode( path->node );
			}
		}

	if ( !found )
		{
		// If still not found, use old method

		for( i = 0; i < 5; i++ )
			{
			flee_node = AI_GetNode( ( int )G_Random( ai_maxnode + 1 ) );
			if ( flee_node )
				break;
			}
		}
	}

qboolean	Flee::Evaluate
	(
	Actor &self
	)

	{
	// Make sure we have somewhere to flee to

	if ( !flee_node )
		return false;

	chase.SetGoal( flee_node );

	// Make a racket

	self.Chatter( "snd_panic", 3 );

	// Try to get to flee node

	if ( !chase.Evaluate( self ) )
		{
		// See if we are done fleeing

		if ( !self.currentEnemy || !self.CanSee( self.currentEnemy ) )
			{
			return false;
			}

		// Find a new spot to flee to

		FindFleeNode( self );
		}

	return true;
	}

void Flee::End
	(
	Actor &self
	)

	{
	chase.End( self );
	}

/****************************************************************************

  PlayAnim Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, PlayAnim, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void PlayAnim::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );
	}

void PlayAnim::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nanim: %s\n", anim.c_str() );
	}

void PlayAnim::Begin
	(
	Actor &self
	)

	{
	if ( anim.length() )
		{
		if ( !self.SetAnim( anim, EV_Actor_FinishedBehavior ) )
         {
         self.PostEvent( EV_Actor_FinishedBehavior, 0 );
         }
		}
	}

qboolean	PlayAnim::Evaluate
	(
	Actor &self
	)

	{
	return true;
	}

void PlayAnim::End
	(
	Actor &self
	)

	{
	self.RemoveAnimDoneEvent();
	}

/****************************************************************************

  Talk Class Definition

****************************************************************************/

#define TALK_MODE_TURN_TO		0
#define TALK_MODE_TALK			1
#define TALK_MODE_WAIT			2
#define TALK_MODE_TURN_BACK	3

CLASS_DECLARATION( Behavior, Talk, NULL )
	{
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ NULL, NULL }
	};

void Talk::SetUser
	(
	Sentient *user
	)

	{
	ent_listening = user;
	}

void Talk::AnimDone
	(
	Event *ev
	)

	{
	turnto.ProcessEvent( EV_Behavior_AnimDone );
	}

void Talk::Begin
	(
	Actor &self
	)

	{
	Vector dir;
	Vector angles;
	const char *anim_name;


	anim_name = self.animname;

	if ( strncmp( anim_name, "sit_leanover", 12 ) == 0 )
		{
		move_allowed = false;
		}
	else if ( strncmp( anim_name, "sit", 3 ) == 0 )
		{
		move_allowed = false;
		self.SetAnim( "sit_talk" );
		}
	else if ( strncmp( anim_name, "talk_sit_stunned", 15 ) == 0 )
		{
		move_allowed = false;
		}
	else if ( strncmp( anim_name, "talk_headset", 12 ) == 0 )
		{
		move_allowed = true;
		}
	else if ( strncmp( anim_name, "stand_hypnotized", 16 ) == 0 )
		{
		move_allowed = false;
		}
	else if ( strncmp( anim_name, "talk_hipnotic", 13 ) == 0 )
		{
		move_allowed = false;
		}
	else if ( strncmp( anim_name, "rope", 4 ) == 0 )
		{
		move_allowed = false;
		}
	else
		{
		move_allowed = true;
		self.SetAnim( "talk" );
		}

	mode = TALK_MODE_TURN_TO;
	original_yaw = self.angles[YAW];

	dir    = ent_listening->centroid - self.centroid;
	angles = dir.toAngles();
	yaw    = angles[YAW];
	}

qboolean	Talk::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;
	Vector angles;
	Event *event;

	if ( !ent_listening )
		mode = TALK_MODE_TURN_BACK;

	switch( mode )
		{
		case TALK_MODE_TURN_TO :
			if ( move_allowed )
				{
				turnto.SetDirection( yaw );

				if ( !turnto.Evaluate( self ) )
					{
					mode = TALK_MODE_TALK;
					self.PlayDialog( ent_listening );

					event = new Event( EV_Player_WatchActor );
					event->AddEntity( &self );
					ent_listening->PostEvent(  event, 0.05 );
					}
				}
			else
				{
				mode = TALK_MODE_TALK;
				self.PlayDialog( ent_listening );

				event = new Event( EV_Player_WatchActor );
				event->AddEntity( &self );
				ent_listening->PostEvent(  event, 0.05 );
				}
			break;
		case TALK_MODE_TALK :

			if ( move_allowed )
				{
				dir    = ent_listening->centroid - self.centroid;
				angles = dir.toAngles();
				turnto.SetDirection( angles[YAW] );
				turnto.Evaluate( self );
				}

			if ( !self.GetActorFlag( ACTOR_FLAG_DIALOG_PLAYING ) )
				{
				mode = TALK_MODE_WAIT;
				self.state_flags &= ~STATE_FLAG_USED;

				// Tell player to stop watching us

				event = new Event( EV_Player_StopWatchingActor );
				event->AddEntity( &self );
				ent_listening->PostEvent(  event, 0 );

				ent_listening->CancelEventsOfType( EV_Player_WatchActor );
				}
			break;
		case TALK_MODE_WAIT :

			if ( move_allowed )
				{
				dir    = ent_listening->centroid - self.centroid;
				angles = dir.toAngles();
				turnto.SetDirection( angles[YAW] );
				turnto.Evaluate( self );
				}

			if ( !self.WithinDistance( ent_listening, 100 ) )
				mode = TALK_MODE_TURN_BACK;

			if ( self.state_flags & STATE_FLAG_USED )
				{
				mode = TALK_MODE_TURN_TO;

				dir    = ent_listening->centroid - self.centroid;
				angles = dir.toAngles();
				yaw    = angles[YAW];

				self.state_flags &= ~STATE_FLAG_USED;

				event = new Event( EV_Player_WatchActor );
				event->AddEntity( &self );
				ent_listening->PostEvent(  event, 0.05 );
				}
			break;
		case TALK_MODE_TURN_BACK :
			if ( move_allowed )
				{
				turnto.SetDirection( original_yaw );

				if ( !turnto.Evaluate( self ) )
					return false;
				}
			else
				{
				return false;
				}

			break;
		}

	return true;
	}

void Talk::End
	(
	Actor &self
	)

	{
	Event *event;

	event = new Event( EV_Player_StopWatchingActor );
	event->AddEntity( &self );
	ent_listening->PostEvent(  event, 0 );

	ent_listening->CancelEventsOfType( EV_Player_WatchActor );
	}

/****************************************************************************

  FindCover Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, FindCover, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void FindCover::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
		crouch_anim = ev->GetString( 2 );
	}

PathNode *FindCover::FindCoverNode
	(
	Actor &self
	)

	{
	int i;
	PathNode	*bestnode;
	float		bestdist;
	PathNode	*desperatebestnode;
	float		desperatebestdist;
	PathNode *node;
	FindCoverPath find;
	Path		*path;
	Vector	delta;
	float		dist;
	Vector	pos;

   pos = self.origin;

   // greater than ( 8192 * sqr(2) ) ^ 2 -- maximum squared distance
	bestdist = 999999999;
	bestnode = NULL;

   // greater than ( 8192 * sqr(2) ) ^ 2 -- maximum squared distance
	desperatebestdist = 999999999;
	desperatebestnode = NULL;

   for( i = 0; i <= ai_maxnode; i++ )
		{
		node = AI_GetNode( i );
		if ( node && ( node->nodeflags & ( AI_DUCK | AI_COVER ) ) &&
			( ( node->occupiedTime <= level.time ) || ( node->entnum == self.entnum ) ) )
			{
			// get the distance squared (faster than getting real distance)
         delta = node->origin - pos;
			dist = delta * delta;
         if ( ( dist < bestdist ) && ( !self.CanSeeEnemyFrom( node->origin ) ||//) )//||
            ( ( node->nodeflags & AI_DUCK ) && !self.CanSeeEnemyFrom( node->origin - Vector( 0, 0, 32 ) ) ) ) )
				{
				bestnode = node;
				bestdist = dist;
				}
			else if ( ( dist < desperatebestdist ) && ( desperatebestdist > ( 64 * 64 ) ) )
				{
				desperatebestnode = node;
				desperatebestdist = dist;
				}
			}
		}

	if ( !bestnode )
		{
		bestnode = desperatebestnode;
		}

	if ( bestnode )
		{
		find.heuristic.self = &self;
		find.heuristic.setSize( self.size );
		find.heuristic.entnum = self.entnum;

      path = find.FindPath( self.origin, bestnode->origin );
		if ( path )
			{
			node = path->End();

			// Mark node as occupied for a short time
			node->occupiedTime = level.time + 1.5;
			node->entnum = self.entnum;

			chase.SetGoal( node );
			chase.SetPath( path );

			return node;
			}
		}

	return NULL;
	}

void FindCover::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nchase:\n" );
   chase.ShowInfo( self );

   gi.Printf( "\nstate: %d\n", state );
   gi.Printf( "anim: %s\n", anim.c_str() );
   gi.Printf( "nextsearch: %f\n", nextsearch );
	}

void FindCover::Begin
	(
	Actor &self
	)

	{
	if ( !anim.length() )
		{
		anim = "run";
		}

	if ( !crouch_anim.length() )
		{
		crouch_anim = "crouch_down";
		}

	movegoal = NULL;
	state = 0;
	}

qboolean	FindCover::Evaluate
	(
	Actor &self
	)

	{
	if ( !movegoal )
		{
		state = 0;
		}

	switch( state )
		{
		case 0 :
			// Checking for cover
			chase.Begin( self );
			movegoal = FindCoverNode( self );
			if ( !movegoal )
				{
            // Couldn't find any!
				return false;
				}

			// Found cover, going to it
			if ( anim.length() && ( anim != self.animname || self.newanim.length() ) )
				{
				self.SetAnim( anim );
				}

			state = 1;
			nextsearch = level.time + 1;

		case 1 :
			if ( chase.Evaluate( self ) )
				{
				if ( nextsearch < level.time )
					{
					state = 0;
					}
				return true;
				}

			// Reached cover
         if ( self.CanSeeEnemyFrom( self.origin ) )
				{
				state = 0;
				}

			if ( movegoal->nodeflags & AI_DUCK )
				{
            // ducking
				self.SetAnim( crouch_anim.c_str() );
				}
			else
				{
            // standing
				self.SetAnim( "idle" );
				}

			chase.End( self );
			return false;
			break;
		}

	return true;
	}

void FindCover::End
	(
	Actor &self
	)

	{
	chase.End( self );
	}

/****************************************************************************

  FindFlee Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, FindFlee, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void FindFlee::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );
	}

PathNode *FindFlee::FindFleeNode
	(
	Actor &self
	)

	{
	int i;
	PathNode	*bestnode;
	float		bestdist;
	PathNode	*desperatebestnode;
	float		desperatebestdist;
	PathNode *node;
	FindFleePath find;
	Path		*path;
	Vector	delta;
	float		dist;
	Vector	pos;

   pos = self.origin;

   // greater than ( 8192 * sqr(2) ) ^ 2 -- maximum squared distance
	bestdist = 999999999;
	bestnode = NULL;

   // greater than ( 8192 * sqr(2) ) ^ 2 -- maximum squared distance
	desperatebestdist = 999999999;
   desperatebestnode = NULL;

	for( i = 0; i <= ai_maxnode; i++ )
		{
		node = AI_GetNode( i );
		if ( node && ( node->nodeflags & AI_FLEE ) &&
			( ( node->occupiedTime <= level.time ) || ( node->entnum == self.entnum ) ) )
			{
			// get the distance squared (faster than getting real distance)
         delta = node->origin - pos;
			dist = delta * delta;
         if ( ( dist < bestdist ) && !self.CanSeeEnemyFrom( node->origin ) )
				{
				bestnode = node;
				bestdist = dist;
				}
			else if ( ( dist < desperatebestdist ) && ( desperatebestdist > ( 64 * 64 ) ) )
				{
				desperatebestnode = node;
				desperatebestdist = dist;
				}
			}
		}

	if ( !bestnode )
		{
		bestnode = desperatebestnode;
		}

	if ( bestnode )
		{
		find.heuristic.self = &self;
		find.heuristic.setSize( self.size );
		find.heuristic.entnum = self.entnum;

      path = find.FindPath( self.origin, bestnode->origin );
		if ( path )
			{
			node = path->End();

			// Mark node as occupied for a short time
			node->occupiedTime = level.time + 1.5;
			node->entnum = self.entnum;

			chase.SetGoal( node );
			chase.SetPath( path );

			return node;
			}
		}

	return NULL;
	}

void FindFlee::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nchase:\n" );
   chase.ShowInfo( self );

   gi.Printf( "\nstate: %d\n", state );
   gi.Printf( "anim: %s\n", anim.c_str() );
   gi.Printf( "nextsearch: %f\n", nextsearch );
	}

void FindFlee::Begin
	(
	Actor &self
	)

	{
	if ( !anim.length() )
		{
		anim = "run";
		}

	movegoal = NULL;
	state = 0;
	}

qboolean	FindFlee::Evaluate
	(
	Actor &self
	)

	{
	if ( !movegoal )
		{
		state = 0;
		}

	switch( state )
		{
		case 0 :
         // Checking for flee node
			chase.Begin( self );
			movegoal = FindFleeNode( self );
			if ( !movegoal )
				{
            // Couldn't find any!
				return false;
				}

         // Found flee node, going to it
			if ( anim.length() && ( anim != self.animname || self.newanim.length() ) )
				{
				self.SetAnim( anim );
				}

			state = 1;
			nextsearch = level.time + 1;

		case 1 :
			if ( chase.Evaluate( self ) )
				{
				if ( nextsearch < level.time )
					{
					state = 0;
					}
				return true;
				}

         // Reached cover
         if ( self.CanSeeEnemyFrom( self.origin ) )
				{
				state = 0;
				}
         else
            {
            // standing
	   		self.SetAnim( "idle" );
		   	chase.End( self );
			   return false;
            }
			break;
		}

	return true;
	}

void FindFlee::End
	(
	Actor &self
	)

	{
	chase.End( self );
	}

/****************************************************************************

  FindEnemy Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, FindEnemy, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void FindEnemy::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );
	}

void FindEnemy::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nchase:\n" );
   chase.ShowInfo( self );

   gi.Printf( "\nstate: %d\n", state );
   gi.Printf( "nextsearch: %f\n", nextsearch );
   gi.Printf( "anim: %s\n", anim.c_str() );
	}

void FindEnemy::Begin
	(
	Actor &self
	)

	{
	if ( !anim.length() )
		{
		anim = "run";
		}

	movegoal = NULL;
   lastSearchNode = NULL;
	state = 0;
	}

PathNode *FindEnemy::FindClosestSightNode
	(
	Actor &self
	)

	{
	int i;
	PathNode	*bestnode;
	float		bestdist;
	PathNode *node;
	Vector	delta;
	float		dist;
	Vector	pos;

   if ( self.currentEnemy )
      {
      pos = self.currentEnemy->origin;
      }
   else
      {
      pos = self.origin;
      }

   // greater than ( 8192 * sqr(2) ) ^ 2 -- maximum squared distance
	bestdist = 999999999;
	bestnode = NULL;

	for( i = 0; i <= ai_maxnode; i++ )
		{
		node = AI_GetNode( i );
		if ( node && ( ( node->occupiedTime <= level.time ) || ( node->entnum != self.entnum ) ) )
			{
			// get the distance squared (faster than getting real distance)
         delta = node->origin - pos;
			dist = delta * delta;
         if ( ( dist < bestdist ) && self.CanSeeFrom( node->origin, self.currentEnemy ) )
				{
				bestnode = node;
				bestdist = dist;
				}
			}
		}

	return bestnode;
	}

qboolean	FindEnemy::Evaluate
	(
	Actor &self
	)

	{
	if ( !self.currentEnemy )
		{
		return false;
		}

	if ( nextsearch < level.time )
		{
      // check if we should search for the first time
      if ( !lastSearchNode )
         {
         state = 0;
         }
      else
         {
         // search less often if we're far away
			nextsearch = self.DistanceTo( self.currentEnemy ) * ( 1.0 / 512.0 );
         if ( nextsearch < 1 )
            {
            nextsearch = 1;
            }
         nextsearch += level.time;

         // don't search again if our enemy hasn't moved very far
         if ( !self.currentEnemy->WithinDistance( lastSearchPos, 256 ) )
            {
            state = 0;
            }
         }
		}

	switch( state )
		{
		case 0 :
			// Searching for enemy
			chase.Begin( self );
         lastSearchPos = self.currentEnemy->origin;
         movegoal = PathManager.NearestNode( lastSearchPos, &self );
         if ( !movegoal )
            {
            movegoal = PathManager.NearestNode( lastSearchPos, &self, false );
            }

         lastSearchNode = movegoal;
			if ( movegoal )
				{
				Path *path;
				FindEnemyPath find;
            PathNode *from;

				find.heuristic.self = &self;
				find.heuristic.setSize( self.size );
				find.heuristic.entnum = self.entnum;

            from = PathManager.NearestNode( self.origin, &self );
            if ( ( from == movegoal ) && ( self.DistanceTo( from->origin ) < 8 ) )
               {
               movegoal = NULL;
               from = NULL;
               }

            if ( from )
               {
               path = find.FindPath( from, movegoal );
				   if ( path )
					   {
					   chase.SetGoal( movegoal );
					   chase.SetPath( path );
					   }
               else
                  {
                  movegoal = NULL;
                  }
               }
				}

			if ( !movegoal )
				{
				if ( self.CanSee( self.currentEnemy ) || ( !self.currentEnemy->groundentity && !self.waterlevel ) )
					{
					chase.SetGoalPos( self.currentEnemy->origin );
					}
				else
					{
					// Couldn't find enemy
					// since we can't reach em
					// clear out enemy state
					self.ClearEnemies();
					return false;
					}
				}

         // Found enemy, going to it
			if ( anim.length() && ( anim != self.animname || self.newanim.length() ) )
				{
				self.SetAnim( anim );
				}

			state = 1;

		case 1 :
			if ( self.CanShoot( self.currentEnemy, false ) )
				{
				// Reached enemy
				chase.End( self );
				return false;
				}

			if ( !chase.Evaluate( self ) )
				{
            state = 0;
				nextsearch = 0;
				}
			break;
		}

	return true;
	}

void FindEnemy::End
	(
	Actor &self
	)

	{
	chase.End( self );
	}

/****************************************************************************

  AimAndShoot Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, AimAndShoot, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ NULL, NULL }
	};

AimAndShoot::AimAndShoot()
	{
	maxshots = 1;
	numshots = 0;
	}

void AimAndShoot::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\naim:\n" );
   aim.ShowInfo( self );

   gi.Printf( "\nmode: %d\n", mode );
   gi.Printf( "maxshots: %d\n", maxshots );
   gi.Printf( "numshots: %d\n", numshots );
   gi.Printf( "animdone: %d\n", animdone );
	}

void AimAndShoot::Begin
	(
	Actor &self
	)

	{
   enemy_health = 0;
	animdone = false;

	if ( aimanim.length() )
		{
		self.SetAnim( aimanim.c_str() );
		mode = 0;
		}
	else
		{
		self.SetAnim( "idle" );
		mode = 1;
		}
   }

void AimAndShoot::SetMaxShots
	(
	int num
	)

	{
	maxshots = (num>>1) + G_Random( num );
	}

void AimAndShoot::SetArgs
	(
	Event *ev
	)

	{
   fireanim = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
      {
		maxshots = ev->GetInteger ( 2 );
      }

	if ( ev->NumArgs() > 2 )
      {
		aimanim = ev->GetString ( 3 );
      }
	}

void AimAndShoot::AnimDone
	(
	Event *ev
	)

	{
	animdone = true;
	}

qboolean	AimAndShoot::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;
	Vector angles;

	switch( mode )
		{
		case 0 :
         if ( !self.currentEnemy )
            {
            return false;
            }

			if ( !self.CanShoot( self.currentEnemy, false ) )
            {
            return false;
            }

			// start Aiming
			animdone = false;
         if ( aimanim.length() )
            {
			   self.SetAnim( aimanim.c_str() );
            }

         //
         // save off time, in case we aim for too long
         //
         aim_time = level.time + 1;
			mode = 1;

		case 1 :
			// Aiming
			if ( aimanim.length() )
				{
				if ( !self.currentEnemy )
					{
					return false;
					}
				
				// see if we aimed for too long				
				if ( aim_time < level.time )
					{
					return false;
					}

				aim.SetTarget( self.currentEnemy );

				if ( aim.Evaluate( self ) )
					{
					break;
					}
				}
			else
				{
				if ( self.IsEntityAlive( self.currentEnemy ) )
					{
					dir = self.currentEnemy->centroid - self.origin;
					angles = dir.toAngles();

					self.angles[YAW] = angles[YAW];
					self.setAngles( self.angles );
					}
				}

			// don't go into our firing animation until our weapon is ready, and we are on target
			if ( self.currentEnemy && self.CanShoot( self.currentEnemy, true ) )
				{
				animdone = false;
				self.Chatter( "snd_inmysights", 5 );
				self.SetAnim( fireanim.c_str(), EV_Actor_NotifyBehavior );
            enemy_health = self.currentEnemy->health;
				mode = 2;
				}
			else if ( !self.currentEnemy || self.currentEnemy->deadflag ||
				( self.currentEnemy->health <= 0 ) || !self.CanShoot( self.currentEnemy, false ) )
				{
				// either our enemy is dead, or we can't shoot the enemy from here
				return false;
				}
			break;

		case 2 :
			// Fire
			if ( animdone )
				{
				aim.SetTarget( self.currentEnemy );
				aim.Evaluate( self );

				self.times_done++;

            if ( !self.currentEnemy || ( self.currentEnemy->health < enemy_health ) )
               {
					self.Chatter( "snd_attacktaunt", 4 );
               }
            else
               {
					self.Chatter( "snd_missed", 7 );
               }

				animdone = false;
				numshots++;

				if ( ( numshots >= maxshots ) || !self.currentEnemy || self.currentEnemy->deadflag ||
					( self.currentEnemy->health <= 0 ) || !self.CanShoot( self.currentEnemy, false ) )
					{
					// either we're out of shots, our enemy is dead, or we can't shoot the enemy from here

					return false;
					}
				else if ( !self.CanShoot( self.currentEnemy, false ) )
					{
					// weapon not ready or not aimed at enemy, so just keep trying to get enemy in our sights
               if ( aimanim.length() )
                  {
		   			self.SetAnim( aimanim.c_str() );
                  }
               //
               // save off time, in case we aim for too long
               //
               aim_time = level.time + 1;
					mode = 1;
					}
				else
					{
					// keep firing
					self.SetAnim( fireanim.c_str(), EV_Actor_NotifyBehavior );
               enemy_health = self.currentEnemy->health;
					}
				}
			break;
		}

	return true;
	}

void AimAndShoot::End
	(
	Actor &self
	)

	{
	aim.End( self );
	//self.SetAnim( "idle" );
	}

/****************************************************************************

  AimAndMelee Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, AimAndMelee, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ NULL, NULL }
	};

AimAndMelee::AimAndMelee()
	{
	maxshots = 1;
	anim_name = "melee";
	}

void AimAndMelee::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\naim:\n" );
   aim.ShowInfo( self );

   gi.Printf( "\nmode: %d\n", mode );
   gi.Printf( "maxshots: %d\n", maxshots );
   gi.Printf( "numshots: %d\n", numshots );
   gi.Printf( "animdone: %d\n", animdone );
	}

void AimAndMelee::Begin
	(
	Actor &self
	)

	{
	mode = 0;
   numshots = 0;
	animdone = false;

	self.SetAnim( "idle" );
	}

void AimAndMelee::SetArgs
	(
	Event *ev
	)

	{
	anim_name = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
      {
		maxshots = ev->GetInteger( 2 );
      }
	}

void AimAndMelee::AnimDone
	(
	Event *ev
	)

	{
	animdone = true;
	}

qboolean	AimAndMelee::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;

	switch( mode )
		{
		case 0 :
			if ( !self.currentEnemy )
            {
            return false;
            }

			if ( self.IsEntityAlive( self.currentEnemy ) )
				{
				dir = self.currentEnemy->centroid - self.origin;
				self.angles[YAW] = dir.toYaw();
				self.setAngles( self.angles );
				}

         numshots++;
         animdone = false;

			// melee
			self.SetAnim( anim_name.c_str() , EV_Actor_NotifyBehavior );
			self.Chatter( "snd_attacktaunt", 4 );
         mode = 1;

		case 1 :
			// finish up the attack
			if ( animdone )
				{
				self.times_done++;
            if ( numshots >= maxshots )
               {
				   return false;
               }
				
            mode = 0;
            }
			break;
		}

	return true;
	}

void AimAndMelee::End
	(
	Actor &self
	)

	{
	aim.End( self );
	}

/****************************************************************************

  JumpToPathNode Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, JumpToPathNode, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void JumpToPathNode::SetArgs
	(
	Event *ev
	)
	{
	Entity *ent;


  	movegoal = AI_FindNode( ev->GetString( 1 ) );

	if ( movegoal )
		jump.SetGoal( movegoal->targetname );
	else
      {
   	ent = ev->GetEntity( 1 );

      if ( ent )
         jump.SetEntity( ent );
      }

   if ( ev->NumArgs() > 1 )
	   jump.SetSpeed( ev->GetFloat( 2 ) );
	else
		jump.SetSpeed( 200 );
	}

void JumpToPathNode::Begin
	(
	Actor &self
	)

	{
	jump.Begin( self );
	}

qboolean	JumpToPathNode::Evaluate
	(
	Actor &self
	)

	{
	return jump.Evaluate( self );
	}

void JumpToPathNode::End
	(
	Actor &self
	)

	{
	jump.End( self );
	}

/****************************************************************************

  FlyToPoint Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, FlyToPoint, NULL )
	{
		{ NULL, NULL }
	};

FlyToPoint::FlyToPoint()
	{
	turn_speed = 10.0;
	speed = 480.0;
	random_allowed = true;
	force_goal = false;
	}

void FlyToPoint::SetTurnSpeed( float new_turn_speed )
	{
	turn_speed = new_turn_speed;
	}

void FlyToPoint::SetGoalPoint( Vector goal_point )
	{
	if ( goal_point != goal )
		avoidtime = 0;
			
	goal = goal_point;
	}

void FlyToPoint::SetRandomAllowed( qboolean allowed )
	{
	random_allowed = allowed;
	}

void FlyToPoint::SetSpeed( float speed_value )
	{
	speed = speed_value;
	}

void FlyToPoint::ForceGoal( void )
	{
	force_goal = true;
	}

void FlyToPoint::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void FlyToPoint::Begin
	(
	Actor &self
	)

	{
   avoidtime = 0;
	old_forward_speed = self.forwardspeed;
	stuck = 0;
	use_temp_goal = false;
	}

qboolean	FlyToPoint::Evaluate
	(
	Actor &self
	)

	{
   trace_t trace;
   Vector dir;
   Vector ang;
	float time;
	float length;
	float old_yaw;
	float old_pitch;

	if ( self.lastmove != STEPMOVE_OK )
		stuck++;
	else
		stuck = 0;

   if ( stuck > 2 || ( avoidtime <= level.time ) )
      {
		time = G_Random( .3 ) + .3;

		use_temp_goal = false;

		if ( !force_goal )
			{
			trace = G_Trace( self.origin, self.mins, self.maxs, goal, &self, self.edict->clipmask, false, "FlyToPoint" );

			if ( trace.fraction < 0.5f || stuck > 2 )
				{
				temp_goal = ChooseRandomDirection( self, goal, &time, MASK_WATER, true );
				use_temp_goal = true;
				avoidtime = level.time + time;

				stuck = 0;
				}
			else
				{
				goal = trace.endpos;
				avoidtime = level.time + time;
				}
			}
		else
			{
			avoidtime = level.time + time;
			}

		if ( use_temp_goal )
			dir = temp_goal - self.origin;
		else
			dir = goal - self.origin;

		length = dir.length();
      dir.normalize();
      ang = dir.toAngles();

		if ( length > 150 && random_allowed && !use_temp_goal )
			{
			ang[YAW]   += G_Random( 20 ) - 10.0;
			ang[PITCH] += G_Random( 20 ) - 10.0;
			}

		target_angle = ang;

		target_angle[YAW]   = AngleNormalize360( target_angle[YAW] );
		target_angle[PITCH] = AngleNormalize360( target_angle[PITCH] );
      }

	if ( (self.angles[YAW] != target_angle[YAW]) || (self.angles[PITCH] != target_angle[PITCH]) )
      {
		self.forwardspeed = speed * 0.8f;
      }
	else
      {
		self.forwardspeed = speed;
      }

	old_yaw   = self.angles[YAW];
	old_pitch = self.angles[PITCH];

	ang[YAW]   = LerpAngle( self.angles[YAW],   target_angle[YAW],   turn_speed );
	ang[PITCH] = LerpAngle( self.angles[PITCH], target_angle[PITCH], turn_speed );
	ang[ROLL]  = self.angles[ROLL];

	if ( (AngleDelta( ang[YAW], old_yaw ) > 0) && (ang[ROLL] > 315 || ang[ROLL] <= 45) )
		{
		ang[ROLL] -= 5;
		}
	else if ( (AngleDelta( ang[YAW], old_yaw ) < 0) && (ang[ROLL] < 45 || ang[ROLL] >= 315) )
		{
		ang[ROLL] += 5;
		}
	else if ( AngleDelta( ang[YAW], old_yaw ) == 0 )
		{
		if ( ang[ROLL] != 0 )
			{
			if ( ang[ROLL] < 180 )
				ang[ROLL] -= 5;
			else
				ang[ROLL] += 5;
			}
		}

	ang[YAW]   = AngleNormalize360( ang[YAW] );
	ang[PITCH] = AngleNormalize360( ang[PITCH] );
	ang[ROLL]  = AngleNormalize360( ang[ROLL] );

	// Don't get stuck if still turning

	if ( ( AngleDelta( ang[YAW], old_yaw ) > .5 ) || ( AngleDelta( ang[YAW], old_yaw ) < -.5 ) ||
		  ( AngleDelta( ang[PITCH], old_pitch ) > .5 ) || ( AngleDelta( ang[PITCH], old_pitch ) < -.5 ) )
		{
		stuck = 0;
		}
		
	self.setAngles( ang );

	return true;
	}

float FlyToPoint::LerpAngle( float old_angle, float new_angle, float lerp_amount )
	{
	float diff;
	float abs_diff;
	float lerp_angle;

	new_angle = AngleNormalize360( new_angle );
	old_angle = AngleNormalize360( old_angle );
	
	diff = new_angle - old_angle;

	if ( diff > 180 )
      {
		diff -= 360;
      }

	if ( diff < -180 )
      {
		diff += 360;
      }

	lerp_angle = old_angle;

	abs_diff = diff;

	if ( abs_diff < 0 )
      {
		abs_diff = -abs_diff;
      }

	if ( abs_diff < lerp_amount )
      {
		lerp_amount = abs_diff;
      }

	if ( diff < 0 )
      {
		lerp_angle -= lerp_amount;
      }
	else if ( diff > 0 )
      {
		lerp_angle += lerp_amount;
      }

	lerp_angle = AngleNormalize360( lerp_angle );

	return lerp_angle;
	}

void FlyToPoint::End
	(
	Actor &self
	)

	{
	self.forwardspeed = old_forward_speed;
	}

/****************************************************************************

  FlyCloseToEnemy Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, FlyCloseToEnemy, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

FlyCloseToEnemy::FlyCloseToEnemy()
	{
	speed = 0;
	turn_speed = 10.0;
	anim = "fly";
	}

void FlyCloseToEnemy::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
		turn_speed = ev->GetFloat( 2 );

	if ( ev->NumArgs() > 2 )
		speed = ev->GetFloat( 3 );
	}

void FlyCloseToEnemy::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void FlyCloseToEnemy::Begin
	(
	Actor &self
	)

	{
	if ( anim.length() )
      {
		self.SetAnim( anim );
      }

	fly.Begin( self );
	fly.SetTurnSpeed( turn_speed );

	if ( speed )
		fly.SetSpeed( speed );

	next_goal_time = 0;
	}

qboolean	FlyCloseToEnemy::Evaluate
	(
	Actor &self
	)

	{
   Vector goal;
 

   if ( !self.IsEntityAlive( self.currentEnemy ) )
      return false;

	if ( next_goal_time <= level.time )
		{
		goal = self.currentEnemy->centroid;

		goal[0] += G_Random( 30 ) - 15.0;
		goal[1] += G_Random( 30 ) - 15.0;
		goal[2] += G_Random( 60 ) - 30.0;

		fly.SetGoalPoint( goal );

		next_goal_time = level.time + .5;
		}

	fly.Evaluate( self );

	return true;
	}

void FlyCloseToEnemy::End
	(
	Actor &self
	)

	{
	fly.End( self );
	}

/****************************************************************************

  FlyCloseToPlayer Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, FlyCloseToPlayer, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

FlyCloseToPlayer::FlyCloseToPlayer()
	{
	speed = 0;
	turn_speed = 10.0;
	anim = "fly";
	}

void FlyCloseToPlayer::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
		turn_speed = ev->GetFloat( 2 );

	if ( ev->NumArgs() > 2 )
		speed = ev->GetFloat( 3 );
	}

void FlyCloseToPlayer::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void FlyCloseToPlayer::Begin
	(
	Actor &self
	)

	{
	if ( anim.length() )
      {
		self.SetAnim( anim );
      }

	fly.Begin( self );
	fly.SetTurnSpeed( turn_speed );

	if ( speed )
		fly.SetSpeed( speed );

	next_goal_time = 0;
	}

qboolean	FlyCloseToPlayer::Evaluate
	(
	Actor &self
	)

	{
   Vector goal;
	Entity *player;


	player = g_entities[ 0 ].entity;
 

   if ( !self.IsEntityAlive( player ) )
      return false;

	if ( next_goal_time <= level.time )
		{
		goal = player->centroid;

		goal[0] += G_Random( 30 ) - 15.0;
		goal[1] += G_Random( 30 ) - 15.0;
		goal[2] += G_Random( 60 ) - 30.0;

		fly.SetGoalPoint( goal );

		next_goal_time = level.time + .5;
		}

	fly.Evaluate( self );

	return true;
	}

void FlyCloseToPlayer::End
	(
	Actor &self
	)

	{
	fly.End( self );
	}

/****************************************************************************

  FlyWander Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, FlyWander, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

FlyWander::FlyWander()
	{
	turn_speed = 10.0;
	anim = "fly";
	change_course_time = 5.0;
	speed = 200;
	try_to_go_up = false;
	}

void FlyWander::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
      {
		speed = ev->GetFloat( 2 );
      }

	if ( ev->NumArgs() > 2 )
      {
		turn_speed = ev->GetFloat( 3 );
      }

	if ( ev->NumArgs() > 3 )
      {
		change_course_time = ev->GetFloat( 4 );
      }

	if ( ev->NumArgs() > 4 )
      {
		try_to_go_up = ev->GetFloat( 5 );
      }
	}

void FlyWander::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void FlyWander::Begin
	(
	Actor &self
	)

	{
	next_change_course_time = 0;

	original_z = self.origin.z;

	if ( anim.length() )
		self.SetAnim( anim );

	fly.Begin( self );
	fly.SetTurnSpeed( turn_speed );
	fly.SetSpeed( speed );
	}

qboolean	FlyWander::Evaluate
	(
	Actor &self
	)

	{
	trace_t trace;
	Vector dir;
	float length;
	int goal_try;
	Vector temp_goal;
	float max_dist = 0;


	dir = goal - self.origin;
	length = dir.length();

	if ( next_change_course_time <= level.time || length < 100 ) //self.lastmove != STEPMOVE_OK )
		{
		for( goal_try = 0 ; goal_try < 5 ; goal_try++ )
			{
			temp_goal = self.origin;

			temp_goal[0] += G_Random( 10000 ) - 5000.0;
			temp_goal[1] += G_Random( 10000 ) - 5000.0;

			if ( try_to_go_up )
				temp_goal[2] += G_Random( 1000 ) - 250.0;
			else
				temp_goal[2] += G_Random( 100 ) - 50.0;

			trace = G_Trace( self.origin, self.mins, self.maxs, temp_goal, &self, self.edict->clipmask, false, "FlyWander" );

			temp_goal = trace.endpos;

			dir = temp_goal - self.origin;
			length = dir.length();

			if ( length > max_dist )
				{
				max_dist = length;
				goal = temp_goal;

				if ( length > 1000 )
					break;
				}
			}

		fly.SetGoalPoint( goal );

		next_change_course_time = level.time + change_course_time;
		}

	fly.Evaluate( self );

	return true;
	}

void FlyWander::End
	(
	Actor &self
	)

	{
	fly.End( self );
	}

/****************************************************************************

  FlyCircle Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, FlyCircle, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

FlyCircle::FlyCircle()
	{
	anim = "fly";
	}

void FlyCircle::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	fly_clockwise = ev->GetBoolean( 2 );
	}

void FlyCircle::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void FlyCircle::Begin
	(
	Actor &self
	)

	{
	original_z = self.origin.z;

	if ( anim.length() )
      {
		self.SetAnim( anim );
      }

	fly.Begin( self );
	fly.SetTurnSpeed( 5.0 );
	}

qboolean	FlyCircle::Evaluate
	(
	Actor &self
	)

	{
   Vector goal;
	trace_t trace;
	Vector dir;
	Vector angle;
	Vector left;
	qboolean too_far = false;
	Vector new_dir;
	Vector fly_dir;

	if ( !self.IsEntityAlive( self.currentEnemy ) )
      {
      return false;
      }

	if ( self.lastmove == STEPMOVE_OK )
		{
		fly.SetTurnSpeed( 5.0 );

		dir = self.currentEnemy->centroid - self.origin;
		dir.z = 0;

		if ( dir.length() > (self.origin.z - self.currentEnemy->centroid.z) / 2 )
			{
			too_far = true;
			}

		angle = dir.toAngles();

		angle.AngleVectors( NULL, &left, NULL );

		if ( fly_clockwise )
			fly_dir = left;
		else
			fly_dir = left * -1;

		dir.normalize();

		if ( too_far )
			{
			new_dir = fly_dir * 0.5 + dir * 0.5;
			new_dir.normalize();
			}
		else
			{
			new_dir = fly_dir;
			}

		goal = self.origin + new_dir * 200;

		trace = G_Trace( self.origin, self.mins, self.maxs, goal, &self, self.edict->clipmask, false, "FlyCircle" );

		if ( trace.fraction < 1 )
			{
			if ( too_far )
				trace.fraction /= 2;

			new_dir = fly_dir * trace.fraction + dir * (1 - trace.fraction);
			new_dir.normalize();

			goal = self.origin + new_dir * 200;
			}
		else
			{
			goal = trace.endpos;
			}

		fly.SetGoalPoint( goal );
		}
	else
		{
		fly.SetTurnSpeed( 20.0 );
		}

	fly.Evaluate( self );

	return true;
	}

void FlyCircle::End
	(
	Actor &self
	)

	{
	fly.End( self );
	}

/****************************************************************************

  FlyDive Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, FlyDive, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

FlyDive::FlyDive()
	{
	anim = "fly";
	speed = 2000;
	damage = 10;
	}

void FlyDive::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
      {
		speed = ev->GetFloat( 2 );
      }

	if ( ev->NumArgs() > 2 )
      {
		damage = ev->GetFloat( 3 );
      }
	}

void FlyDive::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void FlyDive::Begin
	(
	Actor &self
	)

	{
	if ( anim.length() )
		self.SetAnim( anim );

	fly.Begin( self );

	if ( !self.IsEntityAlive( self.currentEnemy ) )
      {
		return;
      }

	goal = self.currentEnemy->centroid - self.origin;
	goal.normalize();
	goal *= 10000;
	goal += self.origin;

	fly.SetGoalPoint( goal );

	fly.SetTurnSpeed( 100 );
	fly.SetSpeed( speed );
	fly.SetRandomAllowed( false );
	fly.ForceGoal();
	}

qboolean	FlyDive::Evaluate
	(
	Actor &self
	)

	{
	trace_t trace;
	Vector dir;
	Entity *hit_entity;
	qboolean stuck;


	if ( !self.IsEntityAlive( self.currentEnemy ) )
      return false;

	if ( self.origin.z < self.currentEnemy->origin.z  - 100 )
      return false;

	if ( self.lastmove == STEPMOVE_STUCK || self.lastmove == STEPMOVE_BLOCKED_BY_WATER )
		{
		stuck = true;

		dir = self.movedir * 100;

		trace = G_Trace( self.origin, self.mins, self.maxs, self.origin + dir, &self, self.edict->clipmask, false, "FlyDive" );

		if ( trace.entityNum != ENTITYNUM_NONE )
			{
			hit_entity = G_GetEntity( trace.entityNum );

			// Damage entity hit
			//if ( hit_entity->isSubclassOf( Sentient ) )
			if ( hit_entity->takedamage )
				{
				//hit_entity->Damage( &self, &self, damage, Vector (0, 0, 0), Vector (0, 0, 0), Vector (0, 0, 0), 0, 0, MOD_CRUSH );
				dir.normalize();
				hit_entity->Damage( &self, &self, damage, self.centroid, dir, vec_zero, 0, 0, MOD_CRUSH );
				self.AddStateFlag( STATE_FLAG_MELEE_HIT );
				stuck = false;
				}
			}

		// Make sure we really are still stuck

		if ( trace.fraction > 0.05 )
			stuck = false;

		self.angles[PITCH] = 0;
		self.setAngles( self.angles );

		if ( stuck )
			self.AddStateFlag( STATE_FLAG_STUCK );

		return false;
		}

	fly.Evaluate( self );

	return true;
	}

void FlyDive::End
	(
	Actor &self
	)

	{
	fly.End( self );
	}

/****************************************************************************

  FlyClimb Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, FlyClimb, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

FlyClimb::FlyClimb()
	{
	anim = "fly";
	height = 500;
	speed = 0;
	}

void FlyClimb::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
		height = ev->GetFloat( 2 );

	if ( ev->NumArgs() > 2 )
		speed = ev->GetFloat( 3 );
	}

void FlyClimb::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void FlyClimb::Begin
	(
	Actor &self
	)

	{
	if ( anim.length() )
      {
		self.SetAnim( anim );
      }

	fly.Begin( self );

	if ( self.currentEnemy )
		height = self.currentEnemy->origin.z + height;
	else
		height = self.origin.z + height;

	goal = self.origin;
	goal.z = height;

	fly.SetTurnSpeed( 10 );

	fly.SetGoalPoint( goal );

	next_height_check = level.time + 2.0;
	last_check_height = self.origin.z;

	if ( speed )
		fly.SetSpeed( speed );
	}

qboolean	FlyClimb::Evaluate
	(
	Actor &self
	)

	{

	if ( self.origin.z >= height )
      {
		return false;
      }

	if ( next_height_check < level.time )
		{
		if ( self.origin.z < last_check_height + 25 )
			return false;

		next_height_check = level.time + 2.0;
		last_check_height = self.origin.z;
		}

	if ( self.lastmove == STEPMOVE_OK )
		fly.SetGoalPoint( goal );

	fly.Evaluate( self );

	return true;
	}

void FlyClimb::End
	(
	Actor &self
	)

	{
	fly.End( self );
	}

/****************************************************************************

  Land Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, Land, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

Land::Land()
	{
	anim = "fly";
	}

void Land::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );
	}

void Land::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void Land::Begin
	(
	Actor &self
	)

	{
	if ( anim.length() )
      {
		self.SetAnim( anim );
      }

	self.velocity = "0 0 -20";
	}

qboolean	Land::Evaluate
	(
	Actor &self
	)

	{
	self.angles[PITCH] = 0;
	self.angles[ROLL]  = 0;

	self.setAngles( self.angles );

	self.velocity.z -= 20;

	if ( self.velocity.z < -200 )
      {
		self.velocity.z = -200;
      }

	return !self.groundentity;
	}

void Land::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  Wander Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, Wander, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void Wander::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );
	}

void Wander::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nseek:\n" );
   seek.ShowInfo( self );

   //gi.Printf( "\navoid:\n" );
   //avoid.ShowInfo( self );
	}

void Wander::Begin
	(
	Actor &self
	)

	{
   avoidtime = 0;
   avoidvec = vec_zero;

	//avoid.Begin( self );
   seek.Begin( self );
   seek.SetTargetVelocity( vec_zero );
	if ( anim.length() )
		{
		self.SetAnim( anim );
		}
	}


qboolean	Wander::Evaluate
	(
	Actor &self
	)

	{
   if ( ( self.lastmove != STEPMOVE_OK ) || ( avoidtime <= level.time ) )
      {
      Vector dir;
      Vector ang;
      float time;

      time = 5;
		//self.Chatter( "snd_idle", 4 );
      avoidvec = ChooseRandomDirection( self, avoidvec, &time, 0, false );
      avoidtime = level.time + time;
      }

	if ( self.movespeed != 1 )
		seek.SetMaxSpeed( self.movespeed );
	else
		seek.SetMaxSpeed( 100 );

   seek.SetPosition( self.origin );
	seek.SetDir( self.movedir );
   seek.SetTargetPosition( avoidvec );

   if ( !seek.Evaluate( self ) )
      {
		// we have reached the goal, re-evaluate
      avoidtime = 0;
      }

   /* avoid.SetMaxSpeed( self.movespeed * 2 );
   avoid.SetPosition( self.origin );
	avoid.SetDir( self.movedir );
	avoid.Evaluate( self ); */

   //self.Accelerate( seek.steeringforce + avoid.steeringforce );

	self.Accelerate( seek.steeringforce );

	return true;
	}

void Wander::End
	(
	Actor &self
	)

	{
	//avoid.End( self );
	seek.End( self );
	}

/****************************************************************************

  GetCloseToEnemy Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, GetCloseToEnemy, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void GetCloseToEnemy::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
		forever = ev->GetBoolean( 2 );
	else
		forever = true;
	}

void GetCloseToEnemy::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nchase:\n" );
   chase.ShowInfo( self );
	}

void GetCloseToEnemy::Begin
	(
	Actor &self
	)

	{
	if ( !anim.length() )
      {
		anim = "run";
      }

	if ( anim != self.animname || self.newanim.length() )
      {
		self.SetAnim( anim, EV_Actor_NotifyBehavior );
      }

	chase.UseNearestNode( false );
	chase.Begin( self );
	wander.Begin( self );

	next_think_time = 0;
	}

qboolean	GetCloseToEnemy::Evaluate
	(
	Actor &self
	)

	{
	qboolean result;

	if ( !self.currentEnemy )
		return false;

	if ( next_think_time <= level.time )
		{
		if ( self.groundentity && self.groundentity->s.number == self.currentEnemy->entnum )
			{
			wander.Evaluate( self );
			result = true;
			}
		else
			{
			chase.SetTarget( self.currentEnemy );

			result = chase.Evaluate( self );
			}

		if ( self.GetActorFlag( ACTOR_FLAG_SIMPLE_PATHFINDING ) )
			next_think_time = level.time + 2 * FRAMETIME;
		else
			next_think_time = 0;
		}
	else
		result = true;

	if ( !forever && !result )
		return false;

	return true;
	}

void GetCloseToEnemy::End
	(
	Actor &self
	)

	{
	chase.End( self );
	wander.End( self );
	}

/****************************************************************************

  GotoDeadEnemy Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, GotoDeadEnemy, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void GotoDeadEnemy::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );
	}

void GotoDeadEnemy::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nchase:\n" );
   chase.ShowInfo( self );
	}

void GotoDeadEnemy::Begin
	(
	Actor &self
	)

	{
	if ( !anim.length() )
      {
		anim = "run";
      }

	if ( anim != self.animname || self.newanim.length() )
      {
		self.SetAnim( anim, EV_Actor_NotifyBehavior );
      }

	chase.Begin( self );
	}

qboolean	GotoDeadEnemy::Evaluate
	(
	Actor &self
	)

	{
	qboolean result;

	if ( !self.currentEnemy )
		return false;

	if ( !self.currentEnemy->deadflag )
		return false;

	chase.SetGoalPos( self.currentEnemy->origin );

	result = chase.Evaluate( self );

	if ( !result )
		return false;

	return true;
	}

void GotoDeadEnemy::End
	(
	Actor &self
	)

	{
	chase.End( self );
	}

/****************************************************************************

  Investigate Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Investigate, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

#define INVESTIGATE_MODE_INVESTIGATE	0
#define INVESTIGATE_MODE_TURN1			1
#define INVESTIGATE_MODE_RETURN			2
#define INVESTIGATE_MODE_TURN2			3

Investigate::Investigate()
	{
	investigate_time = 10;
	anim = "run";
	}

void Investigate::SetArgs
	(
	Event *ev
	)

	{
	anim = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
		investigate_time = ev->GetFloat( 2 );

	if ( ev->NumArgs() > 2 )
		return_to_original_location = ev->GetBoolean( 3 );
	else
		return_to_original_location = true;
	}

void Investigate::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "\nchase:\n" );
   chase.ShowInfo( self );
   gi.Printf( "\nanim: %s\n", anim.c_str() );
   gi.Printf( "curioustime: %f\n", curioustime );
   gi.Printf( "goal: ( %f, %f, %f )\n", goal.x, goal.y, goal.z );
	}

void Investigate::Begin
	(
	Actor &self
	)

	{
	trace_t trace;
	Vector trace_start_pos;
	Vector trace_end_pos;
	PathNode *goal_node;
	Vector delta;
	float xydist;


	// Find the goal position

	trace_start_pos = self.noise_position;
	trace_end_pos   = trace_start_pos - "0 0 1000";

	trace = G_Trace( trace_start_pos, vec_zero, vec_zero, trace_end_pos, NULL, MASK_SOLID, false, "Investigate" );

	goal = trace.endpos;

	// Find the nearest node to our goal

	goal_node = self.NearestNodeInPVS( goal );
	real_goal_position = self.noise_position;

	if ( goal_node )
		goal = goal_node->origin;

	self.SetActorFlag( ACTOR_FLAG_INVESTIGATING, true );

   // We are only interested for a short period, if we can't get there, lets go back to what we were doing
   
   curioustime = level.time + investigate_time;
	self.Chatter( "snd_investigate", 10 );

	chase.Begin( self );
	chase.SetGoal( goal_node );

	turnto.Begin( self );

	// Don't allow guys to change their anim if we're already close enough to the goal

	delta   = goal - self.origin;
	delta.z = 0;

	xydist = delta.length();

	if ( xydist >= 100 && anim.length() )
		{
		self.SetAnim( anim );
		}

	mode = INVESTIGATE_MODE_INVESTIGATE;

	start_pos = self.origin;
	start_yaw = self.angles[YAW];
	}

qboolean	Investigate::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;
	Vector angles;
	Vector delta;
	float xydist;


	switch ( mode )
		{
		case INVESTIGATE_MODE_INVESTIGATE :

			// Go to spot where the noise was heard

			if ( !chase.Evaluate( self ) )
				{
				mode = INVESTIGATE_MODE_TURN1;
				self.SetAnim( "idle" );
				}

			// See if we have investigated long enough

			if ( curioustime < level.time )
				{
				mode = INVESTIGATE_MODE_RETURN;
				curioustime = level.time + investigate_time * 2;
				}
			else
				{
				// See if have gotten close enough to the noise position

				delta   = goal - self.origin;
				delta.z = 0;

				xydist = delta.length();

				if ( xydist < 100 )
					{
					mode = INVESTIGATE_MODE_TURN1;
					self.SetAnim( "idle" );
					}
				}

			break;
		case INVESTIGATE_MODE_TURN1 :

			// Turn towards the noise position

			dir = real_goal_position - self.origin;
			angles = dir.toAngles();
			turnto.SetDirection( angles[YAW] );

			if ( !turnto.Evaluate( self ) )
				{
				mode = INVESTIGATE_MODE_RETURN;
				curioustime = level.time + investigate_time * 2;
				self.SetAnim( anim );
				}

			break;
		case INVESTIGATE_MODE_RETURN :

			if ( !return_to_original_location )
				return false;

			// Return back to our original position

			chase.SetGoalPos( start_pos );

			if ( !chase.Evaluate( self ) )
				mode = INVESTIGATE_MODE_TURN2;

			if ( curioustime < level.time )
				return false;

			break;
		case INVESTIGATE_MODE_TURN2 :

			self.SetAnim( "idle" );

			// Turn back to our original direction

			turnto.SetDirection( start_yaw );
			if ( !turnto.Evaluate( self ) )
				return false;

			break;
		}

	return true;
	}

void Investigate::End
	(
	Actor &self
	)

	{
	self.SetActorFlag( ACTOR_FLAG_INVESTIGATING, false );
	self.SetActorFlag( ACTOR_FLAG_NOISE_HEARD, false );
	chase.End( self );
	turnto.End( self );
	}

/****************************************************************************

  TurnInvestigate Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, TurnInvestigate, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void TurnInvestigate::SetArgs
	(
	Event *ev
	)

	{
	left_anim  = ev->GetString( 1 );
	right_anim = ev->GetString( 2 );
	turn_speed = ev->GetFloat( 3 );
	}

void TurnInvestigate::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );

   gi.Printf( "goal: ( %f, %f, %f )\n", goal.x, goal.y, goal.z );
	}

void TurnInvestigate::Begin
	(
	Actor &self
	)

	{
	goal = self.noise_position;
	self.SetActorFlag( ACTOR_FLAG_INVESTIGATING, true );

	seek.Begin( self );
	seek.SetTargetPosition( goal );

	self.SetAnim( "idle" );
	}

qboolean	TurnInvestigate::Evaluate
	(
	Actor &self
	)

	{
	str turn_anim_name;
	Vector dir;

	self.angles.AngleVectors( &dir );

	seek.SetTargetVelocity( vec_zero );
	seek.SetPosition( self.centroid );
	seek.SetDir( dir );
	seek.Evaluate( self );

	// See if we have turned all of the way to the noise position
	
	if ( seek.steeringforce[YAW] < .5 && seek.steeringforce[YAW] > -.5 )
		return false;

	// Make sure we are not turning faster than out turn speed

	if ( seek.steeringforce[YAW] > turn_speed )
		{
		seek.steeringforce[YAW] = turn_speed;
		}

	if ( seek.steeringforce[YAW] < -turn_speed )
		{
		seek.steeringforce[YAW] = -turn_speed;
		}

	seek.steeringforce[PITCH] = 0;
	seek.steeringforce[ROLL]  = 0;

	// Set the correct animation (left or right)

	if ( seek.steeringforce[YAW] > 0 )
		turn_anim_name = left_anim;
	else
		turn_anim_name = right_anim;

	if ( turn_anim_name != self.animname )
		self.SetAnim( turn_anim_name );

	// Actually turn here

	self.Accelerate( seek.steeringforce );

	return true;
	}

void TurnInvestigate::End
	(
	Actor &self
	)

	{
	self.SetActorFlag( ACTOR_FLAG_INVESTIGATING, false );
	self.SetActorFlag( ACTOR_FLAG_NOISE_HEARD, false );
	seek.End( self );
	}

/****************************************************************************

  TurnToEnemy Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, TurnToEnemy, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ NULL, NULL }
	};

void TurnToEnemy::SetArgs
	(
	Event *ev
	)

	{
	left_anim  = ev->GetString( 1 );
	right_anim = ev->GetString( 2 );
	turn_speed = ev->GetFloat( 3 );
	forever    = ev->GetBoolean( 4 );

	if ( ev->NumArgs() > 4 )
		use_last_known_position = ev->GetBoolean( 5 );
	else
		use_last_known_position = false;
	}

void TurnToEnemy::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void TurnToEnemy::Begin
	(
	Actor &self
	)

	{
	seek.Begin( self );

	self.SetAnim( "idle" );
	}

void TurnToEnemy::AnimDone
	(
	Event *ev
	)

	{
	anim_done = true;
	}
	

qboolean	TurnToEnemy::Evaluate
	(
	Actor &self
	)

	{
	str turn_anim_name;
	Vector dir;

	if ( !self.currentEnemy )
		return false;

	self.angles.AngleVectors( &dir );

	if ( use_last_known_position )
		seek.SetTargetPosition( self.last_known_enemy_pos );
	else
		seek.SetTargetPosition( self.currentEnemy->origin );

	seek.SetTargetVelocity( vec_zero );
	seek.SetPosition( self.centroid );
	seek.SetDir( dir );
	seek.Evaluate( self );

	// See if we have turned all of the way to the enemy position
	
	if ( seek.steeringforce[YAW] < .5 && seek.steeringforce[YAW] > -.5 )
		seek.steeringforce[YAW] = 0;

	// Make sure we are not turning faster than out turn speed

	if ( seek.steeringforce[YAW] > turn_speed )
		{
		seek.steeringforce[YAW] = turn_speed;
		}

	if ( seek.steeringforce[YAW] < -turn_speed )
		{
		seek.steeringforce[YAW] = -turn_speed;
		}

	seek.steeringforce[PITCH] = 0;
	seek.steeringforce[ROLL]  = 0;

	// Set the correct animation (left or right)

	if ( seek.steeringforce[YAW] > 0 )
		turn_anim_name = left_anim;
	else if ( seek.steeringforce[YAW] < 0 )
		turn_anim_name = right_anim;
	else if ( anim_done )
		turn_anim_name = "idle";
	else
		turn_anim_name = self.animname.c_str();

	if ( turn_anim_name != self.animname )
		self.SetAnim( turn_anim_name, EV_Actor_NotifyBehavior );

	// Actually turn here

	self.Accelerate( seek.steeringforce );

	// See if we have turned all of the way to the enemy position
	
	if ( seek.steeringforce[YAW] < turn_speed && seek.steeringforce[YAW] > -turn_speed && !forever )
		return false;

	anim_done = false;

	return true;
	}

void TurnToEnemy::End
	(
	Actor &self
	)

	{
	seek.End( self );
	}

/****************************************************************************

  PickupEntity Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, PickupEntity, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ NULL, NULL }
	};

void PickupEntity::SetArgs
	(
	Event *ev
	)

	{
	ent_to_pickup    = ev->GetEntity( 1 );
	pickup_anim_name = ev->GetString( 2 );
	}

void PickupEntity::Begin
	(
	Actor &self
	)

	{
	anim_done = false;
	self.pickup_ent = ent_to_pickup;

	self.SetAnim( pickup_anim_name.c_str(), EV_Actor_NotifyBehavior );
	}

void PickupEntity::AnimDone
	(
	Event *ev
	)

	{
	anim_done = true;
	}
	

qboolean	PickupEntity::Evaluate
	(
	Actor &self
	)

	{
	if ( !ent_to_pickup )
		return false;

	if ( anim_done )
		return false;

	return true;
	}

void PickupEntity::End
	(
	Actor &self
	)

	{
	self.SetAnim( "idle" );
	self.pickup_ent = NULL;
	}

/****************************************************************************

  ThrowEntity Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, ThrowEntity, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ NULL, NULL }
	};

void ThrowEntity::SetArgs
	(
	Event *ev
	)

	{
	throw_anim_name = ev->GetString( 1 );
	}

void ThrowEntity::Begin
	(
	Actor &self
	)

	{
	anim_done = false;
	self.SetAnim( throw_anim_name, EV_Actor_NotifyBehavior );
	}

void ThrowEntity::AnimDone
	(
	Event *ev
	)

	{
	anim_done = true;
	}
	

qboolean	ThrowEntity::Evaluate
	(
	Actor &self
	)

	{
	if ( anim_done )
		return false;

	return true;
	}

void ThrowEntity::End
	(
	Actor &self
	)

	{
	self.SetAnim( "idle" );
	}



/****************************************************************************
*****************************************************************************

  Behaviors for specific creatures

*****************************************************************************
****************************************************************************/



/****************************************************************************

  BurrowAttack Class Definition

****************************************************************************/

#define BURROW_MODE_MOVING  0
#define BURROW_MODE_ATTACK  1

CLASS_DECLARATION( Behavior, BurrowAttack, NULL )
	{
		{ NULL, NULL }
	};

void BurrowAttack::SetArgs
	(
	Event *ev
	)

	{
	use_last_known_position = ev->GetBoolean( 1 );
	}

void BurrowAttack::Begin
	(
	Actor &self
	)

	{
	Vector attack_dir;
	Vector start_pos;
	Vector end_pos;
	trace_t trace;

	if ( self.animname != "idle_down" )
		self.SetAnim( "idle_down" );

	// Setup our goal point

	if ( self.currentEnemy )
		{
		if ( use_last_known_position )
			goal = self.last_known_enemy_pos;
		else
			goal = self.currentEnemy->origin;

		start_pos = goal + "0 0 10";
		end_pos = start_pos + "0 0 -250";

		trace = G_Trace( start_pos, vec_zero, vec_zero, end_pos, NULL, MASK_DEADSOLID, false, "BurrowAttack::Begin" );

		goal = trace.endpos;
		}

	// Setup our starting point, a little ways in front of our origin

	attack_dir = goal - self.origin;

	too_close = false;

	if ( attack_dir.length() < 300 )
		too_close = true;

	attack_dir.normalize();

	attack_origin = self.origin + attack_dir * 100;

	burrow_mode = BURROW_MODE_MOVING;

	stage = self.stage;

	burrow_speed = 80;

	if ( stage == 3 )
		{
		attacks_left = 2;
		}
	else if ( stage == 4 )
		{
		attacks_left = 3 + G_Random( 3 );
		burrow_speed = 120;
		}
	}

qboolean	BurrowAttack::Evaluate
	(
	Actor &self
	)

	{
	Vector attack_dir;
	Vector new_origin;
	float total_dist;
	Vector start_pos;
	Vector end_pos;
	Animate *dirt;
	trace_t trace;
	Vector temp_angles;
	int cont;
	Vector temp_endpos;

	if ( !self.currentEnemy )
		return false;

	if ( too_close )
		return false;

	switch ( burrow_mode )
		{
		case BURROW_MODE_MOVING :

			attack_dir = goal - attack_origin;
			total_dist = attack_dir.length();
			attack_dir.normalize();

			if ( total_dist < burrow_speed )
				{
				new_origin = goal;
				}
			else
				{
				new_origin = attack_origin + attack_dir * burrow_speed;
				total_dist = burrow_speed;
				}

			// Spawn in dirt or water

			start_pos = attack_origin + attack_dir + "0 0 10";
			end_pos = start_pos + "0 0 -250";

			trace = G_Trace( start_pos, vec_zero, vec_zero, end_pos, NULL, MASK_DEADSOLID | MASK_WATER, false, "BurrowAttack" );

			temp_endpos = trace.endpos;
			temp_endpos -=  "0 0 5";
			cont = gi.pointcontents( temp_endpos, 0 );

			dirt = new Animate;

			dirt->setOrigin( trace.endpos );

			temp_angles = vec_zero;

			if (cont & MASK_WATER)
				dirt->setModel( "fx_splashsmall.tik" );
			else
				dirt->setModel( "fx_dirtcloud.tik" );

			dirt->setAngles( temp_angles );

			dirt->RandomAnimate( "idle" );

			dirt->PostEvent( EV_Remove, 5 );

			attack_origin = new_origin;

			if ( attack_origin == goal )
				{
				// Got to our goal position, do attack

				if ( stage == 1 )
					{
					SpawnArm( self, leg1, attack_origin + " 25  25 0", "attack1", 0 );
					SpawnArm( self, leg2, attack_origin + " 25 -25 0", "attack1", 0 );
					SpawnArm( self, leg3, attack_origin + "-25  25 0", "attack1", 0 );
					SpawnArm( self, leg4, attack_origin + "-25 -25 0", "attack1", 0 );
					}
				else if ( stage == 2 )
					{
					SpawnArm( self, leg1, attack_origin + " 25   0 0", "attack2",   0 );
					SpawnArm( self, leg2, attack_origin + "-25  25 0", "attack2", 120 );
					SpawnArm( self, leg3, attack_origin + "-25 -25 0", "attack2", 240 );
					}
				else
					{
					SpawnArm( self, leg1, attack_origin, "attack1", 0 );
					}

				burrow_mode = BURROW_MODE_ATTACK;
				}

			break;
		case BURROW_MODE_ATTACK :

			// Wait until all of the legs are done
			
			if ( !leg1 && !leg2 && !leg3 && !leg4 )
				{
				if ( self.animname != "idle_down" )
					self.SetAnim( "idle_down" );

				if ( stage == 1 || stage == 2 )
					{
					return false;
					}
				else
					{
					attacks_left--;

					if ( attacks_left > 0 )
						{
						if ( use_last_known_position )
							if ( self.CanReallySee( self.currentEnemy ) )
								goal = self.currentEnemy->origin;
							else
								return false;
						else
							goal = self.currentEnemy->origin;

						burrow_mode = BURROW_MODE_MOVING;
						}
					else
						{
						return false;
						}
					}
				}

			break;
		}

	return true;
	}

void BurrowAttack::SpawnArm
	(
	Actor &self,
	AnimatePtr &leg,
	Vector arm_origin,
	const char *anim_name,
	float angle
	)

	{
	Vector angles;
	trace_t trace;
	Vector start_pos;
	Vector end_pos;
	str anim_to_play;
	Animate *leg_animate_ptr;
	Vector dir;
	Animate *dirt;


	// Find correct spot to spawn

	arm_origin[2] = -575;

	start_pos = arm_origin + "0 0 64";
	end_pos = arm_origin - "0 0 100";

	//trace = G_Trace( start_pos, Vector(-5, -5, 0), Vector(5, 5, 0), end_pos, NULL, MASK_DEADSOLID, false, "BurrowAttack" );
	trace = G_Trace( start_pos, Vector(-10, -10, 0), Vector(10, 10, 0), end_pos, NULL, MASK_DEADSOLID, false, "BurrowAttack" );

	arm_origin = trace.endpos;

	// Make sure can spawn here

	end_pos = arm_origin + "0 0 50";

	trace = G_Trace( arm_origin, Vector(-10, -10, 0), Vector(10, 10, 0), end_pos, NULL, MASK_DEADSOLID, false, "BurrowAttack" );

	if ( trace.fraction < 1 || trace.startsolid || trace.allsolid )
		{
		if ( trace.entityNum == ENTITYNUM_WORLD || !( trace.ent && trace.ent->entity && trace.ent->entity->takedamage ) )
			return;
		}

	// Spawn some dirt

	dirt = new Animate;

	dirt->setOrigin( arm_origin );
	dirt->setModel( "fx_dirtcloud.tik" );
	dirt->setAngles( vec_zero );
	dirt->RandomAnimate( "idle" );
	dirt->PostEvent( EV_Remove, 5 );
	
	// Spawn leg

	leg = new Animate;

	leg->setModel( "vmama_arm.tik" );
	leg->setOrigin( arm_origin );

	leg->ProcessPendingEvents();

	//leg->edict->clipmask	= MASK_MONSTERSOLID;
	leg->setContents( 0 );
	leg->setSolidType( SOLID_NOT );

	leg->PostEvent( EV_BecomeNonSolid, 0 );

	angles = vec_zero;
	angles[YAW] = angle;

	leg->setAngles( angles );

	anim_to_play = anim_name;

	// See if we should get stuck or not

	if ( strcmp( anim_name, "attack1" ) == 0 )
		{
		end_pos = arm_origin + "0 0 250";

		leg_animate_ptr = leg;

		trace = G_Trace( arm_origin, Vector(-5, -5, 0), Vector(5, 5, 0), end_pos, leg_animate_ptr, MASK_DEADSOLID, false, "BurrowAttack" );

		if ( trace.fraction != 1.0 )
			{
			if ( self.animname != "struggle" )
				self.SetAnim( "struggle" );

			anim_to_play = "getstuck";
			}
		}

	// Damage entities in way

	if ( strcmp( anim_name, "attack1" ) == 0 )
		{
		start_pos = arm_origin;
		end_pos = arm_origin + "0 0 250";

		dir = Vector ( G_CRandom( 5 ), G_CRandom( 5 ), 10 );
		}
	else
		{
		start_pos = arm_origin + "0 0 10";

		angles.AngleVectors( &dir );

		end_pos = start_pos + dir * 250;
		}

	leg_animate_ptr = leg;

	MeleeAttack( start_pos, end_pos, 50, &self, MOD_IMPALE, 10, 0, 0, 100 );

	leg->RandomAnimate( anim_to_play.c_str(), EV_Remove );
	}

void BurrowAttack::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  CircleEnemy Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, CircleEnemy, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void CircleEnemy::SetArgs
	(
	Event *ev
	)

	{
	center_part_name = ev->GetString( 1 );
	}

void CircleEnemy::Begin
	(
	Actor &self
	)

	{
	ent_to_circle = self.currentEnemy;
	last_angle_change = 0;
	}

float CircleEnemy::GetAngleDiff
	(
	Actor &self,
	Actor *center_actor,
	Vector origin
	)

	{
	Vector dir;
	Vector enemy_angles;
	Vector actor_angles;
	float angle_diff;

	dir = ent_to_circle->origin - center_actor->origin;
	enemy_angles = dir.toAngles();

	dir = origin - center_actor->origin;
	actor_angles = dir.toAngles();

	angle_diff = AngleDelta( actor_angles[YAW], enemy_angles[YAW] );

	return angle_diff;
	}

#define MAX_CIRCLE_ACCELERATION  .125
#define MAX_CIRCLE_VELOCITY  10

qboolean	CircleEnemy::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;
	Actor *center_actor;
	Vector actor_angles;
	float angle_diff;
	float other_angle_diff;
	float abs_angle_diff;
	float other_abs_angle_diff = 180;
	float angle_change = MAX_CIRCLE_VELOCITY;
	float length;
	float real_angle_change;
	Actor *other;


	if ( !ent_to_circle )
		return false;

	center_actor = self.FindPartActor( center_part_name.c_str() );

	if ( !center_actor )
		return false;

	angle_diff = GetAngleDiff( self, center_actor, self.origin );

	if ( angle_diff < 0 )
		abs_angle_diff = -angle_diff;
	else
		abs_angle_diff = angle_diff;

	other = self.FindPartActor( self.part_name );

	if ( other )
		{
		other_angle_diff = GetAngleDiff( self, center_actor, other->origin );

		if ( other_angle_diff < 0 )
			other_abs_angle_diff = -other_angle_diff;
		else
			other_abs_angle_diff = other_angle_diff;
		}

	if ( abs_angle_diff < other_abs_angle_diff )
		{
		// Turn towards enemy

		if ( abs_angle_diff < angle_change )
			angle_change = abs_angle_diff;

		if ( angle_diff < 0 )
			real_angle_change = angle_change;
		else
			real_angle_change = -angle_change;
		}
	else
		{
		// Turn away from enemy

		if ( 180 - abs_angle_diff < angle_change )
			angle_change = 180 - abs_angle_diff;

		if ( angle_diff < 0 )
			real_angle_change = -angle_change;
		else
			real_angle_change = angle_change;
		}

	if ( real_angle_change < 1.0 && real_angle_change > -1.0 )
		real_angle_change = 0;

	if ( real_angle_change > 0 )
		{
		if ( real_angle_change > last_angle_change + MAX_CIRCLE_ACCELERATION )
			real_angle_change = last_angle_change + MAX_CIRCLE_ACCELERATION;
		}
	else if ( real_angle_change < 0 )
		{
		if ( real_angle_change < last_angle_change - MAX_CIRCLE_ACCELERATION )
			real_angle_change = last_angle_change - MAX_CIRCLE_ACCELERATION;
		}

	last_angle_change = real_angle_change;

	dir = self.origin - center_actor->origin;
	length = dir.length();

	actor_angles = dir.toAngles();
	actor_angles[YAW] += real_angle_change;

	// Find new position 

	actor_angles.AngleVectors( &dir, NULL, NULL );

	dir *= length;
	dir.z = 0;

	self.setOrigin( center_actor->origin + dir );

	// Set the actors angle to look at the center

	dir[0] = -dir[0];
	dir[1] = -dir[1];
	dir[2] = -dir[2];

	self.angles[YAW] = dir.toYaw();
	self.setAngles( self.angles );

	return true;
	}

void CircleEnemy::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  ShockWater Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, ShockWater, NULL )
	{
		{ NULL, NULL }
	};

ShockWater::ShockWater()
	{
	left_beam   = NULL;
	right_beam  = NULL;
	center_beam = NULL;
	already_started = false;
	}

void ShockWater::Begin
	(
	Actor &self
	)

	{
	}

qboolean	ShockWater::Evaluate
	(
	Actor &self
	)

	{
	Vector left_tag_orig;
	Vector right_tag_orig;
	Vector end_pos;
	Vector center_point;
	Actor *center_actor;
	trace_t  trace;
	Entity *hit_entity;
	Vector diff_vect;
	float diff;
	Vector dir;

	if ( !self.currentEnemy )
		return false;

	if ( self.newanimnum == -1 && !already_started )
		{
		// Get tag positions
		self.GetTag( "tag_left",  &left_tag_orig );
		self.GetTag( "tag_right", &right_tag_orig );

		// Get end position
		end_pos = left_tag_orig + right_tag_orig;
		end_pos *= .5;
		end_pos[2] -= 120;

		dir = end_pos - self.origin;
		dir.z = 0;
		dir *= 0.5;

		end_pos += dir;

		// Add the left and right beams
      left_beam   = CreateBeam( NULL, "emap1", left_tag_orig, end_pos, 10, 1.5f, 0.2f );
		right_beam  = CreateBeam( NULL, "emap1", right_tag_orig, end_pos, 10, 1.5f, 0.2f );
      
		center_actor = self.FindPartActor( "body" );
		if ( center_actor )
         {
			center_point = center_actor->origin;
         }

		trace = G_Trace( center_point, vec_zero, vec_zero, end_pos, &self, MASK_SHOT, false, "ShockAttack" );
		if ( trace.fraction < 1.0 && trace.entityNum != center_actor->entnum )
			{
			hit_entity = G_GetEntity( trace.entityNum );
			if ( hit_entity )
            {
				center_point = hit_entity->origin;
            }
			}
		else
			{
			// Shock head
			center_actor->AddStateFlag( STATE_FLAG_IN_PAIN );

			center_actor->SpawnEffect( "fx_elecstrike.tik", center_actor->origin );
			center_actor->Sound( "sound/weapons/sword/electric/hitmix2.wav", 0, 1, 500 );
			}

      // create the center beam
      center_beam = CreateBeam( NULL, "emap1", end_pos, center_point, 20, 3.0f, 0.2f );

		// Damage player if in water
		if ( center_actor )
			{
			diff_vect = self.currentEnemy->origin - center_actor->origin;
			diff_vect[2] = 0;

			diff = diff_vect.length();
			//if ( diff < 240 && self.currentEnemy->groundentity )
			if ( diff < 350 && self.currentEnemy->groundentity )
				{
				self.currentEnemy->Damage( &self, &self, 10, Vector (0, 0, 0), Vector (0, 0, 0), Vector (0, 0, 0), 0, 0, MOD_ELECTRICWATER );
				}
			}
		already_started = true;
		}

	return true;
	}

void ShockWater::End
	(
	Actor &self
	)

	{
   delete left_beam;
	delete right_beam;
	delete center_beam;
	}

/****************************************************************************

  Shock Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Shock, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};
	
Shock::Shock()
	{
	beam = NULL;
	damage = 10;
	already_started = false;
	random_angle = 0;
	}

void Shock::SetArgs
	(
	Event *ev
	)

	{
	tag_name = ev->GetString( 1 );
	
	if ( ev->NumArgs() > 1 )
      {
		damage = ev->GetInteger( 2 );
      }

	if ( ev->NumArgs() > 2 )
      {
		random_angle = ev->GetFloat( 3 );
      }
	}

void Shock::Begin
	(
	Actor &self
	)

	{
	}

qboolean	Shock::Evaluate
	(
	Actor &self
	)

	{
	Vector tag_orig;
	Vector angles;
	Vector end_pos;
	trace_t  trace;
	Vector dir;
	float yaw_diff;


	if ( !self.currentEnemy )
		return false;

	if ( self.newanimnum == -1 && !already_started )
		{
		// Get tag position
		if ( tag_name.length() == 0 )
         {
			return false;
         }

		self.GetTag( tag_name.c_str(), &tag_orig );

		// See if the enemy is in front of us

		dir = self.currentEnemy->origin - self.origin;
		angles = dir.toAngles();

		yaw_diff = AngleNormalize180( angles[YAW] - self.angles[YAW] );

		if ( yaw_diff < 60 && yaw_diff > -60 )
			{
			// The enemy is in front of us

			angles[YAW] += G_CRandom( random_angle );

			angles.AngleVectors( &end_pos, NULL, NULL );
			end_pos *= 500;
			end_pos += tag_orig;
			end_pos.z -= 100;
			}
		else
			{
			// Get end position
			angles = self.angles;

			angles[YAW] += G_Random( random_angle ) - random_angle / 2;
			angles[PITCH] = 0;
			angles[ROLL] = 0;

			angles.AngleVectors( &end_pos, NULL, NULL );
			end_pos *= 500;
			end_pos += tag_orig;
			end_pos.z -= 100;
			}

		trace = G_Trace( tag_orig, Vector (-15, -15, -15), Vector (15, 15, 15), end_pos, &self, MASK_SHOT, false, "ShockAttack" );

		if ( trace.fraction < 1.0 && trace.entityNum == self.currentEnemy->entnum )
			{
			end_pos = self.currentEnemy->centroid;
			dir = end_pos - tag_orig;
			dir.normalize();
			self.currentEnemy->Damage( &self, &self, damage, vec_zero, dir, vec_zero, 0, 0, MOD_ELECTRIC );
			}

		// Add the beam
		beam = CreateBeam( NULL, "emap1", tag_orig, end_pos, 20, 1.5f, 0.2f );

      already_started = true;
		}
	else if ( already_started )
		{
		self.GetTag( tag_name.c_str(), &tag_orig );

		if ( beam )
			beam->setOrigin( tag_orig );
		}

	return true;
	}

void Shock::End
	(
	Actor &self
	)

	{
	if ( beam )
		{
		beam->ProcessEvent( EV_Remove );
		beam = NULL;
		}
	}

/****************************************************************************

  CircleAttack Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, CircleAttack, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};
	
CircleAttack::CircleAttack()
	{
	}

void CircleAttack::SetArgs
	(
	Event *ev
	)

	{
	command   = ev->GetString( 1 );
	direction = ev->GetString( 2 );
	}

Actor *CircleAttack::FindClosestPart
	( 
	Actor &self,
	float angle
	)
	{
	float closest_diff = 360;
	int i;
	part_t *part;
	Entity *partent;
	Actor *partact;
	Vector dir;
	Vector angles;
	float angle_diff;
	Actor *closest_part = NULL;

	for( i = 1 ; i <= self.parts.NumObjects(); i++ )
		{
		part = &self.parts.ObjectAt( i );

		partent = part->ent;
		partact = ( Actor * )partent;

		if ( partact && partact->part_name == "smallarm" )
			{
			dir = partact->origin - self.origin;
			angles = dir.toAngles();

			angle_diff = AngleDelta( angles[ YAW ], angle );

			if ( angle_diff < 0 )
            {
				angle_diff = -angle_diff;
            }

			if ( angle_diff < closest_diff )
				{
				closest_part = partact;
				closest_diff = angle_diff;
				}
			}
		}

	return closest_part;
	}

void CircleAttack::Begin
	(
	Actor &self
	)

	{
	float random_direction;
	Actor *closest_part;

	// Pick which arm to start with
	random_direction = G_Random( 360 );

	closest_part = FindClosestPart( self, random_direction );
	if ( closest_part != NULL )
		{
		first_part   = closest_part;
		current_part = closest_part;

		closest_part->command = command;
		next_time = level.time + 0.2f;
		}

	current_direction = 1;

	if ( direction == "counterclockwise" )
      {
		current_direction = 0;
      }

	number_of_attacks = 1;
	}

qboolean	CircleAttack::Evaluate
	(
	Actor &self
	)

	{
	Entity *current_part_entity;
	Actor *current_part_actor;
	Vector dir;
	Vector angles;
	Actor *closest_part;

	if ( level.time >= next_time )
		{
		current_part_entity = current_part;
		current_part_actor = ( Actor * )current_part_entity;

		// Find the next part

		dir = current_part_actor->origin - self.origin;
		angles = dir.toAngles();

		if ( direction == "changing" )
			{
			if ( number_of_attacks >= 20 )
            {
				return false;
            }

			if ( G_Random( 1 ) < .3 )
            {
				current_direction = !current_direction;
            }
			}

		if ( current_direction == 1 )
         {
			angles[YAW] -= 360 / 8;
         }
		else
         {
			angles[YAW] += 360 / 8;
         }

		closest_part = FindClosestPart( self, angles[YAW] );

		if ( ( closest_part == first_part ) && ( direction != "changing" ) )
         {
			return false;
         }

		current_part = closest_part;

		closest_part->command = command;
		next_time = level.time + 0.2f;

		number_of_attacks++;
		}

	return true;
	}

void CircleAttack::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  DragEnemy Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, DragEnemy, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void DragEnemy::SetArgs
	(
	Event *ev
	)

	{
	tag_name = ev->GetString( 1 );
	damage   = ev->GetInteger( 2 );

	if ( ev->NumArgs() > 2 )
		drop = ev->GetBoolean( 3 );
	else
		drop = false;
	}

void DragEnemy::Begin
	(
	Actor &self
	)

	{
	Actor *body;
	Vector dir;
	Vector angles;

	ent_to_drag = self.currentEnemy;

	attached = false;

	if ( damage > 0 && !drop )
      {
		ent_to_drag->Damage( &self, &self, damage, vec_zero, vec_zero, vec_zero, 0, 0, MOD_EAT );
      }

	body = self.FindPartActor( "body" );

	if ( body )
		{
		dir = body->origin - self.origin;
		angles = dir.toAngles();

		target_yaw = angles[ YAW ];
		last_turn_time = level.time;
		}
	else
		{
		target_yaw = self.angles[ YAW ];
		}
	}

qboolean	DragEnemy::Evaluate
	(
	Actor &self
	)

	{
	Vector orig;
	str anim_name;

	if ( ent_to_drag )
		{
		if ( drop && damage > 0 )
			{
			if ( self.GetTag( tag_name.c_str(), &orig ) )
				{
				if ( ent_to_drag->isClient() )
               {
					orig[ 2 ] -= 85;
               }
				else
					{
					offset[ 2 ] = ( ent_to_drag->absmin[ 2 ] - ent_to_drag->absmax[ 2 ] ) * 0.5f;

					if ( offset[ 2 ] < -40 )
                  {
						offset[ 2 ] -= 25;
                  }
					orig += offset;
					}

				ent_to_drag->setOrigin( orig );
				}

			ent_to_drag->Damage( &self, &self, damage, vec_zero, vec_zero, vec_zero, 0, 0, MOD_EAT );
			}

		if ( ent_to_drag->deadflag )
			return false;

		anim_name = self.AnimName();

		if ( ( anim_name == "raise" ) && ( self.newanim == "" ) )
			{
			if ( !attached )
				{
				Event *ev;

				if ( damage > 0 )
					{
					if ( ent_to_drag->isClient() )
                  {
						offset[ 2 ] -= 85;
                  }
					else
						{
						offset[ 2 ] = ( ent_to_drag->absmin[ 2 ] - ent_to_drag->absmax[ 2 ] ) * 0.5f;

						if ( offset[ 2 ] < -40 )
                     {
							offset[ 2 ] -= 25;
                     }
						}

					ev = new Event( EV_Attach );
					ev->AddEntity( &self );
					ev->AddString( tag_name.c_str() );
					ev->AddInteger( qfalse );
					ev->AddVector( offset );
					ent_to_drag->ProcessEvent( ev );

					ent_to_drag->flags |= FL_PARTIAL_IMMOBILE;
					}

				attached = true;
				}

			if ( target_yaw != self.angles[ YAW ] )
				{
				float yaw_diff = target_yaw - self.angles[ YAW ];

				if ( yaw_diff > 180 )
					{
					target_yaw -= 360;
					yaw_diff -= 360;
					}

				if ( yaw_diff < -180 )
					{
					target_yaw += 360;
					yaw_diff += 360;
					}

				if ( yaw_diff < 0 )
					{
					self.angles[ YAW ] -= 90 * (level.time - last_turn_time);

					if ( self.angles[ YAW ] < 0 )
                  {
						self.angles[ YAW ] += 360;
                  }

					if ( self.angles[ YAW ] < target_yaw )
                  {
						self.angles[ YAW ] = target_yaw;
                  }

					self.setAngles( self.angles );
					}
				else if ( yaw_diff > 0 )
					{
					self.angles[ YAW ] += 90 * (level.time - last_turn_time);

					if ( self.angles[ YAW ] > 360 )
                  {
						self.angles[ YAW ] -= 360;
                  }

					if ( self.angles[ YAW ] > target_yaw )
                  {
						self.angles[ YAW ] = target_yaw;
                  }

					self.setAngles( self.angles );
					} 

				last_turn_time = level.time;
				}
			}
		}

	return true;
	}

void DragEnemy::End
	(
	Actor &self
	)

	{
	Vector orig;
	Event *ev;
	trace_t trace;

	if ( drop || strcmp( self.currentState->getName(), "SUICIDE" ) == 0 )
		{
		ent_to_drag->flags &= ~FL_PARTIAL_IMMOBILE;

		ev = new Event( EV_Detach );
		ent_to_drag->ProcessEvent( ev );

		ent_to_drag->setSolidType( SOLID_BBOX );

		if ( self.GetTag( tag_name.c_str(), &orig ) )
			{
			trace = G_Trace( orig - "0 0 100", ent_to_drag->mins, ent_to_drag->maxs, orig, ent_to_drag, ent_to_drag->edict->clipmask, false, "DragEnemy" );

			if ( trace.allsolid )
				gi.DPrintf( "Dropping entity into a solid!\n" );

			ent_to_drag->setOrigin( trace.endpos );

			/* if ( ent_to_drag->isClient() )
            {
				offset[2] = -85;
            }
			else
				{
				offset[2] = ( ent_to_drag->absmin[2] - ent_to_drag->absmax[2] ) * 0.5;

				if ( offset[2] < -40 )
               {
					offset[2] -= 25;
               }
				}

			ent_to_drag->setOrigin( orig + offset ); */
			}
		}

	ent_to_drag->velocity = "0 0 -20";
	}

/****************************************************************************

  Spin Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Spin, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

Spin::Spin()
	{
	speed = 500.0;
	}

void Spin::SetArgs
	(
	Event *ev
	)

	{
	speed = ev->GetFloat( 1 );
	}

void Spin::Begin
	(
	Actor &self
	)

	{
	SpinningPlant *spinningPlant = (SpinningPlant *)&self;

	if ( spinningPlant->spinner_clip )
      {
		spinningPlant->spinner_clip->avelocity.y = speed;
      }
	}

qboolean	Spin::Evaluate
	(
	Actor &self
	)

	{
	return true;
	}

void Spin::End
	(
	Actor &self
	)

	{
	SpinningPlant *spinningPlant = ( SpinningPlant * )&self;

	if ( spinningPlant->spinner_clip )
      {
		spinningPlant->spinner_clip->avelocity.y = 0;
      }
	}

/****************************************************************************

  Digest Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Digest, NULL )
	{
		{ &EV_Behavior_AnimDone,	AnimDone },
		{ NULL, NULL }
	};


void Digest::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void Digest::Begin
	(
	Actor &self
	)

	{
	float range = 150;
	Entity *ent_in_range;

	// Init some stuff
	spitting = false;
	spit = false;
	yuck = false;

	self.SetAnim( "digest" );

	// Default digest time to current level time

	digest_time = level.time;

	// See if we caught anything

   ent_in_range = findradius( NULL, self.origin, range );

	while ( ent_in_range )
		{
		if ( 
            ( &self != ent_in_range ) && 
			   ( ent_in_range->movetype != MOVETYPE_NONE ) &&
			   ( ent_in_range->movetype != MOVETYPE_STATIONARY ) &&
            !(ent_in_range->flags & FL_NOTARGET) && 
            !ent_in_range->deadflag && 
            ent_in_range->health > 0 
         )
         {
			if ( Vector( self.origin - ent_in_range->origin ).length() < range )
				Eat( ent_in_range, self );
         }

		ent_in_range = findradius( ent_in_range, self.origin, range );
		}

	// Make sure to spit out immediately if its yucky

	if ( yuck )
		digest_time = 0;

	// Make sure we are solid will digesting things

	self.setContents( CONTENTS_SOLID );
	self.setSize( "-32 -32 0", "32 32 192" );
	}

void Digest::Eat
	(
	Entity *food,
	Actor &self
	)

	{
	float mass;
	SafePtr<class Entity> food_ptr = food;

	// Hide the caught entity

	food->hideModel();
	food->flags |= FL_IMMOBILE;

	food->origin[0] = self.centroid[0];
	food->origin[1] = self.centroid[1];
	food->origin[2] = self.centroid[2];

	food->setOrigin( food->origin );

	// See if we want to eat this or spit out immediately

	if ( food->edict->s.eFlags & EF_ANTISBJUICE )
		yuck = true;

	// Add to the digest time

	mass = food->mass;

	if ( mass < 50 )
		mass = 50;

	if ( mass > 300 )
		mass = 300;

	digest_time += ( mass / 50 ) + 1;

	foodlist.AddObject( food_ptr );

	// Extinguish fire on this entity if on fire

	food->ProcessEvent( EV_Sentient_StopOnFire );

	if ( !yuck && food->isSubclassOf( Player ) )
		food->Sound( "snd_longdeath" );
	}

qboolean	Digest::Evaluate
	(
	Actor &self
	)

	{
	Vector   dir;
	Entity   *food;
	int      i;
	float	   m;
	Vector   momentum;
	Entity   *targetent;
	qboolean killed;

	if ( !spitting && digest_time < level.time )
		{
		if ( foodlist.NumObjects() > 0 )
			{
			// Done digesting, start spitting anim
			spitting = true;
			anim_done = false;
			self.SetAnim( "spit", EV_Actor_NotifyBehavior );
			spit_time = level.time + 0.25;
			}
		else
			{
			self.setSize( "-64 -64 0", "64 64 32" );
			self.ProcessEvent( EV_ActorOnlyShootable );
			return false;
			}
		}

	if ( spitting && !spit && spit_time < level.time)
		{
		spit = true;

		self.setSize( "-64 -64 0", "64 64 32" );
		self.ProcessEvent( EV_ActorOnlyShootable );

		// Spit all of the digested entities out
		for( i = 1 ; i <= foodlist.NumObjects() ; i++ )
			{
			food = foodlist.ObjectAt( i );

			if ( food != NULL )
				{
				killed = false;

				// Only damage the entity if we digested it
				if ( !yuck )
               {
					food->Damage( &self, &self, 1000, Vector (0, 0, 0), Vector (0, 0, 0), Vector (0, 0, 0), 0, 0, MOD_EAT );

					if ( food->health <= 0 )
						killed = true;
               }

				food->origin[0] = self.centroid[0];
				food->origin[1] = self.centroid[1];
				food->origin[2] = self.centroid[2];

				if ( food->mass < 50 )
					{
					m = 50;
					}
				else
					{
					m = food->mass;
					}

				if ( killed )
					{
					Event *event;
					int number_of_gibs;

					// Entity was killed, just spit out some gibs

					food->origin[2] += 60;

					food->setOrigin( food->origin );

					number_of_gibs = ( ( m - 50 ) / 300 ) * 5 + 2;

					if ( number_of_gibs > 7 )
						number_of_gibs = 7;

					event = new Event( EV_Sentient_SpawnBloodyGibs );
					event->AddInteger( number_of_gibs );
					food->PostEvent( event, 0 );

					event = new Event( EV_Sentient_SpawnBloodyGibs );
					event->AddInteger( number_of_gibs );
					food->PostEvent( event, 0 );

					if ( !food->isSubclassOf( Player ) )
						food->PostEvent( EV_Remove, 0 );
					}
				else
					{
					// Entity wasn't killed spit it out

					food->setOrigin( food->origin );

					food->showModel();
					food->flags ^= FL_IMMOBILE;

					// Spit the entity out

					targetent = NULL;
					if ( self.target.length() > 0 )
						{
						// Spit the entity to the targeted position
						targetent = G_FindTarget( &self, self.target.c_str() );
						}

					if ( targetent )
						{
						food->velocity = G_CalculateImpulse( food->origin, targetent->origin, 350, 1 );
						}
					else
						{
						// Spit the entity to a random place
						dir[0] = G_Random( 200 ) - 100;
						dir[1] = G_Random( 200 ) - 100;
						dir[2] = 200;

						dir.normalize();

						momentum = dir * ( 500.0f * 500 / m );
						food->velocity += momentum;
						}
               food->VelocityModified();
					}
				}
			}
		}

	if ( spitting && anim_done )
	   {
		// We are done spitting
		return false;
	   }

	return true;
	}

void Digest::AnimDone
	(
	Event *ev
	)

	{
	anim_done = true;
	}

void Digest::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  Teleport Class Definition

****************************************************************************/

#define TELEPORT_BEHIND   0
#define TELEPORT_TOLEFT   1
#define TELEPORT_TORIGHT  2
#define TELEPORT_INFRONT  3

#define TELEPORT_NUMBER_OF_POSITIONS  4

CLASS_DECLARATION( Behavior, Teleport, NULL )
	{
		{ NULL, NULL }
	};


void Teleport::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void Teleport::Begin
	(
	Actor &self
	)

	{
	
	}

qboolean	Teleport::TestPosition
	(
	Actor &self,
	int test_pos,
	Vector &good_position,
	qboolean	use_enemy_dir
	)
	{
	Vector test_position;
	Vector enemy_angles;
	Vector enemy_forward;
	Vector enemy_left;
	trace_t trace;


	// Get the position to test

	if ( use_enemy_dir )
		{
		// Get the enemy direction info

		enemy_angles = self.currentEnemy->angles;
		enemy_angles.AngleVectors( &enemy_forward, &enemy_left );

		test_position = self.currentEnemy->origin;
		
		if ( test_pos == TELEPORT_BEHIND )
			test_position -= enemy_forward * 75;
		else if ( test_pos == TELEPORT_INFRONT )
			test_position += enemy_forward * 75;
		else if ( test_pos == TELEPORT_TOLEFT )
			test_position += enemy_left * 75;
		else 
			test_position -= enemy_left * 75;
		}
	else
		{
		test_position = self.currentEnemy->origin;
		
		if ( test_pos == TELEPORT_BEHIND )
			test_position += "-60 0 0";
		else if ( test_pos == TELEPORT_INFRONT )
			test_position += "60 0 0";
		else if ( test_pos == TELEPORT_TOLEFT )
			test_position += "0 -60 0";
		else 
			test_position += "0 60 0";
		}

	//test_position += "0 0 16";
	test_position += "0 0 64";

	// Test to see if we can fit at the new position

	trace = G_Trace( test_position, self.mins, self.maxs, test_position - "0 0 1000", &self, self.edict->clipmask, false, "Teleport::TestPosition" );

	if ( trace.allsolid || trace.startsolid )
	//if ( trace.allsolid )
		return false;

	// Make sure we can see the enemy from this position
	
	//if ( !self.CanSeeEnemyFrom( trace.endpos ) )
	if ( !self.IsEntityAlive( self.currentEnemy ) || !self.CanSeeFrom( trace.endpos, self.currentEnemy ) )
		return false;

	// This is a good position

	good_position = trace.endpos;
	return true;
	}

qboolean	Teleport::Evaluate
	(
	Actor &self
	)

	{
	int current_position;
	float random_number;
	Vector teleport_position;
	qboolean teleport_position_found;
	Vector new_position;
	int i;
	Vector dir;
	Vector angles;


	// Make sure we stll have an enemy to teleport near

	if ( !self.currentEnemy )
		return false;

	// Default the teleport position to where we are now

	teleport_position = self.origin;
	teleport_position_found = false;

	// Determine which position to try first

	random_number = G_Random();

	if ( random_number < .5 )
		current_position = TELEPORT_BEHIND;
	else if ( random_number < .7 )
		current_position = TELEPORT_TOLEFT;
	else if ( random_number < .9 )
		current_position = TELEPORT_TORIGHT;
	else
		current_position = TELEPORT_INFRONT;

	// Try positions

	for( i = 0 ; i < TELEPORT_NUMBER_OF_POSITIONS ; i++ )
		{
		// Test this position

		if ( TestPosition( self, current_position, new_position, true ) )
			{
			teleport_position = new_position;
			teleport_position_found = true;
			break;
			}

		// Try the next position

		current_position++;

		if ( current_position >= TELEPORT_NUMBER_OF_POSITIONS )
			current_position = 0;
		}

	if ( !teleport_position_found )
		{
		// Try again with not using the enemies angles

		if ( current_position >= TELEPORT_NUMBER_OF_POSITIONS )
			current_position = 0;

		for( i = 0 ; i < TELEPORT_NUMBER_OF_POSITIONS ; i++ )
			{
			// Test this position

			if ( TestPosition( self, current_position, new_position, false ) )
				{
				teleport_position = new_position;
				teleport_position_found = true;
				break;
				}

			// Try the next position

			current_position++;

			if ( current_position >= TELEPORT_NUMBER_OF_POSITIONS )
				current_position = 0;
			}
		}

	// Do teleport stuff

	if ( teleport_position_found )
		{
		self.setOrigin( teleport_position );
		self.NoLerpThisFrame();

		dir = self.currentEnemy->origin - teleport_position;
		angles = dir.toAngles();

		angles[ROLL] = 0;
		angles[PITCH] = 0;

		self.setAngles( angles );

		if ( self.currentEnemy->isSubclassOf( Player ) )
			{
			Player *player = (Player *)(Entity *)self.currentEnemy;

			player->RemoveTarget( &self );
			}
		}

	return false;
	}

void Teleport::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  TeleportToPosition Class Definition

****************************************************************************/


CLASS_DECLARATION( Behavior, TeleportToPosition, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void TeleportToPosition::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void TeleportToPosition::SetArgs
	(
	Event *ev
	)

	{
	teleport_position_name = ev->GetString( 1 );
	number_of_teleport_positions = ev->GetInteger( 2 );
	}

void TeleportToPosition::Begin
	(
	Actor &self
	)

	{
	}

qboolean	TeleportToPosition::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;
	Vector angles;
	trace_t trace;
	str pathnode_name;
	PathNode *goal;
	Vector teleport_position;
	Vector attack_position;
	float half_height;
	Animate *effect;


	// Get the pathnode name to teleport to

	pathnode_name = teleport_position_name;
	pathnode_name += (int)( G_Random( number_of_teleport_positions ) + 1 );

	// Find the path node

	goal = AI_FindNode( pathnode_name );

	if ( !goal )
		{
		gi.DPrintf( "Can't find position %s\n", pathnode_name.c_str() );
		return false;
		}

	// Set the teleport position

	teleport_position = goal->origin;

	// Kill anything at this position

	half_height = self.maxs.z / 2;
	attack_position = teleport_position;
	attack_position.z += half_height;

	MeleeAttack( attack_position, attack_position, 10000, &self, MOD_TELEFRAG, self.maxs.x, -half_height, half_height, 0 );

	// Test to see if we can fit at the new position

	trace = G_Trace( teleport_position + "0 0 64", self.mins, self.maxs, teleport_position - "0 0 128", &self, MASK_PATHSOLID, false, "TeleportToPosition" );
	//trace = G_Trace( teleport_position, self.mins, self.maxs, teleport_position, &self, MASK_PATHSOLID, false, "TeleportToPosition" );

	if ( trace.allsolid )
		{
		gi.DPrintf( "Failed to teleport to %s\n", goal->targetname.c_str() );
		return false;
		}

	teleport_position = trace.endpos;

	// Do teleport stuff

	// Spawn in teleport effect at old position

	effect = new Animate;
	effect->setModel( "fx_teleport3.tik" );
	effect->setOrigin( self.origin );
	effect->setScale( 2 );
	effect->setSolidType( SOLID_NOT );
	effect->RandomAnimate( "idle", EV_Remove );
	//effect->Sound( "snd_teleport" );

	// Set new position

	self.setOrigin( teleport_position );

	// Spawn in teleport effect at new position

	effect = new Animate;
	effect->setModel( "fx_teleport3.tik" );
	effect->setOrigin( self.origin );
	effect->setScale( 2 );
	effect->setSolidType( SOLID_NOT );
	effect->RandomAnimate( "idle", EV_Remove );
	//effect->Sound( "snd_teleport" );

	self.NoLerpThisFrame();

	if ( self.currentEnemy )
		{
		dir = self.currentEnemy->origin - teleport_position;
		angles = dir.toAngles();

		angles[ROLL] = 0;
		angles[PITCH] = 0;

		self.setAngles( angles );

		if ( self.currentEnemy->isSubclassOf( Player ) )
			{
			Player *player = (Player *)(Entity *)self.currentEnemy;

			player->RemoveTarget( &self );
			}
		}

	return false;
	}

void TeleportToPosition::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************

  GhostAttack Class Definition

****************************************************************************/

#define GHOST_ATTACK_START  0
#define GHOST_ATTACK_END    1

#define GHOST_ATTACK_SPEED  350

CLASS_DECLARATION( Behavior, GhostAttack, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void GhostAttack::SetArgs
	(
	Event *ev
	)

	{
	real_attack = ev->GetBoolean( 1 );
	}


void GhostAttack::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void GhostAttack::Begin
	(
	Actor &self
	)

	{
	mode = GHOST_ATTACK_START;

	fly.Begin( self );
	fly.SetTurnSpeed( 25 );
	fly.SetRandomAllowed( false );
	fly.SetSpeed( GHOST_ATTACK_SPEED );

	if ( self.currentEnemy )
		attack_position = self.currentEnemy->centroid;
	else
		attack_position = self.origin;

	if ( !real_attack )
		{
		attack_position[0] += G_CRandom( 300 );
		attack_position[1] += G_CRandom( 300 );
		attack_position[2] += G_Random( 100 );
		}

	fly.SetGoalPoint( attack_position );

	attack_dir = attack_position - self.origin;

	if ( attack_dir == vec_zero )
		attack_dir = "1 1 0";

	attack_dir.normalize();

	self.Sound( "snd_fadein", CHAN_VOICE );
	}

qboolean	GhostAttack::Evaluate
	(
	Actor &self
	)

	{
	Vector dir;
	float dist;
	float zdist;
	Vector new_pos;
	float new_alpha;
	float light_radius;
	float r, g, b;
	qboolean success;
	Vector start;
	Vector end;
	Event *event;


	if ( !self.currentEnemy )
		return false;

	if ( mode == GHOST_ATTACK_START )
		{
		// Move closer to the enemy

		fly.Evaluate( self );

		// Get the new distance info

		dir = attack_position - self.origin;

		dist = dir.length();

		zdist = dir.z;

		if ( zdist < 0 )
			zdist = -zdist;

		dir.z = 0;
			
		// If we are close enough change to shootable_only

		if ( real_attack && dist < 200 )
			{
			// Attackable now

			self.setSolidType( SOLID_BBOX );
			self.setContents( CONTENTS_SHOOTABLE_ONLY );

			event = new Event( EV_Actor_SetTargetable );
			event->AddInteger( 1 );
			self.ProcessEvent( event );
			}

		// If we are close enough damage enemy and goto end mode

		start = self.origin;
		end   = self.origin + attack_dir * 1;

		if ( real_attack )
			{
			success = MeleeAttack( start, end, 7.5, &self, MOD_LIFEDRAIN, 32, 0, 64, 0 );
			self.AddStateFlag( STATE_FLAG_MELEE_HIT );
			}
		else
			success = false;

		if ( success || dist <= GHOST_ATTACK_SPEED / 40 )
			{
			// Attack mode is done go to retreat mode

			if ( self.attack_blocked && self.attack_blocked_time == level.time )
				{
				Vector retreat_angles;

				dir = attack_dir * -1;

				retreat_angles = dir.toAngles();
				retreat_angles[YAW] += G_CRandom( 45 );
				retreat_angles[PITCH] += G_CRandom( 30 );
				retreat_angles.AngleVectors( &dir );

				dir *= 500;

				self.setAngles( retreat_angles );
				}
			else
				{
				dir = attack_dir;

				dir.z = 0;
				dir.normalize();
				dir *= 1000;
				dir.z = 300;
				}

			retreat_position = self.origin + dir;

			fly.SetGoalPoint( retreat_position );

			mode = GHOST_ATTACK_END;
			}

		// Fade in depending on how close we are to attack position

		if ( dist > 400 )
			new_alpha = 0;
		else 
			new_alpha = ( 400 - dist ) / 400;

		if ( new_alpha > 0.4 )
			new_alpha = 0.4;

		r = new_alpha / 0.4;
		g = new_alpha / 0.4;
		b = new_alpha / 0.4;

		light_radius = 0;

		G_SetConstantLight( &self.edict->s.constantLight, &r, &g, &b, &light_radius );

		self.setAlpha( new_alpha );
		}
	else
		{
		// Move away from enemy

		fly.Evaluate( self );

		// Get the new distance info

		dir = attack_position - self.origin;
		dist = dir.length();

		if ( real_attack && dist > 200 )
			{
			// Not attackable again

			self.setSolidType( SOLID_NOT );
			self.setContents( 0 );

			event = new Event( EV_Actor_SetTargetable );
			event->AddInteger( 0 );
			self.ProcessEvent( event );
			}

		// Fade out depending on how far we are from the attack position

		if ( dist > 400 )
			new_alpha = 0;
		else 
			new_alpha = ( 400 - dist ) / 400;

		if ( new_alpha > 0.4 )
			new_alpha = 0.4;

		r = new_alpha / 0.4;
		g = new_alpha / 0.4;
		b = new_alpha / 0.4;

		light_radius = 0;

		G_SetConstantLight( &self.edict->s.constantLight, &r, &g, &b, &light_radius );

		self.setAlpha( new_alpha );

		// See if we are far enough to be done

		if ( new_alpha == 0 )
			return false;
		}
	return true;
	}

void GhostAttack::End
	(
	Actor &self
	)

	{
	// Make sure we can't be shot any more

	self.setSolidType( SOLID_NOT );
	self.setContents( 0 );

	fly.End( self );
	}

/****************************************************************************

  Levitate Class Definition

****************************************************************************/

CLASS_DECLARATION( Behavior, Levitate, NULL )
	{
		{ &EV_Behavior_Args,			SetArgs },
		{ NULL, NULL }
	};

void Levitate::SetArgs
	(
	Event *ev
	)

	{
	distance = ev->GetFloat( 1 );
	speed = ev->GetFloat( 2 );
	}


void Levitate::ShowInfo
	(
	Actor &self
	)

	{
   Behavior::ShowInfo( self );
	}

void Levitate::Begin
	(
	Actor &self
	)

	{
	final_z = self.origin.z + distance;
	}

qboolean	Levitate::Evaluate
	(
	Actor &self
	)

	{
	trace_t trace;
	Vector start;
	Vector end;


	start = self.origin;
	end   = self.origin;

	if ( final_z < self.origin.z )
		{
		end.z -= speed;

		if ( end.z < final_z )
			end.z = final_z;
		}
	else
		{
		end.z += speed;

		if ( end.z > final_z )
			end.z = final_z;
		}
		
	trace = G_Trace( start, self.mins, self.maxs, end, &self, self.edict->clipmask, false, "Levitate" );

	if ( trace.fraction != 1 )
		return false;

	if ( end.z == final_z )
		return false;

	self.setOrigin( trace.endpos );

	return true;
	}

void Levitate::End
	(
	Actor &self
	)

	{
	}

/****************************************************************************
*****************************************************************************

  Utility functions

*****************************************************************************
****************************************************************************/



Vector ChooseRandomDirection
   (
   Actor &self,
   Vector previousdir,
   float *time,
   int disallowcontentsmask,
   qboolean usepitch
   )
   {
   //static float x[ 9 ] = { 0, 22, -22, 45, -45, 0, 22, -22, 45 };
	static float x[ 9 ] = { 0, 22, -22, 0, 22 };
   Vector dir;
   Vector ang;
   Vector bestdir;
   Vector newdir;
   Vector step;
	Vector endpos;
	Vector groundend;
   float bestfraction;
   trace_t trace;
	trace_t groundtrace;
   int i;
   int k;
   int t;
   int u;
   int contents;
   Vector centroid;
	float random_yaw;
	float movespeed;

	if ( self.movespeed != 1 )
		movespeed = self.movespeed;
	else
		movespeed = 100;

   centroid = self.centroid - self.origin;

	step = Vector( 0, 0, STEPSIZE );
   bestfraction = -1;
   bestdir = self.origin;

	random_yaw = G_Random( 360 );

   for( i = 0; i <= 8; i++ )
      {
      t = random_yaw + i * 45;
      
      ang.y = self.angles.y + t;

      if ( usepitch )
         {
         u = ( int )G_Random( 5 );

         //for( k = 0; k < 5; k++ )
			for( k = 0; k < 3; k++ )
            {
            ang.x = x[ k + u ];
            ang.AngleVectors( &dir, NULL, NULL );

            dir *= movespeed * (*time);
            dir += self.origin;
            trace = G_Trace( self.origin, self.mins, self.maxs, dir, &self, self.edict->clipmask, false, "ChooseRandomDirection 1" );

            if ( !trace.startsolid && !trace.allsolid )
               {
               newdir = Vector( trace.endpos );

					if ( disallowcontentsmask )
						{
						contents = gi.pointcontents( ( newdir + centroid ), 0 );

						if ( contents & disallowcontentsmask )
							continue;
						}
               
               if (
                     ( trace.fraction > bestfraction ) &&
                     ( newdir != bestdir ) &&
                     ( newdir != previousdir )
                  )
                  {
                  bestdir = newdir;
                  bestfraction = trace.fraction;

						if ( bestfraction > .9 )
							{
							*time *= bestfraction;

							return bestdir;
							}
                  }
               }
            }
         }
      else
         {
         ang.x = 0;
         ang.AngleVectors( &dir, NULL, NULL );

			endpos = self.origin + dir * movespeed * (*time) + step;

         trace = G_Trace( self.origin + step, self.mins, self.maxs, endpos, &self, self.edict->clipmask, false, "ChooseRandomDirection 2" );

         if ( !trace.startsolid && !trace.allsolid )
            {
            newdir = Vector( trace.endpos );

            if ( disallowcontentsmask )
               {
               contents = gi.pointcontents( ( newdir + centroid ), 0 );

					if ( contents & disallowcontentsmask )
						continue;
					}

            if (
                  ( trace.fraction > bestfraction ) &&
                  ( newdir != bestdir ) &&
                  ( newdir != previousdir )
               )
               {
					groundend = endpos - step * 2;

					groundtrace = G_Trace( endpos, self.mins, self.maxs, groundend, &self, self.edict->clipmask, false, "Chase::ChooseRandomDirection 3" );

					if ( groundtrace.fraction == 1 )
						trace.fraction /= 2;

					if ( trace.fraction > bestfraction )
						{
						bestdir = newdir;
						bestfraction = trace.fraction;

						if ( bestfraction > .9 )
							{
							*time *= bestfraction;

							return bestdir;
							}
						}
               }
            }
         }
      }

   if ( bestfraction > 0 )
      {
      *time *= bestfraction;
      }
   else
      {
      *time = 0;
      }

   return bestdir;
   }

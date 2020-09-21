//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/entity.cpp                         $
// $Revision:: 130                                                            $
//   $Author:: Markd                                                          $
//     $Date:: 8/09/00 1:51p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/entity.cpp                              $
// 
// 130   8/09/00 1:51p Markd
// bullet proofed detachallchildren fix
// 
// 129   8/08/00 3:00p Aldie
// Fix for detachallchildren
// 
// 128   29.07.00 10:51p Jimdose
// added radius2 to gentity_t
// 
// 127   7/26/00 6:18p Aldie
// Fix for detachallchildren
// 
// 126   7/24/00 10:38a Markd
// fixed solid bsp bug
// 
// 125   7/23/00 1:47p Aldie
// Added detach all children command
// 
// 124   7/19/00 9:52p Aldie
// Put ET_EVENTS back in.  They will get sent over once, and should get
// processed once on the client.
// 
// 123   7/17/00 5:09p Markd
// added sendonce flag to svflags
// 
// 122   7/11/00 8:55p Aldie
// Added in an autoaim flag
// 
// 121   7/10/00 11:54p Markd
// added exit level code
// 
// 120   6/30/00 3:08p Markd
// fixed rise animation issues
// 
// 119   6/30/00 10:45a Markd
// added MOVETYPE_STATIONARY and revamped some physics
// 
// 118   6/27/00 5:45p Steven
// Changed HurtEvent to come from the centroid instead of the origin.
// 
// 117   6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 116   6/26/00 2:41p Markd
// put in more world protection for targetname
// 
// 115   6/26/00 2:39p Markd
// made sure that world would not be re-targeted
// 
// 114   6/24/00 7:39p Aldie
// Fixed attachmodel event to handle a failed attach return value and delete
// the object that was created.
// 
// 113   6/19/00 5:55p Aldie
// Added support for invisible models that are lit only by negative intensity
// lights
// 
// 112   6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 111   6/10/00 2:39p Markd
// fixed typo in event documentation
// 
// 110   6/10/00 1:41p Markd
// Added scriptshader alias for shader
// 
// 109   6/09/00 2:25p Steven
// Work to get bound entites to always get sent over if the entity they are
// bound to is.
// 
// 108   6/08/00 8:34p Markd
// fixed localorigin problem
// 
// 107   6/07/00 5:36p Markd
// fixed radius calcualtion for BSP objects
// 
// 106   6/05/00 2:22p Markd
// fixed viewspawn issue
// 
// 105   6/04/00 3:48p Markd
// Added precise shadows to certain characters
// 
// 104   6/03/00 5:45p Markd
// fixed some more savegame issues
// 
// 103   6/03/00 5:23p Markd
// fixed bug in saved games, made items have playersolid as their default
// clipmask
// 
// 102   6/01/00 2:01p Steven
// Made it so you can turn look at me stuff on and off.
// 
// 101   5/31/00 5:33p Steven
// Added look at me stuff.
// 
// 100   5/31/00 10:24a Markd
// changed LoadingServer to LoadingSavegame
// 
// 99    5/29/00 1:16p Markd
// 3rd round of saved games
// 
// 98    5/24/00 6:05p Markd
// Fixed bug where MAX_MAP_BOUNDS was being used instead of MAP_SIZE
// 
// 97    5/10/00 10:31a Steven
// Added com_blood stuff.
// 
// 96    5/07/00 5:00p Markd
// Fixed ProcessInitCommands bug
// 
// 95    5/05/00 2:15p Steven
// Only removed an attached model if the model names match if a model name is
// passed in.
// 
// 94    5/04/00 2:21p Markd
// Added godmode support to flags
// 
// 93    4/20/00 5:44p Steven
// Added offset to attachmodel.
// 
// 92    4/20/00 9:23a Markd
// Fixed CanDamage function to be more forgiving for bmodels
// 
// 91    4/19/00 5:48p Markd
// put in world targetname bulletproofing
// 
// 90    4/15/00 5:43p Steven
// Made damage fractioanl again.
// 
// 89    4/15/00 5:18p Aldie
// Added stun events and fixed yet another bug with Ammo and AutoPutaway
// 
// 88    4/15/00 1:30p Steven
// Made it so the direction in HurtEvent is normalized.
// 
// 87    4/14/00 1:40p Steven
// Added direction to hurt.
// 
// 86    4/13/00 4:58p Steven
// Changed the string name of an event so that it didn't conflict with another
// one in actor.
// 
// 85    4/13/00 3:45p Aldie
// Added more flashbang support.  Added damage_type to entities used to specify
// what type of damage they take.
// 
// 84    4/11/00 5:43p Steven
// Sinking into ground work.
// 
// 83    4/10/00 6:49p Steven
// Added  bind_use_my_angles so that a bound entity could use its angles for
// its local offset or its bindmaster.
// 
// 82    4/10/00 11:57a Steven
// Moved process init commands to happen before EV_POSTSPAWN.
// 
// 81    4/05/00 3:54p Markd
// made lightRadius work with settings from the editor
// 
// 80    4/01/00 3:55p Markd
// Added FL_TOUCH_TRIGGERS support
// 
// 79    3/31/00 6:23p Markd
// fixed usage of local orientation copy when edict->s.mat would work fine
// 
// 78    3/31/00 6:07p Markd
// fixed matrix/orientation bug in entity
// 
// 77    3/28/00 10:05a Steven
// Fixed one of the event documentations.
// 
// 76    3/23/00 10:44a Markd
// fixed fade command, it wasn't setting the final alpha value
// 
// 75    3/21/00 5:06p Markd
// added vehicle support
// 
// 74    3/20/00 3:01p Markd
// added more functionality to falling rock
// 
// 73    3/17/00 12:29p Steven
// Added means of death parameter to HurtEvent.
// 
// 72    3/15/00 4:09p Aldie
// Fixed a bug with using weapons, and added some ability to force a state in
// the player
// 
// 71    3/14/00 5:08p Aldie
// Fixed event mismatch
// 
// 70    3/14/00 4:56p Aldie
// Added new script damage command
// 
// 69    3/04/00 5:05p Steven
// Added a skipent to CanDamage and made Explosion pass in an owner to
// ExplosionAttack.
// 
// 68    3/04/00 11:48a Markd
// Added light style support
// 
// 67    3/01/00 10:58a Jimdose
// added TriggerEvent
// 
// 66    2/21/00 4:39p Markd
// Added fade command to entity
// 
// 65    2/21/00 3:33p Steven
// Added a GetControllerAngles function.
// 
// 64    2/18/00 6:41p Markd
// Added crossblend support to surfaces
// 
// 63    2/18/00 6:21p Aldie
// Added yet another parm to attachmodel... we need to find a better way to fix
// that.
// 
// 62    2/17/00 8:07p Aldie
// Put in a fix for fading models
// 
// 61    2/17/00 6:33p Aldie
// Added even more parms to attachmodel
// 
// 60    2/07/00 3:59p Steven
// Fixed dead monsters not always falling to the ground.
// 
// 59    2/03/00 7:01p Jimdose
// made all hardcoded map bounds use MAX_MAP_BOUNDS
// 
// 58    1/31/00 3:56p Aldie
// working on the auto aim / tracking code
// 
// 57    1/29/00 5:27p Steven
// Fixed children not using entity numbers correctly (weren't using
// ENTITYNUM_NONE).
// 
// 56    1/27/00 12:15p Markd
// added fullbright support and minlight support to all lighting functions
// 
// 55    1/27/00 11:35a Markd
// Fixed solid/notsolid client side entities
// 
// 54    1/22/00 2:54p Markd
// fixed sprite problem where sprites were incorrectly set to ET_MODELANIM
// instead of ET_SPRITE
// 
// 53    1/22/00 1:43p Markd
// Fixed attached entity bug
// 
// 52    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 51    1/20/00 7:05p Jimdose
// removed angmod
// 
// 50    1/19/00 9:01p Steven
// Added fade support to the attachmodel command.
// 
// 49    1/19/00 7:59p Markd
// Rewrote Surface Model Event and also added changeoutfit command to player
// 
// 48    1/19/00 7:09p Steven
// Added a removeattachedmodel event.
// 
// 47    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 46    1/14/00 5:06p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 45    1/13/00 7:08p Steven
// Made a SetControllerAngles event so I could post them in the future.
// 
// 44    1/12/00 6:17p Jimdose
// fixed spawnflags--added spawnflags to level
// 
// 43    1/10/00 6:17p Jimdose
// more code cleanup
// 
// 42    1/06/00 7:00p Steven
// Made it so the surface command would recognize * notation.
// 
// 41    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 40    12/20/99 11:41a Markd
// Fixed a music trigger issue
// 
// 39    12/17/99 8:26p Jimdose
// got rid of unused vars and functions
// 
// 38    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 37    12/14/18 2:42p Jimdose
// moved blood_model to Sentient
// 
// 36    12/02/99 6:57p Jimdose
// removed classname variable from Entity
// 
// 35    11/12/99 6:52p Markd
// fixed up sound manager saving and loading
// 
// 34    11/02/99 6:12p Steven
// Always send original position of sound even if attached to entity.
// 
// 33    11/02/99 5:44p Steven
// Added level wide sound stuff.
// 
// 32    11/01/99 4:00p Jimdose
// added SetControllerAngles and SetControllerTag
// 
// 31    10/28/99 6:07p Steven
// Added a use_angles flag and an offset to the entity attach stuff.
// 
// 30    10/25/99 6:39p Markd
// removed size and other unused variables, added radius and centroid to both
// server and game code
// 
// 29    10/22/99 11:02a Markd
// fixed fadein command again!
// 
// 28    10/21/99 5:24p Aldie
// Removed scaling from fade
// 
// 27    10/21/99 2:19p Markd
// Changed range to use ..., fixed fadein and fadeout some more
// 
// 26    10/21/99 1:55p Markd
// added more functionality to fadein and fadeout
// 
// 25    10/21/99 10:57a Markd
// Added fade in and fixed suppresion of _events.
// 
// 24    10/19/99 7:52p Markd
// Removed three part model system
// 
// 23    10/14/99 11:05a Aldie
// Make attached models Animate instead of Entity
// 
// 22    10/11/99 3:10p Steven
// Event documentation cleanup.
// 
// 21    10/08/99 2:12p Markd
// Made entities default to ET_GENERAL, ET_MODELANIm if tiki and ET_SPRITE if
// sprite
// 
// 20    10/07/99 12:45p Aldie
// initialized the owner num to the ENTITYNUM_NONE
// 
// 19    10/06/99 7:25p Markd
// removed TIMESTAMP, time and fixed make_static bug
// 
// 18    10/03/99 4:38p Markd
// Fixed ?Out command
// 
// 17    10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 16    10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 15    10/01/99 2:42p Markd
// moved all the binding code back into Entity from Mover
// 
// 14    9/30/99 4:38p Aldie
// Fix for sprites
// 
// 13    9/29/99 7:43p Markd
// Made items behave better when dropping to floor
// 
// 12    9/28/99 10:06a Markd
// somehow forgot to checkin some changes
// 
// 11    9/28/99 9:51a Markd
// fixed default flags
// 
// 10    9/27/99 5:44p Markd
// began documentation and cleanup phase after merge
// 
// 9     9/20/99 11:43a Markd
// added currentOrigin and currentAngles support to setOrigin and setAngles
// 
// 8     9/17/99 5:32p Jimdose
// added TR_LERP
// 
// 7     9/17/99 4:54p Aldie
// Fix for parent
// 
// 6     9/16/99 7:43p Jimdose
// added check for NULL child in destructor
// 
// 5     9/16/99 4:47p Jimdose
// removed SpawnParticles
// 
// 4     9/16/99 3:18p Markd
// fixed some entity number screwups
// 
// 3     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 2     9/13/99 3:27p Aldie
// code merge
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 74    9/02/99 7:43p Markd
// Cached blood model
// 
// 73    9/02/99 5:41p Markd
// made CacheResource utility functions changed code every where else
// 
// 72    9/02/99 4:35p Markd
// Added Color Offset support for sentients
// 
// 71    9/02/99 3:06p Markd
// Fixed speakers, precaching of models and appending "models" and
// automatically caching in projectiles.
// 
// 70    9/02/99 2:33p Markd
// Added cache ability to entities
// 
// 69    9/02/99 10:49a Steven
// Added a life parameter to the attachmodel command.
// 
// 68    9/01/99 6:46p Markd
// made attached models MOVETYPE_NONE
// 
// 67    9/01/99 12:02p Steven
// Added blood spurts.
// 
// 66    8/31/99 2:44p Steven
// Added a detach_at_death flag to models and fixed explosion origins.
// 
// 65    8/30/99 3:25p Steven
// Added an event to kill all of an entities attachments.
// 
// 64    8/30/99 2:36p Steven
// Added support for aliases, volume, and minimum distance for loop sounds.
// 
// 63    8/28/99 7:46p Markd
// added broadcast to any entity that is a portal sky origin
// 
// 62    8/28/99 11:43a Steven
// Removed global from sound function calls.
// 
// 61    8/25/99 9:01p Markd
// working on RF_ stuff and local color for entities on client
// 
// 60    8/24/99 11:51a Aldie
// Added viewlensflare command
// 
// 59    8/24/99 11:26a Steven
// Reworked sound stuff to use global alias, then tiki alias, and then the
// literal.
// 
// 58    8/19/99 6:59p Markd
// removed the old tiki_cmd structure, now tiki_cmd_t is passed into the tiki
// functions
// 
// 57    8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// 56    8/17/99 4:49p Markd
// Fixed offset shader effect
// 
// 55    8/09/99 11:44a Markd
// Added timestamps for translation and rotation
// 
// 54    8/09/99 11:36a Steven
// Explosions can now be based off of tags now instead of just the entities
// origin.
// 
// 53    8/06/99 8:00p Markd
// Added shader modifiable from script
// 
// 52    8/06/99 3:35p Markd
// Cleaned up cgame, added shader commands and shader manipulation support
// 
// 51    7/30/99 6:45p Aldie
// Added explosion command
// 
// 50    7/30/99 4:49p Steven
// Added a stationary command to entities and a gas explode flag.
// 
// 49    7/23/99 3:27p Aldie
// 
// 48    7/08/99 4:58p Markd
// Added scale ability to attachmodel events
// 
// 47    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
// 
// 46    6/16/99 3:52p Aldie
// Make sure sprites entity type get set properly
//
// DESCRIPTION:
// Base class for all enities that are controlled by Sin.  If you have any
// object that should be called on a periodic basis and it is not an entity,
// then you have to have an dummy entity that calls it.
//
// An entity in Sin is any object that is not part of the world.  Any non-world
// object that is visible in Sin is an entity, although it is not required that
// all entities be visible to the player.  Some objects are basically just virtual
// constructs that act as an instigator of certain actions, for example, some
// triggers are invisible and cannot be touched, but when activated by other
// objects can cause things to happen.
//
// All entities are capable of receiving messages from Sin or from other entities.
// Messages received by an entity may be ignored, passed on to their superclass,
// or acted upon by the entity itself.  The programmer must decide on the proper
// action for the entity to take to any message.  There will be many messages
// that are completely irrelevant to an entity and should be ignored.  Some messages
// may require certain states to exist and if they are received by an entity when
// it these states don't exist may indicate a logic error on the part of the
// programmer or map designer and should be reported as warnings (if the problem is
// not severe enough for the game to be halted) or as errors (if the problem should
// not be ignored at any cost).
//

#include "entity.h"
#include "worldspawn.h"
#include "scriptmaster.h"
#include "sentient.h"
#include "misc.h"
#include "specialfx.h"
#include "object.h"
#include "player.h"
#include "weaputils.h"
#include "soundman.h"
#include "../qcommon/qfiles.h"

// Player events
Event EV_ClientMove
	( 
	"client_move", 
   EV_DEFAULT, 
	NULL,
	NULL,
	"The movement packet from the client is processed by this event."
	);
Event EV_ClientEndFrame
	( 
	"client_endframe",
	EV_DEFAULT,
	NULL,
	NULL,
	"Called at the end of each frame for each client."
	);

// Generic entity events
Event EV_Classname
	( 
	"classname" ,
	EV_DEFAULT,
	"s",
	"nameOfClass",
	"Determines what class to use for this entity,\n"
	"this is pre-processed from the BSP at the start\n"
	"of the level."
	);
Event EV_SpawnFlags
	( 
	"spawnflags",
	EV_DEFAULT,
	"i",
	"flags",
	"spawnflags from the BSP, these are set inside the editor"
	);
Event EV_SetTeam
	( 
	"team",
	EV_DEFAULT,
	"s",
	"moveTeam",
	"used to make multiple entities move together."
	);
Event EV_Trigger
	( 
	"trigger",
	EV_DEFAULT,
	"s",
	"name",
	"Trigger the specified target or entity."
	);
Event EV_Activate
	( 
	"doActivate",
	EV_DEFAULT,
	"e",
	"activatingEntity",
	"General trigger event for all entities"
	);
Event EV_Use
	( 
	"doUse",
	EV_DEFAULT,
	"e",
	"activatingEntity",
	"sent to entity when it is used by another entity"
	);

Event EV_FadeNoRemove
	( 
	"fade",
	EV_DEFAULT,
	"F[0,]F[0,1]",
	"fadetime target_alpha",
	"Fade the entity's alpha, reducing it by 0.03\n"
	"every FRAMETIME, until it has faded out, does not remove the entity"
	);

Event EV_FadeOut
	( 
	"_fadeout",
	EV_DEFAULT,
	NULL,
	NULL,
	"Fade the entity's alpha and scale out, reducing it by 0.03\n"
	"every FRAMETIME, until it has faded out, removes the entity\n"
   "Once the entity has been completely faded, the entity is removed."
	);

Event EV_Fade
	( 
	"fadeout",
	EV_DEFAULT,
	"F[0,]F[0,1]",
	"fadetime target_alpha",
	"Fade the entity's alpha and scale out, reducing it by 0.03\n"
	"every FRAMETIME, until it has faded out. If fadetime or\n"
   "target_alpha are defined, they will override the defaults.\n"
   "Once the entity has been completely faded, the entity is removed."
	);
Event EV_FadeIn
	( 
	"fadein",
	EV_DEFAULT,
   "F[0,]F[0,1]",
   "fadetime target_alpha",
	"Fade the entity's alpha and scale in, increasing it by 0.03\n"
	"every FRAMETIME, until it has faded completely in to 1.0.\n"
   "If fadetime or target_alpha are defined, they will override\n"
   "the default values."
	);
 Event EV_Killed
	( 
	"killed",
	EV_DEFAULT,
	"eiei",
	"attacker damage inflictor meansofdeath",
	"event which is sent to an entity once it as been killed"
	);
Event EV_GotKill
	( 
	"gotkill" ,
	EV_DEFAULT,
	"eieib",
	"victim damage inflictor meansofdeath gib",
	"event sent to attacker when an entity dies"
	);
Event EV_Pain
	( 
	"pain",
	EV_DEFAULT,
	"iei",
	"damage attacker meansofdeath",
	"used to inflict pain to an entity"
	);
Event EV_Damage
	( 
	"_damage",
	EV_DEFAULT,
	"ieevvviii",
	"damage inflictor attacker position direction normal knockback damageflags meansofdeath",
	"general damage event used by all entities"
	);
Event EV_Stun
	( 
	"_stun",
	EV_DEFAULT,
	"f",
	"time",
	"Stun this entity for the specified time"
	);
Event EV_Kill
	( 
	"kill", 
	EV_CONSOLE,
	NULL,
	NULL,
	"console based command to kill yourself if stuck."
	);
Event EV_Gib
	( 
	"gib",
	EV_DEFAULT,
	"iIFS",
	"number power scale gibmodel",
	"causes entity to spawn a number of gibs"
	);
Event EV_Hurt
	(
	"hurt",
	EV_DEFAULT,
	"iSV",
	"damage means_of_death direction",
	"Inflicts damage if the entity is damageable.  If the number of damage\n"
	"points specified in the command argument is greater or equal than the\n"
	"entity's current health, it will be killed or destroyed."
	);

Event EV_TakeDamage
	( 
	"takedamage",
	EV_DEFAULT,
	NULL,
	NULL,
	"makes entity take damage."
	);
Event EV_NoDamage
	( 
	"nodamage",
	EV_DEFAULT,
	NULL,
	NULL,
	"entity does not take damage."
	);

Event EV_Stationary
	( 
	"stationary",
	EV_DEFAULT,
	NULL,
	NULL,
	"entity does not move, causes no physics to be run on it."
	);

// Physics events
Event EV_MoveDone
	( 
	"movedone",
	EV_DEFAULT,
	"e",
	"finishedEntity",
	"Sent to commanding thread when done with move ."
	);
Event EV_Touch
	( 
	"doTouch",
	EV_DEFAULT,
	"e",
	"touchingEntity",
	"sent to entity when touched."
	);
Event EV_Blocked
	( 
	"doBlocked",
	EV_DEFAULT,
	"e",
	"obstacle",
	"sent to entity when blocked."
	);
Event EV_UseBoundingBox
	( 
	"usebbox",
	EV_DEFAULT,
	NULL,
	NULL,
	"do not perform perfect collision, use bounding box instead."
	);
Event EV_Gravity
	( 
	"gravity",
	EV_DEFAULT,
	"f",
	"gravityValue",
	"Change the gravity on this entity"
	);
Event EV_Stop
	( 
	"stopped",
	EV_DEFAULT,
	NULL,
	NULL,
	"sent when entity has stopped bouncing for MOVETYPE_TOSS."
	);

Event EV_ProcessInitCommands
	( 
	"processinit",
	EV_DEFAULT,
	"i",
	"modelIndex",
	"process the init section of this entity, this is an internal command,\n"
	"it is not meant to be called from script."
	);
Event EV_Attach
	( 
	"attach",
	EV_DEFAULT,
	"esI",
	"parent tagname use_angles",
	"attach this entity to the parent's legs tag called tagname"
	);
Event EV_AttachModel
	( 
	"attachmodel",
	EV_DEFAULT,
	"ssFSBFFFFV",
	"modelname tagname scale targetname detach_at_death removetime fadeintime fadeoutdelay fadetime offset",
	"attach a entity with modelname to this entity to tag called tagname.\n"
	"scale           - scale of attached entities\n"
	"targetname      - targetname for attached entities\n"
	"detach_at_death - when entity dies, should this model be detached.\n"
	"removetime      - when the entity should be removed, if not specified, never.\n"
   "fadeintime      - time to fade the model in over.\n"
   "fadeoutdelay    - time to wait until we fade the attached model out\n"
   "fadeoutspeed    - time the model fades out over\n"
	"offset		     - vector offset for the model from the specified tag"
	);
Event EV_RemoveAttachedModel
	( 
	"removeattachedmodel",
	EV_DEFAULT,
	"s",
	"tagname",
	"Removes the model attached to this entity at the specified tag."
	);
Event EV_Detach
	( 
	"detach",
	EV_DEFAULT,
	NULL,
	NULL,
	"detach this entity from its parent."
	);

// script stuff
Event EV_Model
	( 
	"model",
	EV_DEFAULT,
	"e",
	"modelName",
	"set the model to modelName."
	);
Event EV_Hide
	( 
	"hide",
	EV_DEFAULT,
	NULL,
	NULL,
	"hide the entity, opposite of show."
	);
Event EV_Show
	( 
	"show",
	EV_DEFAULT,
	NULL,
	NULL,
	"show the entity, opposite of hide."
	);
Event EV_BecomeSolid
	( 
	"solid",
	EV_DEFAULT,
	NULL,
	NULL,
	"make solid."
	);
Event EV_BecomeNonSolid
	( 
	"notsolid",
	EV_DEFAULT,
	NULL,
	NULL,
	"make non-solid."
	);
Event EV_Ghost
	( 
	"ghost",
	EV_DEFAULT,
	NULL,
	NULL,
	"make non-solid but still send to client regardless of hide status."
	);
Event EV_TouchTriggers
	( 
	"touchtriggers",
	EV_DEFAULT,
   NULL,
   NULL,
   "this entity should touch triggers."
	);


Event EV_Sound
	( 
	"playsound",
	EV_DEFAULT,
	"sIFS",
	"soundName channel volume min_distance",
	"play a sound coming from this entity.\n"
	"default channel, CHAN_BODY."
	);
Event EV_StopSound
	( 
	"stopsound",
	EV_DEFAULT,
	"I",
	"channel",
	"stop the current sound on the specified channel.\n"
	"default channel, CHAN_BODY."
	);
Event EV_Bind
	( 
	"bind",
	EV_DEFAULT,
	"e",
	"parent",
	"bind this entity to the specified entity."
	);
Event EV_Unbind
	( 
	"unbind",
	EV_DEFAULT,
	NULL,
	NULL,
	"unbind this entity."
	);
Event EV_JoinTeam
	( 
	"joinTeam",
	EV_DEFAULT,
	"e",
	"teamMember",
	"join a bind team."
	);
Event EV_QuitTeam
	( 
	"quitTeam",
	EV_DEFAULT,
	NULL,
	NULL,
	"quit the current bind team"
	);
Event EV_SetHealth
   ( 
   "health", 
   EV_CHEAT,
   "i",
   "newHealth",
   "set the health of the entity to newHealth"
   );
Event EV_SetScale
   ( 
   "scale",
   EV_DEFAULT,
   "f",
   "newScale",
   "set the scale of the entity"
   );
Event EV_SetSize
   ( 
   "setsize",
   EV_DEFAULT,
   "vv",
   "mins maxs",
   "Set the bounding box of the entity to mins and maxs."
   );
Event EV_SetMins
   ( 
   "_setmins",
   EV_DEFAULT,
   "v",
   "mins",
   "Set the mins of the bounding box of the entity to mins."
   );
Event EV_SetMaxs
   ( 
   "_setmaxs",
   EV_DEFAULT,
   "v",
   "maxs",
   "Set the maxs of the bounding box of the entity to maxs."
   );
Event EV_SetAlpha
   ( 
   "alpha",
   EV_DEFAULT,
   "f",
   "newAlpha",
   "Set the alpha of the entity to alpha."
   );
Event EV_SetOrigin
   ( 
   "origin",
   EV_DEFAULT,
   "v",
   "newOrigin",
   "Set the origin of the entity to newOrigin."
   );
Event EV_SetTargetName
   ( 
   "targetname",
   EV_DEFAULT,
   "s",
   "targetName",
   "set the targetname of the entity to targetName."
   );
Event EV_SetTarget
   ( 
   "target",
   EV_DEFAULT,
   "s",
   "targetname_to_target",
   "target another entity with targetname_to_target."
   );
Event EV_SetKillTarget
   ( 
   "killtarget",
   EV_DEFAULT,
   "s",
   "targetName",
   "when dying kill entities with this targetName."
   );
Event EV_SetAngles
   ( 
   "angles",
   EV_DEFAULT,
   "v[0,360][0,360][0,360]",
   "newAngles",
   "set the angles of the entity to newAngles."
   );
Event EV_SetAngle
   ( 
   "angle",
   EV_DEFAULT,
   "f",
   "newAngle",
   "set the angles of the entity using just one value.\n"
   "Sets the yaw of the entity or an up and down\n"
   "direction if newAngle is [0-359] or -1 or -2"
   );
Event EV_RegisterAlias
   ( 
   "alias", 
   EV_CACHE,
   "ssSSSSSS",
   "alias realname parameter1 parameter2 parameter3 parameter4 parameter5 paramater6",
   "create an alias for the given realname\n"
   "Valid parameters are as follows:\n"
   "global - all instances act as one\n"
   "stop - once used, don't use again\n"
   "timeout [seconds] - once used wait [seconds] until using again\n"
   "maxuse [times] - can only be used [times] times.\n"
   "weight [weight] - random weighting"
   );
Event EV_RegisterAliasAndCache
   ( 
   "aliascache", 
   EV_CACHE,
   "ssSSSSSS",
   "alias realname parameter1 parameter2 parameter3 parameter4 parameter5 paramater6",
   "create an alias for the given realname and cache the resource\n"
   "Valid parameters are as follows:\n"
   "global - all instances act as one\n"
   "stop - once used, don't use again\n"
   "timeout [seconds] - once used wait [seconds] until using again\n"
   "maxuse [times] - can only be used [times] times.\n"
   "weight [weight] - random weighting"
   );
Event EV_Cache
   ( 
   "cache", 
   EV_CACHE,
   "s",
   "resourceName",
   "pre-cache the given resource."
   );
Event EV_SetMass
   ( 
   "mass",
   EV_DEFAULT,
   "f",
   "massAmount",
   "set the mass of this entity."
   );

Event EV_LoopSound
   ( 
   "loopsound",
   EV_DEFAULT,
   "sFS",
   "soundName volume minimum_distance",
   "play a looped-sound with a certain volume and minimum_distance\n"
   "which is attached to the current entity."
   );
Event EV_StopLoopSound
   ( 
   "stoploopsound",
   EV_DEFAULT,
   NULL,
   NULL,
   "Stop the looped-sound on this entity."
   );

Event EV_SurfaceModelEvent
   ( 
   "surface",
   EV_DEFAULT,
   "sSSSSSS",
   "surfaceName parameter1 parameter2 parameter3 parameter4 parameter5 parameter6",
   "change a legs surface parameter for the given surface.\n"
   "+ sets the flag, - clears the flag\n"
   "Valid surface commands are:\n"
   "skin1 - set the skin1 offset bit\n"
   "skin2 - set the skin2 offset bit\n"
   "nodraw - don't draw this surface"
   );
// AI sound events
Event EV_BroadcastSound
   ( 
   "soundevent",
   EV_DEFAULT,
   "F",
   "soundRadius",
   "Let the AI know that this entity made a sound,\n"
   "radius determines how far the sound reaches."
   );
Event EV_HeardSound
   ( 
   "heardsound",
   EV_DEFAULT,
   "ev",
   "noisyEntity noisyLocation",
   "sent to entities when another makes a sound, not for script use\n"
   );

// Conditionals
Event EV_IfSkill
   ( 
   "ifskill",
   EV_DEFAULT,
   "isSSSSS",
   "skillLevel command argument1 argument2 argument3 argument4 argument5",
   "if the current skill level is skillLevel than execute command"
   );

// Lighting
Event EV_SetLight
   ( 
   "light",
   EV_DEFAULT,
   "ffff",
   "red green blue radius",
   "Create a dynmaic light on this entity."
   );

Event EV_LightOn
   ( 
   "lightOn",
   EV_DEFAULT,
   NULL,
   NULL,
   "Turn the configured dynmaic light on this entity on."
   );
Event EV_LightOff
   ( 
   "lightOff",
   EV_DEFAULT,
   NULL,
   NULL,
   "Turn the configured dynamic light on this entity off."
   );
Event EV_LightStyle
   ( 
   "lightStyle",
   EV_DEFAULT,
   "i",
   "lightStyleIndex",
   "What light style to use for this dynamic light on this entity."
   );
Event EV_LightRed
   ( 
   "lightRed",
   EV_DEFAULT,
   "f",
   "red",
   "Set the red component of the dynmaic light on this entity."
   );
Event EV_LightGreen
   ( 
   "lightGreen",
   EV_DEFAULT,
   "f",
   "red",
   "Set the red component of the dynmaic light on this entity."
   );
Event EV_LightBlue
   ( 
   "lightBlue",
   EV_DEFAULT,
   "f",
   "red",
   "Set the red component of the dynmaic light on this entity."
   );
Event EV_LightRadius
   ( 
   "lightRadius",
   EV_DEFAULT,
   "f",
   "red",
   "Set the red component of the dynmaic light on this entity."
   );

// Entity flag specific
Event EV_EntityFlags
   ( 
   "flags",
   EV_DEFAULT,
   "SSSSSS",
   "parameter1 parameter2 parameter3 parameter4 parameter5 parameter6",
   "Change the current entity flags.\n"
   "Valid flags are as follows:\n"
   "+ sets a flag, - clears a flag\n"
   "blood - should it bleed\n"
   "explode - should it explode when dead\n"
   "die_gibs - should it spawn gibs when dead\n"
   "god - makes the entity invincible\n"
   );
Event EV_EntityRenderEffects
   ( 
   "rendereffects",
   EV_DEFAULT,
   "SSSSSS",
   "parameter1 parameter2 parameter3 parameter4 parameter5 parameter6",
   "Change the current render effects flags.\n"
   "Valid flags are as follows:\n"
   "+ sets a flag, - clears a flag\n"
   "dontdraw - send the entity to the client, but don't draw\n"
   "betterlighting - do sphere based vertex lighting on the entity\n"
   "lensflare - add a lens glow to the entity at its origin\n"
   "viewlensflare - add a view dependent lens glow to the entity at its origin\n"
   "lightoffset - use the dynamic color values as a light offset to the model\n"
   "skyorigin - this entity is the portal sky origin\n"
   "minlight - this entity always has some lighting on it\n"
   "fullbright - this entity is always fully lit\n"
   "additivedynamiclight - the dynamic light should have an additive effect\n"
   "lightstyledynamiclight - the dynamic light uses a light style, use the\n"
   "'lightstyle' command to set the index of the light style to be used"
   );
Event EV_EntityEffects
   ( 
   "effects",
   EV_DEFAULT,
   "SSSSSS",
   "parameter1 parameter2 parameter3 parameter4 parameter5 parameter6",
   "Change the current entity effects flags.\n"
   "Valid flags are as follows:\n"
   "+ sets a flag, - clears a flag\n"
   "antisbjuice - anti sucknblow juice"
   "everyframe - process commands every time entity is rendered"
   );
Event EV_EntitySVFlags
   ( 
   "svflags",
   EV_DEFAULT,
   "SSSSSS",
   "parameter1 parameter2 parameter3 parameter4 parameter5 parameter6",
   "Change the current server flags.\n"
   "Valid flags are as follows:\n"
   "+ sets a flag, - clears a flag\n"
   "broadcast - always send this entity to the client"
   );

// Special Effects
Event EV_Censor
   ( 
   "censor",
   EV_DEFAULT,
   NULL,
   NULL,
   "used to ban certain contact when in parentmode\n"
   );
Event EV_Explosion
   ( 
   "explosionattack",
   EV_DEFAULT,
   "sS",
   "explosionModel tagName",
   "Spawn an explosion optionally from a specific tag"
   );

Event EV_ShaderEvent
   ( 
   "shader",
   EV_DEFAULT,
   "sfF",
   "shaderCommand argument1 argument2",
   "change a specific shader parameter for the entity.\n"
   "Valid shader commands are:\n"
   "translation [trans_x] [trans_y] - change the texture translation\n"
   "offset [offset_x] [offset_y] - change the texture offset\n"
   "rotation [rot_speed] - change the texture rotation speed\n"
   "frame [frame_num] - change the animated texture frame\n"
   "wavebase [base] - change the base parameter of the wave function\n"
   "waveamp [amp] - change the amp parameter of the wave function\n"
   "wavebase [phase] - change the phase parameter of the wave function\n"
   "wavefreq [freq] - change the frequency parameter of the wave function\n"
   );

Event EV_ScriptShaderEvent
   ( 
   "scriptshader",
   EV_DEFAULT,
   "sfF",
   "shaderCommand argument1 argument2",
   "alias for shader command, change a specific shader parameter for the entity.\n"
   "Valid shader commands are:\n"
   "translation [trans_x] [trans_y] - change the texture translation\n"
   "offset [offset_x] [offset_y] - change the texture offset\n"
   "rotation [rot_speed] - change the texture rotation speed\n"
   "frame [frame_num] - change the animated texture frame\n"
   "wavebase [base] - change the base parameter of the wave function\n"
   "waveamp [amp] - change the amp parameter of the wave function\n"
   "wavebase [phase] - change the phase parameter of the wave function\n"
   "wavefreq [freq] - change the frequency parameter of the wave function\n"
   );

Event EV_KillAttach
   ( 
   "killattach",
   EV_DEFAULT,
   NULL,
   NULL,
   "kill all the attached entities."
   );
Event EV_DropToFloor
	( 
	"droptofloor",
	EV_DEFAULT,
	"F",
	"maxRange",
	"drops the entity to the ground, if maxRange is not specified 8192 is used."
	);
Event EV_AddToSoundManager
	( 
	"_addtosoundmanager",
	EV_DEFAULT,
	NULL,
	NULL,
	"adds the current entity to the sound manager."
	);
Event EV_SetControllerAngles
	( 
	"setcontrollerangles",
	EV_DEFAULT,
	"iv",
	"num angles",
	"Sets the control angles for the specified bone."
	);
Event EV_DeathSinkStart
	( 
	"deathsinkstart",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the entity sink into the ground and then get removed (this starts it)."
	);
Event EV_DeathSink
	( 
	"deathsinkeachframe",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the entity sink into the ground and then get removed (this gets called each frame)."
	);
Event EV_DamageType
	( 
	"damage_type",
	EV_DEFAULT,
	"s",
   "meansofdeathstring",
	"Set the type of damage that this entity can take"
	);
Event EV_LookAtMe
	( 
	"lookatme",
	EV_DEFAULT,
	NULL,
   NULL,
	"Makes the player look at this object if close."
	);
Event EV_DetachAllChildren
	( 
	"detachallchildren",
	EV_DEFAULT,
	NULL,
   NULL,
	"Detach all the children from the entity."
	);

CLASS_DECLARATION( Listener, Entity, NULL )
	{
		{ &EV_Damage,				         DamageEvent },
		{ &EV_DamageType,			         DamageType },
      { &EV_Kill, 				         Kill },
	   { &EV_FadeNoRemove,  	         FadeNoRemove },
	   { &EV_FadeOut,				         FadeOut },
	   { &EV_FadeIn,  			         FadeIn },
	   { &EV_Fade,				            Fade },
	   { &EV_Hide,					         EventHideModel },
	   { &EV_Show,					         EventShowModel },
	   { &EV_BecomeSolid,		         BecomeSolid },
	   { &EV_BecomeNonSolid,	         BecomeNonSolid },
	   { &EV_Ghost,	                  Ghost },
	   { &EV_TouchTriggers,	            TouchTriggersEvent },
		{ &EV_Sound,				         Sound },
	   { &EV_StopSound,			         StopSound },
	   { &EV_SetHealth,			         SetHealth },
	   { &EV_SetSize,				         SetSize },
	   { &EV_SetMins,				         SetMins },
	   { &EV_SetMaxs,				         SetMaxs },
		{ &EV_SetScale,			         SetScale },
	   { &EV_SetAlpha,			         SetAlpha },
	   { &EV_SetOrigin,			         SetOrigin },
	   { &EV_SetTargetName,		         SetTargetName },
	   { &EV_SetTarget,			         SetTarget },
	   { &EV_SetKillTarget,		         SetKillTarget },
	   { &EV_SetAngles,			         SetAngles },
	   { &EV_SetAngle,			         SetAngleEvent },
      { &EV_SetMass,                   SetMassEvent },                                       
	   { &EV_RegisterAlias,	            RegisterAlias },
	   { &EV_RegisterAliasAndCache,     RegisterAliasAndCache },
	   { &EV_Cache,                     Cache },
		{ &EV_LoopSound,						LoopSound },
		{ &EV_StopLoopSound,					StopLoopSound },
		{ &EV_Model,				         SetModelEvent },
      { &EV_SetLight,			         SetLight },
      { &EV_LightOn,				         LightOn },
      { &EV_LightOff,		            LightOff },
      { &EV_LightRed,		            LightRed },
      { &EV_LightGreen,		            LightGreen },
      { &EV_LightBlue,		            LightBlue },
      { &EV_LightRadius,	            LightRadius },
      { &EV_LightStyle,	               LightStyle },
      { &EV_EntityFlags,	            Flags },
      { &EV_EntityEffects,	            Effects },
      { &EV_EntitySVFlags,	            SVFlags },
      { &EV_EntityRenderEffects,	      RenderEffects },
      { &EV_BroadcastSound,            BroadcastSound },
	   { &EV_SurfaceModelEvent,         SurfaceModelEvent },
      { &EV_ProcessInitCommands,       ProcessInitCommandsEvent },
      { &EV_Attach,                    AttachEvent },
      { &EV_AttachModel,               AttachModelEvent },
		{ &EV_RemoveAttachedModel,       RemoveAttachedModelEvent },
      { &EV_Detach,                    DetachEvent },
      { &EV_TakeDamage,                TakeDamageEvent },
      { &EV_NoDamage,                  NoDamageEvent },
      { &EV_Gravity,                   Gravity },                                       
	   { &EV_UseBoundingBox,            UseBoundingBoxEvent },
	   { &EV_Hurt,                      HurtEvent },
	   { &EV_IfSkill,                   IfSkillEvent },                                       
      { &EV_Classname,                 ClassnameEvent },
      { &EV_SpawnFlags,                SpawnFlagsEvent },
      { &EV_SetTeam,                   SetTeamEvent },
      { &EV_Trigger,                   TriggerEvent },
      { &EV_Censor,                    Censor },
		{ &EV_Stationary,                StationaryEvent },
		{ &EV_Explosion,                 Explosion },
		{ &EV_ShaderEvent,               Shader },
		{ &EV_ScriptShaderEvent,         Shader },
		{ &EV_KillAttach,						KillAttach },
		{ &EV_DropToFloor,					DropToFloorEvent },
	   { &EV_Bind,				         	BindEvent },
	   { &EV_Unbind,				         EventUnbind },
	   { &EV_JoinTeam,         			JoinTeam },
	   { &EV_QuitTeam,			         EventQuitTeam },
	   { &EV_AddToSoundManager,         AddToSoundManager },
		{ &EV_SetControllerAngles,       SetControllerAngles },
		{ &EV_DeathSinkStart,				DeathSinkStart },
		{ &EV_DeathSink,						DeathSink },
		{ &EV_LookAtMe,						LookAtMe },
      { &EV_DetachAllChildren,         DetachAllChildren },
		{ NULL, NULL }
	};

Entity::Entity()
	{
	int i;

   edict = level.AllocEdict( this );
	client = edict->client;
	entnum = edict->s.number;

   // spawning variables
	spawnflags = level.spawnflags;
   level.spawnflags = 0;

	// rendering variables
	setAlpha( 1.0f );
	setScale( 1.0f );

	// physics variables
   move_time               = 0;
   total_delta             = "0 0 0";
	mass							= 0;
	gravity						= 1.0;
	groundentity				= NULL;
   groundcontents          = 0;
	velocity						= vec_zero;
	avelocity					= vec_zero;
   edict->clipmask         = MASK_SOLID;

	// team variables
	teamchain	= NULL;
	teammaster	= NULL;

   // bind variables
	bindmaster = NULL;
	edict->s.bindparent = ENTITYNUM_NONE;

   // this is an generic entity
   edict->s.eType = ET_GENERAL;

   setContents( 0 );

   edict->s.parent      = ENTITYNUM_NONE;
   edict->s.pos.trType  = TR_LERP;
   edict->ownerNum      = ENTITYNUM_NONE;

   // model binding variables
   numchildren = 0;

	for( i = 0 ; i < MAX_MODEL_CHILDREN ; i++ )
		children[i] = ENTITYNUM_NONE;

	setOrigin( vec_zero );
   origin.copyTo( edict->s.origin2 );

   setAngles( vec_zero );

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_NOT );

	// Character state
	health		= 0;
	max_health	= 0;
	deadflag		= DEAD_NO;
	flags			= 0;

	// underwater variables
	watertype		= 0;
	waterlevel		= 0;

	// Pain and damage variables
	takedamage				= DAMAGE_NO;
	enemy						= NULL;
	pain_finished			= 0;
	damage_debounce_time = 0;
   damage_type          = -1;

   detach_at_death = qtrue;

   // Surface variables
   numsurfaces    = 0;

   // Light variables
   lightRadius    = 0;

	look_at_me = false;
	}

Entity::~Entity()
	{
   Container<Entity *> bindlist;
   Entity *ent;
   int num;
   int i;

	// unbind any entities that are bound to me
   // can't unbind within this loop, so make an array
   // and unbind them outside of it.
   num = 0;
	for( ent = teamchain; ent; ent = ent->teamchain )
		{
      if ( ent->bindmaster == this )
         {
         bindlist.AddObject( ent );
         }
		}

   num = bindlist.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      bindlist.ObjectAt( i )->unbind();
      }

   bindlist.FreeObjectList();

	unbind();
	quitTeam();

   detach();

   //
   // go through and set our children
   //
   num = numchildren;
   for( i = 0; ( i < MAX_MODEL_CHILDREN ) && num; i++ )
      {
      if ( children[ i ] == ENTITYNUM_NONE )
			{
         continue;
			}
      ent = G_GetEntity( children[ i ] );
      if ( ent )
         {
         ent->PostEvent( EV_Remove, 0 );
         }
      num--;
      }

   if ( targetname.length() && world )
      {
		world->RemoveTargetEntity( targetname, this );
      }
	
   level.FreeEdict( edict );
	}

void Entity::SetEntNum
   (
   int num
   )

   {
   if ( edict )
      {
      level.FreeEdict( edict );
      }

   level.spawn_entnum = num;
   level.AllocEdict( this );
	client = edict->client;
	entnum = edict->s.number;
   }

void Entity::ClassnameEvent
	(
	Event *ev
   )

   {
	strncpy( edict->entname, ev->GetString( 1 ), sizeof( edict->entname ) - 1 );
	}

void Entity::SpawnFlagsEvent
	(
	Event *ev
   )

   {
	// spawning variables
	spawnflags = ev->GetInteger( 1 );
   if ( spawnflags & SPAWNFLAG_DETAIL )
		{
      edict->s.renderfx |= RF_DETAIL;
		}
	}

void Entity::SetTarget
	(
	const char *text
	)

	{
   if ( text )
		{
      target = text;
		}
	else
		{
		target = "";
		}
	}

void Entity::SetTargetName
	(
	const char *text
	)

	{
   if ( targetname.length() && world )
      {
      world->RemoveTargetEntity( targetname, this );
      }

   if ( text )
		{
      if ( text[ 0 ] == '$' )
         text++;
      targetname = text;
		}
	else
		{
		targetname = "";
		}

   if ( targetname.length() && world )
		{
      //
      // make sure we don't re-targetname the world entity
      //
      if ( 
            ( this != world ) || 
            ( targetname == str( "world" ) ) 
         )
         {
         world->AddTargetEntity( targetname, this );
         }
      else
         {
         // this is bad
         assert( 0 );
         gi.DPrintf( "world was re-targeted with targetname %s\n", targetname.c_str() );
         targetname = "world";
         }

		}
	}

void Entity::SetKillTarget
	(
	const char *text
	)

	{
   if ( text )
		{
      killtarget = text;
		}
	else
		{
		killtarget = "";
		}
	}

void Entity::setModel
	(
	const char *mdl
	)

	{
   str temp;

   if ( LoadingSavegame && ( this == world ) )
      {
      // don't set model on the world
      return;
      }

	if ( !mdl )
		{
		mdl = "";
		}

   // Prepend 'models/' to make things easier
   temp = "";
	if ( ( strlen( mdl ) > 0 ) && !strchr( mdl, '*' ) && strnicmp( "models/", mdl, 7 ) && !strstr( mdl, ".spr" ) )
		{
		temp = "models/";
		}
   temp += mdl;

   // we use a temp string so that if model was passed into here, we don't
   // accidentally free up the string that we're using in the process.
   model = temp;

	gi.setmodel( edict, model.c_str() );

   if ( gi.IsModel( edict->s.modelindex ) )
      {
  	   Event *ev;

      numsurfaces = gi.NumSurfaces( edict->s.modelindex );

      if ( !LoadingSavegame )
         {
		   CancelEventsOfType( EV_ProcessInitCommands );

         ev = new Event( EV_ProcessInitCommands );
         ev->AddInteger( edict->s.modelindex );
         PostEvent( ev, EV_PROCESS_INIT );
         }
      else
         {
         ProcessInitCommands( edict->s.modelindex, qtrue );
         }
      }
   else if ( strstr( mdl, ".spr" ) )
      {
      edict->s.eType = ET_SPRITE;
      }
   
	// Sanity check to see if we're expecting a B-Model
	assert( !( ( edict->solid == SOLID_BSP ) && !edict->s.modelindex ) );
	if ( ( edict->solid == SOLID_BSP ) && !edict->s.modelindex )
		{
      const char *name;

      name = getClassID();
      if ( !name )
         {
         name = getClassname();
         }
      gi.DPrintf( "%s with SOLID_BSP and no model - '%s'(%d)\n", name, targetname.c_str(), entnum );

      // Make it non-solid so that the collision code doesn't kick us out.
      setSolidType( SOLID_NOT );
      }

	mins = edict->mins;
	maxs = edict->maxs;
   size = maxs - mins;
   edict->radius = size.length() * 0.5f;
	edict->radius2 = edict->radius * edict->radius;

   //
   // see if we have a mins and maxs set for this model
   //
   //FIXME
   //We only did this on startup, but with the spawnargs as events it would have to
   //be here.  Do we still need this?  It may cause strange effects.
   if ( gi.IsModel( edict->s.modelindex ) && !mins.length() && !maxs.length() )
      {
      vec3_t tempmins, tempmaxs;
      gi.CalculateBounds( edict->s.modelindex, edict->s.scale, tempmins, tempmaxs );
      setSize( tempmins, tempmaxs );
      }
	}

void Entity::ProcessInitCommands
	(
	int index,
   qboolean cache
	)

	{
   tiki_cmd_t cmds;

   if ( LoadingSavegame && !cache )
      {
      // Don't process init commands when loading a savegame since
      // it will cause items to be added to inventories unnecessarily.
      // All variables affected by the init commands will be set
      // by the unarchive functions.
      //
      // we do want to process the cache commands though regardless
      return;
      }

   if ( gi.InitCommands( index, &cmds ) )
      {
      int i, j, savedindex;
   	Event		*event;

      // because the model has not necessarily been spawned yet, we need to set
      // this entity to have this index so that precaches go where they are supposed
      // to, this should have no bad effects, since we are only doing it in the 
      // cache phase of spawning
      if ( index != edict->s.modelindex )
         {
         savedindex = edict->s.modelindex;
         edict->s.modelindex = index;
         }
      else 
         {
         savedindex = -1;
         }
      for( i = 0; i < cmds.num_cmds; i++ )
         {
      	event = new Event( cmds.cmds[ i ].args[ 0 ] );
         if ( !cache || ( event->GetFlags() & EV_CACHE ) )
            {
            for( j = 1; j < cmds.cmds[ i ].num_args; j++ )
               {
      		   event->AddToken( cmds.cmds[ i ].args[ j ] );
               }
            ProcessEvent( event );
            }
         else
            {
            delete event;
            }
         }
      // restore the modelindex, see above
      if ( savedindex != -1 )
         {
         edict->s.modelindex = savedindex;
         }
      }
	}

void Entity::ProcessInitCommandsEvent
	(
	Event *ev
	)

	{
   int index;

   index = ev->GetInteger( 1 );
   ProcessInitCommands( index, qfalse );
	}

void Entity::EventHideModel
	(
	Event *ev
	)

	{
	hideModel();
	}

void Entity::EventShowModel
	(
	Event *ev
	)

	{
	showModel();
	}

void Entity::SetTeamEvent
	(
	Event *ev
	)

	{
   moveteam = ev->GetString( 1 );
	}

void Entity::TriggerEvent
	(
	Event *ev
	)

	{
	const char	*name;
	Event		   *event;
	Entity	   *ent;
   TargetList  *tlist;
   int         i;
   int         num;

	name = ev->GetString( 1 );

	// Check for object commands
	if ( name && name[ 0 ] == '$' )
		{
      tlist = world->GetTargetList( str( name + 1 ) );
      num = tlist->list.NumObjects();
      for ( i = 1; i <= num; i++ )
         {
         ent = tlist->list.ObjectAt( i );

		   assert( ent );

         event = new Event( EV_Activate );
			event->SetSource( ev->GetSource() );
			event->SetThread( ev->GetThread() );
			event->SetLineNumber( ev->GetLineNumber() );
         event->AddEntity( this );
		   ent->ProcessEvent( event );
         }
      }
	else if ( name[ 0 ] == '*' )   // Check for entnum commands
      {
		if ( !IsNumeric( &name[ 1 ] ) )
			{
			ev->Error( "Expecting numeric value for * command, but found '%s'\n", &name[ 1 ] );
			}
		else
         {
         ent = G_GetEntity( atoi( &name[ 1 ] ) );
         if ( ent )
            {
            event = new Event( EV_Activate );
			   event->SetSource( ev->GetSource() );
			   event->SetThread( ev->GetThread() );
			   event->SetLineNumber( ev->GetLineNumber() );
            event->AddEntity( this );
            ent->ProcessEvent( event );
            }
         else
            {
            ev->Error( "Entity not found for * command\n" );
            }
         }
      return;
      }
	else
		{
		ev->Error( "Invalid entity reference '%s'.\n", name );
		}
	}

void Entity::setAlpha
	(
	float alpha
	)

	{
	if ( alpha > 1.0f )
		{
		alpha = 1.0f;
		}
	if ( alpha < 0 )
		{
		alpha = 0;
		}
   edict->s.alpha = alpha;
	}

void Entity::setScale
	(
	float scale
	)

	{
   edict->s.scale = scale;
	}

void Entity::setSolidType
	(
	solid_t type
	)

	{
	if (
         ( !LoadingSavegame ) &&
         ( type == SOLID_BSP ) &&
         ( this != world ) &&
         (
            !model.length() ||
            (
               ( model[ 0 ] != '*' ) &&
               ( !strstr( model.c_str(), ".bsp" ) )
            )
         )
      )
		{
      error( "setSolidType", "SOLID_BSP entity at x%.2f y%.2f z%.2f with no BSP model", origin[ 0 ], origin[ 1 ], origin[ 2 ] );
		}
	edict->solid = type;

   //
   // set the appropriate contents type
   if ( edict->solid == SOLID_BBOX )
      {
      if ( !getContents() )
   	   setContents( CONTENTS_SOLID );
      }
   else if ( edict->solid == SOLID_NOT )
      {
      if ( getContents() == CONTENTS_SOLID )
   	   setContents( 0 );
      }
   else if ( edict->solid == SOLID_BSP )
      {
      if ( !getContents() )
   	   setContents( CONTENTS_SOLID );
      }

	link();

	edict->svflags &= ~SVF_NOCLIENT;
	if ( hidden() )
		{
		edict->svflags |= SVF_NOCLIENT;
		}
	}

void Entity::setSize
	(
	Vector min,
	Vector max
	)

	{
   Vector delta;

   if ( flags & FL_ROTATEDBOUNDS )
      {
      vec3_t tempmins, tempmaxs;

      //
      // rotate the mins and maxs for the model
      //
	   min.copyTo( tempmins );
	   max.copyTo( tempmaxs );

      CalculateRotatedBounds2( edict->s.mat, tempmins, tempmaxs );

      mins = Vector( tempmins );
      maxs = Vector( tempmaxs );
	   size = max - min;

	   mins.copyTo( edict->mins );
	   maxs.copyTo( edict->maxs );
      edict->radius = size.length() * 0.5;
		edict->radius2 = edict->radius * edict->radius;
      }
   else
      {
      if ( ( min == edict->mins ) && ( max == edict->maxs ) )
         {
         return;
         }

	   mins = min;
	   maxs = max;
	   size = max - min;

	   mins.copyTo( edict->mins );
	   maxs.copyTo( edict->maxs );

      //
      // get the full mins and maxs for this model
      //
      if ( gi.IsModel( edict->s.modelindex ) )
         {
         vec3_t fullmins, fullmaxs;
         Vector delta;

         gi.CalculateBounds( edict->s.modelindex, edict->s.scale, fullmins, fullmaxs );

         delta = Vector( fullmaxs ) - Vector( fullmins );
         edict->radius = delta.length() * 0.5;
			edict->radius2 = edict->radius * edict->radius;
         }
      else
         {
         edict->radius = size.length() * 0.5;
			edict->radius2 = edict->radius * edict->radius;
         }
      }

	link();
	}

Vector Entity::getLocalVector
	(
	Vector vec
	)

	{
	Vector pos;

	pos[ 0 ] = vec * orientation[ 0 ];
	pos[ 1 ] = vec * orientation[ 1 ];
	pos[ 2 ] = vec * orientation[ 2 ];

	return pos;
	}

void Entity::link
	(
	void
	)

	{
	gi.linkentity( edict );
	absmin = edict->absmin;
	absmax = edict->absmax;
	centroid = ( absmin + absmax ) * 0.5;
	centroid.copyTo( edict->centroid );

   // If this has a parent, then set the areanum the same
   // as the parent's
   if ( edict->s.parent != ENTITYNUM_NONE )
      {
      edict->areanum = g_entities[ edict->s.parent ].areanum;
      }
	}

void Entity::addOrigin
	(
	Vector add
	)

   {
   setOrigin( localorigin + add );
   }

void Entity::setOrigin
	(
   void
	)

   {
   setOrigin( localorigin );
   }

void Entity::setOrigin
	(
	Vector org
	)

	{
   Entity * ent;
   int i,num;

	if ( bindmaster )
		{
      localorigin = org;

		if ( bind_use_my_angles )
			MatrixTransformVector( localorigin, orientation, origin );
		else
			MatrixTransformVector( localorigin, bindmaster->orientation, origin );

      origin += bindmaster->origin;
      origin.copyTo( edict->s.netorigin );
		}
   // If entity has a parent, then set the origin as the
   // centroid of the parent, and set edict->s.netorigin
   // as the local origin of the entity which will be used
   // to position this entity on the client.
   else if ( edict->s.parent != ENTITYNUM_NONE )
      {
      VectorClear( edict->s.netorigin );
      ent = ( Entity * )G_GetEntity( edict->s.parent );

      ent->GetTag( edict->s.tag_num & TAG_MASK, &origin );

		origin += edict->s.attach_offset;

      localorigin = vec_zero;
      }
	else
		{
      origin = org;
      localorigin = org;
      origin.copyTo( edict->s.netorigin );
		}

   origin.copyTo( edict->s.origin );
   origin.copyTo( edict->currentOrigin );

	link();

#if 0
   if ( this->isClient() )
      {
      i = CurrentAnim();
      j = CurrentFrame();

      G_DrawCoordSystem( origin, orientation[0], orientation[1], orientation[2], 30 );
      gi.Printf( "%s:legs anim:%s frame %i\n", this->getClassname(), gi.Anim_NameForNum( edict->s.modelindex, i ), j );
      }
#endif


   //
   // go through and set our children
   //
   num = numchildren;
   for( i = 0; ( i < MAX_MODEL_CHILDREN ) && num; i++ )
      {
      if ( children[ i ] == ENTITYNUM_NONE )
			{
         continue;
			}
      ent = ( Entity * )G_GetEntity( children[ i ] );
      ent->setOrigin();
      num--;
      }
	}

void Entity::GetRawTag
	(
   int    tagnum,
   orientation_t * orient
	)

	{
   int anim;
   int frame;

   anim = CurrentAnim();
   frame = CurrentFrame();

   *orient = gi.Tag_Orientation( edict->s.modelindex, anim, frame, tagnum & TAG_MASK, edict->s.scale, edict->s.bone_tag, edict->s.bone_quat );
   }

qboolean Entity::GetRawTag
	(
	const char *name,
   orientation_t * orient
	)
	{
   int      tagnum;

   tagnum = gi.Tag_NumForName( edict->s.modelindex, name );

   if ( tagnum < 0 )
      return false;

   GetRawTag( tagnum, orient );
   return true;
   }

void Entity::GetTag
	(
   int    tagnum,
   orientation_t * orient
	)

	{
   orientation_t  or;
   int            i;

   GetRawTag( tagnum, &or );

   VectorCopy( origin, orient->origin );

   for ( i = 0 ; i < 3 ; i++ ) 
      {
		VectorMA( orient->origin, or.origin[i], orientation[i], orient->origin );
	   }
   MatrixMultiply( or.axis, orientation, orient->axis );
   }

qboolean Entity::GetTag
	(
	const char *name,
   orientation_t * orient
	)
	{
   int      tagnum;

   tagnum = gi.Tag_NumForName( edict->s.modelindex, name );

   if ( tagnum < 0 )
      return false;

   GetTag( tagnum, orient );
   return true;
   }

void Entity::GetTag
	(
   int    tagnum,
	Vector *pos,
	Vector *forward,
	Vector *left,
	Vector *up
	)

	{
   orientation_t or;

   GetTag( tagnum, &or );

	if ( pos )
		{
		*pos = Vector( or.origin );
		}
	if ( forward )
		{
		*forward = Vector( or.axis[ 0 ] );
		}
	if ( left )
		{
		*left = Vector( or.axis[ 1 ] );
		}
	if ( up )
		{
		*up = Vector( or.axis[ 2 ] );
		}
   }

qboolean Entity::GetTag
	(
	const char *name,
	Vector *pos,
	Vector *forward,
	Vector *left,
	Vector *up
	)

	{
   int      tagnum;

   tagnum = gi.Tag_NumForName( edict->s.modelindex, name );

   if ( tagnum < 0 )
      return false;

   GetTag( tagnum, pos, forward, left, up );
   return true;
   }

void Entity::addAngles
   (
   Vector add
   )

   {
   if ( bindmaster )
      {
      setAngles( localangles + add );
      }
   else
      {
      setAngles( angles + add );
      }
   }

void Entity::setAngles
	(
   void
   )

   {
   if ( bindmaster )
      {
      setAngles( localangles );
      }
   else
      {
      setAngles( angles );
      }
   }


void Entity::setAngles
	(
	Vector ang
	)

	{
   Entity * ent;
   int num,i;

	angles[ 0 ] = AngleMod( ang[ 0 ] );
	angles[ 1 ] = AngleMod( ang[ 1 ] );
	angles[ 2 ] = AngleMod( ang[ 2 ] );

   localangles = angles;
   if ( bindmaster )
      {
      float	mat[3][3];
		AnglesToAxis( localangles, mat );
		R_ConcatRotations( mat, bindmaster->orientation, orientation );
      MatrixToEulerAngles( orientation, angles );
      }
   else
      {
      AnglesToAxis( angles, orientation );
      }

   angles.copyTo( edict->s.netangles );
   angles.copyTo( edict->s.angles );
   angles.copyTo( edict->currentAngles );
	// Fill the edicts matrix
	VectorCopy( orientation[ 0 ], edict->s.mat[ 0 ] );
	VectorCopy( orientation[ 1 ], edict->s.mat[ 1 ] );
	VectorCopy( orientation[ 2 ], edict->s.mat[ 2 ] );

   //
   // go through and set our children
   //
   num = numchildren;
   for (i=0;(i < MAX_MODEL_CHILDREN) && num;i++)
      {
      if ( children[i] == ENTITYNUM_NONE )
         continue;
      ent = ( Entity * )G_GetEntity( children[i] );
      ent->setAngles();
      num--;
      }
	}

qboolean Entity::droptofloor
	(
	float maxfall
	)

	{
	trace_t	trace;
	Vector	end;
   Vector   start;

   start = origin + Vector( "0 0 1" );
   end = origin;
	end[ 2 ]-= maxfall;

	trace = G_Trace( start, mins, maxs, end, this, edict->clipmask, false, "Entity::droptofloor" );
	if ( trace.fraction == 1 || trace.startsolid || trace.allsolid || !trace.ent )
		{
		groundentity = world->edict;
		return false;
		}

	setOrigin( trace.endpos );

	groundentity = trace.ent;

	return true;
	}

void Entity::DamageType
   (
   Event *ev
   )

   {
   str damage;
   damage = ev->GetString( 1 );
   if ( damage == "all" )
      {
      damage_type = -1;
      }
   else
      {
      damage_type = MOD_string_to_int( damage );
      }
   }

void Entity::Damage
   (
   Entity *inflictor,
   Entity *attacker,
   float damage,
   Vector position,
   Vector direction,
   Vector normal,
   int knockback,
   int dflags,
   int meansofdeath
   )

   {
	Event	*ev;

   // if our damage types do not match, return
   if ( !MOD_matches( meansofdeath, damage_type ) )
      {
      return;
      }

	if ( !attacker )
		{
		attacker = world;
		}
	if ( !inflictor )
		{
		inflictor = world;
		}

	ev = new Event( EV_Damage );
	ev->AddFloat( damage );
	ev->AddEntity ( inflictor );
	ev->AddEntity ( attacker );
   ev->AddVector ( position );
   ev->AddVector ( direction );
   ev->AddVector ( normal );
   ev->AddInteger( knockback );
   ev->AddInteger( dflags );
   ev->AddInteger( meansofdeath );
   ProcessEvent  ( ev );
   }

void Entity::DamageEvent
	(
	Event *ev
	)

	{
	Entity	*inflictor;
	Entity	*attacker;
	int		damage;
	Vector	dir;
	Vector	momentum;
	Event		*event;
	float		m;

	if ( ( takedamage == DAMAGE_NO ) || ( movetype == MOVETYPE_NOCLIP ) )
		{
		return;
		}

	damage		= ev->GetInteger( 1 );
	inflictor	= ev->GetEntity( 2 );
	attacker		= ev->GetEntity( 3 );

	// figure momentum add
	if ( ( inflictor != world ) &&
		( movetype != MOVETYPE_NONE ) &&
		( movetype != MOVETYPE_STATIONARY ) &&
		( movetype != MOVETYPE_BOUNCE ) &&
		( movetype != MOVETYPE_PUSH ) &&
		( movetype != MOVETYPE_STOP ) )
		{
      dir = origin - ( inflictor->origin + ( inflictor->mins + inflictor->maxs ) * 0.5 );
		dir.normalize();

		if ( mass < 50)
			{
			m = 50;
			}
		else
			{
			m = mass;
			}

		momentum = dir * damage * ( 1700.0 / m );
		velocity += momentum;
		}

	// check for godmode or invincibility
	if ( flags & FL_GODMODE )
		{
		return;
		}

	// team play damage avoidance
	//if ( ( global->teamplay == 1 ) && ( edict->team > 0 ) && ( edict->team == attacker->edict->team ) )
	//	{
	//	return;
	//	}

   if ( !deathmatch->integer && isSubclassOf( Player ) )
      {
      damage *= 0.15;
      }

   if ( deadflag )
      {
      // Check for gib.
      if ( inflictor->isSubclassOf( Projectile ) )
         {
         Event *gibEv;

         health -= damage;

         gibEv = new Event( EV_Gib );
         gibEv->AddEntity( this );
         gibEv->AddFloat( health );
         ProcessEvent( gibEv );
         }
      return;
      }

	// do the damage
	health -= damage;
	if ( health <= 0 )
		{
      if ( attacker )
         {
		   event = new Event( EV_GotKill );
		   event->AddEntity( this );
		   event->AddInteger( damage );
		   event->AddEntity( inflictor );
         event->AddInteger( ev->GetInteger( 9 ) );
         event->AddInteger( 0 );
		   attacker->ProcessEvent( event );
         }

		event = new Event( EV_Killed );
		event->AddEntity( attacker );
		event->AddInteger( damage );
		event->AddEntity( inflictor );
		ProcessEvent( event );
		return;
		}

	event = new Event( EV_Pain );
	event->AddFloat( damage );
	event->AddEntity( attacker );
	ProcessEvent( event );
	}

void Entity::Stun
   (
   float time
   )

   {
   Event *ev = new Event( EV_Stun );
   ev->AddFloat( time );
   ProcessEvent( ev );
   }

/*
============
CanDamage

Returns true if the inflictor can directly damage the target.  Used for
explosions and melee attacks.
============
*/
qboolean Entity::CanDamage
	(
	Entity *target,
	Entity *skip_ent
	)

	{
	trace_t	trace;
	Vector	pos;
	Entity	*skip_entity;

	if ( skip_ent )
		skip_entity = skip_ent;
	else
		skip_entity = this;

   trace = G_Trace( origin, vec_origin, vec_origin, target->centroid, skip_entity, MASK_SHOT, false, "Entity::CanDamage 1" );
	if ( trace.fraction == 1 || trace.ent == target->edict )
		{
		return true;
		}
	pos = target->centroid + Vector( 15, 15, 0 );
   trace = G_Trace( origin, vec_origin, vec_origin, pos, skip_entity, MASK_SHOT, false, "Entity::CanDamage 3" );
	if ( trace.fraction == 1 || trace.ent == target->edict )
		{
		return true;
		}
	pos = target->centroid + Vector( -15, 15, 0 );
   trace = G_Trace( origin, vec_zero, vec_zero, pos, skip_entity, MASK_SHOT, false, "Entity::CanDamage 4" );
	if ( trace.fraction == 1 || trace.ent == target->edict )
		{
		return true;
		}
	pos = target->centroid + Vector( 15, -15, 0 );
   trace = G_Trace( origin, vec_zero, vec_zero, pos, skip_entity, MASK_SHOT, false, "Entity::CanDamage 5" );
	if ( trace.fraction == 1 || trace.ent == target->edict )
		{
		return true;
		}
  	pos = target->centroid + Vector( -15, -15, 0 );
   trace = G_Trace( origin, vec_zero, vec_zero, pos, skip_entity, MASK_SHOT, false, "Entity::CanDamage 6" );
	if ( trace.fraction == 1 || trace.ent == target->edict )
		{
		return true;
		}

	return false;
	}

qboolean Entity::IsTouching
	(
	Entity *e1
	)

	{
	if ( e1->absmin.x > absmax.x )
		{
		return false;
		}
	if ( e1->absmin.y > absmax.y )
		{
		return false;
		}
	if ( e1->absmin.z > absmax.z )
		{
		return false;
		}
	if ( e1->absmax.x < absmin.x )
		{
		return false;
		}
	if ( e1->absmax.y < absmin.y )
		{
		return false;
		}
	if ( e1->absmax.z < absmin.z )
		{
		return false;
		}

	return true;
	}

void Entity::FadeNoRemove
	(
	Event *ev
	)

	{
   float rate;
   float target;
   float myalpha;

   if ( ev->NumArgs() > 1 )
      {
      target = ev->GetFloat( 2 );
      }
   else
      {
      target = 0;
      }

   if ( ev->NumArgs() > 0 )
      {
      rate = ev->GetFloat( 1 );
      assert( rate );
      if ( rate > 0 )
         rate = FRAMETIME / rate;
      }
   else
      {
      rate = 0.03;
      }

   myalpha = edict->s.alpha;
   myalpha -= rate;
   
   if ( myalpha < target )
      myalpha = target;

   setAlpha( myalpha );

   if ( myalpha > target )
      {
      PostEvent( *ev, FRAMETIME );
      }

   G_SetConstantLight( &edict->s.constantLight, &myalpha, &myalpha, &myalpha, 0 );
	}

void Entity::FadeOut
	(
	Event *ev
	)

	{
   float myscale;
   float myalpha;

   myscale = edict->s.scale;
   myscale -= 0.03f;
   myalpha = edict->s.alpha;
   myalpha -= 0.03f;
   if ( myscale < 0 )
      myscale = 0;
   if ( myalpha < 0 )
      myalpha = 0;

	if ( myscale <= 0 && myalpha <= 0 )
		{
	   PostEvent( EV_Remove, 0 );
		}
   else
      {
	   PostEvent( *ev, FRAMETIME );
      }

   setScale( myscale );
   setAlpha( myalpha );
	}

void Entity::FadeIn
	(
	Event *ev
	)

	{
   float rate;
   float target;
   float myalpha;

   if ( ev->NumArgs() > 1 )
      {
      target = ev->GetFloat( 2 );
      }
   else
      {
      target = 1;
      }

   if ( ev->NumArgs() > 0 )
      {
      rate = ev->GetFloat( 1 );
      assert( rate );
      if ( rate > 0 )
         rate = FRAMETIME / rate;
      }
   else
      {
      rate = 0.03;
      }


   myalpha = edict->s.alpha;
   myalpha += rate;

   if ( myalpha > target )
      myalpha = target;
   
   if ( myalpha < target )
		{
   	PostEvent( *ev, FRAMETIME );
		}
   setAlpha( myalpha );
	}

void Entity::Fade
	(
	Event *ev
	)

	{
   float rate;
   float target;
   float myalpha;

   if ( ev->NumArgs() > 1 )
      {
      target = ev->GetFloat( 2 );
      }
   else
      {
      target = 0;
      }

   if ( ev->NumArgs() > 0 )
      {
      rate = ev->GetFloat( 1 );
      assert( rate );
      if ( rate > 0 )
         rate = FRAMETIME / rate;
      }
   else
      {
      rate = 0.03;
      }

   myalpha = edict->s.alpha;
   myalpha -= rate;
   
   if ( myalpha <= 0 )
		{
	   PostEvent( EV_Remove, 0 );
      return;
		}

   if ( myalpha < target )
      myalpha = target;

   if ( myalpha > target )
      {
      PostEvent( *ev, FRAMETIME );
      }

   setAlpha( myalpha );
   G_SetConstantLight( &edict->s.constantLight, &myalpha, &myalpha, &myalpha, 0 );
	}

void Entity::SetMassEvent
	(
	Event *ev
	)

	{
   mass = ev->GetFloat( 1 );
	}

void Entity::CheckGround
	(
   void
	)

	{
	Vector	point;
	trace_t	trace;

	if ( flags & ( FL_SWIM | FL_FLY ) )
		{
		return;
		}

	if ( velocity.z > 100 )
		{
		groundentity = NULL;
		return;
		}

	// if the hull point one-quarter unit down is solid the entity is on ground
   point = origin;
	point.z -= 0.25;
   trace = G_Trace( origin, mins, maxs, point, this, edict->clipmask, false, "Entity::CheckGround" );

	// check steepness
	if ( ( trace.plane.normal[ 2 ] <= 0.7 ) && !trace.startsolid )
		{
		groundentity = NULL;
		return;
		}

	groundentity = trace.ent;
	groundplane = trace.plane;
	groundcontents = trace.contents;

	if ( !trace.startsolid && !trace.allsolid )
		{
		setOrigin( trace.endpos );
		velocity.z = 0;
		}
	}

void Entity::BecomeSolid
	(
	Event *ev
	)

	{
	if ( ( model.length() ) && ( ( model[ 0 ] == '*' ) || ( strstr( model.c_str(), ".bsp" ) ) ) )
		{
		setSolidType( SOLID_BSP );
		}
	else
		{
		setSolidType( SOLID_BBOX );
		}
	}

void Entity::BecomeNonSolid
	(
	Event *ev
	)

	{
	setSolidType( SOLID_NOT );
	}

void Entity::Ghost
	(
	Event *ev
	)

	{
   // Make not solid, but send still send over whether it is hidden or not
	setSolidType( SOLID_NOT );
   edict->svflags &= ~SVF_NOCLIENT;
	}

void Entity::LoopSound
	( 
	Event *ev 
	)

	{
	str sound_name;
	float volume   = DEFAULT_VOL;
	float min_dist = DEFAULT_MIN_DIST;
	str min_dist_string;

	
	if (ev->NumArgs() < 1)
		return;

	// Get parameters

	sound_name = ev->GetString( 1 );

	if ( ev->NumArgs() > 1 )
		volume = ev->GetFloat( 2 );

	if ( ev->NumArgs() > 2 )
		{
		min_dist_string = ev->GetString( 3 );

		if ( min_dist_string == LEVEL_WIDE_STRING )
			min_dist = LEVEL_WIDE_MIN_DIST;
		else
			min_dist = ev->GetFloat( 3 );
		}

	// Add this sound to loop

	LoopSound( sound_name.c_str(), volume, min_dist );
	}

void Entity::LoopSound( str sound_name, float volume, float min_dist )
	{
	const char *name = NULL;
	str random_alias;


	// Get the real sound to be played

	if ( sound_name.length() > 0 )
		{
		// Get the real sound to play

		name = gi.GlobalAlias_FindRandom( sound_name.c_str() );

		if ( !name )
			{
			random_alias = GetRandomAlias( sound_name ).c_str();

			if ( random_alias.length() > 0 )
				name = random_alias.c_str();
			}

		if ( !name )
			name = sound_name.c_str();

		// Add the looping sound to the entity

      edict->s.loopSound        = gi.soundindex( name );
		edict->s.loopSoundVolume  = volume;
		edict->s.loopSoundMinDist = min_dist;
		}
	}

void Entity::StopLoopSound( Event *ev )
	{
   StopLoopSound();
	}

void Entity::StopLoopSound( void )
	{
   edict->s.loopSound = 0;
	}

void Entity::Sound( Event *ev )
	{
	str sound_name;
	float volume;
   int channel;
   float min_dist;
   int i;
	str min_dist_string;


   // Set defaults
   
   volume   = DEFAULT_VOL;
	min_dist = DEFAULT_MIN_DIST;
   channel  = CHAN_BODY;

	// Get sound parameters
  
   for ( i = 1 ; i <= ev->NumArgs() ; i++ )
      {
      switch (i-1)
         {
         case 0:
            sound_name = ev->GetString( i );
            break;
         case 1:
            channel = ev->GetInteger( i );
            break;
			case 2:
            volume = ev->GetFloat( i );
            break;
         case 3:
				min_dist_string = ev->GetString( i );

				if ( min_dist_string == LEVEL_WIDE_STRING )
					min_dist = LEVEL_WIDE_MIN_DIST;
				else
					min_dist = ev->GetFloat( i );
            break;
         default:
            break;
         }
      }

	Sound( sound_name, channel, volume, min_dist, NULL );
	}

void Entity::StopSound
	(
	Event *ev
	)

	{
   if (ev->NumArgs() < 1)
      StopSound( CHAN_BODY );
   else
      StopSound( ev->GetInteger( 1 ) );
	}

void Entity::StopSound
	(
	int channel
	)

	{
		gi.StopSound( entnum, channel );
	}

void Entity::SetLight
	(
	Event *ev
	)

	{
   float r, g, b;

   if ( ev->NumArgs() == 1 )
      {
      Vector tmp;

      tmp = ev->GetVector( 1 );
      r = tmp.x;
      g = tmp.y;
      b = tmp.z;
      }
   else
      {
      r = ev->GetFloat( 1 );
      g = ev->GetFloat( 2 );
      b = ev->GetFloat( 3 );
      lightRadius  = ev->GetFloat( 4 );
      }

   G_SetConstantLight( &edict->s.constantLight, &r, &g, &b, &lightRadius );
   }

void Entity::LightOn
	(
	Event *ev
	)

	{
   G_SetConstantLight( &edict->s.constantLight, NULL, NULL, NULL, &lightRadius );
   }

void Entity::LightOff
	(
	Event *ev
	)

	{
   float radius = 0;

   G_SetConstantLight( &edict->s.constantLight, NULL, NULL, NULL, &radius );
   }

void Entity::LightRed
	(
	Event *ev
	)

	{
   float r;

   r = ev->GetFloat( 1 );
   G_SetConstantLight( &edict->s.constantLight, &r, NULL, NULL, NULL );
   }

void Entity::LightGreen
	(
	Event *ev
	)

	{
   float g;

   g = ev->GetFloat( 1 );
   G_SetConstantLight( &edict->s.constantLight, NULL, &g, NULL, NULL );
   }

void Entity::LightBlue
	(
	Event *ev
	)

	{
   float b;

   b = ev->GetFloat( 1 );
   G_SetConstantLight( &edict->s.constantLight, NULL, NULL, &b, NULL );
   }

void Entity::LightRadius
	(
	Event *ev
	)

	{
   lightRadius = ev->GetFloat( 1 );
   G_SetConstantLight( &edict->s.constantLight, NULL, NULL, NULL, &lightRadius );
   }

void Entity::LightStyle
	(
	Event *ev
	)

	{
   int style;

   style = ev->GetInteger( 1 );
   G_SetConstantLight( &edict->s.constantLight, NULL, NULL, NULL, NULL, &style );
   }

void Entity::SetHealth
	(
	Event *ev
	)

	{
	health = ev->GetFloat( 1 );
   max_health = health;
	}

void Entity::SetSize
	(
	Event *ev
	)

	{
	Vector min, max;

   min = ev->GetVector( 1 );
   max = ev->GetVector( 2 );
   setSize( min, max );
   }

void Entity::SetMins
	(
	Event *ev
	)

	{
	Vector min;

   min = ev->GetVector( 1 );
   setSize( min, maxs );
   }

void Entity::SetMaxs
	(
	Event *ev
	)

	{
	Vector max;

   max = ev->GetVector( 1 );
   setSize( mins, max );
   }

void Entity::SetScale
	(
	Event *ev
	)

	{
	setScale( ev->GetFloat( 1 ) );
   }

void Entity::SetAlpha
	(
	Event *ev
	)

	{
	setAlpha( ev->GetFloat( 1 ) );
   }

void Entity::SetOrigin
	(
	Event *ev
	)

	{
	setOrigin( ev->GetVector( 1 ) );
	}

void Entity::SetTargetName
	(
	Event *ev
	)

	{
	SetTargetName( ev->GetString( 1 ) );
	}

void Entity::SetTarget
	(
	Event *ev
	)

	{
	SetTarget( ev->GetString( 1 ) );
	}

void Entity::SetKillTarget
	(
	Event *ev
	)

	{
	SetKillTarget( ev->GetString( 1 ) );
	}

void Entity::SetAngles
	(
	Event *ev
	)

	{
	setAngles( ev->GetVector( 1 ) );
	}

Vector Entity::GetControllerAngles
	(
	int num
	)

	{
	Vector controller_angles;

   assert( ( num >= 0 ) && ( num < NUM_BONE_CONTROLLERS ) );

   if ( ( num < 0 ) || ( num >= NUM_BONE_CONTROLLERS ) )
      {
      error( "GetControllerAngles", "Bone controller index out of range (%d)\n", num );
      return vec_zero;
      }

	controller_angles = edict->s.bone_angles[ num ];

   return controller_angles;
   }

void Entity::SetControllerAngles
	(
	int num,
   vec3_t angles
	)

	{
   assert( ( num >= 0 ) && ( num < NUM_BONE_CONTROLLERS ) );

   if ( ( num < 0 ) || ( num >= NUM_BONE_CONTROLLERS ) )
      {
      error( "SetControllerAngles", "Bone controller index out of range (%d)\n", num );
      return;
      }

   VectorCopy( angles, edict->s.bone_angles[ num ] );
   EulerToQuat( edict->s.bone_angles[ num ], edict->s.bone_quat[ num ] );
   }

void Entity::SetControllerAngles
	(
	Event *ev
	)

	{
	int num;
   Vector angles;

	if ( ev->NumArgs() < 2 )
		return;

	num = ev->GetInteger( 1 );
	angles = ev->GetVector( 2 );

	SetControllerAngles( num, angles );
   }

void Entity::SetControllerTag
	(
	int num,
   int tag_num
	)

	{
   assert( ( num >= 0 ) && ( num < NUM_BONE_CONTROLLERS ) );

   if ( ( num < 0 ) || ( num >= NUM_BONE_CONTROLLERS ) )
      {
      error( "SetControllerTag", "Bone controller index out of range (%d)\n", num );
      return;
      }

   edict->s.bone_tag[ num ] = tag_num;
   }

void Entity::RegisterAlias
	(
	Event *ev
	)

	{
	char parameters[100];
	int i;

	// Get the parameters for this alias command

	parameters[0] = 0;

	for( i = 3 ; i <= ev->NumArgs() ; i++ )
	{
		strcat( parameters, ev->GetString( i ) );
		strcat( parameters, " ");
	}
	
   gi.Alias_Add( edict->s.modelindex, ev->GetString( 1 ), ev->GetString( 2 ),  parameters );
	}

void Entity::Cache
	(
	Event *ev
	)

	{
   CacheResource( ev->GetString( 1 ), this );
   }

void Entity::RegisterAliasAndCache
	(
	Event *ev
	)

	{
	RegisterAlias(ev);

   CacheResource( ev->GetString( 2 ), this );
	}

void Entity::Sound
	(
	str sound_name,
   int   channel,
	float volume,
   float min_dist,
	Vector *sound_origin
	)
	{
	const char *name = NULL;
	vec3_t org;
	str random_alias;


	if ( sound_name.length() > 0 )
		{
		// Get the real sound to play

		name = gi.GlobalAlias_FindRandom( sound_name.c_str() );

		if ( !name )
			{
			random_alias = GetRandomAlias( sound_name ).c_str();

			if ( random_alias.length() > 0 )
				name = random_alias.c_str();
			}

		if ( !name )
			name = sound_name.c_str();

		// Play the sound

		if ( name != NULL )
			{
			if ( sound_origin != NULL)
				{
				sound_origin->copyTo( org );
				entnum = ENTITYNUM_NONE;
				}
			else
				{
				VectorCopy( edict->s.origin, org );
				}
				
			gi.Sound( &org, entnum, channel, name, volume, min_dist );
			}
		}
	else
		{
		warning( "Sound", "Null sample pointer" );
		}
	}

qboolean Entity::attach
	(
   int parent_entity_num,
   int tag_num,
	qboolean use_angles,
	Vector offset
	)

	{
   int i;
   Entity * parent;

   if ( entnum == parent_entity_num )
      {
      warning("attach","Trying to attach to oneself." );
      return false;
      }

   if ( edict->s.parent != ENTITYNUM_NONE )
      detach();

   // 
   // make sure this is a modelanim entity so that the attach works properly
   //
   if ( edict->s.eType == ET_GENERAL )
      {
      edict->s.eType = ET_MODELANIM;
      }

   //
   // get the parent
   //
   parent = ( Entity * )G_GetEntity( parent_entity_num );

   if (parent->numchildren < MAX_MODEL_CHILDREN)
      {
      //
      // find a free spot in the parent
      //
      for ( i=0; i < MAX_MODEL_CHILDREN; i++ )
         if ( parent->children[i] == ENTITYNUM_NONE )
            {
            break;
            }
      edict->s.parent = parent_entity_num;
      setSolidType( SOLID_NOT );
      parent->children[i] = entnum;
      parent->numchildren++;
      edict->s.tag_num = tag_num;
		edict->s.attach_use_angles = use_angles;
		offset.copyTo( edict->s.attach_offset );
      setOrigin();
      return true;
      }
   return false;
	}

void Entity::KillAttach
	(
	Event *ev
	)

	{
   int i;
	Entity *child = NULL;


	// Kill all of this entities children

   for ( i = 0 ; i < MAX_MODEL_CHILDREN; i++ )
      {
      if ( children[i] != ENTITYNUM_NONE )
         {
			// Remove child
			child = ( Entity * )G_GetEntity( children[i] );

			if ( child )
				child->ProcessEvent( EV_Remove );

			// Remove child from this entity
			children[i] = ENTITYNUM_NONE;
         }
      }

	numchildren = 0;
	}

void Entity::detach
	(
	void
	)

	{
   int i;
   int num;
   Entity * parent;

   if ( edict->s.parent == ENTITYNUM_NONE )
      return;

   parent = ( Entity * )G_GetEntity( edict->s.parent );
   if (!parent)
      return;
   for ( i=0,num = parent->numchildren; i < MAX_MODEL_CHILDREN; i++ )
      {
      if ( parent->children[i] == ENTITYNUM_NONE )
         {
         continue;
         }
      if (parent->children[i] == entnum)
         {
         parent->children[i] = ENTITYNUM_NONE;
         parent->numchildren--;
         break;
         }
      num--;
      if (!num)
         break;
      }
   edict->s.parent = ENTITYNUM_NONE;
   setOrigin( origin );
	}

void Entity::Flags( Event *ev )
   {
   const char *flag;
   int mask;
   int action;
   int i;

   for ( i = 1; i <= ev->NumArgs(); i++ )
      {
      action = FLAG_IGNORE;
      flag = ev->GetString( i );
      switch( flag[0] )
         {
         case '+':
            action = FLAG_ADD;
            flag++;
            break;
         case '-':
            action = FLAG_CLEAR;
            flag++;
            break;
         default:
            ev->Error( "Entity::Flags", "First character is not '+' or '-', assuming '+'\n" );
            action = FLAG_ADD;
            break;
         }

      //
      // WARNING: please change the Event decleration,
      // to match this function, if flags are added or
      // deleted the event must be updated.
      // 
      if ( !stricmp( flag, "blood" ) )
         mask = FL_BLOOD;
      else if ( !stricmp( flag, "explode" ) )
         mask = FL_DIE_EXPLODE;
      else if ( !stricmp( flag, "die_gibs" ) )
         mask = FL_DIE_GIBS;
      else if ( !stricmp( flag, "autoaim" ) )
         mask = FL_AUTOAIM;
      else if ( !stricmp( flag, "god" ) )
         mask = FL_GODMODE;
      else
         {
         mask = 0;
         action = FLAG_IGNORE;
         ev->Error( "Unknown flag '%s'", flag );
         }
      switch (action)
         {
         case FLAG_ADD:
            flags |= mask;
            break;
         case FLAG_CLEAR:
            flags &= ~mask;
            break;
         case FLAG_IGNORE:
            break;
         }
      }
   if ( !com_blood->integer )
      {
      if ( flags & (FL_BLOOD|FL_DIE_GIBS) )
         {
         flags &= ~FL_BLOOD;
         flags &= ~FL_DIE_GIBS;
         }
      }
   }


void Entity::Effects( Event *ev )
   {
   const char *flag;
   int mask=0;
   int action;
   int i;

   for ( i = 1; i <= ev->NumArgs(); i++ )
      {
      action = 0;
      flag = ev->GetString( i );
      switch( flag[0] )
         {
         case '+':
            action = FLAG_ADD;
            flag++;
            break;
         case '-':
            action = FLAG_CLEAR;
            flag++;
            break;
         default:
            ev->Error( "Entity::Effects", "First character is not '+' or '-', assuming '+'\n" );
            action = FLAG_ADD;
            break;
         }

      //
      // WARNING: please change the Event decleration,
      // to match this function, if flags are added or
      // deleted the event must be updated.
      // 
      if ( !stricmp( flag, "everyframe" ) )
         mask = EF_EVERYFRAME;
      if ( !stricmp( flag, "antisbjuice" ) )
         mask = EF_ANTISBJUICE;
      else
         {
         action = FLAG_IGNORE;
         ev->Error( "Unknown token %s.", flag );
         }

      switch (action)
         {
         case FLAG_ADD:
            edict->s.eFlags |= mask;
            break;
         case FLAG_CLEAR:
            edict->s.eFlags &= ~mask;
            break;
         case FLAG_IGNORE:
            break;
         }
      }
   }

void Entity::RenderEffects( Event *ev )
   {
   const char *flag;
   int mask=0;
   int action;
   int i;

   for ( i = 1; i <= ev->NumArgs(); i++ )
      {
      action = 0;
      flag = ev->GetString( i );
      switch( flag[0] )
         {
         case '+':
            action = FLAG_ADD;
            flag++;
            break;
         case '-':
            action = FLAG_CLEAR;
            flag++;
            break;
         default:
            ev->Error( "Entity::RenderEffects", "First character is not '+' or '-', assuming '+'\n" );
            action = FLAG_ADD;
            break;
         }

      //
      // WARNING: please change the Event decleration,
      // to match this function, if flags are added or
      // deleted the event must be updated.
      // 
      if ( !stricmp( flag, "dontdraw" ) )
         mask = RF_DONTDRAW;
      else if ( !stricmp( flag, "betterlighting" ) )
         mask = RF_EXTRALIGHT;
      else if ( !stricmp ( flag, "lensflare" ) )
         mask = RF_LENSFLARE;
      else if ( !stricmp ( flag, "viewlensflare" ) )
         mask = RF_VIEWLENSFLARE;
      else if ( !stricmp ( flag, "lightoffset" ) )
         mask = RF_LIGHTOFFSET;
      else if ( !stricmp( flag, "skyorigin" ) )
         mask = RF_SKYORIGIN;
      else if ( !stricmp( flag, "fullbright" ) )
         mask = RF_FULLBRIGHT;
      else if ( !stricmp( flag, "minlight" ) )
         mask = RF_MINLIGHT;
      else if ( !stricmp( flag, "additivedynamiclight" ) )
         mask = RF_ADDITIVE_DLIGHT;
      else if ( !stricmp( flag, "lightstyledynamiclight" ) )
         mask = RF_LIGHTSTYLE_DLIGHT;
      else if ( !stricmp( flag, "shadow" ) )
         mask = RF_SHADOW;
      else if ( !stricmp( flag, "preciseshadow" ) )
         mask = RF_SHADOW_PRECISE;
      else if ( !stricmp( flag, "invisible" ) )
         mask = RF_INVISIBLE;
      else
         {
         action = FLAG_IGNORE;
         ev->Error( "Unknown token %s.", flag );
         }

      switch (action)
         {
         case FLAG_ADD:
            edict->s.renderfx |= mask;
            break;
         case FLAG_CLEAR:
            edict->s.renderfx &= ~mask;
            break;
         case FLAG_IGNORE:
            break;
         }
      }
   }

void Entity::SVFlags
   (
   Event *ev
   )
   
   {
   const char *flag;
   int mask=0;
   int action;
   int i;

   for ( i = 1; i <= ev->NumArgs(); i++ )
      {
      action = 0;
      flag = ev->GetString( i );
      switch( flag[0] )
         {
         case '+':
            action = FLAG_ADD;
            flag++;
            break;
         case '-':
            action = FLAG_CLEAR;
            flag++;
            break;
         default:
            ev->Error( "Entity::SVFlags", "First character is not '+' or '-', assuming '+'\n" );
            action = FLAG_ADD;
            break;
         }

      //
      // WARNING: please change the Event decleration,
      // to match this function, if flags are added or
      // deleted the event must be updated.
      // 
      if ( !stricmp( flag, "broadcast" ) )
         mask = SVF_BROADCAST;
      else if ( !stricmp( flag, "sendonce" ) )
         mask = SVF_SENDONCE;
      else
         {
         action = FLAG_IGNORE;
         ev->Error( "Unknown token %s.", flag );
         }

      switch (action)
         {
         case FLAG_ADD:
            edict->svflags |= mask;
            break;
         case FLAG_CLEAR:
            edict->svflags &= ~mask;
            break;
         case FLAG_IGNORE:
            break;
         }
      }

   if ( edict->svflags & SVF_SENDONCE )
      {
      // Turn this entity into an event if the SENDONCE flag is sent
      edict->s.eType = ET_EVENTS;
      }
   }

void Entity::BroadcastSound
	(
	float rad
	)

	{
	if ( !( this->flags & FL_NOTARGET ) )
		{
      G_BroadcastSound( this, centroid, rad );
      }
	}

void Entity::BroadcastSound
	(
	Event *ev
	)

	{
   float rad;

	if ( !( this->flags & FL_NOTARGET ) )
		{
      rad = ev->NumArgs() < 1 ? SOUND_RADIUS : ev->GetFloat( 1 );
      BroadcastSound( rad );
      }
	}

void Entity::Think
	(
	void
	)

	{
	}

void Entity::SetWaterType
   (
   void
   )

   {
   qboolean isinwater;

   watertype = gi.pointcontents( origin, 0 );
	isinwater = watertype & MASK_WATER;

	if ( isinwater )
		{
		waterlevel = 1;
		}
	else
		{
		waterlevel = 0;
		}
   }

void Entity::DamageSkin
   (
   trace_t * trace,
   float damage
   )

   {
   /* FIXME : Do we need damage skins?
   int surface;

   // FIXME handle different bodyparts
   surface = trace->intersect.surface;
   if ( !edict->s.surfaces[ surface ] )
		{
      edict->s.surfaces[ surface ]++;
		}
   */
   }

void Entity::Kill
	(
	Event *ev
	)

	{
	health = 0;
   Damage( this, this, 10, origin, vec_zero, vec_zero, 0, 0, MOD_SUICIDE );
	}


void Entity::SurfaceCommand
	(
   const char * surf_name,
   const char * token
	)

	{
	const char * current_surface_name;
   int surface_num;
   int mask;
   int action;
   qboolean do_all = false;
	qboolean mult = false;

  
	if ( surf_name[ strlen( surf_name ) - 1 ] == '*' )
		{
		mult = true;
		surface_num = 0;
		}
	else if ( str( surf_name ) != str( "all" ) )
      {
      surface_num = gi.Surface_NameToNum( edict->s.modelindex, surf_name );

      if (surface_num < 0)
         {
		   warning( "SurfaceCommand", "group %s not found.", surf_name );
         return;
         }
      }
   else
      {
      surface_num = 0;
      do_all = true;
      }

   action = 0;
   switch( token[0] )
      {
      case '+':
         action = FLAG_ADD;
         token++;
         break;
      case '-':
         action = FLAG_CLEAR;
         token++;
         break;
      default:
         warning( "Entity::SurfaceModelEvent", "First character is not '+' or '-', assuming '+'\n" );
         action = FLAG_ADD;
         break;
      }
   //
   // WARNING: please change the Event decleration,
   // to match this function, if flags are added or
   // deleted the event must be updated.
   // 
   if (!strcmpi( token, "skin1"))
      {
      mask = MDL_SURFACE_SKINOFFSET_BIT0;
      }
   else if (!strcmpi (token, "skin2"))
      {
      mask = MDL_SURFACE_SKINOFFSET_BIT1;
      }
   else if (!strcmpi (token, "nodraw"))
      {
      mask = MDL_SURFACE_NODRAW;
      }
   else if (!strcmpi (token, "crossfade"))
      {
      mask = MDL_SURFACE_CROSSFADE_SKINS;
      }
   else
      {
      mask = 0;
      warning( "SurfaceCommand", "Unknown token %s.", token );
      action = FLAG_IGNORE;
      }
   for( ; surface_num < numsurfaces ; surface_num++ )
      {
		if ( mult )
			{
			current_surface_name = gi.Surface_NumToName( edict->s.modelindex, surface_num );

			if ( Q_stricmpn( current_surface_name, surf_name, strlen( surf_name ) - 1) != 0 )
				continue;
			}

      switch (action)
         {
         case FLAG_ADD:
            edict->s.surfaces[ surface_num ] |= mask;
            break;
         case FLAG_CLEAR:
            edict->s.surfaces[ surface_num ] &= ~mask;
            break;
         case FLAG_IGNORE:
            break;
         }

      if ( !do_all && !mult )
         break;
      }
	}

void Entity::SurfaceModelEvent
	(
	Event *ev
	)

	{
   const char * surf_name;
   const char * token;
   int i;
  
   surf_name = ev->GetString( 1 );

   for ( i = 2; i <= ev->NumArgs() ; i++ )
      {
      token = ev->GetString( i );
      SurfaceCommand( surf_name, token );
      }
	}

void Entity::AttachEvent
	(
	Event * ev
	)
	{
   Entity * parent;
   const char * bone;
   int tagnum;
	qboolean use_angles = qtrue;
	Vector offset;

	parent = ev->GetEntity( 1 );
   bone = ev->GetString( 2 );

	if ( ev->NumArgs() > 2 )
		use_angles = ev->GetInteger( 3 );

	if ( ev->NumArgs() > 3 )
		offset = ev->GetVector( 4 );

   if ( !parent )
      return;

   tagnum = gi.Tag_NumForName( parent->edict->s.modelindex, bone );
   if ( tagnum >= 0 )
      {
      attach( parent->entnum, tagnum, use_angles, offset );
      }
   else
      {
      warning( "AttachEvent", "Tag %s not found", bone );
      }
   }

void Entity::AttachModelEvent
	(
	Event * ev
	)
	{
   Entity * obj;
   const char * bone;
   str modelname;
   int tagnum;
	float remove_time,fade_time,fade_delay;
	Vector offset;

   obj = new Animate;

	modelname = ev->GetString( 1 );
   bone = ev->GetString( 2 );
   if ( ev->NumArgs() > 2 )
		{
      obj->setScale( ev->GetFloat( 3 ) );
		}
   if ( ev->NumArgs() > 3 )
		{
      obj->SetTargetName( ev->GetString( 4 ) );
		}

	if ( ev->NumArgs() > 4 )
      obj->detach_at_death = ev->GetInteger( 5 );

	if ( ev->NumArgs() > 5 )
		{
		remove_time = ev->GetFloat( 6 );

		if ( remove_time != -1 )
			{
			Event *remove_event = new Event( EV_Remove );
			obj->PostEvent( remove_event, remove_time );
			}
		}

	if ( ev->NumArgs() > 6 )
		{
		Event *fade_event;

      fade_time = ev->GetFloat( 7 );

      if ( fade_time != -1 )
         {
   		obj->setAlpha( 0 );

	   	fade_event = new Event( EV_FadeIn );
		   fade_event->AddFloat( fade_time );
		   obj->PostEvent( fade_event, 0 );
         }
		}

 	if ( ev->NumArgs() > 7 )
		{
		Event *fade_event;

      fade_delay = ev->GetFloat( 8 );

      if ( fade_delay != -1 )
         {
         if ( ev->NumArgs() > 8 )
            fade_time = ev->GetFloat( 9 );
         else
            fade_time = 0;

	   	fade_event = new Event( EV_Fade );

         if ( fade_time )
            fade_event->AddFloat( fade_time );

		   obj->PostEvent( fade_event, fade_delay );
         }
		}

	if ( ev->NumArgs() > 9 )
		offset = ev->GetVector( 10 );

   obj->setModel( modelname );

   tagnum = gi.Tag_NumForName( edict->s.modelindex, bone );
   if ( tagnum >= 0 )
      {
      if ( !obj->attach( this->entnum, tagnum, true, offset ) )
         {
         //warning( "AttachModelEvent", "Could not attach model %s", modelname.c_str() );   
         delete obj;
         return;
         }      
      }
   else
      {
      warning( "AttachModelEvent", "Tag %s not found", bone );
      }
   }

void Entity::RemoveAttachedModelEvent
	(
	Event *ev
	)
	{
   const char *tag_name;
   int tag_num;
	int num;
	int i;
	Entity *ent;
	float fade_rate = 0;
	Event *fade_event;
	str model_name;

   tag_name = ev->GetString( 1 );
	tag_num = gi.Tag_NumForName( edict->s.modelindex, tag_name );

	if ( ev->NumArgs() > 1 )
		fade_rate = ev->GetFloat( 2 );

	if ( ev->NumArgs() > 2 )
		model_name = ev->GetString( 3 );

   if ( tag_num >= 0 )
      {
		num = numchildren;

		for ( i = 0 ; (i < MAX_MODEL_CHILDREN) && num ; i++ )
			{
			if ( children[i] == ENTITYNUM_NONE )
				continue;

			ent = ( Entity * )G_GetEntity( children[i] );

			if ( ent->edict->s.tag_num == tag_num )
				{
				if ( !model_name.length() || model_name == ent->model )
					{
					if ( fade_rate )
						{
						fade_event = new Event( EV_Fade );
						fade_event->AddFloat( fade_rate );
						fade_event->AddFloat( 0 );
						ent->PostEvent( fade_event, 0 );
						}

					ent->PostEvent( EV_Remove, fade_rate );
					}
				}
			
			num--;
			}
      }
   }

void Entity::DetachEvent
	(
	Event * ev
	)

	{
   if ( edict->s.parent == ENTITYNUM_NONE  )
		{
      return;
		}
   detach();
   }

void Entity::TakeDamageEvent
	(
	Event * ev
	)
	{
   takedamage = DAMAGE_YES;
   }

void Entity::NoDamageEvent
	(
	Event * ev
	)
	{
   takedamage = DAMAGE_NO;
   }

void Entity::Gravity
   (
   Event *ev
   )

   {
   gravity = ev->GetFloat( 1 );
   }

void Entity::UseBoundingBoxEvent
   (
   Event *ev
   )
   {
	edict->svflags |= SVF_USEBBOX;
   }

void Entity::HurtEvent
   (
   Event *ev
   )
   {
   Vector normal;
   float dmg;
	int means_of_death;
	Vector direction;

   if ( ev->NumArgs() < 1 )
      {
      dmg = 50;
      }
   else
      {
      dmg = ev->GetFloat( 1 );
      }

	if ( ev->NumArgs() > 1 )
		means_of_death = MOD_string_to_int( ev->GetString( 2 ) );
	else
		means_of_death = MOD_CRUSH;

	if ( ev->NumArgs() > 2 )
		{
		direction = ev->GetVector( 3 );
		direction.normalize();
		}
	else
		{
		direction = vec_zero;
		}

   normal = Vector( orientation[ 0 ] );
   Damage( world, world, dmg, centroid, direction, normal, dmg, 0, means_of_death );
   }

void Entity::IfSkillEvent
	(
	Event *ev
	)

	{
   float skilllevel;

	skilllevel = ev->GetFloat( 1 );

   if ( skill->value == skilllevel )
      {
	   int			argc;
	   int			numargs;
      Event       *event;
	   int			i;

	   numargs = ev->NumArgs();
	   argc = numargs - 2 + 1;

      event = new Event( ev->GetToken( 2 ) );

	   for( i = 1; i < argc; i++ )
		   {
         event->AddToken( ev->GetToken( 2 + i ) );
		   }
      ProcessEvent( event );
		}
	}

void Entity::Censor
	(
	Event *ev
	)

	{
   Vector delta;
   float oldsize;
   float newsize;

   if ( com_blood->integer )
      return;

   oldsize = size.length();
	setSolidType( SOLID_NOT );
   setModel( "censored.tik" );
   gi.CalculateBounds( edict->s.modelindex, 1, mins, maxs );
   delta = maxs - mins;
   newsize = delta.length();
   edict->s.scale = oldsize / newsize;
   mins *= edict->s.scale;
   maxs *= edict->s.scale;
   setSize( mins, maxs );
   setOrigin();
	}

void Entity::StationaryEvent
   (
   Event *ev
   )

	{
	setMoveType( MOVETYPE_STATIONARY );
	}

void Entity::Explosion
   (
   Event *ev
   )

   {
   str expmodel;
	str tag_name;
	//orientation_t orient;
	Vector explosion_origin;
   
	expmodel = ev->GetString( 1 );
	explosion_origin = origin;

	if ( ev->NumArgs() > 1 )
		{
		tag_name = ev->GetString( 2 );

		//if ( GetRawTag( tag_name.c_str(), &orient, legs ) )
		//	VectorAdd( orient.origin, origin, explosion_origin );

		GetTag( tag_name.c_str(), &explosion_origin );
		}

   ExplosionAttack( explosion_origin, this, expmodel );
   }

void Entity::Shader
	(
	Event *ev
	)

	{
   const char * token;

   if ( gi.IsModel( edict->s.modelindex ) )
      {
      ev->Error( "shader event being called on TIKI model\n" );
      }
   //
   // get sub shader command
   //
   token = ev->GetString( 1 );

   //
   // WARNING: please change the Event decleration,
   // to match this function, if flags are added or
   // deleted the event must be updated.
   // 
   if (!strcmpi( token, "translation"))
      {
      float x, y;

      x = ev->GetFloat( 2 );
      y = ev->GetFloat( 3 );
      TRANSLATION_TO_PKT( x, edict->s.tag_num );
      TRANSLATION_TO_PKT( y, edict->s.skinNum );
      }
   else if (!strcmpi( token, "offset"))
      {
      float x, y;

      x = ev->GetFloat( 2 );
      y = ev->GetFloat( 3 );
      OFFSET_TO_PKT( x, edict->s.tag_num );
      OFFSET_TO_PKT( y, edict->s.skinNum );
      }
   else if (!strcmpi (token, "rotation"))
      {
      float rot;

      rot = ev->GetFloat( 2 );
      ROTATE_TO_PKT( rot, edict->s.tag_num );
      }
   else if (!strcmpi (token, "frame"))
      {
      edict->s.frame = ev->GetInteger( 2 );
      }
   else if (!strcmpi (token, "wavebase"))
      {
      float base;

      base = ev->GetFloat( 2 );
      BASE_TO_PKT( base, edict->s.surfaces[ 0 ] );
      }
   else if (!strcmpi (token, "waveamp"))
      {
      float amp;

      amp = ev->GetFloat( 2 );
      AMPLITUDE_TO_PKT( amp, edict->s.surfaces[ 1 ] );
      }
   else if (!strcmpi (token, "wavephase"))
      {
      float phase;

      phase = ev->GetFloat( 2 );
      PHASE_TO_PKT( phase, edict->s.surfaces[ 2 ] );
      }
   else if (!strcmpi (token, "wavefreq"))
      {
      float freq;

      freq = ev->GetFloat( 2 );
      FREQUENCY_TO_PKT( freq, edict->s.surfaces[ 3 ] );
      }
	}

void Entity::DropToFloorEvent
   (
   Event *ev
   )

   {
   float range;

	if ( ev->NumArgs() > 0 )
      {
      range = ev->GetFloat( 1 );
      }
   else
      {
      range = MAP_SIZE;
      }
   if ( !droptofloor( range ) )
      {
      }
	}


//*************************************************************************
//
// BIND code 
//
//*************************************************************************

qboolean Entity::isBoundTo
   (
   Entity *master
   )

   {
   Entity *ent;

   for( ent = bindmaster; ent != NULL; ent = ent->bindmaster )
      {
      if ( ent == master )
         {
         return true;
         }
      }

   return false;
   }

void Entity::bind
	(
	Entity *master,
	qboolean use_my_angles
	)

	{
	float  mat[ 3 ][ 3 ];
	float  local[ 3 ][ 3 ];
	Vector ang;

	assert( master );
	if ( !master )
		{
		warning( "bind", "Null master entity" );
		return;
		}

   if ( master == this )
      {
      warning( "bind", "Trying to bind to oneself." );
      return;
      }

   // unbind myself from my master
   unbind();

	bindmaster = master;
	edict->s.bindparent = master->entnum;
	bind_use_my_angles = use_my_angles;

   // We are now separated from our previous team and are either
   // an individual, or have a team of our own.  Now we can join
   // the new bindmaster's team.  Bindmaster must be set before
   // joining the team, or we will be placed in the wrong position
   // on the team.
   joinTeam( master );

	// calculate local angles
	TransposeMatrix( bindmaster->orientation, mat );
	R_ConcatRotations( mat, orientation, local );
	MatrixToEulerAngles( local, ang );
	setAngles( ang );

   setOrigin( getParentVector( localorigin - bindmaster->origin ) );

   return;
   }

void Entity::unbind
	(
	void
	)

	{
   Entity *prev;
   Entity *next;
   Entity *last;
   Entity *ent;

	if ( !bindmaster )
		{
		return;
		}

	//bindmaster = NULL;

   // Check this GAMEFIX - should it be origin?
	localorigin = Vector( edict->s.origin );
	localangles = Vector( edict->s.angles );

   if ( !teammaster )
      {
      bindmaster = NULL;
		edict->s.bindparent = ENTITYNUM_NONE;
      //Teammaster already has been freed
      return;
      }

   // We're still part of a team, so that means I have to extricate myself
   // and any entities that are bound to me from the old team.
   // Find the node previous to me in the team
   prev = teammaster;

	for( ent = teammaster->teamchain; ent && ( ent != this ); ent = ent->teamchain )
		{
      prev = ent;
		}

   // If ent is not pointing to me, then something is very wrong.
   assert( ent );
   if ( !ent )
      {
      error( "unbind", "corrupt team chain\n" );
      }

   // Find the last node in my team that is bound to me.
   // Also find the first node not bound to me, if one exists.
   last = this;
   for( next = teamchain; next != NULL; next = next->teamchain )
      {
      if ( !next->isBoundTo( this ) )
         {
         break;
         }

      // Tell them I'm now the teammaster
      next->teammaster = this;
      last = next;
		}

   // disconnect the last member of our team from the old team
   last->teamchain = NULL;

   // connect up the previous member of the old team to the node that
   // follow the last node bound to me (if one exists).
   if ( teammaster != this )
      {
      prev->teamchain = next;
      if ( !next && ( teammaster == prev ) )
         {
         prev->teammaster = NULL;
         }
      }
   else if ( next )
      {
      // If we were the teammaster, then the nodes that were not bound to me are now
      // a disconnected chain.  Make them into their own team.
		for( ent = next; ent->teamchain != NULL; ent = ent->teamchain )
         {
         ent->teammaster = next;
			}
      next->teammaster = next;
	   next->flags &= ~FL_TEAMSLAVE;
      }

   // If we don't have anyone on our team, then clear the team variables.
   if ( teamchain )
      {
      // make myself my own team
      teammaster = this;
      }
   else
      {
      // no longer a team
      teammaster = NULL;
      }

	flags &= ~FL_TEAMSLAVE;
   bindmaster = NULL;
	edict->s.bindparent = ENTITYNUM_NONE;
	}

void Entity::EventUnbind
	(
	Event *ev
	)

	{
	unbind();
	}

void Entity::BindEvent
	(
	Event *ev
	)

	{
	Entity *ent;

	ent = ev->GetEntity( 1 );
	if ( ent )
		{
		bind( ent );
		}
	}


Vector Entity::getParentVector
	(
	Vector vec
	)

	{
	Vector pos;

	if ( !bindmaster )
		{
		return vec;
		}

	pos[ 0 ] = vec * bindmaster->orientation[ 0 ];
	pos[ 1 ] = vec * bindmaster->orientation[ 1 ];
	pos[ 2 ] = vec * bindmaster->orientation[ 2 ];

	return pos;
	}

//
// Team methods
//

void Entity::joinTeam
	(
	Entity *teammember
	)

	{
	Entity *ent;
   Entity *master;
   Entity *prev;
   Entity *next;

	if ( teammaster && ( teammaster != this ) )
		{
		quitTeam();
		}

	assert( teammember );
	if ( !teammember )
		{
		warning( "joinTeam", "Null entity" );
		return;
		}

	master = teammember->teammaster;
	if ( !master )
		{
		master = teammember;
		teammember->teammaster = teammember;
      teammember->teamchain = this;

      // make anyone who's bound to me part of the new team
      for( ent = teamchain; ent != NULL; ent = ent->teamchain )
         {
         ent->teammaster = master;
         }
      }
   else
      {
      // skip past the chain members bound to the entity we're teaming up with
      prev = teammember;
	   next = teammember->teamchain;
      if ( bindmaster )
         {
         // if we have a bindmaster, joing after any entities bound to the entity
         // we're joining
	      while( next && (( Entity *)next)->isBoundTo( teammember ) )
		      {
            prev = next;
		      next = next->teamchain;
		      }
         }
      else
         {
         // if we're not bound to someone, then put us at the end of the team
	      while( next )
		      {
            prev = next;
		      next = next->teamchain;
		      }
         }

      // make anyone who's bound to me part of the new team and
      // also find the last member of my team
      for( ent = this; ent->teamchain != NULL; ent = ent->teamchain )
         {
         ent->teamchain->teammaster = master;
         }

    	prev->teamchain = this;
      ent->teamchain = next;
      }

   teammaster = master;
	flags |= FL_TEAMSLAVE;
	}

void Entity::quitTeam
	(
	void
	)

	{
	Entity *ent;

	if ( !teammaster )
		{
		return;
		}

	if ( teammaster == this )
		{
      if ( !teamchain->teamchain )
         {
         teamchain->teammaster = NULL;
         }
      else
         {
		   // make next teammate the teammaster
		   for( ent = teamchain; ent; ent = ent->teamchain )
			   {
			   ent->teammaster = teamchain;
			   }
         }

      teamchain->flags &= ~FL_TEAMSLAVE;
		}
	else
		{
		assert( flags & FL_TEAMSLAVE );
		assert( teammaster->teamchain );

		ent = teammaster;
		while( ent->teamchain != this )
			{
			// this should never happen
			assert( ent->teamchain );

			ent = ent->teamchain;
			}

		ent->teamchain = teamchain;

		if ( !teammaster->teamchain )
			{
			teammaster->teammaster = NULL;
			}
		}

	teammaster = NULL;
	teamchain = NULL;
	flags &= ~FL_TEAMSLAVE;
	}

void Entity::EventQuitTeam
	(
	Event *ev
	)

	{
	quitTeam();
	}


void Entity::JoinTeam
	(
	Event *ev
	)

	{
	Entity *ent;

	ent = ev->GetEntity( 1 );
	if ( ent )
		{
		joinTeam( ent );
		}
	}

void Entity::AddToSoundManager
	(
	Event *ev
	)

	{
   SoundMan.AddEntity( this );
	}

inline qboolean Entity::HitSky
	(
	trace_t *trace
	)

	{
	assert( trace );
   if ( trace->surfaceFlags & SURF_SKY )
		{
		return true;
		}
	return false;
	}

qboolean Entity::HitSky
	(
	void
	)

	{
	return HitSky( &level.impact_trace );
	}

void Entity::SetAngleEvent
	(
	Event *ev
	)
	{
   Vector movedir;

   movedir = G_GetMovedir( ev->GetFloat( 1 ) );
	setAngles( movedir.toAngles() );
   }

void Entity::NoLerpThisFrame
	(
   void
	)
	{
   edict->s.eFlags ^= EF_TELEPORT_BIT;
   }

void Entity::Postthink
	(
	void
	)

	{
	}

void Entity::TouchTriggersEvent
	(
	Event *ev
	)
	{
   flags |= FL_TOUCH_TRIGGERS;
   }

void Entity::DeathSinkStart
	(
	Event *ev
	)
	{
	float time;

	// Stop the sink when we can't be seen anymore

	if ( maxs[2] >= 0 && maxs[2] < 200 )
		time = maxs[2] / 20;
	else
		time = 1;

	PostEvent( EV_Remove, time );

	// Start the sinking 

	ProcessEvent( EV_DeathSink );
	}

void Entity::DeathSink
	(
	Event *ev
	)
	{
	// Sink just a little

	origin[2] -= 1;
	setOrigin( origin );

	// Make sure the sink happens again next frame

	PostEvent( EV_DeathSink, FRAMETIME );
	}

void Entity::LookAtMe
	(
	Event *ev
	)
	{
	if ( ev->NumArgs() > 0 )
		look_at_me = ev->GetBoolean( 1 );
	else
		look_at_me = true;
	}

void Entity::VelocityModified
	(
   void
	)
	{
	}

void Entity::DetachAllChildren
	(
	Event *ev
	)

	{
   int i;

   for (i=0;i<MAX_MODEL_CHILDREN;i++)
      {
      Entity * ent;
      if ( children[i] == ENTITYNUM_NONE )
         continue;

      ent = ( Entity * )G_GetEntity( children[i] );
      if ( ent )
         {
         ent->PostEvent( EV_Remove, 0 );
         }
      }
	}

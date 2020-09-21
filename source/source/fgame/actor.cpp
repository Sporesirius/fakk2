//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/actor.cpp             $
// $Revision:: 250                                                            $
//   $Author:: Steven                                                         $
//     $Date:: 7/29/00 8:33p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/actor.cpp                  $
// 
// 250   7/29/00 8:33p Steven
// Fixed a wakeup problem when loading games.
// 
// 249   7/29/00 7:11p Steven
// Made mission fail if you hurt an edenlander.
// 
// 248   7/29/00 2:28p Steven
// Made it so LoadStateMap does not turn off think if we are
// loading a level.
// 
// 247   7/28/00 9:18p Steven
// Made minimum mass to spawn a big water ampoule 125.
// 
// 246   7/28/00 6:56p Steven
// Set boss health back to 0 if ai goes off.
// 
// 245   7/28/00 1:22p Steven
// Made save attack longer and names spawned items.
// 
// 244   7/27/00 11:46p Steven
// Fixed some depends/dependsnot dialog stuff.
// 
// 243   7/27/00 10:53p Steven
// Added always give water stuff, don't make actor go to sleep
// initially if already has a behavior, and changed the teleport
// effect on spawned actors.
// 
// 242   7/26/00 8:40p Steven
// Fixed a problem with actors getting stuck because of stepping
// up in the movement.
// 
// 241   7/26/00 6:14p Steven
// made it so small actors will not spawn a big water ampoule
// 
// 240   7/25/00 9:25p Steven
// Added damage allowed stuff, made set state run entry/exit
// commands, made it so when actors go into AI mode they turn
// sight/sound stuff back on, and fixed some spawning stuff.
// 
// 239   7/24/00 6:08p Steven
// Added ignore pain from actors and fixed some direct pathfinding
// issues.
// 
// 238   7/24/00 12:15p Steven
// Only update boss health when boss is in ai mode.
// 
// 237   7/23/00 7:58p Steven
// Fixed some boss health stuff.
// 
// 236   7/23/00 5:59p Steven
// Fixed some checkanimname stuff.
// 
// 235   7/23/00 5:12p Steven
// Added check animname.
// 
// 234   7/22/00 3:01p Steven
// Added boss health bar stuff.
// 
// 233   7/22/00 1:18p Steven
// Added water level stuff.
// 
// 232   7/20/00 6:22p Steven
// Tweaked actor spawn items stuff a little.
// 
// 231   7/19/00 9:18p Steven
// Fixed checkmovingactorrange.
// 
// 230   7/19/00 5:08p Steven
// Added electric water means of death and fixed max gibs when
// dying by gib death.
// 
// 229   7/17/00 6:56p Steven
// Fixed a bug in Likes and added the spawning of a big fruit
// item.
// 
// 228   7/17/00 4:42p Steven
// Fixed up some plasma stuff in SpawnItem and made it so we won't
// spawn any ammo for weapons the player doesn't have yet.
// 
// 227   7/17/00 3:15p Steven
// added increment/decrement num spawns stuff
// 
// 226   7/16/00 4:36p Steven
// Moved action level stuff to actor pain and killed.
// 
// 225   7/16/00 2:35p Steven
// Moved Julie watching talking actor events to behavior.
// 
// 224   7/15/00 3:11p Steven
// Added no pain sounds stuff.
// 
// 223   7/15/00 12:47p Steven
// Fixed friend attacking other friends.
// 
// 222   7/14/00 5:38p Steven
// Made spawned items not go through playerclips.
// 
// 221   7/14/00 4:42p Steven
// Made playdialogs from script have no attenuation and added
// blind/deaf prints to actorinfo.
// 
// 220   7/13/00 7:28p Steven
// Fixed some targetname stuff.
// 
// 219   7/13/00 6:52p Steven
// Fixed some means of death stuff.
// 
// 218   7/13/00 5:42p Steven
// Fixed spawned in items from killing actors.
// 
// 217   7/13/00 3:42p Steven
// Added some simple path finding stuff and saved groundtrace
// results so we don't have to checkground.
// 
// 216   7/13/00 12:29p Steven
// Added some ignore sound stuff, made actors not do pain sounds
// as much, and make sure gibs don't process their init commands.
// 
// 215   7/12/00 3:36p Steven
// Made lots of optimizations to actors.
// 
// 214   7/12/00 11:24a Steven
// Fixed some talk mode stuff.
// 
// 213   7/11/00 11:08p Markd
// fixed crash bug where spawnitem wasn't being checked for NULL
// pointer
// 
// 212   7/11/00 10:16p Markd
// spawned in ammo_plasma instead of ammo_bolt which is no more
// 
// 211   7/11/00 7:07p Steven
// Made it so turntowardsenemy would work with killed enemies.
// 
// 210   7/10/00 5:10p Steven
// Made it if get an anim command only go to script mode if
// command came from script and fixed stationary actors dying
// correctly.
// 
// 209   7/07/00 6:34p Steven
// If actor is immmune to mod don't overwrite mod if already set
// this frame amd added more fail level stuff.
// 
// 208   7/06/00 4:43p Steven
// Made sure when reposting an event to save the thread also and
// made sure to set the currentBehavior when restoring a mode.
// 
// 207   7/06/00 12:59p Steven
// Made a way to stimuli an attack without it attacking the entity
// that caused it pain and made spawned actors fade out almost
// immediately.
// 
// 206   7/06/00 9:23a Steven
// Added damage angles stuff.
// 
// 205   7/06/00 7:47a Steven
// Added enemy on ground  check.
// 
// 204   7/05/00 5:17p Steven
// Added part of the code to make the player fail the level if she
// kills an innocent.
// 
// 203   7/05/00 2:27p Steven
// Fixed reposting of events.
// 
// 202   7/03/00 6:58p Steven
// Made actors wakeup instead op just turning on think, added some
// check shield stuff, and made spawned items have a mask of
// MASK_SOLID.
// 
// 201   7/02/00 5:55p Steven
// Added SetIdleStateName.
// 
// 200   7/02/00 5:08p Steven
// Added SpawnActorAtLocation, cleaned up the SpawnActor stuff and
// made it so all actors could gib if killed with mod of gib
// regardless if a bloodmodel is set.
// 
// 199   7/02/00 1:10p Steven
// Added a RunThread event.
// 
// 198   7/01/00 6:07p Steven
// Added falling damage for actors and added a bool parm for
// allowfall.
// 
// 197   7/01/00 12:01p Steven
// Moved actor droptofloor back to 16 because it was causing some
// problems and added electricsword means of death.
// 
// 196   6/30/00 5:05p Steven
// Added on fire check.
// 
// 195   6/30/00 11:40a Steven
// Added a blocked check.
// 
// 194   6/30/00 10:45a Markd
// added MOVETYPE_STATIONARY and revamped some physics
// 
// 193   6/30/00 10:20a Steven
// Added some stuck/off ground stuff and allowed the suicide event
// to keep the old means of death.
// 
// 192   6/30/00 7:51a Steven
// Added impact_sever sound call for cutting off a limb.
// 
// 191   6/29/00 5:20p Steven
// Added min and max height for in range stuff.
// 
// 190   6/28/00 3:11p Steven
// Added level wide ai_off and made actors being touched use
// STIMULI_SIGHT instead of STILUMI_PAIN.
// 
// 189   6/27/00 5:44p Steven
// Made actors drop a little farther at start(32 now), made actors
// not broadcast sound in pain if dead or immune to the damage,
// changed notsolidmask from DEADSOLID TO SOLID, and made actors
// not do babble dialog for at least 5 seconds after a cinematic.
// 
// 188   6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 187   6/26/00 4:51p Steven
// Fixed some active/sleep list issues.
// 
// 186   6/26/00 12:21p Steven
// Printing out better info on stuck warning.
// 
// 185   6/24/00 7:00p Steven
// Fixed SaveAttack not tracing far enough, made InitState only
// get called if a valid state is set and fixed the loading parm
// in LoadStateMap.
// 
// 184   6/24/00 11:21a Steven
// Added check to constructor that doesn't let event get posted if
// loading a savegame and fixed some loading savegame issues with
// dead actors.
// 
// 183   6/22/00 5:32p Steven
// Added StopDialog stuff and fixed gibs from processing server
// commands.
// 
// 182   6/21/00 4:21p Steven
// Improved checkcanflytoenemy.
// 
// 181   6/20/00 7:00p Steven
// Changed saved_anim_event and last_anim_event to strings from
// event pointers.
// 
// 180   6/20/00 12:16p Steven
// Added some SetMask stuff and made it so actors won't babble to
// players when they have weapons out.
// 
// 179   6/19/00 6:19p Steven
// Added die completely stuff, added can bleed after death stuff,
// added actors getting pissed at the player touching them, and
// now make actors make noise when they take pain or die.
// 
// 178   6/17/00 4:03p Steven
// Added GetStateAnims stuff.
// 
// 177   6/17/00 11:09a Steven
// Made it so actors spawned from other actors have their
// targetname set to the parents targetname + _spawned.
// 
// 176   6/15/00 6:55p Steven
// Added moving head while talking stuff.
// 
// 175   6/14/00 2:50p Markd
// removed unused variable
// 
// 174   6/13/00 3:46p Steven
// Added gibbing of actors when killed with a means of death of
// gib and fixed a problem with blind actors never thinking.
// 
// 173   6/10/00 1:48p Steven
// Added statemap caching.
// 
// 172   6/09/00 2:25p Steven
// Made melee weapons always do normal pain not small pain.
// 
// 171   6/08/00 1:43p Steven
// Added minimum melee height and immortal events.
// 
// 170   6/07/00 5:32p Steven
// Added ignore monster clip stuff.
// 
// 169   6/06/00 2:35p Steven
// Improved Likes a little bit, made it so the client doesn't
// process animation commands on a dead actor, fixed IsBlind,
// added check no path, and improved ChangeType.
// 
// 168   6/03/00 6:53p Steven
// Added actor blind stuff and added some farplane stuff to make
// sure actors wakeup and go back to sleep better.
// 
// 167   6/03/00 3:46p Aldie
// Added in g_debugtargets for debugging targetnames and targets
// 
// 166   6/01/00 3:18p Steven
// Added some changetype stuff, change some of the findenemy stuff
// a little, and added a check for in water.
// 
// 165   5/31/00 3:55p Steven
// Another actor save game pass.
// 
// 164   5/27/00 2:29p Steven
// Added attack actors stuff, added targetable stuff and added
// check player range.
// 
// 163   5/26/00 6:19p Steven
// Added a gotoprevstage proc, added set attackable by actors,
// added a final height variable to MeleeEvent, added
// ShouldAttackEntity and made CanWalkTo use MASK_PATHSOLID
// instead of MASK_SOLID.
// 
// 162   5/25/00 1:48p Steven
// Moved the rest of the max_gibs stuff to sentient.
// 
// 161   5/23/00 6:42p Steven
// Moved small gib stuff to sentient.
// 
// 160   5/23/00 10:18a Steven
// Made actors take a little time before doing babble dialog (half
// second or so) and added more items to actor random item spawns.
// 
// 159   5/20/00 4:46p Steven
// Added sendcommand stuff, made pushing not assert gravity on
// flying actors, and added small pain to possible other part
// flags check.
// 
// 158   5/19/00 3:42p Steven
// Added a noclip check.
// 
// 157   5/19/00 11:24a Steven
// Moved little gibs to client side and some small clean up.
// 
// 156   5/11/00 11:11a Steven
// Added pushing actors stuff, added chargewater attack, and did
// some cleanup.
// 
// 155   5/10/00 10:31a Steven
// Fixed actors running in mid air, merged new TryMove stuff in,
// got rid of a trace in TryMove, added a can walk on others
// variable, added com_blood stuff, optimized CheckGround and
// FindEnemy stuff and made CanWalkTo take into account the final
// height compared to the specified position.
// 
// 154   5/05/00 6:23p Steven
// Fixed a actorthread bug when the thread is not found and made
// it so fire will cause actors pain again.
// 
// 153   5/05/00 2:13p Steven
// Made it so for now actors don't do pain when on fire.
// 
// 152   5/04/00 2:07p Steven
// More finishing move stuff.
// 
// 151   5/04/00 12:46p Steven
// Finishing move stuff.
// 
// 150   5/03/00 11:49a Steven
// Made it so actors wouldn't do babble dialog if the player is
// moving.
// 
// 149   5/02/00 3:13p Steven
// Fixed a bug in SpawnBloodyGibs and added player watching actors
// that talk to her.
// 
// 148   5/01/00 2:45p Steven
// Added allow fall stuff, made it so we don't try to wake an
// already awake actor, made it so only a little bit of the pain
// stuff is processed for dead actors, and added volume and
// minimum distance to the playdialog stuff.
// 
// 147   4/28/00 5:37p Steven
// Stop detaching things on death, always fade (don't worry about
// inventory), added an optional number of gibs parameter to
// SpawnBloodyGibs, and added saving of the last known position of
// the enemy.
// 
// 146   4/25/00 10:10a Steven
// Made turntowardsenemy set the actor's roll to 0.
// 
// 145   4/24/00 2:43p Steven
// Fixed the initial state not getting initialized correctly.
// 
// 144   4/21/00 5:39p Steven
// Added some bounceoff stuff (mostly for fleshbinder's shield),
// added spawning of items on actor death stuff and optimized
// CanWalkTo a lot.
// 
// 143   4/20/00 11:33a Steven
// Added stun stuff, made it so if monsters are notsolid in the
// first place they contents won't be set to corpse on death, made
// sure suicide set the actor's health to 0, and made sure the
// fade out flag is set properly.
// 
// 142   4/15/00 11:49a Steven
// Added spawnbloodygibs, added setmaxgibs and cleaned up some
// blood stuff.
// 
// 141   4/14/00 3:58p Steven
// Added a staysolid event.
// 
// 140   4/14/00 11:15a Steven
// Made it so could do kickback and animation movement when dead.
// 
// 139   4/14/00 10:35a Steven
// Fixed some minor pain threshold stuff, made it so KilledEffects
// doesn't overwrite the actor's name and made blood splat size
// scale with the actor size.
// 
// 138   4/13/00 5:33p Steven
// Added a deathsink event, made it so only actors with deathsink
// turned on sink into ground after death and added a nomask event
// for the ghosts.
// 
// 137   4/12/00 6:59p Steven
// Added an addhealth event and made the actors pain event always
// process even if the damage done is 0.
// 
// 136   4/12/00 2:39p Steven
// Made it so named gibs don't spawn if the actor is fadig out.
// 
// 135   4/11/00 6:56p Steven
// Got gibs to sink into ground correctly.
// 
// 134   4/11/00 6:36p Steven
// Added deathshrink stuff.
// 
// 133   4/11/00 5:42p Steven
// Sinking into ground and fading out work.
// 
// 132   4/11/00 4:00p Steven
// Added attack_min_height to MeleeAttack.
// 
// 131   4/11/00 3:07p Steven
// Cleaned up a bunch of spawn stuff and merged SpawnGib and
// SpawnGibAtTag.
// 
// 130   4/11/00 10:31a Steven
// Cleaned up some gib stuff.
// 
// 129   4/10/00 6:52p Steven
// Redid death state to be able to have more levels and to process
// entry and exit commands, made sure the ACTOR_FLAG_SPAWN_FAILED
// flag is always set properly, made it so gibs don't process
// animation commands on the client and made it so gibs use their
// angles not their bind masters.
// 
// 128   4/10/00 10:51a Steven
// Fixed the throwing of shglieks by actors.
// 
// 127   4/08/00 3:51p Steven
// Added a SpawnGibAtTag (temporarily, will be merged with
// SpawnGib soon), added attackmode stuff again, don't spawn gibs
// if fading out, added gibing/hurting of dead monsters, lots of
// general gib work, fixed actors not being able to get off of
// other actors and  made ai_off kick the actor out of ai mode and
// NULL out the currentEnemy.
// 
// 126   4/06/00 3:34p Steven
// Fixed a typo.
// 
// 125   4/06/00 2:57p Steven
// Added death size event.
// 
// 124   4/05/00 6:17p Steven
// Added in real support for gravity based projectiles.
// 
// 123   4/04/00 6:54p Steven
// Added ResetHead event, started some projectile attack changes,
// added NoLerpThisFrame to the WarpTo event and added some tweaks
// to gibs.
// 
// 122   4/03/00 1:56p Steven
// Added a way to set & unset the fly flag and made lighter
// creatures gibs go further.
// 
// 121   4/01/00 4:33p Steven
// Added chackname.
// 
// 120   4/01/00 2:39p Steven
// Added checkcanflytoenemy.
// 
// 119   4/01/00 1:19p Steven
// Fixed up some gib stuff.
// 
// 118   4/01/00 11:10a Steven
// Added checkenemydead and initialized use_gravity flag.
// 
// 117   3/31/00 4:57p Steven
// Tweaked GetNearestEnemy a little and fixed actors not falling
// to the ground when killed.
// 
// 116   3/31/00 1:01p Steven
// Added GetRandomEnemy (for recruiter).
// 
// 115   3/30/00 2:02p Steven
// Added SpawnBlood, added usegravity, added save attack to
// FireBullet, some gib work, and fixed some movement issues.
// 
// 114   3/28/00 6:48p Steven
// Added optional tag_name to TestAttack.
// 
// 113   3/28/00 1:16p Steven
// Added range to bullet attack, fixed some noise heard stuff, and
// imprved checkhasthing so that you could check mulitple things
// at once.
// 
// 112   3/24/00 6:31p Steven
// Fixed another TryMove issue, fixed actors going to sleep that
// have the max_inactive_time set to 0, changes the size parameter
// in SpawnActor to width & height, and started adding a better
// CheckBottom.
// 
// 111   3/22/00 10:35a Steven
// Added SpawnNamedGib and GotoStage, fixed an event leak, and
// fixed some actor movement issues.
// 
// 110   3/20/00 6:07p Steven
// Moved max_mouth_angle stuff to sentient, made it so actor knows
// when behavior's animations are done, and added setmouthangle.
// 
// 109   3/18/00 4:15p Steven
// Added an allowhangback event, added a check for allowhangback,
// and fixed a TryMove issue.
// 
// 108   3/18/00 3:12p Steven
// Fixed some anim_done issues, added a flag to keep track if the
// actor has been started yet or not, and made sure the
// attackplayer command was only received after the actor is
// started.
// 
// 107   3/18/00 1:16p Steven
// Added FireBullet to actor and added pain_angles stuff.
// 
// 106   3/17/00 2:37p Steven
// Made it so dead actors don't care about falling off edges.
// 
// 105   3/17/00 11:49a Steven
// Added jumping stuff.
// 
// 104   3/14/00 12:06p Steven
// Added walkwatch stuff.
// 
// 103   3/13/00 4:42p Steven
// Added in the rest of the has_thing check.
// 
// 102   3/13/00 2:31p Steven
// Added a can_shoot_enemy check, fixed the starting position in
// CanShootFrom, added a warning to SetState if the state doesn't
// exist, and added a check to PlayDialog to make sure the actor
// has a currentState if setting a new one.
// 
// 101   3/11/00 4:11p Steven
// Added have thing stuff, added direction to pain, and made sure
// actors don't think before they are fully spawned.
// 
// 100   3/11/00 2:17p Steven
// Added stun stuff (so the AI knows when the player is incapable
// of doing anything :)
// 
// 99    3/11/00 12:04p Steven
// Added a check in SpawnActor to make sure the new actor isn't
// spawned inside of anything.
// 
// 98    3/11/00 11:33a Steven
// Moved all actor booleans to 1 actor flags variable.
// 
// 97    3/09/00 11:41a Steven
// Fixed a problem in checkcanseeenemy when having no
// currentEnemy.
// 
// 96    3/08/00 6:41p Steven
// Fixed up checkcanseeenemy and made sure all bones of an actor
// are reset back to their normal position when the actor dies.
// 
// 95    3/07/00 4:56p Steven
// Added bounce off stuff.
// 
// 94    3/07/00 11:49a Steven
// Added checkenemyinfov.
// 
// 93    3/04/00 11:49a Steven
// Added a stuck flag and added a check for it.
// 
// 92    3/03/00 5:24p Steven
// Added fast_bullet stuff and made it so actors that are
// activated will automatically attack the player.
// 
// 91    3/02/00 6:40p Steven
// Made which blood model to use a parameter to gib.
// 
// 90    3/02/00 11:01a Steven
// Cleaned up some gib stuff, fixed a velocity problem with
// actors, and added checkenemyrelativeyaw.
// 
// 89    2/29/00 12:21p Steven
// Fixed a problem with starting actorthreads (and going to AI
// mode in the middle of it) and took out actor droptofloor stuff
// temporarily.
// 
// 88    2/28/00 11:18a Steven
// Fixed up some drop to ground stuff.
// 
// 87    2/26/00 3:46p Steven
// Added some more stuff to stuck actor.
// 
// 86    2/26/00 3:32p Steven
// Print a message if actors start stuck in the ground and make it
// very obvious something is wrong :)
// 
// 85    2/26/00 2:56p Steven
// Fixed up some jump issues with actors.
// 
// 84    2/26/00 11:22a Steven
// Added partial immobile flag.
// 
// 83    2/25/00 7:02p Steven
// Added a way for actors to notify others of their kind when they
// are killed.
// 
// 82    2/24/00 5:55p Steven
// Fixed a typo in the event documentation.
// 
// 81    2/24/00 5:34p Steven
// Fixed up some event documentation.
// 
// 80    2/24/00 5:10p Steven
// Fixed up some of the removing anim done events, added a speed
// parm to headwatch and added offset to spawnactor.
// 
// 79    2/24/00 1:59p Steven
// Now make sure to get rid of all anim done events when ending a
// behavior and make sure actors won't go to talk mode while in a
// cinematic.
// 
// 78    2/23/00 5:50p Steven
// Made it so the endthread command also ends the current behavior
// if in script mode.
// 
// 77    2/23/00 5:09p Steven
// Fixed some bugs.
// 
// 76    2/23/00 11:43a Steven
// Moved utility behaviors into actor and added entry and exit
// commands.
// 
// 75    2/21/00 6:26p Steven
// Added an endthread event and made using the fov an option in
// the can see enemy check.
// 
// 74    2/18/00 6:54p Steven
// Added warpto command, did lots move improvements of movement
// and path finding, cleaned up some ai to idle mode stuff, and
// fixed idle thread stuff.
// 
// 73    2/17/00 6:26p Aldie
// Fixed naming conventions for weapon hand and also added various
// attachtotag functionality for weapons that attach to different
// tags depending on which hand they are wielded in.
// 
// 72    2/17/00 5:42p Steven
// Lots of movement and path finding improvements.
// 
// 71    2/16/00 6:44p Steven
// Fixed a bug in CanShootFrom (was negating the pitch still).
// 
// 70    2/16/00 10:41a Steven
// Added small pain stuff, made sure actors would not go to AI
// mode if they don't have a statemap, and made sure actors don't
// go to sleep when they shouldn't.
// 
// 69    2/14/00 3:32p Steven
// Added checks so an actor can tell what weapons the player is
// using and fixed a crash bug if an actor has no statemap but a
// state is set.
// 
// 68    2/11/00 6:40p Steven
// Added pickup/throw stuff, added damage once stuff, added small
// pain stuff, and fixed some bugs.
// 
// 67    2/09/00 10:34a Steven
// Added events to allow an actor's clipmask to be changed.
// 
// 66    2/08/00 4:53p Steven
// Made it so actors would only try to go to talk mode if they
// have babble dialog.
// 
// 65    2/08/00 11:59a Steven
// Added stuff to let actor know he had blocked a hit.
// 
// 64    2/08/00 11:38a Steven
// Some general cleanup, added a state name to idle event, added a
// state name to playdialog event, and added a checkheld check.
// 
// 63    2/04/00 3:11p Aldie
// Changed sword attack method for water usage
// 
// 62    2/04/00 1:56p Steven
// Added a lot on the different modes (AI, script, idle and talk).
// 
// 61    2/02/00 1:33p Steven
// Added headwatching stuff, tweaked meleeevent a little more,
// fixed up some init problems, made non-moving actors die
// properly, and fixed checkmovingactorrange stuff.
// 
// 60    1/28/00 12:04p Steven
// Added another debug message for dialog stuff.
// 
// 59    1/28/00 11:18a Steven
// Added a debug message if a dailog is played and no lip file is
// found.
// 
// 58    1/27/00 2:50p Steven
// Improved all actor's vision distance, fixed various bugs and
// added checkincomingmeleeattackstart and
// checkincomingprojectilestart.
// 
// 57    1/26/00 9:53a Markd
// Changed FOV command to an fov command
// 
// 56    1/25/00 6:32p Steven
// Added knockback to melee event.
// 
// 55    1/25/00 11:09a Steven
// Renamed health_less check to health.
// 
// 54    1/24/00 6:55p Steven
// Made sure actors will fall if spawned off the ground and added
// support to limit the number of actors an actor can spawn.
// 
// 53    1/22/00 5:07p Steven
// Added knockback to meleeattack.
// 
// 52    1/22/00 1:43p Markd
// Fixed attached entity bug
// 
// 51    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 50    1/21/00 8:07p Aldie
// Fixed a link error - bad!
// 
// 49    1/21/00 6:44p Steven
// Cleaned up idle_thread stuff, added tempstate ability, and
// added open door support for actors.
// 
// 48    1/20/00 6:57p Markd
// removed get_lip functions and merged them with SoundLength and
// SoundAmplitudes
// 
// 47    1/20/00 6:54p Aldie
// Removed bloodsplats until we do them the right way
// 
// 46    1/20/00 12:19p Steven
// Fixed a problem in the checkmeansofdeath conditional.
// 
// 45    1/19/00 8:56p Steven
// Improved location of spawned actors from the spawnactor
// command.
// 
// 44    1/19/00 7:46p Aldie
// Fixed func_spawns of various types and removed some unused misc
// classes
// 
// 43    1/19/00 6:33p Steven
// Added kill_thread stuff.
// 
// 42    1/19/00 12:08p Steven
// Added to dialog stuff so that a specific sound could be played,
// fixed anim_done never being set on the first animation and
// fixed death a little.
// 
// 41    1/17/00 10:20p Jimdose
// Rewrote state system initialization.  Made conditionals defined
// with array.
// Made Evaluate functions early exit
// 
// 40    1/14/00 5:06p Markd
// Removed surface num, tri_num and damage_multiplier from
// multiple functions and events
// 
// 39    1/14/00 5:01p Steven
// Added stage stuff.
// 
// 38    1/13/00 7:07p Steven
// Lots and lots of cleanup and fixed lip syncing.
// 
// 37    1/07/00 6:33p Steven
// Stopped using dummy.tik for gibs.
// 
// 36    1/06/00 6:49p Steven
// Removed need for dummy.tik and added a can jump to enemy ai
// check.
// 
// 35    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 34    1/05/00 6:43p Steven
// More work on spawngib and fixed some traces.
// 
// 33    1/05/00 3:07p Jimdose
// got rid of inverted pitch in MyGunAngles
// 
// 32    1/05/00 1:53p Steven
// Added a lot to the spawn gib stuff, fixed the turning speed
// issue, and fixed a death state problem.
// 
// 31    12/22/99 5:11p Steven
// Added incoming melee and incoming projectiles checks, fixed
// CanWalkTo a little and readded turn speed stuff.
// 
// 30    12/20/99 6:50p Steven
// Moved jumpxy to sentient and clened up some stuff.
// 
// 29    12/17/99 8:26p Jimdose
// got rid of unused vars and functions
// 
// 28    12/17/99 5:40p Steven
// Added actor jump event.
// 
// 27    12/07/99 6:09p Aldie
// Added weapon charging
// 
// 26    12/01/99 4:56p Markd
// fixed some reference versus pointer issues with RandomAnimate
// and NewAnim
// 
// 25    12/01/99 3:12p Steven
// Added an onground check and made it so dead flying actors
// always fall to the ground.
// 
// 24    11/19/99 4:54p Steven
// Added some deathfade stuff back in.
// 
// 23    11/19/99 4:29p Steven
// Minor fixes.
// 
// 22    11/19/99 11:30a Steven
// Fixed AnimSame, added commands so actors could tell each other
// to do things, and added a health less than check for ai.
// 
// 21    11/12/99 6:22p Steven
// Made state flags available to other part entities and added a
// attack_vector to melee attacks.
// 
// 20    11/10/99 6:10p Steven
// Added means of death to melee attack,  stopped prethinking on
// dead actors, and fixed a bug dealing with actors going back to
// sleep.
// 
// 19    11/05/99 5:24p Steven
// Added attack_width to melee attacks.
// 
// 18    10/28/99 6:34p Steven
// Fixed a bug where the actor would go to sleep when doing
// scripting.
// 
// 17    10/27/99 10:26a Steven
// Added only shootable contents stuff.
// 
// 16    10/21/99 5:26p Markd
// removed head_modelindex
// 
// 15    10/21/99 5:24p Steven
// General AI work.
// 
// 14    10/19/99 7:52p Markd
// Removed three part model system
// 
// 13    10/19/99 7:10p Steven
// Lots of AI work.
// 
// 12    10/11/99 7:50p Steven
// Major cleanup, made it so scripting and ai could co-exist, and
// fixed some actor bugs.
// 
// 11    10/07/99 5:34p Steven
// Some stimuli work and some event documentation.
// 
// 10    10/01/99 4:51p Markd
// Made Warning level 4 work on all projects
// 
// 9     10/01/99 1:39p Steven
// Event formatting.
// 
// 8     9/27/99 5:44p Markd
// began documentation and cleanup phase after merge
// 
// 6     9/22/99 4:47p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 5     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 4     9/20/99 5:23p Steven
// Added a canwalkto method and fixed a collision issue (ownerNum
// not being initialized).
// 
// 3     9/16/99 4:47p Jimdose
// removed unused melee code
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 61    9/02/99 3:24p Steven
// Added an ECTS hack for creatures liking each other.
// 
// 60    9/01/99 8:15p Steven
// Took out some old gas plant stuff.
// 
// 59    9/01/99 3:49p Jimdose
// made checkmovingactorrange use findclientsinradius and only
// check active actors instead of findradius to try to reduce the
// cpu hit.
// 
// 58    8/31/99 9:20p Steven
// Made actors melee attack range larger.
// 
// 57    8/31/99 2:42p Steven
// Fixed some actor threading issues and added death state
// machine.
// 
// 56    8/28/99 6:35p Steven
// More speed up.
// 
// 55    8/28/99 6:35p Steven
// Made some checks only check 4 times a second and got rid of
// some more actor thread stuff.
// 
// 54    8/28/99 11:42a Steven
// Cleanup and some spinning plant stuff.
// 
// 53    8/27/99 5:03p Steven
// More general AI work.
// 
// 52    8/24/99 11:24a Steven
// More general AI work.
// 
// 51    8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// 50    8/17/99 5:08p Markd
// Changed all FS_ReadFile's to FS_ReadFileEx's in game code
// 
// 49    8/17/99 4:58p Steven
// Some animation work for the AI.
// 
// 48    8/16/99 10:29a Steven
// More general work on AI.
// 
// 47    8/11/99 8:33p Steven
// Added ability to have a fov of 360 (for plants).
// 
// 46    8/11/99 8:00p Steven
// Fixed a bug when checking if anims should be changed from the
// state machine.
// 
// 45    8/11/99 7:23p Steven
// Added a behavior done check for the AI.
// 
// 44    8/11/99 5:56p Steven
// More general AI work.
// 
// 43    8/06/99 6:53p Jimdose
// changed format of state machine callback functions
// 
// 42    8/06/99 6:38p Aldie
// Started removing concept of currentWeapon
// 
// 41    8/05/99 9:13a Steven
// New AI stuff.
// 
// 40    7/08/99 4:28p Markd
// Removed obsolete QUAKED functions
// 
// 39    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
//
// DESCRIPTION:
// Base class for character AI.
//

#include "g_local.h"
#include "actor.h"
#include "behavior.h"
#include "scriptmaster.h"
#include "doors.h"
#include "gibs.h"
#include "misc.h"
#include "specialfx.h"
#include "object.h"
#include "scriptslave.h"
#include "explosion.h"
#include "misc.h"
#include "playerstart.h"
#include "characterstate.h"
#include "weaputils.h"
#include "shield.h"
#include "player.h"

//#define DEBUG_PRINT

Container<Actor *> SleepList;
Container<Actor *> ActiveList;

#define TURN_SPEED		20

Event EV_Actor_Sleep
   ( 
   "sleep",
   EV_DEFAULT,
   NULL,
   NULL,
   "Put the actor to sleep."
   );
Event EV_Actor_Wakeup
	( 
	"wakeup",
	EV_DEFAULT,
   NULL,
   NULL,
   "Wake up the actor."
	);
Event	EV_Actor_Fov
	( 
	"fov",
	EV_CONSOLE,
	"f",
	"fov",
	"Sets the actor's field of view (fov)."
	);
Event EV_Actor_VisionDistance
	( 
	"visiondistance",
	EV_DEFAULT,
	"f",
	"vision_distance",
	"Sets the distance the actor can see."
	);
Event EV_Actor_Start
	( 
	"start",
	EV_DEFAULT,
   NULL,
   NULL,
   "Initializes the actor a little, "
	"it is not meant to be called from script."
	);
Event	EV_Actor_Dead
	( 
	"dead",
	EV_DEFAULT,
   NULL,
   NULL,
   "Does everything necessary when an actor dies, "
	"it is not meant to be called from script."
	);
Event EV_Actor_Friend
	( 
	"friend",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor allied to the player."
	);
Event EV_Actor_Civilian
	( 
	"civilian",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor nuetral to all, runs from danger."
	);
Event EV_Actor_Enemy
	( 
	"enemy",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor an enemy to the player."
	);
Event EV_Actor_Monster
	( 
	"monster",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor an enemy to player, civilians, and inanimate objects."
	);
Event EV_Actor_Animal
	( 
	"animal",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor neutral to all."
	);
Event EV_Actor_Inanimate
	( 
	"inanimate",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor an inanimate object."
	);
Event EV_Actor_SetEnemyType
	( 
	"enemytype",
	EV_DEFAULT,
	"s",
	"enemytype",
	"Sets the name of this actor's enemy type."
	);
Event EV_Actor_Swim
	( 
	"swim",
	EV_DEFAULT,
	NULL,
	NULL,
	"Specifies actor as being able to swim."
	);
Event EV_Actor_Fly
	( 
	"fly",
	EV_DEFAULT,
	"B",
	"fly_bool",
	"Specifies actor as being able to fly (optional bool can turn fly on or off)."
	);
Event EV_Actor_NotLand
	( 
	"noland",
	EV_DEFAULT,
	NULL,
	NULL,
	"Specifies actor as not being able to walk on land."
	);
Event EV_Actor_Thread
	( 
	"thread",
	EV_DEFAULT,
	"s",
	"label",
	"Sets which thread to use for this actor."
	);
Event EV_Actor_RunThread
	( 
	"runthread",
	EV_DEFAULT,
	"s",
	"label",
	"Runs the specified thread."
	);
Event EV_Actor_EndThread
	( 
	"endthread",
	EV_DEFAULT,
	NULL,
	NULL,
	"Ends the actors thread."
	);
Event EV_Actor_Statemap
	( 
	"statemap",
	EV_DEFAULT,
	"sS",
	"statemap_name state_name",
	"Sets which statemap file to use and optionally what the first state to go to."
	);
Event EV_Actor_IfEnemyVisible
	( 
	"ifenemyvisible",
	EV_DEFAULT,
	"SSSSSS",
	"token1 token2 token3 token4 token5 token6",
	"Process the following command if enemy is visible"
	);
Event EV_Actor_IfNear
	( 
	"ifnear",
	EV_DEFAULT,
	"sfSSSSSS",
	"name distance token1 token2 token3 token4 token5 token6",
	"Process the following command if enemy is within specified distance"
	);
Event EV_Actor_ForwardSpeed
	( 
	"forwardspeed",
	EV_DEFAULT,
	"f",
	"forwardspeed",
	"Sets the actor's forward speed."
	);
Event EV_Actor_Idle
	( 
	"idle",
	EV_DEFAULT,
	"S",
	"state_name",
	"Tells the actor to go into idle mode."
	);
Event EV_Actor_LookAt
	( 
	"lookat",
	EV_DEFAULT,
	"e",
	"ent",
	"Specifies an entity to look at."
	);
Event EV_Actor_TurnTo
	( 
	"turnto",
	EV_DEFAULT,
	"f",
	"direction",
	"Specifies the direction to look in."
	);
Event EV_Actor_HeadWatch
	( 
	"headwatch",
	EV_DEFAULT,
	"eF",
	"entity_to_watch max_speed",
	"Actor watches the specified entity by turning his head."
	);
Event EV_Actor_ResetHead
	( 
	"resethead",
	EV_DEFAULT,
	"F",
	"max_speed",
	"Actor resets its head back to looking forwards."
	);
Event EV_Actor_FinishedBehavior
	( 
	"finishedbehavior",
	EV_DEFAULT,
	NULL,
	NULL,
	"Ends the current behavior, "
	"it is not meant to be called from script."
	);
Event EV_Actor_NotifyBehavior
	( 
	"notifybehavior",
	EV_DEFAULT,
	NULL,
	NULL,
	"Notifies the current behavior of an event,"
	"it is not meant to be called from script."
	);
Event EV_Actor_WalkTo
	( 
	"walkto",
	EV_DEFAULT,
	"sS",
	"pathnode anim_name",
	"Actor walks to specified path node"
	);
Event EV_Actor_WalkWatch
	( 
	"walkwatch",
	EV_DEFAULT,
	"seS",
	"pathnode entity anim_name",
	"Actor walks to specified path node and watches the specified entity"
	);
Event EV_Actor_WarpTo
	( 
	"warpto",
	EV_DEFAULT,
	"s",
	"node_name",
	"Warps the actor to the specified node"
	);
Event EV_Actor_JumpTo
	( 
	"jumpto",
	EV_DEFAULT,
	"SSSSSS",
	"token1 token2 token3 token4 token5 token6",
	"Actor jumps to specified path node"
	);
Event EV_Actor_RunTo
	( 
	"runto",
	EV_DEFAULT,
	"SSSSSS",
	"token1 token2 token3 token4 token5 token6",
	"Actor runs to specified path node"
	);
Event EV_Actor_PickupEnt
	( 
	"pickupent",
	EV_DEFAULT,
	"es",
	"entity_to_pickup pickup_anim_name",
	"Makes actor pick up the specified entity"
	);
Event EV_Actor_ThrowEnt
	( 
	"throwent",
	EV_DEFAULT,
	"s",
	"throw_anim_name",
	"Makes actor throw the entity in hands"
	);
Event EV_Actor_Anim
	( 
	"anim",
	EV_DEFAULT,
	"s",
	"anim_name",
	"Starts the PlayAnim behavior."
	);
Event EV_Actor_Attack
	( 
	"attack",
	EV_DEFAULT,
	"e",
	"ent",
	"Makes the actor attack the specified entity."
	);
Event EV_Actor_AttackPlayer
	( 
	"attackplayer",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes enemies of all the players."
	);
Event EV_Actor_ReserveNode
	( 
	"reservenode",
	EV_DEFAULT,
	"vf",
	"pos time",
	"Reserves a path node for the specified amount of time."
	);
Event EV_Actor_ReleaseNode
	( 
	"releasenode",
	EV_DEFAULT,
	"v",
	"pos",
	"Releases a path node from being reserved."
	);
Event EV_Actor_IfCanHideAt
	( 
	"ifcanhideat",
	EV_DEFAULT,
	"vSSSSSS",
	"pos token1 token2 token3 token4 token5 token6",
	"Processes command if actor can hide at specified position."
	);
Event EV_Actor_IfEnemyWithin
	( 
	"ifenemywithin",
	EV_DEFAULT,
	"fSSSSSS",
	"distance token1 token2 token3 token4 token5 token6",
	"Processes command if actor is within distance of its current enemy."
	);
Event EV_Actor_Remove
	( 
	"remove_useless",
	EV_DEFAULT,
	NULL,
	NULL,
	"Removes a useless dead body from the game."
	);
Event EV_Actor_Melee
	( 
	"melee",
	EV_DEFAULT,
	"FSSVFIF",
	"damage tag_name means_of_death attack_vector knockback use_pitch_to_enemy attack_min_height",
	"Makes the actor do a melee attack.\n"
	"  attack_vector = \"width length height\""
	);
Event EV_Actor_PainThreshold
	( 
	"painthreshold",
	EV_DEFAULT,
	"f",
	"pain_threshold",
	"Sets the actor's pain threshold."
	);
Event EV_Actor_SetKillThread
	( 
	"killthread",
	EV_DEFAULT,
	"s",
	"kill_thread",
	"Sets the actor's kill thread."
	);
Event EV_Actor_EyePositionOffset
	( 
	"eyeoffset",
	EV_DEFAULT,
	"v",
	"eyeoffset",
	"Sets the actor's eye position."
	);
Event EV_Actor_DeathFade
	( 
	"deathfade",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor fade when dead."
	);
Event EV_Actor_DeathShrink
	( 
	"deathshrink",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor shrink when dead."
	);
Event EV_Actor_DeathSink
	( 
	"deathsink",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor sink into the ground when dead."
	);
Event EV_Actor_StaySolid
	( 
	"staysolid",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor stay solid after death."
	);
Event EV_Actor_NoChatter
	( 
	"nochatter",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor not chatter."
	);
Event EV_Actor_TurnSpeed
	( 
	"turnspeed",
	EV_DEFAULT,
	"f",
	"turnspeed",
	"Sets the actor's turnspeed."
	);
Event EV_Actor_WatchOffset
	( 
	"watchoffset",
	EV_DEFAULT,
	"v",
	"offset",
	"Sets the actor's watch offset."
	);
Event	EV_Anim_Done
	( 
	"anim_done",
	EV_DEFAULT,
	NULL,
	NULL,
	"Called when the actor's animation is done, "
	"it is not meant to be called from script."
	);
Event EV_Actor_ProjAttack
	( 
	"proj",
	EV_DEFAULT,
	"ssIBF",
	"tag_name projectile_name number_of_tags arc_bool speed",
	"Fires a projectile from the actor towards the current enemy."
	);
Event EV_Actor_BulletAttack
	( 
	"bullet",
	EV_DEFAULT,
	"sB",
	"tag_name use_current_pitch",
	"Fires a bullet from the actor from the specified tag towards the current enemy."
	);
Event EV_Actor_Active
	( 
	"active",
	EV_DEFAULT,
	"i",
	"active_flag",
	"Specifies whether the actor's is active or not."
	);
Event EV_Actor_SpawnGib
	( 
	"spawngib",
	EV_DEFAULT,
	"vffssSSSSSSSS",
	"offset final_pitch width cap_name surface_name1 surface_name2 surface_name3 surface_name4 surface_name5 surface_name6 surface_name7 surface_name8 surface_name9" ,
	"Spawns a body part."
	);
Event EV_Actor_SpawnGibAtTag
	( 
	"spawngibattag",
	EV_DEFAULT,
	"sffssSSSSSSSS",
	"tag_name final_pitch width cap_name surface_name1 surface_name2 surface_name3 surface_name4 surface_name5 surface_name6 surface_name7 surface_name8 surface_name9" ,
	"Spawns a body part."
	);
Event EV_Actor_SpawnNamedGib
	( 
	"spawnnamedgib",
	EV_DEFAULT,
	"ssff",
	"gib_name tag_name final_pitch width",
	"Spawns a body named gib."
	);
Event EV_Actor_SpawnBlood
	( 
	"spawnblood",
	EV_DEFAULT,
	"ssB",
	"blood_name tag_name use_last_spawn_result" ,
	"Spawns blood at the specified tag."
	);
Event EV_Actor_AIOn
	( 
	"ai_on",
	EV_DEFAULT,
	NULL,
	NULL,
	"Turns the AI on for this actor."
	);
Event EV_Actor_AIOff
	( 
	"ai_off",
	EV_DEFAULT,
	NULL,
	NULL,
	"Turns the AI off for this actor."
	);
Event EV_Actor_AIDeaf
	( 
	"ai_deaf",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor ignore sounds."
	);
Event EV_Actor_AIDumb
	( 
	"ai_dumb",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor ignore sounds and sight."
	);
Event EV_Actor_Deaf
	( 
	"deaf",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor permanently deaf (will always ignore sounds)."
	);
Event EV_Actor_Blind
	( 
	"blind",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor permanently blind (will never try to see)."
	);
Event EV_Actor_SetIdleThread
	( 
	"setidlethread",
	EV_DEFAULT,
	"s",
	"thread",
	"Sets the thread that will be run if this actor gets back to the idle state again."
	);
Event EV_Actor_SetMaxInactiveTime
	( 
	"max_inactive_time",
	EV_DEFAULT,
	"f",
	"max_inactive_time",
	"Sets the maximum amount of time an actor will stay idle before going to sleep.\n"
	"Also sepecifies the maximum amount of time an actor will keep looking for an\n"
	"enemy that the actor can no longer see."
	);
Event EV_ActorRegisterParts
	( 
	"register_parts",
	EV_DEFAULT,
	"ei",
	"entity forward",
	"Registers the passed in part as another part of this actor and specifies\n"
	"whether or not to forward this message to the other parts."
	);
Event EV_ActorRegisterSelf
	( 
	"register_self",
	EV_DEFAULT,
	NULL,
	NULL,
	"Starts registration process for multi-entity actors"
	);
Event EV_ActorName
	( 
	"name",
	EV_DEFAULT,
	"s",
	"name",
	"Specifies the name of this actor type."
	);
Event EV_ActorPartName
	( 
	"part_name",
	EV_DEFAULT,
	"s",
	"part_name",
	"Specifies the name of this part (implying that this is a multi-part creature."
	);
Event EV_ActorSetupTriggerField
	( 
	"trigger_field",
	EV_DEFAULT,
	"vv",
	"min max",
	"Specifies to create a trigger field around the actor of the specified size."
	);
Event EV_ActorTriggerTouched
	( 
	"trigger_touched",
	EV_DEFAULT,
	"e",
	"ent",
	"Notifies the actor that its trigger field has been touched."
	);
Event EV_ActorOnlyShootable
	( 
	"only_shootable",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor solid only to projectiles."
	);
Event EV_ActorIncomingProjectile
	( 
	"incoming_proj",
	EV_DEFAULT,
	"e",
	"ent",
	"Notifies the actor of an incoming projectile."
	);
Event EV_ActorSpawnActor
	( 
	"spawnactor",
	EV_DEFAULT,
	"ssibffF",
	"model_name tag_name how_many attack width height spawn_offset",
	"Spawns the specified number of actors."
	);
Event EV_ActorSpawnActorAtLocation
	( 
	"spawnactoratlocation",
	EV_DEFAULT,
	"ssibff",
	"model_name pathnode_name how_many_path_nodes attack width height",
	"Spawns the specified actor at the specified pathnode."
	);
Event EV_Actor_AddDialog
	( 
	"dialog",
	EV_DEFAULT,
	"sSSSSSS",
	"alias token1 token2 token3 token4 token5 token6",
	"Add a dialog to this sentient."
	);
Event EV_Actor_DialogDone
	( 
	"dialogdone",
	EV_DEFAULT,
	NULL,
	NULL,
	"Called when the sentient's dialog is done, "
	"it is not meant to be called from script."
	);
Event EV_Actor_PlayDialog
	( 
	"playdialog",
	EV_DEFAULT,
	"SSE",
	"sound_file state_name user",
	"Plays a dialog."
	);
Event EV_Actor_StopDialog
	( 
	"stopdialog",
	EV_DEFAULT,
	NULL,
	NULL,
	"Stops the actor's dialog."
	);
Event EV_Actor_AllowTalk
	( 
	"allowtalk",
	EV_DEFAULT,
	"i",
	"allow_bool",
	"Sets whether or not the actor will bother to talk to the player."
	);
Event EV_Actor_AllowHangBack
	( 
	"allowhangback",
	EV_DEFAULT,
	"i",
	"allow_bool",
	"Sets whether or not the actor will bother to hang back."
	);
Event EV_Actor_SolidMask
	( 
	"solidmask",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor use a solid mask."
	);
Event EV_Actor_NotSolidMask
	( 
	"notsolidmask",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor use a nonsolid mask."
	);
Event EV_Actor_NoMask
	( 
	"nomask",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor use a mask of 0."
	);
Event EV_Actor_SetMask
	( 
	"setmask",
	EV_DEFAULT,
	"s",
	"mask_name",
	"Sets the actor's mask to the specified mask."
	);
Event EV_Actor_Pickup
	( 
	"actor_pickup",
	EV_DEFAULT,
	"s",
	"tag_name",
	"Makes the actor pickup current pickup_ent (should only be called from a tiki)."
	);
Event EV_Actor_Throw
	( 
	"actor_throw",
	EV_DEFAULT,
	"s",
	"tag_name",
	"Makes the actor throw whatever is in its hand (should only be called from a tiki)."
	);
Event EV_Actor_DamageOnceStart
	( 
	"damage_once_start",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor only do melee damage at most once during this attack."
	);
Event EV_Actor_DamageOnceStop
	( 
	"damage_once_stop",
	EV_DEFAULT,
	NULL,
	NULL,
	"Specifies that the actor is done with the damage once event."
	);
Event EV_Actor_GetNearestEnemy
	( 
	"getnearestenemy",
	EV_DEFAULT,
	NULL,
	NULL,
	"Sets currentEnemy to the nearest enemy."
	);
Event EV_Actor_GetRandomEnemy
	( 
	"getrandomenemy",
	EV_DEFAULT,
	"f",
	"range",
	"Sets currentEnemy to a random enemy in range."
	);
Event EV_Actor_DamageEnemy
	( 
	"damageenemy",
	EV_DEFAULT,
	"f",
	"damage",
	"Damages the current enemy by the specified amount."
	);
Event EV_Actor_TurnTowardsEnemy
	( 
	"turntowardsenemy",
	EV_DEFAULT,
	NULL,
	NULL,
	"Turns the actor towards the current enemy."
	);
Event EV_Actor_Suicide
	( 
	"suicide",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor commit suicide."
	);
Event EV_Actor_GotoNextStage
	( 
	"gotonextstage",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor goto his next stage."
	);
Event EV_Actor_GotoPrevStage
	( 
	"gotoprevstage",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor goto his previous stage."
	);
Event EV_Actor_GotoStage
	( 
	"gotostage",
	EV_DEFAULT,
	"i",
	"stage_number",
	"Makes the actor goto the specified stage."
	);
Event EV_Actor_NotifyOthersAtDeath
	( 
	"notifyothersatdeath",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor notify other actors of the same type when killed."
	);
Event EV_Actor_SetBounceOff
	( 
	"bounceoff",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes projectiles bounce off of actor (if they can't damage actor)."
	);
Event EV_Actor_SetHaveThing
	( 
	"havething",
	EV_DEFAULT,
	"ib",
	"thing_number have_bool",
	"Sets whether or not the actor has this thing number."
	);
Event EV_Actor_SetUseGravity
	( 
	"usegravity",
	EV_DEFAULT,
	"b",
	"use_gravity",
	"Tells the actor whether or not to use gravity for this animation."
	);
Event EV_Actor_SetDeathSize
	( 
	"deathsize",
	EV_DEFAULT,
	"vv",
	"min max",
	"Sets the actors new size for death."
	);
Event EV_Actor_Fade
	( 
	"actorfade",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor fade out."
	);
Event EV_Actor_AttackMode
	( 
	"attackmode",
	EV_DEFAULT,
	"b",
	"attack_bool",
	"Makes the actor go directly into attacking the player if bool is true."
	);
Event EV_Actor_AddHealth
	( 
	"addhealth",
	EV_DEFAULT,
	"ff",
	"health_to_add maxhealth",
	"Adds health to the actor."
	);
Event EV_Actor_BounceOff
	( 
	"bounceoffevent",
	EV_DEFAULT,
	"v",
	"object_origin",
	"Lets the actor know something just bounces off of it."
	);
Event EV_Actor_SetBounceOffEffect
	( 
	"bounceoffeffect",
	EV_DEFAULT,
	"s",
	"bounce_off_effect_name",
	"Sets the name of the effect to play when something bounces off the actor."
	);
Event EV_Actor_AddSpawnItem
	( 
	"spawnitem",
	EV_DEFAULT,
	"s",
	"spawn_item_name",
	"Adds this names item to what will be spawned when this actor is killed."
	);
Event EV_Actor_SetSpawnChance
	( 
	"spawnchance",
	EV_DEFAULT,
	"f",
	"spawn_chance",
	"Sets the chance that this actor will spawn something when killed."
	);
Event EV_Actor_ClearSpawnItems
	( 
	"clearspawnitems",
	EV_DEFAULT,
	NULL,
	NULL,
	"Clears the list of items to spawn when this actor is killed."
	);
Event EV_Actor_SetAllowFall
	( 
	"allowfall",
	EV_DEFAULT,
	"B",
	"allow_fall_bool",
	"Makes the actor ignore falls when trying to move."
	);
Event EV_Actor_SetCanBeFinishedBy
	( 
	"canbefinishedby",
	EV_DEFAULT,
   "sSSSSS",
   "mod1 mod2 mod3 mod4 mod5 mod6",
   "Adds to the can be finished by list for this actor."
	);
Event EV_Actor_SetFeetWidth
	( 
	"feetwidth",
	EV_DEFAULT,
   "f",
   "feet_width",
   "Sets the width of the feet for this actor if different than the bounding box size."
	);
Event EV_Actor_SetCanWalkOnOthers
	( 
	"canwalkonothers",
	EV_DEFAULT,
   NULL,
   NULL,
   "Allows the actor to walk on top of others."
	);
Event EV_Actor_Push
	( 
	"push",
	EV_DEFAULT,
   "v",
   "dir",
   "Pushes the actor in the specified direction."
	);
Event EV_Actor_Pushable
	( 
	"pushable",
	EV_DEFAULT,
   NULL,
   NULL,
   "Sets whether or not an actor can be pushed out of the way."
	);
Event EV_Actor_ChargeWater
	( 
	"chargewater",
	EV_DEFAULT,
   "ff",
   "damage range",
   "Does a charge water attack."
	);
Event EV_Actor_SendCommand
	( 
	"sendcommand",
	EV_DEFAULT,
   "ss",
   "command part_name",
   "Sends a command to another one of its parts."
	);
Event EV_Actor_SetAttackableByActors
	( 
	"attackablebyactors",
	EV_DEFAULT,
   "b",
   "attackable_by_actors",
   "Sets whether or not this actor is allowed to be attacked by other actors."
	);
Event EV_Actor_SetAttackActors
	( 
	"attackactors",
	EV_DEFAULT,
   NULL,
   NULL,
   "Sets this actor to attack other actors."
	);
Event EV_Actor_SetTargetable
	( 
	"targetable",
	EV_DEFAULT,
   "b",
   "should_target",
   "Sets whether or not this actor should be targetable by the player."
	);
Event EV_Actor_ChangeType
	( 
	"changetype",
	EV_DEFAULT,
   "s",
   "new_model_name",
   "Changes the actor to the specified new type of actor."
	);
Event EV_Actor_IgnoreMonsterClip
	( 
	"ignoremonsterclip",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor ignore monster clip brushes."
	);
Event EV_Actor_MinimumMeleeHeight
	( 
	"minmeleeheight",
	EV_DEFAULT,
	"f",
	"minimum_height",
	"Sets the minimum height a melee attack has to be to hurt the actor."
	);
Event EV_Actor_SetDamageAngles
	( 
	"damageangles",
	EV_DEFAULT,
	"f",
	"damage_angles",
	"Sets the the angles where the actor can be hurt (like fov)."
	);
Event EV_Actor_Immortal
	( 
	"immortal",
	EV_DEFAULT,
	"b",
	"immortal_bool",
	"Sets whether or not the actor is immortal or not."
	);
Event EV_Actor_HeadTwitch
	( 
	"headtwitch",
	EV_DEFAULT,
	"B",
	"end",
	"Makes the actors head twitch a little(used while talking)."
	);
Event EV_Actor_HeadTwitchEveryFrame
	( 
	"headtwitcheveryframe",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actors head twitch a little(used while talking)."
	);
Event EV_Actor_SetDieCompletely
	( 
	"diecompletely",
	EV_DEFAULT,
	"b",
	"die_bool",
	"Sets whether or not the actor dies completely (if he doesn't he mostly just"
	"  runs his kill_thread)."
	);
Event EV_Actor_SetBleedAfterDeath
	( 
	"bleed_after_death",
	EV_DEFAULT,
	"b",
	"bleed_bool",
	"Sets whether or not the actor will bleed after dying."
	);
Event EV_Actor_IgnorePlacementWarning
	( 
	"ignore_placement_warning",
	EV_DEFAULT,
	"s",
	"warning_string",
	"Makes the specified placement warning not get printed for this actor."
	);
Event EV_Actor_SetIdleStateName
	( 
	"set_idle_state_name",
	EV_DEFAULT,
	"s",
	"new_idle_state_name",
	"Sets the actor's new idle state name."
	);
Event EV_Actor_SetNotAllowedToKill
	( 
	"not_allowed_to_kill",
	EV_DEFAULT,
	NULL,
	NULL,
	"Player fails the level if he kills an actor with this set."
	);
Event EV_Actor_TouchTriggers
	( 
	"touchtriggers",
	EV_DEFAULT,
	"b",
	"touch_triggers_bool",
	"Sets whether or not this actor can touch triggers or not."
	);
Event EV_Actor_IgnoreWater
	( 
	"ignorewater",
	EV_DEFAULT,
	"b",
	"ignore_water_bool",
	"Sets whether or not this actor will ignore water when moving."
	);
Event EV_Actor_NeverIgnoreSounds
	( 
	"neverignoresounds",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor always listen to sounds even if it already has an enemy."
	);
Event EV_Actor_SimplePathfinding
	( 
	"simplepathfinding",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor use simplier path finding."
	);
Event EV_Actor_NoPainSounds
	( 
	"nopainsounds",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the actor not broadcast sounds (AI stimuli) when taking pain or killed."
	);
Event EV_Actor_IncrementNumSpawns
	( 
	"incrementnumspawns",
	EV_DEFAULT,
	NULL,
	NULL,
	"Increments the number of spawns this actor has."
	);
Event EV_Actor_DecrementNumSpawns
	( 
	"decrementnumspawns",
	EV_DEFAULT,
	NULL,
	NULL,
	"Decrements the number of spawns this actor has."
	);
Event EV_Actor_SetWaterLevel
	( 
	"waterlevel",
	EV_DEFAULT,
	"f",
	"waterlevel",
	"Sets the actor's water level."
	);
Event EV_Actor_UpdateBossHealth
	( 
	"updatebosshealth",
	EV_DEFAULT,
	"f",
	"waterlevel",
	"Tells the actor to update the bosshealth cvar each time it thinks."
	);
Event EV_Actor_SetMaxBossHealth
	( 
	"maxbosshealth",
	EV_DEFAULT,
	"f",
	"max_boss_health",
	"Sets the actor's max boss health."
	);
Event EV_Actor_IgnorePainFromActors
	( 
	"ignorepainfromactors",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes this actor ignore pain from other actors."
	);
Event EV_Actor_DamageAllowed
	( 
	"damageallowed",
	EV_DEFAULT,
	"b",
	"damage_allowed",
	"Turns melee damage on and off."
	);
Event EV_Actor_AlwaysGiveWater
	( 
	"alwaysgivewater",
	EV_DEFAULT,
	"b",
	"give_water",
	"Turns the always give water bool on off (gives water from soul sucker weapon)."
	);


CLASS_DECLARATION( Sentient, Actor, "monster_generic" )
	{
      { &EV_Activate,					   ActivateEvent },
		{ &EV_Use,							   UseEvent },
                                       
      { &EV_Actor_Sleep,				   Sleep },
      { &EV_Actor_Wakeup,				   Wakeup },
                                       
	   { &EV_Actor_Start,				   Start },
	   { &EV_Pain,							   Pain },
	   { &EV_Killed,						   Killed },
		{ &EV_Actor_Dead,					   Dead },
		{ &EV_Actor_Suicide,				   Suicide },
                                       
      { &EV_Actor_ForwardSpeed,        ForwardSpeedEvent },
                                       
      { &EV_Actor_Fov,                 SetFov },
      { &EV_Actor_VisionDistance,      SetVisionDistance },

		{ &EV_Actor_Friend,				   FriendEvent },
		{ &EV_Actor_Civilian,			   CivilianEvent },
		{ &EV_Actor_Enemy,				   EnemyEvent },
      { &EV_Actor_Monster,             MonsterEvent },
      { &EV_Actor_Animal,              AnimalEvent },
      { &EV_Actor_Inanimate,           InanimateEvent },
		{ &EV_Actor_SetEnemyType,        SetEnemyType },
	
      { &EV_Actor_Swim,                SwimEvent },
      { &EV_Actor_Fly,                 FlyEvent },
      { &EV_Actor_NotLand,             NotLandEvent },
                                       
		{ &EV_Actor_Thread,				   SetThread },
		{ &EV_Actor_RunThread,			   RunThread },
		{ &EV_Actor_EndThread,				EndThread },

		{ &EV_Actor_Statemap,			   LoadStateMap },

		{ &EV_Actor_IfEnemyVisible,	   IfEnemyVisibleEvent },
		{ &EV_Actor_IfNear,				   IfNearEvent },
		{ &EV_Actor_Idle,					   IdleEvent },
		{ &EV_Actor_LookAt,				   LookAt },
		{ &EV_Actor_TurnTo,				   TurnToEvent },
		{ &EV_Actor_HeadWatch,				HeadWatchEvent },
		{ &EV_Actor_ResetHead,				ResetHeadEvent },
		{ &EV_Actor_FinishedBehavior,	   FinishedBehavior },
		{ &EV_Actor_NotifyBehavior,	   NotifyBehavior },
		{ &EV_Actor_WalkTo,				   WalkTo },
		{ &EV_Actor_WalkWatch,			   WalkWatch },
		{ &EV_Actor_JumpTo,				   JumpToEvent },
		{ &EV_Actor_RunTo,				   RunTo },
		{ &EV_Actor_WarpTo,				   WarpTo },
		{ &EV_Actor_Anim,					   Anim },
		{ &EV_Actor_Attack,				   AttackEntity },
      { &EV_Actor_AttackPlayer,        AttackPlayer },
      { &EV_Actor_Remove,				   RemoveUselessBody },
                                       
		{ &EV_Actor_ReserveNode,		   ReserveNodeEvent },
		{ &EV_Actor_ReleaseNode,		   ReleaseNodeEvent },
		{ &EV_Actor_IfCanHideAt,		   IfCanHideAtEvent },
      { &EV_Actor_IfEnemyWithin,       IfEnemyWithinEvent },
                                       
		{ &EV_HeardSound,				      HeardSound },

		{ &EV_Actor_Melee,		         MeleeEvent },
                                       
      { &EV_Actor_PainThreshold,       SetPainThresholdEvent },
      { &EV_Actor_SetKillThread,       SetKillThreadEvent },
	   { &EV_SetHealth,			         SetHealth },
		{ &EV_Actor_AddHealth,	         AddHealth },
	   { &EV_Actor_EyePositionOffset,   EyeOffset },
	   { &EV_Actor_DeathFade,				DeathFadeEvent },
		{ &EV_Actor_DeathShrink,			DeathShrinkEvent },
		{ &EV_Actor_DeathSink,				DeathSinkEvent },
		{ &EV_Actor_StaySolid,				StaySolidEvent },
	   { &EV_Actor_NoChatter,           NoChatterEvent },
	   { &EV_Actor_TurnSpeed,           SetTurnSpeed },
		{ &EV_Actor_WatchOffset,         SetWatchOffset },
                                       
      { &EV_ScriptThread_Goto,         GotoEvent },

		{ &EV_Actor_SetMaxInactiveTime,	SetMaxInactiveTime },

		{ &EV_Anim_Done,					   AnimDone },

		{ &EV_Actor_ProjAttack,			   FireProjectile },
		{ &EV_Actor_BulletAttack,			FireBullet },

		{ &EV_Actor_Active,				   Active },

		{ &EV_Actor_SpawnGib,				SpawnGib },
		{ &EV_Actor_SpawnGibAtTag,			SpawnGibAtTag },
		{ &EV_Actor_SpawnNamedGib,			SpawnNamedGib },
		{ &EV_Actor_SpawnBlood,				SpawnBlood },

		{ &EV_Actor_AIOn,						TurnAIOn },
		{ &EV_Actor_AIOff,					TurnAIOff },

		{ &EV_Actor_AIDeaf,					Deaf },
		{ &EV_Actor_Deaf,						PermanentDeaf },
		{ &EV_Actor_Blind,					PermanentBlind },
		{ &EV_Actor_AIDumb,					Dumb },

		{ &EV_Actor_SetIdleThread,			SetIdleThread },

		{ &EV_ActorRegisterParts,			RegisterParts },
		{ &EV_ActorRegisterSelf,			RegisterSelf },
		{ &EV_ActorName,						Name },
		{ &EV_ActorPartName,					PartName },
		{ &EV_Actor_SendCommand,			SendCommand },

		{ &EV_ActorSetupTriggerField,		SetupTriggerField },
		{ &EV_ActorTriggerTouched,			TriggerTouched },
		{ &EV_ActorOnlyShootable,			OnlyShootable },

		{ &EV_ActorIncomingProjectile,	IncomingProjectile },

		{ &EV_ActorSpawnActor,				SpawnActorAtTag },
		{ &EV_ActorSpawnActorAtLocation,	SpawnActorAtLocation },

		{ &EV_Actor_AddDialog,           AddDialog },
		{ &EV_Actor_DialogDone,          DialogDone },
		{ &EV_Actor_PlayDialog,          PlayDialog },
		{ &EV_Actor_StopDialog,          StopDialog },
		{ &EV_Sentient_SetMouthAngle,		SetMouthAngle },

		{ &EV_Actor_AllowTalk,				AllowTalk },
		{ &EV_Actor_AllowHangBack,			AllowHangBack },

		{ &EV_Actor_SolidMask,				SolidMask },
		{ &EV_Actor_IgnoreMonsterClip,	IgnoreMonsterClip },
		{ &EV_Actor_NotSolidMask,			NotSolidMask },
		{ &EV_Actor_NoMask,					NoMask },
		{ &EV_Actor_SetMask,					SetMask },

		{ &EV_Actor_PickupEnt,				PickupEnt },
		{ &EV_Actor_ThrowEnt,				ThrowEnt },

		{ &EV_Actor_Pickup,					Pickup },
		{ &EV_Actor_Throw,					Throw },

		{ &EV_Actor_DamageOnceStart,		DamageOnceStart },
		{ &EV_Actor_DamageOnceStop,		DamageOnceStop },

		{ &EV_Actor_GetNearestEnemy,		GetNearestEnemy },
		{ &EV_Actor_GetRandomEnemy,		GetRandomEnemy },
		{ &EV_Actor_DamageEnemy,			DamageEnemy },
		{ &EV_Actor_TurnTowardsEnemy,		TurnTowardsEnemy },

		{ &EV_Actor_GotoNextStage,			GotoNextStage },
		{ &EV_Actor_GotoPrevStage,			GotoPrevStage },
		{ &EV_Actor_GotoStage,				GotoStage },

		{ &EV_Actor_NotifyOthersAtDeath,	NotifyOthersAtDeath },

		{ &EV_Actor_SetBounceOff,			SetBounceOff },
		{ &EV_Actor_BounceOff,				BounceOffEvent },
		{ &EV_Actor_SetBounceOffEffect,	SetBounceOffEffect },

		{ &EV_Actor_SetHaveThing,			SetHaveThing },

		{ &EV_Actor_SetUseGravity,			SetUseGravity },
		{ &EV_Actor_SetAllowFall,			SetAllowFall },

		{ &EV_Actor_SetDeathSize,			SetDeathSize },

		{ &EV_Actor_Fade,						FadeEvent },

		{ &EV_Actor_AttackMode,				AttackModeEvent },

		{ &EV_Stun,								StunEvent },

		{ &EV_Actor_AddSpawnItem,			AddSpawnItem },
		{ &EV_Actor_SetSpawnChance,		SetSpawnChance },
		{ &EV_Actor_ClearSpawnItems,		ClearSpawnItems },

		{ &EV_Actor_SetCanBeFinishedBy,	SetCanBeFinishedBy },

		{ &EV_Actor_SetFeetWidth,			SetFeetWidth },
		{ &EV_Actor_SetCanWalkOnOthers,	SetCanWalkOnOthers },

		{ &EV_Actor_Push,						Push },
		{ &EV_Actor_Pushable,				Pushable },

		{ &EV_Actor_ChargeWater,			ChargeWater },
		{ &EV_Actor_SetAttackableByActors,	SetAttackableByActors },
		{ &EV_Actor_SetAttackActors,		SetAttackActors },

		{ &EV_Actor_SetTargetable,			SetTargetable },

		{ &EV_Actor_ChangeType,				ChangeType },

		{ &EV_Actor_MinimumMeleeHeight,	MinimumMeleeHeight },
		{ &EV_Actor_SetDamageAngles,		SetDamageAngles },

		{ &EV_Actor_Immortal,				SetImmortal },

		{ &EV_Actor_HeadTwitch,				HeadTwitch },
		{ &EV_Actor_HeadTwitchEveryFrame, HeadTwitchEveryFrame },

		{ &EV_Actor_SetDieCompletely,		SetDieCompletely },
		{ &EV_Actor_SetBleedAfterDeath,	SetBleedAfterDeath },

		{ &EV_Actor_IgnorePlacementWarning,	IgnorePlacementWarning },

		{ &EV_Actor_SetIdleStateName,		SetIdleStateName },

		{ &EV_Actor_SetNotAllowedToKill,	SetNotAllowedToKill },

		{ &EV_Actor_TouchTriggers,			TouchTriggers },
		{ &EV_Actor_IgnoreWater,			IgnoreWater },
		{ &EV_Actor_NeverIgnoreSounds,	NeverIgnoreSounds },

		{ &EV_Actor_SimplePathfinding,	SimplePathfinding },

		{ &EV_Actor_NoPainSounds,			NoPainSounds },

		{ &EV_Actor_IncrementNumSpawns,	IncrementNumSpawns },
		{ &EV_Actor_DecrementNumSpawns,	DecrementNumSpawns },

		{ &EV_Actor_SetWaterLevel,			SetWaterLevel },

		{ &EV_Actor_UpdateBossHealth,		UpdateBossHealth },
		{ &EV_Actor_SetMaxBossHealth,		SetMaxBossHealth },

		{ &EV_Actor_IgnorePainFromActors,	IgnorePainFromActors },

		{ &EV_Actor_DamageAllowed,			DamageAllowed },

		{ &EV_Actor_AlwaysGiveWater,		AlwaysGiveWater },

		{ &EV_Touch,							Touched },

		{ NULL, NULL }
	};

//***********************************************************************************************
//
// Initialization functions
//
//***********************************************************************************************

Actor::Actor()
	{
	Event *immunity_event;


	// don't spawn monsters in deathmatch
   if ( deathmatch->integer || nomonsters->integer )
		{
		PostEvent( EV_Remove, EV_REMOVE );
		return;
		}

   // 
   // make sure this is a modelanim entity
   //
   edict->s.eType = ET_MODELANIM;

	actortype = IS_ENEMY;

	setSolidType( SOLID_BBOX );
	setMoveType( MOVETYPE_STEP );

   actorrange_time = 0;

	actor_flags1 = 0;
	actor_flags2 = 0;

   canseeenemy_time = 0;
	SetActorFlag( ACTOR_FLAG_LAST_CANSEEENEMY, false );
	SetActorFlag( ACTOR_FLAG_LAST_CANSEEENEMY_NOFOV, false );

	health				 = 100;
	max_health			 = health;
	takedamage			 = DAMAGE_AIM;
	mass					 = 200;
	deadflag				 = DEAD_NO;

	edict->clipmask	 = MASK_MONSTERSOLID;
	edict->svflags		|= SVF_MONSTER;
	edict->ownerNum    = ENTITYNUM_NONE;

   forwardspeed       = 0; //FIXME

	statemap = NULL;
	SetActorFlag( ACTOR_FLAG_INACTIVE, false );
	SetActorFlag( ACTOR_FLAG_ANIM_DONE, false );
	currentState = NULL;
	state_time = level.time;
	times_done = 0;
	SetActorFlag( ACTOR_FLAG_STATE_DONE_TIME_VALID, false );
	SetActorFlag( ACTOR_FLAG_AI_ON, true );
	stimuli = STIMULI_ALL;
	permanent_stimuli = STIMULI_ALL;
	last_enemy_sight_time = 0;
	next_enemy_try_sight_time = 0;
	next_try_sleep_time = 0;
	last_time_active = 0;
	next_player_near = 0;

	bullet_hits = 0;

	saved_anim_event_name = "";

	mode = ACTOR_MODE_IDLE;

	state_flags = 0;

	max_inactive_time = MAX_INACTIVE_TIME;

	num_of_spawns = 0;

	SetActorFlag( ACTOR_FLAG_NOISE_HEARD, false );

	noise_time = 0;
	SetActorFlag( ACTOR_FLAG_INVESTIGATING, false );

	dialog_list = NULL;
	SetActorFlag( ACTOR_FLAG_DIALOG_PLAYING, false );
	dialog_done_time = 0;

	stage = 1;

	SetActorFlag( ACTOR_FLAG_NOTIFY_OTHERS_AT_DEATH, false );
	SetActorFlag( ACTOR_FLAG_ALLOW_TALK, true );
	SetActorFlag( ACTOR_FLAG_ALLOW_HANGBACK, true );
	SetActorFlag( ACTOR_FLAG_DAMAGE_ONCE_ON, false );
	SetActorFlag( ACTOR_FLAG_BOUNCE_OFF, false );

	SetActorFlag( ACTOR_FLAG_HAS_THING1, false );
	SetActorFlag( ACTOR_FLAG_HAS_THING2, false );
	SetActorFlag( ACTOR_FLAG_HAS_THING3, false );
	SetActorFlag( ACTOR_FLAG_HAS_THING4, false );

	SetActorFlag( ACTOR_FLAG_LAST_ATTACK_HIT, true );

	SetActorFlag( ACTOR_FLAG_SPAWN_FAILED, false );

	SetActorFlag( ACTOR_FLAG_FADING_OUT, false );

	SetActorFlag( ACTOR_FLAG_USE_GRAVITY, true );
	SetActorFlag( ACTOR_FLAG_ALLOW_FALL, false );

	SetActorFlag( ACTOR_FLAG_STUNNED, false );

	SetActorFlag( ACTOR_FLAG_PUSHABLE, false );

   lastmove = STEPMOVE_OK;

	gunoffset = "0 0 44";

	behavior = NULL;
	path = NULL;

	newanimnum = -1;
	newanim = "";
	newanimevent = NULL;
	last_anim_event_name = "";

	vision_distance = 1536;

	fov = 150;
	fovdot = cos( fov * 0.5 * M_PI / 180.0 );

   eyeoffset = "0 0 0";
	eyeposition = "0 0 64";

	SetActorFlag( ACTOR_FLAG_DEATHFADE, false );
	SetActorFlag( ACTOR_FLAG_DEATHSHRINK, false );
	SetActorFlag( ACTOR_FLAG_DEATHSINK, false );
	SetActorFlag( ACTOR_FLAG_NOCHATTER, false );

	SetActorFlag( ACTOR_FLAG_STAYSOLID, false );

	SetActorFlag( ACTOR_FLAG_FINISHED, false );
	SetActorFlag( ACTOR_FLAG_IN_LIMBO, false );

	SetActorFlag( ACTOR_FLAG_CAN_WALK_ON_OTHERS, false );

	SetActorFlag( ACTOR_FLAG_LAST_TRY_TALK, false );

	SetActorFlag( ACTOR_FLAG_ATTACKABLE_BY_ACTORS, true );
	SetActorFlag( ACTOR_FLAG_ATTACK_ACTORS, false );

	SetActorFlag( ACTOR_FLAG_TARGETABLE, true );

	SetActorFlag( ACTOR_FLAG_IMMORTAL, false );

	SetActorFlag( ACTOR_FLAG_ALLOWED_TO_KILL, true );

	turnspeed = TURN_SPEED;

   if ( com_blood->integer )
      {
      flags |= FL_BLOOD;
      flags |= FL_DIE_GIBS;
      }

   // don't talk all at once initially

	chattime = G_Random( 20 );
	nextsoundtime = 0;

   //trig = NULL;
	SetActorFlag( ACTOR_FLAG_DEATHGIB, false );

   // default pain_threshold
   pain_threshold = 20;

   startpos = origin;

	next_drown_time = 0;
	air_finished = level.time + 5;
   last_jump_time = 0;

	groundentity = NULL;
	velocity = "0 0 -20";

   CheckWater();

   setSize( "-16 -16 0", "16 16 116" );
	showModel();

	SetActorFlag( ACTOR_FLAG_STARTED, false );

	spawn_chance = 0;

	feet_width = 0;

	next_find_enemy_time = 0;

	saved_mode = ACTOR_MODE_NONE;

	minimum_melee_height = -100;
	damage_angles = 0;

	real_head_pitch = 0;
	SetActorFlag( ACTOR_FLAG_TURNING_HEAD, false );

	SetActorFlag( ACTOR_FLAG_DIE_COMPLETELY, true );

	SetActorFlag( ACTOR_FLAG_BLEED_AFTER_DEATH, true );

	next_pain_sound_time = 0;

	SetActorFlag( ACTOR_FLAG_IGNORE_STUCK_WARNING, false );
	SetActorFlag( ACTOR_FLAG_IGNORE_OFF_GROUND_WARNING, false );

	SetActorFlag( ACTOR_FLAG_TOUCH_TRIGGERS, true );

	SetActorFlag( ACTOR_FLAG_IGNORE_WATER, false );

	SetActorFlag( ACTOR_FLAG_NEVER_IGNORE_SOUNDS, false );

	SetActorFlag( ACTOR_FLAG_SIMPLE_PATHFINDING, false );

	SetActorFlag( ACTOR_FLAG_NO_PAIN_SOUNDS, false );

	// All actors start immune to falling damage

	immunity_event = new Event( EV_Sentient_AddImmunity );
	immunity_event->AddString( "falling" );
	ProcessEvent( immunity_event );

	water_level = 0;

	SetActorFlag( ACTOR_FLAG_UPDATE_BOSS_HEALTH, false );
	max_boss_health = 0;

	SetActorFlag( ACTOR_FLAG_IGNORE_PAIN_FROM_ACTORS, false );

	SetActorFlag( ACTOR_FLAG_DAMAGE_ALLOWED, true );

	SetActorFlag( ACTOR_FLAG_ALWAYS_GIVE_WATER, false );

	if ( !LoadingSavegame )
		PostEvent( EV_Actor_Start, EV_POSTSPAWN );
	}

Actor::~Actor()
	{
	if ( actorthread )
		{
		actorthread->ProcessEvent( EV_ScriptThread_End );
		actorthread = NULL;
		}

   if ( SleepList.ObjectInList( ( Actor * )this ) )
      {
      SleepList.RemoveObject( ( Actor * )this );
      }

   if ( ActiveList.ObjectInList( ( Actor * )this ) )
      {
      ActiveList.RemoveObject( ( Actor * )this );
      }

	if ( behavior )
		{
		delete behavior;
		behavior = NULL;
		}

	if ( path )
		{
		delete path;
		path = NULL;
		}

   /* if ( trig )
      {
      delete trig;
      trig = NULL;
      } */

	FreeDialogList();
	}

void Actor::Sleep
   (
   void
   )

   {
   // inanimate actors don't target enemies
   if ( actortype == IS_INANIMATE )
      {
      return;
      }

   if ( !SleepList.ObjectInList( ( Actor * )this ) )
      SleepList.AddObject( ( Actor * )this );

	if ( ActiveList.ObjectInList( ( Actor * )this ) )
      ActiveList.RemoveObject( ( Actor * )this );

   currentEnemy = NULL;
   flags &= ~FL_THINK;
	last_enemy_sight_time = 0;
   }

void Actor::Sleep
   (
   Event *ev
   )

   {
   Sleep();
   }

void Actor::Wakeup
   (
   void
   )

   {
	// See if already awake

	if ( flags & FL_THINK && !LoadingSavegame )
		return;

   // inanimate actors don't target enemies
   if ( actortype == IS_INANIMATE )
      {
      return;
      }

   if ( SleepList.ObjectInList( ( Actor * )this ) )
      SleepList.RemoveObject( ( Actor * )this );

	if ( !ActiveList.ObjectInList( ( Actor * )this ) )
      ActiveList.AddObject( ( Actor * )this );

   flags |= FL_THINK;
   }

void Actor::Wakeup
   (
   Event *ev
   )

   {
   Wakeup();
   }

void Actor::Start
	(
	Event *ev
	)

	{
	trace_t	trace;
	Vector	end;
   Vector   start;
	qboolean stuck;
	str monster_name;

	// Register with other parts of self if there are any

	if ( target.length() > 0 )
		PostEvent( EV_ActorRegisterSelf, FRAMETIME );

	// add them to the active list (they will be removed by sleep).
   ActiveList.AddObject( ( Actor * )this );

	// Drop actor to the ground

	stuck = false;

   start = origin + Vector( "0 0 1" );
   end = origin;
	end[ 2 ] -= 16;

	trace = G_Trace( start, mins, maxs, end, this, MASK_SOLID, false, "Actor::start" );

	if ( trace.startsolid || trace.allsolid )
		{
		stuck = true;
		}
	else if ( !( flags & FL_FLY ) )
		{
		setOrigin( trace.endpos );
		groundentity = trace.ent;
		}

	if ( name.length() )
		monster_name = name;
	else
		monster_name = getClassID();

	if ( trace.fraction == 1 && movetype == MOVETYPE_STATIONARY && !GetActorFlag( ACTOR_FLAG_IGNORE_OFF_GROUND_WARNING ) )
		{
		gi.DPrintf( "%s (%d) off of ground at '%5.1f %5.1f %5.1f'\n", monster_name.c_str(), entnum, origin.x, origin.y, origin.z );
		}

	if ( stuck && !GetActorFlag( ACTOR_FLAG_IGNORE_STUCK_WARNING ) )
		{
		groundentity = world->edict;

		gi.DPrintf( "%s (%d) stuck in world at '%5.1f %5.1f %5.1f'\n", monster_name.c_str(), entnum, origin.x, origin.y, origin.z );
		}

	last_origin = origin;

	SetActorFlag( ACTOR_FLAG_HAVE_MOVED, false );

	last_ground_z = origin.z;

	if ( !behavior || currentBehavior == "Idle" )
		Sleep();

	SetActorFlag( ACTOR_FLAG_STARTED, true );
	}

//***********************************************************************************************
//
// Vision functions
//
//***********************************************************************************************

qboolean Actor::WithinVisionDistance
	( 
	Entity *ent
	)
	{
	float distance;

	// Use whichever is less : the actor's vision distance or the distance of the farplane (fog)

	if ( (world->farplane_distance != 0) && (world->farplane_distance < vision_distance) )
		distance = world->farplane_distance;
	else
		distance = vision_distance;

	return WithinDistance( ent, distance );
	}

inline qboolean Actor::InFOV
	(
	Vector pos,
	float check_fov,
	float check_fovdot
	)
	{
	Vector delta;
	float	 dot;

	if ( check_fov == 360 )
		return true;

	delta = pos - EyePosition();

   if ( !delta.x && !delta.y )
      {
      // special case for straight up and down
      return true;
      }

	// give better vertical vision
	delta.z = 0;

	delta.normalize();
	dot = DotProduct( orientation[ 0 ], delta );

	return ( dot > check_fovdot );
	}

inline qboolean Actor::InFOV
	(
	Vector pos
	)

	{
	return InFOV( pos, fov, fovdot );
	}

inline qboolean Actor::InFOV
	(
	Entity *ent
	)

	{
	return InFOV( ent->centroid );
	}

inline qboolean Actor::CanSeeFOV
	(
	Entity *ent
	)

	{
   return InFOV( ent ) && CanSeeFrom( origin, ent );
	}

inline qboolean Actor::CanSeeFrom
  	(
	Vector pos,
	Entity *ent
	)

	{
	trace_t trace;
	Vector p;

	p = ent->centroid;

	// Check if he's visible
	trace = G_Trace( pos + eyeposition, vec_zero, vec_zero, p, this, MASK_OPAQUE, false, "Actor::CanSeeFrom 1" );
	if ( trace.fraction == 1.0 || trace.ent == ent->edict )
		{
		return true;
		}

	// Check if his head is visible
	p.z = ent->absmax.z;
	trace = G_Trace( pos + eyeposition, vec_zero, vec_zero, p, this, MASK_OPAQUE, false, "Actor::CanSeeFrom 2" );
	if ( trace.fraction == 1.0 || trace.ent == ent->edict )
		{
		return true;
		}

	return false;
	}

qboolean Actor::CanSee
	(
	Entity *ent
	)

	{
   return CanSeeFrom( origin, ent );
	}

qboolean Actor::EnemyCanSeeMeFrom
	(
	Vector pos
	)

	{
	Vector	d;
	Vector	p1;
	Vector	p2;


	if ( !IsEntityAlive( currentEnemy ) )
		{
      return false;
		}

	if ( WithinVisionDistance( currentEnemy ) )
		{
		// To check if we're visible, I create a plane that intersects the actor
		// and is perpendicular to the delta vector between the actor and his enemy.
		// I place four points on this plane that "frame" the actor and check if
		// the enemy can see any of those points.
		d = currentEnemy->centroid - pos;
		d.z = 0;
		d.normalize();
		p1.x = -d.y;
		p1.y = d.x;
		p1 *= max( size.x, size.y ) * 1.44 * 0.5;
		p2 = p1;

		p1.z = mins.z;
		p2.z = maxs.z;
		if ( CanSeeFrom( pos + p1, currentEnemy ) )
			{
			return true;
			}
		if ( CanSeeFrom( pos + p2, currentEnemy ) )
			{
			return true;
			}

		p1.z = -p1.z;
		p2.z = -p2.z;
		if ( CanSeeFrom( pos - p1, currentEnemy ) )
			{
			return true;
			}
		if ( CanSeeFrom( pos - p2, currentEnemy ) )
			{
			return true;
			}
		}

   return false;
	}

qboolean Actor::CanSeeEnemyFrom
	(
	Vector pos
	)

	{
	if ( !IsEntityAlive( currentEnemy ) )
		{
		return false;
		}

	if ( WithinVisionDistance( currentEnemy ) && CanSeeFrom( pos, currentEnemy ) )
		{
		return true;
		}

	return false;
	}

qboolean Actor::CanReallySee
	(
	Entity *ent
	)

	{
	if ( !IsEntityAlive( ent ) )
		return false;

	if ( WithinVisionDistance( ent ) && CanSeeFOV( ent ) )
		return true;

	return false;
	}

//***********************************************************************************************
//
// Combat functions
//
//***********************************************************************************************

void Actor::IncomingProjectile
	(
	Event *ev
	)
	{
	incoming_proj = ev->GetEntity( 1 );
	incoming_time = level.time + .1; //+ G_Random( .1 );
	}

void Actor::FireProjectile
	(
	Event *ev
	)

	{
	Vector orig;
	Vector dir;
	str tag_name;
	str projectile_name;
	int number_of_tags = 1;
	qboolean arc = false;
	float speed = 0;

	if ( !currentEnemy )
		return;

	tag_name        = ev->GetString( 1 );
	projectile_name = ev->GetString( 2 );

	if ( ev->NumArgs() > 2 )
		number_of_tags = ev->GetInteger( 3 );

	if ( ev->NumArgs() > 3 )
		arc = ev->GetBoolean( 4 );

	if ( ev->NumArgs() > 4 )
		speed = ev->GetFloat( 5 );

	// Find the closest tag

	if ( !GetClosestTag( tag_name, number_of_tags, currentEnemy->centroid, &orig ) )
		{
		// Could not find the tag so just use the centroid of the actor
		orig[0] = edict->centroid[0];
		orig[1] = edict->centroid[1];
		orig[2] = edict->centroid[2];
		}

	// Add projectile to world

	dir = currentEnemy->centroid - orig;

	if ( arc )
		{
		Vector xydir;
		float traveltime;
		float vertical_speed;
		Vector proj_velocity;

		xydir = dir;
		xydir.z = 0;

		if ( speed == 0 )
			speed = 500;

		traveltime = xydir.length() / speed;
   
      vertical_speed = ( dir.z  / traveltime ) + ( 0.5f * gravity * sv_gravity->value * traveltime );

		xydir.normalize();

		proj_velocity = speed * xydir;
		proj_velocity.z = vertical_speed;

		speed = proj_velocity.length();
		proj_velocity.normalize();
		dir = proj_velocity;
		}

	dir.normalize();

	ProjectileAttack( orig, dir, this, projectile_name.c_str(), 1.0f, speed );

	SaveAttack( orig, dir );
	}

void Actor::FireBullet
	(
	Event *ev
	)

	{
	str tag_name;
	qboolean use_current_pitch;
	float range = 1000;
	float damage;
	float knockback;
	str means_of_death_string;
	int means_of_death;
	Vector spread;
	Vector pos;
	Vector forward;
	Vector left;
	Vector right;
	Vector up;
	Vector attack_angles;
	Vector dir;
	Vector enemy_angles;

	tag_name						= ev->GetString( 1 );
	use_current_pitch			= ev->GetBoolean( 2 );
	damage						= ev->GetFloat( 3 );
	knockback					= ev->GetFloat( 4 );
	means_of_death_string	= ev->GetString( 5 );
	spread						= ev->GetVector( 6 );

	if ( ev->NumArgs() > 6 )
		range = ev->GetFloat( 7 );

	// Get the position where the bullet starts

	GetTag( tag_name, &pos, &forward, &left, &up );

	right = left * -1;

	// Get the real pitch of the bullet attack

	if ( !use_current_pitch && currentEnemy )
		{
		attack_angles = forward.toAngles();

		dir = currentEnemy->centroid - pos;
		enemy_angles = dir.toAngles();

		attack_angles[PITCH] = enemy_angles[PITCH];

		attack_angles.AngleVectors( &forward, &left, &up );

		right = left * -1;
		}

	means_of_death = MOD_string_to_int( means_of_death_string );

	BulletAttack( pos, forward, right, up, range, damage, knockback, 0, means_of_death, spread, 1, this );

	SaveAttack( pos, forward );
	}

void Actor::SaveAttack
	( 
	Vector orig, 
	Vector dir
	)
	{
	Vector attack_mins;
	Vector attack_maxs;
	Vector end;
	trace_t trace;
	qboolean hit;
	Entity *ent;

	if ( !currentEnemy )
		{
		SetActorFlag( ACTOR_FLAG_LAST_ATTACK_HIT, true );
		return;
		}

	// Do trace

	attack_mins = Vector( -1,-1,-1 );
   attack_maxs = Vector( 1,1,1 );

	end = orig + dir * 8192;

	trace = G_Trace( orig, attack_mins, attack_maxs, end, this, MASK_SHOT, false, "Actor::SaveAttack" );

	// See what we hit

	last_attack_entity_hit = NULL;

	if ( trace.ent )
		{
		ent = trace.ent->entity;

		if ( ent == currentEnemy )
			{
			hit = true;
			}
		else if ( ent->isSubclassOf( Entity ) && ent != world )
			{
			last_attack_entity_hit = ent;
			last_attack_entity_hit_pos = ent->origin;
			hit = false;
			}
		else
			{
			hit = false;
			}
		}
	else
		{
		hit = false;
		}

	// Do an extra check because of NOCLIP

	if ( currentEnemy->movetype == MOVETYPE_NOCLIP )
		hit = true;

	// Save last attack info

	last_attack_pos = origin;

	if ( currentEnemy )
		last_attack_enemy_pos = currentEnemy->origin;

	SetActorFlag( ACTOR_FLAG_LAST_ATTACK_HIT, hit );
	}

qboolean Actor::TestAttack( str tag_name )
	{
	qboolean hit;
	trace_t trace;
	Vector attack_mins;
	Vector attack_maxs;
	Vector start;


	// Make sure we still have an enemy and he is hitable

	if ( !currentEnemy )
		return false;

	if ( currentEnemy->movetype == MOVETYPE_NOCLIP )
		return false;

	// Make sure we won't hit any friends

	attack_mins = Vector( -1,-1,-1 );
   attack_maxs = Vector( 1,1,1 );

	if ( tag_name.length() )
		{
		GetTag( tag_name.c_str(), &start );
		}
	else
		{
		start = centroid;
		}

	trace = G_Trace( start, attack_mins, attack_maxs, currentEnemy->centroid, this, MASK_SHOT, false, "Actor::TestAttack" );

	if ( trace.ent && trace.ent->entity != currentEnemy && trace.ent->entity->isSubclassOf( Sentient ) && !IsEnemy( trace.ent->entity ) )
		return false;

	// See if we hit last time

	hit = GetActorFlag( ACTOR_FLAG_LAST_ATTACK_HIT );

	if ( hit )
		return true;

	// Didn't hit last time so see if anything has changed

	// See if actor has moved

	if ( last_attack_pos != origin )
		return true;

	// See if enemy has moved

	if ( last_attack_enemy_pos != currentEnemy->origin )
		return true;

	// See if entity in the way has moved

	if ( last_attack_entity_hit && last_attack_entity_hit_pos != last_attack_entity_hit->origin )
		return true;

	// See if entity in the way was a door and has opened

	if ( last_attack_entity_hit && last_attack_entity_hit->isSubclassOf( Entity ) )
		{
		Door *door;

		door = (Door *)(Entity *)last_attack_entity_hit;

		if ( door->isOpen() )
			return true;
		}

	// See if entity in the way has become non-solid

	if ( last_attack_entity_hit && last_attack_entity_hit->edict->solid == SOLID_NOT )
		return true;

	// Nothing has changed so this attack should fail too

	return false;
	}

void Actor::MeleeEvent
   (
   Event *ev
   )

   {
	Vector pos;
	Vector end;
	Vector   dir;
	float damage = 20;
	qboolean success;
	str tag_name;
	Vector attack_vector;
	float attack_width  = 0;
	float attack_max_height = 0;
	float attack_min_height = 0;
	float attack_length = 100;
	str means_of_death_string;
	meansOfDeath_t means_of_death;
	float knockback;
	qboolean use_pitch_to_enemy = false;
	float attack_final_height;


	// See if we should really attack

	if ( GetActorFlag( ACTOR_FLAG_DAMAGE_ONCE_ON ) && GetActorFlag( ACTOR_FLAG_DAMAGE_ONCE_DAMAGED ) )
		return;

	if ( !GetActorFlag( ACTOR_FLAG_DAMAGE_ALLOWED ) )
		return;

	// Get all of the parameters

	if ( ev->NumArgs() > 0 )
		damage = ev->GetFloat( 1 );

	if ( ev->NumArgs() > 1 )
		tag_name = ev->GetString( 2 );

	if ( ev->NumArgs() > 2 )
		means_of_death_string = ev->GetString( 3 );

	if ( ev->NumArgs() > 3 )
		{
		attack_vector = ev->GetVector( 4 );

		attack_width      = attack_vector[0];
		attack_length     = attack_vector[1];
		attack_max_height = attack_vector[2];
		}

	if ( ev->NumArgs() > 4 )
		{
		knockback = ev->GetFloat( 5 );
		}
	else
		{
		knockback = damage * 8;
		}

	if ( ev->NumArgs() > 5 )
		{
		use_pitch_to_enemy = ev->GetInteger( 6 );
		}

	if ( ev->NumArgs() > 6 )
		attack_min_height = ev->GetFloat( 7 );
	else
		attack_min_height = -attack_max_height;

	if ( ev->NumArgs() > 7 )
		attack_final_height = ev->GetFloat( 8 );
	else
		attack_final_height = 50;

	if ( tag_name.length() && GetTag( tag_name.c_str(), &pos, &dir ) )
		{
		end = pos + dir * attack_length;
		}
	else
		{
		pos = edict->centroid;
		dir = orientation[0];
		dir.normalize();
		end = pos + dir * attack_length;

		if ( attack_length )
			end[2] += attack_final_height;
		}

	if ( use_pitch_to_enemy )
		{
		if ( currentEnemy )
			{
			Vector enemy_dir;
			Vector angles;
			Vector enemy_angles;
			float length;

			dir    = end - pos;
			length = dir.length();
			angles = dir.toAngles();

			enemy_dir    = currentEnemy->centroid - pos;
			enemy_angles = enemy_dir.toAngles();

			angles[PITCH] = enemy_angles[PITCH];
			angles.AngleVectors( &dir );
			end = pos + dir * length;
			}
		}

	if ( means_of_death_string.length() > 0 )
		means_of_death = (meansOfDeath_t)MOD_string_to_int( means_of_death_string );
	else
		means_of_death = MOD_CRUSH;

	// Do the actual attack

	success = MeleeAttack( pos, end, damage, this, means_of_death, attack_width, attack_min_height, attack_max_height, knockback );

	if ( success )
		{
		AddStateFlag( STATE_FLAG_MELEE_HIT );

		if ( GetActorFlag( ACTOR_FLAG_DAMAGE_ONCE_ON ) )
			SetActorFlag( ACTOR_FLAG_DAMAGE_ONCE_DAMAGED, true );
		}
	}

void Actor::ChargeWater
	(
	Event *ev
	)

	{
	int cont;
	float damage;
	float radius;
	Entity *ent;
	int brushnum;
	int entity_brushnum;
	float real_damage;
	Vector dir;
	float dist;

	// See if we are standing in water

	cont = gi.pointcontents( origin, 0 );

	if ( !(cont & MASK_WATER) )
		return;

	// Get parms

	damage = ev->GetFloat( 1 );
	radius = ev->GetFloat( 2 );

	if ( !damage || !radius )
		return;

	// Determine what brush we are in

	brushnum = gi.pointbrushnum( origin, 0 );

	// Find everything in radius

	ent = NULL;

	for( ent = findradius( ent, origin, radius ) ; ent ; ent = findradius( ent, origin, radius ) )
		{
		if ( ent->takedamage )
			{
			entity_brushnum = gi.pointbrushnum( origin, 0 );

			if ( brushnum == entity_brushnum )
				{
				dir = ent->origin - origin;
				dist = dir.length();

				if ( dist < radius )
					{
					real_damage = damage - damage * ( dist / radius );
					ent->Damage( this, this, real_damage, origin, dir, vec_zero, 0, 0, MOD_ELECTRICWATER );
					}
				}
			}
		}
	}

void Actor::DamageOnceStart
   (
   Event *ev
   )

   {
	SetActorFlag( ACTOR_FLAG_DAMAGE_ONCE_ON, true );
	SetActorFlag( ACTOR_FLAG_DAMAGE_ONCE_DAMAGED, false );
	}

void Actor::DamageOnceStop
   (
   Event *ev
   )

   {
	SetActorFlag( ACTOR_FLAG_DAMAGE_ONCE_ON, false );
	}

void Actor::DamageAllowed
   (
   Event *ev
   )

   {
	SetActorFlag( ACTOR_FLAG_DAMAGE_ALLOWED, ev->GetBoolean( 1 ) );
	}

qboolean Actor::CanShootFrom
	(
	Vector pos,
	Entity *ent,
	qboolean usecurrentangles
	)

	{
   int      mask;
	Vector	delta;
	Vector	start;
	Vector	end;
	float		len;
	trace_t	trace;
	Entity	*t;
   Vector   ang;

	if ( usecurrentangles )
		{
   	Vector	dir;

		// Fixme ?
      //start = pos + GunPosition() - origin;
		start = pos + centroid - origin;
		end = ent->centroid;
		end.z += ( ent->absmax.z - ent->centroid.z ) * 0.75f;
		delta = end - start;
      ang = delta.toAngles();
      ang.x = ang.x;
      ang.y = angles.y;
		len = delta.length();
   	ang.AngleVectors( &dir, NULL, NULL );
      dir *= len;
      end = start + dir;
		}
	else
		{
		// Fixme ?
      //start = pos + GunPosition() - origin;
		start = pos + centroid - origin;
		end = ent->centroid;
		end.z += ( ent->absmax.z - ent->centroid.z ) * 0.75f;
      delta = end - start;
      len = delta.length();
		}

	// shoot past the guy we're shooting at
	end += delta * 4;

	// Check if he's visible
   mask = MASK_SHOT;
	trace = G_Trace( start, vec_zero, vec_zero, end, this, mask, false, "Actor::CanShootFrom" );
	if ( trace.startsolid )
		{
		return false;
		}

   // see if we hit anything at all
   if ( !trace.ent )
      {
      return false;
      }

	// If we hit the guy we wanted, then shoot
	if ( trace.ent == ent->edict )
		{
		return true;
		}

	// If we hit someone else we don't like, then shoot
	t = trace.ent->entity;
	if ( IsEnemy( t ) )
		{
		return true;
		}

	// if we hit something breakable, check if shooting it will
   // let us shoot someone.
	if ( t->isSubclassOf( Object ) ||
		t->isSubclassOf( ScriptModel ) )
		{
      trace = G_Trace( Vector( trace.endpos ), vec_zero, vec_zero, end, t, mask, false, "Actor::CanShootFrom 2" );
	   if ( trace.startsolid )
		   {
		   return false;
		   }
      // see if we hit anything at all
      if ( !trace.ent )
         {
         return false;
         }

	   // If we hit the guy we wanted, then shoot
	   if ( trace.ent == ent->edict )
		   {
		   return true;
		   }

	   // If we hit someone else we don't like, then shoot
	   if ( IsEnemy( trace.ent->entity ) )
		   {
		   return true;
		   }

      // Forget it then
      return false;
		}

	return false;
	}

qboolean Actor::CanShoot
	(
	Entity *ent,
	qboolean usecurrentangles
	)

	{
   return CanShootFrom( origin, ent, usecurrentangles );
	}

qboolean Actor::EntityHasFireType
	(
	Entity *ent,
	firetype_t fire_type
	)

	{
	Player *player;
	Weapon *weapon;
	firetype_t weapon_fire_type;


	if ( !ent )
		return false;

	if ( !ent->isSubclassOf( Player ) )
		return true;

	player = (Player *)(Entity *)ent;

	// Try left hand

	weapon = player->GetActiveWeapon( WEAPON_LEFT );

	if ( weapon )
		{
		weapon_fire_type = weapon->GetFireType( FIRE_PRIMARY );

		if ( weapon_fire_type == fire_type )
			return true;
		}

	// Try right hand

	weapon = player->GetActiveWeapon( WEAPON_RIGHT );

	if ( weapon )
		{
		weapon_fire_type = weapon->GetFireType( FIRE_PRIMARY );

		if ( weapon_fire_type == fire_type )
			return true;
		}

	// Try dual weapons

	weapon = player->GetActiveWeapon( WEAPON_DUAL );

	if ( weapon )
		{
		weapon_fire_type = weapon->GetFireType( FIRE_PRIMARY );

		if ( weapon_fire_type == fire_type )
			return true;
		}

	return false;
	}

void Actor::DamageEnemy
	(
	Event *ev
	)
	{
	float damage = 0;

	if ( ev->NumArgs() > 0 )
		damage = ev->GetFloat( 1 );

	if ( ( damage > 0 ) && currentEnemy )
		currentEnemy->Damage( this, this, damage, vec_zero, vec_zero, vec_zero, 0, 0, MOD_CRUSH );
	}

void Actor::TurnTowardsEnemy
	(
	Event *ev
	)
	{
	Vector dir;
	Vector new_angles;

	if ( currentEnemy && !(currentEnemy->flags & FL_NOTARGET) )
		{
		dir = currentEnemy->centroid - origin;
		new_angles = dir.toAngles();

		angles[YAW] = new_angles[YAW];
		angles[ROLL] = 0;
		setAngles( angles );
		}
	}

void Actor::AttackModeEvent
	(
	Event *ev
	)
	{
	qboolean attack_bool;

	attack_bool = ev->GetBoolean( 1 );

	if ( attack_bool )
		{
		ProcessEvent( EV_Actor_AttackPlayer );
		}
	}

qboolean Actor::ShouldAttackEntity
	( 
	Entity *ent
	)

	{
	if ( !ent || !ent->isSubclassOf( Sentient ) || Likes( ent ) )
		return false;

	if ( ent->isSubclassOf( Actor ) )
		{
		Actor *act = (Actor *)ent;

		if ( GetActorFlag( ACTOR_FLAG_IGNORE_PAIN_FROM_ACTORS ) )
			return false;

		if ( !act->GetActorFlag( ACTOR_FLAG_ATTACKABLE_BY_ACTORS ) )
			return false;
		}

	return true;
	}

void Actor::SetAttackableByActors
	(
	Event *ev
	)

	{
	qboolean bool;

	bool = ev->GetBoolean( 1 );

	SetActorFlag( ACTOR_FLAG_ATTACKABLE_BY_ACTORS, bool );
	}

void Actor::SetAttackActors
	(
	Event *ev
	)

	{
	SetActorFlag( ACTOR_FLAG_ATTACK_ACTORS, true );
	}

void Actor::MinimumMeleeHeight
   (
   Event *ev
   )

   {
	minimum_melee_height = ev->GetFloat( 1 );
	}

void Actor::SetDamageAngles
   (
   Event *ev
   )

   {
	damage_angles = ev->GetFloat( 1 );
	}

void Actor::SetImmortal
   (
   Event *ev
   )

   {
	qboolean bool;

	if ( ev->NumArgs() > 0 )
		bool = ev->GetBoolean( 1 );
	else
		bool = true;

	SetActorFlag( ACTOR_FLAG_IMMORTAL, bool );
	}

qboolean Actor::IsImmortal
   (
   void
   )

   {
	return GetActorFlag( ACTOR_FLAG_IMMORTAL );
	}

//***********************************************************************************************
//
// Actor type script commands
//
//***********************************************************************************************

void Actor::FriendEvent
	(
	Event *ev
	)

	{
	actortype = IS_FRIEND;
	}

void Actor::CivilianEvent
	(
	Event *ev
	)

	{
	actortype = IS_CIVILIAN;
	}

void Actor::EnemyEvent
	(
	Event *ev
	)

	{
	actortype = IS_ENEMY;
	}

void Actor::InanimateEvent
   (
   Event *ev
   )

   {
   actortype = IS_INANIMATE;
   //
   // clear the monster flag so triggers are not triggered
   //
	edict->svflags	&= ~SVF_MONSTER;
   //
   // don't make them move
   //
   setMoveType( MOVETYPE_STATIONARY );
   //
   // don't make it bleed
   //
   flags &= ~FL_BLOOD;
   //
   // don't make it gib
   //
   flags &= ~FL_DIE_GIBS;
   }

void Actor::MonsterEvent
	(
	Event *ev
	)

	{
	actortype = IS_MONSTER;
	}

void Actor::AnimalEvent
	(
	Event *ev
	)

	{
	actortype = IS_ANIMAL;
	}

void Actor::SetEnemyType
	(
	Event *ev
	)
	{
	enemytype = ev->GetString( 1 );
	}

//***********************************************************************************************
//
// Enemy management
//
//***********************************************************************************************

void Actor::FindEnemy
	(
	void
	)
	{
	Entity   *player;

   // don't target while player is not in the game or he's in notarget
   player = g_entities[ 0 ].entity;
   if ( !player || ( player->flags & FL_NOTARGET ) )
      {
      return;
      }

	if ( !GetActorFlag( ACTOR_FLAG_ATTACK_ACTORS ) )
		{
		if ( Hates( player ) && ( ( last_enemy_sight_time && CanSee( player ) ) || CanReallySee( player ) ) )
			Stimuli( STIMULI_SIGHT, player, true );
		}
	else
		{
		Entity *entity_to_attack;

		entity_to_attack = FindNearestEnemy();

		if ( entity_to_attack )
			Stimuli( STIMULI_SIGHT, entity_to_attack, true );
		}
	}

Entity *Actor::FindNearestEnemy( void )
	{
	Entity *ent_in_range;
   int i;
	Vector delta;
	gentity_t *ed;
	float best_dist = -1;
	float dist;
	Entity *nearest_enemy = NULL;


	// Go through clients

	for( i = 0 ; i < game.maxclients; i++ )
		{
		ed = &g_entities[ i ];

		if ( !ed->inuse || !ed->entity )
			continue;

		ent_in_range = ed->entity;

		if ( IsEntityAlive( ent_in_range ) )
			{
			delta = origin - ent_in_range->centroid;

			dist = delta * delta;

			if ( dist < best_dist || best_dist == -1 )
				{
				if ( Hates( ent_in_range) && CanSee( ent_in_range ) )
					{
					nearest_enemy = ent_in_range;
					best_dist = dist;
					}
				}
			}
		}

	// Go through actors now

   for( i = 1; i <= ActiveList.NumObjects(); i++ )
      {
      ent_in_range = ActiveList.ObjectAt( i );

		if ( 
            ( ent_in_range->movetype != MOVETYPE_STATIONARY ) && 
            ( ent_in_range->movetype != MOVETYPE_NONE ) && 
            ( this != ent_in_range ) && 
            ( ent_in_range->health > 0 ) && 
            !( ent_in_range->flags & FL_NOTARGET ) 
         )
         {
         delta = origin - ent_in_range->centroid;

			dist = delta * delta;

			if ( dist < best_dist || best_dist == -1 )
				{
				if ( !Likes( ent_in_range) && CanSee( ent_in_range ) )
					{
					nearest_enemy = ent_in_range;
					best_dist = dist;
					}
				}
         }
      }

	return nearest_enemy;
	}

void Actor::GetNearestEnemy
	(
	Event *ev
	)
	{
	currentEnemy = FindNearestEnemy();
	}

#define MAX_RANDOM_ENTS  10

void Actor::GetRandomEnemy
	(
	Event *ev
	)
	{
	float max_distance;
	float max_distance2;
	Entity *ent_in_range;
   int i;
	Vector delta;
	gentity_t *ed;
	float dist;
	Entity *ents_found[MAX_RANDOM_ENTS];
	int number_of_ents_found = 0;


	// Get the maximum distance that we will look for enemies

	max_distance = ev->GetFloat( 1 ) ;
	max_distance2 = max_distance * max_distance;

	// Go through clients

	for( i = 0 ; i < game.maxclients; i++ )
      {
		if ( number_of_ents_found >= MAX_RANDOM_ENTS )
			break;

      ed = &g_entities[ i ];

		if ( !ed->inuse || !ed->entity )
			continue;

		ent_in_range = ed->entity;

		if ( IsEntityAlive( ent_in_range ) )
         {
         delta = origin - ent_in_range->centroid;

			dist = delta * delta;

			if ( dist < max_distance2 )
				{
				if ( CanSee( ent_in_range ) )
					{
					ents_found[number_of_ents_found] = ent_in_range;
					number_of_ents_found++;
					}
				}
         }
		}

	// Go through actors now

   for( i = 1; i <= ActiveList.NumObjects(); i++ )
      {
		if ( number_of_ents_found >= MAX_RANDOM_ENTS )
			break;

      ent_in_range = ActiveList.ObjectAt( i );

		if ( 
            ( ent_in_range->movetype != MOVETYPE_STATIONARY ) && 
            ( ent_in_range->movetype != MOVETYPE_NONE ) && 
            ( this != ent_in_range ) && 
            ( ent_in_range->health > 0 ) && 
            !( ent_in_range->flags & FL_NOTARGET ) && 
            ent_in_range->isSubclassOf( Actor ) 
         )
         {
			Actor *act = (Actor *)ent_in_range;

			if ( act->actortype == IS_FRIEND && act->dialog_list )
				{
				delta = origin - ent_in_range->centroid;

				dist = delta * delta;

				if ( dist < max_distance2 )
					{
					if ( CanSee( ent_in_range ) )
						{
						ents_found[number_of_ents_found] = ent_in_range;
						number_of_ents_found++;
						}
					}
				}
         }
      }

	if ( number_of_ents_found )
		currentEnemy = ents_found[ (int)G_Random( number_of_ents_found ) ];
	else
		currentEnemy = NULL;
	}

qboolean Actor::HasEnemies
	(
	void
	)

	{
	return ( currentEnemy != NULL );
	}

qboolean Actor::IsEnemy
	(
	Entity *ent
	)

	{
	return ( ent != NULL ) && ( currentEnemy == ent );
	}

void Actor::MakeEnemy
	(
	Entity *ent,
   qboolean force
	)

	{
   // Don't get mad at things that can't be hurt or the world

	if ( !ent || ( ent == world ) || ( ent == this ) || ( ent->flags & FL_NOTARGET ) || ( ent->takedamage == DAMAGE_NO ) )
      return;

	if ( !currentEnemy || force )
		{
		currentEnemy = ent;
		last_enemy_sight_time = level.time;
		}

	Wakeup();
	}

void Actor::ClearEnemies
   (
   void
   )

   {
	currentEnemy = NULL;
   Sleep();
   }


qboolean Actor::Likes
	(
	Entity *ent
	)

	{
	Actor *act;

	if ( ent->isClient() )
		{
		return ( actortype == IS_FRIEND );
		}
	
	if ( actortype == IS_MONSTER )
      {
      // Monsters don't like anyone
      return false;
      }

	if ( ent->isSubclassOf( Actor ) )
		{
		act = ( Actor * )ent;

		if ( act->enemytype == enemytype )
			return true;

		if  ( act->actortype != actortype )
			return false;
		else if ( actortype == IS_FRIEND )
			return true;
		}
   
	return false;
}

qboolean Actor::Hates
	(
	Entity *ent
	)

	{
	Actor *act;

   assert( ent );
   if ( !ent )
      {
      return false;
      }

	if ( ent->isClient() )
		{
	   return ( actortype != IS_CIVILIAN ) && ( actortype != IS_FRIEND );
		}
	else if ( ent->isSubclassOf( Actor ) && ( actortype != IS_INANIMATE ) )
		{
		act = ( Actor * )ent;
      if ( ( act->actortype <= IS_ENEMY ) && ( actortype <= IS_ENEMY ) )
			{
			return false;
			}
		if ( ( act->actortype == IS_FRIEND ) && ( actortype <= IS_ENEMY ) )
			{
			return true;
			}
		if ( ( act->actortype <= IS_ENEMY ) && ( actortype == IS_FRIEND ) )
			{
			return true;
			}
		}

	return false;
	}

//***********************************************************************************************
//
// Targeting functions
//
//***********************************************************************************************

qboolean Actor::CloseToEnemy
	(
	Vector pos,
	float howclose
	)

	{
	if ( !IsEntityAlive( currentEnemy ) )
		{
		return false;
		}

	if ( WithinDistance( currentEnemy, howclose ) )
		{
		return true;
		}

	return false;
	}

void Actor::EyeOffset
	(
	Event *ev
	)
	{
   eyeposition -= eyeoffset;
   eyeoffset = ev->GetVector( 1 );
   eyeposition += eyeoffset;
   }

qboolean Actor::EntityInRange
   (
   Entity *ent,
	float range,
	float min_height,
	float max_height
   )

	{
	float    r;
   Vector   delta;
	float    height_diff;

	// Make sure the entity is alive

	if ( !IsEntityAlive( ent ) )
      {
		return false;
      }

	// See if the entity is in range

   delta = ent->centroid - centroid;

	if ( max_height != 0 || min_height != 0 )
		{
		height_diff = delta[ 2 ];

		if ( ( height_diff < min_height ) || ( height_diff > max_height ) )
         {
			return false;
         }

		delta[ 2 ] = 0;
		}

	r = delta * delta;

	return ( r < range * range );
	}

//***********************************************************************************************
//
// Thread management
//
//***********************************************************************************************

void Actor::SetupThread
	(
	str filename, 
	str label
	)
	{

	if ( actorthread )
		return;

	actorthread = Director.CreateThread( filename.c_str(), MODEL_SCRIPT );

	if ( actorthread )
		{
		if ( label.length() )
			{
			if ( !actorthread->Goto( label.c_str() ) )
				{
            gi.DPrintf( "Label '%s' not found in %s.", label.c_str(), filename.c_str() );
				return;
				}
			}

		ProcessScript( actorthread );
		}
	}

void Actor::ProcessScript
	(
	ScriptThread *thread,
   Event *ev
	)

	{
	thread->Vars()->SetVariable( "self", this );
   thread->Vars()->SetVariable( "origin", origin );
   thread->Vars()->SetVariable( "yaw", angles.y );
	thread->Vars()->SetVariable( "health", health );
	thread->Vars()->SetVariable( "startpos", startpos );
   
	if ( currentEnemy )
		{
		thread->Vars()->SetVariable( "enemy", currentEnemy );
		}
	else
		{
		thread->Vars()->SetVariable( "enemy", "" );
		}

   if ( ev )
      {
	   thread->ProcessEvent( ev );
      }
   else
      {
      thread->ProcessEvent( EV_ScriptThread_Execute );
      }
	}

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   float value
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, value );
      }

   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   int value
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, value );
      }

   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   const char *text
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, text );
      }

   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   str &text
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, text.c_str() );
      }

   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   Entity *ent
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, ent );
      }

   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   Vector &vec
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, vec );
      }

   return NULL;
   }

//***********************************************************************************************
//
// State machine functions
//
//***********************************************************************************************

void Actor::SetIdleStateName
	(
	Event *ev
	)
	{
	idle_state_name = ev->GetString( 1 );
	}

void Actor::SetState( const char *state_name )
	{
	ClassDef *cls;
	int i;
	Event *e;

	if ( !statemap )
		return;

	if ( deadflag )
		return;

	if ( currentState )
		currentState->ProcessExitCommands( this );

   currentState = statemap->FindState( state_name );
	state_time = level.time;

	// Set the behavior

	if ( currentState  )
		{
		cls = getClass( currentState->getBehaviorName() );

		if ( cls )
			{
			if ( currentState->numBehaviorParms() )
				{
				e = new Event( EV_Behavior_Args );

				for ( i = 1 ; i <= currentState->numBehaviorParms() ; i++ )
					e->AddString( currentState->getBehaviorParm( i ) );

				SetBehavior( ( Behavior * )cls->newInstance(), e );
				}
			else
				{
				SetBehavior( ( Behavior * )cls->newInstance() );
				}
			}

		InitState();
		currentState->ProcessEntryCommands( this );
		}
	else
		{
		gi.DPrintf( "State %s not found\n", state_name );
		}
	}

void Actor::InitState
	(
	void
	)

	{
	float min_time;
	float max_time;


	min_time = currentState->getMinTime();
	max_time = currentState->getMaxTime();

	if ( (min_time != -1) && (max_time != -1) )
		{
		SetActorFlag( ACTOR_FLAG_STATE_DONE_TIME_VALID, true );

		state_done_time = level.time + min_time + G_Random( max_time - min_time );
		}
	else
		{
		SetActorFlag( ACTOR_FLAG_STATE_DONE_TIME_VALID, false );
		}

	state_time = level.time;
	times_done = 0;

	ClearStateFlags();
	command = "";

	SetActorFlag( ACTOR_FLAG_ANIM_DONE, false );
	SetActorFlag( ACTOR_FLAG_NOISE_HEARD, false );
	}

void Actor::LoadStateMap
	(
	Event *ev
	)

	{
	str anim_name;
	qboolean loading;


	// Load the new state map

	statemap_name = ev->GetString( 1 );

   conditionals.FreeObjectList();
	statemap = GetStatemap( statemap_name, ( Condition<Class> * )Conditions, &conditionals, false );

	// Set the first state

	if ( ev->NumArgs() > 1 )
		idle_state_name = ev->GetString( 2 );
	else
		idle_state_name = "IDLE";

	if ( ev->NumArgs() > 2 )
		loading = ev->GetBoolean( 3 );
	else
		loading = false;

	// Initialize the actors first animation

	if ( !loading )
		{
		SetState( idle_state_name.c_str() );

		if ( currentState )
			anim_name = currentState->getLegAnim( *this, &conditionals );

		if ( anim_name == "" && !newanim.length() )
			anim_name = "idle";

		SetAnim( anim_name.c_str(), EV_Anim_Done );
		ChangeAnim();

		flags &= ~FL_THINK;
		}
	}

void Actor::ProcessActorStateMachine( void )
	{
	int count;
	ClassDef *cls = NULL;
	str behavior_arg;
	const char *currentanim;
	str behavior_name;
	State	*laststate;

	count = 0;

	if ( deadflag || !currentState )
		return;

	if ( mode != ACTOR_MODE_AI && mode != ACTOR_MODE_IDLE )
		return;

	do
		{
		// Since we could get into an infinite loop here, do a check to make sure we don't.

		count++;
		if ( count > 10 )
			{
			gi.DPrintf( "Possible infinite loop in state '%s'\n", currentState->getName() );
			if ( count > 20 )
				{
				gi.Error( ERR_DROP, "Stopping due to possible infinite state loop\n" );
				break;
				}
			}

		// Determine the next state to go to

		laststate = currentState;
		currentState = currentState->Evaluate( *this, &conditionals );

		// Change the behavior if the state has changed

		if ( laststate != currentState )
			{
			// Process exit commands of the last state

         laststate->ProcessExitCommands( this );

         // Process entry commands of the new state

         currentState->ProcessEntryCommands( this );

			// Setup the new behavior

			behavior_name = currentState->getBehaviorName();

			if ( behavior_name.length() )
				cls = getClass( currentState->getBehaviorName() );

			if ( cls )
				{
				if ( currentState->numBehaviorParms() )
					{
					int i;
					Event *e = new Event( EV_Behavior_Args );

					for ( i = 1 ; i <= currentState->numBehaviorParms() ; i++ )
						e->AddString( currentState->getBehaviorParm( i ) );

					SetBehavior( ( Behavior * )cls->newInstance(), e );
					}
				else
					{
					SetBehavior( ( Behavior * )cls->newInstance() );
					}
				}
			else if ( behavior_name.length() )
				{
				gi.DPrintf( "Invalid behavior name %s\n", behavior_name.c_str() );
				}

			// Initialize some stuff for changing states

			InitState();
			}

		// Change the animation if it has changed

		currentanim = currentState->getLegAnim( *this, &conditionals );

		if ( currentanim[0] != 0 && strcmp( animname, currentanim ) != 0 )
			SetAnim( currentanim, EV_Anim_Done );
		}
	while( laststate != currentState );
	}

//***********************************************************************************************
//
// Thread based script commands
//
//***********************************************************************************************

void Actor::RunThread
	(
	Event *ev
	)

	{
	str thread_name;
	ScriptThread *thread;


	thread_name = ev->GetString( 1 );
	
	thread = ExecuteThread( thread_name.c_str(), false );

	if ( thread )
		ProcessScript( thread, NULL );
	else
		warning( "RunThread", "could not process thread" );
	}

void Actor::SetThread
	(
	Event *ev
	)

	{
	ScriptThread *thread;
	str label;

	if ( mode == ACTOR_MODE_AI )
		return;

	thread = ev->GetThread();
	label = ev->GetString( 1 );

	if ( !thread )
		return;

	if ( mode != ACTOR_MODE_TALK )
		StartMode( ACTOR_MODE_SCRIPT );
		
	SetThread( thread->Filename(), label );

	if ( mode == ACTOR_MODE_TALK )
		{
		saved_mode = ACTOR_MODE_SCRIPT;
		saved_actorthread = actorthread;
		actorthread = NULL;
		return;
		}
	}

void Actor::SetThread
	(
	str filename,
	str label
	)

	{
	str start;

	
	if ( filename.length() == 0 || label.length() == 0 )
		return;

	if ( !actorthread )
		{
		SetupThread( filename, label );
		}
	else
		{
		start = filename + "::" + label;

		if ( actorthread->Goto( start.c_str() ) )
			{
			ProcessScript( actorthread );
			}
		else
			gi.DPrintf( "Label '%s' not found.  Couldn't change thread.", start.c_str() );
		}
	}

void Actor::EndThread
	(
	Event *ev
	)

	{
	if ( actorthread )
		{
		actorthread->ProcessEvent( EV_ScriptThread_End );
		actorthread = NULL;

		if ( mode == ACTOR_MODE_SCRIPT )
			{
			if ( behavior )
				EndBehavior();
			}
		}
	}

//***********************************************************************************************
//
// Behavior management
//
//***********************************************************************************************

void Actor::SendMoveDone( ScriptThread *script_thread )
	{
	Event *event;

	if ( script_thread )
		{
		event = new Event( EV_MoveDone );
		event->AddEntity( this );
		script_thread->PostEvent( event, FRAMETIME );
      }
	}

void Actor::EndBehavior
	(
	void
	)

	{
	ScriptThread *t;
	Event *event;


	if ( behavior )
		{
		behavior->End( *this );
		delete behavior;
		behavior = NULL;

		if ( scriptthread )
			{
			t = scriptthread;
			scriptthread = NULL;

			if ( actorthread )
				{
				event = new Event( EV_MoveDone );
				event->AddEntity( this );
				ProcessScript( actorthread, event );
				}

         if ( t != actorthread )
            {
			   event = new Event( EV_MoveDone );
			   event->AddEntity( this );
			   t->ProcessEvent( event );
            }
         }
		}

   // Prevent previous behaviors from stopping the next behavior
   CancelEventsOfType( EV_Actor_FinishedBehavior );
	}

void Actor::SetBehavior
	(
	Behavior *newbehavior,
	Event *startevent,
	ScriptThread *newthread
	)

	{
	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		// Delete the unused stuff

		if ( newbehavior )
			delete newbehavior;
		if ( startevent )
			delete startevent;

		return;
		}

	// End any previous behavior, but don't call EV_MoveDone if we're using the same thread,
	// or we'll end THIS behavior
	if ( scriptthread == newthread )
		{
		scriptthread = NULL;
		}
	EndBehavior();

	behavior = newbehavior;
	if ( behavior )
		{
		//flags |= FL_THINK;
		Wakeup();

		if ( startevent )
			{
			behavior->ProcessEvent( startevent );
			}
		currentBehavior = behavior->getClassname();
		behavior->Begin( *this );
		scriptthread = newthread;
		}
	}

void Actor::FinishedBehavior
	(
	Event *ev
	)

	{
	EndBehavior();
	}

void Actor::NotifyBehavior
	(
	Event *ev
	)

	{
	if ( behavior )
		{
		behavior->ProcessEvent( EV_Behavior_AnimDone );
		SetActorFlag( ACTOR_FLAG_ANIM_DONE, true );
		}
	}

//***********************************************************************************************
//
// Path and node management
//
//***********************************************************************************************

PathNode *Actor::NearestNodeInPVS
	(
	Vector pos
	)

	{
	Vector	delta;
	PathNode	*node;
	PathNode	*bestnode;
	float		bestdist;
	float		dist;
	int		number_nodes;
	int		i;
	MapCell	*cell;
	Vector	min;
	Vector	max;


	cell = PathManager.GetNodesInCell( pos );

	if ( !cell )
		return NULL;

	number_nodes = cell->NumNodes();

	bestnode = NULL;
	bestdist = 999999999; // greater than ( 8192 * sqr(2) ) ^ 2 -- maximum squared distance

	for( i = 0; i < number_nodes; i++ )
		{
		node = ( PathNode * )cell->GetNode( i );

		if ( !node )
			continue;

      delta = node->origin - pos;

		// get the distance squared (faster than getting real distance)
		dist = delta * delta;

      if ( ( dist < bestdist ) && gi.inPVS( node->origin, pos ) )
			{
			bestnode = node;
			bestdist = dist;

         // if we're close enough, early exit
         if ( dist < 16 )
            break;
			}
		}

	return bestnode;
	}

void Actor::SetPath
	(
	Path *newpath
	)

	{
	if ( path && ( path != newpath ) )
		{
		delete path;
		}
	path = newpath;
	}

void Actor::ReserveNodeEvent
	(
	Event *ev
	)

	{
	PathNode *node;
	Vector pos;

	pos = ev->GetVector( 1 );
	node = PathManager.NearestNode( pos, this );

	if ( node && ( !node->entnum || ( node->entnum == entnum ) || ( node->occupiedTime < level.time ) ) )
		{
		// Mark node as occupied for a short time
		node->occupiedTime = level.time + ev->GetFloat( 2 );
		node->entnum = entnum;
		}
	}

void Actor::ReleaseNodeEvent
	(
	Event *ev
	)

	{
	PathNode *node;
	Vector pos;

	pos = ev->GetVector( 1 );
	node = PathManager.NearestNode( pos, this );

	if ( node && ( node->entnum == entnum ) )
		{
		node->occupiedTime = 0;
		node->entnum = 0;
		}
	}

//***********************************************************************************************
//
// Animation control functions
//
//***********************************************************************************************

void Actor::RemoveAnimDoneEvent( void )
	{
	SetAnimDoneEvent( NULL );

	if ( newanimevent )
		{
		delete newanimevent;
		newanimevent = NULL;
		}

	last_anim_event_name = "";
	}

void Actor::ChangeAnim
	(
	void
	)

	{
	float time;
	Vector totalmove;

	if ( newanimnum == -1 )
		{
		return;
		}

	// If we're changing to the same anim, don't restart the animation
	if ( newanimnum == CurrentAnim() && animname == newanim)
		{
      SetAnimDoneEvent( newanimevent );
		}
	else
		{
		animname = newanim;

		time = gi.Anim_Time( edict->s.modelindex, newanimnum );
		gi.Anim_Delta( edict->s.modelindex, newanimnum, totalmove );

      totalmove *= edict->s.scale;
		totallen = totalmove.length();

		// always have a valid move direction
		if ( totallen > 0.01 )
			{
			movespeed = totallen / time;
			animdir = totalmove * ( 1 / totallen );
			}
		else
			{
         if ( forwardspeed )
            {
	   	   movespeed = forwardspeed;
            }
         else
            {
			   movespeed = 1;
            }
			animdir = Vector( 1, 0, 0 );
			}

		MatrixTransformVector( animdir, orientation, movedir );
		movevelocity = movedir * movespeed;


      NewAnim( newanimnum, newanimevent );
		}

	// clear the new anim variables
	newanimnum = -1;
	newanim = "";
	newanimevent = NULL;
	}

void Actor::AnimDone
	(
	Event *ev
	)

	{
	SetActorFlag( ACTOR_FLAG_ANIM_DONE, true );
	}

qboolean Actor::SetAnim
	(
	str anim,
	Event *ev
	)

   {
   int num;

	num = gi.Anim_Random( edict->s.modelindex, anim.c_str() );
	if ( num != -1 )
		{
		newanim = anim;
		newanimnum = num;

		if ( newanimevent )
			delete newanimevent;

		newanimevent = ev;

		if ( newanimevent )
			last_anim_event_name = newanimevent->getName();
		else
			last_anim_event_name = "";

      if ( actortype == IS_INANIMATE )
         {
         // inanimate objects change anims immediately
         ChangeAnim();
         }

		return true;
		}

	// kill the event
	if ( ev )
		{
		delete ev;
		}

	return false;
	}

qboolean Actor::SetAnim
	(
	str anim,
	Event &ev
	)

	{
   Event * event;

	//last_anim_event = &ev;

   event = new Event( ev );
   return SetAnim( anim, event );
	}

void Actor::Anim
	(
	Event *ev
	)

	{
	Event *e;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			PostEvent( *ev, FRAMETIME );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	e = new Event( EV_Behavior_Args );

	e->SetSource( ev->GetSource() );

	if ( ev->GetSource() == EV_FROM_SCRIPT )
		{
		StartMode( ACTOR_MODE_SCRIPT );

		e->SetThread( ev->GetThread() );
		e->SetLineNumber( ev->GetLineNumber() );
		}

	e->AddToken( ev->GetToken( 1 ) );

	SetBehavior( new PlayAnim, e, ev->GetThread() );
	}

//***********************************************************************************************
//
// Script commands
//
//***********************************************************************************************

void Actor::IdleEvent
	(
	Event *ev
	)

	{
	const char *state_name;

	if ( !ModeAllowed( ACTOR_MODE_IDLE ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_Idle );
		return;
		}

	if ( ev->NumArgs() > 0 )
		state_name = ev->GetString( 1 );
	else
		state_name = idle_state_name;

	SetState( state_name );

	StartMode( ACTOR_MODE_IDLE );
	}

void Actor::LookAt
	(
	Event *ev
	)

	{
	Entity *ent;
	TurnTo *turnTo;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_LookAt );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}

	StartMode( ACTOR_MODE_SCRIPT );

	ent = ev->GetEntity( 1 );
	if ( ent && ent != world )
		{
		turnTo = new TurnTo;
		turnTo->SetTarget( ent );
		SetBehavior( turnTo, NULL, ev->GetThread() );
		}
	}

void Actor::TurnToEvent
	(
	Event *ev
	)

	{
	TurnTo *turnTo;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_TurnTo );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}

	StartMode( ACTOR_MODE_SCRIPT );

	turnTo = new TurnTo;
	turnTo->SetDirection( ev->GetFloat( 1 ) );

	SetBehavior( turnTo, NULL, ev->GetThread() );
	}

void Actor::HeadWatchEvent
	(
	Event *ev
	)

	{
	Event *event;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_HeadWatch );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}
		
	StartMode( ACTOR_MODE_SCRIPT );

	event = new Event( EV_Behavior_Args );
	event->AddEntity( ev->GetEntity( 1 ) );

	if ( ev->NumArgs() > 1 )
		event->AddFloat( ev->GetFloat( 2 ) );

	SetBehavior( new HeadWatch, event, ev->GetThread() );
	}

void Actor::ResetHeadEvent
	(
	Event *ev
	)

	{
	Event *event;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_ResetHead );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}
		
	StartMode( ACTOR_MODE_SCRIPT );

	event = new Event( EV_Behavior_Args );
	event->AddEntity( NULL );

	if ( ev->NumArgs() > 0 )
		event->AddFloat( ev->GetFloat( 1 ) );

	SetBehavior( new HeadWatch, event, ev->GetThread() );
	}

void Actor::WalkTo
	(
	Event *ev
	)

	{
	Event *e;


	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_WalkTo );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}

	StartMode( ACTOR_MODE_SCRIPT );

	e = new Event( EV_Behavior_Args );

	e->SetSource( ev->GetSource() );

	if ( ev->GetSource() == EV_FROM_SCRIPT )
		{
		e->SetThread( ev->GetThread() );
		e->SetLineNumber( ev->GetLineNumber() );
		}

	if ( ev->NumArgs() > 1 )
		e->AddString( ev->GetString( 2 ) );
	else
		e->AddString( "walk" );

	if ( ev->NumArgs() > 0 )
		e->AddToken( ev->GetToken( 1 ) );

	SetBehavior( new GotoPathNode, e, ev->GetThread() );
	}

void Actor::WalkWatch
	(
	Event *ev
	)

	{
	Event *e;


	if ( ev->NumArgs() < 2 )
		return;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_WalkWatch );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}

	StartMode( ACTOR_MODE_SCRIPT );

	e = new Event( EV_Behavior_Args );

	e->SetSource( ev->GetSource() );

	if ( ev->GetSource() == EV_FROM_SCRIPT )
		{
		e->SetThread( ev->GetThread() );
		e->SetLineNumber( ev->GetLineNumber() );
		}

	// Get animation name

	if ( ev->NumArgs() > 2 )
		e->AddString( ev->GetString( 3 ) );
	else
		e->AddString( "walk" );

	// Get the node to walk to

	e->AddToken( ev->GetToken( 1 ) );

	// Get the entity to watch

	e->AddEntity( ev->GetEntity( 2 ) );

	SetBehavior( new GotoPathNode, e, ev->GetThread() );
	}

void Actor::RunTo
	(
	Event *ev
	)

	{
	Event *e;
	int i;
	int n;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_RunTo );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}

	StartMode( ACTOR_MODE_SCRIPT );

	e = new Event( EV_Behavior_Args );

	e->SetSource( ev->GetSource() );

	if ( ev->GetSource() == EV_FROM_SCRIPT )
		{
		e->SetThread( ev->GetThread() );
		e->SetLineNumber( ev->GetLineNumber() );
		}

	e->AddString( "run" );

	n = ev->NumArgs();

	for( i = 1; i <= n; i++ )
		{
		e->AddToken( ev->GetToken( i ) );
		}

	SetBehavior( new GotoPathNode, e, ev->GetThread() );
	}

void Actor::WarpTo
	(
	Event *ev
	)

	{
	PathNode *goal_node;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_WarpTo );
		return;
		}

	if ( ev->NumArgs() > 0 )
		{
		goal_node = AI_FindNode( ev->GetString( 1 ) );

		if ( goal_node )
			{
			origin = goal_node->origin;
			setOrigin( origin );

			angles = goal_node->angles;
			setAngles( angles );

			NoLerpThisFrame();
			}
		}
	}

void Actor::PickupEnt
	(
	Event *ev
	)

	{
	Event *e;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_PickupEnt );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}

	StartMode( ACTOR_MODE_SCRIPT );

	e = new Event( EV_Behavior_Args );

	e->SetSource( ev->GetSource() );

	if ( ev->GetSource() == EV_FROM_SCRIPT )
		{
		e->SetThread( ev->GetThread() );
		e->SetLineNumber( ev->GetLineNumber() );
		}

	e->AddEntity( ev->GetEntity( 1 ) );
	e->AddString( ev->GetString( 2 ) );

	SetBehavior( new PickupEntity, e, ev->GetThread() );
	}

void Actor::ThrowEnt
	(
	Event *ev
	)

	{
	Event *e;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			RepostEvent( ev, EV_Actor_ThrowEnt );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}

	StartMode( ACTOR_MODE_SCRIPT );

	e = new Event( EV_Behavior_Args );

	e->SetSource( ev->GetSource() );

	if ( ev->GetSource() == EV_FROM_SCRIPT )
		{
		e->SetThread( ev->GetThread() );
		e->SetLineNumber( ev->GetLineNumber() );
		}

	e->AddString( ev->GetString( 1 ) );

	SetBehavior( new ThrowEntity, e, ev->GetThread() );
	}

void Actor::AttackEntity
	(
	Event *ev
	)

	{
	Entity *ent;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	ent = ev->GetEntity( 1 );

   // don't get mad at things that can't be hurt or the world
	if (
         ent &&
         ( ent != world ) &&
         ( ent->takedamage != DAMAGE_NO )
      )

		{
      ClearEnemies();
		Stimuli( STIMULI_SCRIPT, ent, true );	
		}
	}

void Actor::AttackPlayer
	(
	Event *ev
	)

	{
   int i;
   gentity_t *ent;

	if ( !GetActorFlag( ACTOR_FLAG_STARTED ) )
		{
		PostEvent( *ev, FRAMETIME );
		return;
		}

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

   ClearEnemies();

   // make enemies of all the players
   for( i = 0; i < maxclients->integer; i++ )
		{
      ent = &g_entities[ i ];
		if ( !ent->inuse || !ent->client || !ent->entity )
			{
			continue;
			}

		Stimuli( STIMULI_SCRIPT, ent->entity, true );
		}
	}

void Actor::JumpToEvent
	(
	Event *ev
	)

	{
	Event *e;
	int i;
	int n;

	if ( !ModeAllowed( ACTOR_MODE_SCRIPT ) )
		{
		if ( mode == ACTOR_MODE_TALK )
			PostEvent( *ev, FRAMETIME );
		else if ( mode == ACTOR_MODE_AI )
			SendMoveDone( ev->GetThread() );
		return;
		}

	StartMode( ACTOR_MODE_SCRIPT );

	e = new Event( EV_Behavior_Args );

	e->SetSource( ev->GetSource() );

	if ( ev->GetSource() == EV_FROM_SCRIPT )
		{
		e->SetThread( ev->GetThread() );
		e->SetLineNumber( ev->GetLineNumber() );
		}

	//e->AddString( "jump" );

	n = ev->NumArgs();

	for( i = 1; i <= n; i++ )
		{
		e->AddToken( ev->GetToken( i ) );
		}

	SetBehavior( new JumpToPathNode, e, ev->GetThread() );
	}

void Actor::GotoEvent
   (
   Event *ev
   )

   {
   // This command was added because it was a common mistake when writing actor scripts
   // to say "local.self goto label".  Since we're such nice guys, we'll print a warning
   // and send it on the the calling thread. :)
   ScriptThread *thread;

   thread = ev->GetThread();
   if ( thread )
      {
      gi.DPrintf( "Actor recieved 'goto' command.  Passing to thread.\n" );
      thread->ProcessEvent( ev );
      }
   else
      {
      // should never happen, but say something anyways.
      gi.DPrintf( "Actor recieved 'goto' command.  Thread is NULL.\n" );
      }
   }

void Actor::RepostEvent
   (
   Event *ev,
	Event &event_type
   )
	{
	Event *event;
	int i;
	str token;

	event = new Event( event_type );

	for( i = 1 ; i <= ev->NumArgs() ; i++ )
		{
		token = ev->GetString( i );
		event->AddString( token.c_str() );
		}

	event->SetThread( ev->GetThread() );

	PostEvent( event, FRAMETIME );
	}

//***********************************************************************************************
//
// Script conditionals
//
//***********************************************************************************************

void Actor::IfEnemyVisibleEvent
	(
	Event *ev
	)

	{
	ScriptThread *thread;

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

   if ( CanSeeEnemyFrom( origin ) )
		{
		thread->ProcessCommandFromEvent( ev, 1 );
		}
	}

void Actor::IfNearEvent
	(
	Event *ev
	)

	{
	ScriptThread	*thread;
	Entity			*ent;
	Entity			*bestent;
	float				bestdist;
	float				dist;
	str				name;
   Vector         delta;
	float				distance;
	TargetList		*tlist;
	int				n;
	int				i;

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

	name = ev->GetString( 1 );
	distance = ev->GetFloat( 2 );

	if ( name[ 0 ] == '*' )
		{
		ent = ev->GetEntity( 1 );
		if ( WithinDistance( ent, distance ) )
			{
			SetVariable( "other", ent );
			thread->ProcessCommandFromEvent( ev, 3 );
			}
		}
	else if ( name[ 0 ] == '$' )
		{
		bestent = NULL;
		bestdist = distance * distance;

		tlist = world->GetTargetList( str( &name[ 1 ] ) );
		n = tlist->list.NumObjects();
		for( i = 1; i <= n; i++ )
			{
			ent = tlist->list.ObjectAt( i );
         delta = centroid - ent->centroid;
			dist = delta * delta;
			if ( dist <= bestdist )
				{
				bestent = ent;
				bestdist = dist;
				}
			}

		if ( bestent )
			{
			SetVariable( "other", bestent );
			thread->ProcessCommandFromEvent( ev, 3 );
			}
		}
	else
		{
		bestent = NULL;
		bestdist = distance * distance;

		ent = NULL;

		for( ent = findradius( ent, origin, distance ) ; ent ; ent = findradius( ent, origin, distance ) )
			{
			if ( ent->inheritsFrom( name.c_str() ) )
				{
            delta = centroid - ent->centroid;
			   dist = delta * delta;
				if ( dist <= bestdist )
					{
					bestent = ent;
					bestdist = dist;
					}
				}
			}

		if ( bestent )
			{
			SetVariable( "other", bestent );
			thread->ProcessCommandFromEvent( ev, 3 );
			}
		}
	}

void Actor::IfCanHideAtEvent
	(
	Event *ev
	)

	{
	PathNode *node;
	Vector pos;
	ScriptThread *thread;

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

	pos = ev->GetVector( 1 );
	node = PathManager.NearestNode( pos, this );

	if ( node && ( node->nodeflags & ( AI_DUCK | AI_COVER ) ) && !CanSeeEnemyFrom( pos ) )
		{
		if ( !node->entnum || ( node->entnum == entnum ) || ( node->occupiedTime < level.time ) )
			{
			thread->ProcessCommandFromEvent( ev, 2 );
			}
		}
	}

void Actor::IfEnemyWithinEvent
	(
	Event *ev
	)

	{
	ScriptThread *thread;

	if ( !currentEnemy )
		{
		return;
		}

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

   if ( WithinDistance( currentEnemy, ev->GetFloat( 1 ) ) )
      {
		thread->ProcessCommandFromEvent( ev, 2 );
      }
	}

//***********************************************************************************************
//
// Sound reaction functions
//
//***********************************************************************************************

void Actor::NoPainSounds
	(
	Event *ev
	)

	{
	SetActorFlag( ACTOR_FLAG_NO_PAIN_SOUNDS, true );
	}

void Actor::HeardSound
	(
	Event *ev
	)

	{
	Vector location;

	location = ev->GetVector( 2 );

	Stimuli( STIMULI_SOUND, location );
	}

qboolean Actor::IgnoreSounds
	(
	void
	)

	{
	if ( GetActorFlag( ACTOR_FLAG_NEVER_IGNORE_SOUNDS ) )
		return false;

	if ( currentEnemy && flags & FL_THINK )
		return true;

	if ( !( stimuli & STIMULI_SOUND ) )
		return true;
		
	return false;
	}

void Actor::NeverIgnoreSounds
   (
   Event *ev
   )
	{
	SetActorFlag( ACTOR_FLAG_NEVER_IGNORE_SOUNDS, true );
	}

//***********************************************************************************************
//
// Pain and death related functions
//
//***********************************************************************************************

void Actor::Pain
	(
	Event *ev
	)

	{
	float damage;
	Entity *ent;
	int mod;
	Vector direction;
	Vector position;
	Vector dir;
	State	*tempState;


	damage		= ev->GetFloat( 1 );
	ent			= ev->GetEntity( 2 );
	mod			= ev->GetInteger( 3 );
	position		= ev->GetVector( 4 );
	direction	= ev->GetVector( 5 );

	// Add to the players action level

	if ( damage && !deadflag && ent && ent->isSubclassOf( Player ) )
		{
		Player *player = (Player *)ent;

		player->IncreaseActionLevel( damage / 4 );
		}

	if ( deadflag )
		{
		// Do gib stuff

		if ( statemap )
			{
			tempState = statemap->FindState( "GIB" );

			if ( tempState )
				tempState = tempState->Evaluate( *this, &conditionals );

			if ( tempState )
				{
				tempState->ProcessEntryCommands( this );
				}
			}
		return;
		}

	if ( damage > 0 && next_pain_sound_time <= level.time && !GetActorFlag( ACTOR_FLAG_NO_PAIN_SOUNDS ) )
		{
		next_pain_sound_time = level.time + 0.4 + G_Random( 0.2 );
		BroadcastSound();
		}

	if ( !GetActorFlag( ACTOR_FLAG_ALLOWED_TO_KILL ) && ent && ent->isSubclassOf( Player ) )
		{
		if ( damage >= pain_threshold )
			G_MissionFailed();
		}
	else
		{
		if ( ShouldAttackEntity( ent ) )
			Stimuli( STIMULI_PAIN, ent, true );
		else
			StimuliNoAttack( STIMULI_PAIN );
		}

	if ( mod == MOD_BULLET && behavior && currentBehavior == "Pain" )
		{
		bullet_hits++;
		}

	// Determine which pain flags to set

	AddStateFlag( STATE_FLAG_SMALL_PAIN );

	if ( damage < pain_threshold )
		{
		if ( G_Random( 1 ) < damage / pain_threshold )
			{
			if ( means_of_death == MOD_SWORD || means_of_death == MOD_AXE || means_of_death == MOD_FIRESWORD || 
				  means_of_death == MOD_ELECTRICSWORD )
				pain_type = PAIN_BIG;
			else
				pain_type = PAIN_SMALL;
			AddStateFlag( STATE_FLAG_IN_PAIN );
			}
		}
	else
		{
		pain_type = PAIN_BIG;
		AddStateFlag( STATE_FLAG_IN_PAIN );
		}

	// Determine pain angles

	if ( Vector( position - centroid ).length() > 1 )
		dir = centroid - position;
	else
		dir = direction;

	dir = dir * -1;

	pain_angles = dir.toAngles();

	pain_angles[YAW]   = AngleNormalize180( angles[YAW] - pain_angles[YAW] );
	pain_angles[PITCH] = AngleNormalize180( angles[PITCH] - pain_angles[PITCH] );
	}

void Actor::StunEvent
	(
	Event *ev
	)

	{
	float time;

	time = ev->GetFloat( 1 );

	SetActorFlag( ACTOR_FLAG_STUNNED, true );

	stunned_end_time = level.time + time;
	}

void Actor::CheckStun
	(
	void
	)

	{
	if ( GetActorFlag( ACTOR_FLAG_STUNNED ) && stunned_end_time <= level.time )
		SetActorFlag( ACTOR_FLAG_STUNNED, false );
	}

void Actor::Dead
	(
	Event *ev
	)

	{
   Vector   min, max;

   // stop animating
   StopAnimatingAtEnd();

	edict->s.eFlags |= EF_DONT_PROCESS_COMMANDS;

	if ( !groundentity && ( velocity != vec_zero ) && ( movetype != MOVETYPE_STATIONARY ) )
		{
		// wait until we hit the ground
		PostEvent( EV_Actor_Dead, FRAMETIME );
		return;
		}

	// don't allow them to fly, think, or swim anymore
   flags &= ~( FL_THINK | FL_SWIM | FL_FLY );

   deadflag = DEAD_DEAD;
   setMoveType( MOVETYPE_NONE );
   setOrigin( origin );

	if ( trigger )
      {
		trigger->ProcessEvent( EV_Remove );
      }

	if ( spawnparent )
		PostEvent( EV_Actor_Fade, .5 );
	else	
		PostEvent( EV_Actor_Fade, 10 );
	}

void Actor::KilledEffects
   (
   Entity *attacker
   )

   {
   Entity   *ent;
   Event    *event;
	str		target_name;
   
   if ( g_debugtargets->integer )
      {
      G_DebugTargets( this, "Actor::KilledEffects" );
      }

   //
   // kill the killtargets
   //
	target_name = KillTarget();
	if ( target_name && strcmp( target_name, "" ) )
		{
      ent = NULL;
		do
			{
			ent = G_FindTarget( ent, target_name );
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
	target_name = Target();
	if ( target_name && strcmp( target_name, "" ) )
		{
      ent = NULL;
		do
			{
			ent = G_FindTarget( ent, target_name );
			if ( !ent )
				{
				break;
				}

			event = new Event( EV_Activate );
			event->AddEntity( attacker );
			ent->PostEvent( event, 0 );
			}
		while ( 1 );
		}
   //
   // see if we have a kill_thread
   //
   if ( kill_thread.length() > 1 )
      {
      ScriptThread * thread;

      //
      // create the thread, but don't start it yet
      //
      thread = ExecuteThread( kill_thread, false );
      if ( thread )
         {
         ProcessScript( thread, NULL );
         }
      else
         {
         warning( "Killed", "could not process kill_thread" );
         }
      }
   }

void Actor::Killed
   (
   Event *ev
   )

   {
   Vector   position;
	ClassDef *cls;
	str deathanim;
	str newdeathanim;
   Entity *attacker;
	float damage;


	attacker = ev->GetEntity( 1 );
	damage   = ev->GetFloat( 2 );

	if ( !GetActorFlag( ACTOR_FLAG_ALLOWED_TO_KILL ) && attacker && attacker->isSubclassOf( Player ) )
		G_MissionFailed();

	// Update boss health if necessary

	if ( GetActorFlag( ACTOR_FLAG_UPDATE_BOSS_HEALTH ) && max_boss_health )
		{
		char bosshealth_string[20];
		sprintf( bosshealth_string, "%.5f", health / max_boss_health );
		gi.cvar_set( "bosshealth", bosshealth_string );
		}

	// Add to the players action level

	if ( damage && attacker && attacker->isSubclassOf( Player ) )
		{
		Player *player = (Player *)attacker;

		player->IncreaseActionLevel( damage / 4 );
		}

   KilledEffects( attacker );

	if ( next_pain_sound_time <= level.time && !GetActorFlag( ACTOR_FLAG_NO_PAIN_SOUNDS ) )
		{
		next_pain_sound_time = level.time + 0.4 + G_Random( 0.2 );
		BroadcastSound();
		}

	if ( !GetActorFlag( ACTOR_FLAG_DIE_COMPLETELY ) )
		return;

	// See if means of death should be bumped up from MOD_BULLET to MOD_FAST_BULLET

	if ( means_of_death == MOD_BULLET )
		{
		if ( bullet_hits < 5 )
			bullet_hits = 0;

		if ( G_Random( 100 ) < bullet_hits * 10 )
			means_of_death = MOD_FAST_BULLET;
		}

	// Make sure all bones are put back in their normal positions

	if ( edict->s.bone_tag[ ACTOR_MOUTH_TAG ] != -1 )
		SetControllerAngles( ACTOR_MOUTH_TAG, vec_zero );

	if ( edict->s.bone_tag[ ACTOR_HEAD_TAG ] != -1 )
		SetControllerAngles( ACTOR_HEAD_TAG, vec_zero );

	if ( edict->s.bone_tag[ ACTOR_TORSO_TAG ] != -1 )
		SetControllerAngles( ACTOR_TORSO_TAG, vec_zero );

	// Stop behavior

	cls = getClass( "idle" );
	SetBehavior( ( Behavior * )cls->newInstance() );

	// don't allow them to fly or swim anymore
	flags &= ~( FL_SWIM | FL_FLY );

	deadflag = DEAD_DYING;

	groundentity = NULL;

	edict->svflags |= SVF_DEADMONSTER;

	if ( !GetActorFlag( ACTOR_FLAG_STAYSOLID ) )
		{
		edict->clipmask = MASK_DEADSOLID;

		if ( edict->solid != SOLID_NOT )
			setContents( CONTENTS_CORPSE );
		}

	// Stop the actor from talking

	if ( GetActorFlag( ACTOR_FLAG_DIALOG_PLAYING ) )
		{
		CancelEventsOfType( EV_SetControllerAngles );
		StopSound( CHAN_DIALOG );
		}

	// Setup the default death animation

	deathanim = "death";

	// See if this actor has a death state in its state machine

	if ( statemap )
		{
		int count = 0;
		State	*temp_state;
		State	*last_temp_state = NULL;
		str temp_anim;

		temp_state = statemap->FindState( "DEATH" );

		if ( temp_state )
			{
			do 
				{
				count++;
				if ( count > 10 )
					{
					gi.Error( ERR_DROP, "Stopping due to possible infinite state loop in death state\n" );
					break;
					}

				// Process the current state

				if ( last_temp_state != temp_state )
					{
					// Get the new animation name

					temp_anim = temp_state->getLegAnim( *this, &conditionals );

					if ( temp_anim.length() )
						newdeathanim = temp_anim;

					// Process exit commands of the last state

					if ( last_temp_state )
						last_temp_state->ProcessExitCommands( this );

					// Process the entry commands of the new state

					temp_state->ProcessEntryCommands( this );
					}

				// Determine the next state to go to

				last_temp_state = temp_state;
				temp_state = temp_state->Evaluate( *this, &conditionals );
				}
				while ( last_temp_state != temp_state );
			}

		if ( newdeathanim.length() > 0 )
			deathanim = newdeathanim;
		}

	// Play the death animation

	SetAnim( deathanim, EV_Actor_Dead );
	ChangeAnim();

	// See if we were spawned by another actor

	if ( spawnparent )
		{
		spawnparent->num_of_spawns--;
		}

	// See if we should notify others

	if ( GetActorFlag( ACTOR_FLAG_NOTIFY_OTHERS_AT_DEATH ) )
		NotifyOthersOfDeath();

	SpawnItems();

	if ( means_of_death == MOD_GIB )
		{
		Event *event;
		int i;

		if ( blood_model.length() == 0 )
			blood_model = "fx_bspurt.tik";

		if ( max_gibs == 0 )
			max_gibs = 4;

		for( i = 0 ; i < 4 ; i++ )
			{
			event = new Event( EV_Sentient_SpawnBloodyGibs );
			event->AddInteger( max_gibs );
			ProcessEvent( event );
			}

		PostEvent( EV_Remove, 0 );
		}
   }

void Actor::SetDieCompletely
	(
	Event *ev
	)
	{
	SetActorFlag( ACTOR_FLAG_DIE_COMPLETELY, ev->GetBoolean( 1 ) );
	}

void Actor::SetBleedAfterDeath
	(
	Event *ev
	)
	{
	SetActorFlag( ACTOR_FLAG_BLEED_AFTER_DEATH, ev->GetBoolean( 1 ) );
	}

void Actor::SpawnGib
	(
	Event *ev
	)
	{
	RealSpawnGib( false, ev );
	}

void Actor::SpawnGibAtTag
	(
	Event *ev
	)
	{
	RealSpawnGib( true, ev );
	}

void Actor::RealSpawnGib
	(
	qboolean use_tag,
	Event *ev
	)
	{
	str tag_name;
	Gib *gib;
	Mover *ent = NULL;
	Vector final_gib_offset;
	Vector orig;
	Vector dir;
	int current_arg;
	float final_pitch;
	float vel;
	trace_t trace;
	float time;
	float pitch_change;
	float pitch_vel;
	str attach_tag_name;
	Vector offset;
	str cap_name;
	float width;
	const char *current_arg_str;
	int current_surface;
	const char *current_surface_name;
	qboolean use_blood;
	str blood_name;
	str blood_splat_name;
	str blood_model_name;
	float blood_splat_size;
	Vector gib_mins;
	Vector gib_maxs;
	float m;
	qboolean at_least_one_visible_surface = false;
	int surface_length;
	int tagnum;
	orientation_t or;
	float raw_offset;
	Vector raw_offset_dir;
	Vector real_tag_pos;
	Vector real_tag_dir;
	Vector real_tag_angles;


	SetActorFlag( ACTOR_FLAG_SPAWN_FAILED, true );

	if ( !com_blood->integer )
		return;

	if ( GetActorFlag( ACTOR_FLAG_FADING_OUT ) )
		return;

	if ( ev->NumArgs() < 5 )
		return;

	if ( use_tag )
		{
		attach_tag_name = ev->GetString( 1 );
		raw_offset      = ev->GetFloat( 2 );
		width           = ev->GetFloat( 3 );

		// Get all the tag information

		tagnum = gi.Tag_NumForName( edict->s.modelindex, attach_tag_name.c_str() );

		if ( tagnum == -1 )
			return;

		GetRawTag( tagnum, &or );
		GetTag( tagnum, &real_tag_pos, &real_tag_dir );

		real_tag_angles = real_tag_dir.toAngles();

		// Determine the final pitch of the gib

		final_pitch = AngleNormalize180( angles[PITCH] - real_tag_angles[PITCH] );

		// Determine the offset of the gib

		raw_offset_dir = or.axis[0];

		offset = or.origin;
		offset += raw_offset * raw_offset_dir;
		MatrixTransformVector( offset, orientation, orig );
		orig += origin;
		}
	else
		{
		offset      = ev->GetVector( 1 );
		final_pitch = ev->GetFloat( 2 );
		width       = ev->GetFloat( 3 );

		MatrixTransformVector( offset, orientation, orig );
		orig += origin;
		}

	// Determine the mass

	m = mass;

	if ( m < 50 )
		m = 50;
	else if ( m > 250 )
		m = 250;

	// Determine which blood spurt & splat to use for the gib

	blood_name       = GetBloodSpurtName();
	blood_splat_name = GetBloodSplatName();
	blood_splat_size = GetBloodSplatSize();

	if ( blood_name.length() && blood_splat_name.length() )
		use_blood = true;
	else
		use_blood = false;

	if ( GetActorFlag( ACTOR_FLAG_BLEED_AFTER_DEATH ) )
		blood_model_name = blood_model;

	// Get the mins and maxs for this gib

	gib_mins = Vector( -width, -width, -width );
	gib_maxs = Vector(  width,  width,  width );

	// Make sure we can spawn in a gib here

	trace = G_Trace( orig, gib_mins, gib_maxs, orig, NULL, MASK_DEADSOLID, false, "spawngib" );

	if ( trace.allsolid || trace.startsolid )
		return;

	// Make sure at least one of the surfaces is not hidden

	for( current_arg = 5 ; current_arg <= ev->NumArgs() ; current_arg++ )
		{
		current_arg_str = ev->GetString( current_arg );

		for( current_surface = 0 ; current_surface < numsurfaces ; current_surface++ )
			{	
			current_surface_name = gi.Surface_NumToName( edict->s.modelindex, current_surface );

			if ( current_arg_str[ strlen( current_arg_str ) - 1 ] == '*' )
				surface_length = strlen( current_arg_str ) - 1;
			else
				surface_length = strlen( current_arg_str );

			if ( Q_stricmpn( current_surface_name, current_arg_str, surface_length ) == 0 )
				{
				if ( !( edict->s.surfaces[ current_surface ] & MDL_SURFACE_NODRAW ) )
					at_least_one_visible_surface = true;
				}
			}
		}

	if ( !at_least_one_visible_surface )
		return;

	// Determine time till it hits the ground

	vel = 100 + G_Random( 200 * ( 2 - ( (m - 50) / 200) ) );

	time = SpawnGetTime( vel , orig, gib_mins, gib_maxs );

	// Flip final pitch 180 degrees?

	if ( G_Random() > .5 )
		{
		final_pitch += 180;
		final_pitch = AngleNormalize360( final_pitch );
		}

	// Calculate the pitch change and velocity

	pitch_change = AngleNormalize180( final_pitch - angles[PITCH] );
	pitch_vel = pitch_change / time;

	// Spawn in the hidden gib

	gib = new Gib( "", use_blood, blood_name, blood_model_name, blood_splat_name, blood_splat_size, final_pitch );

	gib->setOrigin( orig );

	gib->angles[PITCH] = angles[PITCH];
	gib->angles[ROLL]  = 0;

	if ( use_tag )
		gib->angles[YAW]   = real_tag_angles[YAW];
	else
		gib->angles[YAW]   = angles[YAW];

	gib->setAngles( gib->angles );

	gib->velocity  = Vector( G_CRandom( 150 * ( 2 - ( (m - 50) / 200) ) ), G_CRandom( 150 * ( 2 - ( (m - 50) / 200) ) ), vel );
	gib->avelocity = Vector( pitch_vel, G_CRandom( 300 ), 0 );
	
	gib->setSize( gib_mins, gib_maxs );

	gib->edict->svflags |= SVF_DEADMONSTER;
	gib->edict->clipmask = MASK_DEADSOLID;

	gib->setSolidType( SOLID_BBOX );
	gib->setContents( CONTENTS_SHOOTABLE_ONLY );
	gib->link();

	// Spawn in the visible gib

	ent = new Mover;
	ent->setModel( model );

	// Make sure the init stuff in the tiki get processed now

	//ent->ProcessPendingEvents();
	ent->CancelPendingEvents();

	// Make sure no cleint side commands are processed

	ent->edict->s.eFlags |= EF_DONT_PROCESS_COMMANDS;

	// Set the animation to the current anim & frame of the actor

	ent->RandomAnimate( AnimName() );
	ent->SetFrame( CurrentFrame() );

	ent->setAngles( angles );
	ent->bind( gib, true );
	ent->gravity = 0;

	final_gib_offset = offset * -1;
	ent->setOrigin( final_gib_offset );

	ent->setMoveType( MOVETYPE_BOUNCE );
	ent->setSolidType( SOLID_NOT );
	ent->showModel();

	// Hide all of the surfaces on the gib

	ent->SurfaceCommand( "all", "+nodraw" );

	cap_name = ev->GetString( 4 );

	// Show the cap surface on the gib and the actor 

	if ( cap_name.length() )
		{
		ent->SurfaceCommand( cap_name.c_str(), "-nodraw" );

		SurfaceCommand( cap_name.c_str(), "-nodraw" );
		}

	// Show and hide all of the rest of the necessary surfaces

	for ( current_arg = 5 ; current_arg <= ev->NumArgs() ; current_arg++ )
		{
		current_arg_str = ev->GetString( current_arg );

		if ( current_arg_str[ strlen( current_arg_str ) - 1 ] == '*' )
			surface_length = strlen( current_arg_str ) - 1;
		else
			surface_length = strlen( current_arg_str );

		for( current_surface = 0 ; current_surface < numsurfaces ; current_surface++ )
			{	
			current_surface_name = gi.Surface_NumToName( edict->s.modelindex, current_surface );

			if ( Q_stricmpn( current_surface_name, current_arg_str, surface_length ) == 0 )
				{
				if ( !( edict->s.surfaces[ current_surface ] & MDL_SURFACE_NODRAW ) )
					{
					// Show this surface on the gib
					ent->SurfaceCommand( current_surface_name, "-nodraw" );

					// Hide this surface on the actor
					SurfaceCommand( current_surface_name, "+nodraw" );
					}
				}
			}
		}

	// Make sure the gibs go away after a while

	if ( GetActorFlag( ACTOR_FLAG_DEATHFADE ) )
		{
		ent->PostEvent( EV_Fade, 10 );
		gib->PostEvent( EV_Fade, 10.5 );
		}
	else if ( GetActorFlag( ACTOR_FLAG_DEATHSHRINK ) )
		{
		ent->PostEvent( EV_FadeOut, 10 );
		gib->PostEvent( EV_FadeOut, 10.5 );
		}
	else
		{
		ent->PostEvent( EV_Unbind, 10 );
		ent->PostEvent( EV_DeathSinkStart, 12 );
		gib->PostEvent( EV_Remove, 10.5 );
		}

	// Mark the spawn as being successful

	SetActorFlag( ACTOR_FLAG_SPAWN_FAILED, false );

	// Play the severed sound

	ent->Sound( "impact_sever", CHAN_BODY );
	}

void Actor::SpawnNamedGib
	(
	Event *ev
	)
	{
	str gib_name;
	str tag_name;
	Gib *gib;
	Vector orig;
	float final_pitch;
	float vel;
	trace_t trace;
	float time;
	float pitch_change;
	float pitch_vel;
	float width;
	Vector gib_mins;
	Vector gib_maxs;


	SetActorFlag( ACTOR_FLAG_SPAWN_FAILED, true );

	if ( !com_blood->integer )
		return;

	if ( GetActorFlag( ACTOR_FLAG_FADING_OUT ) )
		return;

	// Get all of the parameters

	gib_name      = ev->GetString( 1 );
	tag_name      = ev->GetString( 2 );
	final_pitch   = ev->GetFloat( 3 );
	width         = ev->GetFloat( 4 );

	// Get the tag position

	GetTag( tag_name, &orig );

	// Get the mins and maxs for this gib

	gib_mins = Vector( -width, -width, -width );
	gib_maxs = Vector(  width,  width,  width );

	// Make sure we can spawn in a gib here
	
	trace = G_Trace( orig, gib_mins, gib_maxs, orig, NULL, MASK_DEADSOLID, false, "spawnnamedgib1" );

	if ( trace.allsolid || trace.startsolid )
		SetActorFlag( ACTOR_FLAG_SPAWN_FAILED, true );     

	// Determine time till it hits the ground

	vel = 200 + G_Random( 200 );

	time = SpawnGetTime( vel , orig, gib_mins, gib_maxs );

	pitch_change = AngleNormalize180( final_pitch - angles[PITCH] );
	pitch_vel    = pitch_change / time;

	// Spawn the gib

	gib = new Gib( gib_name, false, "", "", "", final_pitch );

	gib->setOrigin( orig );
	gib->setAngles( angles );

	gib->velocity  = Vector( G_CRandom( 100 ), G_CRandom( 100 ), vel );
   gib->avelocity = Vector( pitch_vel, G_CRandom( 300 ), 0 );

	gib->edict->svflags |= SVF_DEADMONSTER;
	gib->edict->clipmask = MASK_DEADSOLID;

	gib->setSolidType( SOLID_BBOX );
   gib->setContents( CONTENTS_CORPSE );

	// Make sure the gib goes away after a while

	if ( GetActorFlag( ACTOR_FLAG_DEATHFADE ) )
		gib->PostEvent( EV_Fade, 10 );
	else if ( GetActorFlag( ACTOR_FLAG_DEATHSHRINK ) )
		gib->PostEvent( EV_FadeOut, 10 );
	else
		gib->PostEvent( EV_DeathSinkStart, 10 );

	// Mark the spawn as being successful

	SetActorFlag( ACTOR_FLAG_SPAWN_FAILED, false );
	}

float Actor::SpawnGetTime( float vel, Vector orig, Vector gib_mins, Vector gib_maxs )
	{
	float grav;
	Vector end_pos;
	Vector dir;
	float time;
	float other;
	trace_t trace;
	float dist;

	grav = -sv_gravity->value;

	end_pos = orig;
	end_pos[2] = -10000;

	trace = G_Trace( orig, gib_mins, gib_maxs, end_pos, NULL, MASK_DEADSOLID, false, "SpawnGetTime" );

	end_pos = trace.endpos;

	dir = end_pos - orig;
	dist = dir.length();

	time = ( (grav / -20) - vel ) / grav;

	other = sqrt( (grav / 20 + vel) * (grav / 20 + vel) - (2 * grav * dist) );

	time = time - other / grav;

	return time;
	}

void Actor::SpawnBlood
	(
	Event *ev
	)
	{
	str blood_name;
	str tag_name;
	qboolean use_last_result = false;
	Event *attach_event;


	if ( !com_blood->integer )
		return;

	blood_name = ev->GetString( 1 );
	tag_name   = ev->GetString( 2 );

	// See if we care about the last spawn working or not

	if ( ev->NumArgs() > 2 )
		use_last_result = ev->GetBoolean( 3 );

	if ( use_last_result && GetActorFlag( ACTOR_FLAG_SPAWN_FAILED ) )
		return;

	// Spawn the blood

	attach_event = (Event *)new Event( EV_AttachModel );

	attach_event->AddString( blood_name );
	attach_event->AddString( tag_name );
	attach_event->AddInteger( 1 );
	attach_event->AddString( "" );
	attach_event->AddInteger( 0 );
	attach_event->AddInteger( 5 );
	PostEvent( attach_event, 0 );
	}

void Actor::RemoveUselessBody
   (
   Event *ev
   )

   {
   /* if ( trig )
   	{
      trig->PostEvent( EV_Remove, 0 );
		trig = NULL;
      } */

   CancelEventsOfType( EV_Sentient_UselessCheck );
   PostEvent( EV_FadeOut, 5);
   }

void Actor::SetPainThresholdEvent
   (
   Event *ev
   )

   {
   //pain_threshold = ( ev->GetFloat( 1 ) ) * skill->value * 0.66f;
	pain_threshold = ( ev->GetFloat( 1 ) );
   }

void Actor::SetKillThreadEvent
   (
   Event *ev
   )

   {
   kill_thread = ev->GetString( 1 );
   }

void Actor::DeathFadeEvent
	(
	Event *ev
	)

	{
	SetActorFlag( ACTOR_FLAG_DEATHFADE, true );
	}

void Actor::DeathShrinkEvent
	(
	Event *ev
	)

	{
	SetActorFlag( ACTOR_FLAG_DEATHSHRINK, true );
	}

void Actor::DeathSinkEvent
	(
	Event *ev
	)

	{
	SetActorFlag( ACTOR_FLAG_DEATHSINK, true );
	}

void Actor::StaySolidEvent
	(
	Event *ev
	)

	{
	SetActorFlag( ACTOR_FLAG_STAYSOLID, true );
	}

void Actor::Suicide
   (
   Event *ev
   )

	{
	Event *event;
	qboolean use_last_mod;

	health = 0;

	if ( ev->NumArgs() > 0 )
		use_last_mod = ev->GetBoolean( 1 );
	else
		use_last_mod = false;

	if ( !use_last_mod )
		means_of_death = MOD_SUICIDE;

	event = new Event( EV_Killed );
	event->AddEntity( this );
	event->AddInteger( 0 );
	event->AddEntity( this );
	event->AddInteger( MOD_SUICIDE );
	ProcessEvent( event );
	}

void Actor::SetDeathSize
	(
	Event *ev
	)

	{
   Vector death_min;
	Vector death_max;
	trace_t trace;

	death_min = ev->GetVector( 1 );
	death_max = ev->GetVector( 2 );

	// Make sure actor will not be stuck if we change the bounding box

	trace = G_Trace( origin, death_min, death_max, origin, this, edict->clipmask, false, "Actor::SetDeathSize" );

	if ( !trace.startsolid )
		{
		setSize( death_min, death_max );
		return;
		}

	// Try again, calculate a smaller death bounding box

	death_min = (death_min + mins) * .5;
	death_max = (death_max + maxs) * .5;

	trace = G_Trace( origin, death_min, death_max, origin, this, edict->clipmask, false, "Actor::SetDeathSize2" );

	if ( !trace.startsolid )
		setSize( death_min, death_max );
	}

void Actor::FadeEvent
	(
	Event *ev
	)
	{
	SetActorFlag( ACTOR_FLAG_FADING_OUT, true );

	if ( GetActorFlag( ACTOR_FLAG_DEATHFADE ) )
		ProcessEvent( EV_Fade );
	else if ( GetActorFlag( ACTOR_FLAG_DEATHSHRINK ) )
      ProcessEvent( EV_FadeOut );
	else if ( GetActorFlag( ACTOR_FLAG_DEATHSINK ) )
		ProcessEvent( EV_DeathSinkStart );
	else
		SetActorFlag( ACTOR_FLAG_FADING_OUT, false );
	}

//***********************************************************************************************
//
// Movement functions
//
//***********************************************************************************************

void Actor::SimplePathfinding
   (
   Event *ev
   )
	{
	SetActorFlag( ACTOR_FLAG_SIMPLE_PATHFINDING, true );
	}

void Actor::SetCanWalkOnOthers
   (
   Event *ev
   )

   {
   SetActorFlag( ACTOR_FLAG_CAN_WALK_ON_OTHERS, true );
   }

void Actor::SetFeetWidth
   (
   Event *ev
   )

   {
   feet_width = ev->GetFloat( 1 );
   }

void Actor::ForwardSpeedEvent
   (
   Event *ev
   )

   {
   forwardspeed = ev->GetFloat( 1 );
   }

void Actor::SwimEvent
   (
   Event *ev
   )

   {
   flags &= ~FL_FLY;
   flags |= FL_SWIM;
   }

void Actor::FlyEvent
   (
   Event *ev
   )

   {
	if ( ev->NumArgs() == 0 )
		{
		// Turn flying on
		flags &= ~FL_SWIM;
		flags |= FL_FLY;
		}
	else
		{
		if ( ev->GetBoolean( 1 ) )
			{
			// Turn flying on
			flags &= ~FL_SWIM;
			flags |= FL_FLY;
			}
		else
			{
			// Turn flying off
			flags &= ~FL_FLY;
			}
		}
   }

void Actor::NotLandEvent
   (
   Event *ev
   )

   {
   flags &= FL_SWIM | FL_FLY;
   }

qboolean Actor::CanMoveTo
	(
	Vector pos
	)

	{
	Vector	min;
	trace_t	trace;
	Vector	start;
	Vector	end;
	Vector	s;

	s = Vector( 0, 0, STEPSIZE );
   start = origin + s;
	end = pos + s;
	trace = G_Trace( start, mins, maxs, end, this, edict->clipmask, false, "Actor::CanMoveTo" );
	if ( trace.fraction == 1 )
		{
		return true;
		}
	return false;
	}

qboolean Actor::CanWalkTo
	(
	Vector pos,
	int entnum
	)

	{
	trace_t	trace;
	Vector	dir;
	float		length;
	float		i;
	float		j;
	Vector	bottom;
	Vector	current_loc;
	Vector	last_loc;
	float		trace_step;
	float		small_trace_step;
	float		last_height;
	Vector	real_pos;


	// Calculate the real position we have to get to

	if ( entnum != ENTITYNUM_NONE )
		{
		Vector temp_dir;
		float temp_length;

		temp_dir = pos - origin;
		temp_length = temp_dir.length();

		temp_length -= sqrt( maxs.x * maxs.x * 2 ) + 5;

		if ( temp_length < 0 )
			temp_length = 0;

		temp_dir.normalize();
		temp_dir *= temp_length;

		real_pos = origin + temp_dir;
		}
	else
		{
		real_pos = pos;
		}


	// Do simple CanWalkTo if specified

	if ( GetActorFlag( ACTOR_FLAG_SIMPLE_PATHFINDING ) )
		{
		current_loc    = origin;
		current_loc[2] += STEPSIZE;
		last_loc    = real_pos;
		last_loc[2] += STEPSIZE;
		trace = G_Trace( current_loc, mins, maxs, last_loc, this, MASK_PATHSOLID, false, "Actor::CanWalkTo_Simple" );

		if ( trace.fraction == 1 )
			return true;
		else
			return false;
		}

	// Find the vector to walk

 	dir = real_pos - origin;
	length = dir.length();
	dir.normalize();

	// Find the step amount

	trace_step = maxs[0] * 2;

	// Make sure trace_step is divisible by 8

	trace_step = ( (int)(trace_step / 8 ) ) * 8;

	if ( trace_step < 8 )
		trace_step = 8;

	small_trace_step = 8;

	// Test each step to see if the ground is not too far below

	last_height = origin[2];

	for( i = 0 ; i < length ; i += trace_step )
		{
		last_loc = current_loc;

		current_loc    = origin + dir * i;
		current_loc[2] = last_height + STEPSIZE;

		bottom    = current_loc;

		if ( !GetActorFlag( ACTOR_FLAG_ALLOW_FALL ) )
			bottom[2] = last_height - STEPSIZE;
		else
			bottom[2] = last_height - 1000;

		trace = G_Trace( current_loc, mins, maxs, bottom, this, MASK_PATHSOLID, false, "Actor::CanWalkTo1" );

		if ( !( trace.fraction == 1 || trace.startsolid || trace.allsolid ) && feet_width )
			{
			Vector temp_mins;
			Vector temp_maxs;
			Vector saved_endpos;

			saved_endpos = trace.endpos;

			temp_mins[0] = -feet_width;
			temp_mins[1] = -feet_width;
			temp_mins[2] = mins[2];

			temp_maxs[0] = feet_width;
			temp_maxs[1] = feet_width;
			temp_maxs[2] = maxs[2];

			trace = G_Trace( current_loc, temp_mins, temp_maxs, bottom, this, MASK_PATHSOLID, false, "Actor::CanWalkTo2" );

			saved_endpos.copyTo( trace.endpos );
			}

		if ( trace.fraction == 1 || trace.startsolid || trace.allsolid )
			{
			// The wide one failed, do the small traces for this segment

			if ( i == 0 || trace_step == small_trace_step )
				return false;

			for( j = small_trace_step ; j <= trace_step ; j += small_trace_step )
				{
				current_loc    = last_loc + dir * j;
				current_loc[2] = last_height + STEPSIZE;

				bottom    = current_loc;
				bottom[2] = last_height - STEPSIZE;

				trace = G_Trace( current_loc, mins, maxs, bottom, this, MASK_PATHSOLID, false, "Actor::CanWalkTo3" );

				if ( trace.fraction == 1 || trace.startsolid || trace.allsolid || 
					  ( trace.ent && trace.ent->entity->isSubclassOf( Sentient ) && !GetActorFlag( ACTOR_FLAG_CAN_WALK_ON_OTHERS ) ) )
					return false;

				if ( feet_width )
					{
					Vector temp_mins;
					Vector temp_maxs;
					Vector saved_endpos;

					saved_endpos = trace.endpos;

					temp_mins[0] = -feet_width;
					temp_mins[1] = -feet_width;
					temp_mins[2] = mins[2];

					temp_maxs[0] = feet_width;
					temp_maxs[1] = feet_width;
					temp_maxs[2] = maxs[2];

					trace = G_Trace( current_loc, temp_mins, temp_maxs, bottom, this, MASK_PATHSOLID, false, "Actor::CanWalkTo4" );

					saved_endpos.copyTo( trace.endpos );
					}

				last_height = trace.endpos[2];
				}
			}

		last_height = trace.endpos[2];
		}

	if ( last_height > pos.z + STEPSIZE * 2 || last_height < pos.z - STEPSIZE * 2 )
		return false;

	return true;
	}

void Actor::CheckWater
	(
   void
	)
   {
   Vector sample[3];
   int cont;

   //
   // get waterlevel and type
   //
	waterlevel = 0;
	watertype = 0;

   sample[ 0 ] = origin;
   sample[ 2 ] = EyePosition();
   sample[ 1 ] = ( sample[ 0 ] + sample[ 2 ] ) * 0.5f;

	cont = gi.pointcontents( sample[ 0 ], 0 );

	if (cont & MASK_WATER)
	   {
		watertype = cont;
		waterlevel = 1;
   	cont = gi.pointcontents( sample[ 2 ], 0 );
		if (cont & MASK_WATER)
		   {
			waterlevel = 3;
         }
      else
         {
   	   cont = gi.pointcontents( sample[ 1 ], 0 );
		   if (cont & MASK_WATER)
		      {
			   waterlevel = 2;
            }
         }
		}
	}

#define MAX_PITCH 75

void Actor::Accelerate
	(
	Vector steering
	)

	{
	// limit the actor's turnrate

   if ( steering.y > turnspeed )
      steering.y = turnspeed;
   else if ( steering.y < -turnspeed )
      steering.y = -turnspeed;

	angles.y += steering.y;

   if ( frame_delta.x > 4 )
      {
	   // make him lean into the turn a bit
	   angles.z = movespeed * ( 0.4f / 320.0f ) * steering.y;

      if ( ( flags & FL_FLY ) || ( ( flags & FL_SWIM ) && waterlevel > 0 ) )
         {
         angles.z = bound( angles.z, -2, 2 );
         }
      else
         {
         angles.z = bound( angles.z, -5, 5 );
         }
      }
   else
      {
      angles.z = 0;
      }

#if 0
   if ( ( flags & FL_FLY ) || ( ( flags & FL_SWIM ) && waterlevel > 0 ) )
		{
      //angles.x = bound( angles.x, -MAX_PITCH, MAX_PITCH );
		}
#endif

   setAngles( angles );
	}

void Actor::CalcMove
	(
	void
	)

	{
   if ( total_delta != vec_zero )
		{
		MatrixTransformVector( total_delta, orientation, move );
		total_delta = vec_zero;
		}
	else
		{
		move = vec_zero;
		}

   // force movement if forwardspeed is set
   if ( forwardspeed )
      {
      if ( move == vec_zero )
         {
         move = orientation[ 0 ];
         }
      else
         {
         move.normalize();
         }

		animdir = move;
      movedir = move;
		movespeed = forwardspeed;
      move *= movespeed * FRAMETIME;
		totallen = forwardspeed;
		movevelocity = movedir * movespeed;
      }
   }

void Actor::setAngles
	(
	Vector ang
	)

	{
	Sentient::setAngles( ang );
	MatrixTransformVector( animdir, orientation, movedir );
	movevelocity = movedir * movespeed;
	}

stepmoveresult_t Actor::WaterMove
   (
   void
   )

   {
	Vector	oldorg;
	Vector	neworg;
	trace_t	trace;
   int      oldwater;

	if ( ( totallen <= 0.01f ) || ( move == vec_zero ) )
		{
		return STEPMOVE_OK;
		}

	// try the move
   oldorg = origin;
   neworg = origin + move;

	trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, false, "Actor::WaterMove 1" );
	if ( trace.fraction == 0 )
		{
		return STEPMOVE_STUCK;
		}

   oldwater = waterlevel;

   setOrigin( trace.endpos );

   CheckWater();

	// swim monsters don't exit water voluntarily
	if ( ( oldwater > 1 ) && ( waterlevel < 2 ) )
	   {
      waterlevel = oldwater;
      setOrigin( oldorg );
      return STEPMOVE_STUCK;
   	}

	return STEPMOVE_OK;
   }

stepmoveresult_t Actor::AirMove
   (
   void
   )

   {
	Vector	oldorg;
	Vector	neworg;
	trace_t	trace;
   int      oldwater;

	if ( ( totallen <= 0.01f ) || ( move == vec_zero ) )
		{
		return STEPMOVE_OK;
		}

	// try the move
   oldorg = origin;
   neworg = origin + move;

	trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, false, "Actor::AirMove 1" );
	if ( trace.fraction < 0.0001 )
		{
		return STEPMOVE_BLOCKED_BY_WATER;
		}

   oldwater = waterlevel;

   setOrigin( trace.endpos );

	if ( !GetActorFlag( ACTOR_FLAG_IGNORE_WATER ) )
		{
		CheckWater();

		// fly monsters don't enter water voluntarily
		if ( !oldwater && waterlevel )
			{
			waterlevel = oldwater;
			setOrigin( oldorg );
			return STEPMOVE_STUCK;
			}
		}

	return STEPMOVE_OK;
   }

stepmoveresult_t Actor::TryMove
	(
	void
	)

	{
	Vector	oldorg;
	Vector	neworg;
	Vector	end;
	trace_t	trace;
   Door     *door;
   static   Vector step( 0, 0, STEPSIZE );
	qboolean	allow_fall;


	// See if we should bother doing any movement

	if ( velocity != vec_zero  && !deadflag )
		{
		// We have a velocity so movement of the actor is done in physics
		return STEPMOVE_OK;
		}

	if ( ( totallen <= 0.01f ) || ( move == vec_zero ) )
		{
		return STEPMOVE_OK;
		}

   // Try to make the move

	oldorg = origin + step;
   neworg = oldorg + move;
	trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, false, "Actor::TryMove 1" );

	if ( trace.startsolid )
		{
		oldorg = origin;
		neworg = oldorg + move;
		trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, false, "Actor::TryMove 1.5" );
		}

	if ( trace.startsolid || ( trace.fraction < 0.0001f ) )
      {
		return STEPMOVE_STUCK;
      }

   // If we hit an entity, check what it is

   if ( !deadflag && trace.ent )
      {
      // Check if we hit a door

	   if ( trace.ent->entity->isSubclassOf( Door ) )
		   {
		   door = ( Door * )trace.ent->entity;
		   if ( !door->locked && !door->isOpen() )
			   {
			   return STEPMOVE_BLOCKED_BY_DOOR;
			   }
		   }
      }

	// Don't step down an extra step if gravity is turned off for this actor right now or the actor is dead

	if ( !GetActorFlag( ACTOR_FLAG_USE_GRAVITY ) || deadflag )
		{
      // try stepping down
      oldorg = trace.endpos;
      neworg = oldorg - step;
	   trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, false, "Actor::TryMove 2" );

		if ( trace.startsolid )
			{
			return STEPMOVE_STUCK;
         }

		setOrigin( trace.endpos );

      return STEPMOVE_OK;
		}

	// Step down to a step height below our original height to account for gravity

   oldorg = trace.endpos;
   neworg = oldorg - step * 2;
	trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, false, "Actor::TryMove 3" );

	// Determine if we should allow the actor to fall

	if ( ( flags & FL_PARTIALGROUND ) || 
      ( groundentity && groundentity->entity && ( groundentity->entity->isSubclassOf( Sentient ) ) ) ||
		( GetActorFlag( ACTOR_FLAG_ALLOW_FALL ) ) )
		allow_fall = true;
	else
		allow_fall = false;

   // Don't voluntarily step on flying monsters

   if ( trace.ent && trace.ent->entity->flags & FL_FLY && !allow_fall )
		return STEPMOVE_BLOCKED_BY_FALL;

	// Don't voluntarilty step on sentients

	if ( trace.ent && trace.ent->entity->isSubclassOf( Sentient ) && 
		  !allow_fall && !GetActorFlag( ACTOR_FLAG_CAN_WALK_ON_OTHERS ) )
		return STEPMOVE_BLOCKED_BY_FALL;

   // Check if the move places us on solid ground

	if ( trace.fraction == 1  )
		{
		if ( allow_fall )
			{
			// don't let guys get stuck standing on other guys
			// if monster had the ground pulled out, go ahead and fall
			groundentity = NULL;
			}
		else
			{
			// walked off an edge
			return STEPMOVE_BLOCKED_BY_FALL;
			}
		}

	// Make sure ground is not too slopped or we will just slide off

	if ( trace.plane.normal[ 2 ] <= 0.7 && !allow_fall )
		return STEPMOVE_BLOCKED_BY_FALL;

	// If the feet width is set make sure the actor's feet are really on the ground

	if ( feet_width )
		{
		Vector temp_mins;
		Vector temp_maxs;
		Vector saved_endpos;

		saved_endpos = trace.endpos;

		temp_mins[0] = -feet_width;
		temp_mins[1] = -feet_width;
		temp_mins[2] = mins[2];

		temp_maxs[0] = feet_width;
		temp_maxs[1] = feet_width;
		temp_maxs[2] = maxs[2];

		oldorg = trace.endpos;
		neworg = oldorg - step * 3;
		trace = G_Trace( oldorg, temp_mins, temp_maxs, neworg, this, edict->clipmask, false, "Actor::TryMove 4" );

		// Don't voluntarilty step on sentients

		if ( trace.ent && trace.ent->entity->isSubclassOf( Sentient ) && 
			  !allow_fall && !GetActorFlag( ACTOR_FLAG_CAN_WALK_ON_OTHERS ) )
			return STEPMOVE_BLOCKED_BY_FALL;

		if ( trace.fraction == 1 && !allow_fall )
			return STEPMOVE_BLOCKED_BY_FALL;

		saved_endpos.copyTo( trace.endpos );
		}

	// The move is ok

   setOrigin( trace.endpos );

	// Save the ground information now so we don't have to do it later

	if ( trace.fraction < 1 )
		{
		groundentity = trace.ent;
		groundplane = trace.plane;
		groundcontents = trace.contents;
		last_origin = origin;
		SetActorFlag( ACTOR_FLAG_HAVE_MOVED, true );
		}

   flags &= ~FL_PARTIALGROUND;  // set in Actor::Think

   CheckWater();

	return STEPMOVE_OK;
	}

void Actor::Push
	(
	Event *ev
	)
	{
	Push( ev->GetVector( 1 ) );
	}

qboolean Actor::Push
	(
	Vector dir
	)
	{
	Vector oldorg;
	Vector neworg;
	static   Vector step( 0, 0, STEPSIZE );
	trace_t trace;
	int i;


	if ( !GetActorFlag( ACTOR_FLAG_PUSHABLE ) )
		return false;

	for( i = 0 ; i < 5 ; i++ )
		{
		oldorg = origin + step;
		neworg = oldorg + dir;

		trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, false, "Actor::Push 1" );

		if ( trace.startsolid )
			{
			oldorg = origin;
			neworg = oldorg + dir;

			trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, false, "Actor::Push 2" );

			if ( trace.startsolid )
				return false;
			}

		if ( trace.ent && trace.ent->entity->isSubclassOf( Actor ) )
			{
			Actor *act = (Actor *) trace.ent->entity;
			act->Push( dir );
			continue;
			}
		else
			break;
		}

	if ( trace.endpos == oldorg )
		return false;

	// Step down to a step height below our original height to account for gravity

   oldorg = trace.endpos;

	if ( flags & FL_FLY )
		neworg = oldorg - step;
	else
		neworg = oldorg - step * 2;

	trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, false, "Actor::Push 3" );

	setOrigin( trace.endpos );

	return true;
	}

void Actor::Pushable
	(
	Event *ev
	)
	{
	SetActorFlag( ACTOR_FLAG_PUSHABLE, true );
	}

float Actor::JumpTo
   (
   Vector targ,
   float speed
   )
   {
   float		traveltime;
   float		vertical_speed;
   Vector	target;
	Vector	dir;
   Vector	xydir;

   CheckWater();
   //
   // if we got a jump, go into that mode
   //
   traveltime = 0;
   if ( speed <= 0 )
      {
      speed = movespeed * 1.5f;
      if ( speed < (400 * gravity) )
         speed = (400 * gravity);
      }

   target = targ;
   dir = target - origin;
   xydir = dir;
   xydir.z = 0;
   setAngles( xydir.toAngles() );
   traveltime = xydir.length() / speed;
   //
   // we add 16 to allow for a little bit higher
   //
   if ( waterlevel > 2 )
      {
      vertical_speed = ( ( dir.z + 16 ) / traveltime ) + ( 0.5f * gravity * 60 * traveltime );
      }
   else
      {
      vertical_speed = ( ( dir.z + 16 ) / traveltime ) + ( 0.5f * gravity * sv_gravity->value * traveltime );
      }

	if ( vertical_speed < 200 )
		vertical_speed = 200;

   xydir.normalize();

   velocity = speed * xydir;
   velocity.z = vertical_speed;

	groundentity = NULL;

   return traveltime;
   }

float Actor::JumpTo
   (
   PathNode *goal,
   float speed
   )
   {
   if ( goal )
      return JumpTo( goal->origin, speed );
   else
      return 0;
   }

float Actor::JumpTo
   (
   Entity *goal,
   float speed
   )
   {
   if ( goal )
      return JumpTo( goal->origin, speed );
   else
      return 0;
   }

//***********************************************************************************************
//
// Debug functions
//
//***********************************************************************************************

void Actor::ShowInfo
   (
   void
   )

   {
   gi.Printf( "\nEntity #   : %d\n", entnum );
   gi.Printf( "Class ID   : %s\n", getClassID() );
   gi.Printf( "Classname  : %s\n", getClassname() );
	gi.Printf( "Name       : %s\n", name.c_str() );

	if ( part_name.length() > 0 )
		gi.Printf( "Part name  : %s\n", part_name.c_str() );


	gi.Printf( "\n" );

   gi.Printf( "Targetname : %s\n", TargetName() );
   gi.Printf( "Origin     : ( %f, %f, %f )\n", origin.x, origin.y, origin.z );
   gi.Printf( "Bounds     : Mins( %.2f, %.2f, %.2f ) Maxs( %.2f, %.2f, %.2f )\n", mins.x, mins.y, mins.z, maxs.x, maxs.y, maxs.z );

	gi.Printf( "\n" );

   if ( behavior )
      gi.Printf( "Behavior   : %s\n", behavior->getClassname() );
   else
      gi.Printf( "Behavior   : NULL -- was '%s'\n", currentBehavior.c_str() );

	if ( currentState )
      gi.Printf( "State   : %s\n", currentState->getName() );
	else
		gi.Printf( "State   : NONE\n" );

	if ( GetActorFlag( ACTOR_FLAG_AI_ON ) )
		gi.Printf( "AI is ON\n" );
	else
		gi.Printf( "AI is OFF\n" );

	if ( !( permanent_stimuli & STIMULI_SIGHT ) || !( stimuli & STIMULI_SIGHT ) )
		gi.Printf( "Actor is BLIND\n" );

	if ( !( permanent_stimuli & STIMULI_SOUND ) || !( stimuli & STIMULI_SOUND ) )
		gi.Printf( "Actor is DEAF\n" );

	if ( flags & FL_THINK )
		gi.Printf( "Think is ON\n" );
	else
		gi.Printf( "Think is OFF\n" );

	if ( mode == ACTOR_MODE_IDLE )
		gi.Printf( "Mode : IDLE\n" );
	else if ( mode == ACTOR_MODE_AI )
		gi.Printf( "Mode : AI\n" );
	else if ( mode == ACTOR_MODE_SCRIPT )
		gi.Printf( "Mode : SCRIPT\n" );
	else if ( mode == ACTOR_MODE_TALK )
		gi.Printf( "Mode : TALK\n" );

	gi.Printf( "\n" );

   if ( actorthread )
      {
      gi.Printf( "Thread     : %s(%d)\n", actorthread->Filename(), actorthread->CurrentLine() );
      }
   else
      {
      gi.Printf( "Thread     : NULL\n" );
      }

   gi.Printf( "Actortype  : %d\n", actortype );

   gi.Printf( "Model      : %s\n", model.c_str() );
   gi.Printf( "Anim       : %s\n", animname.c_str() );
   gi.Printf( "Movespeed  : %.2f\n", movespeed );
   gi.Printf( "Health     : %f\n", health );

   gi.Printf( "\ncurrentEnemy: " );
   if ( currentEnemy )
      {
      gi.Printf( "%d : '%s'\n", currentEnemy->entnum, currentEnemy->targetname.c_str() );
      }
   else
      {
      gi.Printf( "None\n" );
      }

   gi.Printf( "actortype: %d\n", actortype );

	switch( deadflag )
		{
		case DEAD_NO :
			gi.Printf( "deadflag: NO\n" );		
			break;
		case DEAD_DYING :
			gi.Printf( "deadflag: DYING\n" );		
			break;
		case DEAD_DEAD :
			gi.Printf( "deadflag: DEAD\n" );		
			break;
		case DEAD_RESPAWNABLE :
			gi.Printf( "deadflag: RESPAWNABLE\n" );		
			break;
		
		}

   gi.Printf( "\n" );
   if ( behavior )
      {
      gi.Printf( "Behavior Info:\n" );
      gi.Printf( "Game time: %f\n", level.time );
      behavior->ShowInfo( *this );
      gi.Printf( "\n" );
      }
   }

//***********************************************************************************************
//
// Stimuli functions
//
//***********************************************************************************************

void Actor::TurnAIOn
	(
	Event *ev
	)
	{
	SetActorFlag( ACTOR_FLAG_AI_ON, true );
	stimuli = STIMULI_ALL;
	}

void Actor::TurnAIOff
	(
	Event *ev
	)
	{
	SetActorFlag( ACTOR_FLAG_AI_ON, false );
	stimuli = STIMULI_NONE;

	if ( mode == ACTOR_MODE_AI )
		{
		// Ai is currently on, get out of AI mode
		gi.DPrintf( "Forcing an actor (#%d, %s) out of AI mode, this can be dangerous.\n", entnum, name.c_str() );
		EndMode();
		}
	}

void Actor::Deaf
	(
	Event *ev
	)
	{
	stimuli &= ~STIMULI_SOUND;
	}

void Actor::PermanentDeaf
	(
	Event *ev
	)
	{
	permanent_stimuli &= ~STIMULI_SOUND;
	}
void Actor::PermanentBlind
	(
	Event *ev
	)
	{
	permanent_stimuli &= ~STIMULI_SIGHT;
	}
qboolean Actor::IsBlind
	(
	void
	)
	{
	return ( !( permanent_stimuli & STIMULI_SIGHT ) || !( stimuli & STIMULI_SIGHT ) );
	}

void Actor::Dumb
	(
	Event *ev
	)
	{
	stimuli &= ~STIMULI_SOUND;
	stimuli &= ~STIMULI_SIGHT;
	}

bool Actor::RespondToStimuli( int new_stimuli )
	{
	return ( (( new_stimuli & stimuli ) && ( new_stimuli & permanent_stimuli )) || ( new_stimuli == STIMULI_SCRIPT ) );
	}

void Actor::Stimuli( int new_stimuli, Entity *ent, qboolean force )
	{
	if ( RespondToStimuli( new_stimuli ) )
		{
		MakeEnemy( ent, force );
		Wakeup();
		ActivateAI();
		}
	}

void Actor::Stimuli( int new_stimuli, Vector pos )
	{
	if ( RespondToStimuli( new_stimuli ) )
		{
		// Investigate the position

		if ( !GetActorFlag( ACTOR_FLAG_NOISE_HEARD ) )
			{
			noise_position = pos;
			SetActorFlag( ACTOR_FLAG_NOISE_HEARD, true );
			noise_time = level.time;
			}

		Wakeup();
		ActivateAI();
		}
	}

void Actor::StimuliNoAttack( int new_stimuli )
	{
	if ( RespondToStimuli( new_stimuli ) )
		{
		Wakeup();
		ActivateAI();
		}
	}

void Actor::ActivateAI( void )
	{
	if ( !statemap )
		return;

	StartMode( ACTOR_MODE_AI );

	stimuli = STIMULI_ALL;

	last_time_active = level.time;

	if ( actorthread )
		{
		actorthread->ProcessEvent( EV_ScriptThread_End );
		actorthread = NULL;
		}
	}

void Actor::SetIdleThread( Event *ev )
	{
	idle_thread = ev->GetString( 1 );
	}

//***********************************************************************************************
//
// Targeting functions
//
//***********************************************************************************************

void AI_TargetPlayer
	(
	void
	)

	{
	int		i;
	int		n;
   Entity   *player;
	Actor    *ent;

   // don't target while player is not in the game or he's in notarget
   player = g_entities[ 0 ].entity;
   if ( !player || ( player->flags & FL_NOTARGET ) )
      {
      return;
      }

   // process the list in reverse order in case SleepList is changed
	n = SleepList.NumObjects();
	for( i = n; i > 0; i-- )
		{
		ent = SleepList.ObjectAt( i );

		if ( gi.inPVS( player->centroid, ent->centroid ) )
			{
			if ( !ent->currentEnemy && ent->Hates( player ) && !ent->IsBlind() && ent->CanReallySee( player ) )
				{
				ent->Stimuli( STIMULI_SIGHT, player );
				}
			else
				{
				if ( world->farplane_distance == 0 || Distance( player->centroid, ent->centroid ) < world->farplane_distance )
					ent->Wakeup();
				}
			}
		}
	}

//***********************************************************************************************
//
// Actor checks
//
//***********************************************************************************************


qboolean Actor::checkanimname
   (
   Conditional &condition
   )

   {
	str anim_name_test;
	int use_length;
	int result;

	anim_name_test = condition.getParm( 1 );

	if ( condition.numParms() > 1 )
		use_length = atoi( condition.getParm( 2 ) );
	else
		use_length = false;

	if ( use_length )
		result = strncmp( animname.c_str(), anim_name_test.c_str(), anim_name_test.length() );
	else
		result = strcmp( animname.c_str(), anim_name_test.c_str() );

	return (result == 0);
   }

qboolean Actor::checkinactive
   (
   Conditional &condition
   )

   {
	return GetActorFlag( ACTOR_FLAG_INACTIVE );
   }

qboolean Actor::checkanimdone
   (
   Conditional &condition
   )

   {
	return GetActorFlag( ACTOR_FLAG_ANIM_DONE );
   }

qboolean Actor::checkdead
   (
   Conditional &condition
   )

   {
	return deadflag != 0;
   }

qboolean Actor::checkhaveenemy
   (
   Conditional &condition
   )

   {
	return IsEntityAlive( currentEnemy );
   }

qboolean Actor::checkenemydead
   (
   Conditional &condition
   )

   {
	if ( currentEnemy && ( currentEnemy->deadflag || currentEnemy->health <= 0 ) )
		return true;

	return false;
   }

qboolean Actor::checkenemynoclip
   (
   Conditional &condition
   )

   {
	if ( currentEnemy && currentEnemy->movetype == MOVETYPE_NOCLIP )
		return true;

	return false;
   }

qboolean Actor::checkcanseeenemy
   (
   Conditional &condition
   )

   {
	qboolean use_fov = true;
	qboolean can_see;
	qboolean in_fov;
	qboolean real_can_see;


	if ( condition.numParms() > 0 )
		use_fov = atoi( condition.getParm( 1 ) );

	// See if we should check again

   if ( canseeenemy_time > level.time )
      {
		if ( use_fov )
			return GetActorFlag( ACTOR_FLAG_LAST_CANSEEENEMY );
		else
			return GetActorFlag( ACTOR_FLAG_LAST_CANSEEENEMY_NOFOV );
      }

	can_see = true;
	in_fov  = true;

	// Check to see if we can see enemy

	if ( !IsEntityAlive( currentEnemy ) )
		{
		can_see = false;
		in_fov  = false;
		}

	if ( can_see && !WithinVisionDistance( currentEnemy ) )
		can_see = false;
		
	if ( can_see && !CanSeeFrom( origin, currentEnemy ) )
		can_see = false;
	
	if ( in_fov && !InFOV( currentEnemy ) )
		in_fov = false;

	// Save can see info

	SetActorFlag( ACTOR_FLAG_LAST_CANSEEENEMY, can_see && in_fov );
	SetActorFlag( ACTOR_FLAG_LAST_CANSEEENEMY_NOFOV, can_see );

   canseeenemy_time = level.time + 0.2f + G_Random( 0.1f );

	if ( use_fov )
		real_can_see = GetActorFlag( ACTOR_FLAG_LAST_CANSEEENEMY );
	else
		real_can_see = GetActorFlag( ACTOR_FLAG_LAST_CANSEEENEMY_NOFOV );

	// Save the last known position of our enemy

	if ( real_can_see )
		last_known_enemy_pos = currentEnemy->origin;

	return real_can_see;
   }

qboolean Actor::checkcanshootenemy
   (
   Conditional &condition
   )

   {
	str tag_name;

	if ( !currentEnemy )
		return false;

	if ( condition.numParms() > 1 )
		tag_name = condition.getParm( 2 );

	return ( checkcanseeenemy( condition ) && TestAttack( tag_name ) );
	}

qboolean Actor::checkenemyinfov
   (
   Conditional &condition
   )
	{
	float check_fov;
	float check_fovdot;


	if ( !currentEnemy )
		return false;

	if ( condition.numParms() > 0 )
		{
		check_fov = atof( condition.getParm( 1 ) );
		check_fovdot = cos( check_fov * 0.5 * M_PI / 180.0 );

		return InFOV( currentEnemy->centroid, check_fov, check_fovdot );
		}
	else
		{
		return InFOV( currentEnemy );
		}
	}

qboolean Actor::checkenemyonground
   (
   Conditional &condition
   )
	{
	if ( !currentEnemy )
		return false;

	if ( currentEnemy->groundentity )
		return true;
	else
		return false;
	}

qboolean Actor::checkenemyrelativeyaw
   (
   Conditional &condition
   )

   {
	Vector dir;
	Vector dir_angles;
	float relative_yaw;
	float check_yaw;
	Vector temp_angles;

	if ( !currentEnemy )
		return false;

	check_yaw = atof( condition.getParm( 1 ) );

	dir = origin - currentEnemy->origin;

	dir_angles = dir.toAngles();

	temp_angles = currentEnemy->angles;

	relative_yaw = AngleNormalize180( currentEnemy->angles[YAW] - dir_angles[YAW] );

	if ( relative_yaw < check_yaw )
		return true;
	else
		return false;
   }

qboolean Actor::checkcanjumptoenemy
   (
   Conditional &condition
   )

   {
	return ( currentEnemy && CanWalkTo( currentEnemy->origin, currentEnemy->entnum ) );
   }

qboolean Actor::checkcanflytoenemy
   (
   Conditional &condition
   )

   {
	trace_t trace;

	if ( !currentEnemy )
		return false;

	trace = G_Trace( origin, mins, maxs, currentEnemy->centroid, this, edict->clipmask, false, "Actor::checkcanflytoenemy" );

	if ( trace.startsolid || trace.allsolid )
		return false;

	if ( trace.entityNum == currentEnemy->entnum )
		return true;

	return false;
   }

qboolean Actor::checkinpain
   (
   Conditional &condition
   )

   {
	return ( state_flags & STATE_FLAG_IN_PAIN );
   }

qboolean Actor::checksmallpain
   (
   Conditional &condition
   )

   {
	return ( state_flags & STATE_FLAG_SMALL_PAIN );
   }

qboolean Actor::checkpainyaw
   (
   Conditional &condition
   )

   {
	float check_yaw;

	check_yaw = atof( condition.getParm( 1 ) );

	if ( pain_angles[YAW] <= check_yaw )
		return true;
	else
		return false;
   }

qboolean Actor::checkpainpitch
   (
   Conditional &condition
   )

   {
	float check_pitch;

	check_pitch = atof( condition.getParm( 1 ) );

	if ( pain_angles[PITCH] <= check_pitch )
		return true;
	else
		return false;
   }

qboolean Actor::checkstunned
   (
   Conditional &condition
   )

   {
	return GetActorFlag( ACTOR_FLAG_STUNNED );
   }

qboolean Actor::checkfinished
   (
   Conditional &condition
   )

   {
	return GetActorFlag( ACTOR_FLAG_FINISHED );
   }

qboolean Actor::checkmeleehit
   (
   Conditional &condition
   )

   {
	return ( state_flags & STATE_FLAG_MELEE_HIT );
   }

qboolean Actor::checkblockedhit
   (
   Conditional &condition
   )

   {
	return ( state_flags & STATE_FLAG_BLOCKED_HIT );
   }

qboolean Actor::checkblocked
   (
   Conditional &condition
   )

   {
	if ( attack_blocked && attack_blocked_time + .75 > level.time )
		return true;
	else
		return false;
   }

qboolean Actor::checkonfire
   (
   Conditional &condition
   )

   {
	return on_fire;
   }

qboolean Actor::checkotherdied
   (
   Conditional &condition
   )

   {
	return ( state_flags & STATE_FLAG_OTHER_DIED );
   }

qboolean Actor::checkstuck
   (
   Conditional &condition
   )

   {
	return ( state_flags & STATE_FLAG_STUCK );
   }

qboolean Actor::checknopath
   (
   Conditional &condition
   )

   {
	return ( state_flags & STATE_FLAG_NO_PATH );
   }

qboolean Actor::checkbehaviordone
   (
   Conditional &condition
   )

   {
	return ( behavior == NULL );
   }

qboolean Actor::checktimedone
   (
   Conditional &condition
   )

   {
	if ( GetActorFlag( ACTOR_FLAG_STATE_DONE_TIME_VALID ) )
      {
		return ( state_done_time < level.time );
      }

	return false;
   }

qboolean Actor::checkdone
   (
   Conditional &condition
   )

   {
	return ( checkbehaviordone( condition ) || checktimedone( condition ) );
   }

qboolean Actor::checkenemyrange
   (
   Conditional &condition
   )

	{
	float range;
	float min_height;
	float max_height;
	
	range = atof( condition.getParm( 1 ) );

	if ( condition.numParms() > 1 )
		max_height = atof( condition.getParm( 2 ) );
   else
		max_height = 0;

	if ( condition.numParms() > 2 )
		min_height = atof( condition.getParm( 3 ) );
   else
		min_height = -max_height;

	return EntityInRange( currentEnemy, range, min_height, max_height );
	}

qboolean Actor::checkplayerrange
   (
   Conditional &condition
   )

	{
	float range;
	float height;
	Entity *player;
	
	range = atof( condition.getParm( 1 ) );

	if ( condition.numParms() == 2 )
		height = atof( condition.getParm( 2 ) );
   else
		height = 0;

	player = g_entities[ 0 ].entity;

	return EntityInRange( player, range, -height, height );
	}

qboolean Actor::checkmovingactorrange
   (
   Conditional &condition
   )

   {
	float       range;
	float       height = 0;
	float       height_diff;
	Entity      *ent_in_range;
   int         i;
	Vector      delta;
   float       r2;
	gentity_t   *ed;
	float			smallest_dist2;
	float			dist2;


	// Get distances
	range = atof( condition.getParm( 1 ) );

	if ( condition.numParms() == 2 )
      {
		height = atof( condition.getParm( 2 ) );
      }

	r2 = range * range;

	if ( actorrange_time > level.time && height == last_height )
      {
		ent_in_range = last_ent;

		if ( IsEntityAlive( ent_in_range ) )
			{
			delta = origin - ent_in_range->centroid;

			if ( height )
				{
				height_diff = delta[ 2 ];
				delta[ 2 ] = 0;

				if ( ( height_diff < -height ) || ( height_diff > height ) )
					return false;
				}

				// dot product returns length squared
			if ( ( ( delta * delta ) <= r2 ) && CanSee( ent_in_range ) )
				return true;
			}

		return false;
      }

   actorrange_time = level.time + 0.2f + G_Random( 0.1f );

	last_height = height;
	last_ent    = NULL;

	smallest_dist2 = 99999999;

	// See if any clients are in range
	for( i = 0 ; i < game.maxclients; i++ )
      {
      ed = &g_entities[ i ];

		if ( !ed->inuse || !ed->entity )
         {
			continue;
         }

		ent_in_range = ed->entity;

		if ( IsEntityAlive( ent_in_range ) )
         {
         delta = origin - ent_in_range->centroid;

			if ( height > 0 )
				{
				height_diff = delta[ 2 ];

				if ( ( height_diff < -height ) || ( height_diff > height ) )
               {
					continue;
               }

				delta[ 2 ] = 0;
				}

		   // dot product returns length squared

			dist2 = delta * delta;

		   if ( ( dist2 <= r2 ) && CanSee( ent_in_range ) )
            {
				if ( dist2 < smallest_dist2 )
					{
					smallest_dist2 = dist2;
					last_ent = ent_in_range;
					}
            }
         }
		}

	// See if any actors are in range
   for( i = 1; i <= ActiveList.NumObjects(); i++ )
      {
      ent_in_range = ActiveList.ObjectAt( i );

		if ( 
            ( ent_in_range->movetype != MOVETYPE_NONE ) && 
            ( ent_in_range->movetype != MOVETYPE_STATIONARY ) && 
            ( this != ent_in_range ) && 
            ( ent_in_range->health > 0 ) && 
            !( ent_in_range->flags & FL_NOTARGET ) 
         )
         {
         delta = origin - ent_in_range->centroid;

			if ( height > 0 )
				{
				height_diff = delta[ 2 ];

				if ( ( height_diff < -height ) || ( height_diff > height ) )
               {
					continue;
               }

				delta[ 2 ] = 0;
				}

		   // dot product returns length squared

			dist2 = delta * delta;

		   if ( ( dist2 <= r2 ) && CanSee( ent_in_range ) )
            {
            if ( dist2 < smallest_dist2 )
					{
					smallest_dist2 = dist2;
					last_ent = ent_in_range;
					}
            }
         }
      }

	if ( last_ent )
		return true;

	return false;
	}

qboolean Actor::checkchance
   (
   Conditional &condition
   ) 

	{
	float percent_chance;

	percent_chance = atof( condition.getParm( 1 ) );

	return ( G_Random() < percent_chance );
	}

qboolean Actor::checkstatetime
   (
   Conditional &condition
   ) 

	{
	float time_to_wait;

	time_to_wait = atof( condition.getParm( 1 ) );

	return ( state_time + time_to_wait < level.time );
	}

qboolean Actor::checktimesdone
   (
   Conditional &condition
   )

	{
	return ( times_done == atoi( condition.getParm( 1 ) ) );
	}

qboolean Actor::checkmeansofdeath
   (
   Conditional &condition
   )

	{
	int mod;

	mod = MOD_string_to_int( condition.getParm( 1 ) );

	return ( mod == means_of_death );
	}

qboolean Actor::checknoiseheard
   (
   Conditional &condition
   )

	{
	return GetActorFlag( ACTOR_FLAG_NOISE_HEARD );
	}

qboolean Actor::checkpartstate
   (
   Conditional &condition
   )

	{
	str part_name;
	str state_name;
	Actor *part;

	part_name  = condition.getParm( 1 );
	state_name = condition.getParm( 2 );

	part = FindPartActor( part_name );

	return ( part && strnicmp( part->currentState->getName(), state_name.c_str(), strlen( state_name.c_str() ) ) == 0 );
	}

qboolean Actor::checkpartflag
   (
   Conditional &condition
   )

	{
	str part_name;
	str flag_name;
	unsigned int flag;
	int current_part;
	part_t *part;
	Entity *partent;
	Actor *partact;

	part_name  = condition.getParm( 1 );
	flag_name  = condition.getParm( 2 );

	if ( stricmp( flag_name, "pain" ) == 0 )
      {
		flag = STATE_FLAG_IN_PAIN;
      }
	else if ( stricmp( flag_name, "small_pain" ) == 0 )
      {
		flag = STATE_FLAG_SMALL_PAIN;
      }
	else if ( stricmp( flag_name, "melee_hit" ) == 0 )
      {
		flag = STATE_FLAG_MELEE_HIT;
      }
	else if ( stricmp( flag_name, "touched" ) == 0 )
      {
		flag = STATE_FLAG_TOUCHED;
      }
	else if ( stricmp( flag_name, "activated" ) == 0 )
      {
		flag = STATE_FLAG_ACTIVATED;
      }
	else if ( stricmp( flag_name, "used" ) == 0 )
      {
		flag = STATE_FLAG_USED;
      }
	else if ( stricmp( flag_name, "twitch" ) == 0 )
      {
		flag = STATE_FLAG_TWITCH;
      }
	else
		{
		gi.DPrintf( "Unknown flag name (%s) in checkpartflag.", flag_name.c_str() );
		flag = 0;
		}

	for( current_part = 1; current_part <= parts.NumObjects(); current_part++ )
		{
		part = &parts.ObjectAt( current_part );

		partent = part->ent;
		partact = (Actor *)partent;

		if ( partact && partact->part_name == part_name )
			{
			if ( part->state_flags & flag )
            {
				return true;
            }
			}
		}
	
	return false;
	}

qboolean Actor::checkpartdead
   (
   Conditional &condition
   )

	{
	str part_name;
	str state_name;
	Actor *part;

	part_name = condition.getParm( 1 );

	part = FindPartActor( part_name );

	if ( !part )
		return false;

	return ( part->deadflag || part->health <= 0 );
	}

qboolean Actor::checknumspawns
	(
   Conditional &condition
   )

	{
	int check_num;

	check_num = atoi( condition.getParm( 1 ) );

	return ( num_of_spawns < check_num );
	}

qboolean Actor::checkcommand
   (
   Conditional &condition
   )

	{
	return ( command == condition.getParm( 1 ) );
	}

qboolean Actor::checktouched
   (
   Conditional &condition
   )

	{
	return state_flags & STATE_FLAG_TOUCHED;
	}

qboolean Actor::checkactivated
   (
   Conditional &condition
   )

	{
	return state_flags & STATE_FLAG_ACTIVATED;
	}

qboolean Actor::checkused
   (
   Conditional &condition
   )

	{
	return ( state_flags & STATE_FLAG_USED );
	}

qboolean Actor::checktwitch
   (
   Conditional &condition
   )

	{
	return ( state_flags & STATE_FLAG_TWITCH );
	}

qboolean Actor::checkhealth
   (
   Conditional &condition
   )

	{
	return health < atof( condition.getParm( 1 ) );
	}

qboolean Actor::checkonground
   (
   Conditional &condition
   )

	{
	return groundentity != NULL;
	}

qboolean Actor::checkinwater
   (
   Conditional &condition
   )

	{
	return (waterlevel > 0 );
	}

qboolean Actor::checkincomingmeleeattack
   (
   Conditional &condition
   )

	{
	Entity *enemy_ent;
	Sentient *enemy;
	trace_t trace;
	Vector forward;
	Vector end_pos;

	if ( IsEntityAlive( currentEnemy ) )
		{
		if ( currentEnemy->isSubclassOf( Sentient ) )
			{
			enemy_ent = ( Entity * )currentEnemy;
			enemy = ( Sentient * )enemy_ent;
			
			if ( enemy->in_melee_attack )
				{
				enemy->angles.AngleVectors( &forward );
				end_pos = forward * 125 + enemy->centroid;
				trace = G_Trace( enemy->centroid, vec_zero, vec_zero, end_pos, enemy, MASK_SHOT, false, "Actor::checkincomingmeleeattack" );

				if ( trace.entityNum == entnum )
               {
					return true;
               }
				}
			}
		}

	return false;
	}

qboolean Actor::checkincomingprojectile
   (
   Conditional &condition
   )

	{
	trace_t trace;
	Vector forward;
	Vector end_pos;
	float time = 0;
	float time_left;
	Vector dir;
	float dist;

	if ( condition.numParms() == 1 )
      {
		time = atof( condition.getParm( 1 ) );
      }

	if ( incoming_proj && incoming_time <= level.time )
		{
		incoming_proj->angles.AngleVectors( &forward );
		end_pos = forward * 1000 + incoming_proj->centroid;
		trace = G_Trace( incoming_proj->centroid, vec_zero, vec_zero, end_pos, incoming_proj, MASK_SHOT, false, "Actor::checkincomingprojectile" );

		if ( trace.entityNum == entnum )
         {
			if ( time )
				{
				dir = trace.endpos - incoming_proj->centroid;
				dist = dir.length();
				time_left = dist / incoming_proj->velocity.length();

				return ( time_left <= time );
				}

			return true;
         }
		}

	return false;
	}

qboolean Actor::checkenemystunned
   (
   Conditional &condition
   )

	{
	Sentient *enemy;


	if ( IsEntityAlive( currentEnemy ) )
		{
		if ( currentEnemy->isSubclassOf( Sentient ) )
			{
			enemy = (Sentient *)(Entity *)currentEnemy;
			
			if ( enemy->in_stun )
				return true;
			}
		}

	return false;
	}

qboolean Actor::checkenemyinpath
   (
   Conditional &condition
   )

	{
	trace_t  trace;
	Vector   end_pos;

	if ( IsEntityAlive( currentEnemy ) )
		{
	   Vector forward( orientation[ 0 ] );

		forward *= 1000;
		end_pos = origin + forward;

		trace = G_Trace( centroid, vec_zero, vec_zero, end_pos, this, MASK_SHOT, false, "Actor::checkenemyinpath" );

		if ( trace.entityNum == currentEnemy->entnum )
         {
			return true;
         }
		}

	return false;
	}

qboolean Actor::checkstage
   (
   Conditional &condition
   )

	{
	return ( stage == atoi( condition.getParm( 1 ) ) );
	}

qboolean Actor::checkheld
   (
   Conditional &condition
   )

	{
	return ( edict->s.parent != ENTITYNUM_NONE );
	}

qboolean Actor::checkenemymelee
   (
   Conditional &condition
   )

	{
	return ( EntityHasFireType( currentEnemy, FT_MELEE ) );
	}

qboolean Actor::checkenemyranged
   (
   Conditional &condition
   )

	{
	return ( EntityHasFireType( currentEnemy, FT_BULLET ) || EntityHasFireType( currentEnemy, FT_PROJECTILE ) );
	}

qboolean Actor::checkenemyshield
   (
   Conditional &condition
   )

	{
	if ( !currentEnemy )
		return false;

	if ( currentEnemy->isSubclassOf( Player ) )
		{
		qboolean care_about_using_shield;
		Weapon *weap;
		Player *player;
		
		player = ( Player * )( Entity * )currentEnemy;

		// See if we care if the enemy is currently using a shield

		if ( condition.numParms() > 0 )
			care_about_using_shield = atoi( condition.getParm( 1 ) );
		else
			care_about_using_shield = false;

		// See if they have a shield

		weap = player->GetActiveWeapon( WEAPON_LEFT );

      if ( !weap || !weap->isSubclassOf( Shield ) )
			return false;

		// See if the enemy is using the shield right now (if we care)

		if ( !care_about_using_shield || player->ShieldActive() )
			return true;
		}
	else if ( currentEnemy->isSubclassOf( Sentient ) )
		{
		Sentient *sent = ( Sentient * )( Entity * )currentEnemy;

		// If just a sentient, just return if they are currently blocking

		return sent->in_block;
		}

	return false;
	}

qboolean Actor::checkhasthing
   (
   Conditional &condition
   )

   {
	int thing_number;
	int i;


	for( i = 1 ; i <= condition.numParms() ; i++ )
		{
		thing_number = atoi( condition.getParm( i ) );

		switch( thing_number )
			{
			case 1 :
				if ( GetActorFlag( ACTOR_FLAG_HAS_THING1 ) )
					return true;
				break;
			case 2 :
				if ( GetActorFlag( ACTOR_FLAG_HAS_THING2 ) )
					return true;
				break;
			case 3 :
				if ( GetActorFlag( ACTOR_FLAG_HAS_THING3 ) )
					return true;
				break;
			case 4 :
				if ( GetActorFlag( ACTOR_FLAG_HAS_THING4 ) )
					return true;
				break;
			}
		}

	return false;
   }

qboolean Actor::checkallowhangback
   (
   Conditional &condition
   )

   {
	return GetActorFlag( ACTOR_FLAG_ALLOW_HANGBACK );
   }

qboolean Actor::checkname
   (
   Conditional &condition
   )

	{
	return ( name == condition.getParm( 1 ) );
	}

qboolean Actor::returntrue
   (
   Conditional &condition
   )

   {
   return true;
   }

Condition<Actor> Actor::Conditions[] =
   {
      { "default",							returntrue },
      { "INACTIVE",							checkinactive },
      { "ANIM_DONE",							checkanimdone },
      { "DEAD",								checkdead },
                                                            
      { "HAVE_ENEMY",						checkhaveenemy },
		{ "ENEMY_DEAD",						checkenemydead },
		{ "ENEMY_NOCLIP",						checkenemynoclip },
      { "CAN_SEE_ENEMY",					checkcanseeenemy },
		{ "CAN_SHOOT_ENEMY",					checkcanshootenemy },
		{ "ENEMY_IN_FOV",						checkenemyinfov },
		{ "ENEMY_RELATIVE_YAW",				checkenemyrelativeyaw },
		{ "ENEMY_IN_FOV",						checkenemyinfov },
		{ "ENEMY_ON_GROUND",					checkenemyonground },


      { "CAN_JUMP_TO_ENEMY",				checkcanjumptoenemy },
		{ "CAN_FLY_TO_ENEMY",				checkcanflytoenemy },
                                                            
      { "PAIN",								checkinpain },
		{ "SMALL_PAIN",						checksmallpain },
		{ "PAIN_YAW",							checkpainyaw },
		{ "PAIN_PITCH",						checkpainpitch },

		{ "STUNNED",							checkstunned },
		{ "FINISHED",							checkfinished },

      { "MELEE_HIT",							checkmeleehit },
		{ "BLOCKED_HIT",						checkblockedhit },
		{ "BLOCKED",							checkblocked },
		{ "OTHER_DIED",						checkotherdied },
		{ "STUCK",								checkstuck },
		{ "NO_PATH",							checknopath },

		{ "ON_FIRE",							checkonfire },
                                                            
      { "BEHAVIOR_DONE",					checkbehaviordone },
      { "TIME_DONE",							checktimedone },
      { "DONE",								checkdone },
                                                            
      { "RANGE",								checkenemyrange },
		{ "PLAYER_RANGE",						checkplayerrange },
      { "CHANCE",								checkchance },
      { "MOVING_ACTOR_RANGE",				checkmovingactorrange },
      { "STATE_TIME",						checkstatetime },
      { "TIMES_DONE",						checktimesdone },
                                                            
      { "MOD",									checkmeansofdeath },
                                                            
      { "NOISE_HEARD",						checknoiseheard },
                                                            
      { "PART_STATE",						checkpartstate },
      { "PART_DEAD",							checkpartdead },
      { "PART_FLAG",							checkpartflag },

		{ "NUM_SPAWNS",						checknumspawns },
                                                            
      { "COMMAND",							checkcommand },
                                                            
      { "TOUCHED",							checktouched },
                                                            
      { "ACTIVATED",							checkactivated },
      { "USED",								checkused },
      { "TWITCH",								checktwitch },
                                                            
      { "HEALTH",								checkhealth },
                                                            
      { "ON_GROUND",							checkonground },
		{ "IN_WATER",							checkinwater },

      { "INCOMING_MELEE_ATTACK",			checkincomingmeleeattack },
      { "INCOMING_PROJECTILE",			checkincomingprojectile },

		{ "ENEMY_STUNNED",					checkenemystunned },

      { "ENEMY_IN_PATH",					checkenemyinpath },

      { "STAGE",								checkstage },

		{ "HELD",								checkheld },

		{ "ENEMY_HAS_MELEE",					checkenemymelee },
		{ "ENEMY_HAS_RANGED",				checkenemyranged },
		{ "ENEMY_HAS_SHIELD",				checkenemyshield },

		{ "HAS_THING",							checkhasthing },

		{ "ALLOW_HANGBACK",					checkallowhangback },

		{ "NAME",								checkname },
		{ "ANIM_NAME",							checkanimname },

      { NULL,									NULL },
   };

//***********************************************************************************************
//
// Actor subclasses
//
//***********************************************************************************************

Event	EV_SpinningPlant_GetClip
	( 
	"get_clip",
	EV_DEFAULT,
	NULL,
	NULL,
	"Gets the clip brush for the spinning plant actor,"
	"it is not meant to be called from script."
	);

CLASS_DECLARATION( Actor, SpinningPlant, NULL )
	{
		{ &EV_SpinningPlant_GetClip,			   GetClip },
      { NULL, NULL }
   };

SpinningPlant::SpinningPlant
	(
	)

	{
	spinner_model = NULL;
	spinner_clip  = NULL;

	PostEvent( EV_SpinningPlant_GetClip, 0 );
	}

void SpinningPlant::GetClip
	(
	Event *ev
	)
	{
	Entity * ent;

	spinner_model = new Mover;
	spinner_model->setModel( model );
	spinner_model->setSolidType( SOLID_NOT );
	spinner_model->setOrigin( origin );
	
	hideModel();
	setSolidType( SOLID_NOT );

	if ( target.length() > 0 )
		{
		ent = G_FindTarget( this, target.c_str() );

		if ( ent )
			{
			spinner_clip = (Mover *)ent;
			}
		}

	if ( spinner_clip )
		{
		spinner_clip->hideModel();
		spinner_model->bind( spinner_clip );
		}
	}

SpinningPlant::~SpinningPlant()
	{
	if ( spinner_model )
		{
		spinner_model->PostEvent( EV_Remove, 0 );
		spinner_model = NULL;
		}
	}

//***********************************************************************************************
//
// Code for seperate parts
//
//***********************************************************************************************

void Actor::RegisterParts
	(
	Event *ev
	)
	{
	Entity *targetent;
	qboolean forward;
	int current_part;
	part_t *forward_part;
	part_t new_part;
	Event *event;

	targetent = ev->GetEntity( 1 );
	forward   = ev->GetInteger( 2 );

	if ( !targetent )
		return;

	// See if we should tell other parts about each other

	if ( forward )
		{
		// Tell all old parts about this new part and tell the new part about all of the old ones

		for ( current_part = 1 ; current_part <= parts.NumObjects() ; current_part++ )
			{
			forward_part = &parts.ObjectAt( current_part );

			if ( forward_part )
				{
				// Tell old part about new part

				event = new Event( EV_ActorRegisterParts );
				event->AddEntity( targetent );
				event->AddInteger( false );
				forward_part->ent->PostEvent( event, 0 );

				// Tell new part about old part

				event = new Event( EV_ActorRegisterParts );
				event->AddEntity( forward_part->ent );
				event->AddInteger( false );
				targetent->PostEvent( event, 0 );
				}
			}
		}

	// Add this part to our part list

	new_part.ent         = targetent;
	new_part.state_flags = 0;

	parts.AddObject( new_part );
	}

void Actor::PartName
	(
	Event *ev
	)
	{
	part_name = ev->GetString( 1 );
	}

void Actor::RegisterSelf
	(
	Event *ev
	)
	{
	Entity *targetent;
	Actor *targetact;
	Event *event;
	part_t new_part;

	if ( target.length() > 0 )
		{
		// Get the target entity

		targetent = G_FindTarget( this, target.c_str() );

		if ( !targetent )
			return;

		// See if this target entity is a another part of ourselves

		if ( targetent->isSubclassOf( Actor ) )
			{
			targetact = (Actor *)targetent;

			if ( name.length() > 0 && targetact->name == name )
				{
				// Tell other part about ourselves

				event = new Event( EV_ActorRegisterParts );
				event->AddEntity( this );
				event->AddInteger( true );
				targetent->PostEvent( event, 0 );

				// Add this part to our part list

				new_part.ent         = targetent;
				new_part.state_flags = 0;
				parts.AddObject( new_part );
				}
			}
      }
	}

Actor *Actor::FindPartActor( const char *name )
	{
	int current_part;
	part_t *part;
	Entity *partent;
	Actor *partact;

	for ( current_part = 1 ; current_part <= parts.NumObjects() ; current_part++ )
		{
		part = &parts.ObjectAt( current_part );

		partent = part->ent;
		partact = (Actor *)partent;

		if ( partact && partact->part_name == name )
			return partact;
		}

	return NULL;
	}

void Actor::SendCommand
	(
	Event *ev
	)

	{
	str command;
	str part_to_send_to;
	int i;
	part_t *part;
	Actor *partact;

	command = ev->GetString( 1 );
	part_to_send_to = ev->GetString( 2 );

	if ( command.length() == 0 || part_to_send_to.length() == 0 )
		return;

	for( i = 1 ; i <= parts.NumObjects(); i++ )
		{
		part = &parts.ObjectAt( i );

		partact = ( Actor * )(Entity *)part->ent;

		if ( partact && partact->part_name == part_to_send_to )
			{
			partact->command = command;
			}
		}		
	}

//***********************************************************************************************
//
// Dialog functions
//
//***********************************************************************************************

void Actor::AddDialog
   (
   Event *ev
   )

   {
	DialogNode_t *dialog_node;

	dialog_node = NewDialogNode();

	if (dialog_node != NULL)
	   {
		// Add the alias name to the dialog
		strcpy(dialog_node->alias_name, ev->GetString( 1 ));

		// Add all the other parameters to the dialog
		AddDialogParms( dialog_node, ev );
		
		// Add the new dialog to this dialog list
		dialog_node->next = dialog_list;
		dialog_list = dialog_node;
   	}
   }

DialogNode_t *Actor::NewDialogNode
   (
   void
   )

   {
   DialogNode_t *dialog_node;

   dialog_node = new DialogNode_t;
   memset( dialog_node, 0 , sizeof( DialogNode_t ) );
	dialog_node->random_percent = 1.0;

   return dialog_node;
   }

void Actor::AddDialogParms
   (
   DialogNode_t *dialog_node,
	Event *ev
   )

   {
	const char *token;
	int parm_type;
	float temp_float;
	int current_parm;
	int num_parms;


	if ( dialog_node == NULL )
		return;

	current_parm = 2;
	num_parms    = ev->NumArgs();

	// Get all of the parameters

	while( 1 )
		{
		if ( current_parm > num_parms )
			break;

		token = ev->GetString( current_parm );
		current_parm++;

		parm_type = DIALOG_PARM_TYPE_NONE;

		if (stricmp(token, "randompick") == 0)
			dialog_node->random_flag = qtrue;
		else if (stricmp(token, "playerhas") == 0)
			parm_type = DIALOG_PARM_TYPE_PLAYERHAS;
		else if (stricmp(token, "playerhasnot") == 0)
			parm_type = DIALOG_PARM_TYPE_PLAYERHASNOT;
		else if (stricmp(token, "has") == 0)
			parm_type = DIALOG_PARM_TYPE_HAS;
		else if (stricmp(token, "has_not") == 0)
			parm_type = DIALOG_PARM_TYPE_HASNOT;
		else if (stricmp(token, "depends") == 0)
			parm_type = DIALOG_PARM_TYPE_DEPENDS;
		else if (stricmp(token, "dependsnot") == 0)
			parm_type = DIALOG_PARM_TYPE_DEPENDSNOT;
		else if (stricmp(token, "random") == 0)
			{
			if ( current_parm > num_parms )
				break;

			token = ev->GetString( current_parm );
			current_parm++;

			temp_float = atof(token);

			if ((temp_float >= 0.0) && (temp_float <= 1.0))
				dialog_node->random_percent = temp_float;
			else
				gi.DPrintf("Random percent out of range for dialog (alias %s)\n", dialog_node->alias_name);
			}
		else
			gi.DPrintf("Unknown parameter for dialog (alias %s)\n", dialog_node->alias_name);

		if (parm_type != DIALOG_PARM_TYPE_NONE)
			{
			if ( current_parm > num_parms )
				break;

			token = ev->GetString( current_parm );
			current_parm++;

			if (dialog_node->number_of_parms < MAX_DIALOG_PARMS)
				{
				strcpy(dialog_node->parms[dialog_node->number_of_parms].parm, token);
				dialog_node->parms[dialog_node->number_of_parms].type = parm_type;
				dialog_node->number_of_parms++;
				}
			else
				{
				gi.DPrintf("Too many parms for  dialog (alias %s)\n", dialog_node->alias_name);
				}
			}
		}
   }

void Actor::PlayDialog
	(
	Event *ev
	)
	{
	Sentient *user = NULL;
	const char *dialog_name = NULL;
	const char *state_name = NULL;
	float volume   = DEFAULT_VOL;
	float min_dist = DEFAULT_MIN_DIST;

	if (ev->NumArgs() > 0)
		{
		dialog_name = ev->GetString( 1 );

		if ( strcmp( dialog_name, "" ) == 0 )
			dialog_name = NULL;
		}

	if ( ev->NumArgs() > 1 )
		volume = ev->GetFloat( 2 );

	if ( ev->NumArgs() > 2 )
		min_dist = ev->GetFloat( 3 );

	if ( ev->NumArgs() > 3 )
		{
		state_name = ev->GetString( 4 );

		if ( strcmp( state_name, "" ) == 0 )
			state_name = NULL;
		}

	if ( ev->NumArgs() > 4 )
		user = (Sentient *)ev->GetEntity( 5 );

	// Make sure any playdialog commands from script is full volume

	if ( ev->GetSource() == EV_FROM_SCRIPT )
		min_dist = LEVEL_WIDE_MIN_DIST;

	PlayDialog( user, volume, min_dist, dialog_name, state_name );
	}

void Actor::PlayDialog
   (
   Sentient *user,
	float volume,
	float min_dist,
	const char *dialog_name,
	const char *state_name
   )

   {
	DialogNode_t *dialog_node;
	int good_dialog;
	int i;
	ScriptVariable *script_var;

	if ( GetActorFlag( ACTOR_FLAG_DIALOG_PLAYING ) )
		return;

	if (dialog_name == NULL)
		{
		dialog_node = dialog_list;

		while(dialog_node != NULL)
			{
			// See if we should play the current dialog

			good_dialog = qtrue;

			for(i = 0 ; i < dialog_node->number_of_parms ; i++)
				{
				// Test to see if this parm passes

				switch(dialog_node->parms[ i ].type)
   				{
					case DIALOG_PARM_TYPE_PLAYERHAS :
						if (!user || !user->HasItem(dialog_node->parms[ i ].parm))
							good_dialog = qfalse;
						break;
					case DIALOG_PARM_TYPE_PLAYERHASNOT :
						if (!user || user->HasItem(dialog_node->parms[ i ].parm))
							good_dialog = qfalse;
						break;
					case DIALOG_PARM_TYPE_HAS :
						if (!HasItem(dialog_node->parms[ i ].parm))
							good_dialog = qfalse;
						break;
					case DIALOG_PARM_TYPE_HASNOT :
						if (HasItem(dialog_node->parms[ i ].parm))
							good_dialog = qfalse;
						break;
					case DIALOG_PARM_TYPE_DEPENDS :
						script_var = gameVars.GetVariable( dialog_node->parms[ i ].parm );

						if ( script_var )
							{
							if (!script_var->intValue())
								good_dialog = qfalse;
							}

						script_var = levelVars.GetVariable( dialog_node->parms[ i ].parm );

						if ( script_var )
							{
							if (!script_var->intValue())
								good_dialog = qfalse;
							}
						
						break;
					case DIALOG_PARM_TYPE_DEPENDSNOT :
						script_var = gameVars.GetVariable( dialog_node->parms[ i ].parm );

						if ( script_var )
							{
							if (script_var->intValue())
								good_dialog = qfalse;
							}

						script_var = levelVars.GetVariable( dialog_node->parms[ i ].parm );

						if ( script_var )
							{
							if (script_var->intValue())
								good_dialog = qfalse;
							}
						
						break;
	   			}

				// If dialog is already not good go to next dialog
				if (!good_dialog)
					break;
				}

			if ((dialog_node->random_percent < 1.0) && (G_Random() > dialog_node->random_percent))
				{
				good_dialog = qfalse;
				}
			
			if (good_dialog)
				{
				// Found a good dialog now get the real sound name from the alias 

				dialog_name = gi.Alias_FindDialog( edict->s.modelindex, dialog_node->alias_name, dialog_node->random_flag, entnum);

				if (dialog_name != NULL)
					break;
				}

			// Try the next dialog in the list

			dialog_node = dialog_node->next;
			}
		}

	if (dialog_name != NULL)
	   {
		byte *dialog_amplitudes = NULL;
		int number_of_amplitudes = 0;
		float dialog_length;
		int current_amplitude;
		Event *new_event;
		float angle;
		Vector mouth_angles;

		Sound( dialog_name, CHAN_DIALOG, volume, min_dist );
		SetActorFlag( ACTOR_FLAG_DIALOG_PLAYING, true );

		dialog_amplitudes = gi.SoundAmplitudes( dialog_name, &number_of_amplitudes );
		dialog_length = gi.SoundLength( dialog_name );

		dialog_done_time = level.time + dialog_length;

		if (dialog_length > 0)
			{
			int tag_num;

			if ( state_name != NULL && currentState )
				{
				if ( mode == ACTOR_MODE_SCRIPT || mode == ACTOR_MODE_IDLE )
					{
					dialog_old_state_name = currentState->getName();
					dialog_state_name = state_name;

					Event *idle_event = new Event( EV_Actor_Idle );
					idle_event->AddString( state_name );
					ProcessEvent( idle_event );
					}
				}

			tag_num = gi.Tag_NumForName( edict->s.modelindex, "tag_mouth" );

			if ( tag_num != -1 )
				{
				SetControllerTag( ACTOR_MOUTH_TAG, tag_num );

				for( current_amplitude = 0 ; current_amplitude < number_of_amplitudes ; current_amplitude++ )
					{
					new_event = new Event ( EV_SetControllerAngles );

					new_event->AddInteger( ACTOR_MOUTH_TAG );

					angle = ( dialog_amplitudes[current_amplitude] / 256.0 ) * max_mouth_angle;
					mouth_angles = vec_zero;
					mouth_angles[PITCH] = angle;

					new_event->AddVector( mouth_angles );

					PostEvent( new_event, current_amplitude * (1.0 / LIP_SYNC_HZ), EVENT_DIALOG_ANIM );

					if ( current_amplitude % 10 == 0 )
						PostEvent( EV_Actor_HeadTwitch, current_amplitude * (1.0 / LIP_SYNC_HZ), EVENT_DIALOG_ANIM );
					}
				}

			PostEvent( EV_Actor_DialogDone, dialog_length );

			new_event = new Event ( EV_Actor_HeadTwitch );
			new_event->AddInteger( 1 );
			PostEvent( new_event, dialog_length, EVENT_DIALOG_ANIM );
			}
		else
			{
				SetActorFlag( ACTOR_FLAG_DIALOG_PLAYING, false );
				gi.DPrintf( "Lip file not found for dialog %s\n", dialog_name );
			}
   	}
   }

void Actor::StopDialog
	(
	Event *ev
	)

	{
	StopSound( CHAN_DIALOG );

	CancelEventsOfType( EV_SetControllerAngles );
	CancelEventsOfType( EV_Actor_DialogDone );
	CancelEventsOfType( EV_Actor_HeadTwitch );
	CancelEventsOfType( EV_Actor_HeadTwitchEveryFrame );

	ProcessEvent( EV_Actor_DialogDone );
	}
	

void Actor::HeadTwitch
	(
	Event *ev
	)

	{
	qboolean end = false;
	Vector real_head_angles;
	float pitch_change;
	float roll_change;
	Event *event;


	if ( ev->NumArgs() > 0 )
		end = ev->GetInteger( 1 );

	SetControllerTag( ACTOR_HEAD_TAG, gi.Tag_NumForName( edict->s.modelindex, "Bip01 Head" ) );

	real_head_angles = GetControllerAngles( ACTOR_HEAD_TAG );

	CancelEventsOfType( EV_Actor_HeadTwitchEveryFrame );

	if ( end )
		{
		// Put head back to normal

		SetControllerTag( ACTOR_HEAD_TAG, gi.Tag_NumForName( edict->s.modelindex, "Bip01 Head" ) );

		real_head_angles[PITCH] = real_head_pitch;
		real_head_angles[ROLL]  = 0;
		SetControllerAngles( ACTOR_HEAD_TAG, real_head_angles );
		CancelEventsOfType( EV_Actor_HeadTwitch );
		}
	else
		{
		pitch_change = (real_head_pitch + G_CRandom( 6 ) ) - real_head_angles[PITCH];
		roll_change  = G_CRandom( 6 ) - real_head_angles[ROLL];

		event = new Event( EV_Actor_HeadTwitchEveryFrame );

		event->AddFloat( pitch_change / 10 );
		event->AddFloat( roll_change / 10 );

		PostEvent( event, FRAMETIME );
		}
	}

void Actor::HeadTwitchEveryFrame
	(
	Event *ev
	)

	{
	Vector real_head_angles;
	float pitch_change;
	float roll_change;
	

	pitch_change = ev->GetFloat( 1 );
	roll_change  = ev->GetFloat( 1 );

	SetControllerTag( ACTOR_HEAD_TAG, gi.Tag_NumForName( edict->s.modelindex, "Bip01 Head" ) );

	real_head_angles = GetControllerAngles( ACTOR_HEAD_TAG );

	if ( GetActorFlag( ACTOR_FLAG_TURNING_HEAD ) )
		{
		// Can only change roll

		real_head_angles[ROLL]  += roll_change;
		SetControllerAngles( ACTOR_HEAD_TAG, real_head_angles );
		}
	else
		{
		real_head_angles[PITCH] += pitch_change;
		real_head_angles[ROLL]  += roll_change;
		SetControllerAngles( ACTOR_HEAD_TAG, real_head_angles );
		}

	PostEvent( *ev, FRAMETIME );
	}

float Actor::GetDialogRemainingTime
   ( 
   void
   )

   {
	if ( GetActorFlag( ACTOR_FLAG_DIALOG_PLAYING ) )
		{
		return dialog_done_time - level.time;
		}
	else
		{
		return 0;
		}
   }

void Actor::FreeDialogList
   ( 
   void
   )

   {
	DialogNode_t *dialog_node;

	dialog_node = dialog_list;

	while( dialog_node != NULL )
	   {
		dialog_list = dialog_node->next;

		delete dialog_node;

		dialog_node = dialog_list;
	   }
   }

void Actor::DialogDone
   (
   Event *ev
   )

   {
	SetActorFlag( ACTOR_FLAG_DIALOG_PLAYING, false );

	if ( dialog_state_name )
		{
		dialog_state_name = "";

		if ( mode != ACTOR_MODE_AI && mode != ACTOR_MODE_TALK )
			{
			if ( dialog_old_state_name.length() )
				SetState( dialog_old_state_name.c_str() );
			}
		}
   }

void Actor::SetMouthAngle	
	(
	Event *ev
	)

	{
	int tag_num;
	float angle_percent;
	Vector mouth_angles;


	angle_percent = ev->GetFloat( 1 );

	if ( angle_percent < 0 )
		angle_percent = 0;

	if ( angle_percent > 1 )
		angle_percent = 1;

	tag_num = gi.Tag_NumForName( edict->s.modelindex, "tag_mouth" );

	if ( tag_num != -1 )
		{
		SetControllerTag( ACTOR_MOUTH_TAG, tag_num );

		mouth_angles = vec_zero;
		mouth_angles[PITCH] = max_mouth_angle * angle_percent;

		SetControllerAngles( ACTOR_MOUTH_TAG, mouth_angles );
		}
	}

//***********************************************************************************************
//
// Mode functions
//
//***********************************************************************************************


qboolean Actor::ModeAllowed( int new_mode )
	{
	if ( deadflag && actortype != IS_INANIMATE )
		return false;

	if ( new_mode == ACTOR_MODE_SCRIPT || new_mode == ACTOR_MODE_IDLE )
		{
		if ( mode == ACTOR_MODE_AI || mode == ACTOR_MODE_TALK )
			return false;
		}
	else if ( new_mode == ACTOR_MODE_TALK )
		{
		if ( mode == ACTOR_MODE_AI || mode == ACTOR_MODE_TALK || actortype != IS_FRIEND || !GetActorFlag( ACTOR_FLAG_ALLOW_TALK ) || 
			  !dialog_list || level.cinematic )
			return false;
		}

	return true;
	}

void Actor::StartMode( int new_mode )
	{
	if ( new_mode == ACTOR_MODE_TALK )
		{
		SaveMode();
		CancelEventsOfType( EV_Actor_FinishedBehavior );
		RemoveAnimDoneEvent();
		}

	mode = new_mode;
	}

void Actor::EndMode( void )
	{
	str currentanim;

	if ( mode == ACTOR_MODE_AI )
		{
		if ( GetActorFlag( ACTOR_FLAG_UPDATE_BOSS_HEALTH ) && max_boss_health )
			{
			char bosshealth_string[20];
			sprintf( bosshealth_string, "%.5f", 0 );
			gi.cvar_set( "bosshealth", bosshealth_string );
			}

		mode = ACTOR_MODE_IDLE;
		ProcessEvent( EV_Actor_Idle );

		currentanim = currentState->getLegAnim( *this, &conditionals );

		if ( currentanim.length() && currentanim != animname )
			SetAnim( currentanim, EV_Anim_Done );

		currentEnemy = NULL;
		}
	else if ( mode == ACTOR_MODE_TALK )
		{
		next_player_near = level.time + 5.0;
		RestoreMode();
		}
	}

void Actor::SaveMode( void )
	{
	if ( mode == ACTOR_MODE_IDLE )
		{
		saved_mode       = ACTOR_MODE_IDLE;
		saved_state_name = currentState->getName();
		}
	else if ( mode == ACTOR_MODE_SCRIPT )
		{
		saved_mode            = ACTOR_MODE_SCRIPT;
		saved_behavior        = behavior;
		saved_scriptthread    = scriptthread;
		saved_actorthread     = actorthread;
		saved_anim_name       = animname;
		saved_anim_event_name = last_anim_event_name;

		behavior     = NULL;
		scriptthread = NULL;
		actorthread  = NULL;
		}
	else 
		{
		gi.DPrintf( "Can't saved specified mode: %d\n", mode );
		}
	}

void Actor::RestoreMode( void )
	{
	Event *idle_event;

	if ( saved_mode == ACTOR_MODE_IDLE )
		{
		mode = ACTOR_MODE_IDLE;

		idle_event = new Event( EV_Actor_Idle );
		idle_event->AddString( saved_state_name );
		ProcessEvent( idle_event );
		//StartMode( ACTOR_MODE_IDLE );
		}
	else if ( saved_mode == ACTOR_MODE_SCRIPT )
		{
		StartMode( ACTOR_MODE_SCRIPT );

		behavior     = saved_behavior;
		scriptthread = saved_scriptthread;
		actorthread  = saved_actorthread;

		if ( saved_behavior )
			currentBehavior = saved_behavior->getClassname();
		else
			currentBehavior = "";

		if ( saved_anim_event_name.length() )
			{
			Event *event = new Event( saved_anim_event_name.c_str() );
			SetAnim( saved_anim_name, event );
			}
		else
			SetAnim( saved_anim_name );
		}
	else
		{
		gi.DPrintf( "Can't restore specified mode: %d\n", saved_mode );
		}

	saved_mode = ACTOR_MODE_NONE;
	}


//***********************************************************************************************
//
// Finishing functions
//
//***********************************************************************************************


qboolean Actor::CanBeFinished
	(
	void
	)
	{
	// See if actor can be finished by any means of death

	if ( can_be_finsihed_by_mods.NumObjects() > 0 )
		return true;
	else
		return false;
	}

qboolean Actor::CanBeFinishedBy
	(
	int meansofdeath
	)
	{
	int number_of_mods;
	int i;

	// Make sure in limbo

	if ( !InLimbo() )
		return false;

	// Make sure can be finished by this means of death

	number_of_mods = can_be_finsihed_by_mods.NumObjects();

	for( i = 1 ; i <= number_of_mods ; i++ )
		{
		if ( meansofdeath == can_be_finsihed_by_mods.ObjectAt( i ) )
			return true;
		}

	return false;
	}

void Actor::SetCanBeFinishedBy
	(
	Event *ev
	)
	{
	str mod_string;
	int new_mod;
	int number_of_mods;
	int i;


	number_of_mods = ev->NumArgs();

	for ( i = 1 ; i <= number_of_mods ; i++ )
		{
		mod_string = ev->GetString( i );

		new_mod = MOD_string_to_int( mod_string );

		if ( new_mod != -1 )
			can_be_finsihed_by_mods.AddObject( new_mod );
		}
	}

void Actor::Finish
	(
	int meansofdeath
	)
	{
	// Make sure we can be finsihed by this means of death

	if ( CanBeFinishedBy( meansofdeath ) )
		{
		// Save that the actor is being finished

		SetActorFlag( ACTOR_FLAG_FINISHED, true );

		// Kill the actor

		ProcessEvent( EV_Actor_Suicide );

		// Make sure the correct means of death is set

		means_of_death = meansofdeath;
		}
	else
		{
		gi.DPrintf( "Actor can't be finished by %d means of death\n", meansofdeath );
		}
	}

void Actor::StartLimbo
	(
	void
	)
	{
	State	*temp_state;
	qboolean found_state;

	// Make sure we have a little bit of health

	health = 1;

	// Go to the limbo state

	found_state = false;

	if ( statemap )
		{
		temp_state = statemap->FindState( "LIMBO" );

		if ( temp_state )
			{
			currentState = temp_state;
			InitState();
			found_state = true;
			SetActorFlag( ACTOR_FLAG_IN_LIMBO, true );
			}
		}

	if ( !found_state )
		{
		// Didn't find a limbo state so just die 

		ProcessEvent( EV_Actor_Suicide );
		}
	}

qboolean Actor::InLimbo
	(
	void
	)
	{
	return GetActorFlag( ACTOR_FLAG_IN_LIMBO );
	}


//***********************************************************************************************
//
// General functions
//
//***********************************************************************************************

void Actor::AlwaysGiveWater
   (
   Event *ev
   )
	{
	SetActorFlag( ACTOR_FLAG_ALWAYS_GIVE_WATER, ev->GetBoolean( 1 ) );
	}

void Actor::IgnorePainFromActors
   (
   Event *ev
   )
	{
	SetActorFlag( ACTOR_FLAG_IGNORE_PAIN_FROM_ACTORS, true );
	}

void Actor::UpdateBossHealth
   (
   Event *ev
   )
	{
	SetActorFlag( ACTOR_FLAG_UPDATE_BOSS_HEALTH, true );
	}

void Actor::SetMaxBossHealth
   (
   Event *ev
   )
	{
	max_boss_health = ev->GetFloat( 1 );
	}

void Actor::SetWaterLevel
   (
   Event *ev
   )
	{
	water_level = ev->GetFloat( 1 );
	}

void Actor::IncrementNumSpawns
   (
   Event *ev
   )
	{
	num_of_spawns++;
	}

void Actor::DecrementNumSpawns
   (
   Event *ev
   )
	{
	num_of_spawns--;

	if ( num_of_spawns < 0 )
		num_of_spawns = 0;
	}

void Actor::TouchTriggers
   (
   Event *ev
   )
	{
	SetActorFlag( ACTOR_FLAG_TOUCH_TRIGGERS, ev->GetBoolean( 1 ) );
	}

void Actor::IgnoreWater
   (
   Event *ev
   )
	{
	SetActorFlag( ACTOR_FLAG_IGNORE_WATER, ev->GetBoolean( 1 ) );
	}

void Actor::SetNotAllowedToKill
   (
   Event *ev
   )
	{
	SetActorFlag( ACTOR_FLAG_ALLOWED_TO_KILL, false );
	}

void Actor::IgnorePlacementWarning
   (
   Event *ev
   )

	{
	str warning;

	warning = ev->GetString( 1 );

	if ( warning == "stuck" )
		SetActorFlag( ACTOR_FLAG_IGNORE_STUCK_WARNING, true );
	else if ( warning == "off_ground" )
		SetActorFlag( ACTOR_FLAG_IGNORE_OFF_GROUND_WARNING, true );
	}

void Actor::SetTargetable
   (
   Event *ev
   )

	{
	qboolean bool;

	bool = ev->GetBoolean( 1 );

	SetActorFlag( ACTOR_FLAG_TARGETABLE, bool );
	}

qboolean Actor::CanTarget
   (
   void
   )

	{
	return GetActorFlag( ACTOR_FLAG_TARGETABLE );
	}

void Actor::SetSpawnChance
   (
   Event *ev
   )

	{
	spawn_chance = ev->GetFloat( 1 );
	}

void Actor::AddSpawnItem
   (
   Event *ev
   )

	{
	str spawn_item_name;

	spawn_item_name = ev->GetString( 1 );

	spawn_items.AddObject( spawn_item_name );
	}

void Actor::ClearSpawnItems
   (
   Event *ev
   )

	{
	spawn_items.ClearObjectList();
	}

void Actor::SpawnItems
   (
   void
   )

	{
	int number_of_spawn_items;
	int i;
	qboolean spawn_random = false;
	str spawn_item_name;
	Player *player;
	float health_chance;
	float water_chance;
	float total_chance;
	float plasma_chance;
	float bullets_chance;
	float player_health;
	float player_water;
	int player_plasma;
	int player_bullets;
	float random_number;
	qboolean has_gun;
	qboolean has_crossbow;


	number_of_spawn_items = spawn_items.NumObjects();

	// Spawn in all of the items in the spawn_item list

	if ( number_of_spawn_items )
		{
		for( i = 1 ; i <= number_of_spawn_items ; i++ )
			{
			spawn_item_name = spawn_items.ObjectAt( i );

			if ( spawn_item_name == "random" )
				spawn_random = true;
			else
				SpawnItem( spawn_item_name );
			}
		}
	else
		{
		spawn_random = true;
		}

	// See if we should spawn a random item

	if ( spawn_random )
		{
		if ( G_Random( 100 ) < spawn_chance )
			{
			// Set up default chances

			health_chance  = 1;
			water_chance   = 1;
			plasma_chance  = 1;
			bullets_chance = 1;

			// See what he player needs

			player = (Player *)g_entities[ 0 ].entity;

			player_health  = player->health;
			player_water   = player->GetWaterPower();
			player_plasma  = player->AmmoCount( "Plasma" );
			player_bullets = player->AmmoCount( "Bullet" );

			has_gun      = player->HasItem( "HandGun" );
			has_crossbow = player->HasItem( "Crossbow" );

			// See if the player is low on health

			if ( player_health <= 50 )
				health_chance *= (60 - player_health) / 10;

			if ( player_water <= 50 )
				water_chance *= (60 - player_water) / 10;

			if ( player_plasma <= 20 )
				plasma_chance *= (30 - player_plasma) / 10;

			if ( !has_crossbow )
				plasma_chance = 0;

			if ( player_bullets <= 50 )
				bullets_chance *= (60 - player_bullets) / 10;

			if ( !has_gun )
				bullets_chance = 0;

			// Choose something randomly

			total_chance = health_chance + water_chance + plasma_chance + bullets_chance;

			random_number = G_Random( total_chance );

			if ( random_number < health_chance )
				{
				if ( G_Random( 10 ) < health_chance )
					SpawnItem( "item_bighealthfruit1.tik" );
				else
					SpawnItem( "item_healthfruit1.tik" );
				}
			else if ( random_number < health_chance + water_chance )
				{
				if ( ( mass > 125 ) && ( G_Random( 4 ) < water_chance ) )
					SpawnItem( "item_bigwaterampoule.tik" );
				else
					SpawnItem( "item_waterampoule.tik" );
				}
			else if ( random_number < health_chance + water_chance + plasma_chance )
				SpawnItem( "ammo_plasma.tik" );
			else 
				{
				if ( G_Random( 10 ) < bullets_chance )
					SpawnItem( "ammo_uziclip.tik" );
				else
					SpawnItem( "ammo_gunclip.tik" );
				}
			}
		}
	}

void Actor::SpawnItem
   (
   str spawn_item_name
   )

	{
	SpawnArgs      args;
	Entity *ent;
	Item *item;


	args.setArg( "model", spawn_item_name );
	ent = args.Spawn();

	if ( !ent || !ent->isSubclassOf( Item ) )
		return;

	item = (Item *)ent;

	item->setOrigin( centroid );

	item->ProcessPendingEvents();

	item->PlaceItem();
	item->setOrigin( centroid );
	item->velocity = Vector( G_CRandom( 100 ), G_CRandom( 100 ), 200 + G_Random( 200 ) );
	item->edict->clipmask = CONTENTS_SOLID | CONTENTS_PLAYERCLIP;

	// Give the new item a targetname

	item->targetname = targetname;
	item->targetname += "_item";

	item->SetTargetName( item->targetname );
	}

qboolean Actor::CanJump( void )
	{
	return ( HasAnim( "jump" ) && HasAnim( "fall" ) && HasAnim( "land" ) );
	}

void Actor::SetUseGravity
   (
   Event *ev
   )

	{
	qboolean use_gravity;

	use_gravity = ev->GetBoolean( 1 );

	SetActorFlag( ACTOR_FLAG_USE_GRAVITY, use_gravity );

	if ( use_gravity )
		gravity = 1;
	else
		gravity = 0;
	}

void Actor::SetAllowFall
   (
   Event *ev
   )

	{
	qboolean allow_fall;

	if ( ev->NumArgs() > 0 )
		allow_fall = ev->GetBoolean( 1 );
	else
		allow_fall = true;
		
	SetActorFlag( ACTOR_FLAG_ALLOW_FALL, allow_fall );
	}

void Actor::SetHaveThing
   (
   Event *ev
   )

	{
	int thing_number;
	qboolean thing_bool;

	thing_number = ev->GetInteger( 1 );
	thing_bool   = ev->GetBoolean( 2 );

	switch( thing_number )
		{
		case 1 :
			SetActorFlag( ACTOR_FLAG_HAS_THING1, thing_bool );
			break;
		case 2 :
			SetActorFlag( ACTOR_FLAG_HAS_THING2, thing_bool );
			break;
		case 3 :
			SetActorFlag( ACTOR_FLAG_HAS_THING3, thing_bool );
			break;
		case 4 :
			SetActorFlag( ACTOR_FLAG_HAS_THING4, thing_bool );
			break;
		default :
			gi.DPrintf( "Has thing %d out of range\n", thing_number );
			return;
		}
	}

void Actor::SetActorFlag( int flag, qboolean flag_value )
	{
	unsigned int *flags;
	int index;

	if ( flag > ACTOR_FLAG_MAX )
		{
		gi.DPrintf( "Actor flag %d out of range\n", flag );
		return;
		}

	index = flag / 32;

	switch( index )
		{
		case 0 :
			flags = &actor_flags1;
			break;
		case 1 :
			flags = &actor_flags2;
			break;
		default :
			gi.DPrintf( "Actor flag %d out of range\n", flag );
			return;
		}
	
	if ( flag_value )
		*flags |= 1 << flag;
	else
		*flags &= ~( 1 << flag );
	}

qboolean Actor::GetActorFlag( int flag )
	{
	unsigned int *flags;
	int index;

	if ( flag > ACTOR_FLAG_MAX )
		{
		gi.DPrintf( "Actor flag %d out of range\n", flag );
		return false;
		}

	index = flag / 32;

	switch( index )
		{
		case 0 :
			flags = &actor_flags1;
			break;
		case 1 :
			flags = &actor_flags2;
			break;
		default :
			gi.DPrintf( "Actor flag %d out of range\n", flag );
			return false;
		}

	if ( *flags & ( 1 << flag ) )
		return true;
	else
		return false;
	}

void Actor::SetBounceOff
   (
   Event *ev
   )

	{
	SetActorFlag( ACTOR_FLAG_BOUNCE_OFF, true );
	}

void Actor::BounceOffEvent
   (
   Event *ev
   )

	{
	Vector object_origin;
	Entity *effect;
	Event *event;

	if ( bounce_off_effect.length() )
		{
		object_origin = ev->GetVector( 1 );

		effect = new Animate;
		effect->setModel( bounce_off_effect );

		effect->setOrigin( object_origin );
		effect->setSolidType( SOLID_NOT );

		event = new Event( EV_Remove );
		effect->PostEvent( event, 5 );
		}
	}

void Actor::SetBounceOffEffect
   (
   Event *ev
   )

	{
	bounce_off_effect = ev->GetString( 1 );
	}

void Actor::GotoNextStage
   (
   Event *ev
   )

	{
	stage++;
	}

void Actor::GotoPrevStage
   (
   Event *ev
   )

	{
	stage--;

	if ( stage < 1 )
		stage = 1;
	}

void Actor::GotoStage
   (
   Event *ev
   )

	{
	stage = ev->GetInteger( 1 );
	}

void Actor::NotifyOthersAtDeath
   (
   Event *ev
   )

	{
	SetActorFlag( ACTOR_FLAG_NOTIFY_OTHERS_AT_DEATH, true );
	}

void Actor::NotifyOthersOfDeath
	(
	void
	)

	{
	int i;
	Actor *act;

	for( i = 1; i <= ActiveList.NumObjects(); i++ )
      {
      act = ActiveList.ObjectAt( i );

		if ( name.length() && name == act->name && Vector( act->origin - origin ).length() < 1000 )
			act->AddStateFlag( STATE_FLAG_OTHER_DIED );
		}
	}

void Actor::Pickup
   (
   Event *ev
   )

   {
	str tag_name;
	int tag_num;
	Vector new_angles;

	tag_name = ev->GetString( 1 );
	tag_num  = gi.Tag_NumForName( edict->s.modelindex, tag_name.c_str() );

	new_angles = "0 0 0";

	if ( pickup_ent )
		{
		pickup_ent->setAngles( new_angles );
		pickup_ent->attach( entnum, tag_num );
		}
	}

void Actor::Throw
   (
   Event *ev
   )

   {
	int i;
	int num;
	Entity *child;
	Vector pos;
	Vector forward;
	str tag_name;
	int tag_num;


	tag_name = ev->GetString( 1 );
	tag_num  = gi.Tag_NumForName( edict->s.modelindex, tag_name.c_str() );


	for ( i=0,num = numchildren; i < MAX_MODEL_CHILDREN; i++ )
      {
      if ( children[i] == ENTITYNUM_NONE )
         {
         continue;
         }

		child = ( Entity * )G_GetEntity( children[i] );

		if ( child->edict->s.tag_num == tag_num )
			{
			child->detach();

			child->setSolidType( SOLID_BBOX );

			child->setAngles( angles );

			child->groundentity = NULL;

			tag_num = gi.Tag_NumForName( edict->s.modelindex, tag_name.c_str() );
			GetTag( tag_num, &pos, &forward );

			child->velocity = orientation[0];
			child->velocity *= 500;

			child->velocity.z = 400;
			}

      num--;

      if ( !num )
         break;
		}
	}

void Actor::SolidMask
	(
	Event *ev
	)

	{
	edict->clipmask = MASK_MONSTERSOLID;
	}

void Actor::IgnoreMonsterClip
	(
	Event *ev
	)

	{
	edict->clipmask &= ~CONTENTS_MONSTERCLIP;
	}

void Actor::NotSolidMask
	(
	Event *ev
	)

	{
	edict->clipmask = MASK_SOLID;
	}

void Actor::NoMask
	(
	Event *ev
	)

	{
	edict->clipmask = 0;
	}

void Actor::SetMask
	(
	Event *ev
	)

	{
	str mask_name;

	mask_name = ev->GetString( 1 );

	if ( mask_name == "monstersolid" )
		edict->clipmask = MASK_MONSTERSOLID;
	else if ( mask_name == "deadsolid" )
		edict->clipmask = MASK_DEADSOLID;
	else if ( mask_name == "none" )
		edict->clipmask = 0;
	else if ( mask_name == "pathsolid" )
		edict->clipmask = MASK_PATHSOLID;
	else
		gi.DPrintf( "Unknown mask name - %s\n", mask_name.c_str() );
	}

void Actor::SetWatchOffset
	(
	Event *ev
	)
	{
	watch_offset = ev->GetVector( 1 );
   }

void Actor::setSize
	(
	Vector min,
	Vector max
	)
	{
   min *= edict->s.scale;
   max *= edict->s.scale;
   Sentient::setSize( min, max );
   }

void Actor::SetHealth
	(
	Event *ev
	)

	{
	health = ev->GetFloat( 1 ) * edict->s.scale;
   max_health = health;
	}

void Actor::AddHealth
	(
	Event *ev
	)

	{
	float health_to_add;
	float maxhealth;


	health_to_add = ev->GetFloat( 1 );

	if ( ev->NumArgs() > 1 )
		maxhealth = ev->GetFloat( 2 );
	else
		maxhealth = max_health;

	health += health_to_add;

	if ( health > maxhealth )
		health = maxhealth;
	}

void Actor::SetTurnSpeed
	(
	Event *ev
	)

	{
   turnspeed = ev->GetFloat( 1 );
	}

void Actor::SetMaxInactiveTime
	(
	Event *ev
	)
	{
	max_inactive_time = ev->GetFloat( 1 );
	}

void Actor::SetFov
	(
	Event *ev
	)

	{
	fov = ev->GetFloat( 1 );
	fovdot = cos( fov * 0.5 * M_PI / 180.0 );
	}

void Actor::SetVisionDistance
   (
   Event *ev
   )

   {
   vision_distance = ev->GetFloat( 1 );
   }

bool Actor::IsEntityAlive
   (
   Entity *ent
   )

	{
	return ( ent && !ent->deadflag && (ent->health > 0) && !(ent->flags & FL_NOTARGET) && level.ai_on );
	}

void Actor::Name
	(
	Event *ev
	)
	{
	name = ev->GetString( 1 );
	}

void Actor::SetupTriggerField
	(
	Event *ev
	)
	{
	Vector min;
	Vector max;
	TouchField *trig;

	min = ev->GetVector( 1 );
	max = ev->GetVector( 2 );

	min = min + origin;
	max = max + origin;

	trig = new TouchField;
	trig->Setup( this, EV_ActorTriggerTouched, min, max, TRIGGER_PLAYERS | TRIGGER_MONSTERS );
	trigger = trig;
	}

void Actor::TriggerTouched
	(
	Event *ev
	)
	{
	Entity *other;

	other = ev->GetEntity( 1 );

	if ( 
         ( other->movetype != MOVETYPE_NONE ) && 
         ( other->movetype != MOVETYPE_STATIONARY ) && 
         ( IsEntityAlive( other ) )
      )
		AddStateFlag( STATE_FLAG_TOUCHED );
	}

void Actor::OnlyShootable
   (
   Event *ev
   )

	{
	setContents( CONTENTS_SHOOTABLE_ONLY );
	link();
	}

void Actor::AddStateFlag
   (
   unsigned int flag
   )

	{
	int current_other_part;
	part_t *other_part;
	Entity *other_ent;
	Actor *other_act;
	int current_part;
	part_t *part;


	// Update my state flags

	state_flags |= flag;

	// Update all the other parts of my state flags

	for ( current_other_part = 1 ; current_other_part <= parts.NumObjects() ; current_other_part++ )
		{
		other_part = &parts.ObjectAt( current_other_part );

		other_ent = other_part->ent;
		other_act = (Actor *)other_ent;

		// Look for ourselves in this part's part list

		for ( current_part = 1 ; current_part <= other_act->parts.NumObjects() ; current_part++ )
			{
			part = &other_act->parts.ObjectAt( current_part );

			if ( part->ent == this )
				{
				// Found ourselves, update state flags

				part->state_flags |= flag;
				}
			}
		}
	}

void Actor::ClearStateFlags
   (
   void
   )

	{
	int current_part;
	part_t *part;


	// Clear my state flags

	state_flags = 0;

	// Clear all the other parts state flags

	for ( current_part = 1 ; current_part <= parts.NumObjects() ; current_part++ )
		{
		part = &parts.ObjectAt( current_part );

		part->state_flags = 0;
		}
	}

void Actor::NoChatterEvent
	(
	Event *ev
	)

	{
	SetActorFlag( ACTOR_FLAG_NOCHATTER, true );
	}

void Actor::Chatter
	(
	const char *snd,
	float chance,
	float volume,
	int channel
	)

	{
   str realname;

	if ( GetActorFlag( ACTOR_FLAG_NOCHATTER ) || chattime > level.time )
		{
		return;
		}

	if ( G_Random( 10 ) > chance )
		{
		chattime = level.time + 1 + G_Random( 2 );
		return;
		}

   realname = GetRandomAlias( snd );
	if ( realname.length() > 1 )
		{
      float delay;

      delay = gi.SoundLength( realname.c_str() );

		if ( delay < 0 )
			gi.DPrintf( "Lip file not found for dialog %s\n", realname.c_str() );

		chattime = level.time + delay + 4 + G_Random( 5 );
		Sound( realname, channel, volume );
		}
	else
		{
      // set it into the future, so we don't check it again right away
		chattime = level.time + 1;
		}
	}

void Actor::ActivateEvent
	(
	Event *ev
	)

	{
	Entity *ent;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	ent = ev->GetEntity( 1 );
	SetVariable( "other", ent );

	ProcessEvent( EV_Actor_AttackPlayer );

	AddStateFlag( STATE_FLAG_ACTIVATED );
	}

void Actor::UseEvent
	(
	Event *ev
	)

	{
	Sentient *user;
	Talk *talk;


	AddStateFlag( STATE_FLAG_USED );

	if ( !ModeAllowed( ACTOR_MODE_TALK ) )
		return;

	StartMode( ACTOR_MODE_TALK );

	user = (Sentient *)ev->GetEntity( 1 );

	talk = new Talk;
	talk->SetUser( user );
	SetBehavior( talk );
	}

void Actor::Think
	(
	void
	)

	{

	// Update boss health if necessary

	if ( GetActorFlag( ACTOR_FLAG_UPDATE_BOSS_HEALTH ) && max_boss_health && mode == ACTOR_MODE_AI )
		{
		char bosshealth_string[20];
		sprintf( bosshealth_string, "%.5f", health / max_boss_health );
		gi.cvar_set( "bosshealth", bosshealth_string );
		}

	// Check for the ground

	if ( last_origin != origin )
		SetActorFlag( ACTOR_FLAG_HAVE_MOVED, true );

	if ( !( flags & FL_SWIM ) && !( flags & FL_FLY ) )
		{
		if ( GetActorFlag( ACTOR_FLAG_HAVE_MOVED ) || 
  		   ( groundentity && groundentity->entity && groundentity->entity->entnum != ENTITYNUM_WORLD ) )
			CheckGround();
		}

	// Do falling stuff

	if ( groundentity )
		{
		if ( !Immune( MOD_FALLING ) && !( flags & FL_FLY ) && ( origin.z + 1000 < last_ground_z ) )
			Damage( world, world, 1000, origin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_FALLING );

		last_ground_z = origin.z;
		}

	last_origin = origin;

	if ( !deadflag )
		{
		// Check to see if stunned

		CheckStun();

		// See if can talk to the player

		TryTalkToPlayer();

		// Make sure we can still see our enemy

		if ( max_inactive_time && currentEnemy && next_enemy_try_sight_time < level.time && !IsBlind() )
			{
			float next_sight_delay;

			next_sight_delay = max_inactive_time / 5 + G_CRandom( 0.5 );

			if ( next_sight_delay < 1 )
				next_sight_delay = 1;

			next_enemy_try_sight_time = level.time + next_sight_delay;

			if ( !level.ai_on )
				{
				last_enemy_sight_time = level.time;
				}
			else
				{
				if ( CanSeeEnemyFrom( origin ) )
					last_enemy_sight_time = level.time;

				if ( last_enemy_sight_time + max_inactive_time < level.time )
					currentEnemy = NULL;
				}
			}

		// If actor doesn't have an enemy right now try to find one
		if ( !IsBlind() && !IsEntityAlive ( currentEnemy ) && next_find_enemy_time <= level.time )
			{
			if ( level.ai_on )
				FindEnemy();
			next_find_enemy_time = level.time + .8 + G_Random( .4 );
			}

		// Make sure actor is not immobilized

		if ( flags & FL_IMMOBILE || flags & FL_PARTIAL_IMMOBILE )
			{
			StopAnimating();
			return;
			}

		// Do the state machine for this creature

		ProcessActorStateMachine();

		// See if we should go back to sleep

		if ( ( mode == ACTOR_MODE_AI || mode == ACTOR_MODE_IDLE ) && !currentEnemy && !GetActorFlag( ACTOR_FLAG_INVESTIGATING )
				&& next_try_sleep_time < level.time )
			{
			Entity *player;

			next_try_sleep_time = level.time + 1.0;

			player = g_entities[ 0 ].entity;

			if ( mode == ACTOR_MODE_IDLE && player && !(player->flags & FL_NOTARGET) && gi.inPVS( player->centroid, centroid ) &&
				( world->farplane_distance == 0 || Distance( player->centroid, centroid ) < world->farplane_distance ) )
				last_time_active = level.time;

			if ( !level.ai_on )
				last_time_active = level.time;

			if ( max_inactive_time && last_time_active + 5 < level.time )
				{
				if ( mode == ACTOR_MODE_AI )
					{
					EndMode();

					Sleep();

					if ( idle_thread.length() > 1 )
						{
						//ScriptThread *thread = ExecuteThread( idle_thread, false );

						actorthread = ExecuteThread( idle_thread, false );

						if ( actorthread )
							ProcessScript( actorthread, NULL );
						else
							warning( "Idle", "could not process idle_thread" );
						}
					}
				else
					{
					Sleep();
					}
				}
			}
		else if ( currentEnemy || GetActorFlag( ACTOR_FLAG_INVESTIGATING ) || mode == ACTOR_MODE_SCRIPT || mode == ACTOR_MODE_TALK )
			{
			last_time_active = level.time;
			}

		if ( actortype == IS_INANIMATE )
			{
			if ( behavior && !behavior->Evaluate( *this ) )
				{
				// stop thinking
				flags &= ~FL_THINK;
				EndBehavior();

				// remove them from the active list
				ActiveList.RemoveObject( ( Actor * )this );
				}
			return;
			}

		eyeposition[ 2 ] = maxs[ 2 ] + eyeoffset[ 2 ];
		//angles.z = 0;

		// Process the current behavior

		if ( behavior && !behavior->Evaluate( *this ) )
			{
			if ( stricmp( behavior->getClassname(), "Talk" ) == 0 )
				{
				EndBehavior();
				EndMode();
				}
			else
				{
				EndBehavior();
				}

			// Process state machine again because the behavior finished
			ProcessActorStateMachine();
			}

		// Reset the animation is done flag

		SetActorFlag( ACTOR_FLAG_ANIM_DONE, false );

		// Change the animation if necessary

		if ( newanimnum != -1 )
			ChangeAnim();
		}

	// Do the movement

	if ( !(flags & FL_IMMOBILE) && !(flags & FL_PARTIAL_IMMOBILE) )
		{
		CalcMove();
		lastmove = STEPMOVE_STUCK;

		if ( flags & FL_SWIM )
			lastmove = WaterMove();
		else if ( flags & FL_FLY )
			lastmove = AirMove();
		else
			lastmove = TryMove();
		}

	if ( !deadflag )
		{
		// See if we should damage the actor because of waterlevel

		if ( waterlevel == 3 && !( flags & FL_SWIM ) )
			{
			// if out of air, start drowning
			if ( air_finished < level.time )
				{
				// we may have been in a water brush when we spawned, so check our water level again to be sure
				CheckWater();
				if ( waterlevel < 3 )
					{
					// we're ok, so reset our air
					air_finished = level.time + 5;
					}
				else if ( next_drown_time < level.time && health > 0 )
					{
					// drown!
					next_drown_time = level.time + 1;

					//Sound( "snd_uwchoke", CHAN_VOICE );
					BroadcastSound();

					Damage( world, world, 15, origin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_DROWN );
					}
				}
			}
		else
			{
			air_finished = level.time + 5;
			}

		if ( 
            ( movetype != MOVETYPE_NONE ) &&
		      ( movetype != MOVETYPE_STATIONARY ) && 
				GetActorFlag( ACTOR_FLAG_TOUCH_TRIGGERS ) &&
				GetActorFlag( ACTOR_FLAG_HAVE_MOVED )
         )
			G_TouchTriggers( this );

		if ( groundentity && ( groundentity->entity != world ) && !M_CheckBottom( this ) )
			{
			// G_FixCheckBottom( this );
			flags |= FL_PARTIALGROUND;
			}
		}
	}

qboolean Actor::GetClosestTag
   (
   str tag_name, 
   int number_of_tags, 
   Vector target, 
   Vector *orig
   )

	{
	str temp_tag_name;
	Vector temp_orig;
	Vector diff;
	float dist;
	float best_dist = -1;
	qboolean found = false;
	int i;
	char number[5];

	if ( number_of_tags == 1 )
      {
		return GetTag( tag_name.c_str(), orig );
      }

	for( i = 1 ; i <= number_of_tags ; i++ )
		{
		sprintf( number, "%d", i );

		temp_tag_name = tag_name + str( number );

		if ( GetTag( temp_tag_name.c_str(), &temp_orig ) )
			{
			diff = target - temp_orig;
			dist = diff * diff;

			if ( dist < best_dist || best_dist < 0 )
				{
				best_dist = dist;
				found = true;
				*orig = temp_orig;
				}
			}
		}

	return found;
	}

void Actor::Active
	(
	Event *ev
	)
	{
	int active_flag;

	if ( ev->NumArgs() > 0 )
		{
		active_flag = ev->GetInteger( 1 );

		if ( active_flag )
			SetActorFlag( ACTOR_FLAG_INACTIVE, false );
		else
			SetActorFlag( ACTOR_FLAG_INACTIVE, true );
		}
	}

void Actor::SpawnActorAtLocation
	(
	Event *ev
	)
	{
	str model_name;
	str pathnode_name;
	qboolean attack;
	Vector orig;
	Vector ang;
	float width;
	float height;
	PathNode *goal;
	int number_of_pathnodes;
	Animate *effect;
	trace_t trace;
	Vector spawn_mins;
	Vector spawn_maxs;


	model_name          = ev->GetString( 1 );
	pathnode_name       = ev->GetString( 2 );
	number_of_pathnodes = ev->GetInteger( 3 );
	attack              = ev->GetBoolean( 4 );
	width	              = ev->GetFloat( 5 );
	height	           = ev->GetFloat( 6 );

	// Get the pathnode name to spawn in to

	pathnode_name += (int)( G_Random( number_of_pathnodes ) + 1 );

	// Find the path node

	goal = AI_FindNode( pathnode_name );

	if ( !goal )
		{
		gi.Printf( "Can't find position %s\n", pathnode_name.c_str() );
		return;
		}

	// Set the spawn in position/direction

	orig = goal->origin;
	ang = goal->angles;

	spawn_mins.x = -width;
	spawn_mins.y = -width;
	spawn_mins.z = 0;

	spawn_maxs.x = width;
	spawn_maxs.y = width;
	spawn_maxs.z = height;

	trace = G_Trace( orig + "0 0 64", spawn_mins, spawn_maxs, orig - "0 0 128", NULL, MASK_PATHSOLID, false, "SpawnActorAtLocation" );

	if ( trace.allsolid )
		return;

	orig = trace.endpos;

	SpawnActor( model_name, orig, ang, 1, attack, width, height );

	// Spawn in teleport effect

	effect = new Animate;
	effect->setModel( "fx_teleport3.tik" );
	effect->setOrigin( orig );
	effect->setSolidType( SOLID_NOT );
	effect->RandomAnimate( "idle", EV_Remove );
	effect->Sound( "snd_teleport" );
	}

void Actor::SpawnActorAtTag
	(
	Event *ev
	)
	{
	str model_name;
	str tag_name;
	int how_many;
	qboolean attack;
	float spawn_offset = 0;
	Vector tag_orig;
	Vector tag_dir;
	Vector new_orig;
	Vector new_dir;
	float width;
	float height;


	model_name = ev->GetString( 1 );
	tag_name   = ev->GetString( 2 );
	how_many   = ev->GetInteger( 3 );
	attack     = ev->GetBoolean( 4 );
	width	     = ev->GetFloat( 5 );
	height	  = ev->GetFloat( 6 );

	if ( ev->NumArgs() > 6 )
		spawn_offset = ev->GetFloat( 7 );

	// Calculate a good origin/angles

	GetTag( tag_name.c_str(), &tag_orig, &tag_dir );

	new_orig = tag_orig + tag_dir * spawn_offset;
	new_dir  = tag_dir * -1;

	SpawnActor( model_name, new_orig, new_dir, how_many, attack, width, height );
	}

void Actor::SpawnActor
	(
	str		model_name,
	Vector	orig, 
	Vector	ang, 
	int		how_many, 
	qboolean	attack, 
	float		width, 
	float		height
	)

	{
	Actor *new_actor;
	int current_actor;
	trace_t trace;
	Vector spawn_mins;
	Vector spawn_maxs;


	// Make sure this origin is reasonable

	spawn_mins[0] = -width;
	spawn_mins[1] = -width;
	spawn_mins[2] = 0;

	spawn_maxs[0] = width;
	spawn_maxs[1] = width;
	spawn_maxs[2] = height;

	//trace = G_Trace( tag_orig, spawn_mins, spawn_maxs, new_orig, this, MASK_MONSTERSOLID, false, "Actor::SpawnActor" );
	trace = G_Trace( orig, spawn_mins, spawn_maxs, orig, NULL, MASK_MONSTERSOLID, false, "Actor::SpawnActor" );

	if ( trace.fraction != 1 || trace.allsolid )
		return;

	// Spawn in all new actors

	for( current_actor = 0 ; current_actor < how_many ; current_actor++ )
		{
		new_actor = new Actor;
		new_actor->setModel( model_name );

		new_actor->setOrigin( orig );
		new_actor->setAngles( ang );

		// Make new actor attack player if requested

		if ( attack )
			new_actor->PostEvent( EV_Actor_AttackPlayer, 0 );

		// Update number of spawns

		num_of_spawns++;

		// Save our parent

		new_actor->spawnparent = this;

		// Give the new actor a targetname

		new_actor->targetname = targetname;
		new_actor->targetname += "_spawned";

		new_actor->SetTargetName( new_actor->targetname );
		}
	}

void Actor::TryTalkToPlayer( void )
	{
	int player_near = false;
	Entity *ent_in_range;
   int i;
	Vector delta;
	gentity_t *ed;
	float dist2;
	Sentient	*user = NULL;
	Talk *talk;


	// See if we should even bother looking for players

	if ( level.cinematic )
		next_player_near = level.time + 5.0;

	if ( deadflag || actortype != IS_FRIEND || next_player_near > level.time || !ModeAllowed( ACTOR_MODE_TALK ) )
		return;

	next_player_near = level.time + .2 + G_Random( .1 );

	// See if we are near the player

	for( i = 0 ; i < game.maxclients; i++ )
      {
      ed = &g_entities[ i ];

		if ( !ed->inuse || !ed->entity )
			continue;

		ent_in_range = ed->entity;

		if ( EntityHasFireType( ent_in_range, FT_MELEE ) || EntityHasFireType( ent_in_range, FT_BULLET ) ||
			  EntityHasFireType( ent_in_range, FT_PROJECTILE ) )
			continue;

		if ( IsEntityAlive( ent_in_range ) && ent_in_range->velocity == vec_zero )
         {
         delta = centroid - ent_in_range->centroid;

		   // dot product returns length squared

			dist2 = delta * delta;

		   if ( ( dist2 <= 100 * 100 ) && CanSee( ent_in_range ) )
				{
				player_near = true;
				user = (Sentient *)ent_in_range;
				}
         }
		}

	if ( !player_near )
		{
		SetActorFlag( ACTOR_FLAG_LAST_TRY_TALK, false );
		return;
		}

	if ( !GetActorFlag( ACTOR_FLAG_LAST_TRY_TALK ) )
		{
		SetActorFlag( ACTOR_FLAG_LAST_TRY_TALK, true );
		return;
		}

	SetActorFlag( ACTOR_FLAG_LAST_TRY_TALK, false );

	// Go to talk mode

	StartMode( ACTOR_MODE_TALK );

	talk = new Talk;
	talk->SetUser( user );
	SetBehavior( talk );
	}

void Actor::AllowTalk( Event *ev )
	{
	SetActorFlag( ACTOR_FLAG_ALLOW_TALK, ev->GetBoolean( 1 ) );
	}

void Actor::AllowHangBack( Event *ev )
	{
	SetActorFlag( ACTOR_FLAG_ALLOW_HANGBACK, ev->GetBoolean( 1 ) );
	}

qboolean Actor::CheckBottom( void )
	{
	//Vector	test_mins, test_maxs;
	Vector	start, stop;
	trace_t	trace;
	int		x, y;
	int		corners_ok;
	int		middle_ok;
	float		width;


	width = maxs[0];


   //test_mins = origin + mins;
   //test_maxs = origin + maxs;

	// First see if the origin is on a solid (this is the really simple test)

	start = origin - Vector(0, 0, 1);

	if ( gi.pointcontents( start, 0 ) == CONTENTS_SOLID )
		return true;

	// Next see if at least 3 corners are on a solid (this is the simple test)

	corners_ok = 0;

	start[ 2 ] = absmin[ 2 ] - 1;

	for( x = 0; x <= 1; x++ )
		{
		for( y = 0; y <= 1; y++ )
			{
			start[ 0 ] = x ? absmax[ 0 ] : absmin[ 0 ];
			start[ 1 ] = y ? absmax[ 1 ] : absmin[ 1 ];

			if ( gi.pointcontents( start, 0 ) == CONTENTS_SOLID )
				corners_ok++;
			}
		}

	if ( corners_ok >= 3 )
		return true;

	// Next do the hard test

	corners_ok = 0;
	middle_ok = 0;

	// Test the origin (if it is close to ground is a plus)

	start = origin;
	stop = start - Vector(0, 0, width); // Test down as far as the actor is wide

	trace = G_Trace( start, vec_zero, vec_zero, stop, this, (CONTENTS_SOLID|CONTENTS_MONSTERCLIP), false, "CheckBottom 1" );

	if ( trace.fraction < 1 && trace.plane.normal[2] > .7 )
		middle_ok = 1;

	// Test all of the corners

	for( x = 0; x <= 1; x++ )
		{
		for( y = 0; y <= 1; y++ )
			{
			start[ 0 ] = x ? absmax[ 0 ] : absmin[ 0 ];
			start[ 1 ] = y ? absmax[ 1 ] : absmin[ 1 ];
			start[ 2 ] = origin[ 2 ];

			stop = start - Vector(0, 0, 2 * width);

			trace = G_Trace( start, vec_zero, vec_zero, stop, this, (CONTENTS_SOLID|CONTENTS_MONSTERCLIP), false, "CheckBottom 2" );

			if ( trace.fraction < 1 && trace.plane.normal[2] > .7 )
				corners_ok++;

			if ( ( middle_ok && corners_ok >= 1 ) || ( corners_ok >= 3 ) )
				return true;
			}
		}

	return false;
	}

void Actor::ChangeType
	(
	Event *ev
	)

	{
	velocity = vec_zero;
	setModel( ev->GetString( 1 ) );
	PostEvent( EV_Actor_Wakeup, FRAMETIME );
	NoLerpThisFrame();
	}

void Actor::GetStateAnims
   (
   Container<const char *> *c
   )

   {
   statemap->GetAllAnims( c );
   }

void Actor::Touched
	(
	Event *ev
	)
	{
	Entity *other;

	other = ev->GetEntity( 1 );

	if ( other && other->isSubclassOf( Player ) && !Likes( other ) )
		Stimuli( STIMULI_SIGHT, other, false );
	}


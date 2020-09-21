//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/player.cpp                         $
// $Revision:: 392                                                            $
//   $Author:: Markd                                                          $
//     $Date:: 8/11/00 7:47p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/player.cpp                              $
// 
// 392   8/11/00 7:47p Markd
// changed a forcemenu from main to demomain for demo
// 
// 391   8/04/00 6:06p Markd
// added BeginCinematic and EndCinematic to coolitem code
// 
// 389   7/30/00 2:55p Markd
// initialized outfit_level on cleanup
// 
// 388   7/30/00 2:48a Aldie
// Added a fudge factor to wall hang
// 
// 387   7/29/00 9:05p Aldie
// Fixed armor order
// 
// 386   7/29/00 3:59p Aldie
// Fix some fade stuff
// 
// 385   7/29/00 2:28p Aldie
// Added a nosound weapon check
// 
// 384   7/29/00 12:57p Aldie
// Fixed some ammo check stuff
// 
// 383   7/29/00 12:54a Aldie
// Put a couple more checks in checkcanhang
// 
// 382   7/28/00 11:59p Aldie
// Added forcemenu
// 
// 381   7/28/00 6:58p Steven
// Made crosshairs get hidden when in cinematics.
// 
// 380   7/28/00 1:14p Aldie
// Made crosshair collide with the water
// 
// 379   7/28/00 1:10a Markd
// fixed outfit bug
// 
// 378   7/27/00 11:23p Aldie
// Added a loadstatetable to the archiveperstdata
// 
// 377   7/27/00 9:43p Aldie
// Changed dialog for invalid save games
// 
// 376   7/27/00 5:16p Markd
// fixed legsstate and torsostate bugs, made canbeUsed pass int the activator
// 
// 375   7/27/00 3:52p Aldie
// Changed over letterboxing and fades to the game code.  They are sent over in
// player stats and fields now.
// 
// 374   7/27/00 1:54a Markd
// changed g_playermodel to be more responsive
// 
// 373   7/26/00 6:06p Steven
// Added some reseting of weapon game vars.
// 
// 372   7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 371   7/25/00 2:41p Markd
// made terminal velocity lethal
// 
// 370   7/25/00 12:47p Markd
// Added new player sounds
// 
// 369   7/24/00 6:54p Steven
// Changed sv_cinematic from a cvar to a player stat and added actor_camera to
// this also.
// 
// 368   7/24/00 6:16p Aldie
// Pushmenu loadsave on death
// 
// 367   7/24/00 12:46p Markd
// fixed rope movment
// 
// 366   7/23/00 7:58p Steven
// Fixed some boss health stuff.
// 
// 365   7/23/00 6:03p Markd
// added fadeout and fadesound to dieing and level change
// 
// 364   7/23/00 5:02p Markd
// added boss health 
// 
// 363   7/22/00 8:37p Steven
// Fixed a prediction thing and added a sound effect to the electric spawn
// effect.
// 
// 362   7/22/00 12:52a Markd
// Added can_hang check
// 
// 361   7/21/00 10:49p Aldie
// Fixed an animstate problem when dying.
// 
// 360   7/21/00 8:36p Steven
// Got gravpaths working fairly well.
// 
// 359   7/21/00 3:45p Steven
// Made player have its own showmodel (event & proc) so we could do extra
// commands when the player is shown, fixed throwing evil shglieks, and fixed a
// knockdown bug.
// 
// 358   7/21/00 1:14a Markd
// fixed fakeplayer....again
// 
// 357   7/19/00 8:46p Markd
// added checkgroundentity
// 
// 356   7/19/00 8:19p Steven
// Made it so you wouldn't go to actor camera if already in another camera.
// 
// 355   7/19/00 7:26p Markd
// fixed weapons holstered code
// 
// 354   7/19/00 5:09p Steven
// Don't do pain event if no damage taken, added electric water means of death,
// and added a loaded proc called after load is done.
// 
// 353   7/19/00 3:12p Markd
// Fixed monkey bar problem
// 
// 352   7/19/00 11:07a Markd
// changed weapons_active to WeaponsOut
// 
// 351   7/18/00 5:19p Markd
// added weapons_active boolean
// 
// 350   7/18/00 5:01p Markd
// fixed monkeybar climbing
// 
// 349   7/18/00 4:25p Markd
// rewrote holstering code
// 
// 348   7/18/00 1:24p Markd
// changed FakePlayer so that it now works like it used to
// 
// 347   7/18/00 12:19p Aldie
// Fixed a bug with checkblocked timer
// 
// 346   7/17/00 9:51p Aldie
// Added skipcinematic command which is access by pressing the ESC key
// 
// 345   7/17/00 7:45p Markd
// made fakeplayer work better
// 
// 344   7/17/00 5:26p Aldie
// Fix for fakeplayer to droptofloor
// 
// 343   7/17/00 4:42p Aldie
// Removed a print
// 
// 342   7/17/00 4:19p Aldie
// Changed to using v_angle instead of torsoangles for some aiming stuff.
// 
// 341   7/17/00 3:26p Aldie
// Fix for flashbangs, changed detail variable, and added forcetorsostate
// 
// 340   7/17/00 2:56p Steven
// Made it so the player doesn't turn her head as far when looking at things.
// 
// 339   7/17/00 11:57a Aldie
// Changed some methods for checking weapons for attack
// 
// 338   7/16/00 3:08p Aldie
// Added some holster functions for firing and getting the weapons out.
// 
// 337   7/16/00 2:09p Aldie
// Changed some of the player logging
// 
// 336   7/16/00 10:46a Steven
// Improved head target stuff.
// 
// 335   7/15/00 3:52p Steven
// Only release the shgliek in a throw if he is not in a solid.
// 
// 334   7/15/00 2:26p Steven
// Made noclip movement much slower if walking.
// 
// 333   7/15/00 1:34p Aldie
// Added takepain command.  Allows control for taking pain or not.
// 
// 332   7/15/00 1:06p Aldie
// Added specialmove stuff for weapons so we can do special movement with some
// dualhanded weapons
// 
// 331   7/15/00 1:36a Markd
// fixed cool item issues
// 
// 330   7/14/00 11:45p Markd
// Added ambient sounds to func_supllywater
// 
// 329   7/14/00 10:04p Aldie
// Added g_logstats cvar
// 
// 328   7/14/00 9:46p Aldie
// Changed the way logstats start up
// 
// 327   7/14/00 8:21p Aldie
// Added logstats
// 
// 326   7/14/00 5:36p Markd
// took out hand offsets and fixed rolling coming out of cinematics
// 
// 325   7/13/00 11:10p Markd
// fixed bug in waitforstate, added waitforstate to legs as well as torso
// 
// 324   7/13/00 10:30p Markd
// fixed potential crash bug
// 
// 323   7/13/00 9:18p Markd
// added behind_nopitch camera type
// 
// 322   7/13/00 8:44p Markd
// fixed prediction on moving platforms
// 
// 321   7/13/00 6:24p Markd
// fixed hanging off slanted edges
// 
// 320   7/13/00 4:54p Steven
// Made sure the pitch and roll of a thrown shgliek is 0.
// 
// 319   7/13/00 4:13p Steven
// Fixed problem with give all cheat and made it so the fakeplayer can't die.
// 
// 318   7/13/00 3:19p Markd
// Turned off prediction when standing on non-world brushes
// 
// 317   7/12/00 6:34p Aldie
// Added in crosshair scaling for long distances
// 
// 316   7/12/00 5:36p Markd
// fixed ammo reporting to support bullets in clip
// 
// 315   7/12/00 3:46p Aldie
// Put in a fix for movecontrol_anim where the origin will not get set after a
// pmove
// 
// 314   7/12/00 2:54p Markd
// SetWaterPower on initialization
// 
// 313   7/12/00 2:10p Markd
// fixed water level hud problem
// 
// 312   7/12/00 11:27a Steven
// Changed water to a float.
// 
// 311   7/12/00 12:35a Markd
// made player invulnerable during cool item cinematic
// 
// 310   7/11/00 9:32p Markd
// Took out water flashing effect
// 
// 309   7/11/00 9:28p Markd
// added level.playeritem_edenwater
// 
// 308   7/11/00 7:09p Steven
// Made getting knocked onto the ground hurt the player if blow was blocked.
// 
// 307   7/11/00 3:11p Aldie
// Testing a fix for ::Killed by not stopping the animation and not cancelling
// the pending events.
// 
// 306   7/10/00 11:58p Markd
// fixed level exit issues
// 
// 305   7/10/00 11:54p Markd
// added exit level code
// 
// 304   7/10/00 9:27p Markd
// added ammo variables for how much ammo the player has.  Added levelvars and
// gamevars commands
// 
// 303   7/10/00 8:09p Markd
// fixed cool item pickup problems
// 
// 302   7/10/00 6:50p Markd
// fixed some issues with water running
// 
// 301   7/10/00 5:12p Markd
// made it so that waitForState supports partial names for waitforstate
// Changed archiving of persistant data
// 
// 300   7/10/00 10:41a Markd
// added waitforstate
// 
// 299   7/07/00 6:34p Steven
// Fixed checkblocked when immobile.
// 
// 298   7/07/00 7:32a Steven
// Made it so the player won't not thing she is blocked if immobilized.
// 
// 297   7/06/00 7:17p Aldie
// Added in HAS_ARMORPIECE state command
// 
// 296   7/06/00 4:51p Markd
// clamped server time on commands so no future packets will be processed
// 
// 295   7/06/00 3:37p Markd
// made it so when hurt, the camera is not turned off
// 
// 294   7/05/00 9:19p Markd
// tweaked armor stuff
// 
// 293   7/05/00 7:36p Steven
// Added more outfit stuff and added it to the saved PersistantData.
// 
// 292   7/05/00 6:14p Steven
// Change minimum water needed for turbo speed to 90 and added a damage
// multiplier for combos.
// 
// 291   7/05/00 4:17p Markd
// fixed cool item stuff
// 
// 290   7/04/00 6:45p Markd
// enhanced cool item features
// 
// 289   7/04/00 2:47p Markd
// added ai off to the cool item cinematics
// 
// 288   7/04/00 2:25p Markd
// added cool cinematic for new objects
// 
// 287   7/03/00 7:00p Steven
// Made throwing of the Shgliek based on the player's torso angles instead of
// her regular angles.
// 
// 286   7/03/00 10:23a Steven
// Added some knockback/knockdown stuff.
// 
// 285   7/02/00 6:46p Markd
// added spawn thread to PlayerStart
// 
// 284   7/01/00 6:55p Markd
// made fakeplayer think
// 
// 283   6/30/00 3:11p Markd
// fixed player rise issues
// 
// 282   6/29/00 9:32a Markd
// added camera_side_left and side_right support
// 
// 281   6/28/00 7:56p Aldie
// Added some pain stuff for use with death.
// 
// 280   6/27/00 2:48p Aldie
// Changed some weapon aiming stuff again.  Aimed shots are automatically
// determined now.
// 
// 279   6/26/00 8:21p Markd
// fixed player hanging off the side of horizontal pipes
// 
// 278   6/26/00 7:16p Markd
// tweaked player walking off ledges
// 
// 277   6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 276   6/26/00 9:42a Steven
// Made it so the player won't target things after being killed.
// 
// 275   6/25/00 2:51p Markd
// made use objects easier to use
// 
// 274   6/25/00 12:37p Markd
// fixed player getting stuck
// 
// 273   6/25/00 11:21a Markd
// fixed slime code for player
// 
// 272   6/23/00 8:34p Markd
// fixed player music issues
// 
// 271   6/22/00 8:04p Markd
// bullet proofed crosshair usage
// 
// 270   6/22/00 12:23p Markd
// must be able to push objects 8 units when pushing them
// 
// 269   6/17/00 11:09a Markd
// made it so that julie will not try to grab ledges that are moving
// 
// 268   6/16/00 11:28a Aldie
// Added a ground check to 'rise' to see if we are really rising above the
// ground
// 
// 267   6/15/00 5:50p Aldie
// Added rise checks
// 
// 266   6/15/00 3:54p Aldie
// Took out the legturn command.  We don't really need it. 
// 
// 265   6/15/00 2:54p Aldie
// Fix for the leg turning issue
// 
// 264   6/14/00 5:40p Aldie
// Added state ammo check for weapon in hand/mode
// 
// 263   6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 262   6/13/00 6:41p Markd
// Fixed pushing and pulling of objects
// 
// 261   6/10/00 1:50p Steven
// Added statemap caching.
// 
// 260   6/08/00 9:55a Markd
// added camera_type behind_fixed
// 
// 259   6/06/00 7:33p Aldie
// Fix for putting away weapons when crouching and fix for dualhanded weapon
// being out when 2 weapons are being wielded at once.
// 
// 258   6/06/00 5:20p Markd
// placed some assertions into infite state stuff
// 
// 257   6/06/00 5:02p Markd
// fixed player movement stuff
// 
// 256   6/06/00 3:23p Steven
// Now force a shgliek into AI mode if picked up.
// 
// 255   6/06/00 3:24p Aldie
// Fix for dead check
// 
// 254   6/06/00 12:19p Markd
// working on player movement
// 
// 253   6/05/00 6:31p Aldie
// Sped up water power effect and removed cleartorsoanim from the noclip
// resetting
// 
// 252   6/05/00 5:03p Aldie
// clear oldstats
// 
// 251   6/05/00 3:41p Steven
// Made player not solid when killed.
// 
// 250   6/05/00 3:33p Markd
// Fixed sound bug 
// 
// 249   6/05/00 3:29p Aldie
// Added flickering to waterstats
// 
// 248   6/04/00 6:52p Markd
// Added camera support to TouchAnim's cleaned up player camera interface
// 
// 247   6/04/00 3:49p Markd
// Added precise shadows to certain characters
// 
// 246   6/03/00 6:58p Markd
// don't swing legs when purely strafing
// 
// 245   6/03/00 3:14p Aldie
// Added damage effects to player and sentient 
// 
// 244   6/02/00 6:51p Markd
// added better camera look features
// 
// 243   6/02/00 2:01p Markd
// Fixed client persistant data issues
// 
// 242   6/01/00 7:02p Markd
// removed activeWeapon variable
// 
// 241   6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 240   6/01/00 2:47p Aldie
// Change crosshair distance and checkdeath
// 
// 239   5/31/00 5:05p Aldie
// New aiming method
// 
// 238   5/31/00 10:24a Markd
// Changed LoadingServer to LoadingSavegame
// 
// 237   5/30/00 6:54p Aldie
// Added a muzzle clear check
// 
// 236   5/30/00 5:06p Aldie
// Added large shield to prevent knockdowns
// 
// 235   5/30/00 4:42p Aldie
// Added direction support and knockdown support to player
// 
// 234   5/29/00 1:16p Markd
// 3rd round of saved games
// 
// 233   5/27/00 5:27p Markd
// zeroed out skipthread once executed
// 
// 232   5/27/00 5:14p Steven
// Added player head watch stuff.
// 
// 231   5/27/00 9:49a Steven
// Added RemoveTarget stuff.
// 
// 230   5/26/00 7:47p Aldie
// Added directonal damage to pain
// 
// 229   5/26/00 6:31p Aldie
// Added alternate fire to soulsucker and bug fix to AmmoAvailable()
// 
// 228   5/26/00 4:12p Aldie
// Fix another holster bug (crash)
// 
// 227   5/26/00 3:41p Aldie
// Fix for holstering in cinematic
// 
// 226   5/26/00 2:24p Aldie
// Added waitforplayer commands so we can use it for cinematics when waiting
// for player to finish holstering
// 
// 225   5/25/00 4:15p Aldie
// Added weapon holstering while crouching
// 
// 224   5/25/00 9:59a Steven
// Fixed picking up of the Shgliek.
// 
// 223   5/24/00 6:51p Aldie
// Made some code a little clearer for debugging
// 
// 222   5/24/00 3:46p Steven
// Made the player's splash a variable size based on the player's velocity.
// 
// 221   5/20/00 6:03p Aldie
// Fixed stat bug
// 
// 220   5/20/00 2:12p Steven
// Made it so if the player stands on an actor it will try to push the actor
// downwards.
// 
// 219   5/18/00 3:20p Markd
// added damage feedback
// 
// 218   5/17/00 7:38p Markd
// moved player into position when starting to push objects
// 
// 217   5/16/00 6:25p Markd
// Don't do monkeybar and pipe traces unless the player is on the ground
// 
// 216   5/15/00 2:19p Aldie
// Added new tempmodel system and added player accumulated pain
// 
// 215   5/11/00 11:12a Steven
// Added pushing actors out of the way and added a splash effect when the
// player lands in water.
// 
// 214   5/10/00 10:32a Steven
// Added com_blood stuff.
// 
// 213   5/08/00 10:55p Markd
// fixed water_power jumping
// 
// 212   5/08/00 6:15p Markd
// put in camera cut choice for state based camera types
// 
// 211   5/08/00 6:00p Aldie
// Comment out some debug stuff
// 
// 210   5/08/00 3:19p Aldie
// Added initial crosshair work
// 
// 209   5/06/00 5:25p Markd
// fixed camera and pipe hang issues
// 
// 208   5/06/00 3:15p Markd
// Fixed pipehanging
// 
// 207   5/06/00 2:10p Aldie
// Removed a comment
// 
// 206   5/06/00 1:28p Aldie
// Changed weapon fire check
// 
// 205   5/06/00 11:52a Markd
// fixed player orientation problems
// 
// 204   5/05/00 7:38p Aldie
// Fix dual weapon stats
// 
// 203   5/04/00 10:25p Markd
// fixed player orienation issues again
// 
// 202   5/04/00 5:01p Markd
// fixed player orientation problems
// 
// 201   5/02/00 6:42p Steven
// Made the fakeplayer a step size shorter to fix some collision issues.
// 
// 200   5/02/00 6:27p Markd
// Fixed checkstate so that it would do a string comparison only up to the
// number of letters in statename and not an exact comparison
// 
// 199   5/02/00 3:14p Steven
// Added player watching actors that talk to her.
// 
// 198   5/01/00 2:45p Steven
// Added some action level stuff.
// 
// 197   5/01/00 11:31a Markd
// Added SetWaterPower to Player
// 
// 196   4/30/00 4:42p Markd
// Fixed player turning
// 
// 195   4/29/00 11:28a Markd
// removed old rope code, cleaned up rope interface
// 
// 194   4/28/00 3:07p Steven
// Got rid of dropping items on death for now.
// 
// 193   4/26/00 5:25p Aldie
// Changes to weapons to avoid having to specify the classname
// 
// 192   4/26/00 5:19p Aldie
// Changed from entname to item_name for weapon checking code
// 
// 191   4/24/00 7:22p Markd
// fixed some uninitialized variables
// 
// 190   4/24/00 7:07p Aldie
// Removed old code to try and fix inconsistency between legs and torso for
// firing when moving and standing.  It's all done in the state machine now.
// 
// 189   4/19/00 12:54p Markd
// put in auto_starttime and auto_stoptime support into auto cameras
// 
// 188   4/15/00 5:40p Markd
// fixed falling damage and getting into and out of water
// 
// 187   4/15/00 4:24p Markd
// Fixed player turning
// 
// 186   4/15/00 1:48p Steven
// Made it so the player doesn't cast a shadow when we are using the
// fakeplayer.
// 
// 185   4/15/00 1:30p Markd
// added check_was_running code so that player does not always stop short
// 
// 184   4/15/00 9:53a Markd
// fixed player climbing ladder code
// 
// 183   4/14/00 6:04p Aldie
// Added checksolidforward to state system
// 
// 182   4/13/00 5:31p Steven
// Added a checkshgliekdead check and set have_shgliek to false always when
// throwing not just when the shgliek is found and thrown.
// 
// 181   4/11/00 2:46p Markd
// Implemented Automatic camera support
// 
// 180   4/10/00 1:43p Markd
// changed rope user interface
// 
// 179   4/10/00 11:17a Markd
// Added new rope code
// 
// 178   4/07/00 6:00p Aldie
// Added flashing and fixed radius damage for explosions
// 
// 177   4/07/00 3:00p Markd
// Added legs dangling code for pipehanging
// 
// 176   4/07/00 2:05p Markd
// added MOVETYPE_PIPEHANG
// 
// 175   4/07/00 1:24p Markd
// fixed wall climbing issues
// 
// 174   4/07/00 10:17a Markd
// fixed shgliek pickup and weapon holstering
// 
// 173   4/06/00 6:02p Markd
// changed UseAnim animation from torso to legs
// 
// 172   4/06/00 2:52p Markd
// commented out setting orientation based off of v_angle
// 
// 171   4/06/00 10:59a Markd
// fixed player speed when player has full water
// 
// 170   4/05/00 8:50p Markd
// got rid of damage skin support
// 
// 169   4/05/00 8:41p Markd
// Added water_level conditional
// 
// 168   4/05/00 7:13p Aldie
// Lots of inventory functionality changes.
// 
// 167   4/04/00 3:28p Aldie
// Fix use code for inventory items
// 
// 166   4/04/00 11:02a Markd
// put in checkcanclimb and feet checks
// 
// 165   4/03/00 3:45p Markd
// fixed timescale bug with movement
// 
// 164   3/31/00 6:21p Markd
// took out absolute origin set in StartUseObject
// 
// 163   3/31/00 3:19p Markd
// Added UseObject functionality
// 
// 162   3/28/00 1:47p Markd
// fixed standing jump
// 
// 161   3/27/00 3:45p Markd
// Hooked up UseAnim state info into the game
// 
// 160   3/24/00 2:12p Steven
// Fixed an issue with grabbing of ledges.
// 
// 159   3/22/00 2:04p Aldie
// Added holster command
// 
// 158   3/21/00 6:08p Markd
// Added invehicle check
// 
// 157   3/21/00 5:05p Markd
//
// 156   3/21/00 2:31p Aldie
// Changed checkattackleft and right
//
// 155   3/20/00 6:09p Steven
// Added SetMouthAngle.
//
// 154   3/18/00 3:55p Markd
// working on player turning
//
// 153   3/18/00 2:42p Markd
// added facing up and down slopes
//
// 152   3/17/00 6:37p Markd
// Added chance conditional
//
// 151   3/16/00 3:35p Aldie
// Added checkpain state back instead of forcing it
//
// 150   3/16/00 10:20a Markd
// fixed useanim firing its targets before the animation was completed
//
// 149   3/15/00 4:09p Aldie
// Fixed a bug with using weapons, and added some ability to force a state in
// the player
//
// 148   3/13/00 5:18p Aldie
// Made some changes for usable inventory item stuff
//
// 147   3/07/00 6:38p Steven
// Fixed up some angle stuff when throwing the shgliek.
//
// 146   3/06/00 8:17p Markd
// converted certain events from EV_CONSOLE to EV_CHEAT
//
// 145   3/04/00 1:54p Aldie
// Changed UpdateStats
//
// 144   3/04/00 12:29p Jimdose
// separated feet checks into their own functions
//
// 143   3/02/00 11:12a Markd
// Added additional SetReverb function
//
// 142   3/02/00 10:47a Steven
// Changed reverb interface and set players health to 0 after dying to prevent
// negative health being shown.
//
// 141   3/01/00 8:44p Jimdose
// added turning for monkey bars
// made move checks provide pass/fail results
// added checks for feet and falling when both feet aren't on the ground
//
// 140   3/01/00 10:59a Jimdose
// UseAnim now sends the entity that used it as the activator instead of itself
// when triggering targets
//
// 139   2/28/00 6:51p Jimdose
// added checks for running into walls
//
// 138   2/28/00 6:33p Aldie
// Added more advanced pain state checks
//
// 137   2/26/00 7:09p Jimdose
// added better movement checks for pipecrawl, monkey bars
// added checks to prevent player from going into walk or run animation while
// move is blocked
// fixed setting step height when stepping  up
//
// 136   2/26/00 2:26p Steven
// Fixed a spot where something was comparing an entnum to 0 instead of
// ENTITYNUM_NONE.
//
// 135   2/26/00 12:59p Jimdose
// made player respawning work
//
// 134   2/26/00 11:50a Jimdose
// added slope checks
//
// 133   2/26/00 11:22a Steven
// Added partial immobile flag.
//
// 132   2/25/00 7:27p Markd
// Added useanim_numloop support and fixed useanim_orientation
//
// 131   2/25/00 5:02p Aldie
// Changed some reloading and put in a fix for the animation problem with the
// firing of the weapons
//
// 130   2/24/00 7:26p Aldie
// Added dual wielding
//
// 129   2/24/00 4:20p Jimdose
// added ladder movement
// merged some redundant variables
// made UseAnim have a movetype
// changed bounding box when crouched
//
// 128   2/23/00 5:25p Aldie
// clarified checkuseweapon state check
//
// 127   2/23/00 3:19p Aldie
// Added more inventory functionality with the player
//
// 126   2/22/00 6:56p Jimdose
// fixed double jumping
// fixed climbing on monsters
// no longer forward and back move on ropes
//
// 125   2/22/00 1:57p Jimdose
// added pushobjects
//
// 124   2/17/00 6:26p Aldie
// Fixed naming conventions for weapon hand and also added various attachtotag
// functionality for weapons that attach to different tags depending on which
// hand they are wielded in.
//
// 123   2/17/00 4:18p Jimdose
// made statemap_Legs and statemap_Torso part of player instead of global
// removed redundant physics variables
// made CheckGround use the one from bg_pmove
// onground now checks if player can walk, instead of if player has a
// groundentity
//
// 122   2/17/00 12:00p Aldie
// Added command processing to state system with the addition of entrycommands
// and exitcommands.
//
// 121   2/16/00 4:01p Aldie
// Added shield functionality
//
// 120   2/15/00 9:14p Jimdose
// fixed wall avoidance
//
// 119   2/15/00 8:57p Jimdose
// added move feedback checks for state system
// added wall avoidance code
//
// 118   2/14/00 7:34p Aldie
// Fixed some auto targeting issues
//
// 117   2/14/00 6:36p Markd
// added code to player to setup bootlights and faster/longer running based on
// water level
//
// 116   2/14/00 5:47p Jimdose
// state system now uses leg state only for MOVECONTROL_LEGS
// torso state is now the controlling state
//
// 115   2/10/00 11:25a Markd
// Added bootlights glowing code
//
// 114   2/09/00 8:02p Aldie
// Added loopfire weapons
//
// 113   2/09/00 12:40p Steven
// Made checkhasweapon take into account dual handed weapons also.
//
// 112   2/08/00 9:53p Jimdose
// player now gets set to proper anim at startup
//
// 111   2/08/00 6:35p Aldie
// Added more blocking code to player and sentient
//
// 110   2/08/00 11:33a Steven
// Added picking up of Shgliek.
//
// 109   2/08/00 12:17a Jimdose
// made rope grabbing controlled by state system
//
// 108   2/07/00 7:38p Aldie
// Fixed swiping, also various weapons fixes for sword and for sling
//
// 107   2/04/00 7:28p Aldie
// Combat code - blocking and combos
//
// 106   2/04/00 3:11p Aldie
// Changed sword attack method for water usage
//
// 105   2/03/00 2:56p Aldie
// Sword and water coding
//
// 104   2/02/00 7:08p Aldie
// Added new sword code and water damage
//
// 103   2/02/00 4:28p Aldie
// Added some new state checks for combo help
//
// 102   2/02/00 8:54a Markd
// Set targetname player
//
// 101   2/01/00 8:13p Aldie
// More autoaim work
//
// 100   2/01/00 6:20p Markd
// put in checks for immobile flag or playerfrozen when checking if we can fire
//
// 99    2/01/00 5:28p Aldie
// More updates for auto aiming
//
// 98    1/31/00 7:56p Aldie
// Added some new states and improved arm tracking
//
// 97    1/31/00 4:25p Jimdose
// added dir variable to monkeybar and horizontalpipe
//
// 96    1/31/00 3:56p Aldie
// working on the auto aim / tracking code
//
// 95    1/29/00 6:17p Aldie
// Fixed some problems when state doesn't exist.
//
// 94    1/29/00 11:27a Jimdose
// made ropes work with state system
//
// 93    1/26/00 5:06p Aldie
// Changed .txt to .scr for giveall script
//
// 92    1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
//
// 91    1/26/00 9:53a Markd
// Changed FOV command to an fov command
//
// 90    1/25/00 8:06p Jimdose
// added hardimpact checks
// improved wall hug checks
// fixed side jump angle
//
// 89    1/25/00 3:39p Markd
// added noclip check in evaluate state
//
// 88    1/24/00 6:55p Steven
// Added reverb stuff.
//
// 87    1/24/00 2:56p Markd
// Moved CheckMoveFlags into non-noclip clause
//
// 86    1/24/00 2:50p Jimdose
// added rope checks
//
// 85    1/22/00 4:04p Jimdose
// added pipe crawl and stepping up
// got rid of vec3() calls
//
// 84    1/20/00 7:10p Jimdose
// added checkcanwallhug
// fixed grabbing onto ledges
// added movecontrol
// only call start movement code when movecontrol changes
// fixed UseAnim null pointer bug
//
// 83    1/20/00 10:45a Markd
// removed bootlights from being turned on and off
//
// 82    1/19/00 10:02p Jimdose
// added airspeed
//
// 81    1/19/00 7:59p Markd
// Rewrote Surface Model Event and also added changeoutfit command to player
//
// 80    1/19/00 10:44a Markd
// Cleaned up MOD messages and fixed music starting because of falling damage
//
// 79    1/18/00 6:49p Aldie
// Removed readtofire calls out of the state checking
//
// 78    1/18/00 6:37p Jimdose
// adjusted hang position
//
// 77    1/18/00 2:59p Markd
// Removed unused code
//
// 76    1/17/00 10:20p Jimdose
// Rewrote state system initialization.  Made conditionals defined with array.
// Made Evaluate functions early exit
//
// 75    1/16/00 5:43p Aldie
// Made weapon tag vars
//
// 74    1/15/00 4:13p Markd
// Changed MOVETYPE_ABSOLUTE to have collision and not have user control of the
// angles
//
// 73    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
//
// 72    1/15/00 1:36p Markd
// Added UseAnim and TouchUseAnim functionality to Player and game
//
// 71    1/15/00 9:29a Markd
// rename tag_weapon to tag_weapon_right
//
// 70    1/14/00 5:07p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
//
// 69    1/13/00 5:19p Jimdose
// removed lightvolume stuff
//
// 68    1/13/00 4:55p Aldie
// Changed crossbow weap
//
// 67    1/12/00 8:04p Markd
// changed the way camera_flags were cleared out on the client
//
// 66    1/12/00 3:17p Aldie
// Added some water functionality
//
// 65    1/10/00 6:17p Jimdose
// more code cleanup
//
// 64    1/10/00 10:30a Jimdose
// removed unused code
//
// 63    1/06/00 11:08p Jimdose
// cleaning up unused code
//
// 62    1/06/00 4:58p Markd
// changed the camera angle for topdown
//
// 61    1/06/00 4:39p Markd
// fixed tiki file name
//
// 60    1/06/00 11:54a Jimdose
// Converted AngleVectors from forward,right,up to forward,left,up and also
// fixed functionality of vectoangles function.  Made all cooridinate systems
// identical.
//
// 59    1/03/00 5:08p Markd
// put in camera offsets for player and state machine
//
// 58    12/20/99 6:51p Steven
// Moved jumpxy to sentient.
//
// 57    12/20/99 6:37p Markd
// Made camera cutting work properly
//
// 56    12/17/99 8:27p Jimdose
// got rid of unused vars and functions
//
// 55    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
//
// 54    12/14/18 2:44p Jimdose
// added monkey bar movement
//
// 53    12/13/99 10:17a Markd
// Fixed merge bug
//
// 52    12/13/99 10:14a Aldie
// Temp update for bug fixing due to merge
//
// 51    12/10/99 6:13p Jimdose
// added movement check functions
// unified redundant yaw based orientation calculations
// added wall hug movetype
//
// 50    12/10/99 11:52a Aldie
// Adjusted player angles a bit
//
// 49    12/10/99 11:17a Jimdose
// got rid of unused movement functions
// fixed pulling up from hang
//
// 48    12/09/99 7:38p Jimdose
// improved grabbing and hanging onto walls
//
// 47    12/09/99 3:41p Jimdose
// fixed direction when jumping
// torso anim no longer gets stuck when coming out of noclip
//
// 46    12/09/99 2:31p Aldie
// Head tracking
//
// 45    12/08/99 7:00p Aldie
// Busting up player a bit and wrote some head tracking code
//
// 44    12/03/99 7:02p Aldie
// More ammo joy
//
// 43    12/03/99 9:46a Markd
// fixed a camera lerping bug
//
// 42    12/02/99 6:53p Aldie
// Changed naming conventions from "both" to "dualhanded"  Also put in the
// inventory renderer for the hud file
//
// 41    12/01/99 4:56p Markd
// fixed some reference versus pointer issues with RandomAnimate and NewAnim
//
// 40    12/01/99 3:18p Aldie
// Fix for noclip bug where we should be in idle for noclipping
//
// 39    12/01/99 11:26a Aldie
// Couple of fixes for emitters and more ammo stuff
//
// 38    11/29/99 6:52p Aldie
// Fix 2 handed weapon bug
//
// 37    11/29/99 6:32p Aldie
// Lots of changes for ammo system
//
// 36    11/22/99 6:46p Aldie
// Started working on ammo changes - will finish after Thanksgiving break
//
// 35    11/19/99 6:33p Aldie
// Removed debug print
//
// 34    11/19/99 5:45p Aldie
// Update for primary and alternate fire weapons.  Removed PRIMARY and SECONDAY
// mode weapons of Sin, removed SILENCED properties, and changed ammo types to
// use the new system.  Still need to fix ammo checking for weapons.
//
// 33    11/15/99 11:55a Aldie
// Added rope archiver
//
// 32    11/11/99 5:29p Jimdose
// removed debugging print
//
// 31    11/11/99 5:25p Jimdose
// added separate torso animation
//
// 30    11/09/99 8:05p Markd
// Added SetViewAngles and also made a SetFOV function
//
// 29    11/09/99 5:12p Aldie
// Added ajustanglesforattack
//
// 28    11/05/99 7:30p Aldie
// Angles Adjustment
//
// 27    11/04/99 10:03a Markd
// complete overhaul of the camera system
//
// 26    11/02/99 2:21p Aldie
// Rope stuff
//
// 25    11/01/99 4:00p Jimdose
// added SetControllerAngles and SetControllerTag
//
// 24    10/29/99 6:48p Jimdose
// added bone controllers
// moved torso and head angle calculation from cg_player.c
//
// 23    10/28/99 6:33p Markd
// Added fakeplayer ability, also added CloneEntity
//
// 22    10/28/99 4:01p Aldie
// Fix rope init
//
// 21    10/28/99 11:54a Aldie
// Some more rope stuff
//
// 20    10/28/99 10:42a Aldie
// Added rope functions
//
// 19    10/27/99 12:19p Markd
// added smooth camera lerping
//
// 18    10/27/99 10:29a Steven
// Added new flag PMF_NO_MOVE.
//
// 17    10/19/99 7:53p Markd
// eliminated 3 part model system
//
// 16    10/18/99 6:10p Jimdose
// got rid of separate state machine for torso and legs
// now use skeletal model for player
//
// 15    10/12/99 2:23p Markd
// Rewrote camera and player movetype system
//
// 14    10/08/99 2:13p Markd
// Made player default to ET_PLAYER type and fixed up some PM_LOCKVIEW issues
//
// 13    10/05/99 4:43p Jimdose
// no longer evaluate state while noclipping
//
// 12    10/05/99 4:32p Jimdose
// fixed out of bounds problem in SetAnim when part is all
// go into stand animation when noclipping
//
// 11    10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
//
// 10    9/30/99 5:24p Steven
// Event formatting.
//
// 9     9/17/99 6:31p Jimdose
// changed checks on groundEntityNum
//
// 8     9/17/99 3:40p Jimdose
// fixed jerkiness in player movement
//
// 7     9/16/99 7:44p Jimdose
// PM_SPECTATOR changed to PM_NOCLIP
//
// 6     9/16/99 4:46p Markd
// more merging
//
// 5     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
//
// 4     9/15/99 6:57p Aldie
// Update to get game working
//
// 3     9/13/99 4:22p Jimdose
// merge
//
// 2     9/13/99 3:27p Aldie
// code merge
//
// 1     9/10/99 10:54a Jimdose
//
// 1     9/08/99 3:16p Aldie
//
// 104   9/02/99 9:15p Jimdose
// fixed player shimmy left/right on hangs
//
// 103   9/02/99 7:33p Jimdose
// fixed bool to int warning
//
// 102   9/02/99 7:29p Jimdose
// added checks for doors
//
// 101   9/02/99 6:59p Markd
// put in anti_sucknblow support
//
// 100   9/02/99 4:39p Jimdose
// only get hurt when damage > 15
//
// 99    9/02/99 1:53p Markd
// Added CheckWater to ClientMove
//
// 98    9/01/99 8:09p Markd
// Made slime hurt you
//
// 97    9/01/99 7:54p Jimdose
// fixed canfall checks on player clips
// hardcoded speed when in water
//
// 96    9/01/99 1:44p Jimdose
// made DoUse a script called event
// removed CheckButtons
// disabled obstacle avoidance
//
// 95    9/01/99 12:03p Steven
// Modified sword damage again.
//
// 94    9/01/99 10:29a Aldie
// Added holstering.
//
// 93    8/31/99 8:28p Markd
// fixed noclip
//
// 92    8/31/99 8:23p Steven
// Made it easier to hit with the sword and made the sword do less damage.
//
// 91    8/31/99 7:40p Jimdose
// added check for if she has a weapon
// added movement speed based on animation
//
// 90    8/31/99 10:15a Aldie
// Removed a debug line
//
// 89    8/30/99 10:26p Jimdose
// added check for jump flip
//
// 88    8/30/99 8:58p Aldie
// Fix for sword attack
//
// 87    8/30/99 1:02p Aldie
// Removed a debugline
//
// 86    8/30/99 10:10a Jimdose
// added check in obstacle avoidance to avoid steering away from floor polys
//
// 85    8/27/99 5:05p Markd
// Changed Start( -1 ) to StartImmediately, changed InitInventory.
//
// 84    8/27/99 4:49p Jimdose
// separated state machine into two, one for torso, one for legs
//
// 83    8/23/99 10:16a Jimdose
// added better falling checks
// added 3 part models
//
// 82    8/19/99 3:02p Jimdose
// added steering away from newarly parallel walls
// removed con_clearfade
//
// 81    8/19/99 12:01p Aldie
// Added in firing time checks
//
// 80    8/19/99 11:23a Jimdose
// working on turning away from walls
//
// 79    8/18/99 4:15p Jimdose
// added conditionals for health, death, and pain
//
// 78    8/18/99 3:28p Jimdose
// added cylindrical collision detection
//
// 77    8/17/99 4:52p Jimdose
// added oldorigin
// added various checks for physics
// added JumpXY
//
// 76    8/16/99 10:31a Steven
// Moved ConditionalParameter back into Conditional.
//
// 75    8/12/99 8:04p Jimdose
// working on climbing stuff
//
// 74    8/12/99 12:11p Jimdose
// added g_statefile cvar
//
// 73    8/11/99 10:07p Jimdose
// fixed bug where pmove_t struct wasn't initialized
//
// 72    8/11/99 9:59p Markd
// Added sword to inventory
//
// 71    8/11/99 7:58p Jimdose
// preliminary climbing code in
//
// 70    8/11/99 7:35p Aldie
// Added hand checking to weapons
//
// 69    8/11/99 6:00p Aldie
// Removed a printf
//
// 68    8/11/99 5:43p Aldie
// Fix bug with weapon changing states
//
// 67    8/11/99 11:51a Aldie
// Added giveweapon cheat and fixed weapon changing bug
//
// 66    8/10/99 6:46p Aldie
// Added some better condition logic
//
// 65    8/10/99 11:36a Aldie
// Update of the weapons system
//
// 64    8/10/99 10:52a Jimdose
// started working on climbing
//
// 63    8/06/99 6:52p Jimdose
// changed format of state machine callback functions
//
// 62    8/06/99 6:39p Aldie
// Started moving over to new weapons system
//
// 61    8/04/99 6:02p Jimdose
// now respond to the movetype command from the state machine
//
// 60    8/03/99 3:36p Aldie
// Made the crossbow the default weapon
//
// 59    7/30/99 7:53p Markd
// Added jumping ability to the player
//
// 58    7/29/99 5:33p Markd
// Fixed weird compiler bug
//
// 57    7/23/99 3:27p Aldie
//
// 56    7/19/99 7:55p Markd
// removed unused leftsword, lefttorch, torch loadings
//
// 55    7/07/99 4:06p Jimdose
// changed julie2.st to julie.st
//
// 54    7/07/99 2:53p Jimdose
// added new keys for controlling the player
// added ResetState and LoadState
//
// 53    7/06/99 8:53p Jimdose
// only trace down stepsize from move when on ground
//
// 52    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
//
// 51    6/25/99 5:24p Markd
// changed the player animations and movement speed
//
// DESCRIPTION:
// Class definition of the player.
//
#include "g_local.h"
#include "entity.h"
#include "player.h"
#include "worldspawn.h"
#include "weapon.h"
#include "trigger.h"
#include "scriptmaster.h"
#include "path.h"
#include "navigate.h"
#include "misc.h"
#include "earthquake.h"
#include "gravpath.h"
#include "armor.h"
#include "inventoryitem.h"
#include "gibs.h"
#include "actor.h"
#include "object.h"
#include "characterstate.h"
#include "rope.h"
#include "weaputils.h"

//Forward
//Back
//TurnRight
//TurnLeft
//Moveleft (strafe)
//Moveright (strafe)
//Moveup (Jump)
//Movedown (Duck)
//Action (Use)
//Sneak (Toggle or Momentary)
//Speed/Walk (Toggle or Momentary)
//Fire Left hand
//Fire Right hand

#define SLOPE_45_MIN    0.7071f
#define SLOPE_45_MAX    0.831f
#define SLOPE_22_MIN    SLOPE_45_MAX
#define SLOPE_22_MAX    0.95f

#define MIN_Z                 -999999
#define PUSH_OBJECT_DISTANCE  16.0f

#define R_ARM_NAME "Bip01 R UpperArm"
#define L_ARM_NAME "Bip01 L UpperArm"

const Vector power_color( 0.0, 1.0, 0.0 );
const Vector acolor( 1.0, 1.0, 1.0 );
const Vector bcolor( 1.0, 0.0, 0.0 );

static Vector min_box_8x8( -4, -4, -4 );
static Vector max_box_8x8( 4, 4, 4 );
static Vector min4x4( -4, -4, 0 );
static Vector max4x4x0( 4, 4, 0 );
static Vector max4x4x8( 4, 4, 8 );

qboolean TryPush( int entnum, vec3_t move_origin, vec3_t move_end );

Event EV_Player_DumpState
	(
	"state",
	EV_CHEAT,
   NULL,
   NULL,
   "Dumps the player's state to the console."
	);
Event EV_Player_ForceTorsoState
	(
	"forcetorsostate",
   EV_DEFAULT,
   "s",
   "torsostate",
   "Force the player's torso to a certain state"
	);
Event EV_Player_GiveAllCheat
	(
	"wuss",
	EV_CHEAT,
   NULL,
   NULL,
   "Gives player all weapons."
	);
Event EV_Player_EndLevel
	(
	"endlevel",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called when the player gets to the end of the level."
	);
Event EV_Player_DevGodCheat
	(
	"god",
	EV_CHEAT,
	"I",
   "god_mode",
   "Sets the god mode cheat or toggles it."
	);
Event EV_Player_DevNoTargetCheat
	(
	"notarget",
	EV_CHEAT,
	NULL,
   NULL,
   "Toggles the notarget cheat."
	);
Event EV_Player_DevNoClipCheat
	(
	"noclip",
	EV_CHEAT,
	NULL,
   NULL,
   "Toggles the noclip cheat."
	);
Event EV_Player_PrevItem
	(
	"invprev",
	EV_CONSOLE,
	NULL,
   NULL,
   "Cycle to player's previous item."
	);
Event EV_Player_NextItem
	(
	"invnext",
	EV_CONSOLE,
	NULL,
   NULL,
   "Cycle to player's next item."
	);
Event EV_Player_GiveCheat
	(
	"give",
	EV_CHEAT,
	"sI",
   "name amount",
   "Gives the player the specified thing (weapon, ammo, item, etc.) and optionally the amount."
	);
Event EV_Player_GiveWeaponCheat
	(
	"giveweapon",
	EV_CHEAT,
	"s",
   "weapon_name",
   "Gives the player the specified weapon."
	);
Event EV_Player_UseItem
	(
	"use",
	EV_CONSOLE,
	"sI",
   "name weapon_hand",
   "Use the specified weapon in the hand choosen (optional)."
	);
Event EV_Player_GameVersion
	(
	"gameversion",
	EV_CONSOLE,
	NULL,
   NULL,
   "Prints the game version."
	);
Event EV_Player_Fov
	(
	"fov",
	EV_CONSOLE,
   "F",
   "fov",
   "Sets the fov."
	);
Event EV_Player_Dead
	(
	"dead",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called when the player is dead."
	);
Event EV_Player_SpawnEntity
	(
	"spawn",
	EV_CHEAT,
	"sSSSSSSSS",
   "entityname keyname1 value1 keyname2 value2 keyname3 value3 keyname4 value4",
   "Spawns an entity."
	);
Event EV_Player_SpawnActor
	(
	"actor",
	EV_CHEAT,
	"sSSSSSSSS",
   "modelname keyname1 value1 keyname2 value2 keyname3 value3 keyname4 value4",
   "Spawns an actor."
	);
Event EV_Player_Respawn
	(
	"respawn",
	EV_DEFAULT,
   NULL,
   NULL,
   "Respawns the player."
	);
Event EV_Player_TestThread
	(
	"testthread",
	EV_CHEAT,
   "sS",
   "scriptfile label",
   "Starts the named thread at label if provided."
	);
Event EV_Player_PowerupTimer
	(
	"poweruptimer",
	EV_DEFAULT,
   "ii",
   "poweruptimer poweruptype",
   "Sets the powerup timer and powerup type."
	);
Event EV_Player_UpdatePowerupTimer
	(
	"updatepoweruptime",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called once a second to decrement powerup time."
	);
Event EV_Player_ResetState
	(
	"resetstate",
	EV_CHEAT,
	NULL,
   NULL,
   "Reset the player's state table."
	);
Event EV_Player_WhatIs
	(
	"whatis",
	EV_CHEAT,
	"i",
   "entity_number",
   "Prints info on the specified entity."
	);
Event EV_Player_ActorInfo
	(
	"actorinfo",
	EV_CHEAT,
	"i",
   "actor_number",
   "Prints info on the specified actor."
	);
Event EV_Player_KillEnt
	(
	"killent",
	EV_CHEAT,
	"i",
   "entity_number",
   "Kills the specified entity."
	);
Event EV_Player_KillClass
	(
	"killclass",
	EV_CHEAT,
	"sI",
   "classname except_entity_number",
   "Kills all of the entities in the specified class."
	);
Event EV_Player_RemoveEnt
	(
	"removeent",
	EV_CHEAT,
	"i",
   "entity_number",
   "Removes the specified entity."
	);
Event EV_Player_RemoveClass
	(
	"removeclass",
	EV_CHEAT,
	"sI",
   "classname except_entity_number",
   "Removes all of the entities in the specified class."
	);
Event EV_Player_ActivateNewWeapon
	(
	"activatenewweapon",
	EV_DEFAULT,
   NULL,
   NULL,
   "Active the new weapon specified by useWeapon."
	);
Event EV_Player_DeactivateWeapon
	(
	"deactivateweapon",
	EV_DEFAULT,
   "s",
   "side",
   "Deactivate the weapon in the specified hand."
	);
Event EV_Player_Jump
	(
	"jump",
	EV_DEFAULT,
   "f",
   "height",
   "Makes the player jump."
	);
Event EV_Player_SwordAttack
	(
	"swordattack",
	EV_DEFAULT,
   "s",
   "hand",
   "Makes the player attack with the sword in the specified sword."
	);
Event EV_Player_SwipeOn
	(
	"swipeon",
	EV_DEFAULT,
   NULL,
   NULL,
   "Turn on the sword swiping for the weapon in the specified hand"
	);
Event EV_Player_SwipeOff
	(
	"swipeoff",
	EV_DEFAULT,
   NULL,
   NULL,
   "Turn off the sword swiping for the weapon in the specified hand"
	);
Event EV_Player_AnimLoop_Torso
	(
	"animloop_torso",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called when the torso animation has finished."
	);
Event EV_Player_AnimLoop_Legs
	(
	"animloop_legs",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called when the legs animation has finished."
	);
Event EV_Player_DoUse
	(
	"usestuff",
	EV_DEFAULT,
   NULL,
   NULL,
   "Makes the player try to use whatever is in front of her."
	);
Event EV_Player_SetHeadTarget
	(
	"headtarget",
	EV_CONSOLE,
   NULL,
   NULL,
   "Sets the Makes the player try to use whatever is in front of her."
	);
Event EV_Player_ChangeOutfit
	(
	"changeoutfit",
	EV_CONSOLE,
   "i",
   "outfit_stage",
   "Change the outfit to the specified stage."
	);
Event EV_Player_ListInventory
	(
	"listinventory",
	EV_CONSOLE,
   NULL,
   NULL,
   "List of the player's inventory."
	);
Event EV_Player_PickupShgliek
	(
	"pickup",
	EV_DEFAULT,
   NULL,
   NULL,
   "Picks up a shgliek."
	);
Event EV_Player_ThrowShgliek
	(
	"throw",
	EV_DEFAULT,
   NULL,
   NULL,
   "Throws a shgliek."
	);
Event EV_Player_ClearLeftArmTarget
	(
	"clearleftarmtarget",
	EV_DEFAULT,
   NULL,
   NULL,
   "Clears the left arm target of the player"
	);
Event EV_Player_ClearRightArmTarget
	(
	"clearrightarmtarget",
	EV_DEFAULT,
   NULL,
   NULL,
   "Clears the right arm target of the player"
	);
Event EV_Player_ActivateShield
	(
	"activateshield",
	EV_DEFAULT,
   NULL,
   NULL,
   "Activates the player's shield"
	);
Event EV_Player_DeactivateShield
	(
	"deactivateshield",
	EV_DEFAULT,
   NULL,
   NULL,
   "Deactivates the player's shield"
	);
Event EV_Player_AdjustTorso
	(
	"adjust_torso",
	EV_DEFAULT,
   "b",
   "boolean",
   "Turn or off the torso adjustment"
	);
Event EV_Player_DualWield
	(
	"dualwield",
	EV_CONSOLE,
   "ss",
   "weaponleft weaponright",
   "Dual wield the specified weapons"
	);
Event EV_Player_UseDualWield
	(
	"usedualwield",
	EV_CONSOLE,
   NULL,
   NULL,
   "Use the weapons that are on the dual wield list"
	);
Event EV_Player_EvaluateTorsoAnim
	(
	"evaluatetorsoanim",
	EV_CONSOLE,
   NULL,
   NULL,
   "Evaluate the torso anim for possible changes"
	);
Event EV_Player_StepUp
	(
	"stepup",
	EV_DEFAULT,
   NULL,
   NULL,
   "Causes player to step up"
	);
Event EV_Player_Turn
	(
	"turn",
	EV_DEFAULT,
   "f",
   "yawangle",
   "Causes player to turn the specified amount."
	);
Event EV_Player_TurnUpdate
	(
	"turnupdate",
	EV_DEFAULT,
   "ff",
   "yaw timeleft",
   "Causes player to turn the specified amount."
	);
Event EV_Player_TurnLegs
	(
	"turnlegs",
	EV_DEFAULT,
   "f",
   "yawangle",
   "Turns the players legs instantly by the specified amount."
	);
Event EV_Player_NextPainTime
	(
	"nextpaintime",
	EV_DEFAULT,
   "f",
   "seconds",
   "Set the next time the player experiences pain (Current time + seconds specified)."
	);

Event EV_Player_FinishUseAnim
	(
	"finishuseanim",
	EV_DEFAULT,
   NULL,
   NULL,
   "Fires off all targets associated with a particular useanim."
	);
Event EV_Player_Holster
	(
	"holster",
	EV_CONSOLE,
   NULL,
   NULL,
   "Holsters all wielded weapons, or unholsters previously put away weapons"
	);
Event EV_Player_SafeHolster
	(
	"safeholster",
	EV_CONSOLE,
   "b",
   "putaway",
   "Holsters all wielded weapons, or unholsters previously put away weapons\n"
   "preserves state, so it will not holster or unholster unless necessary"
	);
Event EV_Player_StartUseObject
	(
	"startuseobject",
	EV_DEFAULT,
   NULL,
   NULL,
   "starts up the useobject's animations."
	);
Event EV_Player_FinishUseObject
	(
	"finishuseobject",
	EV_DEFAULT,
   NULL,
   NULL,
   "Fires off all targets associated with a particular useobject."
	);
Event EV_Player_SetWaterPower
	(
	"waterpower",
	EV_DEFAULT,
   NULL,
   NULL,
   "Sets the eden water level of the player."
	);
Event EV_Player_WatchActor
	(
	"watchactor",
	EV_DEFAULT,
   "e",
   "actor_to_watch",
   "Makes the player's camera watch the specified actor."
	);
Event EV_Player_StopWatchingActor
	(
	"stopwatchingactor",
	EV_DEFAULT,
   "e",
   "actor_to_stop_watching",
   "Makes the player's camera stop watching the specified actor."
	);
Event EV_Player_PutawayWeapon
	(
	"putawayweapon",
	EV_DEFAULT,
   "s",
   "whichHand",
   "Put away or deactivate the current weapon, whichHand can be left, right or dual."
	);
Event EV_Player_Weapon
	(
	"weaponcommand",
	EV_DEFAULT,
   "sSSSSSSS",
   "hand arg1 arg2 arg3 arg4 arg5 arg6 arg7",
   "Pass the args to the active weapon in the specified hand"
	);
Event EV_Player_Done
	(
	"playerdone",
	EV_DEFAULT,
   NULL,
   NULL,
   "Clears the waitForPlayer script command, allowing threads to run"
	);
Event EV_Player_ActivateDualWeapons
	(
	"activatedualweapons",
	EV_DEFAULT,
   NULL,
   NULL,
   "Activates 2 weapons at once"
	);

Event EV_Player_StartCoolItem
	(
	"startcoolitem",
	EV_DEFAULT,
   NULL,
   NULL,
   "Player is starting to show off the cool item"
	);

Event EV_Player_StopCoolItem
	(
	"stopcoolitem",
	EV_DEFAULT,
   NULL,
   NULL,
   "Player is starting to show off the cool item"
	);

Event EV_Player_ShowCoolItem
	(
	"showcoolitem",
	EV_DEFAULT,
   NULL,
   NULL,
   "Player is showing the cool item, actually display it"
	);

Event EV_Player_HideCoolItem
	(
	"hidecoolitem",
	EV_DEFAULT,
   NULL,
   NULL,
   "Player is finished showing the cool item, now hide it"
	);
Event EV_Player_SetDamageMultiplier
	(
	"damage_multiplier",
	EV_DEFAULT,
   "f",
   "damage_multiplier",
   "Sets the current damage multiplier"
	);
Event EV_Player_WaitForState
	(
	"waitForState",
	EV_DEFAULT,
   "s",
   "stateToWaitFor",
   "When set, the player will clear waitforplayer when this state is hit\n"
   "in the legs or torso."
	);
Event EV_Player_LogStats
   (
   "logstats",
   EV_CHEAT,
   "b",
   "state",
   "Turn on/off the debugging playlog"
   );
Event EV_Player_TakePain
   (
   "takepain",
   EV_DEFAULT,
   "b",
   "bool",
   "Set whether or not to take pain"
   );
Event EV_Player_SkipCinematic
   (
   "skipcinematic",
   EV_CONSOLE,
   NULL,
   NULL,
   "Skip the current cinematic"
   );
Event EV_Player_ResetHaveItem
   (
   "resethaveitem",
   EV_CONSOLE,
   "s",
   "weapon_name",
   "Resets the game var that keeps track that we have gotten this weapon"
   );


/*
==============================================================================

PLAYER

==============================================================================
*/

CLASS_DECLARATION( Sentient, Player, "player" )
	{
	   { &EV_ClientMove,					         ClientThink },
	   { &EV_ClientEndFrame,			         EndFrame },
      { &EV_Vehicle_Enter,                   EnterVehicle },
		{ &EV_Vehicle_Exit,				         ExitVehicle },
      { &EV_Player_EndLevel,                 EndLevel },
		{ &EV_Player_UseItem,			         EventUseItem },
	   { &EV_Player_GiveCheat,			         GiveCheat },
	   { &EV_Player_GiveWeaponCheat,          GiveWeaponCheat },
		{ &EV_Player_GiveAllCheat,		         GiveAllCheat },
      { &EV_Player_DevGodCheat,		         GodCheat },
      { &EV_Player_DevNoTargetCheat,         NoTargetCheat },
      { &EV_Player_DevNoClipCheat,	         NoclipCheat },
	   { &EV_Player_GameVersion,		         GameVersion },
      { &EV_Player_DumpState,	    	         DumpState },
      { &EV_Player_ForceTorsoState,	         ForceTorsoState },
	   { &EV_Player_Fov,					         Fov },
		{ &EV_Kill,				                  Kill },
      { &EV_Player_Dead,				         Dead },
		{ &EV_Player_SpawnEntity,		         SpawnEntity },
      { &EV_Player_SpawnActor,               SpawnActor },
		{ &EV_Player_Respawn,			         Respawn },
      { &EV_Player_DoUse,                    DoUse },
		{ &EV_Pain,							         Pain },
		{ &EV_Killed,						         Killed },
      { &EV_Gib,                             GibEvent },
		{ &EV_GotKill,						         GotKill },
		{ &EV_Player_TestThread,		         TestThread },
      { &EV_Player_PowerupTimer,		         SetPowerupTimer },
      { &EV_Player_UpdatePowerupTimer,		   UpdatePowerupTimer },
      { &EV_Player_ResetState,               ResetState },
		{ &EV_Player_WhatIs,							WhatIs },
      { &EV_Player_ActorInfo,                ActorInfo },
		{ &EV_Player_KillEnt,						KillEnt },
		{ &EV_Player_RemoveEnt,						RemoveEnt },
		{ &EV_Player_KillClass,						KillClass },
		{ &EV_Player_RemoveClass,					RemoveClass },
      { &EV_Player_AnimLoop_Legs,			   EndAnim_Legs },
  		{ &EV_Player_AnimLoop_Torso,			   EndAnim_Torso },
      { &EV_Player_Jump,               		Jump },
		{ &EV_Sentient_JumpXY,				      JumpXY },
      { &EV_Player_ActivateNewWeapon,        ActivateNewWeapon },
      { &EV_Player_DeactivateWeapon,         DeactivateWeapon },
      { &EV_Player_SwordAttack,              SwordAttackEvent },
      { &EV_Player_SwipeOn,                  SwipeOn },
      { &EV_Player_SwipeOff,                 SwipeOff },
      { &EV_Player_SetHeadTarget,            SetHeadTarget },
      { &EV_Player_ChangeOutfit,             ChangeOutfit },
      { &EV_Player_ListInventory,            ListInventoryEvent },
		{ &EV_Player_PickupShgliek,				PickupShgliek },
		{ &EV_Player_ThrowShgliek,				   ThrowShgliek },
      { &EV_Player_ClearLeftArmTarget,       ClearLeftArmTarget },
      { &EV_Player_ClearRightArmTarget,      ClearRightArmTarget },
      { &EV_Player_ActivateShield,           ActivateShield },
      { &EV_Player_DeactivateShield,         DeactivateShield },
      { &EV_Player_AdjustTorso,              AdjustTorso },
      { &EV_Player_DualWield,                DualWield },
      { &EV_Player_UseDualWield,             UseDualWield },
      { &EV_Player_EvaluateTorsoAnim,        EvaluateTorsoAnim },
      { &EV_Player_NextPainTime,             NextPainTime },
      { &EV_Player_StepUp,                   StepUp },
      { &EV_Player_Turn,                     Turn },
      { &EV_Player_TurnUpdate,               TurnUpdate },
      { &EV_Player_TurnLegs,                 TurnLegs },
      { &EV_Player_FinishUseAnim,            FinishUseAnim },
		{ &EV_Sentient_SetMouthAngle,				SetMouthAngle },
      { &EV_Player_Holster,				      HolsterToggle },
      { &EV_Player_SafeHolster,				   Holster },
      { &EV_Player_StartUseObject,           StartUseObject },
      { &EV_Player_FinishUseObject,          FinishUseObject },
      { &EV_Player_SetWaterPower,            SetWaterPower },
		{ &EV_Player_WatchActor,				   WatchActor },
		{ &EV_Player_StopWatchingActor,			StopWatchingActor },
		{ &EV_Player_PutawayWeapon,			   PutawayWeapon },
      { &EV_Player_Weapon,                   WeaponCommand },
      { &EV_Player_Done,                     PlayerDone },
      { &EV_Player_ActivateDualWeapons,      ActivateDualWeapons },
      { &EV_Player_StartCoolItem,            StartCoolItem },
      { &EV_Player_StopCoolItem,             StopCoolItem },
      { &EV_Player_ShowCoolItem,             ShowCoolItem },
      { &EV_Player_HideCoolItem,             HideCoolItem },
		{ &EV_Player_SetDamageMultiplier,      SetDamageMultiplier },
      { &EV_Player_WaitForState,             WaitForState },
      { &EV_Player_LogStats,                 LogStats },
      { &EV_Player_TakePain,                 SetTakePain },
      { &EV_Player_SkipCinematic,            SkipCinematic },
		{ &EV_Player_ResetHaveItem,            ResetHaveItem },
		{ &EV_Show,										PlayerShowModel },
      { NULL, NULL }
	};

qboolean Player::checkturnleft
   (
   Conditional &condition
   )

   {
   float yaw;

   yaw = SHORT2ANGLE( last_ucmd.angles[ YAW ] + client->ps.delta_angles[ YAW ] );

   return ( angledist( old_v_angle[ YAW ] - yaw ) < -8.0f );
   }

qboolean Player::checkturnright
   (
   Conditional &condition
   )

   {
   float yaw;

   yaw = SHORT2ANGLE( last_ucmd.angles[ YAW ] + client->ps.delta_angles[ YAW ] );

   return ( angledist( old_v_angle[ YAW ] - yaw ) > 8.0f );
   }

qboolean Player::checkforward
   (
   Conditional &condition
   )

   {
   return last_ucmd.forwardmove > 0;
   }

qboolean Player::checkbackward
   (
   Conditional &condition
   )

   {
   return last_ucmd.forwardmove < 0;
   }

qboolean Player::checkstrafeleft
   (
   Conditional &condition
   )

   {
   return last_ucmd.rightmove < 0;
   }

qboolean Player::checkstraferight
   (
   Conditional &condition
   )

   {
   return last_ucmd.rightmove > 0;
   }

qboolean Player::checkrise
   (
   Conditional &condition
   )

   {
   if ( ( do_rise ) && ( velocity.z > 32 ) )
      {
      return true;
      }
   do_rise = qfalse;

   return false;
   }

qboolean Player::checkjump
   (
   Conditional &condition
   )

   {
   return last_ucmd.upmove > 0;
   }

qboolean Player::checkcrouch
   (
   Conditional &condition
   )

   {
   // If the crouch_flag is set, then return true and clear the flag
   if ( crouch_flag )
      {
      crouch_flag = false;
      return true;
      }
   else if ( last_ucmd.upmove < 0 ) // check for downward movement
      {
      if ( client->ps.walking )
         {
         // Player has a weapon, so we can't crouch yet
         // and we must putaway the weapons first.  The crouch_flag is 
         // set so we can allow the state machine to crouch after
         // the weapons have been put away
         if ( WeaponsOut() )
            {
            SafeHolster( qtrue );
            crouch_flag = true;
            return false;
            }
         else // no weapons
            {
            return true;
            }
         }
      else // No weapons out, or not on the ground, and moving down
         {
         return true;
         }
      }

   return false;
   }

qboolean Player::checkjumpflip
   (
   Conditional &condition
   )

   {
   return velocity.z < ( sv_gravity->value * 0.5f );
   }

qboolean Player::checkanimdone_legs
   (
   Conditional &condition
   )

   {
   return animdone_Legs;
   }

qboolean Player::checkanimdone_torso
   (
   Conditional &condition
   )

   {
   return animdone_Torso;
   }


qboolean Player::checkattackleft
   (
   Conditional &condition
   )

   {
   if ( level.playerfrozen || ( flags & FL_IMMOBILE ) )
      {
      return false;
      }

   if ( last_ucmd.buttons & BUTTON_ATTACKLEFT )
      {
      Weapon *weapon;

      last_attack_button = BUTTON_ATTACKLEFT;

      weapon = GetActiveWeapon( WEAPON_LEFT );
      if ( weapon )
         {
         return true;
         }

      weapon = GetActiveWeapon( WEAPON_RIGHT );
      if ( weapon )
         {
         return true;
         }

      weapon = GetActiveWeapon( WEAPON_DUAL );
      if ( weapon )
         {
         return true;
         }

      // No ammo
      return false;
      }
   else
      {
      return false;
      }
   }

qboolean Player::checkattackbuttonleft
   (
   Conditional &condition
   )

   {
   if ( level.playerfrozen || ( flags & FL_IMMOBILE ) )
      {
      return false;
      }

   return ( last_ucmd.buttons & BUTTON_ATTACKLEFT );
   }


qboolean Player::checkattackright
   (
   Conditional &condition
   )

   {
   if ( level.playerfrozen || ( flags & FL_IMMOBILE ) )
      {
      return false;
      }

   if ( last_ucmd.buttons & BUTTON_ATTACKRIGHT )
      {
      Weapon *weapon;

      last_attack_button = BUTTON_ATTACKRIGHT;

      weapon = GetActiveWeapon( WEAPON_RIGHT );
      if ( weapon )
         {
         return true;
         }

      weapon = GetActiveWeapon( WEAPON_LEFT );
      if ( weapon )
         {
         return true;
         }

      weapon = GetActiveWeapon( WEAPON_DUAL );
      if ( weapon )
         {
         return true;
         }

      // No ammo
      return false;
      }
   else
      {
      return false;
      }
   }

qboolean Player::checkattackbuttonright
   (
   Conditional &condition
   )

   {
   if ( level.playerfrozen || ( flags & FL_IMMOBILE ) )
      {
      return false;
      }

   return ( last_ucmd.buttons & BUTTON_ATTACKRIGHT );
   }

qboolean Player::checksneak
   (
   Conditional &condition
   )

   {
   return ( last_ucmd.buttons & BUTTON_SNEAK ) != 0;
   }

qboolean Player::checkrun
   (
   Conditional &condition
   )

   {
   return ( last_ucmd.buttons & BUTTON_RUN ) != 0;
   }

qboolean Player::checkwasrunning
   (
   Conditional &condition
   )

   {
   return ( pm_lastruntime > MINIMUM_RUNNING_TIME );
   }

qboolean Player::checkholsterweapon
   (
   Conditional &condition
   )

   {
   return ( last_ucmd.buttons & BUTTON_HOLSTERWEAPON ) != 0;
   }

qboolean Player::checkuse
   (
   Conditional &condition
   )

   {
   return ( last_ucmd.buttons & BUTTON_USE ) != 0;
   }

qboolean Player::checkcanmoveleft
   (
   Conditional &condition
   )

   {
   if ( condition.numParms() )
      {
      return move_left_dist >= atof( condition.getParm( 1 ) );
      }

   return move_left_dist > 1.0f;
   }

qboolean Player::checkcanturn
   (
   Conditional &condition
   )

   {
   float yaw;
   Vector oldang( v_angle );
   qboolean result;

   yaw = atof( condition.getParm( 1 ) );

   v_angle[ YAW ] = ( int )( anglemod( v_angle[ YAW ] + yaw ) / 22.5f ) * 22.5f;
   SetViewAngles( v_angle );

   result = CheckMove( vec_zero );

   SetViewAngles( oldang );

   return result;
   }

qboolean Player::checkcanmoveright
   (
   Conditional &condition
   )

   {
   if ( condition.numParms() )
      {
      return move_right_dist >= atof( condition.getParm( 1 ) );
      }

   return move_right_dist > 1.0f;
   }

qboolean Player::checkcanmovebackward
   (
   Conditional &condition
   )

   {
   if ( condition.numParms() )
      {
      return move_backward_dist >= atof( condition.getParm( 1 ) );
      }

   return move_backward_dist > 1.0f;
   }

qboolean Player::checkcanmoveforward
   ( 
   Conditional &condition
   )

   {
   if ( condition.numParms() )
      {
      return move_forward_dist >= atof( condition.getParm( 1 ) );
      }

   return move_forward_dist > 1.0f;
   }

qboolean Player::checkcanwallhug
   (
   Conditional &condition
   )

   {
   trace_t trace;
   Vector start( origin.x, origin.y, origin.z + 4 );
   Vector end( start - yaw_forward * 15.0f );

   while( end.z < absmax.z - 4.0f )
      {
      trace = G_Trace( start, min_box_8x8, max_box_8x8, end, this, MASK_DEADSOLID, true, "checkcanwallhug" );
      if ( ( trace.fraction == 1.0f ) || ( trace.ent->entity->getSolidType() != SOLID_BSP ) )
         {
         return false;
         }

      start.z += 16.0f;
      end.z += 16.0f;
      }

   return true;
   }

qboolean Player::checkblocked
   (
   Conditional &condition
   )

   {
	int test_moveresult;

	test_moveresult = moveresult;

	if ( flags & FL_IMMOBILE )
		test_moveresult = MOVERESULT_BLOCKED;

   if ( condition.numParms() )
      {
      return test_moveresult >= atoi( condition.getParm( 1 ) );
      }

   return test_moveresult >= MOVERESULT_BLOCKED;
   }

qboolean Player::checkhangatwall
   (
   Conditional &condition
   )

   {
   trace_t trace;

	Vector end( centroid + yaw_forward * 16.0f );

	trace = G_Trace( centroid, Vector( mins.x, mins.y, -8 ), Vector( maxs.x, maxs.y, 8 ),
      end, this, MASK_DEADSOLID, true, "Player::checkhangatwall" );
   return ( trace.fraction < 0.7f );
   }

qboolean Player::checkcanhang
   (
   Conditional &condition
   )

   {
   trace_t trace;

   Vector end( origin + yaw_forward * 16.0f );

   trace = G_Trace( origin, mins, maxs, end, this, MASK_DEADSOLID, true, "Player::checkcanhang" );
   if ( trace.ent && trace.ent->entity )
      {
      if ( 
            ( trace.ent->entity->velocity.length() ) ||
            ( trace.ent->entity->avelocity.length() )
         )
         {
         return qfalse;
         }
      }
   
   if ( ledgeheight_right == MIN_Z )
      return qfalse;

   if ( ledgeheight_left == MIN_Z )
      return qfalse;

   if ( !trace.ent )
      return qfalse;

   return qtrue;
   }


qboolean Player::checkcanhangleft
   (
   Conditional &condition
   )

   {
   trace_t trace;

   Vector move( origin.x + 26 * yaw_left.x, origin.y + 26 * yaw_left.y, origin.z );

   trace = G_Trace( origin, mins, maxs, move, this, MASK_DEADSOLID, true, "Player::checkcanhangleft" );
   if ( trace.fraction < 1.0f )
      {
      return false;
      }

   Vector lefthand( lefthand_pos + move - origin );
	Vector end( lefthand + yaw_forward * 8.0f );

   lefthand.z -= 4;
   end.z -= 4;

	trace = G_Trace( lefthand, vec_zero, vec_zero, end, this, MASK_DEADSOLID, true, "Player::checkcanhangleft" );
   return ( trace.startsolid ) || ( trace.fraction < 1.0f );
   }

qboolean Player::checkcanhangright
   (
   Conditional &condition
   )

   {
   trace_t trace;

   Vector move( origin.x - 26 * yaw_left.x, origin.y - 26 * yaw_left.y, origin.z );

   trace = G_Trace( origin, mins, maxs, move, this, MASK_DEADSOLID, true, "Player::checkcanhangright" );
   if ( trace.fraction < 1.0f )
      {
      return false;
      }

   Vector righthand( righthand_pos + move - origin );
	Vector end( righthand + yaw_forward * 8.0f );

   righthand.z -= 4;
   end.z -= 4;

	trace = G_Trace( righthand, vec_zero, vec_zero, end, this, MASK_DEADSOLID, true, "Player::checkcanhangright" );
   return ( trace.startsolid ) || ( trace.fraction < 1.0f );
   }

qboolean Player::checktouchrope
   (
   Conditional &condition
   )

   {
   return ( rope_touch != NULL );
   }

qboolean Player::checkonrope
   (
   Conditional &condition
   )

   {
   return ( rope_grabbed != NULL );
   }

qboolean Player::checkcanclimbrope
   (
   Conditional &condition
   )

   {
   if ( rope_grabbed )
      {
      return ( rope_grabbed->CanClimb( atof( condition.getParm( 1 ) ) ) );
      }
   return false;
   }

qboolean Player::checkonground
   (
   Conditional &condition
   )

   {
   return client->ps.walking;
   }

qboolean Player::check22degreeslope
   (
   Conditional &condition
   )

   {
   if ( client->ps.walking && client->ps.groundPlane && ( client->ps.groundTrace.plane.normal[ 2 ] < SLOPE_22_MAX ) &&
      ( client->ps.groundTrace.plane.normal[ 2 ] >= SLOPE_22_MIN ) )
      {
      return qtrue;
      }

   return qfalse;
   }

qboolean Player::check45degreeslope
   (
   Conditional &condition
   )

   {
   if ( client->ps.walking && client->ps.groundPlane && ( client->ps.groundTrace.plane.normal[ 2 ] < SLOPE_45_MAX ) &&
      ( client->ps.groundTrace.plane.normal[ 2 ] >= SLOPE_45_MIN ) )
      {
      return qtrue;
      }

   return qfalse;
   }

qboolean Player::checkrightleghigh
   (
   Conditional &condition
   )

   {
   float groundyaw;
   float yawdelta;
   int which;

   groundyaw = ( int )vectoyaw( client->ps.groundTrace.plane.normal );
   yawdelta = anglemod( v_angle.y - groundyaw );
   which = ( ( int )yawdelta + 45 ) / 90;

   return ( which == 3 );
   }

qboolean Player::checkleftleghigh
   (
   Conditional &condition
   )

   {
   float groundyaw;
   float yawdelta;
   int which;

   groundyaw = ( int )vectoyaw( client->ps.groundTrace.plane.normal );
   yawdelta = anglemod( v_angle.y - groundyaw );
   which = ( ( int )yawdelta + 45 ) / 90;

   return ( which == 1 );
   }

qboolean Player::checkfacingupslope
   (
   Conditional &condition
   )

   {
   float groundyaw;
   float yawdelta;
   int which;

   groundyaw = ( int )vectoyaw( client->ps.groundTrace.plane.normal );
   yawdelta = anglemod( v_angle.y - groundyaw );
   which = ( ( int )yawdelta + 45 ) / 90;

   return ( which == 2 );
   }

qboolean Player::checkfacingdownslope
   (
   Conditional &condition
   )

   {
   float groundyaw;
   float yawdelta;
   int which;

   groundyaw = ( int )vectoyaw( client->ps.groundTrace.plane.normal );
   yawdelta = anglemod( v_angle.y - groundyaw );
   which = ( ( int )yawdelta + 45 ) / 90;

   return ( ( which == 0 ) || ( which == 4 ) );
   }

qboolean Player::checkfalling
   (
   Conditional &condition
   )

   {
   return falling;
   }

qboolean Player::checkgroundentity
   (
   Conditional &condition
   )

   {
   return ( groundentity != NULL );
   }

qboolean Player::checkhardimpact
   (
   Conditional &condition
   )

   {
   return hardimpact;
   }

qboolean Player::checkcanfall
   (
   Conditional &condition
   )

   {
   return canfall;
   }

qboolean Player::checkatdoor
   (
   Conditional &condition
   )

   {
   // Check if the player is at a door
   return ( atobject && atobject->isSubclassOf( Door ) );
   }

qboolean Player::checkatshgliek
   (
   Conditional &condition
   )

   {
	Vector start;
	Vector end;
	trace_t trace;

	// See if there are any Shglieks in front of us

	start = origin + Vector( 0, 0, 32 );
	end	= start + yaw_forward * 64.0f;
	trace = G_Trace( start, mins, maxs, end, this, MASK_PLAYERSOLID, true, "checkatshgliek" );

   if ( trace.ent && trace.ent->entity && ( trace.ent->entity != world ) && trace.ent->entity->isSubclassOf( Actor ) )
      {
		Actor *act = (Actor *)trace.ent->entity;

		if ( act->name == "Shgliek" )
			return true;
      }

   return false;
   }

qboolean Player::checkhaveshgliek
   (
   Conditional &condition
   )

   {
   return have_shgliek;
   }

qboolean Player::checkshgliekdead
   (
   Conditional &condition
   )

   {
	int i;
	Entity *child;
	Actor *act;


	for ( i=0; i < MAX_MODEL_CHILDREN; i++ )
      {
      if ( children[i] == ENTITYNUM_NONE )
         {
         continue;
         }

		child = ( Entity * )G_GetEntity( children[i] );

		if ( child->isSubclassOf( Actor ) )
			{
			act = (Actor *)child;

			if ( ( act->name == "Partially Evil Shgliek" ) || ( act->name == "Evil Shgliek" ) ) 
				return true;

			if ( act->name == "Shgliek" )
				{
				if ( act->deadflag )
					return true;
				else
					return false;
				}
			}
		}

	return true;
   }

qboolean Player::checkatuseanim
   (
   Conditional &condition
   )

   {
   // Check if the player is at a useanim
   if ( atobject && atobject->isSubclassOf( UseAnim ) )
      {
      return ( ( UseAnim * )( Entity * )atobject )->canBeUsed( this );
      }

   return false;
   }

qboolean Player::checktouchuseanim
   (
   Conditional &condition
   )

   {
   if ( toucheduseanim )
      {
      return ( ( UseAnim * )( Entity * )toucheduseanim )->canBeUsed( this );
      }

   return qfalse;
   }

qboolean Player::checkuseanimfinished
   (
   Conditional &condition
   )

   {
   return ( useanim_numloops <= 0 );
   }

qboolean Player::checkatuseobject
   (
   Conditional &condition
   )

   {
   // Check if the player is at a useanim
   if ( atobject && atobject->isSubclassOf( UseObject ) )
      {
      return ( ( UseObject * )( Entity * )atobject )->canBeUsed( origin, yaw_forward );
      }

   return false;
   }

qboolean Player::checkloopuseobject
   (
   Conditional &condition
   )

   {
   // Check if the player is at a useanim
   if ( useitem_in_use && useitem_in_use->isSubclassOf( UseObject ) )
      {
      return ( ( UseObject * )( Entity * )useitem_in_use )->Loop();
      }

   return false;
   }

qboolean Player::checkcangrabledge
   (
   Conditional &condition
   )

   {
   float old_hang_pullup_distance;
   float hang_pullup_distance;
   float deltaleft;
   float deltaright;
   bool  hangleft;
   bool  hangright;

   if ( ( ledgeheight_left <= MIN_Z ) || ( ledgeheight_right <= MIN_Z ) )
      {
      return false;
      }

   if ( groundentity )
      {
      deltaleft = ledgeheight_left - origin.z - 128.0f;
      deltaright = ledgeheight_right - origin.z - 128.0f;

      return ( Q_fabs( deltaleft ) < 1.1f ) && ( Q_fabs( deltaright ) < 1.1f );
      }

#define WALL_FUDGE_FACTOR 5
   hang_pullup_distance = lefthand_pos.z;
   old_hang_pullup_distance = hang_pullup_distance - origin.z + oldorigin.z;
   if ( hang_pullup_distance > old_hang_pullup_distance )
      {
      hangleft = ( hang_pullup_distance >= ledgeheight_left ) && ( ledgeheight_left+WALL_FUDGE_FACTOR >= old_hang_pullup_distance );
      }
   else
      {
      hangleft = ( old_hang_pullup_distance >= ledgeheight_left ) && ( ledgeheight_left+WALL_FUDGE_FACTOR >= hang_pullup_distance );
      }

   hang_pullup_distance = righthand_pos.z;
   old_hang_pullup_distance = hang_pullup_distance - origin.z + oldorigin.z;
   if ( hang_pullup_distance > old_hang_pullup_distance )
      {
      hangright = ( hang_pullup_distance >= ledgeheight_right ) && ( ledgeheight_right+WALL_FUDGE_FACTOR >= old_hang_pullup_distance );
      }
   else
      {
      hangright = ( old_hang_pullup_distance >= ledgeheight_right ) && ( ledgeheight_right+WALL_FUDGE_FACTOR >= hang_pullup_distance );
      }

   return hangleft && hangright;
   }

qboolean Player::checkledgeheight
   (
   Conditional &condition
   )

   {
   float deltaleft;
   float deltaright;
   float minclimbheight;
   float maxclimbheight;

   if ( ( ledgeheight_left <= MIN_Z ) || ( ledgeheight_right <= MIN_Z ) )
      {
      return false;
      }

   if ( condition.numParms() != 2 )
      {
      error( "checkledgeheight", "CAN_CLIMB requires 2 parameters.\n" );
      }

   minclimbheight = atof( condition.getParm( 1 ) );
   maxclimbheight = atof( condition.getParm( 2 ) );

   deltaleft = Q_fabs( ledgeheight_left - origin.z );
   deltaright = Q_fabs( ledgeheight_right - origin.z );

   if ( Q_fabs( deltaright - deltaleft ) < 1.1f )
      {
      deltaright = max( deltaleft, deltaright );
      deltaleft = deltaright;
      }

   return ( deltaleft > minclimbheight ) && ( deltaleft <= maxclimbheight ) &&
      ( deltaright > minclimbheight ) && ( deltaright <= maxclimbheight );
   }

qboolean Player::checkcangrabpipe
   (
   Conditional &condition
   )

   {
   return horizontalpipe != NULL;
   }

qboolean Player::checkcangrabmonkeybar
   (
   Conditional &condition
   )

   {
   float old_hang_pullup_distance;
   float hang_pullup_distance;
   float deltaleft;
   float deltaright;
   bool  hangleft;
   bool  hangright;

   if ( ( monkeybar_left <= MIN_Z ) || ( monkeybar_right <= MIN_Z ) )
      {
      return false;
      }

   if ( groundentity )
      {
      deltaleft = monkeybar_left - origin.z - 128.0f;
      deltaright = monkeybar_right - origin.z - 128.0f;

      return ( Q_fabs( deltaleft ) < 1.0f ) && ( Q_fabs( deltaright ) < 1.0f );
      }

   hang_pullup_distance = lefthand_pos.z;
   old_hang_pullup_distance = hang_pullup_distance - origin.z + oldorigin.z;
   if ( hang_pullup_distance > old_hang_pullup_distance )
      {
      hangleft = ( hang_pullup_distance >= monkeybar_left ) && ( monkeybar_left >= old_hang_pullup_distance );
      }
   else
      {
      hangleft = ( old_hang_pullup_distance >= monkeybar_left ) && ( monkeybar_left >= hang_pullup_distance );
      }

   hang_pullup_distance = righthand_pos.z;
   old_hang_pullup_distance = hang_pullup_distance - origin.z + oldorigin.z;
   if ( hang_pullup_distance > old_hang_pullup_distance )
      {
      hangright = ( hang_pullup_distance >= monkeybar_right ) && ( monkeybar_right >= old_hang_pullup_distance );
      }
   else
      {
      hangright = ( old_hang_pullup_distance >= monkeybar_right ) && ( monkeybar_right >= hang_pullup_distance );
      }

   return hangleft && hangright;
   }

qboolean Player::checkcanpullup
   (
   Conditional &condition
   )

   {
   trace_t trace;

   Vector start( origin.x, origin.y, max( ledgeheight_left, ledgeheight_right ) );
	Vector end( start + yaw_forward * 16.0f );

	trace = G_Trace( origin, mins, maxs, start, this, MASK_DEADSOLID, true, "Player::checkcanpullup" );
   if ( trace.fraction < 1.0f )
      {
      return false;
      }

	trace = G_Trace( start, mins, maxs, end, this, MASK_DEADSOLID, true, "Player::checkcanpullup" );
   return trace.fraction == 1.0f;
   }

qboolean Player::checkdead
   (
   Conditional &condition
   )

   {
   return ( deadflag );
   }

qboolean Player::checkhealth 
   (
   Conditional &condition
   )

   {
   return health < atoi( condition.getParm( 1 ) );
   }

qboolean Player::checkpain
   (
   Conditional &condition
   )

   {
   return ( pain != 0 || knockdown != 0 );
   }

qboolean Player::checkknockdown
   (
   Conditional &condition
   )

   {
   if ( knockdown )
      {
      knockdown = false;
      return true;
      }
   else
      {
      return false;
      }
   }

qboolean Player::checkpaintype
   (
   Conditional &condition
   )

   {
   if ( pain_type == MOD_string_to_int( condition.getParm( 1 ) ) )
      {
      return qtrue;
      }
   else
      {
      return qfalse;
      }
   }

qboolean Player::checkpaindirection
   (
   Conditional &condition
   )

   {
   if ( pain_dir == Pain_string_to_int( condition.getParm( 1 ) ) )
      {
      return qtrue;
      }
   else
      {
      return qfalse;
      }
   }

qboolean Player::checkaccumulatedpain
   (
   Conditional &condition
   )

   {
   float threshold = atof( condition.getParm( 1 ) );

   if ( accumulated_pain >= threshold )
      {
      accumulated_pain = 0; // zero out accumulation
      return true;
      }
   else
      {
      return false;
      }
   }

qboolean Player::checkpainthreshold
   (
   Conditional &condition
   )

   {
   float threshold = atof( condition.getParm( 1 ) );

   if ( (  pain >= threshold ) && ( level.time > nextpaintime ) )
      {
      accumulated_pain = 0; // zero out accumulation since we are going into a pain anim right now
      return true;
      }
   else
      {
      return false;
      }
   }

qboolean Player::checklegsstate
   (
   Conditional &condition
   )

   {
   if ( currentState_Legs )
      {
      str current = currentState_Legs->getName();
      str compare = condition.getParm( 1 );

      if ( current == compare )
         {
         return true;
         }
      }

   return false;
   }

qboolean Player::checktorsostate
   (
   Conditional &condition
   )

   {
   if ( currentState_Torso )
      {
      str current = currentState_Torso->getName();
      str compare = condition.getParm( 1 );

      if ( current == compare )
         {
         return true;
         }
      }

   return false;
   }

qboolean Player::checkhasweapon
   (
   Conditional &condition
   )

   {
   return WeaponsOut();
   }

qboolean Player::checknewweapon
   (
   Conditional &condition
   )

   {
   Weapon * weapon;

   weapon = GetNewActiveWeapon();

   if ( weapon )
      return true;
   else
      return false;
   }

// Check to see if a weapon has been raised
qboolean Player::checkuseweapon
   (
   Conditional &condition
   )

   {
   const char     *weaponName;
   const char     *parm;

   weaponhand_t   hand;
   Weapon         *weap;

   weap = GetNewActiveWeapon();
   parm = condition.getParm( 1 );

   if ( !str::icmp( parm, "ERROR" ) )
      {
      if ( weap )
         warning( "Player::checkuseweapon", "%s does not have a valid RAISE_WEAPON state\n", weap->item_name );
      else
         warning( "Player::checkuseweapon", "New Active weapon does not exist\n" );

      ClearNewActiveWeapon();
      return qtrue;
      }

   hand = WeaponHandNameToNum( parm );

   if ( hand == WEAPON_ERROR )
      return false;

   weaponName = condition.getParm( 2 );

   if (
        ( weap != NULL ) &&
        ( GetNewActiveWeaponHand() == hand ) &&
        ( !stricmp( weap->item_name, weaponName ) )
      )
      {
      return true;
      }
   else
      {
      return false;
      }
   }

// Checks to see if any weapon is active in the specified hand
qboolean Player::checkanyweaponactive
   (
   Conditional &condition
   )

   {
   weaponhand_t   hand;
   Weapon         *weap;

   hand = WeaponHandNameToNum( condition.getParm( 1 ) );

   if ( hand == WEAPON_ERROR )
      return false;

   weap = GetActiveWeapon( hand );
   return ( weap != NULL );
   }

// Checks to see if any weapon is active in the specified hand
qboolean Player::checkweaponhasammo
   (
   Conditional &condition
   )

   {
   weaponhand_t   hand;
   Weapon         *weap;
   firemode_t     mode = FIRE_PRIMARY;

   hand = WeaponHandNameToNum( condition.getParm( 1 ) );
   
   if ( condition.numParms() > 1 )
      mode = WeaponModeNameToNum( condition.getParm( 2 ) );

   if ( hand == WEAPON_ERROR )
      return false;

   weap = GetActiveWeapon( hand );

   if ( !weap )
      return false;
   else
      return ( weap->HasAmmo( mode ) );
   }

qboolean Player::checkmuzzleclear
   (
   Conditional &condition
   )

   {
   weaponhand_t hand;

   hand = WeaponHandNameToNum( condition.getParm( 1 ) );

   if ( hand == WEAPON_ERROR )
      return false;

   Weapon *weapon = GetActiveWeapon( hand );
   return ( weapon && weapon->MuzzleClear() );
   }

// Checks to see if weapon is active
qboolean Player::checkweaponactive
   (
   Conditional &condition
   )

   {
   const char *weaponName;
   weaponhand_t hand;

   weaponName = condition.getParm( 2 );
   hand = WeaponHandNameToNum( condition.getParm( 1 ) );

   if ( hand == WEAPON_ERROR )
      return false;

   Weapon *weapon = GetActiveWeapon( hand );

   return ( weapon && !strcmp( weaponName, weapon->item_name ) );
   }

qboolean Player::checkdualweaponreadytofire
   (
   Conditional &condition
   )

   {
   firemode_t  mode      = FIRE_PRIMARY;
   str         weaponName="None";      
   Weapon      *weapon = GetActiveWeapon( WEAPON_DUAL );
   qboolean    ready;

   mode = WeaponModeNameToNum( condition.getParm( 1 ) );

   if ( condition.numParms() > 1 )
      weaponName = condition.getParm( 2 );

   // Weapon there check
   if ( !weapon )
      return qfalse;

   // Name check
   if ( condition.numParms() > 1 )
      {
      if ( strcmp( weaponName, weapon->item_name ) )
         {
         return qfalse;
         }
      }

   // Ammo check
   ready = weapon->ReadyToFire( mode );
   return( ready );
   }

// Checks to see if weapon is active and ready to fire
qboolean Player::checkweaponreadytofire
   (
   Conditional &condition
   )

   {
   firemode_t     mode = FIRE_PRIMARY;
   str            weaponName="None";
   weaponhand_t   hand;
   qboolean    ready;

   if ( level.playerfrozen || ( flags & FL_IMMOBILE ) )
      {
      return false;
      }

   hand = WeaponHandNameToNum( condition.getParm( 1 ) );

   if ( hand == WEAPON_DUAL )
      {
      gi.DPrintf( "This check should only be used for single handed weapons\n" );
      return false;
      }

   if ( condition.numParms() > 1 )
      weaponName = condition.getParm( 2 );

   if ( hand == WEAPON_ERROR )
      return false;

   Weapon *weapon = GetActiveWeapon( hand );

   // Weapon there check
   if ( !weapon )
      return qfalse;

   // Name check
   if ( condition.numParms() > 1 )
      {
      if ( strcmp( weaponName, weapon->item_name ) )
         {
         return qfalse;
         }
      }

   // Ammo check
   ready = weapon->ReadyToFire( mode );
   return( ready );
   }

qboolean Player::checkweaponreadytofire_nosound
   (
   Conditional &condition
   )

   {
   firemode_t     mode = FIRE_PRIMARY;
   str            weaponName="None";
   weaponhand_t   hand;
   qboolean       ready;

   if ( level.playerfrozen || ( flags & FL_IMMOBILE ) )
      {
      return false;
      }

   hand = WeaponHandNameToNum( condition.getParm( 1 ) );

   if ( hand == WEAPON_DUAL )
      {
      gi.DPrintf( "This check should only be used for single handed weapons\n" );
      return false;
      }

   if ( condition.numParms() > 1 )
      weaponName = condition.getParm( 2 );

   if ( hand == WEAPON_ERROR )
      return false;

   Weapon *weapon = GetActiveWeapon( hand );

   // Weapon there check
   if ( !weapon )
      return qfalse;

   // Name check
   if ( condition.numParms() > 1 )
      {
      if ( strcmp( weaponName, weapon->item_name ) )
         {
         return qfalse;
         }
      }

   // Ammo check
   ready = weapon->ReadyToFire( mode, qfalse );
   return( ready );
   }

// Check to see if any of the active weapons need to be put away
qboolean Player::checkputawayleft
   (
   Conditional &condition
   )

   {
   Weapon *weapon = GetActiveWeapon( WEAPON_LEFT );

   return weapon && weapon->GetPutaway();
   }

qboolean Player::checkputawayright
   (
   Conditional &condition
   )

   {
   Weapon *weapon = GetActiveWeapon( WEAPON_RIGHT );

   return weapon && weapon->GetPutaway();
   }

qboolean Player::checkputawayboth
   (
   Conditional &condition
   )

   {
   Weapon *weapon = GetActiveWeapon( WEAPON_DUAL );

   return weapon && weapon->GetPutaway();
   }

qboolean Player::checktargetacquired
   (
   Conditional &condition
   )

   {
   str side = condition.getParm( 1 );

   if ( !side.icmp( "left" ) )
      {
      return ( left_arm_target != NULL );
      }
   else if ( !side.icmp( "right" ) )
      {
      return ( right_arm_target != NULL );
      }
   else if ( !side.icmp( "both" ) )
      {
      return ( ( left_arm_target != NULL ) && ( right_arm_target != NULL ) );
      }
   else if ( !side.icmp( "any" ) )
      {
      return ( ( left_arm_target != NULL ) || ( right_arm_target != NULL ) );
      }
   else
      {
      return false;
      }
   }

qboolean Player::returntrue
   (
   Conditional &condition
   )

   {
   return true;
   }

qboolean Player::checkstatename
   (
   Conditional &condition
   )

   {
   str part      = condition.getParm( 1 );
   str statename = condition.getParm( 2 );

   if ( currentState_Legs && !part.icmp( "legs" ) )
      {
      return ( !statename.icmpn( currentState_Legs->getName(), statename.length() ) );
      }
   else if ( !part.icmp( "torso" ) )
      {
      return ( !statename.icmpn( currentState_Torso->getName(), statename.length() ) );
      }

   return false;
   }

qboolean Player::checkattackblocked
   (
   Conditional &condition
   )

   {
   if ( attack_blocked )
      {
      attack_blocked = qfalse;
      return true;
      }
   else
      {
      return false;
      }
   }

qboolean Player::checkblockdelay
   (
   Conditional &condition
   )

   {
   float t = atof ( condition.getParm( 1 ) );
   return ( level.time > ( attack_blocked_time + t ) );
   }

qboolean Player::checkpush
   (
   Conditional &condition
   )

   {
   // Check if the player is at a pushobject
   if ( atobject && atobject->isSubclassOf( PushObject ) && ( atobject_dist < ( PUSH_OBJECT_DISTANCE + 15.0f ) ) )
      {
      Vector dir;

      dir = atobject_dir * 8.0f;
      return ( ( PushObject * )( Entity * )atobject )->canPush( dir );
      }

   return qfalse;
   }

qboolean Player::checkpull
   (
   Conditional &condition
   )

   {
   // Check if the player is at a pushobject
   if ( atobject && atobject->isSubclassOf( PushObject ) && ( atobject_dist < ( PUSH_OBJECT_DISTANCE + 15.0f ) ) )
      {
      Vector dir;

      dir = atobject_dir * -64.0f;
      return ( ( PushObject * )( Entity * )atobject )->canPush( dir );
      }

   return qfalse;
   }

#define LADDER_HAND_HEIGHT ( MAXS_X - MINS_X )

qboolean Player::checkladder
   (
   Conditional &condition
   )

   {
   trace_t  trace;
   float    hands_fraction;
   Vector   newmins;
	Vector   end( origin + yaw_forward * 20.0f );

   // the bounding box is made skinnier to account for the hands
   newmins = mins;
   newmins.z = MAXS_Z - LADDER_HAND_HEIGHT;

   trace = G_Trace( origin, newmins, maxs, end, this, MASK_SOLID, true, "checkladder" );
   if ( ( trace.fraction == 1.0f ) || !( trace.surfaceFlags & SURF_LADDER ) )
      {
      return qfalse;
      }
   hands_fraction = trace.fraction;

   // check for the body
   trace = G_Trace( origin, mins, maxs, end, this, MASK_SOLID, true, "checkladder" );

   // if our body does not go as far as our hands, we aren't at a ladder
   if ( trace.fraction < hands_fraction )
      {
      return qfalse;
      }

   return qtrue;
   }

qboolean Player::checkcanclimbladder
   (
   Conditional &condition
   )

   {
   trace_t trace;
   Vector  newmins;
   Vector  vec;
   Vector  start( origin );
   int     i;

   for ( i = 0; i < 3; i++ )
      {
      vec[ i ] = atof ( condition.getParm( i + 1 ) );
      }
   start += vec[ 0 ] * yaw_forward;
   start += vec[ 1 ] * yaw_left;
   start.z += vec[ 2 ];

	Vector  end( start + yaw_forward * 20.0f );

   // check the normal bounding box first and trace to that position
   trace = G_Trace( origin, mins, maxs, start, this, MASK_SOLID, true, "checkcanclimbladder" );
   if ( ( trace.fraction != 1.0f ) || ( trace.startsolid ) || ( trace.allsolid ) )
      {
      return qfalse;
      }

   // the bounding box is made skinnier to account for the hands
   newmins = mins;
   newmins.z = MAXS_Z - LADDER_HAND_HEIGHT;

   trace = G_Trace( start, newmins, maxs, end, this, MASK_SOLID, true, "checkcanclimbladder" );
   if ( ( trace.fraction == 1.0f ) || !( trace.surfaceFlags & SURF_LADDER ) )
      {
      return qfalse;
      }

   return qtrue;
   }


qboolean Player::checkfeetatladder
   (
   Conditional &condition
   )

   {
   trace_t trace;
   Vector  newmins, newmaxs;
	Vector  end( origin + yaw_forward * 20.0f );

   // the bounding box is made skinnier to account for the feet
   newmaxs.x = MAXS_X / 2;
   newmaxs.y = MAXS_Y / 2;
   // just underneath the feet
   newmaxs.z = 28;
   newmins.x = MINS_X / 2;
   newmins.y = MINS_Y / 2;
   newmins.z = 0;
   trace = G_Trace( origin, newmins, newmaxs, end, this, MASK_SOLID, true, "checkfeetatladder" );
   if ( ( trace.fraction == 1.0f ) || !( trace.surfaceFlags & SURF_LADDER ) )
      {
      return qfalse;
      }

   return qtrue;
   }


qboolean Player::checkcanstand
   (
   Conditional &condition
   )

   {
   Vector newmins( mins );
   Vector newmaxs( maxs );
   trace_t trace;

   newmins[ 2 ] = MINS_Z;
   newmaxs[ 2 ] = MAXS_Z;

   trace = G_Trace( origin, newmins, newmaxs, origin, this, MASK_PLAYERSOLID, true, "checkcanstand" );
   if ( trace.startsolid )
      {
      return qfalse;
      }

   return qtrue;
   }

qboolean Player::checkspecialmove
   (
   Conditional &condition
   )

   {
   weaponhand_t   hand;

   hand = WeaponHandNameToNum( condition.getParm( 1 ) );

   if ( hand == WEAPON_ERROR )
      return false;

   Weapon *weapon = GetActiveWeapon( hand );

   if ( !weapon )
      return qtrue;
   else
      return weapon->GetSpecialMove();
   }

qboolean Player::checkdualwield
   (
   Conditional &condition
   )

   {
   // Only start the dual wield state if dual wield is set and the hands have no weapons

   return ( dual_wield_active );
   }

qboolean Player::checkdualweapons
   (
   Conditional &condition
   )

   {
   int i,j;

   for ( i=1; i<=condition.numParms(); i++ )
      {
      str weaponName;
      weaponName = condition.getParm( i );

      for ( j=1; j<=dual_wield_weaponlist.NumObjects(); j++ )
         {
         DualWieldWeapon *dw;
         dw = dual_wield_weaponlist.ObjectAt( j );

         if ( dw->name == weaponName )
            {
            goto out;
            }
         }
      return false;
out:
      ;
      }

   return true;
   }

qboolean Player::checkchance
   (
   Conditional &condition
   )

	{
	float percent_chance;

	percent_chance = atof( condition.getParm( 1 ) );

	return ( G_Random() < percent_chance );
	}

qboolean Player::checkturnedleft
   (
   Conditional &condition
   )

   {
   return yawing_left;
   }


qboolean Player::checkturnedright
   (
   Conditional &condition
   )

   {
   return yawing_right;
   }

qboolean Player::checkinvehicle
   (
   Conditional &condition
   )

   {
   return ( vehicle != NULL );
   }

qboolean Player::checkwaterlevel
   (
   Conditional &condition
   )

   {
   return ( water_power >= atof( condition.getParm( 1 ) ) );
   }

qboolean Player::checkpickupenemy
   (
   Conditional &condition
   )

   {
   return pickup_enemy;
   }

qboolean Player::checksolidforward
   (
   Conditional &condition
   )

   {
   // Trace out forward to see if there is a solid ahead
   float dist = atof( condition.getParm( 1 ) );
	Vector end( centroid + yaw_forward * dist );

	trace_t trace = G_Trace( centroid, Vector( mins.x, mins.y, -8 ), Vector( maxs.x, maxs.y, 8 ),
      end, this, MASK_SOLID, true, "Player::checksolidforward" );
   
   return ( trace.fraction < 0.7f );
   }

qboolean Player::checkcoolitem
   (
   Conditional &condition
   )

   {
   return ( cool_item != NULL );
   }

qboolean Player::checkarmorpiece
   (
   Conditional &condition
   )

   {
   str piece = condition.getParm( 1 );

   if ( !stricmp( piece, "Arm" ) )
      {
      if ( outfit_level >= 2 )
         return true;
      }
   else if ( !stricmp( piece, "Knee" ) )
      {
      if ( outfit_level >= 3 )
         return true;
      }
   else if ( !stricmp( piece, "Shoulder" ) )
      {
      if ( outfit_level >= 4 )
         return true;
      }
   
   return false;
   }

qboolean Player::checkweaponsholstered
   (
   Conditional &condition
   )

   {

   if (
         ( holsteredWeapons[WEAPON_DUAL] ) ||
         ( holsteredWeapons[WEAPON_LEFT] ) ||
         ( holsteredWeapons[WEAPON_RIGHT] )
      )
      {
      return qtrue;
      }
   else
      {
      return qfalse;
      }
   }

qboolean Player::checkfakeplayeractive
   (
   Conditional &condition
   )

   {
   return fakePlayer_active;
   }

Condition<Player> Player::Conditions[] =
   {
      { "default",                  returntrue },
      { "SNEAK",                    checksneak },
      { "RUN",                      checkrun },
      { "WAS_RUNNING",              checkwasrunning },
      { "HOLSTERWEAPON",            checkholsterweapon },
      { "USE",                      checkuse },
      { "LEFT",                     checkturnleft },
      { "RIGHT",                    checkturnright },
      { "FORWARD",                  checkforward },
      { "BACKWARD",                 checkbackward },
      { "STRAFE_LEFT",              checkstrafeleft },
      { "STRAFE_RIGHT",             checkstraferight },
      { "JUMP",                     checkjump },
      { "RISE",                     checkrise },
      { "CROUCH",                   checkcrouch },
      { "DO_JUMP_FLIP",             checkjumpflip },
      { "ANIMDONE_LEGS",            checkanimdone_legs },
      { "ANIMDONE_TORSO",           checkanimdone_torso },
      { "CAN_TURN",                 checkcanturn },
      { "CAN_MOVE_LEFT",            checkcanmoveleft },
      { "CAN_MOVE_RIGHT",           checkcanmoveright },
      { "CAN_MOVE_BACKWARD",        checkcanmovebackward },
      { "CAN_MOVE_FORWARD",         checkcanmoveforward },
      { "CAN_WALL_HUG",             checkcanwallhug },
      { "BLOCKED",                  checkblocked },
      { "HANG_ATWALL",              checkhangatwall },
      { "TOUCHED_ROPE",             checktouchrope },
      { "ONROPE",                   checkonrope },
      { "CAN_CLIMB_ROPE",           checkcanclimbrope },
      { "ONGROUND",                 checkonground },
      { "SLOPE_22",                 check22degreeslope },
      { "SLOPE_45",                 check45degreeslope },
      { "RIGHT_LEG_HIGH",           checkrightleghigh },
      { "LEFT_LEG_HIGH",            checkleftleghigh },
      { "CAN_HANG_LEFT",            checkcanhangleft },
      { "CAN_HANG_RIGHT",           checkcanhangright },
      { "CAN_HANG",                 checkcanhang },
      { "CAN_FALL",                 checkcanfall },
      { "AT_DOOR",                  checkatdoor },
		{ "AT_SHGLIEK",               checkatshgliek },
		{ "HAVE_SHGLIEK",             checkhaveshgliek },
		{ "SHGLIEK_DEAD",             checkshgliekdead },
      { "FALLING",                  checkfalling },
      { "HARD_IMPACT",              checkhardimpact },
      { "CAN_GRAB_LEDGE",           checkcangrabledge },
      { "LEDGE_HEIGHT",             checkledgeheight },
      { "CAN_GRAB_PIPE",            checkcangrabpipe },
      { "CAN_GRAB_MONKEYBARS",      checkcangrabmonkeybar },
      { "CAN_PULLUP",               checkcanpullup },
      { "KILLED",                   checkdead },
      { "HEALTH",                   checkhealth },
      { "PAIN",                     checkpain },
      { "PAIN_TYPE",                checkpaintype },
      { "PAIN_DIRECTION",           checkpaindirection },
      { "PAIN_THRESHOLD",           checkpainthreshold },
      { "PAIN_ACCUMULATED",         checkaccumulatedpain },
      { "KNOCKDOWN",                checkknockdown },
      { "LEGS",                     checklegsstate },
      { "TORSO",                    checktorsostate },
      { "AT_USEANIM",               checkatuseanim },
      { "TOUCHEDUSEANIM",           checktouchuseanim },
      { "FINISHEDUSEANIM",          checkuseanimfinished },
      { "AT_USEOBJECT",             checkatuseobject },
      { "LOOP_USEOBJECT",           checkloopuseobject },
      { "CAN_PUSH",                 checkpush },
      { "CAN_PULL",                 checkpull },
      { "AT_LADDER",                checkladder },
      { "FEET_AT_LADDER",           checkfeetatladder },
      { "CAN_CLIMB_LADDER",         checkcanclimbladder },
      { "CAN_STAND",                checkcanstand },
      { "CHANCE",                   checkchance },
      { "FACING_UP_SLOPE",          checkfacingupslope },
      { "FACING_DOWN_SLOPE",        checkfacingdownslope },
      { "TURNED_LEFT",              checkturnedleft },
      { "TURNED_RIGHT",             checkturnedright },
      { "IN_VEHICLE",               checkinvehicle },
      { "WATER_LEVEL",              checkwaterlevel },
      { "PICKUP_ENEMY",             checkpickupenemy },
      { "SOLID_FORWARD",            checksolidforward },
      { "GOT_COOL_ITEM",            checkcoolitem },
      { "GROUNDENTITY",             checkgroundentity },
      { "FAKEPLAYERACTIVE",         checkfakeplayeractive },

      // Weapon conditions
      { "ATTACKLEFT",                      checkattackleft },  // Checks to see if there is an active weapon as well as the button being pressed
      { "ATTACKRIGHT",                     checkattackright }, // Checks to see if there is an active weapon as well as the button being pressed
      { "ATTACKLEFTBUTTON",                checkattackbuttonleft }, // Checks to see if the left attack button is pressed
      { "ATTACKRIGHTBUTTON",               checkattackbuttonright },// Checks to see if the right attack button is pressed
      { "HAS_WEAPON",                      checkhasweapon },
      { "NEW_WEAPON",                      checknewweapon },
      { "IS_NEW_WEAPON",                   checkuseweapon },
      { "IS_WEAPON_ACTIVE",                checkweaponactive },
      { "IS_WEAPON_READY_TO_FIRE",         checkweaponreadytofire },
      { "IS_WEAPON_READY_TO_FIRE_NOSOUND", checkweaponreadytofire_nosound },
      { "IS_DUALWEAPON_READY_TO_FIRE",     checkdualweaponreadytofire },
      { "PUTAWAYLEFT",                     checkputawayleft },
      { "PUTAWAYRIGHT",                    checkputawayright },
      { "PUTAWAYBOTH",                     checkputawayboth },
      { "TARGET_ACQUIRED",                 checktargetacquired },
      { "ANY_WEAPON_ACTIVE",               checkanyweaponactive },
      { "ATTACK_BLOCKED",                  checkattackblocked },
      { "STATE_ACTIVE",                    checkstatename },
      { "BLOCK_DELAY",                     checkblockdelay },
      { "DUALWIELD",                       checkdualwield },      
      { "DUALWIELDWEAPONS",                checkdualweapons },
      { "MUZZLE_CLEAR",                    checkmuzzleclear },
      { "HAS_AMMO",                        checkweaponhasammo },
      { "HAS_ARMORPIECE",                  checkarmorpiece },
      { "SPECIALMOVE",                     checkspecialmove },
      { "WEAPONS_HOLSTERED",               checkweaponsholstered },
      { NULL,                              NULL },
   };

movecontrolfunc_t Player::MoveStartFuncs[] =
   {
   NULL,             // MOVECONTROL_USER,       // Quake style
   NULL,             // MOVECONTROL_LEGS,       // Quake style, legs state system active
   NULL,             // MOVECONTROL_ANIM,       // move based on animation, with full collision testing
   NULL,             // MOVECONTROL_ABSOLUTE,   // move based on animation, with full collision testing but no turning
   StartHang,        // MOVECONTROL_HANGING,    // move based on animation, with full collision testing, hanging
   NULL,             // MOVECONTROL_WALLHUG,    // move based on animation, with full collision testing, hanging
   StartMonkeyBars,  // MOVECONTROL_MONKEYBARS, // move based on animation, with full collision testing, monkey bars
   StartPipeCrawl,   // MOVECONTROL_PIPECRAWL,  // move based on animation, with full collision testing, crawling on pipe
   StartPipeCrawl,   // MOVECONTROL_PIPEHANG,   // move based on animation, with full collision testing, hanging from pipe
   StartStepUp,      // MOVECONTROL_STEPUP,
   RopeGrab,         // MOVECONTROL_ROPE_GRAB
   RopeRelease,      // MOVECONTROL_ROPE_RELEASE
   NULL,             // MOVECONTROL_ROPE_MOVE
	StartPickup,      // MOVECONTROL_PICKUPENEMY
   StartPush,        // MOVECONTROL_PUSH
   StartClimbWall,   // MOVECONTROL_CLIMBWALL
   StartUseAnim,     // MOVECONTROL_USEANIM
   NULL,             // MOVECONTROL_CROUCH
   StartLoopUseAnim, // MOVECONTROL_LOOPUSEANIM
   SetupUseObject,   // MOVECONTROL_USEOBJECT
   StartCoolItemAnim, // MOVECONTROL_COOLOBJECT
   StartFakePlayer,  // MOVECONTROL_FAKEPLAYER
   };

Player::Player()
	{
   //
   // set the entity type
   //
	edict->s.eType       = ET_PLAYER;
   respawn_time         = -1;
   statemap_Legs        = NULL;
   statemap_Torso       = NULL;
   camera               = NULL;
   atobject             = NULL;
   atobject_dist        = 0;
   toucheduseanim       = NULL;
   useitem_in_use       = NULL;
   horizontalpipe       = NULL;
	damage_blood         = 0;
   damage_count         = 0;
   damage_from          = vec_zero;
	damage_alpha         = 0;
   last_attack_button   = 0;
   attack_blocked       = qfalse;
   shield_active        = qfalse;
   crouch_flag          = qfalse;
   ledgeheight_left     = 0;
   ledgeheight_right    = 0;
   monkeybar_left       = 0;
   monkeybar_right      = 0;
   monkeybar_dir        = 0;
   canfall              = false;
   move_left_dist       = 0;
   move_right_dist      = 0;
   move_backward_dist   = 0;
   move_forward_dist    = 0;
   moveresult           = MOVERESULT_NONE;
   animspeed            = 0;
   airspeed             = 200;
   vehicle              = NULL;
   action_level         = 0;
	have_shgliek         = false;
   pickup_enemy         = false;
   adjust_torso         = qfalse;
   dual_wield_active    = qfalse;
   cool_item            = NULL;
   weapons_holstered_by_code = qfalse;
   actor_camera         = NULL;
   cool_camera          = NULL;
	damage_multiplier    = 1;
   take_pain            = true;
	look_at_time			= 0;
   outfit_level         = 0;
   fakePlayer_active    = qfalse;

   memset( oldstats, 0, sizeof( oldstats ) );

   // make sure that we are not overflowing the stats for players
   assert( STAT_LAST_STAT <= MAX_STATS );

	fov = atof( Info_ValueForKey( client->pers.userinfo, "fov" ) );
	if ( fov < 1 )
      {
		fov = 90;
      }
	else if ( fov > 160 )
      {
		fov = 160;
      }

   if ( !LoadingSavegame )
      {
      crosshair = new Entity;
      crosshair->setModel( "crosshair.spr" );
      crosshair->setSolidType( SOLID_NOT );
      crosshair->setMoveType( MOVETYPE_NONE );
      crosshair->takedamage = DAMAGE_NO;
      crosshair->hideModel();
      }

   //
   // set targetnameplayer
   //
   SetTargetName( "player" );

   Init();

	SetOutfit( 0 );
	}

Player::~Player()
	{
   int         i,num;
   Conditional *cond;
   
   edict->s.modelindex = 0;   

   num = legs_conditionals.NumObjects();
   for ( i=num; i>0; i-- )
      {
      cond = legs_conditionals.ObjectAt( i );
      delete cond;
      }

   num = torso_conditionals.NumObjects();
   for ( i=num; i>0; i-- )
      {
      cond = torso_conditionals.ObjectAt( i );
      delete cond;
      }
   
   legs_conditionals.FreeObjectList();
	torso_conditionals.FreeObjectList();
	}

static qboolean logfile_started = qfalse;

void Player::Init
	(
	void
	)

	{
   InitClient();
   InitPhysics();
   InitPowerups();
   InitWorldEffects();
   InitSound();
   InitView();
   InitState();
   InitEdict();
   InitModel();
   InitWeapons();
   InitInventory();
   InitHealth();
   InitWaterPower();

   LoadStateTable();

   if ( !LoadingSavegame )
      {
      ChooseSpawnPoint();
      }

   // make sure we put the player back into the world
   link();
   logfile_started = qfalse;
	}

void Player::InitEdict
   (
   void
   )

   {
   // entity state stuff
   setSolidType( SOLID_BBOX );
	setMoveType( MOVETYPE_WALK );
	setSize( Vector( -16, -16, 0 ), Vector( 16, 16, STAND_HEIGHT ) );
	edict->clipmask	 = MASK_PLAYERSOLID;
	edict->svflags		&= ~SVF_DEADMONSTER;
   edict->svflags    &= ~SVF_HIDEOWNER;
   edict->ownerNum    = ENTITYNUM_NONE;

	// clear entity state values
	edict->s.eFlags		= 0;
	edict->s.frame	      = 0;

   // players have precise shadows
   edict->s.renderfx |= RF_SHADOW_PRECISE;  
   }

void Player::InitSound
   (
   void
   )

   {
   //
   // reset the music
   //
	client->ps.current_music_mood  = mood_normal;
	client->ps.fallback_music_mood = mood_normal;
   ChangeMusic( "normal", "normal", false );

	client->ps.music_volume           = 1.0;
	client->ps.music_volume_fade_time = 0.0;
	ChangeMusicVolume( 1.0, 0.0 );

   music_forced = false;

	// Reset the reverb stuff

	client->ps.reverb_type  = eax_generic;
	client->ps.reverb_level = 0;
	SetReverb( client->ps.reverb_type, client->ps.reverb_level );
   }

void Player::InitClient
   (
   void
   )

   {
	client_persistant_t	saved;

   // deathmatch wipes most client data every spawn
   if ( deathmatch->integer )
		{
		char userinfo[ MAX_INFO_STRING ];

		memcpy( userinfo, client->pers.userinfo, sizeof( userinfo ) );
		G_InitClientPersistant( client );
		G_ClientUserinfoChanged( edict, userinfo );
		}

	// clear everything but the persistant data and fov
	saved = client->pers;
	memset( client, 0, sizeof( *client ) );
	client->pers = saved;

   client->ps.clientNum = client - game.clients;
   }

void Player::InitState
   (
   void
   )

   {
   gibbed             = false;
   pain               = 0;
   accumulated_pain   = 0;
   nextpaintime       = 0;
   knockdown          = false;
   pain_dir           = PAIN_NONE;
   pain_type          = MOD_NONE;
   crouch_flag        = false;
   takedamage			 = DAMAGE_AIM;
   deadflag				 = DEAD_NO;
	flags					&= ~FL_NO_KNOCKBACK;
	flags					|= ( FL_BLOOD | FL_DIE_GIBS );

   if ( !com_blood->integer )
      {
      flags &= ~FL_BLOOD;
      flags &= ~FL_DIE_GIBS;
      }
   }


void Player::InitWaterPower
   (
   void
   )

   {
   water_power       = 50;
   max_water_power   = 100;
   SetWaterPower( water_power );
   }

void Player::InitHealth
   (
   void
   )

   {
   // Don't do anything if we're loading a server game.
   // This is either a loadgame or a restart
   if ( LoadingSavegame )
      {
      return;
      }

   // reset the health values
   health	  = 100;
	max_health = 100;
   }

void Player::InitModel
   (
   void
   )

   {
   orientation_t orient;
   int anim;
   int tagnum;

   setModel( str( g_playermodel->string ) + ".tik" );

   SetControllerTag( HEAD_TAG,   gi.Tag_NumForName( edict->s.modelindex, "Bip01 Head" ) );
   SetControllerTag( TORSO_TAG,  gi.Tag_NumForName( edict->s.modelindex, "Bip01 Spine1" ) );
   SetControllerTag( R_ARM_TAG,  gi.Tag_NumForName( edict->s.modelindex, R_ARM_NAME ) );
   SetControllerTag( L_ARM_TAG,  gi.Tag_NumForName( edict->s.modelindex, L_ARM_NAME ) );
	SetControllerTag( MOUTH_TAG,   gi.Tag_NumForName( edict->s.modelindex, "tag_mouth" ) );

   anim = gi.Anim_NumForName( edict->s.modelindex, "hang_idle" );

   tagnum = gi.Tag_NumForName( edict->s.modelindex, "tag_weapon_right" ) & TAG_MASK;
   orient = gi.Tag_Orientation( edict->s.modelindex, anim, 0, tagnum, 1.0f, NULL, NULL );
   base_righthand_pos = orient.origin;

   tagnum = gi.Tag_NumForName( edict->s.modelindex, "tag_weapon_left" ) & TAG_MASK;
   orient = gi.Tag_Orientation( edict->s.modelindex, anim, 0, tagnum, 1.0f, NULL, NULL );
   base_lefthand_pos = orient.origin;

   anim = gi.Anim_NumForName( edict->s.modelindex, "stand_idle" );

   tagnum = gi.Tag_NumForName( edict->s.modelindex, "Bip01 R Foot" ) & TAG_MASK;
   orient = gi.Tag_Orientation( edict->s.modelindex, anim, 0, tagnum, 1.0f, NULL, NULL );
   base_rightfoot_pos = orient.origin;
   base_rightfoot_pos.z = 0;

   tagnum = gi.Tag_NumForName( edict->s.modelindex, "Bip01 L Foot" ) & TAG_MASK;
   orient = gi.Tag_Orientation( edict->s.modelindex, anim, 0, tagnum, 1.0f, NULL, NULL );
   base_leftfoot_pos = orient.origin;
   base_leftfoot_pos.z = 0;

   showModel();

	yawing_left = qfalse;
	yawing_right = qfalse;
   }

void Player::InitPhysics
   (
   void
   )

   {
   // Physics stuff
   oldvelocity = vec_zero;
	velocity    = vec_zero;
   old_v_angle = v_angle;
	gravity     = 1.0;
   falling     = false;
   hardimpact  = false;
	mass			= 200;
   rope_touch  = NULL;
   rope_grabbed = NULL;
   memset( &last_ucmd, 0, sizeof( last_ucmd ) );
   }

void Player::InitPowerups
   (
   void
   )

   {
   // powerups
   poweruptimer   = 0;
   poweruptype    = 0;
   }

void Player::InitWorldEffects
   (
   void
   )

   {
   // world effects
   next_drown_time    = 0;
   next_painsound_time    = 0;
	air_finished       = level.time + 20;
	old_waterlevel     = 0;
	drown_damage       = 0;
   }

void Player::InitWeapons
   (
   void
   )

   {
   // Don't do anything if we're loading a server game.
   // This is either a loadgame or a restart
   if ( LoadingSavegame )
      {
      return;
      }


   }

void Player::InitInventory
   (
   void
   )

   {
   }

void Player::InitView
   (
   void
   )

   {
   // view stuff
   camera         = NULL;
	v_angle			= vec_zero;
   SetViewAngles( v_angle );
	viewheight	   = STAND_EYE_HEIGHT;

   head_target       = NULL;
   left_arm_target   = NULL;
   right_arm_target  = NULL;

   // blend stuff
   damage_blend	= vec_zero;
   }

void Player::ChooseSpawnPoint
   (
   void
   )

   {
   str thread;

   // set up the player's spawn location
   SelectSpawnPoint( origin, angles, thread );
	setOrigin( origin	+ "0 0 1" );
   origin.copyTo( edict->s.origin2 );
	edict->s.renderfx |= RF_FRAMELERP;

   KillBox( this );

   setAngles( angles );
   SetViewAngles( angles );

   if ( thread.length() )
      {
      ExecuteThread( thread );
      }
   }

void Player::EndLevel
   (
   Event *ev
   )

   {
   InitPowerups();
   if ( health > max_health )
      {
      health = max_health;
      }

   if ( health < 1 )
      {
      health = 1;
      }
   }

void Player::Respawn
	(
	Event *ev
	)

	{
   if ( deathmatch->integer )
		{
      assert ( deadflag == DEAD_DEAD );

		respawn_time = level.time;

      Init();

		// hold in place briefly
		client->ps.pm_time = 50;
      client->ps.pm_flags |= PMF_TIME_TELEPORT;

		return;
		}
   else
      {
#ifdef PRE_RELEASE_DEMO
      gi.SendConsoleCommand( "forcemenu demomain; forcemenu loadsave\n" );
#else
      gi.SendConsoleCommand( "forcemenu main; forcemenu loadsave\n" );
#endif
      logfile_started = qfalse;
      }
	}

void Player::SetDeltaAngles
   (
   void
   )

   {
   int i;

   // Use v_angle since we may be in a camera
	for( i = 0; i < 3; i++ )
      {
		client->ps.delta_angles[ i ] = ANGLE2SHORT( v_angle[ i ] );
      }
   }

void Player::Obituary
	(
	Entity *attacker,
   Entity *inflictor,
   int meansofdeath
	)

	{
   if ( !deathmatch->integer )
      {
      return;
      }
	}

void Player::Dead
   (
   Event *ev
   )

   {
   deadflag = DEAD_DEAD;

   // stop animating
   StopAnimating( legs );
   
   //
   // drop anything that might be attached to us
   //

	// FIXME : re-enable and fix dropping issues for deathmatch?
   /* if ( numchildren )
      {
      Entity * child;
      int i;
      //
      // detach all our children
      //
      for ( i=0; i < MAX_MODEL_CHILDREN; i++ )
         {
         if ( children[i] != ENTITYNUM_NONE )
            {
            child = ( Entity * )G_GetEntity( children[ i ] );
            child->ProcessEvent( EV_Detach );
            }
         }
      } */
   }

void Player::Killed
	(
	Event *ev
	)

	{
	Entity   *attacker;
   Entity   *inflictor;
   int      meansofdeath;

	attacker       = ev->GetEntity( 1 );
	inflictor      = ev->GetEntity( 3 );
	meansofdeath   = ev->GetInteger( 4 );

   pain_type = (meansOfDeath_t)meansofdeath;

   if ( attacker && inflictor )
      Obituary( attacker, inflictor, meansofdeath );


	deadflag	= DEAD_DYING;

	respawn_time = level.time + 1.0;

	edict->clipmask = MASK_DEADSOLID;
   edict->svflags |= SVF_DEADMONSTER;

	setContents( CONTENTS_CORPSE );

   setMoveType( MOVETYPE_NONE );

	angles.x = 0;
	angles.z = 0;
	setAngles( angles );

   //
   // change music
   //
   ChangeMusic( "failure", "normal", true );

	health = 0;

	// Stop targeting monsters

	if ( left_arm_target )
		{
		left_arm_target->edict->s.eFlags &= ~EF_LEFT_TARGETED;
		left_arm_target = NULL;
		}

	if ( right_arm_target )
		{
		right_arm_target->edict->s.eFlags &= ~EF_RIGHT_TARGETED;
		right_arm_target = NULL;
		}

   // Post a dead event just in case
   PostEvent( EV_Player_Dead, 2 );
   }

void Player::Pain
	(
	Event *ev
	)

	{
	float		damage,yawdiff;
	Entity	*attacker;
   int      meansofdeath;
   Vector   dir,pos,attack_angle;

	damage	      = ev->GetFloat( 1 );
	attacker       = ev->GetEntity( 2 );
	meansofdeath   = ev->GetInteger( 3 );
   pos            = ev->GetVector( 4 );
   dir            = ev->GetVector( 5 );

	if ( !damage && !knockdown )
		return;
		
   client->ps.stats[ STAT_LAST_PAIN ] = damage;
	
   // Determine direction
   attack_angle = dir.toAngles();
	yawdiff = torsoAngles[YAW] - attack_angle[YAW] + 180;
	yawdiff = AngleNormalize180( yawdiff );

   if ( yawdiff > -45 && yawdiff < 45 )
      pain_dir = PAIN_FRONT;
   else if ( yawdiff < -45 && yawdiff > -135 )
      pain_dir = PAIN_LEFT;
   else if ( yawdiff > 45 && yawdiff < 135 )
      pain_dir = PAIN_RIGHT;
   else
      pain_dir = PAIN_REAR;
   
   // accumulate pain for animation purposes
   if ( take_pain )
      {
      accumulated_pain   += damage; 
      }

   // Spawn off any damage effect if we get hit with a certain type of damage
   SpawnDamageEffect( (meansOfDeath_t)meansofdeath );
   
   pain_type          = (meansOfDeath_t)meansofdeath;

   // Only set the regular pain level if enough time since last pain has passed
   if ( ( level.time > nextpaintime ) && take_pain )
      {
      pain = damage;
      }

   if ( meansofdeath > MOD_LAST_SELF_INFLICTED )
      {
      // increase action level of game as we're getting hurt
		IncreaseActionLevel( damage );
      }

	// add to the damage inflicted on a player this frame
	// the total will be turned into screen blends and view angle kicks
	// at the end of the frame
	damage_blood   += damage;
   damage_from    += ev->GetVector( 5 ) * damage;
	}

void Player::DoUse
	(
	Event *ev
	)

	{
	int		   i;
	int		   num;
   int         touch[ MAX_GENTITIES ];
   gentity_t   *hit;
	Event		   *event;
	Vector	   min;
	Vector	   max;
	Vector	   offset;
	trace_t	   trace;
	Vector	   start;
	Vector	   end;
	float		   t;

   // if we are in a vehicle, we want to use the vehicle always
   if ( vehicle )
      {
		event = new Event( EV_Use );
		event->AddEntity( this );
		vehicle->ProcessEvent( event );
      return;
      }

   start = origin;
   start.z += viewheight;
	end = start + yaw_forward * 64.0f;

	trace = G_Trace( start, vec_zero, vec_zero, end, this, MASK_USABLE, true, "Player::DoUse" );

	t = 64 * trace.fraction - maxs[ 0 ];
	if ( t < 0 )
		{
		t = 0;
		}

	offset = yaw_forward * t;

	min = start + offset + "-16 -16 -16";
	max = start + offset + "16 16 16";

   num = gi.AreaEntities( min, max, touch, MAX_GENTITIES );

	// be careful, it is possible to have an entity in this
	// list removed before we get to it (killtriggered)
	for( i = 0; i < num; i++ )
		{
		hit = &g_entities[ touch[ i ] ];
		if ( !hit->inuse )
			{
			continue;
			}

		assert( hit->entity );

		event = new Event( EV_Use );
		event->AddEntity( this );
		hit->entity->ProcessEvent( event );
		}
	}

void Player::TouchStuff
	(
	pmove_t *pm
	)

	{
   gentity_t  *other;
	Event		*event;
	int		i;
	int		j;

   //
   // clear out any conditionals that are controlled by touching
   //
   toucheduseanim = NULL;

	if ( getMoveType() != MOVETYPE_NOCLIP )
		{
		G_TouchTriggers( this );
		}

	// touch other objects
	for( i = 0; i < pm->numtouch; i++ )
		{
		other = &g_entities[ pm->touchents[ i ] ];

		for( j = 0; j < i ; j++ )
			{
         gentity_t *ge = &g_entities[ j ];

			if ( ge == other )
				break;
			}

		if ( j != i )
			{
			// duplicated
			continue;
			}

      // Don't bother touching the world
		if ( ( !other->entity ) || ( other->entity == world ) )
			{
			continue;
			}

		event = new Event( EV_Touch );
		event->AddEntity( this );
		other->entity->ProcessEvent( event );

		event = new Event( EV_Touch );
		event->AddEntity( other->entity );
		ProcessEvent( event );
		}
	}

void Player::GetMoveInfo
	(
	pmove_t *pm
	)

	{
   moveresult = pm->moveresult;

	if ( !deadflag )
		{
		v_angle[ 0 ] = pm->ps->viewangles[ 0 ];
		v_angle[ 1 ] = pm->ps->viewangles[ 1 ];
		v_angle[ 2 ] = pm->ps->viewangles[ 2 ];

      if ( moveresult == MOVERESULT_TURNED )
         {
         angles.y = v_angle[ 1 ];
         setAngles( angles );
         SetViewAngles( angles );
         }
		}

   setOrigin( Vector( pm->ps->origin[ 0 ], pm->ps->origin[ 1 ], pm->ps->origin[ 2 ] ) );
	velocity = Vector( pm->ps->velocity[ 0 ], pm->ps->velocity[ 1 ], pm->ps->velocity[ 2 ] );

   if ( client->ps.pm_flags & PMF_FROZEN || client->ps.pm_flags & PMF_NO_MOVE )
      {
      velocity = vec_zero;
      }
   else
      {
	   setSize( pm->mins, pm->maxs );

	   viewheight	= pm->ps->viewheight;
      }

   // water type and level is set in the predicted code
   waterlevel = pm->waterlevel;
   watertype = pm->watertype;

   // Set the ground entity
   groundentity = NULL;
   if ( pm->ps->groundEntityNum != ENTITYNUM_NONE )
      {
      groundentity = &g_entities[ pm->ps->groundEntityNum ];
      airspeed = 200;
      }
	}

void Player::SetMoveInfo
	(
	pmove_t *pm,
	usercmd_t *ucmd
	)

	{
   Vector move;

   // set up for pmove
	memset( pm, 0, sizeof( pmove_t ) );

   velocity.copyTo( client->ps.velocity );

	pm->ps             = &client->ps;

   if ( ucmd )
      {
	   pm->cmd            = *ucmd;
      }

	pm->tracemask      = MASK_PLAYERSOLID;
	pm->trace          = gi.trace;
	pm->pointcontents  = gi.pointcontents;
	pm->trypush        = TryPush;

   pm->ps->origin[ 0 ] = origin.x;
   pm->ps->origin[ 1 ] = origin.y;
   pm->ps->origin[ 2 ] = origin.z;

	pm->ps->velocity[ 0 ] = velocity.x;
	pm->ps->velocity[ 1 ] = velocity.y;
	pm->ps->velocity[ 2 ] = velocity.z;

   // save off pm_runtime
   if ( pm->ps->pm_runtime )
      pm_lastruntime = pm->ps->pm_runtime;
	}

pmtype_t Player::GetMovePlayerMoveType
	(
	void
	)

	{
	if ( getMoveType() == MOVETYPE_NOCLIP )
		{
		return PM_NOCLIP;
		}
	else if ( deadflag )
		{
		return PM_DEAD;
		}
   else
      {
      return PM_NORMAL;
		}
	}

void Player::CheckGround
   (
   void
   )

   {
   pmove_t pm;

   SetMoveInfo( &pm, current_ucmd );
   Pmove_GroundTrace( &pm );
   GetMoveInfo( &pm );
   }

qboolean Player::MonkeyBarMove
   (
   Vector &move,
   Vector *endpos
   )

   {
	Vector  up;
   Vector  down;
	trace_t trace;

	Vector  start( origin );
	Vector  end( origin + move );

   trace = G_Trace( start, mins, maxs, end, this, MASK_PLAYERSOLID, true, "MonkeyBarMove" );
   if ( trace.startsolid )
      {
      if ( endpos )
         {
         *endpos = origin;
         }
      return qfalse;
      }

   Vector pos( trace.endpos );

   //
   // check if the right hand will still be on the monkey bars
   //
	end = righthand_pos + yaw_left * 4.0f - origin + pos;
   start.x = end.x;
   start.y = end.y;
   start.z = absmax.z;

   trace = G_Trace( start, Vector( -4, -4, 0 ), Vector( 4, 4, 2 ), end, this, MASK_PLAYERSOLID, false, "MonkeyBarMove" );
   if ( trace.startsolid || ( trace.fraction >= 1.0f ) || !trace.ent || !trace.ent->entity->isSubclassOf( MonkeyBars ) )
      {
      if ( endpos )
         {
         *endpos = origin;
         }
      return qfalse;
      }

   //
   // check if the left hand will still be on the monkey bars
   //
	end = lefthand_pos - yaw_left * 4.0f - origin + pos;
   start.x = end.x;
   start.y = end.y;
   start.z = absmax.z;

   trace = G_Trace( start, Vector( -4, -4, 0 ), Vector( 4, 4, 2 ), end, this, MASK_PLAYERSOLID, false, "MonkeyBarMove" );
   if ( trace.startsolid || ( trace.fraction >= 1.0f ) || !trace.ent || !trace.ent->entity->isSubclassOf( MonkeyBars ) )
      {
      if ( endpos )
         {
         *endpos = origin;
         }
      return qfalse;
      }

   if ( endpos )
      {
      *endpos = pos;
      }

   return qtrue;
   }

qboolean Player::PipeMove
   (
   Vector &move,
   Vector *endpos
   )

   {
	Vector  up;
   Vector  down;
	trace_t trace;

	Vector  start( origin );
	Vector  end( origin + move );

   trace = G_Trace( start, mins, maxs, end, this, MASK_PLAYERSOLID, true, "PipeMove" );
   if ( trace.startsolid )
      {
      if ( endpos )
         {
         *endpos = origin;
         }
      return qfalse;
      }

   Vector pos( trace.endpos );

   end.x = pos.x;
   end.y = pos.y;

   end.z = righthand_pos.z + 1 - maxs.z;

	trace = G_Trace( pos, mins, maxs, end, this, MASK_DEADSOLID, true, "PipeMove" );
   if ( ( trace.fraction < 1.0f ) && trace.ent && trace.ent->entity->isSubclassOf( HorizontalPipe ) )
      {
      if ( endpos )
         {
         *endpos = pos;
         }

      return qtrue;
      }

   if ( endpos )
      {
      *endpos = origin;
      }

   return qfalse;
   }

qboolean Player::AnimMove
   (
   Vector &move,
   Vector *endpos
   )

   {
	Vector  up;
   Vector  down;
	trace_t trace;
   int     mask;
	Vector  start( origin );
	Vector  end( origin + move );

   mask = MASK_PLAYERSOLID;

	// test the player position if they were a stepheight higher
	trace = G_Trace( start, mins, maxs, end, this, mask, true, "AnimMove" );
   if ( trace.fraction < 1 )
      {
      if ( ( movecontrol == MOVECONTROL_HANGING ) || ( movecontrol == MOVECONTROL_CLIMBWALL ) )
         {
         up = origin;
         up.z += move.z;
	      trace = G_Trace( origin, mins, maxs, up, this, mask, true, "AnimMove" );
	      if ( trace.fraction < 1 )
            {
            if ( endpos )
               {
               *endpos = origin;
               }
            return qfalse;
            }

         origin = trace.endpos;
         end = origin;
         end.x += move.x;
         end.y += move.y;

	      trace = G_Trace( origin, mins, maxs, end, this, mask, true, "AnimMove" );
         if ( endpos )
            {
            *endpos = trace.endpos;
            }

         return ( trace.fraction > 0 );
         }
      else
         {
         return TestMove( move, endpos );
         }
      }
   else
      {
      if ( endpos )
         {
         *endpos = trace.endpos;
         }

      return qtrue;
      }
   }

qboolean Player::TestMove
   (
   Vector &move,
   Vector *endpos
   )

   {
   trace_t trace;
   Vector pos( origin + move );

   trace = G_Trace( origin, mins, maxs, pos, this, MASK_PLAYERSOLID, true, "TestMove" );
   if ( trace.allsolid )
      {
		// player is completely trapped in another solid
      if ( endpos )
         {
         *endpos = origin;
         }
		return qfalse;
		}

   if ( trace.fraction < 1.0f )
      {
      Vector up( origin );
      up.z += STEPSIZE;

      trace = G_Trace( origin, mins, maxs, up, this, MASK_PLAYERSOLID, true, "TestMove" );
      if ( trace.fraction == 0.0f )
         {
         if ( endpos )
            {
            *endpos = origin;
            }
		   return qfalse;
         }

      Vector temp( trace.endpos );
      Vector end( temp + move );

      trace = G_Trace( temp, mins, maxs, end, this, MASK_PLAYERSOLID, true, "TestMove" );
      if ( trace.fraction == 0.0f )
         {
         if ( endpos )
            {
            *endpos = origin;
            }
		   return qfalse;
         }

      temp = trace.endpos;

      Vector down( trace.endpos );
      down.z = origin.z;

      trace = G_Trace( temp, mins, maxs, down, this, MASK_PLAYERSOLID, true, "TestMove" );
      }

   if ( endpos )
      {
      *endpos = trace.endpos;
      }

	return qtrue;
   }

qboolean Player::RopeMove
   (
   Vector &move,
   Vector *endpos
   )

   {
   if ( rope_grabbed )
      {
      if ( rope_grabbed->CanClimb( move.z ) )
         {
         rope_grabbed->Climb( move.z );
         *endpos = origin;
         return qtrue;
         }
      }
   return qfalse;
   }

float Player::TestMoveDist
   (
   Vector &move
   )

   {
   Vector endpos;

   TestMove( move, &endpos );
   endpos -= origin;

   return endpos.length();
   }


void Player::CheckMoveFlags
   (
   void
   )

   {
   trace_t trace;
   Vector start;
   Vector end;
   float startz;
   float oldsp;
   Vector olddir( oldvelocity.x, oldvelocity.y, 0 );

   MatrixTransformVector( base_righthand_pos, orientation, righthand_pos );
   MatrixTransformVector( base_lefthand_pos, orientation, lefthand_pos );
   MatrixTransformVector( base_rightfoot_pos, orientation, rightfoot_pos );
   MatrixTransformVector( base_leftfoot_pos, orientation, leftfoot_pos );
   righthand_pos += origin;
   lefthand_pos += origin;
   rightfoot_pos += origin;
   leftfoot_pos += origin;

   if ( !client->ps.walking )
      {
      //
      // if we're not on a pole, check if there's a pole we can grab
      //
      if (
            ( movecontrol != MOVECONTROL_PIPECRAWL ) &&
            ( movecontrol != MOVECONTROL_PIPEHANG )
         )
         {
         end.x = origin.x;
         end.y = origin.y;
         end.z = righthand_pos.z + 1 - maxs.z;
         trace = G_Trace( origin, mins, maxs, end, this, MASK_DEADSOLID, false, "CheckMoveFlags" );
         if ( ( trace.fraction < 1.0f ) && trace.ent && trace.ent->entity->isSubclassOf( HorizontalPipe ) )
            {
            horizontalpipe = trace.ent->entity;
            }
         else
            {
            horizontalpipe = NULL;
            }
         }

      //
      // get the right hand monkey bar height
      //
	   end = righthand_pos + yaw_left * 4.0f;
      start.x = end.x;
      start.y = end.y;
      start.z = absmax.z;

      monkeybar_dir = v_angle.y;

      trace = G_Trace( start, min4x4, max4x4x0, end, this, MASK_DEADSOLID, false, "CheckMoveFlags" );
      if ( !trace.startsolid && ( trace.fraction < 1.0f ) && trace.ent && trace.ent->entity->isSubclassOf( MonkeyBars ) )
         {
         monkeybar_right = end.z + ( start.z - end.z ) * ( 1.0f - trace.fraction );
         monkeybar_dir = ( ( MonkeyBars * )trace.ent->entity )->dir;
         }
      else
         {
         monkeybar_right = MIN_Z;
         }

      //
      // get the left hand monkey bar height
      //
	   end = lefthand_pos - yaw_left * 4.0f;
      start.x = end.x;
      start.y = end.y;
      start.z = absmax.z;

      trace = G_Trace( start, min4x4, max4x4x0, end, this, MASK_DEADSOLID, false, "CheckMoveFlags" );
      if ( !trace.startsolid && ( trace.fraction < 1.0f ) && trace.ent && trace.ent->entity->isSubclassOf( MonkeyBars ) )
         {
         monkeybar_left = end.z + ( start.z - end.z ) * ( 1.0f - trace.fraction );
         }
      else
         {
         monkeybar_left = MIN_Z;
         }
      }
   else
      {
      horizontalpipe = NULL;
      monkeybar_left = MIN_Z;
      monkeybar_right = MIN_Z;
      }

   // trace up to see if the player's hands are not in a solid
   end.x = origin.x;
   end.y = origin.y;
   end.z = origin.z + 208;
   trace = G_Trace( origin, min4x4, max4x4x8, end, this, MASK_DEADSOLID, false, "CheckMoveFlags" );
   startz = trace.endpos[ 2 ];

   //
   // get the right hand ledge height for grabbing ledges
   //
	end	= righthand_pos + yaw_left * 4.0f; // + yaw_forward * 4.0f;
   end.z = origin.z;
   start.x = end.x;
   start.y = end.y;
   start.z = startz;

   trace = G_Trace( start, min4x4, max4x4x8, end, this, MASK_DEADSOLID, false, "CheckMoveFlags" );
   ledgeheight_right = end.z + ( start.z - end.z ) * ( 1.0f - trace.fraction );

	if ( trace.fraction == 1 )
		ledgeheight_right = MIN_Z;

   if ( trace.startsolid )
      {
      start.z = ledgeheight_right;
      trace = G_Trace( start, min4x4, max4x4x8, start, this, MASK_DEADSOLID, false, "CheckMoveFlags" );
      if ( trace.startsolid )
         {
         ledgeheight_right = MIN_Z;
         }
      }

   if ( 
         ( ledgeheight_right != MIN_Z ) &&
         trace.ent &&
         (
            trace.ent->entity->isSubclassOf( HorizontalPipe ) ||
            ( trace.ent->entity->velocity.length() > 0 ) ||
            ( trace.ent->entity->avelocity.length() > 0 )
         )
      )
      {
      ledgeheight_right = MIN_Z;
      }
   if ( 
         ( ledgeheight_right != MIN_Z ) &&
         ( trace.plane.normal[ 2 ] < 0.707 )
      )
      {
      ledgeheight_right = MIN_Z;
      }

   //
   // get the left hand ledge height for grabbing ledges
   //
	end	= lefthand_pos - yaw_left * 4.0f; // + yaw_forward * 4.0f;
   end.z = origin.z;
   start.x = end.x;
   start.y = end.y;
   start.z = startz;

   trace = G_Trace( start, min4x4, max4x4x8, end, this, MASK_DEADSOLID, false, "CheckMoveFlags" );
   ledgeheight_left = end.z + ( start.z - end.z ) * ( 1.0f - trace.fraction );

	if ( trace.fraction == 1 )
		ledgeheight_left = MIN_Z;

   if ( trace.startsolid )
      {
      start.z = ledgeheight_left;
      trace = G_Trace( start, min4x4, max4x4x8, start, this, MASK_DEADSOLID, false, "CheckMoveFlags" );
      if ( trace.startsolid )
         {
         ledgeheight_left = MIN_Z;
         }
      }

   if ( 
         ( ledgeheight_left != MIN_Z ) &&
         trace.ent &&
         (
            trace.ent->entity->isSubclassOf( HorizontalPipe ) ||
            ( trace.ent->entity->velocity.length() > 0 )
         )
      )
      {
      ledgeheight_left = MIN_Z;
      }

   if ( 
         ( ledgeheight_left != MIN_Z ) &&
         ( trace.plane.normal[ 2 ] < 0.707 )
      )
      {
      ledgeheight_left = MIN_Z;
      }

   //
   // Check if moving forward will cause the player to fall
   //
   start = origin + yaw_forward * 52.0f;
	end	= start;
   end.z -= STEPSIZE * 2;

   trace = G_Trace( start, mins, maxs, end, this, MASK_PLAYERSOLID, true, "CheckMoveFlags" );
   canfall = !( trace.fraction < 1.0f );

   if ( !groundentity && ( velocity.z < 0 ) )
      {
      falling = true;
      hardimpact = false;
      }
   else
      {
      hardimpact = ( oldvelocity.z < -400.0f );
      falling = false;
      }

   // check for running into walls
   oldsp = VectorNormalize( olddir );
   if ( ( oldsp > 250.0f ) && ( velocity * olddir < 5.0f ) )
      {
      moveresult = MOVERESULT_HITWALL;
      }

   //
   // Check if the player is at a door, pushobject, or useanim
   //
   start = origin;
	end	= start + yaw_forward * 64.0f;
	trace = G_Trace( start, mins, maxs, end, this, MASK_USABLE, true, "CheckMoveFlags" );

   if ( trace.ent && trace.ent->entity && ( trace.ent->entity != world ) )
      {
      atobject = trace.ent->entity;
      atobject_dist = trace.fraction * 64.0f;
      atobject_dir.setXYZ( -trace.plane.normal[ 0 ], -trace.plane.normal[ 1 ], -trace.plane.normal[ 2 ] );
      }
   else
      {
      atobject = NULL;
      }

   //
   // get the distances the player can move left, right, forward, and back
   //
   if ( ( movecontrol == MOVECONTROL_USER ) || ( movecontrol == MOVECONTROL_LEGS ) )
      {
      move_left_dist     = TestMoveDist( yaw_left * 128.0f );
      move_right_dist    = TestMoveDist( yaw_left * -128.0f );
      move_backward_dist = TestMoveDist( yaw_forward * -128.0f );
      move_forward_dist  = TestMoveDist( yaw_forward * 128.0f );
      }
   else
      {
      move_left_dist     = CheckMoveDist( yaw_left * 2.0f );
      move_right_dist    = CheckMoveDist( yaw_left * -2.0f );
      move_backward_dist = CheckMoveDist( yaw_forward * -2.0f );
      move_forward_dist  = CheckMoveDist( yaw_forward * 2.0f );
      }
   }

qboolean Player::CheckMove
   (
   Vector &move,
   Vector *endpos
   )

   {
   switch( movecontrol )
      {
      case MOVECONTROL_MONKEYBARS :
         return MonkeyBarMove( move, endpos );
         break;

      case MOVECONTROL_PIPECRAWL :
      case MOVECONTROL_PIPEHANG :
         return PipeMove( move, endpos );
         break;

      case MOVECONTROL_ROPE_MOVE :
         return RopeMove( move, endpos );
         break;

      default :
         return AnimMove( move, endpos );
         break;
      }
   }

float Player::CheckMoveDist
   (
   Vector &move
   )

   {
   Vector endpos;

   CheckMove( move, &endpos );
   endpos -= origin;

   return endpos.length();
   }

void Player::ClientMove
	(
	usercmd_t *ucmd
	)

	{
   pmove_t pm;
   Vector move;

   oldorigin = origin;

	client->ps.pm_type = GetMovePlayerMoveType();

   // set move flags
   client->ps.pm_flags &= ~( PMF_FROZEN | PMF_NO_PREDICTION | PMF_NO_MOVE | PMF_DUCKED | PMF_LEGS_LIFTED | PMF_NO_GRAVITY );

   if ( level.playerfrozen )
		{
      client->ps.pm_flags |= PMF_FROZEN;
		}

	if ( flags & FL_IMMOBILE || flags & FL_PARTIAL_IMMOBILE )
		{
		client->ps.pm_flags |= PMF_NO_MOVE;
		client->ps.pm_flags |= PMF_NO_PREDICTION;
		}

   switch( movecontrol )
      {
      case MOVECONTROL_USER :
      case MOVECONTROL_LEGS :
         // FIXME, should be done properly, but not enough time
         // turn off prediction when standing on platforms that are moving
         if ( groundentity && ( groundentity->entity ) && 
				  ( ( groundentity->entity->velocity.length() ) || ( groundentity->entity->avelocity.length() ) ) )
            {
            //
            // we kill the delta, so we don't move twice as fast
            //
            total_delta = vec_zero;
            client->ps.pm_flags |= PMF_NO_PREDICTION;
            }
         break;

      case MOVECONTROL_ANIM :
      case MOVECONTROL_ABSOLUTE :
      case MOVECONTROL_HANGING :
      case MOVECONTROL_STEPUP :
      case MOVECONTROL_MONKEYBARS :
      case MOVECONTROL_WALLHUG :
      case MOVECONTROL_ROPE_RELEASE :
		case MOVECONTROL_PICKUPENEMY :
      case MOVECONTROL_PUSH :
      case MOVECONTROL_CLIMBWALL :
      case MOVECONTROL_PIPEHANG :
         client->ps.pm_flags |= PMF_NO_PREDICTION;
         break;

      case MOVECONTROL_PIPECRAWL :
         client->ps.pm_flags |= PMF_NO_PREDICTION | PMF_LEGS_LIFTED;
         break;

      case MOVECONTROL_CROUCH :
         client->ps.pm_flags |= PMF_NO_PREDICTION | PMF_DUCKED;
         break;

      default:
         client->ps.pm_flags |= PMF_NO_PREDICTION;
		}

   // No prediction on a rope
   if ( rope_grabbed )
      {
      client->ps.pm_flags |= PMF_NO_PREDICTION | PMF_NO_GRAVITY;
      }

   if ( !groundentity )
      {
      client->ps.speed = airspeed;
      }
   else if ( getMoveType() == MOVETYPE_NOCLIP || ( waterlevel > 1 ) )
      {
      client->ps.speed = 200;
      }
   else
      {
      client->ps.speed = animspeed;
      }

	if ( getMoveType() == MOVETYPE_NOCLIP )
		{
		if ( last_ucmd.buttons & BUTTON_RUN )
			client->ps.speed = 200;
		else
			client->ps.speed = 50;
		}

   if (
         client->ps.feetfalling && 
         ( !rope_grabbed ) &&
         ( waterlevel < 2 ) && 
         !( client->ps.pm_time ) 
      )
      {
      ucmd->forwardmove = 0;
      ucmd->rightmove = 0;
      }
   if ( fakePlayer_active )
      {
      ucmd->forwardmove = 0;
      ucmd->rightmove = 0;
      ucmd->upmove = 0;
      }

   client->ps.gravity = sv_gravity->value * gravity;

   // FIXME
   // do this a better way
   if ( ( movecontrol != MOVECONTROL_HANGING ) && ( movecontrol != MOVECONTROL_ABSOLUTE ) &&
      ( movecontrol != MOVECONTROL_WALLHUG ) && ( movecontrol != MOVECONTROL_MONKEYBARS ) &&
      ( movecontrol != MOVECONTROL_PIPECRAWL ) && ( movecontrol != MOVECONTROL_STEPUP ) &&
      ( movecontrol != MOVECONTROL_PIPEHANG ) &&
      ( movecontrol != MOVECONTROL_PUSH ) && ( movecontrol != MOVECONTROL_CLIMBWALL ) )
      {
      Vector oldpos( origin );
      qboolean standing;

      CheckGround();

      //FIXME
      // There's probably a better way to do this
      // this assumes we are moving less than 5 units per second or about 3 inches per second
      if ( client->ps.walking && ( getMoveType() != MOVETYPE_NOCLIP ) && ( velocity == vec_zero ) && ( animspeed < 5 ) )
         {
         // pretend that we can really move
         client->ps.speed = 200;

         standing = qtrue;

         Vector oldvel( velocity );

         SetMoveInfo( &pm, ucmd );
         Pmove( &pm );
         GetMoveInfo( &pm );

         client->ps.speed = animspeed;

         // save off origin
         velocity = oldvel;
         VectorCopy( velocity, client->ps.velocity );
         }
      else
         {
         standing = qfalse;

         SetMoveInfo( &pm, ucmd );
         Pmove( &pm );
         GetMoveInfo( &pm );
         }

      ProcessPmoveEvents( pm.pmoveEvent );

      // if we're not moving, set the blocked flag in case the user is trying to move
      if ( ( ucmd->forwardmove || ucmd->rightmove ) && ( ( oldpos - origin ).length() < 0.01f ) )
         {
         moveresult = MOVERESULT_BLOCKED;
         }
      if ( standing && client->ps.walking && !client->ps.feetfalling )
         {
         setOrigin( oldpos );
         VectorCopy( origin, client->ps.origin );
         }
      }
   else
      {
      //FIXME
      // should collect objects to touch against
      memset( &pm, 0, sizeof( pmove_t ) );

      // keep the command time up to date or else the next PMove we run will try to catch up
      client->ps.commandTime = ucmd->serverTime;

      velocity = vec_zero;
      }

   if ( movecontrol == MOVECONTROL_WALLHUG )
      {
      trace_t trace;

   	Vector end( origin - yaw_forward * 18.0f );

   	trace = G_Trace( origin, mins, maxs, end, this, MASK_DEADSOLID, true, "ClientMove" );
      if ( !trace.allsolid && ( trace.fraction < 1.0f ) )
         {
         v_angle.y = Vector( trace.plane.normal ).toYaw();
         angles.y = v_angle.y;
         setAngles( angles );
         setOrigin( ( yaw_forward * 0.1f ) + trace.endpos );
         }
      }

   if ( ( getMoveType() == MOVETYPE_NOCLIP ) || !( client->ps.pm_flags & PMF_NO_PREDICTION ) )
      {
      total_delta = vec_zero;
      }
   else
      {
      if ( ( movecontrol == MOVECONTROL_ABSOLUTE ) || ( movecontrol == MOVECONTROL_HANGING ) ||
         ( movecontrol == MOVECONTROL_WALLHUG ) || ( movecontrol == MOVECONTROL_STEPUP ) || ( movecontrol == MOVECONTROL_CLIMBWALL ) )
         {
         velocity = vec_zero;
         }

      if ( total_delta != vec_zero )
		   {
		   MatrixTransformVector( total_delta, orientation, move );
         if ( ( movecontrol == MOVECONTROL_PUSH ) && atobject && atobject->isSubclassOf( PushObject ) )
            {
            ( ( PushObject * )( Entity * )atobject )->Push( this, move );
            // move the player right up to the object
            StartPush();
            }
         else
            {
            CheckMove( move, &origin );
            setOrigin( origin );
            CheckGround();
            }
         }
      }

	total_delta = vec_zero;

   TouchStuff( &pm );

   if ( ( whereami->integer ) && ( origin != oldorigin ) )
      {
      gi.DPrintf( "x %8.2f y%8.2f z %8.2f area %2d\n", origin[ 0 ], origin[ 1 ], origin[ 2 ], edict->areanum );
      }
	}

/*
==============
ClientThink

This will be called once for each client frame, which will
usually be a couple times for each server frame.
==============
*/
void Player::ClientThink
	(
	Event *ev
	)

	{
	// sanity check the command time to prevent speedup cheating
	if ( current_ucmd->serverTime > level.inttime )
      {
      //
      // we don't want any future commands, these could be from the previous game
      //
      return;
	   }

	if ( current_ucmd->serverTime < level.inttime - 1000 )
      {
		current_ucmd->serverTime = level.inttime - 1000;
	   }

	if ( ( current_ucmd->serverTime - client->ps.commandTime ) < 1 )
      {
      return;
      }

   last_ucmd   = *current_ucmd;
	new_buttons	= current_ucmd->buttons & ~buttons;
	buttons		= current_ucmd->buttons;

	if ( level.intermissiontime )
		{
		client->ps.pm_flags |= PMF_FROZEN;

		// can exit intermission after five seconds
		if ( level.time > level.intermissiontime )
         {
         if ( deathmatch->integer )
            {
            if ( new_buttons & BUTTON_ANY )
               {
      			level.exitintermission = true;
               }
            }
			else
            {
   			level.exitintermission = true;
            }
			}

		// Save cmd angles so that we can get delta angle movements next frame
		client->cmd_angles[ 0 ] = SHORT2ANGLE( current_ucmd->angles[ 0 ] );
		client->cmd_angles[ 1 ] = SHORT2ANGLE( current_ucmd->angles[ 1 ] );
		client->cmd_angles[ 2 ] = SHORT2ANGLE( current_ucmd->angles[ 2 ] );

		return;
		}

   moveresult = MOVERESULT_NONE;

   if ( !vehicle || !vehicle->Drive( current_ucmd ) )
      {
      ClientMove( current_ucmd );
      }

   // only evaluate the state when not noclipping
   if ( getMoveType() == MOVETYPE_NOCLIP )
      {
      // force the stand animation if were in noclip
      SetAnim( "idle", all );
      }
   else
      {
      // set flags for state machine
      CheckMoveFlags();
      EvaluateState();

		if ( groundentity && groundentity->entity && groundentity->entity->isSubclassOf( Actor ) )
			{
			Event *event = new Event( EV_Actor_Push );
			event->AddVector( Vector( 0, 0, -10 ) );
			groundentity->entity->PostEvent( event, 0 );
			}
      }

	oldvelocity = velocity;
   old_v_angle  = v_angle;

   // clear out rope_touch flag after evalutating the state
   rope_touch = NULL;

	// If we're dying, check for respawn
   if ( ( deadflag == DEAD_DEAD && ( level.time > respawn_time ) ) )
		{
		// wait for any button just going down
      if ( new_buttons || ( DM_FLAG( DF_FORCE_RESPAWN ) ) )
         {
         G_PlayerDied( 1 );
			}
		}

	// Save cmd angles so that we can get delta angle movements next frame
	client->cmd_angles[ 0 ] = SHORT2ANGLE( current_ucmd->angles[ 0 ] );
	client->cmd_angles[ 1 ] = SHORT2ANGLE( current_ucmd->angles[ 1 ] );
	client->cmd_angles[ 2 ] = SHORT2ANGLE( current_ucmd->angles[ 2 ] );

   if ( g_logstats->integer ) 
      {
      if ( !logfile_started )
         {
         ProcessEvent( EV_Player_LogStats );
         logfile_started = qtrue;
         }
      }
	}

void Player::LoadStateTable
   (
   void
   )

   {
   statemap_Legs = NULL;
   statemap_Torso = NULL;

	legs_conditionals.FreeObjectList();
	torso_conditionals.FreeObjectList();

	statemap_Legs = GetStatemap( str( g_statefile->string ) + "_Legs.st", ( Condition<Class> * )Conditions, &legs_conditionals, true );
	statemap_Torso = GetStatemap( str( g_statefile->string ) + "_Torso.st", ( Condition<Class> * )Conditions, &torso_conditionals, true );

   animdone_Legs = false;
   animdone_Torso = false;

   movecontrol = MOVECONTROL_USER;

   currentState_Legs = statemap_Legs->FindState( "STAND" );
   currentState_Torso = statemap_Torso->FindState( "STAND" );

   str legsAnim( currentState_Legs->getLegAnim( *this, &legs_conditionals ) );
   if ( legsAnim == "" )
      {
      partAnim[ legs ] = "";
      ClearLegsAnim();
      }
   else if ( legsAnim != "none" )
      {
      SetAnim( legsAnim, legs );
      }

   str torsoAnim( currentState_Torso->getTorsoAnim( *this, &torso_conditionals ) );
   if ( torsoAnim == "" )
      {
      partAnim[ torso ] = "";
      ClearTorsoAnim();
      }
   else if ( torsoAnim != "none" )
      {
      SetAnim( torsoAnim.c_str(), torso );
      }

   movecontrol = currentState_Legs->getMoveType();
   if ( ( movecontrol < ( sizeof( MoveStartFuncs ) / sizeof( MoveStartFuncs[ 0 ] ) ) ) && ( MoveStartFuncs[ movecontrol ] ) )
      {
      ( this->*MoveStartFuncs[ movecontrol ] )();
      }

   SetViewAngles( v_angle );
   }

void Player::ResetState
   (
   Event *ev
   )

   {
   if ( rope_grabbed )
      {
      rope_grabbed->Release( this );
      }

   movecontrol = MOVECONTROL_USER;
   LoadStateTable();
   }

void Player::StartHang
   (
   void
   )

   {
   Vector hand;
   trace_t trace;
   float ang;
   float ledgeheight;

   if ( ( ledgeheight_right <= MIN_Z ) || ( ledgeheight_left <= MIN_Z ) )
      {
      return;
      }

   ledgeheight = max( ledgeheight_left, ledgeheight_right );

   hand = righthand_pos - origin;
   if ( ledgeheight > origin.z )
      {
      origin.z = ledgeheight - hand.z - 1.0f;
      }

   Vector start( origin.x, origin.y, hand.z - 2.0f + origin.z );
	Vector end( start + yaw_forward * 24.0f );

   start -= yaw_forward * 8.0f;

	trace = G_Trace( start, min_box_8x8, max_box_8x8, end, this, MASK_DEADSOLID, true, "StartHang" );
   if ( trace.fraction == 1.0f )
      {
      return;
      }

   ang = vectoyaw( trace.plane.normal ) - 180;

   end = origin + yaw_forward * 8.0f;
   start = origin - yaw_forward * 1.0f;
   trace = G_Trace( start, mins, maxs, end, this, MASK_DEADSOLID, true, "StartHang" );
   if ( trace.fraction == 1.0f )
      {
      return;
      }

   v_angle.y = ang;
   SetViewAngles( v_angle );
   angles.y = ang;
   setAngles( angles );
   setOrigin( trace.endpos - yaw_forward * 0.4f );
   }

void Player::StartPickup
   (
   void
   )

   {
   Vector start;
	Vector end;
   trace_t trace;
	Actor *act;
	Vector dir;
	Vector new_angles;

   if ( WeaponsOut() )
      {
      if ( !pickup_enemy )
         {
         // put away our weapons
         SafeHolster( qtrue );
         pickup_enemy = true;
         }
      return;
      }

   pickup_enemy = false;

	start = origin + Vector( 0, 0, 32 );
	end	= start + yaw_forward * 64.0f;
	trace = G_Trace( start, vec_zero, vec_zero, end, this, MASK_PLAYERSOLID, true, "StartPickup" );

   if ( trace.ent && trace.ent->entity && ( trace.ent->entity != world ) && trace.ent->entity->isSubclassOf( Actor ) )
      {
		act = (Actor *)trace.ent->entity;

		if ( act->name == "Shgliek" )
			{
			// Make sure are turned towards Shgliek
			dir = act->centroid - centroid;
			new_angles = dir.toAngles();

			angles[YAW] = new_angles[YAW];

			setAngles( angles );
			SetViewAngles( angles );
			}
      }
   }

void Player::StartPush
   (
   void
   )

   {
   trace_t trace;
	Vector  end( origin + yaw_forward * 64.0f );

   trace = G_Trace( origin, mins, maxs, end, this, MASK_SOLID, true, "StartPush" );
   if ( trace.fraction == 1.0f )
      {
      return;
      }
   v_angle.y = vectoyaw( trace.plane.normal ) - 180;
   SetViewAngles( v_angle );

   setOrigin( trace.endpos - yaw_forward * 0.4f );
   }

void Player::StartClimbWall
   (
   void
   )

   {
   trace_t trace;
	Vector  end( origin + yaw_forward * 20.0f );

   trace = G_Trace( origin, mins, maxs, end, this, MASK_SOLID, true, "StartClimbWall" );
   if ( ( trace.fraction == 1.0f ) || !( trace.surfaceFlags & SURF_LADDER ) )
      {
      return;
      }

   v_angle.y = vectoyaw( trace.plane.normal ) - 180;
   SetViewAngles( v_angle );

   setOrigin( trace.endpos - yaw_forward * 0.4f );
   }

void Player::StartUseAnim
   (
   void
   )

   {
   UseAnim  *ua;
   Vector   neworg;
   Vector   newangles;
   str      newanim;
   str      state;
   str      camera;
   trace_t  trace;

   if ( toucheduseanim )
      {
      ua = ( UseAnim * )( Entity * )toucheduseanim;
      }
   else if ( atobject )
      {
      ua = ( UseAnim * )( Entity * )atobject;
      }
   else
      {
      return;
      }

   useitem_in_use = ua;
   toucheduseanim = NULL;
   atobject = NULL;

   if ( ua->GetInformation( this, &neworg, &newangles, &newanim, &useanim_numloops, &state, &camera ) )
      {
      trace = G_Trace( origin, mins, maxs, neworg, this, MASK_PLAYERSOLID, true, "StartUseAnim" );
      if ( trace.startsolid || ( trace.fraction < 1.0f ) )
         {
         gi.DPrintf( "Move to UseAnim was blocked.\n" );
         }

      if ( !trace.startsolid )
         {
         setOrigin( trace.endpos );
         }

      setAngles( newangles );
      v_angle.y = newangles.y;
      SetViewAngles( v_angle );

      movecontrol = MOVECONTROL_ABSOLUTE;

      if ( state.length() )
         {
         State * newState;

         newState = statemap_Torso->FindState( state );
         if ( newState )
            {
            EvaluateState( newState );
            }
         else
            {
            gi.DPrintf( "Could not find state %s on UseAnim\n", state.c_str() );
            }
         }
      else
         {
         if ( currentState_Torso )
            {
            if ( camera.length() )
               {
               currentState_Torso->setCameraType( camera );
               }
            else
               {
               currentState_Torso->setCameraType( "behind" );
               }
            }
         SetAnim( newanim, legs );
         }
      }
   }

void Player::StartLoopUseAnim
   (
   void
   )

   {
   useanim_numloops--;
   }

void Player::FinishUseAnim
   (
   Event *ev
   )

   {
   UseAnim  *ua;

   if ( !useitem_in_use )
      return;

   ua = ( UseAnim * )( Entity * )useitem_in_use;
   ua->TriggerTargets( this );
   useitem_in_use = NULL;
   }

void Player::SetupUseObject
   (
   void
   )

   {
   UseObject  *uo;
   Vector   neworg;
   Vector   newangles;
   str      state;
   trace_t  trace;

   if ( atobject )
      {
      uo = ( UseObject * )( Entity * )atobject;
      }
   else
      {
      return;
      }

   useitem_in_use = uo;

   uo->Setup( this, &neworg, &newangles, &state );
      {
      trace = G_Trace( neworg, mins, maxs, neworg, this, MASK_PLAYERSOLID, true, "SetupUseObject - 1" );
      if ( trace.startsolid || trace.allsolid )
         {
         trace = G_Trace( origin, mins, maxs, neworg, this, MASK_PLAYERSOLID, true, "SetupUseObject - 2" );
         if ( trace.startsolid || ( trace.fraction < 1.0f ) )
            {
            gi.DPrintf( "Move to UseObject was blocked.\n" );
            }
         }

      if ( !trace.startsolid )
         {
         setOrigin( trace.endpos );
         }

      setAngles( newangles );
      v_angle.y = newangles.y;
      SetViewAngles( v_angle );

      movecontrol = MOVECONTROL_ABSOLUTE;

      if ( state.length() )
         {
         State * newState;

         newState = statemap_Torso->FindState( state );
         if ( newState )
            {
            EvaluateState( newState );
            }
         else
            {
            gi.DPrintf( "Could not find state %s on UseObject\n", state.c_str() );
            }
         }
      }
   }

void Player::StartUseObject
   (
   Event *ev
   )

   {
   UseObject  *uo;

   if ( !useitem_in_use )
      return;

   uo = ( UseObject * )( Entity * )useitem_in_use;
   uo->Start();
   }

void Player::FinishUseObject
   (
   Event *ev
   )

   {
   UseObject  *uo;

   if ( !useitem_in_use )
      return;

   uo = ( UseObject * )( Entity * )useitem_in_use;
   uo->Stop( this );
   useitem_in_use = NULL;
   }

void Player::PickupShgliek
   (
   Event *ev
   )

   {
   Vector start;
	Vector end;
   trace_t trace;
	Actor *act;
	int tag_num;

	start = origin + Vector( 0, 0, 32 );
	end	= start + yaw_forward * 64.0f;
	trace = G_Trace( start, mins, maxs, end, this, MASK_PLAYERSOLID, true, "PickupShgliek" );

   if ( trace.ent && trace.ent->entity && ( trace.ent->entity != world ) && trace.ent->entity->isSubclassOf( Actor ) )
      {
		act = (Actor *)trace.ent->entity;

		if ( act->name == "Shgliek" )
			{
			// Pickup the Shgliek

			tag_num = gi.Tag_NumForName( edict->s.modelindex, "TAG_WEAPON_RIGHT" );
			act->setAngles( Vector( 0, 0, 0 ) );
			act->attach( entnum, tag_num );
			act->SetAnim( "neckhold" );
			act->StartMode( ACTOR_MODE_AI );
			have_shgliek = true;
			}
      }
   }

void Player::ThrowShgliek
   (
   Event *ev
   )

   {
	int i;
	int num;
	Entity *child;
	Actor *act;
	int tag_num;
	Vector pos;
	Vector forward;
	Vector shgliek_angles;
	Vector torso_angles;
	trace_t trace;


	have_shgliek = false;

	for ( i=0,num = numchildren; i < MAX_MODEL_CHILDREN; i++ )
      {
      if ( children[i] == ENTITYNUM_NONE )
         {
         continue;
         }

		child = ( Entity * )G_GetEntity( children[i] );

		if ( child->isSubclassOf( Actor ) )
			{
			act = (Actor *)child;

			if ( ( act->name == "Shgliek" ) || ( act->name == "Partially Evil Shgliek" ) || ( act->name == "Evil Shgliek" ) )
				{
				// Make sure it is not in a solid right now

				trace = G_Trace( act->origin, act->mins, act->maxs, act->origin, this, MASK_MONSTERSOLID, false, "throwshgliek" );

				if ( !trace.startsolid && !trace.allsolid )
					{
					act->detach();

					// Make it so the shgliek will not get stuck on the player when thrown

					act->setSolidType( SOLID_BBOX );

					// Make the Shgliek face the same way as the player

					torso_angles = GetTorsoAngles();

					torso_angles[PITCH] = 0;
					torso_angles[ROLL]  = 0;

					act->setAngles( torso_angles );

					// Throw the shgliek a little ways

					act->groundentity = NULL;

					tag_num = gi.Tag_NumForName( edict->s.modelindex, "TAG_WEAPON_RIGHT" );
					GetTag( tag_num, &pos, &forward );

					shgliek_angles = forward.toAngles();

					shgliek_angles[YAW] = torso_angles[YAW];

					shgliek_angles.AngleVectors( &forward );

					act->velocity = forward * 500;
					}
				else
					{
					have_shgliek = true;
					}
				}
			}

      num--;

      if ( !num )
         break;
		}
   }

void Player::StartPipeCrawl
   (
   void
   )

   {
   trace_t trace;
   float ang;
   float dist;
   Vector pos;
   float horizang;

   if ( !horizontalpipe )
      {
      return;
      }

   //
   // make sure the correct pm_flags get set for the CheckGround call
   //
   if ( movecontrol == MOVECONTROL_PIPECRAWL )
      {
      client->ps.pm_flags |= PMF_NO_PREDICTION | PMF_LEGS_LIFTED;
      }

   //
   // this ensures that our boudning boxes are correct
   //
   CheckGround();

   Vector end( origin.x, origin.y, righthand_pos.z + 1 - maxs.z );

	trace = G_Trace( origin, mins, maxs, end, this, MASK_DEADSOLID, true, "StartPipeCrawl" );
   setOrigin( trace.endpos );

   horizang = ( ( HorizontalPipe * )( Entity * )horizontalpipe )->dir;
   ang = AngleSubtract( v_angle.y, horizang );
   if ( Q_fabs( ang ) > 90.0f )
      {
      v_angle.y = horizang + 180.0f;
      }
   else
      {
      v_angle.y = horizang;
      }

   SetViewAngles( v_angle );

   pos = origin - horizontalpipe->centroid;
   dist = pos * yaw_left;

   setOrigin( origin - yaw_left * dist );
   }

void Player::StartMonkeyBars
   (
   void
   )

   {
   trace_t trace;
   Vector oldang( v_angle );

   if ( monkeybar_right <= MIN_Z )
      {
      return;
      }

   Vector end( origin.x, origin.y, monkeybar_right - ( righthand_pos.z - origin.z ) );

	trace = G_Trace( origin, mins, maxs, end, this, MASK_DEADSOLID, true, "StartMonkeyBars" );
   setOrigin( trace.endpos );

   //v_angle[ YAW ] = monkeybar_dir;
   v_angle[ YAW ] = ( int )( anglemod( v_angle[ YAW ] + 45.0f ) / 90.0f ) * 90.0f;
   SetViewAngles( v_angle );

   if ( !CheckMove( vec_zero ) )
      {
      SetViewAngles( oldang );
      }
   }

void Player::StartStepUp
   (
   void
   )

   {
   Vector   delta;
   Vector   end( origin + yaw_forward * 24.0f );
   trace_t  trace;

   gi.Anim_Delta( edict->s.modelindex, edict->s.anim & ANIM_MASK, delta );
   animheight = delta.z + origin.z;

	trace = G_Trace( origin, mins, maxs, end, this, MASK_DEADSOLID, true, "StartStepUp" );

   v_angle.y = vectoyaw( trace.plane.normal ) - 180;
   SetViewAngles( v_angle );
   setOrigin( trace.endpos );
   }

void Player::StepUp
   (
   Event *ev
   )

   {
   float    ledgeheight;
   trace_t  trace;

   ledgeheight = max( ledgeheight_left, ledgeheight_right );
   if ( ledgeheight > animheight )
      {
      Vector end( origin );

      end.z += ledgeheight - animheight;
      trace = G_Trace( origin, mins, maxs, end, this, MASK_DEADSOLID, true, "StartStepUp" );
      setOrigin( trace.endpos );
      }
   }

void Player::Turn
   (
   Event *ev
   )

   {
   float yaw;
   Vector oldang( v_angle );

   yaw = ev->GetFloat( 1 );

   v_angle[ YAW ] = ( int )( anglemod( v_angle[ YAW ] ) / 22.5f ) * 22.5f;
   SetViewAngles( v_angle );

   if ( !CheckMove( vec_zero ) )
      {
      SetViewAngles( oldang );
      return;
      }

   CancelEventsOfType( EV_Player_TurnUpdate );

   ev = new Event( EV_Player_TurnUpdate );
   ev->AddFloat( yaw / 5.0f );
   ev->AddFloat( 0.5f );
   ProcessEvent( ev );
   }

void Player::TurnUpdate
   (
   Event *ev
   )

   {
   float yaw;
   float timeleft;
   Vector oldang( v_angle );

   yaw = ev->GetFloat( 1 );
   timeleft = ev->GetFloat( 2 );
   timeleft -= 0.1f;

   if ( timeleft > 0 )
      {
      ev = new Event( EV_Player_TurnUpdate );
      ev->AddFloat( yaw );
      ev->AddFloat( timeleft );
      PostEvent( ev, 0.1f );

   	v_angle[ YAW ] += yaw;
   	SetViewAngles( v_angle );
      }
   else
      {
      v_angle[ YAW ] = ( int )( anglemod( v_angle[ YAW ] ) / 22.5f ) * 22.5f;
      SetViewAngles( v_angle );
      }

   if ( !CheckMove( vec_zero ) )
      {
      SetViewAngles( oldang );
      }
   }

void Player::TurnLegs
   (
   Event *ev
   )

   {
   float yaw;

   yaw = ev->GetFloat( 1 );

   angles[ YAW ] += yaw;
   setAngles( angles );
   }

void Player::RopeRelease
   (
   void
   )

   {
   if ( rope_grabbed )
      {
      rope_grabbed->Release( this );
      }

   movecontrol = MOVECONTROL_USER;
   }

void Player::RopeGrab
   (
   void
   )

   {
   if ( rope_touch && !rope_grabbed )
      {
      // pass in origin offset
      rope_touch->Grab( this, 28 + maxs.z - mins.z );
      }

   rope_touch = NULL;
   movecontrol = MOVECONTROL_USER;
   }


void Player::EvaluateState
   (
   State *forceTorso,
   State *forceLegs
   )

   {
   int count;
   State *laststate_Legs;
   State *laststate_Torso;
   State *startstate_Legs;
   State *startstate_Torso;
   movecontrol_t move;

   if ( getMoveType() == MOVETYPE_NOCLIP )
      {
      return;
      }

   // Evaluate the current state.
   // When the state changes, we reevaluate the state so that if the
   // conditions aren't met in the new state, we don't play one frame of
   // the animation for that state before going to the next state.
   startstate_Torso = laststate_Torso = currentState_Torso;
   count = 0;
   do
      {
      // since we could get into an infinite loop here, do a check
      // to make sure we don't.
      count++;
      if ( count > 10 )
         {
         gi.DPrintf( "Possible infinite loop in state '%s'\n", currentState_Torso->getName() );
         assert( 0 );
         if ( count > 20 )
            {
            gi.Error( ERR_DROP, "Stopping due to possible infinite state loop\n" );
            break;
            }
         }

      laststate_Torso = currentState_Torso;

      if ( forceTorso )
         currentState_Torso = forceTorso;
      else
         currentState_Torso = currentState_Torso->Evaluate( *this, &torso_conditionals );

      animdone_Torso = false;
      if ( movecontrol != MOVECONTROL_LEGS )
         {
         animdone_Legs = false;
         }
      if ( laststate_Torso != currentState_Torso )
         {
         // Process exit commands of the last state
         laststate_Torso->ProcessExitCommands( this );

         // Process entry commands of the new state
         currentState_Torso->ProcessEntryCommands( this );

         if ( waitForState.length() && ( !waitForState.icmpn( currentState_Torso->getName(), waitForState.length() ) ) )
            {
            waitForState = "";
            PlayerDone( NULL );
            }

         move = currentState_Torso->getMoveType();

         str legsAnim( currentState_Torso->getLegAnim( *this, &torso_conditionals ) );
         str torsoAnim( currentState_Torso->getTorsoAnim( *this, &torso_conditionals ) );

         if ( legsAnim != "" )
            {
            animdone_Legs = false;
            SetAnim( legsAnim, legs );
            }
         else if ( move == MOVECONTROL_LEGS )
            {
            if ( !currentState_Legs )
               {
               animdone_Legs = false;
               currentState_Legs = statemap_Legs->FindState( "STAND" );

               legsAnim = currentState_Legs->getLegAnim( *this, &legs_conditionals );
               if ( legsAnim == "" )
                  {
                  partAnim[ legs ] = "";
                  ClearLegsAnim();
                  }
               else if ( legsAnim != "none" )
                  {
                  SetAnim( legsAnim, legs );
                  }
               }
            }
         else
            {
            partAnim[ legs ] = "";
            ClearLegsAnim();
            }

         if ( torsoAnim == "" )
            {
            partAnim[ torso ] = "";
            ClearTorsoAnim();
            }
         else if ( torsoAnim != "none" )
            {
            SetAnim( torsoAnim.c_str(), torso );
            }

         if ( movecontrol != move )
            {
            movecontrol = move;
            if ( ( move < ( sizeof( MoveStartFuncs ) / sizeof( MoveStartFuncs[ 0 ] ) ) ) && ( MoveStartFuncs[ move ] ) )
               {
               ( this->*MoveStartFuncs[ move ] )();
               }
            }

         SetViewAngles( v_angle );
         }
      }
   while( laststate_Torso != currentState_Torso );

   // Evaluate the current state.
   // When the state changes, we reevaluate the state so that if the
   // conditions aren't met in the new state, we don't play one frame of
   // the animation for that state before going to the next state.
   startstate_Legs = laststate_Legs = currentState_Legs;
   if ( movecontrol == MOVECONTROL_LEGS )
      {
      count = 0;
      do
         {
         // since we could get into an infinite loop here, do a check
         // to make sure we don't.
         count++;
         if ( count > 10 )
            {
            gi.DPrintf( "Possible infinite loop in state '%s'\n", currentState_Legs->getName() );
            assert( 0 );
            if ( count > 20 )
               {
               gi.Error( ERR_DROP, "Stopping due to possible infinite state loop\n" );
               break;
               }
            }

         if ( !currentState_Legs )
            {
            currentState_Legs = statemap_Legs->FindState( "STAND" );
            }

         laststate_Legs = currentState_Legs;

         if ( forceLegs )
            currentState_Legs = forceLegs;
         else
            currentState_Legs = currentState_Legs->Evaluate( *this, &legs_conditionals );

         animdone_Legs = false;
         if ( laststate_Legs != currentState_Legs )
            {
            // Process exit commands of the last state
            laststate_Legs->ProcessExitCommands( this );

            // Process entry commands of the new state
            currentState_Legs->ProcessEntryCommands( this );

            if ( waitForState.length() && ( !waitForState.icmpn( currentState_Legs->getName(), waitForState.length() ) ) )
               {
               waitForState = "";
               PlayerDone( NULL );
               }

            str legsAnim( currentState_Legs->getLegAnim( *this, &legs_conditionals ) );
            if ( legsAnim == "" )
               {
               partAnim[ legs ] = "";
               ClearLegsAnim();
               }
            else if ( legsAnim != "none" )
               {
               SetAnim( legsAnim, legs );
               }
            }
         }
      while( laststate_Legs != currentState_Legs );
      }
   else
      {
      currentState_Legs = NULL;
      }

   if ( g_showplayeranim->integer )
      {
      if ( last_leg_anim_name != AnimName( legs ) )
         {
         gi.DPrintf( "Legs change from %s to %s\n", last_leg_anim_name.c_str(), AnimName( legs ) );
         last_leg_anim_name = AnimName( legs );
         }

      if ( last_torso_anim_name != AnimName( torso ) )
         {
         gi.DPrintf( "Torso change from %s to %s\n", last_torso_anim_name.c_str(), AnimName( torso ) );
         last_torso_anim_name = AnimName( torso );
         }
      }

   if ( g_showplayerstate->integer )
      {
      if ( startstate_Legs != currentState_Legs )
         {
         gi.DPrintf( "Legs change from %s to %s\n",
            startstate_Legs ? startstate_Legs->getName() : "NULL",
            currentState_Legs ? currentState_Legs->getName() : "NULL" );
         }

      if ( startstate_Torso != currentState_Torso )
         {
         gi.DPrintf( "Torso change from %s to %s\n",
            startstate_Torso ? startstate_Torso->getName() : "NULL",
            currentState_Torso ? currentState_Torso->getName() : "NULL" );
         }
      }

   // This is so we don't remember pain when we change to a state that has a PAIN condition
   pain = 0;
   // Every second drop accumulated pain by 1
   if ( ( float )( int )( level.time ) == level.time )
      {
      accumulated_pain -= 1;
      if ( accumulated_pain < 0 )
         accumulated_pain = 0;
      }
   }

void Player::EventUseItem
	(
	Event *ev
	)

	{
	const char  *name;
   weaponhand_t hand = WEAPON_RIGHT;

	if ( deadflag )
      {
		return;
      }

	name = ev->GetString( 1 );

   Item *item = ( Item * )FindItem( name );

   if ( item && item->isSubclassOf( InventoryItem ) )
      {
      InventoryItem *ii = ( InventoryItem * )item;
      Event *ev1;

      ev1 = new Event( EV_InventoryItem_Use );
      ev1->AddEntity( this );
      ii->ProcessEvent( ev1 );
      }
   else if ( ev->NumArgs() > 1 )
      {
      hand = WeaponHandNameToNum( ev->GetString( 2 ) );
      useWeapon( name, hand );
      }
   }

void Player::GiveWeaponCheat
   (
   Event *ev
   )

   {
   giveItem( ev->GetString( 1 ) );
   }

void Player::GiveCheat
	(
	Event *ev
	)

	{
	str name;

	if ( deadflag )
		{
		return;
		}

	name = ev->GetString( 1 );

   if ( !name.icmp( "all" ) )
      {
      GiveAllCheat( ev );
      return;
      }
   EventGiveItem( ev );
	}

void Player::GiveAllCheat
	(
	Event *ev
	)

	{
   char  *buffer;
	char  *buf;
   char	com_token[MAX_STRING_CHARS];

	if ( deadflag )
		{
		return;
		}

   if ( gi.FS_ReadFile( "global/giveall.scr", ( void ** )&buf, qtrue ) != -1 )
      {
		buffer = buf;
      while ( 1 )
         {
         strcpy( com_token, COM_ParseExt( &buffer, qtrue ) );

         if (!com_token[0])
            break;

         // Create the event
         ev = new Event( com_token );

         // get the rest of the line
         while( 1 )
            {
            strcpy( com_token, COM_ParseExt( &buffer, qfalse ) );
            if (!com_token[0])
               break;

            ev->AddToken( com_token );
            }

         this->ProcessEvent( ev );
         }
      gi.FS_FreeFile( buf );
      }
   }

void Player::GodCheat
	(
	Event *ev
	)

	{
	const char *msg;

   if ( ev->NumArgs() > 0 )
      {
      if ( ev->GetInteger( 1 ) )
         {
         flags |= FL_GODMODE;
         }
      else
         {
         flags &= ~FL_GODMODE;
         }
      }
   else
      {
   	flags ^= FL_GODMODE;
      }

   if ( ev->GetSource() == EV_FROM_CONSOLE )
      {
	   if ( !( flags & FL_GODMODE ) )
		   {
		   msg = "godmode OFF\n";
		   }
	   else
		   {
		   msg = "godmode ON\n";
		   }

      gi.SendServerCommand( edict-g_entities, "print \"%s\"", msg );
      }
	}

void Player::Kill
	(
	Event *ev
	)

	{
	if ( ( level.time - respawn_time ) < 5 )
		{
		return;
		}

	flags &= ~FL_GODMODE;
	health = 1;
   Damage( this, this, 10, origin, vec_zero, vec_zero, 0, DAMAGE_NO_PROTECTION, MOD_SUICIDE );
	}

void Player::NoTargetCheat
	(
	Event *ev
	)

	{
	const char *msg;

	flags ^= FL_NOTARGET;
	if ( !( flags & FL_NOTARGET ) )
		{
		msg = "notarget OFF\n";
		}
	else
		{
		msg = "notarget ON\n";
		}

   gi.SendServerCommand( edict-g_entities, "print \"%s\"", msg );
	}

void Player::NoclipCheat
	(
	Event *ev
	)

	{
	const char *msg;

   if ( vehicle )
		{
		msg = "Must exit vehicle first\n";
		}
   else if ( getMoveType() == MOVETYPE_NOCLIP )
		{
		setMoveType( MOVETYPE_WALK );
		msg = "noclip OFF\n";

      // reset the state machine so that her animations are correct
      ResetState( NULL );
		}
	else
		{
      if ( rope_grabbed )
         {
         rope_grabbed->Release( this );
         }

      client->ps.feetfalling = false;
      movecontrol = MOVECONTROL_USER;

		setMoveType( MOVETYPE_NOCLIP );
		msg = "noclip ON\n";
		}

   gi.SendServerCommand( edict-g_entities, "print \"%s\"", msg );
	}

void Player::GameVersion
	(
	Event *ev
	)

	{
   gi.SendServerCommand( edict-g_entities, "print \"%s : %s\n\"", GAMEVERSION, __DATE__ );
	}

void Player::SetFov
	(
   float newFov
	)

	{
	fov = newFov;

   if ( ( fov < 90 ) && DM_FLAG( DF_FIXED_FOV ) )
      {
      fov = 90;
      return;
      }

   if ( fov < 1 )
      {
      fov = 90;
      }
   else if ( fov > 160 )
      {
      fov = 160;
      }
	}

void Player::Fov
	(
	Event *ev
	)

	{
   if ( ev->NumArgs() < 1 )
		{
      gi.SendServerCommand( edict-g_entities, "print \"Fov = %d\n\"", fov );
		return;
		}

   SetFov( ev->GetFloat( 1 ) );
	}

/*
===============
CalcRoll

===============
*/
float Player::CalcRoll
	(
	void
	)

	{
	float	sign;
	float	side;
	float	value;
	Vector l;

	angles.AngleVectors( NULL, &l, NULL );
	side = velocity * l;
	sign = side < 0 ? 4 : -4;
	side = fabs( side );

	value = sv_rollangle->value;

	if ( side < sv_rollspeed->value )
		{
		side = side * value / sv_rollspeed->value;
		}
	else
		{
		side = value;
		}

	return side * sign;
	}

void Player::GravityNodes
   (
   void
   )

   {
   Vector grav;
   Vector gravnorm;
   Vector velnorm;
   float  dot;
   qboolean force;
	float max_speed;
	Vector new_velocity;

   //
   // Check for gravity pulling points
   //

   // no pull during waterjumps
   if ( client->ps.pm_flags & PMF_TIME_WATERJUMP )
      {
      return;
      }

   grav = gravPathManager.CalculateGravityPull( *this, origin, &force, &max_speed );

   // Check for unfightable gravity.
   if ( force && grav != vec_zero )
      {
      velnorm = velocity;
      velnorm.normalize();

      gravnorm = grav;
      gravnorm.normalize();

      dot = gravnorm.x * velnorm.x + gravnorm.y * velnorm.y + gravnorm.z * velnorm.z;

      // This prevents the player from trying to swim upstream
      if ( dot < 0 )
         {
         float tempdot;
         Vector tempvec;

         tempdot = 0.2f - dot;
         tempvec = velocity * tempdot;
         velocity = velocity - tempvec;
         }
      }

	if ( grav != vec_zero )
		{
		new_velocity = velocity + grav;
		 
		if ( new_velocity.length() < velocity.length() )
			{
			// Is slowing down, defintely need to apply grav
			velocity = new_velocity;
			}
		else if ( velocity.length() < max_speed )
			{
			// Applay grav

			velocity = new_velocity;

			// Make sure we aren't making the player go too fast

			if ( velocity.length() > max_speed )
				{
 				velocity.normalize();
				velocity *= max_speed;
				}
			}
		else
			{
			// Going too fast but still want to pull the player up if any z velocity in grav

			grav.x = 0;
			grav.y = 0;

			velocity = velocity + grav;
			}
		}
   }

//
// PMove Events
//
void Player::ProcessPmoveEvents
	(
   int event
	)

	{
   float damage;

   switch( event )
      {
      case EV_NONE:
         break;
      case EV_FALL_SHORT:
         break;
      case EV_FALL_MEDIUM:
      case EV_FALL_FAR:
      case EV_FALL_FATAL:
			if ( event == EV_FALL_FATAL ) 
            {
				damage = 1000;
			   } 
			else if ( event == EV_FALL_FAR ) 
            {
				damage = 20;
			   } 
         else 
            {
				damage = 5;
            }
		   if ( !DM_FLAG( DF_NO_FALLING ) )
			   {
            Damage( world, world, ( int )damage, origin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_FALLING );
			   }
         break;
      case EV_TERMINAL_VELOCITY:
   	   Sound( "snd_fall", CHAN_VOICE );
         break;

      case EV_WATER_TOUCH:   // foot touches
		   if ( watertype & CONTENTS_LAVA )
			   {
			   Sound( "snd_burn", CHAN_LOCAL );
   			}
         else
            {
				Animate *water;
				trace_t trace;
				Vector start;
				float scale;

	   		Sound( "impact_playersplash", CHAN_AUTO );

				// Find the correct place to put the splash

				start = origin + Vector(0, 0, 90);
				trace = G_Trace( start, vec_zero, vec_zero, origin, NULL, MASK_WATER, false, "ProcessPmoveEvents" );

				// Figure out a good scale for the splash

				scale = 1 + ( velocity[2] + 400 ) / -1500;

				if ( scale < 1 )
					scale = 1;
				else if ( scale > 1.5 )
					scale = 1.5;

				// Spawn in a water splash

				water = new Animate;

				water->setOrigin( trace.endpos );
				water->setModel( "fx_splashsmall.tik" );
				water->setScale( scale );
				water->RandomAnimate( "idle" );
				water->PostEvent( EV_Remove, 5 );

            }
         break;
      case EV_WATER_LEAVE:   // foot leaves
		   Sound( "impact_playerleavewater", CHAN_AUTO );
         break;
      case EV_WATER_UNDER:   // head touches
		   Sound( "impact_playersubmerge", CHAN_AUTO );
         break;
      case EV_WATER_CLEAR:   // head leaves
			Sound( "snd_gasp", CHAN_LOCAL );
         break;
      }
   }

/*
=============
WorldEffects
=============
*/
void Player::WorldEffects
	(
	void
	)

	{
   if ( deadflag == DEAD_DEAD )
      {
      // if we are dead, no world effects
      return;
      }

	if ( movetype == MOVETYPE_NOCLIP )
		{
		// don't need air
		air_finished = level.time + 20;
		return;
		}

   //
   // Check for earthquakes
   //
   if ( groundentity && ( level.earthquake > level.time ) )
      {
//      velocity[ 0 ] += G_CRandom( EARTHQUAKE_STRENGTH * level.earthquake_magnitude );
//      velocity[ 1 ] += G_CRandom( EARTHQUAKE_STRENGTH * level.earthquake_magnitude );
//      velocity[ 2 ] += G_Random( EARTHQUAKE_STRENGTH * 1.5f * level.earthquake_magnitude  );
      }
   //
   // check for on fire
   //
   if ( on_fire )
      {
      if ( next_painsound_time < level.time )
         {
         next_painsound_time = level.time + 4;
			Sound( "snd_onfire", CHAN_LOCAL );
         }
      }

   //
   // check for lava
   //
   if ( watertype & CONTENTS_LAVA )
      {
      if ( next_drown_time < level.time )
         {
         next_drown_time = level.time + 0.2f;
         Damage( world, world, 10 * waterlevel, origin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_LAVA );
         }
      if ( next_painsound_time < level.time )
         {
         next_painsound_time = level.time + 3;
			Sound( "snd_burned", CHAN_LOCAL );
         }
      }

   //
   // check for slime
   //
   if ( watertype & CONTENTS_SLIME )
      {
      if ( next_drown_time < level.time )
         {
         next_drown_time = level.time + 0.4f;
         Damage( world, world, 7 * waterlevel, origin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_SLIME );
         }
      if ( next_painsound_time < level.time )
         {
         next_painsound_time = level.time + 5;
			Sound( "snd_burned", CHAN_LOCAL );
         }
      }

	//
	// check for drowning
	//
	if ( waterlevel == 3 )
		{
		// if out of air, start drowning
		if ( ( air_finished < level.time ) && !( flags & FL_GODMODE ) )
			{
			// drown!
			if ( next_drown_time < level.time && health > 0 )
				{
				next_drown_time = level.time + 1;

				// take more damage the longer underwater
				drown_damage += 2;
				if ( drown_damage  > 15 )
					{
					drown_damage = 15;
					}

				// play a gurp sound instead of a normal pain sound
				if ( health <= drown_damage )
					{
					Sound( "snd_drown", CHAN_LOCAL );
					BroadcastSound();
					}
				else if ( rand() & 1 )
					{
					Sound( "snd_choke", CHAN_LOCAL );
					BroadcastSound();
					}
				else
					{
					Sound( "snd_choke", CHAN_LOCAL );
					BroadcastSound();
					}

            Damage( world, world, drown_damage, origin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_DROWN );
				}
			}
		}
	else
		{
		air_finished = level.time + 20;
		drown_damage = 2;
		}

   // If on a rope, increase gravity on the player
//   if ( rope_grabbed )
//      {
//      velocity.z += -1250 * level.frametime;
//      }

   GravityNodes();

	old_waterlevel = waterlevel;
	}

/*
=============
AddBlend
=============
*/
void Player::AddBlend
	(
	float r,
	float g,
	float b,
	float a
	)

	{
	float	a2;
	float a3;

	if ( a <= 0 )
		{
		return;
		}

	// new total alpha
	a2 = blend[ 3 ] + ( 1 - blend[ 3 ] ) * a;

	// fraction of color from old
	a3 = blend[ 3 ] / a2;

	blend[ 0 ] = blend[ 0 ] * a3 + r * ( 1 - a3 );
	blend[ 1 ] = blend[ 1 ] * a3 + g * ( 1 - a3 );
	blend[ 2 ] = blend[ 2 ] * a3 + b * ( 1 - a3 );
	blend[ 3 ] = a2;
	}

/*
=============
CalcBlend
=============
*/
void Player::CalcBlend
	(
	void
	)

	{
	int		contents;
	Vector	vieworg;

   client->ps.stats[STAT_ADDFADE] =0;
	blend[ 0 ] = blend[ 1 ] = blend[ 2 ] = blend[ 3 ] = 0;

	// add for contents
   vieworg = origin;
   vieworg[ 2 ] += viewheight;

	contents = gi.pointcontents( vieworg, 0 );

	if ( contents & CONTENTS_SOLID )
		{
		// Outside of world
		//AddBlend( 0.8, 0.5, 0.0, 0.2 );
		}
	else if ( contents & CONTENTS_LAVA )
		{
		AddBlend( level.lava_color[0], level.lava_color[1], level.lava_color[2], level.lava_alpha );
		}
	else if ( contents & CONTENTS_WATER )
		{
      AddBlend( level.water_color[0], level.water_color[1], level.water_color[2], level.water_alpha );
		}

	// add for damage
	if ( damage_alpha > 0 )
		{
      AddBlend( damage_blend[ 0 ], damage_blend[ 1 ], damage_blend[ 2 ], damage_alpha );

      // drop the damage value
   	damage_alpha -= 0.06;
	   if ( damage_alpha < 0 )
		   {
		   damage_alpha = 0;
		   }
      client->ps.blend[0] = blend[0];
      client->ps.blend[1] = blend[1];
      client->ps.blend[2] = blend[2];
      client->ps.blend[3] = blend[3];
		}

   // Do the cinematic fading
   float alpha=1;

   level.m_fade_time -= level.frametime;
   
   // Return if we are completely faded in
   if ( ( level.m_fade_time <= 0 ) && ( level.m_fade_type == fadein ) )
      {
      client->ps.blend[3] = 0 + damage_alpha;
      return;
      }

   // If we are faded out, and another fade out is coming in, then don't bother
   if ( ( level.m_fade_time_start > 0 ) && ( level.m_fade_type == fadeout ) )
      {
      if ( client->ps.blend[3] >= 1 )
         return;
      }

   if ( level.m_fade_time_start > 0 )
      alpha = level.m_fade_time / level.m_fade_time_start;

   if ( level.m_fade_type == fadeout ) 
      alpha = 1.0f - alpha;

   if ( alpha < 0 )
      alpha = 0;

   if ( alpha > 1 )
      alpha = 1;

   if ( level.m_fade_style == additive )
      {
      client->ps.blend[0] = level.m_fade_color[0] * level.m_fade_alpha * alpha;
      client->ps.blend[1] = level.m_fade_color[1] * level.m_fade_alpha * alpha;
      client->ps.blend[2] = level.m_fade_color[2] * level.m_fade_alpha * alpha;
      client->ps.blend[3] = level.m_fade_alpha * alpha;
      client->ps.stats[STAT_ADDFADE] = 1;
      }
   else
      {
      client->ps.blend[0] = level.m_fade_color[0];
      client->ps.blend[1] = level.m_fade_color[1];
      client->ps.blend[2] = level.m_fade_color[2];
      client->ps.blend[3] = level.m_fade_alpha * alpha;
      client->ps.stats[STAT_ADDFADE] = 0;
      }
	}

/*
===============
P_DamageFeedback

Handles color blends and view kicks
===============
*/

void Player::DamageFeedback
	(
	void
	)

	{
	float realcount;
	float count;

   // if we are dead, don't setup any feedback
   if ( health <= 0 )
      {
      damage_count = 0;
      damage_blood = 0;
      damage_alpha = 0;
      VectorClear( damage_angles );
      return;
      }

#define DAMAGE_MAX_PITCH_SCALE 0.3f
#define DAMAGE_MAX_YAW_SCALE 0.3f

   if ( damage_blood > damage_count )
      {
      float  pitch_delta;
      float  yaw_delta;

      damage_angles = damage_from.toAngles();
      pitch_delta = AngleDelta( angles.x, damage_angles.x ) / 90.0f;
      yaw_delta = AngleDelta( angles.y, damage_angles.y ) / 90.0f;

      if ( pitch_delta > DAMAGE_MAX_PITCH_SCALE )
         pitch_delta = DAMAGE_MAX_PITCH_SCALE;
      else if ( pitch_delta < -DAMAGE_MAX_PITCH_SCALE )
         pitch_delta = -DAMAGE_MAX_PITCH_SCALE;

      if ( yaw_delta > DAMAGE_MAX_YAW_SCALE )
         yaw_delta = DAMAGE_MAX_YAW_SCALE;
      else if ( yaw_delta < -DAMAGE_MAX_YAW_SCALE )
         yaw_delta = -DAMAGE_MAX_YAW_SCALE;

      damage_angles[ PITCH ] = pitch_delta;
      damage_angles[ ROLL ] = yaw_delta;
      damage_count = damage_blood * 2.0f;
      }

   if ( damage_count )
      {
      // decay damage_count over time
      damage_count *= 0.90f;
      if ( damage_count < 0.1f )
         damage_count = 0;
      
      }

	// total points of damage shot at the player this frame
	if ( !damage_blood )
		{
		// didn't take any damage
		return;
		}

	count = damage_blood;
	realcount = count;
	if ( count < 10 )
		{
		// always make a visible effect
		count = 10;
		}

	// the total alpha of the blend is always proportional to count
	if ( damage_alpha < 0 )
		{
		damage_alpha = 0;
		}

	damage_alpha += count * 0.001;
	if ( damage_alpha < 0.2 )
		{
		damage_alpha = 0.2;
		}
	if ( damage_alpha > 0.6 )
		{
		// don't go too saturated
		damage_alpha = 0.6;
		}

	// the color of the blend will vary based on how much was absorbed
	// by different armors
	damage_blend = vec_zero;
	if ( damage_blood )
		{
		damage_blend += ( damage_blood / realcount ) * bcolor;
		}

	//
	// clear totals
	//
	damage_blood = 0;
	}

void Player::GetPlayerView
   (
   Vector *pos,
   Vector *angle
   )

   {
   if ( pos )
      {
      *pos = origin;
      pos->z += viewheight;
      }

   if ( angle )
      {
      *angle = Vector( client->ps.viewangles );
      }
   }

void Player::SetPlayerView
	(
   Camera *camera,
	Vector position,
	float cameraoffset,
	Vector ang,
	Vector vel,
	float camerablend[ 4 ],
	float camerafov
	)

	{
	client->ps.viewangles[ 0 ] = ang[ 0 ];
	client->ps.viewangles[ 1 ] = ang[ 1 ];
	client->ps.viewangles[ 2 ] = ang[ 2 ];

	client->ps.viewheight = cameraoffset;

	client->ps.origin[ 0 ] = position[ 0 ];
	client->ps.origin[ 1 ] = position[ 1 ];
	client->ps.origin[ 2 ] = position[ 2 ];

	client->ps.velocity[ 0 ] = vel[ 0 ];
	client->ps.velocity[ 1 ] = vel[ 1 ];
	client->ps.velocity[ 2 ] = vel[ 2 ];

   /*
	client->ps.blend[ 0 ] = camerablend[ 0 ];
	client->ps.blend[ 1 ] = camerablend[ 1 ];
	client->ps.blend[ 2 ] = camerablend[ 2 ];
	client->ps.blend[ 3 ] = camerablend[ 3 ];
   */

	client->ps.fov = camerafov;

   if ( camera )
      {
      client->ps.camera_angles[ 0 ] = camera->angles[ 0 ];
      client->ps.camera_angles[ 1 ] = camera->angles[ 1 ];
      client->ps.camera_angles[ 2 ] = camera->angles[ 2 ];

      client->ps.camera_origin[ 0 ] = camera->origin[ 0 ];
      client->ps.camera_origin[ 1 ] = camera->origin[ 1 ];
      client->ps.camera_origin[ 2 ] = camera->origin[ 2 ];
      client->ps.pm_flags |= PMF_CAMERA_VIEW;

      //
      // clear out the flags, but preserve the CF_CAMERA_CUT_BIT
      //
      client->ps.camera_flags = client->ps.camera_flags & CF_CAMERA_CUT_BIT;
      }
   else
      {
      client->ps.pm_flags &= ~PMF_CAMERA_VIEW;
      //
      // make sure the third person camera is setup correctly.
      //

      if ( getMoveType() != MOVETYPE_NOCLIP )
         {
         qboolean do_cut;
         int camera_type;

         camera_type = currentState_Torso->getCameraType();
         if ( last_camera_type != camera_type )
            {
            //
            // clear out the flags, but preserve the CF_CAMERA_CUT_BIT
            //
            client->ps.camera_flags = client->ps.camera_flags & CF_CAMERA_CUT_BIT;
            do_cut = qtrue;
            switch( camera_type )
               {
               case CAMERA_TOPDOWN:
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_IGNORE_PITCH;
                  client->ps.camera_offset[ PITCH ] = -75;
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_ALLOWOFFSET;
                  do_cut = qfalse;
                  break;
               case CAMERA_FRONT:
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_IGNORE_PITCH;
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_ALLOWOFFSET;
                  client->ps.camera_offset[ YAW ] = 180;
                  client->ps.camera_offset[ PITCH ] = 0;
                  break;
               case CAMERA_SIDE:
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_IGNORE_PITCH;
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_ALLOWOFFSET;
                  // randomly invert the YAW
                  if ( G_Random( 1 ) > 0.5f )
                     {
                     client->ps.camera_offset[ YAW ] = -90;
                     }
                  else
                     {
                     client->ps.camera_offset[ YAW ] = 90;
                     }
                  client->ps.camera_offset[ PITCH ] = 0;
                  break;
               case CAMERA_SIDE_LEFT:
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_IGNORE_PITCH;
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_ALLOWOFFSET;
                  client->ps.camera_offset[ YAW ] = 90;
                  client->ps.camera_offset[ PITCH ] = 0;
                  break;
               case CAMERA_SIDE_RIGHT:
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_IGNORE_PITCH;
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_ALLOWOFFSET;
                  client->ps.camera_offset[ YAW ] = -90;
                  client->ps.camera_offset[ PITCH ] = 0;
                  break;
               case CAMERA_BEHIND_FIXED:
                  do_cut = qfalse;
                  client->ps.camera_offset[ YAW ] = 0;
                  client->ps.camera_offset[ PITCH ] = 0;
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_ALLOWOFFSET;
                  break;
               case CAMERA_BEHIND_NOPITCH:
                  do_cut = qfalse;
                  client->ps.camera_flags |= CF_CAMERA_ANGLES_IGNORE_PITCH;
                  client->ps.camera_offset[ YAW ] = 0;
                  client->ps.camera_offset[ PITCH ] = 0;
                  break;
               case CAMERA_BEHIND:
                  do_cut = qfalse;
                  client->ps.camera_offset[ YAW ] = 0;
                  client->ps.camera_offset[ PITCH ] = 0;
                  break;
               default:
                  do_cut = qfalse;
                  client->ps.camera_offset[ YAW ] = 0;
                  client->ps.camera_offset[ PITCH ] = 0;
                  break;
               }
            last_camera_type = camera_type;
            if ( do_cut )
               CameraCut();
            }
         }

      //
      // these are explicitly not cleared so that when the client lerps it still has the last
      // camera position for reference. Additionally this causes no extra hits to the network
      // traffic.
      //
      //VectorClear( client->ps.camera_angles );
      //VectorClear( client->ps.camera_origin );
      }

#define EARTHQUAKE_SCREENSHAKE_PITCH 2
#define EARTHQUAKE_SCREENSHAKE_YAW 2
#define EARTHQUAKE_SCREENSHAKE_ROLL 3

   if ( level.earthquake > level.time )
      {
      client->ps.damage_angles[ PITCH ] = G_CRandom() * level.earthquake_magnitude * EARTHQUAKE_SCREENSHAKE_PITCH;
      client->ps.damage_angles[ YAW ] = G_CRandom() * level.earthquake_magnitude * EARTHQUAKE_SCREENSHAKE_YAW;
      client->ps.damage_angles[ ROLL ] = G_CRandom() * level.earthquake_magnitude * EARTHQUAKE_SCREENSHAKE_ROLL;
      }
   else if ( damage_count )
      {
      client->ps.damage_angles[ PITCH ] = damage_angles[ PITCH ] * damage_count;
      client->ps.damage_angles[ ROLL ] = damage_angles[ ROLL ] * damage_count;
      }
   else
      {
      VectorClear( client->ps.damage_angles );
      }
	}

void Player::SetupView
	(
	void
	)

	{
   // if we currently are not in a camera or the camera we are looking through is automatic, evaluate our camera choices

	if ( actor_to_watch || actor_camera )
		{
		Vector dir;
		Vector watch_angles;
		float dist = 0;
		Vector focal_point;
		Vector left;
		trace_t trace;
		qboolean delete_actor_camera = false;
		Vector camera_mins;
		Vector camera_maxs;

		if ( actor_to_watch )
			{
			dir = actor_to_watch->origin - origin;
			dist = dir.length();
			}

		// See if we still want to watch this actor

		if ( !actor_to_watch || dist > 150 || actor_to_watch->deadflag )
			{
			delete_actor_camera = true;
			}
		else
			{
			// Create the camera if we don't have one yet

			if ( !actor_camera )
				{
				actor_camera = new Camera();

				if ( G_Random() < .5 )
					{
					actor_camera_right = true;
					starting_actor_camera_right = true;
					}
				else
					{
					actor_camera_right = false;
					starting_actor_camera_right = false;
					}
				}

			// Setup the new position of the actor camera

			// Go a little above the view height

			actor_camera->origin = origin;
			actor_camera->origin[2] += DEFAULT_VIEWHEIGHT + 10;

			// Find the focal point ( either the actor's watch offset or top of the bounding box)

			if ( actor_to_watch->watch_offset != vec_zero )
				{
				MatrixTransformVector( actor_to_watch->watch_offset, actor_to_watch->orientation, focal_point );
				focal_point += actor_to_watch->origin;
				}
			else
				{
				focal_point = actor_to_watch->origin;
				focal_point[2] = actor_to_watch->maxs[2];
				}

			// Shift the camera back just a little

			dir = focal_point - actor_camera->origin;
			dir.normalize();
			actor_camera->origin -= dir * 15;

			// Shift the camera a little to the left or right

			watch_angles = dir.toAngles();
			watch_angles.AngleVectors( NULL, &left );

			if ( actor_camera_right )
				actor_camera->origin -= left * 15;
			else
				actor_camera->origin += left * 15;

			// Make sure this camera position is ok

			camera_mins = "-5 -5 -5";
			camera_maxs = "5 5 5";

			trace = G_Trace( actor_camera->origin, camera_mins, camera_maxs, actor_camera->origin, actor_camera, MASK_DEADSOLID, false, "SetupView" );

			if ( trace.startsolid )
				{
				// Try other side

				if ( actor_camera_right == starting_actor_camera_right )
					{
					if ( actor_camera_right )
						actor_camera->origin += left * 30;
					else
						actor_camera->origin -= left * 30;

					actor_camera_right = !actor_camera_right;

					trace = G_Trace( actor_camera->origin, camera_mins, camera_maxs, actor_camera->origin, actor_camera, MASK_DEADSOLID, false, "SetupView2" );

					if ( trace.startsolid )
						{
						// Both spots have failed stop doing actor camera
						delete_actor_camera = true;
						}
					}
				else
					{
					// Both spots have failed stop doing actor camera
					delete_actor_camera = true;
					}
				}

			if ( !delete_actor_camera )
				{
				// Set the camera's position

				actor_camera->setOrigin( actor_camera->origin );

				// Set the camera's angles

				dir = focal_point - actor_camera->origin;
				watch_angles = dir.toAngles();
				actor_camera->setAngles( watch_angles );

				// Set this as our camera

				SetCamera( actor_camera, .5 );
				}
			}

		if ( delete_actor_camera )
			{
			// Get rid of this camera

			actor_to_watch = NULL;

			if ( actor_camera )
				{
				delete actor_camera;
				actor_camera = NULL;
				SetCamera( NULL, .5 );
				}
			}
		}
	else if ( ( level.automatic_cameras.NumObjects() > 0 ) && ( !camera || camera->IsAutomatic() ) )
      {
      int i;
      float score, bestScore;
      Camera *cam, *bestCamera;

      bestScore = 999;
      bestCamera = NULL;
      for( i = 1; i <= level.automatic_cameras.NumObjects(); i++ )
         {
         cam = level.automatic_cameras.ObjectAt( i );
         score = cam->CalculateScore( this, currentState_Torso->getName() );
         // if this is our current camera, scale down the score a bit to favor it.
         if ( cam == camera )
            {
            score *= 0.9f;
            }

         if ( score < bestScore )
            {
            bestScore = score;
            bestCamera = cam;
            }
         }
      if ( bestScore <= 1.0f )
         {
         // we have a camera to switch to
         if ( bestCamera != camera )
            {
            float time;

            if ( camera )
               {
               camera->AutomaticStop( this );
               }
            time = bestCamera->AutomaticStart( this );
            SetCamera( bestCamera, time );
            }
         }
      else
         {
         // we don't have a camera to switch to
         if ( camera )
            {
            float time;

            time = camera->AutomaticStop( this );
            SetCamera( NULL, time );
            }
         }
      }
   // If there is no camera, use the player's view
	if ( !camera )
		{
      SetPlayerView( NULL, origin, viewheight, v_angle, velocity, blend, fov );
		}
	else
		{
      SetPlayerView( camera, origin, viewheight, v_angle, velocity, blend, camera->Fov() );
		}
	}

/*
==================
SwingAngles
==================
*/
void Player::SwingAngles
   (
   float destination,
   float swingTolerance,
   float clampTolerance,
   float speed,
   float *angle,
   qboolean *swinging
   )

   {
	float	swing;
	float	move;
	float	scale;

	if ( !*swinging )
      {
		// see if a swing should be started
		swing = AngleSubtract( *angle, destination );
		if ( swing > swingTolerance || swing < -swingTolerance )
         {
			*swinging = qtrue;
         // we intentionally return so that we can start the animation before turning
         return;
         }
	   }

	if ( !*swinging )
      {
		return;
	   }

	// modify the speed depending on the delta
	// so it doesn't seem so linear
	swing = AngleSubtract( destination, *angle );
	scale = fabs( swing );

#if 0
	if ( scale < swingTolerance * 0.5 )
      {
		scale = 0.5;
	   }
   else if ( scale < swingTolerance )
      {
		scale = 1.0;
	   }
   else
      {
		scale = 2.0;
	   }
#else
   scale = 1.0f;
#endif

	// swing towards the destination angle
	if ( swing >= 0 )
      {
		move = level.frametime * scale * speed;
		if ( move >= swing )
         {
			move = swing;
			*swinging = qfalse;
		   }

		*angle = AngleMod( *angle + move );
	   }
   else if ( swing < 0 )
      {
		move = level.frametime * scale * -speed;
		if ( move <= swing )
         {
			move = swing;
			*swinging = qfalse;
		   }
		*angle = AngleMod( *angle + move );
	   }

	// clamp to no more than tolerance
	swing = AngleSubtract( destination, *angle );
	if ( swing > clampTolerance )
      {
		*angle = AngleMod( destination - ( clampTolerance - 1 ) );
	   }
   else if ( swing < -clampTolerance )
      {
		*angle = AngleMod( destination + ( clampTolerance - 1 ) );
	   }
   }

void Player::SetHeadTarget
   (
   Event *ev
   )

   {
   str ht = ev->GetString( 1 );

   head_target = G_FindTarget( 0, ht );
   }

qboolean Player::GetTagPositionAndOrientation
   (
   int            tagnum,
   orientation_t  *new_or
   )

   {
   int            i;
   orientation_t  tag_or;
   vec3_t         axis[3];

   tag_or = gi.Tag_OrientationEx( edict->s.modelindex,
                                  CurrentAnim( legs ),
                                  CurrentFrame( legs ),
                                  tagnum & TAG_MASK,
                                  edict->s.scale,
                                  edict->s.bone_tag,
                                  edict->s.bone_quat,
                                  0,
                                  0,
                                  1.0f,
                                  ( edict->s.anim & ANIM_BLEND ) != 0,
                                  ( edict->s.torso_anim & ANIM_BLEND ) != 0,
                                  CurrentAnim( torso ),
                                  CurrentFrame( torso ),
                                  0,
                                  0,
                                  1.0f
                                  );

   AnglesToAxis( angles, axis );
   VectorCopy( origin, new_or->origin );

   for ( i=0;  i<3; i++ )
      VectorMA( new_or->origin, tag_or.origin[i], axis[i], new_or->origin );

   MatrixMultiply( tag_or.axis, axis, new_or->axis );
   return true;
   }

qboolean Player::GetTagPositionAndOrientation
   (
   str            tagname,
   orientation_t  *new_or
   )

   {
   int            tagnum;

   tagnum = gi.Tag_NumForName( edict->s.modelindex, tagname );

   if ( tagnum < 0 )
      {
      warning( "Player::GetTagPositionAndOrientation", "Could not find tag \"%s\"", tagname.c_str() );
      return false;
      }

   return GetTagPositionAndOrientation( tagnum, new_or );
   }

Vector Player::GetAngleToTarget
   (
   Entity *ent,
   str    tag,
   float  yawclamp,
   float  pitchclamp,
   Vector baseangles
   )

   {
   assert( ent );

   if ( ent )
      {
      Vector         delta,angs;
      orientation_t  tag_or;

      int tagnum = gi.Tag_NumForName( edict->s.modelindex, tag.c_str() );

      if ( tagnum < 0 )
         return Vector( 0,0,0 );

      GetTagPositionAndOrientation( tagnum, &tag_or );

		delta = ent->centroid - tag_or.origin;
      delta.normalize();

      angs = delta.toAngles();

      AnglesSubtract( angs, baseangles, angs );

      angs[PITCH] = AngleNormalize180( angs[PITCH] );
      angs[YAW]   = AngleNormalize180( angs[YAW] );

      if ( angs[PITCH] > pitchclamp )
         angs[PITCH] = pitchclamp;
      else if ( angs[PITCH] < -pitchclamp )
         angs[PITCH] = -pitchclamp;

      if ( angs[YAW] > yawclamp )
         angs[YAW] = yawclamp;
      else if ( angs[YAW] < -yawclamp )
         angs[YAW] = -yawclamp;

      return angs;
      }
   else
      {
      return Vector( 0,0,0 );
      }
   }

void Player::DebugWeaponTags
   (
   int controller_tag,
   Weapon *weapon,
   str weapon_tagname
   )

   {
   int i;
   orientation_t  bone_or, tag_weapon_or, barrel_or, final_barrel_or;

   GetTagPositionAndOrientation( edict->s.bone_tag[controller_tag], &bone_or );
   //G_DrawCoordSystem( Vector( bone_or.origin ), Vector( bone_or.axis[0] ), Vector( bone_or.axis[1] ), Vector( bone_or.axis[2] ), 20 );

   GetTagPositionAndOrientation( gi.Tag_NumForName( edict->s.modelindex, weapon_tagname ), &tag_weapon_or );
   //G_DrawCoordSystem( Vector( tag_weapon_or.origin ), Vector( tag_weapon_or.axis[0] ), Vector( tag_weapon_or.axis[1] ), Vector( tag_weapon_or.axis[2] ), 40 );

   weapon->GetRawTag( "tag_barrel", &barrel_or );
   VectorCopy( tag_weapon_or.origin, final_barrel_or.origin );

   for ( i = 0 ; i < 3 ; i++ )
		VectorMA( final_barrel_or.origin, barrel_or.origin[i], tag_weapon_or.axis[i], final_barrel_or.origin );

   MatrixMultiply( barrel_or.axis, tag_weapon_or.axis, final_barrel_or.axis );
   //G_DrawCoordSystem( Vector( final_barrel_or.origin ), Vector( final_barrel_or.axis[0] ), Vector( final_barrel_or.axis[1] ), Vector( final_barrel_or.axis[2] ), 80 );

   if ( g_crosshair->integer )
      {
      trace_t trace;
      Vector  start,end,ang,dir,delta;
      vec3_t  mat[3];

      AnglesToAxis( v_angle, mat );

      dir   = mat[0];
      start = final_barrel_or.origin;
      end   = start + ( dir *  MAX_MAP_BOUNDS ); 

      G_DrawCoordSystem( start, Vector( mat[0] ), Vector( mat[1] ), Vector( mat[2] ), 80 );
      
      trace = G_Trace( start, vec_zero, vec_zero, end, this, MASK_PROJECTILE|MASK_WATER, qfalse, "Crosshair" );
      crosshair->setOrigin( trace.endpos );

      delta = trace.endpos - start;
      float length = delta.length();
      float scale  = g_crosshair_maxscale->value * length / MAX_MAP_BOUNDS;
      
      if ( scale < 1 )
         scale = 1;

      crosshair->setScale( scale );

      if ( trace.ent )
         {
         vectoangles( trace.plane.normal, ang );
         }
      else
         {
         vectoangles( dir, ang );
         }

      crosshair->setAngles( ang );
      }
   }

Vector Player::CalcArmTracking
   (
   int      controller_tag,
   str      weapon_tagname,
   Vector   baseAngles,
   Entity   *target,
   Weapon   *weapon
   )

   {
   Vector         forward, delta, angs;
   orientation_t  bone_or, tag_weapon_or, barrel_or, final_barrel_or;
   int            i;

   assert( target );

   if ( !target )
      {
      warning( "Player::CalcArmTracking", "NULL target for Arm Tracking." );
      return Vector( 0,0,0 );
      }

   GetTagPositionAndOrientation( edict->s.bone_tag[controller_tag], &bone_or );

   if ( g_showautoaim->integer )
      G_DebugLine( bone_or.origin, bone_or.origin + Vector( bone_or.axis[0] ) * 200, 1,1,1,1 );

   GetTagPositionAndOrientation( gi.Tag_NumForName( edict->s.modelindex, weapon_tagname ), &tag_weapon_or );

   if ( g_showautoaim->integer )
      G_DebugLine( tag_weapon_or.origin, tag_weapon_or.origin + Vector( tag_weapon_or.axis[0] ) * 50, 1,0,0,1 );

   if ( !weapon->GetRawTag( "tag_barrel", &barrel_or ) )
      {
      warning( "Player::CalcArmTracking", "Could not find tag_barrel." );
      return Vector( 0,0,0 );
      }

   VectorCopy( tag_weapon_or.origin, final_barrel_or.origin );

   for ( i = 0 ; i < 3 ; i++ )
		VectorMA( final_barrel_or.origin, barrel_or.origin[i], tag_weapon_or.axis[i], final_barrel_or.origin );

   MatrixMultiply( barrel_or.axis, tag_weapon_or.axis, final_barrel_or.axis );

   delta = target->centroid - final_barrel_or.origin;
   delta.normalize();

   angs = delta.toAngles();
   AnglesSubtract( angs, torsoAngles, angs );

   if ( g_showautoaim->integer )
      G_DebugLine( final_barrel_or.origin, final_barrel_or.origin + Vector( final_barrel_or.axis[0] ) * 50, 0,0,1,1 );
   if ( g_showautoaim->integer )
      G_DebugLine( final_barrel_or.origin, target->centroid, 0,1,0,1 );

   return angs;
   }


void Player::AcquireTarget
   (
   void
   )

   {
   Weapon *weapon;
   Vector offset;
   vec3_t mat[3];
   Entity *new_target;

   AnglesToAxis( headAngles, mat );

	if ( left_arm_target )
		{
		left_arm_target->edict->s.eFlags &= ~EF_LEFT_TARGETED;
		}

	if ( right_arm_target )
		{
		right_arm_target->edict->s.eFlags &= ~EF_RIGHT_TARGETED;
		}

   // Find a left hand target if the left hand weapon is an auto aim
   weapon = GetActiveWeapon( WEAPON_LEFT );

   if ( weapon && weapon->autoaim )
      {
      offset = Vector( mat[1] ) * 25;

      if ( left_arm_target )
         {
         new_target  = FindEnemyInFOVFromTagWithOffset( 60, weapon->GetMaxRange(), L_ARM_NAME, offset );
         }
      else
         {
         new_target  = FindEnemyInFOVFromTagWithOffset( 40, weapon->GetMaxRange(), L_ARM_NAME, offset );
         }

      if ( new_target )
         {
         left_arm_target = new_target;
         left_arm_target->edict->s.eFlags |= EF_LEFT_TARGETED;
         CancelEventsOfType( EV_Player_ClearLeftArmTarget );
         }
      else
         PostEvent( EV_Player_ClearLeftArmTarget, 1.0f );
      }
   else
      {
      PostEvent( EV_Player_ClearLeftArmTarget, 1.0f );
      }

   // Find a right hand target ( might be the same one )
   weapon = GetActiveWeapon( WEAPON_RIGHT );

   if ( weapon && weapon->autoaim )
      {
      offset = Vector( mat[1] ) * -25;

      if ( right_arm_target )
         {
         new_target = FindEnemyInFOVFromTagWithOffset( 60, weapon->GetMaxRange(), R_ARM_NAME, offset );
         }
      else
         {
         new_target = FindEnemyInFOVFromTagWithOffset( 40, weapon->GetMaxRange(), R_ARM_NAME, offset );
         }

      if ( new_target )
         {
         right_arm_target = new_target;
         right_arm_target->edict->s.eFlags |= EF_RIGHT_TARGETED;
         CancelEventsOfType( EV_Player_ClearRightArmTarget );
         }
      else
         {
         PostEvent( EV_Player_ClearRightArmTarget, 1.0f );
         }
      }
   else
      {
      PostEvent( EV_Player_ClearRightArmTarget, 1.0f );
      }
   }

void Player::RemoveTarget
   (
   Entity *ent_to_remove
   )

   {
   if ( left_arm_target == ent_to_remove )
      {
      left_arm_target->edict->s.eFlags &= ~EF_LEFT_TARGETED;
		left_arm_target = NULL;
      }

   if ( right_arm_target == ent_to_remove)
      {
      right_arm_target->edict->s.eFlags &= ~EF_RIGHT_TARGETED;
		right_arm_target = NULL;
      }
	}

void Player::AutoAim
   (
   void
   )

   {
   Weapon *weapon;
   Vector newAimAngles;


	if ( deadflag )
		return;

   // Check for targets in the FOV
   AcquireTarget();

   // Update Crosshair
   weapon = GetActiveWeapon( WEAPON_DUAL );
   if ( crosshair )
      {
      if ( g_crosshair->integer )
         {
         if ( weapon && weapon->crosshair && !level.cinematic )
            {
           // Update the position of the crosshair based on the attachment of the weapon
            if ( weapon->dual_attachToTag == "tag_weapon_right" )
               DebugWeaponTags( R_ARM_TAG, weapon, "tag_weapon_right" );
            else
               DebugWeaponTags( L_ARM_TAG, weapon, "tag_weapon_left" );

            crosshair->showModel();
            }
         else 
            {
            crosshair->hideModel();
            }
         }
      else
         {  
         crosshair->hideModel();
         }
      }

   // Check for auto targeting on right side
   weapon = GetActiveWeapon( WEAPON_RIGHT );

   if ( weapon )
      {
      DebugWeaponTags( R_ARM_TAG, weapon, "tag_weapon_right" );
      weapon->SetAimTarget( NULL );  
      }

   if ( weapon && weapon->autoaim && right_arm_target )
      {
      weapon->SetAimTarget( right_arm_target );

      newAimAngles = CalcArmTracking( R_ARM_TAG, "tag_weapon_right", torsoAngles, right_arm_target, weapon );

      // Clamp newAimAngles
      if ( newAimAngles[YAW] > 30 )
         newAimAngles[YAW] = 30;
      if ( newAimAngles[YAW] < -30 )
         newAimAngles[YAW] = -30;
      if ( newAimAngles[PITCH] > 30 )
         newAimAngles[PITCH] = 30;
      if ( newAimAngles[PITCH] < -30 )
         newAimAngles[PITCH] = -30;

      rightArmAimAngles[PITCH]  = LerpAngle( rightArmAimAngles[PITCH], newAimAngles[PITCH], 0.5f );
      rightArmAimAngles[YAW]    = LerpAngle( rightArmAimAngles[YAW],   newAimAngles[YAW],   0.5f );
      }
   else
      {
      rightArmAimAngles[PITCH]  = LerpAngle( rightArmAimAngles[PITCH], 0, 0.5f );
      rightArmAimAngles[YAW]    = LerpAngle( rightArmAimAngles[YAW],   0, 0.5f );
      }

   SetControllerAngles( R_ARM_TAG, rightArmAimAngles );

   // Check for auto targeting on left side
   weapon = GetActiveWeapon( WEAPON_LEFT );

   if ( weapon )
      {
      DebugWeaponTags( L_ARM_TAG, weapon, "tag_weapon_left" );
      weapon->SetAimTarget( NULL );  
      }

   if ( weapon && weapon->autoaim && left_arm_target )
      {
      weapon->SetAimTarget( left_arm_target );

      newAimAngles = CalcArmTracking( L_ARM_TAG, "tag_weapon_left", torsoAngles, left_arm_target, weapon );
      // Clamp newAimAngles
      if ( newAimAngles[YAW] > 30 )
         newAimAngles[YAW] = 30;
      if ( newAimAngles[YAW] < -30 )
         newAimAngles[YAW] = -30;
      if ( newAimAngles[PITCH] > 30 )
         newAimAngles[PITCH] = 30;
      if ( newAimAngles[PITCH] < -30 )
         newAimAngles[PITCH] = -30;

      leftArmAimAngles[PITCH]  = LerpAngle( leftArmAimAngles[PITCH], newAimAngles[PITCH], 0.5f );
      leftArmAimAngles[YAW]    = LerpAngle( leftArmAimAngles[YAW],   newAimAngles[YAW],   0.5f );
      }
   else
      {
      leftArmAimAngles[PITCH]  = LerpAngle( leftArmAimAngles[PITCH], 0, 0.5f );
      leftArmAimAngles[YAW]    = LerpAngle( leftArmAimAngles[YAW],   0, 0.5f );
      }

   SetControllerAngles( L_ARM_TAG, leftArmAimAngles );
   }

/*
===============
PlayerAngles
===============
*/
void Player::PlayerAngles
   (
   void
   )

   {
	float    deltayaw;
   Vector   moveangles;
	float		speed;
	float    yawAngle;
   float    speedscale;
   vec3_t   temp;
   Vector   dir;
   Vector   newAimAngles;

   // Adjust the angles of the player for attacking an enemy
   // AdjustAnglesForAttack();

   if ( gi.Anim_Flags( edict->s.modelindex, CurrentAnim( legs ) ) & MDL_ANIM_DEFAULT_ANGLES )
      {
      SetControllerAngles( HEAD_TAG, vec_zero );
      SetControllerAngles( TORSO_TAG, vec_zero );
      setAngles( Vector( 0, v_angle.y, 0 ) );
      AutoAim();
      return;
      }

   // set the head and torso directly
   headAngles.setXYZ( v_angle.x, AngleMod( v_angle.y ), v_angle.z );
   torsoAngles.setXYZ( v_angle.x, AngleMod( v_angle.y ), v_angle.z );

   dir = Vector( velocity.x, velocity.y, 0 );
	speed = VectorNormalize( dir );

   // If moving, angle the legs toward the direction we are moving
   if ( ( speed > 32 ) && groundentity && last_ucmd.forwardmove )
      {
      speedscale = 3;
      yawing   = qtrue; // always center
      deltayaw = AngleSubtract( dir.toYaw(), headAngles[ YAW ] );
      }
   else
      {
      speedscale = 1;
      deltayaw = 0;
      }

   // --------- yaw -------------
   // Clamp to g_legclampangle
   if ( fabs( deltayaw ) > 90 )
      deltayaw = AngleSubtract( deltayaw, 180 );

   if ( deltayaw > g_legclampangle->value )
      deltayaw = g_legclampangle->value;
   else if ( deltayaw < -g_legclampangle->value )
      deltayaw = -g_legclampangle->value;

   yawAngle = headAngles[ YAW ] + deltayaw;

   yawing_left = qfalse;
   yawing_right = qfalse;

   if ( client->ps.walking && client->ps.groundPlane && ( movecontrol == MOVECONTROL_LEGS ) &&
      !last_ucmd.forwardmove && !last_ucmd.rightmove && ( client->ps.groundTrace.plane.normal[ 2 ] < SLOPE_22_MAX ) )
      {
      float groundyaw;
      float yawdelta;

      groundyaw = ( int )vectoyaw( client->ps.groundTrace.plane.normal );
      yawdelta = anglemod( v_angle.y - groundyaw );
      yawdelta = ( ( ( int )yawdelta + 45 ) / 90 ) * 90.0f;
      angles.y = groundyaw + yawdelta;
      }
   else
      {
      // if purely strafing, don't swing the legs
      if ( client->ps.walking && last_ucmd.rightmove && !last_ucmd.forwardmove ) 
         {
         setAngles( Vector( 0, v_angle.y, 0 ) );
         }
      else
         {
         SwingAngles( yawAngle, g_legtolerance->value, g_legclamptolerance->value, g_legswingspeed->value * speedscale, &angles[ YAW ], &yawing );
         if ( yawing )
            {
            float swing;
   		   swing = AngleSubtract( yawAngle, angles[ YAW ] );
		      if ( swing > 0 )
               {
               yawing_left = qtrue;
               }
            else
               {
               yawing_right = qtrue;
               }
            }
         }
      }

	// --------- pitch -------------

   // only show a fraction of the pitch angle in the torso
	if ( headAngles[ PITCH ] > 180 )
      {
		torsoAngles[PITCH] = ( -360 + headAngles[ PITCH ] ) * 0.75;
	   }
   else
      {
		torsoAngles[PITCH] = headAngles[ PITCH ] * 0.75;
	   }

	AcquireHeadTarget();

   // Adjust head and torso angles for the target if needed
   if ( head_target )
      {
		//newAimAngles   = GetAngleToTarget( head_target, "Bip01 Head", 60, 45, torsoAngles );
		newAimAngles   = GetAngleToTarget( head_target, "Bip01 Head", 40, 30, torsoAngles );

      headAimAngles[PITCH]  = LerpAngle( headAimAngles[PITCH], newAimAngles[PITCH], 0.25f );
      headAimAngles[YAW]    = LerpAngle( headAimAngles[YAW],   newAimAngles[YAW],   0.25f );

		torsoAimAngles[PITCH] = LerpAngle( torsoAimAngles[PITCH], 0, 0.5f );
      torsoAimAngles[YAW]   = LerpAngle( torsoAimAngles[YAW],   0, 0.5f );
      }
   else // Otherwise return to them to 0
      {
      headAimAngles[PITCH]  = LerpAngle( headAimAngles[PITCH],  0, 0.5f );
      headAimAngles[YAW]    = LerpAngle( headAimAngles[YAW],    0, 0.1f );

      torsoAimAngles[PITCH] = LerpAngle( torsoAimAngles[PITCH], 0, 0.5f );
      torsoAimAngles[YAW]   = LerpAngle( torsoAimAngles[YAW],   0, 0.5f );
      }

   // pull the head angles back out of the hierarchial chain
   AnglesSubtract( headAngles, torsoAngles, temp );

	// Add in the aim angles for the head
	VectorAdd( temp, headAimAngles, temp );

   // Update the head controller
   SetControllerAngles( HEAD_TAG, temp );

   // pull the torso angles back out of the hierarchial chain
	AnglesSubtract( torsoAngles, angles, temp );

   // Add in the aim angles for the torso
   VectorAdd( temp, torsoAimAngles, temp );

   // Update the torso controller
   SetControllerAngles( TORSO_TAG, temp );

   // Auto aim for the arms
   AutoAim();

   // Set the rest (legs)
   setAngles( angles );

//   warning( "PlayerAngles", "head %.2f torso %.2f legs %.2f\n", headAngles.y, torsoAngles.y, angles.y );
   }

void Player::FinishMove
	(
	void
	)

	{
	//
	// If the origin or velocity have changed since ClientThink(),
	// update the pmove values.  This will happen when the client
	// is pushed by a bmodel or kicked by an explosion.
	//
	// If it wasn't updated here, the view position would lag a frame
	// behind the body position when pushed -- "sinking into plats"
	//
   if ( !( client->ps.pm_flags & PMF_FROZEN ) && !( client->ps.pm_flags & PMF_NO_MOVE ))
      {
      origin.copyTo( client->ps.origin );
      velocity.copyTo( client->ps.velocity );
      }

   if ( !( client->ps.pm_flags & PMF_FROZEN ) )
      {
	   PlayerAngles();
      }

   // burn from lava, etc
	WorldEffects();

	// determine the view offsets
	DamageFeedback();
	CalcBlend();
	}

void Player::StatCount
   (
   int index,
   int count
   )

   {
   // If stat is going up
   if ( oldstats[index] < count )
      {
      oldstats[index] += count * level.frametime * 4;

      // Clamp
      if ( oldstats[index] > count )
         {
         oldstats[index] = count;
         }

      client->ps.stats[index] = oldstats[index];
      }
   else
      {
      client->ps.stats[index] = count;
      }
   }

void Player::UpdateStats
	(
	void
	)

	{
   int i,count;

   //
   // Health
   //
   if ( ( health < 1 ) && ( health > 0 ) )
      {
 	   client->ps.stats[ STAT_HEALTH ] = 1;
      }
   else
      {
      client->ps.stats[ STAT_HEALTH ] = health;
      }

   //
   // if we just got full water or lost it, update our boots
   //
   if ( water_power >= MINIMUM_WATER_FOR_TURBO && client->ps.stats[STAT_WATER_LEVEL] < MINIMUM_WATER_FOR_TURBO )
      {
      SurfaceCommand( "bootlights", "+skin1" );
      }
   else if ( water_power < MINIMUM_WATER_FOR_TURBO && client->ps.stats[STAT_WATER_LEVEL] >= MINIMUM_WATER_FOR_TURBO )
      {
      SurfaceCommand( "bootlights", "-skin1" );
      }

   client->ps.stats[ STAT_WATER_LEVEL ] = water_power;
   //StatCount( STAT_WATER_LEVEL, water_power );

   /*
   if ( oldstats[STAT_WATER_LEVEL] != water_power )
      {
      client->ps.stats[STAT_WATER_LEVEL] = 0;
      oldstats[STAT_WATER_LEVEL] = water_power;
      }
   else
      {
      client->ps.stats[STAT_WATER_LEVEL] = water_power;
      }
   */

   Weapon *leftweapon  = GetActiveWeapon( WEAPON_LEFT );
   Weapon *rightweapon = GetActiveWeapon( WEAPON_RIGHT );
   Weapon *dualweapon  = GetActiveWeapon( WEAPON_DUAL );

   client->ps.stats[STAT_AMMO_LEFT]                 = 0;
   client->ps.stats[STAT_AMMO_RIGHT]                = 0;
   client->ps.stats[STAT_CLIPAMMO_LEFT]             = 0;
   client->ps.stats[STAT_CLIPAMMO_RIGHT]            = 0;
   client->ps.stats[STAT_MAXAMMO_LEFT]              = 0;
   client->ps.stats[STAT_MAXAMMO_RIGHT]             = 0;
   client->ps.stats[STAT_MAXCLIPAMMO_LEFT]          = 0;
   client->ps.stats[STAT_MAXCLIPAMMO_RIGHT]         = 0;
   
   client->ps.stats[ STAT_ACCUMULATED_PAIN]          = accumulated_pain;

   client->ps.activeItems[ ITEM_NAME_AMMO_LEFT ]      = -1;
   client->ps.activeItems[ ITEM_NAME_AMMO_RIGHT ]     = -1;
   client->ps.activeItems[ ITEM_NAME_WEAPON_LEFT ]    = -1;
   client->ps.activeItems[ ITEM_NAME_WEAPON_RIGHT ]   = -1;
   client->ps.activeItems[ ITEM_NAME_WEAPON_DUAL ]    = -1;


   if ( leftweapon )
      {
      client->ps.stats[STAT_AMMO_LEFT]                = AmmoCount( leftweapon->GetAmmoType( FIRE_PRIMARY ) );
      client->ps.stats[STAT_MAXAMMO_LEFT]             = MaxAmmoCount( leftweapon->GetAmmoType( FIRE_PRIMARY ) );
      client->ps.stats[STAT_CLIPAMMO_LEFT]            = leftweapon->ClipAmmo( FIRE_PRIMARY );
      client->ps.stats[STAT_MAXCLIPAMMO_LEFT]         = leftweapon->GetClipSize( FIRE_PRIMARY );
      client->ps.activeItems[ITEM_NAME_AMMO_LEFT]     = AmmoIndex( leftweapon->GetAmmoType( FIRE_PRIMARY ) );
      client->ps.activeItems[ITEM_NAME_WEAPON_LEFT]   = leftweapon->getIndex();
      }
   if ( rightweapon )
      {
      client->ps.stats[STAT_AMMO_RIGHT]               = AmmoCount( rightweapon->GetAmmoType( FIRE_PRIMARY ) );
      client->ps.stats[STAT_MAXAMMO_RIGHT]            = MaxAmmoCount( rightweapon->GetAmmoType( FIRE_PRIMARY ) );
      client->ps.stats[STAT_CLIPAMMO_RIGHT]           = rightweapon->ClipAmmo( FIRE_PRIMARY );
      client->ps.stats[STAT_MAXCLIPAMMO_RIGHT]        = rightweapon->GetClipSize( FIRE_PRIMARY );
      client->ps.activeItems[ITEM_NAME_AMMO_RIGHT]    = AmmoIndex( rightweapon->GetAmmoType( FIRE_PRIMARY ) );
      client->ps.activeItems[ITEM_NAME_WEAPON_RIGHT]  = rightweapon->getIndex();
      }
   if ( dualweapon )
      {
      // Left is PRIMARY
      client->ps.stats[STAT_AMMO_LEFT]                = AmmoCount( dualweapon->GetAmmoType( FIRE_PRIMARY ) );
      client->ps.stats[STAT_MAXAMMO_LEFT]             = MaxAmmoCount( dualweapon->GetAmmoType( FIRE_PRIMARY ) );
      client->ps.stats[STAT_CLIPAMMO_LEFT]            = dualweapon->ClipAmmo( FIRE_PRIMARY );
      client->ps.activeItems[ITEM_NAME_AMMO_LEFT]     = AmmoIndex( dualweapon->GetAmmoType( FIRE_PRIMARY ) );
      // Right is AlTERNATE
      client->ps.stats[STAT_AMMO_RIGHT]               = AmmoCount( dualweapon->GetAmmoType( FIRE_ALTERNATE ) );
      client->ps.stats[STAT_MAXAMMO_RIGHT]            = MaxAmmoCount( dualweapon->GetAmmoType( FIRE_ALTERNATE ) );
      client->ps.stats[STAT_CLIPAMMO_RIGHT]           = dualweapon->ClipAmmo( FIRE_ALTERNATE );
      client->ps.activeItems[ITEM_NAME_AMMO_RIGHT]    = AmmoIndex( dualweapon->GetAmmoType( FIRE_ALTERNATE ) );

      client->ps.activeItems[ITEM_NAME_WEAPON_DUAL]   = dualweapon->getIndex();
      }

   //
   // set boss health
   //
   client->ps.stats[ STAT_BOSSHEALTH ]                = bosshealth->value * 100.0f;

	if ( bosshealth->value * 100.0f > 0 && client->ps.stats[ STAT_BOSSHEALTH ] == 0 )
		client->ps.stats[ STAT_BOSSHEALTH ] = 1;

	// Set cinematic stuff

	client->ps.stats[ STAT_CINEMATIC ] = 0;

	if ( level.cinematic )
		client->ps.stats[ STAT_CINEMATIC ] = (1<<0);

	if ( actor_camera )
		client->ps.stats[ STAT_CINEMATIC ] += (1<<1);

   // Go through all the player's weapons and send over the indexes of the names
   memset( client->ps.inventory_name_index, 0, sizeof( client->ps.inventory_name_index ) );
   
   count = inventory.NumObjects();

   assert( count < MAX_INVENTORY );
   if ( count > MAX_INVENTORY )
      {
      gi.Error( ERR_DROP, "Player::UpdateStats : Exceeded MAX_ITEMS\n" );
      }

   for ( i=1; i<=count; i++ )
      {
      int entnum = inventory.ObjectAt( i );
      Item *item = ( Item * )G_GetEntity( entnum );

      if ( item )
         client->ps.inventory_name_index[i-1] = item->getIndex();
      }   
   
   // Go through all the player's ammo and send over the names/amounts
   memset( client->ps.ammo_amount, 0, sizeof( client->ps.ammo_amount ) );

   count = ammo_inventory.NumObjects();

   assert( count < MAX_AMMO );
   if ( count > MAX_AMMO )
      {
      gi.Error( ERR_DROP, "Player::UpdateStats : Exceeded MAX_AMMO\n" );
      }

   for ( i=1; i<=count; i++ )
      {
      Ammo *ammo = ammo_inventory.ObjectAt( i );

      if ( ammo )
         {
         client->ps.ammo_amount[i-1]     = ammo->getAmount();
         client->ps.max_ammo_amount[i-1] = ammo->getMaxAmount();
         client->ps.ammo_name_index[i-1] = ammo->getIndex();
         }
      }

   // Do letterbox

   // Check for letterbox fully out
   if ( ( level.m_letterbox_time <= 0 ) && ( level.m_letterbox_dir == letterbox_in ) )
      {
      client->ps.stats[STAT_LETTERBOX] = level.m_letterbox_fraction * MAX_LETTERBOX_SIZE;
      return;
      }
   else if ( ( level.m_letterbox_time <= 0 ) && ( level.m_letterbox_dir == letterbox_out ) )
      {
      client->ps.stats[STAT_LETTERBOX] = 0;
      return;
      }

   float frac;

   level.m_letterbox_time -= level.frametime;
      
   frac = level.m_letterbox_time / level.m_letterbox_time_start;

   if ( frac > 1 )
      frac = 1;
   if ( frac < 0 )
      frac = 0;

   if ( level.m_letterbox_dir == letterbox_in )
      frac = 1.0f - frac;

   client->ps.stats[STAT_LETTERBOX] = ( frac * level.m_letterbox_fraction ) * MAX_LETTERBOX_SIZE;
   }

void Player::UpdateMusic
	(
	void
	)
	{
   if ( music_forced )
      {
      client->ps.current_music_mood = music_current_mood;
      client->ps.fallback_music_mood = music_fallback_mood;
      }
   else if ( action_level > 30 )
      {
      client->ps.current_music_mood = mood_action;
      client->ps.fallback_music_mood = mood_normal;
      }
   else if ( action_level < 15 )
      {
      client->ps.current_music_mood = music_current_mood;
      client->ps.fallback_music_mood = music_fallback_mood;
      }

   if (action_level > 0)
      {
      action_level -= level.fixedframetime * 2.0f;
      if ( action_level > 80 )
         {
         action_level = 80;
         }
      }
   else
      {
      action_level = 0;
      }

   //
   // set the music
   // naturally decay the action level
   //
   if ( s_debugmusic->integer )
      {
      gi.DPrintf( "%s's action_level = %4.2f\n", client->pers.netname, action_level );
      }

	// Copy music volume and fade time to player state
	client->ps.music_volume           = music_current_volume;
	client->ps.music_volume_fade_time = music_volume_fade_time;
   }

void Player::SetReverb
	(
	int type,
	float level
	)

	{
	reverb_type  = type;
	reverb_level = level;
	}

void Player::SetReverb
	(
   str type,
	float level
	)

	{
	reverb_type  = EAXMode_NameToNum( type );
	reverb_level = level;
	}

void Player::SetReverb
	(
	Event *ev
	)
	{
	if ( ev->NumArgs() < 2 )
		return;

	SetReverb( ev->GetInteger( 1 ), ev->GetFloat( 2 ) );
	}

void Player::UpdateReverb
	(
	void
	)
	{
	client->ps.reverb_type  = reverb_type;
	client->ps.reverb_level = reverb_level;
	}

void Player::EndAnim_Legs
   (
   Event *ev
   )

   {
   animdone_Legs = true;
   SetAnimDoneEvent( EV_Player_AnimLoop_Legs, legs );
   EvaluateState();
   }

void Player::EndAnim_Torso
   (
   Event *ev
   )

   {
   animdone_Torso = true;
   SetAnimDoneEvent( EV_Player_AnimLoop_Torso, torso );
   EvaluateState();
   }

void Player::SetAnim
	(
	const char *anim,
   bodypart_t part
	)

   {
   assert( anim );

   if ( ( part != all ) && ( partAnim[ part ] == anim ) )
		{
   	return;
		}

	if ( ( part == all ) && ( partAnim[ legs ] == anim ) && ( partAnim[ torso ] == anim ) )
		{
   	return;
		}

   if ( getMoveType() == MOVETYPE_NOCLIP )
      {
      anim = "idle";
      }

   if ( part != all )
      {
      partAnim[ part ] = anim;
      }
   else
      {
      partAnim[ legs ] = anim;
      partAnim[ torso ] = anim;
      }

   switch( part )
      {
      default :
      case all :
         RandomAnimate( anim, EV_Player_AnimLoop_Legs, part );
         break;

      case legs :
         RandomAnimate( anim, EV_Player_AnimLoop_Legs, part );
         break;

      case torso :
         RandomAnimate( anim, EV_Player_AnimLoop_Torso, part );
         break;
      }

   if ( ( part == legs ) || ( part == all ) )
      {
      Vector animmove;
      float time;
      float len;

      time = gi.Anim_Time( edict->s.modelindex, CurrentAnim() );
      gi.Anim_Delta( edict->s.modelindex, CurrentAnim(), animmove );
      len = animmove.length();
      if ( len == 0 || time == 0 )
         {
         animspeed = 0;
         }
      else
         {
         animspeed = len / time;
         }
      }
	}

void Player::UpdateSword
   (
   Sword *sword
   )

   {
   if ( GetWaterPower() >= sword->GetWaterRequired() )
      {
      sword->SetPowerOn();
      }
   else
      {
      sword->SetPowerOff();
      }
   }

void Player::CheckReloadWeapons
   (
   void
   )

   {
   Weapon *weap;

   weap = GetActiveWeapon( WEAPON_LEFT );
   if ( weap )
      {
      weap->CheckReload( FIRE_PRIMARY );
      }

   weap = GetActiveWeapon( WEAPON_RIGHT );
   if ( weap )
      {
      weap->CheckReload( FIRE_PRIMARY );
      }

   weap = GetActiveWeapon( WEAPON_DUAL );
   if ( weap )
      {
      weap->CheckReload( FIRE_PRIMARY );
      weap->CheckReload( FIRE_ALTERNATE );
      }
   }

void Player::UpdateWeapons
   (
   void
   )

   {
   // Check for ammo reload and sword power
   Weapon *weap;
   Sword  *sword;

   weap = GetActiveWeapon( WEAPON_LEFT );
   if ( weap )
      {
      if ( weap->isSubclassOf( Sword ) )
         {
         sword = ( Sword * )weap;
         UpdateSword( sword );
         }
      }

   weap = GetActiveWeapon( WEAPON_RIGHT );
   if ( weap )
      {
      if ( weap->isSubclassOf( Sword ) )
         {
         sword = ( Sword * )weap;
         UpdateSword( sword );
         }
      }

   weap = GetActiveWeapon( WEAPON_DUAL );
   if ( weap )
      {
      if ( weap->isSubclassOf( Sword ) )
         {
         sword = ( Sword * )weap;
         UpdateSword( sword );
         }
      }
   }

void Player::UpdateMisc
   (
   void
   )

   {
   //
   // clear out the level exit flag
   //
   client->ps.pm_flags &= ~PMF_LEVELEXIT;

   //
   // see if our camera is the level exit camera
   //
   if ( camera && camera->IsLevelExit() )
      {
      client->ps.pm_flags |= PMF_LEVELEXIT;
      }
   else if ( level.near_exit )
      {
      client->ps.pm_flags |= PMF_LEVELEXIT;
      }
   // 
   // do anything special for level exits
   //
   if ( client->ps.pm_flags & PMF_LEVELEXIT )
      {
      //
      // change music
      //
      if ( music_current_mood != mood_success )
         {
         ChangeMusic( "success", "normal", false );
         }
      }
   }

/*
=================
EndFrame

Called for each player at the end of the server frame
and right after spawning
=================
*/
void Player::EndFrame
	(
	Event *ev
	)

	{
	FinishMove();
   CheckReloadWeapons();
   UpdateStats();
   UpdateMusic();
	UpdateReverb();
   UpdateMisc();
   SetupView();
	}

void Player::GibEvent
   (
   Event *ev
   )

   {
   qboolean hidemodel;

   hidemodel = !ev->GetInteger( 1 );

   if ( com_blood->integer )
      {
      if ( hidemodel )
         {
	      gibbed = true;
         takedamage = DAMAGE_NO;
         setSolidType( SOLID_NOT );
         hideModel();
         }

      CreateGibs( this, health, 0.75f, 3 );
      }
   }

void Player::GotKill
	(
	Event *ev
	)

	{
/*
	Entity *victim;
   Entity *inflictor;
   float   damage;
   int     meansofdeath;
   qboolean gibbed;

   if ( deathmatch->integer )
		{
      return;
		}

	victim = ev->GetEntity( 1 );
	damage = ev->GetInteger( 2 );
	inflictor = ev->GetEntity( 3 );
	meansofdeath = ev->GetInteger( 4 );
	gibbed = ev->GetInteger( 5 );
*/
	}

void Player::SetPowerupTimer
   (
   Event *ev
   )

   {
   Event *event;

   poweruptimer = ev->GetInteger( 1 );
   poweruptype  = ev->GetInteger( 2 );
   event = new Event( EV_Player_UpdatePowerupTimer );
   PostEvent ( event, 1 );
   }

void Player::UpdatePowerupTimer
   (
   Event *ev
   )

   {
   poweruptimer -= 1;
   if ( poweruptimer > 0 )
      {
      PostEvent( ev, 1 );
      }
   else
      {
      poweruptype = 0;
      }
   }

void Player::ChangeMusic
	(
   const char * current,
   const char * fallback,
   qboolean force
	)

   {
   int current_mood_num;
   int fallback_mood_num;

   music_forced = force;
   if ( str( current ) == "normal" )
      {
      music_forced = false;
      }
   //
   // we no longer let any music be forced
   //
   music_forced = false;

   // zero out action_level so that we do get a change
   //
   action_level = 0;

   if ( current )
      {
      current_mood_num = MusicMood_NameToNum( current );
      if ( current_mood_num < 0 )
         {
         gi.DPrintf( "current music mood %s not found", current );
         }
      else
         {
         music_current_mood = current_mood_num;
         }
      }

   if ( fallback )
      {
      fallback_mood_num = MusicMood_NameToNum( fallback );
      if ( fallback_mood_num < 0 )
         {
         gi.DPrintf( "fallback music mood %s not found", fallback );
         fallback = NULL;
         }
      else
         {
         music_fallback_mood = fallback_mood_num;
         }
      }
   }

void Player::ChangeMusicVolume
	(
   float volume,
	float fade_time
	)

   {
	music_volume_fade_time = fade_time;
	music_saved_volume     = music_current_volume;
	music_current_volume   = volume;
	}

void Player::RestoreMusicVolume
	(
   float fade_time
	)

   {
	music_volume_fade_time = fade_time;
	music_current_volume   = music_saved_volume;
	music_saved_volume     = -1.0;
	}

void Player::GiveOxygen
   (
   float time
   )

   {
   air_finished = level.time + time;
   }

void Player::Jump
   (
   Event *ev
   )

   {
   float maxheight;

   maxheight = ev->GetFloat( 1 );

   if ( maxheight > 16 )
      {
      // v^2 = 2ad
      velocity[ 2 ] += sqrt( 2 * sv_gravity->integer * maxheight );

      // make sure the player leaves the ground
      client->ps.walking = qfalse;
      }
   }

void Player::JumpXY
   (
   Event *ev
   )

   {
   float forwardmove;
   float sidemove;
   float distance;
   float time;
   float speed;

   forwardmove = ev->GetFloat( 1 );
   sidemove    = ev->GetFloat( 2 );
   speed       = ev->GetFloat( 3 );

   if ( water_power >= MINIMUM_WATER_FOR_TURBO )
      {
      if ( pm_lastruntime > WATER_TURBO_TIME )
         {
         forwardmove *= WATER_TURBO_SPEED;
         //speed *= WATER_TURBO_SPEED;
         }
      }

   velocity = yaw_forward * forwardmove - yaw_left * sidemove;
   distance = velocity.length();
   velocity *= speed / distance;
   time = distance / speed;
   velocity[ 2 ] = sv_gravity->integer * time * 0.5f;

   airspeed = distance;

   // make sure the player leaves the ground
   client->ps.walking = qfalse;
   }

void Player::StartFakePlayer
   (
   void
   )
   {
   Actor * fake;

   // 
   // if we don't have a fakePlayer active, no need to check
   //
   if ( !fakePlayer_active )
      {
      return;
      }

   fakePlayer_active = qfalse;

   fakePlayer = new Actor;

   if ( !fakePlayer )
      return;

   fake = fakePlayer;

   CloneEntity( fake, this );

   fake->SetTargetName( "fakeplayer" );
   fake->ProcessEvent( EV_Actor_AIOff );

   // make sure it thinks so that it can fall when necessary
   fake->flags |= FL_THINK;

	// Make the fake player a stepsize shorter to prevent some collision issues

	fake->maxs[2] -= STEPSIZE;
	fake->setSize( mins, maxs );

	fake->takedamage = DAMAGE_NO;

   // hide the player
   this->hideModel();
	this->ProcessEvent( EV_Sentient_TurnOffShadow );
   //
   // immobolize the player
   //
   this->flags |= FL_IMMOBILE;
   // make the player not solid
   setSolidType( SOLID_NOT );

   // let the scripts now we are ready
   PostEvent( EV_Player_Done, 0 );
   }

void Player::FakePlayer
   (
   qboolean holster
   )
   {
   //
   // make sure we don't have one already
   //
   if ( fakePlayer )
      {
      return;
      }

   fakePlayer_active = qtrue;

   // if we are in the holster state, wait until next frame
   // if we aren't process immediately
   if ( !holster )
      {
      StartFakePlayer();
      }
   else
      {
      if ( WeaponsOut() )
         {
         SafeHolster( qtrue );
         }
      }
   }

void Player::RemoveFakePlayer
   (
   void
   )
   {
   Actor * fake;

   //
   // make sure we have one
   //
   if ( !fakePlayer )
      {
      return;
      }
   fake = fakePlayer;

   //
   // warp the real player to the fakeplayer location
   //
   this->setOrigin( fake->origin );
   this->setAngles( fake->angles );
   this->SetViewAngles( fake->angles );
   // show the player
   this->showModel();
	this->ProcessEvent( EV_Sentient_TurnOnShadow );
   // allow the player to move
   this->flags &= ~FL_IMMOBILE;
   // make the player solid
   setSolidType( SOLID_BBOX );
   // remove the fake
   fake->PostEvent ( EV_Remove, 0.f );
   // null out the fake player
   fakePlayer = NULL;
   SafeHolster( qfalse );
   }

void Player::SetViewAngles
   (
   Vector newViewangles
   )

   {
	// set the delta angle
	client->ps.delta_angles[0] = ANGLE2SHORT( newViewangles.x - client->cmd_angles[0] );
	client->ps.delta_angles[1] = ANGLE2SHORT( newViewangles.y - client->cmd_angles[1] );
	client->ps.delta_angles[2] = ANGLE2SHORT( newViewangles.z - client->cmd_angles[2] );

   v_angle = newViewangles;

   // get the pitch and roll from our leg angles
   newViewangles.x = angles.x;
   newViewangles.z = angles.z;
   AnglesToMat( newViewangles, orientation );
   yaw_forward = orientation[ 0 ];
   yaw_left = orientation[ 1 ];

   MatrixTransformVector( base_righthand_pos, orientation, righthand_pos );
   MatrixTransformVector( base_lefthand_pos, orientation, lefthand_pos );
   MatrixTransformVector( base_rightfoot_pos, orientation, rightfoot_pos );
   MatrixTransformVector( base_leftfoot_pos, orientation, leftfoot_pos );
   righthand_pos += origin;
   lefthand_pos += origin;
   rightfoot_pos += origin;
   leftfoot_pos += origin;
   }

void Player::DumpState
   (
   Event *ev
   )

   {
   gi.DPrintf( "Legs: %s Torso: %s\n", currentState_Legs ? currentState_Legs->getName() : "NULL", currentState_Torso->getName() );
   }

void Player::ForceTorsoState
   (
   Event *ev
   )

   {
   State *ts = statemap_Torso->FindState( ev->GetString( 1 ) );
   EvaluateState( ts );
   }

float Player::GetWaterPower
   (
   void
   )

   {
   return water_power;
   }

void Player::SetWaterPower
   (
   float w
   )

   {
   float diff;

   ScriptVariable * var;


   // Clamp the water
   if ( w < 0 )
      w = 0;

   if ( w > max_water_power )
      w = max_water_power;

   diff = w - water_power;
   water_power = w;

   // shift the player because they picked up the water
   diff *= 16.0f / 100.0f;
   if ( diff > 1.0f )
      diff = 1.0f;
   else if ( diff < 0 )
      diff = 0;

   if ( diff > 0 )
      {
      SetOffsetColor( 0, 0, diff, diff * 2 );
      }

   //
   // set our level variables
   //
   var = levelVars.GetVariable( "playerammo_edenwater" );
   if ( !var )
      {
      levelVars.SetVariable( "playerammo_edenwater", water_power );
      }
   else
      {
      var->setIntValue( water_power );
      }

   oldstats[STAT_WATER_LEVEL] = 0;
   UpdateWeapons();
   }

void Player::TouchedUseAnim
   (
   Entity * ent
   )
   {
   toucheduseanim = ent;
   }

void Player::ChangeOutfit
   (
   Event *ev
   )
   {
   int stage = ev->GetInteger( 1 );

	SetOutfit( stage );
   }

void Player::SetOutfit
   (
   int stage
   )
   {
   // cancel any pending outfit changes
   CancelEventsOfType( EV_Player_ChangeOutfit );

	outfit_level = stage;

   SurfaceCommand( "armpad*", "+nodraw" );
   SurfaceCommand( "holster*", "+nodraw" );
   SurfaceCommand( "pouch", "+nodraw" );
   SurfaceCommand( "kneepad*", "+nodraw" );
   SurfaceCommand( "shoulderpad*", "+nodraw" );
   SurfaceCommand( "glasses", "+nodraw" );
   switch( stage )
      {
      case 5:
         SurfaceCommand( "glasses", "-nodraw" );
      case 4:
         SurfaceCommand( "shoulderpad*", "-nodraw" );
      case 3:
         SurfaceCommand( "kneepad*", "-nodraw" );
      case 2:
         SurfaceCommand( "armpad*", "-nodraw" );
      case 1:
         SurfaceCommand( "holster*", "-nodraw" );
         SurfaceCommand( "pouch", "-nodraw" );
      case 0:
         break;
      }
   }

int Player::GetOutfit
   (
   void
   )
   {
	return outfit_level;
	}

void Player::ClearLeftArmTarget
   (
   Event *ev
   )

   {
   left_arm_target = NULL;
   }

void Player::ClearRightArmTarget
   (
   Event *ev
   )

   {
   right_arm_target = NULL;
   }

void Player::AdjustTorso
   (
   Event *ev
   )

   {
   adjust_torso = ev->GetBoolean( 1 );
   }

void Player::UseDualWield
   (
   Event *ev
   )

   {
   // This is triggered by the state machine.
   // If there is a weapon in the dual wield list, use it, then remove it from the list.
   if ( dual_wield_weaponlist.NumObjects() )
      {
      DualWieldWeapon *dw;

      dw = dual_wield_weaponlist.ObjectAt( 1 );

      useWeapon( dw->name, dw->hand );
      dual_wield_weaponlist.RemoveObjectAt( 1 );
      delete dw;
      }
   else
      {
      dual_wield_active = qfalse;  // We are done wielding all the weapons
      }
   }

void Player::DualWield
   (
   Event *ev
   )

   {
   str      leftweap, rightweap;
   Weapon   *leftactweap, *rightactweap, *dualactweap;

   leftweap  = ev->GetString( 1 );
   rightweap = ev->GetString( 2 );

   // Set the putaway flags on any active weapons
   leftactweap  = GetActiveWeapon( WEAPON_LEFT );
   rightactweap = GetActiveWeapon( WEAPON_RIGHT );
   dualactweap  = GetActiveWeapon( WEAPON_DUAL );

   // Check for any dual handed weapon being out, and mark it for putaway
   if ( dualactweap )
      {
      dualactweap->SetPutAway( qtrue );
      }

   // if the left and right weapons are already out, then holster them both
   if (
        ( leftactweap && !leftweap.icmp( leftactweap->getName() ) ) &&
        ( rightactweap && !rightweap.icmp( rightactweap->getName() ) )
      )
      {
      leftactweap->SetPutAway( qtrue );
      rightactweap->SetPutAway( qtrue );
      return;
      }

   DualWieldWeapon *dualweap;

   // Putaway the old weapons, and add the new ones to the dual_wield list
   if ( !leftactweap )
      {
      dualweap = new DualWieldWeapon;
      dualweap->name = leftweap;
      dualweap->hand = WEAPON_LEFT;
      dual_wield_weaponlist.AddObject( dualweap );
      }
   else if ( leftweap.icmp( leftactweap->getName() ) )
      {
      leftactweap->SetPutAway( qtrue );

      dualweap = new DualWieldWeapon;
      dualweap->name = leftweap;
      dualweap->hand = WEAPON_LEFT;
      dual_wield_weaponlist.AddObject( dualweap );
      }

   if ( !rightactweap )
      {
      dualweap = new DualWieldWeapon;
      dualweap->name = rightweap;
      dualweap->hand = WEAPON_RIGHT;
      dual_wield_weaponlist.AddObject( dualweap );
      }
   else if ( rightweap.icmp( rightactweap->getName() ) )
      {
      rightactweap->SetPutAway( qtrue );

      dualweap = new DualWieldWeapon;
      dualweap->name = rightweap;
      dualweap->hand = WEAPON_RIGHT;
      dual_wield_weaponlist.AddObject( dualweap );
      }

   dual_wield_active = qtrue;
   }

void Player::EvaluateTorsoAnim
   (
   Event *ev
   )

   {
   str torsoAnim( currentState_Torso->getTorsoAnim( *this, &torso_conditionals ) );

   if ( torsoAnim == "" )
      {
      partAnim[ torso ] = "";
      ClearTorsoAnim();
      }
   else if ( torsoAnim != "none" )
      {
      SetAnim( torsoAnim.c_str(), torso );
      }
   }

void Player::NextPainTime
   (
   Event *ev
   )

   {
   nextpaintime = level.time + ev->GetFloat( 1 );
   pain_type    = MOD_NONE;
   pain         = 0;
   }

void Player::SetMouthAngle
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
		SetControllerTag( MOUTH_TAG, tag_num );

		mouth_angles = vec_zero;
		mouth_angles[PITCH] = max_mouth_angle * angle_percent;

		SetControllerAngles( MOUTH_TAG, mouth_angles );
		}
	}

void Player::EnterVehicle
	(
	Event *ev
	)

	{
	Entity *ent;

	ent = ev->GetEntity( 1 );
	if ( ent && ent->isSubclassOf( Vehicle ) )
		{
      flags |= FL_PARTIAL_IMMOBILE;
      viewheight = STAND_EYE_HEIGHT;
      velocity = vec_zero;
		vehicle = ( Vehicle * )ent;
      if ( vehicle->IsDrivable() )
   		setMoveType( MOVETYPE_VEHICLE );
      else
   		setMoveType( MOVETYPE_NOCLIP );
		}
	}

void Player::ExitVehicle
	(
	Event *ev
	)

	{
   flags &= ~FL_PARTIAL_IMMOBILE;
	setMoveType( MOVETYPE_WALK );
	vehicle = NULL;
	}

qboolean Player::WeaponsOut
   (
   void
   )

   {
   return ( GetActiveWeapon( WEAPON_LEFT ) || GetActiveWeapon( WEAPON_RIGHT ) || GetActiveWeapon( WEAPON_DUAL ) );
   }

void Player::Holster
   (
   qboolean putaway
   )

   {
   Weapon   *leftWeap, *rightWeap, *dualWeap;

   leftWeap  = GetActiveWeapon( WEAPON_LEFT );
   rightWeap = GetActiveWeapon( WEAPON_RIGHT );
   dualWeap  = GetActiveWeapon( WEAPON_DUAL );

   // Holster
   if ( leftWeap || rightWeap || dualWeap )
      {
      if ( putaway )
         {
         if ( leftWeap )
            {
            leftWeap->SetPutAway( qtrue );
            holsteredWeapons[WEAPON_LEFT] = leftWeap;
            }
         if ( rightWeap )
            {
            rightWeap->SetPutAway( qtrue );
            holsteredWeapons[WEAPON_RIGHT] = rightWeap;
            }
         if ( dualWeap )
            {
            dualWeap->SetPutAway( qtrue );
            holsteredWeapons[WEAPON_DUAL] = dualWeap;
            }
      
         // Set a level var so the script can know if the player is going to holster
         levelVars.SetVariable( "holster_active", 1 );
         }
      }
   else
      {
      if ( !putaway )
         {
         // Unholster
         if ( holsteredWeapons[WEAPON_DUAL] )
            {
            useWeapon( holsteredWeapons[WEAPON_DUAL], WEAPON_DUAL );
            }
         else if ( holsteredWeapons[WEAPON_LEFT] && holsteredWeapons[WEAPON_RIGHT] )
            {
            Event *ev1;

            ev1 = new Event( EV_Player_DualWield );
            ev1->AddString( holsteredWeapons[WEAPON_LEFT]->getName() );
            ev1->AddString( holsteredWeapons[WEAPON_RIGHT]->getName() );
            ProcessEvent( ev1 );
            }
         else if ( holsteredWeapons[WEAPON_RIGHT] )
            {
            useWeapon( holsteredWeapons[WEAPON_RIGHT], WEAPON_RIGHT );
            }
         else if ( holsteredWeapons[WEAPON_LEFT] )
            {
            useWeapon( holsteredWeapons[WEAPON_LEFT], WEAPON_LEFT );
            }

         holsteredWeapons[WEAPON_LEFT]  = NULL;
         holsteredWeapons[WEAPON_RIGHT] = NULL;
         holsteredWeapons[WEAPON_DUAL]  = NULL;
         // Set a level var to let the script know there is no holstering
         levelVars.SetVariable( "holster_active", 0 );      
         }
      }
   }

void Player::SafeHolster
   (
   qboolean putaway
   )
   {
   if ( WeaponsOut() )
      {
      if ( putaway )
         {
         weapons_holstered_by_code = qtrue;
         Holster( qtrue );
         }
      }
   else
      {
      if ( putaway )
         {
         if ( !fakePlayer_active )
            {
            WeaponsHolstered();
            }
         }
      else
         {
         if ( weapons_holstered_by_code )
            {
            weapons_holstered_by_code = qfalse;
            Holster( qfalse );
            }
         }
      }
   }

void Player::WeaponsNotHolstered
   ( 
   void 
   )
   {
   }

void Player::WeaponsHolstered
   ( 
   void 
   )
   {
   }

void Player::HolsterToggle
   (
   Event *ev
   )

   {
   if ( WeaponsOut() )
      {
      Holster( qtrue );
      }
   else
      {
      Holster( qfalse );
      }
   }

void Player::Holster
   (
   Event *ev
   )

   {
   SafeHolster( ev->GetBoolean( 1 ) );
   }

void Player::GrabRope
   (
   Entity * ent
   )
   {
   rope_grabbed = ( Rope * )ent;
   }

void Player::TouchRope
   (
   Entity * ent
   )
   {
   rope_touch = ( Rope * )ent;
   }

qboolean Player::OnRope
   (
   void
   )
   {
   return ( rope_grabbed != NULL );
   }

void Player::SetWaterPower
	(
	Event *ev
	)

	{
   SetWaterPower( ev->GetInteger( 1 ) );
	}

void Player::IncreaseActionLevel
   (
   float action_level_increase
   )
   {
   action_level += action_level_increase;
   }

void Player::WatchActor
	(
	Event *ev
	)

	{
	if ( camera || currentState_Torso->getCameraType() != CAMERA_BEHIND )
		return;

	actor_to_watch = (Actor *)ev->GetEntity( 1 );
	}

void Player::StopWatchingActor
	(
	Event *ev
	)

	{
	Actor *old_actor;

	old_actor = (Actor *)ev->GetEntity( 1 );

	if ( old_actor == actor_to_watch )
		actor_to_watch = NULL;
	}

void Player::setAngles
	(
	Vector ang
	)

	{
   // set the angles normally
   Entity::setAngles( ang );

   // set the orientation based off of the current view, also update our yaw_forward and yaw_left
   ang[ YAW ] = v_angle[ YAW ];
   AnglesToMat( ang, orientation );
   yaw_forward = orientation[ 0 ];
   yaw_left = orientation[ 1 ];
	}

void Player::WeaponCommand
   (
   Event *ev
   )

   {
   weaponhand_t   hand;
   Weapon         *weap;
   int            i;

   if ( ev->NumArgs() < 2 )
      return;

   hand = WeaponHandNameToNum( ev->GetString( 1 ) );
   weap = GetActiveWeapon( hand );

   if ( !weap )
      return;

   Event *e;
   e = new Event( ev->GetToken( 2 ) );

   for( i=3; i<=ev->NumArgs(); i++ )
      e->AddToken( ev->GetToken( i ) );

   weap->ProcessEvent( e );
   }

qboolean TryPush
	(
	int entnum,
	vec3_t move_origin,
	vec3_t move_end
	)

	{
	Actor *act;
	Vector dir;
	Vector dir2;
	Entity *ent;

	if ( entnum == ENTITYNUM_NONE )
		return false;

	ent = G_GetEntity( entnum );

	if ( ent->isSubclassOf( Actor ) )
		{
		act = (Actor *) ent;

		dir = act->origin - move_origin;
		dir.z = 0;
		dir.normalize();

		dir2 = move_end;
		dir2 -= move_origin;

		if ( act->flags & FL_FLY )
			{
			dir *= dir2.length() / 2;

			if ( act->Push( dir ) )
				return true;
			}
		else
			{
			dir *= dir2.length();

			Event *event = new Event( EV_Actor_Push );
			event->AddVector( dir );
			act->PostEvent( event, 0 );
			}
		}

	return false;
	}

void Player::PlayerDone
   (
   Event *ev
   )

   {
   // This is used to let scripts know that the player is done doing something

   // let any threads waiting on us know they can go ahead
   Director.PlayerSpawned();
   }

painDirection_t Player::Pain_string_to_int
   (
   str pain
   )

   {
   if ( !pain.icmp( pain, "Front" ) )
      return PAIN_FRONT;
   else if ( !pain.icmp( pain, "Left" ) )
      return PAIN_LEFT;
   else if ( !pain.icmp( pain, "Right" ) )
      return PAIN_RIGHT;
   else if ( !pain.icmp( pain, "Rear" ) )
      return PAIN_REAR;
   else 
      return PAIN_NONE;
   }

void Player::ArchivePersistantData
   (
	Archiver &arc
   )

   {
   int i;
	str model_name;

   Sentient::ArchivePersistantData( arc );
 
   arc.ArchiveFloat( &water_power );
   arc.ArchiveFloat( &max_water_power );

	arc.ArchiveInteger( &outfit_level );

	model_name = g_playermodel->string;

	arc.ArchiveString( &model_name );

	if ( arc.Loading() )
		{
      // set the cvar
      gi.cvar_set( "g_playermodel", model_name.c_str() );

		model_name += ".tik";
		setModel( model_name.c_str() );

		Event *event = new Event( EV_Player_ChangeOutfit );
		event->AddInteger( outfit_level );
		PostEvent( event, FRAMETIME * 3 );
		}

   for( i = 0; i < MAX_ACTIVE_WEAPONS; i++ )
      {
      str name;
      if ( arc.Saving() )
         {
         if ( holsteredWeapons[ i ] )
            {
            name = holsteredWeapons[ i ]->getName();
            }
         else
            {
            name = "none";
            }
         }
      arc.ArchiveString( &name );
      if ( arc.Loading() )
         {
         if ( name != "none" )
            {
            holsteredWeapons[ i ] = ( Weapon * )FindItem( name );
            }
         }
      }
   UpdateWeapons();
   // Force a re-evaluation of the player's state
   LoadStateTable();
   }

void Player::SpawnDamageEffect
   (
   meansOfDeath_t mod
   )

   {
   switch ( mod )
      {
      case MOD_ELECTRIC:
		case MOD_ELECTRICWATER:
         {
         SpawnEffect( "fx_elecstrike.tik", origin );
			Sound( "sound/weapons/sword/electric/hitmix2.wav", 0 );
         }
      default:
         {
         }
      }
   }

void Player::ActivateDualWeapons
   (
   Event *ev
   )

   {
   int i;

   for ( i=dual_wield_weaponlist.NumObjects(); i>=1; i-- )
      {
      DualWieldWeapon   *dw;
      Weapon            *weapon;

      dw = dual_wield_weaponlist.ObjectAt( i );

      weapon = ( Weapon * )FindItem( dw->name );

      // Check to see if player has the weapon
      if ( !weapon )
         {
         warning( "Player::ActivateDualWeapons", "Player does not have weapon %s", dw->name );
         return;
         }

      ChangeWeapon( weapon, dw->hand );
      dual_wield_weaponlist.RemoveObjectAt( i );
      delete dw;
      }

   // Check for water and ammo
   UpdateWeapons();

   // Clear out the newActiveWeapon
   ClearNewActiveWeapon();

   // Clear out the holstered weapons
   holsteredWeapons[WEAPON_LEFT]  = NULL;
   holsteredWeapons[WEAPON_RIGHT] = NULL;
   holsteredWeapons[WEAPON_DUAL]  = NULL;

   // let the player know that our weapons are not holstered
   WeaponsNotHolstered();
   }

void Player::VelocityModified
	(
   void
	)
	{
   if ( velocity.z > 32 )
      {
      do_rise = qtrue;
      }
	}

int Player::GetKnockback
	(
   int original_knockback,
	qboolean blocked
	)
	{
	int new_knockback;

	new_knockback = original_knockback;

	// If blocked, absorb some of the knockback

	if ( blocked )
		{
		if ( LargeShieldActive() ) 
			new_knockback -= 150;
		else
			new_knockback -= 50;
		}

	// See if we still have enough knockback to knock the player down

	if ( new_knockback >= 200 && take_pain )
		{
		knockdown = true;

		if ( blocked )
			{
			float damage;

			damage = new_knockback / 50;

			if ( damage > 10 )
				damage = 10;

			Damage( world, world, damage, origin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_CRUSH );
			}
		}

	// Make sure knockback is still at least 0

	if ( new_knockback < 0 )
		new_knockback = 0;

	return new_knockback;
	}
 
void Player::ResetHaveItem
   ( 
   Event *ev
   )
	{
   str fullname;
   ScriptVariable * var;

   fullname = str( "playeritem_" ) + ev->GetString( 1 );

   var = gameVars.GetVariable( fullname.c_str() );

   if ( var )
		var->setIntValue( 0 );
	}

void Player::ReceivedItem
   ( 
   Item * item 
   )
	{
   qboolean forced;
   qboolean first;
   str fullname;
   str dialog;
   str anim;
   ScriptVariable * var;

   //
   // set our global game variables
   //

   fullname = str( "playeritem_" ) + item->getName();

   first = qtrue;

   var = gameVars.GetVariable( fullname.c_str() );
   if ( !var )
      {
      gameVars.SetVariable( fullname.c_str(), 1 );
      }
   else
      {
      int amount;

      amount = var->intValue() + 1;
      var->setIntValue( amount );
      //
      // if we just received it, let the player know
      //
      if ( amount > 1 )
         {
         first = qfalse;
         }
      }

   var = levelVars.GetVariable( fullname.c_str() );
   if ( !var )
      {
      levelVars.SetVariable( fullname.c_str(), 1 );
      }
   else
      {
      int amount;

      amount = var->intValue() + 1;
      var->setIntValue( amount );
      }

   if ( item->IsItemCool( &dialog, &anim, &forced ) )
      {
      if ( first || forced )
         {
         cool_item = item;
         cool_dialog = dialog;
         cool_anim = anim;
         }
      }
   }

void Player::RemovedItem
   ( 
   Item * item 
   )
	{
   str fullname;
   ScriptVariable * var;

   //
   // set our global game variables if client
   //

   fullname = str( "playeritem_" ) + item->getName();

   var = levelVars.GetVariable( fullname.c_str() );
   if ( var )
      {
      int amount;

      amount = var->intValue() - 1;
      if ( amount < 0 )
         amount = 0;
      var->setIntValue( amount );
      }

	var = gameVars.GetVariable( fullname.c_str() );
   if ( var )
      {
      int amount;

      amount = var->intValue() - 1;
      if ( amount < 0 )
         amount = 0;
      var->setIntValue( amount );
      }
   }

void Player::AmmoAmountChanged
   ( 
   Ammo * ammo,
   int ammo_in_clip
   )
   {
   str fullname;
   ScriptVariable * var;

   //
   // set our level variables
   //
   fullname = str( "playerammo_" ) + ammo->getName();

   var = levelVars.GetVariable( fullname.c_str() );
   if ( !var )
      {
      levelVars.SetVariable( fullname.c_str(), ammo->getAmount() + ammo_in_clip );
      }
   else
      {
      var->setIntValue( ammo->getAmount() + ammo_in_clip );
      }
   }


void Player::StartCoolItem
	(
	Event *ev
	)
	{
   // turn off ai off during the cinematic
   level.ai_on = qfalse;
   // make sure we don't take damage during this time
   takedamage = DAMAGE_NO;
   // freeze the player
   level.playerfrozen = qtrue;
   // turn on cinematic mode
   G_StartCinematic();

   assert( ( Camera * )cool_camera == NULL );
   // start playing the success music
   if ( music_current_mood != mood_success )
      {
      ChangeMusic( "success", MusicMood_NumToName( music_current_mood ), qfalse );
      }

   // create an orbit cam
   cool_camera = new Camera();
   cool_camera->SetOrbitHeight( 150 );
   cool_camera->Orbit( this, 200, this, -90 );
   cool_camera->Cut( NULL );
   SetCamera( cool_camera, 1 );
   }

void Player::ShowCoolItem
	(
	Event *ev
	)
	{
   Animate * fx;
   Vector org;

   org = origin;
   org.z += 128;

	fx = new Animate;

	fx->setOrigin( org );
	fx->setModel( "fx_coolitem.tik" );
	fx->RandomAnimate( "idle" );
	fx->PostEvent( EV_Remove, 1 );

   if ( cool_item )
      {
      cool_item->setOrigin( org );
      cool_item->PostEvent( EV_Show, 0.1f );
      // place a lens flare on the object
      cool_item->edict->s.renderfx |= RF_VIEWLENSFLARE;

      if ( cool_dialog.length() )
         {
		   Sound( cool_dialog, CHAN_DIALOG );
         }
      }
   }

void Player::HideCoolItem
	(
	Event *ev
	)
	{
   Animate * fx;
   Vector org;

   org = origin;
   org.z += 128;

	fx = new Animate;

	fx->setOrigin( org );
	fx->setModel( "fx_coolitem_reverse.tik" );
	fx->RandomAnimate( "idle" );
	fx->PostEvent( EV_Remove, 1 );

   if ( cool_item )
      {
      Event * event;

      cool_item->PostEvent( EV_Hide, 1.0f );

      event = new Event( EV_SetOrigin );
      event->AddVector( vec_zero );
      cool_item->PostEvent( event, 1.0f );
      // remove the lens flare on the object
      cool_item->edict->s.renderfx &= ~RF_VIEWLENSFLARE;
      }
   }

void Player::StartCoolItemAnim
	(
   void
	)
	{
   movecontrol = MOVECONTROL_ABSOLUTE;

   if ( cool_item && cool_anim.length() )
      {
      SetAnim( cool_anim, legs );
      // clear out anim till next time
      cool_anim = "";
      }
   }

void Player::StopCoolItem
	(
	Event *ev
	)
	{
   if ( cool_item && cool_anim.length() )
      {
      State * newState;

      newState = statemap_Torso->FindState( "DO_COOL_ITEM_ANIM" );
      if ( newState )
         {
         currentState_Torso = newState;
         return;
         }
      }

   // turn ai back on
   level.ai_on = qtrue;

   // turn damage back on
   takedamage = DAMAGE_AIM;

   // unfreeze the player
   level.playerfrozen = qfalse;

   // turn off cinematic mode
   G_StopCinematic();

   cool_item = NULL;

   // delete our camera
   if ( cool_camera )
      {
      SetCamera( NULL, 1 );
      delete cool_camera;
      cool_camera = NULL;
      }
   }

void Player::WaitForState
	(
	Event *ev
	)
	{
   waitForState = ev->GetString( 1 );
   }


void Player::SetDamageMultiplier
	(
	Event *ev
	)
	{
	damage_multiplier = ev->GetFloat( 1 );
	}

void Player::SetTakePain
   (
   Event *ev
   )

   {
   take_pain = ev->GetBoolean( 1 );
   }

void Player::Loaded
   (
   void
   )

   {
   UpdateWeapons();
   }

void Player::PlayerShowModel
   (
   Event *ev
   )

   {
   Entity::showModel();
	UpdateWeapons();
   }

void Player::showModel
   (
   void
   )

   {
   Entity::showModel();
	UpdateWeapons();
   }

//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/sentient.cpp                       $
// $Revision:: 178                                                            $
//   $Author:: Markd                                                          $
//     $Date:: 7/31/00 1:34a                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/sentient.cpp                            $
// 
// 178   7/31/00 1:34a Markd
// made circle of protection sometimes bleed
// 
// 177   7/29/00 1:27p Steven
// Made damage color have a minimum amount (if any) and made sure fire and
// lifedrain don't make blocked sparks.
// 
// 176   7/28/00 1:24p Steven
// Added some eat means of death stuf and made blood splat on ground work a
// little better.
// 
// 175   7/28/00 8:36a Steven
// When sure player updated all weapons when all of them are attached.
// 
// 174   7/27/00 10:54p Steven
// Added means of death eat and fixed another ammo bug.
// 
// 173   7/25/00 10:44a Steven
// Fixed some bad ammo bugs and now play the decap sound whenever bloody gibs
// are spawned.
// 
// 172   7/23/00 8:49p Aldie
// Added some safety nets to the weapon code in sentient and player
// 
// 171   7/22/00 8:37p Steven
// Made armor and water not absorb lifedrain damage.
// 
// 170   7/22/00 3:02p Steven
// Fixed fire catching person of fire forever.
// 
// 169   7/22/00 1:22p Steven
// Reworked life drain damage on actors.
// 
// 168   7/19/00 8:19p Steven
// Added gas blockable means of death.
// 
// 167   7/19/00 6:22p Steven
// Made the takeItem proc not delete the ammo but just set the amount to 0.
// 
// 166   7/19/00 5:10p Steven
// Added electric water means of death and made actors not be able to block
// explosions.
// 
// 165   7/18/00 4:27p Steven
// Made sure on_fire damage comes from the person that set the fire.
// 
// 164   7/17/00 2:57p Steven
// Made large shield block more, made lava damage unblockable, and made on_fire
// hurt actors more.
// 
// 163   7/16/00 4:37p Steven
// Added new fire means of death.
// 
// 162   7/15/00 12:48p Steven
// Made people immune to fire they start.
// 
// 161   7/14/00 7:08p Steven
// Hopefully fixed a death problem.
// 
// 160   7/14/00 4:43p Steven
// Made lava damage not cause blood or gibs.
// 
// 159   7/13/00 7:30p Aldie
// Added ability to take ammo in TakeItem code
// 
// 158   7/13/00 6:53p Steven
// Fixed some means of death stuff.
// 
// 157   7/13/00 3:09p Markd
// changed water conversion factor back to 1
// 
// 156   7/13/00 12:32p Steven
// Don't try to remove falling immunity if sentient is not immune to it, added
// means of death poison, and made blood splats on ground not happen every
// time.
// 
// 155   7/12/00 5:36p Markd
// fixed ammo reporting to support bullets in clip
// 
// 154   7/12/00 11:37a Steven
// Added a CanBlock function to determined which means of death can be blocked.
// 
// 153   7/10/00 9:27p Markd
// added ammo variables for how much ammo the player has.  Added levelvars and
// gamevars commands
// 
// 152   7/10/00 8:09p Markd
// fixed cool item pickup problems
// 
// 151   7/10/00 5:16p Markd
// Changed the way that water works, it still absorbs 25% damage but only uses
// up 50% of the water
// 
// 150   7/10/00 5:07p Steven
// Made it so knockback and water reduction doesn't happen if in god mode.
// 
// 149   7/07/00 6:35p Steven
// Don't set means of death when immune.
// 
// 148   7/06/00 9:24a Steven
// Added damage angles stuff and made sure lightsword was treated as a melee
// weapon.
// 
// 147   7/05/00 7:36p Steven
// Added armor pieces reducing damage.
// 
// 146   7/05/00 5:38p Steven
// Added water armor - damage = 25% armor/75% health.
// 
// 145   7/04/00 2:25p Markd
// added cool cinematic for new objects
// 
// 144   7/03/00 10:24a Steven
// Added some knockback/knockdown stuff.
// 
// 143   7/02/00 5:09p Steven
// Made gibs not get removed so quickly so the client always displays them.
// 
// 142   7/01/00 6:08p Steven
// Removed falling immunity when someone is knocked back and improved the
// immunity functions.
// 
// 141   7/01/00 2:41p Steven
// Added stop on fire event.
// 
// 140   7/01/00 2:01p Steven
// Added scale to spawn bloody gibs.
// 
// 139   7/01/00 12:02p Steven
// Added electricsword and plasmashotgun means of death.
// 
// 138   6/30/00 4:59p Steven
// Made catching on fire harder and not hurt as much.
// 
// 137   6/30/00 10:45a Markd
// added MOVETYPE_STATIONARY and revamped some physics
// 
// 136   6/29/00 6:24p Steven
// Balanced small gibs stuff a little.
// 
// 135   6/27/00 5:47p Steven
// Made sentient archive animate instead of entity.
// 
// 134   6/24/00 7:01p Steven
// Added code in giveItem to make sure the class created is an item.
// 
// 133   6/24/00 11:22a Steven
// Made slime not cause blood or gibs.
// 
// 132   6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 131   6/22/00 3:54p Steven
// Fixed blood spurts staying around way too long.
// 
// 130   6/21/00 5:27p Steven
// Made it so you can't block being on fire, made it so you wouldn't catch on
// fire if you blocked the attack, and made it so you wouldn't try to set the
// players waterlevel if you blocked a lifedrain attack.
// 
// 129   6/19/00 6:20p Steven
// Improved ShouldBleed a little.
// 
// 128   6/17/00 4:54p Aldie
// Added ability to check aliases for 'checkanimations' command
// 
// 127   6/17/00 3:48p Aldie
// 
// 126   6/17/00 10:42a Steven
// Bullet proofed and cleaned up SpawnBloodyGibs a little.
// 
// 125   6/15/00 6:54p Steven
// Commented out finishing move stuff.
// 
// 124   6/14/00 5:44p Steven
// Added nextbleedtime stuff.
// 
// 123   6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 122   6/13/00 6:46p Aldie
// Added some damage debug info.  Added an ignoreEnt for explosion events
// 
// 121   6/10/00 11:57a Aldie
// Use torsoAngles for shield blocking
// 
// 120   6/08/00 1:45p Steven
// Added minimum melee height stuff and added immortal stuff.
// 
// 119   6/07/00 5:35p Steven
// Made radiation damage not cause blood or gibs.
// 
// 118   6/06/00 2:37p Steven
// Added sting2 means of death.
// 
// 117   6/04/00 3:49p Markd
// Added precise shadows to certain characters
// 
// 116   6/03/00 3:14p Aldie
// Added damage effects to player and sentient 
// 
// 115   6/02/00 2:01p Markd
// Fixed client persistant data issues
// 
// 114   6/01/00 7:02p Markd
// removed activeWeapon variable
// 
// 113   6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 112   6/01/00 10:36a Steven
// Made it so the player doesn't gib unless enough damage is done.
// 
// 111   5/31/00 1:25p Steven
// Made falling not cause blood or gibs.
// 
// 110   5/30/00 6:55p Aldie
// Took a muzzleclear check out of Fire
// 
// 109   5/29/00 1:16p Markd
// 3rd round of saved games
// 
// 108   5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 107   5/25/00 1:48p Steven
// Moved the rest of the max_gibs stuff to sentient.
// 
// 106   5/25/00 10:00a Steven
// Added some scaling to blood spurts.
// 
// 105   5/24/00 3:14p Markd
// first phase of save/load games
// 
// 104   5/23/00 6:42p Steven
// Moved small gib stuff to sentient.
// 
// 103   5/19/00 11:24a Steven
// Changed gib names.
// 
// 102   5/15/00 11:20a Steven
// Made it so sentients will not bleed or spawn gibs when hit by a sling rock.
// 
// 101   5/11/00 4:59p Steven
// Made it so sentients that are immune to on_fire will not catch on fire.
// 
// 100   5/10/00 10:34a Steven
// Added com_blood stuff, made firesword catch people on fire also, and made it
// so on fire sentients could catche other sentients on fire.
// 
// 99    5/06/00 3:40p Steven
// Made player catch on fire half as likely and it only burns half as long.
// 
// 98    5/06/00 11:12a Aldie
// Added block effect and fixed some problems with ammo
// 
// 97    5/05/00 6:24p Steven
// Fixed the EV_RemoveAttachedModel event parms to be correct.
// 
// 96    5/05/00 2:16p Steven
// Added catch on fire stuff and made some means of death not make things gib
// as much.
// 
// 95    5/04/00 4:58p Markd
// Added RandomAnimate("Raise") to Activate Weapon
// 
// 94    5/04/00 2:20p Markd
// put in putaway animation into chainsword
// 
// 93    5/04/00 2:07p Steven
// More finishing move stuff.
// 
// 92    5/03/00 12:24p Steven
// Made it so SetAttackBlocked is called when the player blocks a sentients
// attack.
// 
// 91    4/29/00 2:04p Markd
// fixed crashbug
// 
// 90    4/28/00 2:40p Steven
// Added some more caching of blood stuff when a blood model is set.
// 
// 89    4/27/00 4:00p Aldie
// Fix for take command
// 
// 88    4/27/00 12:04p Steven
// Added crush_every_frame means of death.
// 
// 87    4/26/00 5:25p Aldie
// Changes to weapons to avoid having to specify the classname
// 
// 86    4/20/00 5:45p Steven
// Made flashbangs not cause blood or gibs.
// 
// 85    4/20/00 11:34a Steven
// Added green gibs.
// 
// 84    4/15/00 2:57p Steven
// Added blue blood stuff.
// 
// 83    4/15/00 11:51a Steven
// Added a TurnOnShadow event and added a bunch of blood stuff.
// 
// 82    4/14/00 7:12p Aldie
// Fixed some ammo checking bugs
// 
// 81    4/14/00 6:04p Aldie
// Fix for charging where we should save off the frame and anim
// 
// 80    4/12/00 6:58p Steven
// Added lifedrain means of death and made it so even if the sentient is immune
// the meansofdeath is still set and a pain event is still sent.
// 
// 79    4/10/00 6:07p Steven
// Made it so means of death is set when hitting dead sentients also.
// 
// 78    4/10/00 4:54p Aldie
// Put health assignment back into sentient
// 
// 77    4/10/00 11:28a Aldie
// Added weapon attaching to the sentients
// 
// 76    4/10/00 11:18a Markd
// Added new rope code
// 
// 75    4/07/00 3:52p Steven
// Fixed a crash in giveWeapon and made it so hitting a dead sentient starts a
// blood spurt and sends a pain event.
// 
// 74    4/05/00 8:50p Markd
// got rid of damage skin support
// 
// 73    4/01/00 3:45p Markd
// added FL_TOUCH_TRIGGERS flag and implementation
// 
// 72    3/22/00 6:45p Aldie
// Added some checks to prevent firing through walls
// 
// 71    3/20/00 6:10p Steven
// Added SetMouthAngle event and max_mouth_angle stuff.
// 
// 70    3/18/00 1:16p Steven
// Added position to pain event.
// 
// 69    3/13/00 5:18p Aldie
// Made some changes for usable inventory item stuff
// 
// 68    3/11/00 4:11p Steven
// Added direction to pain event.
// 
// 67    3/11/00 2:16p Steven
// Added stun stuff (so the AI knows when the player is incapable of doing
// anything :)
// 
// 66    3/03/00 5:07p Steven
// Capped off the damage time at 2 seconds.
// 
// 65    3/02/00 4:43p Aldie
// Added some ammo functionality for the HUD
// 
// 64    2/26/00 12:01p Steven
// Took out unlimited life hack.
// 
// 63    2/24/00 4:18p Jimdose
// removed some unused variables
// 
// 62    2/20/00 2:56p Aldie
// Added shield impact function, and added check for getting hit in the front
// arc to see if shield blocks.
// 
// 61    2/18/00 6:29p Aldie
// Added a call to animate the shield if it gets impacted
// 
// 60    2/17/00 6:26p Aldie
// Fixed naming conventions for weapon hand and also added various attachtotag
// functionality for weapons that attach to different tags depending on which
// hand they are wielded in.
// 
// 59    2/17/00 12:00p Aldie
// Added command processing to state system with the addition of entrycommands
// and exitcommands.
// 
// 58    2/16/00 4:01p Aldie
// Added shield functionality
// 
// 57    2/09/00 8:02p Aldie
// Added loopfire weapons
// 
// 56    2/09/00 6:47p Steven
// Made it so I know what type of attack an actor just blocked.
// 
// 55    2/09/00 5:39p Aldie
// Water armor damage reduction
// 
// 54    2/08/00 6:35p Aldie
// Added more blocking code to player and sentient
// 
// 53    2/08/00 11:59a Steven
// Added stuff to let actor know he had blocked a hit.
// 
// 52    2/07/00 7:38p Aldie
// Fixed swiping, also various weapons fixes for sword and for sling
// 
// 51    2/04/00 7:46p Aldie
// Fixed typo
// 
// 50    2/04/00 7:28p Aldie
// Combat code - blocking and combos
// 
// 49    2/04/00 3:11p Aldie
// Changed sword attack method for water usage
// 
// 48    2/04/00 11:48a Aldie
// Fixed ammo inventory free bug
// 
// 47    2/04/00 11:17a Aldie
// Clear out the ammo inventory when a sentient is destroyed
// 
// 46    2/03/00 2:56p Aldie
// Sword and water coding
// 
// 45    2/02/00 7:08p Aldie
// Added new sword code and water damage
// 
// 44    1/29/00 6:17p Aldie
// Fixed some problems when state doesn't exist.
// 
// 43    1/29/00 12:32p Jimdose
// removed ImpactDamage
// 
// 42    1/27/00 11:48a Aldie
// Added player command and takeweapon
// 
// 41    1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 40    1/26/00 12:03p Markd
// added back old lighting code for certain objects in the game
// 
// 39    1/22/00 3:38p Aldie
// Fixed some weapons code
// 
// 38    1/21/00 2:32p Steven
// Fixed the tag for the resurrect special effect for the player.
// 
// 37    1/20/00 6:54p Aldie
// Removed bloodsplats until we do them the right way
// 
// 36    1/18/00 6:49p Aldie
// Added a warning message for firing weapons that aren't active
// 
// 35    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 34    1/14/00 5:07p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 33    1/14/00 4:22p Steven
// Added a remove immunity event.
// 
// 32    1/07/00 8:12p Jimdose
// cleaning up unused code
// 
// 31    1/06/00 7:01p Steven
// Made it so sentients get knocked back even if they block the attack.
// 
// 30    1/06/00 4:39p Markd
// fixed tiki file name
// 
// 29    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 28    1/05/00 6:45p Steven
// Made it so blocking only blocks the front 90 degrees.
// 
// 27    12/22/99 5:16p Steven
// Added some variables to keep track when sentients are melee attacking or
// blocking.
// 
// 26    12/20/99 6:51p Steven
// Moved jumpxy to sentient.
// 
// 25    12/17/99 8:27p Jimdose
// got rid of unused vars and functions
// 
// 24    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 23    12/14/18 2:43p Jimdose
// moved blood_model from Entity
// 
// 22    12/07/99 6:09p Aldie
// Added weapon charging
// 
// 21    12/03/99 7:02p Aldie
// More ammo joy
// 
// 20    12/02/99 6:53p Aldie
// Changed naming conventions from "both" to "dualhanded"  Also put in the
// inventory renderer for the hud file
// 
// 19    12/01/99 4:56p Markd
// fixed some reference versus pointer issues with RandomAnimate and NewAnim
// 
// 18    12/01/99 11:26a Aldie
// Couple of fixes for emitters and more ammo stuff
// 
// 17    11/29/99 6:32p Aldie
// Lots of changes for ammo system
// 
// 16    11/22/99 6:46p Aldie
// Started working on ammo changes - will finish after Thanksgiving break
// 
// 15    11/19/99 5:45p Aldie
// Update for primary and alternate fire weapons.  Removed PRIMARY and SECONDAY
// mode weapons of Sin, removed SILENCED properties, and changed ammo types to
// use the new system.  Still need to fix ammo checking for weapons.
// 
// 14    11/10/99 6:12p Steven
// Don't have a pain event if the sentient just died.
// 
// 13    11/03/99 3:31p Steven
// Fixed blood spurts.
// 
// 12    10/28/99 11:56a Aldie
// Rope stuff
// 
// 11    10/19/99 7:53p Markd
// eliminated 3 part model system
// 
// 10    10/11/99 3:10p Steven
// Event documentation cleanup.
// 
// 9     10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 8     10/01/99 4:14p Steven
// Put regen hack back in.
// 
// 7     9/28/99 7:24p Steven
// Event formatting.
// 
// 6     9/27/99 5:45p Markd
// began documentation and cleanup phase after merge
// 
// 5     9/20/99 6:58p Steven
// Cleanup
// 
// 4     9/16/99 4:49p Jimdose
// removed unused code
// 
// 3     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 2     9/15/99 6:57p Aldie
// Update to get game working
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 43    9/02/99 9:44p Markd
// Added regen sound to player health regeneration
// 
// 42    9/02/99 7:41p Markd
// Added MOD_SLIME to going green
// 
// 41    9/02/99 7:27p Steven
// Improved the direction of the blood spurts.
// 
// 40    9/02/99 4:35p Markd
// Added Color Offset support for sentients
// 
// 39    9/01/99 8:20p Steven
// ECTS hack to give the player health when she dies.
// 
// 38    9/01/99 12:03p Steven
// Added blood spurts.
// 
// 37    8/31/99 2:44p Steven
// Made it so DAMAGE_NO actually works and saved means of death in actor.
// 
// 36    8/28/99 11:45a Steven
// Removed global from sound function calls.
// 
// 35    8/18/99 3:29p Jimdose
// added cylindrical collision detection
// 
// 34    8/16/99 10:32a Steven
// More general AI work.
// 
// 33    8/11/99 5:56p Steven
// More general AI work.
// 
// 32    8/10/99 6:45p Aldie
// Added a debug print
// 
// 31    8/09/99 5:07p Aldie
// More changes to accomodate weapons system
// 
// 30    8/06/99 6:40p Aldie
// Started moving over to new weapons system
// 
// 29    8/04/99 4:53p Steven
// Added immunities to sentient.
// 
// 28    7/23/99 3:27p Aldie
// 
// 27    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
//
// DESCRIPTION:
// Base class of entity that can carry other entities, and use weapons.
//

#include "g_local.h"
#include "entity.h"
#include "sentient.h"
#include "weapon.h"
#include "weaputils.h"
#include "scriptmaster.h"
#include "ammo.h"
#include "armor.h"
#include "misc.h"
#include "inventoryitem.h"
#include "player.h"
#include "actor.h"
#include "shield.h"
#include "decals.h"

// FIXME
// remove this when actor gets checked back in
Event EV_Sentient_UselessCheck
	( 
	"getridofthis",
	EV_DEFAULT,
   "",
   "",
   ""
	);

Event EV_Sentient_Attack
	( 
	"fire",
	EV_DEFAULT,
   "s",
   "hand",
   "Fires the weapon in the specified hand."
	);
Event EV_Sentient_StopFire
	( 
	"stopfire",
	EV_DEFAULT,
   "s",
   "hand",
   "Stops the firing of the weapon in the specified hand."
	);
Event EV_Sentient_Charge
   (
   "charge",
   EV_DEFAULT,
   "s",
   "hand",
   "Starts the charging of the weapon in the specified hand"
   );
Event EV_Sentient_ReleaseAttack
	( 
	"releasefire",
	EV_DEFAULT,
   "f",
   "fireholdtime",
   "Releases the attack in the time specified."
	);
Event EV_Sentient_GiveWeapon
	( 
	"weapon",
	EV_DEFAULT,
   "s",
   "weapon_modelname",
   "Gives the sentient the weapon specified."
	);
Event EV_Sentient_Take
	( 
	"take",
	EV_DEFAULT,
   "s",
   "item_name",
   "Takes away the specified item from the sentient."
	);
Event EV_Sentient_GiveAmmo
	( 
	"ammo",
	EV_DEFAULT,
   "si",
   "type amount",
   "Gives the sentient some ammo."
	);
Event EV_Sentient_GiveArmor
	( 
	"armor",
	EV_DEFAULT,
   "si",
   "type amount",
   "Gives the sentient some armor."
	);
Event EV_Sentient_GiveItem
	( 
	"item",
	EV_DEFAULT,
   "si",
   "type amount",
   "Gives the sentient the specified amount of the specified item."
	);
Event EV_Sentient_GiveTargetname
	( 
	"give",
	EV_DEFAULT,
   "s",
   "name",
   "Gives the sentient the targeted item."
	);
Event EV_Sentient_GiveHealth
	( 
	"health", 
	EV_CHEAT,
	"f",
   "health",
   "Gives the sentient the specified amount health."
	);
Event EV_Sentient_SetBloodModel
   ( 
   "bloodmodel",
   EV_DEFAULT,
   "s",
   "bloodModel",
   "set the model to be used when showing blood"
   );
Event EV_Sentient_TurnOffShadow
	( 
	"noshadow",
	EV_DEFAULT,
   NULL,
   NULL,
   "Turns off the shadow for this sentient."
	);
Event EV_Sentient_TurnOnShadow
	( 
	"shadow",
	EV_DEFAULT,
   NULL,
   NULL,
   "Turns on the shadow for this sentient."
	);
Event EV_Sentient_AddImmunity
	( 
	"immune",
	EV_DEFAULT,
   "sSSSSS",
   "immune_string1 immune_string2 immune_string3 immune_string4 immune_string5 immune_string6",
   "Adds to the immunity list for this sentient."
	);
Event EV_Sentient_RemoveImmunity
	( 
	"removeimmune",
	EV_DEFAULT,
   "sSSSSS",
   "immune_string1 immune_string2 immune_string3 immune_string4 immune_string5 immune_string6",
   "Removes from the immunity list for this sentient."
	);
Event EV_Sentient_UpdateOffsetColor
	( 
	"updateoffsetcolor",
	EV_DEFAULT,
   NULL,
   NULL,
   "Updates the offset color."
	);
Event EV_Sentient_JumpXY
	( 
	"jumpxy",
	EV_DEFAULT,
	"fff",
   "forwardmove sidemove speed",
   "Makes the sentient jump."
	);
Event EV_Sentient_MeleeAttackStart
	( 
	"meleeattackstart",
	EV_DEFAULT,
   NULL,
   NULL,
   "Is the start of the sentient's melee attack."
	);
Event EV_Sentient_MeleeAttackEnd
	( 
	"meleeattackend",
	EV_DEFAULT,
   NULL,
   NULL,
   "Is the end of the sentient's melee attack."
	);
Event EV_Sentient_BlockStart
	( 
	"blockstart",
	EV_DEFAULT,
   NULL,
   NULL,
   "Is the start of the sentient's block."
	);
Event EV_Sentient_BlockEnd
	( 
	"blockend",
	EV_DEFAULT,
   NULL,
   NULL,
   "Is the end of the sentient's block."
	);
Event EV_Sentient_StunStart
	( 
	"stunstart",
	EV_DEFAULT,
   NULL,
   NULL,
   "Is the start of the sentient's stun."
	);
Event EV_Sentient_StunEnd
	( 
	"stunend",
	EV_DEFAULT,
   NULL,
   NULL,
   "Is the end of the sentient's stun."
	);
Event EV_Sentient_SetMouthAngle
	( 
	"mouthangle",
	EV_DEFAULT,
	"f",
	"mouth_angle",
	"Sets the mouth angle of the sentient."
	);
Event EV_Sentient_SetMaxMouthAngle
	( 
	"maxmouthangle",
	EV_DEFAULT,
	"f",
	"max_mouth_angle",
	"Sets the max mouth angle."
	);
Event EV_Sentient_OnFire
	( 
	"onfire",
	EV_DEFAULT,
	NULL,
	NULL,
	"Called every frame when the sentient is on fire."
	);
Event EV_Sentient_StopOnFire
	( 
	"stoponfire",
	EV_DEFAULT,
	NULL,
	NULL,
	"Stops the sentient from being on fire."
	);
Event EV_Sentient_SpawnBloodyGibs
	( 
	"spawnbloodygibs",
	EV_DEFAULT,
	"IF",
	"number_of_gibs scale",
	"Spawns some bloody generic gibs."
	);
Event EV_Sentient_SetMaxGibs
	( 
	"maxgibs",
	EV_DEFAULT,
	"i",
	"max_number_of_gibs",
	"Sets the maximum amount of generic gibs this sentient will spawn when hit."
	);
Event EV_Sentient_CheckAnimations
	( 
	"checkanims",
	EV_DEFAULT,
	NULL,
	NULL,
	"Check the animations in the .tik file versus the statefile"
	);


CLASS_DECLARATION( Animate, Sentient, NULL )
   {
	   { &EV_Sentient_Attack,				   FireWeapon },
	   { &EV_Sentient_StopFire,				StopFireWeapon },
      { &EV_Sentient_Charge,				   ChargeWeapon },
      { &EV_Sentient_ReleaseAttack,		   ReleaseFireWeapon },
	   { &EV_Sentient_GiveAmmo,			   EventGiveAmmo },
	   { &EV_Sentient_GiveWeapon,			   EventGiveItem },
      { &EV_Sentient_GiveArmor,			   EventGiveItem },
      { &EV_Sentient_GiveItem,            EventGiveItem },
      { &EV_Sentient_GiveHealth,          EventGiveHealth },
	   { &EV_Sentient_Take,		      	   EventTake },
      { &EV_Sentient_SetBloodModel,			SetBloodModel },
      { &EV_Sentient_GiveTargetname,      EventGiveTargetname },
      { &EV_Damage,                       ArmorDamage },
  		{ &EV_Sentient_TurnOffShadow,		   TurnOffShadow },
		{ &EV_Sentient_TurnOnShadow,		   TurnOnShadow },
		{ &EV_Sentient_AddImmunity,	      AddImmunity },
		{ &EV_Sentient_RemoveImmunity,	   RemoveImmunity },
		{ &EV_Sentient_UpdateOffsetColor,	UpdateOffsetColor },
		{ &EV_Sentient_JumpXY,				   JumpXY },
		{ &EV_Sentient_MeleeAttackStart,		MeleeAttackStart },
		{ &EV_Sentient_MeleeAttackEnd,		MeleeAttackEnd },
		{ &EV_Sentient_BlockStart,				BlockStart },
		{ &EV_Sentient_BlockEnd,				BlockEnd },
		{ &EV_Sentient_StunStart,				StunStart },
		{ &EV_Sentient_StunEnd,					StunEnd },
		{ &EV_Sentient_SetMaxMouthAngle,		SetMaxMouthAngle },
		{ &EV_Sentient_OnFire,					OnFire },
		{ &EV_Sentient_StopOnFire,					StopOnFire },
		{ &EV_Sentient_SpawnBloodyGibs,		SpawnBloodyGibs },
		{ &EV_Sentient_SetMaxGibs,				SetMaxGibs },
		{ &EV_Sentient_CheckAnimations,  	CheckAnimations },
		{ NULL, NULL }
	};

Container<Sentient *> SentientList;

Sentient::Sentient()
	{
	SentientList.AddObject( ( Sentient * )this );
   setContents( CONTENTS_BODY );
	inventory.ClearObjectList();

	newWeapon         = NULL;
	eyeposition       = "0 0 64";
   firing_frame      = -1;
   firing_anim       = -1;
   charge_start_time = 0;
   poweruptype       = 0;
   poweruptimer      = 0;
   // do better lighting on all sentients
   edict->s.renderfx |= RF_EXTRALIGHT;
   edict->s.renderfx |= RF_SHADOW;  
   // sentients have precise shadows
   edict->s.renderfx |= RF_SHADOW_PRECISE;  
   memset( activeWeaponList, 0, sizeof( activeWeaponList ) );
	in_melee_attack = false;
	in_block = false;
	in_stun = false;
   attack_blocked = qfalse;
	max_mouth_angle = 10;
   // touch triggers by default
   flags |= FL_TOUCH_TRIGGERS;
	on_fire = false;
	max_gibs = 0;
	next_bleed_time = 0;
   }

Sentient::~Sentient()
	{
	SentientList.RemoveObject( ( Sentient * )this );
	FreeInventory();
	}


// HACK HACK HACK
void Sentient::UpdateOffsetColor
   (
   Event *ev
   )
   {
   G_SetConstantLight( &edict->s.constantLight, &offset_color[ 0 ], &offset_color[ 1 ], &offset_color[ 2 ], NULL );
   offset_color -= offset_delta;
   offset_time -= FRAMETIME;
   if ( offset_time > 0 )
      {
      PostEvent( EV_Sentient_UpdateOffsetColor, FRAMETIME );
      }
   else
      {
      CancelEventsOfType( EV_Sentient_UpdateOffsetColor );
      edict->s.renderfx &= ~RF_LIGHTOFFSET;
      offset_color[ 0 ] = offset_color[ 1 ] = offset_color[ 2 ] = 0;
      G_SetConstantLight( &edict->s.constantLight, &offset_color[ 0 ], &offset_color[ 1 ], &offset_color[ 2 ], NULL );
      }
   }

void Sentient::SetOffsetColor
   ( 
   float r, 
   float g, 
   float b, 
   float time 
   )

   {
   // kill all pending events
   CancelEventsOfType( EV_Sentient_UpdateOffsetColor );

   offset_color[ 0 ] = r;
   offset_color[ 1 ] = g;
   offset_color[ 2 ] = b;

   G_SetConstantLight( &edict->s.constantLight, &offset_color[ 0 ], &offset_color[ 1 ], &offset_color[ 2 ], NULL );

   // delta is a little less so we don't go below zero
   offset_delta = offset_color * ( FRAMETIME / ( time + ( 0.5f * FRAMETIME ) ) );
   offset_time = time;

   edict->s.renderfx |= RF_LIGHTOFFSET;

   PostEvent( EV_Sentient_UpdateOffsetColor, FRAMETIME );
   }

Vector Sentient::EyePosition
	(
	void
	)

	{
   return origin + eyeposition;
	}

Vector Sentient::GunPosition
	(
	void
	)

	{
	return origin;
	}

void Sentient::EventGiveHealth
   (
   Event *ev
   )

   {
   health = ev->GetFloat( 1 );
   }

void Sentient::SetBloodModel
   (
   Event *ev
   )

   {
	str name;
	str cache_name;
	str models_dir = "models/";

	if ( ev->NumArgs() < 1 )
		return;

	blood_model = ev->GetString( 1 );
	cache_name = models_dir + blood_model;
   CacheResource( cache_name.c_str(), this );

	name = GetBloodSpurtName();
	if ( name.length() )
		{
		cache_name = models_dir + name;
		CacheResource( cache_name.c_str(), this );
		}

	name = GetBloodSplatName();
	if ( name.length() )
		CacheResource( name.c_str(), this );

	name = GetGibName();
	if ( name.length() )
		{
		cache_name = models_dir + name;
		CacheResource( cache_name.c_str(), this );
		}
	}

void Sentient::ChargeWeapon
   (
   Event *ev
   )

   {
   Weapon * activeWeapon;
   firemode_t     mode=FIRE_PRIMARY;
   weaponhand_t   hand=WEAPON_RIGHT;

   if ( charge_start_time )
      {
      // Charging has already been started, so return
      return;
      }

   if ( ev->NumArgs() > 0 )
      {
      hand = WeaponHandNameToNum( ev->GetString( 1 ) );

      if ( hand < 0 )
         return;

      if ( ev->NumArgs() == 2 )
         {                           
         mode = WeaponModeNameToNum( ev->GetString( 2 ) );
         
         if ( mode < 0 )
            return;
         }
      }

   if ( hand > MAX_ACTIVE_WEAPONS )
      {
      warning( "Sentient::ChargeWeapon", "Weapon hand number \"%d\" is out of bounds of 0 to MAX_ACTIVE_WEAPONS:%d\n", hand, MAX_ACTIVE_WEAPONS );
      return;
      }

   // start charging the active weapon 
   activeWeapon = activeWeaponList[ (int)hand ];

    // Save off firing animation and frame
   firing_anim  = ev->GetAnimationNumber();
   firing_frame = ev->GetAnimationFrame();

	if ( ( activeWeapon ) && activeWeapon->ReadyToFire( mode ) && activeWeapon->MuzzleClear() )
		{
      charge_start_time = level.time;

      if ( mode == FIRE_PRIMARY )
		   activeWeapon->RandomAnimate( "charge", NULL );
      else if ( mode == FIRE_ALTERNATE )
         activeWeapon->RandomAnimate( "alternatecharge", NULL );
		}
   }

void Sentient::FireWeapon
	(
	Event *ev
	)

	{
   Weapon      *activeWeapon;
   firemode_t  mode=FIRE_PRIMARY;
   int         number=0;  
   str         modestring, side;

   if ( ev->NumArgs() > 0 )
      {
      side = ev->GetString( 1 );

      if ( !stricmp( side, "righthand" ) ) 
         number = WEAPON_RIGHT;
      else if ( !stricmp( side, "lefthand" ) ) 
         number = WEAPON_LEFT;
      else if ( !stricmp( side, "dualhand" ) )
         {
         number = WEAPON_DUAL;

         if ( ev->NumArgs() == 2 )
            {
            modestring = ev->GetString( 2 );
            if ( !modestring.icmp( "primary" ) )
               mode = FIRE_PRIMARY;
            else if ( !modestring.icmp( "alternate" ) )
               mode = FIRE_ALTERNATE;
            else
               warning( "Sentient::FireWeapon", "Invalid fire mode %s\n", modestring );
            }
         }
      else 
         number = atoi( side.c_str() );
      }

   if ( ( number > MAX_ACTIVE_WEAPONS ) || ( number < 0 ) )
      {
      warning( "Sentient::FireWeapon", "Weapon number \"%d\" is out of bounds of 0 to MAX_ACTIVE_WEAPONS:%d\n", number, MAX_ACTIVE_WEAPONS );
      return;
      }

   // Save off firing animation and frame
   firing_anim  = ev->GetAnimationNumber();
   firing_frame = ev->GetAnimationFrame();

   activeWeapon = activeWeaponList[ number ];

	if ( ( activeWeapon ) && activeWeapon->ReadyToFire( mode ) )
		{
		activeWeapon->Fire( mode );
		}
   else 
      {
      if ( !activeWeapon )
         gi.DPrintf( "No active weapon in slot #: \"%i\"\n", number );
      }
	}

void Sentient::StopFireWeapon
	(
	Event *ev
	)

	{
   Weapon      *activeWeapon;
   int         number=0;  
   str         side;

   if ( ev->NumArgs() > 0 )
      {
      side = ev->GetString( 1 );

      if ( !stricmp( side, "righthand" ) ) 
         number = WEAPON_RIGHT;
      else if ( !stricmp( side, "lefthand" ) ) 
         number = WEAPON_LEFT;
      else if ( !stricmp( side, "dualhand" ) )
         number = WEAPON_DUAL;
      else 
         number = atoi( side.c_str() );
      }

   if ( ( number > MAX_ACTIVE_WEAPONS ) || ( number < 0 ) )
      {
      warning( "Sentient::StopFireWeapon", "Weapon number \"%d\" is out of bounds of 0 to MAX_ACTIVE_WEAPONS:%d\n", number, MAX_ACTIVE_WEAPONS );
      return;
      }

   activeWeapon = activeWeaponList[ number ];

	if ( activeWeapon )
		{
		activeWeapon->ForceIdle();
		}
   else 
      {
      if ( !activeWeapon )
         gi.DPrintf( "No active weapon in slot #: \"%i\"\n", number );
      }
	}

void Sentient::ReleaseFireWeapon
	(
	Event *ev
	)

	{
   Weapon      *activeWeapon;
   float       charge_time=0;
   firemode_t  mode=FIRE_PRIMARY;
   int         number=0;  
   str         modestring, side;

   charge_time = level.time - charge_start_time;
   
   // Reset the down timer
   charge_start_time  = 0;

   if ( ev->NumArgs() > 0 )
      {
      side = ev->GetString( 1 );

      if ( !stricmp( side, "righthand" ) ) 
         number = WEAPON_RIGHT;
      else if ( !stricmp( side, "lefthand" ) ) 
         number = WEAPON_LEFT;
      else if ( !stricmp( side, "dualhand" ) )
         {
         number = WEAPON_DUAL;
         if ( ev->NumArgs() == 2 )
            {
            modestring = ev->GetString( 2 );
            if ( !modestring.icmp( "primary" ) )
               mode = FIRE_PRIMARY;
            else if ( !modestring.icmp( "alternate" ) )
               mode = FIRE_ALTERNATE;
            else
               warning( "Sentient::FireWeapon", "Invalid fire mode %s\n", modestring );
            }
         }
      else 
         number = atoi( side.c_str() );
      }

   if ( ( number > MAX_ACTIVE_WEAPONS ) || ( number < 0 ) )
      {
      warning( "Sentient::FireWeapon", "Weapon number \"%d\" is out of bounds of 0 to MAX_ACTIVE_WEAPONS:%d\n", number, MAX_ACTIVE_WEAPONS );
      return;
      }

   // Save off firing animation and frame
   firing_anim  = ev->GetAnimationNumber();
   firing_frame = ev->GetAnimationFrame();

   activeWeapon = activeWeaponList[ number ];

   if ( activeWeapon )
		{
      activeWeapon->ReleaseFire( mode, charge_time );
		}
	}

void Sentient::AddItem
	(
	Item *object
	)

	{
	inventory.AddObject( object->entnum );
	}

void Sentient::RemoveItem
	(
	Item *object
	)

	{
	inventory.RemoveObject( object->entnum );
	
   if ( object->isSubclassOf( Weapon ) )
      DeactivateWeapon( (Weapon *)object );

   // 
   // let the sent know about it
   //
   RemovedItem( object );
	}

Item *Sentient::FindItemByExternalName
   (
   const char *itemname
   )

   {
	int	num;
	int	i;
	Item	*item;

	num = inventory.NumObjects();
	for( i = 1; i <= num; i++ )
		{
		item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );
      assert( item );
		if ( !Q_stricmp( item->getName(), itemname ) )
			{
			return item;
			}
		}

	return NULL;
   }

Item *Sentient::FindItemByModelname
   (
   const char *mdl
   )

   {
	int	num;
	int	i;
	Item	*item;
   str   tmpmdl;

   if ( strnicmp( "models/", mdl, 7 ) )
		{
		tmpmdl = "models/";
		}
   tmpmdl += mdl;

	num = inventory.NumObjects();
	for( i = 1; i <= num; i++ )
		{
		item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );
      assert( item );
		if ( !Q_stricmp( item->model, tmpmdl ) )
			{
			return item;
			}
		}

	return NULL;
   }

Item *Sentient::FindItemByClassName
	(
	const char *classname
	)

	{
	int	num;
	int	i;
	Item	*item;

	num = inventory.NumObjects();
	for( i = 1; i <= num; i++ )
		{
		item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );
      assert( item );
		if ( !Q_stricmp( item->edict->entname, classname ) )
			{
			return item;
			}
		}

	return NULL;
	}

Item *Sentient::FindItem
	(
	const char *itemname
	)

	{
	Item	*item;

   item = FindItemByExternalName( itemname );
   if ( !item )
      {
      item = FindItemByModelname( itemname );
      if ( !item )
         {
         item = FindItemByClassName( itemname );
         }
      }
   return item;
	}

void Sentient::AttachAllActiveWeapons
   (
   void
   )

   {
   int i;

   for ( i=0; i<MAX_ACTIVE_WEAPONS; i++ )
      {
      Weapon *weap = activeWeaponList[i];

      if ( weap )
         weap->AttachToOwner( (weaponhand_t )i );
      }

	if ( this->isSubclassOf( Player ) )
		{
		Player *player = (Player * )this;
		player->UpdateWeapons();
		}
   }

void Sentient::DetachAllActiveWeapons
   (
   void
   )

   {
   int i;

   for ( i=0; i<MAX_ACTIVE_WEAPONS; i++ )
      {
      Weapon *weap = activeWeaponList[i];

      if ( weap )
         weap->DetachFromOwner();
      }
   }

void Sentient::FreeInventory
	(
	void
	)

	{
	int	num;
	int	i;
	Item	*item;
   Ammo  *ammo;

   // Detach all Weapons
   DetachAllActiveWeapons();

   // Delete all inventory items ( this includes weapons )
	num = inventory.NumObjects();
	for( i = num; i > 0; i-- )
		{
		item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );
		delete item;
		}
	inventory.ClearObjectList();

   // Remove all ammo
   num = ammo_inventory.NumObjects();
	for( i = num; i > 0; i-- )
		{
		ammo = ( Ammo * )ammo_inventory.ObjectAt( i );
		delete ammo;
		}
	ammo_inventory.ClearObjectList();   
	}

qboolean Sentient::HasItem
	(
	const char *itemname
	)

	{
	return ( FindItem( itemname ) != NULL );
	}

int Sentient::NumWeapons
	(
   void
	)

	{
	int	num;
	int	i;
	Item	*item;
   int   numweaps;

   numweaps = 0;

	num = inventory.NumObjects();
	for( i = 1; i <= num; i++ )
		{
		item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );
      if ( checkInheritance( &Weapon::ClassInfo, item->getClassname() ) )
			{
         numweaps++;
			}
		}

   return numweaps;
	}

void Sentient::ChangeWeapon
	(
	Weapon         *weapon,
   weaponhand_t   hand
	)

	{
   if ( ( hand > MAX_ACTIVE_WEAPONS ) || ( hand < 0 ) )
      {
      warning( "Sentient::ChangeWeapon", "Weapon hand number \"%d\" is out of bounds of 0 to MAX_ACTIVE_WEAPONS:%d\n", hand, MAX_ACTIVE_WEAPONS );
      return;
      }

   // Check if weapon is already active in the slot
   if ( weapon == activeWeaponList[hand] )
      return;

   ActivateWeapon( weapon, hand );
	}

void Sentient::DeactivateWeapon
   (
   weaponhand_t hand
   )

   {
   int i;
   
   if ( !activeWeaponList[hand] ) 
      {
      warning( "Sentient::DeactivateWeapon", "Tried to deactivate a non-active weapon in hand %d\n", hand );
      return;
      }

   activeWeaponList[hand]->AttachToHolster( hand );
   activeWeaponList[hand]->SetPutAway( false );
   activeWeaponList[hand]->RandomAnimate( "putaway" );
   
   // Check the player's inventory and detach any weapons that are already attached to that spot
   for ( i=1; i<=inventory.NumObjects(); i++ )
      {
      Item *item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );

      if ( item->isSubclassOf( Weapon ) )
         {  
         Weapon *weap = ( Weapon * )item;

         if (
            ( weap != activeWeaponList[hand] ) && 
            ( !str::cmp( weap->GetCurrentAttachToTag(), activeWeaponList[hand]->GetCurrentAttachToTag() ) )
            )
            {
            weap->DetachFromOwner();
            }
         }
      }
   activeWeaponList[hand] = NULL;
   }

void Sentient::DeactivateWeapon
   (
   Weapon *weapon
   )

   {
   int i;

   for ( i=0; i<MAX_ACTIVE_WEAPONS; i++ )
      {
      if ( activeWeaponList[i] == weapon )
         {
         activeWeaponList[i]->DetachFromOwner();
         activeWeaponList[i]->SetPutAway( false );
         activeWeaponList[i] = NULL;
         }
      }
   }

void Sentient::ActivateWeapon
   (
   Weapon         *weapon,
   weaponhand_t   hand
   )

   { 
   int i;

   activeWeaponList[hand] = weapon;
   str holsterTag;

   switch( hand )
      {
      case WEAPON_LEFT:
         holsterTag = weapon->GetLeftHolsterTag();
         break;
      case WEAPON_RIGHT:
         holsterTag = weapon->GetRightHolsterTag();
         break;
      case WEAPON_DUAL:
         holsterTag = weapon->GetDualHolsterTag();
         break;
      default:
         holsterTag = "";
         break;
      }

   // Check the player's inventory and detach any weapons that are currently attached to that tag.
   for ( i=1; i<=inventory.NumObjects(); i++ )
      {
      Item *item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );

      if ( item->isSubclassOf( Weapon ) )
         {  
         Weapon *weap = ( Weapon * )item;

         if (
            ( !str::cmp( holsterTag, weap->GetCurrentAttachToTag() ) )
            )
            {
            weap->DetachFromOwner();
            }
         }
      }
   weapon->AttachToOwner( hand );
   weapon->RandomAnimate( "raise" );
   }

Weapon *Sentient::BestWeapon
	(
	Weapon *ignore
	)

	{
	Item		*next;
	int		n;
	int		j;
	int		bestrank;
	Weapon	*bestweapon;

	n = inventory.NumObjects();

	// Search forewards until we find a weapon
	bestweapon = NULL;
	bestrank = -999999;
	for( j = 1; j <= n; j++ )
		{
		next = ( Item * )G_GetEntity( inventory.ObjectAt( j ) );

		assert( next );

		if ( ( next != ignore ) && next->isSubclassOf( Weapon ) && ( ( ( Weapon * )next )->GetRank() > bestrank ) &&
			( ( ( Weapon * )next )->HasAmmo( FIRE_PRIMARY ) )	)
			{
			bestweapon = ( Weapon * )next;
			bestrank = bestweapon->GetRank();
			}
		}

	return bestweapon;
	}

Weapon *Sentient::NextWeapon
	(
	Weapon *weapon
	)

	{
	Item		*item;
	int		i;
	int		n;
	int		weaponorder;
	Weapon	*choice;
	int		choiceorder;
	Weapon	*bestchoice;
	int		bestorder;
	Weapon	*worstchoice;
	int		worstorder;

	if ( !inventory.ObjectInList( weapon->entnum ) )
		{
		error( "NextWeapon", "Weapon not in list" );
		}

	weaponorder = weapon->GetOrder();
	bestchoice = weapon;
	bestorder = 65535;
	worstchoice = weapon;
	worstorder = weaponorder;

	n = inventory.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );

		assert( item );

		if ( item->isSubclassOf( Weapon ) )
			{
			choice = ( Weapon * )item;
			if ( !choice->HasAmmo( FIRE_PRIMARY ) || !choice->AutoChange() )
				{
				continue;
				}

			choiceorder = choice->GetOrder();
			if ( ( choiceorder > weaponorder ) && ( choiceorder < bestorder ) )
				{
				bestorder = choiceorder;
				bestchoice = choice;
				}

			if ( choiceorder < worstorder )
				{
				worstorder = choiceorder;
				worstchoice = choice;
				}
			}
		}

	if ( bestchoice == weapon )
		{
		return worstchoice;
		}

	return bestchoice;
	}

Weapon *Sentient::PreviousWeapon
	(
	Weapon *weapon
	)

	{
	Item		*item;
	int		i;
	int		n;
	int		weaponorder;
	Weapon	*choice;
	int		choiceorder;
	Weapon	*bestchoice;
	int		bestorder;
	Weapon	*worstchoice;
	int		worstorder;

	if ( !inventory.ObjectInList( weapon->entnum ) )
		{
		error( "PreviousWeapon", "Weapon not in list" );
		}

	weaponorder = weapon->GetOrder();
	bestchoice = weapon;
	bestorder = -65535;
	worstchoice = weapon;
	worstorder = weaponorder;

	n = inventory.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );

		assert( item );

		if ( item->isSubclassOf( Weapon ) )
			{
			choice = ( Weapon * )item;
			if ( !choice->HasAmmo( FIRE_PRIMARY ) || !choice->AutoChange() )
				{
				continue;
				}

			choiceorder = choice->GetOrder();
			if ( ( choiceorder < weaponorder ) && ( choiceorder > bestorder ) )
				{
				bestorder = choiceorder;
				bestchoice = choice;
				}

			if ( choiceorder > worstorder )
				{
				worstorder = choiceorder;
				worstchoice = choice;
				}
			}
		}

	if ( bestchoice == weapon )
		{
		return worstchoice;
		}

	return bestchoice;
	}

Weapon *Sentient::GetActiveWeapon
   (
   weaponhand_t hand
   )

   {
   if ( ( hand > MAX_ACTIVE_WEAPONS ) || ( hand < 0 ) )
      {
      warning( "Sentient::GetActiveWeapon", "Weapon hand number \"%d\" is out of bounds of 0 to MAX_ACTIVE_WEAPONS:%d\n", hand, MAX_ACTIVE_WEAPONS );
      return NULL;
      }
   else
      {
      return activeWeaponList[hand];
      }
   }

qboolean Sentient::IsActiveWeapon
   (
   Weapon *weapon
   )

   {
   int i;

   for( i=0; i<MAX_ACTIVE_WEAPONS; i++ )
      {
      Weapon *activeWeap = activeWeaponList[i];

      if ( activeWeap == weapon )
         return true;
      }

   return false;
   }

void Sentient::EventGiveTargetname
   (
   Event *ev
   )

   {
   int         i;
   TargetList  *tlist;
   str         name;
   const char *ptr;
   qboolean    found;

   name = ev->GetString( 1 );

   ptr = name.c_str();

   // skip over the $
   ptr++;

   found = qfalse;

   tlist = world->GetTargetList( str( ptr ) );
   for ( i = 1; i <= tlist->list.NumObjects(); i++ )
      {
      Entity * ent;

      ent = tlist->list.ObjectAt( i );
		assert( ent );

		if ( ent->isSubclassOf( Item ) )
			{
         Item *item;

         item = ( Item * )ent;
         item->SetOwner( this );
         item->ProcessPendingEvents();
         AddItem( item );
         found = qtrue;
         }
      }

   if ( !found )
      {
      ev->Error( "Could not give item with targetname %s to this sentient.\n", name.c_str() );
      }
   }

Item *Sentient::giveItem
   (
   str itemname,
   int amount
   )

   {
	ClassDef	*cls;
	Item     *item;

   item = FindItem( itemname );
   if ( item )
      {
      item->Add( amount );
      return item;
      }
   else
      {
      qboolean set_the_model = qfalse;

      // we don't have it, so lets try to resolve the item name
      // first lets see if it is a registered class name
	   cls = getClass( itemname );
	   if ( !cls )
		   {
         SpawnArgs args;

         // if that didn't work lets try to resolve it as a model
         args.setArg( "model", itemname );

         cls = args.getClassDef();
         if ( !cls )
            {
            gi.DPrintf( "No item called '%s'\n", itemname.c_str() );
		      return NULL;
		      }
         set_the_model = qtrue;
         }
      assert( cls );
	   item = ( Item * )cls->newInstance();
   
      if ( !item )
		   {
         gi.DPrintf( "Could not spawn an item called '%s'\n", itemname.c_str() );
		   return NULL;
		   }

		if ( !item->isSubclassOf( Item ) )
			{
			gi.DPrintf( "Could not spawn an item called '%s'\n", itemname.c_str() );
			delete item;
			return NULL;
			}

      if ( set_the_model )
         {
         // Set the model
         item->setModel( itemname );
         }

      item->SetOwner( this );
      item->ProcessPendingEvents();
      item->setAmount( amount );

      AddItem( item );

      if ( item->isSubclassOf( Weapon ) )
         {
         // Post an event to give the ammo to the sentient
         Event *ev1;

         ev1 = new Event( EV_Weapon_GiveStartingAmmo );
         ev1->AddEntity( this );
         item->PostEvent( ev1, FRAMETIME );
         }

      return item;
      }
   return NULL;
   }

void Sentient::takeItem
   (
   const char *name
   )

   {
   Item * item;

   item = FindItem( name );
   if ( item )
      {
      gi.DPrintf( "Taking item %s away from player\n", item->getName().c_str() );
      
      item->PostEvent( EV_Remove, 0 );
      return;
      }

   Ammo *ammo;
   ammo = FindAmmoByName( name );
   if ( ammo )
      {
      gi.DPrintf( "Taking ammo %s away from player\n", name );
     
		ammo->setAmount( 0 );
      }
   }

void Sentient::useWeapon
	(
	const char     *weaponname,
   weaponhand_t   hand
	)

	{
	Weapon *weapon;

	assert( weaponname );

   if ( !weaponname )
      {
      warning( "Sentient::useWeapon", "weaponname is NULL\n" );
      return;
      }

   // Find the item in the sentient's inventory
	weapon = ( Weapon * )FindItem( weaponname );

   // If it exists, then make the change to the slot number specified
	if ( weapon )
		{
		ChangeWeapon( weapon, hand );
		}
	}

void Sentient::EventTake
   (
   Event *ev
   )

   {
   takeItem( ev->GetString( 1 ) );
   }

void Sentient::EventGiveAmmo
	(
	Event *ev
	)

	{
   int			amount,maxamount=-1;
	const char	*type;

	type        = ev->GetString( 1 );
   amount      = ev->GetInteger( 2 );

   if ( ev->NumArgs() == 3 )
      maxamount   = ev->GetInteger( 3 );

   GiveAmmo( type, amount, maxamount );
   }

void Sentient::EventGiveItem
   (
   Event *ev
   )

   {
	const char	*type;
   float       amount;

	type     = ev->GetString( 1 );
   if ( ev->NumArgs() > 1 )
      amount   = ev->GetInteger( 2 );
   else
      amount = 1;

   giveItem( type, amount );
   }

qboolean Sentient::DoGib
   (
   int meansofdeath,
   Entity *inflictor
   )

   {
   if ( !com_blood->integer )
      {
      return false;
      }

   if (
       ( meansofdeath == MOD_TELEFRAG ) ||
       ( meansofdeath == MOD_LAVA )
      )
      {
      return true;
      }

   if ( health > -75 )
      {
      return false;
      }

   // Impact and Crush < -75 health
   if ( ( meansofdeath == MOD_IMPACT ) || ( meansofdeath == MOD_CRUSH ) )
      {
      return true;
      }

   return false;
   }

void Sentient::SpawnEffect
   (
   str modelname,
   Vector pos
   )

   {
   Animate *block;

   block = new Animate;
   block->setModel( modelname );
   block->setOrigin( pos );
   block->setSolidType( SOLID_NOT );
   block->setMoveType( MOVETYPE_NONE );
   block->RandomAnimate( "idle" );
   block->PostEvent( EV_Remove, 1 );
   }

#define WATER_CONVERSION_FACTOR 1.0f
void Sentient::ArmorDamage 
   (
   Event *ev
   )

   {
 	Entity	   *inflictor;
	Entity	   *attacker;
	float		   damage;
	Vector	   momentum;
   Vector      position;
   Vector      normal;
   Vector      direction;
   Event		   *event;
   int         dflags;
   int         meansofdeath;
   int         knockback;
   float       damage_red;
   float       damage_green;
   float       damage_time;
	qboolean		blocked = false;
	qboolean		set_means_of_death;

   damage		   = ev->GetFloat  ( 1 );
	inflictor	   = ev->GetEntity ( 2 );
	attacker		   = ev->GetEntity ( 3 );
   position       = ev->GetVector ( 4 );
   direction      = ev->GetVector ( 5 );
   normal         = ev->GetVector ( 6 );
   knockback      = ev->GetInteger( 7 );
   dflags         = ev->GetInteger( 8 );
   meansofdeath   = ev->GetInteger( 9 );

	if ( ( takedamage == DAMAGE_NO ) || ( movetype == MOVETYPE_NOCLIP ) )
	   {
      return;
      }

	// See if we should set means of death

	set_means_of_death = true;

	if ( this->isSubclassOf( Actor ) )
		{
		Actor *act = (Actor *)this;

		if ( ( act->state_flags & STATE_FLAG_SMALL_PAIN ) && ( meansofdeath == MOD_ON_FIRE || Immune( meansofdeath ) ) )
			set_means_of_death = false;
		}

	// See if sentient is immune to this type of damage

	if ( Immune ( meansofdeath ) )
      {
		if ( set_means_of_death )
			means_of_death = meansofdeath;

		// Send pain event 
		event = new Event( EV_Pain );
		event->AddFloat( 0 );
		event->AddEntity( attacker );
		event->AddInteger( meansofdeath );
		event->AddVector( position );
		event->AddVector( direction );
		ProcessEvent( event );
		return;
      }

	// See if the damage is melee and high enough on actor

	if ( this->isSubclassOf( Actor ) )
		{
		Actor *act = ( Actor * )this;

		// Check the attack if it is melee
	
		if ( meansofdeath == MOD_SWORD || meansofdeath == MOD_CHAINSWORD || meansofdeath == MOD_AXE || meansofdeath == MOD_FIRESWORD ||
			  meansofdeath == MOD_ELECTRICSWORD || meansofdeath == MOD_LIGHTSWORD )
			{
			// Make sure attack is high enough

			if ( position.z - origin.z < act->minimum_melee_height )
				{
				SpawnEffect( "fx_sparkblock.tik", position );
				return;
				}

			// Make sure attack is within the damage angles

			if ( act->damage_angles )
				{
				Vector attack_angle;
				float yaw_diff;

				attack_angle = direction.toAngles();

				yaw_diff = angles[YAW] - attack_angle[YAW] + 180;

				yaw_diff = AngleNormalize180( yaw_diff );

				if ( yaw_diff < -act->damage_angles || yaw_diff > act->damage_angles )
					{
					SpawnEffect( "fx_sparkblock.tik", position );
					return;
					}
				}
			}
		}

   if ( deadflag )
      {
		// Spawn a blood spurt if this model has one
		if ( ShouldBleed( meansofdeath, true ) )
			{
			AddBloodSpurt( direction );

			if ( ShouldGib( meansofdeath, damage ) )
				ProcessEvent( EV_Sentient_SpawnBloodyGibs );
			}

		if ( set_means_of_death )
			means_of_death = meansofdeath;

		if ( meansofdeath == MOD_FIRE || meansofdeath == MOD_FIRESWORD || meansofdeath == MOD_FIRE_BLOCKABLE )
			TryLightOnFire( meansofdeath, attacker );

		// Send pain event
		event = new Event( EV_Pain );
		event->AddFloat( damage );
		event->AddEntity( attacker );
		event->AddInteger( meansofdeath );
		event->AddVector( position );
		event->AddVector( direction );
		ProcessEvent( event );

      return;
      }

	if ( flags & FL_GODMODE )
      {
		return;
      }

	// Armor/Water reduction of damage & blocking

   if ( this->isSubclassOf( Player ) )
      {
 		Vector attack_angle;
      Vector player_angle;
		float yaw_diff;
      Weapon *weap;
      Player *player;
		float water_level;
		float damage_absorbed;
		int outfit_level;
		float block_size;
      
      player = ( Player * )this;     

		block_size = 0;

		// Check to see if player is wielding a shield

		weap = player->GetActiveWeapon( WEAPON_LEFT );

		if ( weap && weap->isSubclassOf( Shield ) )
			{
			if ( player->LargeShieldActive() )
				block_size = 90;
			else if ( player->ShieldActive() )
				block_size = 45;
			}
      
      player_angle = player->GetTorsoAngles();
  		attack_angle = direction.toAngles();
		yaw_diff     = player_angle[YAW] - attack_angle[YAW] + 180;
		yaw_diff     = AngleNormalize180( yaw_diff );

      // Check to see if attack is in front arc
		if ( block_size && yaw_diff > -block_size && yaw_diff < block_size )
         {
         Shield *shield = ( Shield * )weap;

			if ( CanBlock( meansofdeath, player->LargeShieldActive() ) )
				{
				shield->Impact();

				damage -= damage * shield->GetDamageReduction();

				if ( attacker->isSubclassOf( Sentient ) )
					{
					Sentient *sent = ( Sentient * )attacker;
					sent->SetAttackBlocked( qtrue );
					}

				blocked = true;
				}
         }

		// Get real knockback value

		knockback = player->GetKnockback( knockback, blocked );

		// Armor reduction from armor pieces

		if ( meansofdeath != MOD_LIFEDRAIN )
			{
			outfit_level = player->GetOutfit();

			if ( outfit_level > 0 )
				outfit_level--;

			if ( outfit_level > 3 )
				outfit_level = 3;

			damage -= damage * outfit_level * 0.08;
			}

		// Water/armor stuff

		if ( meansofdeath != MOD_LIFEDRAIN )
			{
			water_level = player->GetWaterPower() * WATER_CONVERSION_FACTOR;

			damage_absorbed = damage / 4;

			if ( damage_absorbed > water_level )
				damage_absorbed = water_level;

			if ( damage_absorbed > 0 )
				{
				damage -= damage_absorbed;
				water_level -= damage_absorbed;
				player->SetWaterPower( water_level / WATER_CONVERSION_FACTOR );
				}
			}
      }

	// Do the kick
	if (!(dflags & DAMAGE_NO_KNOCKBACK))
      {
		if ((knockback) &&
         (movetype != MOVETYPE_NONE) &&
         (movetype != MOVETYPE_STATIONARY) &&
         (movetype != MOVETYPE_BOUNCE) &&
         (movetype != MOVETYPE_PUSH) &&
         (movetype != MOVETYPE_STOP))
         {
	      float	m;
			Event *immunity_event;

	      if (mass < 50)
		      m = 50;
	      else
		      m = mass;

         direction.normalize();
         if ( isClient() && ( attacker == this ) && deathmatch->integer )
		      momentum = direction * ( 1700.0f * ( float )knockback / m ); // the rocket jump hack...
	      else
		      momentum = direction * ( 500.0f * ( float )knockback / m );

         if ( dflags & DAMAGE_BULLET )
            {
            // Clip the z velocity for bullet weapons
            if ( momentum.z > 75)
               momentum.z = 75;
            }
         velocity += momentum;

			// Make this sentient vulnerable to falling damage now

			if ( Immune( MOD_FALLING ) )
				{
				immunity_event = new Event( EV_Sentient_RemoveImmunity );
				immunity_event->AddString( "falling" );
				ProcessEvent( immunity_event );
				}
         }
      }

	// Blocking of the attack by an enemy.
	if ( in_block && meansofdeath != MOD_ON_FIRE && meansofdeath != MOD_EXPLOSION )
		{
		Vector attack_angle;
		float yaw_diff;

		attack_angle = direction.toAngles();

		yaw_diff = angles[YAW] - attack_angle[YAW] + 180;

		yaw_diff = AngleNormalize180( yaw_diff );

		if ( yaw_diff > -45 && yaw_diff < 45 )
         {
			if ( meansofdeath != MOD_FIRE && meansofdeath != MOD_LIFEDRAIN )
				{
				if ( attacker->isSubclassOf( Sentient ) )
					{
					Sentient *sent = ( Sentient * )attacker;
					sent->SetAttackBlocked( qtrue );
					}
				if ( this->isSubclassOf( Actor ) )
					{
					Actor *act = ( Actor * )this;
					act->AddStateFlag( STATE_FLAG_BLOCKED_HIT );
					}

				SpawnEffect( "fx_sparkblock.tik", position );
				}

			means_of_death = meansofdeath;
         return;
         }

		in_block = false;
		}
   
   if ( g_debugdamage->integer )
      G_DebugDamage( damage, this, attacker, inflictor );

	if ( meansofdeath != MOD_LIFEDRAIN )
		{
		health -= damage;
		}
	else
		{
		float damage_left = damage;

		if ( damage_left > 0 )
			{
			float water_level = 0;
			Player *player = NULL;
			Actor *act = NULL;

			// Get the current water level

			if ( this->isSubclassOf( Player ) )
				{
				player = (Player *)this;
				water_level = player->GetWaterPower();
				}
			else if ( this->isSubclassOf( Actor ) )
				{
				act = (Actor *)this;
				water_level = act->water_level;
				}

			// Suck up the water

			if ( damage_left > water_level )
				{
				damage_left -= water_level;
				water_level = 0;
				}
			else
				{
				water_level -= damage_left;
				damage_left = 0;
				}

			// Set the new water level

			if ( this->isSubclassOf( Player ) )
				{
				player->SetWaterPower( water_level );
				}
			else if ( this->isSubclassOf( Actor ) )
				{
				act->water_level = water_level;
				} 
			}

		health -= damage_left;
		}

	if ( ( meansofdeath == MOD_FIRE || meansofdeath == MOD_FIRESWORD || meansofdeath == MOD_FIRE_BLOCKABLE ) && !blocked )
		TryLightOnFire( meansofdeath, attacker );

	// Set means of death
		
	if ( set_means_of_death )
		means_of_death = meansofdeath;

	// Spawn a blood spurt if this model has one
	if ( ShouldBleed( meansofdeath, false ) && !blocked )
		{
		AddBloodSpurt( direction );

		if ( ( this->isSubclassOf( Actor ) || damage > 10 ) && ShouldGib( meansofdeath, damage ) )
			ProcessEvent( EV_Sentient_SpawnBloodyGibs );
		}

	if ( health <= 0 )
      {
		// See if we can kill this actor or not

		if ( this->isSubclassOf( Actor ) )
			{
			Actor *act = ( Actor * )this;

			if ( act->IsImmortal() )
				health = 1;
			}
		}


   if ( health < 0.1 )
      {
		// Recalculate damage so that it is only damage needed to kill

		damage += health;

		// Make sure health is now 0

		health = 0;
		// See if we should go into limbo and get ready for a finishing move

		/* if ( this->isSubclassOf( Actor ) && attacker->isSubclassOf( Player ) )
			{
			float water_level;
			Actor *act = ( Actor * )this;
			Player *player = (Player *)attacker;

			water_level = player->GetWaterPower();

			if ( G_Random( 100 ) < water_level * 0.5 )
				{
				if ( !act->InLimbo() )
					{
					act->StartLimbo();
					return;
					}
				}
			} */
				 
      event = new Event( EV_Killed );
	   event->AddEntity( attacker );
	   event->AddFloat( damage );
	   event->AddEntity( inflictor );
      event->AddInteger( meansofdeath );
      ProcessEvent( event );
      }

   if ( 
         ( meansofdeath == MOD_GAS ) ||
			( meansofdeath == MOD_GAS_BLOCKABLE ) ||
         ( meansofdeath == MOD_SLIME ) || 
			( meansofdeath == MOD_POISON )
      )
      {
      damage_green = damage / 50;
      if ( damage_green > 1.0f )
         damage_green = 1.0f;
		if ( ( damage_green < 0.2 ) && ( damage_green > 0 ) )
			damage_green = 0.2;
      damage_red = 0;
      }
   else
      {
      damage_red = damage / 50;
      if ( damage_red > 1.0f )
         damage_red = 1.0f;
		if ( ( damage_red < 0.2 ) && ( damage_red > 0 ) )
			damage_red = 0.2;
      damage_green = 0;
      }

   damage_time = damage / 50;

	if ( damage_time > 2 )
		damage_time = 2;

   SetOffsetColor( damage_red, damage_green, 0, damage_time );

	if ( health > 0 )
		{
		// Send pain event
		event = new Event( EV_Pain );
		event->AddFloat( damage );
		event->AddEntity( attacker );
		event->AddInteger( meansofdeath );
		event->AddVector( position );
		event->AddVector( direction );
		ProcessEvent( event );
		}

	return;
   }

qboolean Sentient::CanBlock
	( 
	int meansofdeath, 
	qboolean full_block
	)
	{

	// Check to see what a full block can't even block

	switch ( meansofdeath )
		{
		case MOD_DROWN :
		case MOD_TELEFRAG :
		case MOD_SLIME :
		case MOD_LAVA :
		case MOD_FALLING :
		case MOD_RADIATION :
		case MOD_IMPALE :
		case MOD_ON_FIRE :
		case MOD_ELECTRICWATER :
		case MOD_EAT :
			return false;
		}

	// Full blocks block everything else

	if ( full_block )
		return true;

	// Check to see what a small block can't block

	switch ( meansofdeath )
		{
		case MOD_FIRE :
		case MOD_GAS :
		case MOD_CRUSH_EVERY_FRAME :
			return false;
		}

	// Everything else is blocked

	return true;
	}


void Sentient::AddBloodSpurt
	(
	Vector direction
	)
	{
	Entity *blood;
	Vector dir;
	Event *event;
	str blood_splat_name;
	float blood_splat_size;
	float length;
	trace_t trace;
	float scale;


	if ( !com_blood->integer )
		return;

	next_bleed_time = level.time + .5;

	// Calculate a good scale for the blood

	if ( mass < 50 )
		scale = .5;
	else if ( mass > 300 )
		scale = 1.5;
	else if ( mass >= 200 )
		scale = mass / 200.0;
	else
		scale = .5 + (mass - 50 ) / 300;

	// Add blood spurt

	blood = new Animate;
	blood->setModel( blood_model );

	dir[0] = -direction[0];
	dir[1] = -direction[1];
	dir[2] = -direction[2];
	blood->angles = dir.toAngles();
	blood->setAngles( blood->angles );

	blood->setOrigin( centroid );
	blood->origin.copyTo( blood->edict->s.origin2 );
	blood->setSolidType( SOLID_NOT );
	blood->setScale( scale );

	event = new Event( EV_Remove );
	blood->PostEvent( event, 1 );

	// Add blood splats near feet

	blood_splat_name = GetBloodSplatName();
	blood_splat_size = GetBloodSplatSize();

	if ( blood_splat_name.length() && G_Random() < 0.5 )
		{
		dir = origin - centroid;
		dir.z -= 50;
		dir.x += G_CRandom( 20 );
		dir.y += G_CRandom( 20 );

		length = dir.length();

		dir.normalize();

		dir = dir * ( length + 10 );

		trace = G_Trace( centroid, vec_zero, vec_zero, centroid + dir, NULL, MASK_DEADSOLID, false, "AddBloodSpurt" );

		if ( trace.fraction < 1 )
			{
			Decal *decal = new Decal;
			decal->setShader( blood_splat_name );
			decal->setOrigin( Vector( trace.endpos ) + ( Vector( trace.plane.normal ) * 0.2 ) );
			decal->setDirection( trace.plane.normal );
			decal->setOrientation( "random" );
			decal->setRadius( blood_splat_size + G_Random( blood_splat_size ) );
			}
		}
	}

qboolean Sentient::ShouldBleed
	(
	int meansofdeath,
	qboolean dead
	)
	{
	// Make sure we have a blood model

	if ( !blood_model.length() )
		return false;

	// Make sure if we are dead we are allowed to bleed after death

	if ( dead && this->isSubclassOf( Actor ) )
		{
		Actor *act = (Actor *)this;
		
		if ( !act->GetActorFlag( ACTOR_FLAG_BLEED_AFTER_DEATH ) )
			return false;
		}

	// See if we can bleed now based on means of death

	switch ( meansofdeath )
		{
		// Sometimes bleed (based on time)

		case MOD_BULLET :
		case MOD_STING :
		case MOD_STING2 :
		case MOD_VORTEX :
		case MOD_CHAINSWORD :
		case MOD_PLASMABEAM :
		case MOD_CRUSH_EVERY_FRAME :
		case MOD_POISON :
		case MOD_ELECTRICWATER :
		case MOD_EAT :
      case MOD_CIRCLEOFPROTECTION :

			if ( next_bleed_time > level.time )
				return false;

			break;

		// Sometimes bleed (based on chance)

		case MOD_PLASMASHOTGUN :

			if ( G_Random() > 0.1 )
				return false;

			break;

		// Never bleed

		case MOD_LIFEDRAIN :
		case MOD_SLIME :
		case MOD_LAVA :
		case MOD_GAS :
		case MOD_GAS_BLOCKABLE :
		case MOD_FIRE :
		case MOD_FIRE_BLOCKABLE :
		case MOD_SLING :
		case MOD_DROWN :
		case MOD_FLASHBANG :
		case MOD_ON_FIRE :
		case MOD_FALLING :
		case MOD_RADIATION :
			return false;
		}

	// Always bleed by default

	return true;
	}

// ShouldGib assumes that ShouldBleed has already been called

qboolean Sentient::ShouldGib
	(
	int meansofdeath,
	float damage
	)

	{
	// See if we can gib based on means of death

	switch ( meansofdeath )
		{
		// Always gib

		case MOD_CHAINSWORD :
		case MOD_CRUSH_EVERY_FRAME :
		case MOD_PLASMASHOTGUN :
		case MOD_EAT :

			return true;

			break;

		// Sometimes gib

		case MOD_BULLET :
		case MOD_STING :
		case MOD_STING2 :

			if ( G_Random( 100 ) < damage * 10 )
				return true;

			break;

		case MOD_PLASMABEAM :

			if ( G_Random( 100 ) < damage * 5 )
				return true;

			break;

		// Never gib

		case MOD_LIFEDRAIN :
		case MOD_SLIME :
		case MOD_LAVA :
		case MOD_GAS :
		case MOD_GAS_BLOCKABLE :
		case MOD_POISON :
		case MOD_FIRE :
		case MOD_FIRE_BLOCKABLE :
		case MOD_SLING :
		case MOD_DROWN :
		case MOD_FLASHBANG :
		case MOD_ON_FIRE :
		case MOD_FALLING :
		case MOD_RADIATION :
		case MOD_VORTEX :
		case MOD_ELECTRICWATER :
			return false;
		}

	// Default is random based on how much damage done

	if ( G_Random( 100 ) < damage * 2 )
		return true;

	return false;
	}

str Sentient::GetBloodSpurtName
	(
	void
	)
	{
	str blood_spurt_name;

	if ( blood_model == "fx_bspurt.tik" )
		blood_spurt_name = "fx_bspurt2.tik";
	else if ( blood_model == "fx_gspurt.tik" )
		blood_spurt_name = "fx_gspurt2.tik";
	else if ( blood_model == "fx_bspurt_blue.tik" )
		blood_spurt_name = "fx_bspurt2_blue.tik";

	return blood_spurt_name;
	}

str Sentient::GetBloodSplatName
	(
	void
	)
	{
	str blood_splat_name;

	if ( blood_model == "fx_bspurt.tik" )
		blood_splat_name = "bloodsplat.spr";
	else if ( blood_model == "fx_gspurt.tik" )
		blood_splat_name = "greensplat.spr";
	else if ( blood_model == "fx_bspurt_blue.tik" )
		blood_splat_name = "bluesplat.spr";

	return blood_splat_name;
	}

float Sentient::GetBloodSplatSize
	(
	void
	)
	{
	float m;

	m = mass;

	if ( m < 50 )
		m = 50;
	else if ( m > 250 )
		m = 250;

	return( 10 + (m - 50) / 200 * 6 );
	}

str Sentient::GetGibName
	(
	void
	)
	{
	str gib_name;

	if ( blood_model == "fx_bspurt.tik" )
		gib_name = "fx_rgib";
	else if ( blood_model == "fx_gspurt.tik" )
		gib_name = "fx_ggib";

	return gib_name;
	}

int Sentient::NumInventoryItems
   (
   void
   )

   {

   return inventory.NumObjects();

   }

Item *Sentient::NextItem
	(
	Item *item
	)

	{
	Item		*next_item;
	int		i;
	int		n;
   qboolean item_found = false;

   if ( !item )
      {
      item_found = true;
      }
   else if ( !inventory.ObjectInList( item->entnum ) )
		{
		error( "NextItem", "Item not in list" );
		}

	n = inventory.NumObjects();

	for( i = 1; i <= n; i++ )
		{
		next_item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );
      assert( next_item );

 		if ( next_item->isSubclassOf( InventoryItem ) && item_found )
         return next_item;

      if ( next_item == item )
         item_found = true;
      }

   return NULL;
   }

Item *Sentient::PrevItem
	(
	Item *item
	)

	{
	Item		*prev_item;
	int		i;
	int		n;
   qboolean item_found = false;

   if ( !item )
      {
      item_found = true;
      }
   else if ( !inventory.ObjectInList( item->entnum ) )
		{
		error( "NextItem", "Item not in list" );
		}

	n = inventory.NumObjects();

	for( i = n; i >= 1; i-- )
		{
		prev_item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );
      assert( prev_item );

 		if ( prev_item->isSubclassOf( InventoryItem ) && item_found)
         return prev_item;

      if ( prev_item == item )
         item_found = true;
      }

   return NULL;
   }

void Sentient::DropInventoryItems
   (
   void
   )

   {
   int   num;
   int   i;
   Item  *item;

   // Drop any inventory items
 	num = inventory.NumObjects();
	for( i = num; i >= 1; i-- )
		{
		item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );
      if ( item->isSubclassOf( InventoryItem ) )
         {
         item->Drop();
         }
      }
   }

qboolean Sentient::PowerupActive
   (
   void
   )

   {
   if ( poweruptype && this->client )
      {
      gi.SendServerCommand( edict-g_entities, "print \"You are already using a powerup\n\"" );
      }

   return poweruptype;
   }

void Sentient::setModel
	(
	const char *mdl
	)

	{
   // Rebind all active weapons

   DetachAllActiveWeapons();
   Entity::setModel( mdl );
   AttachAllActiveWeapons();
	}

void Sentient::TurnOffShadow
   (
   Event *ev
   )

   {
   edict->s.renderfx &= ~RF_SHADOW;
   }

void Sentient::TurnOnShadow
   (
   Event *ev
   )

   {
   edict->s.renderfx |= RF_SHADOW;
   }

void Sentient::Archive
	(
	Archiver &arc
	)
   {
   int i;
   int num;


   Animate::Archive( arc );

   inventory.Archive( arc );
   if ( arc.Saving() )
      {
      num = ammo_inventory.NumObjects();
      }
   else
      {
      ammo_inventory.ClearObjectList();
      }
   arc.ArchiveInteger( &num );
   for( i = 1; i <= num; i++ )
      {
      Ammo * ptr;

      if ( arc.Loading() )
         {
         ptr = new Ammo;
         ammo_inventory.AddObject( ptr );
         }
      else
         {
         ptr = ammo_inventory.ObjectAt( i );
         }
      arc.ArchiveObject( ptr );
      }

   arc.ArchiveObjectPointer( ( Class ** )&newWeapon );
   arc.ArchiveInteger( &poweruptype );
   arc.ArchiveInteger( &poweruptimer );

   arc.ArchiveInteger( &firing_frame );
   arc.ArchiveInteger( &firing_anim );
   arc.ArchiveVector( &offset_color );
   arc.ArchiveVector( &offset_delta );
   arc.ArchiveFloat( &offset_time );
   arc.ArchiveFloat( &charge_start_time );

	arc.ArchiveString( &blood_model );

   immunities.Archive( arc );

   for( i = 0; i < MAX_ACTIVE_WEAPONS; i++ )
      {
      arc.ArchiveSafePointer( &activeWeaponList[ i ] );
      }

   arc.ArchiveVector( &gunoffset );
   arc.ArchiveVector( &eyeposition );
   arc.ArchiveInteger( &viewheight );
   arc.ArchiveInteger( &means_of_death );
	arc.ArchiveBoolean( &in_melee_attack );
	arc.ArchiveBoolean( &in_block );
	arc.ArchiveBoolean( &in_stun );
      
   arc.ArchiveBoolean( &on_fire );
   arc.ArchiveFloat( &on_fire_stop_time );
   arc.ArchiveFloat( &next_catch_on_fire_time );
   arc.ArchiveInteger( &on_fire_tagnums[ 0 ] );
   arc.ArchiveInteger( &on_fire_tagnums[ 1 ] );
   arc.ArchiveInteger( &on_fire_tagnums[ 2 ] );
	arc.ArchiveSafePointer( &fire_owner );

   arc.ArchiveBoolean( &attack_blocked );
   arc.ArchiveFloat( &attack_blocked_time );

	arc.ArchiveFloat( &max_mouth_angle );
   arc.ArchiveInteger( &max_gibs );

	arc.ArchiveFloat( &next_bleed_time );
   }

void Sentient::ArchivePersistantData
   (
	Archiver &arc
   )

   {
   int i;
   int num;

   // archive the inventory
   if ( arc.Saving() )
      {
      // count up the total number
      num = inventory.NumObjects();
      }
   else
      {
      inventory.ClearObjectList();
      }
   // archive the number
   arc.ArchiveInteger( &num );
   // archive each item
	for( i = 1; i <= num; i++ )
		{
      str name;
      int amount;
      Item * item;

      if ( arc.Saving() )
         {
         Entity * ent;

         ent = G_GetEntity( inventory.ObjectAt( i ) );
         if ( ent && ent->isSubclassOf( Item ) )
            {
            item = ( Item * )ent;
            name = item->model;
            amount = item->getAmount();
            }
         else
            {
            error( "ArchivePersistantData", "Non Item in inventory\n" );
            }
         }
      arc.ArchiveString( &name );
      arc.ArchiveInteger( &amount );
      if ( arc.Loading() )
         {
         item = giveItem( name, amount );
			item->CancelEventsOfType( EV_Weapon_GiveStartingAmmo );
         }
      }

   // archive the ammo inventory
   if ( arc.Saving() )
      {
      // count up the total number
      num = ammo_inventory.NumObjects();
      }
   else
      {
      ammo_inventory.ClearObjectList();
      }
   // archive the number
   arc.ArchiveInteger( &num );
   // archive each item
	for( i = 1; i <= num; i++ )
		{
      str name;
      int amount;
		int maxamount;
      Ammo * ptr;

      if ( arc.Saving() )
         {
         ptr = ammo_inventory.ObjectAt( i );
         name = ptr->getName();
         amount = ptr->getAmount();
			maxamount = ptr->getMaxAmount();
         }
      arc.ArchiveString( &name );
      arc.ArchiveInteger( &amount );
		arc.ArchiveInteger( &maxamount );
      if ( arc.Loading() )
         {
         GiveAmmo( name, amount, maxamount );
         }
      }

   for( i = 0; i < MAX_ACTIVE_WEAPONS; i++ )
      {
      str name;
      if ( arc.Saving() )
         {
         if ( activeWeaponList[ i ] )
            {
            name = activeWeaponList[ i ]->getName();
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
            Weapon * weapon;
	         weapon = ( Weapon * )FindItem( name );
            if ( weapon )
               {
               ChangeWeapon( weapon, ( weaponhand_t )i );
               }
            }
         }
      }

   arc.ArchiveFloat( &health );
   arc.ArchiveFloat( &max_health );
   }


void Sentient::DoubleArmor
   (
   void
   )

   {
   int i,n;

   n = inventory.NumObjects();

	for( i = 1; i <= n; i++ )
		{
		Item  *item;
      item = ( Item * )G_GetEntity( inventory.ObjectAt( i ) );

 		if ( item->isSubclassOf( Armor ) )
         item->setAmount( item->getAmount() * 2 );
      }
   }

void Sentient::WeaponKnockedFromHands
   (
   void
   )

   {
   str realname;

   realname = GetRandomAlias( "snd_lostweapon" );
	if ( realname.length() > 1 )
      {
		Sound( realname.c_str() , CHAN_VOICE );
      }
   else
      {
		Sound( "snd_pain", CHAN_VOICE );
      }
   }

void Sentient::AddImmunity
   (
   Event *ev
   )

   {
	str immune_string;
	int new_immunity;
	int number_of_immunities;
	int i;


	number_of_immunities = ev->NumArgs();

	for ( i = 1 ; i <= number_of_immunities ; i++ )
		{
		immune_string = ev->GetString( i );

		new_immunity = MOD_string_to_int( immune_string );

		if ( new_immunity != -1 )
			immunities.AddUniqueObject( new_immunity );
		}
   }

void Sentient::RemoveImmunity
   (
   Event *ev
   )

   {
	str immune_string;
	int old_immunity;
	int number_of_immunities;
	int i;


	number_of_immunities = ev->NumArgs();

	for ( i = 1 ; i <= number_of_immunities ; i++ )
		{
		immune_string = ev->GetString( i );

		old_immunity = MOD_string_to_int( immune_string );

		if ( old_immunity != -1 && immunities.ObjectInList( old_immunity ) )
			immunities.RemoveObject( old_immunity );
		}
   }

qboolean Sentient::Immune
	(
	int meansofdeath
	)
	{
	int number_of_immunities, i;

	number_of_immunities = immunities.NumObjects();

	for( i = 1 ; i <= number_of_immunities ; i++ )
		{
		if ( meansofdeath == immunities.ObjectAt( i ) )
			return true;
		}

	return false;
	}

Ammo *Sentient::FindAmmoByName
   (
   str name
   )

   {
   int count, i;

   count = ammo_inventory.NumObjects();

   for ( i=1; i<=count; i++ )
      {
      Ammo *ammo = ammo_inventory.ObjectAt( i );
      if ( name == ammo->getName() )
         {
         return ammo;
         }     
      }
   return NULL;
   }

int Sentient::AmmoIndex
   (
   str type
   )

   {
   Ammo *ammo;

   ammo = FindAmmoByName( type );

   if ( ammo )
      return ammo->getIndex();
   else
      return 0;
   }

int Sentient::AmmoCount
   (
   str type
   )

   {
   Ammo *ammo;

   if ( !type.length() )
      return 0;

   ammo = FindAmmoByName( type );

   if ( ammo )
      return ammo->getAmount();
   else
      return 0;
   }

int Sentient::MaxAmmoCount
   (
   str type
   )

   {
   Ammo *ammo;

   ammo = FindAmmoByName( type );

   if ( ammo )
      return ammo->getMaxAmount();
   else
      return 0;
   }

void Sentient::GiveAmmo
   (
   str type,
   int amount,
   int maxamount
   )

   {
   Ammo *ammo;

   ammo = FindAmmoByName( type );

   if ( ammo )
      {
      // Add amount to current amount
      ammo->setAmount( ammo->getAmount() + amount );
      }
   else
      {
      // Create a new inventory entry with this name
      ammo = new Ammo;

		if ( maxamount >= 0 )
         ammo->setMaxAmount( maxamount );

      ammo->setAmount( amount );

      ammo->setName( type );
      ammo_inventory.AddObject( ammo );
      }
   AmmoAmountChanged( ammo );
   }

int Sentient::UseAmmo
   (
   str type,
   int amount
   )

   {
   int count, i;
   
   count = ammo_inventory.NumObjects();

   for ( i=1; i<=count; i++ )
      {
      Ammo *ammo = ammo_inventory.ObjectAt( i );
      if ( type == ammo->getName() )
         {
         int ammo_amount = ammo->getAmount();

         // Less ammo than what we specified to use
         if ( ammo_amount < amount )
            {
            ammo->setAmount( 0 );
            AmmoAmountChanged( ammo );
            return ammo_amount;
            }
         else
            {
            ammo->setAmount( ammo->getAmount() - amount );
            AmmoAmountChanged( ammo );
            return amount;
            }
         }     
      }
   return 0;
   }

void Sentient::AmmoAmountInClipChanged
   (
   str type,
   int amount_in_clip
   )

   {
   int count, i;
   
   count = ammo_inventory.NumObjects();

   for ( i=1; i<=count; i++ )
      {
      Ammo *ammo = ammo_inventory.ObjectAt( i );
      if ( type == ammo->getName() )
         {
         AmmoAmountChanged( ammo, amount_in_clip );
         }     
      }
   }


void Sentient::JumpXY
   (
   Event *ev
   )

   {
   float forwardmove;
   float sidemove;
   float distance;
   float time;
   float speed;
	Vector yaw_forward;
	Vector yaw_left;

   forwardmove = ev->GetFloat( 1 );
   sidemove    = ev->GetFloat( 2 );
   speed       = ev->GetFloat( 3 );

	Vector( 0, angles.y, 0 ).AngleVectors( &yaw_forward, &yaw_left );

   velocity = yaw_forward * forwardmove - yaw_left * sidemove;
   distance = velocity.length();
   velocity *= speed / distance;
   time = distance / speed;
   velocity[ 2 ] = sv_gravity->integer * time * 0.5f;
   }

void Sentient::MeleeAttackStart
   (
   Event *ev
   )

	{
	in_melee_attack = true;
	}

void Sentient::MeleeAttackEnd
   (
   Event *ev
   )

	{
	in_melee_attack = false;
	}

void Sentient::BlockStart
   (
   Event *ev
   )

	{
	in_block = true;
	}

void Sentient::BlockEnd
   (
   Event *ev
   )

	{
	in_block = false;
	}

void Sentient::StunStart
   (
   Event *ev
   )

	{
	in_stun = true;
	}

void Sentient::StunEnd
   (
   Event *ev
   )

	{
	in_stun = false;
	}

void Sentient::ListInventory
   (
   void
   )

   {
   int i,count;

   // Display normal inventory
   count = inventory.NumObjects();

   gi.Printf( "'Name' : 'Amount'\n" );

   for ( i=1; i<=count; i++ )
      {
      int entnum = inventory.ObjectAt( i );
      Item *item = ( Item * )G_GetEntity( entnum );
      gi.Printf( "'%s' : '%d'\n", item->getName().c_str(), item->getAmount() );
      }

   // Display ammo inventory
   count = ammo_inventory.NumObjects();

   for ( i=1; i<=count; i++ )
      {
      Ammo *ammo = ammo_inventory.ObjectAt( i );
      gi.Printf( "'%s' : '%d'\n", ammo->getName().c_str(), ammo->getAmount() );
      }
   }

void Sentient::SetAttackBlocked
   (
   qboolean blocked
   )

   {
   attack_blocked      = blocked;
   attack_blocked_time = level.time;
   }

void Sentient::SetMaxMouthAngle
	(
	Event *ev
	)
	{
   max_mouth_angle = ev->GetFloat( 1 );
   }

void Sentient::TryLightOnFire
	(
	int meansofdeath,
	Entity *attacker
	)
	{
	float chance;
	float min_time;
	float add_time;


	if ( !com_blood->integer )
		return;
	
	// Get the base chance of catching on fire

	if ( meansofdeath == MOD_FIRESWORD )
		chance = .5;
	else
		chance = .05;

	// Get some values based on whether or not the sentient is a player or an actor

	if ( this->isSubclassOf( Player ) )
		{
		chance = chance / 2;
		min_time = 4;
		add_time = 2;
		}
	else
		{
		min_time = 8;
		add_time = 4;
		}

	// Make sure not immune to on_fire

	if ( Immune( MOD_ON_FIRE ) )
		return;

	// See if we should catch the victim on fire
	
	if ( G_Random() < chance )
		{
		Event *event;
		int number_of_tags;
		int i;
		const char *tag_name;
		int number_of_fires_to_add;
		float scale;
		
		if ( !on_fire )
			{
			on_fire_tagnums[0] = -1;
			on_fire_tagnums[1] = -1;
			on_fire_tagnums[2] = -1;
			}

		if ( mass >= 200 )
			number_of_fires_to_add = 3;
		else if ( mass >= 100 )
			number_of_fires_to_add = 2;
		else
			number_of_fires_to_add = 1;

		if ( mass > 200 )
			scale = 1.25;
		else if ( mass >= 300 )
			scale = 1.75;
		else
			scale = 1.00;
			
		number_of_tags = gi.NumTags( edict->s.modelindex );

		if ( number_of_tags )
			{
			for ( i = 0 ; i < number_of_fires_to_add ; i++ )
				{
				if ( !on_fire || G_Random() < chance )
					{
					if ( on_fire && on_fire_tagnums[i] >= 0 )
						{
						tag_name = gi.Tag_NameForNum( edict->s.modelindex, on_fire_tagnums[i] );

						event = new Event( EV_RemoveAttachedModel );
						event->AddString( tag_name );
						event->AddFloat( 0 );
						event->AddString( "models/fx_catchfire.tik" );
						ProcessEvent( event );
						}

					on_fire_tagnums[i] = G_Random( number_of_tags );
					tag_name = gi.Tag_NameForNum( edict->s.modelindex, on_fire_tagnums[i] );

					event = new Event( EV_AttachModel );
					event->AddString( "fx_catchfire.tik" );
					event->AddString( tag_name );
					event->AddFloat( scale );
					ProcessEvent( event );
					}
				}

			if ( !on_fire )
				{
				on_fire = true;
				fire_owner = attacker;
				PostEvent( EV_Sentient_OnFire, FRAMETIME );
				next_catch_on_fire_time = level.time + .15 + G_Random( .2 );
				on_fire_stop_time = level.time + min_time + G_Random( add_time );
				}
			}
		}
	}

void Sentient::OnFire
	(
	Event *ev
	)
	{
	float damage;

	// See if we should stop being on fire

	if ( !on_fire || on_fire_stop_time <= level.time || gi.pointcontents( origin, 0 ) & MASK_WATER )
		{
		// Stop the fire

		ProcessEvent( EV_Sentient_StopOnFire );
		return;
		}

	// Cause a little bit of damage

	if ( this->isSubclassOf( Player ) )
		damage = 0.05;
	else
		damage = 0.1;

	Damage( fire_owner, fire_owner, damage, vec_zero, vec_zero, vec_zero, 0, 0, MOD_ON_FIRE );

	// Try to set other sentients on fire

	if ( next_catch_on_fire_time <= level.time ) 
		{
		MeleeAttack( centroid, centroid, 0.05, fire_owner, MOD_FIRE, maxs[0] + 10, -maxs[2] / 2, maxs[2] / 2, 0, false );
		next_catch_on_fire_time = level.time + .15 + G_Random( .2 );
		}

	// Call this event again next frame

	PostEvent( EV_Sentient_OnFire, FRAMETIME );
   }

void Sentient::StopOnFire
	(
	Event *ev
	)
	{
	int i;
	const char *tag_name;
	Event *event;


	for( i = 0 ; i < 3 ; i++ )
		{
		if ( on_fire_tagnums[i] >= 0 )
			{
			tag_name = gi.Tag_NameForNum( edict->s.modelindex, on_fire_tagnums[i] );

			event = new Event( EV_RemoveAttachedModel );
			event->AddString( tag_name );
			event->AddFloat( 0 );
			event->AddString( "models/fx_catchfire.tik" );
			ProcessEvent( event );
			}
		}

	on_fire = false;
	}

void Sentient::SpawnBloodyGibs
	(
	Event *ev
	)
	{
	str gib_name;
	int number_of_gibs;
	float scale;
	Animate *ent;
	str real_gib_name;

	if ( !com_blood->integer )
		return;

	//if ( GetActorFlag( ACTOR_FLAG_FADING_OUT ) )
	//	return;

	gib_name = GetGibName();

	if ( !gib_name.length() )
		return;

	// Determine the number of gibs to spawn

	if ( ev->NumArgs() > 0 )
		{
		number_of_gibs = ev->GetInteger( 1 );
		}
	else
		{
		if ( max_gibs == 0 )
			return;

		if ( deadflag )
			number_of_gibs = G_Random( max_gibs / 2 ) + 1;
		else
			number_of_gibs = G_Random( max_gibs ) + 1;
		}

	// Make sure we don't have too few or too many gibs

	if ( number_of_gibs <= 0 || number_of_gibs > 9 )
		return;

	if ( ev->NumArgs() > 1 )
		{
		scale = ev->GetFloat( 2 );
		}
	else
		{
		// Calculate a good scale value

		if ( mass <= 50 )
			scale = 1.0;
		else if ( mass <= 100 )
			scale = 1.1;
		else if ( mass <= 250 )
			scale = 1.2;
		else
			scale = 1.3;
		}

	// Spawn the gibs

	real_gib_name = gib_name;
	real_gib_name += number_of_gibs;
	real_gib_name += ".tik";

	ent = new Animate;
	ent->setModel( real_gib_name.c_str() );
	ent->setScale( scale );
	ent->setOrigin( centroid );
	ent->RandomAnimate( "idle" );
	ent->PostEvent( EV_Remove, 1 );

	Sound( "snd_decap", CHAN_BODY, 1, 300 );
	}

void Sentient::SetMaxGibs
	(
	Event *ev
	)
	{
	max_gibs = ev->GetInteger( 1 );
	}

void Sentient::GetStateAnims
   (
   Container<const char *> *c
   )

   {
   }

void Sentient::CheckAnimations
   (
   Event *ev 
   )

   {
   int i,j;
   Container<const char *>co;
   const char *cs;

   GetStateAnims( &co );
   
   gi.DPrintf( "Unused Animations in TIKI\n" );
   gi.DPrintf( "-------------------------\n" );
   for( i=0; i<NumAnims(); i++ )
      {
      const char *c;

      c = gi.Anim_NameForNum( edict->s.modelindex, i );

      for ( j=1; j<=co.NumObjects(); j++ )
         {
         cs = co.ObjectAt( j );

         if ( !stricmp( c, cs ) )
            {
            goto out;
            }
         else if ( !strnicmp( c, cs, strlen( cs ) ) ) // partial match
            {
            int state_len = strlen( cs );

            // Animation in tik file is longer than the state machine's anim
            if ( strlen( c ) > state_len )
               {
               if ( c[state_len] != '_' ) // If next character is an '_' then no match
                  {
                  goto out;
                  }
               }
            else
               {
               goto out;
               }
            }
         }
      // No match made
      gi.DPrintf( "%s used in TIK file but not statefile\n", c );
out:
      ;
      }

   gi.DPrintf( "Unknown Animations in Statefile\n" );
   gi.DPrintf( "-------------------------------\n" );
   for ( j=1; j<=co.NumObjects(); j++ )
      {
      if ( !HasAnim( co.ObjectAt( j ) ) )
         {
         gi.DPrintf( "%s in statefile is not in TIKI\n", co.ObjectAt( j ) );
         }
      }
   }

void Sentient::ReceivedItem
   ( 
   Item * item 
   )
	{
   }

void Sentient::RemovedItem
   ( 
   Item * item 
   )
	{
   }

void Sentient::AmmoAmountChanged
   ( 
   Ammo * ammo,
   int ammo_in_clip
   )
   {
   }

//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/player.h                           $
// $Revision:: 174                                                            $
//   $Author:: Aldie                                                          $
//     $Date:: 7/29/00 2:28p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/player.h                                $
// 
// 174   7/29/00 2:28p Aldie
// Added a nosound weapon check
// 
// 173   7/26/00 6:06p Steven
// Added some reseting of weapon game vars.
// 
// 172   7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 171   7/25/00 12:47p Markd
// Added new player sounds
// 
// 170   7/23/00 8:49p Aldie
// Added some safety nets to the weapon code in sentient and player
// 
// 169   7/22/00 12:52a Markd
// Added can_hang check
// 
// 168   7/21/00 3:47p Steven
// Added some showmodel stuff.
// 
// 167   7/21/00 1:14a Markd
// fixed fakeplayer again
// 
// 166   7/19/00 8:46p Markd
// added checkgroundentity
// 
// 165   7/19/00 7:26p Markd
// fixed weapons holstered code
// 
// 164   7/19/00 5:10p Steven
// Added Loaded proc, gets called after a loadgame is finished so the player
// can process stuff.
// 
// 163   7/19/00 11:02a Markd
// removed weapons_active
// 
// 162   7/18/00 5:19p Markd
// added weapons_active boolean
// 
// 161   7/18/00 4:25p Markd
// rewrote holstering code
// 
// 160   7/17/00 9:51p Aldie
// Added skipcinematic command which is access by pressing the ESC key
// 
// 159   7/17/00 7:45p Markd
// made fakeplayer work better
// 
// 158   7/17/00 4:19p Aldie
// Changed to using v_angle instead of torsoangles for some aiming stuff.
// 
// 157   7/17/00 3:26p Aldie
// Fix for flashbangs, changed detail variable, and added forcetorsostate
// 
// 156   7/17/00 11:57a Aldie
// Changed some methods for checking weapons for attack
// 
// 155   7/16/00 3:08p Aldie
// Added some holster functions for firing and getting the weapons out.
// 
// 154   7/16/00 2:09p Aldie
// Changed some of the player logging
// 
// 153   7/16/00 10:46a Steven
// Improved head target stuff.
// 
// 152   7/15/00 1:34p Aldie
// Added takepain command.  Allows control for taking pain or not.
// 
// 151   7/15/00 1:06p Aldie
// Added specialmove stuff for weapons so we can do special movement with some
// dualhanded weapons
// 
// 150   7/14/00 8:21p Aldie
// Added logstats
// 
// 149   7/12/00 5:36p Markd
// fixed ammo reporting to support bullets in clip
// 
// 148   7/12/00 11:27a Steven
// Changed water to a float.
// 
// 147   7/10/00 11:54p Markd
// added exit level code
// 
// 146   7/10/00 9:27p Markd
// added ammo variables for how much ammo the player has.  Added levelvars and
// gamevars commands
// 
// 145   7/10/00 8:09p Markd
// fixed cool item pickup problems
// 
// 144   7/10/00 10:41a Markd
// added waitforstate
// 
// 143   7/06/00 7:17p Aldie
// Added in HAS_ARMORPIECE state command
// 
// 142   7/05/00 7:37p Steven
// Added more outfit stuff and added it to the saved PersistantData.
// 
// 141   7/05/00 6:15p Steven
// Added a damage multiplier for combos.
// 
// 140   7/05/00 4:17p Markd
// fixed cool item stuff
// 
// 139   7/04/00 6:45p Markd
// enhanced cool item features
// 
// 138   7/04/00 2:25p Markd
// added cool cinematic for new objects
// 
// 137   7/03/00 10:23a Steven
// Added some knockback/knockdown stuff.
// 
// 136   6/30/00 3:08p Markd
// fixed rise animation issues
// 
// 135   6/25/00 11:21a Markd
// fixed slime code for player
// 
// 134   6/20/00 7:55p Markd
// fixed camera position when game is being loaded
// 
// 133   6/17/00 3:48p Aldie
// 
// 132   6/15/00 5:50p Aldie
// Added rise checks
// 
// 131   6/15/00 3:54p Aldie
// Took out the legturn command.  We don't really need it. 
// 
// 130   6/15/00 2:54p Aldie
// Fix for the leg turning issue
// 
// 129   6/14/00 5:40p Aldie
// Added state ammo check for weapon in hand/mode
// 
// 128   6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 127   6/13/00 6:41p Markd
// Fixed pushing and pulling of objects
// 
// 126   6/10/00 1:50p Steven
// Added statemap caching.
// 
// 125   6/06/00 12:19p Markd
// working on player movement
// 
// 124   6/05/00 3:29p Aldie
// Added flickering to waterstats
// 
// 123   6/03/00 3:14p Aldie
// Added damage effects to player and sentient 
// 
// 122   6/02/00 2:01p Markd
// Fixed client persistant data issues
// 
// 121   6/01/00 7:02p Markd
// removed activeWeapon variable
// 
// 120   5/31/00 5:06p Aldie
// New aiming method
// 
// 119   5/30/00 6:54p Aldie
// Added a muzzle clear check
// 
// 118   5/30/00 5:06p Aldie
// Added large shield to prevent knockdowns
// 
// 117   5/30/00 4:42p Aldie
// Added direction support and knockdown support to player
// 
// 116   5/27/00 5:14p Steven
// Added player head watch stuff.
// 
// 115   5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 114   5/27/00 9:49a Steven
// Added RemoveTarget stuff.
// 
// 113   5/26/00 2:24p Aldie
// Added waitforplayer commands so we can use it for cinematics when waiting
// for player to finish holstering
// 
// 112   5/25/00 4:15p Aldie
// Added weapon holstering while crouching
// 
// 111   5/24/00 3:14p Markd
// first phase of save/load games
// 
// 110   5/15/00 2:19p Aldie
// Added new tempmodel system and added player accumulated pain
// 
// 109   5/08/00 3:20p Aldie
// Added initial crosshair work
// 
// 108   5/06/00 5:25p Markd
// fixed camera and pipe hang issues
// 
// 107   5/04/00 4:59p Markd
// Added setAngles and putawayweapons
// 
// 106   5/02/00 3:15p Steven
// Added player watching actors that talk to her.
// 
// 105   5/01/00 2:47p Steven
// Added IncreaseActionLevel.
// 
// 104   5/01/00 11:31a Markd
// Added SetWaterPower to Player
// 
// 103   4/29/00 11:28a Markd
// removed old rope code, cleaned up rope interface
// 
// 102   4/24/00 7:07p Aldie
// Removed old code to try and fix inconsistency between legs and torso for
// firing when moving and standing.  It's all done in the state machine now.
// 
// 101   4/15/00 5:40p Markd
// fixed falling damage and getting into and out of water
// 
// 100   4/15/00 1:30p Markd
// added check_was_running code so that player does not always stop short
// 
// 99    4/14/00 6:04p Aldie
// Added checksolidforward to state system
// 
// 98    4/13/00 5:31p Steven
// Added a checkshgliekdead check
// 
// 97    4/10/00 11:18a Markd
// Added new rope code
// 
// 96    4/07/00 10:17a Markd
// fixed shgliek pickup and weapon holstering
// 
// 95    4/05/00 8:41p Markd
// Added water_level conditional
// 
// 94    4/04/00 11:02a Markd
// put in checkcanclimb and feet checks
// 
// 93    4/03/00 4:21p Steven
// Changed right_arm_target and left_arm_target to EntityPtrs.
// 
// 92    3/31/00 3:19p Markd
// Added UseObject functionality
// 
// 91    3/22/00 2:05p Aldie
// Added holster command
// 
// 90    3/21/00 6:08p Markd
// Added invehicle check
// 
// 89    3/21/00 5:05p Markd
// Added DamageFeedback and vehicle support
// 
// 88    3/20/00 6:09p Steven
// Added SetMouthAngle.
// 
// 87    3/18/00 3:55p Markd
// working on player turning
// 
// 86    3/18/00 2:42p Markd
// added facing up and down slopes
// 
// 85    3/17/00 6:37p Markd
// Added chance conditional
// 
// 84    3/16/00 3:35p Aldie
// Added checkpain state back instead of forcing it
// 
// 83    3/16/00 10:20a Markd
// fixed useanim firing its targets before the animation was completed
// 
// 82    3/15/00 4:09p Aldie
// Fixed a bug with using weapons, and added some ability to force a state in
// the player
// 
// 81    3/13/00 5:18p Aldie
// Made some changes for usable inventory item stuff
// 
// 80    3/04/00 12:29p Jimdose
// separated feet checks into their own functions
// 
// 79    3/02/00 11:12a Markd
// Added additional SetReverb function
// 
// 78    3/02/00 10:48a Steven
// Changed reverb interface.
// 
// 77    3/01/00 8:44p Jimdose
// added turning for monkey bars
// made move checks provide pass/fail results
// added checks for feet and falling when both feet aren't on the ground
// 
// 76    2/28/00 6:33p Aldie
// Added more advanced pain state checks
// 
// 75    2/26/00 7:09p Jimdose
// added better movement checks for pipecrawl, monkey bars
// added checks to prevent player from going into walk or run animation while
// move is blocked
// fixed setting step height when stepping  up
// 
// 74    2/26/00 11:50a Jimdose
// added slope checks
// 
// 73    2/25/00 7:27p Markd
// Added useanim_numloop support and fixed useanim_orientation
// 
// 72    2/25/00 5:02p Aldie
// Changed some reloading and put in a fix for the animation problem with the
// firing of the weapons 
// 
// 71    2/24/00 7:26p Aldie
// Added dual wielding
// 
// 70    2/24/00 4:18p Jimdose
// removed some unused variables
// added ladder movement
// 
// 69    2/23/00 5:27p Aldie
// Changed return value of function
// 
// 68    2/22/00 1:57p Jimdose
// added pushobjects
// 
// 67    2/17/00 6:26p Aldie
// Fixed naming conventions for weapon hand and also added various attachtotag
// functionality for weapons that attach to different tags depending on which
// hand they are wielded in.
// 
// 66    2/17/00 4:16p Jimdose
// made statemap_Legs and statemap_Torso part of player instead of global
// removed redundant physics variables
// 
// 65    2/16/00 4:01p Aldie
// Added shield functionality
// 
// 64    2/15/00 8:57p Jimdose
// changed blocked to moveresult
// 
// 63    2/14/00 7:34p Aldie
// Fixed some autotargeting issues
// 
// 62    2/14/00 5:41p Jimdose
// got rid of unneeded debugging variables
// 
// 61    2/09/00 8:02p Aldie
// Added loopfire weapons
// 
// 60    2/08/00 6:35p Aldie
// Added more blocking code to player and sentient
// 
// 59    2/08/00 11:34a Steven
// Added picking up of Shgliek.
// 
// 58    2/08/00 12:17a Jimdose
// made rope grabbing controlled by state system
// 
// 57    2/07/00 7:38p Aldie
// Fixed swiping, also various weapons fixes for sword and for sling
// 
// 56    2/04/00 7:28p Aldie
// Combat code - blocking and combos
// 
// 55    2/04/00 3:11p Aldie
// Changed sword attack method for water usage
// 
// 54    2/03/00 2:56p Aldie
// Sword and water coding
// 
// 53    2/02/00 4:28p Aldie
// Added some new state checks for combo help
// 
// 52    2/01/00 5:40p Markd
// Fixed Camera cutting issues
// 
// 51    2/01/00 5:28p Aldie
// More updates for auto aiming
// 
// 50    1/31/00 7:56p Aldie
// Added some new states and improved arm tracking
// 
// 49    1/31/00 6:03p Jimdose
// added rope_touch
// 
// 48    1/31/00 3:56p Aldie
// working on the auto aim / tracking code
// 
// 47    1/29/00 6:17p Aldie
// Fixed some problems when state doesn't exist.
// 
// 46    1/29/00 11:27a Jimdose
// made ropes work with state system
// 
// 45    1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 44    1/25/00 8:06p Jimdose
// added hardimpact
// 
// 43    1/24/00 6:56p Steven
// Added reverb stuff.
// 
// 42    1/24/00 2:50p Jimdose
// added rope checks
// 
// 41    1/22/00 4:05p Jimdose
// added pipe crawl and step up
// 
// 40    1/20/00 7:11p Jimdose
// added checkcanwallhug
// added movecontrol
// 
// 39    1/19/00 10:02p Jimdose
// added airspeed
// 
// 38    1/19/00 7:59p Markd
// Rewrote Surface Model Event and also added changeoutfit command to player
// 
// 37    1/17/00 10:20p Jimdose
// Rewrote state system initialization.  Made conditionals defined with array.
// Made Evaluate functions early exit
// 
// 36    1/16/00 5:43p Aldie
// Made weapon tag vars
// 
// 35    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 34    1/15/00 1:36p Markd
// Added UseAnim and TouchUseAnim functionality to Player and game
// 
// 33    1/14/00 5:07p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 32    1/12/00 8:06p Markd
// Added CameraCut function
// 
// 31    1/12/00 3:17p Aldie
// Added some water functionality
// 
// 30    1/10/00 10:30a Jimdose
// removed unused code
// 
// 29    1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 28    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 27    12/20/99 6:51p Steven
// Moved jumpxy to sentient.
// 
// 26    12/20/99 6:37p Markd
// Made camera cutting work properly
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
// 23    12/14/18 2:44p Jimdose
// added monkey bar movement
// 
// 22    12/13/99 10:14a Aldie
// Temp update for bug fixing due to merge
// 
// 21    12/10/99 6:11p Jimdose
// added movement check functions
// 
// 20    12/10/99 2:54p Aldie
// Added L and R ARM tags
// 
// 19    12/10/99 11:17a Jimdose
// got rid of unused movement functions
// 
// 18    12/09/99 7:38p Jimdose
// improved grabbing and hanging onto walls
// 
// 17    12/08/99 7:00p Aldie
// Wrote some head tracking code
// 
// 16    12/01/99 11:26a Aldie
// Couple of fixes for emitters and more ammo stuff
// 
// 15    11/29/99 6:32p Aldie
// Lots of changes for ammo system
// 
// 14    11/19/99 5:45p Aldie
// Update for primary and alternate fire weapons.  Removed PRIMARY and SECONDAY
// mode weapons of Sin, removed SILENCED properties, and changed ammo types to
// use the new system.  Still need to fix ammo checking for weapons.
// 
// 13    11/11/99 5:25p Jimdose
// added separate torso animation
// 
// 12    11/09/99 8:05p Markd
// Added SetViewAngles and also made a SetFOV function
// 
// 11    11/05/99 7:31p Aldie
// Angles adjustment
// 
// 10    10/29/99 7:21p Aldie
// Rope stuff
// 
// 9     10/29/99 6:49p Jimdose
// added SwingAngles and PlayerAngles
// 
// 8     10/28/99 6:33p Markd
// Added fakeplayer ability, also added CloneEntity
// 
// 7     10/28/99 11:55a Aldie
// Rope stuff
// 
// 6     10/28/99 10:42a Aldie
// Added rope functions
// 
// 5     10/27/99 12:19p Markd
// added smooth camera lerping
// 
// 4     10/19/99 7:53p Markd
// Eliminated 3 part model system
// 
// 3     10/18/99 6:10p Jimdose
// got rid of separate state machine for torso and legs
// now use skeletal model for player
// 
// 2     10/12/99 2:23p Markd
// Rewrote camera and player movetype system
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 32    9/02/99 7:29p Jimdose
// added checks for doors
// 
// 31    9/02/99 4:39p Jimdose
// only get hurt when damage > 15
// 
// 30    9/01/99 1:44p Jimdose
// made DoUse a script called event
// removed CheckButtons
// 
// 29    8/31/99 7:40p Jimdose
// added check for if she has a weapon
// added movement speed based on animation
// 
// 28    8/30/99 10:26p Jimdose
// added check for jump flip
// 
// 27    8/27/99 4:49p Jimdose
// separated state machine into two, one for torso, one for legs
// 
// 26    8/23/99 10:16a Jimdose
// added better falling checks
// 
// 25    8/18/99 4:15p Jimdose
// added conditionals for health, death, and pain
// 
// 24    8/17/99 4:52p Jimdose
// added oldorigin
// added various checks for physics
// added JumpXY
// 
// 23    8/12/99 8:04p Jimdose
// working on climbing stuff
// 
// 22    8/11/99 7:58p Jimdose
// preliminary climbing code in
// 
// 21    8/11/99 11:52a Aldie
// Added giveweapon cheat
// 
// 20    8/10/99 6:46p Aldie
// Added some better condition logic and sword attack
// 
// 19    8/10/99 11:36a Aldie
// Update of the weapons system
// 
// 18    8/10/99 10:48a Jimdose
// added hang_pullup_distance and blocked
// 
// 17    8/06/99 6:40p Aldie
// Started moving over to new weapons system
// 
// 16    7/30/99 7:53p Markd
// Added jumping ability to the player
// 
// 15    7/07/99 2:53p Jimdose
// added ResetState and LoadStateTable
// 
// 14    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
//
// DESCRIPTION:
// Class definition of the player.
// 

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "g_local.h"
#include "vector.h"
#include "entity.h"
#include "weapon.h"
#include "sentient.h"
#include "navigate.h"
#include "misc.h"
#include "bspline.h"
#include "camera.h"
#include "specialfx.h"
#include "characterstate.h"
#include "actor.h"
#include "sword.h"
#include "vehicle.h"
#include "rope.h"

extern Event EV_Player_EndLevel;
extern Event EV_Player_GiveCheat;
extern Event EV_Player_GodCheat;
extern Event EV_Player_NoTargetCheat;
extern Event EV_Player_NoClipCheat;
extern Event EV_Player_GameVersion;
extern Event EV_Player_Fov;
extern Event EV_Player_WhatIs;
extern Event EV_Player_Respawn;
extern Event EV_Player_WatchActor;
extern Event EV_Player_StopWatchingActor;
extern Event EV_Player_DoStats;

#define HEAD_TAG        0
#define TORSO_TAG       1
#define L_ARM_TAG       2
#define R_ARM_TAG       3
#define MOUTH_TAG			4

enum painDirection_t 
   { 
   PAIN_NONE, 
   PAIN_FRONT,
   PAIN_LEFT,
   PAIN_RIGHT,
   PAIN_REAR
   };

typedef void ( Player::*movecontrolfunc_t )( void );

class ActiveWeapon : public Class
   {
   public:
      WeaponPtr      weapon;
      weaponhand_t   hand;      
      ActiveWeapon();      
      void Archive( Archiver &arc );
   };

inline ActiveWeapon::ActiveWeapon
   (
   )

   {
   weapon = NULL;
   hand   = WEAPON_ERROR;
   }

inline void ActiveWeapon::Archive
   (
   Archiver &arc
   )

   {
   arc.ArchiveObjectPointer( ( Class ** )&weapon );
   ArchiveEnum( hand, weaponhand_t );
   }

class DualWieldWeapon : public Class
   {
   public:
      str name;
      weaponhand_t hand;
      void Archive( Archiver &arc );
   };

inline void DualWieldWeapon::Archive
   (
   Archiver &arc
   )

   {
   arc.ArchiveString( &name );
   ArchiveEnum( hand, weaponhand_t );
   }


class Player : public Sentient
	{
	private:
      static Condition<Player> Conditions[];
      static movecontrolfunc_t MoveStartFuncs[];
      
      StateMap          *statemap_Legs;
      StateMap          *statemap_Torso;

      State             *currentState_Legs;
      State             *currentState_Torso;
      str               last_torso_anim_name;
      str               last_leg_anim_name;
      movecontrol_t     movecontrol;
      int               last_camera_type;

	   EntityPtr         crosshair;
      ActiveWeapon      newActiveWeapon;
      EntityPtr			head_target;
		float					look_at_time;
      EntityPtr			right_arm_target;
      EntityPtr			left_arm_target;
      qboolean          shield_active;
      qboolean          crouch_flag;

      qboolean                      dual_wield_active;
      Container<DualWieldWeapon *>  dual_wield_weaponlist;
      
      WeaponPtr         holsteredWeapons[MAX_ACTIVE_WEAPONS];
      
      str               partAnim[ 3 ];

      bool              animdone_Legs;
      bool              animdone_Torso;
   
      Vector				oldvelocity;
      Vector            old_v_angle;
      Vector				oldorigin;
      float             animspeed;
      float             airspeed;

		// blend
		float					blend[ 4 ];		// rgba full screen effect
		float					fov;				// horizontal field of view 

		friend class		Camera;
		friend class		Vehicle;

      // vehicle stuff
		VehiclePtr			vehicle;

		// aiming direction
		Vector				v_angle;

      int               buttons;
		int					new_buttons;
		float					respawn_time;
      
      float             water_power;
      float             max_water_power;
		
      int               last_attack_button;

      // Rope
      Rope              *rope_grabbed;
      Rope              *rope_touch;

		// damage blend
		float					damage_blood;
		float					damage_alpha;
		Vector				damage_blend;
		Vector				damage_from;         // the direciton of incoming damage
		Vector				damage_angles;       // the damage angle adjustment that should be applied to the player
		float					damage_count;        // incoming damage which is decayed over time

		float					bonus_alpha;

		float					next_drown_time;     // how long until we drown again
		float					next_painsound_time;      // when we should make a pain sound again
		float					air_finished;

		int					old_waterlevel;
		int					drown_damage;

      str               waitForState;        // if not null, than player will clear waitforplayer when this state is hit
		CameraPtr			camera;
		CameraPtr			actor_camera;
		CameraPtr			cool_camera;
		ActorPtr				actor_to_watch;
		qboolean				actor_camera_right;
		qboolean				starting_actor_camera_right;

      // music stuff

      float             action_level;

      int               music_current_mood;
      int               music_fallback_mood;

		float					music_current_volume;
		float					music_saved_volume;
		float					music_volume_fade_time;

		int					reverb_type;
		float					reverb_level;

      qboolean          gibbed;
      float             pain;
      painDirection_t   pain_dir;
      meansOfDeath_t    pain_type;
      bool              take_pain;
      float             accumulated_pain;
      int               nextpaintime;
      bool              knockdown;

      bool              canfall;
      bool              falling;
      int               feetfalling;
      Vector            falldir;

      bool              hardimpact;

      qboolean          music_forced;

      usercmd_t         last_ucmd;

      // movement variables
      Vector            base_righthand_pos;
      Vector            base_lefthand_pos;
      Vector            righthand_pos;
      Vector            lefthand_pos;

      Vector            base_rightfoot_pos;
      Vector            base_leftfoot_pos;
      Vector            rightfoot_pos;
      Vector            leftfoot_pos;

      int               pm_lastruntime;   // the last runtime before Pmove

      float             animheight;

      Vector            yaw_forward;
      Vector            yaw_left;

      EntityPtr         atobject;
      float             atobject_dist;
      Vector            atobject_dir;

      bool              pickup_enemy;     // set to true when we want to pickup our enemy but are still waiting to put
                                          // away our weapons
      bool					have_shgliek;
      EntityPtr         toucheduseanim;
      int               useanim_numloops; // number of times to loop the animation
      EntityPtr         useitem_in_use;   // used so that we can trigger targets after the useitem is finished
      EntityPtr         cool_item;        // we picked up a cool item and are waiting to show it off
      str               cool_dialog;      // dialog to play when we get it
      str               cool_anim;        // anim to play after the cinematic

      float             ledgeheight_left;
      float             ledgeheight_right;
      float             monkeybar_left;
      float             monkeybar_right;
      float             monkeybar_dir;
      EntityPtr         horizontalpipe;
      float             move_left_dist;
      float             move_right_dist;
      float             move_backward_dist;
      float             move_forward_dist;
      int               moveresult;
      qboolean          do_rise;          // whether or not the player should go into the rise animation
      qboolean          weapons_holstered_by_code; // whether or not we initiated a holstering for a specific animation
      
      // leg angles
	   qboolean	         yawing;
	   qboolean	         yawing_left;
	   qboolean	         yawing_right;
      qboolean          adjust_torso;

      Vector            torsoAngles;
      Vector            headAngles;
      Vector            headAimAngles;
      Vector            torsoAimAngles;
      Vector            rightArmAimAngles;
      Vector            leftArmAimAngles;

      int               oldstats[MAX_STATS];

		float					damage_multiplier;

		int					outfit_level;

      // dummyPlayer stuff
      qboolean          fakePlayer_active;
      SafePtr<class Actor> fakePlayer;

		Container<Conditional *> legs_conditionals;
		Container<Conditional *> torso_conditionals;

	public:
      qboolean          returntrue( Conditional &condition );
      qboolean          checkturnleft( Conditional &condition );
      qboolean          checkturnright( Conditional &condition );
      qboolean          checkforward( Conditional &condition );
      qboolean          checkbackward( Conditional &condition );
      qboolean          checkstrafeleft( Conditional &condition );
      qboolean          checkstraferight( Conditional &condition );
      qboolean          checkjump( Conditional &condition );
      qboolean          checkcrouch( Conditional &condition );
      qboolean          checkjumpflip( Conditional &condition );
      qboolean          checkanimdone_legs( Conditional &condition );
      qboolean          checkanimdone_torso( Conditional &condition );
      qboolean          checkattackleft( Conditional &condition );
      qboolean          checkattackright( Conditional &condition );
      qboolean          checkattackbuttonleft( Conditional &condition );
      qboolean          checkattackbuttonright( Conditional &condition );
      qboolean          checksneak( Conditional &condition );
      qboolean          checkrun( Conditional &condition );
      qboolean          checkwasrunning( Conditional &condition );
      qboolean          checkholsterweapon( Conditional &condition );
      qboolean          checkuse( Conditional &condition );
      qboolean          checkcanturn( Conditional &condition );
      qboolean          checkcanmoveright( Conditional &condition );
      qboolean          checkcanmoveleft( Conditional &condition );
      qboolean          checkcanmovebackward( Conditional &condition );
      qboolean          checkcanmoveforward( Conditional &condition );
      qboolean          checkcanwallhug( Conditional &condition );
      qboolean          checkblocked( Conditional &condition );
      qboolean          checkhangatwall( Conditional &condition );   
      qboolean          checktouchrope( Conditional &condition );
      qboolean          checkcanclimbrope( Conditional &condition );
      qboolean          checkonrope( Conditional &condition );
      qboolean          checkonground( Conditional &condition );
      qboolean          check22degreeslope( Conditional &condition );
      qboolean          check45degreeslope( Conditional &condition );
      qboolean          checkrightleghigh( Conditional &condition );
      qboolean          checkleftleghigh( Conditional &condition );
      qboolean          checkcanhang( Conditional &condition );
      qboolean          checkcanhangleft( Conditional &condition );
      qboolean          checkcanhangright( Conditional &condition );
      qboolean          checkcanfall( Conditional &condition );
      qboolean          checkatdoor( Conditional &condition );
		qboolean          checkatshgliek( Conditional &condition );
		qboolean          checkhaveshgliek( Conditional &condition );
		qboolean          checkshgliekdead( Conditional &condition );
      qboolean          checkfalling( Conditional &condition );
      qboolean          checkgroundentity( Conditional &condition );
      qboolean          checkhardimpact( Conditional &condition );
      qboolean          checkcangrabledge( Conditional &condition );
      qboolean          checkledgeheight( Conditional &condition );
      qboolean          checkcangrabpipe( Conditional &condition );
      qboolean          checkcangrabmonkeybar( Conditional &condition );
      qboolean          checkcanpullup( Conditional &condition );
      qboolean          checkdead( Conditional &condition );
      qboolean          checkhealth( Conditional &condition );
      qboolean          checkpain( Conditional &condition );
      qboolean          checkpaindirection( Conditional &condition );
      qboolean          checkaccumulatedpain( Conditional &condition );
      qboolean          checkpaintype( Conditional &condition );
      qboolean          checkpainthreshold( Conditional &condition );
      qboolean          checkknockdown( Conditional &condition );
      qboolean          checklegsstate( Conditional &condition );
      qboolean          checktorsostate( Conditional &condition );
      qboolean          checkatuseanim( Conditional &condition );
      qboolean          checktouchuseanim( Conditional &condition );
      qboolean          checkatuseobject( Conditional &condition );
      qboolean          checkloopuseobject( Conditional &condition );
      qboolean          checkuseweaponleft( Conditional &condition );
      qboolean          checknewweapon( Conditional &condition );
      qboolean          checkuseweapon( Conditional &condition );
      qboolean          checkhasweapon( Conditional &condition );
      qboolean          checkweaponactive( Conditional &condition );
      qboolean          checkweaponreadytofire( Conditional &condition );
      qboolean          checkweaponreadytofire_nosound( Conditional &condition );
      qboolean          checkmuzzleclear( Conditional &condition );
      qboolean          checkputawayleft( Conditional &condition );
      qboolean          checkputawayright( Conditional &condition );
      qboolean          checkputawayboth( Conditional &condition );
      qboolean          checktargetacquired( Conditional &condition );
      qboolean          checkanyweaponactive( Conditional &condition );
      qboolean          checkstatename( Conditional &condition );
      qboolean          checkattackblocked( Conditional &condition );
      qboolean          checkblockdelay( Conditional &condition );
      qboolean          checkcanstand( Conditional &condition );
      qboolean          checkpush( Conditional &condition );
      qboolean          checkpull( Conditional &condition );
      qboolean          checkladder( Conditional &condition );
      qboolean          checkfeetatladder( Conditional &condition );
      qboolean          checkcanclimbladder( Conditional &condition );
      qboolean          checkdualwield( Conditional &condition );
      qboolean          checkdualweapons( Conditional &condition );
      qboolean          checkuseanimfinished( Conditional &condition );
      qboolean          checkchance( Conditional &condition );
      qboolean          checkfacingupslope( Conditional &condition );
      qboolean          checkfacingdownslope( Conditional &condition );
      qboolean          checkturnedleft( Conditional &condition );
      qboolean          checkturnedright( Conditional &condition );
      qboolean          checkinvehicle( Conditional &condition );
      qboolean          checkwaterlevel( Conditional &condition );
      qboolean          checkpickupenemy( Conditional &condition );
      qboolean          checksolidforward( Conditional &condition );
      qboolean          checkholstercomplete( Conditional &condition );
      qboolean          checkweaponhasammo( Conditional &condition );
      qboolean          checkrise( Conditional &condition );
      qboolean          checkcoolitem( Conditional &condition );
      qboolean          checkarmorpiece( Conditional &condition );
      qboolean          checkspecialmove( Conditional &condition );
      qboolean          checkweaponsholstered( Conditional &condition );
      qboolean          checkdualweaponreadytofire( Conditional &condition );
      qboolean          checkfakeplayeractive( Conditional &condition );
      qboolean          checkfakeplayerholster( Conditional &condition );

      // movecontrol functions
      void              StartHang( void );
      void              StartPipeCrawl( void );
      void              StartMonkeyBars( void );
      void              StartStepUp( void );
      void              RopeGrab( void );
      void              RopeRelease( void );
		void              StartPickup( void );
      void              StartPush( void );
      void              StartClimbWall( void );
		void              StartUseAnim( void );
		void              StartLoopUseAnim( void );
		void              SetupUseObject( void );

      void              StartUseObject( Event *ev );
      void              FinishUseObject( Event *ev );
      void              FinishUseAnim( Event *ev );
      void					PickupShgliek( Event *ev );
		void					ThrowShgliek( Event *ev );
      void					StepUp( Event *ev );
      void					Turn( Event *ev );
      void					TurnUpdate( Event *ev );
      void					TurnLegs( Event *ev );

      CLASS_PROTOTYPE( Player );
      
								Player();
		      				~Player();
		void		         Init( void );

		void		         InitSound( void );
		void		         InitEdict( void );
		void		         InitClient( void );
		void		         InitPhysics( void );
		void		         InitPowerups( void );
		void		         InitWorldEffects( void );
		void		         InitWeapons( void );
		void		         InitView( void );
		void		         InitModel( void );
		void		         InitState( void );
		void		         InitHealth( void );
		void		         InitWaterPower( void );
      void              InitInventory( void );
      void              ChooseSpawnPoint( void );
                        
		void		         EndLevel( Event *ev );
		void		         Respawn( Event *ev );
                        
      void		         SetDeltaAngles( void );
      virtual void      setAngles( Vector ang );
                        
		void		         DoUse( Event *ev );
		void		         Obituary( Entity *attacker, Entity *inflictor, int meansofdeath );
		void		         Killed( Event *ev );
      void		         Dead( Event *ev );
		void		         Pain( Event *ev );
                        
		void		         TouchStuff( pmove_t *pm );

		void		         GetMoveInfo( pmove_t *pm );
		void		         SetMoveInfo( pmove_t *pm, usercmd_t *ucmd );	
		pmtype_t	         GetMovePlayerMoveType( void );
		void		         ClientMove( usercmd_t *ucmd );
//      qboolean          feetOnGround( Vector pos );
//      Vector            findBestFallPos( Vector pos );
//      void              CheckFeet( void );
      void              CheckMoveFlags( void );
		void					ClientThink( Event *ev );

      void              LoadStateTable( void );
      void              ResetState( Event *ev );
      void              EvaluateState( State *forceTorso=NULL, State *forceLegs=NULL );

      void              CheckGround( void );
      void              UpdateViewAngles( usercmd_t *cmd );
      qboolean          AnimMove( Vector &move, Vector *endpos = NULL );
      qboolean          TestMove( Vector &pos, Vector *endpos = NULL  );
      qboolean          PipeMove( Vector &move, Vector *endpos = NULL );
      qboolean          MonkeyBarMove( Vector &move, Vector *endpos = NULL );
      qboolean          CheckMove( Vector &move, Vector *endpos = NULL );
      qboolean          RopeMove( Vector &move, Vector *endpos = NULL );

      float             CheckMoveDist( Vector &delta );
      float             TestMoveDist( Vector &pos );

      void              EndAnim_Legs( Event *ev );
      void              EndAnim_Torso( Event *ev );
      void              SetAnim( const char *anim, bodypart_t part = legs );

		void		         EventUseItem( Event *ev );
		void		         TouchedUseAnim( Entity * ent );

		void		         GiveCheat( Event *ev );
      void		         GiveWeaponCheat( Event *ev );
		void		         GiveAllCheat( Event *ev );
		void		         GodCheat( Event *ev );
		void		         NoTargetCheat( Event *ev );
		void		         NoclipCheat( Event *ev );
		void		         Kill( Event *ev );
      void		         GibEvent( Event *ev );
		void		         SpawnEntity( Event *ev );
      void              SpawnActor( Event *ev );
      void              ListInventoryEvent( Event *ev );

		void					GameVersion( Event *ev );
		void					Fov( Event *ev );

      void              GetPlayerView( Vector *pos, Vector *angle );

		float		         CalcRoll( void );
		void		         WorldEffects( void );
		void		         AddBlend( float r, float g, float b, float a );
		void		         CalcBlend( void );
		void		         DamageFeedback( void );

      void              UpdateStats( void );
      void              StatCount( int index, int count );
      void              UpdateMusic( void );
      void              UpdateWeapons( void );
      void              UpdateSword( Sword *sword );
		void					UpdateReverb( void );
      void              UpdateMisc( void );

      void					SetReverb( str type, float level );
      void					SetReverb( int type, float level );
		void					SetReverb( Event *ev );

      void              SetWaterPower( float water );
      float             GetWaterPower( void );

      Camera            *CurrentCamera( void );
      void              SetCamera( Camera *ent, float switchTime );
      void              CameraCut( void );
      void              CameraCut( Camera *ent );

		void		         SetPlayerView( Camera * camera, Vector position, float cameraoffset, Vector ang, Vector vel, float camerablend[ 4 ], float camerafov );
		void		         SetupView( void );

      void              ProcessPmoveEvents( int event );

      void              SwingAngles( float destination, float swingTolerance, float clampTolerance, float speed, float *angle, qboolean *swinging );
      void              PlayerAngles( void );
		void		         FinishMove( void );
		void		         EndFrame( Event *ev );
		
		void		         TestThread( Event *ev );
      void              useWeapon( const char *weaponname, weaponhand_t hand );
      void              useWeapon( Weapon *weapon, weaponhand_t hand );   

		void		         GotKill( Event *ev );
      void              SetPowerupTimer( Event *ev );
      void              UpdatePowerupTimer( Event *ev );

		void		         WhatIs( Event *ev );
      void              ActorInfo( Event *ev );
		void		         Taunt( Event *ev );

      void              ChangeMusic( const char * current, const char * fallback, qboolean force );
		void		         ChangeMusicVolume( float volume , float fade_time);
		void		         RestoreMusicVolume( float fade_time );

      void              GravityNodes( void );
	   void              Archive( Archiver &arc );
      void              ArchivePersistantData( Archiver &arc );

      void              GiveOxygen( float time );

		void		         KillEnt( Event *ev );
		void		         RemoveEnt( Event *ev );
		void		         KillClass( Event *ev );
		void		         RemoveClass( Event *ev );

      void              Jump( Event *ev );
      void              JumpXY( Event *ev );

      void              ActivateNewWeapon( Event *ev );
      void              ActivateDualWeapons( Event *ev );
      void              DeactivateWeapon( Event *ev );
      void              PutawayWeapon( Event *ev );
      void              SwordAttackEvent( Event *ev );
      void              ActivateShield( Event *ev );
      void              DeactivateShield( Event *ev );
      qboolean          ShieldActive( void );
      qboolean          LargeShieldActive( void );

      void              StartFakePlayer( void );
      void              FakePlayer( qboolean holster );
      void              RemoveFakePlayer( void );
      void              SetViewAngles( Vector angles );
      void              SetFov( float newFov );

      bool              IsNewActiveWeapon( void );
      Weapon            *GetNewActiveWeapon( void );
      weaponhand_t      GetNewActiveWeaponHand( void );
      void              ClearNewActiveWeapon( void );

      void              AdjustAnglesForAttack( void );
      Entity            *FindEnemyInFOV( float fov, float maxdist );
      Entity            *FindEnemyInFOVFromTagWithOffset( float fov, float maxdist, str tagname, Vector offset );
      void              DumpState( Event *ev );
      void              ForceTorsoState( Event *ev );

      void              SetHeadTarget( Event *ev );
      Vector            GetAngleToTarget( Entity *ent, str tag, float yawclamp, float pitchclamp, Vector baseangles );

      void              AutoAim( void );
      void              AcquireTarget( void );
		void					RemoveTarget( Entity *ent_to_remove );
		void					AcquireHeadTarget( void );
      Vector            CalcArmTracking( int controller_tag, str weapon_tagname, Vector baseAngles, Entity *target, Weapon *weapon );

      void              ChangeOutfit( Event *ev );
		void              SetOutfit( int stage );
		int					GetOutfit( void );
      void              SetCurrentCombo( Event *ev );

      qboolean          GetTagPositionAndOrientation( str tagname, orientation_t *new_or );
      qboolean          GetTagPositionAndOrientation( int tagnum, orientation_t *new_or );

      void              DebugWeaponTags( int controller_tag, Weapon *weapon, str weapon_tagname );
      void              SwipeOn( Event *ev );
      void              SwipeOff( Event *ev );
      void              ClearLeftArmTarget( Event *ev );
      void              ClearRightArmTarget( Event *ev );
      void              AdjustTorso( Event *ev );
      void              UseDualWield( Event *ev );
      void              DualWield( Event *ev );
      void              EvaluateTorsoAnim( Event *ev );
      void              CheckReloadWeapons( void );
      void              NextPainTime( Event *ev );
      void              SetTakePain( Event *ev );

		void              SetMouthAngle( Event *ev );

      void              EnterVehicle( Event *ev );
      void              ExitVehicle( Event *ev );
      void              Holster( Event *ev );
      void              HolsterToggle( Event *ev );
      void              SetWaterPower( Event *ev );

      // rope stuff
      void              GrabRope( Entity * rope );
      qboolean          OnRope( void );
      void              TouchRope( Entity * rope );

		void					IncreaseActionLevel( float action_level_increase );

		void					WatchActor(	Event *ev );
		void					StopWatchingActor(	Event *ev );
      void              WeaponCommand( Event *ev );
      void              PlayerDone( Event *ev );
      painDirection_t   Pain_string_to_int( str pain );
      inline Vector     GetTorsoAngles( void ) { return torsoAngles; };
      inline Vector     GetVAngles( void ){ return v_angle; }
      void              SpawnDamageEffect( meansOfDeath_t mod );
      virtual void      GetStateAnims( Container<const char *> *c );
      virtual void      VelocityModified( void );
		int					GetKnockback( int original_knockback, qboolean blocked );
      virtual void      ReceivedItem( Item * item );
      virtual void      RemovedItem( Item * item );
      virtual void      AmmoAmountChanged( Ammo * ammo, int inclip = 0 );
      qboolean          WeaponsOut( void );
      void              Holster( qboolean putaway );
      void              SafeHolster( qboolean putaway );

		void              StartCoolItem( Event *ev );
		void              StartCoolItemAnim( void );
		void              ShowCoolItem( Event *ev );
		void              HideCoolItem( Event *ev );
		void              StopCoolItem( Event *ev );
		void              WaitForState( Event *ev );
      void              SkipCinematic( Event *ev );
		void              SetDamageMultiplier( Event *ev );
      void              LogStats( Event *ev );
      void              WeaponsHolstered( void );
      void              WeaponsNotHolstered( void );
		void              Loaded( void );
		void					PlayerShowModel( Event *ev );
		virtual void		showModel( void );
		void					ResetHaveItem( Event *ev );
   };

inline bool Player::IsNewActiveWeapon
   (
   void 
   ) 
   
   { 
   return ( newActiveWeapon.weapon != NULL ); 
   }

inline weaponhand_t Player::GetNewActiveWeaponHand
   (
   void
   )
   
   {
   return newActiveWeapon.hand; 
   }

inline Weapon *Player::GetNewActiveWeapon
   (
   void
   )

   {
   return newActiveWeapon.weapon;
   }

inline void Player::ClearNewActiveWeapon
   (
   void 
   )

   {
   newActiveWeapon.weapon = NULL;
   newActiveWeapon.hand   = WEAPON_ERROR;
   }

inline void Player::Archive
	(
	Archiver &arc
	)

   {
   str tempStr;
   int i;
   int num;
   DualWieldWeapon *tempDualWeapon;

   Sentient::Archive( arc );

   // make sure we have the state machine loaded up
   if ( arc.Loading() )
      {
      LoadStateTable();
      }

   if ( arc.Saving() )
      {
      if ( currentState_Legs )
         {
         tempStr = currentState_Legs->getName();
         }
      else
         {
         tempStr = "NULL";
         }
      arc.ArchiveString( &tempStr );

      if ( currentState_Torso )
         {
         tempStr = currentState_Torso->getName();
         }
      else
         {
         tempStr = "NULL";
         }
      arc.ArchiveString( &tempStr );
      }
   else
      {
      arc.ArchiveString( &tempStr );
      if ( tempStr != "NULL" )
         {
         currentState_Legs = statemap_Legs->FindState( tempStr );
         }
      else
         {
         currentState_Legs = NULL;
         }
      arc.ArchiveString( &tempStr );
      if ( tempStr != "NULL" )
         {
         currentState_Torso = statemap_Torso->FindState( tempStr );
         }
      else
         {
         currentState_Torso = NULL;
         }
      }
   arc.ArchiveString( &last_torso_anim_name );
   arc.ArchiveString( &last_leg_anim_name );

   ArchiveEnum( movecontrol, movecontrol_t );

   arc.ArchiveInteger( &last_camera_type );
   if ( arc.Loading() )
      {
      // make sure the camera gets reset
      last_camera_type = -1;
      }

   arc.ArchiveSafePointer( &crosshair );

   newActiveWeapon.Archive( arc );

   arc.ArchiveSafePointer( &head_target );
	arc.ArchiveFloat( &look_at_time );

   arc.ArchiveSafePointer( &right_arm_target );
   arc.ArchiveSafePointer( &left_arm_target );
   arc.ArchiveBoolean( &shield_active );
   arc.ArchiveBoolean( &crouch_flag );

   arc.ArchiveBoolean( &dual_wield_active );

   if ( arc.Saving() )
      {
      num = dual_wield_weaponlist.NumObjects();
      }
   else
      {
      dual_wield_weaponlist.ClearObjectList();
      }
   arc.ArchiveInteger( &num );
   for( i = 1; i <= num; i++ )
      {
      if ( arc.Saving() )
         {
         tempDualWeapon = dual_wield_weaponlist.ObjectAt( i );
         }
      else
         {
         tempDualWeapon = new DualWieldWeapon;
         dual_wield_weaponlist.AddObject( tempDualWeapon );
         }
      tempDualWeapon->Archive( arc );
      }
   for( i = 0; i < MAX_ACTIVE_WEAPONS; i++ )
      {
      arc.ArchiveSafePointer( &holsteredWeapons[ i ] );
      }
   arc.ArchiveString( &partAnim[ 0 ] );
   arc.ArchiveString( &partAnim[ 1 ] );
   arc.ArchiveString( &partAnim[ 2 ] );

   arc.ArchiveBool( &animdone_Legs );
   arc.ArchiveBool( &animdone_Torso );

   arc.ArchiveVector( &oldvelocity );
   arc.ArchiveVector( &old_v_angle );
   arc.ArchiveVector( &oldorigin );
   arc.ArchiveFloat( &animspeed );
   arc.ArchiveFloat( &airspeed );

   arc.ArchiveRaw( blend, sizeof( blend ) );
   arc.ArchiveFloat( &fov );

   arc.ArchiveSafePointer( &vehicle );
   arc.ArchiveVector( &v_angle );

   arc.ArchiveInteger( &buttons );
   arc.ArchiveInteger( &new_buttons );
   arc.ArchiveFloat( &respawn_time );
      
   arc.ArchiveFloat( &water_power );
   arc.ArchiveFloat( &max_water_power );

   arc.ArchiveInteger( &last_attack_button );

   arc.ArchiveObjectPointer( ( Class ** )&rope_grabbed );
   arc.ArchiveObjectPointer( ( Class ** )&rope_touch );

   arc.ArchiveFloat( &damage_blood );
   arc.ArchiveFloat( &damage_alpha );
   arc.ArchiveVector( &damage_blend );
   arc.ArchiveVector( &damage_from );
   arc.ArchiveVector( &damage_angles );
   arc.ArchiveFloat( &damage_count );

   arc.ArchiveFloat( &bonus_alpha );

   arc.ArchiveFloat( &next_drown_time );
   arc.ArchiveFloat( &next_painsound_time );
   arc.ArchiveFloat( &air_finished );

   arc.ArchiveInteger( &old_waterlevel );
   arc.ArchiveInteger( &drown_damage );

   arc.ArchiveSafePointer( &camera );
   arc.ArchiveSafePointer( &actor_camera );
   arc.ArchiveSafePointer( &cool_camera );
   arc.ArchiveSafePointer( &actor_to_watch );
   arc.ArchiveBoolean( &actor_camera_right );
   arc.ArchiveBoolean( &starting_actor_camera_right );

   arc.ArchiveFloat( &action_level );
   arc.ArchiveInteger( &music_current_mood );
   arc.ArchiveInteger( &music_fallback_mood );

   arc.ArchiveFloat( &music_current_volume );
   arc.ArchiveFloat( &music_saved_volume );
   arc.ArchiveFloat( &music_volume_fade_time );

   arc.ArchiveInteger( &reverb_type );
   arc.ArchiveFloat( &reverb_level );

   arc.ArchiveBoolean( &gibbed );
   arc.ArchiveFloat( &pain );
   
   ArchiveEnum( pain_dir, painDirection_t );
   ArchiveEnum( pain_type, meansOfDeath_t );
   arc.ArchiveBool( &take_pain );

   arc.ArchiveFloat( &accumulated_pain );
   arc.ArchiveInteger( &nextpaintime );

   arc.ArchiveBool( &knockdown );
   arc.ArchiveBool( &canfall );
   arc.ArchiveBool( &falling );
   arc.ArchiveInteger( &feetfalling );
   arc.ArchiveVector( &falldir );

   arc.ArchiveBool( &hardimpact );

   arc.ArchiveBoolean( &music_forced );

   arc.ArchiveRaw( &last_ucmd, sizeof( last_ucmd ) );

   arc.ArchiveVector( &base_righthand_pos );
   arc.ArchiveVector( &base_lefthand_pos );
   arc.ArchiveVector( &righthand_pos );
   arc.ArchiveVector( &lefthand_pos );

   arc.ArchiveVector( &base_rightfoot_pos );
   arc.ArchiveVector( &base_leftfoot_pos );
   arc.ArchiveVector( &rightfoot_pos );
   arc.ArchiveVector( &leftfoot_pos );

   arc.ArchiveInteger( &pm_lastruntime );
   arc.ArchiveFloat( &animheight );

   arc.ArchiveVector( &yaw_forward );
   arc.ArchiveVector( &yaw_left );

   arc.ArchiveSafePointer( &atobject );
   arc.ArchiveFloat( &atobject_dist );
   arc.ArchiveVector( &atobject_dir );

   arc.ArchiveBool( &pickup_enemy );
   arc.ArchiveBool( &have_shgliek );

   arc.ArchiveSafePointer( &toucheduseanim );
   arc.ArchiveInteger( &useanim_numloops );
   arc.ArchiveSafePointer( &useitem_in_use );
   arc.ArchiveSafePointer( &cool_item );
   arc.ArchiveString( &cool_anim );
   arc.ArchiveString( &cool_dialog );

   arc.ArchiveFloat( &ledgeheight_left );
   arc.ArchiveFloat( &ledgeheight_right );
   arc.ArchiveFloat( &monkeybar_left );
   arc.ArchiveFloat( &monkeybar_right );
   arc.ArchiveFloat( &monkeybar_dir );

   arc.ArchiveSafePointer( &horizontalpipe );
   arc.ArchiveFloat( &move_left_dist );
   arc.ArchiveFloat( &move_right_dist );
   arc.ArchiveFloat( &move_backward_dist );
   arc.ArchiveFloat( &move_forward_dist );
   arc.ArchiveInteger( &moveresult );

   arc.ArchiveBoolean( &do_rise );
   arc.ArchiveBoolean( &weapons_holstered_by_code );
   arc.ArchiveBoolean( &yawing );
   arc.ArchiveBoolean( &yawing_left );
   arc.ArchiveBoolean( &yawing_right );
   arc.ArchiveBoolean( &adjust_torso );

   arc.ArchiveVector( &torsoAngles );
   arc.ArchiveVector( &headAngles );
   arc.ArchiveVector( &headAimAngles );
   arc.ArchiveVector( &torsoAimAngles );
   arc.ArchiveVector( &rightArmAimAngles );
   arc.ArchiveVector( &leftArmAimAngles );

	arc.ArchiveFloat( &damage_multiplier );

	arc.ArchiveInteger( &outfit_level );

   arc.ArchiveBoolean( &fakePlayer_active );

   arc.ArchiveSafePointer( &fakePlayer );

   if ( arc.Loading() )
      {
      UpdateWeapons();
      }
   }

inline Camera *Player::CurrentCamera
   (
   void
   )

   {
   return camera;
   }

inline void Player::CameraCut
	(
   void
	)

	{
   //
   // toggle the camera cut bit
   //
   client->ps.camera_flags = 
      ( ( client->ps.camera_flags & CF_CAMERA_CUT_BIT ) ^ CF_CAMERA_CUT_BIT ) | 
      ( client->ps.camera_flags & ~CF_CAMERA_CUT_BIT );
	}

inline void Player::CameraCut
	(
   Camera * ent
	)

	{
   if ( ent == camera )
      {
      // if the camera we are currently looking through cut, than toggle the cut bits
      CameraCut();
      }
	}

inline void Player::SetCamera
	(
	Camera *ent,
   float switchTime
	)

	{
   camera = ent;
	client->ps.camera_time = switchTime;
   if ( switchTime <= 0.0f )
      {
      CameraCut();
      }
	}

#endif /* player.h */

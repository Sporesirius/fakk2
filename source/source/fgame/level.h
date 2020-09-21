//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/level.h                            $
// $Revision:: 15                                                             $
//     $Date:: 7/28/00 6:59p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/level.h                                 $
// 
// 15    7/28/00 6:59p Steven
// Added some player died stuff.
// 
// 14    7/27/00 3:52p Aldie
// Changed over letterboxing and fades to the game code.  They are sent over in
// player stats and fields now.
// 
// 13    7/10/00 11:54p Markd
// added exit level code
// 
// 12    7/07/00 6:35p Steven
// Added mission failed stuff.
// 
// 11    6/28/00 3:27p Steven
// Added level wide ai_on.
// 
// 10    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 9     4/11/00 2:46p Markd
// Implemented Automatic camera support
// 
// 8     3/21/00 5:05p Markd
// improved earthquakes a lot with a visual effect
// 
// 7     2/29/00 5:51p Jimdose
// added alternate spawnpoint support
// 
// 6     2/26/00 12:58p Jimdose
// added PlayerRestart
// 
// 5     1/28/00 5:43p Markd
// Added script command to the game
// 
// 4     1/13/00 5:19p Jimdose
// removed clearsavegames
// 
// 3     1/12/00 6:14p Jimdose
// added spawnflags to Level
// 
// 2     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 1     12/17/99 6:33p Jimdose
//
// DESCRIPTION:
// 

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "g_local.h"
#include "container.h"

class ScriptThread;
class Camera;
//
// this structure is cleared as each map is entered
// it is read/written to the level.sav file for savegames
//
enum fadetype_t      { fadein, fadeout };
enum fadestyle_t     { alphablend, additive };
enum letterboxdir_t  { letterbox_in, letterbox_out };

class Level : public Class
	{
	public:
      const char     *current_map;
      const char     *current_entities;

      int			   spawn_entnum;
      int            spawnflags;

      int			   framenum;
      int            inttime;                // level time in millisecond integer form
	   float			   time;
      float          frametime;
      float          fixedframetime;         // preset frame time based on sv_fps
   	int			   startTime;				   // level.time the map was started
                     
	   str            level_name;	            // the descriptive name (Outer Base, etc)
	   str            mapname;		            // the server name (base1, etc)
      str            spawnpoint;             // targetname of spawnpoint
	   str            nextmap;		            // go here when fraglimit is hit

      qboolean       restart;                // set true when game loop should restart

      // used for cinematics
      qboolean       playerfrozen;

	   // intermission state
	   float			   intermissiontime;			// time the intermission was started
	   int			   exitintermission;

	   gentity_s	   *next_edict;				// Used to keep track of the next edict to process in G_RunFrame

	   int			   total_secrets;
	   int			   found_secrets;

	   // FIXME - remove this later when it is passed in the event.
      trace_t        impact_trace;
                     
      float          earthquake;
      float          earthquake_magnitude;
                     
      qboolean       cinematic;

		qboolean       ai_on;

		qboolean       mission_failed;
		qboolean       died_already;

      qboolean       near_exit;
                     
      // Blending color for water, light volumes,lava
      Vector         water_color;
      Vector         lava_color;
      float          water_alpha;
      float          lava_alpha;

      str            current_soundtrack;
      str            saved_soundtrack;

      ScriptThread   *consoleThread;

      Vector         m_fade_color;
      float          m_fade_alpha;
      float          m_fade_time;
      float          m_fade_time_start;
      fadetype_t     m_fade_type;
      fadestyle_t    m_fade_style;
      
      float          m_letterbox_fraction;
      float          m_letterbox_time;
      float          m_letterbox_time_start;
      letterboxdir_t m_letterbox_dir;

      //
      // list of automatic_cameras on the level
      //
      Container<Camera *>	automatic_cameras;



		CLASS_PROTOTYPE( Level );

                     Level();

      void           Init( void );
      void           CleanUp( void );

      void           ResetEdicts( void );
      gentity_t      *AllocEdict( Entity *ent );
      void           FreeEdict( gentity_t *ed );
      void           InitEdict( gentity_t *e );
      
      void           Start( void );
      void           Restart( void );
      void           PlayerRestart( void );
      void           Precache( void );
      void			   FindTeams( void );

      void           SpawnEntities( const char *mapname, const char *entities, int levelTime );
      void           NewMap( const char *mapname, const char *entities, int levelTime );

      qboolean       inhibitEntity( int spawnflags );
      void           setSkill( int value );
      void           setTime( int levelTime, int frameTime );
      void           AddAutomaticCamera( Camera * cam );

	   virtual void   Archive( Archiver &arc );
	};

extern Level level;

#endif /* !__LEVEL_H__ */

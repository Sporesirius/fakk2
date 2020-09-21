//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/g_public.h                         $
// $Revision:: 42                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/16/00 2:09p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/g_public.h                              $
// 
// 42    7/16/00 2:09p Aldie
// Changed some of the player logging
// 
// 41    7/14/00 8:21p Aldie
// Added logstats
// 
// 40    7/10/00 6:33p Aldie
// Added SVF_SENDONCE flag and water power for swiping determination
// 
// 39    7/06/00 7:48p Markd
// Added LevelArchiveValid function
// 
// 38    6/16/00 5:14p Aldie
// Added locational printing (print anywhere on the screen)
// 
// 37    6/15/00 8:04p Markd
// Added CleanupGame
// 
// 36    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 35    6/13/00 3:46p Steven
// Added saving alias stuff.
// 
// 34    6/10/00 4:23p Markd
// rewrote map restarting and loading out of date save games
// 
// 33    6/05/00 3:11p Markd
// fixed HasCommands calls in server
// 
// 32    6/02/00 4:26p Markd
// renamed ReadGame functions to ReadPersistant
// 
// 31    5/27/00 8:07p Markd
// Saved games 3rd pass
// 
// 30    5/11/00 11:13a Steven
// Added pointbrushnum.
// 
// 29    3/31/00 11:51a Markd
// Added SetSkyPortal method
// 
// 28    3/04/00 11:48a Markd
// Added light style support
// 
// 27    2/14/00 5:38p Jimdose
// added uselegs to Tag_OrientationEx
// 
// 26    2/01/00 4:11p Markd
// Added Frame bounding box support
// 
// 25    1/27/00 11:35a Markd
// Fixed solid/notsolid client side entities
// 
// 24    1/22/00 5:08p Steven
// Added ClipToEntity to exported interface.
// 
// 23    1/20/00 6:57p Markd
// removed get_lip functions and merged them with SoundLength and
// SoundAmplitudes
// 
// 22    1/20/00 5:20p Markd
// Added skin support into the game
// 
// 21    1/19/00 8:50p Jimdose
// added Anim_AbsolueDelta
// 
// 20    1/11/00 7:29p Jimdose
// added Tag_OrientationEx
// 
// 19    1/10/00 5:33p Markd
// Cleaned up memory allocation routines
// 
// 18    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 17    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 16    12/06/99 6:41p Jimdose
// removed fulltrace, cvar_forceset, and Surface_DamageMultiplier
// 
// 15    11/01/99 4:01p Jimdose
// made tags work with bone controllers
// 
// 14    10/25/99 6:39p Markd
// removed size and other unused variables, added radius and centroid to both
// server and game code
// 
// 13    10/19/99 7:52p Markd
// Removed three part model system
// 
// 12    10/05/99 5:03p Markd
// Removed un-used game function ClientPredict
// 
// 11    10/05/99 2:05p Markd
// Added SVF_SENDPVS which forces an entity to be checked by the PVS for
// sending and not trivially rejected because of lack of modelindex or sound
// 
// 10    10/01/99 6:31p Markd
// added commands hidden inside fgame so that they would show up for command
// completion
// 
// 9     9/28/99 4:26p Markd
// merged listener, class and vector between 3 projects
// 
// 8     9/20/99 4:50p Markd
// fixed memory allocation for snapshot entities, put in farplane culling on
// entities being sent over the net
// 
// 7     9/16/99 4:51p Jimdose
// changed ClientConnect
// added setUserInfo and getUserInfo
// 
// 6     9/15/99 6:57p Aldie
// Update to get game working
// 
// 5     9/14/99 2:38p Aldie
// code merge
// 
// 4     9/13/99 6:18p Aldie
// code merge
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
// 27    8/19/99 6:59p Markd
// removed the old tiki_cmd structure, now tiki_cmd_t is passed into the tiki
// functions
// 
// 26    8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// 25    8/17/99 5:08p Markd
// Changed all FS_ReadFile's to FS_ReadFileEx's in game code
// 
// 24    7/30/99 7:53p Markd
// Added jumping ability to the player
// 
// 23    7/29/99 11:41a Markd
// Added precache and global support
// 
// 22    7/07/99 11:26a Steven
// Added some stuff on the sector pathfinding approach.
//
// DESCRIPTION:
// Game module information visible to server 


#ifndef __G_PUBLIC_H__
#define __G_PUBLIC_H__

#define	GAME_API_VERSION	4

#define	FRAMETIME   		( level.fixedframetime )

// entity->svFlags
// the server does not know how to interpret most of the values
// in entityStates (level eType), so the game must explicitly flag
// special server behaviors
#define	SVF_NOCLIENT			      (1<<0)	// don't send entity to clients, even if it has effects
#define  SVF_BOT					      (1<<1)
#define	SVF_BROADCAST			      (1<<2)	// send to all connected clients
#define	SVF_PORTAL				      (1<<3)	// merge a second pvs at origin2 into snapshots
#define	SVF_SENDPVS				      (1<<4)	// even though it doesn't have a sound or modelindex, still run it through the pvs
#define	SVF_USE_CURRENT_ORIGIN	   (1<<5)	// entity->currentOrigin instead of entity->s.origin
  									                  // for link position (missiles and movers)
#define	SVF_DEADMONSTER			   (1<<6)	// treat as CONTENTS_DEADMONSTER for collision
#define	SVF_MONSTER					   (1<<7)	// treat as CONTENTS_MONSTER for collision
#define	SVF_USEBBOX 				   (1<<9)	// do not perform perfect collision use the bbox instead
#define	SVF_ONLYPARENT				   (1<<10)	// only send this entity to its parent
#define	SVF_HIDEOWNER				   (1<<11)	// hide the owner of the client
#define	SVF_MONSTERCLIP            (1<<12)	// treat as CONTENTS_MONSTERCLIP for collision
#define	SVF_PLAYERCLIP             (1<<13)	// treat as CONTENTS_PLAYERCLIP for collision
#define  SVF_SENDONCE               (1<<14)  // Send this entity over the network at least one time
#define  SVF_SENT                   (1<<15)  // This flag is set when the entity has been sent over at least one time

typedef enum
	{
	SOLID_NOT,			// no interaction with other objects
	SOLID_TRIGGER,		// only touch when inside, after moving
	SOLID_BBOX,			// touch on edge
	SOLID_BSP			// bsp clip, touch on edge
	} solid_t;

//===============================================================

typedef struct gentity_s gentity_t;
typedef struct gclient_s gclient_t;

#ifndef GAME_INCLUDE

// the server needs to know enough information to handle collision and snapshot generation

struct gentity_s 
   {
	entityState_t	         s;				      // communicated by server to clients
	struct playerState_s	   *client;
	qboolean	               inuse;
	qboolean	               linked;				// qfalse if not in any good cluster
	int			            linkcount;

	int			            svFlags;			   // SVF_NOCLIENT, SVF_BROADCAST, etc

	qboolean	               bmodel;				// if false, assume an explicit mins / maxs bounding box
									                  // only set by gi.SetBrushModel
	vec3_t		            mins, maxs;
	int			            contents;			// CONTENTS_TRIGGER, CONTENTS_SOLID, CONTENTS_BODY, etc
									                  // a non-solid entity should set to 0

	vec3_t		            absmin, absmax;	// derived from mins/maxs and origin + rotation

   float                   radius;           // radius of object
   vec3_t                  centroid;         // centroid, to be used with radius
   int                     areanum;          // areanum needs to be seen inside the game as well

	// currentOrigin will be used for all collision detection and world linking.
	// it will not necessarily be the same as the trajectory evaluation for the current
	// time, because each entity must be moved one at a time after time is advanced
	// to avoid simultanious collision issues
	vec3_t		            currentOrigin;
	vec3_t		            currentAngles;

	// when a trace call is made and passEntityNum != ENTITYNUM_NONE,
	// an ent will be excluded from testing if:
	// ent->s.number == passEntityNum	(don't interact with self)
	// ent->s.ownerNum = passEntityNum	(don't interact with your own missiles)
	// entity[ent->s.ownerNum].ownerNum = passEntityNum	(don't interact with other missiles from owner)
	int			            ownerNum;
	//gentity_t               *owner;		// objects never interact with their owners, to
									            // prevent player missiles from immediately
									            // colliding with their owner

   solid_t                 solid;
	// the game dll can add anything it wants after
	// this point in the structure
   };

#endif		// GAME_INCLUDE

//===============================================================

//
// functions provided by the main engine
//
typedef struct 
   {
	//============== general Quake services ==================

	// print message on the local console
	void	         (*Printf)( const char *fmt, ... );
   void           (*DPrintf)( const char *fmt, ... );
   void           (*DebugPrintf)( const char *fmt, ... );

	// abort the game
	void	         (*Error)( int errorLevel, const char *fmt, ... );
	
	// get current time for profiling reasons this should NOT be used for any game related tasks,
	// because it is not journaled
	int	         (*Milliseconds)( void );

	// managed memory allocation
	void	         *(*Malloc)( int size );
	void	         (*Free)( void *block );

	// console variable interaction
	cvar_t	      *(*cvar)( const char *var_name, const char *value, int flags );
	void           (*cvar_set)( const char *var_name, const char *value );

	// ClientCommand and ServerCommand parameter access
	int	         (*argc)( void );
	char	         *(*argv)( int n );
	const char	   *(*args)(void);
   void           (*AddCommand)( const char *cmd );

	// the returned buffer may be part of a larger pak file, or a discrete file from anywhere in the quake search path
	// a -1 return means the file does not exist NULL can be passed for buf to just determine existance
	int	         (*FS_ReadFile)( const char *name, void **buf, qboolean quiet );
	void	         (*FS_FreeFile)( void *buf );
	void	         (*FS_WriteFile)( const char *qpath, const void *buffer, int size );
   fileHandle_t   (*FS_FOpenFileWrite)( const char *qpath );
   fileHandle_t   (*FS_FOpenFileAppend)( const char *filename );

   char *         (*FS_PrepFileWrite)( const char *filename );
   int	         (*FS_Write)( const void *buffer, int len, fileHandle_t f );
   int	         (*FS_Read)( void *buffer, int len, fileHandle_t f );
   void	         (*FS_FCloseFile)( fileHandle_t f );
   int		      (*FS_FTell)( fileHandle_t f );
   int		      (*FS_FSeek)( fileHandle_t f, long offset, int origin );
   void           (*FS_Flush)( fileHandle_t f );

   const char *   (*GetArchiveFileName)( const char *filename, const char *extension );
	// add commands to the console as if they were typed in for map changing, etc
	void	         (*SendConsoleCommand)( const char *text );
	void	         (*DebugGraph)( float value, int color );

	//=========== server specific functionality =============

	// SendServerCommand reliably sends a command string to be interpreted by the given
	// client.  If ent is NULL, it will be sent to all clients
	void	         (*SendServerCommand)( int clientnum, const char *fmt, ... );

	// config strings hold all the index strings, the lightstyles, and misc data like the cdtrack.
	// All of the current configstrings are sent to clients when they connect, and 
   // changes are sent to all connected clients.
   void           (*setConfigstring)( int index, const char *val );
   char *         (*getConfigstring)( int index );

   void           (*setUserinfo)( int index, const char *val );
   void           (*getUserinfo)( int index, char *buffer, int bufferSize );

	// sets mins and maxs based on the brushmodel name
	void	         (*SetBrushModel)( gentity_t *ent, const char *name );

	// collision detection
	void           (*trace)( trace_t *result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask, qboolean cylinder  );
	int		      (*pointcontents)( const vec3_t point, int passEntityNum );
	int		      (*pointbrushnum)( const vec3_t point, int passEntityNum );
	qboolean	      (*inPVS)( vec3_t p1, vec3_t p2 );
	qboolean	      (*inPVSIgnorePortals)( vec3_t p1, vec3_t p2 );
	void		      (*AdjustAreaPortalState)( gentity_t *ent, qboolean open );
	qboolean	      (*AreasConnected)( int area1, int area2 );

	// an entity will never be sent to a client or used for collision
	// if it is not passed to linkentity.  If the size, position, or
	// solidity changes, it must be relinked.
	void	         (*linkentity)( gentity_t *ent );
	void	         (*unlinkentity)( gentity_t *ent );		// call before removing an interactive entity

	// EntitiesInBox will perform exact checking to bmodels, as well as bounding box
	// intersection tests to other models
   int            (*AreaEntities)( vec3_t mins, vec3_t maxs, int *list, int maxcount );
	void				(*ClipToEntity)( trace_t *trace, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int entityNum, int contentmask );


  	int	         (*imageindex)( const char *name );
   int	         (*itemindex)( const char *name );
   int	         (*soundindex)( const char *name );
   int	         (*modelindex)( const char *name );

  	void	         (*SetLightStyle)( int i, const char *data );

   const char	   *(*GameDir)( void );

   //
   // MODEL UTILITY FUNCTIONS
   //
   qboolean       (*IsModel)( int index );
	void		      (*setmodel)( gentity_t *ent, const char *name );

   // DEF SPECIFIC STUFF
   int				(*NumAnims)( int modelindex );
   int				(*NumSkins)( int modelindex );
   int				(*NumSurfaces)( int modelindex );
   int				(*NumTags)( int modelindex );
   qboolean       (*InitCommands)( int modelindex, tiki_cmd_t * tiki_cmd );
   void				(*CalculateBounds)( int modelindex, float scale, vec3_t mins, vec3_t maxs );

   // ANIM SPECIFIC STUFF
   const char *   (*Anim_NameForNum)( int modelindex, int animnum );
   int				(*Anim_NumForName)( int modelindex, const char * name );
   int				(*Anim_Random)( int modelindex, const char * name );
   int				(*Anim_NumFrames)( int modelindex, int animnum );
   float				(*Anim_Time)( int modelindex, int animnum );
   void				(*Anim_Delta)( int modelindex, int animnum, vec3_t delta );
   void				(*Anim_AbsoluteDelta)( int modelindex, int animnum, vec3_t delta );
   int				(*Anim_Flags)( int modelindex, int animnum );
   qboolean			(*Anim_HasCommands) ( int modelindex, int animnum );

   // FRAME SPECIFIC STUFF
   qboolean       (*Frame_Commands)( int modelindex, int animnum, int framenum, tiki_cmd_t * tiki_cmd );
   void				(*Frame_Delta)( int modelindex, int animnum, int framenum, vec3_t delta );
   float				(*Frame_Time)( int modelindex, int animnum, int framenum );
   void				(*Frame_Bounds)( int modelindex, int animnum, int framenum, float scale, vec3_t mins, vec3_t maxs );

   // SURFACE SPECIFIC STUFF
   int				(*Surface_NameToNum)( int modelindex, const char * name );
   const char *   (*Surface_NumToName)( int modelindex, int num );
   int				(*Surface_Flags)( int modelindex, int num );
   int				(*Surface_NumSkins)( int modelindex, int num );

   // TAG SPECIFIC STUFF
   int				(*Tag_NumForName)( int modelindex, const char * name );
   const char *   (*Tag_NameForNum)( int modelindex, int num );
   orientation_t  (*Tag_Orientation)( int modelindex, int anim, int frame, int num, float scale, int *bone_tag, vec4_t *bone_quat );
   orientation_t  (*Tag_OrientationEx)( int modelindex, int anim, int frame, int num, float scale, int *bone_tag, vec4_t *bone_quat,
      int crossblend_anim, int crossblend_frame, float crossblend_lerp, qboolean uselegs, qboolean usetorso, int torso_anim, int torso_frame,
      int torso_crossblend_anim, int torso_crossblend_frame, float torso_crossblend_lerp );

   qboolean			(*Alias_Add)( int modelindex, const char * alias, const char * name, const char *parameters );
   const char *   (*Alias_FindRandom)( int modelindex, const char * alias );
   void				(*Alias_Dump)( int modelindex );
   void				(*Alias_Clear)( int modelindex );
	const char *   (*Alias_FindDialog)( int modelindex, const char * alias, int random, int entity_number );
	void				*(*Alias_GetList)( int modelindex );
	void				(*Alias_UpdateDialog)( int model_index, const char *alias, int number_of_times_played, byte been_played_this_loop, int last_time_played );
	void				(*Alias_AddActorDialog)( int model_index, const char *alias, int actor_number, int number_of_times_played, byte been_played_this_loop, int last_time_played );


	const char *	(*NameForNum)( int modelindex );

   // GLOBAL ALIAS SYSTEM
   qboolean			(*GlobalAlias_Add)( const char * alias, const char * name, const char *parameters );
   const char *   (*GlobalAlias_FindRandom)( const char * alias );
   void				(*GlobalAlias_Dump)( void );
   void			   (*GlobalAlias_Clear)( void );

	void		      (*centerprintf)( gentity_t *ent, const char *fmt, ...);
	void		      (*locationprintf)( gentity_t *ent, int x, int y, const char *fmt, ...);

   // Sound
	void				(*Sound)( vec3_t *org, int entnum, int channel, const char *sound_name, float volume, float attenuation );
	void				(*StopSound)( int entnum, int channel );
 	float 		   (*SoundLength) ( const char *path );
	byte	         *(*SoundAmplitudes)( const char * name, int *number_of_amplitudes );


   unsigned short (*CalcCRC)(const unsigned char *start, int count);

   debugline_t		**DebugLines;
	int				*numDebugLines;

   void           (*LocateGameData)( gentity_t *gEnts, int numGEntities, int sizeofGEntity_t, 
                                     playerState_t *clients, int sizeofGameClient );

   void           (*SetFarPlane)( int farplane );
   void           (*SetSkyPortal)( qboolean skyportal );

   } game_import_t;

//
// functions exported by the game subsystem
//
typedef struct {
	int			apiversion;

	// the init function will only be called when a game starts,
	// not each time a level is loaded.  Persistant data for clients
	// and the server can be allocated in init
	void		   (*Init) ( int startTime, int randomSeed);
	void		   (*Shutdown) (void);
	void		   (*Cleanup) (void);

	// each new level entered will cause a call to SpawnEntities
	void		   (*SpawnEntities) (const char *mapname, const char *entstring, int levelTime);

	// return NULL if the client is allowed to connect, otherwise return
	// a text string with the reason for denial
	char		   *(*ClientConnect)( int clientNum, qboolean firstTime );

	void		   (*ClientBegin)( gentity_t *ent, usercmd_t *cmd );
	void		   (*ClientUserinfoChanged)( gentity_t *ent, const char *userinfo );
	void		   (*ClientDisconnect)( gentity_t *ent );
	void		   (*ClientCommand)( gentity_t *ent );
	void		   (*ClientThink)( gentity_t *ent, usercmd_t *cmd );

	void		   (*BotBegin)( gentity_t *ent );
	void		   (*BotThink)( gentity_t *ent, int msec );

   void		   (*PrepFrame)( void );
	void		   (*RunFrame)( int levelTime, int frameTime );

	// ConsoleCommand will be called when a command has been issued
	// that is not recognized as a builtin function.
	// The game can issue gi.argc() / gi.argv() commands to get the command
	// and parameters.  Return qfalse if the game doesn't recognize it as a command.
	qboolean	   (*ConsoleCommand)( void );

   // Read/Write Persistant is for storing persistant cross level information
	// about the world state and the clients.
	// WriteGame is called every time a level is exited.
	// ReadGame is called every time a level is entered.
	void		   (*WritePersistant)( const char *filename );
	qboolean    (*ReadPersistant)( const char *filename );

 	// ReadLevel is called after the default map information has been
	// loaded with SpawnEntities, so any stored client spawn spots will
	// be used when the clients reconnect.
	void		   (*WriteLevel)( const char *filename, qboolean autosave );
	qboolean	   (*ReadLevel)( const char *filename );
	qboolean	   (*LevelArchiveValid)( const char *filename );

	//
	// global variables shared between game and server
	//

	// The gentities array is allocated in the game dll so it
	// can vary in size from one game to another.
	// 
	// The size will be fixed when ge->Init() is called
	// the server can't just use pointer arithmetic on gentities, because the
	// server's sizeof(struct gentity_s) doesn't equal gentitySize
	struct gentity_s	*gentities;
	int			      gentitySize;
	int			      num_entities;		// current number, <= max_entities
	int			      max_entities;

   const char        *error_message;
} game_export_t;

game_export_t *GetGameApi (game_import_t *import);

#endif // __G_PUBLIC_H__


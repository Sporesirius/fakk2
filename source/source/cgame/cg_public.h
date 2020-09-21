//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_public.h                        $
// $Revision:: 47                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/16/00 11:01p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_public.h                             $
// 
// 47    7/16/00 11:01p Markd
// Added UpdateLoadingScreen call
// 
// 46    7/14/00 9:52p Markd
// added global volume dampener on ambient sound effects for cinematics
// 
// 45    7/10/00 11:54p Markd
// added exit level code
// 
// 44    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 43    6/09/00 10:27a Markd
// got lagometer and CG_2D operations functioning
// 
// 42    6/05/00 3:10p Markd
// Added has_commands check to client side command processing
// 
// 41    6/02/00 6:51p Markd
// added better camera look features
// 
// 40    5/18/00 12:52p Steven
// Added use_listener to S_UpdateEntity.
// 
// 39    3/31/00 11:45a Markd
// Added skyportal toggling support
// 
// 38    3/04/00 11:45a Markd
// Added light style support and malloc and free to the cgame
// 
// 37    3/02/00 10:35a Steven
// Changed reverb interface.
// 
// 36    2/21/00 4:59p Steven
// Changed S_StartLocalSound to be able to use aliases.
// 
// 35    2/21/00 2:51p Markd
// Added GlobalRadius support to tikis
// 
// 34    2/14/00 7:34p Aldie
// Fixed some beam rendering issues
// 
// 33    2/14/00 5:48p Jimdose
// legs animation now only plays when ANIM_BLEND is set on anim or if uselegs
// is set
// 
// 32    2/12/00 3:45p Markd
// Added new exports for cgame access
// 
// 31    2/07/00 7:38p Aldie
// Fixed swiping, also various weapons fixes for sword and for sling
// 
// 30    2/03/00 1:05p Markd
// added real cameralook
// 
// 29    1/29/00 6:17p Aldie
// Added TIKI_NameForNum
// 
// 28    1/28/00 6:11p Jimdose
// added CG_GetRendererConfig to clientGameExport_t
// 
// 27    1/25/00 8:07p Jimdose
// added Anim_CrossblendTime
// 
// 26    1/24/00 6:43p Steven
// Added reverb stuff.
// 
// 25    1/20/00 5:20p Markd
// Added skin support into the game
// 
// 24    1/11/00 7:30p Jimdose
// added Tag_OrientationEx
// 
// 23    12/11/99 5:51p Markd
// First wave of bug fixes after q3a gold merge
// 
// 22    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 21    12/09/99 10:52a Jimdose
// got tags working with torso and crossblended animations
// 
// 20    12/02/99 4:33p Jimdose
// exported TIKI_Tag_NamedLerpOrientation
// 
// 19    11/03/99 6:20p Steven
// Cleaned up some sound entity position stuff.
// 
// 18    11/01/99 4:11p Jimdose
// made tags work with bone controllers
// 
// 17    10/29/99 7:29p Steven
// Moved sound stuff into snapshot.
// 
// 16    10/22/99 6:29p Aldie
// Fix for beams in the sky
// 
// 15    10/22/99 4:29p Aldie
// Added debuglines
// 
// 14    10/19/99 7:52p Markd
// Removed three part model system
// 
// 13    10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// client game public interfaces

#ifndef __CG_PUBLIC_H__
#define __CG_PUBLIC_H__

#ifdef __cplusplus
extern "C"
   {
#endif

#define  MAGIC_UNUSED_NUMBER 7777
#define	CMD_BACKUP			64	
#define	CMD_MASK			(CMD_BACKUP - 1)
// allow a lot of command backups for very fast systems
// multiple commands may be combined into a single packet, so this
// needs to be larger than PACKET_BACKUP


#define	MAX_ENTITIES_IN_SNAPSHOT	256

// snapshots are a view of the server at a given time

// Snapshots are generated at regular time intervals by the server,
// but they may not be sent if a client's rate level is exceeded, or
// they may be dropped by the network.
typedef struct {
	int				snapFlags;			// SNAPFLAG_RATE_DELAYED, etc
	int				ping;

	int				serverTime;		// server time the message is valid for (in msec)

	byte				areamask[MAX_MAP_AREA_BYTES];		// portalarea visibility bits

	playerState_t	ps;						// complete information about the current player at this time

	int				numEntities;			// all of the entities that need to be presented
	entityState_t	entities[MAX_ENTITIES_IN_SNAPSHOT];	// at the time of this snapshot

	int				numServerCommands;		// text based server commands to execute when this
	int				serverCommandSequence;	// snapshot becomes current

	int				number_of_sounds;
	server_sound_t	sounds[ MAX_SERVER_SOUNDS ];
} snapshot_t;


/*
==================================================================

functions imported from the main executable

==================================================================
*/

#define	CGAME_IMPORT_API_VERSION	3

/*
==================================================================

functions exported to the main executable

==================================================================
*/

// This was put back in for FAKK2

typedef struct 
   {
	int			apiversion;
	
	//============== general services ==================

	// print message on the local console
	void	         (*Printf)( const char *fmt, ...);
	void	         (*DPrintf)( const char *fmt, ...);
	void	         (*DebugPrintf)( const char *fmt, ...);

	// managed memory allocation
	void	         *(*Malloc)( int size );
	void	         (*Free)( void *block );

	// abort the game
	void	         (*Error)( int errorLevel, const char *fmt, ...);

	// milliseconds should only be used for profiling, never
	// for anything game related.  Get time from CG_ReadyToBuildScene.
	int		      (*Milliseconds)( void );

	// console variable interaction
	cvar_t *       (*Cvar_Get)( const char *var_name, const char *value, int flags );
	void           (*Cvar_Set)( const char *var_name, const char *value );

	// ClientCommand and ConsoleCommand parameter access
	int		      (*Argc)( void );
	char *         (*Argv)( int n );
	char *         (*Args)( void );	// concatenation of all argv >= 1
   void           (*AddCommand)( const char *cmd );

	// a -1 return means the file does not exist
	// NULL can be passed for buf to just determine existance
	int		      (*FS_ReadFile)( const char *name, void **buf, qboolean quiet );
	void	         (*FS_FreeFile)( void *buf );
	void	         (*FS_WriteFile)( const char *qpath, const void *buffer, int size );
   void           (*FS_WriteTextFile)( const char *qpath, const void *buffer, int size );
	// add commands to the local console as if they were typed in
	// for map changing, etc.  The command is not executed immediately,
	// but will be executed in order the next time console commands
	// are processed
	void	         (*SendConsoleCommand)( const char *text );

   void           (*UpdateLoadingScreen)( void );
	// =========== client specific functions ===============

	// send a string to the server over the network
	void	         (*SendClientCommand)( const char *s );

   // CM functions
	void           (*CM_LoadMap)( const char *name );
	clipHandle_t   (*CM_InlineModel)( int index );		// 0 = world, 1+ = bmodels
	int			   (*CM_NumInlineModels)( void );
	int			   (*CM_PointContents)( const vec3_t p, int headnode );
	int			   (*CM_TransformedPointContents)( const vec3_t p, int headnode, vec3_t origin, vec3_t angles );
	void  	      (*CM_BoxTrace)( trace_t *results, const vec3_t start, const vec3_t end,
     						             const vec3_t mins, const vec3_t maxs,
	 						             int headnode, int brushmask, qboolean cylinder );
   void  		   (*CM_TransformedBoxTrace)( trace_t *results, const vec3_t start, const vec3_t end,
							                        const vec3_t mins, const vec3_t maxs,
							                        int headnode, int brushmask,
   						                        const vec3_t origin, const vec3_t angles, 
                                             qboolean cylinder
                                           );
   clipHandle_t   (*CM_TempBoxModel)( const vec3_t mins, const vec3_t maxs, int contents );
   int		      (*CM_MarkFragments)( int numPoints, const vec3_t *points, const vec3_t projection, 
                                       int maxPoints, vec3_t pointBuffer,
                                       int maxFragments, markFragment_t *fragmentBuffer );

	// =========== sound function calls ===============

   void	         (*S_StartSound)( vec3_t origin, int entnum, int entchannel, sfxHandle_t sfx, float volume, float min_dist );
	void	         (*S_StartLocalSound)( const char *sound_name );
	void				(*S_StopSound)( int entnum, int channel );
	void	         (*S_ClearLoopingSounds)( void );
	void	         (*S_AddLoopingSound)( const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx, float volume, float min_dist );
	void	         (*S_Respatialize)( int entityNum, vec3_t origin, vec3_t axis[3] );
	void	         (*S_BeginRegistration)( void );
	sfxHandle_t		(*S_RegisterSound)( const char *sample );
	void	         (*S_EndRegistration)( void );
	void				(*S_UpdateEntity)( int entityNum, const vec3_t origin, const vec3_t velocity, qboolean use_listener );
	void				(*S_SetReverb)( int reverb_type, float reverb_level );
   void           (*S_SetGlobalAmbientVolumeLevel)( float volume );

	// =========== music function calls ===============

	void           (*MUSIC_NewSoundtrack)( const char *name );
	void				(*MUSIC_UpdateMood)( int current_mood, int fallback_mood );
	void				(*MUSIC_UpdateVolume)( float volume, float fade_time );


	// =========== lip function calls ===============

	float          (*get_lip_length)(const char * name);
	byte *         (*get_lip_amplitudes)(const char * name, int *number_of_amplitudes);

	// =========== camera function calls ===============

	float *  		(*get_camera_offset)( qboolean *lookactive, qboolean *resetview );

	// =========== renderer function calls ================
	void	         (*BeginRegistration)( void );
	void	         (*EndRegistration)( void );

   void           (*R_ClearScene)( void );
   void           (*R_RenderScene)( const refdef_t *fd );
   void	         (*R_LoadWorldMap)( const char *mapname );
   qhandle_t      (*R_RegisterModel)( const char *name );
	qhandle_t      (*R_RegisterSkin)( const char *name );
	qhandle_t      (*R_RegisterShader)( const char *name );
	qhandle_t      (*R_RegisterShaderNoMip)( const char *name );
   void           (*R_AddRefEntityToScene)( refEntity_t *ent );
   void           (*R_AddRefSpriteToScene)( refEntity_t *ent );
   void           (*R_AddLightToScene)( vec3_t origin, float intensity, float r, float g, float b, int type );
	void	         (*R_AddPolyToScene)( qhandle_t hShader, int numVerts, const polyVert_t *verts, int renderfx );
	void	         (*R_SetColor)( const vec4_t rgba );	// NULL = 1,1,1,1
	void	         (*R_DrawStretchPic) ( float x, float y, float w, float h, 
		                                  float s1, float t1, float s2, float t2, 
                                        qhandle_t hShader );	// 0 = white
   refEntity_t *  (*R_GetRenderEntity)( int entityNumber );
   void		      (*R_ModelBounds)( clipHandle_t model, vec3_t mins, vec3_t maxs );
   float 	      (*R_ModelRadius)( clipHandle_t model );
   float          (*R_Noise)( float x, float y, float z, float t );
   void           (*R_DebugLine)( vec3_t start, vec3_t end, float r, float g, float b, float alpha );
   // =========== Swipes =============
   void           (*R_SwipeBegin) ( float thistime, float life, qhandle_t shader );
   void           (*R_SwipePoint) ( vec3_t p1, vec3_t p2, float time );
   void           (*R_SwipeEnd) ( void );
   int            (*R_GetShaderWidth)( qhandle_t shader );
   int            (*R_GetShaderHeight)( qhandle_t shader );
   void           (*R_DrawBox)( float x, float y, float w, float h );

	// =========== data shared with the client =============
	void	         (*GetGameState)( gameState_t *gamestate );
	int	         (*GetSnapshot)( int snapshotNumber, snapshot_t *snapshot );
   void		      (*GetCurrentSnapshotNumber)( int *snapshotNumber, int *serverTime );
   void		      (*GetGlconfig)( glconfig_t *glconfig );

	// will return false if the number is so old that it doesn't exist in the buffer anymore
	qboolean	      (*GetParseEntityState)( int parseEntityNumber, entityState_t *state );
	int		      (*GetCurrentCmdNumber)( void );		// returns the most recent command number
												                  // which is the local predicted command for
												                  // the following frame
	qboolean	      (*GetUserCmd)( int cmdNumber, usercmd_t *ucmd );
   qboolean	      (*GetServerCommand)( int serverCommandNumber );

   // ALIAS STUFF
   qboolean			(*Alias_Add)( const char * alias, const char * name, const char *parameters );
   const char *   (*Alias_FindRandom)( const char * alias );
   void				(*Alias_Dump)( void );
   void				(*Alias_Clear)( void );

   // ==================== TIKI STUFF ==========================
   // TIKI SPECIFIC STUFF
   int            (*TIKI_GetHandle)( qhandle_t handle );
   int				(*NumAnims) ( int tikihandle );
   int				(*NumSkins) ( int tikihandle );
   int				(*NumSurfaces) ( int tikihandle );
   int            (*NumTags)  ( int tikihandle );
   qboolean       (*InitCommands) ( int tikihandle, tiki_cmd_t * tiki_cmd );
   void				(*CalculateBounds) ( int tikihandle, float scale, vec3_t mins, vec3_t maxs );
   void				(*FlushAll) ( void );
	const char *   (*TIKI_NameForNum)( int tikihandle );

   // ANIM SPECIFIC STUFF
   const char *   (*Anim_NameForNum) ( int tikihandle, int animnum );
   int				(*Anim_NumForName) ( int tikihandle, const char * name );
   int				(*Anim_Random) ( int tikihandle, const char * name );
   int				(*Anim_NumFrames) ( int tikihandle, int animnum );
   float				(*Anim_Time) ( int tikihandle, int animnum );
   void				(*Anim_Delta) ( int tikihandle, int animnum, vec3_t delta );
   int				(*Anim_Flags) ( int tikihandle, int animnum );
   int				(*Anim_CrossblendTime) ( int tikihandle, int animnum );
   qboolean			(*Anim_HasCommands) ( int tikihandle, int animnum );

   // FRAME SPECIFIC STUFF
   qboolean       (*Frame_Commands) ( int tikihandle, int animnum, int framenum, tiki_cmd_t * tiki_cmd );
   void				(*Frame_Delta) ( int tikihandle, int animnum, int framenum, vec3_t delta );
   float				(*Frame_Time) ( int tikihandle, int animnum, int framenum );
   void				(*Frame_Bounds)( int tikihandle, int animnum, int framenum, float scale, vec3_t mins, vec3_t maxs );
   float				(*Frame_Radius)( int tikihandle, int animnum, int framenum );

   // SURFACE SPECIFIC STUFF
   int				(*Surface_NameToNum) ( int tikihandle, const char * name );
   const char *   (*Surface_NumToName) ( int tikihandle, int num );
   int				(*Surface_Flags) ( int tikihandle, int num );
   int				(*Surface_NumSkins) ( int tikihandle, int num );

   // TAG SPECIFIC STUFF
   int				(*Tag_NumForName) ( int tikihandle, const char * name );
   const char *   (*Tag_NameForNum) ( int tikihandle, int num );
   orientation_t  (*Tag_Orientation) ( int tikihandle, int anim, int frame, int tagnum, float scale, int *bone_tag, vec4_t *bone_quat );
   orientation_t  (*Tag_OrientationEx) ( int tikihandle, int anim, int frame, int tagnum, float scale, int *bone_tag, vec4_t *bone_quat,
      int crossblend_anim, int crossblend_frame, float crossblend_lerp, qboolean uselegs, qboolean usetorso, int torso_anim, int torso_frame,
      int torso_crossblend_anim, int torso_crossblend_frame, float torso_crossblend_lerp );

   orientation_t  (*Tag_NamedOrientation) ( int tikihandle, int anim, int frame, float scale, const char *tagName, int *bone_tag, vec4_t *bone_quat );
   orientation_t  (*Tag_LerpedOrientation) ( int tikihandle, refEntity_t *model, int tagnum );
   
   // ALIAS SPECIFIC STUF
   qboolean			(*TIKI_Alias_Add)( int tikihandle, const char * alias, const char * name, const char *parameters );
   const char *   (*TIKI_Alias_FindRandom)( int tikihandle, const char * alias );
   void				(*TIKI_Alias_Dump)( int tikihandle );
   void				(*TIKI_Alias_Clear)( int tikihandle );
	const char *   (*TIKI_Alias_FindDialog)( int tikihandle, const char * alias, int random, int entity_number );

} clientGameImport_t;


/*
==================================================================

functions exported to the main executable

==================================================================
*/

typedef struct {
	void     (*CG_Init)( clientGameImport_t *imported, int serverMessageNum, int serverCommandSequence );
   void     (*CG_Shutdown)( void );
   void     (*CG_DrawActiveFrame)( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback );
   qboolean (*CG_ConsoleCommand)( void );
   void     (*CG_GetRendererConfig)( void );
   void     (*CG_Draw2D)( void );

   } clientGameExport_t;


#ifdef __cplusplus
}
#endif

#endif // __CG_PUBLIC_H__

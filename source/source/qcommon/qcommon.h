//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/qcommon/qcommon.h                        $
// $Revision:: 50                                                             $
//     $Date:: 8/10/00 6:41p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/qcommon/qcommon.h                             $
// 
// 50    8/10/00 6:41p Markd
// Added heap functions
// 
// 49    8/07/00 6:42p Markd
// Added Z_Shutdown call for freeing up memory on exit
// 
// 48    7/28/00 11:50p Markd
// Added FS_CopyGameFile
// 
// 47    7/28/00 3:11p Markd
// Added Cvar_Set2
// 
// 46    7/26/00 11:06p Markd
// increased max_msglen to 49152 from 32768
// 
// 45    7/26/00 7:03p Markd
// added prototype for Z_InitMemory
// 
// 44    7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 43    7/18/00 12:48p Markd
// added cacheable tiki system
// 
// 42    7/16/00 11:09p Markd
// Added new types of static memory, added UpdateLoadingScreen call
// 
// 41    7/15/00 12:42a Markd
// bring up main menu and/or console on disconnect
// 
// 40    7/14/00 8:30p Aldie
// Added in logstats
// 
// 39    7/13/00 6:46p Aldie
// Added ability to save weapon groupings
// 
// 38    7/13/00 3:39p Markd
// fixed fs_readfile and freefile issues with temporary allocated memory
// 
// 37    7/11/00 9:27a Steven
// Put MAX_RELIABLE_COMMANDS back where it was now that other problem is fixed.
// 
// 36    7/11/00 8:16a Steven
// Doubled MAX_RELIABLE_COMMANDS for the moment to fix restart problem.
// 
// 35    7/07/00 9:10p Markd
// fixed waiting and some crash bugs
// 
// 34    7/05/00 8:26p Aldie
// Added some restart functionality
// 
// 33    7/05/00 5:18p Aldie
// Added more inventory controls
// 
// 32    7/02/00 11:56a Aldie
// Added some functionality for resolution changing
// 
// 31    6/19/00 7:35p Markd
// added cd checking
// 
// 30    6/16/00 5:14p Aldie
// Added locational printing (print anywhere on the screen)
// 
// 29    6/15/00 8:03p Markd
// Changed CL_MapLoading
// 
// 28    6/13/00 3:44p Markd
// save/load game tweaks
// 
// 27    6/12/00 11:38a Markd
// Added loadsave menu
// 
// 26    6/10/00 4:23p Markd
// rewrote map restarting and loading out of date save games
// 
// 25    6/01/00 7:03p Markd
// Added FS_DeleteFile function
// 
// 24    5/10/00 10:26a Steven
// Moved com_blood cvar.
// 
// 23    4/30/00 1:50p Markd
// fixed message overflow on sending baselines
// 
// 22    3/28/00 6:37p Markd
// Changed FS_FileTime
// 
// 21    3/04/00 11:47a Markd
// Added TAG_CGAME and TAG_CLIENT
// 
// 20    2/26/00 4:27p Markd
// added more memory subdivision to help diagnose leaks
// 
// 19    2/22/00 6:54p Aldie
// Added mouse positioning functionality
// 
// 18    2/10/00 11:25a Markd
// Added TAG_SOUND
// 
// 17    1/18/00 7:33p Markd
// Added date to map picker
// 
// 16    1/10/00 5:25p Markd
// Added TAG_GAME and TAG_TIKI
// 
// 15    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 14    11/04/99 7:16p Morbid
// Added better clipboard getting/setting functions
// 
// 13    10/29/99 7:30p Steven
// Moved sound stuff into snapshot.
// 
// 12    10/01/99 7:14p Morbid
// Made Cvar_FindVar a non-static for the UI
// 
// 11    9/30/99 6:15p Morbid
// Made command and cvar completion return const char *'s
// 
// 10    9/28/99 5:31p Markd
// Successfully merged class.h, listener.h and vector.h into all three modules,
// cgame, fgame and client
// 
// 9     9/20/99 6:58p Steven
// Cleanup
// 
// 8     9/17/99 6:35p Steven
// Fixed some messaging/sound issues.
// 
// 7     9/15/99 6:57p Aldie
// Update to get game working
// 
// 6     9/15/99 2:03p Steven
// Merge.
// 
// 5     9/13/99 6:18p Aldie
// code merge
// 
// 4     9/13/99 3:30p Jimdose
// merge
// 
// 3     9/13/99 12:20p Aldie
// Merging code
// 
// 2     9/10/99 5:46p Jimdose
// merge
//
// DESCRIPTION:
// qcommon.h -- definitions common between client and server, but not game.or ref modules
//

#ifndef _QCOMMON_H_
#define _QCOMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../qcommon/cm_public.h"

//============================================================================

//
// msg.c
//
typedef struct {
	qboolean	allowoverflow;	// if false, do a Com_Error
	qboolean	overflowed;		// set to true if the buffer size failed (with allowoverflow set)
	byte	*data;
	int		maxsize;
	int		cursize;
	int		readcount;
	int		bit;				// for bitwise reads and writes
} msg_t;

void MSG_Init (msg_t *buf, byte *data, int length);
void MSG_Clear (msg_t *buf);
void *MSG_GetSpace (msg_t *buf, int length);
void MSG_WriteData (msg_t *buf, const void *data, int length);


struct usercmd_s;
struct entityState_s;
struct playerState_s;

void MSG_WriteBits( msg_t *msg, int value, int bits );

void MSG_WriteChar (msg_t *sb, int c);
void MSG_WriteByte (msg_t *sb, int c);
void MSG_WriteShort (msg_t *sb, int c);
void MSG_WriteLong (msg_t *sb, int c);
void MSG_WriteFloat (msg_t *sb, float f);
void MSG_WriteString (msg_t *sb, const char *s);
void MSG_WriteAngle16 (msg_t *sb, float f);

void	MSG_BeginReading (msg_t *sb);

int		MSG_ReadBits( msg_t *msg, int bits );

int		MSG_ReadChar (msg_t *sb);
int		MSG_ReadByte (msg_t *sb);
int		MSG_ReadShort (msg_t *sb);
int		MSG_ReadLong (msg_t *sb);
float	MSG_ReadFloat (msg_t *sb);
char	*MSG_ReadString (msg_t *sb);
char	*MSG_ReadStringLine (msg_t *sb);
float	MSG_ReadAngle16 (msg_t *sb);
void	MSG_ReadData (msg_t *sb, void *buffer, int size);


void MSG_WriteDeltaUsercmd( msg_t *msg, struct usercmd_s *from, struct usercmd_s *to );
void MSG_ReadDeltaUsercmd( msg_t *msg, struct usercmd_s *from, struct usercmd_s *to );

void MSG_WriteDeltaEntity( msg_t *msg, struct entityState_s *from, struct entityState_s *to
						   , qboolean force );
void MSG_ReadDeltaEntity( msg_t *msg, entityState_t *from, entityState_t *to, 
						 int number );
void MSG_GetNullEntityState( entityState_t *nullState );

void MSG_WriteDeltaPlayerstate( msg_t *msg, struct playerState_s *from, struct playerState_s *to );
void MSG_ReadDeltaPlayerstate( msg_t *msg, struct playerState_s *from, struct playerState_s *to );

void MSG_WriteSounds( msg_t *msg, server_sound_t *sounds, int number_of_sounds );
void MSG_ReadSounds( msg_t *msg, server_sound_t *sounds, int *number_of_sounds );

void MSG_ReportChangeVectors_f( void );

//============================================================================

extern	short	BigShort (short l);
extern	short	LittleShort (short l);
extern	int		BigLong (int l);
extern	int		LittleLong (int l);
extern	float	BigFloat (float l);
extern	float	LittleFloat (float l);


/*
==============================================================

NET

==============================================================
*/

#define	PACKET_BACKUP	32	// number of old messages that must be kept on client and
							// server for delta comrpession and ping estimation
#define	PACKET_MASK		(PACKET_BACKUP-1)

#define	MAX_PACKET_USERCMDS		32		// max number of usercmd_t in a packet

#define	PORT_ANY			-1

#define	MAX_RELIABLE_COMMANDS	64			// max string commands buffered for restransmit

typedef enum {
	NA_BOT,
	NA_BAD,					// an address lookup failed
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
	NA_IPX,
	NA_BROADCAST_IPX
} netadrtype_t;

typedef enum {
	NS_CLIENT,
	NS_SERVER
} netsrc_t;

typedef struct {
	netadrtype_t	type;

	byte	ip[4];
	byte	ipx[10];

	unsigned short	port;
} netadr_t;

void		NET_Init( void );
void		NET_Shutdown( void );
void		NET_Restart( void );
void		NET_Config( qboolean enableNetworking );

void		NET_SendPacket (netsrc_t sock, int length, const void *data, netadr_t to);
void		NET_OutOfBandPrint( netsrc_t net_socket, netadr_t adr, const char *format, ...);

qboolean	NET_CompareAdr (netadr_t a, netadr_t b);
qboolean	NET_CompareBaseAdr (netadr_t a, netadr_t b);
qboolean	NET_IsLocalAddress (netadr_t adr);
const char	*NET_AdrToString (netadr_t a);
qboolean	NET_StringToAdr ( const char *s, netadr_t *a);
qboolean	NET_GetLoopPacket (netsrc_t sock, netadr_t *net_from, msg_t *net_message);
void		NET_Sleep(int msec);


// If MAX_MSGLEN is changed please change MAX_LOOPBACK also
#define	MAX_MSGLEN				49152		// max length of a message, which may
													// be fragmented into multiple packets


/*
Netchan handles packet fragmentation and out of order / duplicate suppression
*/

typedef struct {
	netsrc_t	sock;

	int			dropped;			// between last packet and previous

	netadr_t	remoteAddress;
	int			qport;				// qport value to write when transmitting

	// sequencing variables
	int			incomingSequence;
	int			outgoingSequence;

	// incoming fragment assembly buffer
	int			fragmentSequence;
	int			fragmentLength;	
	byte		fragmentBuffer[MAX_MSGLEN];
} netchan_t;

void Netchan_Init( int qport );
void Netchan_Setup( netsrc_t sock, netchan_t *chan, netadr_t adr, int qport );

void Netchan_Transmit( netchan_t *chan, int length, const byte *data );
qboolean Netchan_Process( netchan_t *chan, msg_t *msg );


/*
==============================================================

PROTOCOL

==============================================================
*/

#define	PROTOCOL_VERSION	1


#define	UPDATE_SERVER_NAME	   "updatefakk2.ritual.com"
#define  MASTER_SERVER_NAME	   "masterfakk2.ritual.com"
#define	AUTHORIZE_SERVER_NAME	"authorizefakk2.ritual.com"

#define	PORT_MASTER			27950
#define	PORT_UPDATE			27951
#define	PORT_AUTHORIZE		27952
#define	PORT_SERVER			27960
#define	NUM_SERVER_PORTS	4		// broadcast scan this many ports after
									// PORT_SERVER so a single machine can
									// run multiple servers


// the svc_strings[] array in cl_parse.c should mirror this
//
// server to client
//
enum svc_ops_e {
	svc_bad,
	svc_nop,
	svc_gamestate,
	svc_configstring,			// [short] [string] only in gamestate messages
	svc_baseline,				// only in gamestate messages
	svc_serverCommand,			// [string] to be executed by client game module
	svc_download,				// [short] size [size bytes]
	svc_snapshot,
   svc_centerprint,        // Centered on the screen
   svc_locprint            // Centered in X - Y position specified
};


//
// client to server
//
enum clc_ops_e {
	clc_bad,
	clc_nop, 		
	clc_move,				// [[usercmd_t]
	clc_moveNoDelta,		// [[usercmd_t]
	clc_clientCommand		// [string] message
};

/*
==============================================================

CMD

Command text buffering and command execution

==============================================================
*/

/*

Any number of commands can be added in a frame, from several different sources.
Most commands come from either keybindings or console line input, but entire text
files can be execed.

*/

void Cbuf_Init (void);
// allocates an initial text buffer that will grow as needed

void Cbuf_AddText( const char *text );
// Adds command text at the end of the buffer, does NOT add a final \n

void Cbuf_ExecuteText( int exec_when, const char *text );
// this can be used in place of either Cbuf_AddText or Cbuf_InsertText

void Cbuf_Execute ( int msec );
// Pulls off \n terminated lines of text from the command buffer and sends
// them through Cmd_ExecuteString.  Stops when the buffer is empty.
// Normally called once per frame, but may be explicitly invoked.
// Do not call inside a command function, or current args will be destroyed.

//===========================================================================

/*

Command execution takes a null terminated string, breaks it into tokens,
then searches for a command or variable that matches the first token.

*/

typedef void (*xcommand_t) (void);

void	Cmd_Init (void);

void	Cmd_AddCommand( const char *cmd_name, xcommand_t function );
// called by the init functions of other parts of the program to
// register commands and functions to call for them.
// The cmd_name is referenced later, so it should not be in temp memory
// if function is NULL, the command will be forwarded to the server
// as a clc_clientCommand instead of executed locally

void	Cmd_RemoveCommand( const char *cmd_name );

char 	*Cmd_CompleteCommand( const char *partial );
const char  *Cmd_CompleteCommandByNumber ( const char *partial, int number );
// attempts to match a partial command for automatic command line completion
// returns NULL if nothing fits

int		Cmd_Argc (void);
char	*Cmd_Argv (int arg);
void	Cmd_ArgvBuffer( int arg, char *buffer, int bufferLength );
char	*Cmd_Args (void);
void	Cmd_ArgsBuffer( char *buffer, int bufferLength );
// The functions that execute commands get their parameters with these
// functions. Cmd_Argv () will return an empty string, not a NULL
// if arg > argc, so string operations are allways safe.

void	Cmd_TokenizeString( const char *text );
// Takes a null terminated string.  Does not need to be /n terminated.
// breaks the string up into arg tokens.

void	Cmd_ExecuteString( const char *text );
// Parses a single line of text into arguments and tries to execute it
// as if it was typed at the console

// write out the aliases
void Cmd_WriteAliases (fileHandle_t f);

void Cmd_Alias( const char *s, const char *cmd );

/*
==============================================================

CVAR

==============================================================
*/

/*

cvar_t variables are used to hold scalar or string variables that can be changed
or displayed at the console or prog code as well as accessed directly
in C code.

The user can access cvars from the console in three ways:
r_draworder			prints the current value
r_draworder 0		sets the current value to 0
set r_draworder 0	as above, but creates the cvar if not present

Cvars are restricted from having the same names as commands to keep this
interface from being ambiguous.

The are also occasionally used to communicated information between different
modules of the program.

*/
cvar_t *Cvar_FindVar ( const char *var_name );
// tries to find the variable, doesn't create it if it doesn't exist
// used for the user interface.  Returns NULL for no error

cvar_t *Cvar_Get( const char *var_name, const char *value, int flags );
// creates the variable if it doesn't exist, or returns the existing one
// if it exists, the value will not be changed, but flags will be ORed in
// that allows variables to be unarchived without needing bitflags
// if value is "", the value will not override a previously set value.

void	Cvar_Register( vmCvar_t *vmCvar, const char *varName, const char *defaultValue, int flags );
// basically a slightly modified Cvar_Get for the interpreted modules

void	Cvar_Update( vmCvar_t *vmCvar );
// updates an interpreted modules' version of a cvar

cvar_t *Cvar_Set2( const char *var_name, const char *value, qboolean force );
// will create the variable with no flags if it doesn't exist, will not force set the value if latched

void 	Cvar_Set( const char *var_name, const char *value );
// will create the variable with no flags if it doesn't exist

void	Cvar_SetValue( const char *var_name, float value );
// expands value to a string and calls Cvar_Set

float	Cvar_VariableValue( const char *var_name );
int		Cvar_VariableIntegerValue( const char *var_name );
// returns 0 if not defined or non numeric

char	*Cvar_VariableString( const char *var_name );
void	Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );
// returns an empty string if not defined

char 	*Cvar_CompleteVariable( const char *partial );
const char  *Cvar_CompleteVariableByNumber ( const char *partial, int number );
// attempts to match a partial variable name for command line completion
// returns NULL if nothing fits

void 	Cvar_Reset( const char *var_name );

void	Cvar_SetCheatState( void );
// reset all testing vars to a safe value

qboolean Cvar_Command( void );
// called by Cmd_ExecuteString when Cmd_Argv(0) doesn't match a known
// command.  Returns true if the command was a variable reference that
// was handled. (print or change)

void 	Cvar_WriteVariables( fileHandle_t f );
// writes lines containing "set variable value" for all variables
// with the archive flag set to true.

void	Cvar_Init( void );

char	*Cvar_InfoString( int bit );
// returns an info string containing all the cvars that have the given bit set
// in their flags ( CVAR_USERINFO, CVAR_SERVERINFO, CVAR_SYSTEMINFO, etc )
void	Cvar_InfoStringBuffer( int bit, char *buff, int buffsize );

void	Cvar_Restart_f( void );

extern	int			cvar_modifiedFlags;
// whenever a cvar is modifed, its flags will be OR'd into this, so
// a single check can determine if any CVAR_USERINFO, CVAR_SERVERINFO,
// etc, variables have been modified since the last check.  The bit
// can then be cleared to allow another change detection.

/*
==============================================================

FILESYSTEM

No stdio calls should be used by any part of the game, because
we need to deal with all sorts of directory and seperator char
issues.
==============================================================
*/

void	FS_InitFilesystem (void);

qboolean FS_Initialized( void );
int FS_LoadStack( void );
const char *FS_Gamedir (void);
void	FS_CreatePath(const char *OSPath);

void	FS_Restart( void );
// shutdown and restart the filesystem so changes to fs_gamedir can take effect

char	**FS_ListFiles( const char *directory, const char *extension, int *numfiles );
// directory should not have either a leading or trailing /
// if extension is "/", only subdirectories will be returned
// the returned files will not include any directories or /

void	FS_FreeFileList( char **list );

int	FS_GetFileList(  const char *path, const char *extension, char *listbuf, int bufsize );

fileHandle_t	FS_FOpenFileWrite( const char *qpath );
// will properly create any needed paths and deal with seperater character issues
fileHandle_t	FS_FOpenFileAppend( const char *qpath );

fileHandle_t FS_FOpenTextFileWrite( const char *qpath );

int		FS_FOpenFileRead( const char *qpath, fileHandle_t *file, qboolean uniqueFILE, qboolean quiet );
// if uniqueFILE is true, then a new FILE will be fopened even if the file
// is found in an already open pak file.  If uniqueFILE is false, you must call
// FS_FCloseFile instead of fclose, otherwise the pak FILE would be improperly closed
// It is generally safe to always set uniqueFILE to true, because the majority of
// file IO goes through FS_ReadFile, which Does The Right Thing already.

int	FS_FileIsInPAK(const char *filename );
// returns 1 if a file is in the PAK file, otherwise -1

int	FS_Write( const void *buffer, int len, fileHandle_t f );

int	FS_Read( void *buffer, int len, fileHandle_t f );
// properly handles partial reads and reads from other dlls

void	FS_FCloseFile( fileHandle_t f );
// note: you can't just fclose from another DLL, due to MS libc issues

char     *FS_PrepFileWrite( const char *filename );
int		FS_ReadFile( const char *qpath, void **buffer );
int		FS_ReadFileEx( const char *qpath, void **buffer, qboolean quiet );
// returns the length of the file
// a null buffer will just return the file length without loading
// as a quick check for existance. -1 length == not present
// A 0 byte will always be appended at the end, so string ops are safe.
// the buffer should be considered read-only, because it may be cached
// for other uses.

int		FS_ReadFileAndCache( const char *qpath, void **buffer );
// used by the clip model (CM_) system so that files that are read by
// both the CM_ and rendering systems can use the same buffer without
// reloading

void	FS_ForceFlush( fileHandle_t f );
// forces flush on files we're writing to.

void	FS_FreeFile( void *buffer );
// frees the memory returned by FS_ReadFile

void	FS_WriteFile( const char *qpath, const void *buffer, int size );
// writes a complete file, creating any subdirectories needed

void	FS_WriteTextFile( const char *qpath, const void *buffer, int size );
// writes a complete file, creating any subdirectories needed

int		FS_filelength( fileHandle_t f );
// doesn't work for files that are opened from a pack file

int		FS_FTell( fileHandle_t f );
// where are we?

void	FS_Flush( fileHandle_t f );

void 	FS_Printf( fileHandle_t f, const char *fmt, ... );
// like fprintf

int		FS_FOpenFileByMode( const char *qpath, fileHandle_t *f, fsMode_t mode );
// opens a file for reading, writing, or appending depending on the value of mode

int		FS_Seek( fileHandle_t f, long offset, int origin );
// seek on a file (doesn't seek backwards on zip files!!!!!!!!)

const char *FS_PureServerString( void );
// Returns a space separated string containing the checksums of all loaded pk3 files.
// Servers with sv_pure set will get this string and pass it to clients.

void	FS_SetPureServerString( const char *paks );
// If the string is empty, all data sources will be allowed.
// If not empty, only pk3 files that match one of the space
// separated checksums will be checked for files, with the
// sole exception of .cfg files.
void FS_FileTime( const char * filename, char * date, char * size );
// returns positive if src is newer than dest
// returns 0 if they are the same
// returns negative if dest is newer than src
int FS_FileNewer( const char * src, const char * dest );
void FS_DeleteFile( const char *filename );
void FS_CopyFile( char *fromOSPath, char *toOSPath );
void FS_CopyGameFile( char *fromPath, char *toPath );
/*
==============================================================

MISC

==============================================================
*/

// returnbed by Sys_GetProcessorId
#define CPUID_GENERIC			0			// any unrecognized processor

#define CPUID_AXP				0x10

#define CPUID_INTEL_UNSUPPORTED	0x20			// Intel 386/486
#define CPUID_INTEL_PENTIUM		0x21			// Intel Pentium or PPro
#define CPUID_INTEL_MMX			0x22			// Intel Pentium/MMX or P2/MMX
#define CPUID_INTEL_KATMAI		0x23			// Intel Katmai

#define CPUID_AMD_3DNOW			0x30			// AMD K6 3DNOW!

char		*CopyString( const char *in );
void		Info_Print( const char *s );

void		Com_BeginRedirect (char *buffer, int buffersize, void (*flush)(char *));
void		Com_EndRedirect( void );
void 		Com_Printf( const char *fmt, ... );
void 		Com_DPrintf( const char *fmt, ... );
void 		Com_DebugPrintf( const char *fmt, ... );
void 		Com_Error( int code, const char *fmt, ... );
void 		Com_Quit_f( void );
int		Com_EventLoop( void );
int		Com_Milliseconds( void );	// will be journaled properly
unsigned	Com_BlockChecksum( const void *buffer, int length );
int		Com_Filter(char *filter, char *name, int casesensitive);

void		Com_StartupVariable( const char *match );
// checks for and removes command line "+set var arg" constructs
// if match is NULL, all set commands will be executed, otherwise
// only a set with the exact name.  Only used during startup.

extern	cvar_t	*paused;
extern   cvar_t   *config;
extern	cvar_t	*fps;
#define TARGET_FRAMERATE 18

// current frame rate
extern   float    currentfps;

extern	cvar_t	*developer;

extern	cvar_t	*com_dedicated;
extern	cvar_t	*com_speeds;
extern	cvar_t	*com_timescale;
extern	cvar_t	*com_sv_running;
extern	cvar_t	*com_cl_running;
extern	cvar_t	*com_viewlog;			// 0 = hidden, 1 = visible, 2 = minimized
extern	cvar_t	*com_version;
extern	cvar_t	*com_buildScript;		// for building release pak files
extern	cvar_t	*com_journal;

// com_speeds times
extern	int		time_game;
extern	int		time_frontend;
extern	int		time_backend;		// renderer backend time

extern	int		com_frameTime;
extern	int		com_frameMsec;

extern	qboolean	com_errorEntered;

extern	fileHandle_t	com_journalFile;
extern	fileHandle_t	com_journalDataFile;

typedef enum {
	TAG_FREE,
	TAG_GENERAL,
	TAG_BOTLIB,
	TAG_RENDERER,
   TAG_GAME,
   TAG_CGAME,
   TAG_CLIENT,
   TAG_TIKI,
   TAG_STRINGS_AND_COMMANDS,
   TAG_SOUND,
   TAG_STATIC,
   TAG_STATIC_RENDERER,
   TAG_TEMP,
   TAG_NUM_TOTAL_TAGS // Don't use this tag, it's to get the size of all of them
} memtag_t;

/*

--- low memory ----
server vm
server clipmap
---mark---
renderer initialization (shaders, etc)
UI vm
cgame vm
renderer map
renderer models

---free---

temp file loading
--- high memory ---

*/

void Z_Free( void *ptr );
void *Z_Malloc( int size );			// returns 0 filled memory
void *Z_TagMalloc( int size, int tag );	// NOT 0 filled memory
void Z_FreeTags( int tag );
void Z_InitMemory( void );
void Z_Shutdown( void );

void Hunk_Clear( void );
void Hunk_ClearToMark( void );
void Hunk_SetMark( void );
qboolean Hunk_CheckMark( void );
void *Hunk_Alloc( int size );
void Hunk_ClearTempMemory( void );
void *Hunk_AllocateTempMemory( int size );
void Hunk_FreeTempMemory( void *buf );
int	Hunk_MemoryRemaining( void );

void Com_TouchMemory( void );

// commandLine should not include the executable name (argv[0])
void Com_Init( char *commandLine );
void Com_Frame( void );
void Com_Shutdown( void );
const char *Com_GetArchiveFileName( const char *filename, const char *extension );
void Com_WipeSavegame( const char *savename );
void Com_WriteConfiguration( void );
void Com_Pause_f( void );

#define SAVEGAME_DIRECTORY "save"
#define SAVEGAME_SERVER_EXTENSION "ssv"
#define SAVEGAME_GAME_EXTENSION "sav"
#define SAVEGAME_PERSISTANT_EXTENSION "spv"
#define SAVEGAME_IMAGE_EXTENSION "tga"

/*
==============================================================

CLIENT / SERVER SYSTEMS

==============================================================
*/

//
// client interface
//
void CL_InitKeyCommands( void );
// the keyboard binding interface must be setup before execing
// config files, but the rest of client startup will happen later

void CL_Init( void );
void CL_Disconnect( void );
void CL_Shutdown( void );
void CL_Frame( int msec );
qboolean CL_GameCommand( void );
void CL_KeyEvent (int key, qboolean down, unsigned time);
void CL_Key_ForceCommand( int key, unsigned time );

void CL_CharEvent( int key );
// char events are for field typing, not game control

void CL_GetMouseState( int *x, int *y, unsigned *buttons );
void CL_SetMousePos( int x, int y );

void CL_MouseEvent( int dx, int dy, int time );

void CL_JoystickEvent( int axis, int value, int time );

void CL_PacketEvent( netadr_t from, msg_t *msg );
void CL_UpdateLoadingScreen (void);

void UI_PrintConsole( char *text );

void CL_MapLoading( qboolean flush );
// do a screen update before starting to load a map
// when the server is going to load a new map, the entire hunk
// will be cleared, so the client must shutdown cgame, ui, and
// the renderer

void	CL_ForwardCommandToServer( void );
// adds the current command line as a clc_clientCommand to the client message.
// things like godmode, noclip, etc, are commands directed to the server,
// so when they are typed in at the console, they will need to be forwarded.

void CL_CDDialog( void );
// bring up the "need a cd to play" dialog

void CL_FlushMemory( void );
// dump all memory on an error

void CL_StartHunkUsers( void );

// used when the server disconnects abnormally
void CL_AbnormalDisconnect( void );

void Key_WriteBindings( fileHandle_t f );
// for writing the config files

//void S_ClearSoundBuffer( void );
// call before filesystem access

void SCR_DebugGraph (float value, int color);	// FIXME: move logging to common?


//
// server interface
//
void SV_Init( void );
void SV_Shutdown( const char *finalmsg );
void SV_Frame( int msec );
void SV_PacketEvent( netadr_t from, msg_t *msg );
qboolean SV_GameCommand( void );


//
// UI interface
//
qboolean UI_GameCommand( void );


/*
==============================================================

NON-PORTABLE SYSTEM SERVICES

==============================================================
*/

typedef enum {
	AXIS_SIDE,
	AXIS_FORWARD,
	AXIS_UP,
	AXIS_ROLL,
	AXIS_YAW,
	AXIS_PITCH,
	MAX_JOYSTICK_AXIS
} joystickAxis_t;

typedef enum {
	SE_NONE,	// evTime is still valid
	SE_KEY,		// evValue is a key code, evValue2 is the down flag
	SE_CHAR,	// evValue is an ascii char
	SE_MOUSE,	// evValue and evValue2 are reletive signed x / y moves
	SE_JOYSTICK_AXIS,	// evValue is an axis number and evValue2 is the current state (-127 to 127)
	SE_CONSOLE,	// evPtr is a char*
	SE_PACKET	// evPtr is a netadr_t followed by data bytes to evPtrLength
} sysEventType_t;

typedef struct {
	int				evTime;
	sysEventType_t	evType;
	int				evValue, evValue2;
	int				evPtrLength;	// bytes of data pointed to by evPtr, for journaling
	void			*evPtr;			// this must be manually freed if not NULL
} sysEvent_t;

sysEvent_t	Sys_GetEvent( void );

void	Sys_Init (void);

// general development dll loading for virtual machine testing
void	*Sys_LoadDll( const char *name, int (**entryPoint)(int, ...),
				  int (*systemcalls)(int, ...) );
void	Sys_UnloadDll( void *dllHandle );

void *Sys_LoadAPI( const char *name, const char *apiname );

void	Sys_UnloadGame( void );
void	*Sys_GetGameAPI( void *parms );

void	Sys_UnloadCGame( void );
void	*Sys_GetCGameAPI( void );

void	Sys_UnloadUI( void );
void	*Sys_GetUIAPI( void );

//bot libraries
void	Sys_UnloadBotLib( void );
void	*Sys_GetBotLibAPI( void *parms );

char	*Sys_GetCurrentUser( void );

void	Sys_Error( const char *error, ...);
void	Sys_Quit (void);
char	*Sys_GetClipboardData( void );	// note that this isn't journaled...

char *Sys_GetWholeClipboard ( void );
void  Sys_SetClipboard ( const char * );

void	Sys_Print( const char *msg );
void  Sys_DebugPrint( const char *msg );


// Sys_Milliseconds should only be used for profiling purposes,
// any game related timing information should come from event timestamps
int		Sys_Milliseconds (void);


// the system console is shown when a dedicated server is running
void	Sys_DisplaySystemConsole( qboolean show );

int		Sys_GetProcessorId( void );

void	Sys_BeginStreamedFile( fileHandle_t f, int readahead );
void	Sys_EndStreamedFile( fileHandle_t f );
int		Sys_StreamedRead( void *buffer, int size, int count, fileHandle_t f );
void	Sys_StreamSeek( fileHandle_t f, int offset, int origin );

void	Sys_ShowConsole( int level, qboolean quitOnClose );
void	Sys_SetErrorText( const char *text );

void	Sys_SendPacket( int length, const void *data, netadr_t to );

qboolean	Sys_StringToAdr( const char *s, netadr_t *a );
//Does NOT parse port numbers, only base addresses.

qboolean	Sys_IsLANAddress (netadr_t adr);

qboolean	Sys_CheckCD( void );

void	Sys_Mkdir( const char *path );
char	*Sys_Cwd( void );
char	*Sys_DefaultCDPath(void);
char	*Sys_DefaultBasePath(void);

char **Sys_ListFiles( const char *directory, const char *extension, int *numfiles );
void	Sys_FreeFileList( char **list );

void	Sys_BeginProfiling( void );
void	Sys_EndProfiling( void );

//
// Heap functions
//
unsigned Sys_HeapCreate( unsigned initsize, unsigned limit );
qboolean Sys_HeapDestroy( unsigned handle );
void * Sys_HeapAlloc( unsigned heap_handle, unsigned size );
qboolean Sys_HeapFree( unsigned heap_handle, void * ptr );
qboolean Sys_HeapCheck( unsigned heap_handle );

qboolean SaveRegistryInfo( qboolean user, const char *pszName, void *pvBuf, long lSize);
qboolean LoadRegistryInfo( qboolean user, const char *pszName, void *pvBuf, long *plSize);

#ifdef __cplusplus
	}
#endif

#endif // _QCOMMON_H_

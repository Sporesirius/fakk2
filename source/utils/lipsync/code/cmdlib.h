//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/lipsync/code/cmdlib.h                        $
// $Revision:: 1                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 2/15/00 12:17p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/lipsync/code/cmdlib.h                             $
// 
// 1     2/15/00 12:17p Steven
// 
// 14    6/08/98 11:10a Markd
// Fixed const char * stuff
// 
// 13    5/22/98 9:56a Markd
// fixed const char * stuff
// 
// 12    4/30/98 11:57a Markd
// Added WinSlashify
// 
// 11    4/17/98 4:07p Markd
// 
// 10    4/01/98 4:15p Markd
// changed strcmp to strcmpi
// 
// 9     2/22/98 3:42p Markd
// Added Cplusplus stuff
// 
// 8     2/03/98 9:33p Markd
// Added Unsigned "Little" functions
// 
// 7     1/16/98 6:41p Aldie
// Made changes for sindata
// 
// 6     1/16/98 5:00p Aldie
// Changed sinutils to sin
// 
// 5     1/13/98 10:44a Aldie
// Added ProcessDirectory from old cmdlib.c
// 
// 4     12/31/97 12:55p Markd
// Added LoadFileNoCrash and ExtractFileName
// 
// 3     12/30/97 6:30p Jimdose
// Added header text
//
// DESCRIPTION:
// 

#ifndef __CMDLIB__
#define __CMDLIB__

#ifdef _WIN32
#pragma warning(disable : 4244)     // MIPS
#pragma warning(disable : 4136)     // X86
#pragma warning(disable : 4051)     // ALPHA

#pragma warning(disable : 4018)     // signed/unsigned mismatch
#pragma warning(disable : 4305)     // truncate from double to float
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>

#ifndef __BYTEBOOL__
#define __BYTEBOOL__
typedef enum {false, true} qboolean;

typedef unsigned char byte;
// JIM
typedef unsigned short word;
#endif

// the dec offsetof macro doesnt work very well...
#define myoffsetof(type,identifier) ((size_t)&((type *)0)->identifier)

#ifdef SIN
#ifdef __cplusplus
extern "C" {
#endif
#endif

// set these before calling CheckParm
extern int myargc;
extern char **myargv;

char *strupr (char *in);
char *strlower (char *in);
int Q_strncasecmp (const char *s1, const char *s2, int n);
int Q_strcasecmp (const char *s1, const char *s2);
void Q_getwd (char *out);

int Q_filelength (FILE *f);
#ifdef SIN
int	FileTime (const char *path);
void	Q_mkdir (const char *path);
#else
int	FileTime (char *path);
void	Q_mkdir (char *path);
#endif

extern	char		qdir[1024];
extern	char		gamedir[1024];
#ifdef SIN
void SetQdirFromPath (const char *path);
const char *ExpandArg (const char *path);	// from cmd line
const char *ExpandPath (const char *path);	// from scripts
const char *ExpandPathAndArchive (const char *path);
#else
void SetQdirFromPath (char *path);
char *ExpandArg (char *path);	// from cmd line
char *ExpandPath (char *path);	// from scripts
char *ExpandPathAndArchive (char *path);
#endif


double I_FloatTime (void);

void	Error (char *error, ...);
int		CheckParm (char *check);

#ifdef SIN
FILE	*SafeOpenWrite (const char *filename);
FILE	*SafeOpenRead (const char *filename);
#else
FILE	*SafeOpenWrite (char *filename);
FILE	*SafeOpenRead (char *filename);
#endif
void	SafeRead (FILE *f, void *buffer, int count);
void	SafeWrite (FILE *f, void *buffer, int count);

#ifdef SIN
int		LoadFile (const char *filename, void **bufferptr);
int		TryLoadFile (const char *filename, void **bufferptr);
void	   SaveFile (const char *filename, void *buffer, int count);
qboolean	FileExists (const char *filename);
void 	ExtractFilePath (const char *path, char *dest);
void 	ExtractFileBase (const char *path, char *dest);
void	ExtractFileExtension (const char *path, char *dest);
#else
int		LoadFile (char *filename, void **bufferptr);
int		TryLoadFile (char *filename, void **bufferptr);
void	SaveFile (char *filename, void *buffer, int count);
qboolean	FileExists (char *filename);
void 	ExtractFilePath (char *path, char *dest);
void 	ExtractFileBase (char *path, char *dest);
void	ExtractFileExtension (char *path, char *dest);
#endif

void 	DefaultExtension (char *path, char *extension);
void 	DefaultPath (char *path, char *basepath);
void 	StripFilename (char *path);
void 	StripExtension (char *path);


int 	ParseNum (char *str);

short	BigShort (short l);
short	LittleShort (short l);
int		BigLong (int l);
int		LittleLong (int l);
float	BigFloat (float l);
float	LittleFloat (float l);

#ifdef SIN
unsigned short	BigUnsignedShort (unsigned short l);
unsigned short	LittleUnsignedShort (unsigned short l);
unsigned	      BigUnsigned (unsigned l);
unsigned	      LittleUnsigned (unsigned l);
#endif


char *COM_Parse (char *data);

extern	char		com_token[1024];
extern	qboolean	com_eof;

#ifdef SIN
char *copystring(const char *s);
#else
char *copystring(char *s);
#endif


void CRC_Init(unsigned short *crcvalue);
void CRC_ProcessByte(unsigned short *crcvalue, byte data);
unsigned short CRC_Value(unsigned short crcvalue);

#ifdef SIN
void	QCopyFile (const char *from, const char *to);
#else
void	QCopyFile (char *from, char *to);
#endif
void	CreatePath (char *path);

extern	qboolean		archive;
extern	char			archivedir[1024];


extern	qboolean verbose;
void qprintf (char *format, ...);

void ExpandWildcards (int *argc, char ***argv);
#ifdef SIN
int  LoadFileNoCrash (const char *filename, void **bufferptr);
void ExtractFileName (const char *path, char *dest);
#else
int  LoadFileNoCrash (char *filename, void **bufferptr);
void ExtractFileName (char *path, char *dest);
#endif


// for compression routines
typedef struct
{
	byte	*data;
	int		count;
} cblock_t;


// SIN
#ifdef SIN
typedef void (*processfile_t) (char *, char *);
void ProcessDirectory 
   ( 
   char * dir, 
   char * name, 
   char * ext, 
   processfile_t func, 
   qboolean recurse 
   );
void ProcessWildDirectory 
   ( 
   char * dir, 
   char * name, 
   char * wild, 
   processfile_t func, 
   qboolean recurse 
   );
void DeSlashify (char * in);
void WinSlashify (char * in);
FILE *SafeOpenWriteText (const char *filename);

char *COM_GetToken(char **data_p, qboolean crossline);
const char *COM_FileExtension (const char *in);

void *Hunk_Begin (int maxsize);
void *Hunk_Alloc (int size);
int Hunk_End (void);
void Hunk_Free (void *base);
#endif

#ifdef SIN
#ifdef __cplusplus
   }
#endif
#endif

#endif


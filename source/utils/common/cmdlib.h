//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/common/cmdlib.h                 $
// $Revision:: 10                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 3/17/00 11:50a                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/common/cmdlib.h                      $
// 
// 10    3/17/00 11:50a Markd
// working on tiki conversion
// 
// 9     3/17/00 11:34a Markd
// Added ProcessWildDirectory stuff
// 
// 8     12/11/99 4:45p Markd
// q3a gold merge
// 
// 7     11/24/99 6:53p Markd
// Made timing function more accurate
// 
// 6     10/11/99 3:36p Markd
// Added checksum support to the header of the bsp
// 
// 5     9/23/99 4:02p Markd
// Added misc_model support to q3map
// 
// 4     9/15/99 12:12p Markd
// Merged in Carmack's latest build
// 
// 3     9/14/99 8:38a Markd
// merged latest q3
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

#ifdef _WIN32

#pragma intrinsic( memset, memcpy )

#endif

#ifndef __BYTEBOOL__
#define __BYTEBOOL__
#ifdef __cplusplus
typedef int qboolean;
typedef enum {qfalse, qtrue};
#else
typedef enum {qfalse, qtrue} qboolean;
#endif
typedef unsigned char byte;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define	MAX_OS_PATH		1024

// the dec offsetof macro doesnt work very well...
#define myoffsetof(type,identifier) ((size_t)&((type *)0)->identifier)


// set these before calling CheckParm
extern int myargc;
extern char **myargv;

char *strupr (char *in);
char *strlower (char *in);
int Q_strncasecmp( const char *s1, const char *s2, int n );
int Q_stricmp( const char *s1, const char *s2 );
void Q_getwd( char *out );

int Q_filelength (FILE *f);
int	FileTime( const char *path );

void	Q_mkdir( const char *path );

extern	char		qdir[1024];
extern	char		gamedir[1024];
extern  char		writedir[1024];
void SetQdirFromPath( const char *path );
char *ExpandArg( const char *path );	// from cmd line
char *ExpandPath( const char *path );	// from scripts
char *ExpandGamePath (const char *path);
char *ExpandPathAndArchive( const char *path );


double I_FloatTime( void );
double I_MilliSeconds (void);

void	Error( const char *error, ... );
int		CheckParm( const char *check );

FILE	*SafeOpenWrite( const char *filename );
FILE	*SafeOpenRead( const char *filename );
void	SafeRead (FILE *f, void *buffer, int count);
void	SafeWrite (FILE *f, const void *buffer, int count);

int		LoadFile( const char *filename, void **bufferptr );
int		TryLoadFile( const char *filename, void **bufferptr );
void	SaveFile( const char *filename, const void *buffer, int count );
qboolean	FileExists( const char *filename );

void 	DefaultExtension( char *path, const char *extension );
void 	DefaultPath( char *path, const char *basepath );
void 	StripFilename( char *path );
void 	StripExtension( char *path );

void 	ExtractFilePath( const char *path, char *dest );
void 	ExtractFileBase( const char *path, char *dest );
void	ExtractFileExtension( const char *path, char *dest );

int 	ParseNum (const char *str);

short	BigShort (short l);
short	LittleShort (short l);
unsigned short	BigUnsignedShort (unsigned short l);
unsigned short	LittleUnsignedShort (unsigned short l);
int		BigLong (int l);
int		LittleLong (int l);
float	BigFloat (float l);
float	LittleFloat (float l);


char *COM_Parse (char *data);

extern	char		com_token[1024];
extern	qboolean	com_eof;

char *copystring(const char *s);


void CRC_Init(unsigned short *crcvalue);
void CRC_ProcessByte(unsigned short *crcvalue, byte data);
unsigned short CRC_Value(unsigned short crcvalue);

unsigned Com_BlockChecksum (void *buffer, int length);

void	CreatePath( const char *path );
void	QCopyFile( const char *from, const char *to );

extern	qboolean		archive;
extern	char			archivedir[1024];


extern	qboolean verbose;
void qprintf( const char *format, ... );

void ExpandWildcards( int *argc, char ***argv );


// for compression routines
typedef struct
{
	void	*data;
	int		count, width, height;
} cblock_t;

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
void ExtractFileName (const char *path, char *dest);

#ifdef __cplusplus
   }
#endif

#endif
//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/tgaconvert/tgaconvert.c                      $
// $Revision:: 6                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 7/24/00 5:29p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/tgaconvert/tgaconvert.c                           $
// 
// 6     7/24/00 5:29p Markd
// fixed bug in tga conversion process
// 
// 5     7/22/00 12:12a Markd
// fixed conversion bug
// 
// 4     7/21/00 3:16a Markd
// made wrong tga type a soft error so tool could continue
// 
// 3     7/21/00 2:35a Markd
// fixed small bug
// 
// 2     7/21/00 2:32a Markd
// first time check in for tgaconvert
// 
// 1     7/21/00 1:58a Markd
// 
// DESCRIPTION:
// TGACONVERT - Convert all TGA's to right side up 32-bit color TGA's
//
#include <direct.h>
#include <windows.h>
#include "cmdlib.h"
#include "mathlib.h"
#include "imagelib.h"
#include "qfiles.h"

#define VERSION "1.0"
char **  _argv;
int      _argc;
qboolean force = qfalse;
qboolean recursive = qfalse;
char filespec[1024];
char basedir[1024];

/*
=============
ConvertTGA
=============
*/
void ConvertTGA ( const char *name, const char * shortname )
   {
   FILE * fp;
   char srcfile[ 1024 ];
   char destfile[ 1024 ];
   unsigned * buffer;
   qboolean has_alpha;
   int len;
   int width, height;
   int srcTime, destTime;
   ftx_t header;

   strcpy( srcfile, shortname );

   strcpy( destfile, shortname );

   // replace extension with FTX extesion
   len = strlen( destfile );
   destfile[ len - 3 ] = 'f';
   destfile[ len - 2 ] = 't';
   destfile[ len - 1 ] = 'x';

   // get dest file time
   destTime = FileTime( destfile );
   // get src file time
   srcTime = FileTime( shortname );
   // see if we need to update
   if ( !force && ( ( destTime != -1 ) && ( destTime > srcTime ) ) )
      return;

   printf("  converting %s.\n", name );

   buffer = NULL;

   Load32BitImage( srcfile, &buffer, &width, &height, &has_alpha );

   if ( !buffer )
      {
      printf("  cannot convert %s.\n", name );
      return;
      }

   header.width = width;
   header.height = height;
   header.has_alpha = has_alpha;

   fp = SafeOpenWrite( destfile );
   SafeWrite( fp, &header, sizeof( header ) );
   SafeWrite( fp, buffer, width * height * 4 );
   fclose( fp );
   free( buffer );
   }

/*
======================
FixArgs
======================
*/
char * FixArgs(char *arg)
    {
    char *p;

    p = arg;
    DeSlashify(p);
    return arg;
    }

/*
=================
ConvertFile
filename is the name of the file we want to convert
name is the path of the file (built from process_directory)
=================
*/
void ConvertFile ( char * filename, char * name )
   {
   char fullname[ 1024 ];

   strcpy( fullname, name );
   strcat( fullname, filename );
   ConvertTGA( fullname, filename );
   }

/*
======================
Convert
======================
*/
void Convert( const char * wild, qboolean recursive )
   {
   char path[ 1024 ];
   char search[ 1024 ];
   char name[ 1024 ];

   if ( recursive )
      {
      printf( "recursively converting %s\n", wild );
      }
   else
      {
      printf( "            converting %s\n", wild );
      }

   memset( path, 0, sizeof( path ) );
   strcpy( name, wild );
   FixArgs( name );
   ExtractFilePath( name, path );
   ExtractFileName( name, search );
   strcpy( name, path );

   if ( !path[0] )
      strcpy( path, basedir );

   ProcessWildDirectory( path, name, search, ConvertFile, recursive );
   }

void Usage( void )
    {
    printf("USAGE:\n");
    printf("   tgaconvert [-v erbose] [-r ecursive] [-f orce] <file spec (*.tga)>\n");
    }

extern qboolean verbose;

void ParseArguments( void )
   {
   int i;

   qprintf ("argc = %d\n",_argc);
   i = 1;
   while (i<_argc && _argv[i][0]=='-')
       {
        switch( _argv[i][1] )
            {
            case 'v':
                verbose = qtrue;
                break;
            case 'r':
                recursive = qtrue;
                break;
            case 'f':
                force = qtrue;
                break;
            default:
                Usage();
                exit( 0 );
            }
        i++;
        }

    if (i+1>_argc)
       {
       Usage();
       exit( 0 );
       }
    strcpy( filespec, _argv[i] );
    }

/*
==============================
main
==============================
*/
int main (int argc, char **argv)
   {
   _argc = argc;
   _argv = argv;

   printf ("\nTGACONVERT "VERSION" copyright (c) 2000 Ritual Entertainment\n");

   ParseArguments();

   // get the current directory
   _getcwd(basedir,1024);

   Convert( filespec, recursive );

   return 0;
   }

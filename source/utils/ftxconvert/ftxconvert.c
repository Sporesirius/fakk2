//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/ftxconvert/ftxconvert.c                      $
// $Revision:: 4                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 9/12/00 12:13p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/ftxconvert/ftxconvert.c                           $
// 
// 4     9/12/00 12:13p Markd
// fixed documentation
// 
// 3     9/12/00 12:12p Markd
// first time
// 
// 2     9/11/00 6:41p Markd
// 
// 1     9/11/00 6:22p Markd
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
// FTXCONVERT - Convert all FTX's to right side up 32-bit color TGA's
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
ConvertFTX
=============
*/
void ConvertFTX ( const char *name, const char * shortname )
   {
   FILE * fp;
   char srcfile[ 1024 ];
   char destfile[ 1024 ];
   byte * pic_buffer;
   qboolean has_alpha;
   int len;
   int width, height;
   int srcTime, destTime;
	byte * buffer;
   byte * rgb;
	int size, row, column;
   ftx_t header;

   strcpy( srcfile, shortname );

   strcpy( destfile, shortname );

   // replace extension with TGA extesion
   len = strlen( destfile );
   destfile[ len - 3 ] = 't';
   destfile[ len - 2 ] = 'g';
   destfile[ len - 1 ] = 'a';

   // get dest file time
   destTime = FileTime( destfile );
   // get src file time
   srcTime = FileTime( shortname );
   // see if we need to update
   if ( !force && ( ( destTime != -1 ) && ( destTime > srcTime ) ) )
      return;

   printf("  converting %s.\n", name );

   buffer = NULL;

   // read in the ftx file
   fp = SafeOpenRead( srcfile );
   SafeRead( fp, &header, sizeof( header ) );

   width = header.width;
   height = header.height;
   has_alpha = header.has_alpha;

   pic_buffer = malloc( width * height * 4 );
   SafeRead( fp, pic_buffer, width * height * 4 );
   fclose ( fp );

   if ( !pic_buffer )
      {
      printf("  cannot convert %s.\n", name );
      return;
      }

   if ( has_alpha )
      {
      size = width * height * 4 + 18;
      }
   else
      {
	   size = width * height * 3 + 18;
      }

	buffer = malloc( size );

	memset (buffer, 0, 18);
	buffer[2] = 2;		// uncompressed type
	buffer[12] = width & 255;
	buffer[13] = width >> 8;
	buffer[14] = height & 255;
	buffer[15] = height >> 8;
   if ( has_alpha )
      {
	   buffer[16] = 32;	// pixel size
      }
   else
      {
	   buffer[16] = 24;	// pixel size
      }
   // copy the image to the buffer
   rgb = pic_buffer;
	for( row = height - 1; row >= 0; row-- ) 
      {
		for( column = 0; column < width; column++, rgb += 4 ) 
         {
         byte * dest;

         if ( has_alpha )
            {
            dest = &buffer[ ( row * width + column ) * 4 + 18 ];
            }
         else
            {
            dest = &buffer[ ( row * width + column ) * 3 + 18 ];
            }
         //
         // swap as we go to bgr
         //
         dest[ 0 ] = rgb[ 2 ];
         dest[ 1 ] = rgb[ 1 ];
         dest[ 2 ] = rgb[ 0 ];
         // add alpha if necessary
         if ( has_alpha )
            {
            dest[ 3 ] = rgb[ 3 ];
            }
         }
      }
   SaveFile( destfile, buffer, size );
   
   free( buffer );

   free( pic_buffer );
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
   ConvertFTX( fullname, filename );
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
    printf("   ftxconvert [-v erbose] [-r ecursive] [-f orce] <file spec (*.ftx)>\n");
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

   printf ("\nFTXCONVERT "VERSION" copyright (c) 2000 Ritual Entertainment\n");

   ParseArguments();

   // get the current directory
   _getcwd(basedir,1024);

   Convert( filespec, recursive );

   return 0;
   }

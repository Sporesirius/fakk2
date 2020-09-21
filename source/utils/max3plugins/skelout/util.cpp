//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max3plugins/skelout/util.cpp                 $
// $Revision:: 4                                                              $
//     $Date:: 12/13/99 2:16p                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max3plugins/skelout/util.cpp                      $
// 
// 4     12/13/99 2:16p Jimdose
// changed Error to throw an exception
// 
// 3     9/07/99 3:12p Jimdose
// rewrote for ascii output
// 
// 2     7/30/99 4:23p Jimdose
// working on skel output
//
// DESCRIPTION:
// 

#include "util.h"
#include "windows.h"
#include "stdarg.h"
#include "stdio.h"

void Error
   (
   char *error,
   ...
   )

   {
	va_list  argptr;
	char	   text[ 1024 ];
	char	   text2[ 1024 ];
	int		err;
   static   in_error = false;;

   if ( in_error )
      {
      return;
      }

   in_error = true;

	err = GetLastError();

	va_start( argptr, error );
	vsprintf( text, error, argptr );
	va_end( argptr );

	sprintf( text2, "%s\nGetLastError() = %i", text, err );

   throw text2;
   }

FILE *SafeOpenWrite
   (
   const char *filename
   )

   {
	FILE	*f;

	f = fopen( filename, "wb" );
	if ( !f )
      {
		Error( "Error opening %s: %s", filename, strerror( errno ) );
      }

	return f;
   }

FILE *SafeOpenWriteText
   (
   const char *filename
   )

   {
	FILE	*f;

	f = fopen( filename, "wt" );
	if ( !f )
      {
		Error( "Error opening %s: %s", filename, strerror( errno ) );
      }

	return f;
   }

void SafeWrite
   (
   FILE *f,
   void *buffer,
   int count
   )

   {
	if ( fwrite( buffer, 1, count, f ) != ( size_t )count )
      {
		Error( "File write failure" );
      }
   }

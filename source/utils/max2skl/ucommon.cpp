//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/ucommon.cpp                      $
// $Revision:: 2                                                              $
//     $Date:: 9/27/99 5:02p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/ucommon.cpp                           $
// 
// 2     9/27/99 5:02p Jimdose
// removed Error
// 
// 1     9/21/99 2:30p Jimdose
// 
// 3     8/27/99 7:09p Morbid
// Debugger stream changes
// 
// 2     5/28/99 5:28p Jimdose
// moved global functions into namespaces and classes
// 
// 1     5/27/99 8:39p Jimdose
//
// DESCRIPTION:
// 

#include "ucommon.h"
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

cvar_t developer = { 0 };

float global::time = 0;
UDebuggerStream global::debugger;

// Force compiler to link winmm.lib
#pragma comment(lib, "winmm.lib")

/*
===============
DPrintf

Outputs a string to the debug window
===============
*/
void DPrintf
	(
	const char *fmt,
	...
	)

	{
	va_list	argptr;
   char		message[ 1024 ];

	va_start( argptr, fmt );
	vsprintf( message, fmt, argptr );
	va_end( argptr );

#ifdef _WIN32
   OutputDebugString( message );
#else
   printf( message );
#endif
	}

void ShowSystemError
   (
   void
   )

   {
   LPTSTR lpMsgBuf;

   FormatMessage( 
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      GetLastError(),
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
      (LPTSTR) &lpMsgBuf,
      0,
      NULL 
      );

   // Display the string.
   DPrintf( "%s\n", lpMsgBuf );

   MessageBox( NULL, lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );

   // Free the buffer.
   LocalFree( lpMsgBuf );
   }

/*
============
va

does a varargs printf into a temp buffer, so I don't need to have
varargs versions of all text functions.
FIXME: make this buffer size safe someday
============
*/
const char *va
   (
   const char *format, 
   ...
   )

   {
	va_list		argptr;
	static char	string[1024];
	
	va_start (argptr, format);
	vsprintf (string, format,argptr);
	va_end (argptr);

	return string;	
   }

void UDebuggerStream::StreamIn 
   (
   const char *data
   )

   {
   OutputDebugString ( data );
   }


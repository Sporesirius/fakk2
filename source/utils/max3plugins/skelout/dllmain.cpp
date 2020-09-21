//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2plugins/skelout/dllmain.cpp              $
// $Revision:: 2                                                              $
//     $Date:: 7/30/99 4:23p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2plugins/skelout/dllmain.cpp                   $
// 
// 2     7/30/99 4:23p Jimdose
// working on skel output
//
// DESCRIPTION:
// 

#include "dllmain.h"
#include "skelout.h"

HINSTANCE hInstance;

static bool controlsInit = false;

/** public functions **/
BOOL WINAPI DllMain
   (
   HINSTANCE hinstDLL,
   ULONG fdwReason,
   LPVOID lpvReserved
   )

   {
	hInstance = hinstDLL;

   if ( !controlsInit )
      {
		controlsInit = TRUE;

		// jaguar controls
		InitCustomControls( hInstance );

		// initialize Chicago controls
		InitCommonControls();
		}

	return TRUE;
	}

//------------------------------------------------------
// This is the interface to Jaguar:
//------------------------------------------------------

__declspec( dllexport ) const TCHAR *LibDescription
   (
   void
   )

   {
   return _T( "Skel Anim Single Export" );
   }

__declspec( dllexport ) int LibNumberClasses
   (
   void
   )

   {
   return 1;
   }

__declspec( dllexport ) ClassDesc *LibClassDesc
   (
   int i
   )

   {
   switch( i )
      {
      case 0 :
         return &SkelOutDesc;
         break;

      default :
         return 0;
         break;
      }
   }

// Return version so can detect obsolete DLLs
__declspec( dllexport ) ULONG LibVersion
   (
   void
   )

   {
   return VERSION_3DSMAX;
   }

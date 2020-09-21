//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/usys.h                           $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:32p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/usys.h                                $
// 
// 1     9/21/99 2:32p Jimdose
// 
// 2     9/17/99 4:08p Morbid
// More sys functions and revised file finding
// 
// 1     9/07/99 3:25p Morbid
// Created
//
// DESCRIPTION:
// 

#ifndef __USYS_H__
#define __USYS_H__

#include "time.h"

namespace USys
   {
   typedef struct 
      {
      time_t time;
      str name;
      bool isDirectory;
      } findresult_t;

   typedef unsigned findhandle_t; // OS-specific find handle

   findhandle_t FileFindFirst ( const char *name, findresult_t * );
   bool FileFindNext ( findhandle_t, findresult_t * );
   void FileFindClose ( findhandle_t );
   time_t FileGetTime ( const char *name );

   str GetWorkingDirectory ();

   bool Mkdir ( const char * ); // returns true is dir exists or make worked
   };

#endif /* !__USYS_H__ */
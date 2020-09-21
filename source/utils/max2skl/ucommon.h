//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/ucommon.h                        $
// $Revision:: 2                                                              $
//     $Date:: 9/27/99 5:02p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/ucommon.h                             $
// 
// 2     9/27/99 5:02p Jimdose
// removed Error
// 
// 1     9/21/99 2:30p Jimdose
// 
// 8     9/17/99 4:08p Morbid
// included usys
// 
// 7     8/27/99 7:08p Morbid
// Added debugger stream to global namespace
// 
// 6     7/06/99 12:42p Morbid
// Various changes
// 
// 5     6/25/99 7:43p Morbid
// 
// 4     6/17/99 2:09p Morbid
// Lots of misc shit
// 
// 
// 3     5/28/99 5:28p Jimdose
// moved global functions into namespaces and classes
// 
// 2     5/27/99 8:40p Jimdose
// merged math and gui code
//
// DESCRIPTION:
// 

#ifndef __UCOMMON_H__
#define __UCOMMON_H__

typedef unsigned char byte;

struct cvar_t {
   int integer;
   };

extern cvar_t developer;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#include <math.h>
#include <memory.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <gl/gl.h>
#include <gl/glu.h>

#define ASSERT assert

#include "ucasts.h"
#include "umath.h"
#include "umem.h"
#include "uparse.h"
#include "str.h"
#include "streams.h"
#include "usys.h"

typedef unsigned char byte;

//FIXME
//Don't use vargs here?
//add to a namespace
void        DPrintf( const char *fmt, ... );
const char  *va(const char *format, ...);
void        ShowSystemError( void );

class UDebuggerStream : public UStringStreamIn 
   {
   void StreamIn ( const char * );
   };

namespace global
   {
   extern float time;
   extern UDebuggerStream debugger;
   };


#endif
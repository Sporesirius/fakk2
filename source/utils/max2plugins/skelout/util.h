//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2plugins/skelout/util.h                   $
// $Revision:: 3                                                              $
//     $Date:: 9/07/99 3:12p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2plugins/skelout/util.h                        $
// 
// 3     9/07/99 3:12p Jimdose
// rewrote for ascii output
// 
// 2     7/30/99 4:23p Jimdose
// working on skel output
//
// DESCRIPTION:
// 

#ifndef __UTIL_H__
#define __UTIL_H__

#include "stdio.h"

void  Error( char *error, ... );
FILE  *SafeOpenWrite( const char *filename );
FILE  *SafeOpenWriteText( const char *filename );
void  SafeWrite( FILE *f, void *buffer, int count );

#endif /* !__UTIL_H__ */
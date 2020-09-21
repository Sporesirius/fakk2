//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/lipsync/code/scriplib.h                      $
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
// $Log:: /fakk2_code/Utils/lipsync/code/scriplib.h                           $
// 
// 1     2/15/00 12:17p Steven
// 
// 5     6/08/98 11:10a Markd
// Fixed const char * stuff
// 
// 4     2/04/98 5:04p Markd
// Added Push and Pop Script
// 
// 3     12/30/97 6:31p Jimdose
// Added header text
//
// DESCRIPTION:
// 

#ifndef __CMDLIB__
#include "cmdlib.h"
#endif

#define	MAXTOKEN	1024

extern	char	token[MAXTOKEN];
extern	char	*scriptbuffer,*script_p,*scriptend_p;
extern	int		grabbed;
extern	int		scriptline;
extern	qboolean	endofscript;


#ifdef SIN
void LoadScriptFile (const char *filename);
#else
void LoadScriptFile (char *filename);
#endif
void ParseFromMemory (char *buffer, int size);

qboolean GetToken (qboolean crossline);
void UnGetToken (void);
qboolean TokenAvailable (void);

#ifdef SIN
void PushScript( void );
void PopScript( void );
#endif



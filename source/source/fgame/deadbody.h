//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/deadbody.h                         $
// $Revision:: 1                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 9/10/99 10:53a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/deadbody.h                              $
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
//
// DESCRIPTION:
// Dead body

#ifndef __DEADBODY_H__
#define __DEADBODY_H__

#include "g_local.h"
#include "sentient.h"

#define BODY_QUEUE_SIZE		4

void InitializeBodyQueue( void );
void CopyToBodyQueue( gentity_t *ent );

class Deadbody : public Sentient
	{
	public:
      CLASS_PROTOTYPE( Deadbody );

      virtual void   GibEvent( Event *ev );
	};

#endif /* deadbody.h */
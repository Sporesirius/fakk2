//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/light.cpp                          $
// $Revision:: 7                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 3:50p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/light.cpp                               $
// 
// 7     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 6     10/18/99 7:14p Markd
// Fixed fulcrum stuff
// 
// 5     10/11/99 1:08p Markd
// Added angles and spot_angle support to lights
// 
// 4     10/05/99 8:05p Markd
// Forgot to add light handling behavior
// 
// 3     10/05/99 7:58p Markd
// Rewrote light documentation
// 
// 2     9/29/99 5:18p Steven
// Event formatting.
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 9     7/08/99 4:28p Markd
// Removed obsolete QUAKED functions
// 
// 8     6/11/99 1:23p Phook
// 
// 7     6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 6     6/11/99 12:46p Phook
// EClass color changes
// 
// DESCRIPTION:
// Classes for creating and controlling lights.
// 

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "light.h"
#include "scriptmaster.h"

/*****************************************************************************/
/*QUAKED light (0.75 0.5 0) (-8 -8 -8) (8 8 8) LINEAR NO_ENTITIES ENTITY_TRACE

Non-displayed light. If it targets another entity it will become a spot light
if "LINEAR" is set, it will be a linear light
if "NO_ENTITIES" is set, this light will only effect the world, not entities
if "ENTITY_TRACE" is set, a trace is done betwee the light and the entity.\
The light is only added if the trace is clear

"no_entity_light" - this light will not effect entities, just the world
"light" - the intensity of the light, default 300       
"color" - the color of the light
"falloff" - if linear, specify the linear falloff (defaults to 1)
"radius" - make this a spot light of the given radius
"angles" - make this a spot light centered on angles
"spot_angle" - if this is a spot light, what angle to use (default 45)
"entity_trace" - trace between the entity and the light

******************************************************************************/

Event EV_Light_SetLight
	( 
	"light",
	EV_DEFAULT,
   NULL,
   NULL,
   "Set the intensity of the light"
	);

Event EV_Light_SetColor
	( 
	"color",
	EV_DEFAULT,
   NULL,
   NULL,
   ""
	);

Event EV_Light_SetFalloff
	( 
	"falloff",
	EV_HIDE,
   NULL,
   NULL,
   ""
	);

Event EV_Light_SetRadius
	( 
	"falloff",
	EV_HIDE,
   NULL,
   NULL,
   ""
	);

Event EV_Light_SpotDir
	( 
	"spot_dir",
	EV_HIDE,
   NULL,
   NULL,
   ""
	);

Event EV_Light_SpotRadiusByDistance
	( 
	"spot_radiusbydistance",
	EV_HIDE,
   NULL,
   NULL,
   ""
	);

Event EV_Light_NoEntityLight
	( 
	"no_entity_light",
	EV_HIDE,
   NULL,
   NULL,
   ""
	);

Event EV_Light_EntityTrace
	( 
	"entity_trace",
	EV_HIDE,
   NULL,
   NULL,
   ""
	);

Event EV_Light_SpotAngle
	( 
	"spot_angle",
	EV_HIDE,
   NULL,
   NULL,
   ""
	);

CLASS_DECLARATION( Entity, Light, "light" )
	{
      { &EV_Light_SetLight, NULL },
		{ NULL, NULL }
	};

Light::Light()
	{
   PostEvent( EV_Remove, 0 );
	}


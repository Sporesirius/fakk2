//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/g_spawn.h                          $
// $Revision:: 5                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 7/27/00 9:52p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/g_spawn.h                               $
// 
// 5     7/27/00 9:52p Markd
// Added FindClass function
// 
// 4     6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 3     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 2     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 7     8/28/99 3:42p Jimdose
// changed some doubles to floats
//
// DESCRIPTION:
//

#ifndef __G_SPAWN_H__
#define __G_SPAWN_H__

#include "entity.h"

// spawnflags
// these are set with checkboxes on each entity in the map editor
#define	SPAWNFLAG_NOT_EASY			0x00000100
#define	SPAWNFLAG_NOT_MEDIUM			0x00000200
#define	SPAWNFLAG_NOT_HARD			0x00000400
#define	SPAWNFLAG_NOT_DEATHMATCH	0x00000800
#define	SPAWNFLAG_DEVELOPMENT		0x00002000
#define	SPAWNFLAG_DETAIL		      0x00004000

class SpawnArgs : public Class
   {
   private:
      Container<str> keyList;
      Container<str> valueList;

   public:
                     CLASS_PROTOTYPE( SpawnArgs );

                     SpawnArgs();
                     SpawnArgs( SpawnArgs &arglist );

      void           Clear( void );

      const char     *Parse( const char *data );
      const char     *getArg( const char *key, const char *defaultValue = NULL );
      void           setArg( const char *key, const char *value );

      int            NumArgs( void );
      const char     *getKey( int index );
      const char     *getValue( int index );
		void           operator=( SpawnArgs &a );

      ClassDef       *getClassDef( qboolean *tikiWasStatic = NULL );
      Entity		   *Spawn( void );

	   virtual void   Archive( Archiver &arc );
	};

void			G_InitClientPersistant( gclient_t *client );
ClassDef    *FindClass( const char *name, qboolean *isModel	);

#endif


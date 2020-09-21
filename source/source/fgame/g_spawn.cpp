//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/g_spawn.cpp                        $
// $Revision:: 22                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/27/00 9:52p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/g_spawn.cpp                             $
// 
// 22    7/27/00 9:52p Markd
// Added FindClass function
// 
// 21    6/14/00 4:06p Markd
// fixed two typos
// 
// 20    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 19    5/26/00 7:44p Markd
// 2nd phase save games
// 
// 18    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 17    1/26/00 7:00p Markd
// fixed imbedded labels in entity scripts
// 
// 16    1/10/00 5:28p Markd
// inhibited all lights from spawning
// 
// 15    1/07/00 6:34p Steven
// Don't spawn an actor if the model is not found.
// 
// 14    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 13    12/06/99 6:39p Jimdose
// changed call to cvar_forceset to cvar_set
// 
// 12    10/06/99 7:26p Markd
// simplified makestatic code
// 
// 11    10/06/99 7:25p Markd
// removed TIMESTAMP, time and fixed make_static bug
// 
// 10    10/06/99 7:04p Markd
// Added make_static support
// 
// 9     10/06/99 6:25p Markd
// put in MAKE_STATIC support into spawn code
// 
// 8     10/04/99 10:47a Markd
// Fixed assertions which were actually errors
// 
// 7     10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 6     9/29/99 11:52a Markd
// removed some unused enums and variables form shared headers between cgame
// and fgame
// 
// 5     9/28/99 4:26p Markd
// merged listener, class and vector between 3 projects
// 
// 4     9/16/99 4:48p Jimdose
// removed unused code
// 
// 3     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 2     9/15/99 6:57p Aldie
// Update to get game working
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 20    8/30/99 8:09p Markd
// made bad classname a developer 2 bug
// 
// 19    8/28/99 3:42p Jimdose
// changed some doubles to floats
// 
// 18    8/25/99 12:42p Markd
// Fixed some minor and major scripting bugs
// 
// 17    8/19/99 6:59p Markd
// removed the old tiki_cmd structure, now tiki_cmd_t is passed into the tiki
// functions
// 
// 16    8/17/99 3:20p Markd
// Fixed spawn issues with "script" key-value pair
// 
// 15    8/02/99 11:19a Markd
// plugged potential empty line script bug
// 
// 14    8/02/99 10:52a Markd
// Put in \n delimiters into initialization script
// 
// 13    7/29/99 11:41a Markd
// Added precache and global support
// 
// 12    6/18/99 6:00p Markd
// Added Script Initialization for most objects
//
// DESCRIPTION:
//

#include "g_local.h"
#include "class.h"
#include "Entity.h"
#include "g_spawn.h"
#include "navigate.h"
#include "player.h"
#include "gravpath.h"
#include "object.h"

CLASS_DECLARATION( Class, SpawnArgs, NULL )
	{
      { NULL, NULL }
   };

SpawnArgs::SpawnArgs()
   {
   }

SpawnArgs::SpawnArgs
   (
   SpawnArgs &otherlist
   )

   {
   int num;
   int i;

   num = otherlist.NumArgs();
   keyList.Resize( num );
   valueList.Resize( num );
   for( i = 1; i <= num; i++ )
      {
      keyList.AddObject( otherlist.keyList.ObjectAt( i ) );
      valueList.AddObject( otherlist.valueList.ObjectAt( i ) );
      }
   }

void SpawnArgs::Clear
   (
   void
   )

   {
   keyList.FreeObjectList();
   valueList.FreeObjectList();
   }

/*
====================
Parse

Parses spawnflags out of the given string, returning the new position.
Clears out any previous args.
====================
*/
const char *SpawnArgs::Parse
	(
	const char *data
	)

	{
   str         keyname;
	const char	*com_token;

   Clear();

	// parse the opening brace
	com_token = COM_Parse( &data );
	if ( !data )
		{
		return NULL;
		}

	if ( com_token[ 0 ] != '{' )
		{
		gi.Error( ERR_DROP, "SpawnArgs::Parse : found %s when expecting {", com_token );
		}

	// go through all the dictionary pairs
	while( 1 )
		{
		// parse key
		com_token = COM_Parse( &data );
		if ( com_token[ 0 ] == '}' )
			{
			break;
			}

		if ( !data )
			{
			gi.Error( ERR_DROP, "SpawnArgs::Parse : EOF without closing brace" );
			}

		keyname = com_token;

		// parse value
		com_token = COM_Parse( &data );
		if ( !data )
			{
			gi.Error( ERR_DROP, "SpawnArgs::Parse : EOF without closing brace" );
			}

		if ( com_token[ 0 ] == '}' )
			{
			gi.Error( ERR_DROP, "SpawnArgs::Parse : closing brace without data" );
			}

		// keynames with a leading underscore are used for utility comments,
		// and are immediately discarded by Fakk
		if ( keyname[ 0 ] == '_' )
			{
			continue;
			}

      setArg( keyname.c_str(), com_token );
		}

	return data;
	}

const char *SpawnArgs::getArg
   (
   const char *key,
   const char *defaultValue
   )

   {
   int i;
   int num;

   num = keyList.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      if ( keyList.ObjectAt( i ) == key )
         {
         return valueList.ObjectAt( i );
         }
      }

   return defaultValue;
   }

void SpawnArgs::setArg
   (
   const char *key,
   const char *value
   )

   {
   int i;
   int num;

   num = keyList.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      if ( keyList.ObjectAt( i ) == key )
         {
         valueList.ObjectAt( i ) = value;
         return;
         }
      }

   keyList.AddObject( str( key ) );
   valueList.AddObject( str( value ) );
   }

void SpawnArgs::operator=
	(
	SpawnArgs &otherlist
	)

	{
   int num;
   int i;

   Clear();

   num = otherlist.NumArgs();
   keyList.Resize( num );
   valueList.Resize( num );

   for( i = 1; i <= num; i++ )
      {
      keyList.AddObject( otherlist.keyList.ObjectAt( i ) );
      valueList.AddObject( otherlist.valueList.ObjectAt( i ) );
      }
	}

int SpawnArgs::NumArgs
   (
   void
   )

   {
   return keyList.NumObjects();
   }

const char *SpawnArgs::getKey
   (
   int index
   )

   {
   return keyList.ObjectAt( index + 1 );
   }

const char *SpawnArgs::getValue
   (
   int index
   )

   {
   return valueList.ObjectAt( index + 1 );
   }

void SpawnArgs::Archive
   (
   Archiver &arc
   )

   {
   Class::Archive( arc );

   keyList.Archive( arc );
   valueList.Archive( arc );
   }

/*
===============
getClass

Finds the spawn function for the entity and returns ClassDef *
===============
*/

ClassDef *SpawnArgs::getClassDef
	(
	qboolean *tikiWasStatic
	)

	{
	const char	*classname;
	ClassDef		*cls = NULL;

	classname = getArg( "classname" );

   if ( tikiWasStatic )
      {
      *tikiWasStatic = qfalse;
      }

	//
	// check normal spawn functions
   // see if the class name is stored within the model
   //
   if ( classname )
      {
      // 
      // explicitly inhibit lights
      //
      if ( !strcmpi( classname, "light" ) )
         {
         // 
         // HACK HACK HACK
         // hack to suppress a warning message
         //
         if ( tikiWasStatic )
            {
            *tikiWasStatic = qtrue;
            }
         return NULL;
         }

      cls = getClassForID( classname );
      if ( !cls )
         {
         cls = getClass( classname );
         }
      }

	if ( !cls )
      {
      const char *model;

      //
      // get Object in case we cannot find an alternative
      //
      cls = &Object::ClassInfo;
	   model = getArg( "model" );
	   if ( model )
		   {
         tiki_cmd_t cmds;
         int modelindex;
         int i;

         //
         // get handle to def file
         //
         if ( ( strlen( model ) >= 3 ) && ( !strcmpi( &model[ strlen(model) - 3 ], "tik" ) ) )
            {
            modelindex = modelIndex( model );

				if ( modelindex == -1 )
					return NULL;

            if ( gi.IsModel( modelindex ) )
               {
               const char * s;

               s = getArg( "make_static" );
               if ( s && atoi( s ) )
                  {
                  //
                  // if make_static then we don't want to spawn
                  //
                  if ( tikiWasStatic )
                     {
                     *tikiWasStatic = qtrue;
                     }

                  return NULL;
                  }

               if ( gi.InitCommands( modelindex, &cmds ) )
                  {
                  for( i = 0; i < cmds.num_cmds; i++ )
                     {
                     if ( !strcmpi( cmds.cmds[ i ].args[ 0 ], "classname" ) )
                        {
                        cls = getClass( cmds.cmds[ i ].args[ 1 ] );
                        break;
                        }
                     }
                  if ( i == cmds.num_cmds )
                     {
                     if ( developer->integer == 2 )
                        gi.DPrintf( "Classname %s used, but 'classname' was not found in Initialization commands, using Object.\n", classname );
                     }
                  }
               else
                  gi.DPrintf( "Classname %s used, but TIKI had no Initialization commands, using Object.\n", classname );
               }
            else
               gi.DPrintf( "Classname %s used, but TIKI was not valid, using Object.\n", classname );
            }
         else
            gi.DPrintf( "Classname %s used, but model was not a TIKI, using Object.\n", classname );
		   }
      else
         {
         gi.DPrintf( "Classname %s' used, but no model was set, using Object.\n", classname );
         }
      }

   return cls;
	}

/*
===============
Spawn

Finds the spawn function for the entity and calls it.
Returns pointer to Entity
===============
*/

Entity *SpawnArgs::Spawn
	(
	void
	)

	{
	str      classname;
	ClassDef	*cls;
	Entity	*obj;
   Event    *ev;
   int      i;
   qboolean tikiWasStatic; // used to determine if entity was intentionally suppressed

	classname = getArg( "classname", "Unspecified" );
   cls = getClassDef( &tikiWasStatic );
	if ( !cls )
		{
      if ( !tikiWasStatic )
         {
         gi.DPrintf( "%s doesn't have a spawn function\n", classname.c_str() );
         }

      return NULL;
		}

	obj = ( Entity * )cls->newInstance();

   // post spawnarg events
	for( i = 0; i < NumArgs(); i++ )
		{
      // if it is the "script" key, execute the script commands individually
      if ( !Q_stricmp( getKey( i ), "script" ) )
         {
         char *ptr;
         char * token;

         ptr = const_cast< char * >( getValue( i ) );
         while ( 1 )
            {
            token = COM_ParseExt( &ptr, qtrue );
            if ( !token[ 0 ] )
               break;
            if ( strchr( token, ':' ) )
               {
               gi.DPrintf( "Label %s imbedded inside editor script for %s.\n", token, classname.c_str() );
               }
            else
               {
               ev = new Event( token );
               while ( 1 )
                  {
                  token = COM_ParseExt( &ptr, qfalse );
                  if ( !token[ 0 ] )
                     break;
                  ev->AddToken( token );
                  }
               obj->PostEvent( ev, EV_SPAWNARG );
               }
            }
         }
      else
         {
         ev = new Event( getKey( i ) );
         ev->AddToken( getValue( i ) );
         obj->PostEvent( ev, EV_SPAWNARG );
         }
		}

	if ( !obj )
		{
      gi.DPrintf( "%s failed on newInstance\n", classname.c_str() );
   	return NULL;
		}

   return obj;
	}

/*
==============
G_InitClientPersistant

This is only called when the game first initializes in single player,
but is called after each death and level change in deathmatch
==============
*/
void G_InitClientPersistant
	(
	gclient_t *client
	)

	{
	memset( &client->pers, 0, sizeof( client->pers ) );
	}


ClassDef *FindClass
	(
	const char *name,
   qboolean *isModel
	)

	{
	ClassDef *cls;

   *isModel = qfalse;

   // first lets see if it is a registered class name
	cls = getClass( name );
	if ( !cls )
		{
      SpawnArgs args;

      // if that didn't work lets try to resolve it as a model
      args.setArg( "model", name );

      cls = args.getClassDef();
      if ( cls )
         {
         *isModel = qtrue;
         }
      }
   return cls;
   }

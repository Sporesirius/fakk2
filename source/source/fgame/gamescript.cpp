//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/gamescript.cpp                     $
// $Revision:: 6                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 7/07/00 4:27p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/gamescript.cpp                          $
// 
// 6     7/07/00 4:27p Markd
// made it so single : do not count as labels
// 
// 5     4/24/00 12:09p Markd
// Fixed script loading issues for when no path is specified
// 
// 4     4/05/00 3:51p Markd
// added label checking for scripts
// 
// 3     2/22/00 2:23p Jimdose
// GetScript now checks if the name passed in is empty before calling
// FS_ReadFile.  Fixes getting kicked out of game when there is no script and a
// trigger tries to start a thread
// 
// 2     10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 6     8/17/99 5:08p Markd
// Changed all FS_ReadFile's to FS_ReadFileEx's in game code
// 
// DESCRIPTION:
// Subclass of script that preprocesses labels
//

#include "g_local.h"
#include "script.h"
#include "gamescript.h"

ScriptLibrarian ScriptLib;

CLASS_DECLARATION( Class, GameScriptMarker, NULL )
	{
		{ NULL, NULL }
	};

CLASS_DECLARATION( Class, ScriptLibrarian, NULL )
	{
		{ NULL, NULL }
	};

ScriptLibrarian::~ScriptLibrarian()
	{
	int i;
	int num;

   num = scripts.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      delete scripts.ObjectAt( i );
      }
	}

void ScriptLibrarian::CloseScripts
	(
	void
	)

	{
	int i;
	int num;
	GameScript *scr;

   // Clear out the game and dialog scripts
   SetGameScript( "" );
   SetDialogScript( "" );

   num = scripts.NumObjects();
   for( i = num; i > 0; i-- )
      {
		scr = scripts.ObjectAt( i );
		scripts.RemoveObjectAt( i );
      delete scr;
      }
	}

void ScriptLibrarian::SetDialogScript
	(
   str scriptname
	)
   {
   dialog_script = scriptname;
   }

void ScriptLibrarian::SetGameScript
	(
   str scriptname
	)
   {
   game_script = scriptname;
   }

const char *ScriptLibrarian::GetGameScript
	(
   void
	)
   {
   return game_script.c_str();
   }

GameScript *ScriptLibrarian::FindScript
	(
	const char *name
	)

	{
	int i;
	int num;
	GameScript *scr;
	str n;

	// Convert all forward slashes to back slashes
   n = G_FixSlashes( name );

   num = scripts.NumObjects();
   for( i = 1; i <= num; i++ )
      {
		scr = scripts.ObjectAt( i );

		if ( scr->Filename() == n )
			{
			return scr;
			}
      }

   return NULL;
	}

GameScript *ScriptLibrarian::GetScript
	(
	const char *name
	)

	{
	GameScript *scr;
   str n;

   n = G_FixSlashes( name );
   if ( !n.length() )
      {
      return NULL;
      }

	
   // see if we have an absolute path specified, 
   // if we don't use the same path as the map file
   if ( !strchr( n.c_str(), '/' ) )
      {
      int i;
      str mapname;

      mapname = "maps/";
	   mapname += level.mapname;
	   for( i = mapname.length() - 1; i >= 0; i-- )
		   {
		   if ( mapname[ i ] == '/' )
			   {
            // skip back over the '/'
            i++;
			   mapname[ i ] = 0;
			   break;
			   }
		   }
	   mapname += n;
      // copy it back into the write string
      n = mapname;
      }

   scr = FindScript( n.c_str() );
   if ( !scr && ( gi.FS_ReadFile( n.c_str(), NULL, qfalse ) != -1 ) )
		{
		scr = new GameScript();
		scr->LoadFile( n.c_str() );
		scripts.AddObject( scr );
		}
	
	return scr;
	}

qboolean	ScriptLibrarian::Goto
	(
	GameScript *scr,
	const char *name
	)

	{
	const char *p;
	GameScript *s;
	str n;

	p = strstr( name, "::" );
	if ( !p )
		{
		return scr->Goto( name );
		}
	else
		{
		n = str( name, 0, p - name );
      if ( n == str( "dialog" ) )
         {
         n = dialog_script;
         }
		s = GetScript( n.c_str() );
		if ( !s )
			{
			return false;
			}

		p += 2;
		if ( s->labelExists( p ) )
			{
			scr->SetSourceScript( s );
			return scr->Goto( p );
			}
		}

	return false;
	}

qboolean	ScriptLibrarian::labelExists
	(
	GameScript *scr,
	const char *name
	)

	{
	const char *p;
	GameScript *s;
	str n;

   // if we got passed a NULL than that means just run the script so of course it exists
   if ( !name )
      {
      return qtrue;
      }

	p = strstr( name, "::" );
	if ( !p )
		{
		return scr->labelExists( name );
		}
	else
		{
		n = str( name, 0, p - name );
      if ( n == str( "dialog" ) )
         {
         n = dialog_script;
         }
		s = GetScript( n.c_str() );
		if ( !s )
			{
			return false;
			}

		p += 2;
		return s->labelExists( p );
		}
	}

CLASS_DECLARATION( Script, GameScript, NULL )
	{
		{ NULL, NULL }
	};

GameScript::GameScript()
	{
	sourcescript = this;
	labelList = NULL;
   crc = 0;
	}

GameScript::GameScript
	(
	GameScript *scr
	)

	{
   crc = 0;
	labelList = NULL;
	SetSourceScript( scr );
	}

GameScript::~GameScript()
	{
	Close();
	}

void GameScript::Close
	(
	void
	)

	{
	FreeLabels();
	Script::Close();
	sourcescript = this;
   crc = 0;
	}

void GameScript::SetSourceScript
	(
	GameScript *scr 
	)

	{
	if ( scr != this )
		{
		Close();

		sourcescript = scr->sourcescript;
      crc = sourcescript->crc;
		Parse( scr->buffer, scr->length, scr->Filename() );
		}
	}

void GameScript::FreeLabels
	(
	void
	)

	{
   int i;
	int num;

	if ( labelList )
		{
		num = labelList->NumObjects();
		for( i = 1; i <= num; i++ )
			{
			delete labelList->ObjectAt( i );
			}

		delete labelList;
		}

	labelList = NULL;
	}

void GameScript::LoadFile
	( 
	const char *name
	)

	{
	str n;

   // Convert all forward slashes to back slashes
   n = G_FixSlashes( name );

   sourcescript = this;
	Script::LoadFile( n.c_str() );
	FindLabels();

   crc = gi.CalcCRC( (const unsigned char *)buffer, length );
	}

void GameScript::FindLabels
	(
   void
   )

   {
   scriptmarker_t mark;
   const char		*tok;
   script_label_t *label;
	int				len;

	FreeLabels();

	labelList = new Container<script_label_t *>;

	MarkPosition( &mark );
   
   Reset();

	while( TokenAvailable( true ) )
		{
      tok = GetToken( true );
      // see if it is a label
      if ( tok )
			{
			len = strlen( tok );
			if ( ( len > 1 ) && tok[ len - 1 ] == ':' )
				{
				if ( !labelExists( tok ) )
					{
					label = new script_label_t;
         		MarkPosition( &label->pos );
					label->labelname = tok;
					labelList->AddObject( label );
					}
				else
					{
					warning( "FindLabels", "Duplicate labels %s\n", tok );
					}
				}
         }
		}

   RestorePosition( &mark );
   }

qboolean GameScript::labelExists
	(
	const char *name
	)

	{
   str				labelname;
   script_label_t *label;
   int				i;
	int				num;

   // if we got passed a NULL than that means just run the script so of course it exists
   if ( !name )
      {
      return qtrue;
      }

	if ( !sourcescript->labelList )
		{
		return false;
		}

   labelname = name;
	if ( !labelname.length() )
		{
		return false;
		}

   if ( labelname[ labelname.length() - 1 ] != ':' )
		{
      labelname += ":";
		}

   num = sourcescript->labelList->NumObjects();
   for( i = 1; i <= num; i++ )
      {
      label = sourcescript->labelList->ObjectAt( i );
      if ( labelname == label->labelname )
			{
         return true;
			}
      }

   return false;
	}

qboolean GameScript::Goto
	(
	const char *name
	)

	{
   str				labelname;
   script_label_t *label;
   int				i;
	int				num;

	if ( !sourcescript->labelList )
		{
		return false;
		}

   labelname = name;
	if ( !labelname.length() )
		{
		return false;
		}

   if ( labelname[ labelname.length() - 1 ] != ':' )
		{
      labelname += ":";
		}

   num = sourcescript->labelList->NumObjects();
   for( i = 1; i <= num; i++ )
      {
      label = sourcescript->labelList->ObjectAt( i );
      if ( labelname == label->labelname )
         {
         RestorePosition( &label->pos );
         return true;
         }
      }

	return false;
	}

void GameScript::Mark
	( 
	GameScriptMarker *mark 
	)

	{
	assert( mark );
   assert( sourcescript );

	mark->filename = sourcescript->Filename();
	MarkPosition( &mark->scriptmarker );
	}

void GameScript::Restore
	(
	GameScriptMarker *mark
	)

	{
   // If we change this function, we must update the unarchive function as well
   GameScript *scr;

	assert( mark );

   scr = ScriptLib.FindScript( mark->filename.c_str() );
   if ( scr )
      {
      SetSourceScript( scr );
      }
   else
      {
      LoadFile( mark->filename.c_str() );
      }

	RestorePosition( &mark->scriptmarker );
	}

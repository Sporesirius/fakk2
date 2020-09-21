//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/gamescript.h                       $
// $Revision:: 3                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 5/26/00 7:44p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/gamescript.h                            $
// 
// 3     5/26/00 7:44p Markd
// 2nd phase save games
// 
// 2     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// Subclass of script that preprocesses labels
//

#ifndef __GAMESCRIPT_H__
#define __GAMESCRIPT_H__

#include "class.h"
#include "script.h"

typedef struct
	{
	scriptmarker_t pos;
	str labelname;
	} script_label_t;

class GameScript;

class GameScriptMarker : public Class
	{
	public:
		CLASS_PROTOTYPE( GameScriptMarker );

      str               filename;
		scriptmarker_t		scriptmarker;
      virtual void      Archive( Archiver &arc );
	};

inline void GameScriptMarker::Archive
	(
	Archiver &arc
	)

   {
   // Game scripts are unique in that we don't call our superclass to archive it's data.
   // Instead, we only read enough info to then initialize the script ourselves.
   arc.ArchiveString( &filename );
   arc.ArchiveBoolean( &scriptmarker.tokenready );
   arc.ArchiveInteger( &scriptmarker.offset );
   arc.ArchiveInteger( &scriptmarker.line );
   arc.ArchiveRaw( scriptmarker.token, sizeof( scriptmarker.token ) );
   }

class GameScript : public Script
	{
	protected:
		Container<script_label_t *>	*labelList;
		GameScript							*sourcescript;
      unsigned                      crc;

	public:
      CLASS_PROTOTYPE( GameScript );

								GameScript();
								GameScript( GameScript *scr );
								~GameScript();
		void					Close( void );
		void					SetSourceScript( GameScript *scr );
		void					LoadFile( const char *filename );

		void					Mark( GameScriptMarker *mark );
		void					Restore( GameScriptMarker *mark );

		void					FreeLabels( void );
		void					FindLabels( void );
		qboolean				labelExists( const char *name );
		qboolean				Goto( const char *name );
      virtual void      Archive( Archiver &arc );
	};

class ScriptLibrarian : public Class
	{
	protected:
		Container<GameScript *>	scripts;
      str                     dialog_script;
      str                     game_script;

	public:
      CLASS_PROTOTYPE( ScriptLibrarian );

		~ScriptLibrarian();

		void			CloseScripts( void );
		void			SetDialogScript( str scriptname );
		void			SetGameScript( str scriptname );
		const char  *GetGameScript( void );
      GameScript  *FindScript( const char *name );
		GameScript	*GetScript( const char *name );
		qboolean		Goto( GameScript *scr, const char *name );
		qboolean		labelExists( GameScript *scr, const char *name );
      virtual void Archive( Archiver &arc );
	};

inline void ScriptLibrarian::Archive
	(
	Archiver &arc
	)
   {
   GameScript * scr;
   int i, num;

   Class::Archive( arc );

   if ( arc.Loading() )
      {
      scripts.FreeObjectList();
      }
   else
      {
      num = scripts.NumObjects();
      }
   arc.ArchiveInteger( &num );

   for ( i = 1; i <= num; i++ )
      {
      if ( arc.Saving() )
         {
         scr = scripts.ObjectAt( i );
         }
      else
         {
         scr = new GameScript;
         }
      arc.ArchiveObject( scr );
      if ( arc.Loading() )
         {
         scripts.AddObject( scr );
         }
      }
   arc.ArchiveString( &dialog_script );
   arc.ArchiveString( &game_script );
   }

extern ScriptLibrarian ScriptLib;

inline void GameScript::Archive
	(
	Archiver &arc
	)

   {
   // Game scripts are unique in that we don't call our superclass to archive it's data.
   // Instead, we only read enough info to then initialize the script ourselves.
   GameScriptMarker mark;

   if ( arc.Saving() )
      {
      arc.ArchiveUnsigned( &crc );
      Mark( &mark );
      arc.ArchiveObject( &mark );
      }
   else
      {
      unsigned   filecrc;
      GameScript *scr;

      arc.ArchiveUnsigned( &filecrc );
      arc.ArchiveObject( &mark );
      scr = ScriptLib.FindScript( mark.filename.c_str() );
      if ( scr )
         {
         SetSourceScript( scr );
         }
      else
         {
         LoadFile( mark.filename.c_str() );
         }

      // Error out if CRCs have changed
      if ( filecrc != crc )
         {
         gi.Error( ERR_DROP, "File '%s' has changed from when this savegame was written.  Load cancelled.\n", filename.c_str() );
         }

	   RestorePosition( &mark.scriptmarker );
      }
   }

#endif

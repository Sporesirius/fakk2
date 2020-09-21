//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/script.h                           $
// $Revision:: 3                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 5/27/00 2:56p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/script.h                                $
// 
// 3     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 2     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// C++ implementaion of tokenizing text interpretation.  Class accepts filename
// to load or pointer to preloaded text data.  Standard tokenizing operations
// such as skip white-space, get string, get integer, get float, get token,
// and skip line are implemented.  
//
// Note: all '//', '#', and ';' are treated as comments.  Probably should
// make this behaviour toggleable.
// 

#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "class.h"
#include "vector.h"
#include "str.h"

#define	MAXTOKEN	256

typedef struct
	{
	qboolean		tokenready;
   int         offset;
	int			line;		
	char			token[ MAXTOKEN ];
	} scriptmarker_t;

class Script : public Class
	{
	protected:
		qboolean		tokenready;
		
		str			filename;
		const char	*script_p;
		const char	*end_p;
		
		int			line;		
		char			token[ MAXTOKEN ];

		qboolean		releaseBuffer;

		qboolean		AtComment( void );
		void			CheckOverflow( void );

	public:
		const char	*buffer;
		int			length;

      CLASS_PROTOTYPE( Script );

		~Script();
		Script();
		void			Close( void );
		const char *Filename( void );
		int			GetLineNumber( void );
		void			Reset( void );	
		void			MarkPosition( scriptmarker_t *mark );
		void			RestorePosition( scriptmarker_t *mark );
		qboolean		SkipToEOL( void );
		void			SkipWhiteSpace( qboolean crossline );
		void			SkipNonToken( qboolean crossline );
		qboolean		TokenAvailable( qboolean crossline );
		qboolean		CommentAvailable( qboolean crossline );
		void			UnGetToken( void );
		qboolean		AtString( qboolean crossline );
		const char	*GetToken( qboolean crossline );
		const char	*GetLine( qboolean crossline );
		const char	*GetRaw( void );
		const char	*GetString( qboolean crossline );
		qboolean		GetSpecific( const char *string );
		int			GetInteger( qboolean crossline );
		double		GetDouble( qboolean crossline );
		float			GetFloat( qboolean crossline );
		Vector		GetVector( qboolean crossline );
		int			LinesInFile( void );
		void			Parse( const char *data, int length, const char *name );
		void			LoadFile( const char *name );
		const char	*Token( void );
      virtual void Archive( Archiver &arc );
	};

inline void Script::Archive
	(
	Archiver &arc
	)
   {
   int pos;

   Class::Archive( arc );

   arc.ArchiveString( &filename );
   if ( arc.Loading() )
      {
      //
      // load the file in
      //
      LoadFile( filename.c_str() );
      }
   arc.ArchiveBoolean( &tokenready );

   if ( arc.Saving() )
      {
      //
      // save out current pointer as an offset
      //
      pos = script_p - buffer;
      }
   arc.ArchiveInteger( &pos );
   if ( arc.Loading() )
      {
      //
      // restore the script pointer
      //
      script_p = buffer + pos;
      }
   arc.ArchiveInteger( &line );
   arc.ArchiveRaw( token, sizeof( token ) );
   }

#endif

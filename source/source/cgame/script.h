//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/client/script.h                          $
// $Revision:: 2                                                              $
//     $Date:: 9/28/99 4:26p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/client/script.h                               $
// 
// 2     9/28/99 4:26p Markd
// merged listener, class and vector between 3 projects
// 
// 1     9/10/99 10:51a Jimdose
// 
// 1     9/09/99 7:51p Jimdose
// 
// 2     7/01/99 6:56p Aldie
// Update UI
// 
// 1     6/29/99 4:02p Aldie
// 
// 1     6/23/99 2:50p Jimdose
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
	bool		   tokenready;
   int         offset;
	int			line;		
	char			token[ MAXTOKEN ];
	} scriptmarker_t;

class Script : public Class
	{
	protected:
		bool		   m_tokenready;
		
		str			m_filename;
		const char	*m_script_p;
		const char	*m_end_p;
		
		int			m_line;		
		char			m_token[ MAXTOKEN ];

		bool		   m_releaseBuffer;

		bool		   AtComment( void );
		void			CheckOverflow( void );

	public:
	   char	      *buffer;
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
		bool		   SkipToEOL( void );
		void			SkipWhiteSpace( bool crossline );
		void			SkipNonToken( bool crossline );
		bool		   TokenAvailable( bool crossline );
		bool		   CommentAvailable( bool crossline );
		void			UnGetToken( void );
		bool		   AtString( bool crossline );
		const char	*GetToken( bool crossline );
		const char	*GetLine( bool crossline );
		const char	*GetRaw( void );
		const char	*GetString( bool crossline );
      const char  *GetExpression( bool crossline );
		bool		   GetSpecific( const char *string );
		int			GetInteger( bool crossline );
		double		GetDouble( bool crossline );
		float			GetFloat( bool crossline );
		Vector		GetVector( bool crossline );
		int			LinesInFile( void );
		void			Parse( char *data, int length, const char *name );
		void			LoadFile( const char *name );
		const char	*Token( void );
#if 0
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
#endif
	};

#if 0
inline void Script::Archive
	(
	Archiver &arc
	)
   {
   Class::Archive( arc );

   arc.WriteString( m_filename );
   arc.WriteBoolean( m_tokenready );
   //
   // save out current pointer as an offset
   //
   arc.WriteInteger( m_script_p - buffer );
   arc.WriteInteger( m_line );
   arc.WriteRaw( m_token, sizeof( m_token ) );
   }

inline void Script::Unarchive
	(
	Archiver &arc
	)
   {
   int i;

   Class::Unarchive( arc );

   arc.ReadString( &m_filename );
   //
   // load the file in
   //
   LoadFile( m_filename.c_str() );

   arc.ReadBoolean( &m_tokenready );
   arc.ReadInteger( &i );
   //
   // restore the script pointer
   //
   m_script_p = buffer + i;
   arc.ReadInteger( &m_line );
   arc.ReadRaw( m_token, sizeof( m_token ) );
   }
#endif

#endif

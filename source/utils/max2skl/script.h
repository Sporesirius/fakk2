//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/script.h                         $
// $Revision:: 2                                                              $
//     $Date:: 9/24/99 4:40p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/script.h                              $
// 
// 2     9/24/99 4:40p Jimdose
// added Skip, GetVector, and Error
// 
// 1     9/21/99 2:20p Jimdose
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

#include "ucommon.h"
#include "uvector3.h"
#include "str.h"

#define	MAXTOKEN	256

typedef struct
	{
	bool		   tokenready;
   int         offset;
	int			line;		
	char			token[ MAXTOKEN ];
	} scriptmarker_t;

class Script
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
		const char	*buffer;
		int			length;

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
      void        Skip( const char *string, bool crossline = true );
		bool		   GetSpecific( const char *string );
		int			GetInteger( bool crossline );
		double		GetDouble( bool crossline );
		float			GetFloat( bool crossline );
		UVector3		GetVector( bool crossline );
      void        GetVector( float vector[ 3 ], bool crossline );
		int			LinesInFile( void );
		void			Parse( const char *data, int length, const char *name );
		void			LoadFile( const char *name );
		const char	*Token( void );
      void        Error( const char *error, ... );
	};

#endif

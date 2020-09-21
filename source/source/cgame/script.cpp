//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/script.cpp                         $
// $Revision:: 4                                                              $
//     $Date:: 7/13/00 10:17a                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/script.cpp                              $
// 
// 4     7/13/00 10:17a Markd
// fixed a memory leak
// 
// 3     3/14/00 3:35p Aldie
// Fix syntax error
// 
// 2     3/14/00 3:22p Aldie
// Changed some client side emitter functionality and added func_emitter
// 
// 1     9/10/99 10:51a Jimdose
// 
// 1     9/09/99 7:51p Jimdose
// 
// 3     7/29/99 3:31p Aldie
// Updated to new class system
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
// such as skip white-space, get string, get integer, get float, get m_token,
// and skip line are implemented.  
//
// Note: all '//', '#', and ';' are treated as comments.  Probably should
// make this behaviour toggleable.
// 

#include "script.h"
#include "../qcommon/qcommon.h"
#include <stdlib.h>

#if defined ( CGAME_DLL )
//
// cgame dll specific defines
//
#include "cg_local.h"

#define FILE_FS_FreeFile cgi.FS_FreeFile
#define FILE_FS_ReadFile(a,b) cgi.FS_ReadFile(a,b,false)
#define FILE_Malloc cgi.Malloc
#define FILE_Free cgi.Free

#else

#define FILE_FS_FreeFile FS_FreeFile
#define FILE_FS_ReadFile FS_ReadFile
#define FILE_Malloc Z_Malloc
#define FILE_Free Z_Free

#endif

#define TOKENCOMMENT      (';')
//#define TOKENCOMMENT2     ('#')
#define TOKENEOL          ('\n')
#define TOKENNULL         ('\0')
#define TOKENSPACE        (' ')

CLASS_DECLARATION( Class, Script, NULL )
	{
		{ NULL, NULL }
	};

Script::~Script()
	{
	Close();
	}

Script::Script()
	{
	buffer			= NULL;
	m_script_p		= NULL;
	m_end_p			= NULL;
	m_line			= 0;
	m_releaseBuffer = false;
	m_tokenready	= false;
	memset( m_token, 0, sizeof( m_token ) );
	}

void Script::Close
	(
	void
	)

	{
	if ( m_releaseBuffer && buffer )
		{
		FILE_Free( buffer );
		}

	buffer			= NULL;
	m_script_p		= NULL;
	m_end_p			= NULL;
	m_line			= 0;
	m_releaseBuffer = false;
	m_tokenready	= false;
	memset( m_token, 0, sizeof( m_token ) );
	}

/*
==============
=
= Filename
=
==============
*/

const char *Script::Filename
	(
	void
	)
	
	{
	return m_filename.c_str();
	}

/*
==============
=
= GetLineNumber
=
==============
*/

int Script::GetLineNumber
	(
	void
	)
	
	{
	return m_line;
	}

/*
==============
=
= Reset
=
==============
*/

void Script::Reset 
	( 
	void
	)
	
	{
	m_script_p = buffer;
	m_line = 1;
	m_tokenready = false;
	}

/*
==============
=
= MarkPosition
=
==============
*/

void Script::MarkPosition
	( 
	scriptmarker_t *mark 
	)

	{
	assert( mark );

	mark->tokenready = m_tokenready;
	mark->offset     = m_script_p - buffer;
	mark->line		  = m_line;
	strcpy( mark->token, m_token );
	}

/*
==============
=
= RestorePosition
=
==============
*/

void Script::RestorePosition
	(
	scriptmarker_t *mark
	)

	{
	assert( mark );

	m_tokenready = mark->tokenready;
	m_script_p   = buffer + mark->offset;
	m_line		 = mark->line;
	strcpy( m_token, mark->token );

   assert( m_script_p <= m_end_p );
   if ( m_script_p > m_end_p )
      {
      m_script_p = m_end_p;
      }
	}

/*
==============
=
= SkipToEOL
=
==============
*/

bool Script::SkipToEOL
	( 
	void
	)

	{
	if ( m_script_p >= m_end_p )
		{
		return true;
		}

	while( *m_script_p != TOKENEOL )
		{
		if ( m_script_p >= m_end_p )
			{
			return true;
			}
		m_script_p++;
		}
	return false;
	}

/*
==============
=
= CheckOverflow
=
==============
*/

void Script::CheckOverflow
	(
	void
	)
	
	{
	if ( m_script_p >= m_end_p )
		{
		Com_Error( ERR_DROP, "End of token file reached prematurely reading %s\n", m_filename.c_str() );
		}
	}

/*
==============
=
= SkipWhiteSpace
=
==============
*/

void Script::SkipWhiteSpace
	(
	bool crossline
	)

	{
	//
	// skip space
	//
	CheckOverflow();

	while( ( *m_script_p <= TOKENSPACE ) || ( *m_script_p == ',' ) )
		{
		if ( *m_script_p++ == TOKENEOL )
			{
			if ( !crossline )
				{
				Com_Error( ERR_DROP, "Line %i is incomplete in file %s\n", m_line, m_filename.c_str() );
				}

			m_line++;
			}
		CheckOverflow();
		}
	}

bool Script::AtComment
	(
	void
	)

	{
	if ( m_script_p >= m_end_p )
		{
		return false;
		}

	if ( *m_script_p == TOKENCOMMENT )
		{
		return true;
		}
	
//	if ( *m_script_p == TOKENCOMMENT2 )
		//{
		//return true;
		//}

	// Two or more character comment specifiers
	if ( ( m_script_p + 1 ) >= m_end_p )
		{
		return false;
		}
	
	if ( ( *m_script_p == '/' ) && ( *( m_script_p + 1 ) == '/' ) )
		{
		return true;
		}

	return false;
	}

/*
==============
=
= SkipNonToken
=
==============
*/

void Script::SkipNonToken
	(
	bool crossline
	)

	{
	//
	// skip space and comments
	//
	SkipWhiteSpace( crossline );
	while( AtComment() )
		{
		SkipToEOL();
		SkipWhiteSpace( crossline );
		}
	}

/*
=============================================================================
=
= Token section
=
=============================================================================
*/

/*
==============
=
= TokenAvailable
=
==============
*/

bool Script::TokenAvailable 
	(
	bool crossline
	)

	{
	if ( m_script_p >= m_end_p )
		{
		return false;
		}

	while ( 1 )
		{
		while ( *m_script_p <= TOKENSPACE )
			{
			if ( *m_script_p == TOKENEOL )
				{
				if ( crossline==false )
					{
					return( false );
					}
				m_line++;
				}

			m_script_p++;
			if ( m_script_p >= m_end_p )
				{
				return false;
				}
			}
	
		if ( AtComment() )
			{
			bool done;

			done = SkipToEOL();
			if ( done )
				{
				return false;
				}
			}
		else
			{
			break;
			}
		}

	return true;
	}

/*
==============
=
= CommentAvailable
=
==============
*/

bool Script::CommentAvailable
	(
	bool crossline
	)

	{
	const char *searchptr;

	searchptr = m_script_p;

	if ( searchptr >= m_end_p )
		{
		return false;
		}

	while ( *searchptr <= TOKENSPACE )
		{
		if ( ( *searchptr == TOKENEOL ) && ( !crossline ) )
			{
			return false;
			}
		searchptr++;
		if ( searchptr >= m_end_p )
			{
			return false;
			}
		}

	return true;
	}


/*
==============
=
= UnGet
=
= Signals that the current token was not used, and should be reported
= for the next GetToken.  Note that

GetToken (true);
UnGetToken ();
GetToken (false);

= could cross a line boundary.
=
==============
*/

void Script::UnGetToken
	(
	void
	)
	
	{
	m_tokenready = true;
	}

/*
==============
=
= Get
=
==============
*/
bool Script::AtString
	(
	bool crossline
	)
	
	{
	//
	// skip space
	//
	SkipNonToken( crossline );

	return ( *m_script_p == '"' );
	}

/*
==============
=
= Get
=
==============
*/

const char *Script::GetToken
	(
	bool crossline
	)
	
	{
	char *token_p;

	// is a token already waiting?
	if ( m_tokenready )
		{
		m_tokenready = false;
		return m_token;
		}

	//
	// skip space
	//
	SkipNonToken( crossline );

	//
	// copy token
	//

	if ( *m_script_p == '"' )
		{
		return GetString( crossline );
		}

	token_p = m_token;	
	while( *m_script_p > TOKENSPACE && *m_script_p != ',' && !AtComment() )
		{
		if ( ( *m_script_p == '\\' ) && ( m_script_p < m_end_p - 1 ) )
			{
			m_script_p++;
			switch( *m_script_p )
				{
				case 'n' :	*token_p++ = '\n'; break;
				case 'r' :	*token_p++ = '\n'; break;
				case '\'' : *token_p++ = '\''; break;
				case '\"' : *token_p++ = '\"'; break;
				case '\\' : *token_p++ = '\\'; break;
				default:		*token_p++ = *m_script_p; break;
				}
			m_script_p++;
			}
		else
			{
			*token_p++ = *m_script_p++;
			}

		if ( token_p == &m_token[ MAXTOKEN ] )
			{
			Com_Error( ERR_DROP, "Token too large on line %i in file %s\n", m_line, m_filename.c_str() );
			}

		if ( m_script_p == m_end_p )
			{
			break;
			}
		}

	*token_p = 0;

	return m_token;
	}

/*
==============
=
= GetLine
=
==============
*/

const char *Script::GetLine
	(
	bool crossline
	)

	{
	const char	*start;
	int			size;

	// is a token already waiting?
	if ( m_tokenready )
		{
		m_tokenready = false;
		return m_token;
		}

	//
	// skip space
	//
	SkipNonToken( crossline );

	//
	// copy token
	//
   start = m_script_p;
   SkipToEOL();
   size = m_script_p - start;
   if ( size < MAXTOKEN - 1 )
		{
		memcpy( m_token, start, size );
		m_token[ size ] = '\0';
		}
	else
		{
		Com_Error( ERR_DROP, "Token too large on line %i in file %s\n", m_line, m_filename.c_str() );
		}
	
	return m_token;
	}

/*
==============
=
= GetRaw
=
==============
*/

const char *Script::GetRaw
	(
	void
	)

	{
	const char	*start;
	int			size;

	//
	// skip white space
	//
	SkipWhiteSpace( true );

	//
	// copy token
	//
	start = m_script_p;
	SkipToEOL();
	size = m_script_p - start;
	if ( size < MAXTOKEN - 1 )
		{
		memset( m_token, 0, sizeof( m_token ) );
		memcpy( m_token, start, size );
		}
	else
		{
		Com_Error( ERR_DROP, "Token too large on line %i in file %s\n", m_line, m_filename.c_str() );
		}

	return m_token;
	}

/*
==============
=
= GetString
=
==============
*/

const char *Script::GetString
	(
	bool crossline
	)

	{
	int startline;
	char *token_p;

	// is a token already waiting?
	if ( m_tokenready )
		{
		m_tokenready = false;
		return m_token;
		}

	//
	// skip space
	//
	SkipNonToken( crossline );

	if ( *m_script_p != '"' )
		{
		Com_Error( ERR_DROP, "Expecting string on line %i in file %s\n", m_line, m_filename.c_str() );
		}

	m_script_p++;

	startline = m_line;
	token_p = m_token;
	while( *m_script_p != '"' )
		{
		if ( *m_script_p == TOKENEOL )
			{
			Com_Error( ERR_DROP, "Line %i is incomplete while reading string in file %s\n", m_line, m_filename.c_str() );
			}

		if ( ( *m_script_p == '\\' ) && ( m_script_p < m_end_p - 1 ) )
			{
			m_script_p++;
			switch( *m_script_p )
				{
				case 'n' :	*token_p++ = '\n'; break;
				case 'r' :	*token_p++ = '\n'; break;
				case '\'' : *token_p++ = '\''; break;
				case '\"' : *token_p++ = '\"'; break;
				case '\\' : *token_p++ = '\\'; break;
				default:		*token_p++ = *m_script_p; break;
				}
			m_script_p++;
			}
		else
			{
			*token_p++ = *m_script_p++;
			}

		if ( m_script_p >= m_end_p )
			{
			Com_Error( ERR_DROP, "End of token file reached prematurely while reading string on\n"
				"line %d in file %s\n", startline, m_filename.c_str() );
			}

		if ( token_p == &m_token[ MAXTOKEN ] )
			{
			Com_Error( ERR_DROP, "String too large on line %i in file %s\n", m_line, m_filename.c_str() );
			}
		}

	*token_p = 0;

	// skip last quote
	m_script_p++;
	
	return m_token;
	}

const char *Script::GetExpression
   (
   bool crossline
   )

   {
	char *token_p;

	// is a token already waiting?
	if ( m_tokenready )
		{
		m_tokenready = false;
		return m_token;
		}

	//
	// skip space
	//
	SkipNonToken( crossline );

	//
	// copy token
	//

	if ( *m_script_p == '"' )
		{
		return GetString( crossline );
		}

	token_p = m_token;	
	while( *m_script_p != ',' && !AtComment() )
		{
		if ( ( *m_script_p == '\\' ) && ( m_script_p < m_end_p - 1 ) )
			{
			m_script_p++;
			switch( *m_script_p )
				{
				case 'n' :	*token_p++ = '\n'; break;
				case 'r' :	*token_p++ = '\n'; break;
				case '\'' : *token_p++ = '\''; break;
				case '\"' : *token_p++ = '\"'; break;
				case '\\' : *token_p++ = '\\'; break;
				default:		*token_p++ = *m_script_p; break;
				}
			m_script_p++;
			}
		else
			{
			*token_p++ = *m_script_p++;
			}

		if ( token_p == &m_token[ MAXTOKEN ] )
			{
         Com_Error( ERR_DROP, "Token too large on line %i in file %s\n", m_line, m_filename.c_str() );
			}

		if ( m_script_p == m_end_p )
			{
			break;
			}
		}

	*token_p = 0;

	return m_token;
   }

/*
==============
=
= GetSpecific
=
==============
*/

bool Script::GetSpecific
	(
	const char *string
	)

	{
	do
		{
		if ( !TokenAvailable( true ) )
			{
			return false;
			}
		GetToken( true );
		}
	while( strcmp( m_token, string ) );

	return true;
	}

/*
==============
=
= GetInteger
=
==============
*/

int Script::GetInteger
	(
	bool crossline
	)

	{
	GetToken( crossline );
	return atoi( m_token );
	}

/*
==============
=
= GetDouble
=
==============
*/

double Script::GetDouble
	(
	bool crossline
	)

	{
	GetToken( crossline );
	return atof( m_token );
	}

/*
==============
=
= GetFloat
=
==============
*/

float Script::GetFloat
	(
	bool crossline
	)

	{
	return ( float )GetDouble( crossline );
	}

/*
==============
=
= GetVector
=
==============
*/

Vector Script::GetVector
	(
	bool crossline
	)

	{
	return Vector( GetFloat( crossline ), GetFloat( crossline ), GetFloat( crossline ) );
	}

/*
===================
=
= LinesInFile
=
===================
*/
int Script::LinesInFile
	( 
	void
	)
	
	{
	bool		   temp_tokenready;
	const char	*temp_script_p;
	int			temp_line;		
	char			temp_token[ MAXTOKEN ];
	int			numentries;

	temp_tokenready = m_tokenready;
	temp_script_p	= m_script_p;
	temp_line		= m_line;
	strcpy( temp_token, m_token );

	numentries = 0;

	Reset();
	while( TokenAvailable( true ) )
		{
		GetLine( true );
		numentries++;
		}
	
	m_tokenready = temp_tokenready;
	m_script_p	= temp_script_p;
	m_line		= temp_line;
	strcpy( m_token, temp_token );
	
	return numentries;
	}

/*
==============
=
= Parse
=
==============
*/

void Script::Parse
	( 
	char *data, 
	int length, 
	const char *name 
	)

	{
	Close();

	buffer = data;
	Reset();
	m_end_p = m_script_p + length;
	this->length = length;
	m_filename = name;
	}

/*
==============
=
= Load
=
==============
*/

void Script::LoadFile
	(
	const char *name
	)

	{
	int  length;
	char *buf;

	Close();

  	length = FILE_FS_ReadFile( name, (void **)&buf );

   if ( length == -1 )
      {
		error( "LoadFile", "Couldn't load %s\n", name );
      }

   buffer = ( char * )FILE_Malloc( length );
   memcpy( buffer, buf, length );
   FILE_FS_FreeFile( buf );

   Parse( buffer, length, name );
	m_releaseBuffer = true;
	}

const char *Script::Token
	(
	void
	)

	{
	return m_token;
	}

//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/script.cpp                       $
// $Revision:: 4                                                              $
//     $Date:: 10/07/99 2:20p                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/script.cpp                            $
// 
// 4     10/07/99 2:20p Jimdose
// fixed bug in Skip where string wasn't being passed into Error
// 
// 3     9/27/99 5:02p Jimdose
// added include for cmdlib.h
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
// such as skip white-space, get string, get integer, get float, get m_token,
// and skip line are implemented.  
//
// Note: all '//', '#', and ';' are treated as comments.  Probably should
// make this behaviour toggleable.
// 

#include "script.h"
#include <stdlib.h>
#include "ucommon.h"
#include "cmdlib.h"

#define TOKENCOMMENT      (';')
#define TOKENEOL          ('\n')
#define TOKENNULL         ('\0')
#define TOKENSPACE        (' ')

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
		delete[] const_cast<char *>( buffer );
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
		Error( "End of token file reached prematurely" );
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
				Error( "line is incomplete\n" );
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
			Error( "Token too large" );
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
		Error( "Token too large" );
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
		Error( "Token too large" );
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
		Error( "Expecting string" );
		}

	m_script_p++;

	startline = m_line;
	token_p = m_token;
	while( *m_script_p != '"' )
		{
		if ( *m_script_p == TOKENEOL )
			{
			Error( "Line is incomplete while reading string" );
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
			Error( "End of token file reached prematurely while reading string" );
			}

		if ( token_p == &m_token[ MAXTOKEN ] )
			{
			Error( "String too large" );
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
			Error( "Token too large" );
			}

		if ( m_script_p == m_end_p )
			{
			break;
			}
		}

	*token_p = 0;

	return m_token;
   }

void Script::Skip
   (
   const char *string,
   bool crossline
   )

   {
	GetToken( crossline );

   if ( strcmp( m_token, string ) )
      {
      Error( "Expecting '%s'", string );
      }
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

UVector3 Script::GetVector
	(
	bool crossline
	)

	{
	return UVector3( GetFloat( crossline ), GetFloat( crossline ), GetFloat( crossline ) );
	}

/*
==============
=
= GetVector
=
==============
*/

void Script::GetVector
	(
   float vector[ 3 ],
	bool crossline
	)

	{
   vector[ 0 ] = GetFloat( crossline );
   vector[ 1 ] = GetFloat( crossline );
   vector[ 2 ] = GetFloat( crossline );
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
	const char *data, 
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
	char *buffer;
   FILE *f;

	Close();

  	f = fopen( name, "rt" );
   if ( !f )
      {
		::Error( "Script::LoadFile :: Couldn't load %s\n", name );
      }

	fseek( f, 0, SEEK_END );
	length = ftell( f );
	fseek( f, 0, SEEK_SET );

   buffer = new char[ length ];
   fread( buffer, 1, length, f );
	fclose( f );

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

void Script::Error
   (
   const char *error,
   ...
   )

   {
	va_list  argptr;
	char	   text[ 1024 ];

   va_start( argptr, error );
	vsprintf( text, error, argptr );
	va_end( argptr );

   ::Error( "%s(%d): %s\n", m_filename.c_str(), m_line, text );
   }

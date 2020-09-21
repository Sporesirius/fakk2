//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2plugins/skelout/str.h                    $
// $Revision:: 1                                                              $
//     $Date:: 7/23/99 12:00p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2plugins/skelout/str.h                         $
// 
// 1     7/23/99 12:00p Jimdose
// 
// 4     6/25/99 7:43p Morbid
// 
// 3     6/22/99 12:14p Jimdose
// added str::cmp
// 
// 2     5/27/99 8:40p Jimdose
// merged math and gui code
// 
// 1     5/27/99 5:40p Jimdose
// 
// DESCRIPTION:
// Simple, DLL portable string class
// 

#ifndef __STR_H__
#define __STR_H__

#include <assert.h>
#include <string.h>

class str
	{
	protected:
		int					len;
		char					*data;

	public:
								~str();
								str();
								str( const char *text );
								str( const str& string );
								str( const str string, int start, int end );

					int		length( void ) const;
		const		char *	c_str( void ) const;

					void		append( const char *text );
					void		append( const str& text );

					char		operator[]( int index ) const;
					char&		operator[]( int index );

					void		operator=( const str& text );
					void		operator=( const char *text );

		friend	str		operator+( const str& a, const str& b );
		friend	str		operator+( const str& a, const char *b );
		friend	str		operator+( const char *a, const str& b );

      friend	str		operator+( const str& a, const float b );
      friend	str		operator+( const str& a, const int b );
      friend	str		operator+( const str& a, const unsigned b );
      friend	str		operator+( const str& a, const bool b );

					str&		operator+=( const str& a );
					str&		operator+=( const char *a );
					str&		operator+=( const float a );
					str&		operator+=( const int a );
					str&		operator+=( const unsigned a );
					str&		operator+=( const bool a );

		friend	bool		operator==(	const str& a, const str& b );
		friend	bool		operator==(	const str& a, const char *b );
		friend	bool		operator==(	const char *a, const str& b );

		friend	bool		operator!=(	const str& a, const str& b );
		friend	bool		operator!=(	const str& a, const char *b );
		friend	bool		operator!=(	const char *a, const str& b );

                        operator const char * () const;

               int      icmpn( const char *text, int n );
               int      icmpn( const str& text, int n );
               int      icmp( const char *text );
               int      icmp( const str& text );
               int      cmpn( const char *text, int n );
               int      cmpn( const str& text, int n );

               void     tolower( void );
               void     toupper( void );

      static   char     *tolower( char *s1 );
      static   char     *toupper( char *s1 );

      static   int      icmpn( const char *s1, const char *s2, int n );
      static   int      icmp( const char *s1, const char *s2 );
      static   int      cmpn( const char *s1, const char *s2, int n );
      static   int      cmp( const char *s1, const char *s2 );

      static   bool	   isNumeric( const char *str );
               bool	   isNumeric( void );

   };

inline str::~str()
	{
	assert( data );
	if ( data )
		{
		delete [] data;
		data = NULL;
		}
	}

inline str::str()
	{
	data = new char[ 1 ];
	data[ 0 ] = 0;
	len = 0;
	}

inline str::str
	(
	const char *text
	)

	{
	assert( text );

	if ( text )
		{
		len = strlen( text );
		data = new char[ len + 1 ];
		strcpy( data, text );
		}
	else
		{
		data = new char[ 1 ];
		data[ 0 ] = 0;
		len = 0;
		}
	}

inline str::str
	(
	const str& text
	)

	{
	len = text.length();
	data = new char[ len + 1 ];
	strcpy( data, text.c_str() );
	}

inline str::str
	(
	const str text, 
	int start,
	int end
	)

	{
	int i;

	if ( end > text.length() )
		{
		end = text.length();
		}

	if ( start > text.length() )
		{
		start = text.length();
		}

	len = end - start;
	if ( len < 0 )
		{
		len = 0;
		}

	data = new char[ len + 1 ];
	for( i = 0; i < len; i++ )
		{
		data[ i ] = text[ start + i ];
		}

	data[ len ] = 0;
	}

inline int str::length( void ) const
	{
	return len;
	}

inline const char *str::c_str( void ) const
	{
	assert( data );

	return data;
	}

inline void str::append
	(
	const char *text
	)

	{
	char *olddata;

	assert( text );
	assert( data );

	if ( text )
		{
		olddata = data;

		len = strlen( data ) + strlen( text );
		data = new char[ len + 1 ];
		
		strcpy( data, olddata );
		strcat( data, text );

		if ( olddata )
			{
			delete [] olddata;
			olddata = NULL;
			}
		}
	}

inline void str::append
	(
	const str& text
	)

	{
	assert( data );
	append( text.c_str() );
	}

inline char str::operator[]( int index ) const
	{
	assert( data );

	// don't include the '/0' in the test, because technically, it's out of bounds
	assert( ( index >= 0 ) && ( index < len ) );

	// In release mode, give them a null character
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ( ( index < 0 ) || ( index >= len ) )
		{
		return 0;
		}

	return data[ index ];
	}

inline char& str::operator[]
	(
	int index
	)

	{
	// Used for result for invalid indices
	static char dummy = 0;

	assert( data );

	// don't include the '/0' in the test, because technically, it's out of bounds
	assert( ( index >= 0 ) && ( index < len ) );

	// In release mode, let them change a safe variable
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ( ( index < 0 ) || ( index >= len ) )
		{
		return dummy;
		}

	return data[ index ];
	}

inline void str::operator=
	(
	const str& text
	)

	{
   char *temp;

	assert( data );

   len = text.length();
	temp = new char[ len + 1 ];
	strcpy( temp, text.c_str() );

   // we don't destroy the old data until we've allocated the new one
   // in case we are assigning the string from data inside the old string.
	if ( data )
		{
		delete [] data;
		}

   data = temp;
	}

inline void str::operator=
	(
	const char *text
	)

	{
   char *temp;

	assert( data );
	assert( text );

	if ( !text )
		{
		// safe behaviour if NULL
		len = 0;
		temp = new char[ 1 ];
		temp[ 0 ] = 0;
		}
	else
		{
		len = strlen( text );
		temp = new char[ len + 1 ];
		strcpy( temp, text );
		}

   // we don't destroy the old data until we've allocated the new one
   // in case we are assigning the string from data inside the old string.
   if ( data )
		{
		delete [] data;
		}

   data = temp;
	}

inline str operator+
	(
	const str& a,
	const str& b
	)

	{
	str result( a );

	result.append( b );

	return result;
	}

inline str operator+
	(
	const str& a,
	const char *b
	)

	{
	str result( a );

	result.append( b );

	return result;
	}

inline str operator+
	(
	const char *a,
	const str& b
	)

	{
	str result( a );

	result.append( b );

	return result;
	}

inline str operator+
   (
   const str& a,
   const bool b
   )

   {
	str result( a );

   result.append( b ? "true" : "false" );

	return result;
   }

inline str& str::operator+=
	(
	const str& a
	)

	{
	assert( data );
	append( a );
	return *this;
	}

inline str& str::operator+=
	(
	const char *a
	)

	{
	assert( data );
	append( a );
	return *this;
	}

inline str& str::operator+=
	(
	const bool a
	)

	{
	assert( data );
   append( a ? "true" : "false" );
	return *this;
	}

inline bool operator==
	(
	const str& a,
	const str& b
	)

	{
	return ( !strcmp( a.c_str(), b.c_str() ) );
	}

inline bool operator==
	(
	const str& a,
	const char *b
	)

	{
	assert( b );
	if ( !b )
		{
		return false;
		}
	return ( !strcmp( a.c_str(), b ) );
	}

inline bool operator==
	(
	const char *a,
	const str& b
	)

	{
	assert( a );
	if ( !a )
		{
		return false;
		}
	return ( !strcmp( a, b.c_str() ) );
	}

inline bool operator!=
	(
	const str& a,
	const str& b
	)

	{
	return !( a == b );
	}

inline bool operator!=
	(
	const str& a,
	const char *b
	)

	{
	return !( a == b );
	}

inline bool operator!=
	(
	const char *a,
	const str& b
	)

	{
	return !( a == b );
	}

inline int str::icmpn
   (
   const char *text, 
   int n
   )

   {
	assert( data );
	assert( text );

   return str::icmpn( data, text, n );
   }

inline int str::icmpn
   (
   const str& text, 
   int n
   )

   {
	assert( data );
	assert( text.data );

   return str::icmpn( data, text.data, n );
   }

inline int str::icmp
   (
   const char *text
   )

   {
	assert( data );
	assert( text );

   return str::icmp( data, text );
   }

inline int str::icmp
   (
   const str& text
   )

   {
	assert( data );
	assert( text.data );

   return str::icmp( data, text.data );
   }

inline int str::cmpn
   (
   const char *text, 
   int n
   )

   {
	assert( data );
	assert( text );

   return str::cmpn( data, text, n );
   }

inline int str::cmpn
   (
   const str& text, 
   int n
   )

   {
	assert( data );
	assert( text.data );

   return str::cmpn( data, text.data, n );
   }

inline void str::tolower
   (
   void
   )

   {
   assert( data );
   str::tolower( data );
   }

inline void str::toupper
   (
   void
   )

   {
   assert( data );
   str::toupper( data );
   }

inline bool str::isNumeric
   (
   void
   )

   {
   assert( data );
   return str::isNumeric( data );
   }

inline str::operator const char *
   (
   void
   ) const

   {
   return c_str ();
   }

#endif

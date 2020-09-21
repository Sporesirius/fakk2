//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/str.h                            $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:24p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/str.h                                 $
// 
// 1     9/21/99 2:24p Jimdose
// 
// 9     9/17/99 4:07p Morbid
// Much optimized
// 
// 8     8/19/99 8:29p Morbid
// Added CapLength, let's you set a string's max length
// 
// 7     8/19/99 6:49p Morbid
// Fixed operator + ( str, char )
// 
// 6     8/12/99 7:02p Morbid
// Adding streaming support
// 
// 5     8/03/99 2:30p Jimdose
// added character appending functions
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

#include "streams.h"

void TestStringClass ();

class strdata
   {
   public:
      strdata () : refcount ( 0 ), data ( NULL ), alloced ( 0 ) {}
      ~strdata () 
         {
         if ( data )
            delete [] data;
         }

      void AddRef () { refcount++; }
      bool DelRef () // True if killed
         {
         refcount--;
         if ( refcount < 0 )
            {
            delete this;
            return true;
            }
         
         return false;
         }

      char *data;
      int refcount;
      int alloced;
   };

class str : public UStringStreamIn
	{
	protected:
		int					len;
      strdata           *m_data;

      void              EnsureAlloced ( int, bool keepold = true );
      void              EnsureDataWritable ();

  	public:
								~str();
								str();
								str( const char *text );
								str( const str& string );
								str( const str string, int start, int end );
								str( const char ch );

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
      friend	str		operator+( const str& a, const char b );

					str&		operator+=( const str& a );
					str&		operator+=( const char *a );
					str&		operator+=( const float a );
					str&		operator+=( const char a );
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

               void     StreamIn ( const char * );

               void     CapLength ( int );

               void     BackSlashesToSlashes ();
   };

inline str::~str()
	{
   if ( m_data )
      {
      m_data->DelRef ();
      m_data = NULL;
      }
	}

inline str::str() : len ( 0 ), m_data ( NULL )
	{
   EnsureAlloced ( 1 );
	m_data->data[ 0 ] = 0;
	}

inline str::str
	(
	const char *text
   ) : m_data ( NULL )

	{
	assert( text );

	if ( text )
		{
		len = strlen( text );
      EnsureAlloced ( len + 1 );
		strcpy( m_data->data, text );
		}
	else
		{
      EnsureAlloced ( 1 );
		m_data->data[ 0 ] = 0;
		len = 0;
		}
	}

inline str::str
	(
	const str& text
   ) : m_data ( NULL )

	{
   m_data = text.m_data;
   m_data->AddRef ();

   len = text.len;
   }

inline str::str
	(
	const str text, 
	int start,
	int end
   ) : m_data ( NULL )

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

   EnsureAlloced ( len + 1 );

	for( i = 0; i < len; i++ )
		{
		m_data->data[ i ] = text[ start + i ];
		}

	m_data->data[ len ] = 0;
	}

inline str::str
   (
   const char ch
   ) : m_data ( NULL )

   {
	len = 1;
   EnsureAlloced ( 2 );

   m_data->data[ 0 ] = ch;
   m_data->data[ 1 ] = 0;
   }

inline int str::length( void ) const
	{
	return len;
	}

inline const char *str::c_str( void ) const
	{
	assert( m_data );

	return m_data->data;
	}

inline void str::append
	(
	const char *text
	)

	{
	assert( text );

	if ( text )
		{
		len += strlen( text );
		EnsureAlloced ( len + 1 );

      strcat( m_data->data, text );
		}
	}

inline void str::append
	(
	const str& text
	)

	{
   len += text.length ();
   EnsureAlloced ( len + 1 );

   strcat ( m_data->data, text.c_str () );
	}

inline char str::operator[]( int index ) const
	{
   assert ( m_data );
   
   if ( !m_data )
      return 0;

	// don't include the '/0' in the test, because technically, it's out of bounds
	assert( ( index >= 0 ) && ( index < len ) );

	// In release mode, give them a null character
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ( ( index < 0 ) || ( index >= len ) )
		{
		return 0;
		}

	return m_data->data[ index ];
	}

inline char& str::operator[]
	(
	int index
	)

	{
	// Used for result for invalid indices
	static char dummy = 0;
   assert ( m_data );

   // We don't know if they'll write to it or not
   // if it's not a const object
   EnsureDataWritable ();

   if ( !m_data )
      return dummy;

	// don't include the '/0' in the test, because technically, it's out of bounds
	assert( ( index >= 0 ) && ( index < len ) );

	// In release mode, let them change a safe variable
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ( ( index < 0 ) || ( index >= len ) )
		{
		return dummy;
		}

	return m_data->data[ index ];
	}

inline void str::operator=
	(
	const str& text
	)

	{
   m_data->DelRef ();

   len = text.len;
   m_data = text.m_data;
   m_data->AddRef ();
   }

inline void str::operator=
	(
	const char *text
	)

	{
	assert( text );

	if ( !text )
		{
		// safe behaviour if NULL
		len = 0;
		EnsureAlloced ( 1, false );
      m_data->data[0] = 0;
      return;
		}

   if ( !m_data )
      {
      len = strlen ( text );
      EnsureAlloced ( len + 1, false );
      strcpy ( m_data->data, text );
      return;
      }

   if ( text == m_data->data )
      return; // Copying same thing.  Punt.

   // If we alias and I don't do this, I could corrupt other strings...  This 
   // will get called with EnsureAlloced anyway
   EnsureDataWritable ();

   // Now we need to check if we're aliasing..
   if ( text >= m_data->data && text <= m_data->data + len )
      {
      // Great, we're aliasing.  We're copying from inside ourselves.
      // This means that I don't have to ensure that anything is alloced,
      // though I'll assert just in case.
      int diff = text - m_data->data;
      int i;

      assert ( strlen ( text ) < (unsigned) len );
      
      for ( i = 0; text[i]; i++ )
         {
         m_data->data[i] = text[i];
         }

      m_data->data[i] = 0;

      len -= diff;

      return;
      }

	len = strlen( text );
   EnsureAlloced ( len + 1, false );
	strcpy( m_data->data, text );
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

inline str operator+
	(
   const str& a,
	const char b
	)

	{
   char text[ 2 ];

   text[ 0 ] = b;
   text[ 1 ] = 0;

	return a + text;
	}

inline str& str::operator+=
	(
	const str& a
	)

	{
	append( a );
	return *this;
	}

inline str& str::operator+=
	(
	const char *a
	)

	{
	append( a );
	return *this;
	}

inline str& str::operator+=
	(
	const char a
	)

	{
   char text[ 2 ];

   text[ 0 ] = a;
   text[ 1 ] = 0;
	append( text );

   return *this;
	}

inline str& str::operator+=
	(
	const bool a
	)

	{
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
	assert( m_data );
	assert( text );

   return str::icmpn( m_data->data, text, n );
   }

inline int str::icmpn
   (
   const str& text, 
   int n
   )

   {
	assert( m_data );
	assert( text.m_data );

   return str::icmpn( m_data->data, text.m_data->data, n );
   }

inline int str::icmp
   (
   const char *text
   )

   {
	assert( m_data );
	assert( text );

   return str::icmp( m_data->data, text );
   }

inline int str::icmp
   (
   const str& text
   )

   {
	assert( c_str () );
	assert( text.c_str () );

   return str::icmp( c_str () , text.c_str () );
   }

inline int str::cmpn
   (
   const char *text, 
   int n
   )

   {
	assert( c_str () );
	assert( text );

   return str::cmpn( c_str () , text, n );
   }

inline int str::cmpn
   (
   const str& text, 
   int n
   )

   {
	assert( c_str () );
	assert( text.c_str ()  );

   return str::cmpn( c_str () , text.c_str () , n );
   }

inline void str::tolower
   (
   void
   )

   {
   assert( m_data );

   EnsureDataWritable ();

   str::tolower( m_data->data );
   }

inline void str::toupper
   (
   void
   )

   {
   assert( m_data );

   EnsureDataWritable ();

   str::toupper( m_data->data );
   }

inline bool str::isNumeric
   (
   void
   )

   {
   assert( m_data );
   return str::isNumeric( m_data->data );
   }

inline str::operator const char *
   (
   void
   ) const

   {
   return c_str ();
   }

#endif

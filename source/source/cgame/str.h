//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/str.h                              $
// $Revision:: 15                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/25/00 11:32p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/str.h                                   $
// 
// 15    7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 14    6/14/00 3:57p Markd
// fixed bug
// 
// 13    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 12    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 11    5/25/00 4:29p Markd
// made archive a friend class of strings
// 
// 10    3/22/00 3:23p Jimdose
// moved len from str to strdata
// 
// 9     3/21/00 2:44p Jimdose
// fixed a bug where assigning the string to itself would corrupt the object
// 
// 8     3/17/00 3:44p Markd
// added float, int and unsigned constructors
// 
// 7     10/28/99 12:17p Morbid
// Fixed various const-ness issues with the compare functions
// 
// 6     10/06/99 10:01a Markd
// Fixed compiler warnings
// 
// 5     10/05/99 2:03p Markd
// Added warning about files being in multiple projects
// 
// 4     9/29/99 4:38p Morbid
// Added snprintf
// 
// 3     9/24/99 1:55p Morbid
// Strings from Uber
// 
// 2     9/24/99 11:03a Morbid
// Added CapLength ()
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// Simple, DLL portable string class
//
// WARNING: This file is shared between fgame, cgame and possibly the user interface.
// It is instanced in each one of these directories because of the way that SourceSafe works.
// 

#ifndef __STR_H__
#define __STR_H__

#include <assert.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#pragma warning(disable : 4710)     // function 'blah' not inlined
#endif

void TestStringClass ();

class strdata
   {
   public:
      strdata () : len( 0 ), refcount ( 0 ), data ( NULL ), alloced ( 0 ) {}
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
      int len;
   };

#if 1
class __declspec( dllexport ) str
#else
class str : public Class
#endif
	{
	protected:

		friend class		Archiver;
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
                        str( const int num );
								str( const float num );
								str( const unsigned num );


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

               int      icmpn( const char *text, int n ) const;
               int      icmpn( const str& text, int n ) const;
               int      icmp( const char *text ) const;
               int      icmp( const str& text ) const;
               int      cmpn( const char *text, int n ) const;
               int      cmpn( const str& text, int n ) const;

               void     tolower( void );
               void     toupper( void );

      static   char     *tolower( char *s1 );
      static   char     *toupper( char *s1 );

      static   int      icmpn( const char *s1, const char *s2, int n );
      static   int      icmp( const char *s1, const char *s2 );
      static   int      cmpn( const char *s1, const char *s2, int n );
      static   int      cmp( const char *s1, const char *s2 );

      static   void     snprintf ( char *dst, int size, const char *fmt, ... );

      static   bool	   isNumeric( const char *str );
               bool	   isNumeric( void ) const;

               void     CapLength ( int );

               void     BackSlashesToSlashes ();
   };


inline char str::operator[]( int index ) const
	{
   assert ( m_data );
   
   if ( !m_data )
      return 0;

	// don't include the '/0' in the test, because technically, it's out of bounds
	assert( ( index >= 0 ) && ( index < m_data->len ) );

	// In release mode, give them a null character
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ( ( index < 0 ) || ( index >= m_data->len ) )
		{
		return 0;
		}

	return m_data->data[ index ];
	}

inline int str::length( void ) const
	{
   return ( m_data != NULL ) ? m_data->len : 0;
	}

inline str::~str()
	{
   if ( m_data )
      {
      m_data->DelRef ();
      m_data = NULL;
      }
	}

inline str::str() : m_data ( NULL )
	{
   EnsureAlloced ( 1 );
	m_data->data[ 0 ] = 0;
	}

inline str::str
	(
	const char *text
   ) : m_data ( NULL )

	{
   int len;

	assert( text );

	if ( text )
		{
      len = strlen( text );
		EnsureAlloced ( len + 1 );
		strcpy( m_data->data, text );
      m_data->len = len;
		}
	else
		{
      EnsureAlloced ( 1 );
		m_data->data[ 0 ] = 0;
		m_data->len = 0;
		}
	}

inline str::str
	(
	const str& text
   ) : m_data ( NULL )

	{
   m_data = text.m_data;
   m_data->AddRef ();
   }

inline str::str
	(
	const str text, 
	int start,
	int end
   ) : m_data ( NULL )

	{
	int i;
   int len;

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
   m_data->len = len;
	}

inline str::str
   (
   const char ch
   ) : m_data ( NULL )

   {
   EnsureAlloced ( 2 );

   m_data->data[ 0 ] = ch;
   m_data->data[ 1 ] = 0;
   m_data->len = 1;
   }

inline str::str
   (
   const float num
   ) : m_data ( NULL )

   {
   char text[ 32 ];
   int len;

   sprintf( text, "%.3f", num );
   len = strlen( text );
   EnsureAlloced( len + 1 );
   strcpy( m_data->data, text );
   m_data->len = len;
   }

inline str::str
   (
   const int num
   ) : m_data ( NULL )

   {
   char text[ 32 ];
   int len;

   sprintf( text, "%d", num );
   len = strlen( text );
   EnsureAlloced( len + 1 );
   strcpy( m_data->data, text );
   m_data->len = len;
   }

inline str::str
   (
   const unsigned num
   ) : m_data ( NULL )

   {
   char text[ 32 ];
   int len;

   sprintf( text, "%u", num );
   len = strlen( text );
   EnsureAlloced( len + 1 );
   strcpy( m_data->data, text );
   m_data->len = len;
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
   int len;

	assert( text );

	if ( text )
		{
		len = length();
		len += strlen( text );
		EnsureAlloced( len + 1 );

      strcat( m_data->data, text );
      m_data->len = len;
		}
	}

inline void str::append
	(
	const str& text
	)

	{
   int len;

   len = length();
   len += text.length();
   EnsureAlloced ( len + 1 );

   strcat ( m_data->data, text.c_str () );
   m_data->len = len;
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
	assert( ( index >= 0 ) && ( index < m_data->len ) );

	// In release mode, let them change a safe variable
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ( ( index < 0 ) || ( index >= m_data->len ) )
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
   // adding the reference before deleting our current reference prevents
   // us from deleting our string if we are copying from ourself
   text.m_data->AddRef();
   m_data->DelRef();
   m_data = text.m_data;
   }

inline void str::operator=
	(
	const char *text
	)

	{
   int len;

	assert( text );

	if ( !text )
		{
		// safe behaviour if NULL
		EnsureAlloced ( 1, false );
      m_data->data[0] = 0;
      m_data->len = 0;
      return;
		}

   if ( !m_data )
      {
      len = strlen ( text );
      EnsureAlloced( len + 1, false );
      strcpy ( m_data->data, text );
      m_data->len = len;
      return;
      }

   if ( text == m_data->data )
      return; // Copying same thing.  Punt.

   // If we alias and I don't do this, I could corrupt other strings...  This 
   // will get called with EnsureAlloced anyway
   EnsureDataWritable ();

   // Now we need to check if we're aliasing..
   if ( text >= m_data->data && text <= m_data->data + m_data->len )
      {
      // Great, we're aliasing.  We're copying from inside ourselves.
      // This means that I don't have to ensure that anything is alloced,
      // though I'll assert just in case.
      int diff = text - m_data->data;
      int i;

      assert ( strlen ( text ) < (unsigned) m_data->len );
      
      for ( i = 0; text[i]; i++ )
         {
         m_data->data[i] = text[i];
         }

      m_data->data[i] = 0;

      m_data->len -= diff;

      return;
      }

	len = strlen( text );
   EnsureAlloced ( len + 1, false );
	strcpy( m_data->data, text );
   m_data->len = len;
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
   ) const

   {
	assert( m_data );
	assert( text );

   return str::icmpn( m_data->data, text, n );
   }

inline int str::icmpn
   (
   const str& text, 
   int n
   ) const

   {
	assert( m_data );
	assert( text.m_data );

   return str::icmpn( m_data->data, text.m_data->data, n );
   }

inline int str::icmp
   (
   const char *text
   ) const

   {
	assert( m_data );
	assert( text );

   return str::icmp( m_data->data, text );
   }

inline int str::icmp
   (
   const str& text
   ) const

   {
	assert( c_str () );
	assert( text.c_str () );

   return str::icmp( c_str () , text.c_str () );
   }

inline int str::cmpn
   (
   const char *text, 
   int n
   ) const

   {
	assert( c_str () );
	assert( text );

   return str::cmpn( c_str () , text, n );
   }

inline int str::cmpn
   (
   const str& text, 
   int n
   ) const

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
   ) const

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

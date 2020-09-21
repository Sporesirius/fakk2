#include "str.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

char *str::tolower
   (
   char *s1
   )
   
   {
   char *s;

   s = s1;
	while( *s )
      {
      *s = ::tolower( *s );
		s++;
	   }
   
   return s1;
   }

char *str::toupper
   (
   char *s1
   )
   
   {
   char *s;

   s = s1;
	while( *s )
      {
      *s = ::toupper( *s );
		s++;
	   }
   
   return s1;
   }

int str::icmpn
   (
   const char *s1, 
   const char *s2, 
   int n
   )
   
   {
	int c1;
   int c2;
	
	do 
      {
		c1 = *s1++;
		c2 = *s2++;

		if ( !n-- )
         {
         // strings are equal until end point
			return 0;
		   }
		
		if ( c1 != c2 )
         {
			if ( c1 >= 'a' && c1 <= 'z' )
            {
				c1 -= ( 'a' - 'A' );
			   }

			if ( c2 >= 'a' && c2 <= 'z' )
            {
				c2 -= ( 'a' - 'A' );
			   }

			if ( c1 < c2 )
            {
            // strings less than
				return -1;
			   }
         else if ( c1 > c2 ) 
            {
            // strings greater than
            return 1;
            }
		   }
	   } 
   while( c1 );
	
   // strings are equal
	return 0;
   }

int str::icmp
   (
   const char *s1,
   const char *s2
   )
   
   {
	int c1;
   int c2;
	
	do 
      {
		c1 = *s1++;
		c2 = *s2++;

		if ( c1 != c2 )
         {
			if ( c1 >= 'a' && c1 <= 'z' )
            {
				c1 -= ( 'a' - 'A' );
			   }

			if ( c2 >= 'a' && c2 <= 'z' )
            {
				c2 -= ( 'a' - 'A' );
			   }

			if ( c1 < c2 )
            {
            // strings less than
				return -1;
			   }
         else if ( c1 > c2 ) 
            {
            // strings greater than
            return 1;
            }
		   }
	   } 
   while( c1 );
	
   // strings are equal
	return 0;
   }

int str::cmpn
   (
   const char *s1, 
   const char *s2, 
   int n
   )
   
   {
	int c1;
   int c2;
	
	do 
      {
		c1 = *s1++;
		c2 = *s2++;

		if ( !n-- )
         {
         // strings are equal until end point
			return 0;
		   }
		
		if ( c1 < c2 )
         {
         // strings less than
			return -1;
			}
      else if ( c1 > c2 ) 
         {
         // strings greater than
         return 1;
         }
	   } 
   while( c1 );
	
   // strings are equal
	return 0;
   }

int str::cmp
   (
   const char *s1, 
   const char *s2
   )
   
   {
	int c1;
   int c2;
	
	do 
      {
		c1 = *s1++;
		c2 = *s2++;

		if ( c1 < c2 )
         {
         // strings less than
			return -1;
			}
      else if ( c1 > c2 ) 
         {
         // strings greater than
         return 1;
         }
	   } 
   while( c1 );
	
   // strings are equal
	return 0;
   }

/*
============
IsNumeric

Checks a string to see if it contains only numerical values.
============
*/
bool str::isNumeric
   (
   const char *str
   )

   {
	int len;
	int i;
	bool dot;

	if ( *str == '-' )
		{
		str++;
		}

	dot = false;
	len = strlen( str );
	for( i = 0; i < len; i++ )
		{
		if ( !isdigit( str[ i ] ) )
			{
			if ( ( str[ i ] == '.' ) && !dot )
				{
				dot = true;
				continue;
				}
			return false;
			}
		}

	return true;
   }

str operator+
   (
   const str& a,
   const float b
   )

   {
   char text[ 20 ];

	str result( a );

   sprintf( text, "%f", b );
	result.append( text );

	return result;
   }

str operator+
   (
   const str& a,
   const int b
   )

   {
   char text[ 20 ];

	str result( a );

   sprintf( text, "%d", b );
	result.append( text );

	return result;
   }

str operator+
   (
   const str& a,
   const unsigned b
   )

   {
   char text[ 20 ];

	str result( a );

   sprintf( text, "%u", b );
	result.append( text );

	return result;
   }

str& str::operator+=
	(
	const float a
	)

	{
   char text[ 20 ];

	assert( data );

   sprintf( text, "%f", a );
	append( text );

   return *this;
	}

str& str::operator+=
	(
	const int a
	)

	{
   char text[ 20 ];

	assert( data );

   sprintf( text, "%d", a );
	append( text );

   return *this;
	}

str& str::operator+=
	(
	const unsigned a
	)

	{
   char text[ 20 ];

	assert( data );

   sprintf( text, "%u", a );
	append( text );

   return *this;
	}

#include "ucommon.h"

#include "uparse.h"

#define MAX_PARSED_LEN 1024

static char s_parsed[1024];

inline bool IsTokenSeparator ( char c ) 
   {
   return c == ' ' || c == '\n' || c == '\r';
   }

const char *uparse::Parse 
   ( 
   const char **what,
   bool crossline
   )

   {
   const char *&src = *what;
   int parsed_len = 0;
   // Changing src actually changes *what...  RAD, huh?!?!

   if ( !src ) 
      {
      return "";
      }

   while ( 1 ) 
      {
      if ( crossline ) 
         {
         while ( IsTokenSeparator ( src[0] ) )
            src++;
         }
      else
         {
         for ( ; src[0]; src++ ) 
            {
            if ( src[0] == '\n' )
               return "";
            else if ( !IsTokenSeparator ( src[0] ) )
               break;
            }
         }

      if ( !src[0] )
         {
         src = NULL;
         return "";
         }
      
      if ( src[0] == '/' && src[1] == '/' )
         {
         while ( src[0] != '\n' && src[0] != 0 )
            src++;
         }
      else if ( src[0] == '/' && src[1] == '*' )
         {
         for ( src += 2; src[0]; src++ ) 
            {
            if ( src[0] == '*' && src[1] == '/' )
               {
               src += 2;
               break;
               }
            }
         }
      else
         {
         break;
         }
      }

   if ( src[0] == '\"' ) 
      {
      src++;
      while ( src[0] != '\"' && src[0] != 0 )
         {
         s_parsed[parsed_len] = src[0];
         src++;
         parsed_len++;
         if ( parsed_len >= MAX_PARSED_LEN )
            {
            return s_parsed;
            }
         }
      s_parsed[parsed_len] = 0;
      if ( src[0] == '\"' )
         src++;
      return s_parsed;
      }

   // Otherwise, go till we find a token separator
   while ( !IsTokenSeparator ( src[0] ) && src[0] != 0 )
      {
      s_parsed[parsed_len] = src[0];
      src++;
      parsed_len++;
      if ( parsed_len > MAX_PARSED_LEN )
         {
         return s_parsed;
         }
      }

   s_parsed[parsed_len] = 0;
   return s_parsed;
   }

void uparse::SkipRestOfLine
   (
   const char **what
   )

   {
   const char *&src = *what;

   if ( !src )
      return;

   while ( src[0] && src[0] != '\n' )
      src++;

   if ( src[0] == '\n' )
      src++;
   }

#ifndef __UPARSE_H__
#define __UPARSE_H__

#include "ucommon.h"

namespace uparse
   {
   template <class T>
   struct tokens
      {
      const char *token;
      T number;
      
      T Get ( const char *, bool caseSens = false );
      T Parse ( const char **, bool crossline = true, bool caseSens = false );
      };
   
   typedef tokens<int> tokenset;

   extern const char *Parse ( const char **, bool crossline = true );
   extern void SkipRestOfLine ( const char ** );
   };

template <class T>
inline T uparse::tokens<T>::Parse 
   ( 
   const char **in, 
   bool crossline,
   bool caseSens 
   )

   {
   return Get ( uparse::Parse ( in, crossline ), caseSens );
   }

template <class T>
T uparse::tokens<T>::Get 
   ( 
   const char *tocompare, 
   bool caseSens 
   )

   {
   tokens<T> *token = this;
   
   ASSERT ( tocompare );

   if ( caseSens )
      {
      for ( ; token->token; token++ ) 
         {
         if ( !strcmp ( token->token, tocompare ) )
            return token->number;
         }
      }
   else
      {
      for ( ; token->token; token++ )
         {
         if ( !stricmp ( token->token, tocompare ) )
            return token->number;
         }
      }

   return token->number;
   }

#endif /* !__UPARSE_H__ */
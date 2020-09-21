//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/streams.h                        $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:30p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/streams.h                             $
// 
// 1     9/21/99 2:30p Jimdose
// 
// 4     8/27/99 7:08p Morbid
// Allowed you to format int data
// 
// 3     8/12/99 6:54p Morbid
// Fixed really stupid class redefinition
// 
// 2     8/12/99 6:40p Morbid
// Streaming changes
//
// DESCRIPTION:
// 

#ifndef __STREAMS_H__
#define __STREAMS_H__

class UByteStreamInException {};
class UByteStreamOutException {};
class UStringStreamInException {};

class UByteStreamIn
   {
   public:
      virtual void StreamIn ( void *, int len ) = 0;
      
      UByteStreamIn &operator << ( int i )            { StreamIn ( &i, sizeof ( i ) ); return *this; }
      UByteStreamIn &operator << ( char c )           { StreamIn ( &c, sizeof ( c ) ); return *this; }
      UByteStreamIn &operator << ( unsigned u )       { StreamIn ( &u, sizeof ( u ) ); return *this; }
      UByteStreamIn &operator << ( unsigned char u )  { StreamIn ( &u, sizeof ( u ) ); return *this; }
      UByteStreamIn &operator << ( short s )          { StreamIn ( &s, sizeof ( s ) ); return *this; }
      UByteStreamIn &operator << ( unsigned short u ) { StreamIn ( &u, sizeof ( u ) ); return *this; }
      UByteStreamIn &operator << ( float f )          { StreamIn ( &f, sizeof ( f ) ); return *this; }
      UByteStreamIn &operator << ( double d )         { StreamIn ( &d, sizeof ( d ) ); return *this; }
   };

class UByteStreamOut
   {
   public:
      virtual void StreamOut ( void *, int len ) = 0;

      UByteStreamOut &operator >> ( int &i )              { StreamOut ( &i, sizeof ( i ) ); return *this; }
      UByteStreamOut &operator >> ( char &c )             { StreamOut ( &c, sizeof ( c ) ); return *this; }
      UByteStreamOut &operator >> ( unsigned &u )         { StreamOut ( &u, sizeof ( u ) ); return *this; }
      UByteStreamOut &operator >> ( unsigned char &u )    { StreamOut ( &u, sizeof ( u ) ); return *this; }
      UByteStreamOut &operator >> ( short &s )            { StreamOut ( &s, sizeof ( s ) ); return *this; }
      UByteStreamOut &operator >> ( unsigned short &u )   { StreamOut ( &u, sizeof ( u ) ); return *this; }
      UByteStreamOut &operator >> ( float &f )            { StreamOut ( &f, sizeof ( f ) ); return *this; }
      UByteStreamOut &operator >> ( double &d )           { StreamOut ( &d, sizeof ( d ) ); return *this; }
   };

class USSIntLead
   {
   public:
      int lead;
      bool withspaces;
      USSIntLead ( int l, bool leadwithspaces = false ) : 
        lead ( l ), withspaces ( leadwithspaces ) {}
   };

class UStringStreamIn
   {
   private:
      static char s_work[255];
      inline void StreamWork () { StreamIn ( s_work ); }
      int m_intleadingzeros;
      bool m_intleadwithspaces;

   public:
      UStringStreamIn () : m_intleadingzeros ( 0 ) {}
      
      virtual void StreamIn ( const char * ) = 0;
      
      UStringStreamIn &operator << ( const char *s ) { StreamIn ( s ); return *this; }
      UStringStreamIn &operator << ( int );
      UStringStreamIn &operator << ( unsigned );
      UStringStreamIn &operator << ( float );
      UStringStreamIn &operator << ( double );
      UStringStreamIn &operator << ( char );

      UStringStreamIn &operator << ( USSIntLead &lead ) 
         { m_intleadingzeros = lead.lead; m_intleadwithspaces = lead.withspaces; return *this; }
   };



#endif /* !__STREAMS_H__ */
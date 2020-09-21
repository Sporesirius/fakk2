//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/streams.cpp                      $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:30p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/streams.cpp                           $
// 
// 1     9/21/99 2:30p Jimdose
// 
// 3     8/27/99 7:08p Morbid
// Allowed you to format int data
// 
// 2     8/12/99 6:40p Morbid
// Streaming changes
//
// DESCRIPTION:
// 

#include "ucommon.h"
#include "streams.h"

char UStringStreamIn::s_work[255];

UStringStreamIn &UStringStreamIn::operator << 
   (
   int i
   )

   {
   if ( m_intleadwithspaces )
      sprintf ( s_work, "%*d", m_intleadingzeros, i );
   else
      sprintf ( s_work, "%0*d", m_intleadingzeros, i );
   StreamWork ();
   return *this;
   }

UStringStreamIn &UStringStreamIn::operator << 
   (
   unsigned u
   )

   {
   if ( m_intleadwithspaces )
      sprintf ( s_work, "%*u", m_intleadingzeros, u );
   else
      sprintf ( s_work, "%0*u", m_intleadingzeros, u );

   StreamWork ();
   return *this;
   }

UStringStreamIn &UStringStreamIn::operator << 
   (
   float f 
   )

   {
   sprintf ( s_work, "%f", f );
   StreamWork ();
   return *this;
   }

UStringStreamIn &UStringStreamIn::operator << 
   (
   double d
   )

   {
   sprintf ( s_work, "%f", d );
   StreamWork ();
   return *this;
   }

UStringStreamIn &UStringStreamIn::operator << 
   (
   char c
   )

   {
   s_work[0] = c;
   s_work[1] = 0;
   StreamWork ();
   return *this;
   }
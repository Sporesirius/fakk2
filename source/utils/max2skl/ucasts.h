//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/ucasts.h                         $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:31p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/ucasts.h                              $
// 
// 1     9/21/99 2:31p Jimdose
// 
// 2     5/27/99 8:40p Jimdose
// merged math and gui code
//
// DESCRIPTION:
// 

#ifndef __UCASTS_H__
#define __UCASTS_H__

namespace ucasts
   {
   // I have to declare this funciton like this if I want it inline.  Why?  Dunno
   template <class T> 
   inline unsigned &uint_cast 
      ( 
      T &f 
      )

      {
      return *reinterpret_cast<unsigned *>(&f);
      }
   };

using namespace ucasts;

#endif
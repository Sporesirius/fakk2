//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/umem.h                           $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:31p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/umem.h                                $
// 
// 1     9/21/99 2:31p Jimdose
// 
// 2     5/27/99 8:40p Jimdose
// merged math and gui code
//
// DESCRIPTION:
// 

#ifndef __UMEM_H__
#define __UMEM_H__

namespace umem 
   {
   template <class T>
   inline void Zero 
      ( 
      T& obj 
      ) 

      {
      memset ( &obj, 0, sizeof ( T ) );
      }

   template <class T, class U>
   inline void Copy
      ( 
      T &dst, 
      U &src
      )

      {
      assert ( ! ( sizeof ( T ) - sizeof ( U ) ) );
      memcpy ( &dst, &src, sizeof ( T ) );
      }
   };

#endif /* !__UMEM_H__ */
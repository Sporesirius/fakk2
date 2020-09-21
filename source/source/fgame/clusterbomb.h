//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/clusterbomb.h                      $
// $Revision:: 4                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 7/14/00 10:42a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/clusterbomb.h                           $
// 
// 4     7/14/00 10:42a Aldie
// Added archive function
// 
// 3     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 2     6/07/00 4:16p Aldie
// Added clusterbombs, heatseeking, and drunk
//
// DESCRIPTION:
// Clusterbomb

#ifndef __CLUSTERBOMB_H__
#define __CLUSTERBOMB_H__

#include "weapon.h"
#include "weaputils.h"

class ClusterBomb : public Projectile
   {
   private:
      str               m_clustermodel;
      int               m_clustercount;

   public:
      CLASS_PROTOTYPE( ClusterBomb );
      
                        ClusterBomb();
      void              Explode( Event *ev );
      void              Think( Event *ev );
      void              ClusterModel( Event *ev );
      void              ClusterCount( Event *ev );

      virtual void      Archive( Archiver &arc );
   };

inline void ClusterBomb::Archive
	(
	Archiver &arc
	)
   {
   Projectile::Archive( arc );

   arc.ArchiveInteger( &m_clustercount );
   arc.ArchiveString( &m_clustermodel );
   }

#endif // __CLUSTERBOMB_H__

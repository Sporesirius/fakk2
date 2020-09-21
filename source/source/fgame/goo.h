//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/goo.h                              $
// $Revision:: 5                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 7/20/00 6:21p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/goo.h                                   $
// 
// 5     7/20/00 6:21p Aldie
// More fixes to goo
// 
// 4     7/20/00 3:46p Aldie
// Lots of fixes to the goo projectile
// 
// 3     6/08/00 3:56p Aldie
// Fixed a comment
// 
// 2     6/08/00 3:55p Aldie
// Added goo
//
// DESCRIPTION:
// Goo Gun Projectile

#ifndef __GOO_H__
#define __GOO_H__

#include "weapon.h"
#include "weaputils.h"

class GooProjectile : public Projectile
   {
   private:
      str               m_debrismodel;
      int               m_debriscount;

   public:
      CLASS_PROTOTYPE( GooProjectile );
      
                        GooProjectile();
      void              Explode( Event *ev );
      void              SetDebrisModel( Event *ev );
      void              SetDebrisCount( Event *ev );
      void              Archive( Archiver &arc );
   };

void GooProjectile::Archive
   (
   Archiver &arc
   )

   {
   Projectile::Archive( arc );
   arc.ArchiveString( &m_debrismodel );
   arc.ArchiveInteger( &m_debriscount );
   }


class GooDebris : public Projectile
   {
   private:
      float          nexttouch;

   public:
      CLASS_PROTOTYPE( GooDebris );

                     GooDebris();
      void           Touch( Event *ev );
      void           Prethink( Event *ev );
      void           Archive( Archiver &arc );
   };

void GooDebris::Archive
   (
   Archiver &arc
   )

   {
   Projectile::Archive( arc );
   arc.ArchiveFloat( &nexttouch );
   }

#endif // __GOO_H__
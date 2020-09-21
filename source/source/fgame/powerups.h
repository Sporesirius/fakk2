//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/powerups.h                         $
// $Revision:: 2                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 5/30/00 10:59a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/powerups.h                              $
// 
// 2     5/30/00 10:59a Aldie
// Added Circle of Protection Powerup
//
// DESCRIPTION:
// 

#include "inventoryitem.h"

class CircleOfProtection : public InventoryItem
   {
   private:
      Animate           *m_copmodel;
      float             m_minradius;
      float             m_maxradius;
      float             m_damage;
      float             m_damage_delay;
      float             m_knockback;

   public:
      CLASS_PROTOTYPE( CircleOfProtection );
      
                        CircleOfProtection();
      virtual void      Use( Event *ev );
      void              Deactivate( Event *ev );
      void              MinRadius( Event *ev );
      void              MaxRadius( Event *ev );
      void              SetDamage( Event *ev );
      void              DamageDelay( Event *ev );
      void              DoDamage( Event *ev );
      void              Knockback( Event *ev );
      virtual void      Archive( Archiver &arc );
   };

inline void CircleOfProtection::Archive (Archiver &arc)
   {
   InventoryItem::Archive( arc );

   arc.ArchiveFloat( &m_minradius );
   arc.ArchiveFloat( &m_maxradius );
   arc.ArchiveFloat( &m_damage );
   arc.ArchiveFloat( &m_damage_delay );
   arc.ArchiveFloat( &m_knockback );
   arc.ArchiveObjectPointer( (Class **) &m_copmodel );
   }


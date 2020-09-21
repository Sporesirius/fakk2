//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/gibs.h                             $
// $Revision:: 11                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 8/10/00 5:45p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/gibs.h                                  $
// 
// 11    8/10/00 5:45p Steven
// Fixed a way for blood to stay around forever on gibs.
// 
// 10    6/19/00 4:53p Steven
// Added next_bleed_time to make gibs not bleed as much.
// 
// 9     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 8     5/26/00 7:44p Markd
// 2nd phase save games
// 
// 7     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 6     4/14/00 10:36a Steven
// Added blood splat size to gibs.
// 
// 5     4/08/00 3:59p Steven
// Added damage event and blood spurt name.
// 
// 4     4/01/00 1:20p Steven
// Some clean up.
// 
// 3     3/30/00 2:04p Steven
// Added blood splats back in.
// 
// 2     3/02/00 6:40p Steven
// Made which blood model to use a parameter to gib.
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
//
// DESCRIPTION:
// Gibs - nuff said

#ifndef __GIBS_H__
#define __GIBS_H__

#include "g_local.h"
#include "mover.h"

#define NO_FINAL_PITCH  -1000

class Gib : public Mover
   {
   private:
      int      sprayed;
      float    scale;
      Mover    *blood;
		str		blood_splat_name;
		float		blood_splat_size;
		str		blood_spurt_name;
		float		final_pitch;
		float		next_bleed_time;
   public:
      CLASS_PROTOTYPE( Gib );

      qboolean    fadesplat;
      Gib();
		~Gib();
      Gib( str name, qboolean blood_trail, str bloodtrailname="", str bloodspurtname="", str bloodsplatname="", 
				float blood_splat_size = 8, float pitch=NO_FINAL_PITCH );
      void     SetVelocity( float health );
      void     SprayBlood( Vector start );
      void     Throw( Event *ev );
      void     Splat( Event *ev );
      void     Stop( Event *ev );
		void     Damage( Event *ev );
      void     ClipGibVelocity( void );
	   virtual void Archive( Archiver &arc );
	};

inline void Gib::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.ArchiveBoolean( &sprayed );
   arc.ArchiveFloat( &scale );
   arc.ArchiveObjectPointer( ( Class ** )&blood );
   arc.ArchiveString( &blood_splat_name );
   arc.ArchiveFloat( &blood_splat_size );
   arc.ArchiveString( &blood_spurt_name );
   arc.ArchiveFloat( &final_pitch );
   arc.ArchiveBoolean( &fadesplat );
	arc.ArchiveFloat( &next_bleed_time );
   }


void CreateGibs
   ( 
   Entity * ent, 
   float damage = -50, 
   float scale = 1.0f, 
   int num = 1, 
   const char * modelname = NULL
   );

extern Event EV_ThrowGib;

#endif // gibs.h

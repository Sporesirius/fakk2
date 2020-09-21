//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/beam.h                             $
// $Revision:: 17                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/23/00 11:49a                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/beam.h                                  $
// 
// 17    6/23/00 11:49a Markd
// fixed various imagindexes and saved games
// 
// 16    6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 15    5/30/00 10:59a Aldie
// Added Circle of Protection Powerup
// 
// 14    5/25/00 7:52p Markd
// 2nd pass save game stuff
// 
// 13    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 12    3/14/00 4:56p Aldie
// Added persist command
// 
// 11    2/14/00 7:34p Aldie
// Fixed some beam rendering issues
// 
// 10    1/26/00 5:07p Aldie
// Fixed beamdamage
// 
// 9     1/21/00 5:39p Aldie
// Fixed another targeting bug
// 
// 8     1/21/00 2:10p Aldie
// Fixed beam endpoint tracking
// 
// 7     1/10/00 6:17p Jimdose
// more code cleanup
// 
// 6     1/07/00 8:12p Jimdose
// cleaning up unused code
// 
// 5     11/19/99 11:28a Steven
// Added ability to specify the end point of a beam.
// 
// 4     10/19/99 11:57a Aldie
// Added some more beam features
// 
// 3     10/18/99 3:58p Aldie
// Fix for beam endpoints
// 
// 2     10/18/99 1:59p Aldie
// Lots of fixes for beams and stuff
//
// DESCRIPTION:
// 
#ifndef __BEAM_H__
#define __BEAM_H__

#include "g_local.h"
#include "scriptslave.h"

extern Event EV_FuncBeam_Activate;
extern Event EV_FuncBeam_Deactivate;
extern Event EV_FuncBeam_Diameter;
extern Event EV_FuncBeam_Maxoffset;
extern Event EV_FuncBeam_Minoffset;
extern Event EV_FuncBeam_Overlap;
extern Event EV_FuncBeam_Color;
extern Event EV_FuncBeam_SetTarget;
extern Event EV_FuncBeam_SetAngle;
extern Event EV_FuncBeam_SetEndPoint;
extern Event EV_FuncBeam_SetLife;
extern Event EV_FuncBeam_Shader;
extern Event EV_FuncBeam_Segments;
extern Event EV_FuncBeam_Delay;
extern Event EV_FuncBeam_NumSphereBeams;
extern Event EV_FuncBeam_SphereRadius;
extern Event EV_FuncBeam_ToggleDelay;
extern Event EV_FuncBeam_FindEndpoint;
extern Event EV_FuncBeam_EndAlpha;

class FuncBeam : public ScriptSlave
	{
   protected: 
      EntityPtr   end,origin_target;
      float       damage;
      float       life;
		Vector		end_point;
		qboolean  	use_angles;
      float       shootradius;
      str         shader;

   public:
      CLASS_PROTOTYPE( FuncBeam );

						FuncBeam();

      void        SetAngle( Event *ev );
      void        SetAngles( Event *ev );
		void			SetEndPoint( Event *ev );
      void        SetModel( Event *ev );
      void        SetDamage( Event *ev );
      void        SetOverlap( Event *ev );
      void        SetBeamStyle( Event *ev );
      void        SetLife( Event *ev );
      void        Activate( Event *ev );
      void        Deactivate( Event *ev );
      void        SetDiameter( Event *ev );
      void        SetMaxoffset( Event *ev );
      void        SetMinoffset( Event *ev );
      void        SetColor( Event *ev );
      void        SetSegments( Event *ev );
      void        SetBeamShader( str shader );
      void        SetBeamShader( Event *ev );
      void        SetBeamTileShader( Event *ev );
      void        SetDelay( Event *ev );
      void        SetToggleDelay( Event *ev );
      void        SetSphereRadius( Event *ev );
      void        SetNumSphereBeams( Event *ev );
      void        SetEndAlpha( Event *ev );
      void        SetShootRadius( Event *ev );
      void        SetPersist( Event *ev );
      void        FindEndpoint( Event *ev );
      void        UpdateEndpoint( Event *ev );
      void        UpdateOrigin( Event *ev );
      void        Shoot( Event *ev );

      virtual void setAngles( Vector ang );
      virtual void Archive( Archiver &arc );

      friend FuncBeam *CreateBeam( const char *model, const char *shader, Vector start, Vector end, int numsegments = 4, float scale = 1.0f, float life = 1.0f, float damage = 0.0f, Entity *origin_target=NULL );
	};

inline void FuncBeam::Archive
	(
	Archiver &arc
	)
   {
   ScriptSlave::Archive( arc );
   arc.ArchiveSafePointer( &end );
   arc.ArchiveSafePointer( &origin_target );
   arc.ArchiveFloat( &damage );
   arc.ArchiveFloat( &life );
   arc.ArchiveVector( &end_point );
   arc.ArchiveBoolean( &use_angles );
   arc.ArchiveFloat( &shootradius );
   arc.ArchiveString( &shader );
   if ( arc.Loading() )
      {
      SetBeamShader( shader );
      }
   }

#endif // __BEAM_H__

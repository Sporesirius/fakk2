//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/path.h                             $
// $Revision:: 5                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 6/26/00 4:53p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/path.h                                  $
// 
// 5     6/26/00 4:53p Steven
// Fixed some save/load game issues.
// 
// 4     6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 3     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 2     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
//
// DESCRIPTION:
//

#ifndef __PATH_H__
#define __PATH_H__

#include "g_local.h"
#include "class.h"
#include "container.h"
#include "navigate.h"

class Path : public Class
	{
	private:
		Container<PathNodePtr>	pathlist;
      Container<float>	      distanceToNextNode;
      Container<Vector>	      dirToNextNode;
		float							pathlength;
		PathNodePtr					from;
		PathNodePtr					to;
		int							nextnode;

	public:
      CLASS_PROTOTYPE( Path );

						Path();
						Path( int numnodes );
		void			Clear( void );
		void			Reset( void );
		void			AddNode( PathNode *node );
		PathNode		*GetNode( int num );
		PathNode		*NextNode( void );
      PathNode		*NextNode( PathNode *node );
		Vector		ClosestPointOnPath( Vector pos );
		float			DistanceAlongPath( Vector pos );
		Vector		PointAtDistance( float dist );
		PathNode		*NextNode( float dist );
		void			DrawPath( float r, float g, float b, float time );
		int			NumNodes( void );
		float			Length( void );
		PathNode		*Start( void );
		PathNode		*End( void );
	   virtual void Archive( Archiver &arc );
	};

inline void Path::Archive
	(
	Archiver &arc
	)
   {
   PathNodePtr node;
   int i, num;

   Class::Archive( arc );

   if ( arc.Saving() )
      {
      num = pathlist.NumObjects();
      }
   arc.ArchiveInteger( &num );
   if ( arc.Loading() )
      {
      pathlist.FreeObjectList();
      if ( num )
         pathlist.Resize( num );
      distanceToNextNode.FreeObjectList();
      dirToNextNode.FreeObjectList();
      }
   for ( i = 1; i <= num; i++ )
      {
		if ( arc.Loading() )
			pathlist.AddObject( node );

      arc.ArchiveSafePointer( pathlist.AddressOfObjectAt( i ) );
      }

	distanceToNextNode.Archive( arc );
   dirToNextNode.Archive( arc );

   arc.ArchiveFloat( &pathlength );
   arc.ArchiveSafePointer( &from );
   arc.ArchiveSafePointer( &to );
   arc.ArchiveInteger( &nextnode );
   }

typedef SafePtr<Path> PathPtr;

#endif /* path.h */

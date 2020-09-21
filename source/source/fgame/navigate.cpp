//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/navigate.cpp                       $
// $Revision:: 28                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/05/00 2:30p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/navigate.cpp                            $
// 
// 28    7/05/00 2:30p Steven
// Took out pvs check to draw ai routes because can't see routes in water
// (distance cull is good enough) and added a warning if you target a node to
// itself.
// 
// 27    6/27/00 5:47p Steven
// Took out some water restrictions on path connecting.
// 
// 26    6/26/00 4:51p Steven
// Fixed some save/load game issues.
// 
// 25    6/23/00 9:12p Markd
// fixed some loading of events at spawn time
// 
// 24    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 23    5/27/00 8:07p Markd
// Saved games 3rd pass
// 
// 22    5/25/00 4:27p Markd
// rewrote archive functions
// 
// 21    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 20    3/17/00 11:52a Steven
// Added jumping stuff.
// 
// 19    3/06/00 8:12p Markd
// removed unused cvar
// 
// 18    3/03/00 12:06p Steven
// Removed an annoying assert.
// 
// 17    2/25/00 11:07a Steven
// Made ai_showroutes cull out nodes that are farther than the new cvar
// ai_showroutes_distance.
// 
// 16    2/04/00 6:38p Markd
// Only print out the "." when loading in an archive
// 
// 15    2/04/00 1:29p Markd
// Added checksum to ai path nodes. It auto saves on exit now and will
// automatically re-build nodes as needed
// 
// 14    2/04/00 11:18a Markd
// Fixed memory leak with AI_PathNodes
// 
// 13    1/26/00 7:18p Markd
// put in creating path indicator
// 
// 12    1/25/00 6:32p Steven
// Fixed some path node stuff.
// 
// 11    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 10    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 9     12/09/99 3:33p Aldie
// Removed a line where the player's origin was being multiplied by 0.125
// 
// 8     10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 7     10/01/99 6:31p Markd
// added commands hidden inside fgame so that they would show up for command
// completion
// 
// 6     10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 5     9/29/99 5:18p Steven
// Event formatting.
// 
// 4     9/27/99 5:45p Markd
// began documentation and cleanup phase after merge
// 
// 3     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 2     9/15/99 6:57p Aldie
// Update to get game working
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 14    8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// 13    8/17/99 5:08p Markd
// Changed all FS_ReadFile's to FS_ReadFileEx's in game code
// 
// 12    6/11/99 1:23p Phook
// 
// 11    6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
//
// DESCRIPTION:
// C++ implementation of the A* search algorithm.
//

#include "g_local.h"
#include "navigate.h"
#include "path.h"
#include "misc.h"
#include "doors.h"

#define PATHFILE_VERSION 6

Event EV_AI_SavePaths
	( 
	"ai_savepaths", 
	EV_CHEAT,
   NULL,
   NULL,
   "Saves the path nodes under the default name." 
	);
Event EV_AI_SaveNodes
	( 
	"ai_save", 
	EV_CHEAT,
   "s",
   "filename",
   "Save path nodes."
	 );
Event EV_AI_LoadNodes
	( 
	"ai_load", 
	EV_CHEAT,
   "s",
   "filename",
   "Loads path nodes."
	);
Event EV_AI_ClearNodes
	( 
	"ai_clearnodes", 
	EV_CHEAT,
   NULL,
   NULL,
   "Clears all of the path nodes."
	);
Event EV_AI_RecalcPaths
	( 
	"ai_recalcpaths", 
	EV_CHEAT,
   "i",
   "nodenum",
   "Update the specified node."
	);
Event EV_AI_CalcPath
	( 
	"ai_calcpath", 
	EV_CHEAT,
	"ii",
   "nodenum1 nodenum2",
   "Calculate path from node1 to node2."
	);
Event EV_AI_DisconnectPath
	( 
	"ai_disconnectpath", 
	EV_CHEAT,
	"ii",
   "nodenum1 nodenum2",
   "Disconnect path between node1 and node2."
	);
Event EV_AI_SetNodeFlags
	( 
	"ai_setflags", 
	EV_CHEAT,
	"iSSSSSS",
   "nodenum token1 token2 token3 token4 token5 token6",
   "Set the flags for the specified node."
	);

cvar_t	*ai_createnodes = NULL;
cvar_t	*ai_debugpath;
cvar_t	*ai_debuginfo;
cvar_t	*ai_showroutes;
cvar_t	*ai_showroutes_distance;
cvar_t   *ai_shownodenums;
cvar_t   *ai_timepaths;

static Entity  *IgnoreObjects[ MAX_GENTITIES ];
static int		NumIgnoreObjects;

static PathNode *pathnodes[ MAX_PATHNODES ];
static qboolean pathnodesinitialized = false;
static qboolean loadingarchive = false;
static qboolean pathnodescalculated = false;
int ai_maxnode;

#define	MASK_PATHSOLID		(CONTENTS_SOLID|CONTENTS_MONSTERCLIP)

PathSearch PathManager;

int path_checksthisframe;

PathNode *AI_FindNode
	(
	const char *name
	)

	{
	int i;

	if ( !name )
		{
		return NULL;
		}

	if ( name[ 0 ] == '!' )
		{
		name++;
      return AI_GetNode( atof( name ) );
		}

	if ( name[ 0 ] == '$' )
		{
		name++;
		}

	for( i = 0; i <= ai_maxnode; i++ )
		{
		if ( pathnodes[ i ] && ( pathnodes[ i ]->TargetName() == name ) )
			{
			return pathnodes[ i ];
			}
		}

	return NULL;
	}

PathNode *AI_GetNode
	(
	int num
	)

	{
	if ( ( num < 0 ) || ( num > MAX_PATHNODES ) )
		{
		assert( false );
		return NULL;
		}

	return pathnodes[ num ];
	}

void AI_AddNode
	(
	PathNode *node
	)

	{
	int i;

	assert( node );

	for( i = 0; i < MAX_PATHNODES; i++ )
		{
		if ( pathnodes[ i ] == NULL )
			{
			break;
			}
		}

	if ( i < MAX_PATHNODES )
		{
		if ( i > ai_maxnode )
			{
			ai_maxnode = i;
			}
		pathnodes[ i ] = node;
		node->nodenum = i;
		return;
		}

	gi.Error( ERR_DROP, "Exceeded MAX_PATHNODES!\n" );
	}

void AI_RemoveNode
	(
	PathNode *node
	)

	{
	assert( node );
	if ( ( node->nodenum < 0 ) || ( node->nodenum > ai_maxnode ) )
		{
		assert( false );
		gi.Error( ERR_DROP, "Corrupt pathnode!\n" );
		}

	// If the nodenum is 0, the node was probably removed during initialization
	// otherwise, it's a bug.
	assert( ( pathnodes[ node->nodenum ] == node ) || ( node->nodenum == 0 ) );
	if ( pathnodes[ node->nodenum ] == node )
		{
		pathnodes[ node->nodenum ] = NULL;
		}
	}

void AI_ResetNodes
	(
	void
	)

	{
	int i;

	if ( !pathnodesinitialized )
		{
		memset( pathnodes, 0, sizeof( pathnodes ) );
		pathnodesinitialized = true;
		}
	else
		{
		for( i = 0; i < MAX_PATHNODES; i++ )
			{
			if ( pathnodes[ i ] )
				{
				delete pathnodes[ i ];
				}
			}
		}

	ai_maxnode = 0;
	}

/*****************************************************************************/
/*QUAKED info_pathnode (1 0 0) (-24 -24 0) (24 24 32) FLEE DUCK COVER DOOR JUMP LADDER

FLEE marks the node as a safe place to flee to.  Actor will be removed when it reaches a flee node and is not visible to a player.

DUCK marks the node as a good place to duck behind during weapon fire.

COVER marks the node as a good place to hide behind during weapon fire.

DOOR marks the node as a door node.  If an adjacent node has DOOR marked as well, the actor will only use the path if the door in between them is unlocked.

JUMP marks the node as one to jump from when going to the node specified by target.
"target" the pathnode to jump to.

******************************************************************************/

Event EV_Path_FindChildren
	( 
	"findchildren",
	EV_DEFAULT,
   NULL,
   NULL,
   "Adds this node to the path manager."
	);
Event EV_Path_FindEntities
	( 
	"findentities",
	EV_DEFAULT,
   NULL,
   NULL,
   "Finds doors."
	);
Event EV_Path_SetNodeFlags
	( 
	"spawnflags",
	EV_DEFAULT,
   "i",
   "node_flags",
   "Sets the path nodes flags."
	);
Event EV_Path_SetOriginEvent
	( 
	"origin",
	EV_DEFAULT,
   "v",
   "origin",
   "Sets the path node's origin."
	);
Event EV_Path_SetAngles
	( 
	"angles",
	EV_DEFAULT,
   "v",
   "angles",
   "Sets the path node's angles."
	);
Event EV_Path_SetAnim
	( 
	"anim",
	EV_DEFAULT,
   "s",
   "animname",
   "Sets the animname used for this path node."
	);
Event EV_Path_SetTargetname
	( 
	"targetname",
	EV_DEFAULT,
   "s",
   "targetname",
   "Sets the target name for this path node."
	);
Event EV_Path_SetTarget
	( 
	"target",
	EV_DEFAULT,
   "s",
   "target",
   "Sets the target for this path node."
	);

CLASS_DECLARATION( Listener, PathNode, "info_pathnode" )
	{
		{ &EV_Path_FindChildren,      FindChildren },
      { &EV_Path_FindEntities,      FindEntities },
      { &EV_Path_SetNodeFlags,      SetNodeFlags },
      { &EV_Path_SetOriginEvent,    SetOriginEvent },
      { &EV_SetAngle,               SetAngle },
      { &EV_Path_SetAngles,         SetAngles },
      { &EV_Path_SetAnim,           SetAnim },
      { &EV_Path_SetTargetname,     SetTargetname },
      { &EV_Path_SetTarget,         SetTarget },
		{ NULL, NULL }
	};

static Vector     pathNodesChecksum;
static int        numLoadNodes = 0;
static int			numNodes = 0;
static PathNode	*NodeList = NULL;

PathNode::PathNode()
	{
   numLoadNodes++;
	nodenum = 0;
	if ( !loadingarchive )
		{
		// our archive function will take care of this stuff
		AI_AddNode( this );
		PostEvent( EV_Path_FindChildren, 0 );
		}

	occupiedTime = 0;

	nodeflags = 0;
   setangles = false;
   drawtime = 0;
   contents = 0;

   occupiedTime = 0;
   entnum = 0;

	// crouch hieght
	setSize( "-24 -24 0", "24 24 40" );

	f = 0;
	h = 0;
	g = 0;

	gridX = 0;
   gridY = 0;
	inlist = NOT_IN_LIST;

	// reject is used to indicate that a node is unfit for ending on during a search
	reject = false;

	numChildren = 0;

	Parent	= NULL;
	NextNode = NULL;
	}

PathNode::~PathNode()
	{
	PathManager.RemoveNode( this );

	AI_RemoveNode( this );
	}

void PathNode::SetNodeFlags
   (
   Event *ev
   )

   {
	nodeflags = ev->GetInteger( 1 );
   }

void PathNode::SetOriginEvent
   (
   Event *ev
   )

   {
	setOrigin( ev->GetVector( 1 ) );
   pathNodesChecksum += origin;
   }

void PathNode::SetAngle
   (
   Event *ev
   )

   {
   Vector movedir;
	setangles = true;

   movedir = G_GetMovedir( ev->GetFloat( 1 ) );
	setAngles( movedir.toAngles() );
	}

void PathNode::SetAngles
   (
   Event *ev
   )

   {
	setangles = true;
   setAngles( ev->GetVector( 1 ) );
	}

void PathNode::SetAnim
   (
   Event *ev
   )

   {
	animname = ev->GetString( 1 );
   }

void PathNode::SetTargetname
   (
   Event *ev
   )

   {
	targetname = ev->GetString( 1 );
   }

void PathNode::SetTarget
   (
   Event *ev
   )

   {
	target = ev->GetString( 1 );
   }

str &PathNode::TargetName
	(
	void
	)

	{
	return targetname;
	}

void PathNode::setAngles
	(
	Vector ang
	)

	{
   angles = ang;
	}

void PathNode::setOrigin
	(
	Vector org
	)

	{
   origin = org;
   contents = gi.pointcontents( origin, 0 );
	}

void PathNode::setSize
	(
	Vector min,
	Vector max
	)

	{
	mins = min;
	maxs = max;
	}

void PathNode::Setup
	(
	Vector pos
	)

	{
	CancelEventsOfType( EV_Path_FindChildren );

	setOrigin( pos );

	ProcessEvent( EV_Path_FindChildren );
	}

void PathNode::Archive
	(
	Archiver &arc
	)

	{
	int i;

	Listener::Archive( arc );

	arc.ArchiveInteger( &nodenum );
   if ( arc.Loading() )
      {
	   assert( nodenum <= MAX_PATHNODES );
	   if ( nodenum > MAX_PATHNODES )
		   {
		   arc.FileError( "Node exceeds max path nodes" );
		   }
      }
	arc.ArchiveInteger( &nodeflags );
   arc.ArchiveVector( &origin );
   arc.ArchiveVector( &angles );
   if ( arc.Loading() )
      {
	   setOrigin( origin );
	   setAngles( angles );
      }

	arc.ArchiveBoolean( &setangles );
	arc.ArchiveString( &target );
	arc.ArchiveString( &targetname );
	arc.ArchiveString( &animname );

   arc.ArchiveFloat( &occupiedTime );
   arc.ArchiveInteger( &entnum );

   if ( arc.Loading() && !LoadingSavegame )
      {
      occupiedTime = 0;
      entnum       = 0;
      }

	arc.ArchiveInteger( &numChildren );
   if ( arc.Loading() )
      {
	   assert( numChildren <= NUM_PATHSPERNODE );
	   if ( numChildren > NUM_PATHSPERNODE )
		   {
		   arc.FileError( "Exceeded num paths per node" );
		   }
      }
	for( i = 0; i < numChildren; i++ )
		{
		arc.ArchiveShort( &Child[ i ].node );
		arc.ArchiveShort( &Child[ i ].moveCost );
		arc.ArchiveRaw( Child[ i ].maxheight, sizeof( Child[ i ].maxheight ) );
		arc.ArchiveInteger( &Child[ i ].door );
		}

   if ( arc.Loading() )
      {
      if ( !LoadingSavegame )
         {
         // Fixup the doors
         PostEvent( EV_Path_FindEntities, 0 );
         }
	   pathnodes[ nodenum ] = this;
	   if ( ai_maxnode < nodenum )
		   {
		   ai_maxnode = nodenum;
		   }
	   PathManager.AddNode( this );
      }
	}

void PathNode::FindEntities
   (
   Event *ev
   )

   {
   int i;
   Door *door;
   PathNode *node;

	for( i = 0; i < numChildren; i++ )
		{
      if ( Child[ i ].door )
         {
		   node = AI_GetNode( Child[ i ].node );

         assert( node );

         door = CheckDoor( node->origin );
         if ( door )
            {
            Child[ i ].door = door->entnum;
            }
         else
            {
            Child[ i ].door = 0;
            }
         }
		}
	}

void RestoreEnts
	(
	void
	)

	{
	int i;

	for( i = 0; i < NumIgnoreObjects; i++ )
		{
		IgnoreObjects[ i ]->link();
		}
	}

qboolean PathNode::TestMove
	(
   Entity *ent,
   Vector start,
   Vector end,
	Vector &min,
	Vector &max,
	qboolean allowdoors,
   qboolean fulltest
	)

	{
   // NOTE: TestMove may allow wide paths to succeed when they shouldn't since it
   // may place the lower node above obstacles that actors can't step over.
   // Since any path that's wide enough for large boxes must also allow
   // thinner boxes to go through, you must ignore the results of TestMove
   // when thinner checks have already failed.
	trace_t  trace;
	Vector   end_trace;
   Vector   pos;
   Vector   dir;
   float    t;
   float    dist;

   // By requiring that paths have STEPSIZE headroom above the path, we simplify the test
   // to see if an actor can move to a node down to a simple trace.  By stepping up the start
   // and end points, we account for the actor's ability to step up any geometry lower than
   // STEPSIZE in height.
   start.z += STEPSIZE;
   end.z += STEPSIZE;

   // Check the move
   trace = G_Trace( start, min, max, end, ent, MASK_PATHSOLID, false, "PathNode::TestMove 1" );
   if ( trace.startsolid || ( trace.fraction != 1 ) )
		{
      // No direct path available.  The actor will most likely not be able to move through here.
      return false;
		}

   if ( !fulltest )
      {
      // Since we're not doing a full test (full tests are only done when we're connecting nodes to save time),
      // we test to see if the midpoint of the move would only cause a change in height of STEPSIZE
      // from the predicted height.  This prevents most cases where a dropoff lies between a actor and a node.
	   Vector pos;

      // Since we start and end are already STEPSIZE above the ground, we have to check twice STEPSIZE below
      // the midpoint to see if the midpoint is on the ground.
      dir = end - start;
      pos = start + dir * 0.5;
	   end_trace = pos;
      end_trace.z -= STEPSIZE * 2;

	   // Check that the midpos is onground.  This may fail on ok moves, but a true test would be too slow
      // to do in real time.  Also, we may miss cases where a dropoff exists before or after the midpoint.
      // Once the actor is close enough to the drop off, it will discover the fall and hopefully try
      // another route.
	   trace = G_Trace( pos, min, max, end_trace, ent, MASK_PATHSOLID, false, "PathNode::TestMove 2" );
      if ( trace.startsolid || ( trace.fraction == 1 ) )
		   {
         // We're not on the ground, so there's a good posibility that we can't make this move without falling.
		   return false;
		   }
      }
   else //if ( !( contents & MASK_WATER ) )
      {
      // When we're creating the paths during load time, we do a much more exhaustive test to see if the
      // path is valid.  This test takes a bounding box and moves it 8 units at a time closer to the goal,
      // testing the ground after each move.  The test involves checking whether we will fall more than
      // STEPSIZE to the ground (since we've raised the start and end points STEPSIZE above the ground,
      // we must actually test 2 * STEPSIZE down to see if we're on the ground).  After each test, we set
      // the new height of the box to be STEPSIZE above the ground.  Each move closer to the goal is only
      // done horizontally to simulate how the actors normally move.  This method ensures that any actor
      // wider than 8 units in X and Y will be able to move from start to end.
      //
      // NOTE: This may allow wide paths to succeed when they shouldn't since it
      // may place the lower node above obstacles that actors can't step over.
      // Since any path that's wide enough for large boxes must also allow
      // thinner boxes to go through, you must ignore the results of TestMove
      // when thinner checks have already failed.

      dir = end - start;
	   dir.z = 0;
	   dist = dir.length();
      dir *= 1 / dist;

	   // check the entire move
	   pos = start;
	   for( t = 0; t < dist; t += 8 )
		   {
         // Move the box to our position along the path and make our downward trace vector
		   end_trace.x = pos.x = start.x + t * dir.x;
		   end_trace.y = pos.y = start.y + t * dir.y;
         end_trace.z = pos.z - STEPSIZE * 2;

         // check the ground
		   trace = G_Trace( pos, min, max, end_trace, ent, MASK_PATHSOLID, false, "PathNode::TestMove 3" );
		   if ( trace.startsolid || ( trace.fraction == 1 ) )
			   {
            // Either we're stuck in something solid, or we would fall farther than STEPSIZE to the ground,
            // so the path is not acceptable.
            return false;
			   }

         // move the box to STEPSIZE above the ground.
		   pos.z = trace.endpos[ 2 ] + STEPSIZE;
		   }
      }

   return true;
	}

qboolean PathNode::CheckMove
	(
   Entity *ent,
   Vector pos,
	Vector &min,
	Vector &max,
	qboolean allowdoors,
   qboolean fulltest
	)

   {
   // Since we need to support actors of variable widths, we need to do some special checks when a potential
   // path goes up or down stairs.  Placed pathnodes are only 16x16 in width, so when they are dropped to the
   // ground, they may end in a position where a larger box would not fit.  Making the pathnodes larger
   // would make it hard to place paths where smaller actors could go, and making paths of various sizes would
   // be overkill (more work for the level designer, or a lot of redundant data).  The solution is to treat
   // paths with verticle movement differently than paths that are purely horizontal.  For horizontal moves,
   // a simple trace STEPSIZE above the ground will be sufficient to prove that we can travel from one node
   // to another, in either direction.  For moves that have some change in height, we can check that we have
   // a clear path by tracing horizontally from the higher node to a point where larger bounding box actors
   // could then move at a slope downward to the lower node.  This fixes the problem where path points that
   // are larger than the depth of a step would have to intersect with the step in order to get the center
   // of the box on solid ground.  If you're still confused, well, tough. :)  Think about the problem of
   // larger bounding boxes going up stairs for a bit and you should see the problem.  You can also read
   // section 8.4, "Translating a Convex Polygon", from Computational Geometry in C (O'Rourke) (a f'ing
   // great book, BTW) for information on similar problems (which is also a good explanation of how
   // Quake's collision detection works).
   trace_t trace;
   int height;

   height = ( int )fabs( pos.z - origin.z );
   // Check if the path is strictly horizontal
   if ( !height )
      {
      // We do two traces for the strictly horizontal test.  One normal, and one STEPSIZE
      // above.  The normal trace is needed because most doors in the game aren't tall enough
      // to allow actors to trace STEPSIZE above the ground.  This means that failed horizontal
      // tests require two traces.  Annoying.
      trace = G_Trace( origin, min, max, pos, ent, MASK_PATHSOLID, false, "PathNode::CheckMove 1" );
      if ( !trace.startsolid && ( trace.fraction == 1 ) )
		   {
         return true;
		   }

      // Do the step test
      return TestMove( ent, pos, origin, min, max, allowdoors, fulltest );
      }

   Vector size;
   float  width;

   size = max - min;
   width = max( size.x, size.y );

   // if our bounding box is smaller than that of the pathnode, we can do the standard trace.
   if ( width <= 32 )
      {
      return TestMove( ent, pos, origin, min, max, allowdoors, fulltest );
      }

   Vector start;
   Vector end;
   Vector delta;
   float  radius;
   float  len;

   // We calculate the radius of the smallest cylinder that would contain the bounding box.
   // In some cases, this would make the first horizontal move longer than it needs to be, but
   // that shouldn't be a problem.

   // multiply the width by 1/2 the square root of 2 to get radius
   radius = width * 1.415 * 0.5;

   // Make sure that our starting position is the higher node since it doesn't matter which
   // direction the move is in.
   if ( pos.z < origin.z )
      {
      start = origin;
      end = pos;
      }
   else
      {
      start = pos;
      end = origin;
      }

   // If the distance between the two points is less than the radius of the bounding box,
   // then we only have to do the horizontal test since larger bounding boxes would not fall.
   delta = end - start;
   len = delta.length();
   if ( len <= radius )
      {
      end.z = start.z;
      return TestMove( ent, start, end, min, max, allowdoors, fulltest );
      }

   Vector mid;

   // normalize delta and multiply by radius (saving a few multiplies by combining into one).
   delta *= radius / len;

   mid = start;
   mid.x += delta.x;
   mid.y += delta.y;

   // Check the horizontal move
   if ( !TestMove( ent, start, mid, min, max, allowdoors, fulltest ) )
      {
      return false;
      }

   // Calculate our new endpoint
   end.z -= delta.z;

   // Check our new sloping move
   return TestMove( ent, mid, end, min, max, allowdoors, fulltest );
   }

Door *PathNode::CheckDoor
	(
	Vector pos
	)

	{
	trace_t	trace;
	Entity	*ent;

   trace = G_Trace( origin, vec_zero, vec_zero, pos, NULL, MASK_PATHSOLID, false, "PathNode::CheckDoor" );

   if ( trace.ent )
      {
	   ent = trace.ent->entity;
      }
   else
      {
      ent = NULL;
      }
	if ( ent && ent->isSubclassOf( Door ) )
		{
		return ( Door * )ent;
		}

	return NULL;
	}

qboolean PathNode::CheckMove
	(
	Vector pos,
	Vector min,
	Vector max
	)

	{
	return true;
	}

qboolean PathNode::CheckPath
	(
	PathNode *node,
	Vector min,
	Vector max,
   qboolean fulltest
	)

	{
	Vector	delta;
	qboolean allowdoors;
   qboolean result;

   delta = node->origin - origin;
	delta[ 2 ] = 0;
	if ( delta.length() >= PATHMAP_CELLSIZE )
		{
		return false;
		}

	allowdoors = ( nodeflags & AI_DOOR ) && ( node->nodeflags & AI_DOOR );

   result = CheckMove( NULL, node->origin, min, max, allowdoors, fulltest );
	RestoreEnts();

   return result;
	}

qboolean PathNode::ClearPathTo
	(
	PathNode *node,
	byte maxheight[ NUM_WIDTH_VALUES ],
   qboolean fulltest
	)

	{
	int      i;
	int      width;
   int      height;
   int      bottom;
   int      top;
	Vector   min;
	Vector   max;
   Vector   bmin;
   Vector   bmax;
	qboolean path;
   int      touch[ MAX_GENTITIES ];
   Entity   *ent;
   int      num;

	path = false;
	for( i = 0; i < NUM_WIDTH_VALUES; i++ )
		{
		maxheight[ i ] = 0;
      }

   width = NUM_WIDTH_VALUES * WIDTH_STEP * 0.5;
   min = Vector( -width, -width, 0 );
   max = Vector( width, width, MAX_HEIGHT );
   G_CalcBoundsOfMove( origin, node->origin, min, max, &bmin, &bmax );

   num = gi.AreaEntities( bmin, bmax, touch, MAX_GENTITIES );
   //num = gi.BoxEdicts( bmin, bmax, touch, MAX_GENTITIES, AREA_SOLID );
   for( i = 0; i < num; i++ )
      {
		ent = g_entities[ touch[ i ] ].entity;
		if ( ent && ent->isSubclassOf( Door ) )
         {
         ent->unlink();
         }
      }

	for( i = 0; i < NUM_WIDTH_VALUES; i++ )
		{
		width = ( i + 1 ) * WIDTH_STEP * 0.5;

		min.x = min.y = -width;
      max.x = max.y = width;

      // Perform a binary search to find the height of the path.  Neat, eh? :)
      bottom = 0;
      top = MAX_HEIGHT;
      while( top >= bottom )
         {
         height = ( ( bottom + top + 3 ) >> 1 ) & ~0x3;
         if ( !height )
            {
            break;
            }

			max.z = ( float )height;
			if ( !CheckPath( node, min, max, fulltest ) )
            {
            top = height - 4;
            }
         else
            {
            bottom = height + 4;
      	   maxheight[ i ] = height;
            }
         }

      if ( !maxheight[ i ] )
         {
         // If no paths were available at this width, don't allow any wider paths.
         // CheckPath uses TestMove which may allow wide paths to succeed when they
         // shouldn't since it may place the lower node above obstacles that actors
         // can't step over.  Since any path that's wide enough for large boxes must
         // also allow thinner boxes to go through, this check avoids the hole in
         // TestMove's functioning.
         break;
         }

      path = true;
      }

   // Restore the doors
   for( i = 0; i < num; i++ )
      {
		ent = g_entities[ touch[ i ] ].entity;
		if ( ent && ent->isSubclassOf( Door ) )
         {
         ent->link();
         }
      }

	return path;
	}

qboolean PathNode::LadderTo
	(
	PathNode *node,
	byte maxheight[ NUM_WIDTH_VALUES ]
	)

	{
	int i;
	int j;
	int m;
	int width;
	Vector min;
	Vector max;
	qboolean path;

	trace_t trace;

	if ( !( nodeflags & AI_LADDER ) || !( node->nodeflags & AI_LADDER ) )
		{
		return false;
		}

   if ( ( origin.x != node->origin.x ) || ( origin.y != node->origin.y ) )
		{
		return false;
		}

	path = false;

	for( i = 0; i < NUM_WIDTH_VALUES; i++ )
		{
		width = ( i + 1 ) * WIDTH_STEP * 0.5;
		min = Vector( -width, -width, 12 );
		max = Vector( width, width, 40 );

      trace = G_Trace( origin, min, max, node->origin, NULL, MASK_PATHSOLID, false, "PathNode::LadderTo 1" );
		if ( ( trace.fraction != 1 ) || trace.startsolid )
			{
			maxheight[ i ] = 0;
			continue;
			}

		path = true;

		m = 40;
		for( j = 48; j < MAX_HEIGHT; j+= 8 )
			{
			max.z = j;
         trace = G_Trace( origin, min, max, node->origin, NULL, MASK_PATHSOLID, false, "PathNode::LadderTo 2" );
			if ( ( trace.fraction != 1 ) || trace.startsolid )
				{
				break;
				}

			m = j;
			}

		maxheight[ i ] = m;
		}

	return path;
	}

qboolean PathNode::ConnectedTo
	(
	PathNode *node
	)

	{
	int i;

	for( i = 0; i < numChildren; i++ )
		{
		if ( Child[ i ].node == node->nodenum )
			{
			return true;
			}
		}

	return false;
	}

void PathNode::ConnectTo
	(
	PathNode *node,
	byte maxheight[ NUM_WIDTH_VALUES ],
	float cost,
	Door *door
	)

	{
	int i;

	if ( ( numChildren < NUM_PATHSPERNODE ) && ( node != this ) )
		{
		Child[ numChildren ].node = node->nodenum;
		for( i = 0; i < NUM_WIDTH_VALUES; i++ )
			{
			Child[ numChildren ].maxheight[ i ] = maxheight[ i ];
			}
		Child[ numChildren ].moveCost = ( int )cost;
		Child[ numChildren ].door = door ? door->entnum : 0;
		numChildren++;
		}
	else
		{
		warning( "ConnectTo", "Child overflow" );
		}
	}

void PathNode::ConnectTo
	(
	PathNode *node,
	byte maxheight[ NUM_WIDTH_VALUES ]
	)

	{
	Vector delta;
	Door *door;

   door = CheckDoor( node->origin );
   delta = node->origin - origin;
	ConnectTo( node, maxheight, delta.length(), door );
	}

void PathNode::Disconnect
	(
	PathNode *node
	)

	{
	int i;

	for( i = 0; i < numChildren; i++ )
		{
		if ( Child[ i ].node == node->nodenum )
			{
			break;
			}
		}

	// Should never happen, but let it slide after release
	assert( i != numChildren );
	if ( i == numChildren )
		{
		return;
		}

	numChildren--;

	// Since we're not worried about the order of the nodes, just
	// move the last node into the slot occupied by the removed node.
	Child[ i ] = Child[ numChildren ];
	Child[ numChildren ].node = 0;
	Child[ numChildren ].moveCost = 0;
	}

void PathNode::FindChildren
	(
	Event *ev
	)

	{
	trace_t	trace;
	Vector	end;
	Vector	start;

   pathnodescalculated = true;

   origin.x = ( ( int )( origin.x * 0.125 ) ) * 8;
   origin.y = ( ( int )( origin.y * 0.125 ) ) * 8;
   setOrigin( origin );

   //if ( !( contents & MASK_WATER ) )
      {
      start = origin + "0 0 1";
      end = origin;
	   end[ 2 ] -= 256;

	   trace = G_Trace( start, mins, maxs, end, NULL, MASK_PATHSOLID, false, "PathNode::FindChildren" );
	   if ( trace.fraction != 1 && !trace.allsolid )
		   {
		   setOrigin( trace.endpos );
		   }
      }

	PathManager.AddNode( this );
	}

void PathNode::DrawConnections
	(
	void
	)

	{
	int i;
	pathway_t *path;
	PathNode *node;

	for( i = 0; i < numChildren; i++ )
		{
		path = &Child[ i ];
		node = AI_GetNode( path->node );

      G_DebugLine( origin + "0 0 24", node->origin + "0 0 24", 0.7, 0.7, 0, 1 );
		}
	}

void DrawAllConnections
	(
	void
	)

	{
	int         i;
	pathway_t   *path;
	PathNode    *node;
	PathNode    *n;
   Vector      down;
   Vector      up;
   Vector      dir;
   Vector      p1;
   Vector      p2;
   Vector      p3;
   Vector      playerorigin;
   qboolean    showroutes;
   qboolean    shownums;
   qboolean    draw;
   int         maxheight;
   int         pathnum;

   showroutes = ( ai_showroutes->integer != 0 );
   shownums = ( ai_shownodenums->integer != 0 );

   if ( ai_showroutes->integer == 1 || ai_showroutes->integer == 0 )
      {
      pathnum = ( 32 / WIDTH_STEP ) - 1;
      }
   else
      {
      pathnum = ( ( ( int )ai_showroutes->integer ) / WIDTH_STEP ) - 1;
      }

   if ( ( pathnum < 0 ) || ( pathnum >= MAX_WIDTH ) )
      {
      gi.Printf( "ai_showroutes: Value out of range\n" );
      gi.cvar_set( "ai_showroutes", "0" );
      return;
      }

   // Figure out where the camera is
   
	if ( !g_entities[ 0 ].client )
		return;

   playerorigin.x = g_entities[ 0 ].client->ps.origin[ 0 ];
   playerorigin.y = g_entities[ 0 ].client->ps.origin[ 1 ];
   playerorigin.z = g_entities[ 0 ].client->ps.origin[ 2 ];
   
   playerorigin[ 2 ] += g_entities[ 0 ].client->ps.viewheight;

	for( node = NodeList; node != NULL; node = node->chain )
		{
      /* if ( !gi.inPVS( playerorigin, node->origin ) )
			{
			continue;
			} */

		if ( Vector( node->origin - playerorigin ).length() > ai_showroutes_distance->integer )
			{
			continue;
			}

      if ( shownums )
         {
         G_DrawDebugNumber( node->origin + Vector( 0, 0, 14 ), node->nodenum, 1.5, 1, 1, 0 );
         }

      draw = false;
		for( i = 0; i < node->numChildren; i++ )
			{
			path = &node->Child[ i ];
			n = AI_GetNode( path->node );

			maxheight = path->maxheight[ pathnum ];
         if ( maxheight == 0 )
            {
            continue;
            }

         draw = true;

			if ( !showroutes )
            {
            continue;
            }

         // don't draw the path if it's already been drawn by the destination node
         if ( n->drawtime < level.time || !n->ConnectedTo( node ) )
            {
            down.z = 2;
            up.z = maxheight;

				if ( n->nodeflags & AI_JUMP && node->nodeflags & AI_JUMP )
					{
					// These are jump nodes draw, them in blue instead of green
					G_DebugLine( node->origin + down, n->origin + down,     0, 0, 1, 1 );
					G_DebugLine( n->origin + down,    n->origin + up,       0, 0, 1, 1 );
					G_DebugLine( node->origin + up,   n->origin + up,       0, 0, 1, 1 );
					G_DebugLine( node->origin + up,   node->origin + down,  0, 0, 1, 1 );
					}
				else
					{
					G_DebugLine( node->origin + down, n->origin + down,     0, 1, 0, 1 );
					G_DebugLine( n->origin + down,    n->origin + up,       0, 1, 0, 1 );
					G_DebugLine( node->origin + up,   n->origin + up,       0, 1, 0, 1 );
					G_DebugLine( node->origin + up,   node->origin + down,  0, 1, 0, 1 );
					}
            }

         // draw an arrow for the direction
         dir.x = n->origin.x - node->origin.x;
         dir.y = n->origin.y - node->origin.y;
         dir.normalize();

         p1 = node->origin;
         p1.z += maxheight * 0.5;
         p2 = dir * 8;
         p3 = p1 + p2 * 2;

         G_DebugLine( p1, p3, 0, 1, 0, 1 );

         p2.z += 8;
         G_DebugLine( p3, p3 - p2, 0, 1, 0, 1 );

         p2.z -= 16;
         G_DebugLine( p3, p3 - p2, 0, 1, 0, 1 );
			}

      if ( !draw )
         {
         // Put a little X where the node is to show that it had no connections
         p1 = node->origin;
         p1.z += 2;

         p2 = Vector( 12, 12, 0 );
         G_DebugLine( p1 - p2, p1 + p2, 1, 0, 0, 1 );

         p2.x = -12;
         G_DebugLine( p1 - p2, p1 + p2, 1, 0, 0, 1 );
         }

		node->drawtime = level.time;
		}
	}

MapCell::MapCell()
	{
	Init();
	}

MapCell::~MapCell()
	{
	Init();
	}

void MapCell::Init
	(
	void
	)

	{
	numnodes = 0;
	memset( nodes, 0, sizeof( nodes ) );
	}

qboolean MapCell::AddNode
	(
	PathNode *node
	)

	{
	if ( numnodes >= PATHMAP_NODES )
		{
		return false;
		}

	nodes[ numnodes ] = ( short )node->nodenum;
	numnodes++;

	return true;
	}

qboolean MapCell::RemoveNode
	(
	PathNode *node
	)

	{
	int i;
	int num;

	num = node->nodenum;
	for( i = 0; i < numnodes; i++ )
		{
		if ( num == ( int )nodes[ i ] )
			{
			break;
			}
		}

	if ( i >= numnodes )
		{
		return false;
		}

	numnodes--;

	// Since we're not worried about the order of the nodes, just
	// move the last node into the slot occupied by the removed node.
	nodes[ i ] = nodes[ numnodes ];
	nodes[ numnodes ] = 0;

	return true;
	}

PathNode *MapCell::GetNode
	(
	int index
	)

	{
	assert( index >= 0 );
	assert( index < numnodes );
	if ( index >= numnodes )
		{
		return NULL;
		}

	return AI_GetNode( nodes[ index ] );
	}

int MapCell::NumNodes
	(
	void
	)

	{
	return numnodes;
	}

/*                         All
                     work and no play
                 makes Jim a dull boy. All
               work and no  play makes Jim a
             dull boy. All  work and no  play
           makes Jim a dull boy. All work and no
         play makes Jim a dull  boy. All work and
        no play makes Jim a dull boy. All work and
       no play makes Jim a dull boy. All work and no
      play makes Jim a dull boy. All work and no play
     makes Jim a dull boy. All work and no play makes
    Jim a dull boy.  All work and no  play makes Jim a
   dull boy. All work and no play makes Jim a dull boy.
   All work and no play makes  Jim a dull boy. All work
  and no play makes Jim a dull boy. All work and no play
  makes Jim a dull boy. All work and no play makes Jim a
 dull boy. All work and no play makes Jim a dull boy. All
 work and no play makes  Jim a dull boy. All  work and no
 play makes Jim a dull boy. All work and no play makes Jim
 a dull boy. All work  and no play makes Jim  a dull boy.
 All work and no play makes Jim  a dull boy. All work and
 no play makes Jim a dull boy. All work and no play makes
 Jim a dull boy.  All work and no  play makes Jim a  dull
 boy. All work and no play makes Jim a dull boy. All work
 and no play makes Jim  a dull boy. All work  and no play
 makes Jim a dull boy.  All work and no play  makes Jim a
 dull boy. All work and no play makes Jim a dull boy. All
  work and no play makes Jim a dull boy. All work and no
  play makes Jim a dull boy.  All work and no play makes
   Jim a dull boy. All work and no play makes Jim a dull
   boy. All work and no play  makes Jim a dull boy. All
    work and no play makes Jim a dull boy. All work and
     no play makes  Jim a dull  boy. All work  and no
      play makes Jim a dull boy. All work and no play
       makes Jim a dull  boy. All work and  no play
        makes Jim a dull boy. All work and no play
         makes Jim a  dull boy. All  work and no
           play makes Jim a  dull boy. All work
             and no play makes Jim a dull boy.
               All work  and no  play makes
                 Jim a dull boy. All work
                     and no play makes
                          Jim  a
*/

CLASS_DECLARATION( Class, PathSearch, NULL )
	{
		{ &EV_AI_SavePaths,				SavePathsEvent },
		{ &EV_AI_LoadNodes,				LoadNodes },
		{ &EV_AI_SaveNodes,				SaveNodes },
		{ &EV_AI_ClearNodes,				ClearNodes },
      { &EV_AI_SetNodeFlags,        SetNodeFlagsEvent },
      { &EV_AI_RecalcPaths,         RecalcPathsEvent },
      { &EV_AI_CalcPath,            CalcPathEvent },
      { &EV_AI_DisconnectPath,      DisconnectPathEvent },

		{ NULL, NULL }
	};


PathSearch::PathSearch()
	{
   AI_ResetNodes();
   }

PathSearch::~PathSearch()
	{
   AI_ResetNodes();
   }

void PathSearch::AddToGrid
	(
	PathNode *node,
	int x,
	int y
	)

	{
	PathNode *node2;
	MapCell *cell;
	int numnodes;
	int i;
	int j;
	byte maxheight[ NUM_WIDTH_VALUES ];

	cell = GetNodesInCell( x, y );
	if ( !cell )
		{
		return;
		}

	if ( !cell->AddNode( node ) )
		{
		warning( "AddToGrid", "Node overflow at ( %d, %d )\n", x, y );
		return;
		}

	if ( !loadingarchive )
		{
      //
      // explicitly link up the targets and their destinations
      //
      if ( node->nodeflags & AI_JUMP )
         {
         if ( node->target.length() > 1 )
            {
            node2 = AI_FindNode( node->target.c_str() );
            if ( node2 && !node->ConnectedTo( node2 ) )
               {
				   for( j = 0; j < NUM_WIDTH_VALUES; j++ )
					   {
					   maxheight[ j ] = MAX_HEIGHT;
					   }

					if ( node != node2 )
						node->ConnectTo( node2, maxheight );
					else
						gi.DPrintf( "Can't connect pathnode to itself (%s)", node->target.c_str() );
               }
            }
         }

		// Connect the node to its neighbors
		numnodes = cell->NumNodes();
		for( i = 0; i < numnodes; i++ )
			{
			node2 = ( PathNode * )cell->GetNode( i );
			if ( node2 == node )
				{
				continue;
				}

			if ( ( node->numChildren < NUM_PATHSPERNODE ) && !node->ConnectedTo( node2 ) )
            {
            if ( node->ClearPathTo( node2, maxheight ) || node->LadderTo( node2, maxheight ) )
				   {
				   node->ConnectTo( node2, maxheight );
				   }
            }

			if ( ( node2->numChildren < NUM_PATHSPERNODE ) && !node2->ConnectedTo( node ) )
            {
				if ( node2->ClearPathTo( node, maxheight ) || node2->LadderTo( node, maxheight ) )
				   {
				   node2->ConnectTo( node, maxheight );
				   }
            }
			}
		}
	}

qboolean PathSearch::RemoveFromGrid
	(
	PathNode *node,
	int x,
	int y
	)

	{
	MapCell	*cell;
	PathNode *node2;
	int		numnodes;
	int		i;

	cell = GetNodesInCell( x, y );
	if ( !cell || !cell->RemoveNode( node ) )
		{
		return false;
		}

	// Disconnect the node from all nodes in the cell
	numnodes = cell->NumNodes();
	for( i = 0; i < numnodes; i++ )
		{
		node2 = ( PathNode * )cell->GetNode( i );
		if ( node2->ConnectedTo( node ) )
			{
			node2->Disconnect( node );
			}
		}

	return true;
	}

int PathSearch::NodeCoordinate
	(
	float coord
	)

	{
	return ( ( int )coord + MAX_MAP_BOUNDS - ( PATHMAP_CELLSIZE / 2 ) ) / PATHMAP_CELLSIZE;
	}

int PathSearch::GridCoordinate
	(
	float coord
	)

	{
	return ( ( int )coord + MAX_MAP_BOUNDS ) / PATHMAP_CELLSIZE;
	}

void PathSearch::AddNode
	(
	PathNode *node
	)

	{
	int x;
	int y;

	assert( node );

   if ( !loadingarchive )
      {
      gi.DPrintf( "." );
      }

	numNodes++;

	if ( NodeList == NULL )
		{
		NodeList = node;
		node->chain = NULL;
		}
	else
		{
		node->chain = NodeList;
		NodeList = node;
		}

   x = NodeCoordinate( node->origin[ 0 ] );
   y = NodeCoordinate( node->origin[ 1 ] );

	AddToGrid( node, x, y );
	AddToGrid( node, x + 1, y );
	AddToGrid( node, x,	y + 1 );
	AddToGrid( node, x + 1, y + 1 );

	node->gridX = x;
	node->gridY = y;
	}

void PathSearch::RemoveNode
	(
	PathNode *node
	)

	{
	int x;
	int y;
	PathNode *n;
	PathNode *p;

	assert( node );

	x = node->gridX;
	y = node->gridY;

	RemoveFromGrid( node, x, y );
	RemoveFromGrid( node, x + 1, y );
	RemoveFromGrid( node, x, y + 1 );
	RemoveFromGrid( node, x + 1, y + 1 );

	p = NULL;
	for( n = NodeList; n != node; p = n, n = n->chain )
		{
		if ( !n )
			{
			// Not in list.
			return;
			}
		}

	if ( p )
		{
		p->chain = n->chain;
		}
	else
		{
		NodeList = n->chain;
		}

	n->chain = NULL;
	numNodes--;
	}

void PathSearch::UpdateNode
	(
	PathNode *node
	)

	{
	int x;
	int y;
	int mx;
	int my;

	assert( node );

   x = NodeCoordinate( node->origin[ 0 ] );
   y = NodeCoordinate( node->origin[ 1 ] );

	mx = node->gridX;
	my = node->gridY;

	RemoveFromGrid( node, mx, my );
	RemoveFromGrid( node, mx + 1, my );
	RemoveFromGrid( node, mx, my + 1 );
	RemoveFromGrid( node, mx + 1, my + 1 );

	node->numChildren = 0;

	AddToGrid( node, x, y );
	AddToGrid( node, x + 1, y );
	AddToGrid( node, x,	y + 1 );
	AddToGrid( node, x + 1, y + 1 );

	node->gridX = x;
	node->gridY = y;
	}

MapCell *PathSearch::GetNodesInCell
	(
	int x,
	int y
	)

	{
	if ( ( x < 0 ) || ( x >= PATHMAP_GRIDSIZE ) || ( y < 0 ) || ( y >= PATHMAP_GRIDSIZE ) )
		{
		return NULL;
		}

	return &PathMap[ x ][ y ];
	}

MapCell *PathSearch::GetNodesInCell
	(
	Vector pos
	)

	{
	int x;
	int y;

	x = GridCoordinate( pos[ 0 ] );
	y = GridCoordinate( pos[ 1 ] );

	return GetNodesInCell( x, y );
	}

PathNode *PathSearch::NearestNode
	(
	Vector pos,
   Entity *ent,
   qboolean usebbox
	)

	{
	Vector	delta;
	PathNode	*node;
	PathNode	*bestnode;
	float		bestdist;
	float		dist;
	int		n;
	int		i;
	MapCell	*cell;
	Vector	min;
	Vector	max;

	cell = GetNodesInCell( pos );
	if ( !cell )
		{
		return NULL;
		}

   if ( ent && usebbox )
      {
   	min = ent->mins;
      max = ent->maxs;
      }
   else
      {
   	min = Vector( -16, -16, 12 );
   	max = Vector( 16, 16, 40 );
      }

	n = cell->NumNodes();

   if ( ai_debugpath->integer )
		{
      gi.DPrintf( "NearestNode: Checking %d nodes\n", n );
		}

	bestnode = NULL;
	bestdist = 999999999; // greater than ( 8192 * sqr(2) ) ^ 2 -- maximum squared distance
	for( i = 0; i < n; i++ )
		{
		node = ( PathNode * )cell->GetNode( i );
		if ( !node )
			{
			continue;
			}

      delta = node->origin - pos;

		// get the distance squared (faster than getting real distance)
		dist = delta * delta;
      if ( ( dist < bestdist ) && node->CheckMove( ent, pos, min, max, false, false ) )
			{
			bestnode = node;
			bestdist = dist;

         // if we're close enough, early exit
         if ( dist < 16 )
            {
            break;
            }
			}
		}

	return bestnode;
	}

void PathSearch::Teleport
	(
	Entity *teleportee,
	Vector from,
	Vector to
	)

	{
	PathNode	*node1;
	PathNode	*node2;
	byte maxheight[ NUM_WIDTH_VALUES ];
	int j;

   if ( ai_createnodes->integer )
		{
		node1 = new PathNode;
		node1->Setup( from );

		node2 = new PathNode;
		node2->Setup( to );

		// FIXME
		// shouldn't hard-code width and height
		for( j = 0; j < NUM_WIDTH_VALUES; j++ )
			{
			maxheight[ j ] = 72;
			}

		// connect with 0 cost
		node1->ConnectTo( node2, maxheight, 0 );
		}
	}

void PathSearch::ShowNodes
	(
	void
	)

	{
   if ( ai_showroutes->integer || ai_shownodenums->integer )
		{
		DrawAllConnections();
		}
	}

int PathSearch::NumNodes
	(
	void
	)

	{
	return numNodes;
	}

int PathSearch::NumLoadNodes
	(
	void
	)

	{
	return numLoadNodes;
	}

void PathSearch::Checksum
	(
   Vector &checksum
	)

	{
   checksum = pathNodesChecksum;
	}

void PathSearch::Archive
	(
	Archiver &arc
	)

	{
	int i;
	int num;

   if ( arc.Saving() )
      {
   	PathNode *node;

	   num = 0;
	   for( i = 0; i < MAX_PATHNODES; i++ )
		   {
		   node = AI_GetNode( i );
		   if ( node )
			   {
			   num++;
			   }
		   }
      arc.ArchiveInteger( &num );
	   for( i = 0; i < MAX_PATHNODES; i++ )
		   {
		   node = AI_GetNode( i );
		   if ( node )
			   {
			   arc.ArchiveObject( node );
			   }
		   }

      if ( ai_debuginfo->integer )
		   {
         gi.DPrintf( "Wrote %d path nodes\n", num );
		   }
      }
   else
      {
      int x;
      int y;

	   numNodes = 0;
	   NodeList = NULL;
	   loadingarchive = true;

	   // Get rid of the nodes that were spawned by the map
	   AI_ResetNodes();

      // Init the grid
	   for( x = 0; x < PATHMAP_GRIDSIZE; x++ )
		   {
		   for( y = 0; y < PATHMAP_GRIDSIZE; y++ )
			   {
			   PathMap[ x ][ y ].Init();
			   }
		   }

	   arc.ArchiveInteger( &num );

	   assert( num <= MAX_PATHNODES );
	   if ( num > MAX_PATHNODES )
		   {
		   arc.FileError( "Exceeded max path nodes" );
		   }

	   for( i = 0; i < num; i++ )
		   {
		   arc.ReadObject();
		   }

      if ( ai_debuginfo && ai_debuginfo->integer )
		   {
         gi.DPrintf( "Path nodes loaded: %d\n", NumNodes() );
		   }

      loadingarchive = false;
      }
	}

void PathSearch::ClearNodes
	(
	Event *ev
	)

	{
	PathNode *node;
	int i;
	int num;

	num = 0;
	for( i = 0; i < MAX_PATHNODES; i++ )
		{
		node = AI_GetNode( i );
		if ( node )
			{
			node->PostEvent( EV_Remove, 0 );
			num++;
			}
		}

   if ( ai_debuginfo->integer )
		{
      gi.DPrintf( "Deleted %d path nodes\n", num );
		}
	}

void PathSearch::SetNodeFlagsEvent
	(
	Event *ev
	)

	{
   const char * token;
   int i, argnum;
   int mask;
   int action;
   int nodenum;
   PathNode *node;

   nodenum = ev->GetInteger( 1 );
   node = AI_GetNode( nodenum );

   if ( !node )
      {
      ev->Error( "Node not found." );
      return;
      }

   argnum = 2;
   for ( i = argnum; i <= ev->NumArgs() ; i++ )
      {
      token = ev->GetString( i );
      action = 0;
      switch( token[0] )
         {
         case '+':
            action = FLAG_ADD;
            token++;
            break;
         case '-':
            action = FLAG_CLEAR;
            token++;
            break;
         default:
            ev->Error( "PathSearch::SetNodeFlagsEvent", "First character is not '+' or '-', assuming '+'\n" );
            action = FLAG_ADD;
            break;
            break;
         }

      if (!strcmpi( token, "flee"))
         {
         mask = AI_FLEE;
         }
      else if (!strcmpi (token, "duck"))
         {
         mask = AI_DUCK;
         }
      else if (!strcmpi (token, "cover"))
         {
         mask = AI_COVER;
         }
      else if (!strcmpi (token, "door"))
         {
         mask = AI_DOOR;
         }
      else if (!strcmpi (token, "jump"))
         {
         mask = AI_JUMP;
         }
      else if (!strcmpi (token, "ladder"))
         {
         mask = AI_LADDER;
         }
      else if (!strcmpi (token, "action"))
         {
         mask = AI_ACTION;
         }
      else
         {
         mask = 0;
         action = FLAG_IGNORE;
         ev->Error( "Unknown token %s.", token );
         }

      switch (action)
         {
         case FLAG_ADD:
            node->nodeflags |= mask;
            break;

         case FLAG_CLEAR:
            node->nodeflags &= ~mask;
            break;

         case FLAG_IGNORE:
            break;
         }
      }
	}

void PathSearch::CalcPathEvent
	(
	Event *ev
	)

	{
   int nodenum;
   PathNode *node;
   PathNode *node2;
   int j;
	byte maxheight[ NUM_WIDTH_VALUES ];

   nodenum = ev->GetInteger( 1 );
   node = AI_GetNode( nodenum );

   nodenum = ev->GetInteger( 2 );
   node2 = AI_GetNode( nodenum );

   if ( !node || !node2 )
      {
      ev->Error( "Node not found." );
      return;
      }

   if ( ( node->numChildren < NUM_PATHSPERNODE ) && !node->ConnectedTo( node2 ) )
      {
      if ( node->ClearPathTo( node2, maxheight, false ) || node->LadderTo( node2, maxheight ) )
			{
			node->ConnectTo( node2, maxheight );
			}
		else if ( ( node->nodeflags & AI_JUMP ) && ( node->target == node2->targetname ) )
			{
			//FIXME
			// don't hardcode size
			for( j = 0; j < NUM_WIDTH_VALUES; j++ )
				{
				maxheight[ j ] = MAX_HEIGHT;
				}
			node->ConnectTo( node2, maxheight );
			}
      }

	if ( ( node2->numChildren < NUM_PATHSPERNODE ) && !node2->ConnectedTo( node ) )
      {
		if ( node2->ClearPathTo( node, maxheight, false ) || node2->LadderTo( node, maxheight ) )
			{
			node2->ConnectTo( node, maxheight );
			}
      else if ( ( node2->nodeflags & AI_JUMP ) && ( node2->target == node->targetname ) )
			{
			//FIXME
			// don't hardcode size
			for( j = 0; j < NUM_WIDTH_VALUES; j++ )
				{
				maxheight[ j ] = MAX_HEIGHT;
				}
			node2->ConnectTo( node, maxheight );
			}
      }
	}

void PathSearch::DisconnectPathEvent
	(
	Event *ev
	)

	{
   int nodenum;
   PathNode *node;
   PathNode *node2;

   nodenum = ev->GetInteger( 1 );
   node = AI_GetNode( nodenum );

   nodenum = ev->GetInteger( 2 );
   node2 = AI_GetNode( nodenum );

   if ( !node || !node2 )
      {
      ev->Error( "Node not found." );
      return;
      }

	if ( node->ConnectedTo( node2 ) )
		{
		node->Disconnect( node2 );
		}

   if ( node2->ConnectedTo( node ) )
		{
		node2->Disconnect( node );
		}
	}

void PathSearch::RecalcPathsEvent
	(
	Event *ev
	)

	{
   int nodenum;
   PathNode *node;

   nodenum = ev->GetInteger( 1 );
   node = AI_GetNode( nodenum );
   if ( node )
      {
      UpdateNode( node );
      }
   else
      {
      ev->Error( "Node not found." );
      }
   }

qboolean PathSearch::ArchiveNodes
	(
   str name,
   qboolean save
	)

	{
	Archiver arc;
   qboolean success;

   if ( save )
      {
      Vector   checksum;
      int      tempInt;

	   arc.Create( name );
      tempInt = PATHFILE_VERSION;
	   arc.ArchiveInteger( &tempInt );
      tempInt = NumNodes();
	   arc.ArchiveInteger( &tempInt );
      Checksum( checksum );
	   arc.ArchiveVector( &checksum );
   	arc.ArchiveObject( this );
      success = qtrue;
      }
   else
      {
   	int		version;

      success = qfalse;
   	arc.Read( name, qfalse );
	   arc.ArchiveInteger( &version );
	   if ( version == PATHFILE_VERSION )
		   {
         int numnodes, file_numnodes;
         Vector checksum, file_checksum;

         // get current values
         numnodes = NumLoadNodes();
         Checksum( checksum );

         // get file values
         arc.ArchiveInteger( &file_numnodes );
         arc.ArchiveVector( &file_checksum );
         if (
               ( numnodes == file_numnodes ) &&
               ( checksum == file_checksum )
            )
            {
		      arc.ArchiveObject( this );
            if ( arc.NoErrors() )
               {
               success = qtrue;
               }
            }
         else
            {
            gi.Printf( "Pathnodes have changed, rebuilding.\n" );
            }
         }
      else
         {
         gi.Printf( "Expecting version %d path file.  Path file is version %d.", PATHFILE_VERSION, version );
         }

      }
	arc.Close();
   return success;
	}

void PathSearch::SaveNodes
	(
	Event *ev
	)

	{
	str name;

	if ( ev->NumArgs() != 1 )
		{
      gi.Printf( "Usage: ai_save [filename]\n" );
		return;
		}

	name = ev->GetString( 1 );

   gi.Printf( "Archiving\n" );

   ArchiveNodes( name, qtrue );

   gi.Printf( "done.\n" );
   pathnodescalculated = false;
	}

void PathSearch::LoadNodes
	(
	Event *ev
	)

	{
	Archiver arc;
	str		name;
   bool     rebuild;

	if ( ev->NumArgs() != 1 )
		{
      gi.Printf( "Usage: ai_load [filename]\n" );
		return;
		}

   gi.Printf( "Loading nodes...\n" );

	name = ev->GetString( 1 );

   rebuild = !ArchiveNodes( name, qfalse );

   if ( rebuild )
		{
		// Only replace the file if this event was called from our init function (as opposed to the user
		// calling us from the console) 
		if ( ( ev->GetSource() == EV_FROM_CODE ) )
			{
         gi.Printf( "Replacing file.\n\n" );

			// At this point, the nodes are still scheduled to find their neighbors, because we posted this event
			// before we the nodes were spawned.  Post the event with 0 delay so that it gets processed after all
			// the nodes find their neighbors.
			PostEvent( EV_AI_SavePaths, 0 );
			}
		else
			{
			// otherwise, just let them know that the path file needs to be replaced.
         gi.Printf( "Type 'ai_savepaths' at the console to replace the current path file.\n" );
			}

      // Print out something fairly obvious
      gi.DPrintf( "***********************************\n"
                  "***********************************\n"
                  "\n"
                  "Creating paths...\n"
                  "\n"
                  "***********************************\n"
                  "***********************************\n" );
		}
	}

void PathSearch::SavePaths
	(
	void
	)

	{
	str filename;
	Event *ev;

	if ( loadingarchive )
		{
		// force it to zero since we probably had an error
		gi.cvar_set( "ai_createnodes", "0" );
		}

   if ( 
         !loadingarchive && 
         (
            ( ai_createnodes && ai_createnodes->integer ) ||
            ( pathnodescalculated )
         )
      )
		{
		filename = "maps/";
		filename += level.mapname;
		filename += ".pth";

      gi.DPrintf( "\nSaving path nodes to '%s'\n", filename.c_str() );

		ev = new Event( EV_AI_SaveNodes );
		ev->AddString( filename );
		ProcessEvent( ev );
		}
	}

void PathSearch::SavePathsEvent
	(
	Event *ev
	)

	{
	str temp;

	temp = ai_createnodes->string;
	gi.cvar_set( "ai_createnodes", "1" );

	SavePaths();

	gi.cvar_set( "ai_createnodes", temp.c_str() );
	}

void PathSearch::Init
	(
	const char *mapname
	)

	{
	int x;
	int y;
	str filename;
	Event *ev;

   pathNodesChecksum = vec_zero;
   pathnodescalculated = false;

	gi.AddCommand( "ai_savepaths" );
	gi.AddCommand( "ai_save" );
	gi.AddCommand( "ai_load" );
	gi.AddCommand( "ai_clearnodes" );
	gi.AddCommand( "ai_recalcpaths" );
	ai_createnodes		= gi.cvar ("ai_createnodes", "0", 0);
	ai_debugpath		= gi.cvar ("ai_debugpath", "0", 0);
	ai_debuginfo		= gi.cvar ("ai_debuginfo", "0", 0);
	ai_showroutes		= gi.cvar ("ai_showroutes", "0", 0);
	ai_showroutes_distance = gi.cvar ("ai_showroutes_distance", "1000", 0);
   ai_shownodenums   = gi.cvar ("ai_shownodenums", "0", 0);
   ai_timepaths      = gi.cvar ("ai_timepaths", "0", 0);

   numLoadNodes = 0;
	numNodes = 0;
	NodeList = NULL;
	loadingarchive = false;

	// Get rid of the nodes that were spawned by the map
	AI_ResetNodes();

   // Init the grid
	for( x = 0; x < PATHMAP_GRIDSIZE; x++ )
		{
		for( y = 0; y < PATHMAP_GRIDSIZE; y++ )
			{
			PathMap[ x ][ y ].Init();
			}
		}

   if ( LoadingSavegame )
      {
      // no need to go further here 
      return;
      }

   if ( mapname )
      {
      filename = "maps/";
	   filename += mapname;
	   filename += ".pth";
      if ( gi.FS_ReadFile( filename.c_str(), NULL, qtrue ) != -1 )
         {
		   ev = new Event( EV_AI_LoadNodes );
		   ev->AddString( filename );

		   // This can't happen until the world is spawned
		   PostEvent( ev, 0 );
         }
      else
         {
         // Print out something fairly obvious
         gi.DPrintf( "***********************************\n"
                     "***********************************\n"
                     "\n"
                     "No paths found.  Creating paths...\n"
                     "\n"
                     "***********************************\n"
                     "***********************************\n" );
         }
      }
   }


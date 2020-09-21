//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/navigate.h                         $
// $Revision:: 14                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/25/00 11:32p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/navigate.h                              $
// 
// 14    7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 13    6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 12    5/25/00 4:27p Markd
// rewrote archive functions
// 
// 11    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 10    3/17/00 11:53a Steven
// Added jumping stuff.
// 
// 9     3/06/00 8:12p Markd
// removed unused cvar
// 
// 8     2/04/00 1:29p Markd
// Added checksum to ai path nodes. It auto saves on exit now and will
// automatically re-build nodes as needed
// 
// 7     2/04/00 11:18a Markd
// Fixed memory leak with AI_PathNodes
// 
// 6     1/25/00 6:33p Steven
// Fixed some path node stuff.
// 
// 5     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 4     10/01/99 6:31p Markd
// added commands hidden inside fgame so that they would show up for command
// completion
// 
// 3     10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 2     9/28/99 5:15p Markd
// Fixed more merge bugs with sharing class, vector and listener between three
// modules
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 9     7/07/99 11:26a Steven
// Added some stuff on the sector pathfinding approach.
//
// DESCRIPTION:
// Potentially could be an C++ implementation of the A* search algorithm, but
// is currently unfinished.
//

#ifndef __NAVIGATE_H__
#define __NAVIGATE_H__

#include "g_local.h"
#include "class.h"
#include "entity.h"
#include "stack.h"
#include "container.h"
#include "doors.h"
#include "../qcommon/qfiles.h"


extern Event EV_AI_SavePaths;
extern Event EV_AI_SaveNodes;
extern Event EV_AI_LoadNodes;
extern Event EV_AI_ClearNodes;
extern Event EV_AI_RecalcPaths;
extern Event EV_AI_CalcPath;
extern Event EV_AI_DisconnectPath;

extern cvar_t	*ai_createnodes;
extern cvar_t	*ai_shownodes;
extern cvar_t	*ai_debugpath;
extern cvar_t	*ai_debuginfo;
extern cvar_t	*ai_showroutes;
extern cvar_t  *ai_timepaths;

extern int		ai_maxnode;

#define MAX_PATHCHECKSPERFRAME 4

extern int path_checksthisframe;

#define MAX_PATH_LENGTH		128		// should be more than plenty
#define NUM_PATHSPERNODE	16

class Path;
class PathNode;

#define NUM_WIDTH_VALUES	16
#define WIDTH_STEP			8
#define MAX_WIDTH				( WIDTH_STEP * NUM_WIDTH_VALUES )
#define MAX_HEIGHT			128

#define CHECK_PATH( path, width, height ) \
	( ( ( ( width ) >= MAX_WIDTH ) || ( ( width ) < 0 ) ) ? false : \
	( ( int )( path )->maxheight[ ( ( width ) / WIDTH_STEP ) - 1 ] < ( int )( height ) ) )

typedef struct
	{
	short			node;
	short			moveCost;
	byte			maxheight[ NUM_WIDTH_VALUES ];
	int			door;
	} pathway_t;

typedef enum { NOT_IN_LIST, IN_OPEN, IN_CLOSED } pathlist_t;

#define AI_FLEE		1
#define AI_DUCK		2
#define AI_COVER		4
#define AI_DOOR		8
#define AI_JUMP		16
#define AI_LADDER		32
#define AI_ACTION    64

void DrawAllConnections( void );

class PathNode : public Listener
	{
	public:
		PathNode			*chain;
		pathway_t		Child[ NUM_PATHSPERNODE ];	// these are the real connections between nodex
		int				numChildren;

		// These variables are all used during the search
		int				f;
		int				h;
		int				g;

		int				gridX;
		int				gridY;

		float				drawtime;
		float				occupiedTime;
		int				entnum;

		pathlist_t		inlist;

		// reject is used to indicate that a node is unfit for ending on during a search
		qboolean			reject;

		PathNode			*Parent;

		// For the open and closed lists
		PathNode			*NextNode;

		int				nodeflags;

		friend class   PathSearch;
		friend void		DrawAllConnections( void );

	private :
      qboolean       TestMove( Entity *ent, Vector start, Vector end, Vector &min, Vector &max, qboolean allowdoors = false, qboolean fulltest = false );

		qboolean			ConnectedTo( PathNode *node );
		void				ConnectTo( PathNode *node, byte maxheight[ NUM_WIDTH_VALUES ], float cost, Door *door = NULL );
		void				ConnectTo( PathNode *node, byte maxheight[ NUM_WIDTH_VALUES ] );
		void				Disconnect( PathNode *node );

		void				FindChildren( Event *ev );
      void           FindEntities( Event *ev );
      void           SetNodeFlags( Event *ev );
      void           SetOriginEvent( Event *ev );
      void           SetAngle( Event *ev );
      void           SetAngles( Event *ev );
      void           SetAnim( Event *ev );
      void           SetTargetname( Event *ev );
      void           SetTarget( Event *ev );

	public:
      CLASS_PROTOTYPE( PathNode );

      int            contents;
      Vector         origin;
      Vector         angles;
		Vector			mins;
		Vector			maxs;
		str				targetname;
		str				target;

		int				nodenum;

		qboolean			setangles;
		str				animname;

							PathNode();
							~PathNode();

		void				Setup( Vector pos );
		void				setAngles( Vector ang );
		void				setOrigin( Vector org );
		void				setSize( Vector min, Vector max );
		str				&TargetName( void );
		virtual void	Archive( Archiver &arc );

		qboolean			CheckPath( PathNode *node, Vector min, Vector max, qboolean fulltest = true );
		Door				*CheckDoor( Vector pos );

      qboolean       CheckMove( Entity *ent, Vector pos, Vector &min, Vector &max, qboolean allowdoors = false, qboolean fulltest = false );
		qboolean			CheckMove( Vector pos, Vector min, Vector max );
		qboolean			ClearPathTo( PathNode *node, byte maxheight[ NUM_WIDTH_VALUES ], qboolean fulltest = true );
		qboolean			LadderTo( PathNode *node, byte maxheight[ NUM_WIDTH_VALUES ] );
		void				DrawConnections( void );
	};

typedef SafePtr<PathNode> PathNodePtr;

#define PATHMAP_CELLSIZE	256
#define PATHMAP_GRIDSIZE	( MAX_MAP_BOUNDS * 2 / PATHMAP_CELLSIZE )

#define PATHMAP_NODES		126			// 128 - sizeof( int ) / sizeof( short )

class MapCell : public Class
	{
	private :
		int	numnodes;
		short	nodes[ PATHMAP_NODES ];

	public :
								MapCell();
								~MapCell();
		void					Init( void );
		qboolean				AddNode( PathNode *node );
		qboolean				RemoveNode( PathNode *node );
		PathNode				*GetNode( int index );
		int					NumNodes( void );
	};

class PathSearch : public Listener
	{
	private:
		MapCell				PathMap[ PATHMAP_GRIDSIZE ][ PATHMAP_GRIDSIZE ];

		void					AddToGrid( PathNode *node, int x, int y );
		qboolean				RemoveFromGrid( PathNode *node, int x, int y );
		int					NodeCoordinate( float coord );
		int					GridCoordinate( float coord );
		void					ClearNodes( Event *ev );
		void					LoadNodes( Event *ev );
		void					SaveNodes( Event *ev );
      qboolean          ArchiveNodes( str name, qboolean save );
		void					SavePathsEvent( Event *ev );
      void              SetNodeFlagsEvent( Event *ev );
		void					RecalcPathsEvent( Event *ev );
      void              CalcPathEvent( Event *ev );
      void              DisconnectPathEvent( Event *ev );

	public:
      CLASS_PROTOTYPE( PathSearch );

                        PathSearch();
                        ~PathSearch();
		void					Archive( Archiver &arc );
		void					AddNode( PathNode *node );
		void					RemoveNode( PathNode *node );
		void					UpdateNode( PathNode *node );
		MapCell				*GetNodesInCell( int x, int y );
		MapCell				*GetNodesInCell( Vector pos );
		PathNode				*NearestNode( Vector pos, Entity *ent = NULL, qboolean usebbox = true );
		void					Teleport( Entity *teleportee, Vector from, Vector to );
		void					ShowNodes( void );
		int					NumNodes( void );
		int					NumLoadNodes( void );
      void              Checksum( Vector &checksum );
		void					SavePaths( void );
		void					Init( const char *mapname );
	};

extern PathSearch PathManager;

#define MAX_PATHNODES 2048

PathNode *AI_FindNode( const char *name );
PathNode *AI_GetNode( int num );
void AI_AddNode( PathNode *node );
void AI_RemoveNode( PathNode *node );
void AI_ResetNodes( void );

#include "path.h"

template<class Heuristic>
class PathFinder : public Class
	{
	private:
	   Stack<PathNode *>	stack;
	   PathNode				*OPEN;
	   PathNode				*CLOSED;
		PathNode				*endnode;

		void					ClearPath( void );
		void					ClearOPEN( void );
		void					ClearCLOSED( void );
		PathNode				*ReturnBestNode( void );
		void					GenerateSuccessors( PathNode *BestNode );
		void					Insert( PathNode *Successor );
		void					PropagateDown( PathNode *Old );
		Path					*CreatePath( PathNode *startnode );

	public:
		Heuristic			heuristic;

								PathFinder();
								~PathFinder<Heuristic>();
		Path					*FindPath( PathNode *from, PathNode *to );
		Path					*FindPath( Vector start, Vector end );
	};

template <class Heuristic>
PathFinder<Heuristic>::PathFinder()
	{
	OPEN   = NULL;
	CLOSED = NULL;
	}

template <class Heuristic>
PathFinder<Heuristic>::~PathFinder()
	{
	ClearPath();
	}

template <class Heuristic>
void PathFinder<Heuristic>::ClearOPEN
	(
	void
	)

	{
	PathNode *node;

	while( OPEN )
		{
		node = OPEN;
		OPEN = node->NextNode;

		node->inlist = NOT_IN_LIST;
		node->NextNode = NULL;
		node->Parent = NULL;

		// reject is used to indicate that a node is unfit for ending on during a search
		node->reject = false;
		}
	}

template <class Heuristic>
void PathFinder<Heuristic>::ClearCLOSED
	(
	void
	)

	{
	PathNode *node;

	while( CLOSED )
		{
		node = CLOSED;
		CLOSED = node->NextNode;

		node->inlist = NOT_IN_LIST;
		node->NextNode = NULL;
		node->Parent = NULL;

		// reject is used to indicate that a node is unfit for ending on during a search
		node->reject = false;
		}
	}

template <class Heuristic>
void PathFinder<Heuristic>::ClearPath
	(
	void
	)

	{
	stack.Clear();
	ClearOPEN();
	ClearCLOSED();
	}

template <class Heuristic>
Path *PathFinder<Heuristic>::FindPath
	(
	PathNode *from,
	PathNode *to
	)

	{
	Path		*path;
	PathNode	*node;
   int start = 0;
   int end;
   qboolean checktime;

   checktime = false;
   if ( ai_timepaths->integer )
      {
      start = gi.Milliseconds();
      checktime = true;
      }

	OPEN   = NULL;
	CLOSED = NULL;

	endnode = to;

	// Should always be NULL at this point
	assert( !from->NextNode );

	// make Open List point to first node
	OPEN = from;
	from->g = 0;
	from->h = heuristic.dist( from, endnode );
	from->NextNode = NULL;

	node = ReturnBestNode();
	while( node && !heuristic.done( node, endnode ) )
		{
		GenerateSuccessors( node );
		node = ReturnBestNode();
		}

	if ( !node )
		{
		path = NULL;
      if ( ai_debugpath->integer )
			{
         gi.DPrintf( "Search failed--no path found.\n" );
			}
		}
	else
		{
		path = CreatePath( node );
		}

	ClearPath();

   if ( checktime )
      {
      end = gi.Milliseconds();
      if ( ai_timepaths->integer <= ( end - start ) )
         {
         gi.DebugPrintf( "%d: ent #%d : %d\n", level.framenum, heuristic.entnum, end - start );
         }
      }

	return path;
	}

template <class Heuristic>
Path *PathFinder<Heuristic>::FindPath
	(
	Vector start,
	Vector end
	)

	{
	PathNode *from;
	PathNode *to;
   Entity *ent;

   ent = G_GetEntity( heuristic.entnum );
	from = PathManager.NearestNode( start, ent );
	to = PathManager.NearestNode( end, ent );

	if ( !from )
		{
      if ( ai_debugpath->integer )
			{
         gi.DPrintf( "Search failed--couldn't find closest source.\n" );
			}
		return NULL;
		}

	if ( !from || !to )
		{
      if ( ai_debugpath->integer )
			{
         gi.DPrintf( "Search failed--couldn't find closest destination.\n" );
			}
		return NULL;
		}

	return FindPath( from, to );
	}

template <class Heuristic>
Path *PathFinder<Heuristic>::CreatePath
	(
	PathNode *startnode
	)

	{
	PathNode *node;
	Path *p;
	int	i;
	int	n;
	PathNode *reverse[ MAX_PATH_LENGTH ];

	// unfortunately, the list goes goes from end to start, so we have to reverse it
	for( node = startnode, n = 0; ( node != NULL ) && ( n < MAX_PATH_LENGTH ); node = node->Parent, n++ )
		{
		assert( n < MAX_PATH_LENGTH );
		reverse[ n ] = node;
		}

	p = new Path( n );
	for( i = n - 1; i >= 0; i-- )
		{
		p->AddNode( reverse[ i ] );
		}

   if ( ai_debugpath->integer )
		{
      gi.DPrintf( "%d nodes in path\n", n );
      gi.DPrintf( "%d nodes allocated\n", PathManager.NumNodes() );
		}

	return p;
	}

template <class Heuristic>
PathNode *PathFinder<Heuristic>::ReturnBestNode
	(
	void
	)

	{
	PathNode *bestnode;

	if ( !OPEN )
		{
		// No more nodes on OPEN
		return NULL;
		}

	// Pick node with lowest f, in this case it's the first node in list
	// because we sort the OPEN list wrt lowest f. Call it BESTNODE.

	bestnode = OPEN;					// point to first node on OPEN
	OPEN = bestnode->NextNode;		// Make OPEN point to nextnode or NULL.

	// Next take BESTNODE (or temp in this case) and put it on CLOSED
	bestnode->NextNode	= CLOSED;
	CLOSED					= bestnode;

	bestnode->inlist = IN_CLOSED;

	return( bestnode );
	}

template <class Heuristic>
void PathFinder<Heuristic>::GenerateSuccessors
	(
	PathNode *BestNode
	)

	{
	int			i;
	int			g;					// total path cost - as stored in the linked lists.
	PathNode		*node;
	pathway_t	*path;

	for( i = 0; i < BestNode->numChildren; i++ )
		{
		path = &BestNode->Child[ i ];
		node = AI_GetNode( path->node );

		// g(Successor)=g(BestNode)+cost of getting from BestNode to Successor
		g = BestNode->g + heuristic.cost( BestNode, i );

		switch( node->inlist )
			{
			case NOT_IN_LIST :
				// Only allow this if it's valid
				if ( heuristic.validpath( BestNode, i ) )
					{
					node->Parent	= BestNode;
					node->g			= g;
					node->h			= heuristic.dist( node, endnode );
					node->f			= g + node->h;

					// Insert Successor on OPEN list wrt f
					Insert( node );
					}
				break;

			case IN_OPEN :
				// if our new g value is < node's then reset node's parent to point to BestNode
    			if ( g < node->g )
    				{
    				node->Parent	= BestNode;
    				node->g			= g;
    				node->f			= g + node->h;
    				}
				break;

			case IN_CLOSED :
				// if our new g value is < Old's then reset Old's parent to point to BestNode
    			if ( g < node->g )
    				{
    				node->Parent	= BestNode;
    				node->g			= g;
    				node->f			= g + node->h;

					// Since we changed the g value of Old, we need
    				// to propagate this new value downwards, i.e.
    				// do a Depth-First traversal of the tree!
    				PropagateDown( node );
    				}
				break;

			default :
				// shouldn't happen, but try to catch it during debugging phase
				assert( NULL );
				gi.Error( ERR_DROP, "Corrupted path node" );
				break;
			}
		}
	}

template <class Heuristic>
void PathFinder<Heuristic>::Insert
	(
	PathNode *node
	)

	{
	PathNode *prev;
	PathNode *next;
	int		f;

	node->inlist = IN_OPEN;
	f = node->f;

	// special case for if the list is empty, or it should go at head of list (lowest f)
	if ( ( OPEN == NULL ) || ( f < OPEN->f ) )
		{
		node->NextNode = OPEN;
		OPEN = node;
		return;
		}

	// do sorted insertion into OPEN list in order of ascending f
	prev = OPEN;
	next = OPEN->NextNode;
	while( ( next != NULL ) && ( next->f < f ) )
		{
		prev = next;
		next = next->NextNode;
		}

	// insert it between the two nodes
	node->NextNode = next;
	prev->NextNode = node;
	}

template <class Heuristic>
void PathFinder<Heuristic>::PropagateDown
	(
	PathNode *node
	)

	{
	int			c;
	unsigned		g;
	unsigned		movecost;
	PathNode		*child;
	PathNode		*parent;
	pathway_t	*path;
	int			n;

	g = node->g;
	n = node->numChildren;
	for( c = 0; c < n; c++ )
		{
		path = &node->Child[ c ];
		child = AI_GetNode( path->node );

		movecost = g + heuristic.cost( node, c );
		if ( movecost < child->g )
			{
			child->g = movecost;
			child->f = child->g + child->h;
			child->Parent = node;

			// reset parent to new path.
			// Now the Child's branch need to be
			// checked out. Remember the new cost must be propagated down.
			stack.Push( child );
			}
		}

	while( !stack.Empty() )
		{
    	parent = stack.Pop();
		n = parent->numChildren;
		for( c = 0; c < n; c++ )
    		{
			path = &parent->Child[ c ];
			child = AI_GetNode( path->node );

			// we stop the propagation when the g value of the child is equal or better than
			// the cost we're propagating
			movecost = parent->g + path->moveCost;
			if ( movecost < child->g )
    			{
				child->g = movecost;
				child->f = child->g + child->h;
    			child->Parent = parent;
    			stack.Push( child );
    			}
    		}
		}
	}

class StandardMovement : public Class
	{
	public:
		int		minwidth;
		int		minheight;
		int		entnum;
		qboolean can_jump;

	inline void setSize
		(
		Vector size
		)

		{
		minwidth = max( size.x, size.y );
		minheight = size.z;
		}

	inline int dist
		(
		PathNode *node,
		PathNode *end
		)

		{
		Vector	delta;
		int		d1;
		int		d2;
		int		d3;
		int		h;

      delta = node->origin - end->origin;
		d1		= abs( ( int )delta[ 0 ] );
		d2		= abs( ( int )delta[ 1 ] );
		d3		= abs( ( int )delta[ 2 ] );
		h		= max( d1, d2 );
		h		= max( d3, h );

		return h;
		}

	inline qboolean validpath
		(
		PathNode *node,
		int i
		)

		{
		pathway_t *path;
		PathNode *n;

		path = &node->Child[ i ];

		if ( CHECK_PATH( path, minwidth, minheight ) )
			{
			return false;
			}

		if ( path->door )
			{
			Door *door;

			door = ( Door * )G_GetEntity( path->door );
			if ( !door->CanBeOpenedBy( G_GetEntity( entnum ) ) )
				{
				return false;
				}
			}

		n = AI_GetNode( path->node );

		if ( node->nodeflags & AI_JUMP && n->nodeflags & AI_JUMP && !can_jump )
			return false;

		if ( n && ( n->occupiedTime > level.time ) && ( n->entnum != entnum ) )
			{
			return false;
			}

		return true;
		}

	inline int cost
		(
		PathNode *node,
		int i
		)

		{
		return node->Child[ i ].moveCost;
		}

	inline qboolean done
		(
		PathNode *node,
		PathNode *end
		)

		{
		return node == end;
		}
	};

typedef PathFinder<StandardMovement> StandardMovePath;

#endif /* navigate.h */

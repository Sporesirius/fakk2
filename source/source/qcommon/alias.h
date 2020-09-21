//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/qcommon/alias.h                          $
// $Revision:: 5                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 7/26/00 12:03p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/qcommon/alias.h                               $
// 
// 5     7/26/00 12:03p Markd
// Added Alias_sortList for tiki access
// 
// 4     7/22/00 9:06p Markd
// fixed bug with random weight alias commands
// 
// 3     6/13/00 3:44p Steven
// Added alias saving stuff.
// 
// 2     3/01/00 12:53p Markd
// Added Alias_ActorListclear function
// 
// 1     9/10/99 10:52a Jimdose
// 
// 1     9/08/99 4:03p Jimdose
// 
// 5     9/11/98 3:40p Markd
// added some naming to alias functions
// 
// 4     8/18/98 11:08p Markd
// Added new Alias System
// 
// 3     5/20/98 11:14a Markd
// changed char *'s to const char *'s
// 
// 2     3/30/98 6:11p Markd
// Initial
// 
// 1     3/30/98 5:44p Markd
// 
// 2     12/03/97 6:40p Markd
// First Build
// 
// 1     12/03/97 4:21p Markd
// 
// 3     11/24/97 6:55p Markd
// Added Alias Dump as well as cleaning up some stuff
// 
// 2     11/21/97 8:47p Markd
// First Compile
// 
// 1     11/21/97 8:36p Markd
// Alias stuff for sounds and such
// 
// DESCRIPTION:
// Generic alias system for files.
// 

#ifndef __ALIAS_H__
#define __ALIAS_H__

#ifdef __cplusplus
extern "C" {
#endif

//
// public implementation
//

const char *   Alias_Find( const char * alias );
qboolean Alias_Add( const char * alias, const char * name, const char * parameters );
qboolean Alias_Delete( const char * alias );
const char *   Alias_FindRandom( const char * alias );
void     Alias_Dump( void );
void     Alias_Clear( void );

//
// private implementation
//
#define MAX_ALIAS_NAME_LENGTH 32
#define MAX_REAL_NAME_LENGTH 128
#define MAX_ALIASLIST_NAME_LENGTH 32

typedef struct AliasActorNode_s
	{
   int actor_number;

	int  number_of_times_played;
	byte been_played_this_loop;
	int  last_time_played;

   struct AliasActorNode_s * next;
   } AliasActorNode_t;

typedef struct AliasListNode_s
	{
   char alias_name[MAX_ALIAS_NAME_LENGTH];
   char real_name[MAX_REAL_NAME_LENGTH];
   float weight;

	// Static alias info

	byte  global_flag;
	byte  stop_flag;
	float timeout;
	int   maximum_use;

	// Global alias info

	int  number_of_times_played;
	byte been_played_this_loop;
	int  last_time_played;

	// Actor infos

	AliasActorNode_t *actor_list;

   struct AliasListNode_s * next;
   } AliasListNode_t;

typedef struct AliasList_s
   {
   char name[ MAX_ALIASLIST_NAME_LENGTH ];
   qboolean    dirty;
   int         num_in_list;
   AliasListNode_t ** sorted_list;
   AliasListNode_t * data_list;
   } AliasList_t;

void Alias_ListClearActors( AliasList_t * list );
AliasList_t * AliasList_New( const char * name );
const char *   Alias_ListFind( AliasList_t * list, const char * alias );
AliasListNode_t *Alias_ListFindNode( AliasList_t * list, const char * alias );
qboolean Alias_ListAdd( AliasList_t * list, const char * alias, const char * name, const char * parameters );
const char *   Alias_ListFindRandom( AliasList_t * list, const char * alias );
void     Alias_ListDump( AliasList_t * list );
void     Alias_ListClear( AliasList_t * list  );
void     Alias_ListDelete( AliasList_t * list );
void     Alias_ListSort( AliasList_t * list );
int Alias_IsGlobal(AliasListNode_t *node, int actor_number);
AliasActorNode_t *Alias_FindActor(AliasListNode_t *node, int actor_number);
void Alias_ListFindRandomRange( AliasList_t * list, const char * alias, int *min_index, int *max_index, float *total_weight );
const char * Alias_ListFindDialog( AliasList_t * list, const char * alias, int random, int actor_number);
void Alias_ListUpdateDialog( AliasList_t * list, const char * alias, int number_of_times_played, byte been_played_this_loop, int last_time_played );
void Alias_ListAddActorDialog( AliasList_t * list, const char * alias, int actor_number, int number_of_times_played, byte been_played_this_loop, int last_time_played );
float randweight( void );

#ifdef __cplusplus
	}
#endif

#endif /* alias.h */

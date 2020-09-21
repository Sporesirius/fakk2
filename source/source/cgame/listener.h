//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/listener.h                         $
// $Revision:: 36                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/25/00 11:32p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/listener.h                              $
// 
// 36    7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 35    6/22/00 6:34p Markd
// fixed =operator assignment bug
// 
// 34    6/22/00 3:45p Markd
// fixed a bunch of saved game issues
// 
// 33    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 32    5/30/00 7:06p Markd
// saved games 4th pass
// 
// 31    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 30    4/29/00 3:26p Markd
// fleshed out the rest of the event/class documentation
// 
// 29    4/26/00 7:55p Markd
// Added more documentation code into various systems
// 
// 28    4/13/00 7:04p Aldie
// Fixed bug for animation events where the anim was greater than 255.  Added
// animframe and animnumber to Event.
// 
// 27    3/16/00 10:50a Markd
// Fixed some bad syntax in headers that exhibited itself in non-visualc
// compilers
// 
// 26    1/06/00 11:10p Jimdose
// cleaning up unused code
// 
// 25    12/15/99 11:45a Markd
// made Event's Classes and also freed up safe pointers at the appropriate
// times
// 
// 24    12/11/99 5:51p Markd
// First wave of bug fixes after q3a gold merge
// 
// 23    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 22    11/11/99 3:54p Jimdose
// added EVENT_TORSO_ANIM
// 
// 21    10/19/99 7:52p Markd
// Removed three part model system
// 
// 20    10/12/99 11:09a Morbid
// UI merge back to FAKK
// 
// 19    10/07/99 3:02p Steven
// Removed defaults for event constructor and added a new event constructor
// that only takes a const char * as a parm.
// 
// 18    10/06/99 3:09p Steven
// Added dumpevents command.
// 
// 17    10/05/99 2:03p Markd
// Added warning about files being in multiple projects
// 
// 16    10/03/99 4:50p Markd
// removed str& constructor from listener
// 
// 15    10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 14    10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 13    10/01/99 3:49p Markd
// fixed some level 4 warnings
// 
// 12    9/29/99 3:10p Markd
// fixed listener problems
// 
// 11    9/29/99 2:49p Morbid
// 
// 10    9/28/99 7:13p Markd
// moved __LISTENER define up  to the top of the file
// 
// 9     9/28/99 5:31p Markd
// Successfully merged class.h, listener.h and vector.h into all three modules,
// cgame, fgame and client
// 
// 8     9/28/99 5:15p Markd
// Fixed more merge bugs with sharing class, vector and listener between three
// modules
// 
// 7     9/28/99 4:26p Markd
// merged listener, class and vector between 3 projects
// 
// 6     9/28/99 10:12a Markd
// fixed some event issues
// 
// 5     9/27/99 5:44p Markd
// began documentation and cleanup phase after merge
// 
// 4     9/16/99 7:48p Jimdose
// made SetConsoleEdict use 0 based players
// 
// 3     9/16/99 7:48p Jimdose
// fixed GetConsoleEdict to use 0 based players
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 14    9/02/99 2:33p Markd
// Added cache ability to entities
// 
// 13    8/28/99 3:34p Jimdose
// Added EventVar
// All event args now have type information and use lazy evaluation
// 
// 12    8/27/99 8:25p Markd
// added pengingevents and fixed some event holes
// 
// 11    8/27/99 3:30p Markd
// put in event caching system so that events are reused
// 
// 10    8/19/99 12:16p Jimdose
// added event stats
// added lru check to FindEvent
// 
// 9     8/09/99 5:07p Aldie
// More changes to accomodate weapons system
//
// DESCRIPTION:
//
// WARNING: This file is shared between fgame, cgame and possibly the user interface.
// It is instanced in each one of these directories because of the way that SourceSafe works.
//

//
// this has to be placed in front of the __LISTENER_H__
// if it is not, listener.cpp will not compile
//
#if defined( GAME_DLL )
//
// game dll specific defines
//
#include "g_local.h"

#endif

#ifndef __LISTENER_H__
#define __LISTENER_H__

#if defined( GAME_DLL )
//
// game dll specific defines
//
#define EVENT_DebugPrintf gi.DebugPrintf
#define EVENT_DPrintf gi.DPrintf
#define EVENT_Printf gi.Printf
#define EVENT_time   level.time
#define EVENT_realtime gi.Milliseconds()
#define EVENT_Error gi.Error

#define EVENT_FILENAME "events.txt"

class Entity;
class ScriptVariable;
class ScriptThread;
class Archiver;

#elif defined ( CGAME_DLL )
//
// cgame dll specific defines
//
#include "cg_local.h"
#include "vector.h"
#include "str.h"
#include "../qcommon/qcommon.h"

#define EVENT_DebugPrintf cgi.DebugPrintf
#define EVENT_DPrintf cgi.Printf
#define EVENT_Printf cgi.Printf
#define EVENT_time   ( ( ( float )cg.time / 1000.0f ) )
#define EVENT_realtime   cgi.Milliseconds()
#define EVENT_Error cgi.Error

#define EVENT_FILENAME "cg_events.txt"

#elif defined ( UI_LIB )

#include "../fgame/q_shared.h"
#include "vector.h"
#include "str.h"
#include "../qcommon/qcommon.h"
#include "ui_local.h"

#define EVENT_DebugPrintf Com_DebugPrintf
#define EVENT_DPrintf Com_Printf
#define EVENT_Printf Com_Printf
#define EVENT_time   ( ( ( float )cls.realtime / 1000.0f ) )
#define EVENT_realtime   Sys_Milliseconds()
#define EVENT_Error Com_Error

#define EVENT_FILENAME "ui_events.txt"

#else

//
// client specific defines
//
#include "../fgame/q_shared.h"
#include "vector.h"
#include "str.h"
#include "../qcommon/qcommon.h"

#define EVENT_DebugPrintf Com_DebugPrintf
#define EVENT_DPrintf Com_Printf
#define EVENT_Printf Com_Printf
#define EVENT_time   ( ( ( float )cls.realtime / 1000.0f ) )
#define EVENT_realtime Sys_Milliseconds()
#define EVENT_Error Com_Error

#define EVENT_FILENAME "cl_events.txt"
#endif
 
#include "class.h"
#include "container.h"

typedef enum
	{
	EV_FROM_CODE,
	EV_FROM_CONSOLE,
	EV_FROM_SCRIPT,
   EV_FROM_ANIMATION
	} eventsource_t;

// Posted Event Flags
#define EVENT_LEGS_ANIM    (1<<0)      // this event is associated with an animation for the legs
#define EVENT_TORSO_ANIM   (1<<1)      // this event is associated with an animation for the torso
#define EVENT_DIALOG_ANIM  (1<<2)      // this event is associated with an animation for dialog lip syncing


// Event flags
#define EV_CONSOLE	   (1<<0)		// Allow entry from console
#define EV_CHEAT		   (1<<1)		// Only allow entry from console if cheats are enabled
#define EV_HIDE		   (1<<2)		// Hide from eventlist
#define EV_CACHE		   (1<<3)		// This event is used to cache data in

#define EV_DEFAULT	   -1    		// default flags

#define INUSE_BITS      2
#define MAX_EVENT_USE	( ( 1 << INUSE_BITS ) - 1 )

typedef enum
   {
   IS_STRING,
   IS_VECTOR,
   IS_BOOLEAN,
   IS_INTEGER,
   IS_FLOAT,
   IS_ENTITY,
   IS_SCRIPTVARIABLE
   } vartype;

#define DIRTY_STRING    ( 1 << 0 )
#define DIRTY_VECTOR    ( 1 << 1 )
#define DIRTY_INTEGER   ( 1 << 2 )
#define DIRTY_FLOAT     ( 1 << 3 )

#define DIRTY_ALL       ( 0x7fff )

class EventVar : public Class
   {
   private:
      short                   type;
      short                   dirtyFlags;
      str                     stringValue;
      Vector                  vectorValue;
      int                     intValue;
      float                   floatValue;

   public:

								EventVar()
                           {
                           type        = IS_INTEGER;
                           dirtyFlags  = DIRTY_ALL;
                           intValue    = 0;
                           floatValue  = 0;
                           };

                        EventVar( EventVar &ev )
                           {
                           type        = ev.type;
                           dirtyFlags  = ev.dirtyFlags;
                           intValue    = ev.intValue;
                           floatValue  = ev.floatValue;
                           };

                        EventVar( const char *text );
		                  EventVar( str &text );

		                  EventVar( int val )
                           {
                           type        = IS_INTEGER;
                           dirtyFlags  = DIRTY_ALL & ~DIRTY_INTEGER;
                           intValue    = val;
                           };

		                  EventVar( float val )
                           {
                           type        = IS_FLOAT;
                           dirtyFlags  = DIRTY_ALL & ~DIRTY_FLOAT;
                           floatValue  = val;
                           };

		                  EventVar( Vector &vec )
                           {
                           type        = IS_VECTOR;
                           dirtyFlags  = DIRTY_ALL & ~DIRTY_VECTOR;
                           vectorValue = vec;
                           };

#ifdef GAME_DLL
		                  EventVar( Entity *ent );
#endif

      const char			*GetToken( Event &ev );
		const char			*GetString( Event &ev );
		qboolean				GetBoolean( Event &ev );
		int					GetInteger( Event &ev );
		float					GetFloat( Event &ev );
		Vector				GetVector( Event &ev );
#ifdef GAME_DLL
		Entity				*GetEntity( Event &ev );
		ScriptVariable		*GetVariable( Event &ev );
#endif

      qboolean          IsVector( Event &ev );
      qboolean          IsNumeric( Event &ev );

#ifdef GAME_DLL
      void              Archive( Archiver &arc );
#endif
   };


class EventArgDef : public Class
   {
   private:
      int                     type;
      str                     name;
      float                   minRange[ 3 ];
      qboolean                minRangeDefault[ 3 ];
      float                   maxRange[ 3 ];
      qboolean                maxRangeDefault[ 3 ];
      qboolean                optional;
   public:

		EventArgDef()
         {
         type        = IS_INTEGER;
         //name        = "undefined";
         optional    = qfalse;
         };
		void              Setup( const char * eventName, const char *argName, const char *argType, const char *argRange );
		void              PrintArgument( FILE *event_file = NULL );
      void              PrintRange( FILE *event_file = NULL );
#if 0
#ifdef GAME_DLL
      void              Archive( Archiver &arc );
#endif
#endif
   };



#ifndef GAME_DLL
extern "C" 
   {
   // interface functions
   void	        L_ProcessPendingEvents( void );
   void          L_ClearEventList( void );
   void          L_InitEvents( void );
   void          L_ShutdownEvents( void );
   }
#endif


class	Listener;
typedef SafePtr<Listener> ListenerPtr;
                           

class Event : public Class
	{
	private:
      friend class	      Listener;

		typedef struct EventInfo
			{
			unsigned			   inuse			: INUSE_BITS;	// must change MAX_EVENT_USE to reflect maximum number stored here
			unsigned			   source		: 2;
			unsigned			   flags			: 9;
			unsigned			   linenumber	: 19;		      // linenumber does double duty in the case of the console commands
         } EventInfo_t;

		int					   eventnum;
		EventInfo			   info;
      const char           *name;
      const char           *formatspec;
      const char           *argument_names;
      const char           *documentation;
		Container<EventVar>  *data;
		Container<EventArgDef> *definition;
		int					   threadnum;
      short                anim_number;
      short                anim_frame;
      SafePtr<Listener>    m_sourceobject;

	   //Listener             *obj;
	   float		            time;
      int                  flags;
                           
								   Event( int num );
		static void			   initCommandList( void );
      static void          InitializeEventLists( void );
      static void          ShutdownEventLists( void );
      static void          InitializeDocumentation( void );
      static void          ShutdownDocumentation( void );
                           
      static int           numfinds;
      static int           numfirstsearch;
      static int           numcompares;
      static int           lastevent;
      static bool          EventSystemStarted;

		friend void	         L_ProcessPendingEvents( void );
		friend void          L_ClearEventList( void );
		friend void          L_InitEvents( void );
		friend void          L_ShutdownEvents( void );

#ifdef GAME_DLL
      friend void          L_ArchiveEvents( Archiver &arc );
      friend void          L_UnarchiveEvents( Archiver &arc );

#endif

		static Container<str *>	*commandList;
		static Container<int>	*flagList;
		static Container<int>	*sortedList;
		static Container<Event *> *eventDefList;
		static qboolean			dirtylist;

		static int			   compareEvents( const void *arg1, const void *arg2 );
		static void			   SortEventList( void );
		static int			   FindEvent( const char *name );
		static int			   FindEvent( str &name );
		static void			   PrintEvent( Event *ev );

	public:
		CLASS_PROTOTYPE( Event );

      Event             *next;               // next event in the list, used for event recycling
      Event             *prev;               // previous event int the list, used for event recycling

		void * operator	new( size_t );
		void operator		delete( void * );

		static int			NumEventCommands( void );
		static void       ListCommands( const char *mask = NULL );
      static void       ListDocumentation( const char *mask, qboolean print_to_file = qfalse );
		static void       PendingEvents( const char *mask = NULL );
      static void       PrintEventDocumentation( Event * event, FILE *event_file = NULL, qboolean html = qfalse );
      static int        MapSortedEventIndex( int index );

								Event();
								Event( Event &ev );
								Event( Event *ev );
								Event
                           ( 
                           const char *command, 
                           int flags, 
                           const char *formatspec, 
                           const char *argument_names, 
                           const char *documentation 
                           );
								Event( const char *command );
								Event( str &command );
								~Event();

      void              SetupDocumentation( void );
      void              DeleteDocumentation( void );
      void              PrintDocumentation( FILE *event_file = NULL, qboolean html = qfalse );

		str					getName( void );

		void					SetSource( eventsource_t source );
		void					SetLineNumber( int linenumber );
      void              SetSourceObject( Listener *source );
      Listener          *GetSourceObject( void );
      SafePtr<Listener> *GetSourceObjectPointer( void );

		eventsource_t		GetSource( void );
		int					GetLineNumber( void );
      int               GetAnimationNumber( void );
      int               GetAnimationFrame( void );
      void              SetAnimationNumber( int anim );
      void              SetAnimationFrame( int frame );

		int         		GetFlags( void );

		void					Error( const char *fmt, ... );

		static Event		Find( const char *command );
		static qboolean	Exists( const char *command );
		static Event		Find( str &command );

		Event&				printInfo(void);

      friend bool       operator==( const Event &a, const Event &b );
      friend bool       operator!=( const Event &a, const Event &b );
		void		         operator=( const Event &ev );

		operator				int();
		operator				const char *();

		int					NumArgs( void );

		qboolean				IsVectorAt( int pos );
		qboolean				IsEntityAt( int pos );
		qboolean				IsNumericAt( int pos );

		const char			*GetToken( int pos );
		const char			*GetString( int pos );
		int					GetInteger( int pos );
		float					GetFloat( int pos );
		Vector				GetVector( int pos );
      bool              GetBoolean( int pos );

		void					AddToken( const char *text );
		void					AddTokens( int argc, const char **argv );
		void					AddString( const char *text );
		void					AddString( str &text );
		void					AddInteger( int val );
		void					AddFloat( float val );
		void					AddVector( Vector &vec );

#ifdef GAME_DLL
		void					AddEntity( Entity *ent );
		Entity				*GetEntity( int pos );
		ScriptVariable		*GetVariable( int pos );
		void					SetThread( ScriptThread *thread );
		ScriptThread		*GetThread( void );
      void              SetConsoleEdict( gentity_t *consoleedict );
      gentity_t         *GetConsoleEdict( void );

      virtual void      Archive( Archiver &arc );
#endif
	};

extern Event NullEvent;
extern Event EV_Remove;

class Listener;

class Listener : public Class
	{
	private:
		void							ScriptRemove( Event *e );

	protected:
		qboolean						CheckEventFlags( Event *event );

	public:
		CLASS_PROTOTYPE( Listener );

										~Listener();
		void							Remove( Event *e );
		qboolean						ValidEvent( Event &e );
		qboolean						ValidEvent( const char *name );
		qboolean						EventPending( Event &ev );
		qboolean						ProcessEvent( Event *event );
		qboolean						ProcessEvent( Event &event );
		void							PostEvent( Event *event, float time, int flags = 0 );
		void							PostEvent( Event &event, float time, int flags = 0 );
		qboolean						PostponeEvent( Event &event, float time );
		qboolean						PostponeEvent( Event *event, float time );
		void							CancelEventsOfType( Event *event );
		void							CancelEventsOfType( Event &event );
		void							CancelFlaggedEvents( int flags );
		void							CancelPendingEvents( void );
		qboolean						ProcessPendingEvents( void );
	};

inline void Event::SetSourceObject
   (
   Listener *source
   )

   {
   m_sourceobject = source;
   }

inline Listener *Event::GetSourceObject
   (
   void
   )

   {
   return m_sourceobject;
   }

inline SafePtr<Listener> *Event::GetSourceObjectPointer
   (
   void
   )

   {
   return &m_sourceobject;
   }

inline qboolean Event::Exists
	(
	const char *command
	)

	{
	int num;
	str c;

	if ( !commandList )
		{
		initCommandList();
		}

	c = command;
	num = FindEvent( c );
	if ( num )
		{
      return true;
		}

	return false;
	}


inline Event Event::Find
	(
	const char *command
	)

	{
	int num;
	str c;

	if ( !commandList )
		{
		initCommandList();
		}

	c = command;
	num = FindEvent( c );
	if ( num )
		{
      Event ev( num );
		return ev;
		}

	return NullEvent;
	}

inline Event Event::Find
	(
	str &command
	)

	{
	int num;

	if ( !commandList )
		{
		initCommandList();
		}

	num = FindEvent( command );
	if ( num )
		{
      Event ev( num );
		return ev;
		}

	return NullEvent;
	}

inline void Event::SetSource
	(
	eventsource_t source
	)

	{
	info.source = ( unsigned )source;
	}

inline void Event::SetLineNumber
	(
	int linenumber
	)

	{
	info.linenumber = linenumber;
	}

inline eventsource_t Event::GetSource
	(
	void
	)

	{
	return ( eventsource_t )info.source;
	}

inline int Event::GetAnimationNumber
   (
   void
   )

   {
   return anim_number;
   }

inline int Event::GetAnimationFrame
   (
   void
   )

   {
   return anim_frame;
   }

inline void Event::SetAnimationNumber
   (
   int anim
   )

   {
   anim_number = anim;
   }

inline void Event::SetAnimationFrame
   (
   int frame
   )

   {
   anim_frame = frame;
   }

inline int Event::GetLineNumber
	(
	void
	)

	{
	// linenumber does double duty in the case of the console commands
	if ( info.source == EV_FROM_SCRIPT )
		{
		return info.linenumber;
		}

	return 0;
	}

inline int Event::GetFlags
	(
	void
	)

	{
	return info.flags;
	}

inline str Event::getName
	(
	void
	)

	{
   assert( name || !eventnum );

   if ( !name )
		{
		return "NULL";
		}

   return name;
	}

inline Event& Event::printInfo
	(
	void
	)

	{
   EVENT_DPrintf( "event '%s' is number %d\n", getName().c_str(), eventnum );

	return *this;
	}

inline bool operator==
   (
   const Event &a,
   const Event &b
   )

   {
   return a.eventnum == b.eventnum;
   }
   
inline bool operator!=
   (
   const Event &a,
   const Event &b
   )

   {
   return a.eventnum != b.eventnum;
   }

inline void Event::operator=
   (
   const Event &ev
   )
   {
   eventnum = ev.eventnum;
   info = ev.info;
   if ( ev.data )
      {
      int i;

      data = new Container<EventVar>;
      data->Resize( ev.data->NumObjects() );
      for( i = 1; i < ev.data->NumObjects(); i++ )
         {
         data->AddObject( ev.data->ObjectAt( i ) );
         }
      }
   name = ev.name;
   definition = NULL;
	threadnum = ev.threadnum;
   anim_number = ev.anim_number;
   anim_frame = ev.anim_frame;
   m_sourceobject = ev.m_sourceobject;
   time = ev.time;
   flags = ev.flags;
   }


inline Event::operator int()
	{
	return eventnum;
	}

inline Event::operator const char *()
	{
	return getName().c_str();
	}

inline int Event::NumArgs
	(
	void
	)

	{
	if ( !data )
		{
		return 0;
		}

	return ( data->NumObjects() );
	}

#ifdef GAME_DLL
inline void Event::AddEntity
	(
	Entity *ent
	)

	{
	if ( !data )
		{
		data = new Container<EventVar>;
		data->Resize( 1 );
		}


   EventVar var( ent );
   data->AddObject( var );
	}
#endif

inline void Event::AddToken
	(
	const char *text
	)

	{
	if ( !data )
		{
		data = new Container<EventVar>;
		data->Resize( 1 );
		}

   EventVar var( text );
   data->AddObject( var );
	}

inline void Event::AddTokens
	(
	int argc,
	const char **argv
	)

	{
	int i;

	if ( !data )
		{
		data = new Container<EventVar>;
		data->Resize( argc );
		}

	for( i = 0; i < argc; i++ )
		{
		assert( argv[ i ] );
      EventVar var( argv[ i ] );
      data->AddObject( var );
		}
	}

inline void Event::AddString
	(
	const char *text
	)

	{
	if ( !data )
		{
		data = new Container<EventVar>;
		data->Resize( 1 );
		}

   EventVar var( text );
   data->AddObject( var );
	}

inline void Event::AddString
	(
	str &text
	)

	{
	if ( !data )
		{
		data = new Container<EventVar>;
		data->Resize( 1 );
		}

   EventVar var( text );
   data->AddObject( var );
	}

inline void Event::AddInteger
	(
	int val
	)

	{
	if ( !data )
		{
		data = new Container<EventVar>;
		data->Resize( 1 );
		}

   EventVar var( val );
   data->AddObject( var );
	}

inline void Event::AddFloat
	(
	float val
	)

	{
	if ( !data )
		{
		data = new Container<EventVar>;
		data->Resize( 1 );
		}

   EventVar var( val );
   data->AddObject( var );
	}

inline void Event::AddVector
	(
	Vector &vec
	)

	{
	if ( !data )
		{
		data = new Container<EventVar>;
		data->Resize( 1 );
		}

   EventVar var( vec );
   data->AddObject( var );
	}

inline const char *Event::GetToken
	(
	int pos
	)

	{
	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return "";
		}

	return data->ObjectAt( pos ).GetToken( *this );
	}

inline const char *Event::GetString
	(
	int pos
	)

	{
	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return "";
		}
   
   return data->ObjectAt( pos ).GetString( *this );
	}

inline int Event::GetInteger
	(
	int pos
	)

	{
	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return 0;
		}
   
   return data->ObjectAt( pos ).GetInteger( *this );
	}

inline float Event::GetFloat
	(
	int pos
	)

	{
	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return 0;
		}

   return data->ObjectAt( pos ).GetFloat( *this );
	}

inline Vector Event::GetVector
	(
	int pos
	)

	{
	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return vec_zero;
		}
   
   return data->ObjectAt( pos ).GetVector( *this );
	}

inline bool Event::GetBoolean
   (
   int pos
   )

   {
   int val;

   val = this->GetInteger( pos );

   return ( val != 0 ) ? true : false;
   }

#ifdef GAME_DLL

inline Entity *Event::GetEntity
	(
	int pos
	)

	{
	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return NULL;
		}

   return data->ObjectAt( pos ).GetEntity( *this );
	}

inline ScriptVariable *Event::GetVariable
	(
	int pos
	)

	{
	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return NULL;
		}

   return data->ObjectAt( pos ).GetVariable( *this );
	}

#endif

inline qboolean Listener::ProcessEvent
	(
	Event &event
	)

	{
	Event *ev;

	ev = new Event( event );
	return ProcessEvent( ev );
	}

inline void Listener::PostEvent
	(
	Event &event,
	float time, 
   int flags
	)

	{
	Event *ev;

	ev = new Event( event );
	PostEvent( ev, time, flags );
	}

inline qboolean Listener::PostponeEvent
	(
	Event *event,
	float time
	)

	{
	return PostponeEvent( *event, time );
	}

inline void Listener::CancelEventsOfType
	(
	Event &event
	)

	{
	CancelEventsOfType( &event );
	}

#endif


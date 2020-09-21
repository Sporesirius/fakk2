//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_listener.h                      $
// $Revision:: 2                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 9/10/99 5:24p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_listener.h                           $
// 
// 2     9/10/99 5:24p Aldie
// Merge code
// 
// 1     9/10/99 10:48a Jimdose
// 
// 2     9/09/99 3:30p Aldie
// Merge
// 
// 1     9/08/99 3:35p Aldie
//
// DESCRIPTION:
//

#include "cg_local.h"
#include "cg_class.h"
#include "cg_container.h"
#include "cg_vector.h"
#include "../fgame/str.h"

#ifndef __LISTENER_H__
#define __LISTENER_H__

typedef enum
	{
	EV_FROM_CODE,
	EV_FROM_CONSOLE,
	EV_FROM_SCRIPT
	} eventsource_t;

// Event flags
#define EV_CONSOLE	1								// Allow entry from console
#define EV_CHEAT		2								// Only allow entry from console if cheats are enabled
#define EV_HIDE		4								// Hide from eventlist

#define MAX_EVENT_USE	( ( 1 << 8 ) - 1 )

class ScriptThread;

#ifdef EXPORT_TEMPLATE
template class Container<str *>;
#endif

class Event : public Class
	{
	private:
		typedef struct EventInfo
			{
			unsigned			inuse			: 8;		// must change MAX_EVENT_USE to reflect maximum number stored here
			unsigned			source		: 2;
			unsigned			flags			: 2;
			unsigned			linenumber	: 20;		// linenumber does double duty in the case of the console commands
			};

		int					eventnum;
		EventInfo			info;
      const char        *name;
		Container<str>		*data;
		int					threadnum;

								Event( int num );
		static void			initCommandList( void );

		friend class		Listener;

		friend void	CG_ProcessPendingEvents( void );
		friend void CG_ClearEventList( void );
		friend void CG_InitEvents( void );

		static Container<str *>	*Event::commandList;
		static Container<int>	*Event::flagList;
		static Container<int>	*Event::sortedList;
		static qboolean			Event::dirtylist;

		static int			compareEvents( const void *arg1, const void *arg2 );
		static void			SortEventList( void );
		static int			FindEvent( const char *name );
		static int			FindEvent( str &name );

	public:

		CLASS_PROTOTYPE( Event );

		static int			NumEventCommands( void );
		static void       ListCommands( const char *mask = NULL );

								Event();
								Event( Event &ev );
								Event( Event *ev );
								Event( const char *command, int flags = -1 );
								Event( str &command, int flags = -1 );
								~Event();

		str					getName( void );

		void					SetSource( eventsource_t source );
		void					SetLineNumber( int linenumber );
      //void              SetConsoleEdict( gentity_t *consoleedict );
		void					SetThread( ScriptThread *thread );

		eventsource_t		GetSource( void );
		ScriptThread		*GetThread( void );
      // gentity_t           *GetConsoleEdict( void );
		int					GetLineNumber( void );

		void					Error( const char *fmt, ... );

		static Event		Find( const char *command );
		static qboolean	Exists( const char *command );
		static Event		Find( str &command );

		Event&				printInfo(void);

		operator				int();
		operator				const char *();

		int					NumArgs( void );

		qboolean				IsVectorAt( int pos );
		qboolean				IsEntityAt( int pos );
		qboolean				IsNumericAt( int pos );

		const char			*GetToken( int pos );
		const char			*GetString( int pos );
		int					GetInteger( int pos );
		double				GetDouble( int pos );
		float					GetFloat( int pos );
		Vector				GetVector( int pos );
      void              *GetPointer( int pos );

		void					AddToken( const char *text );
		void					AddTokens( int argc, const char **argv );
		void					AddString( const char *text );
		void					AddString( str &text );
		void					AddInteger( int val );
		void					AddDouble( double val );
		void					AddFloat( float val );
		void					AddVector( Vector &vec );
      void              AddPointer( void *ptr );
	};

extern Event NullEvent;
extern Event EV_Remove;

#ifdef EXPORT_TEMPLATE
template class Container<Response>;
#endif

class Listener;

class Listener : public Class
	{
	private:
		void							FloatVarEvent( Event *e );
		void							IntVarEvent( Event *e );
		void							StringVarEvent( Event *e );
		void							CharPtrVarEvent( Event *e );
		void							VectorVarEvent( Event *e );
		void							ScriptRemove( Event *e );

	protected:
		void							FloatVar( Event &e, float *var, float defaultvalue = 0 );
		void							IntVar( Event &e, int *var, float defaultvalue = 0 );
		void							StringVar( Event &e, str *var, const char *defaultvalue = "" );
		void							StringVar( Event &e, char **var, const char *defaultvalue = "" );
		void							VectorVar( Event &e, Vector *var, Vector defaultvalue = Vector( 0, 0, 0 ) );

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
		void							PostEvent( Event *event, float time );
		void							PostEvent( Event &event, float time );
		qboolean						PostponeEvent( Event &event, float time );
		qboolean						PostponeEvent( Event *event, float time );
		void							CancelEventsOfType( Event *event );
		void							CancelEventsOfType( Event &event );
		void							CancelPendingEvents( void );
		qboolean						ProcessPendingEvents( void );
	};

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
      return qtrue;
		}

	return qfalse;
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
		return Event( num );
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
		return Event( num );
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
   cgi.Printf( "event '%s' is number %d\n", getName().c_str(), eventnum );
	return *this;
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

inline void Event::AddToken
	(
	const char *text
	)

	{
	AddString( text );
	}

inline void Event::AddTokens
	(
	int argc,
	const char **argv
	)

	{
	int i;

	for( i = 0; i < argc; i++ )
		{
		assert( argv[ i ] );
		AddString( argv[ i ] );
		}
	}

inline void Event::AddString
	(
	const char *text
	)

	{
	if ( !data )
		{
		data = new Container<str>;
		data->Resize( 1 );
		}

	data->AddObject( str( text ) );
	}

inline void Event::AddString
	(
	str &text
	)

	{
	if ( !data )
		{
		data = new Container<str>;
		data->Resize( 1 );
		}

	data->AddObject( text );
	}

inline void Event::AddPointer
	(
	void *ptr
	)

	{
	char text[ 128 ];

	sprintf( text, "%d", ptr );
	AddString( text );
	}

inline void Event::AddInteger
	(
	int val
	)

	{
	char text[ 128 ];

	sprintf( text, "%d", val );
	AddString( text );
	}

inline void Event::AddDouble
	(
	double val
	)

	{
	char text[ 128 ];

	sprintf( text, "%f", val );
	AddString( text );
	}

inline void Event::AddFloat
	(
	float val
	)

	{
	char text[ 128 ];

	sprintf( text, "%f", val );
	AddString( text );
	}

inline void Event::AddVector
	(
	Vector &vec
	)

	{
	char text[ 128 ];

	sprintf( text, "(%f %f %f)", vec[ 0 ], vec[ 1 ], vec[ 2 ] );
	AddString( text );
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

	return data->ObjectAt( pos ).c_str();
	}

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
	float time
	)

	{
	Event *ev;

	ev = new Event( event );
	PostEvent( ev, time );
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
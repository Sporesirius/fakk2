//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/class.cpp                          $
// $Revision:: 17                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 8/10/00 6:34p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/class.cpp                               $
// 
// 17    8/10/00 6:34p Aldie
// Added a shutdown method
// 
// 16    7/26/00 1:07p Steven
// Made it so in classes new function NULL is returned if we try to allocate 0
// bytes.
// 
// 15    7/07/00 6:57p Markd
// changed default debug printf when starting up event system
// 
// 14    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 13    4/29/00 3:50p Markd
// added some convenience classes and printed out classID when appropriate
// 
// 12    4/29/00 3:26p Markd
// fleshed out the rest of the event/class documentation
// 
// 11    4/29/00 11:38a Markd
// changed formatting for dump all classes
// 
// 10    4/26/00 7:55p Markd
// Added more documentation code into various systems
// 
// 9     4/12/00 6:19p Aldie
// Fixed formatting
// 
// 8     3/04/00 11:45a Markd
// Added malloc and free for cgame and client
// 
// 7     2/26/00 3:27p Markd
// pre-initialized all memory with known bad value
// 
// 6     2/04/00 11:20a Markd
// Added memory leak test code to new and delete operators
// 
// 5     1/10/00 5:34p Markd
// Changed Allocation routines for fgame to use the gi.Malloc and gi.Free
// instead of the in game heap
// 
// 4     12/15/99 11:45a Markd
// made Event's Classes and also freed up safe pointers at the appropriate
// times
// 
// 3     10/05/99 2:03p Markd
// Added warning about files being in multiple projects
// 
// 2     9/28/99 4:26p Markd
// merged listener, class and vector between 3 projects
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
//
// DESCRIPTION:
// Base class that all classes that are used in conjunction with Sin should
// be based off of.  Class gives run-time type information about any class
// derived from it.  This is really handy when you have a pointer to an object
// that you need to know if it supports certain behaviour.
//
// WARNING: This file is shared between fgame, cgame and possibly the user interface.
// It is instanced in each one of these directories because of the way that SourceSafe works.
//

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#if defined( GAME_DLL )

#include "g_local.h"

#elif defined ( CGAME_DLL )

#include "cg_local.h"
#include "listener.h"
#include "../qcommon/qcommon.h"

#else

#include "listener.h"
#include "../qcommon/qcommon.h"

#endif

#include "class.h"
#include "linklist.h"

int totalmemallocated = 0;
int numclassesallocated = 0;

static ClassDef *classlist = NULL;


ClassDef::ClassDef()
	{
	this->classname		= NULL;
	this->classID			= NULL;
	this->superclass		= NULL;
	this->responses		= NULL,
	this->numEvents		= 0;
	this->responseLookup = NULL;
	this->newInstance		= NULL;
	this->classSize		= 0;
	this->super				= NULL;
	this->prev				= this;
	this->next				= this;
	}

ClassDef::ClassDef
	(
	const char *classname,
	const char *classID,
	const char *superclass,
	ResponseDef<Class> *responses,
	void *( *newInstance )( void ),
	int classSize
	)

	{
	ClassDef *node;

	if ( classlist == NULL )
		{
		classlist = new ClassDef;
		}

	this->classname			= classname;
	this->classID				= classID;
	this->superclass			= superclass;
	this->responses			= responses;
	this->numEvents			= 0;
	this->responseLookup		= NULL;
	this->newInstance			= newInstance;
	this->classSize			= classSize;
	this->super					= getClass( superclass );

	// It's not uncommon for classes to not have a class id, so just set it
	// to an empty string so that we're not checking for it all the time.
	if ( !classID )
		{
		this->classID = "";
		}

	// Check if any subclasses were initialized before their superclass
	for( node = classlist->next; node != classlist; node = node->next )
		{
		if ( ( node->super == NULL ) && ( !Q_stricmp( node->superclass, this->classname ) ) &&
			( Q_stricmp( node->classname, "Class" ) ) )
			{
			node->super	= this;
			}
		}

	// Add to front of list
	LL_Add( classlist, this, prev, next );
	}

void ClassDef::Shutdown
   (
   void
   )

   {
	if ( responseLookup )
		{
		delete[] responseLookup;
		responseLookup = NULL;
		}
   }

ClassDef::~ClassDef()
	{
	ClassDef *node;

	if ( classlist != this )
		{
		LL_Remove( this, prev, next );

		// Check if any subclasses were initialized before their superclass
		for( node = classlist->next; node != classlist; node = node->next )
			{
			if ( node->super == this )
				{
				node->super	= NULL;
				}
			}
		}
	else
		{
		// If the head of the list is deleted before the list is cleared, then we may have problems
		assert( this->next == this->prev );
		}

	if ( responseLookup )
		{
		delete[] responseLookup;
		responseLookup = NULL;
		}
	}

void ClassDef::BuildResponseList
	(
	void
	)

	{
	ClassDef		*c;
	ResponseDef<Class> *r;
	int			ev;
	int			i;
	qboolean		*set;
	int			num;

	if ( responseLookup )
		{
		delete[] responseLookup;
		responseLookup = NULL;
		}

	num = Event::NumEventCommands();
	responseLookup = ( Response ** )new char[ sizeof( Response * ) * num ];
	memset( responseLookup, 0, sizeof( Response * ) * num );

	set = new qboolean[ num ];
	memset( set, 0, sizeof( qboolean ) * num );

	this->numEvents = num;

	for( c = this; c != NULL; c = c->super )
		{
		r = c->responses;
		if ( r )
			{
			for( i = 0; r[ i ].event != NULL; i++ )
				{
				ev = ( int )*r[ i ].event;
				if ( !set[ ev ] )
					{
					set[ ev ] = true;
					if ( r[ i ].response )
						{
						responseLookup[ ev ] = &r[ i ].response;
						}
					else
						{
						responseLookup[ ev ] = NULL;
						}
					}
				}
			}
		}

	delete[] set;
	}

void BuildEventResponses
	(
	void
	)

	{
	ClassDef *c;
	int amount;
	int numclasses;

	amount = 0;
	numclasses = 0;
	for( c = classlist->next; c != classlist; c = c->next )
		{
		c->BuildResponseList();

		amount += c->numEvents * sizeof( Response * );
		numclasses++;
		}

   CLASS_DPrintf( "\n------------------\nEvent system initialized: "
		"%d classes %d events %d total memory in response list\n\n",
		numclasses, Event::NumEventCommands(), amount );
	}

ClassDef *getClassForID
	(
	const char *name
	)

	{
	ClassDef *c;

	for( c = classlist->next; c != classlist; c = c->next )
		{
		if ( c->classID && !Q_stricmp( c->classID, name ) )
			{
			return c;
			}
		}

	return NULL;
	}

ClassDef *getClass
	(
	const char *name
	)

	{
	ClassDef *c;

	for( c = classlist->next; c != classlist; c = c->next )
		{
		if ( !Q_stricmp( c->classname, name ) )
			{
			return c;
			}
		}

	return NULL;
	}

ClassDef *getClassList
	(
	void
	)

	{
	return classlist;
	}

void listAllClasses
	(
	void
	)

	{
	ClassDef *c;

	for( c = classlist->next; c != classlist; c = c->next )
		{
      CLASS_DPrintf( "%s\n", c->classname );
		}
	}

void listInheritanceOrder
	(
	const char *classname
	)

	{
	ClassDef *cls;
	ClassDef *c;

	cls = getClass( classname );
	if ( !cls )
		{
      CLASS_DPrintf( "Unknown class: %s\n", classname );
		return;
		}
	for( c = cls; c != NULL; c = c->super )
		{
      CLASS_DPrintf( "%s\n", c->classname );
		}
	}

qboolean checkInheritance
	(
	ClassDef *superclass,
	ClassDef *subclass
	)

	{
	ClassDef *c;

	for( c = subclass; c != NULL; c = c->super )
		{
		if ( c == superclass )
			{
			return true;
			}
		}
	return false;
	}

qboolean checkInheritance
	(
	ClassDef *superclass,
	const char *subclass
	)

	{
	ClassDef *c;

	c = getClass( subclass );
	if ( c == NULL )
		{
      CLASS_DPrintf( "Unknown class: %s\n", subclass );
		return false;
		}
	return checkInheritance( superclass, c );
	}

qboolean checkInheritance
	(
	const char *superclass,
	const char *subclass
	)

	{
	ClassDef *c1;
	ClassDef *c2;

	c1 = getClass( superclass );
	c2 = getClass( subclass );
	if ( c1 == NULL )
		{
      CLASS_DPrintf( "Unknown class: %s\n", superclass );
		return false;
		}
	if ( c2 == NULL )
		{
      CLASS_DPrintf( "Unknown class: %s\n", subclass );
		return false;
		}
	return checkInheritance( c1, c2 );
	}

void CLASS_Print( FILE *class_file, const char *fmt, ... )
	{
	va_list	argptr;
	char		text[ 1024 ];

	va_start( argptr, fmt );
	vsprintf( text, fmt, argptr );
	va_end( argptr );

	if ( class_file )
		fprintf( class_file, text );
	else
		CLASS_DPrintf( text );
	}


CLASS_DECLARATION( NULL, Class, NULL )
	{
		{ NULL, NULL }
	};

#ifdef NDEBUG

void * Class::operator new( size_t s )
	{
	int *p;

	if ( s == 0 )
		return NULL;

	s += sizeof( int );
#if defined( GAME_DLL )
	p = ( int * )gi.Malloc( s );
#elif defined( CGAME_DLL )
	p = ( int * )cgi.Malloc( s );
#else
	p = ( int * )Z_TagMalloc( s, TAG_CLIENT );
#endif
	*p = s;
	totalmemallocated += s;
	numclassesallocated++;
	return p + 1;
	}

void Class::operator delete( void *ptr )
	{
	int *p;

	p = ( ( int * )ptr ) - 1;
	totalmemallocated -= *p;
	numclassesallocated--;
#if defined( GAME_DLL )
	gi.Free( p );
#elif defined( CGAME_DLL )
	cgi.Free( p );
#else
   Z_Free( p );
#endif
	}

#else

#ifdef MEMORY_LEAK_TEST
int classindex = 0;
#endif

void * Class::operator new( size_t s )
	{
	int *p;

	s += sizeof( int ) * 3;
#if defined( GAME_DLL )
	p = ( int * )gi.Malloc( s );
#elif defined( CGAME_DLL )
	p = ( int * )cgi.Malloc( s );
#else
	p = ( int * )Z_TagMalloc( s, TAG_CLIENT );
#endif
   // set memory to a known wrong number
   memset( p, 0xaa, s );
#ifdef MEMORY_LEAK_TEST
	p[ 0 ] = classindex++;
#else
	p[ 0 ] = 0x12348765;
#endif
	*( int * )( ((byte *)p) + s - sizeof( int ) ) = 0x56784321;
	p[ 1 ] = s;
	totalmemallocated += s;
	numclassesallocated++;
	return p + 2;
	}

void Class::operator delete( void *ptr )
	{
	int *p;

	p = ( ( int * )ptr ) - 2;
#ifndef MEMORY_LEAK_TEST
	assert( p[ 0 ] == 0x12348765 );
#endif
	assert( *( int * )( ((byte *)p) + p[ 1 ] - sizeof( int ) ) == 0x56784321 );

	totalmemallocated -= p[ 1 ];
	numclassesallocated--;
#if defined( GAME_DLL )
	gi.Free( p );
#elif defined( CGAME_DLL )
	cgi.Free( p );
#else
   Z_Free( p );
#endif
	}

#endif

void DisplayMemoryUsage
	(
   void
	)

	{
   CLASS_Printf( "Classes %-5d Class memory used: %d\n", numclassesallocated, totalmemallocated );
   }

Class::Class()
	{
	SafePtrList = NULL;
	}

Class::~Class()
	{
   ClearSafePointers();
	}

#ifdef GAME_DLL

void Class::Archive
	(
	Archiver &arc
	)

	{
	}

#endif

void Class::ClearSafePointers( void )
	{
	while( SafePtrList != NULL )
		{
		SafePtrList->Clear();
		}
	}


void Class::warning
	(
	const char *function,
	const char *fmt,
	...
	)

	{
	va_list	argptr;
	char		text[ 1024 ];

	va_start( argptr, fmt );
	vsprintf( text, fmt, argptr );
	va_end( argptr );

	if ( getClassID() )
		{
      CLASS_DPrintf( "%s::%s : %s\n", getClassID(), function, text );
		}
	else
		{
      CLASS_DPrintf( "%s::%s : %s\n", getClassname(), function, text );
		}
	}

void Class::error
	(
	const char *function,
	const char *fmt,
	...
	)

	{
	va_list	argptr;
	char		text[ 1024 ];

	va_start( argptr, fmt );
	vsprintf( text, fmt, argptr );
	va_end( argptr );

	if ( getClassID() )
		{
		CLASS_Error( ERR_DROP, "%s::%s : %s\n", getClassID(), function, text );
		}
	else
		{
		CLASS_Error( ERR_DROP, "%s::%s : %s\n", getClassname(), function, text );
		}
	}

qboolean Class::inheritsFrom
	(
	const char *name
	)

	{
	ClassDef *c;

	c = getClass( name );
	if ( c == NULL )
		{
      CLASS_DPrintf( "Unknown class: %s\n", name );
		return false;
		}
	return checkInheritance( c, classinfo() );
	}

qboolean Class::isInheritedBy
	(
	const char *name
	)

	{
	ClassDef *c;

	c = getClass( name );
	if ( c == NULL )
		{
      CLASS_DPrintf( "Unknown class: %s\n", name );
		return false;
		}
	return checkInheritance( classinfo(), c );
	}

const char *Class::getClassname
	(
	void
	)

	{
	ClassDef *cls;

	cls = classinfo();
	return cls->classname;
	}

const char *Class::getClassID
	(
	void
	)

	{
	ClassDef *cls;

	cls = classinfo();
	return cls->classID;
	}

const char *Class::getSuperclass
	(
	void
	)

	{
	ClassDef *cls;

	cls = classinfo();
	return cls->superclass;
	}

void *Class::newInstance
	(
	void
	)

	{
	ClassDef *cls;

	cls = classinfo();
	return cls->newInstance();
	}

#define MAX_INHERITANCE 64
void ClassEvents
	(
	const char *classname,
   qboolean print_to_disk
	)

	{
	ClassDef		*c;
	ResponseDef<Class> *r;
	int			ev;
	int			i, j;
   qboolean    *set;
	int			num, orderNum;
   Event       **events;
   byte        *order;
   FILE        *class_file;
   str         classNames[ MAX_INHERITANCE ];
   str         class_filename;

	c = getClass( classname );
	if ( !c )
		{
      CLASS_DPrintf( "Unknown class: %s\n", classname );
		return;
		}

   class_file = NULL;

	if ( print_to_disk )
		{
		class_filename = str ( classname ) + ".txt";
		class_file = fopen( class_filename.c_str(), "w" );
		if ( class_file == NULL )
			return;
		}

	num = Event::NumEventCommands();

	set = new qboolean[ num ];
	memset( set, 0, sizeof( qboolean ) * num );

   events = new Event *[ num ];
   memset( events, 0, sizeof( Event * ) * num );

	order = new byte[ num ];
	memset( order, 0, sizeof( byte ) * num );
   
   orderNum = 0;
	for( ; c != NULL; c = c->super )
		{
      if ( orderNum < MAX_INHERITANCE )
         {
         classNames[ orderNum ] = c->classname;
         }
		r = c->responses;
		if ( r )
			{
			for( i = 0; r[ i ].event != NULL; i++ )
				{
				ev = ( int )*r[ i ].event;
				if ( !set[ ev ] )
					{
					set[ ev ] = true;

					if ( r[ i ].response )
						{
                  events[ ev ] = r[ i ].event;
                  order[ ev ] = orderNum;
						}
					}
				}
			}
      orderNum++;
		}

   CLASS_Print( class_file, "********************************************************\n" );
   CLASS_Print( class_file, "********************************************************\n" );
   CLASS_Print( class_file, "* All Events For Class: %s\n", classname );
   CLASS_Print( class_file, "********************************************************\n" );
   CLASS_Print( class_file, "********************************************************\n\n" );

   for( j = orderNum - 1; j >= 0; j-- )
      {
      CLASS_Print( class_file, "\n********************************************************\n" );
      CLASS_Print( class_file, "* Class: %s\n", classNames[ j ].c_str() );
      CLASS_Print( class_file, "********************************************************\n\n" );
      for( i = 1; i < num; i++ )
         {
         int index;

         index = Event::MapSortedEventIndex( i );
         if ( events[ index ] && ( order[ index ] == j ) )
            {
            Event::PrintEventDocumentation( events[ index ], class_file );
            }
         }
      }

	if ( class_file != NULL )
		{
		CLASS_DPrintf( "Printed class info to file %s\n", class_filename.c_str() );
		fclose( class_file );
		}

   delete[] events;
   delete[] order;
	delete[] set;
	}

static int dump_numclasses;
static int dump_numevents;
void DumpClass
	(
   FILE * class_file,
   const char * className
	)

	{
	ClassDef		*c;
	ResponseDef<Class> *r;
	int			ev;
	int			i;
	int			num;
   Event       **events;

	c = getClass( className );
	if ( !c )
		{
		return;
		}

	num = Event::NumEventCommands();

   events = new Event *[ num ];
   memset( events, 0, sizeof( Event * ) * num );

   // gather event responses for this class
	r = c->responses;
	if ( r )
		{
		for( i = 0; r[ i ].event != NULL; i++ )
			{
			ev = ( int )*r[ i ].event;
			if ( r[ i ].response )
				{
            events[ ev ] = r[ i ].event;
				}
			}
		}

   CLASS_Print( class_file, "\n");
   if ( c->classID[ 0 ] )
      {
      CLASS_Print( class_file, "<h2> <a name=\"%s\">%s (<i>%s</i>)</a>", c->classname, c->classname, c->classID );
      }
   else
      {
      CLASS_Print( class_file, "<h2> <a name=\"%s\">%s</a>", c->classname, c->classname );
      }

   // print out lineage
	for( c = c->super; c != NULL; c = c->super )
		{
      CLASS_Print( class_file, " -> <a href=\"#%s\">%s</a>", c->classname, c->classname );
		}
   CLASS_Print( class_file, "</h2>\n");

   dump_numclasses++;

   CLASS_Print( class_file, "<BLOCKQUOTE>\n");
   for( i = 1; i < num; i++ )
      {
      int index;

      index = Event::MapSortedEventIndex( i );
      if ( events[ index ] )
         {
         Event::PrintEventDocumentation( events[ index ], class_file, qtrue );
         dump_numevents++;
         }
      }
   CLASS_Print( class_file, "</BLOCKQUOTE>\n");
   delete[] events;
	}


#define MAX_CLASSES 1024
void DumpAllClasses
	(
   void
	)

	{
   int i, j, num, smallest;
	ClassDef *c;
   FILE * class_file;
   str class_filename;
   str class_title;
   str classes[ MAX_CLASSES ];

#if defined( GAME_DLL )
	class_filename = "g_allclasses.html";
   class_title = "Game Module";
#elif defined( CGAME_DLL )
	class_filename = "cg_allclasses.html";
   class_title = "Client Game Module";
#else
	class_filename = "cl_allclasses.html";
   class_title = "Client Module";
#endif

	class_file = fopen( class_filename.c_str(), "w" );
	if ( class_file == NULL )
		return;

   // construct the HTML header for the document
   CLASS_Print( class_file, "<HTML>\n");
   CLASS_Print( class_file, "<HEAD>\n");
   CLASS_Print( class_file, "<Title>%s Classes</Title>\n", class_title.c_str() );
   CLASS_Print( class_file, "</HEAD>\n");
   CLASS_Print( class_file, "<BODY>\n");
   CLASS_Print( class_file, "<H1>\n");
   CLASS_Print( class_file, "<center>%s Classes</center>\n", class_title.c_str() );
   CLASS_Print( class_file, "</H1>\n");
#if defined( GAME_DLL )
   //
   // print out some commonly used classnames
   //
   CLASS_Print( class_file, "<h2>" );
   CLASS_Print( class_file, "<a href=\"#Actor\">Actor</a>, " );
   CLASS_Print( class_file, "<a href=\"#Animate\">Animate</a>, " );
   CLASS_Print( class_file, "<a href=\"#Entity\">Entity</a>, " );
   CLASS_Print( class_file, "<a href=\"#ScriptSlave\">ScriptSlave</a>, " );
   CLASS_Print( class_file, "<a href=\"#ScriptThread\">ScriptThread</a>, " );
   CLASS_Print( class_file, "<a href=\"#Sentient\">Sentient</a>, " );
   CLASS_Print( class_file, "<a href=\"#Trigger\">Trigger</a>, " );
   CLASS_Print( class_file, "<a href=\"#World\">World</a>" );
   CLASS_Print( class_file, "</h2>" );
#endif

   dump_numclasses = 0;
   dump_numevents = 0;

   // get all the classes
   num = 0;
	for( c = classlist->next; c != classlist; c = c->next )
		{
      if ( num < MAX_CLASSES )
         {
         classes[ num++ ] = c->classname;
         }
		}

   // go through and process each class from smallest to greatest
   for( i = 0; i < num; i++ )
      {
      smallest = -1;
      for( j = 0; j < num; j++ )
         {
         if ( classes[ j ].length() > 1 )
            {
            if ( smallest >= 0 )
               {
               if ( classes[ j ].icmp( classes[ smallest ] ) < 0 )
                  {
                  smallest = j;
                  }
               }
            else
               {
               smallest = j;
               }
            }
         }
      DumpClass( class_file, classes[ smallest ] );
      // delete the name from the list
      classes[ smallest ] = "";
      }

	if ( class_file != NULL )
		{
      CLASS_Print( class_file, "<H2>\n");
      CLASS_Print( class_file, "%d %s Classes.<BR>%d %s Events.\n", dump_numclasses, class_title.c_str(), dump_numevents, class_title.c_str() );
      CLASS_Print( class_file, "</H2>\n");
      CLASS_Print( class_file, "</BODY>\n");
      CLASS_Print( class_file, "</HTML>\n");
		CLASS_DPrintf( "Dumped all classes to file %s\n", class_filename.c_str() );
		fclose( class_file );
		}

	}


void ShutdownClasses
   (
   void
   )

   {
   ClassDef *c;

	for( c = classlist->next; c != classlist; c = c->next )
		{
		c->Shutdown();
      }
   }

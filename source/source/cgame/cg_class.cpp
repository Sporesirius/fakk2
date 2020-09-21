//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_class.cpp                       $
// $Revision:: 2                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 9/10/99 5:24p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_class.cpp                            $
// 
// 2     9/10/99 5:24p Aldie
// Merge code
// 
// 1     9/10/99 10:48a Jimdose
// 
// 2     9/09/99 3:29p Aldie
// Merge
// 
// 1     9/08/99 3:35p Aldie
// 
// 3     7/29/99 3:32p Aldie
// Updated to new class system
//
// DESCRIPTION:
// Base class that all classes that are used in conjunction with Sin should
// be based off of.  Class gives run-time type information about any class
// derived from it.  This is really handy when you have a pointer to an object
// that you need to know if it supports certain behaviour.
//

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "cg_class.h"
#include "cg_listener.h"
#include "../fgame/linklist.h"
#include "../qcommon/qcommon.h"
#include "cg_local.h"

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
					set[ ev ] = qtrue;
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

   cgi.Printf( "\n------------------\nEvent system initialized:\n"
		"%d classes\n%d events\n%d total memory in response list\n\n",
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
      cgi.Printf( "%s\n", c->classname );
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
      cgi.Printf( "Unknown class: %s\n", classname );
		return;
		}
	for( c = cls; c != NULL; c = c->super )
		{
      cgi.Printf( "%s\n", c->classname );
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
			return qtrue;
			}
		}
	return qfalse;
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
      cgi.Printf( "Unknown class: %s\n", subclass );
		return qfalse;
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
      cgi.Printf( "Unknown class: %s\n", superclass );
		return qfalse;
		}
	if ( c2 == NULL )
		{
      cgi.Printf( "Unknown class: %s\n", subclass );
		return qfalse;
		}
	return checkInheritance( c1, c2 );
	}

CLASS_DECLARATION( NULL, Class, NULL )
	{
		{ NULL, NULL }
	};

#ifdef NDEBUG

void * Class::operator new( size_t s )
	{
	int *p;

	s += sizeof( int );
	p = ( int * )::new char[ s ];
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
	::delete[]( p );
	}

#else

void * Class::operator new( size_t s )
	{
	int *p;

	s += sizeof( int ) * 3;
	p = ( int * )::new char[ s ];
	p[ 0 ] = 0x12348765;
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

	assert( p[ 0 ] == 0x12348765 );
	assert( *( int * )( ((byte *)p) + p[ 1 ] - sizeof( int ) ) == 0x56784321 );

	totalmemallocated -= p[ 1 ];
	numclassesallocated--;
	::delete[]( p );
	}

#endif

void DisplayMemoryUsage
	(
   void
	)

	{
   cgi.Printf( "Classes %-5d Class memory used: %d\n", numclassesallocated, totalmemallocated );
   }

Class::Class()
   {
   SafePtrList = NULL;
   }

Class::~Class()
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
      cgi.Printf( "%s::%s : %s\n", getClassID(), function, text );
		}
	else
		{
      cgi.Printf( "%s::%s : %s\n", getClassname(), function, text );
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
		cgi.Error( ERR_DROP, "%s::%s : %s\n", getClassID(), function, text );
		}
	else
		{
		cgi.Error( ERR_DROP, "%s::%s : %s\n", getClassname(), function, text );
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
      cgi.Printf( "Unknown class: %s\n", name );
		return qfalse;
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
      cgi.Printf( "Unknown class: %s\n", name );
		return qfalse;
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

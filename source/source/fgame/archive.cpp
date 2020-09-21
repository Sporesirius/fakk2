//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/archive.cpp                        $
// $Revision:: 20                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/23/00 8:41p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/archive.cpp                             $
// 
// 20    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 19    6/13/00 5:09p Markd
// changed archive version number
// 
// 18    6/13/00 5:07p Markd
// turned off types on archives to trim down sizes
// 
// 17    6/06/00 5:58p Markd
// fixed warning message on archive load
// 
// 16    6/05/00 3:41p Markd
// Made Archvie load quiet
// 
// 15    6/02/00 4:24p Markd
// cleaned up archive functions
// 
// 14    5/31/00 2:58p Markd
// saved game fun
// 
// 13    5/31/00 10:19a Markd
// 4th pass saved games
// 
// 12    5/30/00 7:06p Markd
// saved games 4th pass
// 
// 11    5/27/00 8:06p Markd
// Saved games 3rd pass
// 
// 10    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 9     5/26/00 7:44p Markd
// 2nd phase save games
// 
// 8     5/25/00 4:28p Markd
// fixed up archive functions
// 
// 7     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 6     2/04/00 1:29p Markd
// Added checksum to ai path nodes. It auto saves on exit now and will
// automatically re-build nodes as needed
// 
// 5     1/10/00 5:27p Markd
// Replaced TAG calls with normal malloc and free calls
// 
// 4     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 3     12/13/99 10:46a Markd
// incremental merge fix
// 
// 2     10/01/99 4:51p Markd
// Made Warning level 4 work on all projects
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 7     8/17/99 5:08p Markd
// Changed all FS_ReadFile's to FS_ReadFileEx's in game code
// 
// 6     7/29/99 5:33p Markd
// Fixed weird compiler bug
//
// DESCRIPTION:
// Class for archiving objects
//
#include "g_local.h"
#include "archive.h"

enum
	{
   ARC_NULL, ARC_Vector, ARC_Vec3, ARC_Vec4, ARC_Integer, ARC_Unsigned, ARC_Byte, ARC_Char, ARC_Short, ARC_UnsignedShort,
	ARC_Float, ARC_Double, ARC_Boolean, ARC_String, ARC_Raw, ARC_Object, ARC_ObjectPointer,
   ARC_SafePointer, ARC_Event, ARC_EventPointer, ARC_Quat, ARC_Entity, ARC_Bool,
	ARC_NUMTYPES
	};

static const char *typenames[] =
	{
   "NULL", "vector", "vec3", "vec4", "int", "unsigned", "byte", "char", "short", "unsigned short",
	"float", "double", "qboolean", "string", "raw data", "object", "objectpointer",
   "safepointer", "event", "eventpointer", "quaternion", "entity", "bool"
	};

#define ArchiveHeader   ( *( int * )"FAKK" )
#define ArchiveVersion	4                       // This must be changed any time the format changes!
#define ArchiveInfo     "FAKK Archive Version 4" // This must be changed any time the format changes!

CLASS_DECLARATION( Class, FileRead, NULL )
	{
		{ NULL, NULL }
	};

FileRead::FileRead()
	{
   length = 0;
   buffer = NULL;
   pos = 0;
   }

FileRead::~FileRead()
	{
   Close();
   }

void FileRead::Close
   (
   void
   )

   {
	if ( buffer )
		{
		gi.Free( ( void * )buffer );
      buffer = NULL;
		}

   filename = "";
   length = 0;
   pos = 0;
   }

const char *FileRead::Filename
   (
   void
   )

   {
   return filename.c_str();
   }

size_t FileRead::Length
   (
   void
   )

   {
   return length;
   }

size_t FileRead::Pos
   (
   void
   )

   {
   return pos - buffer;
   }

qboolean FileRead::Seek
   (
   size_t newpos
   )

   {
   if ( !buffer )
      {
      return false;
      }

   if ( newpos > length )
      {
      return false;
      }

   pos = buffer + newpos;

   return true;
   }

qboolean FileRead::Open
   (
   const char *name
   )

   {
   byte  *tempbuf;
   assert( name );

   assert( !buffer );
   Close();

   if ( !name )
      {
      return false;
      }

	length = gi.FS_ReadFile( name, ( void ** )&tempbuf, qtrue );
	if ( length == ( size_t )( -1 ) )
		{
      return false;
      }
   // create our own space
   buffer = ( byte * )gi.Malloc( length );
   // copy the file over to our space
   memcpy( buffer, tempbuf, length );
   // free the file
   gi.FS_FreeFile( tempbuf );

   filename = name;
   pos = buffer;

   return true;
   }

qboolean FileRead::Read
   (
   void *dest,
   size_t size
   )

   {
   assert( dest );
   assert( buffer );
   assert( pos );

   if ( !dest )
      {
      return false;
      }

   if ( size <= 0 )
      {
      return false;
      }

   if ( ( pos + size ) > ( buffer + length ) )
      {
      return false;
      }

   memcpy( dest, pos, size );
   pos += size;

   return true;
   }

CLASS_DECLARATION( Class, Archiver, NULL )
	{
		{ NULL, NULL }
	};

Archiver::Archiver()
	{
	file = 0;
	fileerror = false;
   harderror = true;
	assert( ( sizeof( typenames ) / sizeof( typenames[ 0 ] ) ) == ARC_NUMTYPES );
	}

Archiver::~Archiver()
	{
	if ( file )
		{
		Close();
		}

   readfile.Close();
	}

void Archiver::FileError
	(
	const char *fmt,
	...
	)

	{
	va_list	argptr;
	char		text[ 1024 ];

	va_start( argptr, fmt );
	vsprintf( text, fmt, argptr );
	va_end( argptr );

	fileerror = true;
	Close();
	if ( archivemode == ARCHIVE_READ )
		{
      if ( harderror )
         {
		   gi.Error( ERR_DROP, "Error while loading %s : %s\n", filename.c_str(), text );
         }
      else
         {
         gi.Printf( "Error while loading %s : %s\n", filename.c_str(), text );
         }
		}
	else
		{
      if ( harderror )
         {
   		gi.Error( ERR_DROP, "Error while writing to %s : %s\n", filename.c_str(), text );
         }
      else
         {
         gi.Printf( "Error while writing to %s : %s\n", filename.c_str(), text );
         }
		}
	}

void Archiver::Close
	(
	void
	)

	{
	if ( file )
		{
      if ( archivemode == ARCHIVE_WRITE )
         {
         int numobjects;

         // write out the number of classpointers
		   gi.FS_FSeek( file, numclassespos, FS_SEEK_SET );
         numclassespos = gi.FS_FTell( file );
         numobjects = classpointerList.NumObjects();
         ArchiveInteger( &numobjects );
         }

		gi.FS_FCloseFile( file );
      file = NULL;
		}

   readfile.Close();

	if ( archivemode == ARCHIVE_READ )
      {
      int i, num;
      Class * classptr;
      pointer_fixup_t *fixup;

      num = fixupList.NumObjects();
      for( i = 1; i <= num; i++ )
         {
         fixup = fixupList.ObjectAt( i );
         classptr = classpointerList.ObjectAt( fixup->index );
         if ( fixup->type == pointer_fixup_normal )
            {
            Class ** fixupptr;
            fixupptr = ( Class ** )fixup->ptr;
            *fixupptr = classptr;
            }
         else if ( fixup->type == pointer_fixup_safe )
            {
            SafePtrBase * fixupptr;
            fixupptr = ( SafePtrBase * )fixup->ptr;
            fixupptr->InitSafePtr( classptr );
            }
         delete fixup;
         }
      fixupList.FreeObjectList();
      classpointerList.FreeObjectList();
      }
	}

/****************************************************************************************

  File Read/Write functions

*****************************************************************************************/

qboolean Archiver::Read
	(
   const char *name,
   qboolean harderror
	)

	{
	unsigned header;
	unsigned version;
	str		info;
   int      num;
   int      i;
   Class    *null;

   this->harderror = harderror;

   assert( name );
   if ( !name )
      {
      FileError( "NULL pointer for filename in Archiver::Read.\n" );
      return false;
      }

	fileerror = false;

	archivemode = ARCHIVE_READ;

	filename = name;

	if ( !readfile.Open( filename.c_str() ) )
		{
      if ( harderror )
         {
		   FileError( "Couldn't open file." );
         }
      return false;
		}

	ArchiveUnsigned( &header );
	if ( header != ArchiveHeader )
		{
      readfile.Close();
		FileError( "Not a valid Fakk2 archive." );
      return false;
		}

	ArchiveUnsigned( &version );
	if ( version > ArchiveVersion )
		{
		readfile.Close();
		FileError( "Archive is from version %.2f.  Check http://www.ritual.com for an update.", version );
      return false;
		}

	if ( version < ArchiveVersion )
		{
		readfile.Close();
		FileError( "Archive is out of date." );
      return false;
		}

	ArchiveString( &info );
   gi.DPrintf( "%s\n", info.c_str() );

   // setup out class pointers
   ArchiveInteger( &num );
   classpointerList.Resize( num );
   null = NULL;
   for( i = 1; i <= num; i++ )
      {
      classpointerList.AddObject( null );
      }

   return true;
	}

qboolean Archiver::Create
	(
	const char *name,
   qboolean harderror
	)

	{
   unsigned header;
   unsigned version;
   str      info;
   int      numZero = 0;

   this->harderror = harderror;

   assert( name );
   if ( !name )
      {
      FileError( "NULL pointer for filename in Archiver::Create.\n" );
      return false;
      }

	fileerror = false;

	archivemode = ARCHIVE_WRITE;

	filename = name;

   file = gi.FS_FOpenFileWrite( filename.c_str() );
	if ( !file )
		{
		FileError( "Couldn't open file." );
      return false;
		}

   header = ArchiveHeader;
	ArchiveUnsigned( &header );
   version = ArchiveVersion;
	ArchiveUnsigned( &version );
   info = ArchiveInfo;
	ArchiveString( &info );

  	numclassespos = gi.FS_FTell( file );
   ArchiveInteger( &numZero );

   return true;
	}


inline void Archiver::CheckRead
	(
	void
	)

	{
	assert( archivemode == ARCHIVE_READ );
	if ( !fileerror && ( archivemode != ARCHIVE_READ ) )
		{
		FileError( "File read during a write operation." );
		}
	}

inline void Archiver::CheckWrite
	(
	void
	)

	{
	assert( archivemode == ARCHIVE_WRITE );
	if ( !fileerror && ( archivemode != ARCHIVE_WRITE ) )
		{
		FileError( "File write during a read operation." );
		}
	}

inline size_t Archiver::ReadSize
   (
   void
   )

   {
   size_t s;

   s = 0;
   if ( !fileerror )
      {
      readfile.Read( &s, sizeof( s ) );
      }

   return s;
   }

inline void Archiver::CheckSize
   (
   int type,
   size_t size
   )

   {
   size_t s;

   if ( !fileerror )
      {
      s = ReadSize();

      if ( size != s )
         {
         FileError( "Invalid data size of %d on %s.", s, typenames[ type ] );
         }
      }
   }

inline void Archiver::WriteSize
   (
   size_t size
   )

   {
   gi.FS_Write( &size, sizeof( size ), file );
   }

inline int Archiver::ReadType
	(
	void
	)

	{
	int t;

	if ( !fileerror )
		{
      readfile.Read( &t, sizeof( t ) );

      return t;
		}

   return ARC_NULL;
	}

inline void Archiver::WriteType
	(
	int type
	)

	{
   gi.FS_Write( &type, sizeof( type ), file );
	}


inline void Archiver::CheckType
	(
	int type
	)

	{
	int t;

	assert( ( type >= 0 ) && ( type < ARC_NUMTYPES ) );

	if ( !fileerror )
		{
      t = ReadType();
		if ( t != type )
			{
			FileError( "Expecting %s", typenames[ type ] );
			}
		}
	}

/****************************************************************************************

  File Archive functions

*****************************************************************************************/

//#define ARCHIVE_USE_TYPES 1

inline void Archiver::ArchiveData
	(
	int type,
	void *data,
	size_t size
	)
	{
	if ( archivemode == ARCHIVE_READ )
      {
#ifndef NDEBUG
	   CheckRead();
#endif
#ifdef ARCHIVE_USE_TYPES
	   CheckType( type );
#endif

	   if ( !fileerror && size )
		   {
         readfile.Read( data, size );
		   }
      }
   else
      {
#ifndef NDEBUG
	   CheckWrite();
#endif
#ifdef ARCHIVE_USE_TYPES
	   WriteType( type );
#endif

	   if ( !fileerror && size )
		   {
         gi.FS_Write( data, size, file );
		   }
      }
	}


#define ARCHIVE( func, type )								\
void Archiver::Archive##func								\
	(																\
	type * v														\
	)																\
																	\
	{																\
	ArchiveData( ARC_##func, v, sizeof( type ) );	\
	}

	ARCHIVE( Vector, Vector );
	ARCHIVE( Integer, int );
	ARCHIVE( Unsigned, unsigned );
	ARCHIVE( Byte, byte );
	ARCHIVE( Char, char );
	ARCHIVE( Short, short );
	ARCHIVE( UnsignedShort, unsigned short );
	ARCHIVE( Float, float );
	ARCHIVE( Double, double );
	ARCHIVE( Boolean, qboolean );
	ARCHIVE( Quat, Quat );
	ARCHIVE( Bool, bool );

void Archiver::ArchiveVec3( vec3_t vec )
   {
   ArchiveData( ARC_Vec3, vec, sizeof( vec3_t ) );
   }

void Archiver::ArchiveVec4( vec4_t vec )
   {
   ArchiveData( ARC_Vec4, vec, sizeof( vec4_t ) );
   }

void Archiver::ArchiveObjectPointer
	(
   Class ** ptr
	)

	{
   int index = 0;

	if ( archivemode == ARCHIVE_READ )
      {
      pointer_fixup_t *fixup;
	   ArchiveData( ARC_ObjectPointer, &index, sizeof( index ) );

      // Check for a NULL pointer
      assert( ptr );
      if ( !ptr )
         {
         FileError( "NULL pointer in ArchiveObjectPointer." );
         }

      //
      // see if the variable was NULL
      //
      if ( index == ARCHIVE_NULL_POINTER )
         {
         *ptr = NULL;
         }
      else
         {
         // init the pointer with NULL until we can fix it
         *ptr = NULL;

         fixup = new pointer_fixup_t;
         fixup->ptr = ( void ** )ptr;
         fixup->index = index;
         fixup->type = pointer_fixup_normal;
         fixupList.AddObject( fixup );
         }
      }
   else
      {
      if ( *ptr )
         {
         index = classpointerList.AddUniqueObject( *ptr );
         }
      else
         {
         index = ARCHIVE_NULL_POINTER;
         }
      ArchiveData( ARC_ObjectPointer, &index, sizeof( index ) );
      }
	}

void Archiver::ArchiveSafePointer
	(
   SafePtrBase * ptr
	)

	{
   int index = 0;

	if ( archivemode == ARCHIVE_READ )
      {
      pointer_fixup_t *fixup;

	   ArchiveData( ARC_SafePointer, &index, sizeof( &index ) );

      // Check for a NULL pointer
      assert( ptr );
      if ( !ptr )
         {
         FileError( "NULL pointer in ReadSafePointer." );
         }

      //
      // see if the variable was NULL
      //
      if ( index == ARCHIVE_NULL_POINTER )
         {
         ptr->InitSafePtr( NULL );
         }
      else
         {
         // init the pointer with NULL until we can fix it
         ptr->InitSafePtr( NULL );

         // Add new fixup
         fixup = new pointer_fixup_t;
         fixup->ptr = ( void ** )ptr;
         fixup->index = index;
         fixup->type = pointer_fixup_safe;
         fixupList.AddObject( fixup );
         }
      }
   else
      {
      if ( ptr->Pointer() )
         {
         Class * obj;

         obj = ptr->Pointer();
         index = classpointerList.AddUniqueObject( obj );
         }
      else
         {
         index = ARCHIVE_NULL_POINTER;
         }
	   ArchiveData( ARC_SafePointer, &index, sizeof( index ) );
      }
	}

void Archiver::ArchiveEvent
	(
   Event * ev
	)

	{
	if ( archivemode == ARCHIVE_READ )
      {
#ifndef NDEBUG
	   CheckRead();
#endif
#ifdef ARCHIVE_USE_TYPES
	   CheckType( ARC_Event );
#endif

	   if ( !fileerror )
		   {
         ev->Archive( *this );
	   	}
      }
   else
      {
#ifndef NDEBUG
	   CheckWrite();
#endif
#ifdef ARCHIVE_USE_TYPES
      WriteType( ARC_Event );
#endif

      //FIXME!!!! Make this handle null events
      if ( ev == NULL )
         {
         NullEvent.Archive( *this );
         }
      else
         {
         ev->Archive( *this );
         }
      }
	}

void Archiver::ArchiveEventPointer
	(
   Event ** ev
	)

	{
   int index;

	if ( archivemode == ARCHIVE_READ )
      {
#ifndef NDEBUG
	   CheckRead();
#endif
#ifdef ARCHIVE_USE_TYPES
	   CheckType( ARC_EventPointer );
#endif
      ArchiveInteger( &index );

	   if ( !fileerror )
		   {
         if ( index == ARCHIVE_POINTER_VALID )
            {
            *ev = new Event;
            (*ev)->Archive( *this );
            }
         else
            {
            (*ev) = NULL;
            }
	   	}
      }
   else
      {
#ifndef NDEBUG
	   CheckWrite();
#endif
      if ( *ev )
         {
         index = ARCHIVE_POINTER_VALID;
         }
      else
         {
         index = ARCHIVE_NULL_POINTER;
         }

#ifdef ARCHIVE_USE_TYPES
      WriteType( ARC_EventPointer );
#endif

      ArchiveInteger( &index );
      if ( *ev )
         {
         (*ev)->Archive( *this );
         }
      }
	}

void Archiver::ArchiveRaw
	(
	void *data,
	size_t size
	)

	{
	ArchiveData( ARC_Raw, data, size );
	}

void Archiver::ArchiveString
	(
	str * string
	)

	{
	if ( archivemode == ARCHIVE_READ )
      {
	   size_t	s;
	   char		*data;

#ifndef NDEBUG
	   CheckRead();
#endif
#ifdef ARCHIVE_USE_TYPES
	   CheckType( ARC_String );
#endif

	   if ( !fileerror )
		   {
		   s = ReadSize();
		   if ( !fileerror )
			   {
			   data = new char[ s + 1 ];
            if ( data )
               {
               if ( s )
                  {
                  readfile.Read( data, s );
                  }
			      data[ s ] = 0;

			      *string = data;

			      delete [] data;
               }
			   }
		   }
      }
   else
      {
#ifndef NDEBUG
	   CheckWrite();
#endif
#ifdef ARCHIVE_USE_TYPES
	   WriteType( ARC_String );
#endif
	   WriteSize( string->length() );
   	gi.FS_Write( string->m_data->data, string->length(), file );
      }
	}

Class * Archiver::ReadObject
	(
   void
	)

	{
	ClassDef	*cls;
	Class		*obj;
	str		classname;
	long		objstart;
	long		endpos;
   int      index;
	size_t	size;
   qboolean isent;
   int      type;

	CheckRead();

   type = ReadType();
   if ( ( type != ARC_Object ) && ( type != ARC_Entity ) )
      {
      FileError( "Expecting %s or %s", typenames[ ARC_Object ], typenames[ ARC_Entity ] );
      }

	size = ReadSize();
	ArchiveString( &classname );

   cls = getClass( classname.c_str() );
	if ( !cls )
      {
		FileError( "Invalid class %s.", classname.c_str() );
		}

   isent = checkInheritance( &Entity::ClassInfo, cls );
   if ( type == ARC_Entity )
      {
      if ( !isent )
         {
   		FileError( "Non-Entity class object '%s' saved as an Entity based object.", classname.c_str() );
         }

		ArchiveInteger( &level.spawn_entnum );
      //
      // make sure to setup spawnflags properly
      //
      ArchiveInteger( &level.spawnflags );
      }
   else if ( isent )
      {
      FileError( "Entity class object '%s' saved as non-Entity based object.", classname.c_str() );
      }

	ArchiveInteger( &index );
	objstart = readfile.Pos();


	obj = ( Class * )cls->newInstance();
	if ( !obj )
		{
		FileError( "Failed to on new instance of class %s.", classname.c_str() );
		}
	else
		{
		obj->Archive( *this );
		}

	if ( !fileerror )
		{
		endpos = readfile.Pos();
		if ( ( endpos - objstart ) > size )
			{
			FileError( "Object read past end of object's data" );
			}
		else if ( ( endpos - objstart ) < size )
			{
			FileError( "Object didn't read entire data from file" );
			}
		}

   //
   // register this pointer with our list
   //
   classpointerList.AddObjectAt( index, obj );

	return obj;
	}

void Archiver::ArchiveObject
	(
	Class *obj
	)

	{
   str		classname;
   int      index;
   size_t	size;
   qboolean isent;

	if ( archivemode == ARCHIVE_READ )
      {
	   ClassDef	*cls;
	   long		objstart;
	   long		endpos;
      int      type;

	   CheckRead();
      type = ReadType();
      if ( ( type != ARC_Object ) && ( type != ARC_Entity ) )
         {
         FileError( "Expecting %s or %s", typenames[ ARC_Object ], typenames[ ARC_Entity ] );
         }

      size = ReadSize();
	   ArchiveString( &classname );

      cls = getClass( classname.c_str() );
	   if ( !cls )
         {
		   FileError( "Invalid class %s.", classname.c_str() );
		   }

	   if ( obj->classinfo() != cls )
		   {
		   FileError( "Archive has a '%s' object, but was expecting a '%s' object.", classname.c_str(), obj->getClassname() );
		   }

      isent = obj->isSubclassOf( Entity );
      if ( type == ARC_Entity )
         {
         int entnum;
         if ( !isent )
            {
   		   FileError( "Non-Entity class object '%s' saved as an Entity based object.", classname.c_str() );
            }

         ArchiveInteger( &entnum );
         ( ( Entity * )obj )->SetEntNum( entnum );
         //
         // make sure to setup spawnflags properly
         //
         ArchiveInteger( &level.spawnflags );
         }
      else if ( isent )
         {
         FileError( "Entity class object '%s' saved as non-Entity based object.", classname.c_str() );
         }

	   ArchiveInteger( &index );
	   objstart = readfile.Pos();

      obj->Archive( *this );

	   if ( !fileerror )
		   {
		   endpos = readfile.Pos();
		   if ( ( endpos - objstart ) > size )
			   {
			   FileError( "Object read past end of object's data" );
			   }
		   else if ( ( endpos - objstart ) < size )
			   {
			   FileError( "Object didn't read entire data from file" );
			   }
		   }

      //
      // register this pointer with our list
      //
      classpointerList.AddObjectAt( index, obj );
      }
   else
      {
	   long		sizepos;
	   long		objstart = 0;
	   long		endpos;

	   assert( obj );
	   if ( !obj )
		   {
		   FileError( "NULL object in WriteObject" );
		   }

      isent = obj->isSubclassOf( Entity );

	   CheckWrite();
      if ( isent )
         {
         WriteType( ARC_Entity );
         }
      else
         {
	      WriteType( ARC_Object );
         }

	   sizepos = gi.FS_FTell( file );
	   size = 0;
	   WriteSize( size );

	   classname = obj->getClassname();
	   ArchiveString( &classname );

      if ( isent )
         {
         // Write out the entity number
         ArchiveInteger( &( ( Entity * )obj )->entnum );
         //
         // make sure to setup spawnflags properly
         //
         ArchiveInteger( &( ( Entity * )obj )->spawnflags );
         }

      // write out pointer index for this class pointer
      index = classpointerList.AddUniqueObject( obj );
      ArchiveInteger( &index );

	   if ( !fileerror )
		   {
		   objstart = gi.FS_FTell( file );
		   obj->Archive( *this );
		   }

	   if ( !fileerror )
		   {
		   endpos = gi.FS_FTell( file );
		   size = endpos - objstart;
		   gi.FS_FSeek( file, sizepos, FS_SEEK_SET );
		   WriteSize( size );

		   if ( !fileerror )
			   {
			   gi.FS_FSeek( file, endpos, FS_SEEK_SET );
			   }
		   }
      }
	}


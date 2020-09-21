//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/archive.h                          $
// $Revision:: 7                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 5/31/00 10:19a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/archive.h                               $
// 
// 7     5/31/00 10:19a Markd
// 4th pass saved games
// 
// 6     5/30/00 7:06p Markd
// saved games 4th pass
// 
// 5     5/27/00 8:06p Markd
// Saved games 3rd pass
// 
// 4     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 3     5/26/00 7:44p Markd
// 2nd phase save games
// 
// 2     5/25/00 4:28p Markd
// fixed up archive functions
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 5     7/29/99 5:33p Markd
// Fixed weird compiler bug
// 
// DESCRIPTION:
// Class for archiving objects
// 

#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include "g_local.h"
#include "class.h"
#include "str.h"

#define ARCHIVE_NULL_POINTER ( -654321 )
#define ARCHIVE_POINTER_VALID ( 0 )
#define ARCHIVE_POINTER_NULL ( ARCHIVE_NULL_POINTER )
#define ARCHIVE_POINTER_SELF_REFERENTIAL ( -123456 )

#define ARCHIVE_WRITE 0
#define ARCHIVE_READ  1

enum
	{
   pointer_fixup_normal,
   pointer_fixup_safe
	};

typedef struct
   {
   void **ptr;
   int  index;
   int  type;
   } pointer_fixup_t;

class FileRead : public Class
	{
	protected:
		str				filename;
      size_t         length;
      byte           *buffer;
      byte           *pos;

	public:
      CLASS_PROTOTYPE( FileRead );

							FileRead();
							~FileRead();
		void				Close( void );
      const char     *Filename( void );
      size_t         Length( void );
      size_t         Pos( void );
      qboolean       Seek( size_t newpos );
      qboolean       Open( const char *name );
      qboolean       Read( void *dest, size_t size );
	};

class Archiver : public Class
	{
   private:
      Container<Class *>         classpointerList;
      Container<pointer_fixup_t *> fixupList;

	protected:
		str				filename;
		qboolean			fileerror;
		fileHandle_t   file;
      FileRead       readfile;
		int				archivemode;
      int            numclassespos;
      qboolean       harderror;

		void				CheckRead( void );
		void				CheckType( int type );
		int            ReadType( void );
		size_t			ReadSize( void );
		void				CheckSize( int type, size_t size );
		void				ArchiveData( int type, void *data, size_t size );

		void				CheckWrite( void );
		void				WriteType( int type );
		void				WriteSize( size_t size );

	public:
      CLASS_PROTOTYPE( Archiver );

							Archiver();
							~Archiver();
		void				FileError( const char *fmt, ... );
		void				Close( void );

		qboolean       Read( str &name, qboolean harderror = true );
		qboolean       Read( const char *name, qboolean harderror = true );
		Class				*ReadObject( void );

		qboolean       Create( str &name, qboolean harderror = true );
		qboolean       Create( const char *name, qboolean harderror = true );

      qboolean       Loading( void );
      qboolean       Saving( void );
      qboolean       NoErrors( void );

		void  			ArchiveVector( Vector * vec );
		void  			ArchiveQuat( Quat * quat );
		void				ArchiveInteger( int * num );
		void  			ArchiveUnsigned( unsigned * unum);
		void				ArchiveByte( byte * num );
		void				ArchiveChar( char * ch );
		void				ArchiveShort( short * num );
		void           ArchiveUnsignedShort( unsigned short * num );
		void           ArchiveFloat( float * num );
		void			   ArchiveDouble( double * num );
		void  			ArchiveBoolean( qboolean * boolean );
		void  			ArchiveString( str * string );
		void           ArchiveObjectPointer( Class ** ptr );
		void           ArchiveSafePointer( SafePtrBase * ptr );
		void           ArchiveEvent( Event * ev );
		void           ArchiveEventPointer( Event ** ev );
		void  			ArchiveBool( bool * boolean );
		void  			ArchiveVec3( vec3_t vec );
		void  			ArchiveVec4( vec4_t vec );

		void				ArchiveRaw( void *data, size_t size );
		void				ArchiveObject( Class *obj );

	};

inline qboolean Archiver::Read
   (
   str &name,
   qboolean harderror
   )

   {
   return Read( name.c_str(), harderror );
   }

inline qboolean Archiver::Create
   (
   str &name,
   qboolean harderror
   )

   {
   return Create( name.c_str(), harderror );
   }

inline qboolean Archiver::Loading
   (
   void
   )
   {
	return ( archivemode == ARCHIVE_READ );
   }

inline qboolean Archiver::Saving
   (
   void
   )
   {
	return ( archivemode == ARCHIVE_WRITE );
   }

inline qboolean Archiver::NoErrors
   (
   void
   )
   {
	return ( !fileerror );
   }

inline void Container<str>::Archive
	(
   Archiver &arc
	)
	{
   int i, num;

   if ( arc.Loading() )             
      {                             
      ClearObjectList();              
      arc.ArchiveInteger( &num );    
      Resize( num );                
      }                             
   else                             
      {                             
      num = numobjects;             
      arc.ArchiveInteger( &num );    
      }
   for( i = 1; i <= num; i++ )
      {
      arc.ArchiveString( AddressOfObjectAt( i ) );
      }
	}

inline void Container<Vector>::Archive
	(
   Archiver &arc
	)
	{
   int i, num;

   if ( arc.Loading() )             
      {                             
      ClearObjectList();              
      arc.ArchiveInteger( &num );    
      Resize( num );                
      }                             
   else                             
      {                             
      num = numobjects;             
      arc.ArchiveInteger( &num );    
      }
   for( i = 1; i <= num; i++ )
      {
      arc.ArchiveVector( AddressOfObjectAt( i ) );
      }
	}

inline void Container<int>::Archive
	(
   Archiver &arc
	)
	{
   int i, num;

   if ( arc.Loading() )             
      {                             
      ClearObjectList();              
      arc.ArchiveInteger( &num );    
      Resize( num );                
      }                             
   else                             
      {                             
      num = numobjects;             
      arc.ArchiveInteger( &num );    
      }
   for( i = 1; i <= num; i++ )
      {
      arc.ArchiveInteger( AddressOfObjectAt( i ) );
      }
	}

inline void Container<float>::Archive
	(
   Archiver &arc
	)
	{
   int i, num;

   if ( arc.Loading() )             
      {                             
      ClearObjectList();              
      arc.ArchiveInteger( &num );    
      Resize( num );                
      }                             
   else                             
      {                             
      num = numobjects;             
      arc.ArchiveInteger( &num );    
      }
   for( i = 1; i <= num; i++ )
      {
      arc.ArchiveFloat( AddressOfObjectAt( i ) );
      }
	}

#define ArchiveEnum( thing, type )  \
   {                                \
   int tempInt;                     \
                                    \
   tempInt = ( int )( thing );      \
   arc.ArchiveInteger( &tempInt );  \
   ( thing ) = ( type )tempInt;     \
   }           


#endif /* archive.h */

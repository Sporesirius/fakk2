//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max3plugins/skelout/skelout.h                $
// $Revision:: 12                                                             $
//     $Date:: 1/19/00 3:30p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max3plugins/skelout/skelout.h                     $
// 
// 12    1/19/00 3:30p Jimdose
// added cancel button to progress dialog
// 
// 11    10/18/99 5:16p Jimdose
// added cancel flag
// 
// 10    10/12/99 12:23p Jimdose
// made changes for Max 3 work with Max 2.5
// 
// 9     10/12/99 12:18p Jimdose
// made work with Max 3
// 
// 8     10/08/99 7:23p Jimdose
// added CollectMaterials
// 
// 7     10/06/99 12:44p Jimdose
// added GetVertexNormal
// 
// 6     10/04/99 8:19p Jimdose
// added GetNonRigidVertex
// 
// 5     9/07/99 5:39p Jimdose
// added progress dialog
// 
// 4     9/07/99 3:12p Jimdose
// rewrote for ascii output
// 
// 3     9/03/99 7:12p Jimdose
// working version
// 
// 2     7/30/99 4:23p Jimdose
// working on skel output
//
// DESCRIPTION:
// 

#ifndef __SKELOUT_H__
#define __SKELOUT_H__

#include "Max.h"
#include "container.h"
#include "str.h"
#include "phyexp.h"

#define MAXLOADVERTS       2048
#define MAXLOADFACES		   3072
#define MAXLOADOBJECTS	   32
#define MAX_FRAMES   	   2048
#define MAX_OBJECT_NAMES   32
#define MAX_MATERIALS      256
#define MAX_BLENDBONES     8
#define MAX_BONES          256

#define UNUSED_BONE        -1

// output file version number
#define SKL_VERSION        1

// 3DS Max module information
#define VERSION            100                        // Version number * 100 (i.e. v3.01 = 301)
#define EXTENSION          "skl"
#define LONG_DESCRIPTION   "FAKK2 Skeleton export"
#define SHORT_DESCRIPTION  "FAKK2 Skeleton export"
#define AUTHOR             "Jim Dosé"
#define COPYRIGHT          "Copyright (c) 1999 by Ritual Entertainment, Inc. All Rights Reserved"
#define OTHER_MESSAGE1     ""
#define OTHER_MESSAGE2     ""

typedef struct
   {
   int   parent;
   float offset[ 3 ];
   float matrix[ 3 ][ 3 ];
   } loadbone_t;

typedef struct
   {
   int   bone;
	float	offset[ 3 ];
   float weight;
   } blendvert_t;

typedef struct
   {
   int         numbones;
   blendvert_t blend[ MAX_BLENDBONES ];
   float       normal[ 3 ];
   } loadvertx_t;

typedef struct
   {
   int   vertindex;
   float s;
   float t;
   } loadfacevertx_t;

typedef struct
   {
   int               id;
   loadfacevertx_t   verts[ 3 ];
   } loadtriangle_t;

typedef struct
   {
   char name[ 128 ];
   int  startvert;
   int  startface;
   int  numverts;
   int  numfaces;
   } loadobject_t;

typedef struct
   {
   char           name[ 128 ];
   int            numverts;
   int            numfaces;
   int            numobjects;
   int            nummaterials;
   int            hasmapping;
   loadobject_t   objects[ MAXLOADOBJECTS ];
   loadtriangle_t faces[ MAXLOADFACES ];
   loadvertx_t    verts[ MAXLOADVERTS ];
   int            materials[ MAX_MATERIALS ];
   bool           usedbone[ MAX_BONES ];
   int            numbonesused;
   } loadsinglefile_t;

typedef struct
   {
   loadbone_t     bones[ MAX_BONES ];
   } loadframe_t;

class SkelExport : public SceneExport
   {
   private:
      static BOOL CALLBACK StatusDlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );
      static BOOL CALLBACK GetAnimScaleDlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );
      
      static int        s_startframe;
      static int        s_stopframe;
      static double     s_framerate;
      static double     s_samplerate;
      static bool       cancel;
                        
      void              GetAnimScale( void );
                        
      int               startframe;
      int               stopframe;
      double            framerate;
      double            samplerate;

      IPhyContextExport *context;
      Mesh              *mesh;

      loadsinglefile_t  model;
      loadframe_t       single;

      Container<str>    bonenames;
      Container<str>    objectnames;
      Container<int>    sorted;

      HWND              statusDialog;
      HWND              progressBar;
      HWND              statusText;
      
      Interface         *interfaceptr;

      void              GetNonRigidVertex( INode *node, loadvertx_t *vert, int index );
      void              GetPhysiqueVertex( loadvertx_t *vert, int index );
      int               GetNodeIndex( INode *pnode );
      Modifier          *FindPhysiqueModifier( INode *nodePtr );
      void              GetVertexNormal( int vertindex, int smoothingGroup, float normal[ 3 ] );

      void              CollectMaterials( void );

      void              SortObjectNames( Container<int> &sorted );
      void              SaveAnimFile( const char *filename, loadframe_t *anim, int numframes, float framerate );
      void              SaveAnimFileText( const char *filename, loadframe_t *anim, int numframes, float framerate );

      void              ShowProgressBar( const char *title );
      void              UpdateProgressBar( float percentComplete );
      void              SetStatusText( const char *text );
      void              CloseProgressBar( void );

   public:
                        SkelExport();
                        ~SkelExport();
      int			      ExtCount();					// Number of extensions supported
   	const TCHAR *	   Ext( int n );				// Extension #n (i.e. "ACS")
	   const TCHAR *	   LongDesc();
	   const TCHAR *	   ShortDesc();
	   const TCHAR *	   AuthorName();				// ASCII Author name
	   const TCHAR *	   CopyrightMessage();		// ASCII Copyright message
	   const TCHAR *	   OtherMessage1();			// Other message #1
	   const TCHAR *	   OtherMessage2();			// Other message #2
	   unsigned int	   Version();					// Version number * 100 (i.e. v3.01 = 301)
	   void			      ShowAbout( HWND hWnd ); // Show DLL's "About..." box

#if ( MAX_RELEASE >= 3000 )
      int               DoExport( const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0 ); // Export file
#elif ( MAX_RELEASE >= 2000 )
      int               DoExport( const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE );	// Export file
#else
      int               DoExport( const TCHAR *name, ExpInterface *ei, Interface *i );	// Export file
#endif

      void              AddObject( Object *obj, INode *node );
      void              AddBoneFrame( Object *obj, INode *node );                        
	};                   

class SkelOutClassDesc : public ClassDesc
   {
	public:
      int 			   IsPublic()                       { return 1; }
      void *         Create( BOOL loading = FALSE )   { return new SkelExport; }
      const TCHAR *  ClassName()                      { return _T( "Skel Export" ); }
      SClass_ID		SuperClassID()                   { return SCENE_EXPORT_CLASS_ID; }
      Class_ID       ClassID()                        { return Class_ID( 0xcfb1563, 0x7975414f ); }
      const TCHAR*   Category()                       { return _T( "Export" ); }
	};

extern SkelOutClassDesc SkelOutDesc;

#endif /* !__SKELOUT_H__ */

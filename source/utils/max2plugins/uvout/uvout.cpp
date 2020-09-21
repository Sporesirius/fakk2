/**********************************************************************
 *<
   FILE: uvout.cpp

   DESCRIPTION:  A MAX2 plugin that outputs texture coordinates and materials

	CREATED BY: Mark Dochtermann

   HISTORY: created 3/31/99 11:22AM

 *>   Copyright (c) 1999, All Rights Reserved.
 **********************************************************************/
#include "Max.h"
typedef bool qboolean;

#if (MAX_RELEASE >= 3000)
#pragma comment( lib, "core.lib" )
#pragma comment( lib, "util.lib" )
#pragma comment( lib, "mesh.lib" )
#pragma comment( lib, "geom.lib" )
#endif

#define MAXLOADVERTS       2048
#define MAXLOADFACES		   3072
#define MAXLOADOBJECTS	   32

typedef struct
   {
	float	v[3];
   } loadvertx_t;

typedef struct
   {
   int vertindex;
   float s;
   float t;
   } loadfacevertx_t;

typedef struct
   {
   int id;
   loadfacevertx_t verts[3];
   } loadtriangle_t;

typedef struct
   {
   char name[128];
   int  startvert;
   int  startface;
   int  numverts;
   int  numfaces;
   } loadobject_t;

typedef struct
   {
   char           name[128];
   int            numverts;
   int            numfaces;
   int            numobjects;
   int            hasmapping;
   loadobject_t   objects[MAXLOADOBJECTS];
   loadtriangle_t faces[MAXLOADFACES];
   loadvertx_t    verts[MAXLOADVERTS];
   } loadsinglefile_t;

static HINSTANCE hInstance;
static int controlsInit = FALSE;

void AddObject( Object *obj, INode *node, loadsinglefile_t * load );

class GetObjectsEnumProc : public ITreeEnumProc
    {
	public:
		int callback( INode *node );
	};

static GetObjectsEnumProc theGetObjectsEnumProc;

#define MAX_OBJECT_NAMES 32
char objectnames[MAX_OBJECT_NAMES][32];
int numobjects = 0;
int currentobject = 0;

class GetNamesEnumProc : public ITreeEnumProc
    {
	public:
		int callback( INode *node );
	};

static GetNamesEnumProc theGetNamesEnumProc;


static Interface * interfaceptr;

loadsinglefile_t single;

class _UVExport : public SceneExport {

public:
                  _UVExport();
                  ~_UVExport();
	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "ACS")
	const TCHAR *	LongDesc();
	const TCHAR *	ShortDesc();
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
#if (MAX_RELEASE >= 3000)
	int		      DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0); // Export file
#elif (MAX_RELEASE > 1000)
	int				DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE);	// Export file
#else
	int				DoExport(const TCHAR *name,ExpInterface *ei,Interface *i);	// Export file
#endif
	};
//
// ._UV export module functions follow:
//

_UVExport::_UVExport() {
	}

_UVExport::~_UVExport() {
	}

int
_UVExport::ExtCount() {
	return 1;
	}

const TCHAR *
_UVExport::Ext(int n) {      // Extensions supported for import/export modules
	switch(n) {
		case 0:
         return _T("UV");
		}
	return _T("");
	}

const TCHAR *
_UVExport::LongDesc() {         // Long ASCII description (i.e. "Targa 2.0 Image File")
   return _T("UV Single export");
	}

const TCHAR *
_UVExport::ShortDesc() {        // Short ASCII description (i.e. "Targa")
   return _T("UV Single export");
	}

const TCHAR *
_UVExport::AuthorName() {       // ASCII Author name
	return _T("Mark Dochtermann");
	}

const TCHAR *
_UVExport::CopyrightMessage() { // ASCII Copyright message
	return _T("Copyright (c) 1996. All Rights Reserved");
	}

const TCHAR *
_UVExport::OtherMessage1() {    // Other message #1
	return _T("");
	}

const TCHAR *
_UVExport::OtherMessage2() {    // Other message #2
	return _T("");
	}

unsigned int
_UVExport::Version() {          // Version number * 100 (i.e. v3.01 = 301)
	return 101;
	}

void
_UVExport::ShowAbout(HWND hWnd) {        // Optional
 	}

class UVOutClassDesc:public ClassDesc {
	public:
	int 			IsPublic() {return 1;}
   void *         Create(BOOL loading = FALSE) {return new _UVExport;}
   const TCHAR *  ClassName() {return _T("UV Export");}
	SClass_ID		SuperClassID() {return SCENE_EXPORT_CLASS_ID;}
   Class_ID    ClassID() {return Class_ID(0x69ed2b98, 0x210e37b9);}
   const TCHAR*   Category() {return _T("Export");}
	};

static UVOutClassDesc UVOutDesc;

int GetObjectsEnumProc::callback(INode *node)
   {
   Object *obj = node->EvalWorldState(interfaceptr->GetTime()).obj;

   if (obj->IsDeformable() && obj->CanConvertToType(triObjectClassID))
      {
      if (!strcmpi( node->GetName(), objectnames[currentobject] ) )
         AddObject(obj, node, &single);
		}
   return TREE_CONTINUE;
	}

int GetNamesEnumProc::callback(INode *node)
   {
   Object *obj = node->EvalWorldState(interfaceptr->GetTime()).obj;

   if (
         obj->IsDeformable() && 
         obj->CanConvertToType(triObjectClassID) &&
         strnicmp( node->GetName(), "bip", 3 ) &&
         strnicmp( node->GetName(), "bone", 4 )
      )
      {
      if ( numobjects < MAX_OBJECT_NAMES )
         {
         int i;
         strcpy( objectnames[ numobjects ], node->GetName() );
         for (i=0;i<numobjects;i++)
            if (!strcmpi( objectnames[i], objectnames[numobjects] ) )
               {
               char str[128];
               sprintf( str, "Duplicate object %s.", objectnames[numobjects] );
	            MessageBox(NULL,str,"GetNamesEnumProc",MB_OK);
               }
         if (i==numobjects)
            numobjects++;
         }
		}
   return TREE_CONTINUE;
	}

void AddObject( Object *obj, INode *node, loadsinglefile_t * load )
	{
   int i,j;
	TriObject * tri;
   loadvertx_t * loadvert;
   loadtriangle_t * loadface;
   loadfacevertx_t * loadfacevert;
   loadobject_t * loadobject;
   Matrix3 tm;
   Point3 p;

   //
   // convert it into a triobject
   //
   tri = (TriObject *)obj->ConvertToType(interfaceptr->GetTime(), triObjectClassID);

   //
   // get the mesh
   //
	Mesh * mesh = &tri->mesh;
   if (!mesh) return;

   loadobject = &load->objects[ load->numobjects ];
   loadobject->startvert = load->numverts;
   loadobject->startface = load->numfaces;

   loadvert = &load->verts[ loadobject->startvert ];
   loadface = &load->faces[ loadobject->startface ];

   // get the name of this node
   strcpy( loadobject->name, node->GetName() );
   // get the number of vertices
   loadobject->numverts = mesh->getNumVerts();
   // get the number of faces
   loadobject->numfaces = mesh->getNumFaces();
   if ( !loadobject->numverts || !loadobject->numfaces )
      {
      char str[128];
      sprintf( str, "Object %s had no verts or faces", loadobject->name );
	   MessageBox(NULL,str,"AddObject",MB_OK);
      return;
      }
   // find out if there are TVerts
   load->hasmapping = ( mesh->getNumTVerts() > 0 );
   //
   // get tm for this object
   //
   tm = node->GetObjTMAfterWSM(interfaceptr->GetTime());
   //
   // start filling her up
   //
   // grab the vertices
   for (i=0;i<loadobject->numverts;i++, loadvert++)
      {
      p = tm * mesh->verts[i];
      loadvert->v[0] = p.x;
      loadvert->v[1] = p.y;
      loadvert->v[2] = p.z;
      }
   // grab the faces
   for (i=0;i<loadobject->numfaces;i++, loadface++)
      {
      for (j=0;j<3;j++)
         {
         loadfacevert = &loadface->verts[j];
         loadfacevert->vertindex = (mesh->faces[i].v[2-j] + loadobject->startvert);
         if (load->hasmapping)
            {
            loadfacevert->s = mesh->tVerts[ mesh->tvFace[i].t[2-j] ].x;
            loadfacevert->t = 1.0f - mesh->tVerts[ mesh->tvFace[i].t[2-j] ].y;
            }
         else
            {
            loadfacevert->s = 0.0f;
            loadfacevert->t = 0.0f;
            }
         }
      loadface->id = mesh->faces[i].getMatID();
      }
   load->numverts += loadobject->numverts;
   load->numfaces += loadobject->numfaces;
   load->numobjects++;
	}

void SortObjectNames( int * sorted )
   {
   int i,j,smallest;
   int processed[MAX_OBJECT_NAMES];

   //
   // Sort the object names
   //
   memset( &sorted[0], 0, sizeof(sorted) );
   memset( &processed[0], 0, sizeof(processed) );

   for (i=0;i<numobjects;i++)
      {
      smallest = -1;
      for (j=0;j<numobjects;j++)
         {
         if (processed[j])
            continue;
         if ( ( smallest < 0 ) || ( strcmpi(objectnames[j],objectnames[smallest]) < 0 ) )
            smallest = j;
         }
      sorted[i] = smallest;
      processed[ smallest ] = 1;
      }
   }

void Error (char *error, ...)
   {
	va_list argptr;
	char	text[1024];
	char	text2[1024];
	int		err;
   static in_error = false;;

   if (in_error)
      return;
   in_error = true;
	err = GetLastError ();

	va_start (argptr,error);
	vsprintf (text, error,argptr);
	va_end (argptr);

	sprintf (text2, "%s\nGetLastError() = %i", text, err);
   MessageBox(NULL, text2, "Error", 0 /* MB_OK */ );
   }

FILE *SafeOpenWriteText (const char *filename)
   {
	FILE	*f;

	f = fopen(filename, "w");

	if (!f)
		 Error("Error opening %s: %s",filename,strerror(errno));

	return f;
   }

void SafeRead (FILE *f, void *buffer, int count)
   {
	if ( fread (buffer, 1, count, f) != (size_t)count)
		Error ("File read failure");
   }


void SafeWrite (FILE *f, void *buffer, int count)
   {
	if (fwrite (buffer, 1, count, f) != (size_t)count)
		Error ("File write failure");
   }

void SafeStringWrite ( FILE *f, char *ptr, ... )
   {
	va_list argptr;
	char	text[1024];

	va_start( argptr, ptr );
	vsprintf( text, ptr, argptr );
	va_end( argptr );

   SafeWrite( f, text, strlen( text ) );
   }

#define UV_FILE_VERSION 2
#define MAX_MATERIALS 256
void SaveUVFile( loadsinglefile_t * single )
   {
   FILE * out;
   int i,j;
   int nummaterials;
   int materials[ MAX_MATERIALS ];
   loadtriangle_t * tri;

   out = SafeOpenWriteText( single->name );

   nummaterials = 0;
	for( i = 0; i < single->numfaces; i++ )
	   {
      for( j = 0; j < nummaterials; j++ )
         {
         if ( materials[ j ] == single->faces[ i ].id )
            break;
         }
      if ( j == nummaterials )
         {
         materials[ nummaterials++ ] = single->faces[ i ].id;
         }
      }
   // export the Version number
   SafeStringWrite( out, "version %d\n", UV_FILE_VERSION );

   // export the materials
   SafeStringWrite( out, "nummaterials %d\n", nummaterials );

   for( i = 0; i < nummaterials; i++ )
      {
      SafeStringWrite( out, "material %d material%d\n", materials[ i ]+1, materials[ i ]+1 );
      }

   // export the verts
   SafeStringWrite( out, "numverts %d\n", single->numverts );
   // export the verts
	for( i = 0; i < single->numverts; i++ )
      {
      SafeStringWrite( out, "%f %f %f\n", 
         single->verts[ i ].v[ 0 ],
         single->verts[ i ].v[ 1 ],
         single->verts[ i ].v[ 2 ]
         );
      }

   // export the faces
   SafeStringWrite( out, "numfaces %d\n", single->numfaces );
   // export the faces
	for( i = 0; i < single->numfaces; i++ )
      {
      tri = &single->faces[ i ];
      SafeStringWrite( out, "%d %d %f %f %d %f %f %d %f %f\n", 
         tri->id+1,
         tri->verts[ 0 ].vertindex,
         tri->verts[ 0 ].s, 
         tri->verts[ 0 ].t, 
         tri->verts[ 1 ].vertindex,
         tri->verts[ 1 ].s, 
         tri->verts[ 1 ].t, 
         tri->verts[ 2 ].vertindex,
         tri->verts[ 2 ].s, 
         tri->verts[ 2 ].t
         );
      }

   fclose( out );
   }

#if (MAX_RELEASE >= 3000)
_UVExport::DoExport(const TCHAR *filename,ExpInterface *ei,Interface *gi, BOOL suppressPrompts, DWORD options)
#elif (MAX_RELEASE > 1000)
_UVExport::DoExport(const TCHAR *filename,ExpInterface *ei,Interface *gi, BOOL suppressPrompts)
#else
_UVExport::DoExport(const TCHAR *filename,ExpInterface *ei,Interface *gi)
#endif
   {
   int i;
   int sorted[MAX_OBJECT_NAMES];
	interfaceptr = gi;

   //
   // Get the names of all the objects
   //
   numobjects = 0;
   ei->theScene->EnumTree(&theGetNamesEnumProc);

   SortObjectNames( sorted );

   //
   // clear the file holder
   //
   memset( &single, 0, sizeof( single ) );
   //
   // grab the file from MAX
   //
   for (i=0;i<numobjects;i++)
      {
      currentobject = sorted[i];
      ei->theScene->EnumTree(&theGetObjectsEnumProc);
      }
   //
   // put it into a UV file
   //
   strcpy( single.name, filename );
   SaveUVFile( &single );

   return 1;
	}


/** public functions **/
BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved)
   {
	hInstance = hinstDLL;

   if (!controlsInit)
      {
		controlsInit = TRUE;

		// jaguar controls
		InitCustomControls(hInstance);

		// initialize Chicago controls
		InitCommonControls();
		}

	return (TRUE);
	}

//------------------------------------------------------
// This is the interface to Jaguar:
//------------------------------------------------------

__declspec( dllexport ) const TCHAR * LibDescription()
   {
   return _T("UV Single Export");
   }

__declspec( dllexport ) int LibNumberClasses()
   {
   return 1;
   }

__declspec( dllexport ) ClassDesc * LibClassDesc(int i)
   {
   switch(i)
      {
      case 0:
         return &UVOutDesc;
         break;
      default:
         return 0;
         break;
      }
   }

// Return version so can detect obsolete DLLs
__declspec( dllexport ) ULONG LibVersion()
   {
   return VERSION_3DSMAX;
   }


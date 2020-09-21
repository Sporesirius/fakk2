/**********************************************************************
 *<
   FILE: animout.cpp

   DESCRIPTION:  A MAX2 plugin that outputs animations

	CREATED BY: Mark Dochtermann

   HISTORY: created 3/31/99 11:22AM

 *>   Copyright (c) 1999, All Rights Reserved.
 **********************************************************************/
#include "Max.h"
#include "resource.h"
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
#define MAX_FRAMES   	   2048

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
static bool cancel = false;

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
qboolean bequiet = false;

class GetNamesEnumProc : public ITreeEnumProc
    {
	public:
		int callback( INode *node );
	};

static GetNamesEnumProc theGetNamesEnumProc;


static Interface * interfaceptr;

loadsinglefile_t single;

class _AnimExport : public SceneExport {

public:
                  _AnimExport();
                  ~_AnimExport();
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
// ._Anim export module functions follow:
//

_AnimExport::_AnimExport() {
	}

_AnimExport::~_AnimExport() {
	}

int
_AnimExport::ExtCount() {
	return 1;
	}

const TCHAR *
_AnimExport::Ext(int n) {      // Extensions supported for import/export modules
	switch(n) {
		case 0:
         return _T("ANM");
		}
	return _T("");
	}

const TCHAR *
_AnimExport::LongDesc() {         // Long ASCII description (i.e. "Targa 2.0 Image File")
   return _T("ANIM export");
	}

const TCHAR *
_AnimExport::ShortDesc() {        // Short ASCII description (i.e. "Targa")
   return _T("ANIM export");
	}

const TCHAR *
_AnimExport::AuthorName() {       // ASCII Author name
	return _T("Mark Dochtermann");
	}

const TCHAR *
_AnimExport::CopyrightMessage() { // ASCII Copyright message
	return _T("Copyright (c) 1996. All Rights Reserved");
	}

const TCHAR *
_AnimExport::OtherMessage1() {    // Other message #1
	return _T("");
	}

const TCHAR *
_AnimExport::OtherMessage2() {    // Other message #2
	return _T("");
	}

unsigned int
_AnimExport::Version() {          // Version number * 100 (i.e. v3.01 = 301)
	return 101;
	}

void
_AnimExport::ShowAbout(HWND hWnd) {        // Optional
 	}

class AnimOutClassDesc:public ClassDesc {
	public:
	int 			IsPublic() {return 1;}
   void *         Create(BOOL loading = FALSE) {return new _AnimExport;}
   const TCHAR *  ClassName() {return _T("Anim Export");}
	SClass_ID		SuperClassID() {return SCENE_EXPORT_CLASS_ID;}
   Class_ID    ClassID() {return Class_ID(0x483278b9, 0x39d5051b);}
   const TCHAR*   Category() {return _T("Export");}
	};

static AnimOutClassDesc AnimOutDesc;

int GetObjectsEnumProc::callback(INode *node)
   {
   Object *obj = node->EvalWorldState(interfaceptr->GetTime()).obj;

   if (obj->IsDeformable() && obj->CanConvertToType(triObjectClassID))
      {
      if ( 
            !strcmpi( node->GetName(), objectnames[currentobject] )
         )
         {
         AddObject(obj, node, &single);
         }
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
            if ( !bequiet && !strcmpi( objectnames[i], objectnames[numobjects] ) )
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
      if ( !bequiet )
         {
         char str[128];
         sprintf( str, "Object %s had no verts or faces", loadobject->name );
	      MessageBox(NULL,str,"AddObject",MB_OK);
         }
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

FILE *SafeOpenWrite (const char *filename)
   {
	FILE	*f;

	f = fopen(filename, "wb");

	if (!f)
		 Error("Error opening %s: %s",filename,strerror(errno));

	return f;
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

   SafeWrite( f, text, strlen( text ) + 1 );
   }

#define MAX_MATERIALS 256
void SaveAnimFile( const char * filename, loadsinglefile_t * anim, int numframes, float framerate )
   {
   FILE * out;
   int i;

   out = SafeOpenWrite( filename );

   // write out numframes
   SafeWrite( out, &numframes, sizeof( numframes ) );
   // write out framerate
   SafeWrite( out, &framerate, sizeof( framerate ) );
   // write out num vertices
   SafeWrite( out, &anim[ 0 ].numverts, sizeof( anim[ 0 ].numverts ) );
   // write out each frame's data
	for( i = 0; i < numframes; i++ )
      {
      SafeWrite( out, &anim[ i ].verts, sizeof( loadvertx_t ) * anim[ i ].numverts );
      }

   fclose( out );
   }

static int   startframe;
static int   stopframe;
static double framerate;
static double samplerate;

BOOL CALLBACK GetAnimScaleDlgProc (
    HWND hwndDlg,	// handle to dialog box
    UINT uMsg,	// message
    WPARAM wParam,	// first message parameter
    LPARAM lParam 	// second message parameter
   )
{
	HWND	h;
   char sz[128];

	switch (uMsg)
    {
	case WM_INITDIALOG:
      sprintf(sz,"%d",startframe);
		SetWindowText(GetDlgItem(hwndDlg, IDC_STARTFRAME), sz);
      sprintf(sz,"%d",stopframe);
		SetWindowText(GetDlgItem(hwndDlg, IDC_STOPFRAME), sz);
      sprintf(sz,"%.0f",(float)framerate);
		SetWindowText(GetDlgItem(hwndDlg, IDC_FRAMERATE), sz);
		SetWindowText(GetDlgItem(hwndDlg, IDC_SAMPLERATE), sz);
		h = GetDlgItem(hwndDlg, IDC_ANIMSCALE);
		SetFocus (h);
		return FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDOK:
			GetWindowText(GetDlgItem(hwndDlg, IDC_STARTFRAME), sz, 127);
         startframe = atoi(sz);
			GetWindowText(GetDlgItem(hwndDlg, IDC_STOPFRAME), sz, 127);
         stopframe = atoi(sz);
			GetWindowText(GetDlgItem(hwndDlg, IDC_FRAMERATE), sz, 127);
         framerate = atof(sz);
			GetWindowText(GetDlgItem(hwndDlg, IDC_SAMPLERATE), sz, 127);
         samplerate = atof(sz);
			EndDialog(hwndDlg, 1);
		break;

		case IDCANCEL:
			EndDialog(hwndDlg, 0);
         cancel = true;
		break;
	}
	default:
		return FALSE;
	}
}



void GetAnimScale(void)
{
	DialogBox(hInstance, (char *)IDD_ANIMSCALE, NULL, GetAnimScaleDlgProc);
}


#if (MAX_RELEASE >= 3000)
_AnimExport::DoExport(const TCHAR *filename,ExpInterface *ei,Interface *gi, BOOL suppressPrompts, DWORD options)
#elif (MAX_RELEASE > 1000)
_AnimExport::DoExport(const TCHAR *filename,ExpInterface *ei,Interface *gi, BOOL suppressPrompts)
#else
const BOOL suppressPrompts = false;
_AnimExport::DoExport(const TCHAR *filename,ExpInterface *ei,Interface *gi)
#endif
   {
   int i;
   int sorted[MAX_OBJECT_NAMES];
   loadsinglefile_t * anim;
   int numframes;
   Interval		animinfo;
   double      totaltime;
   double      realframerate;
	TimeValue	t;
   TimeValue   tinc;
   int         maxframe;
   int         minframe;
   int         frame;
   TimeValue   starttime, stoptime;
	interfaceptr = gi;

   //
   // Get the names of all the objects
   //
   numobjects = 0;

   cancel = false;

   bequiet = false;
   ei->theScene->EnumTree(&theGetNamesEnumProc);
   bequiet = true;

   SortObjectNames( sorted );

	// Find the number of frames
	animinfo = interfaceptr->GetAnimRange();
   startframe = animinfo.Start()/GetTicksPerFrame();
   stopframe = animinfo.End()/GetTicksPerFrame();
   minframe = startframe;
   maxframe = stopframe;
	samplerate = realframerate = framerate = GetFrameRate();

   if ( !suppressPrompts )
      {
      GetAnimScale();
      }

   if ( cancel )
      {
      // quit out if the cancel button was pressed
      return TRUE;
      }

   if (framerate < 2.0f)
      framerate = 2.0f;
   if (startframe < minframe || startframe > maxframe )
      {
	   MessageBox(NULL,"Illegal Start Frame, setting to 0","DoExport",MB_OK);
      startframe = 0;
      }
   if (stopframe < minframe || stopframe > maxframe )
      {
	   MessageBox(NULL,"Illegal Stop Frame, setting to maxframe","DoExport",MB_OK);
      stopframe = maxframe;
      }
   if (stopframe < startframe)
      {
	   MessageBox(NULL,"Illegal Stop Frame and Start Frame, setting stopframe to startframe","DoExport",MB_OK);
      stopframe = startframe;
      }
   // get the total time range
   starttime = startframe * GetTicksPerFrame();
   // add one to stoptime because of inclusive nature of frames
   stoptime = (stopframe+1) * GetTicksPerFrame();
   totaltime = TicksToSec( (stoptime - starttime) );

   // lop off any non FPS precision
   // totaltime = (float)((int)(totaltime*framerate));
   // this is also the total number of frames
   numframes = (int) ( ( totaltime * samplerate * realframerate ) / framerate );
//   char sz[ 1024 ];
//   sprintf(sz,"numframes = %d totaltime = %f",numframes, (float)totaltime);
//   MessageBox(NULL,sz,"DoExport",MB_OK);

   // convert it back into seconds
//   totaltime /=  (float)framerate;
   // get the time increment
//   tinc = SecToTicks( ( ( 1.0f/framerate )/ animscale) );
   tinc = SecToTicks( ( framerate / ( samplerate * realframerate ) ) );

   if ( samplerate < realframerate )
      {
      starttime += tinc / 2;
      }

//   sprintf(sz,"tinc = %d",tinc);
//   MessageBox(NULL,sz,"DoExport",MB_OK);
   // check the total amount of frames
   //if (numframes > MAX_FRAMES)
   //   {
	//   MessageBox(NULL,"Too many animation frames for this animation","DoExport",MB_OK);
   //   return 0;
   //   }

   //
   // allocate the data structures
   //
   anim = (loadsinglefile_t *)malloc( sizeof( loadsinglefile_t ) * (numframes+5) );
   if ( !anim )
      {
	   MessageBox(NULL,"Could not allocate memory for export","DoExport",MB_OK);
      return 0;
      }

	// Export each frame
//	for ( t = starttime, frame = 0; t < stoptime; t += tinc, frame++ )
	for ( t = starttime, frame = 0; frame < numframes; t += tinc, frame++ )
		{
//      if ( frame >= numframes )
//         break;

		interfaceptr->SetTime(t,TRUE);
      //
      // clear the file holder
      //
      memset( &single, 0, sizeof( loadsinglefile_t ) );
      //
      // grab the file from MAX
      //
      for (i=0;i<numobjects;i++)
         {
         currentobject = sorted[i];
         ei->theScene->EnumTree(&theGetObjectsEnumProc);
         }
      anim[frame] = single;
		}

   //
   // put it into a Anim file
   //
   SaveAnimFile( filename, anim, numframes, ( float )samplerate );

   free( anim );
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
   return _T("Anim Single Export");
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
         return &AnimOutDesc;
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


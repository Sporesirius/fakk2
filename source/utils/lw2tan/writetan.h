//
// writetan.h: header file for saving out tan files
//
#ifdef __cplusplus
extern "C" {
#endif


#define MAXLOADVERTS		   4096
#define MAXLOADFRAMES	   256
#define MAXLOADFACES		   4096
#define MAXLOADSURFACES    64

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
   loadfacevertx_t verts[3];
   } loadtriangle_t;

typedef struct
   {
   char name[128];
   int  numverts;
   int  numfaces;
   loadvertx_t    verts[MAXLOADVERTS];
   loadtriangle_t faces[MAXLOADFACES];
   } loadsurface_t;

typedef struct
   {
   loadsurface_t   surfaces[MAXLOADSURFACES];
   vec3_t            delta;
   float             time;
   } loadframe_t;

typedef struct
   {
   char           name[128];
   int            numframes;
   int            numsurfaces;
   float          totaltime;
   vec3_t         totaldelta;
   loadframe_t    frames[MAXLOADFRAMES];
   } loadanimfile_t;

int ConvertAnim( loadanimfile_t * load );

#ifdef __cplusplus
   }
#endif
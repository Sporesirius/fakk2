//
// llwolib.h: header file for loading triangles from a LWO triangle file
//

#define MAXPOINTS 10000
#define MAXPOLYS 5000
#define MAXTRIANGLES	5000
#define MAXSURFACES 64

typedef float vec_t;
typedef vec_t vec3_t[3];

//typedef struct {
	//vec3_t	verts[3];
//} triangle_t;

typedef struct {
	vec_t u;
   vec_t v;
   vec_t other;
} uv_t;

typedef struct {
	int verts[3];
   int uv_verts[3];
	int id;
	int surface;
} tridex_t;

typedef struct {
   char name[ 64 ];
   int  polycount;
   int  map;
} surf_t;

typedef struct
{
	tridex_t *triangles; 
   vec3_t *verts;
   int number_of_triangles;
   int number_of_verts;
   int number_of_uv_verts;
   int number_of_surfaces;
   surf_t *surfs;
   uv_t *uv_verts;
} model_info;

extern int surfcount;

void LoadLWOTriangleList (char *filename, tridex_t **pptri, vec3_t **ppvert, int *numtriangles, int *numverts);
void load_triangles(char *filename, model_info *model);


#define UV_VERSION 2
#define UV_NEW_VERSION 4

extern char surfacenames[ 256 ][ 64 ];
extern char surfacepaths[ 256 ][ 64 ];
vec3_t surfacevecs[ 256 ][ 4 ];
int  surfacenumvecs[ 256 ];

void load_uv_coordinates(char *uv_filename, int LWO_number_of_surfaces, int LWO_number_of_polygons,
                         tridex_t *triangles, int *number_of_uv_verts, uv_t *uv_verts);
void read_string(FILE *file, char *string);
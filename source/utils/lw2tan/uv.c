#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cmdlib.h"
#include "lwolib.h"
#include "uv.h"

char surfacenames[ 256 ][ 64 ];
char surfacepaths[ 256 ][ 64 ];
vec3_t surfacevecs[ 256 ][ 4 ];
float surfacebounds[ 256 ][ 5 ];
int  surfacenumvecs[ 256 ];


// Reads a word from a file until a space or end of line is hit 

qboolean read_word(FILE *file, char *string)
   {
   char character;
   int current_character = 0;
   
   if ( fscanf(file, "%c", &character) == EOF )
      {
      return qfalse;
      }

   // If the first character is not a printable character skip it.
   
   while( character <= ' ' )
      {
      if ( fscanf(file, "%c", &character) == EOF )
         {
         return qfalse;
         }
      }

	// Read unitl the end of line is hit

   while( character > ' ' )
      {
      string[current_character] = character;
      current_character++;
      if ( fscanf(file, "%c", &character) == EOF )
         {
         return qfalse;
         }
      }

	// Make sure the string is NULL terminated

   string[current_character] = 0;
   return qtrue;
   }

void load_new_uv_coordinates( FILE *uv_file, int LWO_number_of_surfaces, int LWO_number_of_polygons,
                         tridex_t *triangles, int *number_of_uv_verts, uv_t *uv_verts)
   {
   int number_of_surfaces;
   int number_of_polygons;
   int current_surface;
   int current_polygon;
   int current_vertex;
   int current_uv_vertex = 0;
   char current_token[ 128 ];

   while ( read_word( uv_file, current_token ) )
      {
      // interpret the token
      // version
      if ( !strcmpi( current_token, "VERSION" ) )
         {
         // skip the version number
         read_word( uv_file, current_token );
         }
      // channel
      else if ( !strcmpi( current_token, "CHANNEL" ) )
         {
         // skip the channel number
         read_word( uv_file, current_token );
         }
      // surface count
      else if ( !strcmpi( current_token, "SURFACE_COUNT" ) )
         {
         // read the number of surfaces
         fscanf( uv_file, "%d", &number_of_surfaces);
         }
      // set current surface
      else if ( !strcmpi( current_token, "SURFACE" ) )
         {
         // read the surface number
         fscanf( uv_file, "%d", &current_surface);
         }
      // surface name
      else if ( !strcmpi( current_token, "SURFACE_NAME" ) )
         {
         // read the surface name
         read_word( uv_file, surfacenames[ current_surface ] );
         }
      // surface name
      else if ( !strcmpi( current_token, "SURFACE_IMAGE_FILE" ) )
         {
         // read the surface image file
         read_word( uv_file, surfacepaths[ current_surface ] );
         }
      // surface ptype
      else if ( !strcmpi( current_token, "SURFACE_PTYPE" ) )
         {
         // read the number of vecs
         read_word( uv_file, current_token );
         surfacenumvecs[ current_surface ] = atof( current_token );
         }
      // surface porot
      else if ( !strcmpi( current_token, "SURFACE_POROT" ) )
         {
         // read theO Rotation
         fscanf(uv_file, "%f %f %f",
            &surfacevecs[ current_surface ][ 0 ][ 0 ],
            &surfacevecs[ current_surface ][ 0 ][ 1 ],
            &surfacevecs[ current_surface ][ 0 ][ 2 ]
            );
         }
      // surface prot
      else if ( !strcmpi( current_token, "SURFACE_PROT" ) )
         {
         // read the Rotation
         fscanf(uv_file, "%f %f %f",
            &surfacevecs[ current_surface ][ 1 ][ 0 ],
            &surfacevecs[ current_surface ][ 1 ][ 1 ],
            &surfacevecs[ current_surface ][ 1 ][ 2 ]
            );
         }
      // surface pos
      else if 
         ( 
            !strcmpi( current_token, "SURFACE_PPOS" ) ||
            !strcmpi( current_token, "SUFACE_PPOS" )
         )
         {
         // read the position
         fscanf(uv_file, "%f %f %f",
            &surfacevecs[ current_surface ][ 2 ][ 0 ],
            &surfacevecs[ current_surface ][ 2 ][ 1 ],
            &surfacevecs[ current_surface ][ 2 ][ 2 ]
            );
         }
      // surface scale
      else if ( !strcmpi( current_token, "SURFACE_PSCL" ) )
         {
         // read the position
         fscanf(uv_file, "%f %f %f",
            &surfacevecs[ current_surface ][ 3 ][ 0 ],
            &surfacevecs[ current_surface ][ 3 ][ 1 ],
            &surfacevecs[ current_surface ][ 3 ][ 2 ]
            );
         }
      // surface bounds
      else if ( !strcmpi( current_token, "SURFACE_BOUNDS" ) )
         {
         // read the position
         fscanf(uv_file, "%f %f %f %f %f",
            &surfacebounds[ current_surface ][ 0 ],
            &surfacebounds[ current_surface ][ 1 ],
            &surfacebounds[ current_surface ][ 2 ],
            &surfacebounds[ current_surface ][ 3 ],
            &surfacebounds[ current_surface ][ 4 ]
            );
         }
      // group count
      else if ( !strcmpi( current_token, "GROUP_COUNT" ) )
         {
         read_word( uv_file, current_token );
         }
      // light count
      else if ( !strcmpi( current_token, "LIGHT_COUNT" ) )
         {
         read_word( uv_file, current_token );
         }
      // poly_count
      else if ( !strcmpi( current_token, "POLY_COUNT" ) )
         {
         // read the polycount

         fscanf(uv_file, "%d", &number_of_polygons);

         if (number_of_polygons != LWO_number_of_polygons)
            {
		      Error( "Number of polygons in UV file does not match number in LWO file" );
            }
         }
      // poly
      else if ( !strcmpi( current_token, "POLY" ) )
         {
         // read the current poly
         fscanf(uv_file, "%d", &current_polygon);
         }
      // poly surface
      else if ( !strcmpi( current_token, "POLY_SURF" ) )
         {
         // we ignore the surface assignment since this is also in the LWO file
         read_word( uv_file, current_token );
         }
      // poly user variable
      else if ( !strcmpi( current_token, "POLY_USER" ) )
         {
         // ignore the user info
         read_word( uv_file, current_token );
         }
      // poly vertex count
      else if ( !strcmpi( current_token, "POLY_VERT_COUNT" ) )
         {
         int count;

         // read the vertex count
         fscanf(uv_file, "%d", &count);
         if ( count != 3 )
            Error( "Non-triangle defined in UV file" );
         }
      // current vertex
      else if ( !strcmpi( current_token, "VERT" ) )
         {
         // read the current vertex
         fscanf(uv_file, "%d", &current_vertex);
         }
      // Vertex UV coordinate
      else if ( !strcmpi( current_token, "VERT_UV" ) )
         {
         triangles[current_polygon].uv_verts[current_vertex] = current_uv_vertex;

         // read in u and v
         fscanf(uv_file, "%f", &uv_verts[current_uv_vertex].u);
         fscanf(uv_file, "%f", &uv_verts[current_uv_vertex].v);
         current_uv_vertex++;
         }
      // vert user variable
      else if ( !strcmpi( current_token, "VERT_USER" ) )
         {
         // ignore the user info
         read_word( uv_file, current_token );
         }
      // vert RGB
      else if ( !strcmpi( current_token, "VERT_RGB" ) )
         {
         // ignore red
         read_word( uv_file, current_token );
         // ignore green
         read_word( uv_file, current_token );
         // ignore blue
         read_word( uv_file, current_token );
         }
      // vert normal
      else if ( !strcmpi( current_token, "VERT_NORMAL" ) )
         {
         // ignore x
         read_word( uv_file, current_token );
         // ignore y
         read_word( uv_file, current_token );
         // ignore z
         read_word( uv_file, current_token );
         }
      else
         {
         assert( 0 );
         }
      }
   *number_of_uv_verts = current_uv_vertex;

   fclose( uv_file );
   }


void load_uv_coordinates(char *uv_filename, int LWO_number_of_surfaces, int LWO_number_of_polygons,
                         tridex_t *triangles, int *number_of_uv_verts, uv_t *uv_verts)
   {
   FILE *uv_file;
   int version_number;
   int number_of_surfaces;
   int number_of_polygons;
   int number_of_vertexes;
   int current_surface;
   int current_polygon;
   int current_vertex;
   int polygon_number;
   int current_uv_vertex = 0;

   memset( surfacevecs, 0, sizeof( surfacevecs ) );
   memset( surfacenumvecs, 0, sizeof( surfacenumvecs ) );

   // Open the uv file

   uv_file = fopen(uv_filename, "r");

   if (!uv_file)
   {
		Error("UV file not found");
   }

   // Get the version number

   fscanf(uv_file, "%d", &version_number);

   if (version_number != UV_VERSION)
   {
      if (version_number != UV_NEW_VERSION)
         {
   		Error("UV file version incorrect");
         }
      else
         {
         load_new_uv_coordinates( uv_file, LWO_number_of_surfaces, LWO_number_of_polygons, triangles, number_of_uv_verts, uv_verts );
         return;
         }
   }

   // Get all of the surface info

   fscanf(uv_file, "%d", &number_of_surfaces);

   if (number_of_surfaces != LWO_number_of_surfaces)
   {
		Error( "Number of surfaces in UV file does not match number in LWO file" );
   }

   // Get all of the surface names

   for(current_surface = 0 ; current_surface < number_of_surfaces ; current_surface++)
   {
		read_string(uv_file, surfacenames[ current_surface ] );
   }

   // Get all of the image names & path

   for(current_surface = 0 ; current_surface < number_of_surfaces ; current_surface++)
   {
		read_string(uv_file, surfacepaths[ current_surface ] );
   }

   // Read in the number of polygons

   fscanf(uv_file, "%d", &number_of_polygons);

   if (number_of_polygons != LWO_number_of_polygons)
   {
		Error( "Number of polygons in UV file does not match number in LWO file" );
   }

   // Read in all of the UV coordinates for each polygon

   for(current_polygon = 0 ; current_polygon < number_of_polygons ; current_polygon++)
   {
      fscanf(uv_file, "%d", &polygon_number);

      if (polygon_number >= LWO_number_of_polygons)
      {
			Error( "Polygon out of range" );
      }

      fscanf(uv_file, "%d", &number_of_vertexes);

      if (number_of_vertexes != 3)
      {
			Error( "Polygon is not a triangle" );
      }

      for(current_vertex = 0 ; current_vertex < number_of_vertexes ; current_vertex++)
      {
         triangles[polygon_number].uv_verts[current_vertex] = current_uv_vertex;

         fscanf(uv_file, "%f", &uv_verts[current_uv_vertex].u);
         fscanf(uv_file, "%f", &uv_verts[current_uv_vertex].v);
         fscanf(uv_file, "%f", &uv_verts[current_uv_vertex].other);
         current_uv_vertex++;
      }
   }

   // read in the surface vectors

   for(current_surface = 0 ; current_surface < number_of_surfaces ; current_surface++)
   {
      int i;

      // read number of vectors
      fscanf(uv_file, "%d", &surfacenumvecs[ current_surface ]);

      for( i = 0; i < surfacenumvecs[ current_surface ]; i++ )
      {
         fscanf(uv_file, "%f", &surfacevecs[current_surface][i][0]);
         fscanf(uv_file, "%f", &surfacevecs[current_surface][i][1]);
         fscanf(uv_file, "%f", &surfacevecs[current_surface][i][2]);
      }

   }

   *number_of_uv_verts = current_uv_vertex;

   fclose( uv_file );
}

// Reads a string from a file until an end of line is hit 

void read_string(FILE *file, char *string)
{
   char character;
   int current_character = 0;
   
   fscanf(file, "%c", &character);

   // If the first character is an end of line skip it

   if (character == '\n')
      fscanf(file, "%c", &character);

	// Read unitl the end of line is hit

   while(character != '\n')
   {
      string[current_character] = character;
      current_character++;
      fscanf(file, "%c", &character);
   }

	// Make sure the string is NULL terminated

   string[current_character] = 0;
}
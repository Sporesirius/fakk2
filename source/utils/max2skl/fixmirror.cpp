//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2skl/fixmirror.cpp                        $
// $Revision:: 2                                                              $
//     $Date:: 6/16/00 4:15p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2skl/fixmirror.cpp                             $
// 
// 2     6/16/00 4:15p Markd
// Added more error checking for exceeding max verts
// 
// 1     4/25/00 11:30a Jimdose
// 
// 2     4/17/00 2:55p Jimdose
// created file
// 
// DESCRIPTION:
// 

#include "fixmirror.h"
#include "max2skl.h"

#define SIGN( x ) ( ( x < 0 ) ? -1 : ( ( x > 0 ) ? 1 : 0 ) )

List<Vert *>   vertices;
List<Tri *> triangles;

Tri::Tri
   (
   Vert *v0,
   Vert *v1,
   Vert *v2
   )
   
   {
   int i;
   int j;

	assert( v0 != v1 && v1 != v2 && v2 != v0 );

	vertex[ 0 ] = v0;
	vertex[ 1 ] = v1;
	vertex[ 2 ] = v2;

	ComputeNormal();
	triangles.Add( this );

	for( i = 0; i < 3; i++ )
      {
		vertex[ i ]->face.Add( this );
		for( j = 0; j < 3; j++ )
         {
         if ( i != j )
            {
			   vertex[ i ]->neighbor.AddUnique( vertex[ j ] );
		      }
         }
	   }

   modified = v0->modified || v1->modified || v2->modified;
   }

Tri::~Tri()
   {
	int i;
   int j;

	triangles.Remove( this );

	for( i = 0; i < 3; i++ )
      {
		if ( vertex[ i ] )
         {
         vertex[ i ]->face.Remove( this );
         }
	   }

	for( i = 0; i < 3; i++ )
      {
		j = ( i + 1 ) % 3;

		if ( !vertex[ i ] || !vertex[ j ] )
         {
         continue;
         }

		vertex[ i ]->RemoveIfNonNeighbor( vertex[ j ] );
		vertex[ j ]->RemoveIfNonNeighbor( vertex[ i ] );
	   }
   }

int Tri::HasVertex
   (
   Vert *v
   )
   
   {
	return ( v == vertex[ 0 ] || v == vertex[ 1 ] || v == vertex[ 2 ] );
   }

void Tri::ComputeNormal
   (
   void
   )

   {
	Vector v0;
	Vector v1;
	Vector v2;

	v0 = vertex[ 0 ]->position;
	v1 = vertex[ 1 ]->position;
	v2 = vertex[ 2 ]->position;

   normal = ( v1 - v0 ) * ( v2 - v1 );
	if ( magnitude( normal ) == 0 )
      {
      return;
      }

	normal = normalize( normal );
   }

void Tri::InvertFace
   (
   void
   )

   {
   Vert *t;

   t = vertex[ 0 ];
   vertex[ 0 ] = vertex[ 2 ];
   vertex[ 2 ] = t;

   ComputeNormal();
   }

Tri *Tri::GetAdjacentTriangle
   (
   int edge
   )

   {
   int i;
   Vert *u;
   Vert *v;
   Tri *tri;

   u = vertex[ edge ];
   v = vertex[ ( edge + 1 ) % 3 ];

   for( i = 0; i < u->face.num; i++ )
      {
      tri = u->face[ i ];
		if ( ( tri != this ) && tri->HasVertex( v ) )
         {
         return tri;
         }
      }

   return NULL;
   }

Vector ProjectPointOnPlane
   (
   const Vector p,
   const Vector normal
   )

   {
	float d;
	Vector n;
	float inv_denom;

	inv_denom = 1.0F / ( normal ^ normal ); // ^ is dot product

	d = ( normal ^ p ) * inv_denom; // ^ is dot product

   n = normal * inv_denom;

   return p - d * n;
   }

////////////////////////
// PerpendicularVector
// assumes "src" is normalized
////////////////////////
Vector PerpendicularVector
   (
   const Vector src
   )

   {
	int   pos;
	int   i;
	float minelem;
	Vector tempvec;
   Vector dst;

   minelem = 1.0F;

	// find the smallest magnitude axially aligned vector
	for( pos = 0, i = 0; i < 3; i++ )
	   {
		if ( fabs( src[ i ] ) < minelem )
		   {
			pos = i;
			minelem = fabs( src[ i ] );
		   }
	   }

	tempvec[ pos ] = 1.0F;

	// project the point onto the plane defined by src
	dst = ProjectPointOnPlane( tempvec, src );

	// normalize the result
	return normalize( dst );
   }

Vector RotatePointAroundVector
   (
   const Vector dir,
   const Vector point,
   float degrees
   )
   
   {
	matrix   im;
	matrix   zrot;
	matrix   tmpmat;
	matrix   rot;
	Vector   vr;
   Vector   vup;
   Vector   vf;
	float	   rad;

	vf = dir;
	vr = PerpendicularVector( dir );
	vup = vr * vf;  // Note: * is Cross product for Vector

   matrix m( vr, vup, vf );
   im = transpose( m );

	rad = DEG2RAD( degrees );
	zrot.x[0] = cos( rad );
	zrot.x[1] = sin( rad );
	zrot.y[0] = -sin( rad );
	zrot.y[1] = cos( rad );

	tmpmat = m * zrot;
	rot = tmpmat * im;

	return rot * point;
   }

#define CANTFLIP        -1
#define NOTREADYTOFLIP  -2
#define DONTFLIP        0
#define FLIP            1

int Tri::CheckFlip
   (
   void
   )

   {
   int i;
   int edge;
   Tri *tri;
   Vert *u;
   Vert *v;
   Vert *w1;
   Vert *w2;
   Vector edgevec;
   Vector midpoint;
   Vector perp1;
   Vector perp2;
   float d1;
   float d2;

   if ( !modified )
      {
      return CANTFLIP;
      }
   
   for( edge = 0; edge < 3; edge++ )
      {
      tri = GetAdjacentTriangle( edge );
      if ( tri && !tri->modified )
         {
         break;
         }
      }

   if ( !tri || tri->modified )
      {
      return NOTREADYTOFLIP;
      }

   u = vertex[ edge ];
   v = vertex[ ( edge + 1 ) % 3 ];
   w1 = vertex[ ( edge + 2 ) % 3 ];

   for( i = 0; i < 3; i++ )
      {
      w2 = tri->vertex[ i ];
      if ( ( w2 != u ) && ( w2 != v ) )
         {
         break;
         }
      }

   edgevec = normalize( v->position - u->position );
   perp1 = normal * edgevec;        // NOTE : ^ is crossproduct
   perp2 = edgevec * tri->normal;   // NOTE : ^ is crossproduct

   d1 = perp1 ^ perp2;
   if ( d1 > 0.99f )
      {
      // triangles are folded against each other,
      // so normals should be nearly opposite each other
      d2 = normal ^ tri->normal;
      return d2 < 0;
      }

   // generate a point between the two triangles and make
   // sure it's in front of or in back of both triangles
   midpoint = normalize( perp1 + perp2 );

   d1 = midpoint ^ normal;
   d2 = midpoint ^ tri->normal;

   return ( SIGN( d1 ) != SIGN( d2 ) );
   }

Vert::Vert
   (
   Vector v,
   bool mod
   )
   
   {
	position = v;
   modified = mod;
	vertices.Add( this );
   }

Vert::~Vert()
   {
	assert( face.num == 0 );

	while( neighbor.num )
      {
		neighbor[ neighbor.num - 1 ]->neighbor.Remove( this );
		neighbor.Remove( neighbor[ neighbor.num - 1 ] );
	   }

	vertices.Remove( this );
   }

void Vert::RemoveIfNonNeighbor
   (
   Vert *n
   )
   
   {
   int i;

	// removes n from neighbor list if n isn't a neighbor.
	if ( !neighbor.Contains( n ) )
      {
      return;
      }

	for( i = 0; i < face.num; i++ )
      {
		if ( face[ i ]->HasVertex( n ) )
         {
         return;
         }
	   }

	neighbor.Remove( n );
   }

void ClearLists
   (
   void
   )

   {
   int i;
   
   for( i = triangles.num - 1; i >= 0; i-- )
      {
      delete triangles[ i ];
      }

   for( i = vertices.num - 1; i >= 0; i-- )
      {
      delete vertices[ i ];
      }
   }

void SkelModel::FixMirroredBones
   (
   void
   )

   {
	int			i;
   int         j;
   loadframe_t *frame;
   loadbone_t  *bone;
   UMat3       mats[ MAX_BONES ];
   UMat3       mat;
   loadvertx_t *vert;
   blendvert_t *blend;
   UVector3    temp;
   UVector3    offset;
   vec3_t      newVerts[ TIKI_MAX_VERTS ];
   bool        modified[ TIKI_MAX_VERTS ];
   Vert        *v;
   Tri         *t;
   Vector      vec;
   int         nummod;
   int         flip;
   int         numfixed;
   loadfacevertx_t tv;

   if ( model.numverts > TIKI_MAX_VERTS )
      {
      Error( "Too many vertices %d out of %d in model %s\n", model.numverts, TIKI_MAX_VERTS, model.name );
      }
   // precalculate the first frame
   bone = model.anim->bones;
   for( i = 0; i < model.numbones; i++, bone++ )
      {
      mats[ i ] = *( UMat3 * )bone->matrix;
      }

   // fix all the frames
   frame = model.anim;
	for( i = 0; i < model.numframes; i++, frame++ )
	   {
      bone = frame->bones;
      for( j = 0; j < model.numbones; j++, bone++ )
         {
         ( *( UMat3 * )bone->matrix ).OrthoNormalize();
         }
      }

   // convert all the verts to the new coordinate system
   bone = model.anim->bones;
   vert = model.verts;
   nummod = 0;
   for( i = 0; i < model.numverts; i++, vert++ )
      {
      modified[ i ] = false;

      blend = vert->blend;
      for( j = 0; j < vert->numbones; j++, blend++ )
         {
         bone = &model.anim->bones[ blend->bone ];

         mat = *( UMat3 * )bone->matrix;

         mats[ blend->bone ].UnprojectVector( blend->offset, temp );
         mat.ProjectVector( temp, offset );

         if ( ( SIGN( offset.x ) != SIGN( blend->offset[ 0 ] ) ) ||
            ( SIGN( offset.y ) != SIGN( blend->offset[ 1 ] ) ) ||
            ( SIGN( offset.z ) != SIGN( blend->offset[ 2 ] ) ) )
            {
            modified[ i ] = true;
            nummod++;
            }

         blend->offset[ 0 ] = offset[ 0 ];
         blend->offset[ 1 ] = offset[ 1 ];
         blend->offset[ 2 ] = offset[ 2 ];

         if ( j == 0 )
            {
            mats[ blend->bone ].ProjectVector( vert->normal, temp );
            mat.UnprojectVector( temp, offset );

            vert->normal[ 0 ] = offset.x;
            vert->normal[ 1 ] = offset.y;
            vert->normal[ 2 ] = offset.z;
            }
         }
      }

   if ( !nummod )
      {
      return;
      }

   CalcFrame( 0, newVerts );

   // convert vertices
	for( i = 0; i < model.numverts; i++ )
      {
      vec = Vector( newVerts[ i ][ 0 ], newVerts[ i ][ 1 ], newVerts[ i ][ 2 ] );
      v   = new Vert( vec, modified[ i ] );
	   }

   // convert triangles
   nummod = 0;
   for( i = 0; i < model.numfaces; i++ )
      {
		t = new Tri( 
         vertices[ model.faces[ i ].verts[ 0 ].vertindex ],
         vertices[ model.faces[ i ].verts[ 1 ].vertindex ],
         vertices[ model.faces[ i ].verts[ 2 ].vertindex ]
         );

      if ( t->modified )
         {
         nummod++;
         }
      }

   numfixed = 1;
   while( ( nummod > 0 ) && ( numfixed > 0 ) )
      {
      numfixed = 0;
      nummod = 0;
      for( i = 0; i < triangles.num; i++ )
         {
         if ( triangles[ i ]->modified )
            {
            flip = triangles[ i ]->CheckFlip();
            if ( flip != CANTFLIP )
               {
               nummod++;
               triangles[ i ]->modified = ( flip == NOTREADYTOFLIP );
               if ( flip == FLIP )
                  {
                  triangles[ i ]->InvertFace();
                  numfixed++;

                  memcpy( &tv, &model.faces[ i ].verts[ 0 ], sizeof( loadfacevertx_t ) );
                  memcpy( &model.faces[ i ].verts[ 0 ], &model.faces[ i ].verts[ 2 ], sizeof( loadfacevertx_t ) );
                  memcpy( &model.faces[ i ].verts[ 2 ], &tv, sizeof( loadfacevertx_t ) );
                  }
               else if ( flip == DONTFLIP )
                  {
                  numfixed++;
                  }
               }
            }
         }
      }

   ClearLists();
   }

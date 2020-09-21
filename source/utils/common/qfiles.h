//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/common/qfiles.h                 $
// $Revision:: 47                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/21/00 2:32a                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/common/qfiles.h                      $
// 
// 47    7/21/00 2:32a Markd
// first time check in for tgaconvert
// 
// 46    7/20/00 10:50p Markd
// created new skeletal format
// 
// 45    7/20/00 10:29p Markd
// working on new model format
// 
// 44    7/20/00 5:47p Markd
// working on new skel format
// 
// 43    7/20/00 9:29a Markd
// added new skel format
// 
// 42    7/18/00 12:48p Markd
// added cacheable tiki system
// 
// 41    6/16/00 4:16p Markd
// increased TIKI_MAX_VERTS
// 
// 40    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 39    6/10/00 11:15a Markd
// changed format of BSP file
// 
// 38    4/05/00 4:52p Markd
// gave ability to models to control their own picmip settings as
// well as mipmap
// 
// 37    4/04/00 3:28p Markd
// added ability for models to have no mipmapping
// 
// 36    3/17/00 8:52a Markd
// fixed typo in drawSoupVert decleration
// 
// 35    3/17/00 8:11a Markd
// did more lod tweaking to misc_model stuff
// 
// 34    3/17/00 7:56a Markd
// added lod to static models
// 
// 33    3/16/00 6:31p Markd
// Decreased LIGHTING_GRID_Z
// 
// 32    3/02/00 5:58p Markd
// fixed lighting against skies
// 
// 31    2/21/00 2:51p Markd
// Added GlobalRadius support to tikis
// 
// 30    2/18/00 6:41p Markd
// Added CROSSBLEND flag
// 
// 29    2/08/00 10:12a Markd
// decreased max skel models to a more reasonable number to reduce
// tiki_bone_cache memory requirements
// 
// 28    2/07/00 7:15p Markd
// Rewrote map loading routines
// 
// 27    2/07/00 2:47p Markd
// Added entry support to client command processor
// 
// 26    2/02/00 4:23p Jimdose
// added  MIN_MAP_BOUNDS and MAP_SIZ
// 
// 25    1/29/00 12:21p Markd
// rewrote tiki loading temp storage routines
// 
// 24    1/26/00 12:01p Markd
// changed LIGHTING_GRID sizes
// 
// 23    1/26/00 11:35a Markd
// added lighting gridsize
// 
// 22    1/25/00 8:07p Jimdose
// added blendtime to dtikianimdef_t
// 
// 21    1/20/00 5:20p Markd
// Added skin support into the game
// 
// 20    1/11/00 6:51p Jimdose
// added flags to skelBoneName_t
// incremented skeleton file version number
// 
// 19    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 18    11/30/99 2:15p Markd
// Added preview lighting to the editor
// 
// 17    11/24/99 3:51p Markd
// Fixed huge map size issues, had to increase MakePlane
// parameters to be sufficiently larger than max world extents (2
// times to be exact)
// 
// 16    10/21/99 6:19p Markd
// removed torso and head members from entity_state
// 
// 15    10/19/99 7:52p Markd
// Removed three part model system
// 
// 14    10/14/99 6:38p Jimdose
// moved vertex offset from md4Vertex_t to md4Weight_t
// 
// 13    10/11/99 3:05p Markd
// Added subdivisions to dshader_t
// 
// 12    10/08/99 2:57p Markd
// Changed POINTSCALE from 30,000 to 7,500 because of overbright
// bits
// 
// 11    10/06/99 5:36p Jimdose
// defined TIKI_SKEL_PARENTBONE
// 
// 10    10/04/99 8:02p Markd
// Added default light intensity and fixed hard-coded
// light_pointscale issue
// 
// 9     10/04/99 6:54p Markd
// changed default LIGHTING_POINTSCALE back to 30,000 our defaults
// 
// 8     10/04/99 11:15a Jimdose
// more skeleton stuff
// 
// 7     9/30/99 9:48p Jimdose
// added skeletal animation
// 
// 6     9/27/99 11:40a Jimdose
// changed TIKI_ANIM_IDENT to TIKI_SKEL_ANIM_IDENT
// 
// 5     9/15/99 5:05p Aldie
// changed version number
// 
// 4     9/15/99 12:12p Markd
// Merged in Carmack's latest build
//
// 3     9/14/99 8:38a Markd
// merged latest q3
//
// 2     9/10/99 3:18p Jimdose
// merge
//
// 44    8/23/99 10:15a Jimdose
// added MDL_ANIM_DEFAULT_ANGLES
//
// 43    8/04/99 12:18a Jimdose
// added tiki skel macros
//
// 42    7/21/99 5:04p Markd
// added light definition for energy by distance
//
// 41    7/20/99 6:42p Markd
// abstracted some of the lighting code
//
// 40    7/01/99 4:36p Phook
// + sped up curve subdivision increment/decrement
// + increased another hardlimit with resizing multiple brushes
// + fixed a problem with the selected brushes deselecting after a
// filter was toggled, and another brush was selected
// + added select untextured from the menu
// + fixed problem with patches that are created when the global
// texture was "notexture"
// + increased max world size to +-8192
// + brushes can now exist in the 2D view to +-16384
// + the 2D view can be zoomed out 50% further
//
// + fixed the mouse chaser jumping 1000s of units when zoomed out
// + fixed the 2D view jumping arround when scrolling quickly
// + fixed "save as region" not adding top and bottom brushes to
// the region
//
// 39    6/29/99 6:20p Markd
// Added light_offset support
//
// 38    6/18/99 2:39p Markd
// implemented some new surface and shader variables
//
// 37    6/18/99 12:24p Markd
// fixed some data, increased BSP version number
//
// 36    6/16/99 10:20a Markd
// modified lightmap resolution.  Moved it to lightdef instead of
// drawsurface
//
// 35    6/15/99 6:07p Markd
// fixed some lighting issues
//
// 34    6/15/99 4:58p Phook
//
// 33    6/15/99 4:57p Phook
// Added default lightmap resolution #define to qfiles
//
// 32    6/11/99 4:21p Markd
// implemented new BSP format
//
// 31    6/10/99 6:37p Markd
// removed a lot of snap to plane point stuff
//
// 30    6/07/99 3:59p Morbid
//
// DESCRIPTION:
//

#ifndef __QFILES_H__
#define __QFILES_H__

//
// qfiles.h: quake file formats
// This file must be identical in the quake and utils directories
//

// surface geometry should not exceed these limits
#define	SHADER_MAX_VERTEXES	1000
#define	SHADER_MAX_INDEXES	(6*SHADER_MAX_VERTEXES)


// the maximum size of game reletive pathnames
#define	MAX_QPATH		64


/*
========================================================================

QVM files

========================================================================
*/

#define	VM_MAGIC	0x12721444
typedef struct {
	int		vmMagic;

	int		instructionCount;

	int		codeOffset;
	int		codeLength;

	int		dataOffset;
	int		dataLength;
	int		litLength;			// ( dataLength - litLength ) should be byteswapped on load
	int		bssLength;			// zero filled memory appended to datalength
} vmHeader_t;

/*
========================================================================

PCX files are used for 8 bit images

========================================================================
*/

typedef struct {
    char	manufacturer;
    char	version;
    char	encoding;
    char	bits_per_pixel;
    unsigned short	xmin,ymin,xmax,ymax;
    unsigned short	hres,vres;
    unsigned char	palette[48];
    char	reserved;
    char	color_planes;
    unsigned short	bytes_per_line;
    unsigned short	palette_type;
    char	filler[58];
    unsigned char	data;			// unbounded
} pcx_t;


/*
========================================================================

TGA files are used for 24/32 bit images

========================================================================
*/

typedef struct _TargaHeader {
	unsigned char 	id_length, colormap_type, image_type;
	unsigned short	colormap_index, colormap_length;
	unsigned char	colormap_size;
	unsigned short	x_origin, y_origin, width, height;
	unsigned char	pixel_size, attributes;
} TargaHeader;

/*
========================================================================

FTX files are pre mipmapped files for FAKK 2

========================================================================
*/
#define FTX_EXTENSION ".ftx"

typedef struct ftx_s {
   int   width;
   int   height;
   int   has_alpha;
   // data follows
   } ftx_t;

/*
========================================================================

.MD3 triangle model file format

========================================================================
*/

#define MD3_IDENT			(('3'<<24)+('P'<<16)+('D'<<8)+'I')
#define MD3_VERSION			15

// limits
#define MD3_MAX_LODS		3
#define	MD3_MAX_TRIANGLES	8192	// per surface
#define MD3_MAX_VERTS		4096	// per surface
#define MD3_MAX_SHADERS		256		// per surface
#define MD3_MAX_FRAMES		1024	// per model
#define	MD3_MAX_SURFACES	32		// per model
#define MD3_MAX_TAGS		16		// per frame

// vertex scales
#define	MD3_XYZ_SCALE		(1.0/64)

typedef struct md3Frame_s {
	vec3_t		bounds[2];
	vec3_t		localOrigin;
	float		radius;
	char		name[16];
} md3Frame_t;

typedef struct md3Tag_s {
	char		name[MAX_QPATH];	// tag name
	vec3_t		origin;
	vec3_t		axis[3];
} md3Tag_t;

/*
** md3Surface_t
**
** CHUNK			SIZE
** header			sizeof( md3Surface_t )
** shaders			sizeof( md3Shader_t ) * numShaders
** triangles[0]		sizeof( md3Triangle_t ) * numTriangles
** st				sizeof( md3St_t ) * numVerts
** XyzNormals		sizeof( md3XyzNormal_t ) * numVerts * numFrames
*/
typedef struct {
	int		ident;				//

	char	name[MAX_QPATH];	// polyset name

	int		flags;
	int		numFrames;			// all surfaces in a model should have the same

	int		numShaders;			// all surfaces in a model should have the same
	int		numVerts;

	int		numTriangles;
	int		ofsTriangles;

	int		ofsShaders;			// offset from start of md3Surface_t
	int		ofsSt;				// texture coords are common for all frames
	int		ofsXyzNormals;		// numVerts * numFrames

	int		ofsEnd;				// next surface follows
} md3Surface_t;

typedef struct {
	char			name[MAX_QPATH];
	int				shaderIndex;	// for in-game use
} md3Shader_t;

typedef struct {
	int			indexes[3];
} md3Triangle_t;

typedef struct {
	float		st[2];
} md3St_t;

typedef struct {
	short		xyz[3];
	short		normal;
} md3XyzNormal_t;

typedef struct {
	int			ident;
	int			version;

	char		name[MAX_QPATH];	// model name

	int			flags;

	int			numFrames;
	int			numTags;
	int			numSurfaces;

	int			numSkins;

	int			ofsFrames;			// offset for first frame
	int			ofsTags;			// numFrames * numTags
	int			ofsSurfaces;		// first surface, others follow

	int			ofsEnd;				// end of file
} md3Header_t;


/*
==============================================================================

MD4 file format

==============================================================================
*/

#define MD4_IDENT			(('4'<<24)+('P'<<16)+('D'<<8)+'I')
#define MD4_VERSION			1
#define	MD4_MAX_BONES		128

typedef struct {
	int			boneIndex;		// these are indexes into the boneReferences,
	float		   boneWeight;		// not the global per-frame bone list
	vec3_t		offset;
} md4Weight_t;

typedef struct {
   vec3_t      vertex;
	vec3_t		normal;
	vec2_t		texCoords;
	int			numWeights;
	md4Weight_t	weights[1];		// variable sized
} md4Vertex_t;

typedef struct {
	int			indexes[3];
} md4Triangle_t;

typedef struct {
	int			ident;

	char		name[MAX_QPATH];	// polyset name
	char		shader[MAX_QPATH];
	int			shaderIndex;		// for in-game use

	int			ofsHeader;			// this will be a negative number

	int			numVerts;
	int			ofsVerts;

	int			numTriangles;
	int			ofsTriangles;

	// Bone references are a set of ints representing all the bones
	// present in any vertex weights for this surface.  This is
	// needed because a model may have surfaces that need to be
	// drawn at different sort times, and we don't want to have
	// to re-interpolate all the bones for each surface.
	int			numBoneReferences;
	int			ofsBoneReferences;

	int			ofsEnd;				// next surface follows
} md4Surface_t;

typedef struct {
	float		matrix[3][4];
} md4Bone_t;

typedef struct {
	vec3_t		bounds[2];			// bounds of all surfaces of all LOD's for this frame
	vec3_t		localOrigin;		// midpoint of bounds, used for sphere cull
	float		radius;				// dist from localOrigin to corner
	char		name[16];
	md4Bone_t	bones[1];			// [numBones]
} md4Frame_t;

typedef struct {
	int			numSurfaces;
	int			ofsSurfaces;		// first surface, others follow
	int			ofsEnd;				// next lod follows
} md4LOD_t;

typedef struct {
	int			ident;
	int			version;

	char		name[MAX_QPATH];	// model name

	// frames and bones are shared by all levels of detail
	int			numFrames;
	int			numBones;
	int			ofsFrames;			// md4Frame_t[numFrames]

	// each level of detail has completely separate sets of surfaces
	int			numLODs;
	int			ofsLODs;

	int			ofsEnd;				// end of file
} md4Header_t;


/*
==============================================================================

  TIKI model file format

==============================================================================
*/

#define TIKI_IDENT         (('I'<<24)+('K'<<16)+('I'<<8)+'T')
#define TIKI_ANIM_IDENT    ((' '<<24)+('N'<<16)+('A'<<8)+'T')
#define TIKI_ANIM_VERSION  2

// limits
#define TIKI_MAX_LODS      4
#define TIKI_MAX_TRIANGLES 4096  // per surface
#define TIKI_MAX_VERTS     1200  // per surface
#define TIKI_MAX_SHADERS   256   // per surface
#define TIKI_MAX_FRAMES    2048  // per model
#define TIKI_MAX_SURFACES  32    // per model
#define TIKI_MAX_TAGS      16    // per frame

#define MAX_SHADERNAME     64

typedef struct
   {
   unsigned short xyz[3];
   short    normal;
   } tikiXyzNormal_t;

typedef struct tikiFrame_s
   {
   vec3_t      bounds[2];
   vec3_t      scale; // multiply by this
   vec3_t      offset; // and add by this
   vec3_t      delta;
   float       radius;
   float       frametime;
   } tikiFrame_t;

/*
** tikiSurface_t
**
** CHUNK       SIZE
** header         sizeof( md3Surface_t )
** triangles[0]   sizeof( md3Triangle_t ) * numTriangles
** st             sizeof( md3St_t ) * numVerts
** XyzNormals     sizeof( md3XyzNormal_t ) * numVerts * numFrames
*/
typedef struct
   {
   int      ident;            //

   char     name[MAX_QPATH];  // polyset name

   int      numFrames;        // all surfaces in a model should have the same
   int      numVerts;
   int      minLod;

   int      numTriangles;
   int      ofsTriangles;

   int      ofsCollapseMap;   // numVerts * int

   int      ofsSt;            // texture coords are common for all frames
   int      ofsXyzNormals;    // numVerts * numFrames

   int      ofsEnd;           // next surface follows
   } tikiSurface_t;

typedef struct
   {
   vec3_t      origin;
   vec3_t      axis[3];
   } tikiTagData_t;

typedef struct
   {
   char     name[MAX_QPATH];  // tag name
   } tikiTag_t;

typedef struct
   {
   int      ident;
   int      version;

   char     name[MAX_QPATH];  // model name

   int      numFrames;
   int      numTags;
   int      numSurfaces;
   float    totaltime;
   vec3_t   totaldelta;

   int      ofsFrames;        // offset for first frame
   int      ofsSurfaces;      // first surface, others follow
   int      ofsTags[ TIKI_MAX_TAGS ]; // tikiTag_t + numFrames * tikiTagData_t

   int      ofsEnd;           // end of file
   } tikiHeader_t;

/*
==============================================================================

  TIKI Skeleton model file format

==============================================================================
*/
#define TIKI_SKEL_IDENT       ((' '<<24)+('L'<<16)+('K'<<8)+'S')
#define TIKI_SKEL_ANIM_IDENT  (('N'<<24)+('A'<<16)+('K'<<8)+'S')
#define TIKI_SKEL_VERSION     3
#define TIKI_SKEL_MAXBONES    100
#define MAX_SKEL_MODELS       20
#define TIKI_BONE_CACHE       ( TIKI_SKEL_MAXBONES * MAX_SKEL_MODELS )

#define TIKI_SKEL_PARENTBONE  -1

#define TIKI_BONEFLAG_LEG     1

#define TIKI_ANIM_NORMAL      0
#define TIKI_ANIM_NO_OFFSETS  1

#define TIKI_BONE_OFFSET_MANTISSA_BITS ( 9 )
#define TIKI_BONE_OFFSET_MAX_SIGNED_VALUE ( ( 1 << TIKI_BONE_OFFSET_MANTISSA_BITS ) - 1 )
#define TIKI_BONE_OFFSET_SIGNED_SHIFT ( 15 - ( TIKI_BONE_OFFSET_MANTISSA_BITS ) )
#define TIKI_BONE_OFFSET_MULTIPLIER ( ( 1 << ( TIKI_BONE_OFFSET_SIGNED_SHIFT ) ) - 1 )
#define TIKI_BONE_OFFSET_MULTIPLIER_RECIPROCAL ( ( 1.0f ) / ( TIKI_BONE_OFFSET_MULTIPLIER ) )

#define TIKI_BONE_QUAT_FRACTIONAL_BITS ( 15 )
#define TIKI_BONE_QUAT_MULTIPLIER ( ( 1 << ( TIKI_BONE_QUAT_FRACTIONAL_BITS ) ) - 1 )
#define TIKI_BONE_QUAT_MULTIPLIER_RECIPROCAL ( ( 1.0f ) / ( TIKI_BONE_QUAT_MULTIPLIER ) )

typedef struct
   {
	int			         boneIndex;
	float		            boneWeight;
   vec3_t               offset;
   } skelWeight_t;

typedef struct
   {
	vec3_t		         normal;
	vec2_t		         texCoords;
	int			         numWeights;
	skelWeight_t	      weights[ 1 ];		// variable sized
   } skelVertex_t;

typedef struct
   {
   short                shortQuat[ 4 ];
   short                shortOffset[ 3 ];
   short                padding_do_not_use;
   } skelBone_t;

typedef struct
   {
   float                quat[ 4 ];
   float                offset[ 3 ];
   float                matrix[ 3 ][ 3 ];
   } skelBoneCache_t;

typedef struct
   {
   vec3_t		         bounds[ 2 ];
   float		            radius;				// dist to corner
   vec3_t               delta;
   skelBone_t           bones[ 1 ];       // variable sized
   } skelFrame_t;

typedef struct
   {
	int			         indexes[ 3 ];
   } skelTriangle_t;

typedef struct {
	int			         ident;
	char		            name[ MAX_QPATH ];	// polyset name
	int			         numTriangles;
	int			         numVerts;
   int                  minLod;
   int			         ofsTriangles;
   int			         ofsVerts;
   int                  ofsCollapse;
   int			         ofsEnd;				   // next surface follows
   } skelSurface_t;

typedef struct
   {
   int                  parent;
   int                  flags;
	char		            name[ MAX_QPATH ];	// bone name
   } skelBoneName_t;

typedef struct          
   {                    
	int                  ident;
	int                  version;
	char		            name[ MAX_QPATH ];	// model name

   int                  numsurfaces;
   int                  numbones;

   int                  ofsBones;
   int                  ofsSurfaces;
	int                  ofsEnd;
   } skelHeader_t;

typedef struct
   {
	int                  ident;
	int                  version;
   char		            name[ MAX_QPATH ];   // anim name

   int                  type;
	int                  numFrames;
	int                  numbones;
   float                totaltime;
   float                frametime;
   vec3_t               totaldelta;
	int                  ofsFrames;
   } skelAnimHeader_t;

//====================================
// TIKI DEF STUFF
//====================================


// 
// frame cmd flags
//
#define TIKI_FRAME_CMD_EVERY_FRAME  -1
#define TIKI_FRAME_CMD_EXIT         -2
#define TIKI_FRAME_CMD_ENTRY        -3
#define TIKI_FRAME_CMD_LAST_SPECIAL -4

#define TIKI_FRAME_CMD_MAXFRAMERATE ( 1000 / 50 )

#define MAX_ANIMDEFNAME   48
#define MAX_ARGS_PER_CMD  32

#define MAX_ANIMFULLNAME   128
#define MAX_DEFNAME        128
#define MAX_SKELNAME       128

typedef struct
{
   int         frame_num;
   int         num_args;
   int         ofs_args[MAX_ARGS_PER_CMD];
} dtikicmd_t;

#define  MAX_TIKI_SKINS    4
typedef struct
   {
   char        name[MAX_QPATH];  // polyset name
   char        shader[MAX_TIKI_SKINS][MAX_SHADERNAME];// shader name
#ifdef UTILS
   int         shaderIndex[MAX_TIKI_SKINS];      // for in-game use
#else
   qhandle_t   hShader[MAX_TIKI_SKINS];      // for in-game use
#endif
   int         numskins;         // number of skins for this surface
   int         flags;
   float       damage_multiplier;
   } dtikisurface_t;

//
// Animation flags
//
#define  MDL_ANIM_DELTA_DRIVEN   ( 1 << 0 )
#define  MDL_ANIM_DEFAULT_ANGLES ( 1 << 3 )

typedef struct
{
   char        alias[MAX_ANIMDEFNAME]; // anim name from grabbing
   char        fullname[MAX_ANIMFULLNAME]; // the full path name of the animation
   float       weight;
   int         blendtime;
   int         handle;
   int         flags;
   int         num_client_cmds;
   int         ofs_client_cmds;
   int         num_server_cmds;
   int         ofs_server_cmds;
} dtikianimdef_t;

//
// surface flags for models
//
//

//
// Surface flags sent over the net when changed
//
#define  MDL_SURFACE_SKINOFFSET_BIT0  ( 1 << 0 )
#define  MDL_SURFACE_SKINOFFSET_BIT1  ( 1 << 1 )
#define  MDL_SURFACE_NODRAW           ( 1 << 2 )
#define  MDL_SURFACE_SURFACETYPE_BIT0 ( 1 << 3 )
#define  MDL_SURFACE_SURFACETYPE_BIT1 ( 1 << 4 )
#define  MDL_SURFACE_SURFACETYPE_BIT2 ( 1 << 5 )
#define  MDL_SURFACE_CROSSFADE_SKINS  ( 1 << 6 )
#define  MDL_SURFACE_SKIN_NO_DAMAGE   ( 1 << 7 )

// 
// Surface flags which are static (not sent over net)
//
#define  MDL_SURFACE_NOMIPMAPS        ( 1 << 8 )
#define  MDL_SURFACE_NOPICMIP         ( 1 << 9 )

typedef struct dtiki_s
{
   char           name[MAX_DEFNAME];
   int            num_surfaces;
   int            num_tags;
   int            num_anims;
   void           *alias_list;
   int            num_client_initcmds;
   int            ofs_client_initcmds;
   int            num_server_initcmds;
   int            ofs_server_initcmds;
   int            ofs_surfaces;
   float          load_scale;
   float          lod_scale;
   float          lod_bias;
   vec3_t         light_offset;
   vec3_t         load_origin;
   vec3_t         mins;
   vec3_t         maxs;
   float          radius;
   int            skelIndex;
   char           skelName[ MAX_SKELNAME ];
   int            ofs_animdefs[ 1 ];
} dtiki_t;

/*
==============================================================================

  .BSP file format

==============================================================================
*/


#define BSP_HEADER  (('K'<<24)+('K'<<16)+('A'<<8)+'F')
		// little-endian "FAKK"

#define BSP_VERSION			12


// there shouldn't be any problem with increasing these values at the
// expense of more memory allocation in the utilities
#define	MAX_MAP_MODELS		      0x400
#define	MAX_MAP_BRUSHES		   0x8000
#define	MAX_MAP_ENTITIES	      0x800
#define	MAX_MAP_ENTSTRING	      0x40000
#define	MAX_MAP_SHADERS		   0x400

#define  MAX_MAP_SHADERSTRING    0x4000
#define  MAX_MAP_NUM_SHADERS     4096

#define	MAX_MAP_AREAS		      0x100	// MAX_MAP_AREA_BYTES in q_shared must match!
#define	MAX_MAP_FOGS		      0x100
#define	MAX_MAP_PLANES		      0x20000
#define	MAX_MAP_NODES		      0x20000
#define	MAX_MAP_BRUSHSIDES	   0x20000
#define	MAX_MAP_LEAFS		      0x20000
#define	MAX_MAP_LEAFFACES	      0x20000
#define	MAX_MAP_LEAFBRUSHES     0x40000
#define	MAX_MAP_PORTALS		   0x20000
#define	MAX_MAP_LIGHTING	      0x800000
#define	MAX_MAP_LIGHTGRID	      0x800000
#define	MAX_MAP_VISIBILITY	   0x200000
#define  MAX_MAP_SPHERE_LIGHTS   0x400

#define	MAX_MAP_DRAW_SURFS	   0x20000
#define	MAX_MAP_DRAW_VERTS	   0x80000
#define	MAX_MAP_DRAW_INDEXES	   0x80000

#define  MAX_MAP_LIGHTDEFS       MAX_MAP_DRAW_SURFS

#define  MAX_MAP_BOUNDS          8192
#define  MIN_MAP_BOUNDS          ( -MAX_MAP_BOUNDS )
#define  MAP_SIZE                ( MAX_MAP_BOUNDS - MIN_MAP_BOUNDS )

// key / value pair sizes in the entities lump
#define	MAX_KEY				      32
#define	MAX_VALUE			      1024

// the editor uses these predefined yaw angles to orient entities up or down
#define	ANGLE_UP			               -1
#define	ANGLE_DOWN			            -2

#define  DEFAULT_CURVE_SUBDIVISIONS    4
#define  DEFAULT_LIGHTMAP_RESOLUTION   32
#define  MIN_LIGHTMAP_RESOLUTION       4
#define  MAX_LIGHTMAP_RESOLUTION       128

#define	LIGHTMAP_WIDTH		            128
#define	LIGHTMAP_HEIGHT		         128


//=============================================================================


// in game version of lump
typedef struct {
   void     *buffer;
   int      length;
} gamelump_t;

typedef struct {
	int		fileofs, filelen;
} lump_t;

#define  LUMP_SHADERS       0
#define  LUMP_PLANES        1
#define  LUMP_LIGHTMAPS     2
#define  LUMP_SURFACES      3
#define  LUMP_DRAWVERTS     4
#define  LUMP_DRAWINDEXES   5
#define  LUMP_LEAFBRUSHES   6
#define  LUMP_LEAFSURFACES  7
#define  LUMP_LEAFS         8
#define  LUMP_NODES         9
#define  LUMP_BRUSHSIDES    10
#define  LUMP_BRUSHES       11
#define  LUMP_FOGS          12
#define  LUMP_MODELS        13
#define  LUMP_ENTITIES      14
#define  LUMP_VISIBILITY    15
#define  LUMP_LIGHTGRID     16
#define  LUMP_ENTLIGHTS     17
#define  LUMP_ENTLIGHTSVIS  18
#define  LUMP_LIGHTDEFS     19
#define  HEADER_LUMPS       20


typedef struct {
	int			ident;
	int			version;
   int         checksum;

	lump_t		lumps[HEADER_LUMPS];
} dheader_t;

typedef struct {
	float		mins[3], maxs[3];
	int		firstSurface, numSurfaces;
	int		firstBrush, numBrushes;
} dmodel_t;

typedef struct {
	char		shader[MAX_QPATH];
	int		surfaceFlags;
	int		contentFlags;
   int      subdivisions;
} dshader_t;

// planes x^1 is allways the opposite of plane x

typedef struct {
	float		normal[3];
	float		dist;
} dplane_t;

typedef struct {
	int			planeNum;
	int			children[2];	// negative numbers are -(leafs+1), not nodes
	int			mins[3];		// for frustom culling
	int			maxs[3];
} dnode_t;

typedef struct {
   int         cluster;       // -1 = opaque cluster (brushes but no surfaces)
	int			area;

	int			mins[3];			// for frustum culling
	int			maxs[3];

	int			firstLeafSurface;
	int			numLeafSurfaces;

	int			firstLeafBrush;
	int			numLeafBrushes;
} dleaf_t;

typedef struct {
	int			planeNum;			// positive plane side faces out of the leaf
	int			shaderNum;
} dbrushside_t;

typedef struct {
	int			firstSide;
	int			numSides;
	int			shaderNum;		// the shader that determines the contents flags
} dbrush_t;

typedef struct {
	char		   shader[MAX_QPATH];
	int			brushNum;
	int			visibleSide;	// the brush side that ray tests need to clip against (-1 == none)
} dfog_t;

#ifndef QERADIANT
//
// if drawVert_t changes, change drawSoupVert_t
typedef struct {
	vec3_t		xyz;
	float		   st[2];
	float		   lightmap[2];
	vec3_t		normal;
	byte		   color[4];
} drawVert_t;


typedef struct {
	vec3_t		xyz;
	float		   st[2];
   int         collapseMap;
   float       lodExtra;  // depending on the vertexNumber, will be 0 - minLOD, 1 - lodScale or 2 - lodBias
	vec3_t		normal;
	byte		   color[4];
} drawSoupVert_t;
#endif

typedef enum {
	MST_BAD,
	MST_PLANAR,
	MST_PATCH,
	MST_TRIANGLE_SOUP,
	MST_FLARE
} mapSurfaceType_t;

typedef struct {
	int			shaderNum;
	int			fogNum;
	int			surfaceType;

	int			firstVert;
	int			numVerts;

	int			firstIndex;
	int			numIndexes;

	int			lightmapNum;
	int			lightmapX, lightmapY;
	int			lightmapWidth, lightmapHeight;

	vec3_t		lightmapOrigin;
	vec3_t		lightmapVecs[3];	// for patches, [0] and [1] are lodbounds

	int			patchWidth;
	int			patchHeight;

   float       subdivisions;
} dsurface_t;

// the light grid may not contain the entire bounds of the world, to
// allow q3test2 like levels that float in the middle of a giant sky box
// to not waste huge amounts of time and space
typedef struct {
	vec3_t		origin;
	vec3_t		axis;
	int			bounds[3];
} dlightGrid_t;

typedef struct {
	int		lightIntensity;
	int		lightAngle;
   int      lightmapResolution;
   qboolean twoSided;
	qboolean	lightLinear;
	vec3_t	lightColor;
   float    lightFalloff;
   float    backsplashFraction;
   float    backsplashDistance;
   float    lightSubdivide;
   qboolean autosprite;
} dlightdef_t;

typedef struct
   {
   vec3_t origin;
   vec3_t color;
   float intensity;
   int leaf;

   qboolean needs_trace;
   qboolean spot_light;
   vec3_t spot_dir;
   float spot_radiusbydistance;
   } mapspherel_t;

//
// Q3RADIANT defines
//
#define MAX_BRUSH_SIZE 16384

/*
==============================================================================

  .WAL texture file format

==============================================================================
*/


#define  MIPLEVELS   4
typedef struct miptex_s
{
   char        name[32];
   unsigned    width, height;
   unsigned    offsets[MIPLEVELS];     // four mip maps stored
   char        animname[32];           // next frame in animation chain
   int         flags;
   int         contents;
   int         value;
} miptex_t;


/*
==============================================================================
LIGHTING DEFINITIONS
==============================================================================
*/
#define LIGHTING_GRIDSIZE_X 192
#define LIGHTING_GRIDSIZE_Y 192
#define LIGHTING_GRIDSIZE_Z 320
#define LIGHTING_GRIDSIZE { LIGHTING_GRIDSIZE_X, LIGHTING_GRIDSIZE_Y, LIGHTING_GRIDSIZE_Z }
#define LIGHTING_POINTSCALE 7500
#define LIGHTING_LINEARSCALE ( 1.0f / 8000.0f )
#define LIGHTING_SUNDIRECTION { 0.45,  0.3, 0.9 }
#define LIGHTING_SUNCOLOR     { 100, 100, 92 }
#define LIGHTING_DEFAULT_INTENSITY 300.0f
#define LIGHTING_AREASCALE 0.25
#define LIGHTING_FORMFACTORSCALE 3

#define LIGHTING_SPOTRADIUS      64
#define LIGHTING_SPOTDISTANCE    64
#define LIGHTING_RADIUSBYDISTANCE( rad, dist ) ( ( ( ( rad ) + 16 ) / ( dist ) ) )
#define LIGHTING_SUNLIGHT( dot, sunColor, dest ) \
   {                                               \
   float sunlight_scale = 2 * ( dot );             \
   if ( sunlight_scale > 1 ) sunlight_scale = 1;   \
	VectorMA( ( dest ), (sunlight_scale + (1-sunlight_scale)/4), ( sunColor ), ( dest ) ); \
   }
#define LIGHTING_LINEARPOINTLIGHT( dot, photons, linearscale, distance, falloff ) \
         ( ( dot ) * ( photons ) * ( linearscale ) - ( ( distance ) / ( falloff ) ) )
#define LIGHTING_POINTLIGHT( dot, photons, distance ) \
         ( ( dot ) * ( photons ) / ( ( distance ) * ( distance ) ) )

#define LIGHTING_DISTANCE_AT_POWER( lightintensity, power ) sqrt( LIGHTING_POINTSCALE * ( lightintensity ) / ( power )  )

typedef enum
{
	emit_point,
	emit_area,
	emit_spotlight,
	emit_sun
} emittype_t;

#endif


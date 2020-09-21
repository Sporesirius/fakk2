//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/lipsync/code/qfiles.h                        $
// $Revision:: 1                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 2/15/00 12:17p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/lipsync/code/qfiles.h                             $
// 
// 1     2/15/00 12:17p Steven
// 
// 65    10/13/98 7:17p Aldie
// Added SPRITE_MODULATE flag
// 
// 64    10/08/98 4:09p Markd
// Changed pak format
// 
// 63    10/08/98 12:17a Aldie
// Increase pack files
// 
// 62    10/06/98 9:15p Aldie
// Changed SURF_STRONG to SURF_ADD
// 
// 61    9/28/98 5:26p Markd
// Changed SWAMP to DUCT
// 
// 60    9/16/98 3:36p Markd
// Added st_fixed parameter to sinmdl
// 
// 59    9/09/98 3:07p Markd
// replaced damaged with hardwareonly
// 
// 58    9/03/98 2:15p Aldie
// Added checksums checks to .def files
// 
// 57    9/01/98 8:45p Markd
// Added base sprite to sprites
// 
// 56    9/01/98 6:18p Markd
// Added star type of sprite
// 
// 55    8/18/98 11:08p Markd
// Added new Alias System
// 
// 54    8/06/98 10:22p Markd
// upped some arguments for loaded sinmdls
// 
// 53    6/22/98 1:34p Markd
// Added SPRITE_OVERBRIGHT flag
// 
// 52    6/18/98 5:09p Aldie
// Added cross sprites
// 
// 51    6/09/98 4:43p Markd
// Added additional envmapped flag
// 
// 50    5/25/98 7:20p Markd
// Added scale to sprites
// 
// 49    5/23/98 5:38p Markd
// Added flags to dsprite_t and sprite flags
// 
// 48    5/23/98 12:30p Markd
// Increased MAXARGS per line
// 
// 47    5/19/98 10:41p Markd
// Added surf_envmapped
// 
// 46    5/14/98 6:09p Markd
// Added DUMMY_FENCE STUFF
// 
// 45    5/06/98 7:58p Markd
// Changed MAXLIGHTSTYLES from 4 to 16
// 
// 44    5/05/98 3:10p Markd
// Added alias_prefix to pmdl_t
// 
// 43    5/04/98 7:21p Markd
// Added base angle and color to texinfo_t
// 
// 42    5/03/98 4:44p Markd
// Added SURF_USECOLOR to surface flags
// 
// 41    5/02/98 8:55p Markd
// Added SURF_START_BIT and other stuff
// 
// 40    4/25/98 4:46p Markd
// Added SURF_CONSOLE
// 
// 39    4/22/98 11:36a Markd
// Added alpha to sprite frames
// 
// 38    4/06/98 11:23p Markd
// Changed MAX_MAP_TEXINFO back to 8192
// 
// 37    4/06/98 11:00p Markd
// Increased MAX_MAP_TEXINFO
// 
// 36    4/04/98 5:15p Markd
// Commented out MAX_TRIANGLES not needed
// 
// 35    3/29/98 8:43p Markd
// Added name field to dsinmdl_t
// 
// 34    3/29/98 8:34p Markd
// changed entire structure of cmd structure, client and server commands are
// now separated for both the initcmds as well as the frame commands
// 
// 33    3/28/98 8:56p Jimdose
// Added twosided sprites
// 
// 32    3/27/98 7:04p Markd
// Added orientation to bone def
// 
// 31    3/24/98 9:56a Markd
// Added a lot of bone stuff and some new surface flags
// 
// 30    3/17/98 7:38p Markd
// Added swamp and water, nofilter and new group define for models
// 
// 29    3/12/98 5:36p Markd
// Cleaned up sprite structure
// 
// 28    3/10/98 7:45p Aldie
// Added sprite support.
// 
// 27    3/04/98 3:36p Markd
// Added scale and translate to each frame
// 
// 26    3/03/98 7:10p Markd
// Added load_origin
// 
// 25    3/02/98 5:53p Markd
// Added SURF_NOMERGE
// 
// 24    3/02/98 4:31p Markd
// Added SURF_TRANSLATE to the surface flags
// 
// 23    2/28/98 6:32p Markd
// updating sinmdl stuff
// 
// 22    2/25/98 2:24p Markd
// Upped BSPVERSION
// 
// 21    2/25/98 2:22p Markd
// Incremental new model format stuff
// 
// 20    2/22/98 4:08p Aldie
// 
// 19    2/22/98 2:34p Markd
// 
// 18    2/19/98 2:38p Markd
// Added directstylename to textureref_t
// 
// 17    2/05/98 5:12p Aldie
// Increased MAX_MAP_LIGHTING
// 
// 16    2/04/98 11:42a Markd
// Added direct_style to sinmiptex_t
// 
// 15    2/04/98 11:35a Markd
// Added directvalue to lightinfo_t
// 
// 14    2/03/98 9:46p Markd
// Changed Lightinfo_t to lightvalue_t
// 
// 13    2/03/98 9:34p Markd
// Added Lightinfo to dbrushside_t
// 
// 12    2/03/98 6:43p Markd
// Added lightinfo_t stuff
// 
// 11    1/29/98 5:16p Markd
// Added SURF_PRELIT
// 
// 10    1/29/98 3:05p Markd
// Changed sinmiptex_t made bytes floats, and reformatted
// 
// 9     1/27/98 8:07p Markd
// Added new files to sinmiptex_t
// 
// 8     1/22/98 10:44a Aldie
// Increased size of vis data
// 
// 7     1/21/98 4:28p Aldie
// Changed size of texture names
// 
// 6     1/16/98 4:59p Aldie
// Added palcrc
// 
// 5     1/16/98 2:26p Aldie
// Added sinmiptex
// 
// 4     1/16/98 11:47a Aldie
// Added palette to the qtex structure.
// 
// 3     12/30/97 6:30p Jimdose
// Added header text
//
// DESCRIPTION:
// quake file formats
// This file must be identical in the quake and utils directories
//

/*
========================================================================

The .pak files are just a linear collapse of a directory tree

========================================================================
*/

#ifdef SIN
#define MAX_PAK_FILENAME_LENGTH 120
#define SINPAKHEADER		(('K'<<24)+('A'<<16)+('P'<<8)+'S')

typedef struct
{
	char	name[MAX_PAK_FILENAME_LENGTH];
	int		filepos, filelen;
} dpackfile_t;

typedef struct
{
	int		ident;		// == IDPAKHEADER
	int		dirofs;
	int		dirlen;
} dpackheader_t;

#define	MAX_FILES_IN_PACK	16384
#else
#define IDPAKHEADER		(('K'<<24)+('C'<<16)+('A'<<8)+'P')

typedef struct
{
	char	name[56];
	int		filepos, filelen;
} dpackfile_t;

typedef struct
{
	int		ident;		// == IDPAKHEADER
	int		dirofs;
	int		dirlen;
} dpackheader_t;

#define	MAX_FILES_IN_PACK	16384
#endif


/*
========================================================================

PCX files are used for as many images as possible

========================================================================
*/

typedef struct
{
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

.MD2 triangle model file format

========================================================================
*/

#define IDALIASHEADER		(('2'<<24)+('P'<<16)+('D'<<8)+'I')
#define ALIAS_VERSION	8

//#define	MAX_TRIANGLES	4096
#define MAX_VERTS		2048
#define MAX_FRAMES		512
#define MAX_MD2SKINS	32
#define	MAX_SKINNAME	64

#ifdef SIN
/*
========================================================================

SIN specific model formats

========================================================================
*/
#define SINBASEMODEL_HEADER ((' '<<24)+('M'<<16)+('B'<<8)+'S')
#define SINBASEMODEL_VERSION 1

#define SINANIMMODEL_HEADER ((' '<<24)+('M'<<16)+('A'<<8)+'S')
#define SINANIMMODEL_VERSION 1

#define SINDEF_HEADER (('F'<<24)+('E'<<16)+('D'<<8)+'S')

typedef struct
{
	float	s;
	float	t;
} dsinstvert_t;

typedef struct 
{
	short	      index_xyz[3];
	short	      index_st[3];
   int         id;
} dsintriangle_t;

typedef struct
{
   int         id;
   int         num_tris;
	int         num_glcmds;		// dwords in strip/fan command list
   int         ofs_glcmds;
   int         ofs_tris;
   int         ofs_end;
} dsintrigroup_t;


typedef struct
{
	int			ident;
	int			version;

	int			num_xyz;
	int			num_st;			// greater than num_xyz for seams
   int         num_groups;

	int			ofs_st;			// byte offset from start for stverts
	int			ofs_end;		// end of file
   dsintrigroup_t groups[1];
} dsinbasemdl_t;

typedef struct
{
   float       movedelta[3]; // used for driving the model around
   float       frametime;
	float		   scale[3];	// multiply byte verts by this
	float		   translate[3];	// then add this
   int         ofs_verts;
} dsintriframe_t;

typedef struct
{
	int			ident;
	int			version;

   char        name[64];
	float		   scale[3];	// multiply byte verts by this
	float		   translate[3];	// then add this

   float       totaldelta[3]; // total displacement of this animation
   float       totaltime;

   int         num_xyz;
	int			num_frames;
   int         ofs_frames;
	int			ofs_end;		   // end of file

} dsinanim_t;

//====================================
// SIN DEF STUFF
//====================================


#define	MAX_ANIMDEFNAME	32
#define	MAX_SKINDEFNAME	32
#define	MAX_GROUPDEFNAME	32
#define	MAX_BONEDEFNAME	32
#define  MAX_ARGS_PER_CMD  32

typedef struct
{
   int         frame_num;
   int         num_args;
   int         ofs_args[MAX_ARGS_PER_CMD];
} dsincmd_t;

typedef struct
{
	char		   alias[MAX_ANIMDEFNAME];	// anim name from grabbing
   float       weight;
   int         handle;
   int         num_client_cmds;
   int         ofs_client_cmds;
   int         num_server_cmds;
   int         ofs_server_cmds;
} dsinanimdef_t;

//
// group flags for models
// 
//

//
// DYNAMIC flags sent over the net when changed
//
#define  MDL_GROUP_SKINOFFSET_BIT0  0x0001
#define  MDL_GROUP_SKINOFFSET_BIT1  0x0002
#define  MDL_GROUP_FULLBRIGHT       0x0004
#define  MDL_GROUP_ENVMAPPED_GOLD   0x0008
#define  MDL_GROUP_ENVMAPPED_SILVER 0x0010
#define  MDL_GROUP_TRANSLUCENT_33   0x0020
#define  MDL_GROUP_TRANSLUCENT_66   0x0040
#define  MDL_GROUP_NODRAW           0x0080

//
// STATIC flags NEVER sent over the net
//
#define  MDL_GROUP_SURFACETYPE_BIT0 0x0100
#define  MDL_GROUP_SURFACETYPE_BIT1 0x0200
#define  MDL_GROUP_SURFACETYPE_BIT2 0x0400
#define  MDL_GROUP_SURFACETYPE_BIT3 0x0800
#define  MDL_GROUP_RICOCHET         0x1000
#define  MDL_GROUP_SKIN_NO_DAMAGE   0x2000
#define  MDL_GROUP_MASKED           0x4000
#define  MDL_GROUP_TWOSIDED         0x8000

#define  MAX_SIN_SUB_GROUPS         8

typedef struct
{
   unsigned short basegroupnum;
   unsigned short flags;
} dsinsubgroup_t;

typedef struct
{
   char        name[ MAX_GROUPDEFNAME ];
   float       damage_multiplier;
   int         num_subgroups;
   dsinsubgroup_t subgroups[ MAX_SIN_SUB_GROUPS ];
} dsingroup_t;

typedef struct
{
   char        alias[ MAX_SKINDEFNAME ];
   char        path[ MAX_SKINNAME ];
   float       weight;
} dsinskin_t;

typedef struct
{
   char        name[ MAX_BONEDEFNAME ];
   int         basegroupindex;
   int         tri_num;
   vec3_t      orientation;
} dbone_t;

typedef struct
{
   int         version;
   char        name[64];
   int         num_skins;
   int         num_groups;
   int         num_bones;
   int         base_handle;
   void        *alias_list;
   qboolean    st_corrected;        // pinch the st coordinates to prevent software problems
   int         num_client_initcmds;
   int         ofs_client_initcmds;
   int         num_server_initcmds;
   int         ofs_server_initcmds;
   int         ofs_skins;
   int         ofs_groups;
   int         ofs_bones;
   vec3_t      mins, maxs;
   float       load_scale;
   vec3_t      load_origin;
   int         num_anims;
   unsigned    checksum;
   int         ofs_animdefs[1];
} dsinmdl_t;
/*
========================================================================
End of SIN specific model formats
========================================================================
*/

#endif

typedef struct
{
	short	s;
	short	t;
} dstvert_t;

typedef struct 
{
	short	index_xyz[3];
	short	index_st[3];
} dtriangle_t;

typedef struct
{
	byte	v[3];			// scaled byte to fit in frame mins/maxs
	byte	lightnormalindex;
} dtrivertx_t;

#define DTRIVERTX_V0   0
#define DTRIVERTX_V1   1
#define DTRIVERTX_V2   2
#define DTRIVERTX_LNI  3
#define DTRIVERTX_SIZE 4
typedef struct
{
	float		scale[3];	// multiply byte verts by this
	float		translate[3];	// then add this
	char		name[16];	// frame name from grabbing
	dtrivertx_t	verts[1];	// variable sized
} daliasframe_t;

// the glcmd format:
// a positive integer starts a tristrip command, followed by that many
// vertex structures.
// a negative integer starts a trifan command, followed by -x vertexes
// a zero indicates the end of the command list.
// a vertex consists of a floating point s, a floating point t,
// and an integer vertex index.


typedef struct
{
	int			ident;
	int			version;

	int			skinwidth;
	int			skinheight;
	int			framesize;		// byte size of each frame

	int			num_skins;
	int			num_xyz;
	int			num_st;			// greater than num_xyz for seams
	int			num_tris;
	int			num_glcmds;		// dwords in strip/fan command list
	int			num_frames;

	int			ofs_skins;		// each skin is a MAX_SKINNAME string
	int			ofs_st;			// byte offset from start for stverts
	int			ofs_tris;		// offset for dtriangles
	int			ofs_frames;		// offset for first frame
	int			ofs_glcmds;	
	int			ofs_end;		// end of file

} dmdl_t;

/*
========================================================================

.SP2 sprite file format

========================================================================
*/

#ifdef SIN
#define IDSPRITEHEADER	(('T'<<24)+('R'<<16)+('P'<<8)+'S')		// little-endian "SIN1"
#else
#define IDSPRITEHEADER	(('2'<<24)+('S'<<16)+('D'<<8)+'I') 		// little-endian "IDS2"
#endif
#ifdef SIN
#define SPRITE_VERSION 3
#else
#define SPRITE_VERSION	2
#endif

#ifdef SIN
#define SPR_VP_PARALLEL_UPRIGHT		0
#define SPR_FACING_UPRIGHT			1
#define SPR_VP_PARALLEL				2
#define SPR_ORIENTED				3
#define SPR_VP_PARALLEL_ORIENTED	4
#define SPR_ORIENTED_CROSS 5
#define SPR_ORIENTED_STAR 6

// sprite flags
#define SPRITE_WORLDLIT    (1<<0)
#define SPRITE_OVERBRIGHT  (1<<1)
#define SPRITE_HASBASE     (1<<2)
#define SPRITE_MODULATE    (1<<3)
#endif

typedef struct
{
	int		width, height;
	int		origin_x, origin_y;		// raster coordinates inside pic
#ifdef SIN
   float    alpha;
#endif
	char	   name[MAX_SKINNAME];		// name of pcx file
} dsprframe_t;

typedef struct {
	int			ident;
	int			version;
	int			numframes;
#ifdef SIN
   float       scale;
   int         type;
   int         flags;
	qboolean		twosided;
	dsprframe_t	base;			      // base frame present
#endif
	dsprframe_t	frames[1];			// variable sized
} dsprite_t;

/*
==============================================================================

  .WAL texture file format

==============================================================================
*/


#define	MIPLEVELS	4
typedef struct miptex_s
{
	char		name[32];
	unsigned	width, height;
    unsigned	offsets[MIPLEVELS];		// four mip maps stored
	char		animname[32];			// next frame in animation chain
	int			flags;
	int			contents;
	int			value;
} miptex_t;

#ifdef SIN
#define SIN_PALETTE_SIZE 256*4

/*
==============================================================================

  .SWL texture file format

==============================================================================
*/

typedef struct sinmiptex_s
{
	char		         name[64];
	unsigned	         width, height;
   byte              palette[SIN_PALETTE_SIZE];
   unsigned short    palcrc;
   unsigned	         offsets[MIPLEVELS];		// four mip maps stored
	char		         animname[64];			// next frame in animation chain
	unsigned	         flags;
	unsigned	         contents;
	unsigned short	   value;
   unsigned short    direct;
   float             animtime;
   float             nonlit;      
   unsigned short    directangle;
   unsigned short    trans_angle;
   float             directstyle;
   float             translucence; 
   float             friction;   
   float             restitution;   
   float             trans_mag;     
   float             color[3];      
} sinmiptex_t;
#endif

/*
==============================================================================

  .BSP file format

==============================================================================
*/

#define IDBSPHEADER	(('P'<<24)+('S'<<16)+('B'<<8)+'I')
		// little-endian "IBSP"

#define BSPVERSION	41


// upper design bounds
// leaffaces, leafbrushes, planes, and verts are still bounded by
// 16 bit short limits
#define	MAX_MAP_MODELS		1024
#define	MAX_MAP_BRUSHES		8192
#define	MAX_MAP_ENTITIES	2048
#define	MAX_MAP_ENTSTRING	0x40000
#define	MAX_MAP_TEXINFO		8192
#ifdef SIN
#define	MAX_MAP_LIGHTINFO		8192
#endif

#define	MAX_MAP_AREAS		256
#define	MAX_MAP_AREAPORTALS	1024
#define	MAX_MAP_PLANES		65536
#define	MAX_MAP_NODES		65536
#define	MAX_MAP_BRUSHSIDES	65536
#define	MAX_MAP_LEAFS		65536
#define	MAX_MAP_VERTS		65536
#define	MAX_MAP_FACES		65536
#define	MAX_MAP_LEAFFACES	65536
#define	MAX_MAP_LEAFBRUSHES 65536
#define	MAX_MAP_PORTALS		65536
#define	MAX_MAP_EDGES		128000
#define	MAX_MAP_SURFEDGES	256000
#ifdef SIN
#define	MAX_MAP_LIGHTING	0x300000
#else
#define	MAX_MAP_LIGHTING	0x200000
#endif
#ifdef SIN
#define	MAX_MAP_VISIBILITY	0x280000
#else
#define MAX_MAP_VISIBILITY  0x100000
#endif

// key / value pair sizes

#define	MAX_KEY		32
#define	MAX_VALUE	1024

//=============================================================================

typedef struct
{
	int		fileofs, filelen;
} lump_t;

#define	LUMP_ENTITIES		0
#define	LUMP_PLANES			1
#define	LUMP_VERTEXES		2
#define	LUMP_VISIBILITY		3
#define	LUMP_NODES			4
#define	LUMP_TEXINFO		5
#define	LUMP_FACES			6
#define	LUMP_LIGHTING		7
#define	LUMP_LEAFS			8
#define	LUMP_LEAFFACES		9
#define	LUMP_LEAFBRUSHES	10
#define	LUMP_EDGES			11
#define	LUMP_SURFEDGES		12
#define	LUMP_MODELS			13
#define	LUMP_BRUSHES		14
#define	LUMP_BRUSHSIDES		15
#define	LUMP_POP			16
#define	LUMP_AREAS			17
#define	LUMP_AREAPORTALS	18
#ifdef SIN
#define	LUMP_LIGHTINFO 	19
#define	HEADER_LUMPS		20
#else
#define	HEADER_LUMPS		19
#endif

typedef struct
{
	int			ident;
	int			version;	
	lump_t		lumps[HEADER_LUMPS];
} dheader_t;

typedef struct
{
	float		mins[3], maxs[3];
	float		origin[3];		// for sounds or lights
	int			headnode;
	int			firstface, numfaces;	// submodels just draw faces
										// without walking the bsp tree
} dmodel_t;


typedef struct
{
	float	point[3];
} dvertex_t;


// 0-2 are axial planes
#define	PLANE_X			0
#define	PLANE_Y			1
#define	PLANE_Z			2

// 3-5 are non-axial planes snapped to the nearest
#define	PLANE_ANYX		3
#define	PLANE_ANYY		4
#define	PLANE_ANYZ		5

// planes (x&~1) and (x&~1)+1 are allways opposites

typedef struct
{
	float	normal[3];
	float	dist;
	int		type;		// PLANE_X - PLANE_ANYZ ?remove? trivial to regenerate
} dplane_t;


// contents flags are seperate bits
// a given brush can contribute multiple content bits
// multiple brushes can be in a single leaf

// these definitions also need to be in q_shared.h!

// lower bits are stronger, and will eat weaker brushes completely
#define	CONTENTS_SOLID			1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			2		// translucent, but not watery
#ifdef SIN
#define	CONTENTS_FENCE			4
#else
#define	CONTENTS_AUX			4
#endif
#define	CONTENTS_LAVA			8
#define	CONTENTS_SLIME			16
#define	CONTENTS_WATER			32
#define	CONTENTS_MIST			64
#define	LAST_VISIBLE_CONTENTS	64

// remaining contents are non-visible, and don't eat brushes

#ifdef SIN
#define	CONTENTS_DUMMYFENCE	0x1000
#endif

#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEADMONSTER	0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000


#define	SURF_LIGHT		0x1		// value will hold the light strength

#ifdef SIN
#define	SURF_MASKED		0x2		// surface texture is masked
#else
#define	SURF_SLICK		0x2		// effects game physics
#endif

#define	SURF_SKY		0x4		// don't draw, but add to skybox
#define	SURF_WARP		0x8		// turbulent water warp
#ifdef SIN
#define	SURF_NONLIT	   0x10	// surface is not lit
#define	SURF_NOFILTER  0x20	// surface is not bi-linear filtered
#else
#define	SURF_TRANS33	0x10
#define	SURF_TRANS66	0x20
#endif
#ifdef SIN
#define	SURF_CONVEYOR  0x40	// surface is not lit
#else
#define	SURF_FLOWING	0x40	// scroll towards angle
#endif
#define	SURF_NODRAW		0x80	// don't bother referencing the texture

#define	SURF_HINT		0x100	// make a primary bsp splitter
#define	SURF_SKIP		0x200	// completely ignore, allowing non-closed brushes

#ifdef SIN
#define	SURF_WAVY            0x400       // surface has waves
#define	SURF_RICOCHET		   0x800	      // projectiles bounce literally bounce off this surface
#define	SURF_PRELIT		      0x1000	   // surface has intensity information for pre-lighting
#define	SURF_MIRROR		      0x2000	   // surface is a mirror
#define	SURF_CONSOLE         0x4000	   // surface is a console
#define	SURF_USECOLOR        0x8000	   // surface is lit with non-lit * color
#define	SURF_HARDWAREONLY    0x10000     // surface has been damaged
#define	SURF_DAMAGE          0x20000     // surface can be damaged
#define	SURF_WEAK            0x40000     // surface has weak hit points
#define	SURF_NORMAL          0x80000     // surface has normal hit points
#define	SURF_ADD             0x100000    // surface will be additive
#define	SURF_ENVMAPPED       0x200000    // surface is envmapped
#define	SURF_RANDOMANIMATE   0x400000    // surface start animating on a random frame
#define	SURF_ANIMATE         0x800000    // surface animates
#define	SURF_RNDTIME         0x1000000   // time between animations is random
#define	SURF_TRANSLATE       0x2000000   // surface translates
#define	SURF_NOMERGE         0x4000000   // surface is not merged in csg phase
#define  SURF_TYPE_BIT0       0x8000000   // 0 bit of surface type
#define  SURF_TYPE_BIT1       0x10000000  // 1 bit of surface type
#define  SURF_TYPE_BIT2       0x20000000  // 2 bit of surface type
#define  SURF_TYPE_BIT3       0x40000000  // 3 bit of surface type

#define SURF_START_BIT        27
#define SURFACETYPE_FROM_FLAGS( x ) ( ( x >> (SURF_START_BIT) ) & 0xf )


#define  SURF_TYPE_SHIFT(x)   ( (x) << (SURF_START_BIT) ) // macro for getting proper bit mask

#define  SURF_TYPE_NONE       SURF_TYPE_SHIFT(0)
#define  SURF_TYPE_WOOD       SURF_TYPE_SHIFT(1)
#define  SURF_TYPE_METAL      SURF_TYPE_SHIFT(2)
#define  SURF_TYPE_STONE      SURF_TYPE_SHIFT(3)
#define  SURF_TYPE_CONCRETE   SURF_TYPE_SHIFT(4)
#define  SURF_TYPE_DIRT       SURF_TYPE_SHIFT(5)
#define  SURF_TYPE_FLESH      SURF_TYPE_SHIFT(6)
#define  SURF_TYPE_GRILL      SURF_TYPE_SHIFT(7)
#define  SURF_TYPE_GLASS      SURF_TYPE_SHIFT(8)
#define  SURF_TYPE_FABRIC     SURF_TYPE_SHIFT(9)
#define  SURF_TYPE_MONITOR    SURF_TYPE_SHIFT(10)
#define  SURF_TYPE_GRAVEL     SURF_TYPE_SHIFT(11)
#define  SURF_TYPE_VEGETATION SURF_TYPE_SHIFT(12)
#define  SURF_TYPE_PAPER      SURF_TYPE_SHIFT(13)
#define  SURF_TYPE_DUCT       SURF_TYPE_SHIFT(14)
#define  SURF_TYPE_WATER      SURF_TYPE_SHIFT(15)
#endif

typedef struct
{
	int			planenum;
	int			children[2];	// negative numbers are -(leafs+1), not nodes
	short		mins[3];		// for frustom culling
	short		maxs[3];
	unsigned short	firstface;
	unsigned short	numfaces;	// counting both sides
} dnode_t;


#ifdef SIN

typedef struct lightvalue_s
{
    int			value;			// light emission, etc
    vec3_t   color;
    float    direct;
    float    directangle;
    float    directstyle;
    char     directstylename[32];
} lightvalue_t;

typedef struct texinfo_s
{
    float		vecs[2][4];		// [s/t][xyz offset]
    int			flags;			// miptex flags + overrides
    char		   texture[64];	// texture name (textures/*.wal)
    int			nexttexinfo;	// for animations, -1 = end of chain
    float      trans_mag;     
    int        trans_angle;
    int        base_angle;
    float      animtime;
    float      nonlit;      
    float      translucence; 
    float      friction;   
    float      restitution;  
    vec3_t     color;
    char       groupname[32];
} texinfo_t;

#else
typedef struct texinfo_s
{
	float		vecs[2][4];		// [s/t][xyz offset]
	int			flags;			// miptex flags + overrides
	int			value;			// light emission, etc
	char		texture[32];	// texture name (textures/*.wal)
	int			nexttexinfo;	// for animations, -1 = end of chain
} texinfo_t;
#endif

// note that edge 0 is never used, because negative edge nums are used for
// counterclockwise use of the edge in a face
typedef struct
{
	unsigned short	v[2];		// vertex numbers
} dedge_t;

#define	MAXLIGHTMAPS	16
typedef struct
{
	unsigned short	planenum;
	short		side;

	int			firstedge;		// we must support > 64k edges
	short		numedges;	
	short		texinfo;

// lighting info
	byte		styles[MAXLIGHTMAPS];
	int			lightofs;		// start of [numstyles*surfsize] samples
#ifdef SIN
   int      lightinfo;
#endif
} dface_t;

typedef struct
{
	int				contents;			// OR of all brushes (not needed?)

	short			cluster;
	short			area;

	short			mins[3];			// for frustum culling
	short			maxs[3];

	unsigned short	firstleafface;
	unsigned short	numleaffaces;

	unsigned short	firstleafbrush;
	unsigned short	numleafbrushes;
} dleaf_t;

typedef struct
{
	unsigned short	planenum;		// facing out of the leaf
	short	texinfo;
#ifdef SIN
   int lightinfo;
#endif
} dbrushside_t;

typedef struct
{
	int			firstside;
	int			numsides;
	int			contents;
} dbrush_t;

#define	ANGLE_UP	-1
#define	ANGLE_DOWN	-2


// the visibility lump consists of a header with a count, then
// byte offsets for the PVS and PHS of each cluster, then the raw
// compressed bit vectors
#define	DVIS_PVS	0
#define	DVIS_PHS	1
typedef struct
{
	int			numclusters;
	int			bitofs[8][2];	// bitofs[numclusters][2]
} dvis_t;

// each area has a list of portals that lead into other areas
// when portals are closed, other areas may not be visible or
// hearable even if the vis info says that it should be
typedef struct
{
	int		portalnum;
	int		otherarea;
} dareaportal_t;

typedef struct
{
	int		numareaportals;
	int		firstareaportal;
} darea_t;

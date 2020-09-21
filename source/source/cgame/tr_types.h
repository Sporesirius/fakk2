//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/tr_types.h                         $
// $Revision:: 24                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/28/00 7:34p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/tr_types.h                              $
// 
// 24    6/28/00 7:34p Markd
// Increased EXTENSIONS string size
// 
// 23    6/20/00 11:55a Markd
// changed frames from bytes to shorts
// 
// 22    3/31/00 11:45a Markd
// Added skyportal toggling support
// 
// 21    3/17/00 6:37p Markd
// fixed 8 bit anim bug
// 
// 20    3/04/00 2:47p Markd
// Made dynamic light types into bits so that they could be combined
// 
// 19    2/25/00 12:31p Markd
// Added additive dynamic light support
// 
// 18    2/21/00 7:02p Markd
// started adding old-school dlights and sky_alpha support
// 
// 17    2/14/00 5:41p Jimdose
// added uselegs to refEntity_t
// 
// 16    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 15    11/11/99 11:35a Jimdose
// added usetorso tp refEntity_t
// 
// 14    11/10/99 2:16p Jimdose
// added torso animation variables to refEntity_t
// 
// 13    10/29/99 6:52p Jimdose
// added bone controllers
// 
// 12    10/26/99 6:29p Jimdose
// added animation blending vars to refEntity_t
// 
// 11    10/25/99 12:19p Jimdose
// made head and torso angles local to each entity
// 
// 10    10/19/99 7:52p Markd
// Removed three part model system
// 
// 9     10/14/99 4:51p Jimdose
// added head_angles and torso_angles to refdef_t
// 
// 8     10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// Renderer types

#ifndef __TR_TYPES_H
#define __TR_TYPES_H


#define	MAX_DLIGHTS		32			// can't be increased, because bit flags are used on surfaces
#define	MAX_ENTITIES	1023		// can't be increased without changing drawsurf bit packing
#define  MAX_POINTS     32
#define  MAX_SPRITES    1024

// refdef flags
#define RDF_NOWORLDMODEL	1		// used for player configuration screen
#define RDF_HYPERSPACE		4		// teleportation effect

typedef struct
   {
   float pos[2];
   float size[2];
   } letterloc_t;

typedef struct 
   {
   int               indirection[256];
   letterloc_t       locations[256];
   char              name[255];
   float             height;
   float             aspectRatio;
   void             *shader;
   int               trhandle; // the last renderer handle this font used
   } fontheader_t;

typedef struct {
	vec3_t		xyz;
	float		st[2];
	byte		modulate[4];
} polyVert_t;

typedef struct poly_s {
	qhandle_t			hShader;
	int					numVerts;
	polyVert_t			*verts;
} poly_t;

typedef enum {
	RT_MODEL,
	RT_POLY,
	RT_SPRITE,
	RT_BEAM,
	RT_RAIL_CORE,
	RT_RAIL_RINGS,
	RT_LIGHTNING,
	RT_PORTALSURFACE,		// doesn't draw anything, just info for portals

	RT_MAX_REF_ENTITY_TYPE
} refEntityType_t;

typedef enum {
   lensflare = ( 1 << 0 ),
   viewlensflare = ( 1 << 1 ),
   additive = ( 1 << 2 )
} dlighttype_t;

struct tikiFrame_s;
struct dtiki_s;

typedef struct {
	refEntityType_t	reType;

	int			renderfx;

	qhandle_t	hModel;				         // opaque type outside refresh
                                          
	// most recent data                    
	vec3_t		lightingOrigin;		      // so multi-part models can be lit identically (RF_LIGHTING_ORIGIN)
	float		   shadowPlane;		         // projection shadows go here, stencils go slightly lower
                                          
	vec3_t		axis[3];			            // rotation vectors
	qboolean	   nonNormalizedAxes;	      // axis are not normalized, i.e. they have scale
	float		   origin[3];			         // also used as MODEL_BEAM's "from"
   int         anim;                      // animation
	int			oldanim;                   // old animation
	short			oldframe;                  // old frame
	short			frame;			            // also used as MODEL_BEAM's diameter
   float       scale;                     // scale of the thing
                                          
   qboolean    useAngles;                 
                                          
   // torso animation                     
   int         torso_anim;                // animation
	int 			torso_oldanim;             // old animation
	short			torso_frame;               
   short			torso_oldframe;            // old frame

   // data for animation cross-blending
   float       crossblend_lerp;
   float		   crossblend_backlerp;	      // 0.0 = current, 1.0 = old

	int   		crossblend_anim;           // crossblend animation
	short			crossblend_frame;          // crossblend anim frame
   short			crossblend_oldframe;       // crossblend anim old frame
   int         uselegs;                   // non-zero means use leg animation

   float       torso_crossblend_lerp;
   float		   torso_crossblend_backlerp; // 0.0 = current, 1.0 = old

   int   		torso_crossblend_anim;     // crossblend animation
	short			torso_crossblend_frame;    // crossblend anim frame
   short			torso_crossblend_oldframe; // crossblend anim old frame
   int         usetorso;                  // non-zero means use torso animation

   // previous data for frame interpolation
	float		   oldorigin[3];		         // also used as MODEL_BEAM's "to"
	float		   backlerp;			         // 0.0 = current, 1.0 = old
   float		   torso_backlerp;	         // 0.0 = current, 1.0 = old

	// texturing
	int			skinNum;			            // inline skin index
	qhandle_t	customSkin;			         // NULL for default skin
	qhandle_t	customShader;		         // use one image for the entire thing
                                          
	// misc                                
	byte		   shaderRGBA[4];		         // colors used by colorSrc=vertex shaders
	float		   shaderTexCoord[2];	      // texture coordinates used by tcMod=vertex modifiers
	float		   shaderTime;			// subtracted from refdef time to control effect start times
                                          
   int         entityNumber;              // the real entity number

   byte        surfaces[MAX_MODEL_SURFACES]; // the surface state of the entity
   short       shader_data[ 2 ];          // data passed in from shader manipulation

   int         bone_tag[ NUM_BONE_CONTROLLERS ];
   vec4_t      bone_quat[ NUM_BONE_CONTROLLERS ];

   // renderer use only
   struct tikiFrame_s   *of,
                        *nf;
   struct dtiki_s       *tiki;
   int         bonestart;

	// extra sprite information
	float		   radius;
	float		   rotation;

} refEntity_t;

#define	MAX_RENDER_STRINGS			8
#define	MAX_RENDER_STRING_LENGTH	32

typedef struct {
	int			x, y, width, height;
	float		fov_x, fov_y;
	vec3_t		vieworg;
	vec3_t		viewaxis[3];		// transformation matrix

	// time in milliseconds for shader effects and other time dependent rendering issues
	int			time;

	int			rdflags;			// RDF_NOWORLDMODEL, etc

	// 1 bits will prevent the associated area from rendering at all
	byte		areamask[MAX_MAP_AREA_BYTES];

	// text messages for deform text shaders
	char		text[MAX_RENDER_STRINGS][MAX_RENDER_STRING_LENGTH];

   // fog stuff
   float       farplane_distance;
   vec3_t      farplane_color;
   qboolean    farplane_cull;

   // sky portal stuff
   qboolean    sky_portal;
   float       sky_alpha;
   vec3_t      sky_origin;
   vec3_t      sky_axis[ 3 ];

} refdef_t;


typedef enum {
	STEREO_CENTER,
	STEREO_LEFT,
	STEREO_RIGHT
} stereoFrame_t;


/*
** glconfig_t
**
** Contains variables specific to the OpenGL configuration
** being run right now.  These are constant once the OpenGL
** subsystem is initialized.
*/
typedef enum {
	TC_NONE,
	TC_S3TC
} textureCompression_t;

typedef enum {
	GLDRV_ICD,					// driver is integrated with window system
								// WARNING: there are tests that check for
								// > GLDRV_ICD for minidriverness, so this
								// should always be the lowest value in this
								// enum set
	GLDRV_STANDALONE,			// driver is a non-3Dfx standalone driver
	GLDRV_VOODOO				// driver is a 3Dfx standalone driver
} glDriverType_t;

typedef enum {
	GLHW_GENERIC,			// where everthing works the way it should
	GLHW_3DFX_2D3D,			// Voodoo Banshee or Voodoo3, relevant since if this is
							// the hardware type then there can NOT exist a secondary
							// display adapter
	GLHW_RIVA128,			// where you can't interpolate alpha
	GLHW_RAGEPRO,			// where you can't modulate alpha on alpha textures
	GLHW_PERMEDIA2			// where you don't have src*dst
} glHardwareType_t;


typedef struct {
	char					renderer_string[ MAX_STRING_CHARS ];
	char					vendor_string[ MAX_STRING_CHARS ];
	char					version_string[ MAX_STRING_CHARS ];
	char					extensions_string[ MAX_STRING_CHARS * 2 ];

	int						maxTextureSize;			// queried from GL
	int						maxActiveTextures;		// multitexture ability

	int						colorBits, depthBits, stencilBits;

	glDriverType_t			driverType;
	glHardwareType_t		hardwareType;

	qboolean				deviceSupportsGamma;
	textureCompression_t	textureCompression;
	qboolean				textureEnvAddAvailable;

	int						vidWidth, vidHeight;
	// aspect is the screen's physical width / height, which may be different
	// than scrWidth / scrHeight if the pixels are non-square
	// normal screens should be 4/3, but wide aspect monitors may be 16/9
	float					windowAspect;

	int						displayFrequency;

	// synonymous with "does rendering consume the entire screen?", therefore
	// a Voodoo or Voodoo2 will have this set to TRUE, as will a Win32 ICD that
	// used CDS.
	qboolean				isFullscreen;
	qboolean				stereoEnabled;
	qboolean				smpActive;		// dual processor
} glconfig_t;

#if !defined _WIN32

#define _3DFX_DRIVER_NAME	"libMesaVoodooGL.so.3.1"
#define OPENGL_DRIVER_NAME	"libGL.so"

#else

#define _3DFX_DRIVER_NAME	"3dfxvgl"
#define OPENGL_DRIVER_NAME	"opengl32"

#endif	// !defined _WIN32


#endif	// __TR_TYPES_H

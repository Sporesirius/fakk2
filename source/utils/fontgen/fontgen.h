class FontGenException {
public:
   FontGenException () {}
};

#define ABORT throw FontGenException ()

const int FONT_STYLE_BOLD       = (1<<0);
const int FONT_STYLE_ITALIC     = (1<<1);
const int FONT_STYLE_UNDERLINE  = (1<<2);
const int FONT_STYLE_STRIKEOUT  = (1<<3);

typedef struct {
   float pos[2];
   float size[2];
} letterloc_t;

typedef struct {
   int indirection[256];
   letterloc_t locations[256];
   float height;
   float aspectRatio;
   char name[255];
} fontDef_t;

class FontGen {
// Init vars
   int 
      firstChar,
      lastChar,
      fontSize, 
      fontStyle;

   char fontName[255];
   char fontWinName[255];
   bool is_valid;

// Variable vars
   HFONT hf;
   HDC dc;
   HBITMAP dib, oldbitmap;
   unsigned char *bmbits;
   fontDef_t font_def;
   int texture_height;

// Functions
   void PrepareFont ();
   void PrepareBitmap ();
   void PrepareHeader ();
   void DrawFont ();
   void SaveTarga ();
   void SaveFontdef ();
   void SaveShader ();

public:
   FontGen ( int argc, char *argv[] );
   virtual ~FontGen ();
   
   bool IsValid () { return is_valid; }
   void Go ();
};

template <class T> 
void ZeroMem ( T &obj ) {
   memset ( &obj, 0, sizeof ( T ) );
}

typedef struct _TargaHeader {
   unsigned char  id_length, colormap_type, image_type;
   unsigned short colormap_index, colormap_length;
   unsigned char  colormap_size;
   unsigned short x_origin, y_origin, width, height;
   unsigned char  pixel_size, attributes;
} TargaHeader;

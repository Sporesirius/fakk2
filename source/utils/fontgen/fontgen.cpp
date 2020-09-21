#include <stdio.h>
#include <windows.h>
#include <direct.h>

#include "fontgen.h"

class MemoryStream {
private:
   unsigned char *mem;

public:
   MemoryStream ( void *p ) {
      mem = reinterpret_cast<unsigned char *>(p);
   }

   template <class T> MemoryStream &operator>> ( T &obj ) {
      memcpy ( &obj, mem, sizeof ( T ) );
      mem += T;
   }
   template <class T> MemoryStream &operator<< ( const T &obj ) {
      memcpy ( mem, &obj, sizeof ( T ) );
      mem += T;
   }
};

class ClosingFile {
   FILE *f;
   MemoryStream *mem;
   void *data;
   
public:
   ClosingFile () { 
      f = NULL; 
      mem = NULL;
      data = NULL;
   }
   ~ClosingFile () { 
      Close (); 
   }
   bool Open ( const char *file, const char *how ) {
      Close ();
      f = fopen ( file, how );
      
      return f != NULL;
   }
   operator FILE * () { return f; }
   
   template <class T> ClosingFile &operator<< ( const T &obj ) {
      if ( f ) 
         fwrite ( &obj, sizeof ( T ), 1, f );
      return *this;
   }

   template <class T> ClosingFile &operator>> ( const T &obj ) {
      if ( f ) 
         fread ( &obj, sizeof ( T ), 1, f );
      return *this;
   }

   void Close () { 
      if ( f ) 
         fclose ( f ); 
      
      if ( mem )
         delete mem;
      
      if ( data )
         free ( data );
      
      mem = NULL;
      data = NULL;
      f = NULL;
   }   
};

const char *GetArg ( int which, int argc, char *argv[] ) {
   if ( which >= argc )
      return "";
   else
      return argv[which];
}

#define ARG(X) GetArg ( X, argc, argv )

FontGen::FontGen ( int argc, char *argv[] ) :
hf ( NULL ), dc ( NULL ), dib ( NULL ), oldbitmap ( NULL ), fontStyle ( 0 ), fontSize ( 16 ), 
firstChar ( ' ' ), lastChar ( 126 ), is_valid ( false ) {
   int arg;
   
   fontName[0] = 0;
   fontWinName[0] = 0;

   for ( arg = 1; arg < argc; arg++ ) {
      if ( !stricmp ( ARG ( arg ), "-size" ) ) {
         fontSize = atoi ( ARG ( ++arg ) );
      }
      else if ( !stricmp ( ARG ( arg ), "-styles" ) ) {
         const char *styles = ARG ( ++arg );

         fontStyle = 0;
         if ( strstr ( styles, "bold" ) )
            fontStyle |= FONT_STYLE_BOLD;
         if ( strstr ( styles, "italic" ) )
            fontStyle |= FONT_STYLE_ITALIC;
         if ( strstr ( styles, "underline" ) )
            fontStyle |= FONT_STYLE_UNDERLINE;
         if ( strstr ( styles, "strikeout" ) )
            fontStyle |= FONT_STYLE_STRIKEOUT;
      }
      else if ( !stricmp ( ARG ( arg ), "-first" ) ) {
         firstChar = atoi ( ARG ( ++arg ) );
      } 
      else if ( !stricmp ( ARG ( arg ), "-last" ) ) {
         lastChar = atoi ( ARG ( ++arg ) );
      } 
      else if ( !stricmp ( ARG ( arg ), "-winname" ) ) {
         strcpy ( fontWinName, ARG ( ++arg ) );
      }
      else if ( !stricmp ( ARG ( arg ), "-name" ) ) {
         strcpy ( fontName, ARG ( ++arg ) );
      }
   }
   
   // Check validity...
   if ( firstChar >= lastChar ) {
      printf ( "ERROR: First char (%d) is >= last char (%d)\n", firstChar, lastChar );
      ABORT;
   }
   if ( fontSize <= 0 ) {
      printf ( "ERROR: Font size (%d) is <= 0\n", fontSize );
      ABORT;
   }
   if ( !fontName[0] ) {
      printf ( "ERROR: No font name specified (do it with -name)\n" );
      ABORT;
   }
   if ( !fontWinName[0] ) {
      printf ( "ERROR: No windows font name specified (do it with -winname)\n" );
      ABORT;
   }

   is_valid = true;
   return;
}

FontGen::~FontGen () {
   if ( dc ) {
      SelectObject ( dc, GetStockObject ( DEFAULT_GUI_FONT ) );
      if ( oldbitmap )
         SelectObject ( dc, oldbitmap );
   }

   if ( hf )
      DeleteObject ( hf );
   if ( dib )
      DeleteObject ( dib );
   if ( dc )
      DeleteDC ( dc );
}

void FontGen::PrepareFont () {
   hf = 
      ::CreateFont ( fontSize, 0, 0, 0, 
      ( fontStyle & FONT_STYLE_BOLD ) ? FW_BOLD : FW_NORMAL,
      ( fontStyle & FONT_STYLE_ITALIC ) ? TRUE : FALSE, 
      ( fontStyle & FONT_STYLE_UNDERLINE ) ? TRUE : FALSE,
      ( fontStyle & FONT_STYLE_STRIKEOUT ) ? TRUE : FALSE,
      DEFAULT_CHARSET,
      OUT_TT_PRECIS,
      CLIP_DEFAULT_PRECIS,
      PROOF_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE,
      fontWinName );

   

   if ( !hf ) {
      printf ( "ERROR: Could not create font object\n" );
      ABORT;
   }
}

void FontGen::PrepareBitmap () {
   BITMAPINFO bmi;
   BITMAPINFOHEADER &head = bmi.bmiHeader;

   dc = CreateCompatibleDC ( NULL );
   if ( !dc ) {
      printf ( "ERROR: Couldn't create DC\n" );
      ABORT;
   }

   SetTextColor ( dc, RGB ( 0xFF, 0xFF, 0xFF ) );
   SetBkColor ( dc, 0 );
   SelectObject ( dc, hf );

   SIZE theSize;
   GetTextExtentPoint32 ( dc, " ", 1, &theSize );
   fontSize = theSize.cy;

   ZeroMem ( bmi );
   head.biSize = sizeof ( BITMAPINFOHEADER );
   head.biWidth = 256;
   head.biHeight = 256;
   head.biPlanes = 1;
   head.biBitCount = 24;
   head.biCompression = BI_RGB;

   dib = CreateDIBSection ( dc, &bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&bmbits), NULL, 0 );
   if ( !dib ) {
      printf ( "ERROR: Could not create DIB section.\n" );
      ABORT;
   }

   oldbitmap = static_cast<HBITMAP>(SelectObject ( dc, dib ));

   memset ( bmbits, 0, 256 * 256 * 3 );
}

void FontGen::PrepareHeader () {
   int i;
   
   ZeroMem ( font_def );
   for ( i=0; i < 256; i++ )\
      font_def.indirection[i] = -1;
   for ( i=firstChar; i <= lastChar; i++ ) {
      font_def.indirection[i] = i-firstChar;
   }

   strcpy ( font_def.name, fontName );
   font_def.height = float ( fontSize );
}

void FontGen::DrawFont () {
   int currentLine = 0;
   int currentColumn = 0;
   int maxHeight = 0;
   int i;
   int numChars = lastChar - firstChar + 1;

   for ( i=0; i < numChars; i++ ) {
      char s[2];
      SIZE size;
      RECT fmtRect;

      s[0] = i + firstChar;
      s[1] = 0;

      if ( !GetTextExtentPoint32 ( dc, s, 1, &size ) ) {
         printf ( "ERROR: Couldn't draw character #%d (%c) - Bye!\n", (int) s[0], s[0] );
         ABORT;
      }

      // These below are padded for bilinear filtering
      size.cx += 1;
      size.cy += 1;

      if ( currentColumn + size.cx > 256 ) {
         currentColumn = 0;
         currentLine += maxHeight;
         maxHeight = 0;
         i--;
         continue;
      }

      if ( currentLine + size.cy > 256 ) {
         // FIXME allow multiple textures
         printf ( "ERROR: Font size exceeds 256x256 texture size.\n" );
         ABORT;
      }

      maxHeight = max ( maxHeight, size.cy );

      fmtRect.left = currentColumn;
      fmtRect.top = currentLine;
      fmtRect.right = fmtRect.left + size.cx - 1;
      fmtRect.bottom = fmtRect.top + size.cy - 1;

      if ( !DrawText ( dc, s, 1, &fmtRect, DT_LEFT | DT_NOPREFIX | DT_TOP ) ) {
         printf ( "ERROR: Drawtext failed on char #%d (%c) - Bye!\n", (int) s[0], s[0] );
      }

      font_def.locations[i].pos[0] = (float) currentColumn;
      font_def.locations[i].pos[1] = (float) currentLine;
      font_def.locations[i].size[0] = (float) size.cx-1;
      font_def.locations[i].size[1] = (float) size.cy-1;

      currentColumn += size.cx;
   }

   // This sees if it can eliminate things
   texture_height = 256;
   currentLine += maxHeight;

   font_def.aspectRatio = 1.f;

   while ( ( texture_height / 2 ) > currentLine ) 
      {
      texture_height /= 2;
      font_def.aspectRatio *= 2.f;
      }

   // I don't know how necessary this is, but it can't hurt.
   GdiFlush ();
}

void FontGen::SaveTarga () {
   ClosingFile f;
   TargaHeader tga;
   int start_line;
   int line;
   char fileName[255];

   mkdir ( "gfx" );
   mkdir ( "gfx/fonts" );

   sprintf ( fileName, "gfx/fonts/%s.tga", font_def.name );

   if ( !f.Open ( fileName, "wb" ) ) {
      printf ( "ERROR: Could not write %s\n", fileName );
      ABORT;
   }

   // Let's write the targa header
   ZeroMem ( tga );
   tga.image_type = 2;
   tga.width = 256;
   tga.height = texture_height;
   tga.pixel_size = 32;

   f << tga.id_length << tga.colormap_type << tga.image_type;
   f << tga.colormap_index << tga.colormap_length;
   f << tga.colormap_size;
   f << tga.x_origin << tga.y_origin << tga.width << tga.height;
   f << tga.pixel_size << tga.attributes;

   start_line = 256 - texture_height;

   for ( line = start_line; line < 256; line++ ) {
      int i;
      int bits;
      for ( i=0; i < 256*3; i+=3 ) {
         unsigned char c, a;
         
         bits = bmbits[256*3 * line + i];
         bits += bmbits[256*3 * line + i + 1];
         bits += bmbits[256*3 * line + i + 2];
         bits /= 3;
         a = bits;
         c = 255;
         f << c << c << c << a;
//         f << bmbits[256*3 * line + i];
      }
   }
}

void FontGen::SaveFontdef () 
   {
   ClosingFile f;
   char fileName[255];
   int i;

   mkdir ( "fonts" );
   sprintf ( fileName, "fonts/%s.RitualFont", font_def.name );

   if ( !f.Open ( fileName, "wt" ) )
      {
      printf ( "ERROR: Could not write %s\n", fileName );
      ABORT;
      }

   fprintf ( f, "RitFont\n" );
   fprintf ( f, "height %f\n", font_def.height );
   fprintf ( f, "aspect %.8f\n", font_def.aspectRatio );
   fprintf ( f, "indirections { \n" );
   for ( i=0; i < 256; i++ ) 
      {
      fprintf ( f, "%d ", font_def.indirection[i] );
      if ( ( i + 1 ) % 10 == 0 )
         fprintf ( f, "\n" );
//      if ( ( i + 1 ) % 40 == 0 )
//         fprintf ( f, "\n" );
      }

   fprintf ( f, "\n}\n" );
   fprintf ( f, "locations {\n" );
   for ( i=0; i < 256; i++ ) 
      {
      fprintf ( f, "{ %.8f %.8f %.8f %.8f } ", font_def.locations[i].pos[0], font_def.locations[i].pos[1],
         font_def.locations[i].size[0], font_def.locations[i].size[1] );
      if ( ( i + 1 ) % 3 == 0 )
         fprintf ( f, "\n" );
      }

   fprintf ( f, "\n}\n" );
   }

void FontGen::SaveShader ()
   {
   ClosingFile f;
   char fileName[255];

   mkdir ( "scripts" );
   sprintf ( fileName, "scripts/font_%s.shader", font_def.name );

   if ( !f.Open ( fileName, "wt" ) )
      {
      printf ( "ERROR: Could not write %s\n", fileName );
      ABORT;
      }

   fprintf ( f, "fonts/%s\n{\n", font_def.name );
   fprintf ( f, "  cull none\n" );
   fprintf ( f, "  noMipMaps\n" );
   fprintf ( f, "  {\n" );
   fprintf ( f, "    map textures/fonts/%s.tga\n", font_def.name );
   fprintf ( f, "    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA\n" );
   fprintf ( f, "    noDepthTest\n" );
   fprintf ( f, "  }\n}\n" );
   }

void FontGen::Go () {
   // Starts genereting the font stuff
   PrepareFont ();
   PrepareBitmap ();
   PrepareHeader ();
   DrawFont ();
   SaveTarga ();
   SaveFontdef ();
   //SaveShader (); No need for shader
}

void main ( int argc, char *argv[] ) {
   if ( argc == 1 )
      {
      printf ( "fontgen usage:\n" );
      printf ( " Required:\n" );
      printf ( "  -name <name>      - The font name that the game will use\n" );
      printf ( "  -winname \"<name>\" - The Windows name of the font (in quotes)\n" );
      printf ( " Optional:\n" );
      printf ( "  -size <number>    - The size of the font in pixels (default 16)\n" );
      printf ( "  -first <number>   - First character number to use. (default 32 (spacebar) )\n" );
      printf ( "  -last <number>    - Last character number to use (default 126)\n" );
      printf ( "  -styles <string>  - Styles to apply.  <string> is comma separated list of:\n" );
      printf ( "     bold, underline, strikeout, italic\n" );
      printf ( "     EX: For a bold underlined string, it's -styles bold,underline\n" );
      printf ( "     (No spaces between commas)\n" );
      printf ( "\nExiting...\n" );

      return;
      }
   
   try {
      FontGen font ( argc, argv );

      font.Go ();

      printf ( "Success!\n" );
   } catch ( FontGenException ) {
      printf ( "\nProgram did not finish.  Read above.\n" );
   }
}
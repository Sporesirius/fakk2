#include <stdafx.h>

#include "resource.h"
#include "drawobj.h"
#include "objprops.h"
#include "mousehandle.h"

static const int s_grabberSize = 7;

MouseEventHandler *cntHandler = NULL;

DrawingObjectList drawList;

DrawingObject::DrawingObject () : rect ( 0, 0, 0, 0 )
   {
   className      = "Button";
   borderstyle    = "RAISED";
   title          = "";
   name           = "Default";
   extended       = "";
   bgalpha        = 1.0f;
   fgalpha        = 1.0f;
   bgcolor[0] = bgcolor[1] = bgcolor[2] = 0.5;
   fgcolor[0] = fgcolor[1] = fgcolor[2] = 0;
   }

bool DrawingObject::Properties 
   (
   void
   )

   {
   CObjProps props;

   props.m_attribs      = extended;
   props.m_name         = name;
   props.m_title        = title;
   props.m_class        = className;
   props.m_linkcvar     = linkcvar;
   props.m_stuffcommand = stuffcommand;
   props.m_borderstyle  = borderstyle;
   props.m_position.Format ( "%d %d %d %d", rect.left, rect.top, rect.Width (), rect.Height () );
   props.m_fgcolor.Format ( "%0.2f %0.2f %0.2f", fgcolor[0], fgcolor[1], fgcolor[2] );
   props.m_bgcolor.Format ( "%0.2f %0.2f %0.2f", bgcolor[0], bgcolor[1], bgcolor[2] );
   props.m_bgalpha.Format ( "%0.2f", bgalpha );
   props.m_fgalpha.Format ( "%0.2f", fgalpha );

   if ( IDOK != props.DoModal () )
      return false;

   extended       = props.m_attribs;
   name           = props.m_name;
   title          = props.m_title;
   className      = props.m_class;
   linkcvar       = props.m_linkcvar;
   stuffcommand   = props.m_stuffcommand;
   borderstyle    = props.m_borderstyle;
   sscanf ( props.m_position, "%d %d %d %d", &rect.left, &rect.top, &rect.right, &rect.bottom );
   sscanf ( props.m_fgcolor, "%f %f %f", &fgcolor[0], &fgcolor[1], &fgcolor[2] );
   sscanf ( props.m_bgcolor, "%f %f %f", &bgcolor[0], &bgcolor[1], &bgcolor[2] );
   rect.right += rect.left;
   rect.bottom += rect.top;
   sscanf ( props.m_bgalpha, "%f", &bgalpha );
   sscanf ( props.m_fgalpha, "%f", &fgalpha );

   return true;
   }

DrawingObject::hits DrawingObject::HitTest 
   ( 
   CPoint pt
   )

   {
   if ( !rect.PtInRect ( pt ) )
      return DO_HIT_NONE;

   if ( rect.left + s_grabberSize > pt.x ) 
      {
      if ( rect.top + s_grabberSize > pt.y )      
         return DO_HIT_TLEFT;
      else if ( rect.bottom - s_grabberSize < pt.y )
         return DO_HIT_LLEFT;
      }
   else if ( rect.right - s_grabberSize < pt.x )
      {
      if ( rect.top + s_grabberSize > pt.y )
         return DO_HIT_TRIGHT;
      else if ( rect.bottom - s_grabberSize < pt.y )
         return DO_HIT_LRIGHT;
      }

   return DO_HIT_BODY;
   }

void DrawingObject::Draw 
   ( 
   CDC &dc
   )

   {
#if 0
   if ( active )
      {
      dc.SelectStockObject ( LTGRAY_BRUSH );
      }
   else
      {
      dc.SelectStockObject ( GRAY_BRUSH );
      }
   
   dc.SelectStockObject ( BLACK_PEN );
   dc.SelectStockObject ( DEFAULT_GUI_FONT );
#endif
   CBrush bgbrush;

   bgbrush.CreateSolidBrush( RGB( bgcolor[0]*255, bgcolor[1]*255, bgcolor[2]*255 ) );

   dc.SelectObject( bgbrush );
   dc.Rectangle ( rect );

   if ( active )
      {
      CBrush borderbrush;

      borderbrush.CreateSolidBrush( RGB( 255, 0, 0 ) );
      
      dc.SelectObject( borderbrush );
      dc.Rectangle( rect.left, rect.top, rect.left+3, rect.bottom );
      dc.Rectangle( rect.right, rect.top, rect.right-3, rect.bottom );
      dc.Rectangle( rect.left, rect.top, rect.right, rect.top+3 );
      dc.Rectangle( rect.left, rect.bottom, rect.right, rect.bottom-3 );
      }

   dc.SetTextColor( RGB( fgcolor[0]*255, fgcolor[1]*255, fgcolor[2]*255 ) );
   dc.SetBkColor ( GetSysColor ( COLOR_3DLIGHT ) );

   dc.SetBkMode ( TRANSPARENT );
   dc.DrawText ( title, rect, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE );

   // Let's draw the grabbers..

   dc.SelectStockObject ( BLACK_BRUSH );
   dc.Rectangle ( rect.left, rect.top, rect.left + s_grabberSize, rect.top + s_grabberSize );
   dc.Rectangle ( rect.left, rect.bottom - s_grabberSize, rect.left + s_grabberSize, rect.bottom );
   dc.Rectangle ( rect.right - s_grabberSize, rect.top, rect.right, rect.top + s_grabberSize );
   dc.Rectangle ( rect.right - s_grabberSize, rect.bottom - s_grabberSize, rect.right, rect.bottom );
   }

DrawingObjectList::DrawingObjectList 
   (
   void
   ) : workspaceSize ( 640, 480 ), workspaceName( "UnamedMenu" ), workspaceMotion( "NONE" ), time( "1" )

   {
   }

bool DrawingObjectList::SaveAs 
   (
   void
   )

   {
   CString newName;
   CFileDialog cfd ( FALSE, "urc", ( m_fileName == "" ) ? (const char *) NULL : m_fileName, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, 
      "Uber Resource Scripts (*.urc)|*.urc|All Files|*.*||", AfxGetMainWnd () );

   if ( cfd.DoModal () != IDOK )
      return false;

   m_fileName = cfd.GetPathName ();
   if ( !Save () ) 
      {
      m_fileName = "";
      return false;
      }
   else
      return true;
   }

bool DrawingObjectList::Save 
   (
   void
   )

   {
   if ( m_fileName == "" )
      {
      return SaveAs ();
      }

   FILE *f = fopen ( m_fileName, "wt" );
   POSITION pos;

   if ( !f )
      {
      AfxMessageBox ( "Couldn't open " + m_fileName + " for writing." );
      return false;
      }

   fprintf ( f, "menu \"%s\" %d %d %s %s\n", workspaceName, workspaceSize.cx, workspaceSize.cy, workspaceMotion, time );
   CString copy = extradata;
   copy.Remove( '\r' );
   fputs ( copy, f );
   fputs ( "\n", f );

   for ( pos = GetHeadPosition (); pos; GetNext ( pos ) )
      {
      DrawingObject &obj = GetAt ( pos );

      fprintf ( f, "resource\n%s\n{\n", obj.className );
      if ( obj.title != "" )
         fprintf ( f, "title \"%s\"\n", obj.title );
      fprintf ( f, "name \"%s\"\n", obj.name );
      fprintf ( f, "rect %d %d %d %d\n", obj.rect.left, obj.rect.top, obj.rect.Width (), obj.rect.Height () );
      fprintf ( f, "fgcolor %0.2f %0.2f %0.2f %0.2f\n", obj.fgcolor[0], obj.fgcolor[1], obj.fgcolor[2], obj.fgalpha );
      fprintf ( f, "bgcolor %0.2f %0.2f %0.2f %0.2f\n", obj.bgcolor[0], obj.bgcolor[1], obj.bgcolor[2], obj.bgalpha );
      fprintf ( f, "borderstyle \"%s\"\n", obj.borderstyle );

      if ( strlen( obj.stuffcommand ) )
         fprintf ( f, "stuffcommand \"%s\"\n", obj.stuffcommand );
      if ( strlen( obj.linkcvar ) )
         fprintf ( f, "linkcvar \"%s\"\n", obj.linkcvar );
      if ( obj.extended != "" ) 
         {
         CString copy = obj.extended;
         copy.Remove( '\r' );
         fputs ( copy, f );
         fputs ( "\n", f );
         }
      fputs ( "}\n", f );
      }
   fputs ( "end.\n", f );

   fclose ( f );

   return true;
   }

void fgets2 ( char *s, FILE *f )
   {
   if ( !fgets ( s, 255, f ) )
      throw DOOExcept ();

   if ( s[strlen(s) - 1] == '\n' )
      s[strlen(s) - 1] = 0;
   }


char *stripquotes
   (
   char *tok
   )

   {
   int i,j;
   char *buff;

   int len = strlen( tok );
   if ( len > 255 )
      throw DOOExcept ();
   
   buff = new char[len];

   j=0;
   for ( i=0; i<len; i++ )
      {
      if ( tok[i] != '"' )
         {
         buff[j++] = tok[i];
         }
      }
   
   buff[j] = 0;
   return buff;
   }

bool DrawingObjectList::Open
   (
   void
   )

   {
   int i;
   CString newName;
   CFileDialog cfd ( TRUE, "urc", NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
      "Uber Resource Scripts (*.urc)|*.urc|All Files|*.*||", AfxGetMainWnd () );

   if ( cfd.DoModal () != IDOK )
      return false;

   m_fileName = cfd.GetPathName ();

   FILE *f = fopen ( m_fileName, "rt" );
   char s[255];
   
   if ( !f ) 
      {
      AfxMessageBox ( "Couldn't open " + m_fileName + " for reading." );
      return false;
      }

   try
      {
      for ( fgets2 ( s, f ); stricmp ( s, "end." ); fgets2 ( s, f ) )
         {
         char *tok, *tok2;

         if ( !strnicmp ( s, "menu", 4 ) )
            {            
            tok = strtok ( s, " " );
            if ( !tok )
               throw DOOExcept ();
            
            tok = strtok ( NULL, " " );
            if ( tok )
               workspaceName = stripquotes( tok );
            
            tok = strtok ( NULL, " " );
            if ( tok )
               workspaceSize.cx = atol( tok );

            tok = strtok ( NULL, " " );
            if ( tok )
               workspaceSize.cy = atol( tok );

            tok = strtok ( NULL, " " );
            if ( tok )
               workspaceMotion = stripquotes( tok );

            tok = strtok ( NULL, " " );
            if ( tok )
               this->time = stripquotes( tok );
            }
         else if ( !stricmp ( s, "resource" ) )
            {
            DrawingObject obj;

            fgets2 ( s, f );
            obj.className = s;

            fgets2 ( s, f );
            if ( stricmp ( s, "{" ) )
               throw DOOExcept ();
            
            for ( fgets2 ( s, f ); stricmp ( s, "}" ); fgets2 ( s, f ) )
               {
               tok  = strtok ( s, " " );
               if ( !tok )
                  continue;

               if ( !stricmp ( tok, "name" ) )
                  {
                  tok2 = strtok ( NULL, "\"" );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.name = stripquotes( tok2 );
                  }
               else if ( !stricmp ( tok, "title" ) )
                  {
                  tok2 = strtok ( NULL, "\"" );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.title = stripquotes( tok2 );
                  }
               else if ( !stricmp ( tok, "linkcvar" ) )
                  {
                  tok2 = strtok ( NULL, "\"" );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.linkcvar = stripquotes( tok2 );
                  }
               else if ( !stricmp ( tok, "stuffcommand" ) )
                  {
                  tok2 = strtok ( NULL, "\"" );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.stuffcommand = stripquotes( tok2 );
                  }
               else if ( !stricmp ( tok, "borderstyle" ) )
                  {
                  tok2 = strtok ( NULL, "\"" );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.borderstyle = stripquotes( tok2 );
                  }
               else if ( !stricmp ( tok, "bgcolor" ) )
                  {
                  for ( i=0; i<3; i++ )
                     {
                     tok2 = strtok ( NULL, " " );
                     if ( !tok2 )
                        throw DOOExcept ();
                     obj.bgcolor[i] = (float)atof( tok2 );
                     }

                  tok2 = strtok ( NULL, " " );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.bgalpha = (float)atof( tok2 );
                  }
               else if ( !stricmp ( tok, "fgcolor" ) )
                  {
                  for ( i=0; i<3; i++ )
                     {
                     tok2 = strtok ( NULL, " " );
                     if ( !tok2 )
                        throw DOOExcept ();
                     obj.fgcolor[i] = (float)atof( tok2 );
                     }
                  tok2 = strtok ( NULL, " " );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.fgalpha = (float)atof( tok2 );
                  }
               else if ( !stricmp ( tok, "rect" ) )
                  {
                  tok2 = strtok ( NULL, " " );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.rect.left   = atol( tok2 );

                  tok2 = strtok ( NULL, " " );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.rect.top    = atol( tok2 );

                  tok2 = strtok ( NULL, " " );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.rect.right  = atol( tok2 );

                  tok2 = strtok ( NULL, " " );
                  if ( !tok2 )
                     throw DOOExcept ();
                  obj.rect.bottom = atol( tok2 );
                  
                  obj.rect.right += obj.rect.left;
                  obj.rect.bottom += obj.rect.top;
                  }
               else
                  {
                  tok2 = strtok( NULL, "" );
                  if ( tok2 )
                     obj.extended += tok + CString( " " ) + tok2 +  CString ( "\n" );
                  else
                     obj.extended += tok + CString ( "\n" );
                  }
               }
            if ( obj.extended.GetLength () )
               {
               obj.extended.Replace( "\n", "\r\n" );
               }
            AddTail ( obj );
            }
         else 
            {
            extradata += s + CString ( "\n" );
            }
         }
      }


   catch ( DOOExcept )
      {
      fclose ( f );
      AfxMessageBox ( "Invalid resource file.  File not loaded" );
      RemoveAll ();
      return false;
      }
   
   if ( extradata )
      {
      extradata.Replace( "\n", "\r\n" );
      }

   return true;
   }

   void DrawingObjectList::operator = 
   (
   const DrawingObjectList &other 
   )

   {
   POSITION pos;

   RemoveAll ();

   for ( pos = other.GetHeadPosition (); pos; other.GetNext ( pos ) ) 
      {
      AddTail ( other.GetAt ( pos ) );
      }

   workspaceSize     = other.workspaceSize;
   workspaceName     = other.workspaceName;
   workspaceMotion   = other.workspaceMotion;
   extradata         = other.extradata;
   time              = other.time;

   m_fileName = other.m_fileName;
   }
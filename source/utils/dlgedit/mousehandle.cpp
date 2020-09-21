#include <stdafx.h>

#include "resource.h"
#include "mousehandle.h"
#include "drawobj.h"
#include <stddef.h>

MouseEventHandler *mouseHandler = NULL;
POSITION lastClicked = NULL;

static const int s_minsizex = 30;
static const int s_minsizey = 15;

DefaultMouseEventHandler::DefaultMouseEventHandler
   (
   void
   )

   {
   SetCapture ( NULL );
   }

void DefaultMouseEventHandler::RightClick 
   (
   CPoint pt
   )

   {
   POSITION pos;
   lastClicked = NULL;

   for ( pos = drawList.GetTailPosition (); pos; drawList.GetPrev ( pos ) )
      {
      DrawingObject &obj = drawList.GetAt ( pos );
      DrawingObject::hits testRes = obj.HitTest ( pt );

      if ( testRes != DrawingObject::DO_HIT_NONE )
         {
         lastClicked = pos;
         break;
         }
      }
   
   CMenu menu, *subMenu;

   menu.LoadMenu ( IDR_MAINMENU );
   subMenu = menu.GetSubMenu ( 0 );

   AfxGetMainWnd ()->ClientToScreen ( &pt );
   subMenu->TrackPopupMenu ( TPM_RIGHTBUTTON, pt.x, pt.y, AfxGetMainWnd () );
   }

void DefaultMouseEventHandler::LeftDoubleClick 
   (
   CPoint pt
   )

   {
   POSITION pos;

   for ( pos = drawList.GetTailPosition (); pos; drawList.GetPrev ( pos ) )
      {
      DrawingObject &obj = drawList.GetAt ( pos );
      DrawingObject::hits testRes = obj.HitTest ( pt );

      if ( testRes == DrawingObject::DO_HIT_NONE )
         continue;

      obj.Properties ();
      AfxGetMainWnd ()->RedrawWindow ();
      break;
      }
   }

void DefaultMouseEventHandler::LeftButtonDown 
   (
   int keys, 
   CPoint pt
   )

   {
   POSITION pos;
   bool cleared = false;

   for ( pos = drawList.GetHeadPosition (); pos; drawList.GetNext ( pos ) )
      {
      DrawingObject &obj = drawList.GetAt ( pos );
      obj.active = false;
      }

   for ( pos = drawList.GetTailPosition (); pos; drawList.GetPrev ( pos ) )
      {
      DrawingObject &obj_old = drawList.GetAt ( pos );
      DrawingObject::hits testRes = obj_old.HitTest ( pt );

      if ( testRes == DrawingObject::DO_HIT_NONE )
         continue;

      // Let's bring the object forward
      DrawingObject new_obj = obj_old;

      drawList.RemoveAt ( pos );
      DrawingObject &obj = drawList.GetAt ( drawList.AddTail ( new_obj ) );

      obj.active = true;

      if ( testRes == DrawingObject::DO_HIT_BODY )
         mouseHandler = new MoveRectHandler ( &obj.rect, pt, CPoint ( 0, 0 ), CPoint ( 640, 480 ) );
      else 
         {
         long *x= NULL, *y = NULL;
         CPoint mins ( 0, 0 );
         CPoint maxes ( 640, 480 );

         if ( testRes == DrawingObject::DO_HIT_TLEFT || testRes == DrawingObject::DO_HIT_LLEFT ) 
            {
            x = &obj.rect.left;
            maxes.x = min ( obj.rect.right - s_minsizex, maxes.x );
            } 
         else 
            {
            x = &obj.rect.right;
            mins.x = max ( obj.rect.left + s_minsizex, mins.x );
            }

         if ( testRes == DrawingObject::DO_HIT_TLEFT || testRes == DrawingObject::DO_HIT_TRIGHT )
            {
            y = &obj.rect.top;
            maxes.y = min ( obj.rect.bottom - s_minsizey, maxes.y );
            }
         else
            {
            y = &obj.rect.bottom;
            mins.y = max ( obj.rect.top + s_minsizey, mins.y );
            }

         mouseHandler = new MoveXYHandler ( x, y, pt, mins, maxes );
         }  
      AfxGetMainWnd ()->SetCapture ();
      delete this;
      return;
      }
      
      DrawingObject obj;

      obj.rect.SetRect( pt, pt );
      drawList.AddTail( obj );

      DrawingObject &refobj = drawList.GetTail();
      mouseHandler = new MoveXYHandler( &refobj.rect.right, &refobj.rect.bottom, pt, pt + CPoint( 10,10 ), CPoint( 640,480 ) );
      delete this;
      return;
   }

MoveXYHandler::MoveXYHandler 
   (
   long *x,
   long *y,
   CPoint curMousePos,
   CPoint _mins,
   CPoint _maxes
   ) : px ( x ), py ( y ), orig ( *x, *y ), mins ( _mins ), maxes ( _maxes )
   
   {
   offset = CPoint ( curMousePos.x - *px, curMousePos.y - *py );
   }

template <class T>
T clamp ( T toclamp, T _min, T _max )
   {
   if ( toclamp < _min )
      return _min;
   if ( toclamp > _max )
      return _max;

   return toclamp;
   }

void MoveXYHandler::MouseMove
   (
   int keys,
   CPoint pt 
   )

   {
   *px = clamp ( pt.x - offset.x, mins.x, maxes.x );
   *py = clamp ( pt.y - offset.y, mins.y, maxes.y );

   AfxGetMainWnd ()->RedrawWindow ( NULL, NULL, RDW_INVALIDATE );
   }

void MoveXYHandler::LeftButtonUp 
   (
   int keys,
   CPoint pt
   )

   {
   MoveXYHandler::MouseMove ( keys | MK_LBUTTON, pt );

   DrawingObject &obj = drawList.GetAt ( drawList.GetTailPosition () );
   if( obj.rect.bottom - obj.rect.top <= 10 || obj.rect.right - obj.rect.left <= 10 )
	   drawList.RemoveTail ();
   
   if ( this == mouseHandler ) 
      {
      mouseHandler = new DefaultMouseEventHandler;
      delete this;
      }
   }

void MoveXYHandler::Cancel 
   (
   void
   )

   {
   *px = orig.x;
   *py = orig.y;

   AfxGetMainWnd ()->RedrawWindow ( NULL, NULL, RDW_INVALIDATE );

   if ( this == mouseHandler )
      {
      mouseHandler = new DefaultMouseEventHandler;
      delete this;
      }
   }

MoveRectHandler::MoveRectHandler 
   (
   CRect *rect,
   CPoint curMousePos,
   CPoint _mins,
   CPoint _maxes
   ) :
   topleft ( &rect->left, &rect->top, curMousePos, _mins, _maxes ),
   botright ( &rect->right, &rect->bottom, curMousePos, _mins + rect->Size (), _maxes + rect->Size () )

   {
   }

void MoveRectHandler::MouseMove
   (
   int keys,
   CPoint pt 
   )

   {
   topleft.MouseMove ( keys, pt );
   botright.MouseMove ( keys, pt );
   }

void MoveRectHandler::LeftButtonUp 
   (
   int keys,
   CPoint pt
   )

   {
   MoveRectHandler::MouseMove ( keys | MK_LBUTTON, pt );
   
   if ( this == mouseHandler ) 
      {
      mouseHandler = new DefaultMouseEventHandler;
      delete this;
      }
   }

void MoveRectHandler::Cancel 
   (
   void
   )

   {
   topleft.Cancel ();
   botright.Cancel ();

   if ( this == mouseHandler )
      {
      mouseHandler = new DefaultMouseEventHandler;
      delete this;
      }
   }
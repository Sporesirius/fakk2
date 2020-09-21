#ifndef __MOUSEHANDLE_H__
#define __MOUSEHANDLE_H__

class MouseEventHandler 
   {
   public:
      virtual void RightClick ( CPoint pt ) {}
      virtual void LeftDoubleClick ( CPoint pt ) {}
      virtual void LeftButtonDown ( int keys, CPoint pt ) {}
      virtual void LeftButtonUp ( int keys, CPoint pt ) {}
      virtual void MouseMove ( int keys, CPoint pt ) {}
      virtual void Cancel () {}

      virtual ~MouseEventHandler () {}
   };


class DefaultMouseEventHandler : public MouseEventHandler
   {
   public:
      DefaultMouseEventHandler ();
     
      virtual void RightClick ( CPoint pt );
      virtual void LeftDoubleClick ( CPoint pt );
      virtual void LeftButtonDown ( int keys, CPoint pt );
   };

class MoveXYHandler : public MouseEventHandler
   {
   long *px, *py;
   CPoint offset;
   CPoint orig;
   CPoint mins;
   CPoint maxes;

   public:
      MoveXYHandler ( long *x, long *y, CPoint curMousePos, CPoint _mins, CPoint _maxes );
      
      virtual void MouseMove ( int keys, CPoint pt );
      virtual void LeftButtonUp ( int keys, CPoint pt );
      virtual void Cancel ();
   };

class MoveRectHandler : public MouseEventHandler 
   {
   MoveXYHandler topleft, botright;

   public:
      MoveRectHandler ( CRect *rect, CPoint curMousePos, CPoint _mins, CPoint _maxes );

      virtual void MouseMove ( int keys, CPoint pt );
      virtual void LeftButtonUp ( int keys, CPoint pt );
      virtual void Cancel ();
   };

extern MouseEventHandler *mouseHandler;
extern POSITION lastClicked;

#endif /* !__MOUSEHANDLE_H__ */
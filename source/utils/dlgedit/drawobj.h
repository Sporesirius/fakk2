#ifndef __DRAWOBJ_H__
#define __DRAWOBJ_H__

class DrawingObject 
   {
   public:
      enum hits 
         {
         DO_HIT_NONE,
         DO_HIT_BODY,
         DO_HIT_TLEFT,
         DO_HIT_LLEFT,
         DO_HIT_TRIGHT,
         DO_HIT_LRIGHT
         };

      CString  className;
      CString  name;
      CString  title;
      CString  extended;
      CString  linkcvar;
      CString  stuffcommand;
      CString  borderstyle;
      float    fgcolor[3];
      float    bgcolor[3];
      CRect    rect;
      bool     active;
      float    bgalpha;
      float    fgalpha;

      DrawingObject ();
      void Draw ( CDC &dc );
      bool Properties ();
      bool DoColor( float color[3] );
      hits HitTest ( CPoint pt );

   };

class DOOExcept {};

class DrawingObjectList : public CList<DrawingObject, DrawingObject &>
   {
   CString m_fileName;
   public:
      DrawingObjectList ();

      bool Save ();
      bool SaveAs ();

      bool Open ();

      CString getFileName () { return m_fileName; }

      CSize workspaceSize;
      CString workspaceName;
      CString workspaceMotion;
      CString extradata;
	  CString time;

      void operator = ( const DrawingObjectList & );
   };

extern DrawingObjectList drawList;

#endif /* !__DRAWOBJ_H__ */
// dlgeditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dlgedit.h"
#include "dlgeditDlg.h"
#include "drawobj.h"
#include "mousehandle.h"
#include "menuprops.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgeditDlg dialog

CDlgeditDlg::CDlgeditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgeditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgeditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgeditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgeditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgeditDlg, CDialog)
	//{{AFX_MSG_MAP(CDlgeditDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_COMMAND(ID_DELETE_ITEM, OnDeleteItem)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveas)
	ON_COMMAND(ID_NEW_ITEM, OnNewItem)
	ON_WM_SIZE()
	ON_COMMAND(ID_MENU_PROPERTIES, OnMenuProperties)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_SENDTOBACK, OnEditSendtoback)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgeditDlg message handlers

BOOL CDlgeditDlg::OnInitDialog()
{
	CRect wndRect;

   CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
   // TODO: Add extra initialization here
	wndRect.SetRect ( 0, 0, 640, 480 );
   AdjustWindowRectEx ( wndRect, GetWindowLong ( m_hWnd, GWL_STYLE ), FALSE, GetWindowLong ( m_hWnd, GWL_EXSTYLE ) );
   MoveWindow ( wndRect );
   CenterWindow ();

   mouseHandler = new DefaultMouseEventHandler;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlgeditDlg::OnPaint() 
{
	CPaintDC dc ( this );
   POSITION pos;
   HRGN updateRgn;

   updateRgn = CreateRectRgnIndirect ( &dc.m_ps.rcPaint );

   for ( pos = drawList.GetHeadPosition (); pos; drawList.GetNext ( pos ) )
      {
      HRGN newRgn;
      DrawingObject &obj = drawList.GetAt ( pos );

      obj.Draw ( dc );
  
      newRgn = CreateRectRgnIndirect ( obj.rect );
      CombineRgn ( updateRgn, updateRgn, newRgn, RGN_DIFF );
      DeleteObject ( newRgn );
      }
   
   FillRgn ( dc.m_hDC, updateRgn, (HBRUSH) GetStockObject ( WHITE_BRUSH ) );

   DeleteObject ( updateRgn );
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgeditDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDlgeditDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
   mouseHandler->LeftDoubleClick ( point );
}

void CDlgeditDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
   mouseHandler->LeftButtonDown ( nFlags, point );
}

void CDlgeditDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
   mouseHandler->LeftButtonUp ( nFlags, point );
}

void CDlgeditDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
   mouseHandler->RightClick ( point );
}

void CDlgeditDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
   mouseHandler->MouseMove ( nFlags, point );
}

void CDlgeditDlg::OnCancelMode() 
{
   mouseHandler->Cancel ();   
}

void CDlgeditDlg::OnDeleteItem() 
{
   if ( !lastClicked )
      return;

   drawList.RemoveAt ( lastClicked );
   RedrawWindow ();
}

bool CDlgeditDlg::CheckAndContinue ()
   {
   int res;
   
   if ( !drawList.GetCount () )
      return true;
   
   CString saveString;

   if ( drawList.getFileName () == "" )
      saveString = "Would you like to save changes?";
   else
      saveString = "Would you like to save " + drawList.getFileName () + " first?";

   res = MessageBox ( "Would you like to save changes?", NULL, MB_YESNOCANCEL );

   if ( res == IDNO )
      return true;

   if ( res == IDCANCEL )
      return false;

   return drawList.Save ();
   }

void CDlgeditDlg::OnFileOpen() 
   {
   DrawingObjectList list;

   if ( !CheckAndContinue () )
      return;

   if ( list.Open () )
      {
      drawList = list;

      SetWindowText ( "Dialog Editor - " + drawList.getFileName () );

      // Now let's size the window.
	   CRect wndRect ( 0, 0, drawList.workspaceSize.cx, drawList.workspaceSize.cy );
      AdjustWindowRectEx ( wndRect, GetWindowLong ( m_hWnd, GWL_STYLE ), FALSE, GetWindowLong ( m_hWnd, GWL_EXSTYLE ) );
      MoveWindow ( wndRect );
      CenterWindow ();
      }
   else
      AfxMessageBox ( "Could not open file." );

   RedrawWindow ();
   }

void CDlgeditDlg::OnFileSave() 
   {
   drawList.Save ();
   
   if ( drawList.getFileName () != "" )
      SetWindowText ( "Dialog Editor - " + drawList.getFileName () );
   else
      SetWindowText ( "Dialog Editor" );
   }

void CDlgeditDlg::OnFileSaveas() 
{
   drawList.SaveAs ();
   
   if ( drawList.getFileName () != "" )
      SetWindowText ( "Dialog Editor - " + drawList.getFileName () );
   else
      SetWindowText ( "Dialog Editor" );
}

void CDlgeditDlg::OnNewItem() 
{
   DrawingObject obj;

   obj.rect.SetRect ( 0, 0, 200, 100 );
   if ( obj.Properties () )
      {
      drawList.AddTail ( obj );
      }
   RedrawWindow ();
}

void CDlgeditDlg::OnCancel() 
{
   if ( !CheckAndContinue () )
      return;

   CDialog::OnCancel();
}

void CDlgeditDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

   if ( nType == SIZE_RESTORED ) 
      {
      drawList.workspaceSize.cx = cx;
      drawList.workspaceSize.cy = cy;
      }
}

void CDlgeditDlg::OnMenuProperties() 
{
   MenuProps props;

   props.m_menuname  = drawList.workspaceName;
   props.m_motion    = drawList.workspaceMotion;
   props.m_extradata = drawList.extradata;
   props.m_time      = drawList.time;

   if ( IDOK != props.DoModal () )
      return;

   drawList.workspaceName = props.m_menuname;
   drawList.workspaceMotion = props.m_motion;
   drawList.extradata = props.m_extradata;
   drawList.time = props.m_time;
}

BOOL IsKeyDown(int virtKeyCode) 
{ 
    if (GetAsyncKeyState(virtKeyCode) & 0x8000) return TRUE; 
 
    return FALSE; 
} 

void CDlgeditDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   static DrawingObject *copyObj=NULL;
   static int offsetX=0,offsetY=0;

   if ( drawList.GetCount() <= 0 )
      return;

   DrawingObject &obj = drawList.GetTail();

   switch ( nChar )
      {
      case VK_NUMPAD8:
         obj.rect.top -= 1;
         obj.rect.bottom -= 1;
         break;
      case VK_NUMPAD2:
         obj.rect.top += 1;
         obj.rect.bottom += 1;
         break;
      case VK_NUMPAD4:
         obj.rect.left -= 1;
         obj.rect.right -= 1;
         break;
      case VK_NUMPAD6:
         obj.rect.left += 1;
         obj.rect.right += 1;
         break;
      case 'C':
         {
         if ( IsKeyDown( VK_CONTROL ) )
            {
            copyObj = &obj;
            offsetX = 0;
            offsetY = 0;
            }
         }
         break;
      case 'V':
         {
         if ( IsKeyDown( VK_CONTROL ) && copyObj )
            {
            DrawingObject newObj;

            newObj = *copyObj;
           
            offsetY += copyObj->rect.Height();
            
            newObj.rect.top      += offsetY;
            newObj.rect.bottom   += offsetY;
            
            drawList.AddTail ( newObj );
            RedrawWindow ();
            }
         break;
         }
      case 'B':
         {
         if ( IsKeyDown( VK_CONTROL ) && copyObj )
            {
            DrawingObject newObj;

            newObj.rect = copyObj->rect;
            newObj = *copyObj;

            offsetX += copyObj->rect.Width();
            
            newObj.rect.left    += offsetX;
            newObj.rect.right   += offsetX;            

            drawList.AddTail ( newObj );
            RedrawWindow ();
            }
         break;
         }
      case VK_DELETE:
		  if( obj.active )
			  drawList.RemoveTail ();

      default:
         break;
      }

   CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
   RedrawWindow ();
}

void CDlgeditDlg::OnOK() 
{
	POSITION pos;
	for ( pos = drawList.GetHeadPosition (); pos; drawList.GetNext ( pos ) )
	{
		DrawingObject &obj = drawList.GetAt ( pos );
		if ( obj.active )
		{
			mouseHandler->LeftDoubleClick ( obj.rect.CenterPoint () );
		}
	}

	return;
}

void CDlgeditDlg::OnEditSendtoback() 
{
	if ( !lastClicked )
		return;

	DrawingObject &obj = drawList.GetAt ( lastClicked );
	drawList.AddHead ( obj );
	drawList.RemoveAt ( lastClicked );

	RedrawWindow ();
}

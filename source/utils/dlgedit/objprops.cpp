// ObjProps.cpp : implementation file
//

#include "stdafx.h"
#include "dlgedit.h"
#include "ObjProps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjProps dialog


CObjProps::CObjProps(CWnd* pParent /*=NULL*/)
	: CDialog(CObjProps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjProps)
	m_attribs = _T("");
	m_title = _T("");
	m_position = _T("");
	m_name = _T("");
	m_class = _T("");
	m_stuffcommand = _T("");
	m_linkcvar = _T("");
	m_bgalpha = _T("");
	m_fgalpha = _T("");
	m_fgcolor = _T("");
	m_bgcolor = _T("");
	m_borderstyle = _T("");
	//}}AFX_DATA_INIT
}


void CObjProps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjProps)
	DDX_Text(pDX, IDC_ATTRIBS, m_attribs);
	DDX_Text(pDX, IDC_TITLE, m_title);
	DDX_Text(pDX, IDC_POSITION, m_position);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_CBString(pDX, IDC_CLASS, m_class);
	DDX_Text(pDX, IDC_STUFFCOMMAND, m_stuffcommand);
	DDX_Text(pDX, IDC_CVAR, m_linkcvar);
	DDX_Text(pDX, IDC_BGALPHA, m_bgalpha);
	DDX_Text(pDX, IDC_FGALPHA, m_fgalpha);
	DDX_CBString(pDX, IDC_BORDERSTYLE, m_borderstyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjProps, CDialog)
	//{{AFX_MSG_MAP(CObjProps)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BGCOLOR, OnBgcolor)
	ON_BN_CLICKED(IDC_FGCOLOR, OnFgcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjProps message handlers

void CObjProps::OnOK() 
{
   if ( !UpdateData ( TRUE ) )
      return;

   if ( m_name == "" || m_class == "" )
      {
      MessageBox ( "Name and class must all be filled in" );
      return;
      }
	
   int i[4];
   if ( sscanf ( m_position, "%d %d %d %d", i, i+1, i+2, i+3 ) != 4 )
      {
      MessageBox ( "x, y, width, height must be space-separated list of ints" );
      return;
      }

	CDialog::OnOK();
}

void CObjProps::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT dis) 
{
   float color[3];
   
   CDC dc;

   if ( ( nIDCtl != IDC_BGCOLOR ) && ( nIDCtl != IDC_FGCOLOR ) )
      return;

   dc.Attach ( dis->hDC );
   
   if ( nIDCtl == IDC_BGCOLOR )
      sscanf( m_bgcolor, "%f %f %f", &color[0], &color[1], &color[2] );
   else
      sscanf( m_fgcolor, "%f %f %f", &color[0], &color[1], &color[2] );

   dc.FillSolidRect ( &dis->rcItem, RGB ( color[0] * 255, color[1] * 255, color[2] * 255 ) );

   dc.Detach ();
	
	CDialog::OnDrawItem(nIDCtl, dis);
}

void CObjProps::OnFgcolor() 
{
   float             color[3]={ 0,0,0 };
	CHOOSECOLOR		   cc;
	static COLORREF	custom[16];;
   COLORREF          result;

   cc.lStructSize = sizeof(cc);
	cc.hwndOwner = NULL;
   cc.lpCustColors = custom;
	
#if 0
	cc.rgbResult =  (int)(color[0]*255) + 
	   	         ((int)(color[1]*255) <<8) +
		   		   ((int)(color[2]*255)<<16);
#endif

   cc.Flags = CC_FULLOPEN;//|CC_RGBINIT; 

   CColorDialog cd;

   cd.m_cc = cc;

   if ( IDOK != cd.DoModal () )
      return;
   
   result = cd.GetColor();
   
   color[0] = (float)(result&255)/255.0f;
	color[1] = (float)(result>>8&255)/255.0f;
	color[2] = (float)(result>>16&255)/255.0f;

   m_fgcolor.Format( "%0.2f %0.2f %0.2f", color[0], color[1], color[2] );

   GetDlgItem ( IDC_FGCOLOR )->RedrawWindow ();   
}

void CObjProps::OnBgcolor() 
{
	float             color[3]={ 0,0,0 };
	CHOOSECOLOR		   cc;
	static COLORREF	custom[16];;
   COLORREF          result;

   cc.lStructSize    = sizeof(cc);
	cc.hwndOwner      = NULL;
   cc.lpCustColors   = custom;
	
#if 0
	cc.rgbResult =  (int)(color[0]*255) + 
	   	         ((int)(color[1]*255) <<8) +
		   		   ((int)(color[2]*255)<<16);
#endif

   cc.Flags = CC_FULLOPEN;//|CC_RGBINIT; 

   CColorDialog cd;

   cd.m_cc = cc;

   if ( IDOK != cd.DoModal () )
      return;
   
   result = cd.GetColor();
   
   color[0] = (float)(result&255)/255.0f;
	color[1] = (float)(result>>8&255)/255.0f;
	color[2] = (float)(result>>16&255)/255.0f;

   m_bgcolor.Format( "%0.2f %0.2f %0.2f", color[0], color[1], color[2] );

   GetDlgItem ( IDC_BGCOLOR )->RedrawWindow ();   
}

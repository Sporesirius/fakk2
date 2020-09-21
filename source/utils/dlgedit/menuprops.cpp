// MenuProps.cpp : implementation file
//

#include "stdafx.h"
#include "dlgedit.h"
#include "MenuProps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MenuProps dialog


MenuProps::MenuProps(CWnd* pParent /*=NULL*/)
	: CDialog(MenuProps::IDD, pParent)
{
	//{{AFX_DATA_INIT(MenuProps)
	m_menuname = _T("");
	m_motion = _T("");
	m_extradata = _T("");
	m_time = _T("");
	//}}AFX_DATA_INIT
}


void MenuProps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MenuProps)
	DDX_Text(pDX, IDC_MENUNAME, m_menuname);
	DDX_CBString(pDX, IDC_MOTION, m_motion);
	DDX_Text(pDX, IDC_EXTRADATA, m_extradata);
	DDX_Text(pDX, IDC_TIME, m_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MenuProps, CDialog)
	//{{AFX_MSG_MAP(MenuProps)
	ON_EN_CHANGE(IDC_MENUNAME, OnChangeMenuname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MenuProps message handlers

void MenuProps::OnChangeMenuname() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

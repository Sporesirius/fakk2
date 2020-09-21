// dlgedit.h : main header file for the DLGEDIT application
//

#if !defined(AFX_DLGEDIT_H__4A13D7C4_300F_11D3_BFC7_005004759DF7__INCLUDED_)
#define AFX_DLGEDIT_H__4A13D7C4_300F_11D3_BFC7_005004759DF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgeditApp:
// See dlgedit.cpp for the implementation of this class
//

class CDlgeditApp : public CWinApp
{
public:
	CDlgeditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgeditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlgeditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDIT_H__4A13D7C4_300F_11D3_BFC7_005004759DF7__INCLUDED_)

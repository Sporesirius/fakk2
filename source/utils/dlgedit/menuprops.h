#if !defined(AFX_MENUPROPS_H__2F6C5CE2_3482_11D3_BECA_0060083D7614__INCLUDED_)
#define AFX_MENUPROPS_H__2F6C5CE2_3482_11D3_BECA_0060083D7614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuProps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MenuProps dialog

class MenuProps : public CDialog
{
// Construction
public:
	MenuProps(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MenuProps)
	enum { IDD = IDD_MENUPROPS };
	CString	m_menuname;
	CString	m_motion;
	CString	m_extradata;
	CString	m_time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MenuProps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MenuProps)
	afx_msg void OnChangeMenuname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUPROPS_H__2F6C5CE2_3482_11D3_BECA_0060083D7614__INCLUDED_)

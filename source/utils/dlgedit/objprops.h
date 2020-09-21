#if !defined(AFX_OBJPROPS_H__4A13D7CF_300F_11D3_BFC7_005004759DF7__INCLUDED_)
#define AFX_OBJPROPS_H__4A13D7CF_300F_11D3_BFC7_005004759DF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjProps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjProps dialog

class CObjProps : public CDialog
{
// Construction
public:
	CObjProps(CWnd* pParent = NULL);   // standard constructor

	CString	m_fgcolor;
   CString  m_bgcolor;

// Dialog Data
	//{{AFX_DATA(CObjProps)
	enum { IDD = IDD_PROPS };
	CString	m_attribs;
	CString	m_title;
	CString	m_position;
	CString	m_name;
	CString	m_class;
	CString	m_stuffcommand;
	CString	m_linkcvar;
	CString	m_bgalpha;
	CString	m_fgalpha;
	CString	m_borderstyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjProps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjProps)
	virtual void OnOK();
	afx_msg void OnChooseFGColor();
	afx_msg void OnChooseBGColor();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBgcolor();
	afx_msg void OnFgcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJPROPS_H__4A13D7CF_300F_11D3_BFC7_005004759DF7__INCLUDED_)

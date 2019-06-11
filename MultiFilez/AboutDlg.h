#if !defined(AFX_ABOUTDLG_H__D2C14108_0F5D_4C36_8BA7_36B82217A2AD__INCLUDED_)
#define AFX_ABOUTDLG_H__D2C14108_0F5D_4C36_8BA7_36B82217A2AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

class CAboutDlg : public CDialog
{
// Construction
public:
	CAboutDlg(CWnd* pParent = NULL);   // standard constructor

  void UpdateAllData();
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUT };
	CStatic	m_lblRegistered;
	CStatic	m_lblVersion;
	CStatic	m_lblInfo;
	CButton	m_btnRegExplorer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnRegExplorer();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTDLG_H__D2C14108_0F5D_4C36_8BA7_36B82217A2AD__INCLUDED_)
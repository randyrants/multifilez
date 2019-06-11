#if !defined(AFX_SPLASHDLG_H__2D88195D_E5B4_4A39_94AC_C0F874890667__INCLUDED_)
#define AFX_SPLASHDLG_H__2D88195D_E5B4_4A39_94AC_C0F874890667__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplashDlg dialog

class CSplashDlg : public CDialog
{
// Construction
public:
	CSplashDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSplashDlg)
	enum { IDD = IDD_SPLASH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void OnOK();
  virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSplashDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHDLG_H__2D88195D_E5B4_4A39_94AC_C0F874890667__INCLUDED_)

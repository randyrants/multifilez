#if !defined(AFX_DLGRESULTS_H__E5E93AEA_AB8E_4ACD_9A70_E04AE23CC5FD__INCLUDED_)
#define AFX_DLGRESULTS_H__E5E93AEA_AB8E_4ACD_9A70_E04AE23CC5FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgResults.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgResults dialog

class CDlgResults : public CDialog
{
    // Construction
public:
    CDlgResults(CWnd* pParent = NULL);   // standard constructor

    CStringArray ma_str;
    CUIntArray ma_n;

    CImageList m_ilIcons;

    // Dialog Data
        //{{AFX_DATA(CDlgResults)
    enum { IDD = IDD_REPORT };
    CListCtrl	m_lvStatus;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgResults)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgResults)
    virtual BOOL OnInitDialog();
    afx_msg void OnDblclkResults(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRESULTS_H__E5E93AEA_AB8E_4ACD_9A70_E04AE23CC5FD__INCLUDED_)

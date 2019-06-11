// MultiFilezDlg.h : header file
//

#if !defined(AFX_MULTIFILEZDLG_H__31ED90A5_A021_4234_A19C_AFBC5272D65D__INCLUDED_)
#define AFX_MULTIFILEZDLG_H__31ED90A5_A021_4234_A19C_AFBC5272D65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMultiFilezDlg dialog
#include "resource.h"
#include "DirTreeCtrl.h"
#include "RegistryKey.h"
#include "parsestring.h"
#include "splashdlg.h"
#include "aboutdlg.h"
#include "DlgResults.h"
#include "MFZ_Defines.h"
#include "encoding.h"

DWORD WINAPI AddFiles(LPVOID lpVoid);
DWORD WINAPI GoFiles(LPVOID lpVoid);

int FindAndReplace(CString strFile, CString strWith, CString strReplace);
int AddToLine(CString strFile, CString strWith, BOOL bStart);
int AddToFile(CString strFile, CString strWith, BOOL bStart);

class CMultiFilezDlg : public CDialog
{
	// Construction
public:
	CMultiFilezDlg(CWnd* pParent = NULL);	// standard constructor
	CStatusBarCtrl m_sbMain;
	CWinApp *theApp;
	CDirTreeCtrl m_dirTreeCtrl;
	CProgressCtrl m_pcMain;
	CImageList m_ilMain, m_ilCommands;

	HANDLE m_hThread;
	DWORD m_dwID;

	BOOL    m_bUseExplorer, m_bIncludeSubs, m_bCancel, m_bGo, m_bReport;
	int     m_nCurDo;
	CString m_strWorkingDir, m_strFilter, m_strDirList, m_strFilterList;
	CRect   m_rcReplace, m_rcWith, m_rcPane;

	CStringArray ma_strFiles;
	CUIntArray ma_nStatus;

	void AddToListView(CString strFile, int nPos);
	void ShowResults();

	// Dialog Data
	//{{AFX_DATA(CMultiFilezDlg)
	enum { IDD = IDD_MULTIFILEZ_DIALOG };
	CButton	m_chkReports;
	CButton	m_btnUp;
	CButton	m_btnDown;
	CButton	m_btnAddCriteria;
	CButton	m_btnGo;
	CButton	m_btnAddFiles;
	CButton	m_btnCancel;
	CListCtrl	m_lvCommands;
	CListCtrl	m_lvFiles;
	CButton	m_chkIncludeSubs;
	CComboBox	m_cbFilter;
	CTreeCtrl	m_tvDrives;
	CEdit	m_ebWith;
	CEdit	m_ebReplace;
	CStatic	m_lblWith;
	CStatic	m_lblThis;
	CComboBox	m_cbDo;
	CComboBox	m_cbWhere;
	CButton	m_chkUseExplorer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiFilezDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMultiFilezDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExplore();
	afx_msg void OnClose();
	afx_msg void OnSelchangeDo();
	afx_msg void OnSelchangedDrives(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddFiles();
	virtual void OnOK();
	afx_msg void OnAddCommand();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLvDelete();
	afx_msg void OnLvDeleteall();
	afx_msg void OnLvSelectall();
	afx_msg void OnLvCmdDelete();
	afx_msg void OnLvCmdDeleteall();
	afx_msg void OnLvCmdSelectall();
	afx_msg void OnKeydownFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownCommands(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGo();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnHelp();
	afx_msg void OnAbout();
	afx_msg void OnClickCancel();
	afx_msg void OnOpen();
	afx_msg void OnDblclkFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDown();
	afx_msg void OnUp();
	afx_msg void OnDblclkCommands(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnDown();
	afx_msg void OnBtnUp();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPostReports(WPARAM wParam, LPARAM lParam);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void LoadRegistry();
	void SaveRegistry();

	void SetDoSection(int n);
	void SetExplorer(int n);
	//  void GetSysImgList();
	void UpdateComboBoxes();

	void DeleteFiles(CListCtrl *lv);
	void DeleteAllFiles(CListCtrl *lv);
	void SelectAllFiles(CListCtrl *lv);

	void OpenFile();

	//void ResizeControls(int cx, int cy);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIFILEZDLG_H__31ED90A5_A021_4234_A19C_AFBC5272D65D__INCLUDED_)

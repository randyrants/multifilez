// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultiFilez.h"
#include "AboutDlg.h"
#include "registrykey.h"
#include "MFZ_Defines.h"
#include "encoding.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog


CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
  DDX_Control(pDX, IDC_REG_EXPLORER, m_btnRegExplorer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_REG_EXPLORER, OnRegExplorer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

  UpdateAllData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::UpdateAllData()
{
  // Check to see if it's registered
  CRegistryKey hKey;
  LONG l;
  l = hKey.Open(HKEY_CLASSES_ROOT, "Directory\\shell\\MultiFilez");

  if (l == ERROR_SUCCESS) {
    m_btnRegExplorer.SetWindowText("Unregister in &Explorer");
  }
  else {
    m_btnRegExplorer.SetWindowText("Register in &Explorer");
  }
  hKey.Close();
}


void CAboutDlg::OnRegExplorer() 
{
  CRegistryKey hKey;
  LONG l;
  CString strButton;
  m_btnRegExplorer.GetWindowText(strButton);

  if (strButton == "Register in &Explorer") {
    l = hKey.Create(HKEY_CLASSES_ROOT, "Directory\\shell\\MultiFilez");
    if (l == ERROR_SUCCESS) {
      hKey.SetValue("Open MultiFilez Here", "");
    }
    hKey.Close();
    if (l != ERROR_SUCCESS)
      return;

    l = hKey.Create(HKEY_CLASSES_ROOT, "Directory\\shell\\MultiFilez\\command");
    if (l == ERROR_SUCCESS) {
      char szDir[MAX_PATH];
      memset(szDir, 0, sizeof(szDir));
      GetCurrentDirectory(sizeof(szDir), szDir);

      CString strDir;
      strDir.Format("\"%s\\%s\" \"%%1\"", szDir, AfxGetAppName());
      hKey.SetValue(strDir, "");
    }
    hKey.Close();
    if (l != ERROR_SUCCESS)
      return;

    l = hKey.Create(HKEY_CLASSES_ROOT, "Drive\\shell\\MultiFilez");
    if (l == ERROR_SUCCESS) {
      hKey.SetValue("Open MultiFilez Here", "");
    }
    hKey.Close();
    if (l != ERROR_SUCCESS)
      return;

    l = hKey.Create(HKEY_CLASSES_ROOT, "Drive\\shell\\MultiFilez\\command");
    if (l == ERROR_SUCCESS) {
      char szDir[MAX_PATH];
      memset(szDir, 0, sizeof(szDir));
      GetCurrentDirectory(sizeof(szDir), szDir);

      CString strDir;
      strDir.Format("\"%s\\%s\" \"%%1\"", szDir, AfxGetAppName());
      hKey.SetValue(strDir, "");
    }
    hKey.Close();
    if (l != ERROR_SUCCESS)
      return;

    m_btnRegExplorer.SetWindowText("Unregister in &Explorer");
  }
  else {
    l = hKey.Open(HKEY_CLASSES_ROOT, "Directory\\shell\\MultiFilez");
    if (l == ERROR_SUCCESS) {
      hKey.DeleteSubKey("command");
    }
    hKey.Close();
    if (l != ERROR_SUCCESS)
      return;

    l = hKey.Open(HKEY_CLASSES_ROOT, "Directory\\shell");
    if (l == ERROR_SUCCESS) {
      hKey.DeleteSubKey("MultiFilez");
    }
    hKey.Close();
    if (l != ERROR_SUCCESS)
      return;

    l = hKey.Open(HKEY_CLASSES_ROOT, "Drive\\shell\\MultiFilez");
    if (l == ERROR_SUCCESS) {
      hKey.DeleteSubKey("command");
    }
    hKey.Close();
    if (l != ERROR_SUCCESS)
      return;

    l = hKey.Open(HKEY_CLASSES_ROOT, "Drive\\shell");
    if (l == ERROR_SUCCESS) {
      hKey.DeleteSubKey("MultiFilez");
    }
    hKey.Close();
    if (l != ERROR_SUCCESS)
      return;

    m_btnRegExplorer.SetWindowText("Register in &Explorer");
  }
}


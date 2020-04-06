// MultiFilezDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultiFilez.h"
#include "MultiFilezDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiFilezDlg dialog

CMultiFilezDlg::CMultiFilezDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CMultiFilezDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CMultiFilezDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_bCancel = FALSE;
    m_bGo = FALSE;
    m_hThread = NULL;
    //  m_bRegistered = FALSE;
    m_bRegistered = TRUE;
    LoadRegistry();
}

void CMultiFilezDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CMultiFilezDlg)
    DDX_Control(pDX, IDC_CHK_RESULTS, m_chkReports);
    DDX_Control(pDX, IDC_UP, m_btnUp);
    DDX_Control(pDX, IDC_DOWN, m_btnDown);
    DDX_Control(pDX, IDC_ADD_COMMAND, m_btnAddCriteria);
    DDX_Control(pDX, IDC_GO, m_btnGo);
    DDX_Control(pDX, IDC_ADD_FILES, m_btnAddFiles);
    DDX_Control(pDX, IDC_CLICKCANCEL, m_btnCancel);
    DDX_Control(pDX, IDC_COMMANDS, m_lvCommands);
    DDX_Control(pDX, IDC_FILES, m_lvFiles);
    DDX_Control(pDX, IDC_SUBS, m_chkIncludeSubs);
    DDX_Control(pDX, IDC_FILTER, m_cbFilter);
    DDX_Control(pDX, IDC_WITH, m_ebWith);
    DDX_Control(pDX, IDC_REPLACE, m_ebReplace);
    DDX_Control(pDX, IDC_LBL_WITH, m_lblWith);
    DDX_Control(pDX, IDC_LBL_THIS, m_lblThis);
    DDX_Control(pDX, IDC_DO, m_cbDo);
    DDX_Control(pDX, IDC_WHERE, m_cbWhere);
    DDX_Control(pDX, IDC_EXPLORE, m_chkUseExplorer);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMultiFilezDlg, CDialog)
    //{{AFX_MSG_MAP(CMultiFilezDlg)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_EXPLORE, OnExplore)
    ON_WM_CLOSE()
    ON_CBN_SELCHANGE(IDC_DO, OnSelchangeDo)
    ON_NOTIFY(TVN_SELCHANGED, IDC_DRIVES, OnSelchangedDrives)
    ON_BN_CLICKED(IDC_ADD_FILES, OnAddFiles)
    ON_BN_CLICKED(IDC_ADD_COMMAND, OnAddCommand)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(IDM_LV_DELETE, OnLvDelete)
    ON_COMMAND(IDM_LV_DELETEALL, OnLvDeleteall)
    ON_COMMAND(IDM_LV_SELECTALL, OnLvSelectall)
    ON_COMMAND(IDM_LV_CMDDELETE, OnLvCmdDelete)
    ON_COMMAND(IDM_LV_CMDDELETEALL, OnLvCmdDeleteall)
    ON_COMMAND(IDM_LV_CMDSELECTALL, OnLvCmdSelectall)
    ON_NOTIFY(LVN_KEYDOWN, IDC_FILES, OnKeydownFiles)
    ON_NOTIFY(LVN_KEYDOWN, IDC_COMMANDS, OnKeydownCommands)
    ON_BN_CLICKED(IDC_GO, OnGo)
    ON_COMMAND(IDM_ABOUT, OnAbout)
    ON_BN_CLICKED(IDC_CLICKCANCEL, OnClickCancel)
    ON_COMMAND(IDM_OPEN, OnOpen)
    ON_NOTIFY(NM_DBLCLK, IDC_FILES, OnDblclkFiles)
    ON_COMMAND(IDM_DOWN, OnDown)
    ON_COMMAND(IDM_UP, OnUp)
    ON_NOTIFY(NM_DBLCLK, IDC_COMMANDS, OnDblclkCommands)
    ON_BN_CLICKED(IDC_DOWN, OnBtnDown)
    ON_BN_CLICKED(IDC_UP, OnBtnUp)
    ON_WM_SIZE()
    ON_MESSAGE(MFZ_POSTREPORTS, OnPostReports)
    ON_WM_INITMENU()
    ON_WM_NCHITTEST()
    ON_WM_SETCURSOR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiFilezDlg message handlers

BOOL CMultiFilezDlg::OnInitDialog()
{
    BeginWaitCursor();

    CDialog::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    //GetSysImgList();
    m_ilCommands.Create(IDB_LV_COMMANDS, 16, 1, RGB(255, 0, 255));
    m_lvFiles.SetImageList(&m_ilCommands, LVSIL_SMALL);
    m_lvCommands.SetImageList(&m_ilCommands, LVSIL_SMALL);
    m_lvCommands.SetExtendedStyle(m_lvCommands.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

    // Insert column
    LV_COLUMN lvCol;
    CRect rc;

    memset(&lvCol, 0, sizeof(lvCol));
    lvCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
    lvCol.fmt = LVCFMT_LEFT;
    m_lvCommands.GetClientRect(&rc);
    lvCol.cx = rc.Width();
    lvCol.pszText = "Criteria";
    lvCol.cchTextMax = sizeof(lvCol.pszText);
    lvCol.iSubItem = 0;
    m_lvCommands.InsertColumn(0, &lvCol);

    memset(&lvCol, 0, sizeof(lvCol));
    lvCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
    lvCol.fmt = LVCFMT_LEFT;
    lvCol.cx = 0;
    lvCol.pszText = "Storage";
    lvCol.cchTextMax = sizeof(lvCol.pszText);
    lvCol.iSubItem = 1;
    m_lvCommands.InsertColumn(1, &lvCol);

    m_sbMain.Create(CCS_BOTTOM | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_STATUS_BAR);

    int a_nWidth[3] = { 270, 540, -1 };
    m_sbMain.SetParts(3, a_nWidth);
    m_sbMain.SetText("0 files selected for editing", 0, 0);
    m_sbMain.SetText("0 changes made in 0 files", 1, 0);
    m_sbMain.SetText("Ready", 2, 0);

    m_sbMain.GetRect(2, &m_rcPane);

    m_pcMain.Create(WS_CHILD | PBS_SMOOTH, m_rcPane, &m_sbMain, IDC_PROGRESS_BAR);

    // Here we subclass our CDirTreeCtrl
    if (!m_dirTreeCtrl.m_hWnd) {
        if (m_dirTreeCtrl.SubclassDlgItem(IDC_DRIVES, this)) {
            // set the Path to the current Work-Directory
            m_dirTreeCtrl.SetSelPath(m_strWorkingDir);
        }
    }

    m_ebReplace.GetWindowRect(m_rcReplace);
    ScreenToClient(m_rcReplace);
    m_ebWith.GetWindowRect(m_rcWith);
    ScreenToClient(m_rcWith);

    m_cbFilter.SetWindowText(m_strFilter);;
    m_cbWhere.SetWindowText(m_strWorkingDir);
    m_cbDo.SetCurSel(m_nCurDo);
    SetDoSection(m_nCurDo);

    m_chkUseExplorer.SetCheck(m_bUseExplorer);
    SetExplorer(m_bUseExplorer);

    m_chkIncludeSubs.SetCheck(m_bIncludeSubs);

    m_chkReports.SetCheck(m_bReport);

    CStringArray a_str;
    parseStr('\05', m_strDirList, a_str);
    for (int n = 0; n < a_str.GetSize(); n++) {
        m_cbWhere.AddString(a_str[n]);
    }

    a_str.RemoveAll();
    parseStr('\05', m_strFilterList, a_str);
    for (int n = 0; n < a_str.GetSize(); n++) {
        m_cbFilter.AddString(a_str[n]);
    }

    EndWaitCursor();
    return TRUE;  // return TRUE unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMultiFilezDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMultiFilezDlg::OnQueryDragIcon()
{
    return (HCURSOR)m_hIcon;
}

void CMultiFilezDlg::OnExplore()
{
    SetExplorer(m_chkUseExplorer.GetCheck());
}

void CMultiFilezDlg::OnClose()
{
    if (m_bGo) {
        MessageBox("Please wait until the file editing is done before closing.", APP_NAME, MB_ICONSTOP);
        return;
    }
    OnClickCancel();
    SaveRegistry();
    m_ilMain.Detach();
    m_ilCommands.Detach();
    CDialog::OnClose();
    CloseHandle(m_hThread);
}

void CMultiFilezDlg::SetDoSection(int n)
{
    if (n != 0) {
        m_ebReplace.ShowWindow(SW_HIDE);
        m_lblWith.ShowWindow(SW_HIDE);
        m_ebWith.SetWindowPos(NULL, m_rcReplace.left, m_rcWith.top, m_rcWith.right - m_rcReplace.left, m_rcWith.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
    }
    else {
        m_ebReplace.ShowWindow(SW_SHOW);
        m_lblWith.ShowWindow(SW_SHOW);
        m_ebWith.SetWindowPos(NULL, m_rcWith.left, m_rcWith.top, m_rcWith.Width(), m_rcWith.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
    }
}

void CMultiFilezDlg::SetExplorer(int n)
{
    CString strTemp = m_strWorkingDir;
    if (n) {
        theApp->DoWaitCursor(TRUE);
        m_dirTreeCtrl.EnableWindow(TRUE);
        m_dirTreeCtrl.DisplayTree(NULL, FALSE);
        m_dirTreeCtrl.SetSelPath(m_strWorkingDir);
        theApp->DoWaitCursor(FALSE);
    }
    else {
        m_dirTreeCtrl.DeleteAllItems();
        m_dirTreeCtrl.EnableWindow(FALSE);
    }
    m_strWorkingDir = strTemp;
    m_cbWhere.SetWindowText(m_strWorkingDir);
}

void CMultiFilezDlg::OnSelchangeDo()
{
    SetDoSection(m_cbDo.GetCurSel());
}

void CMultiFilezDlg::OnSelchangedDrives(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    TVITEM tvItem;
    memset(&tvItem, 0, sizeof(tvItem));
    tvItem = pNMTreeView->itemNew;

    m_strWorkingDir = m_dirTreeCtrl.GetFullPath(tvItem.hItem);
    m_cbWhere.SetWindowText(m_strWorkingDir);

    *pResult = 0;
}

void CMultiFilezDlg::AddToListView(CString strFile, int nPos)
{
    m_lvFiles.InsertItem(nPos, strFile, 5);

    // Cool icon thing that takes a lot of time.
    // Adding the Item to the TreeCtrl with the current Icons
    /*	SHFILEINFO shFinfo;
    int iIcon, iIconSel;
    CString    strTemp = strFile;

    if (!SHGetFileInfo( strTemp,
    0,
    &shFinfo,
    sizeof(shFinfo),
    SHGFI_ICON | SHGFI_SMALLICON)) {
    return;
    }

    iIcon = shFinfo.iIcon;

    DestroyIcon( shFinfo.hIcon );

    if (!SHGetFileInfo( strTemp,
    0,
    &shFinfo,
    sizeof( shFinfo ),
    SHGFI_ICON | SHGFI_OPENICON | SHGFI_SMALLICON)) {
    return;
    }

    iIconSel = shFinfo.iIcon;

    DestroyIcon( shFinfo.hIcon );

    m_lvFiles.InsertItem(nPos, strFile, iIcon);
    */
}

/*void CMultiFilezDlg::GetSysImgList()
{
SHFILEINFO shFinfo;
HIMAGELIST hImgList = NULL;

if (m_lvFiles.GetImageList( LVSIL_SMALL ) )
m_ilMain.Detach();

hImgList = (HIMAGELIST)SHGetFileInfo( "C:\\",
0,
&shFinfo,
sizeof( shFinfo ),
SHGFI_SYSICONINDEX |
SHGFI_SMALLICON );

if ( !hImgList )
return;

m_ilMain.m_hImageList = hImgList;
m_lvFiles.SetImageList(&m_ilMain, LVSIL_SMALL);
return;   // OK
}
*/
void CMultiFilezDlg::UpdateComboBoxes()
{
    int nPos = m_cbFilter.FindStringExact(0, m_strFilter);
    if (nPos != CB_ERR)
        m_cbFilter.DeleteString(nPos);
    if (m_cbFilter.GetCount() == 10)
        m_cbFilter.DeleteString(9);
    m_cbFilter.InsertString(0, m_strFilter);
    m_cbFilter.SetCurSel(0);

    nPos = m_cbWhere.FindStringExact(0, m_strWorkingDir);
    if (nPos != CB_ERR)
        m_cbWhere.DeleteString(nPos);
    if (m_cbWhere.GetCount() == 10)
        m_cbWhere.DeleteString(9);
    m_cbWhere.InsertString(0, m_strWorkingDir);
    m_cbWhere.SetCurSel(0);
}

void CMultiFilezDlg::OnOK()
{
    CWnd* wnd = GetFocus();
    CWnd* wndParent;

    if (wnd)
        wndParent = wnd->GetParent();
    if ((wnd == &m_cbFilter) || (wndParent == &m_cbFilter))
        OnAddFiles();
    else if ((wnd == &m_cbWhere) || (wndParent == &m_cbWhere))
        OnAddFiles();
    else if (wnd == &m_chkIncludeSubs)
        OnAddFiles();
    else if (wnd == &m_chkUseExplorer)
        OnAddFiles();
    else if (wnd == &m_lvFiles)
        OpenFile();
    else if (wnd == &m_cbDo)
        OnAddCommand();
    else if (wnd == &m_ebReplace)
        OnAddCommand();
    else if (wnd == &m_ebWith)
        OnAddCommand();

}

void CMultiFilezDlg::OnAddCommand()
{
    int nPos = m_lvCommands.GetItemCount();
    CString str, strWith, strReplace, strMsg;
    m_ebReplace.GetWindowText(strReplace);
    m_ebWith.GetWindowText(strWith);
    int nType = m_cbDo.GetCurSel();
    switch (nType) {
    case 0:
        if (strReplace.GetLength() == 0) {
            strMsg = "You must have a string to Replace";
            break;
        }
        str.Format("Replace %s with %s", strReplace, strWith);
        nPos = m_lvCommands.InsertItem(nPos, str, nType);
        str.Format("%s\05%s", strReplace, strWith);
        m_lvCommands.SetItem(nPos, 1, LVIF_TEXT, (LPCTSTR)str, 0, 0, 0, 0);
        m_lvCommands.SetItemData(nPos, nType);
        break;
    case 1:
        if (strWith.GetLength() == 0) {
            strMsg = "You must have a string to add";
            break;
        }
        str.Format("Add %s to the start of every line", strWith);
        nPos = m_lvCommands.InsertItem(nPos, str, nType);
        str.Format("%s", strWith);
        m_lvCommands.SetItem(nPos, 1, LVIF_TEXT, (LPCTSTR)str, 0, 0, 0, 0);
        m_lvCommands.SetItemData(nPos, nType);
        break;
    case 2:
        if (strWith.GetLength() == 0) {
            strMsg = "You must have a string to add";
            break;
        }
        str.Format("Add %s to the end of every line", strWith);
        nPos = m_lvCommands.InsertItem(nPos, str, nType);
        str.Format("%s", strWith);
        m_lvCommands.SetItem(nPos, 1, LVIF_TEXT, (LPCTSTR)str, 0, 0, 0, 0);
        m_lvCommands.SetItemData(nPos, nType);
        break;
    case 3:
        if (strWith.GetLength() == 0) {
            strMsg = "You must have a string to add";
            break;
        }
        str.Format("Add %s to the start of every file", strWith);
        nPos = m_lvCommands.InsertItem(nPos, str, nType);
        str.Format("%s", strWith);
        m_lvCommands.SetItem(nPos, 1, LVIF_TEXT, (LPCTSTR)str, 0, 0, 0, 0);
        m_lvCommands.SetItemData(nPos, nType);
        break;
    case 4:
        if (strWith.GetLength() == 0) {
            strMsg = "You must have a string to add";
            break;
        }
        str.Format("Add %s to the end of every file", strWith);
        nPos = m_lvCommands.InsertItem(nPos, str, nType);
        str.Format("%s", strWith);
        m_lvCommands.SetItem(nPos, 1, LVIF_TEXT, (LPCTSTR)str, 0, 0, 0, 0);
        m_lvCommands.SetItemData(nPos, nType);
        break;
    }

    if (strMsg.GetLength() > 0) {
        MessageBox(strMsg, APP_NAME, MB_OK | MB_ICONSTOP);
        return;
    }
    m_cbDo.SetFocus();
    m_ebWith.SetWindowText("");
    m_ebReplace.SetWindowText("");
}

void CMultiFilezDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
    CMenu menu;
    if (pWnd->m_hWnd == m_lvFiles.m_hWnd) {
        menu.LoadMenu(MAKEINTRESOURCE(IDR_LV_MENU));

        menu.GetSubMenu(0)->SetDefaultItem(IDM_OPEN);

        // Get the selected ListView item
        int nSel = m_lvFiles.GetNextItem(-1, LVNI_SELECTED);
        if (nSel == -1) {
            menu.GetSubMenu(0)->EnableMenuItem(IDM_LV_DELETE, MF_GRAYED | MF_BYCOMMAND);
        }

        if (point == CPoint(-1, -1))
            ::GetCursorPos(&point);
        menu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this, NULL);
    }
    else if (pWnd->m_hWnd == m_lvCommands.m_hWnd) {
        menu.LoadMenu(MAKEINTRESOURCE(IDR_LV_COMMANDS));

        menu.GetSubMenu(0)->SetDefaultItem(IDM_LV_CMDDELETE);

        // Get the selected ListView item
        int nSel = m_lvCommands.GetSelectedCount();
        if (nSel == 1) {
            menu.GetSubMenu(0)->EnableMenuItem(IDM_UP, MF_ENABLED | MF_BYCOMMAND);
            menu.GetSubMenu(0)->EnableMenuItem(IDM_DOWN, MF_ENABLED | MF_BYCOMMAND);
        }
        nSel = m_lvCommands.GetNextItem(-1, LVNI_SELECTED);
        if (nSel == -1) {
            menu.GetSubMenu(0)->EnableMenuItem(IDM_LV_CMDDELETE, MF_GRAYED | MF_BYCOMMAND);
        }
        if (point == CPoint(-1, -1))
            ::GetCursorPos(&point);
        menu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this, NULL);
    }
    else {
        menu.LoadMenu(MAKEINTRESOURCE(IDR_MENU));

        if (point == CPoint(-1, -1))
            ::GetCursorPos(&point);
        menu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this, NULL);
    }
}

void CMultiFilezDlg::OnLvDelete()
{
    DeleteFiles(&m_lvFiles);

    CString strFiles;
    int nTotal = m_lvFiles.GetItemCount();
    if (nTotal == 1)
        strFiles = "1 file selected for editing";
    else
        strFiles.Format("%d files selected for editing", nTotal);
    m_sbMain.SetText(strFiles, 0, 0);
}

void CMultiFilezDlg::OnLvDeleteall()
{
    DeleteAllFiles(&m_lvFiles);
    m_sbMain.SetText("0 files selected for editing", 0, 0);
}

void CMultiFilezDlg::OnLvSelectall()
{
    SelectAllFiles(&m_lvFiles);
}

void CMultiFilezDlg::OnLvCmdDelete()
{
    DeleteFiles(&m_lvCommands);
}

void CMultiFilezDlg::OnLvCmdDeleteall()
{
    DeleteAllFiles(&m_lvCommands);
}

void CMultiFilezDlg::OnLvCmdSelectall()
{
    SelectAllFiles(&m_lvCommands);
}

void CMultiFilezDlg::OnKeydownFiles(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
    if (pLVKeyDow->wVKey == 46) //delete
        DeleteFiles(&m_lvFiles);

    *pResult = 0;
}

void CMultiFilezDlg::OnKeydownCommands(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
    if (pLVKeyDow->wVKey == 46) //delete
        DeleteFiles(&m_lvCommands);

    *pResult = 0;
}

void CMultiFilezDlg::OnAbout()
{
    CAboutDlg dlgAbout;
    //  dlgAbout.m_bRegistered = m_bRegistered;
    dlgAbout.DoModal();
    //  m_bRegistered = dlgAbout.m_bRegistered;
}

void CMultiFilezDlg::OnClickCancel()
{
    theApp->DoWaitCursor(TRUE);
    m_bCancel = TRUE;
    WaitForSingleObject(m_hThread, 5000);

    CString strFiles;
    int nTotal = m_lvFiles.GetItemCount();
    if (nTotal == 1)
        strFiles = "1 file selected for editing";
    else
        strFiles.Format("%d files selected for editing", nTotal);
    m_sbMain.SetText(strFiles, 0, 0);

    m_btnCancel.ShowWindow(SW_HIDE);

    m_btnAddFiles.EnableWindow(TRUE);
    m_btnGo.EnableWindow(TRUE);
    m_lvFiles.EnableWindow(TRUE);
    m_btnAddCriteria.EnableWindow(TRUE);
    m_btnDown.EnableWindow(TRUE);
    m_btnUp.EnableWindow(TRUE);

    m_pcMain.ShowWindow(SW_HIDE);

    m_bCancel = FALSE;
    theApp->DoWaitCursor(FALSE);
}

void CMultiFilezDlg::OnOpen()
{
    OpenFile();
}

void CMultiFilezDlg::OpenFile() {
    int nSel = m_lvFiles.GetNextItem(-1, LVNI_SELECTED);
    if (nSel != -1) {
        CString str;
        str = m_lvFiles.GetItemText(nSel, 0);
        ShellExecute(m_hWnd, "open", str, NULL, NULL, SW_SHOWNORMAL);
    }
}

void CMultiFilezDlg::OnDblclkFiles(NMHDR* pNMHDR, LRESULT* pResult)
{
    OpenFile();

    *pResult = 0;
}


void CMultiFilezDlg::OnDblclkCommands(NMHDR* pNMHDR, LRESULT* pResult)
{
    DeleteFiles(&m_lvCommands);
    *pResult = 0;
}

void CMultiFilezDlg::OnBtnDown()
{
    OnDown();
}

void CMultiFilezDlg::OnBtnUp()
{
    OnUp();
}

void CMultiFilezDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    //  ResizeControls(cx, cy);
}

/*
void CMultiFilezDlg::ResizeControls(int cx, int cy)
{
HDWP hdwp = NULL;

int a_nWidth[3] = { 270, cx - 81, -1 };


if (IsWindow(m_sbMain.m_hWnd)) {
m_sbMain.SetParts(3, a_nWidth);
m_sbMain.GetRect(2, &m_rcPane);
}

CRect rcCtlWin;

hdwp = BeginDeferWindowPos(12);

GetClientRect(&rcCtlWin);
hdwp = DeferWindowPos(hdwp, m_sbMain.m_hWnd, NULL, 0, 0, 0, 0, SWP_NOZORDER);

// Up button
if (m_btnUp.m_hWnd) {
m_btnUp.GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, m_btnUp.m_hWnd, NULL, cx-43, rcCtlWin.top, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

// Down button
if (m_btnDown.m_hWnd) {
m_btnDown.GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, m_btnDown.m_hWnd, NULL, cx-43, cy-77, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

// Go button
if (m_btnGo.m_hWnd) {
m_btnGo.GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, m_btnGo.m_hWnd, NULL, cx-54, cy-47, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

// Report button
if (m_chkReports.m_hWnd) {
m_chkReports.GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, m_chkReports.m_hWnd, NULL, rcCtlWin.left, cy-44, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

// Criteria LV
if (m_lvCommands.m_hWnd) {
m_lvCommands.GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, m_lvCommands.m_hWnd, NULL, 0, 0, cx - 47 - rcCtlWin.left, cy - 54 - rcCtlWin.top, SWP_NOZORDER|SWP_NOMOVE);

// Add Criteria button
if (m_btnAddCriteria.m_hWnd) {
m_btnAddCriteria.GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, m_btnAddCriteria.m_hWnd, NULL, cx-43, rcCtlWin.top, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

// Files LV
if (m_lvFiles.m_hWnd) {
m_lvFiles.GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, m_lvFiles.m_hWnd, NULL, 0, 0, cx - 5 - rcCtlWin.left, rcCtlWin.Height(), SWP_NOZORDER|SWP_NOMOVE);

// Lines!
if (GetDlgItem(IDC_LINE_PERFORM)) {
if (GetDlgItem(IDC_LINE_PERFORM)->m_hWnd) {
GetDlgItem(IDC_LINE_PERFORM)->GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, GetDlgItem(IDC_LINE_PERFORM)->m_hWnd, NULL, 0, 0, cx - 5 - rcCtlWin.left, rcCtlWin.Height(), SWP_NOZORDER|SWP_NOMOVE);
}

if (GetDlgItem(IDC_LINE_CRITERIA)) {
if (GetDlgItem(IDC_LINE_CRITERIA)->m_hWnd) {
GetDlgItem(IDC_LINE_CRITERIA)->GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, GetDlgItem(IDC_LINE_CRITERIA)->m_hWnd, NULL, 0, 0, cx - 5 - rcCtlWin.left, rcCtlWin.Height(), SWP_NOZORDER|SWP_NOMOVE);
}

if (GetDlgItem(IDC_LINE_FILES)) {
if (GetDlgItem(IDC_LINE_FILES)->m_hWnd) {
GetDlgItem(IDC_LINE_FILES)->GetWindowRect(rcCtlWin);
ScreenToClient(rcCtlWin);
}
hdwp = DeferWindowPos(hdwp, GetDlgItem(IDC_LINE_FILES)->m_hWnd, NULL, 0, 0, cx - 5 - rcCtlWin.left, rcCtlWin.Height(), SWP_NOZORDER|SWP_NOMOVE);
}

EndDeferWindowPos(hdwp);

// For what ever reason the progress bar goes here
if (IsWindow(m_pcMain.m_hWnd)) {
m_pcMain.SetWindowPos(NULL, m_rcPane.left, m_rcPane.top, m_rcPane.Width(), m_rcPane.Height(), SWP_NOZORDER);
}

}
*/

BOOL CMultiFilezDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    // Prevents sizing cursor

    switch (nHitTest) {
    case HTSIZE:
    case HTBOTTOM:
    case HTBOTTOMLEFT:
    case HTBOTTOMRIGHT:
    case HTLEFT:
    case HTRIGHT:
    case HTTOP:
    case HTTOPLEFT:
    case HTTOPRIGHT:
        return 0;
        break;
    }
    return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CMultiFilezDlg::OnNcHitTest(CPoint point)
{
    // Prevents sizing

    LRESULT u = CDialog::OnNcHitTest(point);

    switch (u) {
    case HTSIZE:
    case HTTOP:
    case HTTOPLEFT:
    case HTTOPRIGHT:
    case HTLEFT:
    case HTRIGHT:
    case HTBOTTOM:
    case HTBOTTOMLEFT:
    case HTBOTTOMRIGHT:
        u = HTCLIENT;
        break;
    }

    return u;
}

void CMultiFilezDlg::OnInitMenu(CMenu* pMenu)
{
    CDialog::OnInitMenu(pMenu);

    // Get the Files ListView item
    int nSel = m_lvFiles.GetNextItem(-1, LVNI_SELECTED);
    if (nSel == -1) {
        pMenu->EnableMenuItem(IDM_LV_DELETE, MF_GRAYED | MF_BYCOMMAND);
    }
    else {
        pMenu->EnableMenuItem(IDM_LV_DELETE, MF_ENABLED | MF_BYCOMMAND);
    }

    // Get the Criteria ListView item
    nSel = m_lvCommands.GetSelectedCount();
    if (nSel == 1) {
        pMenu->EnableMenuItem(IDM_UP, MF_ENABLED | MF_BYCOMMAND);
        pMenu->EnableMenuItem(IDM_DOWN, MF_ENABLED | MF_BYCOMMAND);
    }
    else {
        pMenu->EnableMenuItem(IDM_UP, MF_GRAYED | MF_BYCOMMAND);
        pMenu->EnableMenuItem(IDM_DOWN, MF_GRAYED | MF_BYCOMMAND);
    }

    nSel = m_lvCommands.GetNextItem(-1, LVNI_SELECTED);
    if (nSel == -1) {
        pMenu->EnableMenuItem(IDM_LV_CMDDELETE, MF_GRAYED | MF_BYCOMMAND);
    }
    else {
        pMenu->EnableMenuItem(IDM_LV_CMDDELETE, MF_ENABLED | MF_BYCOMMAND);
    }
}

/*
void CMultiFilezDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
// Keeps size to 629 x 472 at a minimum
lpMMI->ptMinTrackSize.x=629;
lpMMI->ptMinTrackSize.y=472;

CDialog::OnGetMinMaxInfo(lpMMI);
}
*/

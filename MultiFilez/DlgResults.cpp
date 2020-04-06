// DlgResults.cpp : implementation file
//

#include "stdafx.h"
#include "MultiFilez.h"
#include "DlgResults.h"
#include "MFZ_Defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgResults dialog


CDlgResults::CDlgResults(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgResults::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgResults)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CDlgResults::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgResults)
    DDX_Control(pDX, IDC_RESULTS, m_lvStatus);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgResults, CDialog)
    //{{AFX_MSG_MAP(CDlgResults)
    ON_NOTIFY(NM_DBLCLK, IDC_RESULTS, OnDblclkResults)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgResults message handlers

BOOL CDlgResults::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_ilIcons.Create(IDB_LV_STATUS, 16, 1, RGB(255, 0, 255));
    m_lvStatus.SetImageList(&m_ilIcons, LVSIL_SMALL);
    m_lvStatus.SetExtendedStyle(m_lvStatus.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

    // Insert column
    LV_COLUMN lvCol;
    CRect rc;

    memset(&lvCol, 0, sizeof(lvCol));
    lvCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
    lvCol.fmt = LVCFMT_LEFT;
    m_lvStatus.GetClientRect(&rc);
    lvCol.cx = rc.Width() - 75;
    lvCol.pszText = "File Name";
    lvCol.cchTextMax = sizeof(lvCol.pszText);
    lvCol.iSubItem = 0;
    m_lvStatus.InsertColumn(0, &lvCol);

    memset(&lvCol, 0, sizeof(lvCol));
    lvCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
    lvCol.fmt = LVCFMT_LEFT;
    lvCol.cx = 75;
    lvCol.pszText = "Status";
    lvCol.cchTextMax = sizeof(lvCol.pszText);
    lvCol.iSubItem = 1;
    m_lvStatus.InsertColumn(1, &lvCol);

    UpdateWindow();

    int nTot = ma_str.GetSize();
    for (int n = 0; n < nTot; n++) {
        int nStatus = ma_n[n];
        m_lvStatus.InsertItem(n, ma_str[n], nStatus);
        switch (nStatus) {
        case MFZ_UNCHANGED:
            m_lvStatus.SetItemText(n, 1, "Unchanged");
            break;
        case MFZ_UPDATED:
            m_lvStatus.SetItemText(n, 1, "Updated");
            break;
        case MFZ_NOTFOUND:
            m_lvStatus.SetItemText(n, 1, "Not found");
            break;
        case MFZ_READONLY:
            m_lvStatus.SetItemText(n, 1, "Read only");
            break;
        }
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgResults::OnDblclkResults(NMHDR* pNMHDR, LRESULT* pResult)
{
    int nSel = m_lvStatus.GetNextItem(-1, LVNI_SELECTED);
    if (nSel != -1) {
        CString str;
        str = m_lvStatus.GetItemText(nSel, 0);
        ShellExecute(m_hWnd, "open", str, NULL, NULL, SW_SHOWNORMAL);
    }
    *pResult = 0;
}

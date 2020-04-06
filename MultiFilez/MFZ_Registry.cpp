#include "stdafx.h"
#include "MultiFilezDlg.h"

void CMultiFilezDlg::LoadRegistry()
{
    // Set all Defaults here
    m_strWorkingDir = "C:\\";
    m_nCurDo = 0;
    m_bUseExplorer = FALSE;
    m_strFilter = "*.htm; *.html";
    m_bIncludeSubs = FALSE;
    m_strDirList = "";
    m_strFilterList = "*.htm; *.html\05*.*\05*.aspx\05*.txt\05*.sys\05*.ini\05";
    m_bReport = TRUE;

    // Get Registry stuff here
    CRegistryKey hKey;
    LONG l;
    int nRet, nTemp;
    CString strTemp;

    l = hKey.Open(HKEY_CURRENT_USER, APP_REG_KEY);

    if (l == ERROR_SUCCESS) {
        // Working Dir
        nRet = hKey.QueryValue(strTemp, "WorkingDir");
        if (nRet == ERROR_SUCCESS)
            m_strWorkingDir = strTemp;

        // Current Do
        nRet = hKey.QueryValue(nTemp, "CurrentDo");
        if (nRet == ERROR_SUCCESS)
            m_nCurDo = nTemp;

        // Use Explorer
        nRet = hKey.QueryValue(nTemp, "UseExplorer");
        if (nRet == ERROR_SUCCESS)
            m_bUseExplorer = (BOOL)nTemp;

        // Current filter
        nRet = hKey.QueryValue(strTemp, "CurrentFilter");
        if (nRet == ERROR_SUCCESS)
            m_strFilter = strTemp;

        // Include subdirectories
        nRet = hKey.QueryValue(nTemp, "IncludeSubdirectories");
        if (nRet == ERROR_SUCCESS)
            m_bIncludeSubs = (BOOL)nTemp;

        // Working Dir List
        nRet = hKey.QueryValue(strTemp, "WorkingDirList");
        if (nRet == ERROR_SUCCESS) {
            m_strDirList = strTemp;
        }

        // Filter List
        nRet = hKey.QueryValue(strTemp, "FilterList");
        if (nRet == ERROR_SUCCESS) {
            m_strFilterList = strTemp;
        }

        // Show Reports
        nRet = hKey.QueryValue(nTemp, "ShowReport");
        if (nRet == ERROR_SUCCESS)
            m_bReport = (BOOL)nTemp;

        /*    CString strKeyName;
            strKeyName = "RegisterMe!";
            char sz[250];
            memset(sz, 0, sizeof(sz));
            encodeBase64(sz, (LPSTR)(LPCTSTR)strKeyName);
            strKeyName = sz;
            nRet = hKey.QueryValue(strTemp, strKeyName);
            if (nRet == ERROR_SUCCESS) {
              memset(sz, 0, sizeof(sz));
              decodeBase64(sz, (LPSTR)(LPCTSTR)strTemp);
              strTemp = sz;
              if (strTemp == "Fluffinutter")
                m_bRegistered = TRUE;
            }
            */
    }

    hKey.Close();
}

void CMultiFilezDlg::SaveRegistry()
{
    CRegistryKey hKey;
    LONG l;
    int nTemp;
    CString strTemp;

    l = hKey.Create(HKEY_CURRENT_USER, APP_REG_KEY);

    if (l == ERROR_SUCCESS) {
        // Working Dir
        m_cbWhere.GetWindowText(m_strWorkingDir);
        hKey.SetValue(m_strWorkingDir, "WorkingDir");

        // Current Do
        nTemp = m_cbDo.GetCurSel();
        hKey.SetValue(nTemp, "CurrentDo");

        // Use Explorer
        nTemp = m_chkUseExplorer.GetCheck();
        hKey.SetValue(nTemp, "UseExplorer");

        // Current Filter
        m_cbFilter.GetWindowText(m_strFilter);
        hKey.SetValue(m_strFilter, "CurrentFilter");

        // Include subs
        nTemp = m_chkIncludeSubs.GetCheck();
        hKey.SetValue(nTemp, "IncludeSubdirectories");

        // Working Dir ComboBox
        strTemp.Empty();
        for (int n = 0; n < m_cbWhere.GetCount(); n++) {
            CString str;
            m_cbWhere.GetLBText(n, str);
            strTemp += str;
            strTemp += "\05";
        }
        hKey.SetValue(strTemp, "WorkingDirList");

        // Filter ComboBox
        strTemp.Empty();
        for (int n = 0; n < m_cbFilter.GetCount(); n++) {
            CString str;
            m_cbFilter.GetLBText(n, str);
            strTemp += str;
            strTemp += "\05";
        }
        hKey.SetValue(strTemp, "FilterList");

        // Show Report
        nTemp = m_chkReports.GetCheck();
        hKey.SetValue(nTemp, "ShowReport");
    }

    hKey.Close();

}

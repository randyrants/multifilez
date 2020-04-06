#include "stdafx.h"
#include "MultiFilezDlg.h"

DWORD WINAPI AddFiles(LPVOID lpVoid) {
    CMultiFilezDlg* pDlg = (CMultiFilezDlg*)lpVoid;

    { // ************ Required to assure that the CString is deleted on the exit of the loop ****************

        pDlg->m_btnCancel.ShowWindow(SW_SHOW);
        int nCount = 0, nOffset = pDlg->m_lvFiles.GetItemCount();
        BOOL bFind;
        CFileFind ffFind;

        // set up all of the filters
        CStringArray a_strFilters;
        CString strFilter = pDlg->m_strFilter;
        strFilter.Replace(",", ";");
        strFilter.Replace("; ", ";");
        if (strFilter.Right(1) != ";")
            strFilter += ";";
        parseStr(';', strFilter, a_strFilters);

        CString strSearchDir = pDlg->m_strWorkingDir;
        if (strSearchDir.Right(1) != "\\")
            strSearchDir += "\\";

        CStringArray a_strSubdirectories;

        // Build ALL of the subdirectories
        a_strSubdirectories.Add(strSearchDir);

        CString strFiles;
        strFiles = "Searching for subdirectories to use...";
        pDlg->m_sbMain.SetText(strFiles, 0, 0);
        strFiles = "0 changes made in 0 files";
        pDlg->m_sbMain.SetText(strFiles, 1, 0);

        //ffFind.FindFile("C:\\config.sys");
        if (pDlg->m_bIncludeSubs) {
            for (int n = 0; n < a_strSubdirectories.GetSize(); n++) {
                if (pDlg->m_bCancel)
                    goto Exit;
                CString strSum = a_strSubdirectories[n] + "\\*.*";
                bFind = ffFind.FindFile(strSum);

                while (bFind) {
                    if (pDlg->m_bCancel)
                        goto Exit;
                    bFind = ffFind.FindNextFile();
                    if (ffFind.IsDirectory() && !ffFind.IsDots()) {
                        CString strTemp = ffFind.GetFilePath() + "\\";
                        a_strSubdirectories.Add(strTemp);
                    }
                }

                ffFind.Close();
            }
        }

        if (pDlg->m_bCancel)
            goto Exit;

        int nTotal = a_strSubdirectories.GetSize() - 1;
        if (nTotal == 1)
            strFiles = "1 subdirectory will be searched";
        else
            strFiles.Format("%d subdirectories will be searched", nTotal);
        pDlg->m_sbMain.SetText(strFiles, 0, 0);

        // Go thru subdivisions if you're supposed to.
        int nExist = pDlg->m_lvFiles.GetItemCount();
        for (int n = 0; n < a_strSubdirectories.GetSize(); n++) {
            for (int nFilters = 0; nFilters < a_strFilters.GetSize(); nFilters++) {
                if (pDlg->m_bCancel)
                    goto Exit;

                strSearchDir = a_strSubdirectories[n];

                strSearchDir += a_strFilters[nFilters];

                bFind = ffFind.FindFile(strSearchDir);

                while (bFind) {
                    /*          if (!pDlg->m_bRegistered) {
                                if ((nExist + nCount) == 15) {
                                  n = a_strSubdirectories.GetSize();
                                  nFilters = a_strFilters.GetSize();
                                  break;
                                }
                              }
                     */       if (pDlg->m_bCancel)
    goto Exit;
                     bFind = ffFind.FindNextFile();
                     if (!ffFind.IsDirectory()) {
                         pDlg->AddToListView(ffFind.GetFilePath(), nCount + nOffset);
                         nCount++;
                     }
                }
                ffFind.Close();
            }
        }

        int nTotalFiles = pDlg->m_lvFiles.GetItemCount();
        if (nTotalFiles == 1) {
            if (nTotal == 1) {
                strFiles = "1 file selected for editing (1 subdirectory)";
            }
            else {
                strFiles.Format("1 file selected for editing (%d subdirectories)", nTotal);
            }
        }
        else {
            if (nTotal == 1) {
                strFiles.Format("%d files selected for editing (1 subdirectory)", nTotalFiles);
            }
            else {
                strFiles.Format("%d files selected for editing (%d subdirectories)", nTotalFiles, nTotal);
            }
        }
        pDlg->m_sbMain.SetText(strFiles, 0, 0);

        // here for completed search - won't fire on cancel
        pDlg->m_btnCancel.ShowWindow(SW_HIDE);
        pDlg->m_btnAddFiles.EnableWindow(TRUE);
        pDlg->m_btnGo.EnableWindow(TRUE);
        pDlg->m_lvFiles.EnableWindow(TRUE);
        pDlg->m_btnAddCriteria.EnableWindow(TRUE);
        pDlg->m_btnDown.EnableWindow(TRUE);
        pDlg->m_btnUp.EnableWindow(TRUE);
    }

Exit:
    ExitThread(0);
    return 0;
}

void CMultiFilezDlg::OnAddFiles()
{
    // Shareware Trap
  /*  if (!m_bRegistered) {
      if (m_lvFiles.GetItemCount() >= 15) {
        MessageBox("The Shareware Version can only edit 15 files at a time!\n\nRight click and select About for more information!", APP_NAME, MB_ICONSTOP);
        return;
      }
    }
  */	m_cbFilter.GetWindowText(m_strFilter);
  m_cbWhere.GetWindowText(m_strWorkingDir);
  m_bIncludeSubs = m_chkIncludeSubs.GetCheck();

  UpdateComboBoxes();

  m_btnAddFiles.EnableWindow(FALSE);
  m_btnGo.EnableWindow(FALSE);
  m_lvFiles.EnableWindow(FALSE);
  m_btnAddCriteria.EnableWindow(FALSE);
  m_btnDown.EnableWindow(FALSE);
  m_btnUp.EnableWindow(FALSE);

  m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AddFiles, (LPVOID)this, 0, &m_dwID);
}

void CMultiFilezDlg::OnGo()
{
    // Shareware Trap
    if (m_lvCommands.GetItemCount() <= 0) {
        MessageBox("You must have at least 1 edit criteria defined!", APP_NAME, MB_ICONSTOP);
        m_cbDo.SetFocus();
        return;
    }

    m_bGo = TRUE;

    theApp->DoWaitCursor(TRUE);

    m_bReport = m_chkReports.GetCheck();

    m_cbFilter.GetWindowText(m_strFilter);
    m_cbWhere.GetWindowText(m_strWorkingDir);
    m_bIncludeSubs = m_chkIncludeSubs.GetCheck();

    UpdateComboBoxes();

    m_btnAddFiles.EnableWindow(FALSE);
    m_btnGo.EnableWindow(FALSE);
    m_lvFiles.EnableWindow(FALSE);
    m_btnAddCriteria.EnableWindow(FALSE);
    m_btnDown.EnableWindow(FALSE);
    m_btnUp.EnableWindow(FALSE);

    int nTot = m_lvFiles.GetItemCount();
    m_pcMain.ShowWindow(SW_SHOW);
    m_pcMain.SetRange32(0, nTot);
    m_pcMain.SetPos(0);

    m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GoFiles, (LPVOID)this, 0, &m_dwID);
}

DWORD WINAPI GoFiles(LPVOID lpVoid) {
    CMultiFilezDlg* pDlg = (CMultiFilezDlg*)lpVoid;

    { // ************ Required to assure that the CString is deleted on the exit of the loop ****************
        int nCount = 0;
        CStringArray a_strCmd;

        pDlg->m_sbMain.SetText("Editing files...", 1, 0);
        for (int n = 0; n < pDlg->m_lvCommands.GetItemCount(); n++) {
            CString strWith, strReplace;
            int nType;
            strWith = pDlg->m_lvCommands.GetItemText(n, 1);
            nType = pDlg->m_lvCommands.GetItemData(n);
            if (nType == 0) {
                CStringArray a_str;
                parseStr('\05', strWith, a_str);
                strReplace = a_str[0];
                if (a_str.GetSize() < 2)
                    strWith = ""; //blank replacement
                else
                    strWith = a_str[1];
            }
            CString str;
            str.Format("%d\05%s\05%s\05", nType, strWith, strReplace);
            a_strCmd.Add(str);
        }

        CStringArray a_strFiles;
        CUIntArray a_nStatus;
        int nFiles = pDlg->m_lvFiles.GetItemCount();
        for (int n = 0; n < nFiles; n++) {
            CString strFile;
            strFile = pDlg->m_lvFiles.GetItemText(n, 0);
            a_strFiles.Add(strFile);
        }

        CStringArray a_str;
        for (int n = 0; n < a_strCmd.GetSize(); n++) {
            CString strCmd = a_strCmd[n];
            int i = 0, nTot = a_strFiles.GetSize();

            a_str.RemoveAll();

            parseStr('\05', strCmd, a_str);
            int nType = atoi(a_str[0]);
            switch (nType) {
            case 0:
                for (i = 0; i < nTot; i++) {
                    int n = FindAndReplace(a_strFiles[i], a_str[1], a_str[2]);
                    if (n <= 1)
                        nCount += n;
                    a_nStatus.Add(n);
                    pDlg->m_pcMain.SetPos(i);
                }
                break;
            case 1:
                for (i = 0; i < nTot; i++) {
                    int n = AddToLine(a_strFiles[i], a_str[1], TRUE);
                    if (n <= 1)
                        nCount += n;
                    a_nStatus.Add(n);
                    pDlg->m_pcMain.SetPos(i);
                }
                break;
            case 2:
                for (i = 0; i < nTot; i++) {
                    int n = AddToLine(a_strFiles[i], a_str[1], FALSE);
                    if (n <= 1)
                        nCount += n;
                    a_nStatus.Add(n);
                    pDlg->m_pcMain.SetPos(i);
                }
                break;
            case 3:
                for (i = 0; i < nTot; i++) {
                    int n = AddToFile(a_strFiles[i], a_str[1], TRUE);
                    if (n <= 1)
                        nCount += n;
                    a_nStatus.Add(n);
                    pDlg->m_pcMain.SetPos(i);
                }
                break;
            case 4:
                for (i = 0; i < nTot; i++) {
                    int n = AddToFile(a_strFiles[i], a_str[1], FALSE);
                    if (n <= 1)
                        nCount += n;
                    a_nStatus.Add(n);
                    pDlg->m_pcMain.SetPos(i);
                }
                break;
            }
        }

        // here for completed search
        pDlg->m_btnAddFiles.EnableWindow(TRUE);
        pDlg->m_btnGo.EnableWindow(TRUE);
        pDlg->m_lvFiles.EnableWindow(TRUE);
        pDlg->m_btnAddCriteria.EnableWindow(TRUE);
        pDlg->m_btnDown.EnableWindow(TRUE);
        pDlg->m_btnUp.EnableWindow(TRUE);

        CString str;
        if (nCount == 1) {
            if (nFiles == 1) {
                str = "1 change made in 1 file";
            }
            else {
                str.Format("1 change made in %d files", nFiles);
            }
        }
        else {
            if (nFiles == 1) {
                str.Format("%d changes made in 1 file", nCount);
            }
            else {
                str.Format("%d changes made in %d files", nCount, nFiles);
            }
        }
        pDlg->m_sbMain.SetText(str, 1, 0);
        pDlg->m_pcMain.SetFocus();
        pDlg->m_pcMain.ShowWindow(SW_HIDE);

        if (pDlg->m_bReport) {
            pDlg->ma_strFiles.Copy(a_strFiles);
            pDlg->ma_nStatus.Copy(a_nStatus);
            pDlg->PostMessage(MFZ_POSTREPORTS, 0, 0L);
        }

        pDlg->theApp->DoWaitCursor(FALSE);
        pDlg->m_bGo = FALSE;

    }
    return 0;
}

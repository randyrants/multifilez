#include "stdafx.h"
#include "MultiFilezDlg.h"


int FindAndReplace(CString strFile, CString strWith, CString strReplace) {
    CFile cFile;

    LPSTR sz;
    int nFileSize;
    int nSuccess = 0;

    try {
        CFileException e;
        if (!cFile.Open(strFile, CFile::shareExclusive | CFile::modeReadWrite, &e)) {
            switch (e.m_cause) {
            case CFileException::fileNotFound:
                return MFZ_NOTFOUND; //2
                break;
            case (5):
                return MFZ_READONLY; //5
                break;
            }
        }

        nFileSize = (int)cFile.GetLength();

        sz = (LPSTR)LocalAlloc(LPTR, nFileSize + 2);
        memset(sz, 0, sizeof(sz));

        cFile.Read(sz, nFileSize);

        CString str;
        str = sz;
        int nChanges = str.Replace(strReplace, strWith);

        if (nChanges > 0) {
            cFile.SetLength(0);
            cFile.Write(str, str.GetLength());
            nSuccess = 1;
        }

        cFile.Close();
    }
    catch (CFileException* cFileEx) {
        CString str;
        str.Format("An error has occurred while attempting file access on: %s", strFile);
        MessageBox(NULL, str, APP_NAME, MB_ICONSTOP);
        cFileEx->Delete();
    }
    return nSuccess;
}

int AddToLine(CString strFile, CString strWith, BOOL bStart) {
    CStdioFile cFile;

    int nSuccess = 0;

    try {
        if (!cFile.Open(strFile, CFile::shareExclusive | CFile::modeReadWrite | CFile::typeText)) {
            CString str;
            str.Format("An error has occurred while attempting file access on: %s", strFile);
            MessageBox(NULL, str, APP_NAME, MB_ICONSTOP);
            return nSuccess;
        }

        CString strLine;
        CStringArray a_str;

        while (cFile.ReadString(strLine)) {
            if (bStart) {
                strLine = strWith + strLine;
            }
            else {
                strLine += strWith;
            }
            strLine += "\n"; //Required for the new line!
            a_str.Add(strLine);
        }

        int nLines = a_str.GetSize();
        if (nLines > 0) {
            cFile.SetLength(0);
            nSuccess = 1;
        }
        for (int n = 0; n < nLines; n++) {
            cFile.WriteString(a_str[n]);
        }

        cFile.Close();
    }
    catch (CFileException* cFileEx) {
        CString str;
        str.Format("An error has occurred while attempting file access on: %s", strFile);
        MessageBox(NULL, str, APP_NAME, MB_ICONSTOP);
        cFileEx->Delete();
    }
    return nSuccess;
}

int AddToFile(CString strFile, CString strWith, BOOL bStart) {
    CFile cFile;

    LPSTR sz;
    int nFileSize;
    int nSuccess = 0;

    try {
        if (!cFile.Open(strFile, CFile::shareExclusive | CFile::modeReadWrite)) {
            CString str;
            str.Format("An error has occurred while attempting file access on: %s", strFile);
            MessageBox(NULL, str, APP_NAME, MB_ICONSTOP);
            return nSuccess;
        }

        nFileSize = (int)cFile.GetLength();

        sz = (LPSTR)LocalAlloc(LPTR, nFileSize + 2);
        memset(sz, 0, sizeof(sz));

        cFile.Read(sz, nFileSize);

        CString str;
        str = sz;
        if (bStart) {
            strWith += "\r\n"; //required for the new line!
            str = strWith + str;
        }
        else {
            strWith = "\r\n" + strWith; //required for the new line!
            str += strWith;
        }

        cFile.SetLength(0);
        cFile.Write(str, str.GetLength());
        nSuccess = 1;

        cFile.Close();
    }
    catch (CFileException* cFileEx) {
        CString str;
        str.Format("An error has occurred while attempting file access on: %s", strFile);
        MessageBox(NULL, str, APP_NAME, MB_ICONSTOP);
        cFileEx->Delete();
    }
    return nSuccess;
}


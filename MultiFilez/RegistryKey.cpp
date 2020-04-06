#include "StdAfx.h"
#include "registrykey.h"

//////////////////////////////////////////////////////////////////////////////

CRegistryKey::CRegistryKey()
{
    Clear();
}

CRegistryKey::~CRegistryKey()
{
    if ((m_bOpen) || (m_hKey)) {
        TRACE("WARNING: You still have a Key open!");
    }
    Clear();
}

//////////////////////////////////////////////////////////////////////////////

void CRegistryKey::Clear()
{
    m_hKey = NULL;
    m_bOpen = FALSE;
}

//////////////////////////////////////////////////////////////////////////////

LONG CRegistryKey::Create(HKEY hKeyParent, LPCTSTR lpszKeyName, LPTSTR lpszClass/* = REG_NONE*/, DWORD dwOptions/* = REG_OPTION_NON_VOLATILE*/, REGSAM samDesired/* = KEY_ALL_ACCESS*/, LPSECURITY_ATTRIBUTES lpSecAttr /*= NULL*/, LPDWORD lpdwDisposition /*= NULL*/)
{
    if (m_bOpen) {
        TRACE("WARNING: You are creating a new key while one is open!");
    }
    LONG lResult = ::RegCreateKeyEx(hKeyParent, lpszKeyName, 0, lpszClass, dwOptions, samDesired, lpSecAttr, &m_hKey, lpdwDisposition);
    if (lResult == ERROR_SUCCESS)
        m_bOpen = TRUE;
    else
        m_bOpen = FALSE;
    return lResult;
}

LONG CRegistryKey::Open(HKEY hKeyParent, LPCTSTR lpszKeyName, REGSAM samDesired/* = KEY_ALL_ACCESS*/)
{
    if (m_bOpen) {
        TRACE("WARNING: You are creating a new key while one is open!");
    }
    LONG lResult = ::RegOpenKeyEx(hKeyParent, lpszKeyName, 0, samDesired, &m_hKey);
    if (lResult == ERROR_SUCCESS)
        m_bOpen = TRUE;
    else
        m_bOpen = FALSE;
    return lResult;
}

LONG CRegistryKey::Close()
{
    if (!m_bOpen) {
        TRACE("WARNING: You are closing a key while there isn't one open!");
    }
    LONG lResult = ::RegCloseKey(m_hKey);
    m_hKey = NULL;
    if (lResult == ERROR_SUCCESS)
        m_bOpen = FALSE;
    else
        m_bOpen = TRUE;
    return lResult;
}

HKEY CRegistryKey::Detach()
{
    HKEY hKeyTemp = m_hKey;
    m_hKey = NULL;
    return hKeyTemp;
}

void CRegistryKey::Attach(HKEY hKey)
{
    m_hKey = hKey;
}

LONG CRegistryKey::DeleteSubKey(LPCTSTR lpszSubKey)
{
    if (!m_bOpen) {
        TRACE("WARNING: You are deleting a subkey while m_hKey isn't open!");
    }
    LONG lResult = ::RegDeleteKey(m_hKey, lpszSubKey);
    return lResult;
}

LONG CRegistryKey::DeleteSubKey(HKEY hKeyParent, LPCTSTR lpszSubKey)
{
    LONG lResult = ::RegDeleteKey(hKeyParent, lpszSubKey);
    return lResult;
}

LONG CRegistryKey::DeleteValue(LPCTSTR lpszValue)
{
    if (!m_bOpen) {
        TRACE("WARNING: You are deleting a value while m_hKey isn't open!");
    }
    LONG lResult = ::RegDeleteValue(m_hKey, lpszValue);
    return lResult;
}

LONG CRegistryKey::DeleteValue(HKEY hKeyParent, LPCTSTR lpszValue)
{
    LONG lResult = ::RegDeleteValue(hKeyParent, lpszValue);
    return lResult;
}

LONG CRegistryKey::SetValue(DWORD dwValue, LPCTSTR lpszValueName)
{
    if (!m_bOpen) {
        TRACE("WARNING: You are setting a value while m_hKey isn't open!");
    }
    DWORD dw;
    dw = dwValue;
    LONG lResult = ::RegSetValueEx(m_hKey, lpszValueName, 0, REG_DWORD, (PBYTE)&dw, sizeof(dw));
    return lResult;
}

LONG CRegistryKey::SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
    if (!m_bOpen) {
        TRACE("WARNING: You are setting a value while m_hKey isn't open!");
    }
    LONG lResult = ::RegSetValueEx(m_hKey, lpszValueName, 0, REG_SZ, (PBYTE)lpszValue, (strlen(lpszValue) + 1));
    return lResult;
}

LONG CRegistryKey::SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
    LONG lResult = ::RegSetValueEx(hKeyParent, lpszValueName, 0, REG_SZ, (PBYTE)lpszValue, (strlen(lpszValue) + 1));
    return lResult;
}

LONG CRegistryKey::SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
    if (!m_bOpen) {
        TRACE("WARNING: You are setting a sub key value while m_hKey isn't open!");
    }
    HKEY hKeyNew;
    LONG lResult = ::RegOpenKeyEx(m_hKey, lpszKeyName, 0, KEY_ALL_ACCESS, &hKeyNew);
    if (lResult != ERROR_SUCCESS) {
        lResult = ::RegCreateKeyEx(m_hKey, lpszKeyName, 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyNew, NULL);
    }

    if (lResult != ERROR_SUCCESS) {
        TRACE("WARNING: Attempt to create and/or open subkey has failed!");
        return lResult;
    }
    lResult = SetValue(hKeyNew, lpszKeyName, lpszValue, lpszValueName);
    ::RegCloseKey(hKeyNew);
    return lResult;
}

LONG CRegistryKey::QueryValue(DWORD& dwValue, LPCTSTR lpszValueName, DWORD dwSize/*=-1*/)
{
    if (!m_bOpen) {
        TRACE("WARNING: You are query a value while m_hKey isn't open!");
    }
    DWORD cbData;
    if (dwSize == -1)
        cbData = sizeof(dwValue);
    else
        cbData = dwSize;
    DWORD nType = REG_DWORD;
    LONG lResult = ::RegQueryValueEx(m_hKey, lpszValueName, NULL, NULL, (PBYTE)&dwValue, &cbData);
    return lResult;
}

LONG CRegistryKey::QueryValue(int& nValue, LPCTSTR lpszValueName)
{
    if (!m_bOpen) {
        TRACE("WARNING: You are query a value while m_hKey isn't open!");
    }
    DWORD dwValue;
    dwValue = nValue;
    LONG lResult = QueryValue(dwValue, lpszValueName);
    nValue = dwValue;
    return lResult;
}

LONG CRegistryKey::QueryValue(LPTSTR szValue, LPCTSTR lpszValueName, DWORD* pdwCount)
{
    if (!m_bOpen) {
        TRACE("WARNING: You are query a value while m_hKey isn't open!");
    }
    DWORD nType = REG_SZ;
    LONG lResult = ::RegQueryValueEx(m_hKey, lpszValueName, NULL, &nType, (PBYTE)&szValue, pdwCount);
    return lResult;
}

LONG CRegistryKey::QueryValue(CString& strValue, LPCTSTR lpszValueName, int nMaxChar/*=256*/)
{
    if (!m_bOpen) {
        TRACE("WARNING: You are query a value while m_hKey isn't open!");
    }
    LPSTR lpszTempString;
    lpszTempString = (LPSTR)LocalAlloc(LPTR, nMaxChar + 2);

    memset(lpszTempString, 0, nMaxChar + 2);
    DWORD cbData = nMaxChar;
    DWORD nType = REG_SZ;
    LONG lResult = ::RegQueryValueEx(m_hKey, lpszValueName, NULL, &nType, (PBYTE)lpszTempString, &cbData);
    if (lResult == ERROR_SUCCESS)
        strValue = lpszTempString;
    else
        strValue.Empty();
    LocalFree(lpszTempString);
    return lResult;
}

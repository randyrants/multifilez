#ifndef REGISTRYKEY_H
#define REGISTRYKEY_H

class CRegistryKey : public CObject
{
public:
    CRegistryKey();
    ~CRegistryKey();

public:
    HKEY m_hKey;

    // Operations
public:
    LONG SetValue(DWORD dwValue, LPCTSTR lpszValueName);
    LONG QueryValue(int& nValue, LPCTSTR lpszValueName);
    LONG QueryValue(DWORD& dwValue, LPCTSTR lpszValueName, DWORD dwSize = -1);
    LONG QueryValue(LPTSTR szValue, LPCTSTR lpszValueName, DWORD* pdwCount);
    LONG QueryValue(CString& strValue, LPCTSTR lpszValueName, int nMaxChar = 256);
    LONG SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName);

    LONG SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);
    static LONG WINAPI SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName,
        LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);

    LONG Create(HKEY hKeyParent, LPCTSTR lpszKeyName,
        LPTSTR lpszClass = REG_NONE, DWORD dwOptions = REG_OPTION_NON_VOLATILE,
        REGSAM samDesired = KEY_ALL_ACCESS,
        LPSECURITY_ATTRIBUTES lpSecAttr = NULL,
        LPDWORD lpdwDisposition = NULL);
    LONG Open(HKEY hKeyParent, LPCTSTR lpszKeyName,
        REGSAM samDesired = KEY_ALL_ACCESS);

    LONG Close();
    HKEY Detach();
    void Attach(HKEY hKey);
    LONG DeleteSubKey(LPCTSTR lpszSubKey);
    static LONG WINAPI DeleteSubKey(HKEY hKeyParent, LPCTSTR lpszSubKey);
    LONG DeleteValue(LPCTSTR lpszValue);
    static LONG WINAPI DeleteValue(HKEY hKeyParent, LPCTSTR lpszValue);

private:
    void Clear();
    BOOL m_bOpen;
};

#endif

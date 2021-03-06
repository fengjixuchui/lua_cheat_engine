#pragma once
extern lua_State* L;
extern HWND g_hWnd;
extern DWORD g_dwProcessId;
extern HANDLE g_hProcess;

extern HMODULE aa_engine;
typedef BOOL(FAR WINAPI *AutoAssemble)(HANDLE, char*, int);
typedef DWORD(FAR WINAPI *GetAddress)(HANDLE, char*);
typedef char *(FAR WINAPI *GetVer)();

extern AutoAssemble autoAssemble;
extern GetAddress getAddress;
extern GetVer getVer;





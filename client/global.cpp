#include "stdafx.h"
#include "global.h"

lua_State* L = NULL;
HWND g_hWnd = NULL;
DWORD g_dwProcessId = NULL;
HANDLE g_hProcess = NULL;
HMODULE aa_engine = NULL;

AutoAssemble autoAssemble;
GetAddress getAddress;
GetVer getVer;
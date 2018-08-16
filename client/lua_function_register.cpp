#include "stdafx.h"
#include "lua_function_register.h"
#include "global.h"
#include "base_functions.h"
wchar_t temp_str[255] = { NULL };


int findWindow(lua_State* L)
{
	HWND hWnd;
	wchar_t lpszClass[100] = { NULL };
	wchar_t lpszWindow[100] = { NULL };
	wsprintf(lpszClass, L"%hs", lua_tostring(L, 1));
	wsprintf(lpszWindow, L"%hs", lua_tostring(L, 2));
	hWnd = FindWindow(lpszClass, lpszWindow);
	if (hWnd == NULL)
	{
		lua_pushboolean(L, 0);
	}
	else {
		lua_pushinteger(L, (int)hWnd);
	}
	return 1;
}

int lua_operProcess(lua_State* L)
{
	lua_pushboolean(L, openProcess(lua_tostring(L, 1)));
	return 1;
}

int getOpenedProcessID(lua_State* L)
{
	lua_pushinteger(L,g_dwProcessId);
	return 1;
}

INT lua_readByte(lua_State* L)
{
	printf("123456");
	lua_pushinteger(L,readByte((DWORD)lua_tointeger(L, 1)));
	return 1;
}

INT lua_readShort(lua_State* L)
{
	lua_pushinteger(L, readShort((DWORD)lua_tointeger(L, 1)));
	return 1;
}

INT lua_readInteger(lua_State* L)
{
	lua_pushinteger(L, readInteger((DWORD)lua_tointeger(L, 1)));
	return 1;
}

INT lua_readFloat(lua_State* L)
{
	lua_pushnumber(L, readFloat((DWORD)lua_tointeger(L, 1)));
	return 1;
}

INT lua_readDouble(lua_State* L)
{
	lua_pushnumber(L, readDouble((DWORD)lua_tointeger(L, 1)));
	return 1;
}

INT lua_readString(lua_State* L)
{
	lua_pushstring(L, readString((DWORD)lua_tointeger(L, 1), (INT)lua_tointeger(L, 2)));
	return 1;
}


int lua_writeByte(lua_State* L)
{
	lua_pushboolean(L,writeByte((INT)lua_tointeger(L,1), (BYTE)lua_tointeger(L, 2)));
	return 1;
}

int lua_writeShort(lua_State* L)
{
	lua_pushboolean(L, writeShort((INT)lua_tointeger(L, 1), (short)lua_tointeger(L, 2)));
	return 1;
}

int lua_writeInteger(lua_State* L)
{
	lua_pushboolean(L, writeInteger((INT)lua_tointeger(L, 1), (int)lua_tointeger(L, 2)));
	return 1;
}

int lua_writeFloat(lua_State* L)
{
	lua_pushboolean(L, writeFloat((INT)lua_tointeger(L, 1), (float)lua_tointeger(L, 2)));
	return 1;
}

int lua_writeDouble(lua_State* L)
{
	lua_pushboolean(L, writeDouble((INT)lua_tointeger(L, 1), (double)lua_tointeger(L, 2)));
	return 1;
}

int lua_autoAssemble(lua_State* L)
{
	lua_pushboolean(L, autoAssemble(g_hProcess, (char *)lua_tostring(L, 1),1));
	return 1;
}

int lua_getAddress(lua_State* L)
{
	lua_pushinteger(L, (int)getAddress(g_hProcess, (char *)lua_tostring(L, 1)));
	return 1;
}

int lua_sleep(lua_State* L)
{
	Sleep((int)lua_tointeger(L, 1));
	return 0;
}

void lua_function_register()
{
	lua_register(L, "findWindow", findWindow); // 
	lua_register(L, "operProcess", lua_operProcess); // 
	lua_register(L, "getOpenedProcessID", getOpenedProcessID); // 
	lua_register(L, "readByte", lua_readByte); // 
	lua_register(L, "readShort", lua_readShort); // 
	lua_register(L, "readInteger", lua_readInteger); // 
	lua_register(L, "readFloat", lua_readFloat); // 
	lua_register(L, "readDouble", lua_readDouble); // 
	lua_register(L, "readString", lua_readString); // 
	lua_register(L, "writeByte", lua_writeByte); // 
	lua_register(L, "writeShort", lua_writeShort); // 
	lua_register(L, "writeInteger", lua_writeInteger); // 
	lua_register(L, "writeFloat", lua_writeFloat); // 
	lua_register(L, "writeDouble", lua_writeDouble); // 
	lua_register(L, "getAddress", lua_getAddress); // 
	lua_register(L, "autoAssemble", lua_autoAssemble); // 
	lua_register(L, "sleep", lua_sleep); // 
}
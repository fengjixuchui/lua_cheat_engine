#include "stdafx.h"
#include "base_functions.h"
#include <TLHELP32.H>
#include "global.h"

char temp_var[255] = { NULL };

DWORD getProcessIdByProcessName(const char * processName)
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		sprintf_s(temp_var,"%s(%d) error_code - <%d> error_msg：%s ", __FILE__, __LINE__,GetLastError(),"遍历进程错误");
		throw temp_var;
	}
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore)
	{
		sprintf_s(temp_var, "%ws", pe32.szExeFile);
		if (strcmp((const char *)temp_var, processName) == 0) {
			g_dwProcessId = pe32.th32ProcessID;
		}
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	::CloseHandle(hProcessSnap);
	return g_dwProcessId;
}

BOOL openProcess(const char * processName)
{
	DWORD dwProcessId = NULL;
	dwProcessId = getProcessIdByProcessName(processName);
	if (dwProcessId == NULL) {
		printf("%s 找不到此进程\n",processName);
		return false;
	}
	g_hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwProcessId);
	if (g_hProcess == NULL) return false;
	return true;
}

char* unicodeToAnsi(TCHAR* wstr)
{
	if (!wstr)
		return NULL;
	INT strlen = ::WideCharToMultiByte(CP_ACP, NULL, wstr, wcslen(wstr), NULL, 0, NULL, FALSE);
	char* str = new char[strlen + 1];
	::WideCharToMultiByte(CP_ACP, NULL, wstr, wcslen(wstr), str, strlen, NULL, FALSE);
	str[strlen] = '\0';
	return str;
}

//=====================================读======================================//
BOOL readMemory(INT baseAddress, LPVOID lpBuffer, INT nSize)
{
	SIZE_T lpNumberOfBytesRead;
	if (g_hProcess == NULL) {
		printf("readMemory error 请先打开进程\n");
		return false;
	}
	if (!ReadProcessMemory(g_hProcess, (LPCVOID)baseAddress, lpBuffer, (SIZE_T)nSize, &lpNumberOfBytesRead)) {
		printf("读取 %x 内存时失败！\n", baseAddress);
		return false;
	}
	if (lpNumberOfBytesRead != nSize) {
		printf("读取 %x 内存时实际读取的长度与要读取的长度不一致！\n", baseAddress);
		return false;
	}
	return true;
}

byte readByte(INT address)
{
	byte lpBuffer = NULL;
	readMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

short readShort(INT address)
{
	short lpBuffer = NULL;
	readMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

int readInteger(INT address)
{
	int lpBuffer = NULL;
	readMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

LONGLONG readLong(INT address)
{
	LONGLONG lpBuffer = NULL;
	readMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

float readFloat(INT lpBaseAddress)
{
	float lpBuffer = NULL;
	readMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

double readDouble(INT lpBaseAddress)
{
	double lpBuffer = NULL;
	readMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

std::vector<byte> readBytes(INT lpBaseAddress, INT len)
{
	byte * lpBuffer = NULL;
	lpBuffer = new byte[len];
	memset(lpBuffer, 0, len);
	readMemory(lpBaseAddress, lpBuffer, len);
	std::vector<byte>  result;
	result.resize(len);
	for (INT i = 0; i < len; i++)
	{
		result[i] = lpBuffer[i];
	}
	delete[]lpBuffer;
	return result;
}

CHAR* readString(INT lpBaseAddress, INT len)
{
	TCHAR *lpBuffer = NULL;
	len = len * 2 + 2;
	lpBuffer = new TCHAR[len];
	readMemory(lpBaseAddress, lpBuffer, len);
	CHAR * str = unicodeToAnsi(lpBuffer);
	return str;
}

//=====================================写======================================//

BOOL writeMemory(INT lpBaseAddress, LPCVOID lpBuffer, INT nSize)
{
	SIZE_T lpNumberOfBytesRead;
	if (g_hProcess == NULL) {
		printf("readMemory error 请先打开进程\n");
		return false;
	}
	if (!WriteProcessMemory(g_hProcess, (LPVOID)lpBaseAddress, lpBuffer, (SIZE_T)(nSize), &lpNumberOfBytesRead)) {
		printf("写入 %x 内存时失败！\n", lpBaseAddress);
		return false;
	}
	if (lpNumberOfBytesRead != nSize) {
		printf("写入 %x 内存时实际写入的长度与要写入的长度不一致！\n", lpBaseAddress);
		return false;
	}
	return true;
}

BOOL writeByte(INT lpBaseAddress, byte lpBuffer)
{
	return writeMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL writeShort(INT lpBaseAddress, short lpBuffer)
{
	return writeMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL writeInteger(INT lpBaseAddress, int lpBuffer)
{
	return writeMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL writeLong(INT lpBaseAddress, LONGLONG lpBuffer)
{
	return writeMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL writeFloat(INT lpBaseAddress, float lpBuffer)
{
	return writeMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL writeDouble(INT lpBaseAddress, double lpBuffer)
{
	return writeMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL writeBytes(INT lpBaseAddress, std::vector<int> bytes)
{
	INT size = bytes.size();
	byte *lpBuffer = new byte[size];
	for (INT i = 0; i < size; i++)
	{
		lpBuffer[i] = bytes[i];
	}
	bool result = writeMemory(lpBaseAddress, lpBuffer, size);
	delete[]lpBuffer;
	return result;
}

BOOL writeString(INT lpBaseAddress, LPCWSTR lpBuffer)
{
	INT len = wcslen(lpBuffer) * 2 + 2;
	return writeMemory(lpBaseAddress, (LPCVOID)lpBuffer, len);
}


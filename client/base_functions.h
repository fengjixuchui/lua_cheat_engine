#pragma once

BOOL openProcess(const char * processName);

BOOL readMemory(INT baseAddress, LPVOID lpBuffer, INT nSize);

byte readByte(INT address);

short readShort(INT address);

int readInteger(INT address);

LONGLONG readLong(INT address);

float readFloat(INT lpBaseAddress);

double readDouble(INT lpBaseAddress);

std::vector<byte> readBytes(INT lpBaseAddress, INT len);

CHAR * readString(INT lpBaseAddress, INT len);

BOOL writeMemory(INT lpBaseAddress, LPCVOID lpBuffer, INT nSize);

BOOL writeByte(INT lpBaseAddress, byte lpBuffer);

BOOL writeShort(INT lpBaseAddress, short lpBuffer);

BOOL writeInteger(INT lpBaseAddress, int lpBuffer);

BOOL writeLong(INT lpBaseAddress, LONGLONG lpBuffer);

BOOL writeFloat(INT lpBaseAddress, float lpBuffer);

BOOL writeDouble(INT lpBaseAddress, double lpBuffer);

BOOL writeBytes(INT lpBaseAddress, std::vector<int> bytes);

BOOL writeString(INT lpBaseAddress, LPCWSTR lpBuffer);

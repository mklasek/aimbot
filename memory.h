#pragma once

#include <windows.h>
#include <TlHelp32.h>
#include <iostream>


class Memory
{
private:

	DWORD procID;
	HANDLE procHandle;

public:

	MODULEENTRY32 ClientDLL, EngineDLL;
	DWORD ClientDLL_size, ClientDLL_base;
	DWORD EngineDLL_size, EngineDLL_base;

	Memory();

	~Memory();

	template<class whatever>
	whatever Read(DWORD Address)
	{
		whatever val;
		ReadProcessMemory(procHandle, (LPVOID)Address, &val, sizeof(whatever), NULL);
		return val;
	}

	template<class whatever>
	bool Write(DWORD Address, whatever Content)
	{
		if (WriteProcessMemory(procHandle, (LPVOID)Address, &Content, sizeof(whatever), NULL))
			return true;
		else
			return false;
	}

	bool GetHandle(char* procName);
	bool ListProcesses();
	MODULEENTRY32 GetModule(char* moduleName);
	bool GetModules();


};



extern Memory Kevin;
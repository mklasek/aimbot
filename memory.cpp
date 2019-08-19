#include "memory.h"

Memory Kevin;

Memory::Memory()
{
	procHandle = NULL;
	procID = NULL;
}

Memory::~Memory()
{
	CloseHandle(procHandle);
}

bool Memory::GetHandle(char* procName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);

	do
	{
		//std::cout << "Process name: " << procEntry.szExeFile << std::endl;
		if (!strcmp(procEntry.szExeFile, procName))
		{
			procID = procEntry.th32ProcessID;
			CloseHandle(hSnapshot);
			procHandle = OpenProcess(PROCESS_VM_READ, false, procID);
			return true;
		}
	} while (Process32Next(hSnapshot, &procEntry));

	return false;
}

MODULEENTRY32 Memory::GetModule(char* modName)
{
	HANDLE mSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procID);

	if (mSnapshot == INVALID_HANDLE_VALUE)
		std::cout << "INVALID_HANDLE_VALUE returned." << std::endl;

	MODULEENTRY32 modEntry;
	modEntry.dwSize = sizeof(MODULEENTRY32);

	do
	{
		if (!strcmp(modEntry.szModule, modName))
		{
			CloseHandle(mSnapshot);
			return modEntry;
		}
	} while (Module32Next(mSnapshot, &modEntry));

	CloseHandle(mSnapshot);
	modEntry.dwSize = 0;
	std::cout << "Module not found" << std::endl;
	return modEntry;
}

bool Memory::GetModules()
{
	ClientDLL = GetModule("client.dll");
	EngineDLL = GetModule("engine.dll");

	ClientDLL_base = (DWORD)ClientDLL.modBaseAddr;
	EngineDLL_base = (DWORD)EngineDLL.modBaseAddr;

	ClientDLL_size = ClientDLL.dwSize;
	EngineDLL_size = EngineDLL.dwSize;

	if (ClientDLL_size == 0) return false;
	if (EngineDLL_size == 0) return false;

	return true;
}

bool Memory::ListProcesses()
{
	HANDLE pSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (pSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "handle invalid" << std::endl;
		return false;
	}
	else
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(PROCESSENTRY32);

		do
		{
			std::cout << "Process name: " << procEntry.szExeFile << std::endl;
		} while (Process32Next(pSnapshot, &procEntry));
		CloseHandle(pSnapshot);
		return true;
	}
}





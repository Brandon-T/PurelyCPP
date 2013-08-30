#ifndef SYSTEM_HPP_INCLUDED
#define SYSTEM_HPP_INCLUDED

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0500

#define TA_FAILED 0
#define TA_SUCCESS_CLEAN 1
#define TA_SUCCESS_KILL 2

#include "Platforms.hpp"
#include "Strings.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <fstream>
#include <TlHelp32.h>

namespace cxx
{
    std::chrono::time_point<std::chrono::system_clock> SystemTime();

    std::uint32_t TimeDuration(std::chrono::time_point<std::chrono::system_clock> Time);

    tstring TheTime();

    int AddOnTermination(void(*function)(void));

    tstring GetEnvironmentVariables(const tstring Variable);

    void SetTransparency(HWND hwnd, std::uint8_t Transperancy = 0);

    PROCESSENTRY32 GetProcessInfo(const TCHAR* ProcessName);

    bool IsProcessRunning(const TCHAR* pProcessName);

    void PrintProcessInfo(const TCHAR* ProcessName);

    DWORD CountProcesses(const TCHAR* pProcessName);

    std::vector<MODULEENTRY32> GetModulesInfo(std::uint32_t ProcessID);

    MODULEENTRY32 GetModuleInfo(std::uint32_t ProcessID, tstring ModuleName);

    void PrintModuleInfo(MODULEENTRY32 Mod32);

    DWORD __stdcall TerminateProcessClean(const TCHAR* ProcessName, DWORD Timeout);

    void ClearConsoleRow(int Row);

    void TrackMouse(HWND hwnd);

    void LockConsoleMenu(HWND WindowHandle);

    bool ReadResourceFromDisk(tstring FilePath, std::vector<std::uint8_t> &Data, const TCHAR* ResourceType);

    bool UpdateResources(std::uint16_t ResourceID, std::uint32_t LanguageID, tstring ModuleName, void* ResourceBuffer, std::uint32_t BufferSize, const TCHAR* ResType);

    bool UpdateResources(std::uint16_t ResourceID, std::uint32_t LanguageID, tstring ModuleName, tstring FileName, const TCHAR* ResType);

    bool ExtractResource(std::uint16_t resourceID, tstring outputFilename, const TCHAR* resName);

    bool RunApplication(tstring ApplicationName, tstring ApplicationArguments, bool WaitInputIdle);

    void RunFromMemory(TCHAR* Buffer, TCHAR* ModulePath);

    bool StartService(tstring szServiceName);

    bool StopService(tstring szServiceName);

    bool CreateRegistryKey(HKEY Root, tstring SubRoot, tstring KeyName = tstring(), DWORD KeyType = 0, tstring InitialValue = tstring());

    bool DeleteRegistryKey(HKEY Root, tstring KeyToRemove);

    bool DeleteRegistryValue(HKEY Root, tstring SubRoot, tstring KeyToRemove);

    bool SetRegistryKey(HKEY Root, tstring SubRoot, tstring KeyToEdit, tstring NewValue = tstring(), DWORD KeyType = REG_SZ);

    tstring ReadRegistryKey(HKEY Root, tstring SubRoot, tstring KeyToRead, DWORD KeyType = 0);
}

#endif // SYSTEM_HPP_INCLUDED

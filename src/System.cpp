// *** ADDED BY HEADER FIXUP ***
#include <algorithm>
#include <string>
// *** END ***
#include "System.hpp"

namespace cxx
{
    std::chrono::time_point<std::chrono::system_clock> SystemTime()
    {
        return std::chrono::system_clock::now();
    }

    std::uint32_t TimeDuration(std::chrono::time_point<std::chrono::system_clock> Time)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(SystemTime() - Time).count();
    }

    tstring TheTime()
    {
        std::time_t Now = std::chrono::system_clock::to_time_t(SystemTime());
        std::tm* LocalTime = std::localtime(&Now);
        tstring Meridian = _T("AM");
        int Hour = LocalTime->tm_hour, Minute = LocalTime->tm_min, Second = LocalTime->tm_sec;

        if (LocalTime->tm_hour > 12)
        {
            Hour -= 12;
            Meridian = _T("PM");
        }
        else if(LocalTime->tm_hour == 12)
        {
            Meridian = _T("PM");
        }
        else if (LocalTime->tm_hour == 0)
        {
            Hour = 12;
        }

        return (Pad(to_tstring(Hour), 2, _T("0")) + _T(':') + Pad(to_tstring(Minute), 2, _T("0")) + _T(':') + Pad(to_tstring(Second), 2, _T("0")) + _T(' ') + Meridian);
    }

    int AddOnTermination(void(*function)(void))
    {
        return std::atexit(function);
    }

    tstring GetEnvironmentVariables(const tstring Variable)
    {
        return _tgetenv(Variable.c_str());
    }

    void SetTransparency(HWND hwnd, std::uint8_t Transperancy)
    {
        long wAttr = GetWindowLong(hwnd, GWL_EXSTYLE);
        SetWindowLong(hwnd, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hwnd, 0, Transperancy, 2);
    }

    PROCESSENTRY32 GetProcessInfo(const TCHAR* ProcessName)
    {
        void* hSnap = nullptr;
        PROCESSENTRY32 Proc32 = {0};

        if((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
            return Proc32;

        Proc32.dwSize = sizeof(PROCESSENTRY32);
        while(Process32Next(hSnap, &Proc32))
        {
            if(StringsEqual(ProcessName, Proc32.szExeFile, false))
            {
                CloseHandle(hSnap);
                return Proc32;
            }
        }
        CloseHandle(hSnap);
        Proc32 = {0};
        return Proc32;
    }

    bool IsProcessRunning(const TCHAR* pProcessName)
    {
        return (GetProcessInfo(pProcessName).th32ProcessID != 0);
    }

    void PrintProcessInfo(const TCHAR* ProcessName)
    {
        PROCESSENTRY32 Proc32 = GetProcessInfo(ProcessName);
        if (Proc32.th32ProcessID != 0)
        {
            tcout << _T("  =======================================================\n");
            tcout << _T("  Process Name:            ") << Proc32.szExeFile           << nl;
            tcout << _T("  =======================================================\n\n");
            tcout << _T("  Process ID:              ") << Proc32.th32ProcessID       << nl;
            tcout << _T("  Thread Count:            ") << Proc32.cntThreads          << nl;
            tcout << _T("  Priority Base:           ") << Proc32.pcPriClassBase      << nl;
            tcout << _T("  Parent Process ID:       ") << Proc32.th32ParentProcessID << nl << nl;
            tcout << _T("  =======================================================\n");
        }
    }

    DWORD CountProcesses(const TCHAR* pProcessName)
    {
        DWORD dwCount = 0;
        HANDLE hSnap = nullptr;
        PROCESSENTRY32 proc32;
        if((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
            return -1;
        proc32.dwSize = sizeof(PROCESSENTRY32);

        while(Process32Next(hSnap, &proc32))
            if(StringsEqual(proc32.szExeFile, pProcessName, false))
                ++dwCount;
        CloseHandle(hSnap);
        return dwCount;
    }

    std::vector<MODULEENTRY32> GetModulesInfo(std::uint32_t ProcessID)
    {
        void* hSnap = nullptr;
        MODULEENTRY32 Mod32 = {0};
        std::vector<MODULEENTRY32> Modules;

        if((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID)) == INVALID_HANDLE_VALUE)
            return Modules;

        Mod32.dwSize = sizeof(MODULEENTRY32);
        while(Module32Next(hSnap, &Mod32))
        {
            Modules.push_back(Mod32);
        }
        CloseHandle(hSnap);
        return Modules;
    }

    MODULEENTRY32 GetModuleInfo(std::uint32_t ProcessID, tstring ModuleName)
    {
        void* hSnap = nullptr;
        MODULEENTRY32 Mod32 = {0};

        if((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID)) == INVALID_HANDLE_VALUE)
            return Mod32;

        Mod32.dwSize = sizeof(MODULEENTRY32);
        while(Module32Next(hSnap, &Mod32))
        {
            if(StringsEqual(ModuleName, Mod32.szModule, false))
            {
                CloseHandle(hSnap);
                return Mod32;
            }
        }

        CloseHandle(hSnap);
        Mod32 = {0};
        return Mod32;
    }

    void PrintModuleInfo(MODULEENTRY32 Mod32)
    {
        tcout << _T("  =======================================================\n");
        tcout << _T("  Module Name:             ") << Mod32.szModule             << nl;
        tcout << _T("  =======================================================\n\n");
        tcout << _T("  Module Path:             ") << Mod32.szExePath            << nl;
        tcout << _T("  Process ID:              ") << Mod32.th32ProcessID        << nl;
        tcout << _T("  Load Count (Global):     ") << static_cast<int>(Mod32.GlblcntUsage != 0xFFFF ? Mod32.GlblcntUsage : -1) << nl;
        tcout << _T("  Load Count (Process):    ") << static_cast<int>(Mod32.ProccntUsage != 0xFFFF ? Mod32.ProccntUsage : -1) << nl;
        tcout << _T("  Base Address:            0x") << std::hex << reinterpret_cast<SIZE_T>(Mod32.modBaseAddr) << nl;
        tcout << _T("  Base Size:               0x") << Mod32.modBaseSize        << nl << nl;
        tcout << _T("  =======================================================\n");
    }

    DWORD WINAPI TerminateProcessClean(const TCHAR* ProcessName, DWORD Timeout)
    {
        DWORD Result = 0;
        HANDLE hProc = nullptr;
        PROCESSENTRY32 Processes = GetProcessInfo(ProcessName);
        if (Processes.th32ProcessID == 0)
            return TA_SUCCESS_CLEAN;

        if (!(hProc = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, false, Processes.th32ProcessID)))
            return TA_FAILED;

        if (Processes.th32ProcessID != 0)
        {
            class TerminateInner
            {
                private:
                    static bool __stdcall TerminateEnum(HWND Hwnd, LPARAM lParam)
                    {
                        DWORD PID;
                        GetWindowThreadProcessId(Hwnd, &PID);
                        if(PID == (DWORD)lParam)
                            PostMessage(Hwnd, WM_CLOSE, 0, 0);
                        return true;
                    }

                public:
                    void TerminateWindows(DWORD PID)
                    {
                        EnumWindows(reinterpret_cast<WNDENUMPROC>(this->TerminateEnum), static_cast<LPARAM>(PID));
                    }
            };
            TerminateInner TIMember;
            TIMember.TerminateWindows(Processes.th32ProcessID);
        }

        Result = (WaitForSingleObject(hProc, Timeout) != WAIT_OBJECT_0) ? (TerminateProcess(hProc, 0) ? TA_SUCCESS_KILL : TA_FAILED) : TA_SUCCESS_CLEAN;
        CloseHandle(hProc);

        return Result;
    }

    void ClearConsoleRow(int Row)
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord;
        coord.X = 0;
        coord.Y = (Row - 1);
        CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
        GetConsoleScreenBufferInfo(hStdOut, &ConsoleScreenBufferInfo);
        FillConsoleOutputCharacter(hStdOut, _T(' '), 80, coord, nullptr);
        SetConsoleCursorPosition(hStdOut, ConsoleScreenBufferInfo.dwCursorPosition);
    }

    void TrackMouse(HWND hwnd)
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.dwHoverTime = 1;
        tme.hwndTrack = hwnd;
        TrackMouseEvent(&tme);
    }

    void LockConsoleMenu(HWND WindowHandle)
    {
        HMENU MenuHandle = GetSystemMenu(WindowHandle, FALSE);
        RemoveMenu(MenuHandle, SC_CLOSE, MF_BYCOMMAND);
        RemoveMenu(MenuHandle, SC_SIZE, MF_BYCOMMAND);
        RemoveMenu(MenuHandle, SC_SEPARATOR, MF_BYCOMMAND);
        RemoveMenu(MenuHandle, SC_STATUS_PROCESS_INFO, MF_BYCOMMAND);
        RemoveMenu(MenuHandle, SC_MOVE, MF_BYCOMMAND);
        RemoveMenu(MenuHandle, SC_MAXIMIZE, MF_BYCOMMAND);
        RemoveMenu(MenuHandle, SC_MINIMIZE, MF_BYCOMMAND);
    }

    bool ReadResourceFromDisk(std::string FilePath, std::vector<std::uint8_t> &Data, const TCHAR* ResourceType)
    {
        std::fstream File(FilePath.c_str(), std::ios::in | std::ios::binary);
        if (File.is_open())
        {
            std::streampos FileSize = 0;
            if (ResourceType == RT_BITMAP)
            {
                File.seekg(0, std::ios::end);
                FileSize = File.tellg();
                FileSize -= sizeof(BITMAPFILEHEADER);
                File.seekg(sizeof(BITMAPFILEHEADER), std::ios::beg);
            }
            else
            {
                File.seekg(0, std::ios::end);
                FileSize = File.tellg();
                File.seekg(0, std::ios::beg);
            }

            Data.resize(FileSize);
            File.read(reinterpret_cast<char*>(Data.data()), FileSize);
            return true;
        }
        return false;
    }

    bool UpdateResources(std::uint16_t ResourceID, std::uint32_t LanguageID, tstring ModuleName, void* ResourceBuffer, std::uint32_t BufferSize, const TCHAR* ResType)
    {
        HANDLE hRes = BeginUpdateResource(ModuleName.c_str(), false);
        if (hRes != nullptr)
        {
            bool Result = UpdateResource(hRes, ResType, MAKEINTRESOURCE(ResourceID), LanguageID, ResourceBuffer, BufferSize);
            EndUpdateResource(hRes, false);
            return Result;
        }
        return false;
    }

    bool UpdateResources(std::uint16_t ResourceID, std::uint32_t LanguageID, tstring ModuleName, std::string FileName, const TCHAR* ResType)
    {
        std::fstream File(FileName.c_str(), std::ios::in | std::ios::binary);
        if (File.is_open())
        {
            File.seekg(0, std::ios::end);
            std::size_t FileSize = File.tellg();
            File.seekg(0, std::ios::beg);

            std::vector<std::uint8_t> Buffer(FileSize);
            File.read(reinterpret_cast<char*>(Buffer.data()), FileSize);
            File.close();

            return UpdateResources(ResourceID, LanguageID, ModuleName, Buffer.data(), FileSize, ResType);
        }
        return false;
    }

    bool ExtractResource(std::uint16_t ResourceID, tstring OutputFileName, const TCHAR* ResType)
    {
        bool success = false;
        try
        {
            HRSRC hResource = FindResource(nullptr, MAKEINTRESOURCE(ResourceID), ResType);
            if (hResource == nullptr)
            {
                return false;
            }

            HGLOBAL hFileResource = LoadResource(nullptr, hResource);
            if (hFileResource == nullptr)
            {
                return false;
            }

            void* lpFile = LockResource(hFileResource);
            if (lpFile == nullptr)
            {
                return false;
            }

            std::uint32_t dwSize = SizeofResource(nullptr, hResource);
            if (dwSize == 0)
            {
                return false;
            }

            HANDLE hFile = CreateFile(OutputFileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            HANDLE hFilemap = CreateFileMapping(hFile, nullptr, PAGE_READWRITE, 0, dwSize, nullptr);
            if (hFilemap == nullptr)
            {
                return false;
            }

            void* lpBaseAddress = MapViewOfFile(hFilemap, FILE_MAP_WRITE, 0, 0, 0);
            CopyMemory(lpBaseAddress, lpFile, dwSize);
            UnmapViewOfFile(lpBaseAddress);
            CloseHandle(hFilemap);
            CloseHandle(hFile);

            return true;
        }
        catch (...) {}
        return success;
    }

    bool RunApplication(tstring ApplicationName, tstring ApplicationArguments, bool WaitInputIdle)
    {
        bool Result = false;
        STARTUPINFO         siStartupInfo;
        PROCESS_INFORMATION piProcessInfo;

        std::vector<TCHAR> Arguments(ApplicationArguments.begin(), ApplicationArguments.end()); //strcpy(Arguments, ApplicationArguments.c_str());
        std::memset(&siStartupInfo, 0, sizeof(siStartupInfo));
        std::memset(&piProcessInfo, 0, sizeof(piProcessInfo));

        if (CreateProcess(ApplicationName.c_str(), &Arguments[0], nullptr, nullptr, false, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &siStartupInfo, &piProcessInfo) != false)
            Result = true;

        if (WaitInputIdle)
        {
            Result = false;
            if (WaitForInputIdle(piProcessInfo.hProcess, 10000) == 0)
                Result = true;
        }
        CloseHandle(piProcessInfo.hThread);
        CloseHandle(piProcessInfo.hProcess);
        return Result;
    }

    void RunFromMemory(TCHAR* Buffer, TCHAR* ModulePath)
    {
        /*std::uint32_t dwWritten = 0, dwHeader = 0, dwImageSize = 0, dwSectionCount = 0;
        std::uint32_t dwSectionSize = 0, firstSection = 0, previousProtection = 0, jmpSize = 0;

        IMAGE_NT_HEADERS INH;
        IMAGE_DOS_HEADER IDH;
        IMAGE_SECTION_HEADER Sections[1000];

        PROCESS_INFORMATION peProcessInformation;
        STARTUPINFO peStartUpInformation;
        CONTEXT pContext;

        std::memcpy(&IDH, Buffer, sizeof(IDH));
        std::memcpy(&INH, Buffer + IDH.e_lfanew, sizeof(INH));

        dwImageSize = INH.OptionalHeader.SizeOfImage;
        std::vector<char> pMemory(dwImageSize);
        std::memset(&pMemory[0], 0, dwImageSize);
        std::vector<char>::iterator pFile = pMemory.begin();

        dwHeader = INH.OptionalHeader.SizeOfHeaders;
        firstSection = ToNumber<std::uint32_t>(tstring(Buffer + IDH.e_lfanew + sizeof(IMAGE_NT_HEADERS)));
        std::memcpy(Sections, reinterpret_cast<const void*>(firstSection), sizeof(IMAGE_SECTION_HEADER)*INH.FileHeader.NumberOfSections);

        std::copy(Buffer, Buffer + dwHeader, pFile);

        if((INH.OptionalHeader.SizeOfHeaders % INH.OptionalHeader.SectionAlignment) == 0)
        {
            jmpSize = INH.OptionalHeader.SizeOfHeaders;
        }
        else
        {
            jmpSize = INH.OptionalHeader.SizeOfHeaders / INH.OptionalHeader.SectionAlignment;
            jmpSize += 1;
            jmpSize *= INH.OptionalHeader.SectionAlignment;
        }

        pFile += jmpSize;

        for(dwSectionCount = 0; dwSectionCount < INH.FileHeader.NumberOfSections; ++dwSectionCount)
        {
            jmpSize = 0;
            dwSectionSize = Sections[dwSectionCount].SizeOfRawData;
            std::copy(Buffer + Sections[dwSectionCount].PointerToRawData, Buffer + (Sections[dwSectionCount].PointerToRawData + dwSectionSize), pFile);

            if((Sections[dwSectionCount].Misc.VirtualSize % INH.OptionalHeader.SectionAlignment) == 0)
            {
                jmpSize = Sections[dwSectionCount].Misc.VirtualSize;
            }
            else
            {
                jmpSize = Sections[dwSectionCount].Misc.VirtualSize / INH.OptionalHeader.SectionAlignment;
                jmpSize += 1;
                jmpSize *= INH.OptionalHeader.SectionAlignment;
            }
            pFile += jmpSize;
        }

        std::memset(&peStartUpInformation, 0, sizeof(STARTUPINFO));
        std::memset(&peProcessInformation, 0, sizeof(PROCESS_INFORMATION));
        std::memset(&pContext, 0, sizeof(CONTEXT));

        peStartUpInformation.cb = sizeof(peStartUpInformation);
        if(CreateProcess(nullptr, ModulePath, nullptr, nullptr, false, CREATE_SUSPENDED, nullptr, nullptr, &peStartUpInformation, &peProcessInformation))
        {
            pContext.ContextFlags = CONTEXT_FULL;
            GetThreadContext(peProcessInformation.hThread, &pContext);
            VirtualProtectEx(peProcessInformation.hProcess, reinterpret_cast<void*>(INH.OptionalHeader.ImageBase), dwImageSize, PAGE_EXECUTE_READWRITE, (PDWORD)&previousProtection);
            WriteProcessMemory(peProcessInformation.hProcess, reinterpret_cast<void*>(INH.OptionalHeader.ImageBase), &pMemory[0], dwImageSize, reinterpret_cast<std::size_t*>(&dwWritten));
            WriteProcessMemory(peProcessInformation.hProcess, reinterpret_cast<void*>(pContext.Ebx + 8), &INH.OptionalHeader.ImageBase, 4, &dwWritten);
            pContext.Eax = INH.OptionalHeader.ImageBase + INH.OptionalHeader.AddressOfEntryPoint;
            SetThreadContext(peProcessInformation.hThread, &pContext);
            VirtualProtectEx(peProcessInformation.hProcess, reinterpret_cast<void*>(INH.OptionalHeader.ImageBase), dwImageSize, previousProtection, 0);
            ResumeThread(peProcessInformation.hThread);
        }*/
    }

    bool StartService(tstring szServiceName)
    {
        SC_HANDLE schService;
        SC_HANDLE schSCManager;
        SERVICE_STATUS ssStatus;
        bool bRet = false;
        int iCont = 0;

        schSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
        if (schSCManager)
        {
            schService = OpenService(schSCManager, szServiceName.c_str(), SERVICE_ALL_ACCESS);
            if (schService)
            {
                if (StartService(schService, 0, nullptr))
                {
                    Sleep(1000);
                    while(QueryServiceStatus(schService, &ssStatus))
                    {
                        ++iCont;
                        if (ssStatus.dwCurrentState == SERVICE_START_PENDING)
                        {
                            Sleep(1000);
                            if (iCont > 10)
                                break;
                        }
                        else
                            break;
                    }

                    if (ssStatus.dwCurrentState == SERVICE_RUNNING)
                        bRet = true;
                    else
                        bRet = false;
                }
                CloseServiceHandle(schService);
            }
            else
                bRet = true;
            CloseServiceHandle(schSCManager);
        }
        else
            bRet = false;
        return bRet;
    }

    bool StopService(tstring szServiceName)
    {
        SC_HANDLE schService;
        SC_HANDLE schSCManager;
        SERVICE_STATUS ssStatus;
        bool bRet = true;
        int iCont = 0;

        schSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
        if (schSCManager)
        {
            schService = OpenService(schSCManager, szServiceName.c_str(), SERVICE_ALL_ACCESS);
            if (schService)
            {
                if (ControlService(schService, SERVICE_CONTROL_STOP, &ssStatus))
                {
                    Sleep(1000);
                    while(QueryServiceStatus(schService, &ssStatus))
                    {
                        ++iCont;
                        if (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
                        {
                            Sleep(1000);
                            if (iCont > 10)
                                break;
                        }
                        else
                            break;
                    }

                    if (ssStatus.dwCurrentState == SERVICE_STOPPED)
                        bRet = true;
                    else
                        bRet = false;
                }
                CloseServiceHandle(schService);
            }
            else
                bRet = true;
            CloseServiceHandle(schSCManager);
        }
        else
            bRet = false;
        return bRet;
    }

    bool CreateRegistryKey(HKEY Root, tstring SubRoot, tstring KeyName, DWORD KeyType, tstring InitialValue)
    {
        HKEY hKey;
        DWORD dwError = ERROR_CANTOPEN;
        if ((dwError = RegOpenKeyEx(Root, SubRoot.c_str(), 0, KEY_ALL_ACCESS, &hKey)) != ERROR_SUCCESS)
        {
            dwError = ERROR_CANTOPEN;
            DWORD Disposition;
            dwError = RegCreateKeyEx(Root, SubRoot.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &hKey, &Disposition);
            dwError = (Disposition != 0) ? Disposition : dwError;
        }

        if ((dwError == ERROR_SUCCESS) || (dwError == REG_CREATED_NEW_KEY) || (dwError == REG_OPENED_EXISTING_KEY))
        {
            if (!InitialValue.empty())
            {
                dwError = ERROR_CANTWRITE;
                size_t Size = sizeof(DWORD);
                switch(KeyType)
                {
                    case REG_DWORD:
                        {
                            Size = sizeof(DWORD);
                            DWORD Value = ToNumber<DWORD>(InitialValue);
                            dwError = RegSetValueEx(hKey, KeyName.c_str(), 0, KeyType, reinterpret_cast<const std::uint8_t*>(&Value), Size);
                        }
                        break;

                    case REG_QWORD:
                        {
                            Size = sizeof(std::uint64_t);
                            std::uint64_t Value = ToNumber<std::uint64_t>(InitialValue);
                            dwError = RegSetValueEx(hKey, KeyName.c_str(), 0, KeyType, reinterpret_cast<const std::uint8_t*>(&Value), Size);
                        }
                        break;

                    case REG_MULTI_SZ:
                        {
                            std::vector<TCHAR> Buffer(Size);
                            for (size_t I = 0; I < Buffer.size(); I++)
                                Buffer[I] = InitialValue[I] != 0xA ? InitialValue[I] : 0;
                            dwError = RegSetValueEx(hKey, KeyName.c_str(), 0, KeyType, reinterpret_cast<const std::uint8_t*>(Buffer.data()), Buffer.size());
                        }
                        break;

                    case REG_SZ:
                    case REG_EXPAND_SZ:
                        {
                            Size = InitialValue.size();
                            dwError = RegSetValueEx(hKey, KeyName.c_str(), 0, KeyType, reinterpret_cast<const std::uint8_t*>(InitialValue.c_str()), Size);
                        }
                        break;

                    default:
                        dwError = ERROR_CANTWRITE;
                        break;
                }
            }
            RegCloseKey(hKey);
        }

        bool Result = ((InitialValue.empty()) ? ((dwError == REG_CREATED_NEW_KEY) || (dwError == REG_OPENED_EXISTING_KEY) || (dwError == ERROR_SUCCESS)) : (dwError == ERROR_SUCCESS));
        if (!Result)
            tcout << ErrorMessage(dwError);

        return Result;
    }

    bool DeleteRegistryKey(HKEY Root, tstring KeyToRemove)
    {
        DWORD dwError = ERROR_CANTOPEN;
        if ((dwError = RegDeleteKey(Root, KeyToRemove.c_str())) == ERROR_SUCCESS)
            RegCloseKey(Root);
        else
            tcout << ErrorMessage(dwError);

        return (dwError == ERROR_SUCCESS);
    }

    bool DeleteRegistryValue(HKEY Root, tstring SubRoot, tstring KeyToRemove)
    {
        HKEY hKey;
        DWORD dwError = ERROR_CANTOPEN;
        if ((dwError = RegOpenKeyEx(Root, SubRoot.c_str(), 0, KEY_ALL_ACCESS, &hKey)) == ERROR_SUCCESS)
        {
            dwError = ERROR_CANTOPEN;
            dwError = RegDeleteValue(hKey, KeyToRemove.c_str());
            RegCloseKey(hKey);
        }
        if (dwError != ERROR_SUCCESS)
            tcout << ErrorMessage(dwError);

        return (dwError == ERROR_SUCCESS);
    }

    bool SetRegistryKey(HKEY Root, tstring SubRoot, tstring KeyToEdit, tstring NewValue, DWORD KeyType)
    {
        HKEY hKey;
        DWORD dwError = ERROR_CANTOPEN;
        if ((dwError = RegOpenKeyEx(Root, SubRoot.c_str(), 0, KEY_ALL_ACCESS, &hKey)) == ERROR_SUCCESS)
        {
            dwError = ERROR_CANTWRITE;
            switch(KeyType)
            {
                case REG_DWORD:
                    {
                        DWORD dwSize = sizeof(DWORD);
                        DWORD Data = ToNumber<DWORD>(NewValue);
                        dwError = RegSetValueEx(hKey, KeyToEdit.c_str(), 0, KeyType, reinterpret_cast<const std::uint8_t*>(&Data), dwSize);
                    }
                    break;

                case REG_QWORD:
                    {
                        DWORD dwSize = sizeof(std::uint64_t);
                        std::uint64_t Data = ToNumber<std::uint64_t>(NewValue);
                        dwError = RegSetValueEx(hKey, KeyToEdit.c_str(), 0, KeyType, reinterpret_cast<const std::uint8_t*>(&Data), dwSize);
                    }
                    break;

                case REG_MULTI_SZ:
                    {
                        std::vector<TCHAR> Buffer(NewValue.size());
                        for (std::size_t I = 0; I < Buffer.size(); ++I)
                            Buffer[I] = NewValue[I] != 0xA ? NewValue[I] : 0;
                        dwError = RegSetValueEx(hKey, KeyToEdit.c_str(), 0, KeyType, reinterpret_cast<const std::uint8_t*>(Buffer.data()), Buffer.size());
                    }
                    break;

                case REG_SZ:
                case REG_EXPAND_SZ:
                    {
                        dwError = RegSetValueEx(hKey, KeyToEdit.c_str(), 0, KeyType, reinterpret_cast<const std::uint8_t*>(NewValue.c_str()), NewValue.size());
                    }
                    break;

                default:
                    dwError = ERROR_CANTWRITE;
                    break;
            }
            RegCloseKey(hKey);
        }
        if (dwError != ERROR_SUCCESS)
            tcout << ErrorMessage(dwError);

        return (dwError == ERROR_SUCCESS);
    }

    tstring ReadRegistryKey(HKEY Root, tstring SubRoot, tstring KeyToRead, DWORD KeyType)
    {
        HKEY hKey;
        DWORD dwError = ERROR_CANTOPEN;
        tstring Result;
        if ((dwError = RegOpenKeyEx(Root, SubRoot.c_str(), 0, KEY_READ, &hKey)) == ERROR_SUCCESS)
        {
            DWORD dwSize = sizeof(DWORD);
            dwError = ERROR_CANTREAD;

            if (KeyType == 0)
            {
                TCHAR TempData[255] = {0};
                dwSize = sizeof(TempData) / sizeof(TCHAR);
                dwError = RegQueryValueEx(hKey, KeyToRead.c_str(), nullptr, &KeyType, reinterpret_cast<std::uint8_t*>(TempData), &dwSize);
                KeyType = (dwError == ERROR_SUCCESS) ? KeyType : 0;
            }

            if (KeyType != 0)
            {
                switch(KeyType)
                {
                    case REG_DWORD:
                        {
                            dwSize = sizeof(DWORD);
                            DWORD Data = 0;
                            dwError = RegQueryValueEx(hKey, KeyToRead.c_str(), nullptr, &KeyType, reinterpret_cast<std::uint8_t*>(&Data), &dwSize);
                            Result = to_tstring(Data);
                        }
                        break;

                    case REG_QWORD:
                        {
                            dwSize = sizeof(std::uint64_t);
                            std::uint64_t Data = 0;
                            dwError = RegQueryValueEx(hKey, KeyToRead.c_str(), nullptr, &KeyType, reinterpret_cast<std::uint8_t*>(&Data), &dwSize);
                            Result = to_tstring(Data);
                        }
                        break;

                    case REG_MULTI_SZ:
                        {
                            std::vector<TCHAR> Data(dwSize - 1); //char* Data = new char[dwSize];
                            dwError = RegQueryValueEx(hKey, KeyToRead.c_str(), nullptr, &KeyType, reinterpret_cast<std::uint8_t*>(Data.data()), &dwSize);
                            for (std::size_t I = 0; I < Data.size(); ++I)    /*for (char* ptr = Data; *ptr; ptr += lstrlen(ptr) + 1){Result.append(ptr); Result += 0xA;}delete[] Data; Data = 0;*/
                                Result += (Data[I] == 0 ? 0xA : Data[I]);   /*char* ptr = Data;while (*ptr){Result.append(ptr); Result += "\n"; ptr += strlen(ptr) + 1;}*/
                        }
                        break;

                    case REG_SZ:
                    case REG_EXPAND_SZ:
                        {
                            std::vector<TCHAR> Data(dwSize);
                            dwError = RegQueryValueEx(hKey, KeyToRead.c_str(), nullptr, &KeyType, reinterpret_cast<std::uint8_t*>(Data.data()), &dwSize);
                            Result.append(Data.data(), dwSize);
                        }
                        break;

                    default:
                        dwError = ERROR_CANTREAD;
                        break;
                }
            }
            RegCloseKey(hKey);
        }

        if (dwError != ERROR_SUCCESS)
            tcout << ErrorMessage(dwError);

        return Result;
    }
}

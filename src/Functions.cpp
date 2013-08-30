// *** ADDED BY HEADER FIXUP ***
#include <algorithm>
#include <vector>
// *** END ***
#include "Functions.hpp"

namespace cxx
{
    bool CompressFile(std::string FileToCompress, std::string FileToSaveAs)
    {
        std::ifstream File(FileToCompress.c_str(), std::ios::in | std::ios::binary);
        gzFile outfile = gzopen(FileToSaveAs.c_str(), "wb");

        if (!File.is_open() || !outfile)
            return false;

        std::array<char, 128> Buffer;
        while (File.read(Buffer.data(), Buffer.size()))
        {
            File.read(Buffer.data(), Buffer.size());
            gzwrite(outfile, Buffer.data(), File.gcount());
        }

        File.close();
        gzclose(outfile);
        return true;
    }

    bool DecompressFile(std::string FileToDecompress, std::string FileToSaveAs)
    {
        gzFile infile = gzopen(FileToDecompress.c_str(), "rb");
        if (!infile)
            return false;

        std::ofstream File(FileToSaveAs.c_str(), std::ios::out | std::ios::binary);
        if (File.is_open())
        {
            int FileLen = 0;
            std::array<char, 128> Buffer;
            while ((FileLen = gzread(infile, Buffer.data(), Buffer.size())) > 0)
            {
                File.write(Buffer.data(), FileLen);
            }
            File.close();
        }

        gzclose(infile);
        return true;
    }

    tstring ReadFile(const std::string& FileName, bool BinaryMode)
    {
        tstring Result;
        std::_Ios_Openmode OpenMode = BinaryMode ? std::ios::in | std::ios::binary : std::ios::in;

        tifstream File(FileName.c_str(), OpenMode);
        if (File.is_open())
        {
            File.seekg(0, std::ios::end);
            int FileLen = File.tellg();
            File.seekg(0, std::ios::beg);

            std::vector<TCHAR> Buffer(FileLen);
            File.read(Buffer.data(), FileLen);
            File.close();

            Result.append(Buffer.begin(), Buffer.end());
        }
        return Result;
    }

    bool WriteFile(const std::string& FileName, tstring DataToWrite, bool BinaryMode, bool Append)
    {
        std::_Ios_Openmode OpenMode = BinaryMode ? std::ios::out | std::ios::binary : std::ios::out;
        if (Append)
        {
            OpenMode |= std::ios::app;
        }

        tofstream file(FileName.c_str(), OpenMode);
        if (file.is_open())
            file << DataToWrite;
        else
            return false;

        file.close();
        return true;
    }

    StringArray SearchDirectory(tstring RootDirectory, tstring FileExtension, bool SearchSubdirectories, tstring FileName, bool FullPath, bool IncludeFolders)
    {
        tstring  FilePath;              // Filepath
        tstring  Extension;             // Extension
        StringArray FilesFound;             // Result

#if defined _WIN32 || defined _WIN64
        void*  hFile;                      // Handle to file
        tstring  Pattern;               // Pattern
        WIN32_FIND_DATA FileInformation;    // File information

        Pattern = RootDirectory + _T("/") + FileName + _T(".*");

        hFile = FindFirstFile(Pattern.c_str(), &FileInformation);
        if(hFile != INVALID_HANDLE_VALUE)
        {
            Repeat
            if(FileInformation.cFileName[0] != '.')
            {
                FilePath.erase();
                FilePath = (FullPath ? RootDirectory + _T("/") + FileInformation.cFileName : FileInformation.cFileName);

                if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (IncludeFolders)
                        FilesFound(FilePath);

                    if (SearchSubdirectories)
                    {
                        // Search subdirectory
                        StringArray Temp = SearchDirectory(!FullPath ? RootDirectory + _T("/") + FilePath : FilePath, FileExtension, SearchSubdirectories, FileName, FullPath);
                        for (std::size_t I = 0; I < Temp.Size(); ++I)
                        {
                            FilesFound(Temp[I]);
                        }
                        Temp.Clear();
                    }
                }
                else
                {
                    //Check extension
                    Extension = FileInformation.cFileName;
                    Extension = Extension.substr(Extension.rfind(_T(".")) + 1);

                    if (!FileExtension.empty() && (Extension == FileExtension))
                        FilesFound(FilePath);   //Save filename
                    else if (FileExtension.empty() || FileExtension == _T(".*"))
                        FilesFound(FilePath);
                }
            }
            Until(FindNextFile(hFile, &FileInformation) == FALSE);

            FindClose(hFile);   //CloseFile Handle
        }

#else

        DIR* pDirectory = 0;
        struct stat    FileStat;
        struct dirent* pDirentStruct;
        if((pDirectory = opendir(RootDirectory.c_str())) == nullptr) return FilesFound;

        while ((pDirentStruct = readdir(pDirectory)) != nullptr)
        {
            if (tstring(pDirentStruct->d_name) != _T(".") && tstring(pDirentStruct->d_name) != _T(".."))
            {
                FilePath.erase();
                FilePath = (FullPath ? RootDirectory + _T("/") + tstring(pDirentStruct->d_name) : tstring(pDirentStruct->d_name));

                const TCHAR *pFilePath = tstring(RootDirectory + _T("/") + tstring(pDirentStruct->d_name)).c_str();
                stat(pFilePath, &FileStat);
                if (S_ISDIR(FileStat.st_mode))
                {
                    if (IncludeFolders)
                        FilesFound(FilePath);

                    if (SearchSubdirectories)
                    {
                        StringArray Temp = SearchDirectory(!FullPath ? RootDirectory + _T("/") + FilePath : FilePath, FileExtension, SearchSubdirectories, FileName, FullPath);
                        FilesFound.Append(Temp);
                    }
                }
                else
                {
                    if (!S_ISDIR(FileStat.st_mode))
                    {
                        Extension = pDirentStruct->d_name;
                        Extension = Extension.substr(Extension.rfind(_T(".")) + 1);

                        if (!FileExtension.empty() && (Extension == FileExtension))
                            FilesFound(FilePath);
                        else if (FileExtension.empty() || FileExtension == _T(".*"))
                            FilesFound(FilePath);
                    }
                }
            }
        }
        closedir(pDirectory);
#endif
        return FilesFound;
    }

    bool OpenFileDialog(HWND Parent, tstring& FileName, tstring& FilePath, bool InvertSlashes, const TCHAR* Filter)
    {
        OPENFILENAME OFN;
        TCHAR FPath[MAX_PATH];
        TCHAR FTitle[MAX_PATH];

        ZeroMemory(&OFN, sizeof(OFN));
        OFN.lStructSize = sizeof(OFN);

        OFN.hwndOwner = Parent;
        OFN.lpstrInitialDir = nullptr;
        OFN.lpstrFile = FPath;
        OFN.lpstrFile[0] = _T('\0');
        OFN.nFilterIndex = 1;
        OFN.nMaxFile = sizeof(FPath);
        OFN.lpstrFileTitle = FTitle;
        OFN.lpstrFileTitle[0] = _T('\0');
        OFN.nMaxFileTitle = sizeof(FTitle);
        OFN.lpstrFilter = (Filter == tstring().c_str() ? _T("All Files\0*.*\0\0") : Filter);
        OFN.lpstrDefExt = nullptr;
        OFN.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

        if (GetOpenFileName(&OFN) != 0)
        {
            if (InvertSlashes)
            {
                tstring TempFilePath = OFN.lpstrFile;
                std::replace(TempFilePath.begin(), TempFilePath.end(), '\\', '/');
                _tcscpy(OFN.lpstrFile, TempFilePath.c_str());
            }
            FilePath = OFN.lpstrFile;
            FileName = OFN.lpstrFileTitle;

            return true;
        }
        return false;
    }

    int MessageBoxTimeoutA(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, std::uint32_t uType, std::uint32_t dwMilliseconds, std::uint16_t wLanguageId)
    {
        typedef int (__stdcall * MSGBOXAAPI)(IN HWND hWnd, IN LPCTSTR lpText, IN LPCTSTR lpCaption, IN std::uint32_t uType, IN std::uint16_t wLanguageId, IN std::uint32_t dwMilliseconds);
        static MSGBOXAAPI MsgBoxTOA = nullptr;

        if (!MsgBoxTOA)
        {
            HMODULE hUser32 = xLoadLibrary(_T("user32.dll"));
            if (hUser32)
                MsgBoxTOA = reinterpret_cast<MSGBOXAAPI>(xGetProcAddress(hUser32, "MessageBoxTimeoutA"));
            else
                return 0;
            xFreeLibrary(hUser32);
        }

        if (MsgBoxTOA)
            return MsgBoxTOA(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);

        return 0;
    }

    int MessageBoxTimeoutW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, std::uint32_t uType, std::uint32_t dwMilliseconds, std::uint16_t wLanguageId)
    {
        typedef int (__stdcall * MSGBOXWAPI)(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN std::uint32_t uType, IN std::uint16_t wLanguageId, IN std::uint32_t dwMilliseconds);
        static MSGBOXWAPI MsgBoxTOW = nullptr;

        if (!MsgBoxTOW)
        {
            HMODULE hUser32 = xLoadLibrary(_T("user32.dll"));
            if (hUser32)
                MsgBoxTOW = reinterpret_cast<MSGBOXWAPI>(xGetProcAddress(hUser32, "MessageBoxTimeoutW"));
            else
                return 0;
            xFreeLibrary(hUser32);
        }

        if (MsgBoxTOW)
            return MsgBoxTOW(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);

        return 0;
    }
}

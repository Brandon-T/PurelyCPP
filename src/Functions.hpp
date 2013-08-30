// *** ADDED BY HEADER FIXUP ***
#include <string>
// *** END ***
#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_HPP_INCLUDED

#define MB_TIMEDOUT 32000
#ifdef UNICODE
#define MessageBoxTimeout MessageBoxTimeoutW
#else
#define MessageBoxTimeout MessageBoxTimeoutA
#endif

#include <fstream>
#include <array>
#include "Types.hpp"
#include "Libraries/ZLib/zlib.h"

namespace cxx
{
    bool CompressFile(std::string FileToCompress, std::string FileToSaveAs);

    bool DecompressFile(std::string FileToDecompress, std::string FileToSaveAs);

    tstring ReadFile(const std::string& FileName, bool BinaryMode = true);

    bool WriteFile(const std::string& FileName, tstring DataToWrite, bool BinaryMode = true, bool Append = false);

    StringArray SearchDirectory(tstring RootDirectory, tstring FileExtension, bool SearchSubdirectories, tstring FileName = _T("*"), bool FullPath = true, bool IncludeFolders = false);

    bool OpenFileDialog(HWND Parent, tstring& FileName, tstring& FilePath, bool InvertSlashes = false, const TCHAR* Filter = nullptr);

    int MessageBoxTimeoutA(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, std::uint32_t uType, std::uint32_t dwMilliseconds, std::uint16_t wLanguageId = 0);

    int MessageBoxTimeoutW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, std::uint32_t uType, std::uint32_t dwMilliseconds, std::uint16_t wLanguageId = 0);
}

#endif // FUNCTIONS_HPP_INCLUDED

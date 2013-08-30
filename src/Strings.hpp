// *** ADDED BY HEADER FIXUP ***
#include <string>
#include <vector>
// *** END ***
#ifndef STRINGS_HPP_INCLUDED
#define STRINGS_HPP_INCLUDED

#include "Unicode.hpp"
#include <stdexcept>
#include <cstring>
#include "Defines.hpp"
#include "Types.hpp"
#include "Libraries/ZLib/zlib.h"

namespace cxx
{
    tstring Pad(tstring StringToPad, int Amount, tstring PadChars, bool Left = true);

    tstring Copy(tstring Str, int FirstChar, std::size_t Count = tstring::npos);

    tstring UpperCase(tstring Str);

    tstring LowerCase(tstring Str);

    tstring Capitalize(tstring Str);

    int Pos(tstring Needle, tstring Haystack, std::size_t StartPos = 0);

    int RPos(tstring Needle, tstring Haystack, std::size_t StartPos = tstring::npos);

    int PosFirstOf(tstring Needle, tstring Haystack, std::size_t StartPos = 0);

    int PosFirstNotOf(tstring Needle, tstring Haystack, std::size_t StartPos = 0);

    int PosLastOf(tstring Needle, tstring Haystack, std::size_t StartPos = tstring::npos);

    int PosLastNotOf(tstring Needle, tstring Haystack, std::size_t StartPos = tstring::npos);

    tstring Mid(const tstring& Str, int Pos1, int Pos2);

    tstring Left(const tstring& Str, int Pos);

    tstring& LeftTrim(tstring &Value);

    tstring& RightTrim(tstring &Value);

    tstring &Trim(tstring &Value);

    StringArray SplitString(tstring StrToSplit, int NumberOfPieces);

    StringArray SplitString(tstring StringToSplit, tstring Delimiter);

    tstring ConcatStrArrayToStr(StringArray Strings, tstring Delimiter = tstring());

    int ConcatStrArrayToInt(StringArray Strings);

    IntegerArray StringArrayToIntArray(StringArray StrArrayToConvert);

    StringArray IntegerArrayToStrArray(IntegerArray IntArrayToConvert);

    tstring ConcatCharArrayToString(CharArray Chars, tstring Delimiter = tstring());

    StringArray CharArrayToStrArray(CharArray CharArrayToConvert);

    IntegerArray CharArrayToIntArray(CharArray CharArrayToConvert);

    CharArray IntegerArrayToCharArray(IntegerArray IntArrayToConvert);

    tstring Replace(tstring Text, tstring FindStr, tstring ReplacementString, ReplacementFlags Flags);

    template <typename charT, typename Traits, typename Allocator>
    std::vector<std::basic_string<charT, Traits, Allocator>> Explode(const std::basic_string<charT, Traits, Allocator>& s, charT delim);

    tstring Implode(tstring Glue, StringArray Pieces);

    tstring Implode(const tstring &Glue, const std::vector<tstring> &Pieces);

    StringArray Explode(tstring Del, tstring Str);

    std::string CompressString(const std::string& StringToCompress, int compressionlevel = Z_BEST_COMPRESSION);

    std::string DecompressString(const std::string& StringToDecompress);

    bool StringsEqual(tstring Str1, tstring Str2, bool CaseSensitive = true);

    tstring ExtractFromString(tstring String, tstring WhatToExtract);

    tstring HtmlDecode(tstring StringToDecode);
}

#endif // STRINGS_HPP_INCLUDED

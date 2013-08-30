// *** ADDED BY HEADER FIXUP ***
#include <algorithm>
// *** END ***
#include "Strings.hpp"

namespace cxx
{
    tstring Pad(tstring StringToPad, int Amount, tstring PadChars, bool Left)
    {
        tstring Temp;
        for (std::size_t I = Amount; I > StringToPad.size(); --I)
            Temp += PadChars;

        return (Left ? (Temp + StringToPad) : (StringToPad + Temp));
    }

    tstring Copy(tstring Str, int FirstChar, std::size_t Count)
    {
        return Str.substr(--FirstChar >= 0 ? FirstChar : 0, Count);
    }

    tstring UpperCase(tstring Str)
    {
        /*
        for (std::size_t I = 0; I < Str.size(); ++I)
            if(Str[I] >= 0x61 && Str[I] <= 0x7A)
                Str[I] = Str[I] - 0x20;
        */
        //Str[I] -= 'a' - 'A' ;
        for (std::size_t I = 0; I < Str.length(); ++I)
        {
            Str[I] = _totupper(Str[I]);
        }
        return Str;
    }

    tstring LowerCase(tstring Str)
    {
        /*
        for (std::size_t I = 0; I < Str.size(); ++I)
            if(Str[I] >= 0x41 && Str[I] <= 0x5A)
                Str[I] = Str[I] + 0x20;
        */
        //Str[I] += 'a' - 'A' ;
        for (std::size_t I = 0; I < Str.length(); ++I)
        {
            Str[I] = _totlower(Str[I]);
        }
        return Str;
    }

    tstring Capitalize(tstring Str)
    {
        Str[0] = _totupper(Str[0]);
        return Str;
    }

    int Pos(tstring Needle, tstring Haystack, std::size_t StartPos)
    {
        std::size_t Position = Haystack.find(Needle, StartPos);
        return (Position != tstring::npos ? Position : -1);
    }

    int RPos(tstring Needle, tstring Haystack, std::size_t StartPos)
    {
        size_t Position = Haystack.rfind(Needle, StartPos);
        return (Position != tstring::npos ? Position : -1);
    }

    int PosFirstOf(tstring Needle, tstring Haystack, std::size_t StartPos)
    {
        size_t Position = Haystack.find_first_of(Needle, StartPos);
        return (Position != tstring::npos ? Position : -1);
    }

    int PosFirstNotOf(tstring Needle, tstring Haystack, std::size_t StartPos)
    {
        std::size_t Position = Haystack.find_first_not_of(Needle, StartPos);
        return (Position != tstring::npos ? Position : -1);
    }

    int PosLastOf(tstring Needle, tstring Haystack, std::size_t StartPos)
    {
        size_t Position = Haystack.find_last_of(Needle, StartPos);
        return (Position != tstring::npos ? Position : -1);
    }

    int PosLastNotOf(tstring Needle, tstring Haystack, std::size_t StartPos)
    {
        std::size_t Position = Haystack.find_last_not_of(Needle, StartPos);
        return (Position != tstring::npos ? Position : -1);
    }

    tstring Mid(const tstring& Str, int Pos1, int Pos2)
    {
        tstring Temp;
        for(int I = Pos1; I < Pos2; ++I)
        {
            Temp += Str[I];
        }
        return Temp;
    }

    tstring Left(const tstring& Str, int Pos)
    {
        tstring Temp;
        for(int I = 0; I < Pos; ++I)
        {
            Temp += Str[I];
        }
        return Temp;
    }

    tstring& LeftTrim(tstring &Value)
    {
        Value.erase(Value.begin(), std::find_if(Value.begin(), Value.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return Value;
    }

    tstring& RightTrim(tstring &Value)
    {
        Value.erase(std::find_if(Value.rbegin(), Value.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), Value.end());
        return Value;
    }

    tstring &Trim(tstring &Value)
    {
        return LeftTrim(RightTrim(Value));
    }

    StringArray SplitString(tstring StrToSplit, int NumberOfPieces)
    {
        tstring Temp = StrToSplit;
        StringArray Result;
        while(Temp.size())
        {
            Result(Temp.substr(0, NumberOfPieces));
            Temp.erase(0, NumberOfPieces);
        }
        return Result;
    }

    StringArray SplitString(tstring StringToSplit, tstring Delimiter)
    {
        StringArray Result;
        std::size_t Pos = StringToSplit.find_first_of(Delimiter);
        while(Pos != tstring::npos)
        {
            if(Pos > 0)
            {
                Result(StringToSplit.substr(0, Pos));
            }
            StringToSplit = StringToSplit.substr(Pos + 1);
            Pos = StringToSplit.find_first_of(Delimiter);
        }
        if(StringToSplit.length() > 0)
        {
            Result(StringToSplit);
        }
        return Result;
    }

    tstring ConcatStrArrayToStr(StringArray Strings, tstring Delimiter)
    {
        tstring Result;
        for (std::size_t I = 0; I < Strings.Size() - 1; ++I)
            Result += Strings[I] + Delimiter;

        Result += Strings[Strings.Size() - 1];
        return Result;
    }

    int ConcatStrArrayToInt(StringArray Strings)
    {
        tstring Result;
        for (std::size_t I = 0; I < Strings.Size(); ++I)
            Result += Strings[I];

        return ToNumber<int>(Result);
    }

    IntegerArray StringArrayToIntArray(StringArray StrArrayToConvert)
    {
        IntegerArray Result;
        Result.SetLength(StrArrayToConvert.Size());
        for (std::size_t I = 0; I < StrArrayToConvert.Size(); ++I)
        {
            Result[I] = ToNumber<int>(StrArrayToConvert[I]);
        }
        return Result;
    }

    StringArray IntegerArrayToStrArray(IntegerArray IntArrayToConvert)
    {
        StringArray Result;
        Result.SetLength(IntArrayToConvert.Size());
        for (std::size_t I = 0; I < IntArrayToConvert.Size(); ++I)
        {
            Result[I] = IntArrayToConvert[I];
        }
        return Result;
    }

    tstring ConcatCharArrayToString(CharArray Chars, tstring Delimiter)
    {
        tstring Result;
        for (std::size_t I = 0; I < Chars.Size() - 1; ++I)
            Result += Chars[I] + Delimiter;

        Result += Chars[Chars.Size() - 1];
        return Result;
    }

    StringArray CharArrayToStrArray(CharArray CharArrayToConvert)
    {
        StringArray Result;
        Result.SetLength(CharArrayToConvert.Size());
        for (std::size_t I = 0; I < CharArrayToConvert.Size(); ++I)
        {
            Result[I] = CharArrayToConvert[I];
        }
        return Result;
    }

    IntegerArray CharArrayToIntArray(CharArray CharArrayToConvert)
    {
        IntegerArray Result;
        Result.SetLength(CharArrayToConvert.Size());
        for (std::size_t I = 0; I < CharArrayToConvert.Size(); ++I)
        {
            Result[I] = Ord(CharArrayToConvert[I]);
        }
        return Result;
    }

    CharArray IntegerArrayToCharArray(IntegerArray IntArrayToConvert)
    {
        CharArray Result;
        Result.SetLength(IntArrayToConvert.Size());
        for (std::size_t I = 0; I < IntArrayToConvert.Size(); ++I)
        {
            Result[I] = Chr(IntArrayToConvert[I]);
        }
        return Result;
    }

    tstring Replace(tstring Text, tstring FindStr, tstring ReplacementString, ReplacementFlags Flags)
    {
        std::size_t Pos = 0;
        tstring TempStr = Text;
        tstring TempFind = FindStr;

        if (!Flags.rfReplaceAll)
        {
            Pos = Flags.rfIgnoreCase ? LowerCase(Text).find(LowerCase(FindStr)) : Text.find(FindStr);

            if (Pos != tstring::npos)
            {
                Text.replace(Pos, FindStr.size(), ReplacementString);
            }
        }
        else
        {
            if (Flags.rfIgnoreCase)
            {
                TempStr = LowerCase(Text);
                TempFind = LowerCase(FindStr);
            }

            while ((Pos = TempStr.find(TempFind, Pos)) != tstring::npos)
            {
                Text.replace(Pos, FindStr.size(), ReplacementString);
                TempStr.replace(Pos, FindStr.size(), ReplacementString);
            }
        }

        return Text;
    }

    template <typename charT, typename Traits, typename Allocator>
    std::vector<std::basic_string<charT, Traits, Allocator>> Explode(const std::basic_string<charT, Traits, Allocator>& s, charT delim)
    {
        std::vector<tstring> elems;
        tstringstream ss(s);
        tstring item;
        while(std::getline(ss, item, delim))
        {
            elems.emplace_back(item);
        }
        return elems;
    }

    tstring Implode(tstring Glue, StringArray Pieces)
    {
        tstring Result;
        int Len = Pieces.Size();

        if (Len < 0)
            return Result;

        Result = Pieces[0];
        for (int I = 1; I < Len; ++I)
            Result += Glue + Pieces[I];

        return Result;
    }

    tstring Implode(const tstring &Glue, const std::vector<tstring> &Pieces)
    {
        tstring Str;
        int Len = Pieces.size();
        for(int I = 0; I < Len; ++I)
        {
            Str += Pieces[I];
            if (I < (Len - 1))
                Str += Glue;
        }
        return Str;
    }

    StringArray Explode(tstring Del, tstring Str)
    {
        StringArray Result;
        int I = 1, II, LastPos = 1, StrLen = Str.size(), DelLen = Del.size(), ResultLen = 0;
        Result.SetLength(ResultLen);

        while (I <= ResultLen)
        {
            if (!((I + DelLen - 1) > StrLen))
            {
                for (II = 1; I < DelLen; ++I)
                    if (Str[I + II - 1] != Del[II])
                    {
                        break;
                    }
            }
            else
                break;
            I += 1;
        }
        ResultLen += 1;
        Result.SetLength(ResultLen);
        Result[ResultLen - 1] = Copy(Str, LastPos, StrLen - LastPos + 1);
        return Result;
    }

    std::string CompressString(const std::string& StringToCompress, int compressionlevel)
    {
        std::string Result;
        if (StringToCompress.empty())
            return Result;

        z_stream zs;
        std::memset(&zs, 0, sizeof(zs));

        if (deflateInit(&zs, compressionlevel) != Z_OK)
            throw(std::runtime_error("deflateInit failed while compressing."));

        zs.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(StringToCompress.data()));
        zs.avail_in = StringToCompress.size();

        int Success = 0;
        std::vector<char> Buffer(32768);

        Repeat
        zs.next_out = reinterpret_cast<Bytef*>(Buffer.data());
        zs.avail_out = Buffer.size();

        Success = deflate(&zs, Z_FINISH);

        if (Result.size() < zs.total_out)
        {
            Result.append(Buffer.data(), zs.total_out - Result.size());
        }
        Until(Success != Z_OK);

        deflateEnd(&zs);

        if (Success != Z_STREAM_END)
        {
            tostringstream OS;
            OS << _T("Exception during zlib compression: (") << Success << _T(")") << zs.msg;
            throw(std::runtime_error(std::string(OS.str().begin(), OS.str().end())));
        }

        return Result;
    }

    std::string DecompressString(const std::string& StringToDecompress)
    {
        std::string Result;
        if (StringToDecompress.empty())
            return Result;

        z_stream zs;
        std::memset(&zs, 0, sizeof(zs));

        if (inflateInit(&zs) != Z_OK)
            throw(std::runtime_error("inflateInit failed while decompressing."));

        zs.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(StringToDecompress.data()));
        zs.avail_in = StringToDecompress.size();

        int Success = 0;
        std::vector<char> Buffer(32768);

        Repeat
        zs.next_out = reinterpret_cast<Bytef*>(Buffer.data());
        zs.avail_out = Buffer.size();

        Success = inflate(&zs, 0);

        if (Result.size() < zs.total_out)
        {
            Result.append(Buffer.data(), zs.total_out - Result.size());
        }
        Until(Success != Z_OK);

        inflateEnd(&zs);

        if (Success != Z_STREAM_END)
        {
            tostringstream OS;
            OS << _T("Exception during zlib decompression: (") << Success << _T(")") << zs.msg;
            throw(std::runtime_error(std::string(OS.str().begin(), OS.str().end())));
        }

        return Result;
    }

    bool StringsEqual(tstring Str1, tstring Str2, bool CaseSensitive)
    {
        if (Str1.size() != Str2.size()) return false;

        if (!CaseSensitive)
        {
            Str1 = LowerCase(Str1);
            Str2 = LowerCase(Str2);
        }

        for (std::size_t I = 0; I < Str1.size(); ++I)
        {
            if (Str1[I] != Str2[I])
                return false;
        }
        return true;
    }

    tstring ExtractFromString(tstring String, tstring WhatToExtract)
    {
        CharArray Range;
        tstring Result;

        if (StringsEqual(WhatToExtract, _T("Numbers"), false))
        {
            for (TCHAR I = _T('0'); I <= _T('9'); ++I)
                Range(I);
        }
        else if (StringsEqual(WhatToExtract, _T("Letters"), false))
        {
            for (TCHAR I = _T('A'); I <= _T('z'); ++I)
                if (!((I > 'Z') && (I < 'a')))
                    Range(I);
        }
        else if (StringsEqual(WhatToExtract, _T("Others"), false))
        {
            for (std::uint32_t I = 0; I <= 255; ++I)
                if (!(((I >= 47) && (I <= 58)) || ((I >= 65) && (I <= 90)) || ((I >= 97) && (I <= 122))))
                    Range(I);
        }
        else
            throw(std::invalid_argument("Extract From String: " + std::string(WhatToExtract.begin(), WhatToExtract.end()) + " Is Not An Option!"));

        for (auto it = String.begin(); it != String.end(); ++it)
            if (Range.Contains(*it))
                Result += *it;

        return Result;
    }

    tstring HtmlDecode(tstring StringToDecode)
    {
        tstring HtmlReplacements[] = {_T("\""), _T("\""), _T("'"), _T("'"), _T("&"), _T("&"), _T("<"), _T("<"), _T(">"), _T(">"), _T("\""), _T("'"), _T("&"), _T("<"), _T(">")};
        tstring HtmlChars[] = {_T("& #34;"), _T("&quot;"), _T("& #39;"), _T("&apos;"), _T("& #38;"), _T("&amp;"), _T("& #60;"), _T("&lt;"), _T("& #62;"), _T("&gt;"), _T("&34;"), _T("&39;"), _T("&38;"), _T("&60;"), _T("&62;")};

        std::size_t Found;
        for(int I = 0; I < 15; ++I)
        {
            do
            {
                Found = StringToDecode.find(HtmlChars[I]);
                if (Found != tstring::npos)
                    StringToDecode.replace(Found, HtmlChars[I].size(), HtmlReplacements[I]);
            }
            while(Found != tstring::npos);
        }

        return StringToDecode;
    }
}

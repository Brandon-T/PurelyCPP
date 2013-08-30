// *** ADDED BY HEADER FIXUP ***
#include <algorithm>
// *** END ***
#include "Base64.hpp"

namespace cxx
{
    tstring EncodeBase64(tstring Data)
    {
        tstring Binary = tstring();
        tstring Result = tstring();

        for (auto it = Data.begin(); it != Data.end(); ++it)
        {
            Binary += DecimalToBinary(*it, 8);
        }

        for (std::size_t I = 0; I < Binary.size(); I += 6)
        {
            Result += Base64Chars[BinaryToDecimal(Pad(Copy(Binary, I, 6), 6, _T("0"), false))];
            if (I == 0) ++I;
        }

        if (Result.size() % 4)
        {
            Result.resize(Result.size() + 4 - Result.size() % 4, '=');
        }

        return Result;
    }

    tstring DecodeBase64(tstring Data)
    {
        tstring Binary = tstring();
        tstring Result = tstring();

        for (std::size_t I = Data.size(); I > 0; --I)
        {
            if (Data[I - 1] != '=')
            {
                tstring Characters = Copy(Data, 0, I);

                for (auto it = Characters.begin(); it != Characters.end(); ++it)
                    Binary += DecimalToBinary(Base64Chars.find(*it), 6);
                break;
            }
        }

        for (std::size_t I = 0; I < Binary.size(); I += 8)
        {
            Result += static_cast<TCHAR>(BinaryToDecimal(Copy(Binary, I, 8)));
            if (I == 0) ++I;
        }

        return Result;
    }
}

/*tstring EncodeB64Chars(tstring StringToEncode)
{
    tstring Binaries, Result;
    std::size_t STE_Size = StringToEncode.size();
    if(STE_Size)
    {
        for (std::size_t I = 0; I < STE_Size; ++I)
            Binaries += DecToBinStr(Ord(StringToEncode[I]), 8);

        while(Binaries.size())
        {
            Result += Base64Chars[BinToDecStr(Binaries.substr(0, 6))];
            Binaries.erase(0, 6);
        }
    }
    return Result;
}

tstring DecodeB64Chars(tstring StringToDecode)
{
    tstring Binaries, Result;
    std::size_t STE_Size = StringToDecode.size();
    if(STE_Size)
    {
        for (std::size_t I = 0; I < STE_Size - 1; ++I)
            Binaries += DecToBinStr(Base64Chars.find(StringToDecode[I]), 6);
        Binaries += DecToBinStr(Base64Chars.find(StringToDecode[STE_Size - 1]), 8 - ((STE_Size - 1) * 6) % 8);

        while(Binaries.size())
        {
            Result += Chr(BinToDecStr(Binaries.substr(0,8)));
            Binaries.erase(0,8);
        }
    }
    return Result;
}

tstring EncodeB64(tstring StringToEncode)
{
    tstring Result;
    std::size_t STE_Size = StringToEncode.size();
    if(STE_Size)
    {
        StringArray Binaries;

        for (std::size_t I = 0; I < STE_Size; ++I)
            Binaries(DecToBinStr(Ord(StringToEncode[I]), 8));

        Binaries = SplitString(ConcatStrArrayToStr(Binaries), 6);

        for (std::size_t I = 0; I < Binaries.Size(); ++I)
        {
            Binaries[I] = BinToDec(Binaries[I]);
        }
        for (std::size_t I = 0; I < Binaries.Size(); ++I)
            Result += Base64Chars[StringArrayToIntArray(Binaries)[I]];
    }
    return Result;
}

tstring DecodeB64(tstring StringToDecode)
{
    tstring Result;
    std::size_t STE_Size = StringToDecode.size();
    if(STE_Size)
    {
        StringArray Binaries;

        for (std::size_t I = 0; I < STE_Size - 1; ++I)
            Binaries(DecToBinStr(Base64Chars.find(StringToDecode[I]), 6));
        Binaries(DecToBinStr(Base64Chars.find(StringToDecode[STE_Size - 1]), 8 - ((STE_Size - 1) * 6) % 8));

        Binaries = SplitString(ConcatStrArrayToStr(Binaries), 8);

        for (std::size_t I = 0; I < Binaries.Size(); ++I)
        {
            Binaries[I] = BinToDec(Binaries[I]);
        }

        for (std::size_t I = 0; I < Binaries.Size(); ++I)
            Result += Chr(StringArrayToIntArray(Binaries)[I]);
    }

    return Result;
}

tstring EncodeB64X(tstring StringToEncode)
{
    tstring Binaries, Result;
    std::size_t STE_Size = StringToEncode.size();
    if(STE_Size)
    {
        for (std::size_t I = 0; I < STE_Size; ++I)
            Binaries += DecToBinStr(Ord(StringToEncode[I]), 8);

        while(Binaries.size())
        {
            Result += Base64Chars[BinToDecStr(Binaries.substr(0, 6))];
            Binaries.erase(0, 6);
        }
    }
    return Result;
}

tstring DecodeB64X(tstring StringToEncode)
{
    tstring Binaries, Result;
    std::size_t STE_Size = StringToEncode.size();
    if(STE_Size)
    {
        for (std::size_t I = 0; I < STE_Size - 1; ++I)
            Binaries += DecToBinStr(Base64Chars.find(StringToEncode[I]), 6);
        Binaries += DecToBinStr(Base64Chars.find(StringToEncode[STE_Size - 1]), 8 - ((STE_Size - 1) * 6) % 8);

        while(Binaries.size())
        {
            Result += Chr(BinToDecStr(Binaries.substr(0, 8)));
            Binaries.erase(0, 8);
        }
    }
    return Result;
}*/

// *** ADDED BY HEADER FIXUP ***
#include <algorithm>
#include <cassert>
// *** END ***
#include "Mathematics.hpp"

namespace cxx
{
    int ConcatIntArrayToInt(IntegerArray Integers)
    {
        tstringstream SS;
        for (std::size_t I = 0; I < Integers.Size(); ++I)
        {
            SS << Integers[I];
        }
        assert(SS.str().size() <= 10);
        return _tcstol(SS.str().c_str(), nullptr, 10);
    }

    tstring ConcatIntArrayToStr(IntegerArray Integers, tstring Delimiter)
    {
        tstringstream SS;
        for (std::size_t I = 0; I < Integers.Size() - 1; ++I)
            SS << Integers[I] << Delimiter;

        SS << Integers[Integers.Size() - 1];
        return SS.str();
    }

    long Fibonachi(std::uint64_t Number)
    {
        return Number <= 1 ? Number : Fibonachi(Number - 1) + Fibonachi(Number - 2);
    }

    int ReverseNumber(int Number)
    {
        int Sum = 0;
        while (Number)
        {
            Sum *= 10;
            Sum += Number % 10;
            Number /= 10;
        }
        return Sum;
    }

    tstring NumberToRadix(std::uint32_t Value, std::uint32_t Base, std::uint32_t Padding)
    {
        assert(Base >= 2 && Base <= 36);
        static TCHAR const Digits[] = _T("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        tstring Result;
        while (Value != 0)
        {
            Result += Digits[Value % Base];
            Value /= Base;
        }

        while (Result.size() < Padding)
        {
            Result += _T('0');
        }

        std::reverse(Result.begin(), Result.end());
        return Result;
    }

    tstring DecimalToBinary(int Value, int Padding)
    {
        tstring Result = tstring();

        for (int I = Padding; I > 0; --I)
        {
            Result += (Value & (1 << (I - 1))) ? _T('1') : _T('0');
        }

        return Result;
    }

    /*int DecimalToBinary(int Value, int Padding = 8)
    {
        int Bin = 0;

        for (int I = 1, Pos = 1; I < (Padding + 1); ++I, Pos *= 10)
        {
            Bin += ((Value >> I - 1) & 1) * Pos;
        }
        return Bin;
    }*/

    int BinaryToDecimal(tstring Value)
    {
        int Dec = 0, Bin = ToNumber<int>(Value);
        bool Negative = ((Value.size() == 8) && (Value[0] == '1'));

        for (int I = 0; Bin > 0; ++I)
        {
            if(Bin % 10 == 1)
            {
                Dec += (1 << I);
            }
            Bin /= 10;
        }

        return Negative ? (Dec -= (1 << 8)) : Dec;
    }

    void ConvertTime(std::uint32_t Time, int &Hours, int &Minutes, int &Seconds)
    {
        Hours = (Time / (1000 * 60 * 60));
        Minutes = ((Time % (1000 * 60 * 60)) / (1000 * 60));
        Seconds = (((Time % (1000 * 60 * 60)) % (1000 * 60)) / 1000);
    }
}

#ifndef MATHEMATICS_HPP_INCLUDED
#define MATHEMATICS_HPP_INCLUDED

#include "Strings.hpp"

namespace cxx
{
    int ConcatIntArrayToInt(IntegerArray Integers);

    tstring ConcatIntArrayToStr(IntegerArray Integers, tstring Delimiter = tstring());

    long Fibonachi(std::uint64_t Number);

    int ReverseNumber(int Number);

    tstring NumberToRadix(std::uint32_t Value, std::uint32_t Base, std::uint32_t Padding = 8);

    tstring DecimalToBinary(int Value, int Padding = 8);

    int BinaryToDecimal(tstring Value);

    void ConvertTime(std::uint32_t Time, int &Hours, int &Minutes, int &Seconds);
}

#endif // MATHEMATICS_HPP_INCLUDED

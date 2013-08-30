/**  © 2012, Brandon T. All Rights Reserved.
  *
  *  This file is part of the PurelyCPlusPlus Library.
  *  You may use this file only for your personal, and non-commercial use.
  *  You may not modify or use the contents of this file for any purpose (other
  *  than as specified above) without the express written consent of the author.
  *  You may not reproduce, republish, post, transmit, publicly display,
  *  publicly perform, or distribute in print or electronically any of the contents
  *  of this file without express consent of rightful owner.
  *  This License is subject to change at any time without notice/warning.
  *
  *						Author : Brandon T.
  *						Contact: Brandon.T-@Live.com
  */

#ifndef DEFINES_HPP_INCLUDED
#define DEFINES_HPP_INCLUDED

#include "Unicode.hpp"
#include "Platforms.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <string>

/** Definitions **/
#define nl _T('\n')
#define BitSize(x) (sizeof(x)*8)
#define Chr(n) ((TCHAR)(n))
#define Ord(c) ((int)(std::uint8_t)(c))
#define BmPitch(bmWidth) (((std::uint32_t)(bmWidth + 3) & ~3))
#define BmStride(Pitch, bmBitCount) (((Pitch * bmBitCount) >> 3))

#define Repeat do{
#define Until(condition) }while(!(condition));

#define Write(Output) (tcout<<(Output))
#define WriteLn(Output) (tcout<<(Output)<<_T("\n"))

namespace cxx
{
    typedef struct
    {
        double X, Y, Z;
    } XYZ, *PXYZ;

    typedef struct
    {
        double Hue, Sat, Lum;
    } HSL, *PHSL;

    typedef struct
    {
        double L, A, B;
    } LAB, *PLAB;

    typedef union RGBA
    {
        std::uint32_t Colour;
        struct
        {
            std::uint8_t B, G, R, A;
        };
    } *PRGB;


    bool Odd(int Value);

    XYZ Xyz(double X, double Y, double Z);

    HSL Hsl(double Hue, double Sat, double Lum);

    LAB Lab(double L, double A, double B);

    RGBA Rgba(std::uint32_t R, std::uint32_t G, std::uint32_t B);

    RGBA Rgba(std::uint32_t Colour);

    std::uint32_t ColourSwap(std::uint32_t Colour);

    RGBA ColourSwap(RGBA Rgba);

    void ColourSwap(std::uint8_t* Buffer, int BufferSize, int BitsPerPixel);

    void StreamFlags(std::ios_base& Stream);

    TCHAR ToUpper(TCHAR C);

    TCHAR ToLower(TCHAR C);

    tstring ToUpperCase(tstring S);

    tstring ToLowerCase(tstring S);

    tostream& operator << (tostream& Str, const RGBA &Rgba);

    tostream& operator << (tostream& Str, const HSL &Hsl);

    tostream& operator << (tostream& Str, const XYZ &Xyz);

    bool SimilarColours(RGBA FirstCol, RGBA SecondCol, int Tol);

    tstring ErrorMessage(std::uint32_t Error, bool Throw = false);

    template <typename T>
    T ToNumber(const tstring &Text)
    {
        tistringstream SS(Text);
        T Result;
        return (SS >> Result ? Result : 0);
    }

    template <typename T>
    inline T ReadPointer(TCHAR* &Pointer)
    {
        T Result = *(reinterpret_cast<T*>(Pointer));
        Pointer += sizeof(T) / sizeof(TCHAR);
        return Result;
    }

    template <typename T>
    inline void WritePointer(TCHAR* &Pointer, const T& Value)
    {
        *(reinterpret_cast<T*>(Pointer)) = Value;
        Pointer += sizeof(T) / sizeof(TCHAR);
    }

    template<class BidirectionalIterator>
    inline void Reverse(BidirectionalIterator first, BidirectionalIterator last)
    {
        while ((first != last) && (first != --last))
            std::swap(*first++, *last);
    }

    template <typename T>
    bool TryParse(tstring input, T &var)
    {
        static const tstring ws(_T(" \t\f\v\n\r"));
        std::size_t pos = input.find_last_not_of(ws);

        if (pos != tstring::npos)
            input.erase(pos + 1);
        else input.clear();

        tstringstream buffer(input);
        return buffer >> var && buffer.eof();
    }
}

#endif // DEFINES_HPP_INCLUDED

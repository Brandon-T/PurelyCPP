#include "Defines.hpp"

namespace cxx
{
    bool Odd(int Value)
    {
        return (Value & 1);
    }

    void StreamFlags(std::ios_base& Stream)
    {
        Stream.flags(std::ios::boolalpha);
    }

    TCHAR ToUpper(TCHAR C)
    {
        return _totupper(C);
    }

    TCHAR ToLower(TCHAR C)
    {
        return _totlower(C);
    }

    tstring ToUpperCase(tstring S)
    {
        for (std::size_t I = 0; I < S.size(); ++I)
        {
            S[I] = _totupper(S[I]);
        }
        return S;
    }

    tstring ToLowerCase(tstring S)
    {
        for (std::size_t I = 0; I < S.size(); ++I)
        {
            S[I] = _totlower(S[I]);
        }
        return S;
    }

    tostream& operator << (tostream& Str, const RGBA &Rgba)
    {
        return Str << _T("R: ") << (int)Rgba.R << _T(", G: ") << (int)Rgba.G << _T(", B: ") << (int)Rgba.B;
    }

    tostream& operator << (tostream& Str, const HSL &Hsl)
    {
        return Str << _T("H: ") << Hsl.Hue << _T(", S: ") << Hsl.Sat << _T(", L: ") << Hsl.Lum;
    }

    tostream& operator << (tostream& Str, const XYZ &Xyz)
    {
        return Str << _T("X: ") << Xyz.X << _T(", Y: ") << Xyz.Y << _T(", Z: ") << Xyz.Z;
    }

    XYZ Xyz(double X, double Y, double Z)
    {
        return {X, Y, Z};
    }

    HSL Hsl(double Hue, double Sat, double Lum)
    {
        return {Hue, Sat, Lum};
    }

    LAB Lab(double L, double A, double B)
    {
        return {L, A, B};
    }

    RGBA Rgba(std::uint32_t R, std::uint32_t G, std::uint32_t B)
    {
        return {((R << 16) & 0x00FF0000) | ((G << 8) & 0x0000FF00) | (B & 0x000000FF)};
    }

    RGBA Rgba(std::uint32_t Colour)
    {
        return {((Colour & 0xFF000000) | ((Colour & 0xFF0000) >> 16) | (Colour & 0x00FF00) | ((Colour & 0x0000FF) << 16))};
    }

    std::uint32_t ColourSwap(std::uint32_t Colour)
    {
        return ((Colour & 0xFF000000) | ((Colour & 0xFF0000) >> 16) | (Colour & 0x00FF00) | ((Colour & 0x0000FF) << 16));
    }

    RGBA ColourSwap(RGBA Rgba)
    {
        //return (((Colour & 0xFF) << 16) + (((Colour & 0x00FF00) >> 8) << 8) + ((Colour & 0xFF0000) >> 16));
        return {((Rgba.Colour & 0xFF000000) | ((Rgba.Colour & 0xFF0000) >> 16) | (Rgba.Colour & 0x00FF00) | ((Rgba.Colour & 0x0000FF) << 16))};
    }

    void ColourSwap(std::uint8_t* Buffer, int BufferSize, int BitsPerPixel)
    {
        for(int I = 0; I < BufferSize; I += (BitsPerPixel / 8))
        {
            Buffer[I] ^= Buffer[I + 2] ^= Buffer[I] ^= Buffer[I + 2];
        }
    }

    bool SimilarColours(RGBA FirstCol, RGBA SecondCol, int Tol)
    {
        return ((FirstCol.R - SecondCol.R) * (FirstCol.R - SecondCol.R) + (FirstCol.G - SecondCol.G) * (FirstCol.G - SecondCol.G) + (FirstCol.B - SecondCol.B) * (FirstCol.B - SecondCol.B)) <= (Tol * Tol);
    }

    tstring ErrorMessage(std::uint32_t Error, bool Throw)
    {
        LPTSTR lpMsgBuf = nullptr;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, Error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPTSTR>(&lpMsgBuf), 0, nullptr);
        if (Throw)
        {
            tstring Buffer(lpMsgBuf);
            throw std::runtime_error(std::string(Buffer.begin(), Buffer.end()));
        }
        return lpMsgBuf;
    }
}

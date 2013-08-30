#ifndef IMAGEFINDER_HPP_INCLUDED
#define IMAGEFINDER_HPP_INCLUDED

#include "Images.hpp"

namespace cxx
{
    class ImageFinder
    {
        private:
            int CTSValue;
            double TMod, HueMod, SatMod;
            Image* TargetImage;

        protected:
            bool (ImageFinder::*CTS) (RGBA FirstCol, RGBA SecondCol, int Tol);

            bool CTSN(RGBA FirstCol, RGBA SecondCol, int Tol);
            bool CTS0(RGBA FirstCol, RGBA SecondCol, int Tol);
            bool CTS1(RGBA FirstCol, RGBA SecondCol, int Tol);
            bool CTS2(RGBA FirstCol, RGBA SecondCol, int Tol);
            bool CTS3(RGBA FirstCol, RGBA SecondCol, int Tol);

            void ValidateRange(int X1, int Y1, int X2, int Y2);

        public:
            ImageFinder();
            ~ImageFinder();

            ImageFinder(const ImageFinder& ImgFinder) = delete;

            ImageFinder& operator = (const ImageFinder& ImgFinder) = delete;

            void SetTargetImage(Image IMG);

            void Reset();

            int GetColourToleranceSpeed();

            void SetColourToleranceSpeed(int Value);

            void GetSpeed2Modifiers(double &HueMod, double &SatMod);

            void SetSpeed2Modifiers(double HueMod, double SatMod);

            double GetSpeed3Modifier();

            void SetSpeed3Modifier(double TMod);

            bool SimilarColours(RGBA FirstColour, RGBA SecondColour, int Tolerance);

            bool SimilarColours(std::uint32_t FirstColour, std::uint32_t SecondColour, int Tolerance);

            std::uint32_t CountColour(RGBA Colour, int X1, int Y1, int X2, int Y2);

            std::uint32_t CountColourTolerance(RGBA Colour, int X1, int Y1, int X2, int Y2, int Tolerance);

            bool FindColour(int &X, int &Y, RGBA Colour, int X1, int Y1, int X2, int Y2);

            bool FindColours(PointArray &Points, RGBA Colour, int X1, int Y1, int X2, int Y2);

            bool FindColourTolerance(int &X, int &Y, RGBA Colour, int X1, int Y1, int X2, int Y2, int Tolerance);

            bool FindColoursTolerance(PointArray &Points, RGBA Colour, int X1, int Y1, int X2, int Y2, int Tolerance);

            bool FindImage(Image ImageToFind, int &X, int &Y);

            bool FindImageIn(Image ImageToFind, int &X, int &Y, int X1, int Y1, int X2, int Y2);

            bool FindImageToleranceIn(Image ImageToFind, int &X, int &Y, int X1, int Y1, int X2, int Y2, int Tolerance);
    };
}

#endif // IMAGEFINDER_HPP_INCLUDED


/*
std::vector<std::vector<RGBA>::iterator> CalculateRowPtrs(Bitmap& BMP)
{
    std::vector<std::vector<RGBA>::iterator> Result;
    for (int I = 0; I < BMP.Height() - 1; ++I)
        Result.push_back(BMP.PixelsBegin() + BMP.Width() * I);

    return Result;
}

std::vector<std::vector<bool>> CalculateBitmapSkipCoords(Bitmap& BMP)
{
    std::vector<RGBA>::iterator Ptr = BMP.PixelsBegin();
    std::vector<std::vector<bool>> Result(BMP.Height(), std::vector<bool>(BMP.Width()));

    for (int Y = 0; Y < BMP.Height() - 1; ++Y)
    {
        for (int X = 0; X < BMP.Width() - 1; ++X)
        {
            if ((Ptr->RGBA.R == 0) && (Ptr->RGBA.G == 0) && (Ptr->RGBA.B == 0))
                Result[Y][X] = true;
            else
                Result[Y][X] = false;
            ++Ptr;
        }
    }
    return Result;
}
*/

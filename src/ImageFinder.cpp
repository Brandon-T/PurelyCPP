// *** ADDED BY HEADER FIXUP ***
#include <cstdlib>
#include <stdexcept>
// *** END ***
#include "ImageFinder.hpp"

namespace cxx
{
    void ImageFinder::SetTargetImage(Image IMG)
    {
        delete TargetImage;
        TargetImage = new Image(IMG);
    }

    ImageFinder::~ImageFinder()
    {
        delete TargetImage;
        this->TargetImage = nullptr;
    }

    ImageFinder::ImageFinder() : CTSValue(1), TMod(4.0), HueMod(0.2), SatMod(0.2), TargetImage(nullptr), CTS(&ImageFinder::CTS1) {}

    void ImageFinder::Reset()
    {
        CTSValue = 1;
        CTS = &ImageFinder::CTS1;
        TMod = 4.0;
        HueMod = 0.2;
        SatMod = 0.2;
    }

    int ImageFinder::GetColourToleranceSpeed()
    {
        return this->CTSValue;
    }

    void ImageFinder::SetColourToleranceSpeed(int Value)
    {
        switch (Value)
        {
            case -1:
                CTSValue = -1;
                CTS = &ImageFinder::CTSN;
                break;
            case 0:
                CTSValue = 0;
                CTS = &ImageFinder::CTS0;
                break;
            case 1:
                CTSValue = 1;
                CTS = &ImageFinder::CTS1;
                break;
            case 2:
                CTSValue = 2;
                CTS = &ImageFinder::CTS2;
                break;
            case 3:
                CTSValue = 3;
                CTS = &ImageFinder::CTS3;
                break;
            default:
                CTSValue = 1;
                CTS = &ImageFinder::CTS1;
                break;
        }
    }

    void ImageFinder::GetSpeed2Modifiers(double &HueMod, double &SatMod)
    {
        HueMod = this->HueMod;
        SatMod = this->SatMod;
    }

    void ImageFinder::SetSpeed2Modifiers(double HueMod, double SatMod)
    {
        this->HueMod = HueMod;
        this->SatMod = SatMod;
    }

    double ImageFinder::GetSpeed3Modifier()
    {
        return TMod;
    }

    void ImageFinder::SetSpeed3Modifier(double TMod)
    {
        this->TMod = TMod;
    }

    bool ImageFinder::SimilarColours(RGBA FirstColour, RGBA SecondColour, int Tolerance)
    {
        return (this->*ImageFinder::CTS)(FirstColour, SecondColour, Tolerance);
    }

    bool ImageFinder::SimilarColours(std::uint32_t FirstColour, std::uint32_t SecondColour, int Tolerance)
    {
        return (this->*ImageFinder::CTS)(Rgba(FirstColour), Rgba(SecondColour), Tolerance);
    }

    bool ImageFinder::CTSN(RGBA FirstCol, RGBA SecondCol, int Tol)
    {
        return (FirstCol.Colour == SecondCol.Colour);
    }

    bool ImageFinder::CTS0(RGBA FirstCol, RGBA SecondCol, int Tol)
    {
        return std::abs(FirstCol.R - SecondCol.R) <= Tol && std::abs(FirstCol.G - SecondCol.G) <= Tol && std::abs(FirstCol.B - SecondCol.B) <= Tol;
    }

    bool ImageFinder::CTS1(RGBA FirstCol, RGBA SecondCol, int Tol)
    {
        return ((FirstCol.R - SecondCol.R) * (FirstCol.R - SecondCol.R) + (FirstCol.G - SecondCol.G) * (FirstCol.G - SecondCol.G) + (FirstCol.B - SecondCol.B) * (FirstCol.B - SecondCol.B)) <= (Tol * Tol);
    }

    bool ImageFinder::CTS2(RGBA FirstCol, RGBA SecondCol, int Tol)
    {
        static HSL HFirstCol = Hsl(0), HSecondCol = Hsl(0);
        if (FirstCol.Colour != 0)
        {
            HFirstCol = Hsl(FirstCol);
        }

        if (SecondCol.Colour != 0)
        {
            HSecondCol = Hsl(SecondCol);
        }

        return (std::fabs(HSecondCol.Hue - HFirstCol.Hue) <= (Tol * HueMod)) && (std::fabs(HSecondCol.Sat - HFirstCol.Sat) <= (Tol * SatMod));
    }

    bool ImageFinder::CTS3(RGBA FirstCol, RGBA SecondCol, int Tol)
    {
        static LAB LabFirstCol = Lab(0), LabSecondCol = Lab(0);
        if (FirstCol.Colour != 0)
        {
            LabFirstCol = Lab(Xyz(FirstCol));
        }

        if (SecondCol.Colour != 0)
        {
            LabSecondCol = Lab(Xyz(SecondCol));
        }

        double L = (LabSecondCol.L - LabFirstCol.L);
        double A = (LabSecondCol.A - LabFirstCol.A);
        double B = (LabSecondCol.B - LabFirstCol.B);

        return ((L * L) + (A * A) + (B * B)) <= std::ceil(std::sqrt(Tol * TMod));
    }

    void ImageFinder::ValidateRange(int X1, int Y1, int X2, int Y2)
    {
        if (X1 < 0 || Y1 < 0)
        {
            throw std::invalid_argument("Error: X1 and Y1 must be greater than Zero.");
        }

        if (X2 < X1)
        {
            throw std::invalid_argument("Error: X2 < X1. X2 must be greater than X1.");
        }

        if (Y2 < Y1)
        {
            throw std::invalid_argument("Error: Y2 < Y1. Y2 must be greater than Y1.");
        }

        if (X2 > TargetImage->Width())
        {
            throw std::out_of_range("Error: X2 out of bounds. X2 must be within the search area.");
        }

        if (Y2 > TargetImage->Height())
        {
            throw std::out_of_range("Error: Y2 out of bounds. Y2 must be within the search area.");
        }
    }

    std::uint32_t ImageFinder::CountColour(RGBA Colour, int X1, int Y1, int X2, int Y2)
    {
        int TemporaryCTS = this->CTSValue;
        SetColourToleranceSpeed(-1);
        std::uint32_t Result = CountColourTolerance(Colour, X1, Y1, X2, Y2, 0);
        SetColourToleranceSpeed(TemporaryCTS);
        return Result;
    }

    std::uint32_t ImageFinder::CountColourTolerance(RGBA Colour, int X1, int Y1, int X2, int Y2, int Tolerance)
    {
        int Result = 0;
        ValidateRange(X1, Y1, X2, Y2);

        for (int I = Y1; I < Y2; ++I)
        {
            for (int J = X1; J < X2; ++J)
            {
                if (SimilarColours(Colour, TargetImage->GetPixel(J, I), Tolerance))
                {
                    ++Result;
                }
            }
        }

        return Result;
    }

    bool ImageFinder::FindColour(int &X, int &Y, RGBA Colour, int X1, int Y1, int X2, int Y2)
    {
        int TemporaryCTS = CTSValue;
        SetColourToleranceSpeed(-1);
        bool Result = FindColourTolerance(X, Y, Colour, X1, Y1, X2, Y2, 0);
        SetColourToleranceSpeed(TemporaryCTS);
        return Result;
    }

    bool ImageFinder::FindColours(PointArray &Points, RGBA Colour, int X1, int Y1, int X2, int Y2)
    {
        int TemporaryCTS = CTSValue;
        SetColourToleranceSpeed(-1);
        bool Result = FindColoursTolerance(Points, Colour, X1, Y1, X2, Y2, 0);
        SetColourToleranceSpeed(TemporaryCTS);
        return Result;
    }

    bool ImageFinder::FindColourTolerance(int &X, int &Y, RGBA Colour, int X1, int Y1, int X2, int Y2, int Tolerance)
    {
        ValidateRange(X1, Y1, X2, Y2);
        for (int I = Y1; I < Y2; ++I)
        {
            for (int J = X1; J < X2; ++J)
            {
                if (SimilarColours(TargetImage->GetPixel(J, I), Colour, Tolerance))
                {
                    X = J;
                    Y = I;
                    return true;
                }
            }
        }
        return false;
    }

    bool ImageFinder::FindColoursTolerance(PointArray &Points, RGBA Colour, int X1, int Y1, int X2, int Y2, int Tolerance)
    {
        ValidateRange(X1, Y1, X2, Y2);
        for (int I = Y1; I < Y2; ++I)
        {
            for (int J = X1; J < X2; ++J)
            {
                if (SimilarColours(TargetImage->GetPixel(J, I), Colour, Tolerance))
                    Points(Point(J, I));
            }
        }
        return (!Points.Empty());
    }

    bool ImageFinder::FindImage(Image ImageToFind, int &X, int &Y)
    {
        return FindImageIn(ImageToFind, X, Y, 0, 0, TargetImage->Width(), TargetImage->Height());
    }

    bool ImageFinder::FindImageIn(Image ImageToFind, int &X, int &Y, int X1, int Y1, int X2, int Y2)
    {
        int TemporaryCTS = CTSValue;
        bool Result = FindImageToleranceIn(ImageToFind, X, Y, X1, Y1, X2, Y2, 0);
        SetColourToleranceSpeed(TemporaryCTS);
        return Result;
    }

    bool ImageFinder::FindImageToleranceIn(Image ImageToFind, int &X, int &Y, int X1, int Y1, int X2, int Y2, int Tolerance)
    {
        ValidateRange(X1, Y1, X2, Y2);

        int dX = (X2 - X1) - (ImageToFind.Width() - 1);
        int dY = (Y2 - Y1) - (ImageToFind.Height() - 1);

        for (int I = 0; I < dY; ++I)
        {
            for (int J = 0; J < dX; ++J)
            {
                for (int YY = 0; YY < ImageToFind.Height(); ++YY)
                {
                    for (int XX = 0; XX < ImageToFind.Width(); ++XX)
                    {
                        if (ImageToFind.GetPixel(XX, YY).Colour != 0)
                        {
                            if (!SimilarColours(ImageToFind.GetPixel(XX, YY), TargetImage->GetPixel(XX + J, YY + I), Tolerance))
                            {
                                goto Skip;
                            }
                        }
                    }
                }

                X = J + X1;
                Y = I + Y1;
                return true;
Skip:
                continue;
            }
        }

        X = -1;
        Y = -1;
        return false;
    }
}

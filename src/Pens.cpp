// *** ADDED BY HEADER FIXUP ***
#include <algorithm>
// *** END ***
#include "Pens.hpp"

namespace cxx
{
    Pens::Pens(HDC hdc, std::uint32_t colour) : hDC(hdc), NewPen(CreatePen(PS_SOLID, 0, colour)), OldPen((HPEN)SelectObject (hDC, NewPen)) {}

    Pens::Pens(HDC hdc, std::uint32_t Style, std::uint32_t Width, std::uint32_t colour) : hDC(hdc), NewPen(CreatePen(Style, Width, colour)), OldPen((HPEN)SelectObject (hDC, NewPen)) {}

    Pens::Pens(Pens && P) : hDC(nullptr), NewPen(nullptr), OldPen(nullptr)
    {
        this->Swap(P);
    }

    Pens::~Pens()
    {
        SelectObject(hDC, OldPen);
        DeleteObject(NewPen);
    }

    Pens& Pens::operator = (Pens P)
    {
        P.Swap(*this);
        return *this;
    }

    void Pens::ColourPixel(Point ColourPoint)
    {
        SetPixel(hDC, ColourPoint.X, ColourPoint.Y, ColourPoint.Color);
    }

    void Pens::DrawLine(Point Begin, Point End)
    {
        MoveToEx (hDC, Begin.X, Begin.Y, nullptr);
        LineTo (hDC, End.X, End.Y);
    }

    void Pens::DrawRectangle(Box B)
    {
        Rectangle(hDC, B.X1, B.Y1, B.X2, B.Y2);
    }

    void Pens::DrawRoundRectangle(Box B, int Width, int Height)
    {
        RoundRect(hDC, B.X1, B.Y1, B.X2, B.Y2, Width, Height);
    }

    void Pens::DrawEllipse(Point UpperLeftBound, Point LowerRightBound)
    {
        Ellipse(hDC, UpperLeftBound.X, UpperLeftBound.Y, LowerRightBound.X, LowerRightBound.Y);
    }

    void Pens::DrawArcAngle(Point CenterPoint, std::uint32_t Radius, float StartAngle, float EndAngle)
    {
        AngleArc(hDC, CenterPoint.X, CenterPoint.Y, Radius, StartAngle, EndAngle);
    }

    void Pens::DrawArc(Point UpperLeftBound, Point LowerRightBound, Point ArcStartPoint, Point ArcEndPoint)
    {
        Arc(hDC, UpperLeftBound.X, UpperLeftBound.Y, LowerRightBound.X, LowerRightBound.Y, ArcStartPoint.X, ArcStartPoint.Y, ArcEndPoint.X, ArcEndPoint.Y);
    }

    void Pens::DrawArcTo(Point UpperLeftBound, Point LowerRightBound, Point ArcStartPoint, Point ArcEndPoint)
    {
        ArcTo(hDC, UpperLeftBound.X, UpperLeftBound.Y, LowerRightBound.X, LowerRightBound.Y, ArcStartPoint.X, ArcStartPoint.Y, ArcEndPoint.X, ArcEndPoint.Y);
    }

    void Pens::Swap(Pens& P) //throw()
    {
        std::swap(hDC, P.hDC);
        std::swap(NewPen, P.NewPen);
        std::swap(OldPen, P.OldPen);
    }
}

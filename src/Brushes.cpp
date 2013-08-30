#include "Brushes.hpp"

namespace cxx
{
    Brushes::Brushes(HDC hdc, std::uint32_t colour) : hDC(hdc), NewBrush(CreateSolidBrush(colour)), OldBrush((HBRUSH)SelectObject (hDC, NewBrush)) {}

    Brushes::Brushes(Brushes && B)  : hDC(nullptr), NewBrush(nullptr), OldBrush(nullptr)
    {
        this->Swap(B);
    }

    Brushes::~Brushes()
    {
        SelectObject(hDC, OldBrush);
        DeleteObject(NewBrush);
    }

    Brushes& Brushes::operator = (Brushes B)
    {
        B.Swap(*this);
        return *this;
    }

    void Brushes::ColourPixel(Point ColourPoint)
    {
        SetPixel(hDC, ColourPoint.X, ColourPoint.Y, ColourPoint.Color);
    }

    void Brushes::DrawLine(Point Begin, Point End)
    {
        MoveToEx (hDC, Begin.X, Begin.Y, nullptr);
        LineTo (hDC, End.X, End.Y);
    }

    void Brushes::DrawRectangle(Box B, bool Fill)           //bool Fill = false
    {
        if (!Fill)
        {
            DrawLine(Point(B.X1, B.Y1), Point(B.X2, B.Y1)); //Draw the Top.
            DrawLine(Point(B.X1, B.Y1), Point(B.X1, B.Y2)); //Draw the Left.
            DrawLine(Point(B.X2, B.Y1), Point(B.X2, B.Y2)); //Draw the Right.
            DrawLine(Point(B.X1, B.Y2), Point(B.X2, B.Y2)); //Draw the Bottom.
            ColourPixel(Point(B.X2, B.Y2, 0));  //Last Pixel.
        }
        else
            Rectangle(hDC, B.X1, B.Y1, B.X2, B.Y2);
    }

    void Brushes::DrawRoundRectangle(Box B, int Width, int Height)
    {
        RoundRect(hDC, B.X1, B.Y1, B.X2, B.Y2, Width, Height);
    }

    void Brushes::DrawEllipse(Point UpperLeftBound, Point LowerRightBound)
    {
        Ellipse(hDC, UpperLeftBound.X, UpperLeftBound.Y, LowerRightBound.X, LowerRightBound.Y);
    }

    void Brushes::DrawArcAngle(Point CenterPoint, std::uint32_t Radius, float StartAngle, float EndAngle)
    {
        AngleArc(hDC, CenterPoint.X, CenterPoint.Y, Radius, StartAngle, EndAngle);
    }

    void Brushes::DrawArc(Point UpperLeftBound, Point LowerRightBound, Point ArcStartPoint, Point ArcEndPoint)
    {
        Arc(hDC, UpperLeftBound.X, UpperLeftBound.Y, LowerRightBound.X, LowerRightBound.Y, ArcStartPoint.X, ArcStartPoint.Y, ArcEndPoint.X, ArcEndPoint.Y);
    }

    void Brushes::DrawArcTo(Point UpperLeftBound, Point LowerRightBound, Point ArcStartPoint, Point ArcEndPoint)
    {
        ArcTo(hDC, UpperLeftBound.X, UpperLeftBound.Y, LowerRightBound.X, LowerRightBound.Y, ArcStartPoint.X, ArcStartPoint.Y, ArcEndPoint.X, ArcEndPoint.Y);
    }

    void Brushes::Swap(Brushes& B) //throw()
    {
        std::swap(hDC, B.hDC);
        std::swap(NewBrush, B.NewBrush);
        std::swap(OldBrush, B.OldBrush);
    }
}

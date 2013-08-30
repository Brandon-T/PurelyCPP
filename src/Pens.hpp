#ifndef PENS_HPP_INCLUDED
#define PENS_HPP_INCLUDED

#include "Platforms.hpp"
#include "Types.hpp"

namespace cxx
{
    class Pens
    {
        private:
            HDC  hDC;
            HPEN NewPen;
            HPEN OldPen;
            void Swap(Pens& P);

        public:
            Pens(HDC hdc, std::uint32_t colour);
            Pens(HDC hdc, std::uint32_t Style, std::uint32_t Width, std::uint32_t colour);
            Pens(const Pens& P) = delete;
            Pens(Pens && P);
            ~Pens();

            Pens& operator = (const Pens& P) = delete;

            Pens& operator = (Pens P);

            void ColourPixel(Point ColourPoint);

            void DrawLine(Point Begin, Point End);

            void DrawRectangle(Box B);

            void DrawRoundRectangle(Box B, int Width, int Height);

            void DrawEllipse(Point UpperLeftBound, Point LowerRightBound);

            void DrawArcAngle(Point CenterPoint, std::uint32_t Radius, float StartAngle, float EndAngle);

            void DrawArc(Point UpperLeftBound, Point LowerRightBound, Point ArcStartPoint, Point ArcEndPoint);

            void DrawArcTo(Point UpperLeftBound, Point LowerRightBound, Point ArcStartPoint, Point ArcEndPoint);
    };
}

#endif // PENS_HPP_INCLUDED

#ifndef BRUSHES_HPP_INCLUDED
#define BRUSHES_HPP_INCLUDED

#include "Platforms.hpp"
#include "Types.hpp"

namespace cxx
{
    class Brushes
    {
        private:
            HDC     hDC;
            HBRUSH  NewBrush;
            HBRUSH  OldBrush;
            void Swap(Brushes& B);

        public:
            Brushes(HDC hdc, std::uint32_t colour);
            Brushes(const Brushes& B) = delete;
            Brushes(Brushes && B);
            ~Brushes();

            Brushes& operator = (const Brushes& B) = delete;

            Brushes& operator = (Brushes B);

            void ColourPixel(Point ColourPoint);

            void DrawLine(Point Begin, Point End);

            void DrawRectangle(Box B, bool Fill = false);

            void DrawRoundRectangle(Box B, int Width, int Height);

            void DrawEllipse(Point UpperLeftBound, Point LowerRightBound);

            void DrawArcAngle(Point CenterPoint, std::uint32_t Radius, float StartAngle, float EndAngle);

            void DrawArc(Point UpperLeftBound, Point LowerRightBound, Point ArcStartPoint, Point ArcEndPoint);

            void DrawArcTo(Point UpperLeftBound, Point LowerRightBound, Point ArcStartPoint, Point ArcEndPoint);
    };
}

#endif // BRUSHES_HPP_INCLUDED

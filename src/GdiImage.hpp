#ifndef GDIIMAGE_HPP_INCLUDED
#define GDIIMAGE_HPP_INCLUDED

#include "Unicode.hpp"
#include <windows.h>
#include <gdiplus.h>
#include "Types.hpp"

namespace cxx
{
#ifdef UNICODE
    class GdiImage
    {
        private:
            bool Initialized;
            Gdiplus::Image* Img = nullptr;

            static int Instances;
            static ULONG_PTR GDIToken;
            static Gdiplus::GdiplusStartupInput GDIStartInput;

        public:
            GdiImage(const tstring &ImageFile);
            GdiImage(const GdiImage &G) = delete;
            GdiImage(GdiImage && G) = delete;
            ~GdiImage();

            //operator Gdiplus::Image*() const;

            GdiImage& operator = (const GdiImage& G) = delete;
            GdiImage& operator = (GdiImage && G) = delete;

            void DrawTo(HWND Window, Point Location = Point(0, 0));
    };
#endif
}

#endif // GDIIMAGE_HPP_INCLUDED

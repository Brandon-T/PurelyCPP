#include "GdiImage.hpp"

namespace cxx
{
#ifdef UNICODE
    int GdiImage::Instances = 0;
    ULONG_PTR GdiImage::GDIToken = 0;
    Gdiplus::GdiplusStartupInput GdiImage::GDIStartInput = nullptr;

    GdiImage::~GdiImage()
    {
        delete Img;
        if (--Instances <= 0)
        {
            Gdiplus::GdiplusShutdown(GdiImage::GDIToken);
        }
    }

    GdiImage::GdiImage(const tstring &ImageFile) : Initialized(true)
    {
        ++Instances;
        if (!GdiImage::GDIToken)
        {
            Gdiplus::GdiplusStartup(&GdiImage::GDIToken, &GdiImage::GDIStartInput, nullptr);
        }
        Img = Gdiplus::Image::FromFile(ImageFile.c_str());
    }

//GdiImage::operator Gdiplus::Image*() const {return this->Img;}

    void GdiImage::DrawTo(HWND Window, Point Location)
    {
        HDC DC = GetDC(Window);
        Gdiplus::Graphics G(DC);
        G.DrawImage(Img, Location.X, Location.Y);
        ReleaseDC(Window, DC);
    }
#endif
}

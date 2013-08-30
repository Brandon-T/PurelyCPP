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

#ifndef IMAGES_HPP_INCLUDED
#define IMAGES_HPP_INCLUDED

#include <cmath>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include "Defines.hpp"
#include "Base64.hpp"
#include "Types.hpp"
#include "Libraries/LibPng/png.h"

namespace cxx
{
    XYZ Xyz(RGBA Rgba);
    RGBA Rgba(XYZ Xyz);
    HSL Hsl(RGBA Rgba);
    RGBA Rgba(HSL Hsl);
    LAB Lab(XYZ Xyz);
    XYZ Lab(LAB Lab);
    HSL Hsl(std::uint32_t Color);
    XYZ Xyz(std::uint32_t Color);
    LAB Lab(std::uint32_t Color);

    /** Image Class **/


    enum IMAGE_TYPE {GIF = 0, PNG, BMP, JPG, JPEG, TIFF, TGA};

    class Image
    {
        private:
            std::vector<RGBA> Pixels;
            BITMAPINFO Info;
            bool ImageCompressed;
            std::uint32_t width, height, size;
            BITMAPFILEHEADER bFileHeader;

            std::uint32_t BitsPerPixel, ImageType;
            int bitdepth, colortype, interlacetype, channels;
            static int ValidImage(std::uint8_t* ImageBytes);
            static void ReadFromStream(png_structp PngPointer, std::uint8_t* Data, std::size_t Length);
            static void WriteToStream(png_structp PngPointer, std::uint8_t* Data, std::size_t Length);

        protected:
            HDC DC;
            HBITMAP ImageHandle;
            void Swap(Image& Img);

        public:
            ~Image();
            Image(const Image& Img);
            Image(Image && Img);
            explicit Image(const char* FilePath);

            explicit Image(HBITMAP Bmp);
            explicit Image(std::uint16_t ResourceID);
            explicit Image(std::vector<std::uint8_t> &Pointer, int Width, int Height, std::uint32_t BitsPerPixel = 32, IMAGE_TYPE Value = BMP);
            explicit Image(const void* Pointer, int Width, int Height, std::uint32_t BitsPerPixel = 32, IMAGE_TYPE Value = BMP);
            explicit Image(int Width, int Height, std::uint32_t BitsPerPixel = 32);
            explicit Image(HWND Window, Box Area = Box(0, 0, 0, 0), std::uint32_t BitsPerPixel = 32);
            explicit Image(HDC hdc, Box Area = Box(0, 0, 0, 0), std::uint32_t BitsPerPixel = 32);

            bool Save(const char* FilePath, IMAGE_TYPE Value = BMP);

            Image& operator = (Image Img);

            HBITMAP ToHBitmap();

            void Draw(HWND Hwnd, HBITMAP hBmp = nullptr, int X = 0, int Y = 0, int Width = 0, int Height = 0, int SourceX = 0, int SourceY = 0, DWORD RasterType = SRCCOPY);

            void Draw(HDC hDC, HBITMAP hBmp = nullptr, int X = 0, int Y = 0, int Width = 0, int Height = 0, int SourceX = 0, int SourceY = 0, DWORD RasterType = SRCCOPY);

            tstring ToString();

            Image& FromString(tstring Data, std::uint32_t BitsPerPixel = 32);

            int Width() const;

            int Height() const;

            int Size() const;

            void Size(int& Width, int& Height) const;

            int GetBitsPerPixel() const;

            void SetBitsPerPixel(std::uint32_t Depth);

            RGBA& operator [](int I);

            const RGBA& operator [](int I) const;

            std::vector<RGBA>::iterator PixelsBegin();

            std::vector<RGBA>::const_iterator PixelsBegin() const;

            std::vector<RGBA>::iterator PixelsEnd();

            std::vector<RGBA>::const_iterator PixelsEnd() const;

            std::pair<std::vector<RGBA>::iterator, std::vector<RGBA>::iterator> PixelsRange();

            std::pair<std::vector<RGBA>::const_iterator, std::vector<RGBA>::const_iterator> PixelsRange() const;

            RGBA GetPixel(int X, int Y) const;

            void SetPixel(int X, int Y, RGBA Color);
    };

    /** Portable Bitmap Class **/

    class PBitmap
    {
        private:
            std::vector<RGBA> Pixels;
            std::uint32_t width, height;
            std::uint16_t BitsPerPixel;

        public:
            PBitmap(const char* FilePath);

            void Save(const char* FilePath);

            inline int Width() const
            {
                return width;
            }

            inline int Height() const
            {
                return height;
            }

            inline RGBA GetPixel(int X, int Y) const
            {
                return Pixels[Y * width + X];
            }

            inline void SetPixel(int X, int Y, RGBA Color)
            {
                Pixels[Y * width + X] = Color;
            }
    };

    /** Functions **/

//std::string BitmapToString(Bitmap Image);

//Bitmap BitmapFromString(std::string Data);

    void FlipImageBytes(void* In, void* Out, int width, int height, std::uint16_t Bpp = 32);
}


#endif // IMAGES_HPP_INCLUDED

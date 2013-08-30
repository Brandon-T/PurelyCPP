// *** ADDED BY HEADER FIXUP ***
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
// *** END ***
#include "Images.hpp"

namespace cxx
{
    XYZ Xyz(RGBA Rgba)
    {
        XYZ Result;
        double Red = (Rgba.R / 255.0);
        double Green = (Rgba.G / 255.0);
        double Blue = (Rgba.B / 255.0);

        Red = (Red > 0.04045) ? std::pow(((Red + 0.055) / 1.055), 2.4) * 100 : Red / 12.92;
        Green = (Green > 0.04045) ? std::pow(((Green + 0.055) / 1.055), 2.4) * 100.0 : Green / 12.92;
        Blue = (Blue > 0.04045) ? std::pow(((Blue + 0.055) / 1.055), 2.4) * 100.0 : Blue / 12.92;
        Result.X = Red * 0.4124 + Green * 0.3576 + Blue * 0.1805;
        Result.Y = Red * 0.2126 + Green * 0.7152 + Blue * 0.0722;
        Result.Z = Red * 0.0193 + Green * 0.1192 + Blue * 0.9505;
        return Result;
    }

    RGBA Rgba(XYZ Xyz)
    {
        RGBA Result;
        double X = Xyz.X / 100.0;
        double Y = Xyz.Y / 100.0;
        double Z = Xyz.Z / 100.0;

        double Red = X * 3.2406 + Y * -1.5372 + Z * -0.4986;
        double Green = X * -0.9689 + Y * 1.8758 + Z * 0.0415;
        double Blue = X * 0.0557 + Y * -0.2040 + Z * 1.0570;

        Red = (Red > 0.0031308) ? (1.055 * std::pow(Red, (1 / 2.4)) - 0.055) : 12.92 * Red;
        Green = (Green > 0.0031308) ? (1.055 * std::pow(Green, (1 / 2.4)) - 0.055) : 12.92 * Green;
        Blue = (Blue > 0.0031308) ? (1.055 * std::pow(Blue, (1 / 2.4)) - 0.055) : 12.92 * Blue;

        Result.R = static_cast<std::uint8_t>(std::round(Red * 255.0));
        Result.G = static_cast<std::uint8_t>(std::round(Green * 255.0));
        Result.B = static_cast<std::uint8_t>(std::round(Blue * 255.0));

        return Result;
    }

    HSL Hsl(RGBA Rgba)
    {
        HSL Result;
        double Red, Green, Blue;
        Red = Rgba.R / 255.0;
        Green = Rgba.G / 255.0;
        Blue = Rgba.B / 255.0;
double Max = Red > Blue ? Red > Green ? Red : Green : Blue > Green ? Blue : Green;
double Min = Red < Blue ? Red < Green ? Red : Green : Blue < Green ? Blue : Green;
        Result.Lum = (Max + Min) / 2.0;

        if(Max == Min)
            Result.Hue = Result.Sat = 0.0;
        else
        {
            double Delta = Max - Min;
            Result.Sat = Result.Lum > 0.5 ? Delta / (2.0 - Max - Min) : Delta / (Max + Min);
            if (Max == Red)
                Result.Hue = (Green - Blue) / Delta + (Green < Blue ? 6.0 : 0.0);
            else if(Max == Green)
                Result.Hue = (Blue - Red) / Delta + 2.0;
            else
                Result.Hue = (Red - Green) / Delta + 4.0;

            Result.Hue /= 6.0;
        }
        Result.Hue *= 100.0;
        Result.Sat *= 100.0;
        Result.Lum *= 100.0;
        return Result;
    }

    RGBA Rgba(HSL Hsl)
    {
        RGBA Result;
        double H = Hsl.Hue / 100.0;
        double S = Hsl.Sat / 100.0;
        double L = Hsl.Lum / 100.0;

        auto HSLToRGBHelper = [](double I, double J, double Hue) -> double
        {
            if (Hue < 0.0) Hue += 1.0;
            if (Hue > 1.0) Hue -= 1.0;
            if (Hue < (1.0 / 6.0))
                return std::round((I + (J - I) * 6.0 * Hue) * 255.0);
            else if (Hue < (1.0 / 2.0))
                return std::round(J * 255.0);
            else if (Hue < (2.0 / 3.0))
                return std::round((I + (J - I) * 6.0 * ((2.0 / 3.0) - Hue)) * 255.0);
            else
                return std::round(I * 255.0);
        };

        if (S == 0.0)
        {
            Result.R = Result.G = Result.B = (std::uint8_t)(L * 255.0);
        }
        else
        {
            double J = (L < 0.5) ? (L * (1.0 + S)) : ((L + S) - (S * L));
            double I = 2.0 * L - J;

            Result.R = static_cast<std::uint8_t>(HSLToRGBHelper(I, J, H + (1.0 / 3.0)));
            Result.G = static_cast<std::uint8_t>(HSLToRGBHelper(I, J, H));
            Result.B = static_cast<std::uint8_t>(HSLToRGBHelper(I, J, H - (1.0 / 3.0)));
        }
        return Result;
    }

    LAB Lab(XYZ Xyz)
    {
        double X = Xyz.X / 95.047;
        double Y = Xyz.Y / 100.000;
        double Z = Xyz.Z / 108.883;

        X = (X > 0.008856) ? std::pow(X, (1.0 / 3.0)) : (X * 7.787) + (16.0 / 116.0);
        Y = (Y > 0.008856) ? std::pow(Y, (1.0 / 3.0)) : (Y * 7.787) + (16.0 / 116.0);
        Z = (Z > 0.008856) ? std::pow(Z, (1.0 / 3.0)) : (Z * 7.787) + (16.0 / 116.0);

        return {((Y * 116.0) - 16.0), ((X - Y) * 500), ((Y - Z) * 200)};
    }

    XYZ Xyz(LAB Lab)
    {
        double Y = (Lab.L + 16.0) / 116.0;
        double X = ((Lab.A / 500.0) + Y);
        double Z = (Y - (Lab.B / 200.0));

        Y = (std::pow(Y, 3) > 0.008856) ? std::pow(Y, 3) : ((Y - (16.0 / 116.0)) / 7.787);
        X = (std::pow(X, 3) > 0.008856) ? std::pow(X, 3) : ((X - (16.0 / 116.0)) / 7.787);
        Z = (std::pow(Z, 3) > 0.008856) ? std::pow(Z, 3) : ((Z - (16.0 / 116.0)) / 7.787);

        return {(X * 95.047), (Y * 100.000), (Z * 108.883)};
    }

    HSL Hsl(std::uint32_t Colour)
    {
        return Hsl(Rgba(Colour));
    }
    XYZ Xyz(std::uint32_t Colour)
    {
        return Xyz(Rgba(Colour));
    }
    LAB Lab(std::uint32_t Colour)
    {
        return Lab(Xyz(Colour));
    }


    /** Image Class **/

    Image::~Image()
    {
        Pixels.clear();
        DeleteDC(DC);
        DeleteObject(ImageHandle);
        ImageHandle = nullptr;
    }

    int Image::ValidImage(std::uint8_t* ImageBytes)
    {
        const static std::vector<std::uint8_t> GIFBytesOne = { 0x47, 0x49, 0x46, 0x38, 0x37, 0x61 };
        const static std::vector<std::uint8_t> GIFBytesTwo = { 0x47, 0x49, 0x46, 0x38, 0x39, 0x61 };
        const static std::vector<std::uint8_t> PNGBytes = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
        const static std::vector<std::uint8_t> BMPBytes = { 0x42, 0x4D };
        const static std::vector<std::uint8_t> JPGBytes = { 0xFF, 0xD8, 0xFF };
        const static std::vector<std::uint8_t> JPEGBytes = { 0x00, 0x00, 0x00, 0x0C, 0x6A, 0x50, 0x20, 0x20 };
        const static std::vector<std::uint8_t> TIFFMonoChrome = { 0x0C, 0xED };
        const static std::vector<std::uint8_t> TIFFOne = { 0x49, 0x20, 0x49 };
        const static std::vector<std::uint8_t> TIFFTwo = { 0x49, 0x49, 0x2A, 0x00 };
        const static std::vector<std::uint8_t> TIFFThree = { 0x4D, 0x4D, 0x00, 0x2A };
        const static std::vector<std::uint8_t> TIFFFour = { 0x4D, 0x4D, 0x00, 0x2B };
        const static std::vector<std::uint8_t> CompressedTGA = {0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        const static std::vector<std::uint8_t> DeCompressedTGA = {0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

        const static std::vector<std::vector<std::uint8_t>> All = {GIFBytesOne, GIFBytesTwo, PNGBytes, BMPBytes, JPGBytes, JPEGBytes, TIFFMonoChrome, TIFFOne, TIFFTwo, TIFFThree, TIFFFour, CompressedTGA, DeCompressedTGA};

        auto BytesMatch = [](std::vector<std::uint8_t> One, std::uint8_t * Two) -> bool
        {
            for (size_t I = 0; I < One.size(); ++I)
            {
                if (One[I] != Two[I])
                    return false;
            }
            return true;
        };

        int I = 0;
        for (std::vector<std::uint8_t> Bytes : All)
        {
            if (BytesMatch(Bytes, ImageBytes))
                return I;
            ++I;
        }
        return -1;
    }

    void Image::ReadFromStream(png_structp PngPointer, std::uint8_t* Data, std::size_t Length)
    {
        std::ifstream *Stream = reinterpret_cast<std::ifstream*>(png_get_io_ptr(PngPointer));
        Stream->read(reinterpret_cast<char*>(Data), Length);
    }

    void Image::WriteToStream(png_structp PngPointer, std::uint8_t* Data, std::size_t Length)
    {
        std::ofstream *Stream = reinterpret_cast<std::ofstream*>(png_get_io_ptr(PngPointer));
        Stream->write(reinterpret_cast<char*>(Data), Length);
    }

    Image::Image(const Image& Img) : Pixels(Img.Pixels), Info(Img.Info), ImageCompressed(Img.ImageCompressed), width(Img.width), height(Img.height), size(Img.size), bFileHeader(Img.bFileHeader), BitsPerPixel(Img.BitsPerPixel), ImageType(Img.ImageType), bitdepth(Img.bitdepth), colortype(Img.colortype), interlacetype(Img.interlacetype), channels(Img.channels), DC(nullptr), ImageHandle(nullptr) {}

    Image::Image(Image && Img) : Pixels(), Info(), ImageCompressed(false), width(0), height(0), size(0), bFileHeader(), BitsPerPixel(32), ImageType(0), bitdepth(8), colortype(PNG_COLOR_TYPE_RGBA), interlacetype(0), channels(4), DC(nullptr), ImageHandle(nullptr)
    {
        this->Swap(Img);
        Img.Pixels.clear();
    }

    Image::Image(const char* FilePath) : Pixels(0), Info(), ImageCompressed(false), width(0), height(0), size(0), bFileHeader(), BitsPerPixel(32), ImageType(0), bitdepth(8), colortype(PNG_COLOR_TYPE_RGBA), interlacetype(0), channels(4), DC(nullptr), ImageHandle(nullptr)
    {
        Pixels.clear();
        std::fstream hFile(FilePath, std::ios::in | std::ios::binary);

        if (!hFile.is_open())
        {
            throw std::invalid_argument("File Not Found.");
        }

        std::uint8_t Header[18] = {0};
        hFile.read(reinterpret_cast<char*>(&Header), sizeof(Header));
        hFile.seekg(0, std::ios::beg);

        int IMAGETYPE = ValidImage(Header);

        if (IMAGETYPE == 2)                     //It's a PNG..
        {
            hFile.seekg(8);
            if (png_sig_cmp(Header, 0, 8))
            {
                hFile.close();
                throw std::invalid_argument("Error: Invalid File Format. Required: Png.");
            }

            png_structp PngPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            if (!PngPointer)
            {
                hFile.close();
                throw std::runtime_error("Error: Cannot Create Read Structure.");
            }

            png_infop InfoPointer = png_create_info_struct(PngPointer);
            if (!InfoPointer)
            {
                hFile.close();
                png_destroy_read_struct(&PngPointer, nullptr, nullptr);
                throw std::runtime_error("Error: Cannot Create InfoPointer Structure.");
            }

            png_infop EndInfo = png_create_info_struct(PngPointer);
            if (!EndInfo)
            {
                hFile.close();
                png_destroy_read_struct(&PngPointer, &InfoPointer, nullptr);
                throw std::runtime_error("Error: Cannot Create EndInfo Structure.");
            }

            if (setjmp(png_jmpbuf(PngPointer)))
            {
                hFile.close();
                png_destroy_read_struct(&PngPointer, &InfoPointer, nullptr);
                throw std::runtime_error("Error: Cannot Set Jump Pointer.");
            }

            png_set_sig_bytes(PngPointer, 8);
            png_set_read_fn(PngPointer, &hFile, ReadFromStream);
            png_read_info(PngPointer, InfoPointer);

            channels = png_get_channels(PngPointer, InfoPointer);
            png_get_IHDR(PngPointer, InfoPointer, &width, &height, &bitdepth, &colortype, &interlacetype, nullptr, nullptr);
            png_set_interlace_handling(PngPointer);
            png_set_strip_16(PngPointer);
            png_set_packing(PngPointer);

            switch (colortype)
            {
                case PNG_COLOR_TYPE_GRAY:
                    {
                        png_set_expand_gray_1_2_4_to_8(PngPointer);
                        png_set_gray_to_rgb(PngPointer);
                        png_set_bgr(PngPointer);
                        break;
                    }

                case PNG_COLOR_TYPE_PALETTE:
                    {
                        png_set_palette_to_rgb(PngPointer);
                        if (png_get_valid(PngPointer, InfoPointer, PNG_INFO_tRNS))
                            png_set_tRNS_to_alpha(PngPointer);
                        else
                            png_set_filler(PngPointer, 0xFF, PNG_FILLER_AFTER);
                        png_set_bgr(PngPointer);
                        BitsPerPixel = 24;
                        break;
                    }

                case PNG_COLOR_TYPE_GRAY_ALPHA:
                    {
                        png_set_gray_to_rgb(PngPointer);
                        break;
                    }

                case PNG_COLOR_TYPE_RGB:
                    {
                        png_set_bgr(PngPointer);
                        png_set_filler(PngPointer, 0xFF, PNG_FILLER_AFTER);
                        BitsPerPixel = 24;
                        break;
                    }

                case PNG_COLOR_TYPE_RGBA:
                    {
                        png_set_bgr(PngPointer);
                        BitsPerPixel = 32;
                        break;
                    }

                default:
                    png_destroy_read_struct(&PngPointer, &InfoPointer, nullptr);
                    throw std::runtime_error("Error: Png Type not supported.");
                    break;
            }

            png_read_update_info(PngPointer, InfoPointer);
            channels = png_get_channels(PngPointer, InfoPointer);
            png_get_IHDR(PngPointer, InfoPointer, &width, &height, &bitdepth, &colortype, &interlacetype, nullptr, nullptr);

            Pixels.resize(width * height);
            std::vector<std::uint8_t*> RowPointers(height);
            std::uint8_t* BuffPos = reinterpret_cast<std::uint8_t*>(Pixels.data());

            for (size_t I = 0; I < height; ++I)
            {
                RowPointers[I] = BuffPos + (I * width * sizeof(RGBA));
            }

            png_read_image(PngPointer, RowPointers.data());
            png_read_end(PngPointer, InfoPointer);
            png_destroy_read_struct(&PngPointer, &InfoPointer, nullptr);
            hFile.close();
        }
        else if (IMAGETYPE == 3)            //It's a Bitmap.
        {
            std::memset(&Info, 0, sizeof(BITMAPINFO));
            hFile.read(reinterpret_cast<char*>(&bFileHeader), sizeof(bFileHeader));
            hFile.read(reinterpret_cast<char*>(&Info.bmiHeader), sizeof(Info.bmiHeader));

            if (((Info.bmiHeader.biBitCount != 24) && (Info.bmiHeader.biBitCount != 32)) || (bFileHeader.bfType != 0x4D42) || (Info.bmiHeader.biCompression != BI_RGB))
            {
                hFile.close();
                throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
            }

            width = Info.bmiHeader.biWidth;
            height = std::abs(Info.bmiHeader.biHeight);
            size = Info.bmiHeader.biSizeImage;

            std::vector<std::uint8_t> TEMP(size);
            hFile.seekg (bFileHeader.bfOffBits, std::ios::beg);
            hFile.read(reinterpret_cast<char*>(TEMP.data()), size);
            hFile.close();

            std::uint8_t* BuffPos = TEMP.data();
            Pixels.resize(width * height);

            for (std::size_t I = 0; I < height; ++I)
            {
                for (std::size_t J = 0; J < width; ++J)
                {
                    Pixels[(height - 1 - I) * width + J].B = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].G = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].R = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].A = (Info.bmiHeader.biBitCount > 24 ? * (BuffPos++) : 0xFF);
                }
                if(Info.bmiHeader.biBitCount == 24)
                    BuffPos += (-width * 3) & 3;    //(4 - ((width * 3) % 4)) % 4;
            }
        }
        else if (IMAGETYPE == 11 || IMAGETYPE == 12)    //It's a TGA Image.
        {
            hFile.seekg(sizeof(Header));
            std::vector<std::uint8_t> ImageData;

            if (IMAGETYPE == 11)
            {
                BitsPerPixel = Header[16];
                width  = (Header[13] << 8) + Header[12];
                height = (Header[15] << 8) + Header[14];
                size  = ((width * BitsPerPixel + 31) / 32) * 4 * height;

                if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
                {
                    hFile.close();
                    throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
                }

                RGBA Pixel = {0};
                int CurrentByte = 0;
                std::size_t CurrentPixel = 0;
                ImageCompressed = true;
                std::uint8_t ChunkHeader = {0};
                int BytesPerPixel = (BitsPerPixel / 8);
                ImageData.resize(width * height * sizeof(RGBA));

                do
                {
                    hFile.read(reinterpret_cast<char*>(&ChunkHeader), sizeof(ChunkHeader));

                    if(ChunkHeader < 128)
                    {
                        ++ChunkHeader;
                        for(int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
                        {
                            hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

                            ImageData[CurrentByte++] = Pixel.B;
                            ImageData[CurrentByte++] = Pixel.G;
                            ImageData[CurrentByte++] = Pixel.R;
                            if (BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
                        }
                    }
                    else
                    {
                        ChunkHeader -= 127;
                        hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

                        for(int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
                        {
                            ImageData[CurrentByte++] = Pixel.B;
                            ImageData[CurrentByte++] = Pixel.G;
                            ImageData[CurrentByte++] = Pixel.R;
                            if (BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
                        }
                    }
                }
                while(CurrentPixel < (width * height));
            }
            else if (IMAGETYPE == 12)
            {
                BitsPerPixel = Header[16];
                width  = (Header[13] << 8) + Header[12];
                height = (Header[15] << 8) + Header[14];
                size  = ((width * BitsPerPixel + 31) / 32) * 4 * height;

                if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
                {
                    hFile.close();
                    throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
                }

                ImageData.resize(size);
                ImageCompressed = false;
                hFile.read(reinterpret_cast<char*>(ImageData.data()), size);
            }
            else
            {
                hFile.close();
                throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit TGA File.");
            }

            hFile.close();
            std::uint8_t* BuffPos = ImageData.data();
            Pixels.resize(width * height);

            for (std::size_t I = 0; I < height; ++I)
            {
                for (std::size_t J = 0; J < width; ++J)
                {
                    Pixels[(height - 1 - I) * width + J].B = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].G = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].R = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].A = (BitsPerPixel > 24 ? * (BuffPos++) : 0xFF);
                }
            }
        }
        else
        {
            hFile.close();
            throw std::invalid_argument("Error: Invalid File Format!");
        }

        std::memset(&Info, 0, sizeof(BITMAPINFO));
        Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        Info.bmiHeader.biPlanes = 1;
        Info.bmiHeader.biBitCount = BitsPerPixel;
        Info.bmiHeader.biCompression = BI_RGB;
        Info.bmiHeader.biWidth = width;
        Info.bmiHeader.biHeight = height;
        Info.bmiHeader.biSizeImage = size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
        bFileHeader.bfType = 0x4D42;
        bFileHeader.bfSize = bFileHeader.bfOffBits + size;
        bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
        channels = (BitsPerPixel > 24 ? 4 : 3);
        colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);
    }

    Image::Image(HBITMAP BitmapHandle) : Pixels(0), Info(), ImageCompressed(false), width(0), height(0), size(0), bFileHeader(), BitsPerPixel(32), ImageType(0), bitdepth(8), colortype(PNG_COLOR_TYPE_RGBA), interlacetype(0), channels(4), DC(nullptr), ImageHandle(nullptr)
    {
        if (BitmapHandle == nullptr)
        {
            throw std::logic_error("Null Pointer Exception. BitmapHandle is Null.");
        }
        BITMAP Bmp;
        Pixels.clear();
        DC = CreateCompatibleDC(nullptr);
        std::memset(&Info, 0, sizeof(BITMAPINFO));
        HBITMAP OldBitmap = (HBITMAP)SelectObject(DC, BitmapHandle);
        GetObject(BitmapHandle, sizeof(Bmp), &Bmp);

        Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        Info.bmiHeader.biWidth = width = Bmp.bmWidth;
        Info.bmiHeader.biHeight = height = Bmp.bmHeight;
        Info.bmiHeader.biPlanes = 1;
        Info.bmiHeader.biBitCount = Bmp.bmBitsPixel;
        Info.bmiHeader.biCompression = BI_RGB;
        Info.bmiHeader.biSizeImage = size = ((width * Bmp.bmBitsPixel + 31) / 32) * 4 * height;
        bFileHeader.bfType = 0x4D42;
        bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
        bFileHeader.bfSize = bFileHeader.bfOffBits + size;
        channels = (BitsPerPixel > 24 ? 4 : 3);
        colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);

        std::vector<std::uint8_t> ImageData(size);
        GetDIBits(DC, BitmapHandle, 0, height, ImageData.data(), &Info, DIB_RGB_COLORS);
        SelectObject(DC, OldBitmap);

        height = std::abs(height);
        std::uint8_t* BuffPos = ImageData.data();
        Pixels.resize(width * height);

        for (std::size_t I = 0; I < height; ++I)
        {
            for (std::size_t J = 0; J < width; ++J)
            {
                Pixels[(height - 1 - I) * width + J].B = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].G = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].R = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].A = (Info.bmiHeader.biBitCount > 24 ? *(BuffPos++) : 0xFF);
            }
            if(Info.bmiHeader.biBitCount == 24)
                BuffPos += (-width * 3) & 3;
        }
    }

    Image::Image(std::uint16_t ResourceID) : Pixels(0), Info(), ImageCompressed(false), width(0), height(0), size(0), bFileHeader(), BitsPerPixel(32), ImageType(0), bitdepth(8), colortype(PNG_COLOR_TYPE_RGBA), interlacetype(0), channels(4), DC(nullptr), ImageHandle(nullptr)
    {
        BITMAP Bmp;
        Pixels.clear();
        DC = CreateCompatibleDC(nullptr);
        std::memset(&Info, 0, sizeof(BITMAPINFO));
        ImageHandle = (HBITMAP)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCE(ResourceID), IMAGE_BITMAP, 0, 0, LR_SHARED);
        HBITMAP OldBitmap = (HBITMAP)SelectObject(DC, ImageHandle);
        GetObject(ImageHandle, sizeof(Bmp), &Bmp);

        Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        Info.bmiHeader.biWidth = width = Bmp.bmWidth;
        Info.bmiHeader.biHeight = height = Bmp.bmHeight;
        Info.bmiHeader.biPlanes = 1;
        Info.bmiHeader.biBitCount = Bmp.bmBitsPixel;
        Info.bmiHeader.biCompression = BI_RGB;
        Info.bmiHeader.biSizeImage = size = ((width * Bmp.bmBitsPixel + 31) / 32) * 4 * height;
        bFileHeader.bfType = 0x4D42;
        bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
        bFileHeader.bfSize = bFileHeader.bfOffBits + size;
        channels = (BitsPerPixel > 24 ? 4 : 3);
        colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);

        std::vector<std::uint8_t> ImageData(size);
        GetDIBits(DC, ImageHandle, 0, height, ImageData.data(), &Info, DIB_RGB_COLORS);
        SelectObject(DC, OldBitmap);

        height = std::abs(height);
        std::uint8_t* BuffPos = ImageData.data();
        Pixels.resize(width * height);

        for (std::size_t I = 0; I < height; ++I)
        {
            for (std::size_t J = 0; J < width; ++J)
            {
                Pixels[(height - 1 - I) * width + J].B = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].G = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].R = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].A = (Info.bmiHeader.biBitCount > 24 ? * (BuffPos++) : 0xFF);
            }
            if(Info.bmiHeader.biBitCount == 24)
                BuffPos += (-width * 3) & 3;
        }
    }

    Image::Image(std::vector<std::uint8_t> &Pointer, int Width, int Height, std::uint32_t BitsPerPixel, IMAGE_TYPE Value) : Pixels(0), Info(), ImageCompressed(false), width(Width), height(Height), size(0), bFileHeader(), BitsPerPixel(32), ImageType(Value), bitdepth(8), colortype(PNG_COLOR_TYPE_RGBA), interlacetype(0), channels(4), DC(nullptr), ImageHandle(nullptr)
    {
        Pixels.clear();
        if (Pointer.empty())
        {
            throw std::logic_error("NullPointer Exception. Pointer is NULL.");
        }
        if (Width < 1 || Height < 1)
        {
            throw std::invalid_argument("Invalid Arguments. Width and Height cannot be less than or equal to 0.");
        }

        if (Value == BMP)
        {
            if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
            {
                throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
            }
            if ((BitsPerPixel > 24) && (Pointer.size() < static_cast<std::size_t>(((width * 32 + 31) / 32) * 4 * height)))
            {
                throw std::logic_error("Invalid Pointer Size. Pointer may not contain an Alpha channel.");
            }
            std::memset(&Info, 0, sizeof(BITMAPINFO));
            size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

            Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            Info.bmiHeader.biWidth = width;
            Info.bmiHeader.biHeight = height;
            Info.bmiHeader.biPlanes = 1;
            Info.bmiHeader.biBitCount = BitsPerPixel;
            Info.bmiHeader.biCompression = BI_RGB;
            Info.bmiHeader.biSizeImage = size;
            bFileHeader.bfType = 0x4D42;
            bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
            bFileHeader.bfSize = bFileHeader.bfOffBits + size;
            channels = (BitsPerPixel > 24 ? 4 : 3);
            colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);

            height = std::abs(height);
            std::uint8_t* BuffPos = Pointer.data();
            Pixels.resize(width * height);
            for (std::size_t I = 0; I < height; ++I)
            {
                for (std::size_t J = 0; J < width; ++J)
                {
                    Pixels[(height - 1 - I) * width + J].B = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].G = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].R = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].A = (Info.bmiHeader.biBitCount > 24 ? * (BuffPos++) : 0xFF);
                }
                if(Info.bmiHeader.biBitCount == 24)
                    BuffPos += (-width * 3) & 3;
            }
        }
        else if (Value == PNG)
        {
            if ((BitsPerPixel != 24) || (BitsPerPixel != 32))
            {
                throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
            }

            std::memset(&Info, 0, sizeof(BITMAPINFO));
            Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            Info.bmiHeader.biPlanes = 1;
            Info.bmiHeader.biBitCount = BitsPerPixel;
            Info.bmiHeader.biCompression = BI_RGB;
            Info.bmiHeader.biWidth = width;
            Info.bmiHeader.biHeight = height;
            Info.bmiHeader.biSizeImage = size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
            bFileHeader.bfType = 0x4D42;
            bFileHeader.bfSize = bFileHeader.bfOffBits + size;
            bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
            channels = (BitsPerPixel > 24 ? 4 : 3);
            colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);
            Pixels.resize(width * height * sizeof(RGBA));
            std::vector<RGBA>::iterator jt = Pixels.begin();

            for (std::vector<std::uint8_t>::iterator it = Pointer.begin(); it != Pointer.end(); ++jt)
            {
                jt->B = *(it++);
                jt->G = *(it++);
                jt->R = *(it++);
                jt->A = (BitsPerPixel > 24 ? * (it++) : 0xFF);
            }
        }
    }

    Image::Image(const void* Pointer, int Width, int Height, std::uint32_t BitsPerPixel, IMAGE_TYPE Value) : Pixels(0), Info(), ImageCompressed(false), width(Width), height(Height), size(0), bFileHeader(), BitsPerPixel(32), ImageType(Value), bitdepth(8), colortype(PNG_COLOR_TYPE_RGBA), interlacetype(0), channels(4), DC(nullptr), ImageHandle(nullptr)
    {
        Pixels.clear();
        if (Pointer == nullptr)
        {
            throw std::logic_error("Null Pointer Exception. Pointer is NULL.");
        }
        if (Width < 1 || Height < 1)
        {
            throw std::invalid_argument("Invalid Arguments. Width and Height cannot be less than or equal to 0.");
        }

        if (Value == BMP)
        {
            if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
            {
                throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
            }
            std::memset(&Info, 0, sizeof(BITMAPINFO));
            size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

            Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            Info.bmiHeader.biWidth = width;
            Info.bmiHeader.biHeight = height;
            Info.bmiHeader.biPlanes = 1;
            Info.bmiHeader.biBitCount = BitsPerPixel;
            Info.bmiHeader.biCompression = BI_RGB;
            Info.bmiHeader.biSizeImage = size;
            bFileHeader.bfType = 0x4D42;
            bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
            bFileHeader.bfSize = bFileHeader.bfOffBits + size;
            channels = (BitsPerPixel > 24 ? 4 : 3);
            colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);

            height = std::abs(height);
            const std::uint8_t* BuffPos = static_cast<const std::uint8_t*>(Pointer);
            Pixels.resize(width * height);

            for (std::size_t I = 0; I < height; ++I)
            {
                for (std::size_t J = 0; J < width; ++J)
                {
                    Pixels[(height - 1 - I) * width + J].B = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].G = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].R = *(BuffPos++);
                    Pixels[(height - 1 - I) * width + J].A = (Info.bmiHeader.biBitCount > 24 ? * (BuffPos++) : 0xFF);
                }
                if(Info.bmiHeader.biBitCount == 24)
                    BuffPos += (-width * 3) & 3;
            }
        }
        else if (Value == PNG)
        {
            if ((BitsPerPixel != 24) || (BitsPerPixel != 32))
            {
                throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
            }
            std::memset(&Info, 0, sizeof(BITMAPINFO));
            Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            Info.bmiHeader.biPlanes = 1;
            Info.bmiHeader.biBitCount = BitsPerPixel;
            Info.bmiHeader.biCompression = BI_RGB;
            Info.bmiHeader.biWidth = width;
            Info.bmiHeader.biHeight = height;
            Info.bmiHeader.biSizeImage = size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
            bFileHeader.bfType = 0x4D42;
            bFileHeader.bfSize = bFileHeader.bfOffBits + size;
            bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
            channels = (BitsPerPixel > 24 ? 4 : 3);
            colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);

            const std::uint8_t* BuffPos = static_cast<const std::uint8_t*>(Pointer);
            Pixels.resize(width * height * sizeof(RGBA));

            for (std::vector<RGBA>::iterator it = Pixels.begin(); it != Pixels.end(); ++it)
            {
                it->B = *(BuffPos++);
                it->G = *(BuffPos++);
                it->R = *(BuffPos++);
                it->A = (BitsPerPixel > 24 ? * (BuffPos++) : 0xFF);
            }
        }
    }

    Image::Image(int Width, int Height, std::uint32_t BitsPerPixel) : Pixels(0), Info(), ImageCompressed(false), width(Width), height(Height), size(0), bFileHeader(), BitsPerPixel(32), ImageType(0), bitdepth(8), colortype(PNG_COLOR_TYPE_RGBA), interlacetype(0), channels(4), DC(nullptr), ImageHandle(nullptr)
    {
        Pixels.clear();
        if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
        {
            throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
        }
        if (Width < 1 || Height < 1)
        {
            throw std::invalid_argument("Invalid Arguments. Width and Height cannot be less than or equal to 0.");
        }
        std::memset(&Info, 0, sizeof(BITMAPINFO));
        Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        Info.bmiHeader.biPlanes = 1;
        Info.bmiHeader.biBitCount = BitsPerPixel;
        Info.bmiHeader.biCompression = BI_RGB;
        Info.bmiHeader.biWidth = width;
        Info.bmiHeader.biHeight = height;
        Info.bmiHeader.biSizeImage = size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
        bFileHeader.bfType = 0x4D42;
        bFileHeader.bfSize = bFileHeader.bfOffBits + size;
        bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
        channels = (BitsPerPixel > 24 ? 4 : 3);
        colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);
        Pixels.resize(width * height);
    }

    Image::Image(HWND Window, Box Area, std::uint32_t BitsPerPixel) : Pixels(0), Info(), ImageCompressed(false), width(0), height(0), size(0), bFileHeader(), BitsPerPixel(32), ImageType(0), bitdepth(8), colortype(PNG_COLOR_TYPE_RGBA), interlacetype(0), channels(4), DC(nullptr), ImageHandle(nullptr)
    {
        Pixels.clear();
        if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
        {
            throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
        }
        std::memset(&Info, 0, sizeof(BITMAPINFO));
        HDC DC = GetDC(Window);
        BITMAP Bmp;
        HBITMAP hBmp = (HBITMAP)GetCurrentObject(DC, OBJ_BITMAP);

        if (GetObject(hBmp, sizeof(BITMAP), &Bmp) == 0)
            tcout << ErrorMessage(ERROR_INVALID_WINDOW_HANDLE);

        Box BMBox;
        GetClientRect(Window, reinterpret_cast<LPRECT>(&BMBox));
        width = (Area.Width() == 0) ? BMBox.Width() : Area.Width();
        height = (Area.Height() == 0) ? BMBox.Height() : Area.Height();

        HDC MemDC = GetDC(nullptr);
        HDC SDC = CreateCompatibleDC(MemDC);
        HBITMAP hSBmp = CreateCompatibleBitmap(MemDC, width, height);
        DeleteObject(SelectObject(SDC, hSBmp));

        BitBlt(SDC, 0, 0, width, height, DC, Area.X1, Area.Y1, SRCCOPY);
        size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

        Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        Info.bmiHeader.biWidth = width;
        Info.bmiHeader.biHeight = height;
        Info.bmiHeader.biPlanes = 1;
        Info.bmiHeader.biBitCount = BitsPerPixel;
        Info.bmiHeader.biCompression = BI_RGB;
        Info.bmiHeader.biSizeImage = size;
        bFileHeader.bfType = 0x4D42;
        bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
        bFileHeader.bfSize = bFileHeader.bfOffBits + size;
        channels = (BitsPerPixel > 24 ? 4 : 3);
        colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);

        std::vector<std::uint8_t> ImageData(size);
        GetDIBits(SDC, hSBmp, 0, height, ImageData.data(), &Info, DIB_RGB_COLORS);

        DeleteDC(SDC);
        DeleteObject(hSBmp);
        ReleaseDC(nullptr, MemDC);
        ReleaseDC(Window, DC);

        height = std::abs(height);
        std::uint8_t* BuffPos = ImageData.data();
        Pixels.resize(width * height);

        for (std::size_t I = 0; I < height; ++I)
        {
            for (std::size_t J = 0; J < width; ++J)
            {
                Pixels[(height - 1 - I) * width + J].B = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].G = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].R = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].A = (Info.bmiHeader.biBitCount > 24 ? * (BuffPos++) : 0xFF);
            }
            if(Info.bmiHeader.biBitCount == 24)
                BuffPos += (-width * 3) & 3;
        }
    }

    Image::Image(HDC Hdc, Box Area, std::uint32_t BitsPerPixel) : Pixels(0), Info(), ImageCompressed(false), width(0), height(0), size(0), bFileHeader(), BitsPerPixel(32), ImageType(0), bitdepth(8), colortype(PNG_COLOR_TYPE_RGBA), interlacetype(0), channels(4), DC(Hdc), ImageHandle(nullptr)
    {
        Pixels.clear();
        if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
        {
            throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
        }
        BITMAP Bmp;
        HBITMAP hBmp = (HBITMAP)GetCurrentObject(DC, OBJ_BITMAP);
        std::memset(&Info, 0, sizeof(BITMAPINFO));

        if (GetObject(hBmp, sizeof(BITMAP), &Bmp) == 0)
            tcout << ErrorMessage(ERROR_DC_NOT_FOUND);

        Box BMBox;
        HWND Window = WindowFromDC(DC);
        GetClientRect(Window, reinterpret_cast<LPRECT>(&BMBox));
        width = (Area.Width() == 0) ? BMBox.Width() : Area.Width();
        height = (Area.Height() == 0) ? BMBox.Height() : Area.Height();

        HDC MemDC = GetDC(nullptr);
        HDC SDC = CreateCompatibleDC(MemDC);
        HBITMAP hSBmp = CreateCompatibleBitmap(MemDC, width, height);
        DeleteObject(SelectObject(SDC, hSBmp));

        BitBlt(SDC, 0, 0, width, height, DC, Area.X1, Area.Y1, SRCCOPY);
        size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

        Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        Info.bmiHeader.biWidth = width;
        Info.bmiHeader.biHeight = height;
        Info.bmiHeader.biPlanes = 1;
        Info.bmiHeader.biBitCount = BitsPerPixel;
        Info.bmiHeader.biCompression = BI_RGB;
        Info.bmiHeader.biSizeImage = size;
        bFileHeader.bfType = 0x4D42;
        bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
        bFileHeader.bfSize = bFileHeader.bfOffBits + size;
        channels = (BitsPerPixel > 24 ? 4 : 3);
        colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);

        std::vector<std::uint8_t> ImageData(size);
        GetDIBits(SDC, hSBmp, 0, height, ImageData.data(), &Info, DIB_RGB_COLORS);

        DeleteDC(SDC);
        DeleteObject(hSBmp);
        ReleaseDC(nullptr, MemDC);

        height = std::abs(height);
        std::uint8_t* BuffPos = ImageData.data();
        Pixels.resize(width * height);

        for (std::size_t I = 0; I < height; ++I)
        {
            for (std::size_t J = 0; J < width; ++J)
            {
                Pixels[(height - 1 - I) * width + J].B = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].G = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].R = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].A = (Info.bmiHeader.biBitCount > 24 ? * (BuffPos++) : 0xFF);
            }
            if(Info.bmiHeader.biBitCount == 24)
                BuffPos += (-width * 3) & 3;
        }
    }

    bool Image::Save(const char* FilePath, IMAGE_TYPE Value)
    {
        std::fstream hFile(FilePath, std::ios::out | std::ios::binary);
        if (!hFile.is_open())
        {
            throw std::invalid_argument("Cannot open file for writing.");
        }
        SetBitsPerPixel(BitsPerPixel);

        if (Value == BMP)
        {
            size = Info.bmiHeader.biSizeImage = ((width * Info.bmiHeader.biBitCount + 31) / 32) * 4 * height;
            std::vector<std::uint8_t> ImageData(size);
            std::uint8_t* BuffPos = ImageData.data();

            for (std::size_t I = 0; I < height; ++I)
            {
                for (std::size_t J = 0; J < width; ++J)
                {
                    //Flip The ScanLines/Rows back to normal.
                    *(BuffPos++) = Pixels[(height - 1 - I) * width + J].B;
                    *(BuffPos++) = Pixels[(height - 1 - I) * width + J].G;
                    *(BuffPos++) = Pixels[(height - 1 - I) * width + J].R;

                    if (Info.bmiHeader.biBitCount > 24)
                        *(BuffPos++) = Pixels[(height - 1 - I) * width + J].A;
                }
                if(Info.bmiHeader.biBitCount == 24)
                    BuffPos += (-width * 3) & 3;
            }

            hFile.write(reinterpret_cast<char*>(&bFileHeader), sizeof(BITMAPFILEHEADER));
            hFile.write(reinterpret_cast<char*>(&Info.bmiHeader), sizeof (BITMAPINFOHEADER));
            hFile.write(reinterpret_cast<char*>(ImageData.data()), size);
            hFile.close();
        }
        else if (Value == PNG)
        {
            png_structp PngPointer = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            if (!PngPointer)
            {
                hFile.close();
                throw std::runtime_error("Error: Cannot Create Write Structure.");
            }

            png_infop InfoPointer = png_create_info_struct(PngPointer);
            if (!InfoPointer)
            {
                hFile.close();
                png_destroy_write_struct(&PngPointer, nullptr);
                throw std::runtime_error("Error: Cannot Create InfoPointer Structure.");
            }

            if (setjmp(png_jmpbuf(PngPointer)))
            {
                hFile.close();
                png_destroy_write_struct(&PngPointer, &InfoPointer);
                throw std::runtime_error("Error: Cannot Set Jump Pointer.");
            }

            png_set_write_fn(PngPointer, &hFile, WriteToStream, nullptr);
            png_set_IHDR (PngPointer, InfoPointer, width, height, bitdepth, BitsPerPixel == 24 ? PNG_COLOR_TYPE_RGB : PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
            png_write_info(PngPointer, InfoPointer);

            png_set_bgr(PngPointer);
            png_set_packing(PngPointer);
            png_set_interlace_handling(PngPointer);
            if (colortype == PNG_COLOR_TYPE_RGB) png_set_filler(PngPointer, 0xFF, PNG_FILLER_AFTER);

            std::vector<std::uint8_t*> RowPointers(height);
            std::uint8_t* BuffPos = reinterpret_cast<std::uint8_t*>(Pixels.data());

            for (std::size_t I = 0; I < height; ++I)
            {
                RowPointers[I] = BuffPos + (I * width * sizeof(RGBA));
            }

            png_write_image(PngPointer, RowPointers.data());
            png_write_end(PngPointer, InfoPointer);
            png_destroy_write_struct(&PngPointer, &InfoPointer);
            hFile.close();
        }
        else if (Value == TGA)
        {
            size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
            std::vector<std::uint8_t> ImageData(size);
            std::uint8_t* BuffPos = ImageData.data();

            for (std::size_t I = 0; I < height; ++I)
            {
                for (std::size_t J = 0; J < width; ++J)
                {
                    //Flip The ScanLines/Rows back to normal.
                    *(BuffPos++) = Pixels[(height - 1 - I) * width + J].B;
                    *(BuffPos++) = Pixels[(height - 1 - I) * width + J].G;
                    *(BuffPos++) = Pixels[(height - 1 - I) * width + J].R;

                    if (BitsPerPixel > 24)
                        *(BuffPos++) = Pixels[(height - 1 - I) * width + J].A;
                }
                if(BitsPerPixel == 24)
                    BuffPos += (-width * 3) & 3;
            }

            static std::uint8_t DeCompressed[12] = {0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
            static std::uint8_t IsCompressed[12] = {0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

            if (!ImageCompressed)
            {
                hFile.write(reinterpret_cast<char*>(&DeCompressed), sizeof(DeCompressed));
                hFile.put((width & 0xFF));
                hFile.put(((width >> 8) & 0xFF));
                hFile.put((height & 0xFF));
                hFile.put(((height >> 8) & 0xFF));
                hFile.put(BitsPerPixel);
                hFile.put(0x0);
                hFile.write(reinterpret_cast<char*>(ImageData.data()), ImageData.size());
                hFile.close();
            }
            else
            {
                hFile.write(reinterpret_cast<char*>(&IsCompressed), sizeof(IsCompressed));
                hFile.put((width & 0xFF));
                hFile.put(((width >> 8) & 0xFF));
                hFile.put((height & 0xFF));
                hFile.put(((height >> 8) & 0xFF));
                hFile.put(BitsPerPixel);
                hFile.put(0x0);
            }
            hFile.close();
        }

        return true;
    }

    Image& Image::operator = (Image Img)
    {
        Img.Swap(*this);
        return *this;
    }

    void Image::Swap(Image& Img) //throw()
    {
        using std::swap;
        swap(Pixels, Img.Pixels);
        swap(Info, Img.Info);
        swap(ImageCompressed, Img.ImageCompressed);
        swap(width, Img.width);
        swap(height, Img.height);
        swap(size, Img.size);
        swap(bFileHeader, Img.bFileHeader);
        swap(BitsPerPixel, Img.BitsPerPixel);
        swap(ImageType, Img.ImageType);
        swap(bitdepth, Img.bitdepth);
        swap(colortype, Img.colortype);
        swap(interlacetype, Img.interlacetype);
        swap(channels, Img.channels);
        swap(DC, Img.DC);
        swap(ImageHandle, Img.ImageHandle);
    }

    HBITMAP Image::ToHBitmap()
    {
        std::vector<std::uint8_t> ImageData(size);
        std::uint8_t* BuffPos = ImageData.data();
        std::uint8_t* Memory = ImageData.data();

        for (std::size_t I = 0; I < height; ++I)
        {
            for (std::size_t J = 0; J < width; ++J)
            {
                *(BuffPos++) = Pixels[(height - 1 - I) * width + J].B;
                *(BuffPos++) = Pixels[(height - 1 - I) * width + J].G;
                *(BuffPos++) = Pixels[(height - 1 - I) * width + J].R;

                if (Info.bmiHeader.biBitCount > 24)
                    *(BuffPos++) = Pixels[(height - 1 - I) * width + J].A;
            }
            if(Info.bmiHeader.biBitCount == 24)
                BuffPos += (-width * 3) & 3;
        }

        DeleteObject(ImageHandle);
        return (ImageHandle = CreateDIBitmap(GetDC(nullptr), &Info.bmiHeader, CBM_INIT, Memory, &Info, DIB_RGB_COLORS));
    }

    void Image::Draw(HWND Hwnd, HBITMAP hBmp , int X , int Y , int Width , int Height , int SourceX , int SourceY, DWORD RasterType)
    {
        HDC hDC = GetDC(Hwnd);
        Draw(hDC, hBmp, X, Y, Width, Height, SourceX, SourceY, RasterType);
        ReleaseDC(Hwnd, hDC);
    }

    void Image::Draw(HDC hDC, HBITMAP hBmp , int X , int Y , int Width , int Height , int SourceX , int SourceY, DWORD RasterType)
    {
        BITMAP Bmp;
        HDC MemDC = CreateCompatibleDC(hDC);
        if (!ImageHandle) ToHBitmap();
        HGDIOBJ hbmOld = SelectObject(MemDC, hBmp == nullptr ? ImageHandle : hBmp);
        GetObject(hBmp == nullptr ? ImageHandle : hBmp, sizeof(Bmp), &Bmp);

        BitBlt(hDC, X, Y, Width == 0 ? Bmp.bmWidth : Width, Height == 0 ? Bmp.bmHeight : Height, MemDC, SourceX, SourceY, RasterType);

        SelectObject(MemDC, hbmOld);
        DeleteDC(MemDC);
    }

    tstring Image::ToString()
    {
        std::string Data;
        Data.resize(width * height * sizeof(RGBA));
        PRGB Pointer = reinterpret_cast<PRGB>(&Data[0]);

        for (std::vector<RGBA>::iterator it = Pixels.begin(); it != Pixels.end(); ++it)
        {
            Pointer->R = it->R;
            Pointer->G = it->G;
            Pointer->B = it->B;
            ++Pointer;
        }

        Data = CompressString(Data);
        return EncodeBase64(_T("IMG.") + to_tstring(width) + _T("*") + to_tstring(height)) + _T(".") + EncodeBase64(tstring(Data.begin(), Data.end()));
    }

    Image& Image::FromString(tstring Data, std::uint32_t BitsPerPixel)
    {
        int PosDot = Pos(_T("."), Data, 0);
        tstring DataHeader = DecodeBase64(Copy(Data, 0, PosDot));

        if (Copy(DataHeader, 0, 4) != _T("IMG."))
        {
            throw std::logic_error("Error: Invalid Image String.");
        }

        int PosStar = Pos(_T("*"), DataHeader, 4);
        width = ToNumber<int>(Copy(DataHeader, 5, PosStar - 4));
        height = ToNumber<int>(Copy(DataHeader, PosStar + 2, PosDot - PosStar));
        Data.erase(Data.begin(), Data.begin() + PosDot + 1);
        Data = DecodeBase64(Data);
        std::string DataBits = DecompressString(std::string(Data.begin(), Data.end()));

        Pixels.clear();
        std::memset(&Info, 0, sizeof(BITMAPINFO));
        Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        Info.bmiHeader.biPlanes = 1;
        Info.bmiHeader.biBitCount = BitsPerPixel;
        Info.bmiHeader.biCompression = BI_RGB;
        Info.bmiHeader.biWidth = width;
        Info.bmiHeader.biHeight = height;
        Info.bmiHeader.biSizeImage = size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
        bFileHeader.bfType = 0x4D42;
        bFileHeader.bfSize = bFileHeader.bfOffBits + size;
        bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(Info.bmiHeader);
        Pixels.resize(width * height);
        PRGB Pointer = reinterpret_cast<PRGB>(&DataBits[0]);

        for (std::vector<RGBA>::iterator it = Pixels.begin(); it != Pixels.end(); ++it)
        {
            it->R = Pointer->R;
            it->G = Pointer->G;
            it->B = Pointer->B;
            ++Pointer;
        }

        return *this;
    }

    int Image::Width() const
    {
        return std::abs(width);
    }

    int Image::Height() const
    {
        return std::abs(height);
    }

    int Image::Size() const
    {
        return this->size;
    }

    void Image::Size(int& W, int& H) const
    {
        W = this->Width();
        H = this->Height();
    }

    int Image::GetBitsPerPixel() const
    {
        return Info.bmiHeader.biBitCount;
    }

    void Image::SetBitsPerPixel(std::uint32_t Depth)
    {
        assert(Depth == 24 || Depth == 32);
        bitdepth = 8;
        Info.bmiHeader.biBitCount = BitsPerPixel = Depth;
        channels = (BitsPerPixel > 24 ? 4 : 3);
        colortype = (BitsPerPixel > 24 ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB);
    }

    RGBA& Image::operator [](int I)
    {
        assert(I >= 0 && !Pixels.empty());
        return Pixels[I];
    }

    const RGBA& Image::operator [](int I) const
    {
        assert(I >= 0 && !Pixels.empty());
        return Pixels[I];
    }

    std::vector<RGBA>::iterator Image::PixelsBegin()
    {
        return Pixels.begin();
    }

    std::vector<RGBA>::const_iterator Image::PixelsBegin() const
    {
        return Pixels.begin();
    }

    std::vector<RGBA>::iterator Image::PixelsEnd()
    {
        return Pixels.end();
    }

    std::vector<RGBA>::const_iterator Image::PixelsEnd() const
    {
        return Pixels.end();
    }

    std::pair<std::vector<RGBA>::iterator, std::vector<RGBA>::iterator> Image::PixelsRange()
    {
        return std::make_pair(Pixels.begin(), Pixels.end());
    }

    std::pair<std::vector<RGBA>::const_iterator, std::vector<RGBA>::const_iterator> Image::PixelsRange() const
    {
        return std::make_pair(Pixels.begin(), Pixels.end());
    }

    RGBA Image::GetPixel(int X, int Y) const
    {
        return Pixels[Y * width + X];   //return Pixels[(height - 1 - y) * width + x];   //If Not Flipped..
    }

    void Image::SetPixel(int X, int Y, RGBA Color)
    {
        Pixels[Y * width + X] = Color;
    }


    /** Portable Bitmap Class **/


    PBitmap::PBitmap(const char* FilePath) : Pixels(0), width(0), height(0), BitsPerPixel(0)
    {
        std::fstream hFile(FilePath, std::ios::in | std::ios::binary);
        if (!hFile.is_open()) throw std::invalid_argument("Error: File Not Found.");

        hFile.seekg(0, std::ios::end);
        int Length = hFile.tellg();
        hFile.seekg(0, std::ios::beg);
        std::vector<std::uint8_t> FileInfo(Length);

        hFile.read(reinterpret_cast<char*>(FileInfo.data()), 54);

        if(FileInfo[0] != 'B' && FileInfo[1] != 'M')
        {
            hFile.close();
            throw std::invalid_argument("Error: Invalid File Format. Bitmap Required.");
        }

        if (FileInfo[28] != 24 && FileInfo[28] != 32)
        {
            hFile.close();
            throw std::invalid_argument("Error: Invalid File Format. 24 or 32 bit Image Required.");
        }

        BitsPerPixel = FileInfo[28];
        width = FileInfo[18] + (FileInfo[19] << 8);
        height = FileInfo[22] + (FileInfo[23] << 8);
        std::uint32_t PixelsOffset = FileInfo[10] + (FileInfo[11] << 8);
        std::uint32_t size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

        hFile.seekg (PixelsOffset, std::ios::beg);
        hFile.read(reinterpret_cast<char*>(FileInfo.data()), size);
        hFile.close();

        std::uint8_t* BuffPos = FileInfo.data();
        Pixels.resize(width * height);

        for (std::uint16_t I = 0; I < height; ++I)
        {
            for (std::uint16_t J = 0; J < width; ++J)
            {
                Pixels[(height - 1 - I) * width + J].B = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].G = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].R = *(BuffPos++);
                Pixels[(height - 1 - I) * width + J].A = (BitsPerPixel > 24 ? * (BuffPos++) : 0xFF);
            }
            if (BitsPerPixel == 24)
                BuffPos += (-width * 3) & 3;
        }
    }

    void PBitmap::Save(const char* FilePath)
    {
        std::fstream hFile(FilePath, std::ios::out | std::ios::binary);
        if (!hFile.is_open()) throw std::invalid_argument("Error: File not found.");

        std::uint32_t Trash = 0;
        std::uint16_t Planes = 1;
        std::uint32_t biSize = 40;
        std::uint16_t Type = 0x4D42;
        std::uint32_t compression = 0;
        std::uint32_t PixelsOffsetBits = 54;
        std::uint32_t size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
        std::uint32_t bfSize = 54 + size;

        std::vector<std::uint8_t> ImageData(size);
        std::uint8_t* BuffPos = ImageData.data();

        for (std::size_t I = 0; I < height; ++I)
        {
            for (std::size_t J = 0; J < width; ++J)
            {
                *(BuffPos++) = Pixels[(height - 1 - I) * width + J].B;
                *(BuffPos++) = Pixels[(height - 1 - I) * width + J].G;
                *(BuffPos++) = Pixels[(height - 1 - I) * width + J].R;

                if (BitsPerPixel > 24)
                    *(BuffPos++) = Pixels[(height - 1 - I) * width + J].A;
            }
            if(BitsPerPixel == 24)
                BuffPos += (-width * 3) & 3;
        }

        hFile.write(reinterpret_cast<char*>(&Type), sizeof(Type));
        hFile.write(reinterpret_cast<char*>(&bfSize), sizeof(bfSize));
        hFile.write(reinterpret_cast<char*>(&Trash), sizeof(std::uint32_t));
        hFile.write(reinterpret_cast<char*>(&PixelsOffsetBits), sizeof(PixelsOffsetBits));
        hFile.write(reinterpret_cast<char*>(&biSize), sizeof(biSize));
        hFile.write(reinterpret_cast<char*>(&width), sizeof(width));
        hFile.write(reinterpret_cast<char*>(&height), sizeof(height));
        hFile.write(reinterpret_cast<char*>(&Planes), sizeof(Planes));
        hFile.write(reinterpret_cast<char*>(&BitsPerPixel), sizeof(BitsPerPixel));
        hFile.write(reinterpret_cast<char*>(&compression), sizeof(compression));
        hFile.write(reinterpret_cast<char*>(&size), sizeof(size));
        hFile.write(reinterpret_cast<char*>(&Trash), sizeof(std::uint32_t) * 4);
        hFile.write(reinterpret_cast<char*>(ImageData.data()), size);
        hFile.close();
    }

    /** Functions **/

    void FlipImageBytes(void* In, void* Out, int width, int height, std::uint16_t Bpp)
    {
        std::uint32_t Chunk = (Bpp > 24 ? width * 4 : width * 3 + width % 4);
        std::uint8_t* Destination = static_cast<std::uint8_t*>(Out);
        std::uint8_t* Source = static_cast<std::uint8_t*>(In) + Chunk * (height - 1);

        while(Source != In)
        {
            std::memcpy(Destination, Source, Chunk);
            Destination += Chunk;
            Source -= Chunk;
        }
    }
}

/*void BufferToRGB(int width, int height, int BitsPerPixel, std::uint8_t* Input, std::vector<RGBA>::iterator it)
{
    std::uint8_t* BuffPos = Input;
    height = (height < 0 ? -height : height);

    for (int I = 0; I < height; ++I)
    {
        for (int J = 0; J < width; ++J)
        {
            (it + ((height - 1 - I) * width + J))->B = *(BuffPos++);
            (it + ((height - 1 - I) * width + J))->G = *(BuffPos++);
            (it + ((height - 1 - I) * width + J))->R = *(BuffPos++);
            (it + ((height - 1 - I) * width + J))->A = (BitsPerPixel > 24 ? *(BuffPos++) : 255);
        }
        if(BitsPerPixel == 24)
            BuffPos += (-width * 3) & 3;
    }
}

void RGBToBuffer(int width, int height, int BitsPerPixel, std::vector<RGBA>::iterator it, std::uint8_t* Output)
{
    std::uint8_t* BuffPos = Output;

    for (int I = 0; I < height; ++I)
    {
        for (int J = 0; J < width; ++J)
        {
            *(BuffPos++) = (it + ((height - 1 - I) * width + J))->B;
            *(BuffPos++) = (it + ((height - 1 - I) * width + J))->G;
            *(BuffPos++) = (it + ((height - 1 - I) * width + J))->R;

            if (BitsPerPixel > 24)
                *(BuffPos++) = (it + ((height - 1 - I) * width + J))->A;
        }
        if(BitsPerPixel == 24)
            BuffPos += (-width * 3) & 3;
    }
}*/

#ifndef IMAGE16_HPP
#define IMAGE16_HPP

#include <Magick++.h>
#include <vector>

#include "image.hpp"
#include "color.hpp"

class Image32Bpp;

/** 16 Bit Image BGR / ABGR
  * Used for GBA mode 3 and DS bitmap mode
  */
class Image16Bpp : public Image
{
    public:
        Image16Bpp(const Image32Bpp& image);
        void WriteData(std::ostream& file) const;
        void WriteCommonExport(std::ostream& file) const;
        void WriteExport(std::ostream& file) const;
        const Color16& At(int x, int y) const {return pixels[y * width + x];}
        std::vector<Color16> pixels;
};

#endif

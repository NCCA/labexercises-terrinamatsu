#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include <cstdlib>
#include <memory> // make unique, smart pointers, etc.
#include <string>

struct RGBA
{
    union
    {
        struct
        {
            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;
            unsigned char a = 255;
        };
        uint32_t pixels;
    };  

    RGBA() = default;
    RGBA(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) :
    r{_r},g{_g},b{_b},a{_a} {}
};

class Image
{
    public :
        Image() = default;
        Image(size_t _width, size_t  _height);
        Image(size_t _width, size_t  _height, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);

        size_t width() const;
        size_t height() const;

        RGBA getPixel(size_t _x, size_t _y); 
        void setPixel(size_t _x, size_t _y, RGBA _p);

        void line(int _sx, int _sy, int _ex, int _ey, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
        void rectangle(int _tx, int _ty, int _bx, int _by, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a  ) ;

        bool write(const std::string &_fname) const;

    private:
        size_t m_width = 0;
        size_t m_height = 0;
        std::unique_ptr<RGBA []> m_pixels;
};

#endif
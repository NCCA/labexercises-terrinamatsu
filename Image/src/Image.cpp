#include "Image.h"
#include <cstring>
#include <OpenImageIO/imageio.h>

Image::Image(size_t _width, size_t  _height) : 
    m_width{_width}, m_height{_height} 
{
    m_pixels = std::make_unique<RGBA []>(m_width * m_height);
}

Image::Image(size_t _width, size_t  _height, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : 
    m_width{_width}, m_height{_height}
{
    m_pixels = std::make_unique<RGBA []>(m_width * m_height);
    
    RGBA p(_r, _g, _b, _a);
    for(size_t i = 0; i < (m_width * m_height); ++i)
    {
        m_pixels[i] = p;
    }
}


size_t Image::width() const
{
    return m_width;
}

size_t Image::height() const
{
    return m_height;
}

RGBA Image::getPixel(size_t _x, size_t _y)
{
    return m_pixels[_y * m_width + _x];
} 

void Image::setPixel(size_t _x, size_t _y, RGBA _p)
{
    m_pixels[_y * m_width + _x] = _p;
}

void Image::line(int _sx, int _sy, int _ex, int _ey, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
    int dx = _ex - _sx;
    int dy = _ey - _sy;
    int D = (2 * dy) - dx;
    int y = _ey;

    RGBA colour(_r, _g, _b, _a);

    for(size_t x = _sx; x <= _ex; ++x)
    {
        setPixel(x, y, colour);

        if(D > 0)
        {
            y++;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
}

void Image::rectangle(int _tx, int _ty, int _bx, int _by, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a  )
{
    RGBA colour(_r, _g, _b, _a);

    for(size_t x = _tx; x <= _bx; ++x)
    {
        for(size_t y = _ty; y <= _by; ++y)
        {
            setPixel(x, y, colour);
        }
    }
}

bool Image::write(const std::string &_fname) const
{
  bool success=true;

  using namespace OIIO;
  std::unique_ptr<ImageOutput> out = ImageOutput::create (_fname.data());
  if(!out)
  {
    return false;
  }
  ImageSpec spec (m_width,m_height,4, TypeDesc::UINT8);
  success=out->open(_fname.data(),spec);
  success=out->write_image(TypeDesc::UINT8,m_pixels.get());
  success=out->close();
  return success;
}
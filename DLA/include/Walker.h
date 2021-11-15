#ifndef WALKER_H_
#define WALKER_H_

#include <memory>
#include <string>
#include <random>
#include "Image.h"

class Walker
{
    public:
        Walker(size_t _w, size_t _h);
        Walker(const Walker &) = delete;

        void setImageSeed(size_t _x, size_t _y);
        void randomImageSeed();

        bool walk();
        void resetStart();

        void saveImage(const std::string &_fname) const;

    private:
        int m_xpos;
        int m_ypos;
        std::unique_ptr<Image> m_map;
        std::uniform_int_distribution<> m_xRand;
        std::uniform_int_distribution<> m_yRand;

        void initRNG();
};

#endif
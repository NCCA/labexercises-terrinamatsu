#include <gtest/gtest.h>
#include <Image.h>

TEST(RGBA, ctor)
{
    RGBA a;
    ASSERT_EQ(a.r, 0);
    ASSERT_EQ(a.g, 0);
    ASSERT_EQ(a.b, 0);
    ASSERT_EQ(a.a, 255);
}

TEST(RGBA, usr_ctor)
{
    RGBA a(255, 128, 64, 55);
    ASSERT_EQ(a.r, 255);
    ASSERT_EQ(a.g, 128);
    ASSERT_EQ(a.b, 64);
    ASSERT_EQ(a.a, 55);
}

TEST(IMAGE, ctor)
{
    Image img;
    ASSERT_EQ(img.width(), 0);
    ASSERT_EQ(img.height(), 0);
}

TEST(IMAGE, usr_ctor)
{
    Image img(250, 150);
    ASSERT_EQ(img.width(), 250);
    ASSERT_EQ(img.height(), 150);

    for(size_t y = 0; y < img.height(); ++y)
    {
        for(size_t x = 0; x < img.width(); ++x)
        {
            auto pixel = img.getPixel(x,y);
            ASSERT_EQ(pixel.r, 0);
            ASSERT_EQ(pixel.g, 0);
            ASSERT_EQ(pixel.b, 0);
            ASSERT_EQ(pixel.a, 255);
        }
    }
}

TEST(IMAGE, usr_ctor_colour)
{
    Image img(250, 150, 255, 0, 0, 255);
    ASSERT_EQ(img.width(), 250);
    ASSERT_EQ(img.height(), 150);

    for(size_t y = 0; y < img.height(); ++y)
    {
        for(size_t x = 0; x < img.width(); ++x)
        {
            auto pixel = img.getPixel(x,y);
            ASSERT_EQ(pixel.r, 255);
            ASSERT_EQ(pixel.g, 0);
            ASSERT_EQ(pixel.b, 0);
            ASSERT_EQ(pixel.a, 255);
        }
    }
}

TEST(IMAGE, writeToFile)
{
    Image img(500, 500, 255, 127, 64, 255);
    ASSERT_TRUE(img.write("test.exr"));
}

TEST(IMAGE, setPixel)
{
    Image img(100, 100, 255, 255, 255, 255);

    for(int i = 0; i < img.width(); ++i)
    {
        img.setPixel(i, 30, {255, 0, 0, 255});
        img.setPixel(i, 31, {255, 0, 0, 255});
        img.setPixel(i, 32, {255, 0, 0, 255});
        img.setPixel(i, 33, {255, 0, 0, 255});
    }

    img.write("band.exr");
}

TEST(IMAGE, lineHorizontalE)
{
    Image img(200,200);

    img.line(0,100,200,100,255,0,0,255);
    RGBA p;
    
    for(size_t x=0; x<img.width(); ++x)
    {
        p=img.getPixel(x,100);
        ASSERT_EQ(p.r,255);
        ASSERT_EQ(p.g,0);
        ASSERT_EQ(p.b,0);
        ASSERT_EQ(p.a,255);
        
    }

    ASSERT_TRUE(img.write("line1.exr"));
}

TEST(IMAGE, lineHorizontalW)
{
    Image img(200,200);

    img.line(200,100,100,100,255,0,0,255);
    RGBA p;
    
    for(size_t x=0; x<img.width(); ++x)
    {
        p=img.getPixel(x,100);
        ASSERT_EQ(p.r,255);
        ASSERT_EQ(p.g,0);
        ASSERT_EQ(p.b,0);
        ASSERT_EQ(p.a,255);
        
    }

    ASSERT_TRUE(img.write("line2.exr"));
}

TEST(IMAGE, drawRectangle)
{
    Image img(300, 300);

    img.rectangle(50, 50, 250, 275, 0, 255, 0, 255);
    RGBA p;

    for(size_t x = 50; x <= 250; x++)
    {
        for(size_t y = 50; y <= 275; y++)
        {
            p = img.getPixel(x, y);
            ASSERT_EQ(p.r, 0);
            ASSERT_EQ(p.g, 255);
            ASSERT_EQ(p.b, 0);
            ASSERT_EQ(p.a, 255);
        }
    }

    ASSERT_TRUE(img.write("rectangle1.exr"));
}
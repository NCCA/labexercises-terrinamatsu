#include <iostream>
#include <cstdlib>
#include <fmt/format.h>
#include <cxxopts.hpp>

#include "Walker.h"

int main(int argc, char **argv)
{
    // Setup Commandline Aguments
    cxxopts::Options options("DLA", "Simple DLA Simulation");
    options.add_options()
    ("w,width", "image width", cxxopts::value<int>()->default_value("200"))
    ("h,height", "image height", cxxopts::value<int>()->default_value("200"))
    ("u,help", "Print usage");

    auto results = options.parse(argc, argv);
    if (results.count("help"))
    {
        std::cout << options.help() << '\n';
        exit(EXIT_FAILURE);
    }
    auto width=results["width"].as<int>();
    auto height=results["height"].as<int>();

    // Spawn Walker
    Walker w(width, height);

    // Set initial seeds
    w.setImageSeed(0,0);
    for(int i = 0; i < 20; ++i)
    {
        w.randomImageSeed();
    }

    // Iterate walks
    int iterations = 10000;
    int simCount = 0;
    int imageIndex = 0;
    for(int i = 0; i < iterations; ++i)
    {
        if(w.walk() == true)
        {
            if(!(simCount++ % 100))
            {
                // Save out image every 100 walk simulations
                w.saveImage(fmt::format("sim{:04d}.exr", imageIndex++));
            }
        }

        w.resetStart();
    }

    return EXIT_SUCCESS;
}
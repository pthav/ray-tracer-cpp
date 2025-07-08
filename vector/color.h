#ifndef COLOR_H
#define COLOR_H
#include "vector.h"
#include <iostream>

using color = Vec3;

inline double linearToGamma(double c)
{
    if (c > 0){
        return std::sqrt(c);
    }

    return 0;
}

inline void write_color(std::ostream &out, const color &pixelColor)
{
    // Gamma correction
    auto r {linearToGamma(pixelColor[0])};
    auto g {linearToGamma(pixelColor[1])};
    auto b {linearToGamma(pixelColor[2])};
    // auto r {pixelColor[0]};
    // auto g {pixelColor[1]};
    // auto b {pixelColor[2]};

    // Translate from [0,1] to [0,255].
    int rbyte = static_cast<int>(255.999 * r);
    int gbyte = static_cast<int>(255.999 * g);
    int bbyte = static_cast<int>(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif

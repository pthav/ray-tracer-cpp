#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include "vector.h"
#include "../utility/interval.h"

using color = Vec3;

inline double linearToGamma(double c)
{
    if (c > 0){
        return std::sqrt(c);
    }

    return 0;
}

inline void writeColor(std::ostream &out, const color &pixelColor)
{
    // Gamma correction
    auto r {linearToGamma(pixelColor[0])};
    auto g {linearToGamma(pixelColor[1])};
    auto b {linearToGamma(pixelColor[2])};
    // auto r {pixelColor[0]};
    // auto g {pixelColor[1]};
    // auto b {pixelColor[2]};

    // Translate from [0,1] to [0,255].
    static const Interval intensity {0,0.9999};
    int rbyte = static_cast<int>(256 * intensity.clamp(r));
    int gbyte = static_cast<int>(256 * intensity.clamp(g));
    int bbyte = static_cast<int>(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif

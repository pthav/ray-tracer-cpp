#ifndef COLOR_H
#define COLOR_H
#include "vector.h"
#include <iostream>

using color = vec3;

inline void write_color(std::ostream& out, const color& pixel_color) {
    // Translate from [0,1] to [0,255].
    int rbyte = int(255.999 * pixel_color[0]);
    int gbyte = int(255.999 * pixel_color[1]);
    int bbyte = int(255.999 * pixel_color[2]);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif

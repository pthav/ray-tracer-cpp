#ifndef TEXTURE_H
#define TEXTURE_H
#include "../vector/color.h"

class Texture
{
public:
    virtual ~Texture() = default;

    [[nodiscard]] virtual color value(double u, double v, const point3 &p) const = 0;
};

#endif //TEXTURE_H

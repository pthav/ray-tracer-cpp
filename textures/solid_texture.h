#ifndef SOLID_H
#define SOLID_H

#include "texture.h"
#include "../vector/color.h"

class SolidTexture : public Texture
{
public:
    explicit SolidTexture(color color): m_albedo{color}{}

    [[nodiscard]] color value(double u, double v, const point3 &p) const override
    {
        return m_albedo;
    }

private:
    color m_albedo{};
};

#endif //SOLID_H

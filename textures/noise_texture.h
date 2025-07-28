#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H
#include "texture.h"
#include "../utility/perlin.h"

class NoiseTexture : public Texture
{
public:
    explicit NoiseTexture(double scale)
    : m_scale{scale}
    {
    }

    [[nodiscard]] color value(double u, double v, const point3 &p) const override
    {
        auto radius {std::sqrt(p[0] * p[0] + p[2] * p[2])};
        return color{0.5,0.5,0.5} * (1 + std::sin(m_scale * radius + 3 * noise.turbulence(p, 7)));
    }

private:
    PerlinNoise noise {};
    double m_scale{};
};

#endif //NOISE_TEXTURE_H

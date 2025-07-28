#include "perlin.h"

double PerlinNoise::noise(const point3 &p) const{
    // Get the local coordinates within the grid entry
    auto u{p[0] - std::floor(p[0])};
    auto v{p[1] - std::floor(p[1])};
    auto w{p[2] - std::floor(p[2])};

    // Get the grid coordinates for the smallest corner
    auto i{static_cast<int>(std::floor(p[0]))};
    auto j{static_cast<int>(std::floor(p[1]))};
    auto k{static_cast<int>(std::floor(p[2]))};

    // Random vectors for each corner
    Vec3 c[2][2][2];

    for (int di{0}; di < 2; di++)
    {
        for (int dj{0}; dj < 2; dj++)
        {
            for (int dk{0}; dk < 2; dk++)
            {
                c[di][dj][dk] = m_randomVectors[
                    m_permX[(i + di) & 255] ^
                    m_permY[(j + dj) & 255] ^
                    m_permZ[(k + dk) & 255]
                ];
            }
        }
    }

    return interpolateNoise(c, u, v, w);
}

double PerlinNoise::turbulence(const point3 &p, int depth) const
{
    double accumulate {0};
    auto temp {p};
    auto weight {1.0};

    for (int i {0}; i < depth; i++)
    {
        accumulate += weight * noise(temp);
        weight *= 0.5;
        temp *= 2;
    }

    return std::fabs(accumulate);
}

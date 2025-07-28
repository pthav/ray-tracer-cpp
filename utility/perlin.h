#ifndef PERLIN_H
#define PERLIN_H

#include "../textures/texture.h"
#include "random.h"

class PerlinNoise
{
public:
    PerlinNoise()
    {
        // Generate random vectors with values in the range (-1,1)
        for (int i = 0; i < 256; i++)
        {
            m_randomVectors[i] = Vec3{
                Random::randomDouble() * 2 - 1, Random::randomDouble() * 2 - 1, Random::randomDouble() * 2 - 1
            };
        }

        generatePermutation(m_permX);
        generatePermutation(m_permY);
        generatePermutation(m_permZ);
    };

    [[nodiscard]] double noise(const point3 &p) const;

    [[nodiscard]] double turbulence(const point3 &p, int depth) const;

private:
    static constexpr int pointCount{256};
    Vec3 m_randomVectors[256];
    int m_permX[256]{};
    int m_permY[256]{};
    int m_permZ[256]{};

    // Permute the given array of size n
    static void permute(int *a, int n)
    {
        for (int i{0}; i < n; i++)
        {
            int swapTo{Random::randomInt(0, n)};
            std::swap(a[i], a[swapTo]);
        }
    }

    // Fill the array then permute it
    static void generatePermutation(int *a)
    {
        for (int i{0}; i < pointCount; i++)
        {
            a[i] = i;
        }
        permute(a, pointCount);
    }

    // Trilinear interpolation for perlin noise
    static double interpolateNoise(const Vec3 c[2][2][2], double u, double v, double w)
    {
        // Hermitian smoothing
        auto uu{u * u * (3 - 2 * u)};
        auto vv{v * v * (3 - 2 * v)};
        auto ww{w * w * (3 - 2 * w)};

        double accumulation{0};
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    Vec3 difference{(u - i), (v - j), (w - k)};
                    accumulation += (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j) * (1 - vv)) * (
                        k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], difference);
                }
            }
        }

        return accumulation;
    }
};

#endif //PERLIN_H

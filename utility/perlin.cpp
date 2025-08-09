#include "perlin.h"
#include "random.h"

PerlinNoise::PerlinNoise()
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

double PerlinNoise::noise(const point3 &p) const
{
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
    double accumulate{0};
    auto temp{p};
    auto weight{1.0};

    for (int i{0}; i < depth; i++)
    {
        accumulate += weight * noise(temp);
        weight *= 0.5;
        temp *= 2;
    }

    return std::fabs(accumulate);
}

// Permute the given array of size n
void PerlinNoise::permute(int *a, int n)
{
    for (int i{0}; i < n; i++)
    {
        int swapTo{Random::randomInt(0, n)};
        std::swap(a[i], a[swapTo]);
    }
}

// Fill the array then permute it
void PerlinNoise::generatePermutation(int *a)
{
    for (int i{0}; i < pointCount; i++)
    {
        a[i] = i;
    }
    permute(a, pointCount);
}

// Trilinear interpolation for perlin noise
double PerlinNoise::interpolateNoise(const Vec3 c[2][2][2], double u, double v, double w)
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

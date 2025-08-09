#ifndef PERLIN_H
#define PERLIN_H

#include "../textures/texture.h"

class PerlinNoise
{
public:
    PerlinNoise();

    [[nodiscard]] double noise(const point3 &p) const;

    [[nodiscard]] double turbulence(const point3 &p, int depth) const;

private:
    static constexpr int pointCount{256};
    Vec3 m_randomVectors[256];
    int m_permX[256]{};
    int m_permY[256]{};
    int m_permZ[256]{};

    // Permute the given array of size n
    static void permute(int *a, int n);

    // Fill the array then permute it
    static void generatePermutation(int *a);

    // Trilinear interpolation for perlin noise
    static double interpolateNoise(const Vec3 c[2][2][2], double u, double v, double w);
};

#endif //PERLIN_H

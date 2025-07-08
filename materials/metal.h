#ifndef METAL_H
#define METAL_H

#include <random>
#include "material.h"

class MetalMaterial : public Material
{
private:
    color m_albedo {};
    double m_fuzz {};
    std::mt19937 m_gen;
    std::uniform_real_distribution<> m_distribution{};

    Vec3 reflect(const Vec3& in, const Vec3& n);

public:
    explicit MetalMaterial(const color &albedo,double fuzz): m_albedo{albedo}, m_fuzz{fuzz < 1 ? fuzz: 1}
    {
        std::random_device rd;
        m_gen = std::mt19937(rd());
        m_distribution = std::uniform_real_distribution<>(0, 1);
    }

    bool scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered) override;
};

#endif //METAL_H

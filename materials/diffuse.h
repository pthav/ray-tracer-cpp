#ifndef DIFFUSE_H
#define DIFFUSE_H
#include <random>
#include "material.h"

class DiffuseMaterial : public Material
{
private:
    color m_albedo{};
    std::mt19937 m_gen;
    std::uniform_real_distribution<> m_distribution{};

    Vec3 cosineWeightedSample(const hitRecord &record);

public:
    explicit DiffuseMaterial(const color &albedo): m_albedo{albedo}
    {
        std::random_device rd;
        m_gen = std::mt19937(rd());
        m_distribution = std::uniform_real_distribution<>(0, 1);
    }

    bool scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered) override;
};

#endif //DIFFUSE_H

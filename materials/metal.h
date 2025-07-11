#ifndef METAL_H
#define METAL_H

#include "material.h"

class MetalMaterial : public Material
{
private:
    color m_albedo{};
    double m_fuzz{};

    [[nodiscard]] Vec3 fuzzyReflection(const Vec3 &in, const Vec3 &n) const;

public:
    explicit MetalMaterial(const color &albedo, double fuzz): m_albedo{albedo}, m_fuzz{fuzz < 1 ? fuzz : 1}{}

    bool scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered) override;
};

#endif //METAL_H

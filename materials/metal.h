#ifndef METAL_H
#define METAL_H

#include "material.h"

class MetalMaterial : public Material
{
public:
    explicit MetalMaterial(const color &albedo, double fuzz);

    bool scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered) override;

private:
    color m_albedo{};
    double m_fuzz{};

    [[nodiscard]] Vec3 fuzzyReflection(const Vec3 &in, const Vec3 &n) const;
};

#endif //METAL_H

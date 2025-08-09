#ifndef DIELECTRIC_H
#define DIELECTRIC_H
#include "material.h"

class DielectricMaterial : public Material
{
public:
    explicit DielectricMaterial(double refractiveIndex);

    bool scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered) override;

    static double reflectance(double cosine, double refraction_index);

private:
    double m_refractiveIndex{}; // Ratio between refractive index of object and surrounding one
};

#endif

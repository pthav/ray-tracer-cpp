#ifndef DIELECTRIC_H
#define DIELECTRIC_H
#include "material.h"

class DielectricMaterial : public Material
{
private:
    double m_refractiveIndex{}; // Ratio between refractive index of object and surrounding one
public:
    explicit DielectricMaterial(double refractiveIndex): m_refractiveIndex{refractiveIndex}{}

    // bool refract(const Vec3& in, const Vec3 &n, double ni, double nt, double &fr, Vec3 &t) const;

    bool scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered) override;

    static double reflectance(double cosine, double refraction_index) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0*r0;
        return r0 + (1-r0)*std::pow((1 - cosine),5);
    }
};

#endif

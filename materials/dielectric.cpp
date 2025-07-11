#include "dielectric.h"

#include <cassert>

// auto refractiveRatio{ni / nt};
// auto d{-in}; // Direction away from surface
// auto z{(refractiveRatio) * (dot(d, n) * n - d)};
//
// // Total internal reflection will occur in this scenario
// if (z.lengthSquared() > 1.0)
// {
//     fr = 1.0;
//     return false;
// }
//
// t = z - (std::sqrt(1 - z.lengthSquared())) * n; // Transmission vector
// auto rPar{
//     ((nt * dot(n, d) + ni * dot(n, t)) /
//      (nt * dot(n, d) - ni * dot(n, t)))
// }; // Parallel polarized light
// auto rPerp{
//     ((ni * dot(n, d) + nt * dot(n, t)) /
//      (ni * dot(n, d) - nt * dot(n, t)))
// }; // Perpendicular polarized light
//
// fr = 0.5 * (rPar * rPar + rPerp * rPerp); // Percent of light that reflects
// return true;

// Randomly select whether to generate a reflected or refracted ray based on fr.
bool DielectricMaterial::scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered)
{
    attenuation = color(1.0, 1.0, 1.0);
    double ri = record.m_isFrontFace ? (1.0 / m_refractiveIndex) : m_refractiveIndex;

    Vec3 unitDirection = normalize(in.getDirection());
    double cosTheta = std::fmin(dot(-unitDirection, record.m_normal), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = ri * sinTheta > 1.0;
    Vec3 direction {};

    if (cannotRefract || m_distribution(m_gen) < reflectance(cosTheta, ri))
    {
        direction = reflect(unitDirection, record.m_normal);
    } else
    {
        direction = refract(unitDirection, record.m_normal, ri);
    }

    scattered = ray(record.m_intersection, direction);
    return true;
}

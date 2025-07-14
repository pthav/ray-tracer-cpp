#include "dielectric.h"
#include "../utility/random.h"

#include <cassert>

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

    if (cannotRefract || Random::randomDouble() < reflectance(cosTheta, ri))
    {
        direction = reflect(unitDirection, record.m_normal);
    } else
    {
        direction = refract(unitDirection, record.m_normal, ri);
    }

    scattered = ray(record.m_intersection, direction, in.getTime());
    return true;
}

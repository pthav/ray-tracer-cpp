#include "diffuse.h"
#include "../utility/random.h"

Vec3 DiffuseMaterial::cosineWeightedSample(const hitRecord &record)
{
    // Generate a cosine weighted vector
    auto r {std::sqrt(Random::randomDouble())};
    auto theta {2 * std::numbers::pi * Random::randomDouble()};
    auto x {r * cos(theta)};
    auto y {r * sin(theta)};
    auto z {std::sqrt(1 - r * r)};
    Vec3 localDirection {x,y,z};

    // Create orthonormal base for the local coordinates
    Vec3 tangent {};
    if (std::fabs(record.m_normal[0]) > fabs(record.m_normal[2]))
        tangent = normalize(Vec3(-record.m_normal[1], record.m_normal[0], 0));
    else
        tangent = normalize(Vec3(0, -record.m_normal[2], record.m_normal[1]));
    auto tangent2 {cross(record.m_normal,tangent)};

    // Convert local coordinates to global coordinates
    return normalize(tangent * localDirection[0] + tangent2 * localDirection[1] + record.m_normal * localDirection[2]);
}

bool DiffuseMaterial::scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered)
{
    scattered = ray{record.m_intersection,cosineWeightedSample(record),in.getTime()};
    attenuation = m_texture->value(record.m_u,record.m_v,record.m_intersection);
    return true;
}


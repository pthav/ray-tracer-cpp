#include "metal.h"

Vec3 MetalMaterial::fuzzyReflection(const Vec3 &in, const Vec3 &n) const
{
    auto reflection {reflect(in,n)};
    auto fuzz {Vec3{m_distribution(m_gen), m_distribution(m_gen), m_distribution(m_gen)}};
    auto fuzzyReflection {m_fuzz * fuzz + reflection};
    return normalize(fuzzyReflection);
}

bool MetalMaterial::scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered)
{
    scattered = ray{record.m_intersection, fuzzyReflection(in.getDirection(), record.m_normal), in.getRefractionIndex()};
    attenuation = m_albedo;
    return dot(scattered.getDirection(),record.m_normal) > 0;
}


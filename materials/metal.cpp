#include "metal.h"

Vec3 MetalMaterial::reflect(const Vec3 &in, const Vec3 &n)
{
    auto reflection {in - n * 2 * dot(in,n)};
    auto fuzz {Vec3{m_distribution(m_gen), m_distribution(m_gen), m_distribution(m_gen)}};
    auto fuzzyReflection {m_fuzz * fuzz + reflection};
    return normalize(fuzzyReflection);
}

bool MetalMaterial::scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered)
{
    scattered = ray(record.m_intersection, reflect(in.getDirection(), record.m_normal));
    attenuation = m_albedo;
    return dot(scattered.getDirection(),record.m_normal) > 0;
}


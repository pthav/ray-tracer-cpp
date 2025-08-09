#include "metal.h"
#include "../utility/random.h"

MetalMaterial::MetalMaterial(const color &albedo, double fuzz): m_albedo{albedo}, m_fuzz{fuzz < 1 ? fuzz : 1}
{
}

Vec3 MetalMaterial::fuzzyReflection(const Vec3 &in, const Vec3 &n) const
{
    auto reflection{reflect(in, n)};
    auto fuzz{Vec3{Random::randomDouble(), Random::randomDouble(), Random::randomDouble()}};
    auto fuzzyReflection{m_fuzz * fuzz + reflection};
    return normalize(fuzzyReflection);
}

bool MetalMaterial::scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered)
{
    scattered = ray{record.m_intersection, fuzzyReflection(in.getDirection(), record.m_normal), in.getTime()};
    attenuation = m_albedo;
    return dot(scattered.getDirection(), record.m_normal) > 0;
}

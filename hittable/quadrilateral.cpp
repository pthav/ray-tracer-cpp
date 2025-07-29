#include "quadrilateral.h"

[[nodiscard]] bool Quadrilateral::isInside(double a, double b, hitRecord &rec) const
{
    Interval unitInterval {0,1};
    if (!unitInterval.contains(a) || !unitInterval.contains(b))
    {
        return false;
    }

    rec.m_u = a;
    rec.m_v = b;
    return true;
}

bool Quadrilateral::hit(const ray &r, Interval rayT, hitRecord &rec) const
{
    auto denominator {dot(m_normal, r.getDirection())};
    if (std::fabs(denominator) < 1e-8)
    {
        return false;
    }

    auto t {(m_d - dot(m_normal, r.getOrigin())) / denominator};
    if (!rayT.contains(t))
    {
        return false;
    }

    auto intersection {r.at(t)};
    Vec3 relativeIntersection {intersection - m_origin};
    auto a {dot(m_w,cross(relativeIntersection, m_v))};
    auto b {dot(m_w,cross(m_u, relativeIntersection))};

    if (!isInside(a,b,rec))
    {
        return false;
    }

    rec.m_t = t;
    rec.m_material = m_material;
    rec.m_intersection = intersection;
    setNormal(r, m_normal, rec);
    return true;
}

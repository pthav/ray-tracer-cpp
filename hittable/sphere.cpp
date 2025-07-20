#include "sphere.h"

#include <cmath>

bool Sphere::hit(const ray &r, Interval rayT, hitRecord &rec) const
{
    auto currentCenter {m_center.at(r.getTime())};
    auto oc{currentCenter - r.getOrigin()};
    auto a{r.getDirection().lengthSquared()};
    auto h{dot(r.getDirection(), oc)};
    auto c{oc.lengthSquared() - m_radius * m_radius};
    auto discriminant{h * h - a * c};

    // No intersection
    if (discriminant < 0)
    {
        return false;
    }

    auto sqrtDiscriminant{std::sqrt(discriminant)};

    // Find the closest intersection that is within [rayTMin,rayTMax]
    auto hitT{(h - sqrtDiscriminant) / a};
    if (hitT < rayT.m_start || hitT > rayT.m_end)
    {
        hitT = (h + sqrtDiscriminant) / a;
        if (hitT < rayT.m_start || hitT > rayT.m_end)
        {
            return false;
        }
    }

    // Fill out hit record
    rec.m_t = hitT;
    rec.m_intersection = r.at(hitT);
    rec.m_material = m_material;
    auto normal{(rec.m_intersection - currentCenter) / m_radius};
    setNormal(r, normal, rec);

    return true;
}

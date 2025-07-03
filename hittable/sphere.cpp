#include "sphere.h"

#include <cmath>

bool Sphere::hit(const ray &r, double rayTMin, double rayTMax, hitRecord &rec) const
{
    auto oc{m_center - r.getOrigin()};
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
    if (hitT < rayTMin || hitT > rayTMax)
    {
        hitT = (h + sqrtDiscriminant) / a;
        if (hitT < rayTMin || hitT > rayTMax)
        {
            return false;
        }
    }

    // Fill out hit record
    rec.m_t = hitT;
    rec.m_intersection = r.at(hitT);
    auto normal{(rec.m_intersection - m_center) / m_radius};
    setNormal(r, normal, rec);

    return true;
}

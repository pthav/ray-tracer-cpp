#include "sphere.h"

#include <cmath>

// Static sphere
Sphere::Sphere(const point3 &center, double r, const std::shared_ptr<Material> &material)
    : m_center{center, Vec3{0, 0, 0}},
      m_radius{r},
      m_material{material}
{
    auto rVec{Vec3{r, r, r}};
    m_boundingBox = AABB(center - rVec, center + rVec);
}

// Moving sphere
Sphere::Sphere(const point3 &start, const point3 &end, double r, const std::shared_ptr<Material> &material)
    : m_center{start, end - start},
      m_radius{r},
      m_material{material}
{
    auto rVec{Vec3{r, r, r}};
    m_boundingBox = AABB(AABB(m_center.at(0) - rVec, m_center.at(0) + rVec),
                         AABB(m_center.at(1) - rVec, m_center.at(1) + rVec));
}

bool Sphere::hit(const ray &r, Interval rayT, hitRecord &rec) const
{
    auto currentCenter{m_center.at(r.getTime())};
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
    if (hitT < rayT.m_min || hitT > rayT.m_max)
    {
        hitT = (h + sqrtDiscriminant) / a;
        if (hitT < rayT.m_min || hitT > rayT.m_max)
        {
            return false;
        }
    }

    // Fill out hit record
    rec.m_t = hitT;
    rec.m_intersection = r.at(hitT);
    rec.m_material = m_material;
    getUV(rec.m_u, rec.m_v, (rec.m_intersection - m_center.at(r.getTime())) / m_radius);
    auto normal{(rec.m_intersection - currentCenter) / m_radius};
    setNormal(r, normal, rec);

    return true;
}

[[nodiscard]] AABB Sphere::boundingBox() const
{
    return m_boundingBox;
}

void Sphere::getUV(double &u, double &v, const point3 &p)
{
    auto theta{std::acos(-p[1])};
    auto phi{std::atan2(-p[2], p[0]) + std::numbers::pi};

    u = phi / (2 * std::numbers::pi);
    v = theta / std::numbers::pi;
}

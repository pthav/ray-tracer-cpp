#ifndef QUAD_H
#define QUAD_H
#include "hittable.h"
#include "../materials/material.h"

class Quadrilateral : public Hittable
{
public:
    Quadrilateral(const point3 &origin, const Vec3 &u, const Vec3 &v, const std::shared_ptr<Material> &material)
        : m_material{material},
          m_origin{origin},
          m_u{u},
          m_v{v}
    {
        auto n = cross(u,v);
        m_normal = normalize(n);
        m_d = dot(m_normal, origin);
        m_w = n / dot(n,n);

        setBoundingBox();
    }

    [[nodiscard]] virtual bool isInside(double a, double b, hitRecord &rec) const;

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override;

    [[nodiscard]] AABB boundingBox() const override
    {
        return m_aabb;
    }

    void setBoundingBox()
    {
        m_aabb = AABB(m_origin, m_origin + m_u + m_v);
    }

protected:
    std::shared_ptr<Material> m_material;
    point3 m_origin{};
    point3 m_normal{};
    Vec3 m_u{};
    Vec3 m_v{};
    Vec3 m_w{};
    AABB m_aabb{};
    double m_d{};
};

#endif //QUAD_H

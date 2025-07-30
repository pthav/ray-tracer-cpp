#ifndef QUAD_H
#define QUAD_H
#include "hittable.h"
#include "hittable_list.h"
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

inline std::shared_ptr<HittableList> box(const point3& a, const point3& b, std::shared_ptr<Material> mat)
{
    // Returns the 3D box (six sides) that contains the two opposite vertices a & b.
    auto sides = std::make_shared<HittableList>();

    // Construct the two opposite vertices with the minimum and maximum coordinates.
    auto min = point3(std::fmin(a[0],b[0]), std::fmin(a[1],b[1]), std::fmin(a[2],b[2]));
    auto max = point3(std::fmax(a[0],b[0]), std::fmax(a[1],b[1]), std::fmax(a[2],b[2]));

    auto dx = Vec3(max[0] - min[0], 0, 0);
    auto dy = Vec3(0, max[1] - min[1], 0);
    auto dz = Vec3(0, 0, max[2] - min[2]);

    sides->add(make_shared<Quadrilateral>(point3(min[0], min[1], max[2]),  dx,  dy, mat)); // front
    sides->add(make_shared<Quadrilateral>(point3(max[0], min[1], max[2]), -dz,  dy, mat)); // right
    sides->add(make_shared<Quadrilateral>(point3(max[0], min[1], min[2]), -dx,  dy, mat)); // back
    sides->add(make_shared<Quadrilateral>(point3(min[0], min[1], min[2]),  dz,  dy, mat)); // left
    sides->add(make_shared<Quadrilateral>(point3(min[0], max[1], max[2]),  dx, -dz, mat)); // top
    sides->add(make_shared<Quadrilateral>(point3(min[0], min[1], min[2]),  dx,  dz, mat)); // bottom

    return sides;
}

#endif //QUAD_H

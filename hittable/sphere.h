#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"

// Spherical object
class Sphere : public Hittable
{
private:
    ray m_center{};
    double m_radius{};
    std::shared_ptr<Material> m_material{};
    AABB m_boundingBox{};

public:
    // Static sphere
    Sphere(const point3 &center, double r, const std::shared_ptr<Material> &material)
        : m_center{center, Vec3{0, 0, 0}},
          m_radius{r},
          m_material{material}
    {
        auto rVec{Vec3{r, r, r}};
        m_boundingBox = AABB(center - rVec, center + rVec);
    }

    // Moving sphere
    Sphere(const point3 &start, const point3 &end, double r, const std::shared_ptr<Material> &material)
        : m_center{start, end - start},
          m_radius{r},
          m_material{material}
    {
        auto rVec{Vec3{r, r, r}};
        m_boundingBox = AABB(AABB(m_center.at(0) - rVec, m_center.at(0) + rVec),
                             AABB(m_center.at(1) - rVec, m_center.at(1) + rVec));
    }

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override;

    static void getUV(double &u, double &v, const point3 &p)
    {
        auto theta{std::acos(-p[1])};
        auto phi{std::atan2(-p[2], p[0]) + std::numbers::pi};

        u = phi / (2 * std::numbers::pi);
        v = theta / std::numbers::pi;
    }

    [[nodiscard]] AABB boundingBox() const override
    {
        return m_boundingBox;
    }
};

#endif //SPHERE_H

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

    bool hit(const ray &r, double rayTMin, double rayTMax, hitRecord &rec) const override;

    [[nodiscard]] AABB boundingBox() const override
    {
        return m_boundingBox;
    }

    [[nodiscard]] const Vec3& centroid() const override
    {
        return m_center.getOrigin();
    }
};

#endif //SPHERE_H

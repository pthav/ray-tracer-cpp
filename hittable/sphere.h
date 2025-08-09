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
    Sphere(const point3 &center, double r, const std::shared_ptr<Material> &material);

    // Moving sphere
    Sphere(const point3 &start, const point3 &end, double r, const std::shared_ptr<Material> &material);

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override;

    [[nodiscard]] AABB boundingBox() const override;

    static void getUV(double &u, double &v, const point3 &p);
};

#endif //SPHERE_H

#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"

// Spherical object
class Sphere final : public Hittable
{
private:
    point3 m_center{};
    double m_radius{};
    std::shared_ptr<Material> m_material{};

public:
    Sphere(double x, double y, double z, double r, const std::shared_ptr<Material> &material)
        : m_center{x, y, z},
          m_radius{r},
          m_material{material}
    {
    }

    bool hit(const ray &r, double rayTMin, double rayTMax, hitRecord &rec) const override;
};

#endif //SPHERE_H

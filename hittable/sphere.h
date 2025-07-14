#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"

// Spherical object
class Sphere final : public Hittable
{
private:
    point3 m_centerStart{};
    point3 m_centerEnd{};
    double m_radius{};
    std::shared_ptr<Material> m_material{};

public:
    Sphere(const point3 &start, const point3 &end, double r, const std::shared_ptr<Material> &material)
        : m_centerStart{start},
          m_centerEnd{end},
          m_radius{r},
          m_material{material}
    {
    }

    bool hit(const ray &r, double rayTMin, double rayTMax, hitRecord &rec) const override;
};

#endif //SPHERE_H

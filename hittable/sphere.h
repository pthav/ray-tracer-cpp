#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"

// Spherical object
class Sphere final : public Hittable
{
private:
    point3 m_center{};
    double m_radius{};

public:
    Sphere(double x, double y, double z, double r): m_center{x, y, z}, m_radius{r}
    {
    }

    bool hit(const ray &r, double rayTMin, double rayTMax, hitRecord &rec) const override;
};

#endif //SPHERE_H

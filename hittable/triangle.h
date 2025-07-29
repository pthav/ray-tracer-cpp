#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "quadrilateral.h"

class Triangle : public Quadrilateral
{
public:
    Triangle(const point3 &origin, const Vec3 &u, const Vec3 &v, const std::shared_ptr<Material> &material)
        : Quadrilateral(origin, u, v, material)
    {
    }

    bool isInside(double a, double b, hitRecord &rec) const override
    {
        if (a > 0.0 && b > 0.0 && (a + b) < 1.0)
        {
            rec.m_u = a;
            rec.m_v = b;
            return true;
        }
        return false;
    }
};

#endif

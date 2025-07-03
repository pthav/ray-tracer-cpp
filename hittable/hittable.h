#ifndef HITTABLE_H
#define HITTABLE_H
#include "../vector/ray.h"
#include "../vector/vector.h"

// hitRecord stores information about a ray intersection with an object
struct hitRecord
{
    point3 m_intersection{};
    Vec3 m_normal{};
    bool m_isFrontFace{};
    double m_t{};
};

// hittable defines a base class for objects
class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(const ray &r, double rayTMin, double rayTMax, hitRecord &rec) const = 0;

    // Set the normal to always face away from the ray
    // and store whether the intersection occurs on the front face
    static void setNormal(const ray &r, const Vec3 &n, hitRecord &rec)
    {
        // Check which side of object hit
        if (dot(n, r.getDirection()) < 0)
        {
            rec.m_normal = n;
            rec.m_isFrontFace = true;
        } else
        {
            rec.m_normal = -n;
            rec.m_isFrontFace = false;
        }
    }
};

#endif //HITTABLE_H

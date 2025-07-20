#ifndef HITTABLE_H
#define HITTABLE_H
#include <memory>

#include "../utility/aabb.h"
#include "../vector/ray.h"
#include "../vector/vector.h"

class Material;

// hitRecord stores information about a ray intersection with an object
struct hitRecord
{
    point3 m_intersection{};
    Vec3 m_normal{};
    std::shared_ptr<Material> m_material{};
    bool m_isFrontFace{};
    double m_t{};
};

// hittable defines a base class for objects
class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(const ray &r, Interval rayT, hitRecord &rec) const = 0;

    [[nodiscard]] virtual AABB boundingBox() const = 0;

    [[nodiscard]] virtual const Vec3& centroid() const = 0;

    // Set the normal to always face away from the ray
    // and store whether the intersection occurs on the front face
    static void setNormal(const ray &r, const Vec3 &n, hitRecord &rec)
    {
        rec.m_isFrontFace = dot(r.getDirection(), n) < 0;
        rec.m_normal = rec.m_isFrontFace ? n : -n;
    }
};

#endif //HITTABLE_H

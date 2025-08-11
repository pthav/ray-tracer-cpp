#ifndef AABB_H
#define AABB_H
#include "interval.h"
#include "../vector/vector.h"
#include "../vector/ray.h"

class AABB
{
public:
    Interval m_x, m_y, m_z;

    AABB();

    AABB(const Interval &x, const Interval &y, const Interval &z);

    AABB(const point3 &a, const point3 &b);

    AABB(const AABB &box0, const AABB &box1);

    AABB(const AABB &box, const point3 &point);

    AABB(const point3 &point, const AABB &box);

    [[nodiscard]] const Interval &axisInterval(int n) const;

    [[nodiscard]] bool hit(const ray &r, Interval rayT) const;

    [[nodiscard]] int longestAxis() const;

    [[nodiscard]] double surfaceArea() const;

    [[nodiscard]] double centroid(int axis) const;

    static const AABB empty, universe;

private:
    void padToMinimums();
};

inline const AABB AABB::empty = AABB(Interval::empty, Interval::empty, Interval::empty);
inline const AABB AABB::universe = AABB(Interval::universe, Interval::universe, Interval::universe);

inline AABB operator+(const AABB &bbox, const Vec3 &offset)
{
    return {bbox.m_x + offset[0], bbox.m_y + offset[1], bbox.m_z + offset[2]};
}

inline AABB operator+(const Vec3 &offset, const AABB &bbox)
{
    return bbox + offset;
}

#endif

#ifndef AABB_H
#define AABB_H
#include "interval.h"
#include "../vector/vector.h"
#include "../vector/ray.h"


class AABB
{
private:
    Interval m_x{};
    Interval m_y{};
    Interval m_z{};

public:
    AABB() = default;

    AABB(Interval x, Interval y, Interval z)
        : m_x{x}, m_y{y}, m_z{z}
    {
    }

    AABB(const point3 &point1, const point3 &point2)
        : m_x{Interval(point1[0], point2[0])}, m_y{Interval(point1[1], point2[1])}, m_z{Interval(point1[2], point2[2])}
    {
    }

    AABB(const AABB &aabb1, const AABB &aabb2)
        : m_x{Interval(aabb1.m_x, aabb2.m_x)}, m_y{Interval(aabb1.m_y, aabb2.m_y)}, m_z{Interval(aabb1.m_z, aabb2.m_z)}
    {
    }

    const Interval &operator[](size_t i) const
    {
        if (i == 0)
        {
            return m_x;
        }
        if (i == 1)
        {
            return m_y;
        }
        return m_z;
    }

    bool hit(const ray& r, const Interval& t) const;
};

#endif //AABB_H

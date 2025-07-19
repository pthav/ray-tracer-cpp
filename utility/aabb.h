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
    Vec3 m_centroid{};

    // Ensure minimum dimension sizes
    void expand()
    {
        double delta {0.0001};
        if (m_x.size() < delta)
        {
            m_x = m_x.expand(delta);
        }
        if (m_y.size() < delta)
        {
            m_y = m_y.expand(delta);
        }
        if (m_z.size() < delta)
        {
            m_z = m_z.expand(delta);
        }
    }

public:
    AABB() = default;

    AABB(Interval x, Interval y, Interval z)
        : m_x{x},
          m_y{y},
          m_z{z},
          m_centroid{calculateCentroid()}
    {
        expand();
    }

    AABB(const point3 &point1, const point3 &point2)
        : m_x{Interval(point1[0], point2[0])},
          m_y{Interval(point1[1], point2[1])},
          m_z{Interval(point1[2], point2[2])},
          m_centroid{calculateCentroid()}
    {
        expand();
    }

    AABB(const AABB &aabb1, const AABB &aabb2)
        : m_x{Interval(aabb1.m_x, aabb2.m_x)},
          m_y{Interval(aabb1.m_y, aabb2.m_y)},
          m_z{Interval(aabb1.m_z, aabb2.m_z)},
          m_centroid{calculateCentroid()}
    {
        expand();
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

    [[nodiscard]] Vec3 calculateCentroid() const
    {
        return Vec3(
                   m_x.m_start + m_x.m_end,
                   m_y.m_start + m_y.m_end,
                   m_z.m_start + m_z.m_end
               ) / 2.0;
    }

    [[nodiscard]] const Vec3 &centroid() const
    {
        return m_centroid;
    }

    [[nodiscard]] double surfaceArea() const
    {
        Vec3 bounds {
            m_x.m_end - m_x.m_start,
            m_y.m_end - m_y.m_start,
            m_z.m_end - m_z.m_start
        };

        return bounds[0] * bounds[1] + bounds[1] * bounds[2] + bounds[2] * bounds[0];
    }

    double hit(const ray &r, Interval &t) const;
};

#endif //AABB_H

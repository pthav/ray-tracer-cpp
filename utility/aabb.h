#ifndef AABB_H
#define AABB_H
#include "interval.h"
#include "../vector/vector.h"
#include "../vector/ray.h"

class AABB
{
public:
    Interval m_x, m_y, m_z;

    AABB() = default;

    AABB(const Interval &x, const Interval &y, const Interval &z)
        : m_x{x}, m_y{y}, m_z{z}
    {
        padToMinimums();
    }

    AABB(const point3 &a, const point3 &b)
    {
        m_x = (a[0] <= b[0]) ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
        m_y = (a[1] <= b[1]) ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
        m_z = (a[2] <= b[2]) ? Interval(a[2], b[2]) : Interval(b[2], a[2]);

        padToMinimums();
    }

    AABB(const AABB &box0, const AABB &box1)
    {
        m_x = Interval(box0.m_x, box1.m_x);
        m_y = Interval(box0.m_y, box1.m_y);
        m_z = Interval(box0.m_z, box1.m_z);
    }

    AABB(const AABB &box, const point3 &point)
    {
        m_x = Interval(box.m_x,point[0]);
        m_y = Interval(box.m_y,point[1]);
        m_z = Interval(box.m_z,point[2]);
    }

    AABB(const point3 &point, const AABB &box)
        : AABB(box, point)
    {
    }

    [[nodiscard]] const Interval &axisInterval(int n) const
    {
        if (n == 1) return m_y;
        if (n == 2) return m_z;
        return m_x;
    }

    [[nodiscard]] bool hit(const ray &r, Interval rayT) const;

    [[nodiscard]] int longestAxis() const
    {
        // Returns the index of the longest axis of the bounding box.

        if (m_x.size() > m_y.size())
            return m_x.size() > m_z.size() ? 0 : 2;
        else
            return m_y.size() > m_z.size() ? 1 : 2;
    }

    static const AABB empty, universe;

private:
    // Prevent a volumeless AABB
    void padToMinimums()
    {
        double delta = 0.0001;
        if (m_x.size() < delta) m_x = m_x.expand(delta);
        if (m_y.size() < delta) m_y = m_y.expand(delta);
        if (m_z.size() < delta) m_z = m_z.expand(delta);
    }
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

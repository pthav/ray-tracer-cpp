#include "aabb.h"

AABB::AABB() = default;

AABB::AABB(const Interval &x, const Interval &y, const Interval &z)
    : m_x{x}, m_y{y}, m_z{z}
{
    padToMinimums();
}

AABB::AABB(const point3 &a, const point3 &b)
{
    m_x = (a[0] <= b[0]) ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
    m_y = (a[1] <= b[1]) ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
    m_z = (a[2] <= b[2]) ? Interval(a[2], b[2]) : Interval(b[2], a[2]);

    padToMinimums();
}

AABB::AABB(const AABB &box0, const AABB &box1)
{
    m_x = Interval(box0.m_x, box1.m_x);
    m_y = Interval(box0.m_y, box1.m_y);
    m_z = Interval(box0.m_z, box1.m_z);
}

AABB::AABB(const AABB &box, const point3 &point)
{
    m_x = Interval(box.m_x,point[0]);
    m_y = Interval(box.m_y,point[1]);
    m_z = Interval(box.m_z,point[2]);
}

AABB::AABB(const point3 &point, const AABB &box)
    : AABB(box, point)
{
}

[[nodiscard]] const Interval &AABB::axisInterval(int n) const
{
    if (n == 1) return m_y;
    if (n == 2) return m_z;
    return m_x;
}

[[nodiscard]] int AABB::longestAxis() const
{
    if (m_x.size() > m_y.size())
        return m_x.size() > m_z.size() ? 0 : 2;
    return m_y.size() > m_z.size() ? 1 : 2;
}

double AABB::centroid(int axis) const
{
    if (axis == 0)
    {
        return (m_x.m_max + m_x.m_min) / 2.0;
    }
    if (axis == 1)
    {
        return (m_y.m_max + m_y.m_min) / 2.0;
    }
    return (m_z.m_max + m_z.m_min) / 2.0;
}


bool AABB::hit(const ray& r, Interval rayT) const {
    const point3& rayO = r.getOrigin();
    const Vec3&   rayInverseDir  = r.getInverseDirection();

    for (int axis = 0; axis < 3; axis++) {
        const Interval& ax = axisInterval(axis);
        const double dInv = rayInverseDir[axis];

        auto t0 = (ax.m_min - rayO[axis]) * dInv;
        auto t1 = (ax.m_max - rayO[axis]) * dInv;

        if (t1 < t0)
        {
            std::swap(t0, t1);
        }
        rayT.m_min = std::max(t0,rayT.m_min);
        rayT.m_max = std::min(t1,rayT.m_max);

        if (rayT.m_max <= rayT.m_min)
        {
            return false;
        }
    }
    return true;
}

void AABB::padToMinimums()
{
    double delta = 0.0001;
    if (m_x.size() < delta) m_x = m_x.expand(delta);
    if (m_y.size() < delta) m_y = m_y.expand(delta);
    if (m_z.size() < delta) m_z = m_z.expand(delta);
}

double AABB::surfaceArea() const
{
    return m_x.size() * m_y.size() + m_y.size() * m_z.size() + m_z.size() * m_x.size();
}

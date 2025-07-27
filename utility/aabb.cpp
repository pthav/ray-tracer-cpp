#include "aabb.h"

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

        // if (t0 < t1) {
        //     if (t0 > ray_t.m_min) ray_t.m_min = t0;
        //     if (t1 < ray_t.m_max) ray_t.m_max = t1;
        // } else {
        //     if (t1 > ray_t.m_min) ray_t.m_min = t1;
        //     if (t0 < ray_t.m_max) ray_t.m_max = t0;
        // }

        if (rayT.m_max <= rayT.m_min)
        {
            return false;
        }
    }
    return true;
}

// auto rd{r.getInverseDirection()};
// auto ro{r.getOrigin()};
// auto tx1 {(m_x.m_start - ro[0]) * rd[0]};
// auto tx2 {(m_x.m_end - ro[0]) * rd[0]};
// auto tMin{std::min(tx1,tx2)};
// auto tMax{std::max(tx1,tx2)};
// auto ty1 {(m_y.m_start - ro[1]) * rd[1]};
// auto ty2 {(m_y.m_end - ro[1]) * rd[1]};
// tMin = std::min(tMin, std::min(ty1,ty2));
// tMax = std::max(tMax, std::max(ty1,ty2));
// auto tz1 {(m_z.m_start - ro[2]) * rd[2]};
// auto tz2 {(m_z.m_end - ro[2]) * rd[2]};
// tMin = std::min(tMin, std::min(tz1,tz2));
// tMax = std::max(tMax, std::max(tz1,tz2));
//
// if (tMax >= tMin && tMin < 0.001 && tMax > 0)
// {
//     return tMin;
// }
// return 1e30f;
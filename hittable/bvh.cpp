#include "bvh.h"

bool BVH::hit(const ray &r, Interval rayT, hitRecord &rec) const
{
    if (!m_aabb.hit(r, rayT))
    {
        return false;
    }

    bool hitLeft = m_left->hit(r, rayT, rec);
    bool hitRight = m_right->hit(r, Interval(rayT.m_min, hitLeft ? rec.m_t : rayT.m_max), rec);

    return hitLeft || hitRight;
}

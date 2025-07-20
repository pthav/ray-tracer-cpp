#include "hittable_list.h"

void HittableList::add(const std::shared_ptr<Hittable> &object)
{
    m_objects.push_back(object);
    m_boundingBox = AABB(m_boundingBox, object->boundingBox());
}

bool HittableList::hit(const ray &r, Interval rayT, hitRecord &rec) const
{
    hitRecord tempRec{};
    bool hitAny = false;
    auto closest{rayT.m_end};

    // Find the closest object the ray hits
    for (const auto &object: m_objects)
    {
        auto hit{object->hit(r, rayT, tempRec)};
        hitAny |= hit;
        if (hit && tempRec.m_t < closest)
        {
            rec = tempRec;
            closest = rec.m_t;
        }
    }

    return hitAny;
}

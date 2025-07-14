#include "hittable_list.h"

void HittableList::add(const std::shared_ptr<Hittable> &object)
{
    m_objects.push_back(object);
    m_boundingBox = AABB(m_boundingBox, object->boundingBox());
}

bool HittableList::hit(const ray &r, double rayTMin, double rayTMax, hitRecord &rec) const
{
    hitRecord tempRec{};
    bool hitAny = false;
    auto closest{rayTMax};

    // Find the closest object the ray hits
    for (const auto &object: m_objects)
    {
        auto hit{object->hit(r, rayTMin, rayTMax, tempRec)};
        hitAny |= hit;
        if (hit && tempRec.m_t < closest)
        {
            rec = tempRec;
            closest = rec.m_t;
        }
    }

    return hitAny;
}

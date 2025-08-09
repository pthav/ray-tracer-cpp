#include "hittable_list.h"

HittableList::HittableList(std::vector<std::shared_ptr<Hittable> > objects) : m_objects{std::move(objects)}
{
}

void HittableList::add(const std::shared_ptr<Hittable> &object)
{
    m_objects.push_back(object);
    m_boundingBox = AABB(m_boundingBox, object->boundingBox());
}

bool HittableList::hit(const ray &r, Interval rayT, hitRecord &rec) const
{
    hitRecord tempRec{};
    bool hitAny = false;
    auto closest{rayT.m_max};

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

[[nodiscard]] AABB HittableList::boundingBox() const
{
    return m_boundingBox;
}

std::vector<std::shared_ptr<Hittable> > &HittableList::getObjects()
{
    return m_objects;
}

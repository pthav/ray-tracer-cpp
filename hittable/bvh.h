#ifndef BVH_H
#define BVH_H

#include "../utility/aabb.h"
#include "hittable.h"
#include "hittable_list.h"

#include <algorithm>


class BVH : public Hittable
{
public:
    explicit BVH(HittableList list) : BVH(list.getObjects(), 0, list.getObjects().size())
    {
    }

    BVH(std::vector<std::shared_ptr<Hittable> > &objects, size_t start, size_t end)
    {
        // Build the bounding box of the span of source objects.
        m_aabb = AABB::empty;
        for (size_t object_index = start; object_index < end; object_index++)
            m_aabb = AABB(m_aabb, objects[object_index]->boundingBox());

        int axis = m_aabb.longestAxis();

        auto comparator = (axis == 0)
                              ? boxXCompare
                              : (axis == 1)
                                    ? boxYCompare
                                    : boxZCompare;

        size_t object_span = end - start;

        if (object_span == 1)
        {
            m_left = m_right = objects[start];
        } else if (object_span == 2)
        {
            m_left = objects[start];
            m_right = objects[start + 1];
        } else
        {
            std::sort(std::begin(objects) + static_cast<int>(start), std::begin(objects) + static_cast<int>(end),
                      comparator);

            auto mid = start + object_span / 2;
            m_left = make_shared<BVH>(objects, start, mid);
            m_right = make_shared<BVH>(objects, mid, end);
        }
    }

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override;

    [[nodiscard]] AABB boundingBox() const override { return m_aabb; }

private:
    std::shared_ptr<Hittable> m_left;
    std::shared_ptr<Hittable> m_right;
    AABB m_aabb;

    static bool boxCompare(
        const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b, int axis_index
    )
    {
        auto a_axis_interval = a->boundingBox().axisInterval(axis_index);
        auto b_axis_interval = b->boundingBox().axisInterval(axis_index);
        return a_axis_interval.m_min < b_axis_interval.m_min;
    }

    static bool boxXCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b)
    {
        return boxCompare(a, b, 0);
    }

    static bool boxYCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b)
    {
        return boxCompare(a, b, 1);
    }

    static bool boxZCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b)
    {
        return boxCompare(a, b, 2);
    }
};


#endif

#include "bvh.h"
#include <algorithm>
#include <queue>

BVH::BVH(HittableList list)
    : m_objects{list.getObjects()},
      m_aabb{list.boundingBox()}
{
    size_t bitLength{0};
    size_t x{m_objects.size()};
    for (; x != 0; x >>= 1)
    {
        bitLength++;
    }
    m_nodes.resize(1 << (bitLength + 1));

    std::queue<work> queue{};
    queue.push(work{1, 0, m_objects.size()});

    while (!queue.empty())
    {
        work w{queue.front()};
        queue.pop();

        auto aabb{AABB::empty};
        for (size_t i = w.m_start; i < w.m_end; i++)
        {
            aabb = AABB(aabb, m_objects[i]->boundingBox());
        }
        m_nodes[w.m_node].m_aabb = aabb;

        int axis = aabb.longestAxis();

        auto comparator = (axis == 0)
                              ? boxXCompare
                              : (axis == 1)
                                    ? boxYCompare
                                    : boxZCompare;

        size_t span{w.m_end - w.m_start};
        size_t left = {w.m_node * 2};
        size_t right{w.m_node * 2 + 1};
        if (span == 1)
        {
            m_nodes[left] = m_nodes[right] = {m_objects[w.m_start]->boundingBox(), true, w.m_start};
        } else if (span == 2)
        {
            m_nodes[left] = {m_objects[w.m_start]->boundingBox(), true, w.m_start};
            m_nodes[right] = {m_objects[w.m_start + 1]->boundingBox(), true, w.m_start + 1};
        } else
        {
            std::sort(std::begin(m_objects) + w.m_start, std::begin(m_objects) + w.m_end,
                      comparator);

            auto mid = w.m_start + span / 2;
            queue.push(work{w.m_node * 2, w.m_start, mid});
            queue.push(work{w.m_node * 2 + 1, mid, w.m_end});
        }
    }
}

bool BVH::hit(const ray &r, Interval rayT, hitRecord &rec) const
{
    if (!m_aabb.hit(r, rayT))
    {
        return false;
    }

    bool hitSomething{false};
    double closest {rayT.m_max};
    std::queue<size_t> queue{};
    queue.push(2);
    queue.push(3);

    while (!queue.empty())
    {
        auto idx {queue.front()};
        queue.pop();

        auto node {m_nodes[idx]};
        if (!node.m_leaf)
        {
            if (node.m_aabb.hit(r, rayT))
            {
                queue.emplace(idx * 2);
                queue.emplace(idx * 2 + 1);
            }
        } else
        {
            if (m_objects[node.m_object]->hit(r, Interval(rayT.m_min, closest), rec))
            {
                hitSomething = true;
                closest = rec.m_t;
            }
        }
    }
    return hitSomething;
}

[[nodiscard]] AABB BVH::boundingBox() const
{
    return m_aabb;
}

bool BVH::boxCompare(
    const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b, int axis_index
)
{
    auto a_axis_interval = a->boundingBox().axisInterval(axis_index);
    auto b_axis_interval = b->boundingBox().axisInterval(axis_index);
    return a_axis_interval.m_min < b_axis_interval.m_min;
}

bool BVH::boxXCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b)
{
    return boxCompare(a, b, 0);
}

bool BVH::boxYCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b)
{
    return boxCompare(a, b, 1);
}

bool BVH::boxZCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b)
{
    return boxCompare(a, b, 2);
}

#include "bvh.h"
#include <algorithm>
#include <cassert>
#include <queue>

BVH::BVH(HittableList list)
    : m_objects{list.getObjects()},
      m_aabb{list.boundingBox()}
{
    m_nodes.resize(4 * m_objects.size());

    std::queue<work> queue{};
    queue.push(work{allocateNode(), 0, m_objects.size()});

    while (!queue.empty())
    {
        work w{queue.front()};
        queue.pop();

        auto aabb{AABB::empty};
        for (size_t i = w.m_start; i < w.m_end; i++)
        {
            aabb = AABB(aabb, m_objects[i]->boundingBox());
        }

        size_t span{w.m_end - w.m_start};
        assert(span > 0 && "degenerate span");
        int axis{};
        double splitPos {};
        auto splitCost {findSplit(aabb, w.m_start, w.m_end, axis, splitPos)};
        if (span <= m_maxLeafNodes || splitCost > (aabb.surfaceArea() * static_cast<int>(span)))
        {
            m_nodes[w.m_node] = makeLeaf(aabb, w.m_start, static_cast<int>(span));
        }else{
            size_t left{allocateNode()};
            size_t right{allocateNode()};
            m_nodes[w.m_node] = makeInternal(aabb, left, right);
            auto mid {partition(w.m_start, w.m_end, axis, splitPos)};
            assert(w.m_start < mid && mid < w.m_end && "degenerate partition");
            m_nodes[w.m_node] = makeInternal(aabb, left, right);
            queue.push(work{left, w.m_start, mid});
            queue.push(work{right, mid, w.m_end});
        }
    }
}

bool BVH::hit(const ray &r, Interval rayT, hitRecord &rec) const
{
    bool hitSomething{false};
    double closest{rayT.m_max};
    std::queue<size_t> queue{};
    queue.emplace(1);

    while (!queue.empty())
    {
        auto idx{queue.front()};
        queue.pop();

        auto n{m_nodes[idx]};
        if (n.m_primCount == 0)
        {
            if (n.m_aabb.hit(r, rayT))
            {
                queue.emplace(n.m_left);
                queue.emplace(n.m_right);
            }
        } else
        {
            for (auto i{n.m_firstPrim}; i < n.m_firstPrim + n.m_primCount; i++)
            {
                if (m_objects[i]->hit(r, Interval(rayT.m_min, closest), rec))
                {
                    hitSomething = true;
                    closest = rec.m_t;
                }
            }
        }
    }
    return hitSomething;
}

[[nodiscard]] AABB BVH::boundingBox() const
{
    return m_aabb;
}

double BVH::evaluateSplit(size_t left, size_t right, int axis, double splitPos) const
{
    AABB leftBox{AABB::empty};
    AABB rightBox{AABB::empty};
    int leftCount{};
    int rightCount{};

    for (size_t i{left}; i < right; ++i)
    {
        if (m_objects[i]->boundingBox().centroid(axis) < splitPos)
        {
            ++leftCount;
            leftBox = AABB(leftBox, m_objects[i]->boundingBox());
        }else
        {
            ++rightCount;
            rightBox = AABB(rightBox, m_objects[i]->boundingBox());
        }
    }

    auto cost {leftCount * leftBox.surfaceArea() + rightCount * rightBox.surfaceArea()};
    return (cost > 0) ? cost : std::numeric_limits<double>::infinity();
}

double BVH::findSplit(const AABB& subtree, size_t left, size_t right, int &axis, double &splitPos) const
{
    // auto numBins{4};
    double bestSplit{};
    double bestCost{std::numeric_limits<double>::infinity()};

    for (auto a{0}; a < 3; ++a)
    {
        for (size_t i{left}; i < right; ++i)
        {
            auto candidate {m_objects[i]->boundingBox().centroid(a)};
            if (auto cost {evaluateSplit(left,right,a,candidate)}; cost < bestCost)
            {
                axis = a;
                bestSplit = candidate;
                bestCost = cost;
            }
        }
    }
    splitPos = bestSplit;
    return bestCost;
}

size_t BVH::partition(size_t start, size_t end, int axis, double splitPos)
{
    size_t first {start};
    while (first < end)
    {
        if (m_objects[first]->boundingBox().centroid(axis) >= splitPos)
        {
            break;
        }
        ++first;
    }

    if (first == end)
    {
        return first;
    }

    for (auto i {first+1}; i < end; ++i)
    {
        if (m_objects[i]->boundingBox().centroid(axis) < splitPos)
        {
            std::swap(m_objects[i], m_objects[first]);
            ++first;
        }
    }
    return first;
}

size_t BVH::allocateNode()
{
    auto next{m_next.fetch_add(1)};
    assert(next < m_nodes.size());
    return next;
}

node BVH::makeInternal(const AABB &bounds, size_t left, size_t right)
{
    node result{};
    result.m_aabb = bounds;
    result.m_left = left;
    result.m_right = right;
    result.m_primCount = 0;
    return result;
}


node BVH::makeLeaf(const AABB &bounds, size_t start, int primCount)
{
    node result{};
    result.m_aabb = bounds;
    result.m_firstPrim = start;
    result.m_primCount = primCount;
    return result;
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

#ifndef BVH_H
#define BVH_H

#include <atomic>

#include "../utility/aabb.h"
#include "hittable.h"
#include "hittable_list.h"

struct node
{
    AABB m_aabb{AABB::empty};
    size_t m_left{};
    size_t m_right{};
    size_t m_firstPrim{};
    int m_primCount{};
};

struct work
{
    size_t m_node{};
    size_t m_start{};
    size_t m_end{};
};

class BVH : public Hittable
{
public:
    static int m_maxLeafNodes;

    explicit BVH(HittableList list);

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override;

    [[nodiscard]] AABB boundingBox() const override;

private:
    std::vector<std::shared_ptr<Hittable> > m_objects;
    std::vector<node> m_nodes{};
    std::atomic<size_t> m_next{1};
    AABB m_aabb{};

    [[nodiscard]] double evaluateSplit(size_t left, size_t right, int axis, double splitPos) const;

    double findSplit(const AABB& subtree, size_t left, size_t right, int &axis, double &splitPos) const;

    size_t partition(size_t start, size_t end, int axis, double splitPos);

    size_t allocateNode();

    static node makeInternal(const AABB &bounds, size_t left, size_t right);

    static node makeLeaf(const AABB &bounds, size_t start, int primCount);

    static bool boxCompare(
        const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b, int axis_index
    );

    static bool boxXCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b);

    static bool boxYCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b);

    static bool boxZCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b);
};

inline int BVH::m_maxLeafNodes{4};

#endif

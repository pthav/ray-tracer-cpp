#ifndef BVH_H
#define BVH_H

#include <vector>

#include "hittable.h"
#include "hittable_list.h"

// The bin struct is used for calculating the best split
struct bin
{
    AABB m_aabb;
    int m_count {0};
};

class BVH : public Hittable
{
private:
    AABB m_aabb{};
    std::vector<std::shared_ptr<Hittable> > m_children{};
    std::shared_ptr<BVH> m_left{};
    std::shared_ptr<BVH> m_right{};
    int m_count{};

public:
    static int m_bins; // The number of bins to use when calculating the best split

    BVH() = default;

    // This constructor is used for starting BVH tree construction from a root node
    explicit BVH(HittableList list)
        : m_aabb{list.boundingBox()},
          m_children{list.getObjects()},
          m_count{static_cast<int>(m_children.size())}
    {
        subdivide();
    }

    [[nodiscard]] AABB boundingBox() const override
    {
        return m_aabb;
    };

    [[nodiscard]] bool isLeaf() const
    {
        return m_count > 0;
    }

    [[nodiscard]] double sahCost() const
    {
        return m_count * m_aabb.surfaceArea();
    }

    [[nodiscard]] const Vec3 &centroid() const override
    {
        return m_aabb.centroid();
    }

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override;

    void subdivide();

    double bestSplit(int &a, double &splitPos) const;
};

inline int BVH::m_bins{8};
#endif //BVH_H

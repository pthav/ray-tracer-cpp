#ifndef BVH_H
#define BVH_H

#include "../utility/aabb.h"
#include "hittable.h"
#include "hittable_list.h"

struct node
{
    AABB m_aabb{AABB::empty};
    bool m_leaf{false};
    size_t m_object{};
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
    explicit BVH(HittableList list);

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override;

    [[nodiscard]] AABB boundingBox() const override;

private:
    std::vector<std::shared_ptr<Hittable>> m_objects;
    std::vector<node> m_nodes{};
    AABB m_aabb{};

    static bool boxCompare(
        const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b, int axis_index
    );

    static bool boxXCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b);

    static bool boxYCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b);

    static bool boxZCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b);
};


#endif

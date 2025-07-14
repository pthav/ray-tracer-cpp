#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <utility>
#include <vector>

#include "hittable.h"

class HittableList : public Hittable
{
private:
    std::vector<std::shared_ptr<Hittable> > m_objects{};
    AABB m_boundingBox {};

public:
    HittableList() = default;

    explicit HittableList(std::vector<std::shared_ptr<Hittable> > objects) : m_objects{std::move(objects)}
    {
    }

    void add(const std::shared_ptr<Hittable> &object);

    bool hit(const ray &r, double rayTMin, double rayTMax, hitRecord &rec) const override;

    AABB boundingBox() const override
    {
        return m_boundingBox;
    }
};

#endif //HITTABLE_LIST_H

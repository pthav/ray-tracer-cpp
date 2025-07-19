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

    [[nodiscard]] AABB boundingBox() const override
    {
        return m_boundingBox;
    }

    [[nodiscard]] const Vec3& centroid() const override
    {
        return m_boundingBox.centroid();
    }

    std::vector<std::shared_ptr<Hittable>> &getObjects()
    {
        return m_objects;
    }
};

#endif //HITTABLE_LIST_H

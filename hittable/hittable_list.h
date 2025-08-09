#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"

class HittableList : public Hittable
{
private:
    std::vector<std::shared_ptr<Hittable> > m_objects{};
    AABB m_boundingBox{};

public:
    HittableList() = default;

    explicit HittableList(std::vector<std::shared_ptr<Hittable> > objects);

    void add(const std::shared_ptr<Hittable> &object);

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override;

    [[nodiscard]] AABB boundingBox() const override;

    std::vector<std::shared_ptr<Hittable> > &getObjects();
};

#endif //HITTABLE_LIST_H

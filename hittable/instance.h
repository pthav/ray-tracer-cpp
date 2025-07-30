#ifndef INSTANCE_H
#define INSTANCE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "hittable.h"

class Instance : public Hittable
{
public:
    explicit Instance(const std::shared_ptr<Hittable> &object, const Vec3 &t, const Vec3 &r = Vec3{0, 0, 0},
                      const Vec3 &s = Vec3{1, 1, 1}
    );

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override;

    [[nodiscard]] AABB boundingBox() const override;

private:
    glm::mat4 m_transform;
    glm::mat4 m_inverse{};
    std::shared_ptr<Hittable> m_object;
    AABB m_aabb{};

    static Vec3 transformVec3(const glm::mat4 &m, const glm::vec3 &v, float w);
};

#endif //INSTANCE_H

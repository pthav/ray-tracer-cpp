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
    )
        : m_transform{glm::identity<glm::mat4>()},
          m_object{object},
          m_aabb{AABB()}
    {
        m_transform = glm::translate(m_transform, glm::vec3(t[0], t[1], t[2]));
        // Add rotations in the order Z->X->Y to achieve an application order of Y->X->Z
        for (int i{2}; i < 5; i++)
        {
            auto a{i % 3};
            auto axis{glm::vec3()};
            axis[a] = 1.0f;
            m_transform = glm::rotate(m_transform, glm::radians(static_cast<float>(r[a])), axis);
        }
        m_transform = glm::scale(m_transform, glm::vec3(s[0], s[1], s[2]));
        m_inverse = glm::inverse(m_transform);


        // Get all eight original bounding box corners to compute the new bounding box
        auto boundingBox{object->boundingBox()};
        auto xInterval{boundingBox.axisInterval(0)};
        auto yInterval{boundingBox.axisInterval(1)};
        auto zInterval{boundingBox.axisInterval(2)};
        for (int x{0}; x < 2; x++)
        {
            auto xPoint{x == 0 ? xInterval.m_min : xInterval.m_max};
            for (int y{0}; y < 2; y++)
            {
                auto yPoint{y == 0 ? yInterval.m_min : yInterval.m_max};
                for (int z{0}; z < 2; z++)
                {
                    auto zPoint{z == 0 ? zInterval.m_min : zInterval.m_max};
                    auto pointHomogenous{glm::vec4{xPoint, yPoint, zPoint, 1}};
                    auto transformedPointHomogenous{m_transform * pointHomogenous};
                    point3 transformedPoint{};
                    transformedPoint[0] = transformedPointHomogenous[0] / transformedPointHomogenous[3];
                    transformedPoint[1] = transformedPointHomogenous[1] / transformedPointHomogenous[3];
                    transformedPoint[2] = transformedPointHomogenous[2] / transformedPointHomogenous[3];
                    m_aabb = AABB(m_aabb, transformedPoint);
                }
            }
        }
    }

    bool hit(const ray &r, Interval rayT, hitRecord &rec) const override
    {
        if (!m_aabb.hit(r, rayT))
        {
            return false;
        }

        // Translate ray direction and origin into object local coordinates
        auto globalDirection{r.getDirection()};
        Vec3 localDirection{
            transformVec3(m_inverse, glm::vec3{globalDirection[0], globalDirection[1], globalDirection[2]}, 0)
        };
        auto globalOrigin{r.getOrigin()};
        point3 localOrigin{transformVec3(m_inverse, glm::vec3{globalOrigin[0], globalOrigin[1], globalOrigin[2]}, 1)};

        // Perform hit detection on object in local coordinates
        if (!m_object->hit(ray{localOrigin, localDirection, r.getTime()}, rayT, rec))
        {
            return false;
        }

        // Translate intersection and normal back to global coordinates
        rec.m_intersection = transformVec3(m_transform, glm::vec3{
                                               rec.m_intersection[0], rec.m_intersection[1], rec.m_intersection[2]
                                           }, 1);
        rec.m_normal = normalize(transformVec3(glm::transpose(m_inverse),
                                               glm::vec3{rec.m_normal[0], rec.m_normal[1], rec.m_normal[2]}, 0));

        // t of intersection may be incorrect for non-uniform scaling
        rec.m_t = (rec.m_intersection - globalOrigin).length();

        return true;
    }

    [[nodiscard]] AABB boundingBox() const override
    {
        return m_aabb;
    }

private:
    glm::mat4 m_transform;
    glm::mat4 m_inverse{};
    std::shared_ptr<Hittable> m_object;
    AABB m_aabb{};

    static Vec3 transformVec3(const glm::mat4 &m, const glm::vec3 &v, float w)
    {
        auto temp = m * glm::vec4{v, w};
        return Vec3{temp[0], temp[1], temp[2]} / (w != 0 ? temp.w : 1.0f);
    }
};

#endif //INSTANCE_H

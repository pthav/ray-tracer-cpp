#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "hittable.h"
#include "../materials/Isotropic.h"
#include "../textures/texture.h"
#include "../utility/random.h"

class ConstantMedium : public Hittable
{
public:
    ConstantMedium(const std::shared_ptr<Hittable> &boundary, double density, const std::shared_ptr<Texture> &tex)
        : boundary(boundary), neg_inv_density(-1 / density),
          phase_function(std::make_shared<Isotropic>(tex))
    {
    }

    ConstantMedium(const std::shared_ptr<Hittable> &boundary, double density, const color &albedo)
        : boundary(boundary), neg_inv_density(-1 / density),
          phase_function(std::make_shared<Isotropic>(albedo))
    {
    }

    bool hit(const ray &r, Interval ray_t, hitRecord &rec) const override
    {
        hitRecord rec1, rec2;

        // Make sure it's not a glancing hit by checking it can hit the AABB twice
        if (!boundary->hit(r, Interval::universe, rec1))
            return false;

        if (!boundary->hit(r, Interval(rec1.m_t + 0.0001, std::numeric_limits<double>::infinity()), rec2))
            return false;

        if (rec1.m_t < ray_t.m_min) rec1.m_t = ray_t.m_min;
        if (rec2.m_t > ray_t.m_max) rec2.m_t = ray_t.m_max;

        if (rec1.m_t >= rec2.m_t)
            return false;

        if (rec1.m_t < 0)
            rec1.m_t = 0;

        auto ray_length = r.getDirection().length();
        auto distance_inside_boundary = (rec2.m_t - rec1.m_t) * ray_length;
        auto hit_distance = neg_inv_density * std::log(Random::randomDouble());

        if (hit_distance > distance_inside_boundary)
            return false;

        rec.m_t = rec1.m_t + hit_distance / ray_length;
        rec.m_intersection = r.at(rec.m_t);

        rec.m_normal = Vec3(1, 0, 0); // arbitrary
        rec.m_isFrontFace = true; // also arbitrary
        rec.m_material = phase_function;

        return true;
    }

    AABB boundingBox() const override { return boundary->boundingBox(); }

private:
    std::shared_ptr<Hittable> boundary;
    double neg_inv_density;
    std::shared_ptr<Material> phase_function;
};

#endif //CONSTANT_MEDIUM_H

#include "constant_medium.h"

ConstantMedium::ConstantMedium(const std::shared_ptr<Hittable> &boundary, double density,
                               const std::shared_ptr<Texture> &tex)
    : boundary(boundary), negInvDensity(-1 / density),
      phaseFunction(std::make_shared<isotropic>(tex))
{
}

ConstantMedium::ConstantMedium(const std::shared_ptr<Hittable> &boundary, double density, const color &albedo)
    : boundary(boundary), negInvDensity(-1 / density),
      phaseFunction(std::make_shared<isotropic>(albedo))
{
}

bool ConstantMedium::hit(const ray &r, Interval ray_t, hitRecord &rec) const
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
    auto hit_distance = negInvDensity * std::log(Random::randomDouble());

    if (hit_distance > distance_inside_boundary)
        return false;

    rec.m_t = rec1.m_t + hit_distance / ray_length;
    rec.m_intersection = r.at(rec.m_t);

    rec.m_normal = Vec3(1, 0, 0); // arbitrary
    rec.m_isFrontFace = true; // also arbitrary
    rec.m_material = phaseFunction;

    return true;
}

[[nodiscard]] AABB ConstantMedium::boundingBox() const
{
    return boundary->boundingBox();
}

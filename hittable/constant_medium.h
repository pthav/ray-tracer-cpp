#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "hittable.h"
#include "../materials/Isotropic.h"
#include "../textures/texture.h"
#include "../utility/random.h"

class ConstantMedium : public Hittable
{
public:
    ConstantMedium(const std::shared_ptr<Hittable> &boundary, double density, const std::shared_ptr<Texture> &tex);

    ConstantMedium(const std::shared_ptr<Hittable> &boundary, double density, const color &albedo);

    bool hit(const ray &r, Interval ray_t, hitRecord &rec) const override;

    [[nodiscard]] AABB boundingBox() const override;

private:
    std::shared_ptr<Hittable> boundary;
    double negInvDensity;
    std::shared_ptr<Material> phaseFunction;
};

#endif //CONSTANT_MEDIUM_H

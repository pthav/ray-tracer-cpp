#ifndef ISOTROPIC_H
#define ISOTROPIC_H
#include "../textures/solid_texture.h"
#include "../textures/texture.h"
#include "material.h"
#include "../utility/random.h"

class isotropic : public Material
{
public:
    explicit isotropic(const color &albedo) : tex(std::make_shared<SolidTexture>(albedo))
    {
    }

    explicit isotropic(const std::shared_ptr<Texture> &tex) : tex(tex)
    {
    }

    bool scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered)
    override
    {
        scattered = ray(record.m_intersection,
                        Vec3{Random::randomDouble(), Random::randomDouble(), Random::randomDouble()}, in.getTime());
        attenuation = tex->value(record.m_u, record.m_v, record.m_intersection);
        return true;
    }

private:
    std::shared_ptr<Texture> tex;
};

#endif //ISOTROPIC_H

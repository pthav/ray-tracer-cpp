#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H
#include "material.h"
#include "../textures/texture.h"
#include "../textures/solid_texture.h"

class DiffuseLight : public Material
{
public:
    explicit DiffuseLight(const std::shared_ptr<Texture> &texture)
        : m_texture{texture}
    {
    }

    explicit DiffuseLight(const color &color)
        : m_texture{std::make_shared<SolidTexture>(color)}
    {
    }

    color emit(double u, double v, const point3 &p) override
    {
        return m_texture->value(u,v,p);
    }

private:
    std::shared_ptr<Texture> m_texture{};
};

#endif //DIFFUSE_LIGHT_H

#ifndef DIFFUSE_H
#define DIFFUSE_H
#include "material.h"
#include "../textures/solid.h"
#include "../textures/texture.h"

class DiffuseMaterial : public Material
{
public:
    // Solid Texture
    explicit DiffuseMaterial(const color &albedo): m_texture{std::make_shared<SolidTexture>(albedo)}{}

    // Any Texture
    explicit DiffuseMaterial(const std::shared_ptr<Texture> &texture): m_texture{texture}{}

    bool scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered) override;

private:
    std::shared_ptr<Texture> m_texture{};

    static Vec3 cosineWeightedSample(const hitRecord &record);
};

#endif //DIFFUSE_H

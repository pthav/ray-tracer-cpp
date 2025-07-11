#ifndef DIFFUSE_H
#define DIFFUSE_H
#include "material.h"

class DiffuseMaterial : public Material
{
private:
    color m_albedo{};

    static Vec3 cosineWeightedSample(const hitRecord &record);

public:
    explicit DiffuseMaterial(const color &albedo): m_albedo{albedo}{}

    bool scatter(const ray &in, const hitRecord &record, color &attenuation, ray &scattered) override;
};

#endif //DIFFUSE_H

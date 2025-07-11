#ifndef MATERIAL_H
#define MATERIAL_H
#include <random>

#include "../hittable/hittable.h"
#include "../vector/color.h"
#include "../vector/ray.h"

class Material
{
protected:
    static std::mt19937 m_gen;
    static std::uniform_real_distribution<double> m_distribution;

public:
    virtual ~Material() = default;
    virtual bool scatter(const ray& in, const hitRecord& record, color& attenuation, ray& scattered)
    {
        return false;
    }
};


#endif //MATERIAL_H

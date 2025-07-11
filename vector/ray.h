#ifndef RAY_H
#define RAY_H
#include "vector.h"

class ray
{
private:
    point3 m_origin{};
    Vec3 m_direction{};
    double m_refractionIndex{};

public:
    ray() = default;

    ray(const point3 &origin, const Vec3 &direction, const double refractionIndex = 1.0003)
    : m_origin{origin}, m_direction{direction}, m_refractionIndex{refractionIndex}
    {
    }

    [[nodiscard]] const point3 &getOrigin() const
    {
        return m_origin;
    }

    [[nodiscard]] const Vec3 &getDirection() const
    {
        return m_direction;
    }

    [[nodiscard]] double getRefractionIndex() const
    {
        return m_refractionIndex;
    }

    [[nodiscard]] point3 at(double t) const
    {
        return m_origin + t * m_direction;
    }
};

#endif

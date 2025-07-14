#ifndef RAY_H
#define RAY_H
#include "vector.h"

class ray
{
private:
    point3 m_origin{};
    Vec3 m_direction{};
    double m_refractionIndex{};
    double m_timeOrigin{};

public:
    ray() = default;

    ray(const point3 &origin, const Vec3 &direction, double timeOrigin)
    : m_origin{origin}, m_direction{direction}, m_timeOrigin{timeOrigin}
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

    [[nodiscard]] double getTime() const
    {
        return m_timeOrigin;
    }

    [[nodiscard]] point3 at(double t) const
    {
        return m_origin + t * m_direction;
    }
};

#endif

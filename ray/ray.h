#ifndef RAY_H
#define RAY_H
#include "vector.h"

class ray
{
private:
    point3 origin{};
    Vec3 direction{};

public:
    ray() = default;

    ray(point3 origin, Vec3 direction) : origin{origin}, direction{direction}
    {
    }

    [[nodiscard]] const point3 &getOrigin() const
    {
        return origin;
    }

    [[nodiscard]] const Vec3 &getDirection() const
    {
        return direction;
    }

    [[nodiscard]] point3 at(double t) const
    {
        return origin + t * direction;
    }
};

#endif

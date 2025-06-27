#ifndef VECTOR_H
#define VECTOR_H
#include <iosfwd>

class vec3
{
private:
    double v[3]{};

public:
    explicit vec3(double x = 0, double y = 0, double z = 0) : v{x, y, z}
    {
    }

    const double &operator[](int i) const;

    double &operator[](int i);

    vec3 operator-() const;

    vec3 &operator*=(double scalar);

    vec3 &operator/=(double scalar);

    vec3 &operator+=(const vec3 &other);

    vec3 &operator-=(const vec3 &other);

    [[nodiscard]] double length() const;

    [[nodiscard]] double lengthSquared() const;

    friend vec3 operator*(const vec3 &left, const vec3 &right);

    friend vec3 operator*(double scalar, const vec3 &v);

    friend vec3 operator*(const vec3 &v, double scalar);

    friend vec3 operator/(const vec3 &v, double scalar);

    friend vec3 operator+(const vec3 &left, const vec3 &right);

    friend vec3 operator-(const vec3 &left, const vec3 &right);

    friend double dot(const vec3 &left, const vec3 &right);

    friend vec3 cross(const vec3 &left, const vec3 &right);

    friend vec3 normalize(const vec3 &v);

    friend std::ostream &operator<<(std::ostream &os, const vec3 &v);
};

#endif

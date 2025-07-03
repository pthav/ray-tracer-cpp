#ifndef VECTOR_H
#define VECTOR_H
#include <iosfwd>

class Vec3
{
private:
    double m_v[3]{};

public:
    explicit Vec3(double x = 0, double y = 0, double z = 0) : m_v{x, y, z}
    {
    }

    const double &operator[](int i) const;

    double &operator[](int i);

    Vec3 operator-() const;

    Vec3 &operator*=(double scalar);

    Vec3 &operator/=(double scalar);

    Vec3 &operator+=(const Vec3 &other);

    Vec3 &operator-=(const Vec3 &other);

    [[nodiscard]] double length() const;

    [[nodiscard]] double lengthSquared() const;

    friend Vec3 operator*(const Vec3 &left, const Vec3 &right);

    friend Vec3 operator*(double scalar, const Vec3 &v);

    friend Vec3 operator*(const Vec3 &v, double scalar);

    friend Vec3 operator/(const Vec3 &v, double scalar);

    friend Vec3 operator+(const Vec3 &left, const Vec3 &right);

    friend Vec3 operator-(const Vec3 &left, const Vec3 &right);

    friend double dot(const Vec3 &left, const Vec3 &right);

    friend Vec3 cross(const Vec3 &left, const Vec3 &right);

    friend Vec3 normalize(const Vec3 &v);

    friend std::ostream &operator<<(std::ostream &os, const Vec3 &v);
};

using point3 = Vec3;

#endif

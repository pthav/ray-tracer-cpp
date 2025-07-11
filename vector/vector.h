#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
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

inline Vec3 reflect(const Vec3 &in, const Vec3 &n)
{
    auto reflection {in - n * 2 * dot(in,n)};
    return normalize(reflection);
}

inline Vec3 refract(const Vec3& in, const Vec3& n, double refractiveRatio) {
    auto cosTheta = std::fmin(dot(-in, n), 1.0);
    Vec3 rOutPerp =  refractiveRatio * (in + cosTheta*n);
    Vec3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.lengthSquared())) * n;
    return rOutPerp + rOutParallel;
}

using point3 = Vec3;

#endif

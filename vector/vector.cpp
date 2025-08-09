#include "vector.h"

#include <cmath>
#include <iterator>
#include <iostream>

Vec3::Vec3(double x, double y, double z) : m_v{x, y, z}
{
}

const double &Vec3::operator[](int i) const
{
    return m_v[i];
}

double &Vec3::operator[](int i)
{
    return m_v[i];
}

Vec3 Vec3::operator-() const
{
    return Vec3{-m_v[0], -m_v[1], -m_v[2]};
}

Vec3 &Vec3::operator*=(double scalar)
{
    m_v[0] *= scalar;
    m_v[1] *= scalar;
    m_v[2] *= scalar;
    return *this;
}

Vec3 &Vec3::operator/=(double scalar)
{
    m_v[0] /= scalar;
    m_v[1] /= scalar;
    m_v[2] /= scalar;
    return *this;
}

Vec3 &Vec3::operator+=(const Vec3 &other)
{
    m_v[0] += other[0];
    m_v[1] += other[1];
    m_v[2] += other[2];
    return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &other)
{
    m_v[0] -= other[0];
    m_v[1] -= other[1];
    m_v[2] -= other[2];
    return *this;
}

double Vec3::length() const
{
    return std::sqrt(lengthSquared());
}

double Vec3::lengthSquared() const
{
    return m_v[0] * m_v[0] + m_v[1] * m_v[1] + m_v[2] * m_v[2];
}

Vec3 operator*(const Vec3 &left, const Vec3 &right)
{
    return Vec3{left[0] * right[0], left[1] * right[1], left[2] * right[2]};
}

Vec3 operator*(double scalar, const Vec3 &v)
{
    return Vec3{scalar * v[0], scalar * v[1], scalar * v[2]};
}

Vec3 operator*(const Vec3 &v, double scalar)
{
    return scalar * v;
}

Vec3 operator/(const Vec3 &v, double scalar)
{
    return v * (1 / scalar);
}

Vec3 operator+(const Vec3 &left, const Vec3 &right)
{
    return Vec3{left[0] + right[0], left[1] + right[1], left[2] + right[2]};
}

Vec3 operator-(const Vec3 &left, const Vec3 &right)
{
    return left + -right;
}

double dot(const Vec3 &left, const Vec3 &right)
{
    return left[0] * right[0] + left[1] * right[1] + left[2] * right[2];
}

Vec3 cross(const Vec3 &left, const Vec3 &right)
{
    return Vec3{
        left[1] * right[2] - left[2] * right[1],
        left[2] * right[0] - left[0] * right[2],
        left[0] * right[1] - left[1] * right[0]
    };
}

Vec3 normalize(const Vec3 &v)
{
    return v / v.length();
}

std::ostream &operator<<(std::ostream &os, const Vec3 &v)
{
    return os << v[0] << ' ' << v[1] << ' ' << v[2];
}

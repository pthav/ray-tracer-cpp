#include "vector.h"

#include <cmath>
#include <iterator>
#include <iostream>

const double &vec3::operator[](int i) const
{
    return v[i];
}

double &vec3::operator[](int i)
{
    return v[i];
}

vec3 vec3::operator-() const
{
    return vec3{-v[0], -v[1], -v[2]};
}

vec3 &vec3::operator*=(double scalar)
{
    v[0] *= scalar;
    v[1] *= scalar;
    v[2] *= scalar;
    return *this;
}

vec3 &vec3::operator/=(double scalar)
{
    v[0] /= scalar;
    v[1] /= scalar;
    v[2] /= scalar;
    return *this;
}

vec3 &vec3::operator+=(const vec3 &other)
{
    v[0] += other[0];
    v[1] += other[1];
    v[2] += other[2];
    return *this;
}

vec3 &vec3::operator-=(const vec3 &other)
{
    v[0] -= other[0];
    v[1] -= other[1];
    v[2] -= other[2];
    return *this;
}

double vec3::length() const
{
    return std::sqrt(lengthSquared());
}

double vec3::lengthSquared() const
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

vec3 operator*(const vec3 &left, const vec3 &right)
{
    return vec3{left[0] * right[0], left[1] * right[1], left[2] * right[2]};
}

vec3 operator*(double scalar, const vec3 &v)
{
    return vec3{scalar * v[0], scalar * v[1], scalar * v[2]};
}

vec3 operator*(const vec3 &v, double scalar)
{
    return scalar * v;
}

vec3 operator/(const vec3 &v, double scalar)
{
    return v * (1 / scalar);
}

vec3 operator+(const vec3 &left, const vec3 &right)
{
    return vec3{left[0] + right[0], left[1] + right[1], left[2] + right[2]};
}

vec3 operator-(const vec3 &left, const vec3 &right)
{
    return left + -right;
}

double dot(const vec3 &left, const vec3 &right)
{
    return left[0] * right[0] + left[1] * right[1] + left[2] * right[2];
}

vec3 cross(const vec3 &left, const vec3 &right)
{
    return vec3{
        left[1] * right[2] - left[2] * right[1],
        left[2] * right[0] - left[0] * right[2],
        left[0] * right[1] - left[1] * right[0]
    };
}

vec3 normalize(const vec3 &v)
{
    return v / v.length();
}

std::ostream &operator<<(std::ostream &os, const vec3 &v)
{
    return os << v[0] << ' ' << v[1] << ' ' << v[2];
}


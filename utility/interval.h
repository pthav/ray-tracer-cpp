#ifndef INTERVAL_H
#define INTERVAL_H
#include <limits>
#include "../vector/vector.h"

class Interval
{
public:
    double m_min, m_max;

    Interval()
        : m_min{+std::numeric_limits<double>::infinity()},
          m_max{-std::numeric_limits<double>::infinity()}
    {
    }

    Interval(double min, double max) : m_min{min}, m_max{max}
    {
    }

    Interval(const Interval &a, const Interval &b)
        : m_min{a.m_min <= b.m_min ? a.m_min : b.m_min},
          m_max{a.m_max >= b.m_max ? a.m_max : b.m_max}
    {
    }

    Interval(const Interval &a, double b)
    : m_min{a.m_min <= b ? a.m_min : b},
      m_max{a.m_max >= b ? a.m_max : b}
    {
    }

    Interval(double b, const Interval &a)
        : Interval(a,b)
    {
    }

    [[nodiscard]] double size() const
    {
        return m_max - m_min;
    }

    [[nodiscard]] bool contains(double x) const
    {
        return m_min <= x && x <= m_max;
    }

    [[nodiscard]] bool surrounds(double x) const
    {
        return m_min < x && x < m_max;
    }

    [[nodiscard]] double clamp(double x) const
    {
        if (x < m_min) return m_min;
        if (x > m_max) return m_max;
        return x;
    }

    [[nodiscard]] Interval expand(double delta) const
    {
        auto padding = delta / 2;
        return {m_min - padding, m_max + padding};
    }

    static const Interval empty, universe;
};

inline const Interval Interval::empty = Interval(+std::numeric_limits<double>::infinity(),
                                                 -std::numeric_limits<double>::infinity());
inline const Interval Interval::universe = Interval(-std::numeric_limits<double>::infinity(),
                                                    +std::numeric_limits<double>::infinity());

inline Interval operator+(const Interval &i, double displacement)
{
    return {i.m_min + displacement, i.m_max + displacement};
}

inline Interval operator+(double displacement, const Interval &i)
{
    return i + displacement;
}


#endif

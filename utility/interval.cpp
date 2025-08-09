#include "interval.h"

Interval::Interval()
    : m_min{+std::numeric_limits<double>::infinity()},
      m_max{-std::numeric_limits<double>::infinity()}
{
}

Interval::Interval(double min, double max) : m_min{min}, m_max{max}
{
}

Interval::Interval(const Interval &a, const Interval &b)
    : m_min{a.m_min <= b.m_min ? a.m_min : b.m_min},
      m_max{a.m_max >= b.m_max ? a.m_max : b.m_max}
{
}

Interval::Interval(const Interval &a, double b)
    : m_min{a.m_min <= b ? a.m_min : b},
      m_max{a.m_max >= b ? a.m_max : b}
{
}

Interval::Interval(double b, const Interval &a)
    : Interval(a, b)
{
}

[[nodiscard]] double Interval::size() const
{
    return m_max - m_min;
}

[[nodiscard]] bool Interval::contains(double x) const
{
    return m_min <= x && x <= m_max;
}

[[nodiscard]] bool Interval::surrounds(double x) const
{
    return m_min < x && x < m_max;
}

[[nodiscard]] double Interval::clamp(double x) const
{
    if (x < m_min) return m_min;
    if (x > m_max) return m_max;
    return x;
}

[[nodiscard]] Interval Interval::expand(double delta) const
{
    auto padding = delta / 2;
    return {m_min - padding, m_max + padding};
}

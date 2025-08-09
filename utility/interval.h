#ifndef INTERVAL_H
#define INTERVAL_H
#include <limits>
#include "../vector/vector.h"

class Interval
{
public:
    double m_min, m_max;

    Interval();

    Interval(double min, double max);

    Interval(const Interval &a, const Interval &b);

    Interval(const Interval &a, double b);

    Interval(double b, const Interval &a);

    [[nodiscard]] double size() const;

    [[nodiscard]] bool contains(double x) const;

    [[nodiscard]] bool surrounds(double x) const;

    [[nodiscard]] double clamp(double x) const;

    [[nodiscard]] Interval expand(double delta) const;

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

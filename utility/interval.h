#ifndef INTERVAL_H
#define INTERVAL_H
#include <limits>
#include <algorithm>

class Interval
{
public:
    double m_start{};
    double m_end{};

    Interval() : m_start{-std::numeric_limits<double>::infinity()}, m_end{std::numeric_limits<double>::infinity()}
    {
    }

    Interval(double start, double end): m_start{std::min(start, end)}, m_end{std::max(start, end)}
    {
    }

    Interval(Interval int1, Interval int2)
        : m_start{std::min(int1.m_start, int2.m_end)}, m_end{std::max(int1.m_end, int2.m_end)}
    {
    }

    [[nodiscard]] double size() const
    {
        return m_end - m_start;
    }

    [[nodiscard]] Interval expand(double delta) const
    {
        auto padding {delta / 2};
        return Interval{m_start - padding, m_end + padding};
    }
};
#endif //INTERVAL_H

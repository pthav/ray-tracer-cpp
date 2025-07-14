#ifndef INTERVAL_H
#define INTERVAL_H
#include <limits>

class Interval
{
private:
    double m_start{};
    double m_end{};

public:
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

    double s() const
    {
        return m_start;
    }

    double e() const
    {
        return m_end;
    }
};
#endif //INTERVAL_H

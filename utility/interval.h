#ifndef INTERVAL_H
#define INTERVAL_H
#include <limits>

class Interval
{
private:
    double m_start{};
    double m_end{};

public:
    Interval() : m_start{-std::numeric_limits<double>::infinity()}, m_end{std::numeric_limits<double>::infinity()} {}
    Interval(double start, double end): m_start{start}, m_end{end} {}
};
#endif //INTERVAL_H

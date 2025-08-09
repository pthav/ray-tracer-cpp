#ifndef RANDOM_H
#define RANDOM_H
#include <chrono>
#include <random>

class Random
{
public:
    static double randomDouble()
    {
        return m_double(m_gen);
    }

    static int randomInt(int start, int end)
    {
        return std::uniform_int_distribution<int>(start,end)(m_gen);
    }
private:
    static std::mt19937 m_gen;
    static std::uniform_real_distribution<double> m_double;
};

inline std::mt19937 Random::m_gen{
    static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()
    )
};

inline std::uniform_real_distribution<double> Random::m_double(0.0, 1.0);

#endif //RANDOM_H

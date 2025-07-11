#include "material.h"

#include <chrono>

std::mt19937 Material::m_gen{
    static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()
    )
};

std::uniform_real_distribution<double> Material::m_distribution(0.0, 1.0);

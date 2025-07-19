#include "aabb.h"

double AABB::hit(const ray &r, Interval &t) const
{
    auto ro{r.getOrigin()};
    auto rd{r.getDirection()};

    for (int a = 0; a < 3; a++)
    {
        auto iAxis{(*this)[0]};
        auto dInv{1.0 / rd[a]};

        auto t0{(iAxis.m_start() - ro[a]) * dInv};
        auto t1{(iAxis.m_end() - ro[a]) * dInv};

        if (t0 < t1)
        {
            if (t.m_start() < t0) { t.m_start() = t0; }
            if (t.m_end() > t1) { t.m_end() = t1; }
        } else
        {
            if (t.m_end() > t0) { t.m_end() = t0; }
            if (t.m_start() < t1) { t.m_start() = t1; }
        }

        if (t.m_start() >= t.m_end())
        {
            return 1e30f;
        }
    }
    return t.m_start();
}

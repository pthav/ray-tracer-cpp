#include "bvh.h"

bool BVH::hit(const ray &r, double rayTMin, double rayTMax, hitRecord &rec) const
{
}

double BVH::bestSplit(int &axis, double &splitPos) const
{
    double bestCost{1e30f};
    for (int a{0}; a < 3; a++)
    {
        // Find the axis min and max for the objects
        double boundsMin{1e30f};
        double boundsMax{-1e30f};
        for (const auto &child: m_children)
        {
            boundsMin = std::min(child->centroid()[a], boundsMin);
            boundsMax = std::max(child->centroid()[a], boundsMax);
        }

        if (boundsMin == boundsMax)
        {
            continue;
        }

        // Populate the bins
        bin bins[m_bins];
        double scale{m_bins / (boundsMax - boundsMin)};
        for (const auto &child: m_children)
        {
            int binIdx{std::min(static_cast<int>((child->centroid()[a] - boundsMin) * scale), m_bins - 1)};
            if (bins[binIdx].m_count == 0)
            {
                bins[binIdx].m_aabb = child->boundingBox();
            } else
            {
                bins[binIdx].m_aabb = AABB(child->boundingBox(), bins[binIdx].m_aabb);
            }
            ++bins[binIdx].m_count;
        }

        // Prefix + Suffix sums for calculating the best split in O(n) time
        int leftCount[m_bins - 1];
        double leftArea[m_bins - 1];
        int leftSum{0};
        double rightArea[m_bins - 1];
        int rightCount[m_bins - 1];
        int rightSum{0};
        AABB leftAABB{bins[0].m_aabb};
        AABB rightAABB{bins[m_bins - 1].m_aabb};
        for (int b{0}; b < m_bins - 1; b++)
        {
            leftSum += bins[b].m_count;
            leftCount[b] = leftSum;
            leftAABB = AABB(leftAABB, bins[b].m_aabb);
            leftArea[b] = leftAABB.surfaceArea();

            rightSum += bins[m_bins - 1 - b].m_count;
            rightCount[m_bins - 2 - b] = rightSum;
            rightAABB = AABB(rightAABB, bins[m_bins - 1 -b].m_aabb);
            rightArea[m_bins - 2 - b] = rightAABB.surfaceArea();
        }

        // Get best split
        scale = (boundsMax - boundsMin) / m_bins;
        for (int b{0}; b < m_bins; b++)
        {
            double planeCost {leftCount[b] * leftArea[b] + rightCount[b] * rightArea[b]};
            if (planeCost < bestCost)
            {
                bestCost = planeCost;
                axis = a;
                splitPos = boundsMin + (b+1) * scale;
            }
        }
    }
    return bestCost;
}

void BVH::subdivide()
{
    int axis{};
    double splitPos{};
    auto splitCost{bestSplit(axis, splitPos)};
    auto noSplitCost{sahCost()};

    if (noSplitCost > splitCost)
    {
        return;
    }

    m_left = std::make_shared<BVH>(BVH());
    m_right = std::make_shared<BVH>(BVH());
    for (const auto &child: m_children)
    {
        if (child->centroid()[axis] < splitPos)
        {
            m_left->m_children.push_back(child);
            m_left->m_aabb = AABB(m_left->m_aabb, child->boundingBox());
            ++(m_left->m_count);
        } else
        {
            m_right->m_children.push_back(child);
            m_right->m_aabb = AABB(m_right->m_aabb, child->boundingBox());
            ++(m_right->m_count);
        }
    }

    m_count = 0;
    m_children.clear();

    m_left->subdivide();
    m_right->subdivide();
}

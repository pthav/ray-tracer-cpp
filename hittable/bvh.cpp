#include "bvh.h"

bool BVH::hit(const ray &r, Interval rayT, hitRecord &rec) const
{
    // Get the closest hit from the leaf nodes
    if (isLeaf())
    {
        auto closest{rayT.m_end};
        hitRecord tempRec{};
        bool hitAnything{false};
        for (const auto &child: m_children)
        {
            auto hit{child->hit(r, rayT, tempRec)};
            hitAnything |= hit;
            if (hit && tempRec.m_t < closest)
            {
                closest = tempRec.m_t;
                rec = tempRec;
            }
        }
        return hitAnything;
    }

    // Get child bounding box distance
    auto leftChild{m_left.get()};
    auto rightChild{m_right.get()};
    auto leftDist{leftChild->m_aabb.hit(r)};
    auto rightDist{rightChild->m_aabb.hit(r)};
    if (leftDist > rightDist)
    {
        std::swap(leftChild, rightChild);
        std::swap(leftDist, rightDist);
    }

    // Check from front to back if the bounding boxes register a hit
    if (leftDist != 1e30f)
    {
        if (auto hit{leftChild->hit(r, rayT, rec)})
        {
            return hit;
        }
    }

    if (rightDist != 1e30f)
    {
        return rightChild->hit(r, rayT, rec);
    }

    return false;
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
            if (bins[b].m_count > 0)
            {
                leftSum += bins[b].m_count;
                leftAABB = AABB(leftAABB, bins[b].m_aabb);
            }
            leftCount[b] = leftSum;
            leftArea[b] = leftAABB.surfaceArea();

            if (bins[m_bins - 1 - b].m_count > 0)
            {
                rightSum += bins[m_bins - 1 - b].m_count;
                rightAABB = AABB(rightAABB, bins[m_bins - 1 - b].m_aabb);
            }
            rightCount[m_bins - 2 - b] = rightSum;
            rightArea[m_bins - 2 - b] = rightAABB.surfaceArea();
        }

        // Get best split
        scale = (boundsMax - boundsMin) / m_bins;
        for (int b{0}; b < m_bins - 1; b++)
        {
            double planeCost{leftCount[b] * leftArea[b] + rightCount[b] * rightArea[b]};
            if (planeCost < bestCost)
            {
                bestCost = planeCost;
                axis = a;
                splitPos = boundsMin + (b + 1) * scale;
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

    if (noSplitCost < splitCost)
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

    if (m_left->m_count == 0 || m_right->m_count == 0)
    {
        m_left.reset();
        m_right.reset();
        return;
    }

    m_count = 0;
    m_children.clear();

    m_left->subdivide();
    m_right->subdivide();
}

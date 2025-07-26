#include <gtest/gtest.h>

#include "../utility/aabb.h"
#include "../utility/interval.h"

class AABBTest : public testing::Test
{
protected:
    static void CheckEqualsInterval(Interval interval1, Interval interval2, std::string_view message)
    {
        EXPECT_DOUBLE_EQ(interval1.m_start, interval2.m_start) << message << "failed for the start";
        EXPECT_DOUBLE_EQ(interval1.m_end, interval2.m_end) << message << "failed for the end";
    }

    static void CheckEqualsVector(const Vec3 &vec1, const Vec3 &vec2, std::string_view message)
    {
        EXPECT_DOUBLE_EQ(vec1[0], vec2[0]) << message << " failed for x coordinate";
        EXPECT_DOUBLE_EQ(vec1[1], vec2[1]) << message << " failed for y coordinate";
        EXPECT_DOUBLE_EQ(vec1[2], vec2[2]) << message << " failed for z coordinate";
    }
};

TEST_F(AABBTest, TestBracketOperator)
{
    Interval x{-5, 2.4};
    Interval y{4, 5};
    Interval z{2, 7.5};
    AABB aabb{x, y, z};
    CheckEqualsInterval(x, aabb[0], "Bracket operator");
    CheckEqualsInterval(y, aabb[1], "Bracket operator");
    CheckEqualsInterval(z, aabb[2], "Bracket operator");
}

TEST_F(AABBTest, TestGetCentroid)
{
    point3 point1{-5, 4, 2};
    point3 point2{2.4, 5, 7.5};
    AABB aabb{point1, point2};
    CheckEqualsVector(aabb.centroid(), Vec3{-1.3, 4.5, 4.75}, "Get Centroid");
}

TEST_F(AABBTest, TestSurfaceArea)
{
    Interval x{-5, 2.4};
    Interval y{4, 5};
    Interval z{2, 7.5};
    AABB aabb{x, y, z};
    EXPECT_DOUBLE_EQ(aabb.surfaceArea(),
                     x.size() * y.size() + y.size() * z.size() + z.size() * x.size()) << "Surface area incorrect";
}

TEST_F(AABBTest, TestExpand)
{
    double delta{0.0001};
    Interval x{0, 0};
    Interval y{1, 1};
    Interval z{2, 2};
    AABB aabb{x, y, z};

    CheckEqualsInterval(aabb[0], Interval{x.m_start - delta / 2.0, x.m_end + delta / 2.0}, "Expand interval");
    CheckEqualsInterval(aabb[1], Interval{y.m_start - delta / 2.0, y.m_end + delta / 2.0}, "Expand interval");
    CheckEqualsInterval(aabb[2], Interval{z.m_start - delta / 2.0, z.m_end + delta / 2.0}, "Expand interval");
}

TEST_F(AABBTest, TestMergeAABB)
{
    point3 p1{-5, 4, 2};
    point3 p2{2.4, 5, 7.5};
    AABB aabb1{p1, p2};
    point3 p3{-3, -4, 1};
    point3 p4{17.4, -13, 1.5};
    AABB aabb2{p3, p4};

    AABB merged{aabb1, aabb2};
    CheckEqualsInterval(merged[0],Interval{-5,17.4},"Merge AABB x");
    CheckEqualsInterval(merged[1],Interval{-13,5},"Merge AABB y");
    CheckEqualsInterval(merged[2],Interval{1,7.5},"Merge AABB z");
}

#include <gtest/gtest.h>

#include "../utility/aabb.h"
#include "../utility/interval.h"

class AABBTest : public testing::Test
{
protected:
    static double error;

    static void CheckEqualsInterval(Interval interval1, Interval interval2, std::string_view message)
    {
        EXPECT_NEAR(interval1.m_min, interval2.m_min,error) << message << "failed for the start";
        EXPECT_NEAR(interval1.m_max, interval2.m_max,error) << message << "failed for the end";
    }

    static void CheckEqualsAABB(const AABB &aabb1, const AABB &aabb2, std::string_view message)
    {
        CheckEqualsInterval(aabb1.axisInterval(0), aabb2.axisInterval(0), message);
        CheckEqualsInterval(aabb1.axisInterval(1), aabb2.axisInterval(1), message);
        CheckEqualsInterval(aabb1.axisInterval(2), aabb2.axisInterval(2), message);
    }

    static void CheckEqualsVector(const Vec3 &vec1, const Vec3 &vec2, std::string_view message)
    {
        EXPECT_DOUBLE_EQ(vec1[0], vec2[0]) << message << " failed for x coordinate";
        EXPECT_DOUBLE_EQ(vec1[1], vec2[1]) << message << " failed for y coordinate";
        EXPECT_DOUBLE_EQ(vec1[2], vec2[2]) << message << " failed for z coordinate";
    }
};

inline double AABBTest::error{0.0001};

TEST_F(AABBTest, TestAABBFromIntervals)
{
    struct Test
    {
        Interval x;
        Interval y;
        Interval z;
    };

    auto tests{
        std::vector<Test>{
            {{0, 2}, {5, 10}, {3, 11}},
            {{-105.21, -10.56}, {100, 152.2}, {-5, -2}}
        }
    };

    for (const auto &test: tests)
    {
        AABB result{test.x, test.y, test.z};
        CheckEqualsInterval(test.x, result.axisInterval(0), "AABB From Intervals");
        CheckEqualsInterval(test.y, result.axisInterval(1), "AABB From Intervals");
        CheckEqualsInterval(test.z, result.axisInterval(2), "AABB From Intervals");
    }
}

TEST_F(AABBTest, TestAABBFromPoints)
{
    struct Test
    {
        point3 point1;
        point3 point2;
        AABB expected;
    };

    auto tests{
        std::vector<Test>{
            {point3{0, 2, 1}, point3{-1, 5, 13}, AABB{Interval{-1, 0}, Interval{2, 5}, Interval{1, 13}}},
            {point3{-5, -2, 11}, point3{-3, 5, 12}, AABB{Interval{-5, -3}, Interval{-2, 5}, Interval{11, 12}}},
        }
    };

    for (const auto &test: tests)
    {
        CheckEqualsAABB(test.expected, AABB{test.point1, test.point2}, "AABB From Points");
        CheckEqualsAABB(test.expected, AABB{test.point2, test.point1}, "AABB From Points");
    }
}

TEST_F(AABBTest, TestMergeAABBWithPoint)
{
    struct Test
    {
        AABB aabb;
        point3 point;
        AABB expected;
    };

    auto tests{
        std::vector<Test>{
            {
                AABB{Interval{-5, 5}, Interval{3, 12.1}, Interval{-101.2, 12.5}}, point3{-6, -4, -103},
                AABB{Interval{-6, 5}, Interval{-4, 12.1}, Interval{-103, 12.5}}
            },
            {
                AABB{Interval{-5, 5}, Interval{3, 12.1}, Interval{-101.2, 12.5}}, point3{6, 13, 13},
                AABB{Interval{-5, 6}, Interval{3, 13}, Interval{-101.2, 13}}
            },
        }
    };

    for (const auto &test: tests)
    {
        CheckEqualsAABB(test.expected, AABB{test.aabb, test.point}, "Merge AABB with Point");
        CheckEqualsAABB(test.expected, AABB{test.point, test.aabb}, "Merge AABB with Point");
    }
}

TEST_F(AABBTest, TestMergeAABB)
{
    struct Test
    {
        AABB aabb1;
        AABB aabb2;
        AABB expected;
    };

    auto tests{
        std::vector<Test>{
            {
                AABB{point3{-5, 4, 2}, point3{2.4, 5, 7.5}}, AABB{point3{-3, -4, 1}, point3{17.4, -13, 1.5}},
                AABB{Interval{-5, 17.4}, Interval{-13, 5}, Interval{1, 7.5}},
            }
        }
    };

    for (const auto &test: tests)
    {
        CheckEqualsAABB(test.expected, AABB{test.aabb1, test.aabb2}, "Merging AABBs");
        CheckEqualsAABB(test.expected, AABB{test.aabb2, test.aabb1}, "Merging AABBs");
    }
}

TEST_F(AABBTest, TestAxisInterval)
{
    Interval x{-5, 2.4};
    Interval y{4, 5};
    Interval z{2, 7.5};
    AABB aabb{x, y, z};
    CheckEqualsInterval(x, aabb.axisInterval(0), "Bracket operator");
    CheckEqualsInterval(y, aabb.axisInterval(1), "Bracket operator");
    CheckEqualsInterval(z, aabb.axisInterval(2), "Bracket operator");
}

TEST_F(AABBTest, TestSurfaceArea)
{
    struct Test
    {
        Interval x;
        Interval y;
        Interval z;
    };

    auto tests{
        std::vector<Test>{
            {{-5, 2.4}, {4, 5}, {2, 7.5}},
        }
    };

    for (const auto &test: tests)
    {
        AABB aabb{test.x, test.y, test.z};
        EXPECT_DOUBLE_EQ(aabb.surfaceArea(),
                         test.x.size() * test.y.size() + test.y.size() * test.z.size() + test.z.size() * test.x.size(
                         )) << "Surface area incorrect";
    }
}

TEST_F(AABBTest, TestPad)
{
    double delta{0.0001};
    struct Test
    {
        Interval x;
        Interval y;
        Interval z;
    };

    auto tests{
        std::vector<Test>{
            {{0, 0}, {1, 1}, {2, 2}},
        }
    };

    for (const auto &test: tests)
    {
        AABB aabb{test.x, test.y, test.z};

        CheckEqualsAABB(aabb, AABB{
                            Interval{test.x.m_min - delta / 2.0, test.x.m_max + delta / 2.0},
                            Interval{test.y.m_min - delta / 2.0, test.y.m_max + delta / 2.0},
                            Interval{test.z.m_min - delta / 2.0, test.z.m_max + delta / 2.0},
                        }, "Pad AABB");
    }
}

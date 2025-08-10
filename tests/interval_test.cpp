#include <gtest/gtest.h>
#include "../utility/interval.h"

class IntervalTest : public testing::Test
{
protected:
    static void CheckEquals(Interval interval1, Interval interval2, std::string_view message)
    {
        EXPECT_DOUBLE_EQ(interval1.m_min, interval2.m_min) << message << " failed for the start";
        EXPECT_DOUBLE_EQ(interval1.m_max, interval2.m_max) << message << " failed for the end";
    }
};

TEST_F(IntervalTest, TestSize)
{
    Interval interval{-5.6, 12.1};
    EXPECT_DOUBLE_EQ(interval.size(), 12.1 - (-5.6)) << "Size failed";
}

TEST_F(IntervalTest, TestExpand)
{
    Interval interval{-5, 10};
    Interval expanded{interval.expand(0.56f)};
    EXPECT_DOUBLE_EQ(expanded.m_min, -5 - 0.56f/2.0) << "Expanded failed for start";
    EXPECT_DOUBLE_EQ(expanded.m_max, 10 + 0.56f/2.0) << "Expanded failed for end";
}

TEST_F(IntervalTest, TestMergeIntervals)
{
    struct Test
    {
        Interval interval1;
        Interval interval2;
        Interval expected;
    };

    auto tests{
        std::vector<Test>{
            {Interval{0, 10}, Interval{5, 8}, {Interval{0, 10}}},
            {Interval{-5, 12}, Interval{-6, 12}, {Interval{-6, 12}}},
            {Interval{3, 6}, Interval{5, 9}, {Interval{3, 9}}},
            {Interval{0, 10}, Interval{-3, 8}, {Interval{-3, 10}}},
        }
    };

    for (const auto &test: tests)
    {
        Interval result{test.interval1, test.interval2};
        CheckEquals(result, test.expected, "Merge Intervals");
    }
}

TEST_F(IntervalTest, TestMergeIntervalWithScalar)
{
    struct Test
    {
        Interval interval;
        double scalar;
        Interval expected;
    };

    auto tests{
        std::vector<Test>{
            {Interval{0, 10}, 5, {Interval{0, 10}}},
            {Interval{-5, 12}, -6, {Interval{-6, 12}}},
            {Interval{3, 6}, 9, {Interval{3, 9}}},
            {Interval{0, 10}, -3, {Interval{-3, 10}}},
        }
    };

    for (const auto &test: tests)
    {
        Interval result{test.interval, test.scalar};
        CheckEquals(result, test.expected, "Merge Intervals");

        result = {test.scalar, test.interval};
        CheckEquals(result, test.expected, "Merge Intervals");
    }
}

TEST_F(IntervalTest, TestContains)
{
    struct Test
    {
        Interval interval;
        double scalar;
        bool contains;
    };

    auto tests{
        std::vector<Test>{
            {{0, 10}, 5, true},
            {{0, 10}, 10, true},
            {{0, 10}, 0, true},
            {{0, 10}, -5, false},
            {{0, 10}, 15, false}
        }
    };

    for (const auto &test: tests)
    {
        EXPECT_EQ(test.interval.contains(test.scalar), test.contains);
    }
}

TEST_F(IntervalTest, TestSurrounds)
{
    struct Test
    {
        Interval interval;
        double scalar;
        bool surrounds;
    };

    auto tests{
        std::vector<Test>{
            {{0, 10}, 5, true},
            {{0, 10}, 10, false},
            {{0, 10}, 0, false},
            {{0, 10}, -5, false},
            {{0, 10}, 15, false}
        }
    };

    for (const auto &test: tests)
    {
        EXPECT_EQ(test.interval.surrounds(test.scalar), test.surrounds);
    }
}

TEST_F(IntervalTest, TestClamp)
{
    struct Test
    {
        Interval interval;
        double scalar;
        double expected;
    };

    auto tests{
        std::vector<Test>{
            {{0, 10}, 5, 5},
            {{0, 10}, -1, 0},
            {{0, 10}, 11, 10}
        }
    };

    for (const auto &test: tests)
    {
        EXPECT_DOUBLE_EQ(test.expected, test.interval.clamp(test.scalar));
    }
}

TEST_F(IntervalTest, TestDisplacement)
{
    struct Test
    {
        Interval interval;
        double displacement;
        Interval expected;
    };

    auto tests{
        std::vector<Test>{
            {{0, 10}, 2.1,{2.1,12.1}},
            {{0,10},-1.9,{-1.9,8.1}}
        }
    };

    for (const auto &test: tests)
    {
        CheckEquals(test.expected, test.interval + test.displacement, "Interval displacement");
        CheckEquals(test.expected, test.displacement + test.interval, "Interval displacement");
    }
}

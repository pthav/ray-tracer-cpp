#include <gtest/gtest.h>
#include "../utility/interval.h"

class IntervalTest : public testing::Test
{
protected:
    static void CheckEquals(Interval interval1, Interval interval2, std::string_view message)
    {
        EXPECT_DOUBLE_EQ(interval1.m_start, interval2.m_start) << message << " failed for the start";
        EXPECT_DOUBLE_EQ(interval1.m_end, interval2.m_end) << message << " failed for the end";
    }
};

TEST_F(IntervalTest, TestSize)
{
    Interval interval {12.1,-5.6};
    EXPECT_DOUBLE_EQ(interval.size(), 12.1 - (-5.6)) << "Size failed";
}

TEST_F(IntervalTest, TestExpand)
{
    Interval interval {10,-5};
    Interval expanded {interval.expand(0.56f)};
    EXPECT_DOUBLE_EQ(expanded.m_start, -5 - 0.56f/2.0) << "Expanded failed for start";
    EXPECT_DOUBLE_EQ(expanded.m_end, 10 + 0.56f/2.0) << "Expanded failed for end";
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

    for (const auto& test: tests)
    {
        Interval result {test.interval1, test.interval2};
        CheckEquals(result, test.expected, "Merge Intervals");
    }

}

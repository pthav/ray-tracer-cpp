#include "../vector/ray.h"

#include <gtest/gtest.h>
#include "../vector/vector.h"

class RayTest : public testing::Test
{
protected:
    static void CheckEquals(const Vec3 &vec1, const Vec3 &vec2, std::string_view message)
    {
        EXPECT_DOUBLE_EQ(vec1[0], vec2[0]) << message << " failed for x coordinate";
        EXPECT_DOUBLE_EQ(vec1[1], vec2[1]) << message << " failed for y coordinate";
        EXPECT_DOUBLE_EQ(vec1[2], vec2[2]) << message << " failed for z coordinate";
    }
};

TEST_F(RayTest, TestGetters)
{
    point3 origin {1,0.5,2};
    Vec3 direction {-15.2,2.7,5};
    auto tOrigin {1.5};
    ray r {origin, direction,tOrigin};
    CheckEquals(r.getDirection(),direction, "Get Direction");
    CheckEquals(r.getOrigin(), origin, "Get Origin");
    EXPECT_EQ(r.getTime(), tOrigin) << "Get Time";
}

TEST_F(RayTest, TestAt)
{
    struct Test {
        ray r;
        double a;
        Vec3 expected;
    };

    const std::vector<Test> tests{{
        {ray{point3{1,0.5,0.2},Vec3{-15.2,2.7,5}}, 2.1, Vec3{-30.92,6.17,10.7}},
    }};

    for (const auto &test : tests)
    {
        Vec3 result {test.r.at(test.a)};
        CheckEquals(result, test.expected, "Ray At");
    }
}

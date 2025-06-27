#include <gtest/gtest.h>
#include "../vector.h"

#include <cmath>

class VectorTest : public testing::Test
{
protected:
    static void CheckEquals(const vec3 &vec1, const vec3 &vec2, std::string_view message)
    {
        EXPECT_DOUBLE_EQ(vec1[0], vec2[0]) << message << " failed for x coordinate";
        EXPECT_DOUBLE_EQ(vec1[1], vec2[1]) << message << " failed for y coordinate";
        EXPECT_DOUBLE_EQ(vec1[2], vec2[2]) << message << " failed for z coordinate";
    }
};

TEST_F(VectorTest, TestMembers)
{
    // Member Operations
    vec3 bracketVec{0, 2, 2};
    EXPECT_DOUBLE_EQ(bracketVec[0], 0) << "Bracket operator failed for x axis";
    EXPECT_DOUBLE_EQ(bracketVec[1], 2) << "Bracket operator failed for y axis";
    EXPECT_DOUBLE_EQ(bracketVec[2], 2) << "Bracket operator failed for z axis";

    vec3 memberVec{2, 4, 6};
    CheckEquals(memberVec /= 2, vec3{1, 2, 3}, "/= Operator");
    CheckEquals(memberVec *= 2.5, vec3{2.5, 5, 7.5}, "*= Operator");
    CheckEquals(memberVec += vec3{2, 3, 4}, vec3{4.5, 8, 11.5}, "+= Operator");
    CheckEquals(memberVec -= vec3{0.5, 1, -2}, vec3{4, 7, 13.5}, "-= Operator");
    CheckEquals(-memberVec, vec3{-4, -7, -13.5}, "- Operator");
    EXPECT_DOUBLE_EQ(memberVec.length(), std::sqrt(16 + 49 + 13.5 * 13.5)) << "Length failed";
    EXPECT_DOUBLE_EQ(memberVec.lengthSquared(), 16 + 49 + 13.5 * 13.5) << "Length Squared failed";
}

TEST_F(VectorTest, TestFriends)
{
    // Friend Operations
    vec3 addResult{vec3{0, 0, 0} + vec3{-1, 5, 2}};
    vec3 addExpected{-1, 5, 2};
    CheckEquals(addResult, addExpected, "Addition");

    vec3 subResult{vec3{0, 0, 0} - vec3{-1, 5, 2}};
    vec3 subExpected{1, -5, -2};
    CheckEquals(subResult, subExpected, "Subtraction");

    vec3 vecVecMultResult{vec3{-1, 2, 2} * vec3{-1, 5, 2}};
    vec3 vecVecMultExpected{1, 10, 4};
    CheckEquals(vecVecMultResult, vecVecMultExpected, "Multiplication");

    vec3 vecScalarMultResult{vec3{-1, 2, 2} * 3.2};
    vec3 vecScalarMultExpected{-3.2, 6.4, 6.4};
    CheckEquals(vecScalarMultResult, vecScalarMultExpected, "Multiplication");

    vec3 scalarVecMultResult{3.2 * vec3{-1, 2, 2}};
    vec3 scalarVecMultExpected{-3.2, 6.4, 6.4};
    CheckEquals(scalarVecMultResult, scalarVecMultExpected, "Multiplication");

    vec3 divResult{vec3{5, 4, 2} / 4};
    vec3 divExpected{5.0 / 4, 1, 2.0 / 4};
    CheckEquals(divResult, divExpected, "Division");

    EXPECT_DOUBLE_EQ(dot(vec3{1,2,3},vec3{-1,4,7.4}), -1 + 8 + 22.2) << "Dot product failed";

    vec3 cross1{1, -2, 6};
    vec3 cross2{-5.2, 4, 0.5};
    CheckEquals(cross(cross1, cross2), vec3{-25, -31.7, -6.4}, "Cross product");

    CheckEquals(normalize(vec3{2, 2, std::sqrt(17)}), vec3{2.0 / 5, 2.0 / 5, std::sqrt(17) / 5}, "Normalize ");
}

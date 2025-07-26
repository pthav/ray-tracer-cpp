#include <gtest/gtest.h>
#include "../vector/vector.h"

#include <cmath>

class VectorTest : public testing::Test
{
protected:
    static void CheckEquals(const Vec3 &vec1, const Vec3 &vec2, std::string_view message)
    {
        EXPECT_DOUBLE_EQ(vec1[0], vec2[0]) << message << " failed for x coordinate";
        EXPECT_DOUBLE_EQ(vec1[1], vec2[1]) << message << " failed for y coordinate";
        EXPECT_DOUBLE_EQ(vec1[2], vec2[2]) << message << " failed for z coordinate";
    }

    static void CheckEqualsNear(const Vec3 &vec1, const Vec3 &vec2, std::string_view message)
    {
        constexpr auto gap {0.0000001f};
        EXPECT_NEAR(vec1[0], vec2[0], gap) << message << " failed for x coordinate";
        EXPECT_NEAR(vec1[1], vec2[1], gap) << message << " failed for y coordinate";
        EXPECT_NEAR(vec1[2], vec2[2], gap) << message << " failed for z coordinate";
    }
};

TEST_F(VectorTest, TestBracketOperator)
{
    // Member Operations
    Vec3 vec{0,2,-3};
    Vec3 bracketVec{vec[0],vec[1],vec[2]};
    CheckEquals(vec, bracketVec, "Bracket operator");
}

TEST_F(VectorTest, TestScalarDivide)
{
    Vec3 divResult{Vec3{5, 4, 2} / 4};
    Vec3 divExpected{5.0 / 4, 1, 2.0 / 4};
    CheckEquals(divResult, divExpected, "Division");

    Vec3 memberVec{2, 4, 6};
    CheckEquals(memberVec /= 2, Vec3{1, 2, 3}, "/= Operator");
}

TEST_F(VectorTest, TestScalarMultiplication)
{
    Vec3 vecScalarMultResult{Vec3{-1, 2, 2} * 3.2};
    Vec3 vecScalarMultExpected{-3.2, 6.4, 6.4};
    CheckEquals(vecScalarMultResult, vecScalarMultExpected, "Multiplication");

    Vec3 scalarVecMultResult{3.2 * Vec3{-1, 2, 2}};
    Vec3 scalarVecMultExpected{-3.2, 6.4, 6.4};
    CheckEquals(scalarVecMultResult, scalarVecMultExpected, "Multiplication");

    Vec3 memberVec{1, 2, 3};
    CheckEquals(memberVec *= 2.5, Vec3{2.5, 5, 7.5}, "*= Operator");
}

TEST_F(VectorTest, TestVectorMultiplication)
{
    Vec3 vecVecMultResult{Vec3{-1, 2, 2} * Vec3{-1, 5, 2}};
    Vec3 vecVecMultExpected{1, 10, 4};
    CheckEquals(vecVecMultResult, vecVecMultExpected, "Vector multiplication");
}

TEST_F(VectorTest, TestVectorAddition)
{
    Vec3 addResult{Vec3{0, 0, 0} + Vec3{-1, 5, 2}};
    Vec3 addExpected{-1, 5, 2};
    CheckEquals(addResult, addExpected, "Addition");

    Vec3 memberVec{2.5, 5, 7.5};
    CheckEquals(memberVec += Vec3{2, 3, 4}, Vec3{4.5, 8, 11.5}, "+= Operator");
}

TEST_F(VectorTest, TestVectorSubtraction)
{
    Vec3 subResult{Vec3{0, 0, 0} - Vec3{-1, 5, 2}};
    Vec3 subExpected{1, -5, -2};
    CheckEquals(subResult, subExpected, "Subtraction");

    Vec3 memberVec{4.5, 8, 11.5};
    CheckEquals(memberVec -= Vec3{0.5, 1, -2}, Vec3{4, 7, 13.5}, "-= Operator");
}

TEST_F(VectorTest, TestVectorNegation)
{
    Vec3 memberVec{4, -7, 13.5};
    CheckEquals(-memberVec, Vec3{-4, 7, -13.5}, "- Operator");
}

TEST_F(VectorTest, TestVectorLength)
{
    Vec3 memberVec{-4, 7, -13.5};
    EXPECT_DOUBLE_EQ(memberVec.length(), std::sqrt(16 + 49 + 13.5 * 13.5)) << "Length failed";
}

TEST_F(VectorTest, TestVectorLengthSquared)
{
    Vec3 memberVec{-4, 7, -13.5};
    EXPECT_DOUBLE_EQ(memberVec.lengthSquared(), 16 + 49 + 13.5 * 13.5) << "Length Squared failed";
}

TEST_F(VectorTest, TestVectorNormalize)
{
    CheckEquals(normalize(Vec3{2, 2, std::sqrt(17)}), Vec3{2.0 / 5, 2.0 / 5, std::sqrt(17) / 5}, "Normalize ");
}

TEST_F(VectorTest, TestDotProduct)
{
    EXPECT_DOUBLE_EQ(dot(Vec3{1,2,3},Vec3{-1,4,7.4}), -1 + 8 + 22.2) << "Dot product failed";
}

TEST_F(VectorTest, TestCrossProduct)
{
    Vec3 cross1{1, -2, 6};
    Vec3 cross2{-5.2, 4, 0.5};
    CheckEquals(cross(cross1, cross2), Vec3{-25, -31.7, -6.4}, "Cross product");
}

TEST_F(VectorTest, TestVectorReflection)
{
    struct Test {
        Vec3 in;
        Vec3 n;
        Vec3 expected;
    };

    const std::vector<Test> tests{{
        {Vec3{1,-4,5},Vec3{3,5,2},normalize(Vec3{43,66,33})},
        {Vec3{-10.1,14.2,5},Vec3{0.5,1.86,-2.5},normalize(Vec3{-18.962,-18.766636,49.309998})}
    }};

    for (const auto test: tests)
    {
        auto result {reflect(test.in,test.n)};
        CheckEqualsNear(result, test.expected, "Reflection");
    }
}
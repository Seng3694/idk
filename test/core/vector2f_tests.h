#ifndef CORE_VECTOR2F_TESTS_H
#define CORE_VECTOR2F_TESTS_H

#include "idk_test.h"

#include <idk/core/vector2f.h>

IDK_TEST(CoreVector2fEqualsTest)
{
    const idk_vec2_t a = {1.0f, 1.0f};
    const idk_vec2_t b = {1.0f, 2.0f};
    const idk_vec2_t c = {2.0f, 1.0f};
    const idk_vec2_t d = {2.0f, 2.0f};

    IDK_ASSERT(idk_vector2f_equals(a, a) == true);
    IDK_ASSERT(idk_vector2f_equals(a, b) == false);
    IDK_ASSERT(idk_vector2f_equals(a, c) == false);
    IDK_ASSERT(idk_vector2f_equals(a, d) == false);

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fAddTest)
{
    const idk_vec2_t left = {3.0f, 9.0f};
    const idk_vec2_t right = {7.0f, 1.0f};
    const idk_vec2_t expectedResult = {10.0f, 10.0f};
    const idk_vec2_t actualResult = idk_vector2f_add(left, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

	return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fSubTest)
{
    const idk_vec2_t left = {10.0f, 10.0f};
    const idk_vec2_t right = {7.0f, 1.0f};
    const idk_vec2_t expectedResult = {3.0f, 9.0f};
    const idk_vec2_t actualResult = idk_vector2f_sub(left, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fMulTest)
{
    const idk_vec2_t left = {10.0f, 10.0f};
    const idk_vec2_t right = {2.5f, 3.1f};
    const idk_vec2_t expectedResult = {25.0f, 31.0f};
    const idk_vec2_t actualResult = idk_vector2f_mul(left, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fMulfTest)
{
    const idk_vec2_t left = {10.0f, 10.0f};
    const float right = 3.1f;
    const idk_vec2_t expectedResult = {31.0f, 31.0f};
    const idk_vec2_t actualResult = idk_vector2f_mulf(left, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fDivTest)
{
    const idk_vec2_t left = {10.0f, 10.0f};
    const idk_vec2_t right = {2.0f, 4.0f};
    const idk_vec2_t expectedResult = {5.0f, 2.5f};
    const idk_vec2_t actualResult = idk_vector2f_div(left, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fDivfTest)
{
    const idk_vec2_t left = {10.0f, 40.0f};
    const float right = 4.0f;
    const idk_vec2_t expectedResult = {2.5f, 10.0f};
    const idk_vec2_t actualResult = idk_vector2f_divf(left, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fDotTest)
{
    const idk_vec2_t left = {3.0f, 4.0f};
    const idk_vec2_t right = {7.0f, -2.0f};

    //x1 * x2 + y1 * y2
    //=> 3 * 7 + 4 * -2
    //=> 21 - 8 = 13
    const float expectedResult = 13.0f;
    const float actualResult = idk_vector2f_dot(left, right);

    IDK_ASSERT(expectedResult == actualResult);

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fCrossTest)
{
    const idk_vec2_t left = {3.0f, 4.0f};
    const idk_vec2_t right = {7.0f, -2.0f};

    // 3 * -2 - 4 * 7
    //x1 * y2 - y1 * x2
    //=> 3 * -2 - 4 * 7
    //=> -6 - 28 = 
    const float expectedResult = -34.0f;
    const float actualResult = idk_vector2f_cross(left, right);

    IDK_ASSERT(expectedResult == actualResult);

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fMagTest)
{
    const idk_vec2_t vec = {3.0f, 4.0f};

    //sqrt(x*x + y*y)
    //sqrt(3*3 + 4*4)
    //sqrt(9 + 16)
    //sqrt(25) = 5
    const float expectedResult = 5.0f;
    const float actualResult = idk_vector2f_mag(vec);

    IDK_ASSERT(expectedResult == actualResult);

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fNormalizeTest)
{
    const idk_vec2_t vec = {3.0f, 4.0f};
    //divide by vector magnitude (5.0f)
    const idk_vec2_t expectedResult = {0.6f, 0.8f};
    const idk_vec2_t actualResult = idk_vector2f_normalize(vec);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fLerpTest)
{
    const idk_vec2_t start = {2.0f, 3.0f};
    const idk_vec2_t end = {18.0f, 6.0f};
    const float t = 0.5f;

    //should be the point in the center between both vectors
    const idk_vec2_t expectedResult = {10.0f, 4.5f};
    const idk_vec2_t actualResult = idk_vector2f_lerp(start, end, t);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fAddRefTest)
{
    const idk_vec2_t left = {3.0f, 9.0f};
    const idk_vec2_t right = {7.0f, 1.0f};
    const idk_vec2_t expectedResult = {10.0f, 10.0f};
    idk_vec2_t actualResult;
    idk_vector2f_add_ref(left, right, &actualResult);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fSubRefTest)
{
    const idk_vec2_t left = {10.0f, 10.0f};
    const idk_vec2_t right = {7.0f, 1.0f};
    const idk_vec2_t expectedResult = {3.0f, 9.0f};
    idk_vec2_t actualResult;
    idk_vector2f_sub_ref(left, right, &actualResult);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fMulRefTest)
{
    const idk_vec2_t left = {10.0f, 10.0f};
    const idk_vec2_t right = {2.5f, 3.1f};
    const idk_vec2_t expectedResult = {25.0f, 31.0f};
    idk_vec2_t actualResult;
    idk_vector2f_mul_ref(left, right, &actualResult);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fMulfRefTest)
{
    const idk_vec2_t left = {10.0f, 10.0f};
    const float right = 3.1f;
    const idk_vec2_t expectedResult = {31.0f, 31.0f};
    idk_vec2_t actualResult;
    idk_vector2f_mulf_ref(left, right, &actualResult);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fDivRefTest)
{
    const idk_vec2_t left = {10.0f, 10.0f};
    const idk_vec2_t right = {2.0f, 4.0f};
    const idk_vec2_t expectedResult = {5.0f, 2.5f};
    idk_vec2_t actualResult;
    idk_vector2f_div_ref(left, right, &actualResult);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fDivfRefTest)
{
    const idk_vec2_t left = {10.0f, 40.0f};
    const float right = 4.0f;
    const idk_vec2_t expectedResult = {2.5f, 10.0f};
    idk_vec2_t actualResult;
    idk_vector2f_divf_ref(left, right, &actualResult);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fDotRefTest)
{
    const idk_vec2_t left = {3.0f, 4.0f};
    const idk_vec2_t right = {7.0f, -2.0f};

    // x1 * x2 + y1 * y2
    //=> 3 * 7 + 4 * -2
    //=> 21 - 8 = 13
    const float expectedResult = 13.0f;
    float actualResult;
    idk_vector2f_dot_ref(left, right, &actualResult);

    IDK_ASSERT(expectedResult == actualResult);

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fCrossRefTest)
{
    const idk_vec2_t left = {3.0f, 4.0f};
    const idk_vec2_t right = {7.0f, -2.0f};

    // 3 * -2 - 4 * 7
    // x1 * y2 - y1 * x2
    //=> 3 * -2 - 4 * 7
    //=> -6 - 28 =
    const float expectedResult = -34.0f;
    float actualResult;
    idk_vector2f_cross_ref(left, right, &actualResult);

    IDK_ASSERT(expectedResult == actualResult);

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fMagRefTest)
{
    const idk_vec2_t vec = {3.0f, 4.0f};

    // sqrt(x*x + y*y)
    // sqrt(3*3 + 4*4)
    // sqrt(9 + 16)
    // sqrt(25) = 5
    const float expectedResult = 5.0f;
    float actualResult;
    idk_vector2f_mag_ref(vec, &actualResult);

    IDK_ASSERT(expectedResult == actualResult);

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fNormalizeRefTest)
{
    const idk_vec2_t expectedResult = {0.6f, 0.8f};

    idk_vec2_t actualResult = {3.0f, 4.0f};
    // divide by vector magnitude (5.0f)
    idk_vector2f_normalize_ref(&actualResult);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fLerpRefTest)
{
    const idk_vec2_t start = {2.0f, 3.0f};
    const idk_vec2_t end = {18.0f, 6.0f};
    const float t = 0.5f;

    // should be the point in the center between both vectors
    const idk_vec2_t expectedResult = {10.0f, 4.5f};
    idk_vec2_t actualResult;
    idk_vector2f_lerp_ref(start, end, t, &actualResult);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fAddEqTest)
{
    idk_vec2_t actualResult = {3.0f, 9.0f};
    const idk_vec2_t right = {7.0f, 1.0f};
    const idk_vec2_t expectedResult = {10.0f, 10.0f};
    idk_vector2f_add_eq(&actualResult, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fSubEqTest)
{
    idk_vec2_t actualResult = {10.0f, 10.0f};
    const idk_vec2_t right = {7.0f, 1.0f};
    const idk_vec2_t expectedResult = {3.0f, 9.0f};
    idk_vector2f_sub_eq(&actualResult, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fMulEqTest)
{
    idk_vec2_t actualResult = {10.0f, 10.0f};
    const idk_vec2_t right = {2.5f, 3.1f};
    const idk_vec2_t expectedResult = {25.0f, 31.0f};
    idk_vector2f_mul_eq(&actualResult, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fMulfEqTest)
{
    idk_vec2_t actualResult = {10.0f, 10.0f};
    const float right = 3.1f;
    const idk_vec2_t expectedResult = {31.0f, 31.0f};
    idk_vector2f_mulf_eq(&actualResult, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fDivEqTest)
{
    idk_vec2_t actualResult = {10.0f, 10.0f};
    const idk_vec2_t right = {2.0f, 4.0f};
    const idk_vec2_t expectedResult = {5.0f, 2.5f};
    idk_vector2f_div_eq(&actualResult, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

IDK_TEST(CoreVector2fDivfEqTest)
{
    idk_vec2_t actualResult = {10.0f, 40.0f};
    const float right = 4.0f;
    const idk_vec2_t expectedResult = {2.5f, 10.0f};
    idk_vector2f_divf_eq(&actualResult, right);

    IDK_ASSERT(idk_vector2f_equals(expectedResult, actualResult));

    return IDK_SUCCESS;
}

#define CoreVector2fTests                                                     \
    CoreVector2fEqualsTest, CoreVector2fAddTest, CoreVector2fSubTest,         \
        CoreVector2fMulTest, CoreVector2fMulfTest, CoreVector2fDivTest,       \
        CoreVector2fDivfTest, CoreVector2fDotTest, CoreVector2fCrossTest,     \
        CoreVector2fMagTest, CoreVector2fNormalizeTest, CoreVector2fLerpTest, \
        CoreVector2fAddRefTest, CoreVector2fSubRefTest,                       \
        CoreVector2fMulRefTest, CoreVector2fMulfRefTest,                      \
        CoreVector2fDivRefTest, CoreVector2fDivfRefTest,                      \
        CoreVector2fDotRefTest, CoreVector2fCrossRefTest,                     \
        CoreVector2fMagRefTest, CoreVector2fNormalizeRefTest,                 \
        CoreVector2fLerpRefTest, CoreVector2fAddEqTest,                       \
        CoreVector2fSubEqTest, CoreVector2fMulEqTest, CoreVector2fMulfEqTest, \
        CoreVector2fDivEqTest, CoreVector2fDivfEqTest

#endif

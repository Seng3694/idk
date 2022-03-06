#ifndef CORE_MATRIX4_TESTS_H
#define CORE_MATRIX4_TESTS_H

#include "idk_test.h"

#include <idk/core/matrix4.h>

#include <stdint.h>
#include <stdbool.h>
#include <memory.h>

#define _USE_MATH_DEFINES
#include <math.h>

static bool float_equals(
    const float left, const float right, const uint32_t digits)
{
    return roundf(left * powf(10, digits)) == roundf(right * powf(10, digits));
}

IDK_TEST(CoreMatrix4ZeroTest)
{
    const idk_mat4_t expected = (idk_mat4_t){
        .data = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
    }};
    const idk_mat4_t actual = idk_matrix4_zero();

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4IdentityTest)
{
    const idk_mat4_t expected = (idk_mat4_t){
        .data = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    }};
    const idk_mat4_t actual = idk_matrix4_identity();

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4CreateTest)
{
    const idk_mat4_t expected = (idk_mat4_t){
        .data = {
            1.0f, 2.0f, 3.0f, 4.0f,
            0.0f, 0.0f, 5.0f, 0.0f,
            0.0f, 6.0f, 0.0f, 0.0f,
            7.0f, 8.0f, 9.0f, 10.0f
    }};
    const idk_mat4_t actual = idk_matrix4_create(
        1.0f, 0.0f, 0.0f, 7.0f,
        2.0f, 0.0f, 6.0f, 8.0f,
        3.0f, 5.0f, 0.0f, 9.0f,
        4.0f, 0.0f, 0.0f, 10.0f
    );

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4Create2Test)
{
    const idk_mat4_t expected = (idk_mat4_t){
        .data = {
            1.0f, 2.0f, 0.0f, 3.0f,
            0.0f, 4.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            5.0f, 6.0f, 0.0f, 7.0f
    }};
    const idk_mat4_t actual = idk_matrix4_create2(
        1.0f, 0.0f, 5.0f,
        2.0f, 4.0f, 6.0f,
        3.0f, 0.0f, 7.0f
    );

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4CopyTest)
{
    const idk_mat4_t expected = idk_matrix4_create(
        1.0f, 0.0f, 0.0f, 7.0f,
        2.0f, 0.0f, 6.0f, 8.0f,
        3.0f, 5.0f, 0.0f, 9.0f,
        4.0f, 0.0f, 0.0f, 10.0f
    );
    const idk_mat4_t actual = idk_matrix4_copy(&expected);

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4CopyRefTest)
{
    const idk_mat4_t expected = idk_matrix4_create(
        1.0f, 0.0f, 0.0f, 7.0f,
        2.0f, 0.0f, 6.0f, 8.0f,
        3.0f, 5.0f, 0.0f, 9.0f,
        4.0f, 0.0f, 0.0f, 10.0f
    );
    idk_mat4_t actual;
    idk_matrix4_copy_ref(&expected, &actual);

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4ZeroRefTest)
{
    const idk_mat4_t expected = (idk_mat4_t){
        .data = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
    }};
    idk_mat4_t actual;
    idk_matrix4_zero_ref(&actual);

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4IdentityRefTest)
{
    const idk_mat4_t expected = (idk_mat4_t){
        .data = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    }};
    idk_mat4_t actual;
    idk_matrix4_identity_ref(&actual);

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4CreateRefTest)
{
    const idk_mat4_t expected = (idk_mat4_t){
        .data = {
            1.0f, 2.0f, 3.0f, 4.0f,
            0.0f, 0.0f, 5.0f, 0.0f,
            0.0f, 6.0f, 0.0f, 0.0f,
            7.0f, 8.0f, 9.0f, 10.0f
    }};
    idk_mat4_t actual;
    idk_matrix4_create_ref(&actual,
        1.0f, 0.0f, 0.0f, 7.0f,
        2.0f, 0.0f, 6.0f, 8.0f,
        3.0f, 5.0f, 0.0f, 9.0f,
        4.0f, 0.0f, 0.0f, 10.0f
    );

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4CombineTest)
{
    const idk_mat4_t mat1 = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );
    const idk_mat4_t mat2 = idk_matrix4_create(
        9.0f, 7.0f, 5.0f, 3.0f,
        7.0f, 8.0f, 6.0f, 4.0f, 
        5.0f, 6.0f, 7.0f, 5.0f,
        3.0f, 4.0f, 5.0f, 6.0f
    );
    const idk_mat4_t expected = idk_matrix4_create(
        35.0f, 39.0f,  0.0f, 35.0f,
        34.0f, 34.0f,  0.0f, 28.0f,
         0.0f,  0.0f,  1.0f,  0.0f,
        60.0f, 56.0f,  0.0f, 30.0f
    );

    idk_mat4_t actual;
    idk_matrix4_combine(mat1, mat2, &actual);

    IDK_ASSERT(memcmp(&expected, &actual, sizeof(idk_mat4_t)) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4RotateTest)
{
    const idk_mat4_t expected = idk_matrix4_create(
         2.0f, -1.0f,  0.0f,  4.0f,
         1.0f, -2.0f,  0.0f,  3.0f,
         0.0f,  0.0f,  1.0f,  0.0f,
         3.0f, -4.0f,  0.0f,  1.0f
    );

    idk_mat4_t actual = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    //90 deg rotation
    idk_matrix4_rotate(&actual, M_PI / 2.0f);

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 6))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4RotateCenterTest)
{
    const idk_mat4_t expected = idk_matrix4_create(
        2.0f, -1.0f,  0.0f,  64.0f,
        1.0f, -2.0f,  0.0f,  93.0f,
        0.0f,  0.0f,  1.0f,   0.0f,
        3.0f, -4.0f,  0.0f, 191.0f
    );

    idk_mat4_t actual = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    //90 deg rotation
    idk_matrix4_rotate_center(&actual, M_PI / 2.0f, 15.0f, 25.0f);

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 6))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4RotateCenter2Test)
{
 const idk_mat4_t expected = idk_matrix4_create(
        2.0f, -1.0f,  0.0f,  64.0f,
        1.0f, -2.0f,  0.0f,  93.0f,
        0.0f,  0.0f,  1.0f,   0.0f,
        3.0f, -4.0f,  0.0f, 191.0f
    );

    idk_mat4_t actual = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    //90 deg rotation
    idk_matrix4_rotate_center2(
        &actual, M_PI / 2.0f, (idk_vec2_t){15.0f, 25.0f});

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 6))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4ScaleTest)
{
    const idk_mat4_t expected = idk_matrix4_create(
         2.0f,  6.0f,  0.0f,  4.0f,
         4.0f,  3.0f,  0.0f,  3.0f,
         0.0f,  0.0f,  1.0f,  0.0f,
         8.0f,  9.0f,  0.0f,  1.0f
    );

    idk_mat4_t actual = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    idk_matrix4_scale(&actual, 2.0f, 3.0f);

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 6))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4Scale2Test)
{
    const idk_mat4_t expected = idk_matrix4_create(
         2.0f,  6.0f,  0.0f,  4.0f,
         4.0f,  3.0f,  0.0f,  3.0f,
         0.0f,  0.0f,  1.0f,  0.0f,
         8.0f,  9.0f,  0.0f,  1.0f
    );

    idk_mat4_t actual = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    idk_matrix4_scale2(&actual, (idk_vec2_t){2.0f, 3.0f});

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 6))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4TranslateTest)
{
    const idk_mat4_t expected = idk_matrix4_create(
        1.0f,  2.0f,  0.0f,  91.0f,
        2.0f,  1.0f,  0.0f,  66.0f,
        0.0f,  0.0f,  1.0f,   0.0f,
        4.0f,  3.0f,  0.0f, 164.0f
    );

    idk_mat4_t actual = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    idk_matrix4_translate(&actual, 13.0f, 37.0f);

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 6))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4Translate2Test)
{
    const idk_mat4_t expected = idk_matrix4_create(
        1.0f,  2.0f,  0.0f,  91.0f,
        2.0f,  1.0f,  0.0f,  66.0f,
        0.0f,  0.0f,  1.0f,   0.0f,
        4.0f,  3.0f,  0.0f, 164.0f
    );

    idk_mat4_t actual = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    idk_matrix4_translate2(&actual, (idk_vec2_t){13.0f, 37.0f});

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 6))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4TransformPointTest)
{
    const idk_mat4_t matrix = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    idk_vec2_t actual = {13.0f, 37.0f};
    idk_vec2_t expected = {91.0f, 66.0f};
    actual = idk_matrix4_transform_point(&matrix, actual);

    IDK_ASSERT(idk_vector2f_equals(actual, expected));

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4TransformPointRefTest)
{
    const idk_mat4_t matrix = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    idk_vec2_t actual = {13.0f, 37.0f};
    idk_vec2_t expected = {91.0f, 66.0f};
    idk_matrix4_transform_point_ref(&matrix, &actual.x, &actual.y);

    IDK_ASSERT(idk_vector2f_equals(actual, expected));

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4TransformPoint2RefTest)
{
    const idk_mat4_t matrix = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    idk_vec2_t actual = {13.0f, 37.0f};
    idk_vec2_t expected = {91.0f, 66.0f};
    idk_matrix4_transform_point2_ref(&matrix, &actual);

    IDK_ASSERT(idk_vector2f_equals(actual, expected));

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4OrthographicTest)
{
    const idk_mat4_t expected = idk_matrix4_create(
        0.00250,  0.00000,  0.00000, -1.00000, 
        0.00000, -0.00333,  0.00000,  1.00000, 
        0.00000,  0.00000, -1.00000, -0.00000, 
        0.00000,  0.00000,  0.00000,  1.00000
    );

    idk_mat4_t actual;
    idk_matrix4_orthographic(&actual, 0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 5))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4GetInverseTest)
{
    const idk_mat4_t expected = idk_matrix4_create(
        -0.400f,  0.500f,  0.000f,  0.100f,
         0.500f, -0.750f,  0.000f,  0.250f,
         0.000f,  0.000f,  1.000f,  0.000f,
         0.100f,  0.250f,  0.000f, -0.150f
    );

    idk_mat4_t actual = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    actual = idk_matrix4_get_inverse(&actual);

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 6))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreMatrix4GetInverseRefTest)
{
    const idk_mat4_t expected = idk_matrix4_create(
        -0.400f,  0.500f,  0.000f,  0.100f,
         0.500f, -0.750f,  0.000f,  0.250f,
         0.000f,  0.000f,  1.000f,  0.000f,
         0.100f,  0.250f,  0.000f, -0.150f
    );

    const idk_mat4_t input = idk_matrix4_create(
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 1.0f, 2.0f, 3.0f, 
        3.0f, 2.0f, 1.0f, 2.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    idk_mat4_t actual;
    idk_matrix4_get_inverse_ref(&input, &actual);

    bool isEqual = true;
    for (uint32_t i = 0; i < 16; ++i)
    {
        if (!float_equals(actual.data[i], expected.data[i], 6))
        {
            isEqual = false;
            break;
        }
    }

    IDK_ASSERT(isEqual);

    return IDK_SUCCESS;
}

#define CoreMatrix4Tests                                                      \
    CoreMatrix4ZeroTest, CoreMatrix4IdentityTest, CoreMatrix4CreateTest,      \
        CoreMatrix4Create2Test, CoreMatrix4ZeroRefTest,                       \
        CoreMatrix4IdentityRefTest, CoreMatrix4CreateRefTest,                 \
        CoreMatrix4CombineTest, CoreMatrix4RotateTest,                        \
        CoreMatrix4RotateCenterTest, CoreMatrix4RotateCenter2Test,            \
        CoreMatrix4ScaleTest, CoreMatrix4Scale2Test,                          \
        CoreMatrix4TranslateTest, CoreMatrix4Translate2Test,                  \
        CoreMatrix4TransformPointTest, CoreMatrix4TransformPointRefTest,      \
        CoreMatrix4TransformPoint2RefTest, CoreMatrix4OrthographicTest,       \
        CoreMatrix4GetInverseTest, CoreMatrix4GetInverseRefTest,              \
        CoreMatrix4CopyTest, CoreMatrix4CopyRefTest

#endif

#ifndef CORE_COLOR_TESTS_H
#define CORE_COLOR_TESTS_H

#include "idk_test.h"

#include <idk/core/color.h>

#include <memory.h>

static inline int color_equals(const idk_color_t left, const idk_color_t right)
{
    return left.r == right.r && left.g == right.g && left.b == right.b &&
           left.a == right.a;
}

IDK_TEST(CoreColorFromPackedTest)
{
    idk_color_t expectedColor = {.r = 255, .g = 150, .b = 100, .a = 255};
    idk_color_t actualColor;

    idk_color_from_packed(&actualColor, 0xff9664ff);

    IDK_ASSERT(color_equals(expectedColor, actualColor));

    return IDK_SUCCESS;
}

IDK_TEST(CoreColorFromNormalizedTest)
{
    idk_color_t expectedColor = {.r = 255, .g = 150, .b = 100, .a = 255};
    idk_color_t actualColor;

    idk_color_from_normalized(
        &actualColor, 1.0f, 0.5882352941f, 0.3921568627f, 1.0f);

    IDK_ASSERT(color_equals(expectedColor, actualColor));

    return IDK_SUCCESS;
}

IDK_TEST(CoreColorFromRGBATest)
{
    idk_color_t expectedColor = {.r = 255, .g = 150, .b = 100, .a = 255};
    idk_color_t actualColor;

    idk_color_from_rgba(&actualColor, 255, 150, 100, 255);

    IDK_ASSERT(color_equals(expectedColor, actualColor));

    return IDK_SUCCESS;
}

IDK_TEST(CoreColorToNormalizedTest)
{
    idk_color_t color = {.r = 255, .g = 150, .b = 100, .a = 255};
    float expectedValues[4] = {1.0f, 0.5882352941f, 0.3921568627f, 1.0f};
    float actualValues[4];

    idk_color_to_normalized(color, actualValues);

    IDK_ASSERT(memcmp(expectedValues, actualValues, sizeof(float) * 4) == 0);

    return IDK_SUCCESS;
}

IDK_TEST(CoreColorPackedToNormalized)
{
    uint32_t packed = 0xff9664ff;
    float expectedValues[4] = {1.0f, 0.5882352941f, 0.3921568627f, 1.0f};
    float actualValues[4];

    idk_color_packed_to_normalized(packed, actualValues);

    IDK_ASSERT(memcmp(expectedValues, actualValues, sizeof(float) * 4) == 0);

    return IDK_SUCCESS;
}

#define CoreColorTests                                                        \
    CoreColorFromPackedTest, CoreColorFromNormalizedTest,                     \
        CoreColorFromRGBATest, CoreColorToNormalizedTest,                     \
        CoreColorPackedToNormalized

#endif

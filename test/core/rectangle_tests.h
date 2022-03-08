#ifndef CORE_RECTANGLE_TESTS_H
#define CORE_RECTANGLE_TESTS_H

#include "idk_test.h"

#include <idk/core/rectangle.h>

IDK_TEST(CoreRectangleCreateTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    IDK_ASSERT(rectangle.left == left);
    IDK_ASSERT(rectangle.top == top);
    IDK_ASSERT(rectangle.width == width);
    IDK_ASSERT(rectangle.height == height);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleCreate2Test)
{
    const float left = 1;
    const float top = 2;
    const float right = 3;
    const float bottom = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create2(left, top, right, bottom);

    const float expectedWidth = 2;  // right - left
    const float expectedHeight = 2; // bottom - top

    IDK_ASSERT(rectangle.left == left);
    IDK_ASSERT(rectangle.top == top);
    IDK_ASSERT(rectangle.width == expectedWidth);
    IDK_ASSERT(rectangle.height == expectedHeight);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleRightTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const float expected = 4;
    const float actual = idk_rectangle_right(&rectangle);

    IDK_ASSERT(expected == actual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleBottomTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const float expected = 6;
    const float actual = idk_rectangle_bottom(&rectangle);

    IDK_ASSERT(expected == actual);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleCenterTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const idk_vec2_t expected = {2.5f, 4.0f};
    const idk_vec2_t actual = idk_rectangle_center(&rectangle);

    IDK_ASSERT(expected.x == actual.x && expected.y == actual.y);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleSetCenterTest)
{
    idk_rect_t rectangle = idk_rectangle_create(0, 0, 16, 10);

    idk_rectangle_set_center(&rectangle, (idk_vec2_t){4, 3});

    const float expectedLeft = -4;
    const float expectedTop = -2;
    const float expectedWidth = 16;
    const float expectedHeight = 10;

    IDK_ASSERT(rectangle.left == expectedLeft);
    IDK_ASSERT(rectangle.top == expectedTop);
    IDK_ASSERT(rectangle.width == expectedWidth);
    IDK_ASSERT(rectangle.height == expectedHeight);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleBottomRightTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const idk_vec2_t expected = {4, 6};
    const idk_vec2_t actual = idk_rectangle_bottomright(&rectangle);

    IDK_ASSERT(expected.x == actual.x && expected.y == actual.y);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleTopRightTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const idk_vec2_t expected = {4, 2};
    const idk_vec2_t actual = idk_rectangle_topright(&rectangle);

    IDK_ASSERT(expected.x == actual.x && expected.y == actual.y);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleBottomLeftTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const idk_vec2_t expected = {1, 6};
    const idk_vec2_t actual = idk_rectangle_bottomleft(&rectangle);

    IDK_ASSERT(expected.x == actual.x && expected.y == actual.y);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleLeftCenterTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const idk_vec2_t expected = {1, 4};
    const idk_vec2_t actual = idk_rectangle_leftcenter(&rectangle);

    IDK_ASSERT(expected.x == actual.x && expected.y == actual.y);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleTopCenterTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const idk_vec2_t expected = {2.5, 2};
    const idk_vec2_t actual = idk_rectangle_topcenter(&rectangle);

    IDK_ASSERT(expected.x == actual.x && expected.y == actual.y);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleRightCenterTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const idk_vec2_t expected = {4, 4};
    const idk_vec2_t actual = idk_rectangle_rightcenter(&rectangle);

    IDK_ASSERT(expected.x == actual.x && expected.y == actual.y);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleBottomCenterTest)
{
    const float left = 1;
    const float top = 2;
    const float width = 3;
    const float height = 4;
    const idk_rect_t rectangle =
        idk_rectangle_create(left, top, width, height);

    const idk_vec2_t expected = {2.5, 6};
    const idk_vec2_t actual = idk_rectangle_bottomcenter(&rectangle);

    IDK_ASSERT(expected.x == actual.x && expected.y == actual.y);

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleContainsPointTest)
{
    const idk_rect_t r = idk_rectangle_create(1, 2, 3, 4);

    /*    0 1 2 3 4 5
     *   0
     *   1
     *   2  x - - x
     *   3  |     |
     *   4  |     |
     *   5  |     |
     *   6  x - - x
     *   7
     */

    for (float y = 0; y < 7; ++y)
    {
        for (float x = 0; x < 5; ++x)
        {
            idk_vec2_t pos = {x, y};
            if ((x < 1 || x > 4) && (y < 2 || y > 6))
            {
                // outside of rectangle
                IDK_ASSERT(idk_rectangle_contains_point(&r, pos) == false);
            }
            else if ((x >= 1 && x <= 4) && (y >= 2 && y <= 6))
            {
                // inside
                IDK_ASSERT(idk_rectangle_contains_point(&r, pos) == true);
            }
        }
    }

    return IDK_SUCCESS;
}

IDK_TEST(CoreRectangleIntersectsTest)
{
    const idk_rect_t r1 = idk_rectangle_create(1, 2, 3, 4);
    idk_rect_t r2 = idk_rectangle_create(1, 2, 3, 4);
    idk_rect_t intersection;

    /*    0 1 2 3 4 5
     *   0
     *   1
     *   2  x - - x
     *   3  |     |
     *   4  |     |
     *   5  |     |
     *   6  x - - x
     *   7
     */

    for (float y = -20; y < 20; ++y)
    {
        r2.top = y;
        for (float x = -20; x < 20; ++x)
        {
            r2.left = x;

            if (idk_rectangle_bottom(&r2) <= r1.top ||
                idk_rectangle_right(&r2) <= r1.left ||
                r2.left >= idk_rectangle_right(&r1) ||
                r2. top >= idk_rectangle_bottom(&r1))
            {
                // outside => no intersection
                IDK_ASSERT(idk_rectangle_intersects(&r1, &r2, NULL) == false);
            }
            else
            {
                // intersection
                IDK_ASSERT(
                    idk_rectangle_intersects(&r1, &r2, &intersection) == true);
                IDK_ASSERT(intersection.width > 0 && intersection.height > 0);
            }
        }
    }

    return IDK_SUCCESS;
}

#define CoreRectangleTests                                                    \
    CoreRectangleCreateTest, CoreRectangleCreate2Test,                        \
        CoreRectangleRightTest, CoreRectangleBottomTest,                      \
        CoreRectangleCenterTest, CoreRectangleSetCenterTest,                  \
        CoreRectangleBottomRightTest, CoreRectangleTopRightTest,              \
        CoreRectangleBottomLeftTest, CoreRectangleLeftCenterTest,             \
        CoreRectangleTopCenterTest, CoreRectangleRightCenterTest,             \
        CoreRectangleBottomCenterTest, CoreRectangleContainsPointTest,        \
        CoreRectangleIntersectsTest

#endif

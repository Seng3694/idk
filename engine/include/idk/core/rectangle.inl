#ifndef IDK_CORE_RECTANGLE_INL
#define IDK_CORE_RECTANGLE_INL

#include "idk/core/rectangle.h"

inline idk_rect_t idk_rectangle_create(
    const float x, const float y, const float width, const float height)
{
    idk_rect_t rect;
    rect.left = x;
    rect.top = y;
    rect.width = width;
    rect.height = height;
    return rect;
}

inline idk_rect_t idk_rectangle_create2(
    const float left, const float top, const float right, const float bottom)
{
    return idk_rectangle_create(left, top, right - left, bottom - top);
}

inline float idk_rectangle_right(const idk_rect_t *rect)
{
    return rect->left + rect->width;
}

inline float idk_rectangle_bottom(const idk_rect_t *rect)
{
    return rect->top + rect->height;
}

inline idk_vec2_t idk_rectangle_center(const idk_rect_t *rect)
{
    return idk_vector2f_create(
        rect->left + rect->width / 2.0f, rect->top + rect->height / 2.0f);
}

inline void idk_rectangle_set_center(
    idk_rect_t *rect, const idk_vec2_t pos)
{
    rect->left = pos.x - rect->width / 2.0f;
    rect->top = pos.y - rect->height / 2.0f;
}

inline idk_vec2_t idk_rectangle_bottomright(const idk_rect_t *rect)
{
    return idk_vector2f_create(
        idk_rectangle_right(rect), idk_rectangle_bottom(rect));
}

inline idk_vec2_t idk_rectangle_topright(const idk_rect_t *rect)
{
    return idk_vector2f_create(idk_rectangle_right(rect), rect->top);
}

inline idk_vec2_t idk_rectangle_bottomleft(const idk_rect_t *rect)
{
    return idk_vector2f_create(rect->left, idk_rectangle_bottom(rect));
}

inline idk_vec2_t idk_rectangle_leftcenter(const idk_rect_t *rect)
{
    return idk_vector2f_create(rect->left, rect->top + rect->height / 2.0f);
}

inline idk_vec2_t idk_rectangle_topcenter(const idk_rect_t *rect)
{
    return idk_vector2f_create(rect->left + rect->width / 2.0f, rect->top);
}

inline idk_vec2_t idk_rectangle_rightcenter(const idk_rect_t *rect)
{
    return idk_vector2f_create(
        idk_rectangle_right(rect), rect->top + rect->height / 2.0f);
}

inline idk_vec2_t idk_rectangle_bottomcenter(const idk_rect_t *rect)
{
    return idk_vector2f_create(
        rect->left + rect->width / 2.0f, idk_rectangle_bottom(rect));
}

inline bool idk_rectangle_contains_point(
    const idk_rect_t *rect, const idk_vec2_t vec)
{
    return vec.x >= rect->left && vec.x <= idk_rectangle_right(rect) &&
           vec.y >= rect->top && vec.y <= idk_rectangle_bottom(rect);
}

#endif

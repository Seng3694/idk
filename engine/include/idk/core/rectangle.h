#ifndef IDK_CORE_RECTANGLE_H
#define IDK_CORE_RECTANGLE_H

#include "idk/core/common.h"

IDK_C_API_BEGIN

#include "idk/core/vector2f.h"

#include <stdbool.h>

typedef struct idk_rectangle
{
    union {
        struct
        {
            float left;
            float top;
        };
        idk_vec2_t position;
    };
    
    union {
        struct
        {
            float height;
            float width;
        };
        idk_vec2_t size;
    };
    
} idk_rectangle_t;

typedef idk_rectangle_t idk_rect_t;

inline idk_rect_t idk_rectangle_create(
    const float x, const float y, const float width, const float height);
inline idk_rect_t idk_rectangle_create2(
    const float left, const float top, const float right, const float bottom);

inline float idk_rectangle_right(const idk_rect_t *rect);
inline float idk_rectangle_bottom(const idk_rect_t *rect);

inline idk_vec2_t idk_rectangle_center(const idk_rect_t *rect);
inline void idk_rectangle_set_center(
    idk_rect_t *rect, const idk_vec2_t pos);

inline idk_vec2_t idk_rectangle_bottomright(const idk_rect_t *rect);
inline idk_vec2_t idk_rectangle_topright(const idk_rect_t *rect);
inline idk_vec2_t idk_rectangle_bottomleft(const idk_rect_t *rect);

inline idk_vec2_t idk_rectangle_leftcenter(const idk_rect_t *rect);
inline idk_vec2_t idk_rectangle_topcenter(const idk_rect_t *rect);
inline idk_vec2_t idk_rectangle_rightcenter(const idk_rect_t *rect);
inline idk_vec2_t idk_rectangle_bottomcenter(const idk_rect_t *rect);

inline bool idk_rectangle_contains_point(
    const idk_rect_t *rect, const idk_vec2_t vec);

bool idk_rectangle_intersects(
    const idk_rect_t *left, const idk_rect_t *right,
    idk_rect_t *outIntersection);

#include "idk/core/rectangle.inl"

IDK_C_API_END

#endif

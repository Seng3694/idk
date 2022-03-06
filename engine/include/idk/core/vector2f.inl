#ifndef IDK_CORE_VECTOR2F_INL
#define IDK_CORE_VECTOR2F_INL

#include "idk/core/vector2f.h"
#include <math.h>

inline idk_vec2_t idk_vector2f_add(const idk_vec2_t left, const idk_vec2_t right)
{
    return (idk_vec2_t){left.x + right.x, left.y + right.y};
}

inline idk_vec2_t idk_vector2f_sub(
    const idk_vec2_t left, const idk_vec2_t right)
{
    return (idk_vec2_t){left.x - right.x, left.y - right.y};
}

inline idk_vec2_t idk_vector2f_mul(
    const idk_vec2_t left, const idk_vec2_t right)
{
    return (idk_vec2_t){left.x * right.x, left.y * right.y};
}

inline idk_vec2_t idk_vector2f_mulf(const idk_vec2_t left, const float right)
{
    return (idk_vec2_t){left.x * right, left.y * right};
}

inline idk_vec2_t idk_vector2f_div(const idk_vec2_t left, const idk_vec2_t right)
{
    return (idk_vec2_t){left.x / right.x, left.y / right.y};
}

inline idk_vec2_t idk_vector2f_divf(const idk_vec2_t left, const float right)
{
    return (idk_vec2_t){left.x / right, left.y / right};
}

inline float idk_vector2f_dot(const idk_vec2_t left, const idk_vec2_t right)
{
    return left.x * right.x + left.y * right.y;
}

inline float idk_vector2f_cross(const idk_vec2_t left, const idk_vec2_t right)
{
    return left.x * right.y - left.y * right.x;
}

inline float idk_vector2f_mag(const idk_vec2_t vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

inline idk_vec2_t idk_vector2f_normalize(const idk_vec2_t vec)
{
    const float mag = idk_vector2f_mag(vec);
    return idk_vector2f_divf(vec, mag);
}

inline bool idk_vector2f_equals(const idk_vec2_t left, const idk_vec2_t right)
{
    return left.x == right.x && left.y == right.y;
}

inline void idk_vector2f_add_ref(const idk_vec2_t left, const idk_vec2_t right, idk_vec2_t *result)
{
    result->x = left.x + right.x;
    result->y = left.y + right.y;
}

inline void idk_vector2f_sub_ref(const idk_vec2_t left, const idk_vec2_t right, idk_vec2_t *result)
{
    result->x = left.x - right.x;
    result->y = left.y - right.y;
}

inline void idk_vector2f_mul_ref(const idk_vec2_t left, const idk_vec2_t right, idk_vec2_t *result)
{
    result->x = left.x * right.x;
    result->y = left.y * right.y;
}

inline void idk_vector2f_mulf_ref(const idk_vec2_t left, const float right, idk_vec2_t *result)
{
    result->x = left.x * right;
    result->y = left.y * right;
}

inline void idk_vector2f_div_ref(const idk_vec2_t left, const idk_vec2_t right, idk_vec2_t *result)
{
    result->x = left.x / right.x;
    result->y = left.y / right.y;
}

inline void idk_vector2f_divf_ref(const idk_vec2_t left, const float right, idk_vec2_t *result)
{
    result->x = left.x / right;
    result->y = left.y / right;
}

inline void idk_vector2f_dot_ref(
    const idk_vec2_t left, const idk_vec2_t right, float *result)
{
    *result = left.x * right.x + left.y * right.y;
}

inline void idk_vector2f_cross_ref(const idk_vec2_t left, const idk_vec2_t right, float *result)
{
    *result = left.x * right.y - left.y * right.x;
}

inline void idk_vector2f_mag_ref(const idk_vec2_t vec, float *result)
{
    *result = sqrtf(vec.x * vec.x + vec.y * vec.y);
}

inline void idk_vector2f_normalize_ref(idk_vec2_t *vec)
{
    const float mag = idk_vector2f_mag(*vec);
    idk_vector2f_divf_eq(vec, mag);
}

inline void idk_vector2f_add_eq(idk_vec2_t *left, const idk_vec2_t right)
{
    left->x += right.x;
    left->y += right.y;
}

inline void idk_vector2f_sub_eq(idk_vec2_t *left, const idk_vec2_t right)
{
    left->x -= right.x;
    left->y -= right.y;
}

inline void idk_vector2f_mul_eq(idk_vec2_t *left, const idk_vec2_t right)
{
    left->x *= right.x;
    left->y *= right.y;
}

inline void idk_vector2f_mulf_eq(idk_vec2_t *left, const float right)
{
    left->x *= right;
    left->y *= right;
}

inline void idk_vector2f_div_eq(idk_vec2_t *left, const idk_vec2_t right)
{
    left->x /= right.x;
    left->y /= right.y;
}

inline void idk_vector2f_divf_eq(idk_vec2_t *left, const float right)
{
    left->x /= right;
    left->y /= right;
}

#endif

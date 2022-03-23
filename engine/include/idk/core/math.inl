#ifndef IDK_CORE_MATH_INL
#define IDK_CORE_MATH_INL

#include "idk/core/math.h"

inline float idk_clampf(const float x, const float min, const float max)
{
    if (x > max)
        return max;
    else if (x < min)
        return min;
    else
        return x;
}

inline float idk_ring_clampf(
    const float x, const float min, const float max)
{
    if (x > max)
        return min + (x - max);
    else if (x < min)
        return max - (min - x);
    else
        return x;
}

inline float idk_lerpf(
    const float start, const float end, const float t)
{
    return start + t * (end - start);
}

#endif

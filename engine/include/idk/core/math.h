#ifndef IDK_CORE_MATH_H
#define IDK_CORE_MATH_H

#include "idk/core/common.h"

IDK_C_API_BEGIN

inline float idk_clampf(const float x, const float min, const float max);
inline float idk_ring_clampf(const float x, const float min, const float max);
inline float idk_lerpf(const float start, const float end, const float t);

#include "math.inl"

IDK_C_API_END

#endif

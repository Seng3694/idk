#include "idk/core/vector2f.h"

static inline float lerpf(const float start, const float end, const float t);

idk_vec2_t idk_vector2f_lerp(const idk_vec2_t from, const idk_vec2_t to, const float t)
{
    return (idk_vec2_t){lerpf(from.x, to.x, t), lerpf(from.y, to.y, t)};
}


void idk_vector2f_lerp_ref(const idk_vec2_t from, const idk_vec2_t to, const float t, idk_vec2_t* result)
{
    result->x = lerpf(from.x, to.x, t);
    result->y = lerpf(from.y, to.y, t);
}

static inline float lerpf(const float start, const float end, const float t)
{
    return start + t * (end - start);
}

#include "idk/core/vector2f.h"
#include "idk/core/math.h"

idk_vec2_t idk_vector2f_lerp(
    const idk_vec2_t from, const idk_vec2_t to, const float t)
{
    return (idk_vec2_t){
        idk_lerpf(from.x, to.x, t), idk_lerpf(from.y, to.y, t)};
}

void idk_vector2f_lerp_ref(
    const idk_vec2_t from, const idk_vec2_t to, const float t,
    idk_vec2_t *result)
{
    result->x = idk_lerpf(from.x, to.x, t);
    result->y = idk_lerpf(from.y, to.y, t);
}

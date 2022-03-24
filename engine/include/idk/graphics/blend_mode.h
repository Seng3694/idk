#ifndef IDK_GRAPHICS_BLEND_MODE_H
#define IDK_GRAPHICS_BLEND_MODE_H

#include "idk/core/common.h"

IDK_C_API_BEGIN

typedef enum idk_blend_factor
{
    IDK_BLEND_FACTOR_ZERO,
    IDK_BLEND_FACTOR_ONE,
    IDK_BLEND_FACTOR_SRC_COLOR,
    IDK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
    IDK_BLEND_FACTOR_DST_COLOR,
    IDK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,
    IDK_BLEND_FACTOR_SRC_ALPHA,
    IDK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
    IDK_BLEND_FACTOR_DST_ALPHA,
    IDK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA
} idk_blend_factor_t;

typedef enum idk_blend_equation
{
    IDK_BLEND_EQUATION_ADD,
    IDK_BLEND_EQUATION_SUBTRACT,
    IDK_BLEND_EQUATION_REVERSE_SUBTRACT
} idk_blend_equation_t;

typedef struct idk_blend_mode
{
    idk_blend_factor_t colorSrcFactor;
    idk_blend_factor_t colorDstFactor;
    idk_blend_equation_t colorEquation;

    idk_blend_factor_t alphaSrcFactor;
    idk_blend_factor_t alphaDstFactor;
    idk_blend_equation_t alphaEquation;
} idk_blend_mode_t;

const extern idk_blend_mode_t idk_blend_mode_alpha;
const extern idk_blend_mode_t idk_blend_mode_add;
const extern idk_blend_mode_t idk_blend_mode_multiply;
const extern idk_blend_mode_t idk_blend_mode_none;

IDK_C_API_END

#endif

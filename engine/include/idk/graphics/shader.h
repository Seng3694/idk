#ifndef IDK_GRAPHICS_SHADER_H
#define IDK_GRAPHICS_SHADER_H

#include "idk/core/common.h"

IDK_C_API_BEGIN

#include <stdint.h>
#include "idk/core/color.h"
#include "idk/core/matrix4.h"
#include "idk/core/vector2f.h"

typedef uint32_t idk_shader_t;

//gldocs: valid shader program has a non-zero value
#define IDK_SHADER_INVALID ((idk_shader_t)0)

idk_shader_t idk_shader_create(
    const char *vertexSource, const char *fragmentSource,
    const char *geometrySource);
idk_shader_t idk_shader_create_vf(
    const char *vertexSource, const char *fragmentSource);

void idk_shader_destroy(idk_shader_t shader);

void idk_shader_use(idk_shader_t shader);

void idk_shader_set_float(
    const idk_shader_t shader, const char *name, const float value);
void idk_shader_set_integer(
    const idk_shader_t shader, const char *name, const int32_t value);

void idk_shader_set_float2(
    const idk_shader_t shader, const char *name, const float x, const float y);
void idk_shader_set_vec2f(
    const idk_shader_t shader, const char *name, const idk_vector2f_t vec);

void idk_shader_set_float3(
    const idk_shader_t shader, const char *name, const float x, const float y,
    const float z);

void idk_shader_set_float4(
    const idk_shader_t shader, const char *name, const float x, const float y,
    const float z, const float w);
void idk_shader_set_color(
    const idk_shader_t shader, const char *name, const idk_color_t color);

void idk_shader_set_matrix4(
    const idk_shader_t shader, const char *name, const idk_matrix4_t* matrix);

IDK_C_API_END

#endif

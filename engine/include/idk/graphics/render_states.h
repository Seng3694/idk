#ifndef IDK_GRAPHICS_RENDER_STATES_H
#define IDK_GRAPHICS_RENDER_STATES_H

#include "idk/core/matrix4.h"
#include "idk/graphics/shader.h"

typedef struct idk_render_states
{
    idk_mat4_t currentMatrix;
    idk_shader_t currentShader;
} idk_render_states_t;

#endif

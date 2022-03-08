#ifndef IDK_GRAPHICS_BATCH_RENDERER_H
#define IDK_GRAPHICS_BATCH_RENDERER_H

#include <stdint.h>
#include "idk/core/vertex.h"
#include "idk/graphics/render_states.h"
#include "idk/graphics/texture.h"
#include "idk/graphics/window.h"

typedef struct idk_batch_renderer idk_batch_renderer_t;

idk_batch_renderer_t *idk_batch_renderer_create(
    idk_window_t *window, const idk_texture_t* texture, const uint32_t vertexCount, const idk_vertex_t *vertices);
void idk_batch_renderer_destroy(idk_batch_renderer_t *renderer);

void idk_batch_renderer_update(idk_batch_renderer_t *renderer);
void idk_batch_renderer_reset(
    idk_batch_renderer_t *renderer, const idk_texture_t* texture, const uint32_t vertexCount,
    const idk_vertex_t *vertices);

void idk_batch_renderer_draw(idk_batch_renderer_t *renderer, idk_render_states_t renderStates);

#endif

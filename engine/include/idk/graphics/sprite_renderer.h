#ifndef IDK_GRAPHICS_SPRITE_RENDERER_H
#define IDK_GRAPHICS_SPRITE_RENDERER_H

#include "idk/core/color.h"
#include "idk/core/rectangle.h"
#include "idk/core/vector2f.h"
#include "idk/graphics/render_states.h"
#include "idk/graphics/texture.h"
#include "idk/graphics/window.h"

typedef struct idk_sprite_renderer idk_sprite_renderer_t;

idk_sprite_renderer_t *idk_sprite_renderer_create(idk_window_t *window);
void idk_sprite_renderer_destroy(idk_sprite_renderer_t *renderer);

void idk_sprite_renderer_draw(
    idk_sprite_renderer_t *renderer, const idk_texture_t *texture, const idk_rect_t textureRect,
    const idk_vec2_t position, const idk_vec2_t origin, const idk_vec2_t size, const float rotate,
    const idk_color_t color, idk_render_states_t renderStates);

#endif

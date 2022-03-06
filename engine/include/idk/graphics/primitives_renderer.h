#ifndef IDK_GRAPHICS_PRIMTIVES_RENDERER_H
#define IDK_GRAPHICS_PRIMTIVES_RENDERER_H

#include <stdint.h>
#include "idk/core/color.h"

typedef struct idk_primitives_renderer idk_primitives_renderer_t;

idk_primitives_renderer_t *idk_primitives_renderer_create(
    const uint32_t screenWidth, const uint32_t screenHeight);
void idk_primitives_renderer_destroy(idk_primitives_renderer_t *renderer);

void idk_primitives_renderer_set_color(
    idk_primitives_renderer_t *renderer, float r, float g, float b, float a);
void idk_primitives_renderer_set_color2(
    idk_primitives_renderer_t *renderer, uint8_t r, uint8_t g, uint8_t b,
    uint8_t a);
void idk_primitives_renderer_set_color3(
    idk_primitives_renderer_t *renderer, const idk_color_t color);

void idk_draw_point(
    idk_primitives_renderer_t *renderer, const float x, const float y);
void idk_draw_line(
    idk_primitives_renderer_t *renderer, const float x1, const float y1,
    const float x2, const float y2);

void idk_draw_triangle(
    idk_primitives_renderer_t *renderer, const float x1, const float y1,
    const float x2, const float y2, const float x3, const float y3);
void idk_draw_triangle_fill(
    idk_primitives_renderer_t *renderer, const float x1, const float y1,
    const float x2, const float y2, const float x3, const float y3);

void idk_draw_rectangle(
    idk_primitives_renderer_t *renderer, const float x, const float y,
    const float width, const float height);
void idk_draw_rectangle2(
    idk_primitives_renderer_t *renderer, const float left, const float top,
    const float right, const float bottom);
void idk_draw_rectangle_fill(
    idk_primitives_renderer_t *renderer, const float x, const float y,
    const float width, const float height);
void idk_draw_rectangle2_fill(
    idk_primitives_renderer_t *renderer, const float left, const float top,
    const float right, const float bottom);

void idk_draw_circle(
    idk_primitives_renderer_t *renderer, const float x, const float y,
    const float radius);
void idk_draw_circle_fill(
    idk_primitives_renderer_t *renderer, const float x, const float y,
    const float radius);

#endif

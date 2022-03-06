#ifndef IDK_CORE_COLOR_H
#define IDK_CORE_COLOR_H

#include <stdint.h>

typedef struct idk_color
{
    uint8_t a;
    uint8_t b;
    uint8_t g;
    uint8_t r;
} idk_color_t;

void idk_color_from_packed(idk_color_t *color, const uint32_t packed);
void idk_color_from_normalized(
    idk_color_t *color, const float r, const float g, const float b,
    const float a);
void idk_color_from_rgba(
    idk_color_t *color, const uint8_t r, const uint8_t g,
    const uint8_t b, const uint8_t a);

void idk_color_to_normalized(const idk_color_t color, float *out);
void idk_color_packed_to_normalized(const uint32_t packed, float *out);

#endif

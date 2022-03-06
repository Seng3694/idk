#include "idk/core/color.h"

void idk_color_from_packed(idk_color_t *color, const uint32_t packed)
{
    color->r = (uint8_t)((packed & 0xff000000) >> 24);
    color->g = (uint8_t)((packed & 0x00ff0000) >> 16);
    color->b = (uint8_t)((packed & 0x0000ff00) >> 8);
    color->a = (uint8_t)(packed & 0x000000ff);
}

void idk_color_from_normalized(
    idk_color_t *color, const float r, const float g, const float b,
    const float a)
{
    color->r = (uint8_t)(r * 0xff);
    color->g = (uint8_t)(g * 0xff);
    color->b = (uint8_t)(b * 0xff);
    color->a = (uint8_t)(a * 0xff);
}

void idk_color_from_rgba(
    idk_color_t *color, const uint8_t r, const uint8_t g, const uint8_t b,
    const uint8_t a)
{
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}

void idk_color_to_normalized(const idk_color_t color, float *out)
{
    out[0] = color.r / (float)0xff;
    out[1] = color.g / (float)0xff;
    out[2] = color.b / (float)0xff;
    out[3] = color.a / (float)0xff;
}

void idk_color_packed_to_normalized(const uint32_t packed, float *out)
{
    out[0] = (uint8_t)((packed & 0xff000000) >> 24) / (float)0xff;
    out[1] = (uint8_t)((packed & 0x00ff0000) >> 16) / (float)0xff;
    out[2] = (uint8_t)((packed & 0x0000ff00) >>  8) / (float)0xff;
    out[3] = (uint8_t)(packed & 0x000000ff) / (float)0xff;
}

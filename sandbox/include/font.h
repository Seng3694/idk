#ifndef GAME_FONT_H
#define GAME_FONT_H

#include <stdbool.h>
#include <stdint.h>
#include <idk/tiles/tileset.h>

typedef struct idk_font
{
    idk_tileset_t *sheet;
    uint32_t charInfoCount;
    const char *charInfo;
} idk_font_t;

idk_font_t *idk_font_create(
    const idk_texture_t *texture, const uint32_t charWidth,
    const uint32_t charHeight, const uint32_t charInfoCount,
    const char *charInfos);

void idk_font_destroy(idk_font_t *font);

bool idk_font_get_char_rect(const idk_font_t *font, const char c, idk_rect_t *out);

#endif

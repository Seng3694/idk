#include "font.h"

#include <stdlib.h>

idk_font_t *idk_font_create(
    const idk_texture_t *texture, const uint32_t charWidth,
    const uint32_t charHeight,
    const uint32_t charInfoCount,
    const char *charInfos)
{
    idk_font_t *font = malloc(sizeof(idk_font_t));
    font->sheet = idk_tileset_create(texture, charWidth, charHeight);
    font->charInfoCount = charInfoCount;
    font->charInfo = charInfos;
    return font;
}

void idk_font_destroy(idk_font_t *font)
{
    idk_tileset_destroy(font->sheet);
    free(font);
}

bool idk_font_get_char_rect(const idk_font_t *font, const char c, idk_rect_t *out)
{
    for (uint32_t i = 0; i < font->charInfoCount; ++i)
    {
        if (font->charInfo[i] == c)
        {
            *out = font->sheet->textureRectangles[i];
            return true;
        }
    }
    return false;
}

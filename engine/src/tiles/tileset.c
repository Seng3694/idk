#include "idk/tiles/tileset.h"

#include <stdlib.h>

idk_tileset_t *idk_tileset_create(
    const idk_texture_t *texture, const uint32_t tileWidth,
    const uint32_t tileHeight)
{
    idk_tileset_t *tileset = malloc(sizeof(idk_tileset_t));
    tileset->tileWidth = tileWidth;
    tileset->tileHeight = tileHeight;
    tileset->texture = texture;
    tileset->width = texture->width / tileWidth;
    tileset->height = texture->height / tileHeight;
    tileset->textureRectangles =
        malloc(sizeof(idk_rect_t) * tileset->width * tileset->height);

    idk_rect_t *rects = tileset->textureRectangles;
    for (uint32_t y = 0; y < tileset->height; ++y)
    {
        for (uint32_t x = 0; x < tileset->width; ++x)
        {
            const uint32_t index = y * tileset->width + x;
            rects[index] = idk_rectangle_create(
                x * tileWidth, y * tileHeight, tileWidth, tileHeight);
        }
    }

    return tileset;
}

void idk_tileset_destroy(idk_tileset_t *tileset)
{
    free(tileset->textureRectangles);
    free(tileset);
}

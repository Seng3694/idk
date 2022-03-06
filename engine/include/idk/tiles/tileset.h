#ifndef IDK_TILES_TILESET_H
#define IDK_TILES_TILESET_H

#include "idk/core/rectangle.h"
#include "idk/graphics/texture.h"

#include <stdint.h>

typedef struct idk_tileset
{
    const idk_texture_t *texture;
    uint32_t tileWidth;
    uint32_t tileHeight;
    uint32_t width;
    uint32_t height;
    idk_rectangle_t *textureRectangles;
} idk_tileset_t;

idk_tileset_t *idk_tileset_create(
    const idk_texture_t *texture, const uint32_t tileWidth,
    const uint32_t tileHeight);

void idk_tileset_destroy(idk_tileset_t *tileset);

#endif

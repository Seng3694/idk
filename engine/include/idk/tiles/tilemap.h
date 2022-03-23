#ifndef IDK_TILES_TILEMAP_H
#define IDK_TILES_TILEMAP_H

#include "idk/core/common.h"

IDK_C_API_BEGIN

#include "idk/core/vertex.h"
#include "idk/tiles/tileset.h"

#include <stdint.h>

typedef uint8_t tile_id;

#define IDK_EMPTY_TILE ((uint8_t)0)

typedef struct idk_tilemap
{
    uint32_t width;
    uint32_t height;
    const idk_tileset_t *tileset;
    tile_id *tiles;
    idk_vertex_t *vertices;
} idk_tilemap_t;

idk_tilemap_t *idk_tilemap_create(
    const uint32_t width, const uint32_t height, const idk_tileset_t *tileset,
    tile_id *tiles);

void idk_tilemap_destroy(idk_tilemap_t *tilemap);

inline tile_id idk_tilemap_get_tile(idk_tilemap_t *tilemap, const uint32_t x, const uint32_t y)
{
    if (y * tilemap->width + x >= tilemap->width * tilemap->height)
        return IDK_EMPTY_TILE;
    return tilemap->tiles[y * tilemap->width + x];
}

void idk_tilemap_update_vertex(idk_tilemap_t *tilemap, const uint32_t index);

IDK_C_API_END

#endif

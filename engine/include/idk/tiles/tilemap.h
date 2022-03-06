#ifndef IDK_TILES_TILEMAP_H
#define IDK_TILES_TILEMAP_H

#include "idk/tiles/tileset.h"

#include <stdint.h>

typedef uint8_t tile_id;

#define IDK_EMPTY_TILE ((uint8_t)0)

typedef struct idk_tile_vertex
{
    float posX;
    float posY;
    float texX;
    float texY;
} idk_tile_vertex_t;

typedef struct idk_tilemap
{
    uint32_t width;
    uint32_t height;
    const idk_tileset_t *tileset;
    const tile_id *tiles;

    idk_tile_vertex_t *vertices;
    uint32_t vao;
    uint32_t vbo;
} idk_tilemap_t;

idk_tilemap_t *idk_tilemap_create(
    const uint32_t width, const uint32_t height, const idk_tileset_t *tileset,
    const tile_id *tiles);

void idk_tilemap_destroy(idk_tilemap_t *tilemap);

#endif

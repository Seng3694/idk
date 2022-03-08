#ifndef TILES_TILESET_TESTS_H
#define TILES_TILESET_TESTS_H

#include "idk_test.h"

#include <idk/tiles/tileset.h>

IDK_TEST(TilesTilesetCreateTest)
{
    const uint32_t tileWidth = 47;
    const uint32_t tileHeight = 73;

    idk_texture_t texture = (idk_texture_t){
        .id = 0,
        .width = 94,
        .height = 146
    };

    idk_tileset_t *tileset =
        idk_tileset_create(&texture, tileWidth, tileHeight);

    IDK_ASSERT(tileset != NULL);
    IDK_ASSERT(tileset->textureRectangles != NULL);

    const uint32_t expectedTileWidth = 47;
    const uint32_t expectedTileHeight = 73;
    const uint32_t expectedTilesetWidth = 2;
    const uint32_t expectedTilesetHeight = 2;

    bool success = expectedTileWidth == tileset->tileWidth &&
                   expectedTileHeight == tileset->tileHeight &&
                   expectedTilesetWidth == tileset->width &&
                   expectedTilesetHeight == tileset->height;
    if (!success)
    {
        idk_tileset_destroy(tileset);
        IDK_ASSERT(success);
    }

    //4 tiles
    const idk_rect_t tl = idk_rectangle_create(0,   0, 47, 73);
    const idk_rect_t tr = idk_rectangle_create(47,  0, 47, 73);
    const idk_rect_t bl = idk_rectangle_create(0,  73, 47, 73);
    const idk_rect_t br = idk_rectangle_create(47, 73, 47, 73);

    const idk_rect_t *rects = tileset->textureRectangles;
    success = memcmp(&tl, &rects[0], sizeof(idk_rect_t)) == 0 &&
              memcmp(&tr, &rects[1], sizeof(idk_rect_t)) == 0 &&
              memcmp(&bl, &rects[2], sizeof(idk_rect_t)) == 0 &&
              memcmp(&br, &rects[3], sizeof(idk_rect_t)) == 0;

    if (!success)
    {
        idk_tileset_destroy(tileset);
        IDK_ASSERT(success);
    }

    idk_tileset_destroy(tileset);

    return IDK_SUCCESS;
}

#define TilesTilesetTests TilesTilesetCreateTest

#endif

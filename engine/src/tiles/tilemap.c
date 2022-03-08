#include "idk/tiles/tilemap.h"

#include <glad/glad.h>

#include <stdlib.h>

static void idk_tilemap_set_tile_vertices(
    idk_tilemap_t *tilemap, const uint32_t x, const uint32_t y);

idk_tilemap_t *idk_tilemap_create(
    const uint32_t width, const uint32_t height, const idk_tileset_t *tileset,
    tile_id *tiles)
{
    idk_tilemap_t *tilemap = malloc(sizeof(idk_tilemap_t));
    tilemap->width = width;
    tilemap->height = height;
    tilemap->tileset = tileset;
    tilemap->tiles = tiles;

    const uint32_t totalVertexSize = width * height * 6 * sizeof(idk_vertex_t);
    tilemap->vertices = malloc(totalVertexSize);

    for (uint32_t y = 0; y < height; ++y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {
            idk_tilemap_set_tile_vertices(tilemap, x, y);
        }
    }

    return tilemap;
}

void idk_tilemap_destroy(idk_tilemap_t *tilemap)
{
    free(tilemap->vertices);
    free(tilemap);
}

void idk_tilemap_update_vertex(idk_tilemap_t *tilemap, const uint32_t index)
{
    const uint32_t x = index % tilemap->width;
    const uint32_t y = index / tilemap->width;
    idk_tilemap_set_tile_vertices(tilemap, x, y);
}

static void idk_tilemap_set_tile_vertices(
    idk_tilemap_t *tilemap, const uint32_t x, const uint32_t y)
{
    const uint32_t index = y * tilemap->width + x;
    const uint32_t vindex = index * 6;
    const tile_id tileID = tilemap->tiles[index];
    const idk_rect_t *textureRect =
        &tilemap->tileset->textureRectangles[tileID];
    const idk_texture_t *texture = tilemap->tileset->texture;

    const float tex_l = textureRect->left / texture->width;
    const float tex_t = textureRect->top / texture->height;
    const float tex_r = tex_l + (textureRect->width / texture->width);
    const float tex_b = tex_t + (textureRect->height / texture->height);

    const float tile_l = (x * tilemap->tileset->tileWidth);
    const float tile_t = (y * tilemap->tileset->tileHeight);
    const float tile_r =
        ((x * tilemap->tileset->tileWidth) + tilemap->tileset->tileWidth);
    const float tile_b =
        ((y * tilemap->tileset->tileHeight) + tilemap->tileset->tileHeight);

    tilemap->vertices[vindex] =
        (idk_vertex_t){.pos = {tile_l, tile_b}, .texPos = {tex_l, tex_b}};

    tilemap->vertices[vindex + 1] =
        (idk_vertex_t){.pos = {tile_r, tile_t}, .texPos = {tex_r, tex_t}};

    tilemap->vertices[vindex + 2] =
        (idk_vertex_t){.pos = {tile_l, tile_t}, .texPos = {tex_l, tex_t}};

    tilemap->vertices[vindex + 3] =
        (idk_vertex_t){.pos = {tile_l, tile_b}, .texPos = {tex_l, tex_b}};

    tilemap->vertices[vindex + 4] =
        (idk_vertex_t){.pos = {tile_r, tile_b}, .texPos = {tex_r, tex_b}};

    tilemap->vertices[vindex + 5] =
        (idk_vertex_t){.pos = {tile_r, tile_t}, .texPos = {tex_r, tex_t}};
}

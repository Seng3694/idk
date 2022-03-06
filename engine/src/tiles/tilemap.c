#include "idk/tiles/tilemap.h"

#include <glad/glad.h>

#include <stdlib.h>

idk_tilemap_t *idk_tilemap_create(
    const uint32_t width, const uint32_t height, const idk_tileset_t *tileset,
    const tile_id *tiles)
{
    idk_tilemap_t *tilemap = malloc(sizeof(idk_tilemap_t));
    tilemap->width = width;
    tilemap->height = height;
    tilemap->tileset = tileset;
    tilemap->tiles = tiles;

    const uint32_t totalVertexSize =
        width * height * 6 * sizeof(idk_tile_vertex_t);
    tilemap->vertices = malloc(totalVertexSize);

    for (uint32_t y = 0; y < height; ++y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {
            const uint32_t index = y * width + x;
            const uint32_t vindex = index * 6;
            const tile_id tileID = tilemap->tiles[index];
            const idk_rect_t *textureRect =
                &tilemap->tileset->textureRectangles[tileID];
            const idk_texture_t *texture = tilemap->tileset->texture;

            const float l = textureRect->left / texture->width;
            const float t = textureRect->top / texture->height;
            const float r = l + (textureRect->width / texture->width);
            const float b = t + (textureRect->height / texture->height);
            const float vx = x * tilemap->tileset->tileWidth;
            const float vy = y * tilemap->tileset->tileHeight;

            tilemap->vertices[vindex] = (idk_tile_vertex_t){
                .posX = vx, .posY = vy, .texX = l, .texY = b};

            tilemap->vertices[vindex + 1] = (idk_tile_vertex_t){
                .posX = vx, .posY = vy, .texX = r, .texY = t};

            tilemap->vertices[vindex + 2] = (idk_tile_vertex_t){
                .posX = vx, .posY = vy, .texX = l, .texY = t};

            tilemap->vertices[vindex + 3] = (idk_tile_vertex_t){
                .posX = vx, .posY = vy, .texX = l, .texY = b};

            tilemap->vertices[vindex + 4] = (idk_tile_vertex_t){
                .posX = vx, .posY = vy, .texX = r, .texY = b};

            tilemap->vertices[vindex + 5] = (idk_tile_vertex_t){
                .posX = vx, .posY = vy, .texX = r, .texY = t};
        }
    }

    glGenVertexArrays(1, &tilemap->vao);
    glGenBuffers(1, &tilemap->vbo);

    glBindVertexArray(tilemap->vao);
    glBindBuffer(GL_ARRAY_BUFFER, tilemap->vbo);
    glBufferData(
        GL_ARRAY_BUFFER, totalVertexSize, tilemap->vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(idk_tile_vertex_t), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return tilemap;
}

void idk_tilemap_destroy(idk_tilemap_t *tilemap)
{

    glDeleteBuffers(1, &tilemap->vbo);
    glDeleteVertexArrays(1, &tilemap->vao);
    free(tilemap->vertices);
    free(tilemap);
}

void idk_tilemap_render(idk_tilemap_t *tilemap)
{
    //TODO: see sprite renderer code
}

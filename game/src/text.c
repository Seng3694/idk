#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

static void idk_text_set_char_vertices(idk_text_t *text, const uint32_t index);

idk_text_t *idk_text_create(const idk_font_t *font, const uint32_t capacity)
{
    idk_text_t *text = malloc(sizeof(idk_text_t));
    text->capacity = capacity;
    text->length = 0;
    text->data = calloc(capacity + 1, sizeof(char));
    text->font = font;
    text->vertices = calloc(capacity * 6, sizeof(idk_vertex_t));
    return text;
}

void idk_text_print(idk_text_t *text, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsnprintf_s(text->data, text->capacity + 1, text->data, fmt, args);
    va_end(args);

    text->length = (uint32_t)strlen(text->data);
    for (uint32_t i = 0; i < text->length; ++i)
        idk_text_set_char_vertices(text, i);
}

void idk_text_destroy(idk_text_t *text)
{
    free(text->data);
    free(text->vertices);
    free(text);
}

static void idk_text_set_char_vertices(
    idk_text_t *text, const uint32_t index)
{
    const uint32_t vindex = index * 6;
    const char c = text->data[index];
    idk_rect_t textureRect;
    assert(idk_font_get_char_rect(text->font, c, &textureRect));
        
    const idk_texture_t *texture = text->font->sheet->texture;

    const float tex_l = textureRect.left / texture->width;
    const float tex_t = textureRect.top / texture->height;
    const float tex_r = tex_l + (textureRect.width / texture->width);
    const float tex_b = tex_t + (textureRect.height / texture->height);

    const float margin = 1.5f;
    const float tile_l = index * text->font->sheet->tileWidth + margin;
    const float tile_t = margin;
    const float tile_r = ((index * text->font->sheet->tileWidth) + text->font->sheet->tileWidth) - margin;
    const float tile_b = text->font->sheet->tileHeight - margin;

    text->vertices[vindex] =
        (idk_vertex_t){.pos = {tile_l, tile_b}, .texPos = {tex_l, tex_b}};

    text->vertices[vindex + 1] =
        (idk_vertex_t){.pos = {tile_r, tile_t}, .texPos = {tex_r, tex_t}};

    text->vertices[vindex + 2] =
        (idk_vertex_t){.pos = {tile_l, tile_t}, .texPos = {tex_l, tex_t}};

    text->vertices[vindex + 3] =
        (idk_vertex_t){.pos = {tile_l, tile_b}, .texPos = {tex_l, tex_b}};

    text->vertices[vindex + 4] =
        (idk_vertex_t){.pos = {tile_r, tile_b}, .texPos = {tex_r, tex_b}};

    text->vertices[vindex + 5] =
        (idk_vertex_t){.pos = {tile_r, tile_t}, .texPos = {tex_r, tex_t}};
}

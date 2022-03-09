#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include "font.h"
#include <idk/core/vertex.h>

typedef struct idk_text
{
    const idk_font_t *font;
    uint32_t length;
    uint32_t capacity;
    char *data;
    idk_vertex_t *vertices;
} idk_text_t;

idk_text_t *idk_text_create(const idk_font_t *font, const uint32_t capacity);
void idk_text_destroy(idk_text_t *text);

void idk_text_print(idk_text_t *text, const char *fmt, ...);

#endif

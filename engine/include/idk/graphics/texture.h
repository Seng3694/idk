#ifndef IDK_GRAPHICS_TEXTURE_H
#define IDK_GRAPHICS_TEXTURE_H

#include "idk/core/common.h"

IDK_C_API_BEGIN

#include <stdint.h>
#include "idk/core/color.h"

typedef struct idk_texture
{
    uint32_t id;
    uint32_t width;
    uint32_t height;
} idk_texture_t;

#define IDK_TEXTURE_INVALID ((idk_texture_t){.id = 0, .width = 0, .height = 0})

idk_texture_t idk_texture_load_from_memory(
    const uint32_t width, const uint32_t height, const idk_color_t *data);
idk_texture_t idk_texture_load_from_file(const char *path);

void idk_texture_destroy(const idk_texture_t *texture);

void idk_texture_bind(const idk_texture_t *texture);

IDK_C_API_END

#endif

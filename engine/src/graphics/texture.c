#include "idk/graphics/texture.h"

#include "idk/core/common.h"
#include <glad/glad.h>
#include <stb_image.h>

idk_texture_t idk_texture_load_from_memory(
    const uint32_t width, const uint32_t height, const idk_color_t *data)
{
    idk_texture_t texture = {.width = width, .height = height};
    
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
        (const void *)data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

idk_texture_t idk_texture_load_from_file(const char *path)
{
    int32_t width, height, channels;
    const idk_color_t *data =
        (idk_color_t *)stbi_load(path, &width, &height, &channels, 4);
    if (!data)
    {
        LOG("Error loading texture \"%s\".\n", path);
        return IDK_TEXTURE_INVALID;
    }
    idk_texture_t texture = idk_texture_load_from_memory(
        (uint32_t)width, (uint32_t)height, data);

    stbi_image_free((void*)data);
    return texture;
}

void idk_texture_destroy(const idk_texture_t *texture)
{
    glDeleteTextures(1, &texture->id);
}

void idk_texture_bind(const idk_texture_t *texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

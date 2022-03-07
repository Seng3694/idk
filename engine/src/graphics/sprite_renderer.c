#include "idk/graphics/sprite_renderer.h"
#include "idk/graphics/shader.h"
#include "idk/core/common.h"
#include "idk/core/matrix4.h"
#include "idk/core/file_system.h"

#include <glad/glad.h>
#include <stdlib.h>

typedef struct idk_sprite_renderer
{
    idk_window_t *window;
    idk_shader_t shader;
    uint32_t vao;
    uint32_t vbo;
} idk_sprite_renderer_t;

idk_sprite_renderer_t *idk_sprite_renderer_create(idk_window_t* window)
{
    idk_sprite_renderer_t *renderer = malloc(sizeof(idk_sprite_renderer_t));
    renderer->window = window;

    char *vertShaderCode = NULL;
    if(!idk_file_system_load_file_string("content/shaders/sprite.vert", &vertShaderCode))
    {
        free(renderer);
        return NULL;
    }

    char *fragShaderCode = NULL;
    if(!idk_file_system_load_file_string("content/shaders/sprite.frag", &fragShaderCode))
    {
        free(renderer);
        return NULL;
    }

    renderer->shader = idk_shader_create_vf(vertShaderCode, fragShaderCode);

    free(vertShaderCode);
    free(fragShaderCode);

    idk_shader_use(renderer->shader);
    idk_shader_set_integer(renderer->shader, "u_Image", 0);

    float vertices[] = {// pos      // tex
                        0.0f, 1.0f, 0.0f, 1.0f, 
                        1.0f, 0.0f, 1.0f, 0.0f, 
                        0.0f, 0.0f, 0.0f, 0.0f,

                        0.0f, 1.0f, 0.0f, 1.0f, 
                        1.0f, 1.0f, 1.0f, 1.0f, 
                        1.0f, 0.0f, 1.0f, 0.0f};

    glGenVertexArrays(1, &renderer->vao);
    glGenBuffers(1, &renderer->vbo);

    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(renderer->vao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return renderer;
}

void idk_sprite_renderer_destroy(idk_sprite_renderer_t *renderer)
{
    idk_shader_destroy(renderer->shader);
    glDeleteBuffers(1, &renderer->vbo);
    glDeleteVertexArrays(1, &renderer->vao);
    free(renderer);
}

void idk_sprite_renderer_draw(
    idk_sprite_renderer_t *renderer, const idk_texture_t *texture,
    const idk_rect_t textureRect, const idk_vec2_t position,
    const idk_vec2_t origin, const idk_vec2_t size, const float rotate,
    const idk_color_t color)
{
    idk_mat4_t model = idk_matrix4_identity();
    idk_matrix4_translate2(&model, position);

    idk_matrix4_rotate_center2(&model, rotate, origin);

    idk_matrix4_scale2(&model, size);

    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);

    idk_mat4_t modelView;
    idk_matrix4_combine(view, model, &modelView);

    idk_shader_use(renderer->shader);
    idk_shader_set_matrix4(renderer->shader, "u_ModelView", &modelView);
    idk_shader_set_color(renderer->shader, "u_Color", color);

    glActiveTexture(GL_TEXTURE0);
    idk_texture_bind(texture);

    if (textureRect.left != 0 || textureRect.top != 0 ||
        textureRect.width != texture->width ||
        textureRect.height != texture->height)
    {
        const float l = textureRect.left / texture->width;
        const float t = textureRect.top / texture->height;
        const float r = l + (textureRect.width / texture->width);
        const float b = t + (textureRect.height / texture->height);

        const float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, l, b, 
            1.0f, 0.0f, r, t, 
            0.0f, 0.0f, l, t,

            0.0f, 1.0f, l, b, 
            1.0f, 1.0f, r, b, 
            1.0f, 0.0f, r, t};

        glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    }
    
    glBindVertexArray(renderer->vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

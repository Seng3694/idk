#include "idk/graphics/sprite_renderer.h"
#include "idk/graphics/shader.h"
#include "idk/core/common.h"
#include "idk/core/matrix4.h"
#include "idk/core/file_system.h"

#include <glad/glad.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

typedef struct idk_sprite_shader_uniform
{
    idk_shader_t shaderID;
    int32_t u_Image;
    int32_t u_Color;
    int32_t u_ModelView;
} idk_sprite_shader_uniform_t;

typedef struct idk_sprite_renderer
{
    idk_sprite_shader_uniform_t uniform;
    idk_window_t *window;
    uint32_t vao;
    uint32_t vbo;
} idk_sprite_renderer_t;

idk_sprite_renderer_t *idk_sprite_renderer_create(idk_window_t* window)
{
    idk_sprite_renderer_t *renderer = malloc(sizeof(idk_sprite_renderer_t));
    renderer->window = window;
    renderer->uniform.u_Color = -1;
    renderer->uniform.u_ModelView = -1;
    renderer->uniform.shaderID = 0;

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
    glDeleteBuffers(1, &renderer->vbo);
    glDeleteVertexArrays(1, &renderer->vao);
    free(renderer);
}

void idk_sprite_renderer_draw(
    idk_sprite_renderer_t *renderer, const idk_texture_t *texture,
    const idk_rect_t textureRect, const idk_vec2_t position,
    const idk_vec2_t origin, const idk_vec2_t scale, const float rotate,
    const idk_color_t color, idk_sprite_flip_states_t flipStates,
    idk_render_states_t renderStates)
{
    idk_mat4_t model = idk_matrix4_identity();
    idk_matrix4_translate2(&model, position);

    idk_matrix4_translate(&model, origin.x, origin.y);
    idk_matrix4_rotate_z(&model, rotate);

    if ((flipStates & IDK_SPRITE_FLIP_HORIZONTAL) == IDK_SPRITE_FLIP_HORIZONTAL)
        idk_matrix4_rotate_x(&model, M_PI);
    if ((flipStates & IDK_SPRITE_FLIP_VERTICAL) ==
        IDK_SPRITE_FLIP_VERTICAL)
        idk_matrix4_rotate_y(&model, M_PI);

    idk_matrix4_translate(&model, -origin.x, -origin.y);

    idk_matrix4_scale2(&model, scale);

    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);

    idk_mat4_t modelView;
    idk_matrix4_combine(view, model, &modelView);

    idk_mat4_t transform;
    idk_matrix4_combine(modelView, renderStates.currentMatrix, &transform);

    idk_shader_use(renderStates.currentShader);
    if (renderer->uniform.shaderID != renderStates.currentShader)
    {
        renderer->uniform.shaderID = renderStates.currentShader;
        renderer->uniform.u_Image = -1;
        renderer->uniform.u_Color = -1;
        renderer->uniform.u_ModelView = -1;
    }

    if (renderer->uniform.u_Image == -1)
        renderer->uniform.u_Image =
            glGetUniformLocation(renderStates.currentShader, "u_Image");
    if (renderer->uniform.u_Color == -1)
        renderer->uniform.u_Color =
            glGetUniformLocation(renderStates.currentShader, "u_Color");
    if (renderer->uniform.u_ModelView == -1)
        renderer->uniform.u_ModelView =
            glGetUniformLocation(renderStates.currentShader, "u_ModelView");

    idk_shader_set_integer(renderer->uniform.u_Image, 0);
    idk_shader_set_matrix4(renderer->uniform.u_ModelView, &transform);
    idk_shader_set_color(renderer->uniform.u_Color, color);

    idk_window_set_blend_mode(renderer->window, renderStates.currentBlendMode);

    glActiveTexture(GL_TEXTURE0);
    idk_texture_bind(texture);

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
    
    glBindVertexArray(renderer->vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

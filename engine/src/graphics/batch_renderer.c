#include "idk/graphics/batch_renderer.h"

#include <glad/glad.h>
#include <stdlib.h>

typedef struct idk_batch_renderer
{
    idk_window_t *window;
    const idk_texture_t *texture;
    uint32_t vertexCount;
    uint32_t vbo;
    uint32_t vao;
    const idk_vertex_t *vertices;
} idk_batch_renderer_t;

idk_batch_renderer_t *idk_batch_renderer_create(
    idk_window_t *window, const idk_texture_t *texture,
    const uint32_t vertexCount,
    const idk_vertex_t *vertices)
{
    idk_batch_renderer_t *renderer = malloc(sizeof(idk_batch_renderer_t));
    renderer->window = window;
    renderer->texture = texture;
    renderer->vertexCount = vertexCount;
    renderer->vertices = vertices;

    glGenVertexArrays(1, &renderer->vao);
    glGenBuffers(1, &renderer->vbo);

    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferData(
        GL_ARRAY_BUFFER, vertexCount * sizeof(idk_vertex_t), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE, sizeof(idk_vertex_t), (void *)0);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE, sizeof(idk_vertex_t),
        (void *)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return renderer;
}

void idk_batch_renderer_destroy(idk_batch_renderer_t *renderer)
{
    glDeleteBuffers(1, &renderer->vbo);
    glDeleteVertexArrays(1, &renderer->vao);
    free(renderer);
}

void idk_batch_renderer_update(idk_batch_renderer_t *renderer)
{
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferSubData(
        GL_ARRAY_BUFFER, 0, renderer->vertexCount * sizeof(idk_vertex_t), renderer->vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void idk_batch_renderer_reset(
    idk_batch_renderer_t *renderer, const idk_texture_t *texture,
    const uint32_t vertexCount,
    const idk_vertex_t *vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    //only resize if bigger. keep it big if it's smaller
    if (vertexCount > renderer->vertexCount)
    {
        glBufferData(
            GL_ARRAY_BUFFER, vertexCount * sizeof(idk_vertex_t), vertices,
            GL_STATIC_DRAW);
    }
    else
    {
        glBufferSubData(
            GL_ARRAY_BUFFER, 0, vertexCount * sizeof(idk_vertex_t), vertices);
    }

    renderer->vertices = vertices;
    renderer->vertexCount = vertexCount;
    renderer->texture = texture;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void idk_batch_renderer_draw(
    idk_batch_renderer_t *renderer, idk_render_states_t renderStates)
{
    glActiveTexture(GL_TEXTURE0);
    idk_texture_bind(renderer->texture);

    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBindVertexArray(renderer->vao);

    idk_shader_use(renderStates.currentShader);
    idk_shader_set_integer(renderStates.currentShader, "u_Image", 0);
    idk_shader_set_color(
        renderStates.currentShader, "u_Color", (idk_color_t){255, 255, 255, 255});

    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);

    idk_mat4_t modelView;
    idk_matrix4_combine(renderStates.currentMatrix, view, &modelView);

    idk_shader_set_matrix4(
        renderStates.currentShader, "u_ModelView", &modelView);

    glDrawArrays(GL_TRIANGLES, 0, renderer->vertexCount);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

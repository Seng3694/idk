#include "idk/core/file_system.h"
#include "idk/core/matrix4.h"
#include "idk/graphics/primitives_renderer.h"
#include "idk/graphics/shader.h"
#include <stdlib.h>
#include <glad/glad.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define CIRCLE_POINT_COUNT 24

#define VERTEX_SIZE (sizeof(float) * 2)
#define POINT_VERTEX_COUNT 1
#define LINE_VERTEX_COUNT 2
#define TRIANGLE_VERTEX_COUNT 3
#define RECTANGLE_VERTEX_COUNT 4
#define RECTANGLE_FILL_VERTEX_COUNT 6
#define CIRCLE_VERTEX_COUNT (CIRCLE_POINT_COUNT)
#define CIRCLE_FILL_VERTEX_COUNT (CIRCLE_VERTEX_COUNT + 2)

#define TOTAL_VERTEX_COUNT                                                    \
    (POINT_VERTEX_COUNT + LINE_VERTEX_COUNT + TRIANGLE_VERTEX_COUNT +         \
     RECTANGLE_VERTEX_COUNT + RECTANGLE_FILL_VERTEX_COUNT +                   \
     CIRCLE_VERTEX_COUNT + CIRCLE_FILL_VERTEX_COUNT)

#define TOTAL_VERTEX_SIZE (TOTAL_VERTEX_COUNT * VERTEX_SIZE)

#define POINT_OFFSET 0
#define LINE_OFFSET (POINT_VERTEX_COUNT)
#define TRIANGLE_OFFSET (LINE_OFFSET + LINE_VERTEX_COUNT)
#define RECTANGLE_OFFSET (TRIANGLE_OFFSET + TRIANGLE_VERTEX_COUNT)
#define RECTANGLE_FILL_OFFSET (RECTANGLE_OFFSET + RECTANGLE_VERTEX_COUNT)
#define CIRCLE_OFFSET (RECTANGLE_FILL_OFFSET + RECTANGLE_FILL_VERTEX_COUNT)
#define CIRCLE_FILL_OFFSET (CIRCLE_OFFSET + CIRCLE_VERTEX_COUNT)

typedef struct idk_primitives_renderer
{
    idk_window_t *window;
    idk_shader_t shader;
    uint32_t vao;
    uint32_t vbo;
} idk_primitives_renderer_t;

idk_primitives_renderer_t *idk_primitives_renderer_create(idk_window_t *window)
{
    idk_primitives_renderer_t *renderer = malloc(sizeof(idk_primitives_renderer_t));
    renderer->window = window;

    char *vertShaderCode = NULL;
    if (!idk_file_system_load_file_string(
            "content/shaders/prim.vert", &vertShaderCode))
    {
        free(renderer);
        return NULL;
    }

    char *fragShaderCode = NULL;
    if (!idk_file_system_load_file_string(
            "content/shaders/prim.frag", &fragShaderCode))
    {
        free(renderer);
        free(vertShaderCode);
        return NULL;
    }

    renderer->shader = idk_shader_create_vf(vertShaderCode, fragShaderCode);

    free(vertShaderCode);
    free(fragShaderCode);

    glGenVertexArrays(1, &renderer->vao);
    glGenBuffers(1, &renderer->vbo);

    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, TOTAL_VERTEX_SIZE, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    idk_primitives_renderer_set_color2(renderer, 255, 255, 255, 255);

    return renderer;
}

void idk_primitives_renderer_destroy(idk_primitives_renderer_t *renderer)
{
    glDeleteVertexArrays(1, &renderer->vao);
    glDeleteBuffers(1, &renderer->vbo);
    idk_shader_destroy(renderer->shader);
    free(renderer);
}

void idk_primitives_renderer_set_color(
    idk_primitives_renderer_t *renderer, float r, float g, float b, float a)
{
    glUseProgram(renderer->shader);
    glUniform4fv(
        glGetUniformLocation(renderer->shader, "u_Color"), 1,
        (float[]){r, g, b, a});
    glUseProgram(0);
}
void idk_primitives_renderer_set_color2(
    idk_primitives_renderer_t *renderer, uint8_t r, uint8_t g, uint8_t b,
    uint8_t a)
{
    idk_primitives_renderer_set_color(
        renderer, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
void idk_primitives_renderer_set_color3(
    idk_primitives_renderer_t *renderer, const idk_color_t color)
{
    idk_primitives_renderer_set_color2(
        renderer, color.r, color.g, color.b, color.a);
}

void idk_draw_point(
    idk_primitives_renderer_t *renderer, const float x, const float y)
{
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    const float vertices[] = {x, y};
    glBufferSubData(
        GL_ARRAY_BUFFER, POINT_OFFSET * VERTEX_SIZE,
        POINT_VERTEX_COUNT * VERTEX_SIZE, vertices);

    idk_shader_use(renderer->shader);
    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);
    idk_shader_set_matrix4(renderer->shader, "u_ModelView", &view);

    glDrawArrays(GL_POINTS, POINT_OFFSET, POINT_VERTEX_COUNT);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void idk_draw_line(
    idk_primitives_renderer_t *renderer, const float x1, const float y1,
    const float x2, const float y2)
{
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    const float vertices[] = {x1, y1, x2, y2};
    glBufferSubData(
        GL_ARRAY_BUFFER, LINE_OFFSET * VERTEX_SIZE,
        LINE_VERTEX_COUNT * VERTEX_SIZE, vertices);
    
    idk_shader_use(renderer->shader);
    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);
    idk_shader_set_matrix4(renderer->shader, "u_ModelView", &view);

    glDrawArrays(GL_LINES, LINE_OFFSET, LINE_VERTEX_COUNT);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void idk_draw_triangle(
    idk_primitives_renderer_t *renderer, const float x1, const float y1,
    const float x2, const float y2, const float x3, const float y3)
{
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    const float vertices[] = {x1, y1, x2, y2, x3, y3};
    glBufferSubData(
        GL_ARRAY_BUFFER, TRIANGLE_OFFSET * VERTEX_SIZE,
        TRIANGLE_VERTEX_COUNT * VERTEX_SIZE, vertices);
    glUseProgram(renderer->shader);
    glDrawArrays(GL_LINE_LOOP, TRIANGLE_OFFSET, TRIANGLE_VERTEX_COUNT);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void idk_draw_triangle_fill(
    idk_primitives_renderer_t *renderer, const float x1, const float y1,
    const float x2, const float y2, const float x3, const float y3)
{
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    const float vertices[] = {x1, y1, x2, y2, x3, y3};
    glBufferSubData(
        GL_ARRAY_BUFFER, TRIANGLE_OFFSET * VERTEX_SIZE,
        TRIANGLE_VERTEX_COUNT * VERTEX_SIZE, vertices);

    idk_shader_use(renderer->shader);
    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);
    idk_shader_set_matrix4(renderer->shader, "u_ModelView", &view);

    glDrawArrays(GL_TRIANGLES, TRIANGLE_OFFSET, TRIANGLE_VERTEX_COUNT);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void idk_draw_rectangle(
    idk_primitives_renderer_t *renderer, const float x, const float y,
    const float width, const float height)
{
    idk_draw_rectangle2(renderer, x, y, x + width, y + height);
}

void idk_draw_rectangle2(
    idk_primitives_renderer_t *renderer, const float left, const float top,
    const float right, const float bottom)
{
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    const float vertices[] = {left,  top,    right, top,
                              right, bottom, left,  bottom};
    glBufferSubData(
        GL_ARRAY_BUFFER, RECTANGLE_OFFSET * VERTEX_SIZE,
        RECTANGLE_VERTEX_COUNT * VERTEX_SIZE, vertices);

    idk_shader_use(renderer->shader);
    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);
    idk_shader_set_matrix4(renderer->shader, "u_ModelView", &view);

    glDrawArrays(GL_LINE_LOOP, RECTANGLE_OFFSET, RECTANGLE_VERTEX_COUNT);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void idk_draw_rectangle_fill(
    idk_primitives_renderer_t *renderer, const float x, const float y,
    const float width, const float height)
{
    idk_draw_rectangle2_fill(renderer, x, y, x + width, y + height);
}
void idk_draw_rectangle2_fill(
    idk_primitives_renderer_t *renderer, const float left, const float top,
    const float right, const float bottom)
{
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    const float vertices[] = {left,  top,    right, top,    right, bottom,
                              right, bottom, left,  bottom, left,  top};
    glBufferSubData(
        GL_ARRAY_BUFFER, RECTANGLE_FILL_OFFSET * VERTEX_SIZE,
        RECTANGLE_FILL_VERTEX_COUNT * VERTEX_SIZE, vertices);

    idk_shader_use(renderer->shader);
    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);
    idk_shader_set_matrix4(renderer->shader, "u_ModelView", &view);
    
    glDrawArrays(
        GL_TRIANGLES, RECTANGLE_FILL_OFFSET, RECTANGLE_FILL_VERTEX_COUNT);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

static void get_circle_vertices(
    const float x, const float y, const float radius, float *vertices)
{
    for (uint32_t i = 0; i < CIRCLE_POINT_COUNT; ++i)
    {
        const float rad = i * ((2.0f * M_PI) / CIRCLE_POINT_COUNT);
        vertices[i * 2] = x + cosf(rad) * radius;
        vertices[(i * 2) + 1] = y + sinf(rad) * radius;
    }
}

void idk_draw_circle(
    idk_primitives_renderer_t *renderer, const float x, const float y,
    const float radius)
{
    float vertices[CIRCLE_VERTEX_COUNT * 2];
    get_circle_vertices(x, y, radius, vertices);
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferSubData(
        GL_ARRAY_BUFFER, CIRCLE_OFFSET * VERTEX_SIZE,
        CIRCLE_VERTEX_COUNT * VERTEX_SIZE, vertices);

    idk_shader_use(renderer->shader);
    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);
    idk_shader_set_matrix4(renderer->shader, "u_ModelView", &view);
    
    glDrawArrays(GL_LINE_LOOP, CIRCLE_OFFSET, CIRCLE_VERTEX_COUNT);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void idk_draw_circle_fill(
    idk_primitives_renderer_t *renderer, const float x, const float y,
    const float radius)
{
    float vertices[CIRCLE_FILL_VERTEX_COUNT * 2];
    // start point in center
    vertices[0] = x;
    vertices[1] = y;

    get_circle_vertices(x, y, radius, &(vertices[2]));

    // end point first vertex
    vertices[(CIRCLE_POINT_COUNT * 2) + 2] = vertices[2];
    vertices[(CIRCLE_POINT_COUNT * 2) + 3] = vertices[3];

    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferSubData(
        GL_ARRAY_BUFFER, CIRCLE_FILL_OFFSET * VERTEX_SIZE,
        CIRCLE_FILL_VERTEX_COUNT * VERTEX_SIZE, vertices);

    idk_shader_use(renderer->shader);
    idk_camera_t *cam = idk_window_get_camera(renderer->window);
    idk_mat4_t view;
    idk_camera_get_transform_matrix(cam, &view);
    idk_shader_set_matrix4(renderer->shader, "u_ModelView", &view);
    
    glDrawArrays(
        GL_TRIANGLE_FAN, CIRCLE_FILL_OFFSET, CIRCLE_FILL_VERTEX_COUNT);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

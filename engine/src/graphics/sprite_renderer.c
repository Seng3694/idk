#include "idk/graphics/sprite_renderer.h"
#include "idk/graphics/shader.h"
#include "idk/core/common.h"
#include "idk/core/matrix4.h"

#include <glad/glad.h>
#include <stdlib.h>

typedef struct idk_sprite_renderer
{
    idk_shader_t shader;
    uint32_t vao;
    uint32_t vbo;
} idk_sprite_renderer_t;

static const char *spriteVertShader = GLSL(
    "330 core",
    layout(location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

    out vec2 TexCoords;

    uniform mat4 model; uniform mat4 projection;

    void main() {
        TexCoords = vertex.zw;
        gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
    });

static const char *spriteFragShader = GLSL(
    "330 core", in vec2 TexCoords; out vec4 color;

    uniform sampler2D image; uniform vec4 spriteColor;

    void main() { color = spriteColor * texture(image, TexCoords); });

idk_sprite_renderer_t *idk_sprite_renderer_create(
    const uint32_t width, const uint32_t height)
{
    idk_sprite_renderer_t *renderer = malloc(sizeof(idk_sprite_renderer_t));

    renderer->shader =
        idk_shader_create_vf(spriteVertShader, spriteFragShader);

    idk_mat4_t projection;
    idk_matrix4_orthographic(
        &projection, 0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);

    idk_shader_use(renderer->shader);
    idk_shader_set_integer(renderer->shader, "image", 0);
    idk_shader_set_matrix4(renderer->shader, "projection", &projection);

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
    glVertexAttribPointer(
        0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
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

    idk_shader_use(renderer->shader);
    idk_shader_set_matrix4(renderer->shader, "model", &model);
    idk_shader_set_color(renderer->shader, "spriteColor", color);

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

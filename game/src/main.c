#include <idk/core/common.h>
#include <idk/graphics/primitives_renderer.h>
#include <idk/graphics/sprite_renderer.h>
#include <idk/graphics/shader.h>
#include <idk/graphics/window.h>
#include <idk/tiles/tileset.h>
#include <idk/tiles/tilemap.h>
#include <memory.h>

#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <stdlib.h>

#include <idk/core/rectangle.h>

#include <glad/glad.h>

static void render_rectangle(
    idk_primitives_renderer_t *pr, const idk_rect_t rect, uint8_t r, uint8_t g,
    uint8_t b, uint8_t a);

static void shapes_and_rendering(void);


static const char *spriteVertShader2 = GLSL(
    "330 core",
    layout(location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

    out vec2 TexCoords;

    uniform mat4 model; uniform mat4 projection;

    void main() {
        TexCoords = vertex.zw;
        gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
    });

static const char *spriteFragShader2 = GLSL(
    "330 core", in vec2 TexCoords; out vec4 color;

    uniform sampler2D image;

    void main() { color = texture(image, TexCoords); });

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

int main(void)
{
    
    idk_window_t *window =
        idk_window_create(WINDOW_WIDTH, WINDOW_HEIGHT, "testing");
    if (!window)
    {
        printf("something wrong\n");
        return 1;
    }
    idk_window_set_cursor_visibility(window, true);

    idk_color_t clearColor;
    idk_color_from_packed(&clearColor, 0x222222ff);


    const tile_id tiles[] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
        0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,
        0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,2,1,1,1,2,1,1,1,3,3,3,3,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };

    idk_texture_t texture = idk_texture_load_from_file("content/test_tileset1.png");
    idk_tileset_t *tileset = idk_tileset_create(&texture, 16, 16);
    idk_tilemap_t *tilemap = idk_tilemap_create(30, 10, tileset, tiles);

    idk_shader_t shader =
        idk_shader_create_vf(spriteVertShader2, spriteFragShader2);

    idk_primitives_renderer_t *pr =
        idk_primitives_renderer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    idk_mat4_t projection;
    idk_matrix4_orthographic(
        &projection, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

    idk_shader_use(shader);
    idk_shader_set_integer(shader, "image", 0);
    idk_shader_set_matrix4(shader, "projection", &projection);
    idk_shader_set_color(
        shader, "spriteColor",
        (idk_color_t){
            0xff,
            0xff,
            0xff,
            0xff});


    while (idk_window_is_open(window))
    {
        idk_window_poll_events(window);

        idk_window_set_clear_color(window, clearColor);
        idk_window_clear(window);

        idk_shader_use(shader);
        idk_mat4_t model = idk_matrix4_identity();
        idk_matrix4_translate2(&model, (idk_vec2_t){0, 0});
        
        idk_shader_set_matrix4(shader, "model", &model);

        glActiveTexture(GL_TEXTURE0);
        idk_texture_bind(&texture);

        glBindBuffer(GL_ARRAY_BUFFER, tilemap->vbo);
        glBindVertexArray(tilemap->vao);

        uint32_t vertexCount = tilemap->width * tilemap->height * 6;
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glBindVertexArray(0);

        idk_window_display(window);
    }

    idk_primitives_renderer_destroy(pr);
    idk_tilemap_destroy(tilemap);
    idk_tileset_destroy(tileset);
    idk_texture_destroy(&texture);
    idk_shader_destroy(shader);
    idk_window_destroy(window);
    return 0;
}

static void shapes_and_rendering(void)
{
    idk_window_t *window = idk_window_create(800, 600, "My Game");
    if (!window)
    {
        printf("something wrong\n");
        return;
    }
    idk_window_set_cursor_visibility(window, false);

    idk_color_t clearColor;
    idk_color_from_packed(&clearColor, 0x222222ff);

    idk_sprite_renderer_t *sr = idk_sprite_renderer_create(800, 600);
    idk_primitives_renderer_t *pr = idk_primitives_renderer_create(800, 600);

    idk_texture_t texture =
        idk_texture_load_from_file("content/test_tileset1.png");

    idk_vec2_t pos = {70.0f, 70.0f};
    idk_vec2_t size = {16 * 2, 16 * 2};
    idk_rectangle_t texRect = {.left = 0, .top = 0, .width = 16, .height = 16};
    idk_vec2_t origin = idk_vector2f_divf(size, 2.0f);
    idk_color_t color;
    idk_color_from_packed(&color, 0xffffffff);

    // float passedTime = 0.0f;

    idk_rect_t rect = idk_rectangle_create(400, 200, 150, 200);
    idk_rect_t other = idk_rectangle_create(400, 400, 100, 100);

    while (idk_window_is_open(window))
    {
        idk_window_poll_events(window);

        idk_rectangle_set_center(&other, idk_window_get_mouse_pos(window));

        idk_window_set_clear_color(window, clearColor);
        idk_window_clear(window);

        texRect.left = 0;
        pos.y = 70;
        for (int i = 0; i < 4; ++i)
        {
            pos.x = 70 + (i * 32);
            idk_sprite_renderer_draw(
                sr, &texture, texRect, pos, origin, size, 0.0f, color);
        }

        texRect.left = 16;
        pos.y = 102;
        for (int i = 0; i < 4; ++i)
        {
            pos.x = 70 + (i * 32);
            idk_sprite_renderer_draw(
                sr, &texture, texRect, pos, origin, size, 0.0f, color);
        }

        texRect.left = 32;
        pos.y = 134;
        for (int i = 0; i < 4; ++i)
        {
            pos.x = 70 + (i * 32);
            idk_sprite_renderer_draw(
                sr, &texture, texRect, pos, origin, size, 0.0f, color);
        }

        render_rectangle(pr, rect, 255, 10, 0, 100);
        render_rectangle(pr, other, 0, 10, 255, 100);

        idk_rect_t intersection;
        if (idk_rectangle_intersects(&rect, &other, &intersection))
        {
            if (memcmp(&intersection, &other, sizeof(idk_rectangle_t)) == 0)
                render_rectangle(pr, intersection, 170, 255, 10, 160);
            else
                render_rectangle(pr, intersection, 170, 255, 10, 100);
        }

        idk_window_display(window);
    }

    idk_texture_destroy(&texture);
    idk_primitives_renderer_destroy(pr);
    idk_sprite_renderer_destroy(sr);
    idk_window_destroy(window);
}

static void render_rectangle(
    idk_primitives_renderer_t *pr, const idk_rect_t rect, uint8_t r, uint8_t g,
    uint8_t b, uint8_t a)
{
    idk_primitives_renderer_set_color2(pr, r, g, b, a);
    idk_draw_rectangle_fill(pr, rect.left, rect.top, rect.width, rect.height);

    idk_primitives_renderer_set_color2(pr, b, g, r, 230);
    idk_vec2_t vec = rect.position;
    idk_draw_circle_fill(pr, vec.x, vec.y, 5);

    vec = idk_rectangle_topcenter(&rect);
    idk_draw_circle_fill(pr, vec.x, vec.y, 5);

    vec = idk_rectangle_topright(&rect);
    idk_draw_circle_fill(pr, vec.x, vec.y, 5);

    vec = idk_rectangle_rightcenter(&rect);
    idk_draw_circle_fill(pr, vec.x, vec.y, 5);

    vec = idk_rectangle_bottomright(&rect);
    idk_draw_circle_fill(pr, vec.x, vec.y, 5);

    vec = idk_rectangle_bottomcenter(&rect);
    idk_draw_circle_fill(pr, vec.x, vec.y, 5);

    vec = idk_rectangle_bottomleft(&rect);
    idk_draw_circle_fill(pr, vec.x, vec.y, 5);

    vec = idk_rectangle_leftcenter(&rect);
    idk_draw_circle_fill(pr, vec.x, vec.y, 5);

    vec = idk_rectangle_center(&rect);
    idk_draw_circle_fill(pr, vec.x, vec.y, 5);
}

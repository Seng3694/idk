#include <idk/core/common.h>
#include <idk/core/file_system.h>
#include <idk/graphics/batch_renderer.h>
#include <idk/graphics/camera.h>
#include <idk/graphics/primitives_renderer.h>
#include <idk/graphics/sprite_renderer.h>
#include <idk/graphics/shader.h>
#include <idk/graphics/window.h>
#include <idk/tiles/tileset.h>
#include <idk/tiles/tilemap.h>
#include <memory.h>

#include <assert.h>
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
static void tilemaps_and_batch_rendering_2(void);

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

int main(void)
{
    //shapes_and_rendering();
    tilemaps_and_batch_rendering_2();
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

    idk_sprite_renderer_t *sr = idk_sprite_renderer_create(window);
    idk_primitives_renderer_t *pr = idk_primitives_renderer_create(window);

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

    char* vertShaderSource = NULL;
    assert(idk_file_system_load_file_string(
        "content/shaders/sprite.vert", &vertShaderSource));
    char *fragShaderSource = NULL;
    assert(idk_file_system_load_file_string(
        "content/shaders/sprite.frag", &fragShaderSource));

    idk_shader_t shader =
        idk_shader_create_vf(vertShaderSource, fragShaderSource);

    idk_render_states_t states = {
        .currentShader = shader, .currentMatrix = idk_matrix4_identity()
    };

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
                sr, &texture, texRect, pos, origin, size, 0.0f, color, states);
        }

        texRect.left = 16;
        pos.y = 102;
        for (int i = 0; i < 4; ++i)
        {
            pos.x = 70 + (i * 32);
            idk_sprite_renderer_draw(
                sr, &texture, texRect, pos, origin, size, 0.0f, color, states);
        }

        texRect.left = 32;
        pos.y = 134;
        for (int i = 0; i < 4; ++i)
        {
            pos.x = 70 + (i * 32);
            idk_sprite_renderer_draw(
                sr, &texture, texRect, pos, origin, size, 0.0f, color, states);
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

    idk_shader_destroy(shader);
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

static void tilemaps_and_batch_rendering_2(void)
{
    idk_window_t *window =
        idk_window_create(WINDOW_WIDTH, WINDOW_HEIGHT, "testing");
    if (!window)
    {
        printf("something wrong\n");
        return;
    }
    idk_window_set_cursor_visibility(window, true);

    idk_color_t clearColor;
    idk_color_from_packed(&clearColor, 0x000b1eff);

    tile_id tiles[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1,
        1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 3, 3, 3, 3, 1,
        1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    idk_texture_t texture =
        idk_texture_load_from_file("content/test_tileset1.png");
    idk_tileset_t *tileset = idk_tileset_create(&texture, 16, 16);
    idk_tilemap_t *tilemap = idk_tilemap_create(30, 13, tileset, tiles);

    idk_batch_renderer_t *br = idk_batch_renderer_create(
        window, &texture, tilemap->width * tilemap->height * 6, tilemap->vertices);

    idk_camera_t *cam = idk_window_get_camera(window);
    idk_camera_set_center(
        cam, (idk_vec2_t){
                 (WINDOW_WIDTH / 4.0f) / 2.0f,
                 (WINDOW_HEIGHT / 4.0f) / 2.0f + 16 * 4});
    idk_camera_set_size(
        cam, (idk_vec2_t){WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 4.0f});

    char *vertShaderSource = NULL;
    assert(idk_file_system_load_file_string(
        "content/shaders/sprite.vert", &vertShaderSource));
    char *fragShaderSource = NULL;
    assert(idk_file_system_load_file_string(
        "content/shaders/sprite.frag", &fragShaderSource));

    idk_shader_t shader =
        idk_shader_create_vf(vertShaderSource, fragShaderSource);

    idk_render_states_t states = {
        .currentShader = shader, .currentMatrix = idk_matrix4_identity()};

    while (idk_window_is_open(window))
    {
        idk_window_poll_events(window);

        idk_window_set_clear_color(window, clearColor);
        idk_window_clear(window);

        float dt = idk_window_get_dt(window);
        idk_vec2_t camMove = {0.0f, 0.0f};
        float camMoveSpeed = 200.0f * dt;
        if (idk_window_is_key_down(window, IDK_KEY_D))
        {
            camMove.x += 1;
        }
        if (idk_window_is_key_down(window, IDK_KEY_A))
        {
            camMove.x -= 1;
        }
        if (idk_window_is_key_down(window, IDK_KEY_W))
        {
            camMove.y -= 1;
        }
        if (idk_window_is_key_down(window, IDK_KEY_S))
        {
            camMove.y += 1;
        }
        if (camMove.x != 0 || camMove.y != 0)
            idk_vector2f_normalize_ref(&camMove);
        idk_vector2f_mulf_eq(&camMove, camMoveSpeed);

        idk_camera_move(cam, camMove);

        if (cam->center.x - cam->size.x / 2.0f < 0)
            cam->center.x = cam->size.x / 2.0f;
        if (cam->center.x + cam->size.x / 2.0f >
            tilemap->width * tilemap->tileset->tileWidth)
            cam->center.x = tilemap->width * tilemap->tileset->tileWidth -
                            cam->size.x / 2.0f;
        if (cam->center.y - cam->size.y / 2.0f < 0)
            cam->center.y = cam->size.y / 2.0f;
        if (cam->center.y + cam->size.y / 2.0f >
            tilemap->height * tilemap->tileset->tileHeight)
            cam->center.y = tilemap->height * tilemap->tileset->tileHeight -
                            cam->size.y / 2.0f;

        if (idk_window_is_mouse_down(window, IDK_MOUSE_BUTTON_LEFT))
        {
            idk_vec2_t mousePos = idk_window_get_mouse_pos(window);
            
            idk_vec2_t mapPixel =
                idk_window_map_pixel_to_coords(window, mousePos);

            idk_vector2f_divf_eq(&mapPixel, tilemap->tileset->tileWidth);
           
            const uint32_t mapIndex =
                (int)mapPixel.y * (int)tilemap->width + (int)mapPixel.x;
            tilemap->tiles[mapIndex] = 1;
            idk_tilemap_update_vertex(tilemap, mapIndex);
            idk_batch_renderer_reset(
                br, &texture, tilemap->width * tilemap->height * 6,
                tilemap->vertices);
        }
        if (idk_window_is_mouse_down(window, IDK_MOUSE_BUTTON_RIGHT))
        {
            idk_vec2_t mousePos = idk_window_get_mouse_pos(window);

            idk_vec2_t mapPixel =
                idk_window_map_pixel_to_coords(window, mousePos);

            idk_vector2f_divf_eq(&mapPixel, tilemap->tileset->tileWidth);

            const uint32_t mapIndex =
                (int)mapPixel.y * (int)tilemap->width + (int)mapPixel.x;
            tilemap->tiles[mapIndex] = 0;
            idk_tilemap_update_vertex(tilemap, mapIndex);
            idk_batch_renderer_update(br);
        }

        idk_batch_renderer_draw(br, states);

        idk_window_display(window);
    }

    idk_shader_destroy(shader);
    idk_batch_renderer_destroy(br);
    idk_tilemap_destroy(tilemap);
    idk_tileset_destroy(tileset);
    idk_texture_destroy(&texture);
    idk_window_destroy(window);
}

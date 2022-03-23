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

#include "font.h"
#include "text.h"

#include <assert.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <stdlib.h>

#include <idk/core/rectangle.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

int main(void)
{
    idk_window_t *window =
        idk_window_create(WINDOW_WIDTH, WINDOW_HEIGHT, "testing");
    if (!window)
    {
        printf("something wrong\n");
        return 0;
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

    idk_texture_t fontTexture = idk_texture_load_from_file("content/font.png");
    const char *charInfos = " abcdefghijklmnopqrstuvwxyz0123456789.,!?%ABC";
    idk_font_t *font = idk_font_create(&fontTexture, 16, 16, 45, charInfos);

    idk_batch_renderer_t *br = idk_batch_renderer_create(
        window, &texture, tilemap->width * tilemap->height * 6,
        tilemap->vertices);

    idk_text_t *text = idk_text_create(font, 45);
    idk_text_print(text, "%s", charInfos);
    idk_batch_renderer_t *fontRenderer = idk_batch_renderer_create(
        window, &fontTexture, text->capacity * 6, text->vertices);

    idk_camera_t cam = *idk_window_get_camera(window);
    idk_camera_set_center(
        &cam, (idk_vec2_t){
                  (WINDOW_WIDTH / 4.0f) / 2.0f,
                  (WINDOW_HEIGHT / 4.0f) / 2.0f + 16 * 4});
    idk_camera_set_size(
        &cam, (idk_vec2_t){WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 4.0f});

    char *vertShaderSource = NULL;
    assert(idk_file_system_load_file_string(
        "content/shaders/sprite.vert", &vertShaderSource));
    char *fragShaderSource = NULL;
    assert(idk_file_system_load_file_string(
        "content/shaders/sprite.frag", &fragShaderSource));

    idk_shader_t shader =
        idk_shader_create_vf(vertShaderSource, fragShaderSource);

    const int32_t shaderColorUniform = idk_shader_get_uniform_location(shader, "u_Color");

    idk_render_states_t states = {
        .currentShader = shader, .currentMatrix = idk_matrix4_identity()};

    float totalElapsed = 0.0f;
    while (idk_window_is_open(window))
    {
        idk_window_poll_events(window);

        idk_window_set_clear_color(window, clearColor);
        idk_window_clear(window);

        float dt = idk_window_get_dt(window);
        totalElapsed += dt;
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

        idk_camera_move(&cam, camMove);

        if (cam.center.x - cam.size.x / 2.0f < 0)
            cam.center.x = cam.size.x / 2.0f;
        if (cam.center.x + cam.size.x / 2.0f >
            tilemap->width * tilemap->tileset->tileWidth)
            cam.center.x = tilemap->width * tilemap->tileset->tileWidth -
                           cam.size.x / 2.0f;
        if (cam.center.y - cam.size.y / 2.0f < 0)
            cam.center.y = cam.size.y / 2.0f;
        if (cam.center.y + cam.size.y / 2.0f >
            tilemap->height * tilemap->tileset->tileHeight)
            cam.center.y = tilemap->height * tilemap->tileset->tileHeight -
                           cam.size.y / 2.0f;

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

        states.currentMatrix = idk_matrix4_identity();
        idk_window_set_camera(window, &cam);
        idk_batch_renderer_draw(br, states);

        states.currentMatrix = idk_matrix4_identity();
        idk_vec2_t interfacePos = {10, WINDOW_HEIGHT - 30};
        interfacePos = idk_window_map_pixel_to_coords(window, interfacePos);
        idk_matrix4_translate2(&states.currentMatrix, interfacePos);
        idk_matrix4_scale(&states.currentMatrix, 0.4f, 0.4f);

        idk_color_t color = {
            .r = (uint8_t)(((sinf(totalElapsed) + 1) / 2.0f) * 255),
            .g = (uint8_t)(((cosf(totalElapsed) + 1) / 2.0f) * 255),
            .b = (uint8_t)(((sinf(totalElapsed - M_PI) + 1) / 2.0f) * 255),
            .a = 255};

        idk_shader_set_color(shaderColorUniform, color);

        idk_text_print(text, "fps B %8.3f noice", 1 / dt);
        idk_batch_renderer_reset(
            fontRenderer, text->font->sheet->texture, text->length * 6,
            text->vertices);

        idk_batch_renderer_draw(fontRenderer, states);

        idk_window_display(window);
    }

    idk_shader_destroy(shader);
    idk_text_destroy(text);
    idk_font_destroy(font);
    idk_batch_renderer_destroy(fontRenderer);
    idk_batch_renderer_destroy(br);
    idk_tilemap_destroy(tilemap);
    idk_tileset_destroy(tileset);
    idk_texture_destroy(&fontTexture);
    idk_texture_destroy(&texture);
    idk_window_destroy(window);
    return 0;
}

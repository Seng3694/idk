#ifndef IDK_GRAPHICS_WINDOW_H
#define IDK_GRAPHICS_WINDOW_H

#include <stdbool.h>
#include <stdint.h>

#include "idk/core/color.h"
#include "idk/core/gamepad_state.h"
#include "idk/core/keys.h"
#include "idk/core/mouse_buttons.h"
#include "idk/core/vector2f.h"
#include "idk/graphics/camera.h"

typedef struct idk_window idk_window_t;

idk_window_t *idk_window_create(const uint32_t width, const uint32_t height, const char* title);
void idk_window_destroy(idk_window_t *window);

bool idk_window_is_open(idk_window_t *window);
void idk_window_close(idk_window_t *window);
void idk_window_poll_events(idk_window_t *window);
void idk_window_clear(idk_window_t *window);
void idk_window_display(idk_window_t *window);

void idk_window_set_cursor_visibility(
    idk_window_t *window, const bool visible);

void idk_window_set_camera(idk_window_t *window, const idk_camera_t *cam);

float idk_window_get_dt(idk_window_t *window);
idk_camera_t *idk_window_get_camera(idk_window_t *window);
idk_vec2_t idk_window_get_size(const idk_window_t *window);

idk_vec2_t idk_window_map_pixel_to_coords(
    idk_window_t *window, const idk_vec2_t point);
idk_vec2_t idk_window_map_coords_to_pixel(
    idk_window_t *window, const idk_vec2_t point);

void idk_window_set_title(idk_window_t *window, const char *title);
void idk_window_set_clear_color(idk_window_t *window, const idk_color_t color);
void idk_window_set_vsync(idk_window_t *window, const bool enable);

bool idk_window_is_key_down(idk_window_t *window, const idk_key_t key);
bool idk_window_is_key_up(idk_window_t *window, const idk_key_t key);
bool idk_window_was_key_pressed(idk_window_t *window, const idk_key_t key);
bool idk_window_was_key_released(idk_window_t *window, const idk_key_t key);

bool idk_window_is_mouse_down(idk_window_t *window, const idk_mouse_button_t btn);
bool idk_window_is_mouse_up(idk_window_t *window, const idk_mouse_button_t btn);
bool idk_window_was_mouse_pressed(
    idk_window_t *window, const idk_mouse_button_t btn);
bool idk_window_was_mouse_released(
    idk_window_t *window, const idk_mouse_button_t btn);


idk_vec2_t idk_window_get_mouse_pos(idk_window_t *window);
void idk_window_get_mouse_pos2(idk_window_t *window, float *x, float *y);

bool idk_window_is_gamepad_down(
    idk_window_t *window, const idk_gamepad_button_t btn);
bool idk_window_is_gamepad_up(
    idk_window_t *window, const idk_gamepad_button_t btn);
bool idk_window_was_gamepad_pressed(
    idk_window_t *window, const idk_gamepad_button_t btn);
bool idk_window_was_gamepad_released(
    idk_window_t *window, const idk_gamepad_button_t btn);

float idk_window_get_gamepad_axis(
    idk_window_t *window, const idk_gamepad_axis_t axis);

#endif

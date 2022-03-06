#ifndef IDK_GRAPHICS_CAMERA_H
#define IDK_GRAPHICS_CAMERA_H

#include <stdbool.h>

#include "idk/core/matrix4.h"
#include "idk/core/rectangle.h"
#include "idk/core/vector2f.h"

typedef struct idk_camera
{
    idk_mat4_t transformMatrix;
    idk_mat4_t inverseTransformMatrix;
    idk_rect_t viewport;
    idk_vec2_t center;
    idk_vec2_t size;
    float rotation;
    bool transformNeedsUpdate;
    bool inverseTransformNeedsUpdate;
} idk_camera_t;

idk_camera_t idk_camera_create(const idk_vec2_t center, const idk_vec2_t size);

void idk_camera_set_center(idk_camera_t *camera, const idk_vec2_t center);
void idk_camera_set_size(idk_camera_t *camera, const idk_vec2_t size);
void idk_camera_set_rotation(idk_camera_t *camera, const float rotation);
void idk_camera_reset(idk_camera_t *camera, const idk_rect_t rect);

void idk_camera_move(idk_camera_t *camera, const idk_vec2_t offset);
void idk_camera_rotate(idk_camera_t *camera, const float angle);
void idk_camera_zoom(idk_camera_t *camera, const float factor);

void idk_camera_get_transform_matrix(
    idk_camera_t *camera, idk_mat4_t *outMatrix);

void idk_camera_get_inverse_transform_matrix(
    idk_camera_t *camera, idk_mat4_t *outMatrix);

idk_vec2_t idk_camera_map_pixel_to_coords(
    idk_camera_t *camera, const idk_vec2_t point);
idk_vec2_t idk_camera_map_coords_to_pixel(
    idk_camera_t *camera, const idk_vec2_t point);

#endif

#include "idk/graphics/camera.h"
#include <math.h>

static void idk_camera_update_transform_matrix(idk_camera_t *camera);

idk_camera_t idk_camera_create(
    const idk_vec2_t center, const idk_vec2_t size,
    const idk_vec2_t windowSize)
{
    return (idk_camera_t){
        .center = center,
        .size = size,
        .windowSize = windowSize,
        .rotation = 0.0f,
        .viewport = {.left = 0.0f, .top = 0.0f, .width = 1.0f, .height = 1.0f},
        .transformNeedsUpdate = true,
        .inverseTransformNeedsUpdate = true};
}

void idk_camera_set_center(idk_camera_t *camera, const idk_vec2_t center)
{
    camera->center = center;
    camera->transformNeedsUpdate = true;
    camera->inverseTransformNeedsUpdate = true;
}

void idk_camera_set_size(idk_camera_t *camera, const idk_vec2_t size)
{
    camera->size = size;
    camera->transformNeedsUpdate = true;
    camera->inverseTransformNeedsUpdate = true;
}

void idk_camera_set_rotation(idk_camera_t *camera, const float rotation)
{
    camera->rotation = rotation;
    camera->transformNeedsUpdate = true;
    camera->inverseTransformNeedsUpdate = true;
}

void idk_camera_set_window_size(
    idk_camera_t *camera, const idk_vec2_t windowSize)
{
    camera->windowSize = windowSize;
}

void idk_camera_reset(idk_camera_t *camera, const idk_rect_t rect)
{
    camera->center.x = rect.left + rect.width / 2.f;
    camera->center.y = rect.top + rect.height / 2.f;
    camera->size.x = rect.width;
    camera->size.y = rect.height;
    camera->rotation = 0.0f;

    camera->transformNeedsUpdate = true;
    camera->inverseTransformNeedsUpdate = true;
}

void idk_camera_move(idk_camera_t *camera, const idk_vec2_t offset)
{
    idk_camera_set_center(camera, idk_vector2f_add(camera->center, offset));
}

void idk_camera_rotate(idk_camera_t *camera, const float angle)
{
    idk_camera_set_rotation(camera, camera->rotation + angle);
}

void idk_camera_zoom(idk_camera_t *camera, const float factor)
{
    idk_camera_set_size(camera, idk_vector2f_mulf(camera->size, factor));
}

void idk_camera_get_transform_matrix(idk_camera_t *camera, idk_mat4_t *outMatrix)
{
    idk_camera_update_transform_matrix(camera);
    idk_matrix4_copy_ref(&camera->transformMatrix, outMatrix);
}

void idk_camera_get_inverse_transform_matrix(
    idk_camera_t *camera, idk_mat4_t *outMatrix)
{
    if (camera->inverseTransformNeedsUpdate)
    {
        idk_camera_update_transform_matrix(camera);
        idk_matrix4_get_inverse_ref(&camera->transformMatrix, &camera->inverseTransformMatrix);
    }
    idk_matrix4_copy_ref(&camera->inverseTransformMatrix, outMatrix);
}

static void idk_camera_update_transform_matrix(idk_camera_t *camera)
{
    if (camera->transformNeedsUpdate)
    {
        const float cosine = cosf(camera->rotation);
        const float sine   = sinf(camera->rotation);
        const float tx = -camera->center.x * cosine - camera->center.y * sine +
                         camera->center.x;
        const float ty = camera->center.x * sine - camera->center.y * cosine +
                         camera->center.y;

        const float a =  2.f / camera->size.x;
        const float b = -2.f / camera->size.y;
        const float c = -a * camera->center.x;
        const float d = -b * camera->center.y;
        
        idk_matrix4_create2_ref(
            &camera->transformMatrix,
            a * cosine,   a * sine, a * tx + c,
             -b * sine, b * cosine, b * ty + d,
                   0.f,        0.f,        1.f
        );
        camera->transformNeedsUpdate = false;
    }
}

idk_vec2_t idk_camera_map_pixel_to_coords(
    idk_camera_t *camera, const idk_vec2_t point)
{
    const idk_rect_t vp = idk_rectangle_create(
        floorf(0.5f + camera->windowSize.x * camera->viewport.left), 
        floorf(0.5f + camera->windowSize.y * camera->viewport.top),
        floorf(0.5f + camera->windowSize.x * camera->viewport.width),
        floorf(0.5f + camera->windowSize.y * camera->viewport.height)
        );
    idk_vec2_t normalized = {
        .x = -1.f + 2.f * (point.x - vp.left) / vp.width,
        .y = 1.f - 2.f * (point.y - vp.top) / vp.height};

    idk_mat4_t inverseMatrix;
    idk_camera_get_inverse_transform_matrix(camera, &inverseMatrix);
    return idk_matrix4_transform_point(&inverseMatrix, normalized);
}

idk_vec2_t idk_camera_map_coords_to_pixel(
    idk_camera_t *camera, const idk_vec2_t point)
{
    idk_mat4_t matrix;
    idk_camera_get_transform_matrix(camera, &matrix);

    const idk_vec2_t normalized = idk_matrix4_transform_point(&matrix, point);

    const idk_rect_t vp = idk_rectangle_create(
        floorf(0.5f + camera->windowSize.x * camera->viewport.left),
        floorf(0.5f + camera->windowSize.y * camera->viewport.top),
        floorf(0.5f + camera->windowSize.x * camera->viewport.width),
        floorf(0.5f + camera->windowSize.y * camera->viewport.height));

    return (idk_vec2_t){
        .x = (normalized.x + 1.f) / 2.f * vp.width + vp.left,
        .y = (-normalized.y + 1.f) / 2.f * vp.height + vp.top};
}

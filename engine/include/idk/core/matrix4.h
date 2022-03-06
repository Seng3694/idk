#ifndef IDK_CORE_MATRIX4_H
#define IDK_CORE_MATRIX4_H

#include "idk/core/vector2f.h"

typedef struct idk_matrix4
{
    union {
        float data[16];

        struct
        {
            //column1
            float m00;
            float m01;
            float m02;
            float m03;

            // column2
            float m10;
            float m11;
            float m12;
            float m13;

            // column1
            float m20;
            float m21;
            float m22;
            float m23;

            // column1
            float m30;
            float m31;
            float m32;
            float m33;
        };
    };
} idk_matrix4_t;

typedef idk_matrix4_t idk_mat4_t;

idk_mat4_t idk_matrix4_zero(void);
idk_mat4_t idk_matrix4_identity(void);
idk_mat4_t idk_matrix4_create(
    const float m00, const float m01, const float m02, const float m03,
    const float m10, const float m11, const float m12, const float m13,
    const float m20, const float m21, const float m22, const float m23,
    const float m30, const float m31, const float m32, const float m33);
idk_mat4_t idk_matrix4_create2(
    const float m00, const float m01, const float m02,
    const float m10, const float m11, const float m12,
    const float m20, const float m21, const float m22
);

void idk_matrix4_zero_ref(idk_mat4_t *matrix);
void idk_matrix4_identity_ref(idk_mat4_t *matrix);
void idk_matrix4_create_ref(
    idk_mat4_t* matrix,
    const float m00, const float m01, const float m02, const float m03,
    const float m10, const float m11, const float m12, const float m13,
    const float m20, const float m21, const float m22, const float m23,
    const float m30, const float m31, const float m32, const float m33);
void idk_matrix4_create2_ref(
    idk_mat4_t* matrix,
    const float m00, const float m01, const float m02,
    const float m10, const float m11, const float m12,
    const float m20, const float m21, const float m22
);

void idk_matrix4_combine(
    const idk_mat4_t left, const idk_mat4_t right, idk_mat4_t *result);

void idk_matrix4_rotate(idk_mat4_t *matrix, const float radians);
void idk_matrix4_rotate_center(idk_mat4_t *matrix, const float radians, const float centerX, const float centerY);
void idk_matrix4_rotate_center2(idk_mat4_t *matrix, const float radians, const idk_vec2_t center);

void idk_matrix4_scale(idk_mat4_t *matrix, const float x, const float y);
void idk_matrix4_scale2(idk_mat4_t *matrix, const idk_vec2_t vec);

void idk_matrix4_translate(idk_mat4_t *matrix, const float x, const float y);
void idk_matrix4_translate2(idk_mat4_t *matrix, const idk_vec2_t vec);

idk_vec2_t idk_matrix4_transform_point(const idk_mat4_t *matrix, const idk_vec2_t point);
void idk_matrix4_transform_point_ref(const idk_mat4_t *matrix, float *x, float *y);
void idk_matrix4_transform_point2_ref(const idk_mat4_t *matrix, idk_vec2_t *point);

void idk_matrix4_orthographic(
    idk_mat4_t *matrix, const float left, const float right,
    const float bottom, const float top, const float nearZ, const float farZ);

#endif

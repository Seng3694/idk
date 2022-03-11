#include "idk/core/matrix4.h"

#include <memory.h>
#include <math.h>

idk_mat4_t idk_matrix4_zero(void)
{
    return (idk_mat4_t){
        .data = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        }
    };
}

idk_mat4_t idk_matrix4_identity(void)
{
     return (idk_mat4_t){
        .data = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }
    };
}

idk_mat4_t idk_matrix4_create(
    const float m00, const float m01, const float m02, const float m03,
    const float m10, const float m11, const float m12, const float m13,
    const float m20, const float m21, const float m22, const float m23,
    const float m30, const float m31, const float m32, const float m33)
{
    return (idk_mat4_t)
    {
        .data = {
            m00, m10, m20, m30,
            m01, m11, m21, m31,
            m02, m12, m22, m32,
            m03, m13, m23, m33
        }
    };
}

idk_mat4_t idk_matrix4_create2(
    const float m00, const float m01, const float m02,
    const float m10, const float m11, const float m12,
    const float m20, const float m21, const float m22
)
{
    return (idk_mat4_t)
    {
        .data = {
            m00, m10, 0.f, m20,
            m01, m11, 0.f, m21,
            0.f, 0.f, 1.f, 0.f,
            m02, m12, 0.f, m22
        }
    };
}

idk_mat4_t idk_matrix4_copy(const idk_mat4_t *matrix)
{
    idk_mat4_t out;
    idk_matrix4_copy_ref(matrix, &out);
    return out;
}

void idk_matrix4_copy_ref(const idk_mat4_t *matrix, idk_mat4_t *out)
{
    memcpy(out, matrix, sizeof(idk_mat4_t));
}

void idk_matrix4_zero_ref(idk_mat4_t *matrix)
{
    memset(matrix->data, 0, sizeof(float) * 16);
}

void idk_matrix4_identity_ref(idk_mat4_t *matrix)
{
    idk_matrix4_zero_ref(matrix);
    matrix->m00 = 1.0f;
    matrix->m11 = 1.0f;
    matrix->m22 = 1.0f;
    matrix->m33 = 1.0f;
}

void idk_matrix4_create_ref(
    idk_mat4_t* matrix,
    const float m00, const float m01, const float m02, const float m03,
    const float m10, const float m11, const float m12, const float m13,
    const float m20, const float m21, const float m22, const float m23,
    const float m30, const float m31, const float m32, const float m33)
{
    *matrix = idk_matrix4_create(
        m00, m01, m02, m03, 
        m10, m11, m12, m13, 
        m20, m21, m22, m23, 
        m30, m31, m32, m33);
}

void idk_matrix4_create2_ref(
    idk_mat4_t* matrix,
    const float m00, const float m01, const float m02,
    const float m10, const float m11, const float m12,
    const float m20, const float m21, const float m22)
{
    *matrix = idk_matrix4_create2(
        m00, m01, m02,
        m10, m11, m12,
        m20, m21, m22
    );
}

void idk_matrix4_combine(
    const idk_mat4_t left, const idk_mat4_t right, idk_mat4_t *result)
{
    const float *a = left.data;
    const float *b = right.data;

    idk_matrix4_create2_ref(result, 
        a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
        a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
        a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
        a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
        a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
        a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
        a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
        a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
        a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);
}

void idk_matrix4_rotate_x(idk_mat4_t *matrix, const float radians)
{
    const float cosine = cosf(radians);
    const float sine = sinf(radians);
    idk_mat4_t rotation = {
        .m00 = 1.0f,
        .m11 = cosine,
        .m12 = sine,
        .m21 = -sine,
        .m22 = cosine,
        .m33 = 1};
    idk_matrix4_combine(*matrix, rotation, matrix);
}

void idk_matrix4_rotate_y(idk_mat4_t *matrix, const float radians)
{
    const float cosine = cosf(radians);
    const float sine = sinf(radians);
    idk_mat4_t rotation = {
        .m00 = cosf(radians),
        .m02 = sinf(radians),
        .m11 = 1,
        .m20 = -rotation.m02,
        .m22 = rotation.m00,
        .m33 = 1};
    idk_matrix4_combine(*matrix, rotation, matrix);
}

void idk_matrix4_rotate_z(idk_mat4_t *matrix, const float radians)
{
    /*const float cosine = cosf(radians);
    const float sine = sinf(radians);
    const idk_mat4_t rotation = idk_matrix4_create2(
        cosine,  -sine, 0.0f,
          sine, cosine, 0.0f,
          0.0f,   0.0f, 1.0f);

    idk_matrix4_combine(*matrix, rotation, matrix);*/
    const float cosine = cosf(radians);
    const float sine = sinf(radians);
    idk_mat4_t rotation = { 
        .m00 = cosine,
        .m01 = sine,
        .m10 = -sine,
        .m11 = cosine,
        .m22 = 1,
        .m33 = 1
    };
    idk_matrix4_combine(*matrix, rotation, matrix);
}

void idk_matrix4_scale(idk_mat4_t *matrix, const float x, const float y)
{
    const idk_mat4_t scaling = idk_matrix4_create2(
           x, 0.0f, 0.0f,
        0.0f,    y, 0.0f,
        0.0f, 0.0f, 1.0f);

    idk_matrix4_combine(*matrix, scaling, matrix);
}

void idk_matrix4_scale2(idk_mat4_t *matrix, const idk_vec2_t vec)
{
    idk_matrix4_scale(matrix, vec.x, vec.y);
}

void idk_matrix4_translate(idk_mat4_t *matrix, const float x, const float y)
{
    const idk_mat4_t translation = idk_matrix4_create2(
        1.0f, 0.0f, x,
        0.0f, 1.0f, y,
        0.0f, 0.0f, 1.0f);

    idk_matrix4_combine(*matrix, translation, matrix);
}

void idk_matrix4_translate2(idk_mat4_t *matrix, const idk_vec2_t vec)
{
    idk_matrix4_translate(matrix, vec.x, vec.y);
}

idk_vec2_t idk_matrix4_transform_point(
    const idk_mat4_t *matrix, const idk_vec2_t point)
{
    return (idk_vec2_t){
        .x = matrix->data[0] * point.x + matrix->data[4] * point.y + matrix->data[12],
        .y = matrix->data[1] * point.x + matrix->data[5] * point.y + matrix->data[13]
    };
}

void idk_matrix4_transform_point_ref(const idk_mat4_t *matrix, float *x, float *y)
{
    const float xc = *x;
    const float yc = *y;
    *x = matrix->data[0] * xc + matrix->data[4] * yc + matrix->data[12];
    *y = matrix->data[1] * xc + matrix->data[5] * yc + matrix->data[13];
}

void idk_matrix4_transform_point2_ref(const idk_mat4_t *matrix, idk_vec2_t *point)
{
    idk_matrix4_transform_point_ref(matrix, &point->x, &point->y);
}

void idk_matrix4_orthographic(
    idk_mat4_t *matrix, const float left, const float right,
    const float bottom, const float top, const float nearZ,
    const float farZ)
{
    idk_matrix4_zero_ref(matrix);
    const float rightLeft = 1.0f / (right - left);
    const float topBottom = 1.0f / (top - bottom);
    const float farNear =  -1.0f / (farZ - nearZ);

    matrix->m00 = 2.0f * rightLeft;
    matrix->m11 = 2.0f * topBottom;
    matrix->m22 = 2.0f * farNear;

    matrix->m30 = -(right + left) * rightLeft;
    matrix->m31 = -(top + bottom) * topBottom;
    matrix->m32 = (farZ + nearZ) * farNear;
    matrix->m33 = 1.0f;
}

idk_mat4_t idk_matrix4_get_inverse(const idk_mat4_t *matrix)
{
    idk_mat4_t out;
    idk_matrix4_get_inverse_ref(matrix, &out);
    return out;
}

void idk_matrix4_get_inverse_ref(const idk_mat4_t *matrix, idk_mat4_t *out)
{
    const float *m = matrix->data;
    const float determinant = m[0] * (m[15] * m[5] - m[7] * m[13]) -
                              m[1] * (m[15] * m[4] - m[7] * m[12]) +
                              m[3] * (m[13] * m[4] - m[5] * m[12]);

    if (determinant != 0.0f)
    {
        idk_matrix4_create2_ref(out,
             (m[15] * m[5] - m[7] * m[13]) / determinant,
            -(m[15] * m[4] - m[7] * m[12]) / determinant,
             (m[13] * m[4] - m[5] * m[12]) / determinant,
            -(m[15] * m[1] - m[3] * m[13]) / determinant,
             (m[15] * m[0] - m[3] * m[12]) / determinant,
            -(m[13] * m[0] - m[1] * m[12]) / determinant,
             (m[7]  * m[1] - m[3] * m[5])  / determinant,
            -(m[7]  * m[0] - m[3] * m[4])  / determinant,
             (m[5]  * m[0] - m[1] * m[4])  / determinant);
    }
    else
    {
        idk_matrix4_identity_ref(out);
    }
}

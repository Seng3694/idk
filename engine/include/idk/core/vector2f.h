#ifndef IDK_CORE_VECTOR2F_H
#define IDK_CORE_VECTOR2F_H

#include <stdbool.h>

typedef struct idk_vector2f
{
    float x;
    float y;
} idk_vector2f_t;

typedef idk_vector2f_t idk_vec2_t;

inline idk_vec2_t idk_vector2f_add(const idk_vec2_t left, const idk_vec2_t right);
inline idk_vec2_t idk_vector2f_sub(const idk_vec2_t left, const idk_vec2_t right);
inline idk_vec2_t idk_vector2f_mul(const idk_vec2_t left, const idk_vec2_t right);
inline idk_vec2_t idk_vector2f_mulf(const idk_vec2_t left, const float right);
inline idk_vec2_t idk_vector2f_div(const idk_vec2_t left, const idk_vec2_t right);
inline idk_vec2_t idk_vector2f_divf(const idk_vec2_t left, const float right);
inline float idk_vector2f_dot(const idk_vec2_t left, const idk_vec2_t right);
inline float idk_vector2f_cross(const idk_vec2_t left, const idk_vec2_t right);
inline float idk_vector2f_mag(const idk_vec2_t vec);
inline idk_vec2_t idk_vector2f_normalize(const idk_vec2_t vec);
idk_vec2_t idk_vector2f_lerp(const idk_vec2_t from, const idk_vec2_t to, const float t);
inline bool idk_vector2f_equals(const idk_vec2_t left, const idk_vec2_t right);

inline void idk_vector2f_add_ref(const idk_vec2_t left, const idk_vec2_t right, idk_vec2_t *result);
inline void idk_vector2f_sub_ref(const idk_vec2_t left, const idk_vec2_t right, idk_vec2_t *result);
inline void idk_vector2f_mul_ref(const idk_vec2_t left, const idk_vec2_t right, idk_vec2_t *result);
inline void idk_vector2f_mulf_ref(const idk_vec2_t left, const float right, idk_vec2_t *result);
inline void idk_vector2f_div_ref(const idk_vec2_t left, const idk_vec2_t right, idk_vec2_t *result);
inline void idk_vector2f_divf_ref(const idk_vec2_t left, const float right, idk_vec2_t *result);
inline void idk_vector2f_dot_ref(const idk_vec2_t left, const idk_vec2_t right, float *result);
inline void idk_vector2f_cross_ref(const idk_vec2_t left, const idk_vec2_t right, float *result);
inline void idk_vector2f_mag_ref(const idk_vec2_t vec, float *result);
inline void idk_vector2f_normalize_ref(idk_vec2_t *vec);
void idk_vector2f_lerp_ref(const idk_vec2_t from, const idk_vec2_t to, const float t, idk_vec2_t* result);

inline void idk_vector2f_add_eq(idk_vec2_t *left, const idk_vec2_t right);
inline void idk_vector2f_sub_eq(idk_vec2_t *left, const idk_vec2_t right);
inline void idk_vector2f_mul_eq(idk_vec2_t *left, const idk_vec2_t right);
inline void idk_vector2f_mulf_eq(idk_vec2_t *left, const float right);
inline void idk_vector2f_div_eq(idk_vec2_t *left, const idk_vec2_t right);
inline void idk_vector2f_divf_eq(idk_vec2_t *left, const float right);

#include "vector2f.inl"

#endif

#ifndef IDK_CORE_VERTEX_H
#define IDK_CORE_VERTEX_H

#include "idk/core/common.h"

IDK_C_API_BEGIN

#include "idk/core/vector2f.h"

typedef struct idk_vertex
{
    idk_vec2_t pos;
    idk_vec2_t texPos;
} idk_vertex_t;

IDK_C_API_END

#endif

#include "idk/core/common.h"

#ifndef NDEBUG

void gl_error_check(const char *file, const uint32_t line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        printf("error: %s in %d 0x%04x\n", file, line, err);
    }
}

#endif

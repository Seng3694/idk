#ifndef IDK_CORE_COMMON_H
#define IDK_CORE_COMMON_H

#define GLSL(version, shader) "#version " version "\n" #shader

#define IDK_CLEAR_BIT(value, bit) ((value) & ~(1 << (bit)))
#define IDK_SET_BIT(value, bit) ((value) | (1 << (bit)))
#define IDK_TOGGLE_BIT(value, bit) ((value) ^ (1 << (bit)))
#define IDK_CHECK_BIT(value, bit) (((value) & (1 << (bit))) == (1 << (bit)))
#define IDK_COPY_BIT(dest, src, bit) dest = (dest & (~(1 << (bit)))) | ((src) & (1 << (bit)))

#ifndef NDEBUG
#include <stdio.h>
#include <stdarg.h>
#define LOG(fmt, ...) printf((fmt), __VA_ARGS__)

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void gl_error_check(const char *file, const uint32_t line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        printf("error: %s in %d 0x%04x\n", file, line, err);
    }
}

#define GL_CALL(func)                                                         \
    func;                                                                     \
    gl_error_check(__FILE__, __LINE__)


#else
#define LOG(fmt, ...)
#define GL_CALL(func)
#endif

#endif

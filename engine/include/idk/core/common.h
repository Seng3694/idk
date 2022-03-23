#ifndef IDK_CORE_COMMON_H
#define IDK_CORE_COMMON_H

#ifdef __cplusplus
#define IDK_C_API_BEGIN extern "C" {
#define IDK_C_API_END }
#else
#define IDK_C_API_BEGIN 
#define IDK_C_API_END
#endif

IDK_C_API_BEGIN

#define IDK_CLEAR_BIT(value, bit) ((value) & ~(1 << (bit)))
#define IDK_SET_BIT(value, bit) ((value) | (1 << (bit)))
#define IDK_TOGGLE_BIT(value, bit) ((value) ^ (1 << (bit)))
#define IDK_CHECK_BIT(value, bit) (((value) & (1 << (bit))) == (1 << (bit)))
#define IDK_COPY_BIT(dest, src, bit)                                          \
    dest = (dest & (~(1 << (bit)))) | ((src) & (1 << (bit)))

#ifndef NDEBUG
#include <stdio.h>
#include <stdarg.h>
#define LOG(fmt, ...) printf((fmt), __VA_ARGS__)

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void gl_error_check(const char *file, const uint32_t line);

#define GL_CALL(func)                                                         \
    func;                                                                     \
    gl_error_check(__FILE__, __LINE__)


#else
#define LOG(fmt, ...)
#define GL_CALL(func)
#endif

IDK_C_API_END

#endif

#ifndef IDK_CORE_FILE_SYSTEM_H
#define IDK_CORE_FILE_SYSTEM_H

#include "idk/core/common.h"

IDK_C_API_BEGIN

#include <stdbool.h>
#include <stddef.h>

typedef void (*idk_file_system_line_func)(char *line, void* userData);

bool idk_file_system_load_file_string(const char *path, char **output);
bool idk_file_system_load_file_binary(const char *path, void *output);
bool idk_file_system_load_file_line_by_line(
    const char *path, idk_file_system_line_func processor, void *userData);

bool idk_file_system_save_file_string(const char *path, const char *contents);
bool idk_file_system_save_file_binary(
    const char *path, const size_t contentSize, const void *contents);

IDK_C_API_END

#endif

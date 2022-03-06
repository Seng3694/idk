#include "idk/core/file_system.h"
#include "idk/core/common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool idk_file_system_load_file_string(const char *path, char **output)
{
    FILE *file;
    if (fopen_s(&file, path, "r") != 0)
    {
        LOG("Could not open file: \"%s\".\n", path);
        return false;
    }

    fseek(file, 0, SEEK_END);
    const size_t length = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);

    char *contents = calloc(length + 1, 1);
    if (!contents)
    {
        LOG("Could not allocate %zu B memory for file contents: \"%s\".\n",
            length, path);
        fclose(file);
        return false;
    }

    fread(contents, 1, length, file);
    fclose(file);

    *output = contents;
    return true;
}

bool idk_file_system_load_file_binary(const char *path, void *output)
{
    FILE *file;
    if (fopen_s(&file, path, "rb") != 0)
    {
        LOG("Could not open file: \"%s\".\n", path);
        return false;
    }

    fseek(file, 0, SEEK_END);
    const size_t length = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);

    fread(output, 1, length, file);
    fclose(file);

    return true;
}

bool idk_file_system_load_file_line_by_line(
    const char *path, idk_file_system_line_func processor, void *userData)
{
    FILE *file;
    if (fopen_s(&file, path, "r") != 0)
    {
        LOG("Could not open file: \"%s\".\n", path);
        return false;
    }

    char buffer[255];
    while (fgets(buffer, 255, file) != NULL)
    {
        const size_t length = strnlen_s(buffer, 255);
        if (buffer[length - 1] == '\n')
            buffer[length - 1] = '\0';
        processor(buffer, userData);
    }

    fclose(file);

    return true;
}

bool idk_file_system_save_file_string(const char *path, const char *contents)
{
    FILE *file;
    if (fopen_s(&file, path, "w") != 0)
    {
        LOG("Could not open file: \"%s\".\n", path);
        return false;
    }
    fputs(contents, file);
    fclose(file);

    return true;
}

bool idk_file_system_save_file_binary(
    const char *path, const size_t contentSize, const void *contents)
{
    FILE *file;
    if (fopen_s(&file, path, "wb") != 0)
    {
        LOG("Could not open file: \"%s\".\n", path);
        return false;
    }
    fwrite(contents, contentSize, 1, file);
    fclose(file);

    return true;
}

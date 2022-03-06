#ifndef CORE_FILE_SYSTEM_TESTS_H
#define CORE_FILE_SYSTEM_TESTS_H

#include "idk_test.h"

#include <idk/core/file_system.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct test_vec2
{
    float x;
    float y;
} test_vec2_t;

typedef struct test_object
{
    uint32_t id;
    test_vec2_t pos;
    char name[32];
} test_object_t;

static bool test_object_equals(
    const test_object_t left, const test_object_t right)
{
    return left.id == right.id && left.pos.x == right.pos.x &&
           left.pos.y == right.pos.y && strcmp(left.name, right.name) == 0;
}

IDK_TEST(CoreFileSystemLoadFileStringTest)
{
    const char *testFileName = "test_file.txt";
    const char *testString = "Hello World!";
    FILE *testFile;
    IDK_ASSERT(fopen_s(&testFile, testFileName, "w") == 0);
    fputs(testString, testFile);
    fclose(testFile);

    char *contents = NULL;
    IDK_ASSERT(idk_file_system_load_file_string(testFileName, &contents));

    IDK_ASSERT(strcmp(testString, contents) == 0);

    free(contents);
    remove(testFileName);

    return IDK_SUCCESS;
}

IDK_TEST(CoreFileSystemLoadFileBinaryTest)
{
    test_object_t testObjectExpected = {
        .id = 1337, .pos = {10.0f, 20.0f}, .name = "Player"};

    const char *testFileName = "test_file.txt";
    FILE *testFile;
    IDK_ASSERT(fopen_s(&testFile, testFileName, "wb") == 0);
    fwrite(&testObjectExpected, sizeof(test_object_t), 1, testFile);
    fclose(testFile);

    test_object_t testObjectActual;
    idk_file_system_load_file_binary(testFileName, &testObjectActual);

    IDK_ASSERT(test_object_equals(testObjectExpected, testObjectActual));

    remove(testFileName);

    return IDK_SUCCESS;
}

static void file_line_processor(char *line, void *userData)
{
    test_object_t *obj = (test_object_t *)userData;
    char *nextToken = NULL;
    char *token = strtok_s(line, "=", &nextToken);

    if (token != NULL)
    {
        if (strcmp(token, "id") == 0)
        {
            if ((token = strtok_s(NULL, "=", &nextToken)) != NULL)
            {
                obj->id = atoi(token);
            }
        }
        else if (strcmp(token, "name") == 0)
        {
            if ((token = strtok_s(NULL, "=", &nextToken)) != NULL)
            {
                strcpy_s(obj->name, 32, token);
            }
        }
        else if (strcmp(token, "x") == 0)
        {
            if ((token = strtok_s(NULL, "=", &nextToken)) != NULL)
            {
                obj->pos.x = (float)atof(token);
            }
        }
        else if (strcmp(token, "y") == 0)
        {
            if ((token = strtok_s(NULL, "=", &nextToken)) != NULL)
            {
                obj->pos.y = (float)atof(token);
            }
        }
    }
}

IDK_TEST(CoreFileSystemLoadFileLineByLineTest)
{
    const char *testFileName = "test_file.txt";
    const char *testString = "id=94\nname=Player 2\nx=32\ny=15";
    FILE *testFile;
    IDK_ASSERT(fopen_s(&testFile, testFileName, "w") == 0);
    fputs(testString, testFile);
    fclose(testFile);

    const test_object_t testObjectExpected = {
        .id = 94, .pos = {32.0f, 15.0f}, .name = "Player 2"};

    test_object_t testObjectActual;

    IDK_ASSERT(idk_file_system_load_file_line_by_line(
        testFileName, file_line_processor, &testObjectActual));

    IDK_ASSERT(test_object_equals(testObjectExpected, testObjectActual));

    remove(testFileName);

    return IDK_SUCCESS;
}

IDK_TEST(CoreFileSystemSaveFileStringTest)
{
    const char *testFileName = "test_file.txt";
    const char *expectedString = "Hello world!";
    char *actualString = NULL;
    IDK_ASSERT(idk_file_system_save_file_string(testFileName, expectedString));
    IDK_ASSERT(idk_file_system_load_file_string(testFileName, &actualString));

    IDK_ASSERT(strcmp(expectedString, actualString) == 0);

    free(actualString);
    remove(testFileName);
    return IDK_SUCCESS;
}

IDK_TEST(CoreFileSystemSaveFileBinaryTest)
{
    const char *testFileName = "test_file.txt";
    
    const test_object_t testObjectExpected = {
        .id = 34, .pos = {64.3f, 97.4f}, .name = "Player 3"};

    test_object_t testObjectActual;
    IDK_ASSERT(idk_file_system_save_file_binary(testFileName, sizeof(test_object_t), &testObjectExpected));
    IDK_ASSERT(idk_file_system_load_file_binary(testFileName, &testObjectActual));

    IDK_ASSERT(test_object_equals(testObjectExpected, testObjectActual));

    remove(testFileName);
    return IDK_SUCCESS;
}

#define CoreFileSystemTests                                                   \
    CoreFileSystemLoadFileStringTest, CoreFileSystemLoadFileBinaryTest,       \
        CoreFileSystemLoadFileLineByLineTest,                                 \
        CoreFileSystemSaveFileStringTest, CoreFileSystemSaveFileBinaryTest

#endif

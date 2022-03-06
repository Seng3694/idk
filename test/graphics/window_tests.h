#ifndef CORE_WINDOW_TESTS_H
#define CORE_WINDOW_TESTS_H

#include "idk_test.h"
#include <idk/graphics/window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

IDK_TEST(GraphicsWindowCreationTest)
{
    const uint32_t windowWidth = 800;
    const uint32_t windowHeight = 600;
    idk_window_t *window = idk_window_create(windowWidth, windowHeight, "Window Test");

    IDK_ASSERT(window != NULL);
    IDK_ASSERT(glGetError() == 0);
    IDK_ASSERT(glfwGetError(NULL) == GLFW_NO_ERROR);
    
    idk_window_close(window);
    idk_window_destroy(window);
    return IDK_SUCCESS;
}

IDK_TEST(GraphicsWindowOpenCloseTest)
{
    idk_window_t *window = idk_window_create(800, 600, "Window Test");

    IDK_ASSERT(window != NULL);
    IDK_ASSERT(glGetError() == 0);
    IDK_ASSERT(glfwGetError(NULL) == GLFW_NO_ERROR);

    IDK_ASSERT(idk_window_is_open(window) == true);
    idk_window_close(window);

    IDK_ASSERT(idk_window_is_open(window) == false);
    idk_window_destroy(window);

    return IDK_SUCCESS;
}

#define GraphicsWindowTests                                                   \
    GraphicsWindowCreationTest, GraphicsWindowOpenCloseTest

#endif

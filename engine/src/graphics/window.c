#include "idk/graphics/window.h"
#include "idk/core/common.h"

#include <memory.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef NDEBUG
static void idk_gl_error_callback(int error_code, const char *description);
#endif
static void idk_framebuffer_size_callback(
    GLFWwindow *window, int width, int height);
static void idk_key_callback(
    GLFWwindow *window, int key, int scancode, int action, int mods);
static void idk_mouse_pos_callback(
    GLFWwindow *window, double xpos, double ypos);
static void idk_mouse_button_callback(
    GLFWwindow *window, int button, int action, int mods);
static void idk_window_focus_callback(GLFWwindow *window, int focused);

typedef struct idk_window
{
    idk_camera_t camera;
    uint32_t previousKeys[16];
    uint32_t keys[16];
    GLFWgamepadstate previousGamepadState;
    GLFWgamepadstate gamepadState;
    idk_vec2_t mousePos;
    GLFWwindow *window;
    uint32_t width;
    uint32_t height;
    float deltaTime;
    float lastFrame;
    uint8_t previousMouseButtons;
    uint8_t mouseButtons;
    bool hasFocus;
} idk_window_t;

idk_window_t *idk_window_create(
    const uint32_t width, const uint32_t height, const char *title)
{
    idk_window_t *window = malloc(sizeof(idk_window_t));
    window->camera = idk_camera_create(
        (idk_vec2_t){width / 2.0f, height / 2.0f},
        (idk_vec2_t){width, height});
    window->width = width;
    window->height = height;
    window->deltaTime = 0.0f;
    window->lastFrame = 0.0f;
    memset(window->keys, 0, sizeof(uint32_t) * 16);
    memset(window->previousKeys, 0, sizeof(uint32_t) * 16);
    window->mouseButtons = 0;
    window->previousMouseButtons = 0;
    memset(&window->gamepadState, 0, sizeof(GLFWgamepadstate));
    memset(&window->previousGamepadState, 0, sizeof(GLFWgamepadstate));
    window->hasFocus = true;

    if (!glfwInit())
    {
        LOG("Couldn't initialize GLFW.\n");
        free(window);
        return NULL;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window->window =
        glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
    glfwMakeContextCurrent(window->window);
    glfwSwapInterval(0);

    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
    const int windowPosX = (mode->width / 2.0f) - (width / 2.0f);
    const int windowPosY = (mode->height / 2.0f) - (height / 2.0f);
    glfwSetWindowPos(window->window, windowPosX, windowPosY);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG("Couldn't initialize GLAD.\n");
        glfwDestroyWindow(window->window);
        glfwTerminate();
        free(window);
        return NULL;
    }

#ifndef NDEBUG
    glfwSetErrorCallback(idk_gl_error_callback);
#endif

    glfwSetWindowUserPointer(window->window, window);
    glfwSetFramebufferSizeCallback(
        window->window, idk_framebuffer_size_callback);
    glfwSetKeyCallback(window->window, idk_key_callback);
    glfwSetCursorPosCallback(window->window, idk_mouse_pos_callback);
    glfwSetMouseButtonCallback(window->window, idk_mouse_button_callback);
    glfwSetWindowFocusCallback(window->window, idk_window_focus_callback);

    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float clearColor[4];
    idk_color_packed_to_normalized(0x000b1eff, clearColor);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

    return window;
}

void idk_window_destroy(idk_window_t *window)
{
    glfwDestroyWindow(window->window);
    glfwTerminate();
    free(window);
}

bool idk_window_is_focused(idk_window_t *window)
{
    return window->hasFocus;
}

void idk_window_set_cursor_visibility(
    idk_window_t *window, const bool visible)
{
    glfwSetInputMode(window->window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

bool idk_window_is_open(idk_window_t *window)
{
    return !glfwWindowShouldClose(window->window);
}

void idk_window_close(idk_window_t *window)
{
    glfwSetWindowShouldClose(window->window, (int)true);
}

void idk_window_poll_events(idk_window_t *window)
{
    const float currentFrame = (float)glfwGetTime();
    window->deltaTime = currentFrame - window->lastFrame;
    window->lastFrame = currentFrame;

    memcpy(window->previousKeys, window->keys, sizeof(window->previousKeys));
    memcpy(
        &window->previousMouseButtons, &window->mouseButtons,
        sizeof(window->mouseButtons));

    memcpy(
        &window->previousGamepadState, &window->gamepadState,
        sizeof(GLFWgamepadstate));

    glfwPollEvents();

    glfwGetGamepadState(0, &window->gamepadState);
}

void idk_window_clear(idk_window_t *window)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void idk_window_display(idk_window_t *window)
{
    glfwSwapBuffers(window->window);
}

void idk_window_set_camera(idk_window_t *window, const idk_camera_t *cam)
{
    window->camera = *cam;
}

float idk_window_get_dt(idk_window_t *window)
{
    return window->deltaTime;
}

idk_camera_t *idk_window_get_camera(idk_window_t *window)
{
    return &window->camera;
}

idk_vec2_t idk_window_get_size(const idk_window_t *window)
{
    return (idk_vec2_t){window->width, window->height};
}

idk_vec2_t idk_window_map_pixel_to_coords(
    idk_window_t *window, const idk_vec2_t point)
{
    idk_camera_t *cam = &window->camera;
    const idk_rect_t vp = idk_rectangle_create(
        floorf(0.5f + window->width * cam->viewport.left),
        floorf(0.5f + window->height * cam->viewport.top),
        floorf(0.5f + window->width * cam->viewport.width),
        floorf(0.5f + window->height * cam->viewport.height));

    idk_vec2_t normalized = {
        .x = -1.f + 2.f * (point.x - vp.left) / vp.width,
        .y = 1.f - 2.f * (point.y - vp.top) / vp.height};

    idk_mat4_t inverseMatrix;
    idk_camera_get_inverse_transform_matrix(cam, &inverseMatrix);
    return idk_matrix4_transform_point(&inverseMatrix, normalized);
}

idk_vec2_t idk_window_map_coords_to_pixel(
    idk_window_t *window, const idk_vec2_t point)
{
    idk_camera_t *cam = &window->camera;
    idk_mat4_t matrix;
    idk_camera_get_transform_matrix(cam, &matrix);

    const idk_vec2_t normalized = idk_matrix4_transform_point(&matrix, point);

    const idk_rect_t vp = idk_rectangle_create(
        floorf(0.5f + window->width * cam->viewport.left),
        floorf(0.5f + window->height * cam->viewport.top),
        floorf(0.5f + window->width * cam->viewport.width),
        floorf(0.5f + window->height * cam->viewport.height));

    return (idk_vec2_t){
        .x = (normalized.x + 1.f) / 2.f * vp.width + vp.left,
        .y = (-normalized.y + 1.f) / 2.f * vp.height + vp.top};
}

void idk_window_set_clear_color(idk_window_t *window, const idk_color_t color)
{
    float clearColor[4];
    idk_color_to_normalized(color, clearColor);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

void idk_window_set_title(idk_window_t *window, const char *title)
{
    glfwSetWindowTitle(window->window, title);
}

void idk_window_set_vsync(idk_window_t *window, const bool enable)
{
    glfwSwapInterval((int)enable);
}

bool idk_window_is_key_down(idk_window_t *window, const idk_key_t key)
{
    return IDK_CHECK_BIT(window->keys[(key / 32)], (key % 32));
}

bool idk_window_is_key_up(idk_window_t *window, const idk_key_t key)
{
    return !idk_window_is_key_down(window, key);
}

bool idk_window_was_key_pressed(idk_window_t *window, const idk_key_t key)
{
    return !IDK_CHECK_BIT(window->previousKeys[(key / 32)], (key % 32)) &&
           IDK_CHECK_BIT(window->keys[(key / 32)], (key % 32));
}

bool idk_window_was_key_released(idk_window_t *window, const idk_key_t key)
{
    return IDK_CHECK_BIT(window->previousKeys[(key / 32)], (key % 32)) &&
           !IDK_CHECK_BIT(window->keys[(key / 32)], (key % 32));
}

bool idk_window_is_mouse_down(
    idk_window_t *window, const idk_mouse_button_t btn)
{
    return IDK_CHECK_BIT(window->mouseButtons, btn);
}

bool idk_window_is_mouse_up(idk_window_t *window, const idk_mouse_button_t btn)
{
    return !IDK_CHECK_BIT(window->mouseButtons, btn);
}

bool idk_window_was_mouse_pressed(
    idk_window_t *window, const idk_mouse_button_t btn)
{
    return !IDK_CHECK_BIT(window->previousMouseButtons, btn) &&
           IDK_CHECK_BIT(window->mouseButtons, btn);
}

bool idk_window_was_mouse_released(
    idk_window_t *window, const idk_mouse_button_t btn)
{
    return IDK_CHECK_BIT(window->previousMouseButtons, btn) &&
           !IDK_CHECK_BIT(window->mouseButtons, btn);
}

idk_vec2_t idk_window_get_mouse_pos(idk_window_t *window)
{
    return window->mousePos;
}

void idk_window_get_mouse_pos2(idk_window_t *window, float *x, float *y)
{
    *x = window->mousePos.x;
    *y = window->mousePos.y;
}

bool idk_window_is_gamepad_down(
    idk_window_t *window, const idk_gamepad_button_t btn)
{
    return window->gamepadState.buttons[btn] == 1;
}

bool idk_window_is_gamepad_up(
    idk_window_t *window, const idk_gamepad_button_t btn)
{
    return !idk_window_is_gamepad_down(window, btn);
}

bool idk_window_was_gamepad_pressed(
    idk_window_t *window, const idk_gamepad_button_t btn)
{
    return window->previousGamepadState.buttons[btn] == 0 &&
           window->gamepadState.buttons[btn] == 1;
}

bool idk_window_was_gamepad_released(
    idk_window_t *window, const idk_gamepad_button_t btn)
{
    return window->previousGamepadState.buttons[btn] == 1 &&
           window->gamepadState.buttons[btn] == 0;
}

float idk_window_get_gamepad_axis(
    idk_window_t *window, const idk_gamepad_axis_t axis)
{
    return window->gamepadState.axes[axis];
}

#ifndef NDEBUG
static void idk_gl_error_callback(int error_code, const char *description)
{
    LOG("ERROR[0x%8x]: %s\n", error_code, description);
}
#endif

static void idk_framebuffer_size_callback(
    GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    idk_window_t *w = (idk_window_t *)glfwGetWindowUserPointer(window);
    w->width = (uint32_t)width;
    w->height = (uint32_t)height;
}

static void idk_key_callback(
    GLFWwindow *window, int key, int scancode, int action, int mods)
{
    idk_window_t *idkWindow = (idk_window_t *)glfwGetWindowUserPointer(window);

    if (key >= 0 && key < 512)
    {
        const uint32_t arrayIndex = (key / 32);
        const uint32_t bitIndex = (key % 32);

        if (action == GLFW_PRESS)
        {
            idkWindow->keys[arrayIndex] =
                IDK_SET_BIT(idkWindow->keys[arrayIndex], bitIndex);
        }
        else if (action == GLFW_RELEASE)
        {
            idkWindow->keys[arrayIndex] =
                IDK_CLEAR_BIT(idkWindow->keys[arrayIndex], bitIndex);
        }
    }
}

static void idk_mouse_pos_callback(
    GLFWwindow *window, double xpos, double ypos)
{
    idk_window_t *idkWindow = (idk_window_t *)glfwGetWindowUserPointer(window);
    idkWindow->mousePos.x = (float)xpos;
    idkWindow->mousePos.y = (float)ypos;
}

static void idk_mouse_button_callback(
    GLFWwindow *window, int button, int action, int mods)
{
    idk_window_t *idkWindow = (idk_window_t *)glfwGetWindowUserPointer(window);

    if (action == GLFW_PRESS)
    {
        idkWindow->mouseButtons = IDK_SET_BIT(idkWindow->mouseButtons, button);
    }
    else if (action == GLFW_RELEASE)
    {
        idkWindow->mouseButtons =
            IDK_CLEAR_BIT(idkWindow->mouseButtons, button);
    }
}

static void idk_window_focus_callback(GLFWwindow *window, int focused)
{
    idk_window_t *idkWindow = (idk_window_t *)glfwGetWindowUserPointer(window);
    idkWindow->hasFocus = focused;
}

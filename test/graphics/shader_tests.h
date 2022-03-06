#ifndef CORE_SHADER_TESTS_H
#define CORE_SHADER_TESTS_H

#include "idk_test.h"

#include <idk/graphics/shader.h>
#include <idk/graphics/window.h>

static const char *testVertSource =
    "#version 330 core\n"
    "layout (location=0) in vec2 position;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * vec4(position.xy, 0.0, 1.0);\n"
    "}\n";

static const char *testFragSource = "#version 330 core\n"
                                    "out vec4 color;\n"
                                    "uniform vec4 primitiveColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "  color = primitiveColor;\n"
                                    "}\n";

static const char *testGeomSource =
    "#version 330 core\n"
    "layout(points) in;\n"
    "layout(line_strip, max_vertices = 2) out;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);\n"
    "  EmitVertex();\n"
    "  gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);\n"
    "  EmitVertex();\n"
    "  EndPrimitive();\n"
    "}\n";

IDK_TEST(GraphicsShaderCreateTest)
{
    // create window for gl context
    idk_window_t *window = idk_window_create(800, 600, "shader test");
    idk_shader_t shader =
        idk_shader_create(testVertSource, testFragSource, testGeomSource);

    IDK_ASSERT(shader != IDK_SHADER_INVALID);

    idk_shader_destroy(shader);
    idk_window_destroy(window);

    return IDK_SUCCESS;
}

IDK_TEST(GraphicsShaderCreateVFTest)
{
    // create window for gl context
    idk_window_t *window = idk_window_create(800, 600, "shader test");

    idk_shader_t shader = idk_shader_create_vf(testVertSource, testFragSource);

    IDK_ASSERT(shader != IDK_SHADER_INVALID);

    idk_shader_destroy(shader);
    idk_window_destroy(window);

    return IDK_SUCCESS;
}

#define GraphicsShaderTests                                                   \
    GraphicsShaderCreateTest, GraphicsShaderCreateVFTest

#endif

#include "idk/graphics/shader.h"
#include "idk/core/common.h"

#include <stdbool.h>
#include <glad/glad.h>

static bool idk_shader_check_compile_errors(const uint32_t shaderID);
static bool idk_shader_check_link_errors(const uint32_t shaderID);
static bool idk_shader_compile_shader(
    const uint32_t type, const char *source, uint32_t *outID);

idk_shader_t idk_shader_create(
    const char *vertexSource, const char *fragmentSource,
    const char *geometrySource)
{
    if (vertexSource == NULL || fragmentSource == NULL || geometrySource == NULL)
        return IDK_SHADER_INVALID;

    uint32_t vertexID = 0;
    if (!idk_shader_compile_shader(GL_VERTEX_SHADER, vertexSource, &vertexID))
    {
        glDeleteShader(vertexID);
        return IDK_SHADER_INVALID;
    }

    uint32_t fragmentID = 0;
    if (!idk_shader_compile_shader(
            GL_FRAGMENT_SHADER, fragmentSource, &fragmentID))
    {
        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);
        return IDK_SHADER_INVALID;
    }

    uint32_t geometryID = 0;
    if (!idk_shader_compile_shader(
            GL_GEOMETRY_SHADER, geometrySource, &geometryID))
    {
        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);
        glDeleteShader(geometryID);
        return IDK_SHADER_INVALID;
    }

    idk_shader_t shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexID);
    glAttachShader(shaderID, fragmentID);
    glAttachShader(shaderID, geometryID);
    glLinkProgram(shaderID);
    
    const bool success = idk_shader_check_link_errors(shaderID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    glDeleteShader(geometryID);

    return success ? shaderID : IDK_SHADER_INVALID;
}

idk_shader_t idk_shader_create_vf(
    const char *vertexSource, const char *fragmentSource)
{
    if (vertexSource == NULL || fragmentSource == NULL)
        return IDK_SHADER_INVALID;

    uint32_t vertexID = 0;
    if (!idk_shader_compile_shader(GL_VERTEX_SHADER, vertexSource, &vertexID))
    {
        glDeleteShader(vertexID);
        return IDK_SHADER_INVALID;
    }

    uint32_t fragmentID = 0;
    if (!idk_shader_compile_shader(
            GL_FRAGMENT_SHADER, fragmentSource, &fragmentID))
    {
        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);
        return IDK_SHADER_INVALID;
    }

    idk_shader_t shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexID);
    glAttachShader(shaderID, fragmentID);
    glLinkProgram(shaderID);

    const bool success = idk_shader_check_link_errors(shaderID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    return success ? shaderID : IDK_SHADER_INVALID;
}

void idk_shader_destroy(idk_shader_t shader)
{
    glDeleteProgram(shader);
}

void idk_shader_use(idk_shader_t shader)
{
    glUseProgram(shader);
}

void idk_shader_set_float(
    const idk_shader_t shader, const char *name, const float value)
{
    glUniform1f(glGetUniformLocation(shader, name), value);
}

void idk_shader_set_integer(
    const idk_shader_t shader, const char *name, const int32_t value)
{
    glUniform1i(glGetUniformLocation(shader, name), value);
}

void idk_shader_set_float2(
    const idk_shader_t shader, const char *name, const float x, const float y)
{
    glUniform2f(glGetUniformLocation(shader, name), x, y);
}

void idk_shader_set_vec2f(
    const idk_shader_t shader, const char *name, const idk_vector2f_t vec)
{
    idk_shader_set_float2(shader, name, vec.x, vec.y);
}

void idk_shader_set_float3(
    const idk_shader_t shader, const char *name, const float x, const float y,
    const float z)
{
    glUniform3f(glGetUniformLocation(shader, name), x, y, z);
}

void idk_shader_set_float4(
    const idk_shader_t shader, const char *name, const float x, const float y,
    const float z, const float w)
{
    glUniform4f(glGetUniformLocation(shader, name), x, y, z, w);
}

void idk_shader_set_color(
    const idk_shader_t shader, const char *name, const idk_color_t color)
{
    float normalized[4];
    idk_color_to_normalized(color, normalized);
    idk_shader_set_float4(
        shader, name, normalized[0], normalized[1], normalized[2],
        normalized[3]);
}

void idk_shader_set_matrix4(
    const idk_shader_t shader, const char *name, const idk_matrix4_t *matrix)
{
    glUniformMatrix4fv(
        glGetUniformLocation(shader, name), 1, GL_FALSE, matrix->data);
}

static bool idk_shader_check_compile_errors(const uint32_t shaderID)
{
    int success = 0;
    char buffer[1024];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success); 
    if (success != GL_TRUE)
    {
        glGetShaderInfoLog(shaderID, 1024, NULL, buffer);
        LOG("Error compiling shader: %s\n", buffer);
    }
    return success;
}

static bool idk_shader_check_link_errors(const uint32_t shaderID)
{
    int success = 0;
    char buffer[1024];
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        glGetShaderInfoLog(shaderID, 1024, NULL, buffer);
        LOG("Error linking shader: %s\n", buffer);
    }
    return success;
}

static bool idk_shader_compile_shader(
    const uint32_t type, const char *source, uint32_t *outID)
{
    uint32_t id;
    id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    if (!idk_shader_check_compile_errors(id))
        return false;
    *outID = id;
    return true;
}

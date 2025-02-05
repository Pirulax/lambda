#pragma once

#include <Base.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "GLObjID.h"

namespace lambda {
/*!
* @brief Collection of a fragment, vertex and optionally a geometry shader. Represents a `glCreateProgram`
*/
class ShaderProgram {
public:
    ShaderProgram(FragmentShader fragment, VertexShader vertex, std::optional<GeometryShader> geometry = std::nullopt);

    /*!
    * @brief Uniform value setters
    * @param name Name of the uniform
    * @param v    Value to set
    */
    void Set(const GLchar* name, GLint v)     { glUniform1i(GetUniform(name), v); }
    void Set(const GLchar* name, bool v)      { Set(name, (GLint)v); }
    void Set(const GLchar* name, GLuint v)    { Set(name, (GLint)v); }
    void Set(const GLchar* name, Real v)      { glUniform1f(GetUniform(name), v); }
    void Set(const GLchar* name, glm::vec2 v) { glUniform2f(GetUniform(name), v.x, v.y); }
    void Set(const GLchar* name, glm::vec3 v) { glUniform3f(GetUniform(name), v.x, v.y, v.z); }
    void Set(const GLchar* name, glm::vec4 v) { glUniform4f(GetUniform(name), v.x, v.y, v.z, v.w); }

    void Use() const { glUseProgram(m_ID); }

private:
    GLint GetUniform(const GLchar* name) const {
        const auto loc = glGetUniformLocation(m_ID, name);
        if (loc == -1) {
            throw std::runtime_error{ "Uniform doesn't exist! "};
        }
        return loc;
    }

private:
    GLObjID m_ID{}; // GL ID (From `glCreateProgram`)
};
};
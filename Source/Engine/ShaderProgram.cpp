#include "ShaderProgram.h"

namespace lambda {
ShaderProgram::ShaderProgram(FragmentShader fragment, VertexShader vertex, std::optional<GeometryShader> geometry) :
    m_ID{ glCreateProgram() }
{
    assert(m_ID);
    
    // Attach shaders, and link the code
    glAttachShader(m_ID, fragment.GetID());
    glAttachShader(m_ID, vertex.GetID());
    if (geometry.has_value()) {
        glAttachShader(m_ID, geometry->GetID());
    }
    glLinkProgram(m_ID);

    // Check for errors
    GLint success;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar log[1024];
        glGetProgramInfoLog(m_ID, std::size(log), NULL, log);
        throw std::runtime_error{ log };
    }
}
};
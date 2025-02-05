#include "Shader.h"

#include <fstream>

namespace lambda {
Shader::Shader(GLenum type, const fs::path& codePath) :
    m_Type{ type }
{
    std::ifstream ifs{codePath};
    ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream ss;
    ss << ifs.rdbuf();

    LoadCode(ss.str().c_str());
}

Shader::Shader(GLenum type, std::string_view code) :
    m_Type{ type }
{
    LoadCode(code);
}

Shader::~Shader() {
    glDeleteShader(m_ID);
}

void Shader::LoadCode(std::string_view code) {
    m_ID = glCreateShader(m_Type);
    assert(m_ID);
    
    // Load shader source into GL, and compile it
    const GLint   len = (GLint)code.length();
    const GLchar* str = code.data();
    glShaderSource(m_ID, 1, &str, &len);
    glCompileShader(m_ID);

    // Check for errors
    GLint success;
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar log[1024];
        glGetShaderInfoLog(m_ID, std::size(log), NULL, log);
        throw std::runtime_error{ log };
    }
}
};
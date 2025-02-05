#pragma once

#include <Base.h>

#include <filesystem>
namespace fs = std::filesystem;

#include <glad/glad.h>

#include "GLObjID.h"

namespace lambda {
/*!
 * @brief Represents a shader (`glCreateShader`)
*/
class Shader {
public:
    /*!
     * @brief Construct a shader given a path at which the source code is. Load code using the `Load*` functions.
     * @param type Shader's type
     * @param codePath Path to the file for the source code
    */
    Shader(GLenum type, const fs::path& codePath);

    /*!
    * @brief Construct a shader given a path at which the source code is. Load code using the `Load*` functions.
    * @param type Shader's type
    * @param code Source code of the shader
    */
    Shader(GLenum type, std::string_view code);

public:
    Shader(const Shader&) = delete; // No copy allowed
    Shader(Shader&&) = default;

    ~Shader();

    GLuint GetID() const { return m_ID; }

protected:
    void LoadCode(std::string_view code);

private:
    GLObjID m_ID{}; // GL ID (From `glCreateShader`)
    GLenum  m_Type{};
};
namespace detail::shader {
template<typename Klass, GLenum Type>
struct Constructors {
    static Klass FromFile(const fs::path& codePath) { return Klass{ Type, codePath }; };
    static Klass FromString(std::string_view code)  { return Klass{ Type, code };     };
};
};
struct FragmentShader : Shader, detail::shader::Constructors<FragmentShader, GL_FRAGMENT_SHADER> { using Shader::Shader; };
struct VertexShader : Shader, detail::shader::Constructors<VertexShader, GL_VERTEX_SHADER> { using Shader::Shader; };
struct GeometryShader : Shader, detail::shader::Constructors<GeometryShader, GL_GEOMETRY_SHADER> { using Shader::Shader; };
};
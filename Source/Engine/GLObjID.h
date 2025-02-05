#pragma once

#include <utility>
#include <glad/glad.h>

namespace lambda {
/*!
 * @brief Wrapper for GL object ID's. Does nothing more than setting the "moved from" ID to 0 (In the move ctor)
*/
struct GLObjID {
    GLObjID(GLuint id = GL_NONE) noexcept : ID{id} { }
    GLObjID(const GLObjID&) noexcept = default;
    GLObjID(GLObjID&& other) noexcept : ID(GL_NONE) { swap(*this, other); }

    GLObjID& operator=(GLObjID o) noexcept { swap(*this, o); return *this; }

    friend void swap(GLObjID& a, GLObjID& b) noexcept { std::swap(a.ID, b.ID); }

    operator GLuint() const noexcept { return ID; }
    GLuint* operator&() noexcept    { return &ID; }
private:
    GLuint ID;
};
};
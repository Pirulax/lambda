#pragma once

#include <memory>

#include "Engine/Model.h"

namespace lambda {
class ShaderProgram;
struct ModelComponent {
    ModelComponent(std::shared_ptr<Model> mesh)  :
        m_Model{ std::move(mesh) }
    {   
    }

    void Draw(ShaderProgram* shdr) {
        m_Model->Draw(shdr);
    }

private:
    std::shared_ptr<Model> m_Model{};
};
};
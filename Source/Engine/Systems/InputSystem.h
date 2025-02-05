#pragma once

#include <entt/fwd.hpp>

namespace lambda {
class InputSystem final {
public:
    InputSystem();
    ~InputSystem();

    void Update(entt::registry& registry);
};
};

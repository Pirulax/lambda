#pragma once

#include <assert.h>
#include <cstdint>
#include <string_view>

#include <ranges>
namespace rng = std::ranges;

#include <filesystem>
namespace fs = std::filesystem;

#include <Windows.h>

using u8 = std::uint8_t;
using i8 = std::uint8_t;

using u16 = std::uint16_t;
using i16 = std::uint16_t;

using u32 = std::uint32_t;
using i32 = std::uint32_t;

using u64 = std::uint64_t;
using i64 = std::uint64_t;

using Real = float;


namespace lambda::detail {
static const fs::path SOURCE_PATH = fs::path(__FILE__).parent_path();

template<typename... Ts>
[[noreturn]] static void unreachable(std::string_view method, std::string_view file, unsigned line, std::string_view fmt = "", Ts&&... fmtArgs) {
    const auto userDetails = std::vformat(fmt, std::make_format_args(std::forward<Ts>(fmtArgs)...));
    const auto mbMsg = std::format("File: {}\nIn: {}:{}\n\nDetails:\n{}", fs::relative(file, SOURCE_PATH).string(), method, line, userDetails.empty() ? "<None provided>" : userDetails.c_str());

    const auto result = MessageBox(
        NULL,
        mbMsg.c_str(),
        "Unreachable code reached! SEND HALP IMMEDIATELY!",
        MB_TASKMODAL | MB_ICONHAND | MB_ABORTRETRYIGNORE | MB_SETFOREGROUND
    );

    if (result == IDRETRY) {
        __debugbreak();
    }

    exit(3);
}
};
#define LAMBDA_UNREACHABLE(...) do { lambda::detail::unreachable(__FUNCTION__, __FILE__, __LINE__ __VA_OPT__(,) ##__VA_ARGS__); } while (false)


#define VERIFY(expr) do { if (!(expr)) { __debugbreak(); } }
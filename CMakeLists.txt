cmake_minimum_required(VERSION 3.15)

project(
    lambda 
    VERSION 1.0
    LANGUAGES CXX
)

find_package(EnTT)
find_package(Edyn)
find_package(VulkanHeaders)

add_executable(lambda src/main.cpp)

target_link_libraries(lambda Edyn::Edyn)
target_link_libraries(lambda EnTT::EnTT)
target_link_libraries(lambda vulkan-headers::vulkan-headers)

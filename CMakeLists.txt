cmake_minimum_required(VERSION 3.15)

project(
    lambda 
    VERSION 1.0
    LANGUAGES CXX
)

find_package(EnTT REQUIRED)
find_package(Edyn REQUIRED)
#find_package(SDL2 REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(OPENGL REQUIRED)
find_package(assimp REQUIRED)
find_package(stb REQUIRED)
#find_package(VulkanHeaders REQUIRED)

# Add the source files to your project
add_executable(lambda Source/App/main.cpp)

target_compile_definitions(lambda PRIVATE NOMINMAX)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(lambda PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/MP;/Zc:preprocessor;/wd26812;/wd26495>")
endif()

# Create a variable to hold the list of source and header files
file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "Source/*.h")
# Associate the source files with the target using target_sources
target_sources(lambda PRIVATE ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(lambda PRIVATE Source/)

# Set a symbolic link so exe can find the "Data" folder
set(link_src "${CMAKE_SOURCE_DIR}/Data")
if(APPLE) 
    set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Data") 
else() 
    set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/Data")
endif() 
add_custom_command( 
    TARGET lambda
    POST_BUILD COMMAND ${CMAKE_COMMAND} 
        -E create_symlink ${link_src} ${link_dst} 
    DEPENDS ${link_dst} 
    COMMENT "symbolic link ${link_src} => ${link_dst}" 
)

target_link_libraries(lambda PRIVATE Edyn::Edyn)
target_link_libraries(lambda PRIVATE EnTT::EnTT)
#target_link_libraries(lambda PRIVATE SDL2::SDL2)
target_link_libraries(lambda PRIVATE glfw)
target_link_libraries(lambda PRIVATE glm::glm)
target_link_libraries(lambda PRIVATE glu::glu)
target_link_libraries(lambda PRIVATE glad::glad)
target_link_libraries(lambda PRIVATE opengl::opengl)
target_link_libraries(lambda PRIVATE GLEW::GLEW)
target_link_libraries(lambda PRIVATE assimp::assimp)
target_link_libraries(lambda PRIVATE stb::stb)
#target_link_libraries(lambda PRIVATE vulkan-headers::vulkan-headers)

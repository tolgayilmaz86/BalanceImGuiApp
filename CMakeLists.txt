cmake_minimum_required(VERSION 3.22)

project(
    "BalanceApp"
    VERSION 1.0.0
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

file(COPY ${PROJECT_SOURCE_DIR}/fonts/Roboto-Medium.ttf DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/fonts/fa-solid-900.ttf DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/sounds/start.wav DESTINATION ${CMAKE_BINARY_DIR})

option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)
option(ENABLE_CLANG_TIDY "Enable to add clang tidy." ON)
option(ENABLE_CLANG_FORMAT "Enable to add clang-format." ON)

include(Warnings)
#  include(Tools) # needs clang tidy and clang format
include(ConfigSafeGuards)

# add_clang_format_target() # needs python

set (VCPKG_DIR ${CMAKE_SOURCE_DIR}/external/vcpkg)
include(${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(SFML COMPONENTS audio REQUIRED)
find_package(SFML COMPONENTS graphics REQUIRED)
find_package(SFML COMPONENTS network REQUIRED)
find_package(Boost COMPONENTS thread REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} WIN32
 "src/main.cpp"
 "src/view/WindowSystem/IWindow.hpp"
 "src/view/WindowSystem/OpenGLWindow.cpp"
 "src/view/WindowSystem/OpenGLWindow.h"
 "src/view/Menu/AbstractMenu.hpp"
 "src/view/Menu/MainMenu.h"
 "src/view/Menu/MenuBuilder.hpp"
 "src/view/Menu/MainMenu.cpp"
 "src/view/Menu/SideMenu.hpp"
 "src/view/Menu/SideMenu.cpp"
 "src/view/Overlay/OverlayRenderEngine.hpp"
 "src/view/Overlay/IOverlayRenderer.hpp"
 "src/view/Overlay/TimerOverlay.hpp"
 "src/view/WindowSystem/OpenGLWin32Window.h"
 "src/view/WindowSystem/OpenGLWin32Window.cpp")

add_compile_definitions(NOMINMAX)

target_set_warnings(TARGET ${PROJECT_NAME}
    ENABLE ${ENABLE_WARNINGS}
    AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS})
    
target_include_directories(${PROJECT_NAME} PUBLIC src/)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE implot::implot)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-network)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::thread)

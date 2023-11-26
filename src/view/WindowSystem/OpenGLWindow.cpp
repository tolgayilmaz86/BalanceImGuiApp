#include "OpenGLWindow.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <cstdio>

namespace WS = View::WindowSystem;

void WS::OpenGL::glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

WS::OpenGL::OpenGLWindow::OpenGLWindow()
{
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Controls whether the window has a border and title bar. 
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    // A floating window is a window that stays above other regular windows
    // and is not constrained by the normal window stacking order.
    glfwWindowHint(GLFW_FLOATING, FALSE);

    // A transparent framebuffer allows you to have windows with transparent or
    // semi-transparent regions, useful for creating visually interesting effects or
    // overlaying windows with partial transparency.
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only

    window = glfwCreateWindow(WS::WINDOW_WIDTH,
                              WS::WINDOW_HEIGHT,
                              "Tomoto",
                              nullptr,
                              nullptr);

    glfwMakeContextCurrent(window);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(WS::OpenGL::gl_version);
}

void WS::OpenGL::OpenGLWindow::startFrame()
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
}

void WS::OpenGL::OpenGLWindow::endFrame()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

void WS::OpenGL::OpenGLWindow::renderWindow()
{
}

void WS::OpenGL::OpenGLWindow::createWindow()
{
}

inline bool WS::OpenGL::OpenGLWindow::isOpen()
{
    return !glfwWindowShouldClose(window);
}

WS::OpenGL::OpenGLWindow::~OpenGLWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

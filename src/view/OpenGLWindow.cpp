#include "OpenGLWindow.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void View::OpenGL::glfw_error_callback(int error, const char *description)
{
    //fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void View::OpenGL::startFrame()
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
}

void View::OpenGL::endFrame(GLFWwindow *const window)
{
    const auto clear_color =
        ImVec4(30.0F / 255.0F, 30.0F / 255.0F, 30.0F / 255.0F, 1.00f);
    //glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(clear_color.x * clear_color.w,
                 clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

View::OpenGL::OpenGLWindow::OpenGLWindow()
{
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only

    window = glfwCreateWindow(View::WINDOW_WIDTH,
                              View::WINDOW_HEIGHT,
                              "View::OpenGLMainWindow",
                              nullptr,
                              nullptr);

    glfwMakeContextCurrent(window);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(View::OpenGL::gl_version);
}

bool View::OpenGL::OpenGLWindow::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        startFrame();

        DrawMainMenu();

        endFrame(window);
    }

    return true;
}

View::OpenGL::OpenGLWindow::~OpenGLWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

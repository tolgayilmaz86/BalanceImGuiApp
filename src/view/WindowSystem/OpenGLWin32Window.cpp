#include "OpenGLWin32Window.h"

#include <imgui_impl_win32.h>
#include <imgui_impl_opengl3.h>
#include <cstdio>

namespace WS = View::WindowSystem;

static bool done = false;
HWND hwnd = 0;

// Data stored per platform window
struct WGL_WindowData
{
    HDC hDC;
};

// Data
static HGLRC g_hRC;
static WGL_WindowData g_MainWindow;
static int g_Width;
static int g_Height;

// Forward declarations of helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData *data);
void CleanupDeviceWGL(HWND hWnd, WGL_WindowData *data);
void ResetDeviceWGL();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Support function for multi-viewports
// Unlike most other backend combination, we need specific hooks to combine Win32+OpenGL.
// We could in theory decide to support Win32-specific code in OpenGL backend via e.g. an hypothetical ImGui_ImplOpenGL3_InitForRawWin32().
static void Hook_Renderer_CreateWindow(ImGuiViewport *viewport)
{
    assert(viewport->RendererUserData == NULL);

    WGL_WindowData *data = IM_NEW(WGL_WindowData);
    CreateDeviceWGL((HWND)viewport->PlatformHandle, data);
    viewport->RendererUserData = data;
}

static void Hook_Renderer_DestroyWindow(ImGuiViewport *viewport)
{
    if (viewport->RendererUserData != NULL)
    {
        WGL_WindowData *data = (WGL_WindowData *)viewport->RendererUserData;
        CleanupDeviceWGL((HWND)viewport->PlatformHandle, data);
        IM_DELETE(data);
        viewport->RendererUserData = NULL;
    }
}

static void Hook_Platform_RenderWindow(ImGuiViewport *viewport, void *)
{
    // Activate the platform window DC in the OpenGL rendering context
    if (WGL_WindowData *data = (WGL_WindowData *)viewport->RendererUserData)
        wglMakeCurrent(data->hDC, g_hRC);
}

static void Hook_Renderer_SwapBuffers(ImGuiViewport *viewport, void *)
{
    if (WGL_WindowData *data = (WGL_WindowData *)viewport->RendererUserData)
        ::SwapBuffers(data->hDC);
}

WS::OpenGL::OpenGLWin32Window::OpenGLWin32Window()
{
    // Create application window
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = {sizeof(wc),
                      CS_OWNDC,
                      WndProc,
                      0L,
                      0L,
                      GetModuleHandle(NULL),
                      NULL,
                      NULL,
                      NULL,
                      NULL,
                      L"Tomoto",
                      NULL};
    ::RegisterClassExW(&wc);

    hwnd = ::CreateWindowExW(WS_EX_LAYERED | WS_EX_TRANSPARENT,
                            wc.lpszClassName,
                            L"Tomoto",
                            WS_OVERLAPPEDWINDOW,
                            0,
                            0,
                            GetSystemMetrics(SM_CXSCREEN),
                            GetSystemMetrics(SM_CYSCREEN),
                            NULL,
                            NULL,
                            wc.hInstance,
                            NULL);

    SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);

    // Initialize OpenGL
    if (!CreateDeviceWGL(hwnd, &g_MainWindow))
    {
        CleanupDeviceWGL(hwnd, &g_MainWindow);
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        // TODO handle error
    }

    wglMakeCurrent(g_MainWindow.hDC, g_hRC);

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_InitForOpenGL(hwnd);
    ImGui_ImplOpenGL3_Init();

    // Win32+GL needs specific hooks for viewport, as there are specific things needed to tie Win32 and GL api.
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGuiPlatformIO &platform_io = ImGui::GetPlatformIO();
        IM_ASSERT(platform_io.Renderer_CreateWindow == NULL);
        IM_ASSERT(platform_io.Renderer_DestroyWindow == NULL);
        IM_ASSERT(platform_io.Renderer_SwapBuffers == NULL);
        IM_ASSERT(platform_io.Platform_RenderWindow == NULL);
        platform_io.Renderer_CreateWindow = Hook_Renderer_CreateWindow;
        platform_io.Renderer_DestroyWindow = Hook_Renderer_DestroyWindow;
        platform_io.Renderer_SwapBuffers = Hook_Renderer_SwapBuffers;
        platform_io.Platform_RenderWindow = Hook_Platform_RenderWindow;
    }
}

WS::OpenGL::OpenGLWin32Window::~OpenGLWin32Window()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
}

void WS::OpenGL::OpenGLWin32Window::startFrame()
{
  // Poll and handle messages (inputs, window resize, etc.)
  // See the WndProc() function below for our to dispatch events to the Win32 backend.
  MSG msg;
  while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
  {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
            done = true;
  }

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void WS::OpenGL::OpenGLWin32Window::endFrame()
{
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Update and Render additional Platform Windows
  if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        // Restore the OpenGL rendering context to the main window DC, since platform windows might have changed it.
        wglMakeCurrent(g_MainWindow.hDC, g_hRC);
  }

  // Present
  ::SwapBuffers(g_MainWindow.hDC);
}

ImVec2 WS::OpenGL::OpenGLWin32Window::GetWindowSize()
{
  int width{WS::MENU_WINDOW_WIDTH}, height{WS::MENU_WINDOW_HEIGHT};
  //RECT rect;
  //if (GetWindowRect(hwnd, &rect))
  //{
  //  width = rect.right - rect.left;  // Width of the window
  //  height = rect.bottom - rect.top; // Height of the window
  //}
  return ImVec2(static_cast<float>(width), static_cast<float>(height));
}

ImVec2 WS::OpenGL::OpenGLWin32Window::GetWindowPos()
{
  RECT rect;
  ::GetWindowRect(hwnd, &rect);
  return ImVec2(static_cast<float>(rect.left), static_cast<float>(rect.top));
}

void WS::OpenGL::OpenGLWin32Window::SetWindowPos(ImVec2 pos)
{
  ::SetWindowPos(hwnd,
               HWND_TOP,
               static_cast<int>(pos.x),
               static_cast<int>(pos.y),
               0,
               0,
               SWP_NOSIZE | SWP_NOZORDER);
}

inline bool WS::OpenGL::OpenGLWin32Window::isOpen()
{
  return !done;
}

// Helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData *data)
{
  HDC hDc = ::GetDC(hWnd);
  PIXELFORMATDESCRIPTOR pfd = {0};
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;

  const int pf = ::ChoosePixelFormat(hDc, &pfd);
  if (pf == 0)
    return false;
  if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
    return false;
  ::ReleaseDC(hWnd, hDc);

  data->hDC = ::GetDC(hWnd);
  if (!g_hRC)
    g_hRC = wglCreateContext(data->hDC);
  return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData *data)
{
  wglMakeCurrent(NULL, NULL);
  ::ReleaseDC(hWnd, data->hDC);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    return true;

  switch (msg)
  {
  case WM_SIZE:
    if (wParam != SIZE_MINIMIZED)
    {
        g_Width = LOWORD(lParam);
        g_Height = HIWORD(lParam);
    }
    return 0;
  case WM_SYSCOMMAND:
    if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
        return 0;
    break;
  case WM_DESTROY:
    ::PostQuitMessage(0);
    return 0;
  }
  return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

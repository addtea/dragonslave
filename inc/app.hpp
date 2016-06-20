#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "asset_manager.hpp"
#include "error.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include "window.hpp"

namespace dragonslave {


struct AppConfig
{
    std::string title = "Window";
    int width = 800;
    int height = 600;

    bool shown = true;
    bool borderless = false;
    bool fullscreen = false;
    bool resizable = false;

    bool double_buffered = true;
};


class AppInitError : public FatalError
{ 
public:
    AppInitError(const std::string& message)
      : FatalError("AppInitError", message)
    { }
};


class App
{
public:
    AssetManager asset;
    Graphics graphics;
    Input input;
    Window window;

    App();
    virtual ~App();
     
    void initiate(const AppConfig& config);
    void terminate();

    void poll();

private:
    static void handle_char_(GLFWwindow* window, unsigned int code_point);
    static void handle_key_(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void handle_cursor_pos_(GLFWwindow* window, double x, double y);
    static void handle_mouse_button_(GLFWwindow* window, int button, int action, int mods);
    static void handle_scroll_(GLFWwindow* window, double dx, double dy);
    static void handle_framebuffer_size_(GLFWwindow* window, int width, int height);

    GLFWwindow* glfw_window_ = nullptr;
};


}

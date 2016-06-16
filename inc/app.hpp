#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "error.hpp"
#include "window.hpp"
#include "input.hpp"
#include "graphics.hpp"


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
    App();
    virtual ~App();
     
    void init(const AppConfig& config);
    void term();

    void poll_events();

    inline Window& get_window() { return window_; }
    inline Input& get_input() { return input_; }
    inline Graphics& get_graphics() { return graphics_; }

private:
    static void handle_char(GLFWwindow* window, unsigned int code_point);
    static void handle_key(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void handle_cursor_pos(GLFWwindow* window, double x, double y);
    static void handle_mouse_button(GLFWwindow* window, int button, int action, int mods);
    static void handle_scroll(GLFWwindow* window, double dx, double dy);
    static void handle_framebuffer_size(GLFWwindow* window, int width, int height);

    GLFWwindow* glfw_window_ = nullptr;

    Window window_;
    Input input_;
    Graphics graphics_;
};


}

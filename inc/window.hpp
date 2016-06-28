#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "channel.hpp"

namespace dragonslave {


struct GLFormat 
{
    int major_version = 3;
    int minor_version = 3;
    bool has_forward_compat = false;
};


struct WindowConfig
{
    std::string title = "Window";
    int width = 800;
    int height = 600;
};


class WindowInputBehavior
{
public:
    virtual ~WindowInputBehavior() { }

    virtual void on_key(int key, int scancode, int action, int mods) = 0;
    virtual void on_mouse_button(int button, int action, int mods) = 0;
    virtual void on_mouse_motion(double x, double y) = 0;
    virtual void on_mouse_scroll(double scroll_x, double scroll_y) = 0;
};


struct WindowResizeMessage
{
    int width;
    int height;
};


class WindowResizeHandler
{
public:
    virtual ~WindowResizeHandler() { }

    virtual void on_resize(int width, int height) = 0;

    void handle(const WindowResizeMessage& message) 
    {
        on_resize(message.width, message.height);
    }
};


class Window
{
public:
    Window();
    virtual ~Window();

    void initialize(
        WindowInputBehavior* input_behavior,
        const GLFormat& gl_format,
        const WindowConfig& config);
    void terminate();

    int get_width() const { return width_; }
    int get_height() const { return height_; }
    bool should_close() const;

    void add_resize_handler(WindowResizeHandler* handler);
    void remove_resize_handler(WindowResizeHandler* handler);
    void make_current();
    void swap_buffers();

private:
    static void handle_key_(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void handle_cursor_pos_(GLFWwindow* window, double x, double y);
    static void handle_mouse_button_(GLFWwindow* window, int button, int action, int mods);
    static void handle_scroll_(GLFWwindow* window, double dx, double dy);
    static void handle_framebuffer_size_(GLFWwindow* window, int width, int height);

    GLFWwindow* glfw_window_ = nullptr;
    WindowInputBehavior* input_behavior_ = nullptr;
    int width_ = 0;
    int height_ = 0;
    Channel<WindowResizeHandler, WindowResizeMessage> resize_channel_;

    void on_resize_(int width, int height);
};

    
}

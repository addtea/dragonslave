#include "error.hpp"
#include "window.hpp"

namespace dragonslave {


Window::Window() { }


Window::~Window() { }


void Window::initialize(
        WindowInputBehavior* input_behavior,
        const GLFormat& gl_format,
        const WindowConfig& config)
{
    input_behavior_ = input_behavior;
    glfwWindowHint(
        GLFW_OPENGL_PROFILE, 
        gl_format.has_forward_compat ? 
        GLFW_OPENGL_COMPAT_PROFILE : 
        GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, gl_format.has_forward_compat);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_format.major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_format.minor_version);

    width_ = config.width;
    height_ = config.height;
    glfw_window_ = glfwCreateWindow(width_, height_, config.title.c_str(), nullptr, nullptr);

    if (!glfw_window_) {
        throw FatalError("WindowInitError", "Failed to create window");
    }

    glfwSetWindowUserPointer(glfw_window_, this);

    glfwSetKeyCallback(glfw_window_, Window::handle_key_);
    glfwSetCursorPosCallback(glfw_window_, Window::handle_cursor_pos_);
    glfwSetMouseButtonCallback(glfw_window_, Window::handle_mouse_button_);
    glfwSetScrollCallback(glfw_window_, Window::handle_scroll_);
    glfwSetFramebufferSizeCallback(glfw_window_, Window::handle_framebuffer_size_);
}


void Window::terminate() 
{
    if (glfw_window_)
        glfwDestroyWindow(glfw_window_);
}


bool Window::should_close() const
{
    return glfwWindowShouldClose(glfw_window_);
}


void Window::make_current()
{
   glfwMakeContextCurrent(glfw_window_); 
}


void Window::swap_buffers()
{
    glfwSwapBuffers(glfw_window_);
}


void Window::add_resize_handler(WindowResizeHandler* handler)
{
    resize_channel_.add(handler);
}


void Window::remove_resize_handler(WindowResizeHandler* handler)
{
    resize_channel_.remove(handler);
}


void Window::handle_key_(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    if (window->input_behavior_) 
        window->input_behavior_->on_key(key, scancode, action, mods);
}


void Window::handle_cursor_pos_(GLFWwindow* glfw_window, double x, double y)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    if (window->input_behavior_) 
        window->input_behavior_->on_mouse_motion(x, y);
}


void Window::handle_mouse_button_(GLFWwindow* glfw_window, int button, int action, int mods)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    if (window->input_behavior_) 
        window->input_behavior_->on_mouse_button(button, action, mods);
}


void Window::handle_scroll_(GLFWwindow* glfw_window, double dx, double dy)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    if (window->input_behavior_) 
        window->input_behavior_->on_mouse_scroll(dx, dy);
}


void Window::handle_framebuffer_size_(GLFWwindow* glfw_window, int width, int height)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    window->on_resize_(width, height);
}


void Window::on_resize_(int width, int height)
{
    width_ = width;
    height_ = height;
    WindowResizeMessage message {width_, height_};
    resize_channel_.broadcast(message);
}


}

#include "window.hpp"

namespace dragonslave {


Window::Window() { }


Window::~Window() { }


void Window::init(GLFWwindow* glfw_window)
{
    glfw_window_ = glfw_window;
}


void Window::term()
{
    glfw_window_ = nullptr;
}


void Window::on_resize(int width, int height)
{
    width_ = width;
    height_ = height;

    WindowResizeEvent resize_event (width, height);
    resize_target_.emit_event(resize_event);
}

    
}

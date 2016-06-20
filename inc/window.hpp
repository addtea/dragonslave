#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "event_target.hpp"

namespace dragonslave {


struct WindowResizeEvent
{
    int width = 0;
    int height = 0;

    WindowResizeEvent(int width, int height)
      : width (width)
      , height (height)
    { }
};


class Window
{
public:
    Window();
    virtual ~Window();

    void initiate(GLFWwindow* glfw_window);
    void terminate();

    int get_width() const { return width_; }
    int get_height() const { return height_; }

    EventTarget<WindowResizeEvent>& get_resize_target()
    { return resize_target_; }

    void on_resize(int width, int height);

private:
    GLFWwindow* glfw_window_ = nullptr;
    int width_ = 0;
    int height_ = 0;
    EventTarget<WindowResizeEvent> resize_target_;
};


}

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "input_queue.hpp"

namespace dragonslave {


class Input
{
public:
    Input();
    virtual ~Input();

    void initiate(GLFWwindow* glfw_window);
    void terminate();

    InputQueue& get_queue() { return queue_; }

    void on_char(unsigned int codepoint);
    void on_key(int key, int scancode, int action, int mods);
    void on_cursor_pos(double x, double y);
    void on_mouse_button(int button, int action, int mods);
    void on_scroll(double dx, double dy);

private:
    GLFWwindow* glfw_window_ = nullptr;
    InputQueue queue_;
};


}

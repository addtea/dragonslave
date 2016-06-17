#include "input.hpp"

namespace dragonslave {


Input::Input() { }


Input::~Input() { }


void Input::init(GLFWwindow* glfw_window)
{
    glfw_window_ = glfw_window;
    queue_.reset();
}

void Input::term()
{
    glfw_window_ = nullptr;
}

void Input::on_char(unsigned int codepoint) { }


void Input::on_key(int key, int scancode, int action, int mods)
{
    queue_.on_keyboard(key, scancode, action, mods);
}


void Input::on_cursor_pos(double x, double y)
{
    queue_.on_mouse_motion(x, y);
}


void Input::on_mouse_button(int button, int action, int mods)
{
    queue_.on_mouse_button(button, action, mods);
}


void Input::on_scroll(double dx, double dy)
{
    queue_.on_mouse_scroll(dx, dy);
}


}

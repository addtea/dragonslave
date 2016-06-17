#include "input_queue.hpp"

namespace dragonslave {

void InputQueue::register_kbd(int key, int scancode, int action, int mods)
{
    this->input_queue.push(
            InputEvent(InputType::KEYBOARD, KeyboardEvent(key, scancode), action, mods));
}

void InputQueue::register_mouse_button(int button, int action, int mods)
{
    this->input_queue.push(
            InputEvent(InputType::MOUSE_BUTTON, MouseEvent(button), action, mods));
}

void InputQueue::register_mouse_pos(double x = 0, double y = 0)
{
    this->input_queue.push(InputEvent(InputType::MOUSE_POS, MouseEvent(x, y)));
}

void InputQueue::register_mouse_scroll(double x = 0, double y = 0)
{
    this->input_queue.push(InputEvent(InputType::MOUSE_SCROLL, MouseEvent(x, y)));
}


}


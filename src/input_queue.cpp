#include "input_queue.hpp"

namespace dragonslave {

void InputQueue::register_kbd(int key, int scancode, int action, int mods)
{
    InputEvent input_event(InputType::KEYBOARD, action, mods);
    input_event.kbd = InputKeyboardEvent(key, scancode);
    input_queue_.push(input_event);
}

void InputQueue::register_mouse_button(int button, int action, int mods)
{
    InputEvent input_event(InputType::MOUSE_BUTTON, action, mods);
    input_event.mouse_button = InputMouseButtonEvent(button);
    input_queue_.push(input_event);
}

void InputQueue::register_mouse_pos(double x = 0, double y = 0)
{
    InputEvent input_event(InputType::MOUSE_POSITION);
    input_event.mouse_position = InputMousePositionEvent(x, y);
    input_queue_.push(input_event);
}

void InputQueue::register_mouse_scroll(double x = 0, double y = 0)
{
    InputEvent input_event(InputType::MOUSE_SCROLL);
    input_event.mouse_scroll = InputMouseScrollEvent(x, y);
    input_queue_.push(input_event);
}

}


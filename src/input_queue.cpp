#include "input_queue.hpp"

namespace dragonslave {


void InputQueue::reset()
{
    while (!input_queue_.empty()) input_queue_.pop();
    seen_mouse_motion_ = false;
    mouse_x_ = -1.0f;
    mouse_y_ = -1.0f;
}


void InputQueue::on_keyboard(int key, int scancode, int action, int mods)
{
    InputEvent input_event(InputType::KEYBOARD);
    input_event.keyboard = InputKeyboardEvent(key, scancode, action, mods);
    input_queue_.push(input_event);
}


void InputQueue::on_mouse_button(int button, int action, int mods)
{
    InputEvent input_event(InputType::MOUSE_BUTTON);
    input_event.mouse_button = InputMouseButtonEvent(
            button, action, mods, mouse_x_, mouse_y_);
    input_queue_.push(input_event);
}


void InputQueue::on_mouse_motion(double x, double y)
{
    double dx = 0.0f;
    double dy = 0.0f;
    if (seen_mouse_motion_) {
        dx = x - mouse_x_;
        dy = y - mouse_y_;
    }
    seen_mouse_motion_ = true;

    InputEvent input_event(InputType::MOUSE_POSITION);
    input_event.mouse_motion = InputMouseMotionEvent(x, y, dx, dy);
    input_queue_.push(input_event);
}


void InputQueue::on_mouse_scroll(double dx, double dy)
{
    InputEvent input_event(InputType::MOUSE_SCROLL);
    input_event.mouse_scroll = InputMouseScrollEvent(dx, dy);
    input_queue_.push(input_event);
}


}


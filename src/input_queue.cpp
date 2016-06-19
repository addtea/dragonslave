#include "input_queue.hpp"

namespace dragonslave {


InputQueue::InputQueue() { }


InputQueue::~InputQueue() { }


bool InputQueue::has_events() const
{
    return !input_queue_.empty();
}


const InputEvent* InputQueue::next_event() const
{
    return input_queue_.front().get();
}


void InputQueue::pop_event()
{
    return input_queue_.pop();
}


void InputQueue::reset()
{
    while (!input_queue_.empty()) input_queue_.pop();
    seen_mouse_motion_ = false;
    mouse_x_ = -1.0f;
    mouse_y_ = -1.0f;
}


void InputQueue::on_keyboard(int key, int scancode, int action, int mods)
{
    input_queue_.push(std::make_unique<KeyboardInputEvent>(
        key, scancode, action, mods));
}


void InputQueue::on_mouse_button(int button, int action, int mods)
{
    input_queue_.push(std::make_unique<MouseButtonInputEvent>(
        mouse_x_, mouse_y_, button, action, mods));
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
    input_queue_.push(std::make_unique<MouseMotionInputEvent>(
        mouse_x_, mouse_y_, dx, dy));
}


void InputQueue::on_mouse_scroll(double scroll_x, double scroll_y)
{
    input_queue_.push(std::make_unique<MouseScrollInputEvent>(
        mouse_x_, mouse_y_, scroll_x, scroll_y));
}


}


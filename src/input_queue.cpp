#include "input_queue.hpp"

namespace dragonslave {

    
InputQueue::InputQueue() { }


InputQueue::~InputQueue() { }


void InputQueue::on_key(int key, int scancode, int action, int mods)
{
    std::lock_guard<std::mutex> lock (queue_mutex_);
    queue_.push_back(std::make_unique<KeyboardInputEvent>(
                key, scancode, action, mods));
}


void InputQueue::on_mouse_button(int button, int action, int mods)
{
    std::lock_guard<std::mutex> lock (queue_mutex_);
    queue_.push_back(std::make_unique<MouseButtonInputEvent>(
                cursor_x_, cursor_y_, button, action, mods));
}


void InputQueue::on_mouse_motion(double x, double y)
{
    double dx = 0.; 
    double dy = 0.;
    if (seen_cursor_) {
        dx = x - cursor_x_;
        dy = y - cursor_y_;
    } else {
        seen_cursor_ = true;
    }
    cursor_x_ = x;
    cursor_y_ = y;
    std::lock_guard<std::mutex> lock (queue_mutex_);
    queue_.push_back(std::make_unique<MouseMotionInputEvent>(
                cursor_x_, cursor_y_, dx, dy));
}


void InputQueue::on_mouse_scroll(double scroll_x, double scroll_y)
{
    std::lock_guard<std::mutex> lock (queue_mutex_);
    queue_.push_back(std::make_unique<MouseScrollInputEvent>(
                cursor_x_, cursor_y_, scroll_x, scroll_y));
}


void InputQueue::add_handler(InputEventHandler* handler)
{
    event_channel_.add(handler);
}


void InputQueue::remove_handler(InputEventHandler* handler)
{
    event_channel_.remove(handler);
}


void InputQueue::flush_events()
{
    std::vector<std::unique_ptr<InputEvent> > local_queue;
    {
        std::lock_guard<std::mutex> lock (queue_mutex_);
         local_queue = std::move(queue_);
         queue_.clear();
    }
    for (auto& event_ptr : local_queue) {
        event_channel_.broadcast(*event_ptr);
    }
}


}

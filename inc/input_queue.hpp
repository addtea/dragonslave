#pragma once

#include <memory>
#include <queue>

#include "input_event.hpp"

namespace dragonslave {


class InputQueue
{
public:
    InputQueue();
    virtual ~InputQueue();

    bool has_events() const;
    const InputEvent* next_event() const;
    void pop_event();

    void reset();

    void on_keyboard(int key, int scancode, int action, int mods);
    void on_mouse_button(int button, int action, int mods);
    void on_mouse_motion(double x, double y);
    void on_mouse_scroll(double scroll_x, double scroll_y);

private:
    std::queue<std::unique_ptr<InputEvent> > input_queue_;

    bool seen_mouse_motion_ = false;
    double mouse_x_ = -1.0;
    double mouse_y_ = -1.0;
};


}

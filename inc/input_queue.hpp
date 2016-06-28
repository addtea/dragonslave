#pragma once

#include <memory>
#include <mutex>
#include <vector>
#include "window.hpp"
#include "input_events.hpp"
#include "channel.hpp"

namespace dragonslave {


class InputQueue : public WindowInputBehavior
{
public:
    InputQueue();
    virtual ~InputQueue();

    void add_handler(InputEventHandler* handler);
    void remove_handler(InputEventHandler* handler);
    void flush_events();

    void on_key(int key, int scancode, int action, int mods) override;
    void on_mouse_button(int button, int action, int mods)  override;
    void on_mouse_motion(double x, double y) override;
    void on_mouse_scroll(double scroll_x, double scroll_y) override;

private:
    bool seen_cursor_ = false;
    double cursor_x_ = 0.;
    double cursor_y_ = 0.;
    Channel<InputEventHandler, InputEvent> event_channel_;
    std::vector<std::unique_ptr<InputEvent> > queue_;
    std::mutex queue_mutex_;
};


}

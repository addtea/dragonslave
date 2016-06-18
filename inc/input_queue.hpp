#pragma once
#include <queue>

namespace dragonslave {


enum class InputType {
    KEYBOARD,
    MOUSE_POSITION,
    MOUSE_BUTTON,
    MOUSE_SCROLL,
};


struct InputMouseButtonEvent
{
    int button = 0;
    int action = 0;
    int mods = 0;
    double x = 0;
    double y = 0;

    InputMouseButtonEvent(int button, int action, int mods, double x, double y)
      : button (button)
      , action (action)
      , mods (mods)
      , x (x)
      , y (y)
    { }
};


struct InputMouseMotionEvent
{
    double x = 0.0; 
    double y = 0.0; 
    double dx = 0.0; 
    double dy = 0.0;

    InputMouseMotionEvent(double x, double y, double dx, double dy)
      : x (x)
      , y (y)
      , dx (dx)
      , dy (dy)
    { }
};


struct InputMouseScrollEvent
{
    double dx = 0.0; 
    double dy = 0.0;

    InputMouseScrollEvent(double dx, double dy)
      : dx (dx)
      , dy (dy)
    { }
};


struct InputKeyboardEvent
{
    int key = 0; 
    int scancode = 0;
    int action = 0;
    int mods = 0;

    InputKeyboardEvent(int key, int scancode, int action, int mods)
      : key (key)
      , scancode (scancode)
      , action (action)
      , mods (mods)
    { }
};


struct InputEvent
{
    InputType type;
    union
    {
        InputMouseButtonEvent mouse_button;
        InputMouseMotionEvent mouse_motion;
        InputMouseScrollEvent mouse_scroll;
        InputKeyboardEvent keyboard;
    };

    InputEvent(InputType type)
      : type (type)
    { }
};


class InputQueue
{
public:
    bool has_next_event() const { return !input_queue_.empty(); }

    InputEvent pop_next_event() 
    { 
        InputEvent next = input_queue_.front();
        input_queue_.pop();
        return next;
    }

    void reset();

    void on_keyboard(int key, int scancode, int action, int mods);
    void on_mouse_button(int button, int action, int mods);
    void on_mouse_motion(double x, double y);
    void on_mouse_scroll(double dx, double dy);

private:
    std::queue<InputEvent> input_queue_;
    bool seen_mouse_motion_ = false;
    double mouse_x_ = -1.0;
    double mouse_y_ = -1.0;
};


}

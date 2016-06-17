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
    InputMouseButtonEvent(int button)
        : button(button)
    { }
};


struct InputMousePositionEvent
{
    double x = 0.0, y = 0.0;
    InputMousePositionEvent(double x, double y)
        : x(x)
        , y(y)
    { }
};


struct InputMouseScrollEvent
{
    double x = 0.0, y = 0.0;
    InputMouseScrollEvent(double x, double y)
        : x(x)
        , y(y)
    { }
};


struct InputKeyboardEvent
{
    int key = 0, scancode = 0;

    InputKeyboardEvent(int key, int scancode)
        : key(key)
        , scancode(scancode)
    { }
};


struct InputEvent
{
    InputType type;
    union
    {
        InputMouseButtonEvent mouse_button;
        InputMousePositionEvent mouse_position;
        InputMouseScrollEvent mouse_scroll;
        InputKeyboardEvent kbd;
    };
    int action;
    int mods;

    InputEvent(InputType type, int action = 0, int mods = 0)
        : type(type)
        , action(action)
        , mods(mods)
    { }
};


class InputQueue
{
public:
    InputEvent get_next_event() { InputEvent next = input_queue_.front(); input_queue_.pop(); return next; }
    void register_kbd(int key, int scancode, int action, int mods);
    void register_mouse_button(int button, int action, int mods);
    void register_mouse_pos(double x, double y);
    void register_mouse_scroll(double x, double y);

private:
    std::queue<InputEvent> input_queue_;
};

}

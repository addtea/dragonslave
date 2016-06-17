#pragma once
#include <queue>

namespace dragonslave {

enum class InputType {
    KEYBOARD,
    MOUSE_POS,
    MOUSE_BUTTON,
    MOUSE_SCROLL,
};

struct MouseEvent
{
    double x = 0, y = 0;
    int button = 0;

    MouseEvent(double x, double y) :
        x(x), y(y)
    { }

    MouseEvent(int button) :
        button(button)
    { }
};

struct KeyboardEvent
{
    int key, scancode;

    KeyboardEvent(int key, int scancode)
        : key(key), scancode(scancode)
    { }
};

struct InputEvent
{
    InputType type;
    union
    {
        MouseEvent mouse;
        KeyboardEvent kbd;
    };
    int action;
    int mods;

    InputEvent(InputType type, MouseEvent mouse, int action = 0, int mods = 0)
        : type(type), mouse(mouse), action(action), mods(mods)
    { }

    InputEvent(InputType type, KeyboardEvent kbd, int action = 0, int mods = 0)
        : type(type), kbd(kbd), action(action), mods(mods)
    { }

};

class InputQueue
{
public:
    InputEvent get_next_event() { InputEvent next = input_queue.front(); input_queue.pop(); return next; }
    void register_kbd(int key, int scancode, int action, int mods);
    void register_mouse_button(int button, int action, int mods);
    void register_mouse_pos(double x, double y);
    void register_mouse_scroll(double x, double y);

private:
    std::queue<InputEvent> input_queue;
};

}

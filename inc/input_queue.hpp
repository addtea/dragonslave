#pragma once
#include <queue>

namespace dragonslave {

enum class InputType {
    KEYBOARD,
    MOUSE_POS,
    MOUSE_BUTTON,
    MOUSE_SCROLL,
};

struct InputEvent {
    InputEvent(InputType type,
               int action, char key, double x, double y)
               : type(type), action(action), key(key), x(x), y(y) {}
    InputType type;
    int action = 0;
    char key = 0;
    double x = 0, y = 0;
};


class InputQueue
{
    public:
    void register_input(InputType, int, char, double, double);
    InputEvent get_next_event() { InputEvent tmp = queue.front(); queue.pop(); return tmp; }

    private:
    std::queue<InputEvent> queue;
};
}

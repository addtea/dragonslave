#include "input_queue.hpp"

namespace dragonslave {

void InputQueue::register_input(InputType type, int action, char key,
        double x = 0, double y = 0)
{
    this->queue.push(InputEvent(type, action, key, x, y));
}
}


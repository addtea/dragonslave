#include "input_events.hpp"

namespace dragonslave {


void KeyboardInputEvent::dispatch(InputEventHandler* handler) const
{
    handler->handle(*this);
}


void MouseButtonInputEvent::dispatch(InputEventHandler* handler) const
{
    handler->handle(*this);
}


void MouseMotionInputEvent::dispatch(InputEventHandler* handler) const
{
    handler->handle(*this);
}


void MouseScrollInputEvent::dispatch(InputEventHandler* handler) const
{
    handler->handle(*this);
}


void InputEventHandler::handle(const InputEvent& event) 
{
    event.dispatch(this);
}


}


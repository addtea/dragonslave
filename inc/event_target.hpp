#pragma once

#include <vector>
#include "event_listener.hpp"

namespace dragonslave {


template <typename EventType>
class EventTarget
{
public:
    void add_event_listener(EventListener<EventType> listener);
    void remove_event_listener(EventListener<EventType> listener);
    void emit_event();
private:
    std::vector<EventListener<EventType> > listeners_;
};


}

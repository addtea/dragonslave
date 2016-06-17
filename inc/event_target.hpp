#pragma once

#include <list>
#include "event_listener.hpp"

namespace dragonslave {


template <typename Event>
class EventTarget
{
public:
    void add_event_listener(EventListener<Event> listener)
    { listeners_.push_back(listener); }

    void remove_event_listener(EventListener<Event> listener)
    { listeners_.remove(listener); }

    void emit_event(const Event& ev)
    {
        for (EventListener<Event> listener : listeners_) {
            listener.handle(ev);
        }
    }
private:
    std::list<EventListener<Event> > listeners_;
};


}

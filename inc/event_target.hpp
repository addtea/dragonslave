#pragma once

#include <map>
#include <vector>
#include "event_listener.hpp"

namespace dragonslave {


class EventBase
{
};


class EventTarget
{
public:
    template <typename EventType>
    void addEventListener(const EventType& ev, EventListener<EventType> listener);
    template <typename EventType>
    void removeEventListener(const EventType& ev, EventListener<EventType> listener);
    template <typename EventType>
    void emitEvent(const EventType& ev);
private:
    std::map<EventBase, std::vector<EventListener<EventBase> > > listeners_;
};


}

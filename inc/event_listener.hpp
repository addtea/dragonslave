#pragma once

namespace dragonslave {


template <typename EventType>
class EventListener
{
public:
    virtual void handle(const EventType& ev) = 0;
};


}

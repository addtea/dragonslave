#pragma once

namespace dragonslave {


template <typename EventType>
class EventHandler
{
public:
    virtual void handle(const EventType& ev) = 0;
};


}

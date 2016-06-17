#pragma once

namespace dragonslave {

template <typename EventKType>
class EventHandler
{
public:
    EventHandler();
    virtual ~EventHandler();
    void handle(const EventKType& ev);
};

}

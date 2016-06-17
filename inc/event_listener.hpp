#pragma once

namespace dragonslave {


template <typename Event>
class EventListener
{
public:
    virtual void handle(const Event& ev) = 0;
};


}

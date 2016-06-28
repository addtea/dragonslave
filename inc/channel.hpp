#pragma once

#include <algorithm>
#include <mutex>
#include <future>
#include <vector>

namespace dragonslave {


/** \class Channel
 *  
 *  \brief Asynchronous event handler facilitator
 *
 *  TODO(eugene): Full description
 */
template<typename THandler, typename TMessage>
class Channel 
{
public:
    virtual ~Channel() { }

    void add(THandler* handler);
    void remove(THandler* handler);
    void broadcast(const TMessage& message);

private:
    std::mutex handlers_mutex_;
    std::vector<THandler*> handlers_;
};


template <typename THandler, typename TMessage>
void Channel<THandler, TMessage>::broadcast(const TMessage& message) 
{ 
    std::lock_guard<std::mutex> lock (handlers_mutex_);
    for (THandler* handler : handlers_) {
        handler->handle(message);
    }
}


template <typename THandler, typename TMessage>
void Channel<THandler, TMessage>::add(THandler* handler)
{
    handlers_.push_back(handler);
}


template <typename THandler, typename TMessage>
void Channel<THandler, TMessage>::remove(THandler* handler) 
{
    std::remove(handlers_.begin(), handlers_.end(), handler);
}


}

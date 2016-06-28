#pragma once

#include <iostream>
#include <shared_mutex>
#include <sstream>
#include <unordered_map>
#include <glm/glm.hpp>


namespace dragonslave {


enum class LogLevel 
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};


/** \class Logger
 *  
 *  \brief Simple debugger output
 *
 *  TODO(eugene): Full description
 *
 */
class Logger 
{
public:
    Logger(const char* file, 
                int line,
                LogLevel level);
    ~Logger();

    template <typename TValue>
    Logger& operator<<(const TValue& value);

private:
    std::stringstream buffer_;
};



template <typename TValue>
Logger& Logger::operator<<(const TValue& value)
{
    buffer_ << value;
    return *this;
}


#define LOG(level)\
dragonslave::Logger(__FILE__, __LINE__, dragonslave::LogLevel::level)


}

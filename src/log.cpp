#include <iomanip>
#include "log.hpp"

namespace dragonslave {


Logger::Logger(
        const char* file,
        int line,
        LogLevel level)
{ 
    switch (level) {
        case LogLevel::DEBUG:
            buffer_ << "\033[0;34m" << "DD";
            break;
        case LogLevel::INFO:
            buffer_ << "\033[0;32m" << "II";
            break;
        case LogLevel::WARNING:
            buffer_ << "\033[0;33m" << "WW";
            break;
        case LogLevel::ERROR:
            buffer_ << "\033[0;31m" << "XX";
    }
    buffer_ << "\033[0;0m" 
            << std::right << std::setw(20) << file << ":"
            << std::left  << std::setw(5)  << line << "] ";
}

Logger::~Logger()
{
    buffer_ << std::endl;
    std::cerr << buffer_.str();
}

}

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
            buffer_ << "\033[0;34m" << "DEBUG";
            break;
        case LogLevel::INFO:
            buffer_ << "\033[0;32m" << "INFO";
            break;
        case LogLevel::WARNING:
            buffer_ << "\033[0;33m" << "WARNING";
            break;
        case LogLevel::ERROR:
            buffer_ << "\033[0;31m" << "ERROR";
    }
    buffer_ << "\033[0;0m " 
            << file << ":"
            << line << " -- ";
}

Logger::~Logger()
{
    buffer_ << std::endl;
    std::cerr << buffer_.str();
}

}

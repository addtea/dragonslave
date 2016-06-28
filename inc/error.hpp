#pragma once

#include <stdexcept>
#include <string>

namespace dragonslave {


class FatalError : public std::runtime_error
{
public:
    FatalError(const std::string& type, const std::string& message)
      : std::runtime_error(build_what_(type, message))
      , type_ (type)
      , message_ (message)
    { }

    virtual ~FatalError() { }

    inline const std::string& get_type() const { return type_; }
    inline const std::string& get_message() const { return message_; }

private: 
    static std::string build_what_(const std::string& type, const std::string& message) 
    {
        return type + ": " + message;
    }

    std::string type_;
    std::string message_;
};


}

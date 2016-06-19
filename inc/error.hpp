#pragma once

#include <stdexcept>
#include <string>

namespace dragonslave {


class FatalError : public std::runtime_error
{
public:
    FatalError(const std::string& type, const std::string& message)
      : std::runtime_error(build_runtime_error_what(type, message))
      , type_ (type)
      , message_ (message)
    { }

    virtual ~FatalError() { }

    inline const std::string& get_type() const { return type_; }
    inline const std::string& get_message() const { return message_; }

private: 
    static std::string build_runtime_error_what(const std::string& type, const std::string& message) 
    {
        return type + ": " + message;
    }

    std::string type_;
    std::string message_;
};


class FileNotFoundError : public FatalError
{
public:
    NotFoundError(const std::string& path) 
      : FatalError ("File \"" + path + "\" does not exist.");
    { }
}

}

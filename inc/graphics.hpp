#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "error.hpp"

namespace dragonslave {


class InitGlewError : public FatalError { 
public:
    InitGlewError() 
      : FatalError("InitGlewError", "Failed to initialize GLEW")
    { }
};


class ShaderCompileError : public FatalError {
public:
    std::string log;

    ShaderCompileError(const std::string& path, const std::string& log) 
      : FatalError("ShaderCompileError", "Failed to compile shader, \"" + path + "\"")
      , log (log)
    { }
};


class ProgramLinkError : public FatalError {
public:
    std::string log;

    ProgramLinkError(const std::string& log) 
      : FatalError("ProgramLinkError", "Failed to link program")
      , log (log)
    { }
};


class Graphics
{
public:
    Graphics();
    virtual ~Graphics();

    void initiate();
    void terminate();

    GLuint load_shader(GLenum type, const std::string& path);
    GLuint load_program(const std::vector<GLuint>& shaders);

    GLuint create_vertex_array();
    GLuint create_buffer();
    GLuint create_texture(); 

private:
    std::vector<GLuint> shaders_;
    std::vector<GLuint> programs_;
    std::vector<GLuint> vertex_arrays_;
    std::vector<GLuint> buffers_;
    std::vector<GLuint> textures_;
};


}

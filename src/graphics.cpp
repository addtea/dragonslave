#include <fstream>

#include "graphics.hpp"

namespace dragonslave {


Graphics::Graphics() { }


Graphics::~Graphics() { }


void Graphics::init() 
{ 
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        throw InitGlewError();
    }
    glGetError();
}


void Graphics::term()
{
    for (GLuint shader : shaders_) {
        glDeleteShader(shader);
    }

    for (GLuint program : programs_) {
        glDeleteProgram(program);
    }
}


GLuint Graphics::load_shader(GLenum type, const std::string& path)
{
    std::ifstream in (path);
    GLuint shader = glCreateShader(type);
    int file_size = 0;
    in.seekg(0, std::ios::end);
    file_size = in.tellg();
    in.seekg(0, std::ios::beg);
    std::vector<GLchar> source_buffer (file_size);
    in.read(source_buffer.data(), file_size);
    const GLchar* source = source_buffer.data();

    glShaderSource(shader, 1, &source, &file_size);

    glCompileShader(shader);

    GLint is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if (!is_compiled) {
        GLint log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<GLchar> log_buffer (log_length);
        glGetShaderInfoLog(shader, log_length, &log_length, log_buffer.data());
        std::string log (log_buffer.data(), static_cast<size_t>(log_length - 1));
        throw ShaderCompileError(path, log);
    }

    shaders_.push_back(shader);
    return shader;
}


GLuint Graphics::load_program(const std::vector<GLuint>& shaders)
{
    GLuint program = glCreateProgram();    

    for (GLuint shader : shaders) {
        glAttachShader(program, shader);
    }

    glLinkProgram(program);

    GLint is_linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
    if (!is_linked) {
        GLint log_length = 0;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<GLchar> log_buffer (log_length);
        glGetProgramInfoLog(program, log_length, &log_length, log_buffer.data());
        std::string log (log_buffer.data(), static_cast<size_t>(log_length - 1));
        throw ProgramLinkError(log);
    }

    for (GLuint shader : shaders) {
        glDetachShader(program, shader);
    }

    programs_.push_back(program);
    return program;
}


}

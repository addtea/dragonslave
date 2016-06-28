#include <algorithm>
#include <fstream>
#include "graphics_context.hpp"
#include "error.hpp"
#include "log.hpp"

namespace dragonslave {


GraphicsContext::GraphicsContext() { }


GraphicsContext::~GraphicsContext() { }


void GraphicsContext::initialize(Window* window) 
{ 
    window->make_current();
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
    }
    glGetError();
}


void GraphicsContext::terminate()
{
    for (GLuint shader : shaders_) {
        glDeleteShader(shader);
    }

    for (GLuint program : programs_) {
        glDeleteProgram(program);
    }

    glDeleteVertexArrays(vertex_arrays_.size(), vertex_arrays_.data());
    glDeleteBuffers(buffers_.size(), buffers_.data());
    glDeleteTextures(textures_.size(), textures_.data());
}


GLuint GraphicsContext::load_shader(GLenum type, const std::string& path)
{
    std::ifstream in (path);
    if (!in.is_open()) {
        LOG(ERROR) << "Could not open file, \"" << path << "\"";
        throw FatalError("FileNotFoundError", "Failed to open file");
    }
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
        LOG(ERROR) << "Dumping log:\n" << log;
        throw FatalError("ShaderCompileError", "Failed to compile shader");
    }

    shaders_.push_back(shader);
    return shader;
}


GLuint GraphicsContext::load_program(const std::vector<GLuint>& shaders)
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
        LOG(ERROR) << "Dumping log:\n" << log;
        throw FatalError("ProgramLinkError", "Failed to link program");
    }

    for (GLuint shader : shaders) {
        glDetachShader(program, shader);
    }

    programs_.push_back(program);
    return program;
}


GLuint GraphicsContext::create_vertex_array()
{
    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    vertex_arrays_.push_back(vertex_array);
    return vertex_array;
}


GLuint GraphicsContext::create_buffer()
{
    GLuint buffer;
    glGenBuffers(1, &buffer);
    buffers_.push_back(buffer);
    return buffer;
}


GLuint GraphicsContext::create_texture()
{
    GLuint texture;
    glGenTextures(1, &texture);
    textures_.push_back(texture);
    return texture;
}


void GraphicsContext::destroy_buffer(GLuint buffer)
{
    glDeleteBuffers(1, &buffer);
    std::remove(buffers_.begin(), buffers_.end(), buffer);
}


void GraphicsContext::destroy_program(GLuint program)
{
    glDeleteProgram(program);
    std::remove(programs_.begin(), programs_.end(), program);
}


void GraphicsContext::destroy_shader(GLuint shader)
{
    glDeleteShader(shader);
    std::remove(shaders_.begin(), shaders_.end(), shader);
}


void GraphicsContext::destroy_texture(GLuint texture)
{
    glDeleteTextures(1, &texture);
    std::remove(textures_.begin(), textures_.end(), texture);
}


void GraphicsContext::destroy_vertex_array(GLuint vertex_array)
{
    glDeleteVertexArrays(1, &vertex_array);
    std::remove(vertex_arrays_.begin(), vertex_arrays_.end(), vertex_array);
}




}

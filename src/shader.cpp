#include "shader.hpp"

namespace dragonslave {


void Shader::create(GraphicsContext* gc) 
{
    gc_ = gc;
    setup(gc_);
}


void Shader::destroy()
{
    cleanup(gc_);
    gc_ = nullptr;
}


}

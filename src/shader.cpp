#include "shader.hpp"

namespace dragonslave {


void Shader::create(GraphicsContext* gc) 
{
    gc_ = gc;
    on_setup(gc_);
}


void Shader::destroy()
{
    on_cleanup(gc_);
    gc_ = nullptr;
}


}

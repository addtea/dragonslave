#pragma once

#include "graphics_context.hpp"
#include "image.hpp"

namespace dragonslave {


class ImageLoader
{
public:
    ImageLoader();
    virtual ~ImageLoader();

    Image load(GraphicsContext* gc, const std::string& path);
};


}

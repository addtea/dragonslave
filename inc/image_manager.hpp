#pragma once

#include <list>
#include <string>
#include "geometry.hpp"
#include "image.hpp"
#include "image_loader.hpp"

namespace dragonslave {


class ImageManager
{
public:
    ImageManager();
    virtual ~ImageManager();

    void initialize(GraphicsContext* gc, ImageLoader* image_loader);
    void terminate();

    Image* load_image(const std::string& path);
    void destroy_image(Image* image);

private:
    GraphicsContext* gc_ = nullptr;
    ImageLoader* image_loader_ = nullptr;
    std::list<Image> images_;
};

    
}

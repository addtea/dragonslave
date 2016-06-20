#pragma once

#include <string>

#include "graphics.hpp"
#include "image.hpp"

namespace dragonslave {


class ImageLoader
{
public:
    ImageLoader();
    virtual ~ImageLoader();

    void initiate(Graphics* graphics);
    void terminate();

    void load_image_from_file(const std::string& path, Image& image);

private:
    Graphics* graphics_ = nullptr;
};


}

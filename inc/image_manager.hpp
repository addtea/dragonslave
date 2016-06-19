#pragma once

#include <list>
#include <string>
#include <unordered_map>

#include <GL/glew.h>

#include "image.hpp"
#include "image_loader.hpp"

namespace dragonslave {


class ImageManager 
{
public:
    ImageManager();
    ~ImageManager();

    void set_loader(ImageLoader* loader);

    Image& create_image();
    Image& create_named_image(const std::string& name);

    Image& load_image(const std::string& path);
    Image& load_named_image(const std::string& name, const std::string& path);

    Image* get_image(const std::string& name);

private:
    ImageLoader* loader_ = nullptr;
    std::unordered_map<
            std::string, 
            std::list<Image>::iterator>
        path_cache_;
    std::unordered_map<
            std::string, 
            std::list<Image>::iterator>
        image_lookup_;
    std::list<Image> images_;

    void validate_name_(const std::string& name);
    std::list<Image>::iterator create_image_it_();
};


}

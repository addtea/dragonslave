#include "image_manager.hpp"

namespace dragonslave {

    
ImageManager::ImageManager() { }


ImageManager::~ImageManager() { }


void ImageManager::initialize(GraphicsContext* gc, ImageLoader* image_loader)
{
    gc_ = gc;
    image_loader_ = image_loader;
}


void ImageManager::terminate()
{
    gc_ = nullptr;
    image_loader_ = nullptr;
}


Image* ImageManager::load_image(const std::string& path)
{
    images_.push_back(image_loader_->load(gc_, path));
    return &images_.back();
}


void ImageManager::destroy_image(Image* image)
{
    gc_->destroy_texture(image->texture);
    std::remove_if(
        images_.begin(),
        images_.end(),
        [=](Image& stored_image){ 
            return &stored_image == image;
        });
}


}

#include <algorithm>

#include "image_manager.hpp"

namespace dragonslave {


ImageManager::ImageManager() { }


ImageManager::~ImageManager() { }


void ImageManager::set_loader(ImageLoader* loader)
{
    loader_ = loader;
}


Image& ImageManager::create_image()
{
    std::list<Image>::iterator it = create_image_it_();
    return *it;
}


Image& ImageManager::create_named_image(const std::string& name)
{
    validate_name_(name);
    std::list<Image>::iterator it = create_image_it_();
    image_lookup_[name] = it;
    return *it;
}


Image& ImageManager::load_image(const std::string& path)
{
    std::unordered_map<
            std::string,
            std::list<Image>::iterator>::const_iterator
        mit = path_cache_.find(path);
    if (mit != path_cache_.end())
        return *mit->second;
    std::list<Image>::iterator it = create_image_it_();
    path_cache_[path] = it;
    loader_->load_image_from_file(path, *it);
    return *it;
}


Image& ImageManager::load_named_image(const std::string& name, const std::string& path)
{
    validate_name_(name);
    std::unordered_map<
            std::string,
            std::list<Image>::iterator>::const_iterator
        mit = path_cache_.find(path);
    if (mit != path_cache_.end()) {
        image_lookup_[name] = mit->second; 
        return *mit->second;
    }
    std::list<Image>::iterator it = create_image_it_();
    path_cache_[path] = it;
    image_lookup_[name] = it;
    loader_->load_image_from_file(path, *it);
    return *it;
}


Image* ImageManager::get_image(const std::string& name)
{
    std::unordered_map<
            std::string,
            std::list<Image>::iterator>::const_iterator
        mit = image_lookup_.find(name);
    if (mit == image_lookup_.end()) 
        return nullptr;
    return &*mit->second;
}


void ImageManager::validate_name_(const std::string& name)
{
    std::unordered_map<
            std::string,
            std::list<Image>::iterator>::const_iterator
        mit = image_lookup_.find(name);
    if (mit != image_lookup_.end()) 
        throw DuplicateError("Image", name);
}


std::list<Image>::iterator ImageManager::create_image_it_()
{
    images_.emplace_back();
    return std::prev(images_.end());
}


}

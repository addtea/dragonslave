#include "asset_manager.hpp"

namespace dragonslave {


AssetManager::AssetManager() { }


AssetManager::~AssetManager() { }


void AssetManager::initiate(Graphics* graphics) 
{
    image_loader_.initiate(
        graphics);
    model_loader_.initiate(
        graphics,
        &geometry,
        &material,
        &image);
    model.set_loader(&model_loader_);
    image.set_loader(&image_loader_);
}

void AssetManager::terminate()
{
    image_loader_.terminate();
    model_loader_.terminate();
    model.set_loader(nullptr);
    image.set_loader(nullptr);
}


}

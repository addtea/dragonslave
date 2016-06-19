#pragma once

namespace dragonslave {


class TextureManager
{
public:
    TextureManager(Graphics& graphics);
    virtual ~TextureManager();

    GLuint load_image_texture(const std::string& path);
    void unload_texture(const std::string& path);

private:
    Graphics& graphics_;
};


}

#include <FreeImage.h>
#include "image_loader.hpp"
#include "error.hpp"
#include "log.hpp"

namespace dragonslave {
    

ImageLoader::ImageLoader() { }


ImageLoader::~ImageLoader() { }


Image ImageLoader::load(GraphicsContext* gc, const std::string& path)
{
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(), 0);

    if (format == -1) {
        LOG(DEBUG) << "Failed to open file, \"" << path << "\"";
        throw FatalError("FileNotFoundError", "Failed to open file");
    }

    // TODO(eugene): Check if image format is supported
    
    FIBITMAP* bitmap = FreeImage_Load(format, path.c_str());
    int bpp = FreeImage_GetBPP(bitmap);

    if (bpp != 32) {
        FIBITMAP* orig_bitmap = bitmap;
        bitmap = FreeImage_ConvertTo32Bits(bitmap);
        FreeImage_Unload(orig_bitmap);
    } 

    Image image;

    image.width = FreeImage_GetWidth(bitmap);
    image.height = FreeImage_GetHeight(bitmap);
    GLubyte* pixels = FreeImage_GetBits(bitmap);

    image.texture = gc->create_texture();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image.texture);
    
    glTexImage2D(
        GL_TEXTURE_2D, 
        0, GL_RGBA,
        image.width, image.height, 
        0, GL_BGRA, 
        GL_UNSIGNED_BYTE, pixels);

    glGenerateMipmap(GL_TEXTURE_2D);

    FreeImage_Unload(bitmap);
    
    // TODO(eugene): Allow for different filters and wraps

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0u);

    return image;
}


}

#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "graphics.hpp"
#include "mesh.hpp"

namespace dragonslave {

class ModelFileNotFoundError : public FatalError {
public:
    ModelFileNotFoundError(const std::string& filepath)
      : FatalError("ModelFileNotFoundError", "Could not find file: \"" + filepath + "\"")
    { }
};

class AssimpImporterError : public FatalError {
public:
    AssimpImporterError(const std::string& error_string)
        : FatalError("AssimpImporterError", error_string)
    { }
};


class ModelLoader
{
    public:
    ModelLoader(Graphics& graphics)
    : graphics_(graphics)
    { }

    std::vector<Mesh> meshes;
    void load_file(const std::string& filepath);

    private:
    Assimp::Importer importer_;
    const aiScene * scene_;
    Graphics& graphics_;

    void process_mesh_(const aiMesh * ai_mesh);
    void process_node_(aiNode * ai_node);
};

}

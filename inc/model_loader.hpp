#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "graphics.hpp"
#include "mesh.hpp"

namespace dragonslave {


class AssimpImporterError : public FatalError {
public:
    AssimpImporterError(const std::string& message)
        : FatalError("AssimpImporterError", message)
    { }
};


}

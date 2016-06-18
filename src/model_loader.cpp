#include "model_loader.hpp"
#include <string>
#include <fstream>
#include <assimp/scene.h>

namespace dragonslave {

void ModelLoader::load_file(const std::string& filepath)
{
    std::ifstream input_file(filepath, std::ifstream::in);
    if (!input_file.fail()) {
        input_file.close();
    } else {
        throw ModelFileNotFoundError(filepath);
    }

    scene_ = importer_.ReadFile(filepath, aiProcess_Triangulate);
    if (!scene_) {
        throw AssimpImporterError(importer_.GetErrorString());
    }

    process_node_(scene_->mRootNode);
}


void ModelLoader::process_mesh_(const aiMesh * ai_mesh)
{
    Mesh mesh(graphics_);
    mesh.has_positions = ai_mesh->HasPositions();
    mesh.has_normals = ai_mesh->HasNormals();
    mesh.has_tex_coords = ai_mesh->HasTextureCoords(0);

    glm::vec2 v2;
    glm::vec3 v3;
    for (unsigned i = 0; i < ai_mesh->mNumVertices; ++i) {
        if (mesh.has_positions) {
            v3.x = ai_mesh->mVertices[i].x;
            v3.y = ai_mesh->mVertices[i].y;
            v3.z = ai_mesh->mVertices[i].z;
            mesh.positions.push_back(v3);
        }
        if (mesh.has_normals) {
            v3.x = ai_mesh->mNormals[i].x;
            v3.y = ai_mesh->mNormals[i].y;
            v3.z = ai_mesh->mNormals[i].z;
            mesh.normals.push_back(v3);
        }
        if (mesh.has_tex_coords) {
            v2.x = ai_mesh->mTextureCoords[0][i].x;
            v2.y = ai_mesh->mTextureCoords[0][i].y;
            mesh.tex_coords.push_back(v2);
        }
    }

    mesh.has_indices = ai_mesh->HasFaces();
    for (unsigned i = 0; i < ai_mesh->mNumFaces; ++i) {
        aiFace ai_face = ai_mesh->mFaces[i];
        for (unsigned j = 0; j < ai_face.mNumIndices; ++j) {
            mesh.indices.push_back(ai_face.mIndices[j]);
        }
    }

    /* TODO: Implement bones
    mesh.has_skeleton = ai_mesh->HasBones();
    for (unsigned i = 0; i < ai_mesh->mNumBones; ++i) {
        aiBone ai_bone = ai_mesh->mBones[i];
        for (unsigned j = 0; j < ai_bone.mNumBones; ++i) {


        }

    }
    */

    /* TODO: Implement materials
     Need to discuss texture naming conventions

    */

   mesh.upload();
}

void ModelLoader::process_node_(aiNode * ai_node)
{
    for (unsigned i = 0; i < ai_node->mNumMeshes; ++i) {
        aiMesh * ai_mesh = scene_->mMeshes[ai_node->mMeshes[i]];
        process_mesh_(ai_mesh);
    }

    for (unsigned i = 0; i < ai_node->mNumChildren; ++i) {
        process_node_(ai_node->mChildren[i]);
    }
}

}

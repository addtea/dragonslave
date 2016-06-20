#include "model_loader.hpp"

namespace dragonslave {


ModelLoader::ModelLoader() { }


ModelLoader::~ModelLoader() { }


void ModelLoader::initiate(
        Graphics* graphics,
        GeodeManager* geode_manager,
        MaterialManager* material_manager,
        ImageManager* image_manager)
{
    graphics_ = graphics;
    geode_manager_ = geode_manager;
    material_manager_ = material_manager;
    image_manager_ = image_manager;
}


void ModelLoader::terminate() 
{ 
    graphics_ = nullptr;
    geode_manager_ = nullptr;
    material_manager_ = nullptr;
    image_manager_ = nullptr;
}


void ModelLoader::load_model_from_file(
        const std::string& path,
        Model& model)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        // TODO(eugene): Create error for unloaded file
    }

    std::string base_dir = path.substr(0, path.find_last_of('/'));
    std::vector<Material*> materials;

    load_materials_(scene, base_dir, materials);
    load_meshes_(scene, materials, model);
}


void ModelLoader::process_geode_(aiMesh* ai_mesh, Geode& geode)
{
    geode.has_normals = true;
    geode.has_tex_coords = ai_mesh->mTextureCoords[0] != nullptr;
    for (int i = 0; i < ai_mesh->mNumVertices; i++) {
        geode.positions.emplace_back(
            static_cast<float>(ai_mesh->mVertices[i].x),
            static_cast<float>(ai_mesh->mVertices[i].y),
            static_cast<float>(ai_mesh->mVertices[i].z));
        geode.normals.emplace_back(
            static_cast<float>(ai_mesh->mNormals[i].x),
            static_cast<float>(ai_mesh->mNormals[i].y),
            static_cast<float>(ai_mesh->mNormals[i].z));
        if (geode.has_tex_coords) {
            geode.tex_coords.emplace_back(
                static_cast<float>(ai_mesh->mTextureCoords[0][i].x),
                static_cast<float>(ai_mesh->mTextureCoords[0][i].y));
        }
    }

    for(int i = 0; i < ai_mesh->mNumFaces; i++)
    {
        aiFace& face = ai_mesh->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++)
            geode.indices.push_back(face.mIndices[j]);
    }

    geode.upload(graphics_);
}


void ModelLoader::process_material_(
        aiMaterial* ai_material, 
        const std::string& base_dir,
        Material& material)
{
    int ai_int;
    float ai_float;
    aiColor3D ai_color;
    aiString ai_string;

    if (ai_material->Get(AI_MATKEY_COLOR_AMBIENT, ai_color) == AI_SUCCESS) {
        material.ambient_color = {ai_color.r, ai_color.g, ai_color.b};
    }

    if (ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, ai_color) == AI_SUCCESS) {
        material.diffuse_color = {ai_color.r, ai_color.g, ai_color.b};
    }

    if (ai_material->Get(AI_MATKEY_COLOR_SPECULAR, ai_color) == AI_SUCCESS) {
        material.specular_color = {ai_color.r, ai_color.g, ai_color.b};
    }

    if (ai_material->Get(AI_MATKEY_SHININESS, ai_float) == AI_SUCCESS) {
        material.shininess = ai_float;
    }

    if (ai_material->GetTextureCount(aiTextureType_AMBIENT) > 0 &&
            ai_material->GetTexture(
                aiTextureType_AMBIENT, 0u, &ai_string, nullptr, nullptr, 
                nullptr, nullptr, nullptr) 
            == AI_SUCCESS) {
        // TODO(eugene): Update for multiple operating systems
        std::string path = base_dir + "/" + ai_string.data;
        Image& image = image_manager_->load_image(path);
        material.has_ambient_map = true;
        material.ambient_map = image.texture;
    }

    if (ai_material->GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
            ai_material->GetTexture(
                aiTextureType_DIFFUSE, 0u, &ai_string, nullptr, nullptr, 
                nullptr, nullptr, nullptr) 
            == AI_SUCCESS) {
        // TODO(eugene): Update for multiple operating systems
        std::string path = base_dir + "/" + ai_string.data;
        Image& image = image_manager_->load_image(path);
        material.has_diffuse_map = true;
        material.diffuse_map = image.texture;
    }

    if (ai_material->GetTextureCount(aiTextureType_SPECULAR) > 0 &&
            ai_material->GetTexture(
                aiTextureType_SPECULAR, 0u, &ai_string, nullptr, nullptr, 
                nullptr, nullptr, nullptr) 
            == AI_SUCCESS) {

        // TODO(eugene): Update for multiple operating systems
        std::string path = base_dir + "/" + ai_string.data;
        Image& image = image_manager_->load_image(path);
        material.has_specular_map = true;
        material.specular_map = image.texture;
    }
}


void ModelLoader::load_materials_(
        const aiScene* scene, 
        const std::string& base_dir, 
        std::vector<Material*>& materials)
{
    for (int i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* ai_material = scene->mMaterials[i];
        Material& material = material_manager_->create_material();
        process_material_(ai_material, base_dir, material);
        materials.push_back(&material);
    }
}


void ModelLoader::load_meshes_(
        const aiScene* scene,
        const std::vector<Material*>& materials,
        Model& model)
{
    for (int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* ai_mesh = scene->mMeshes[i];
        Geode& geode = geode_manager_->create_geode();
        process_geode_(ai_mesh, geode);
        
        Material* material = nullptr;
        if (ai_mesh->mMaterialIndex >= 0) {
            material = materials.at(ai_mesh->mMaterialIndex);
        }
        model.meshes.emplace_back(&geode, material);
    }
}


}

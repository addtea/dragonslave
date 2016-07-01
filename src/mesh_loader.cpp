#include "mesh_loader.hpp"

namespace dragonslave {


MeshLoader::MeshLoader() { }


MeshLoader::~MeshLoader() { }


void MeshLoader::load_mesh(
        GeometryManager* geometry_manager,
        MaterialManager* material_manager,
        ImageManager* image_manager,
        ShaderManager* shader_manager,
        const std::string& path,
        Mesh* mesh)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        // TODO(eugene): Create error for unloaded file
    }

    std::string base_dir = path.substr(0, path.find_last_of('/'));
    std::vector<Material*> materials;

    load_materials_(material_manager, image_manager, scene, base_dir, materials);
    load_mesh_(geometry_manager, shader_manager, scene, materials, mesh);
}


void MeshLoader::process_material_(
        ImageManager* image_manager,
        aiMaterial* ai_material, 
        const std::string& base_dir,
        Material* material)
{
    int ai_int;
    float ai_float;
    aiColor3D ai_color;
    aiString ai_string;

    if (ai_material->Get(AI_MATKEY_COLOR_AMBIENT, ai_color) == AI_SUCCESS) {
        material->ambient_color = {ai_color.r, ai_color.g, ai_color.b};
    }

    if (ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, ai_color) == AI_SUCCESS) {
        material->diffuse_color = {ai_color.r, ai_color.g, ai_color.b};
    }

    if (ai_material->Get(AI_MATKEY_COLOR_SPECULAR, ai_color) == AI_SUCCESS) {
        material->specular_color = {ai_color.r, ai_color.g, ai_color.b};
    }

    if (ai_material->Get(AI_MATKEY_SHININESS, ai_float) == AI_SUCCESS) {
        material->shininess = ai_float;
    }

    if (ai_material->GetTextureCount(aiTextureType_AMBIENT) > 0 &&
            ai_material->GetTexture(
                aiTextureType_AMBIENT, 0u, &ai_string, nullptr, nullptr, 
                nullptr, nullptr, nullptr) 
            == AI_SUCCESS) {
        // TODO(eugene): Update for multiple operating systems
        std::string path = base_dir + "/" + ai_string.data;
        Image* image = image_manager->load_image(path);
        material->has_ambient_map = true;
        material->ambient_map = image->texture;
    }

    if (ai_material->GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
            ai_material->GetTexture(
                aiTextureType_DIFFUSE, 0u, &ai_string, nullptr, nullptr, 
                nullptr, nullptr, nullptr) 
            == AI_SUCCESS) {
        // TODO(eugene): Update for multiple operating systems
        std::string path = base_dir + "/" + ai_string.data;
        Image* image = image_manager->load_image(path);
        material->has_diffuse_map = true;
        material->diffuse_map = image->texture;
    }

    if (ai_material->GetTextureCount(aiTextureType_SPECULAR) > 0 &&
            ai_material->GetTexture(
                aiTextureType_SPECULAR, 0u, &ai_string, nullptr, nullptr, 
                nullptr, nullptr, nullptr) 
            == AI_SUCCESS) {

        // TODO(eugene): Update for multiple operating systems
        std::string path = base_dir + "/" + ai_string.data;
        Image* image = image_manager->load_image(path);
        material->has_specular_map = true;
        material->specular_map = image->texture;
    }
}


void MeshLoader::process_geometry_(aiMesh* ai_mesh, Geometry* geometry)
{
    geometry->has_normals = true;
    geometry->has_tex_coords = ai_mesh->mTextureCoords[0] != nullptr;
    for (int i = 0; i < ai_mesh->mNumVertices; i++) {
        geometry->positions.emplace_back(
            static_cast<float>(ai_mesh->mVertices[i].x),
            static_cast<float>(ai_mesh->mVertices[i].y),
            static_cast<float>(ai_mesh->mVertices[i].z));
        geometry->normals.emplace_back(
            static_cast<float>(ai_mesh->mNormals[i].x),
            static_cast<float>(ai_mesh->mNormals[i].y),
            static_cast<float>(ai_mesh->mNormals[i].z));
        if (geometry->has_tex_coords) {
            geometry->tex_coords.emplace_back(
                static_cast<float>(ai_mesh->mTextureCoords[0][i].x),
                static_cast<float>(ai_mesh->mTextureCoords[0][i].y));
        }
    }

    for(int i = 0; i < ai_mesh->mNumFaces; i++)
    {
        aiFace& face = ai_mesh->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++)
            geometry->indices.push_back(face.mIndices[j]);
    }

    geometry->upload();
}


void MeshLoader::load_materials_(
        MaterialManager* material_manager,
        ImageManager* image_manager,
        const aiScene* scene, 
        const std::string& base_dir, 
        std::vector<Material*>& materials)
{
    for (int i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* ai_material = scene->mMaterials[i];
        Material* material = material_manager->create_material();
        process_material_(image_manager, ai_material, base_dir, material);
        materials.push_back(material);
    }
}


void MeshLoader::load_mesh_(
        GeometryManager* geometry_manager,
        ShaderManager* shader_manager,
        const aiScene* scene,
        const std::vector<Material*>& materials,
        Mesh* mesh)
{
    for (int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* ai_mesh = scene->mMeshes[i];
        Geometry* geometry = geometry_manager->create_geometry();
        process_geometry_(ai_mesh, geometry);
        
        Material* material = nullptr;
        material = materials.at(ai_mesh->mMaterialIndex);
        Shader* shader = shader_manager->get_default_shader();
        mesh->add_submesh(geometry, material, shader);
    }
}


}

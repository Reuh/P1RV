#include <GL/glew.h>
#include "ModelRenderer.hpp"
#include <iostream>
#include <string>
#include "Shader.hpp"

vector<Texture> textures_loaded; // global texture cache

ModelRenderer::ModelRenderer(string path) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void ModelRenderer::render(Shader* shader) {
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].render(shader);
}

void ModelRenderer::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}  

MeshRenderer ModelRenderer::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    Texture texture;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector; 
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z; 
        vertex.Position = vector;

        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertex.Color = glm::vec4(1.f, 1.f, 1.f, 1.f); // TODO: extract value from model to support untextured faces
        
        vertices.push_back(vertex);
    }
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        texture = loadMaterialTextures(material, aiTextureType_DIFFUSE);
    }

    MeshRenderer r = MeshRenderer(vertices, indices, texture);

    return r;
}  

Texture ModelRenderer::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
{
    Texture texture;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                return textures_loaded[j];
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            texture.path = directory + '/' + string(str.C_Str());
            if (!texture.tex.loadFromFile(texture.path)) {
                std::cout << "ERROR: can't load texture " << texture.path << endl;
            }
            textures_loaded.push_back(texture); // add to loaded textures
            break; // TODO: support multiples textures
        }
    }
    return texture;
}  

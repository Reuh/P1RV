#include <GL/glew.h>
#include "ModelRenderer.hpp"
#include <iostream>
#include <string>
#include "Shader.hpp"
#include "BoxCollider.hpp"

vector<Texture*> textures_loaded; // global texture cache

ModelRenderer::ModelRenderer(const string& path) {
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

GroupCollider* ModelRenderer::makeCollider(bool rigid) {
    GroupCollider* r = new GroupCollider(rigid);
    r->object = object;
    for(auto& mesh : meshes)
        r->addCollider(mesh.makeCollider(rigid));
    return r;
}

void ModelRenderer::render(Shader* shader) {
    shader->sendUniform("hasLightning", getLightning());
    for(auto & mesh : meshes)
        mesh.render(shader);
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
    auto* material = new Material();

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex{};
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

        if(mesh->mColors[0])
            vertex.Color = glm::vec4(mesh->mColors[0]->r, mesh->mColors[0]->g, mesh->mColors[0]->b, mesh->mColors[0]->a);
        else
            vertex.Color = glm::vec4(1.f, 1.f, 1.f, 1.f);
        
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
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
        if (loadMaterialTextures(mat, aiTextureType_DIFFUSE, &material->textureDiffuse)) {
            material->hasTexture = true;
        } else {
            material->hasTexture = false;
            // no texture, use diffuse color
            aiColor3D diffuseColor(1.f,1.f,1.f);
            mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
            material->diffuseColor = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);
        }

        // load ambient color
        aiColor3D ambientColor(1.f,1.f,1.f);
        mat->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
        material->ambientColor = glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b);

        // load specular color
        aiColor3D specularColor(1.f,1.f,1.f);
        mat->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
        material->specularColor = glm::vec3(specularColor.r, specularColor.g, specularColor.b);

        // load shininess
        float shininess = 1.0f;
        mat->Get(AI_MATKEY_SHININESS_STRENGTH, shininess);
        material->shininess = shininess;

    // default material
    } else {
        material->hasTexture = false;
        material->diffuseColor = glm::vec3(1.f,1.f,1.f);
        material->ambientColor = glm::vec3(1.f,1.f,1.f);
        material->specularColor = glm::vec3(1.f,1.f,1.f);
        material->shininess = 1.0f;
    }

    MeshRenderer r = MeshRenderer(vertices, indices, *material);

    return r;
}  

bool ModelRenderer::loadMaterialTextures(aiMaterial *mat, aiTextureType type, Texture* texture)
{
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture has already been loaded
        for(auto & j : textures_loaded)
        {
            if(j->path == (directory + '/' + string(str.C_Str())))
            {
                texture->path = j->path;
                texture->tex = j->tex;
                return true;
            }
        }
        // if texture hasn't been loaded already, load it
        texture->path = directory + '/' + string(str.C_Str());
        if (!texture->tex.loadFromFile(texture->path)) {
            cout << "ERROR: can't load texture " << texture->path << endl;
            return false;
        }
        textures_loaded.push_back(texture); // add to loaded textures
        return true; // TODO: support multiples textures (specular, normal...)
    }
    return false;
}  

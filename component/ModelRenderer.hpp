#ifndef P1RV_MODELRENDERER_H
#define P1RV_MODELRENDERER_H

#include "MeshRenderer.hpp"
#include "Renderer.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.hpp"


using namespace std;

class ModelRenderer : public Renderer {
private:
	// model data
    vector<MeshRenderer> meshes; // mesh list
    string directory; // model directory (for loading textures from the same directory)

    // Create meshes in the Assimp node and add them to the mesh list
    void processNode(aiNode *node, const aiScene *scene);

    // Create a new mesh from an Assimp mesh
    MeshRenderer processMesh(aiMesh *mesh, const aiScene *scene);

    // Try to get a texture from a Assimp material
    bool loadMaterialTextures(aiMaterial *mat, aiTextureType type, Texture* texture);

public:

    ModelRenderer(const string& path);

    void render(Shader* shader) override;
};

#endif //P1RV_MODELRENDERER_H

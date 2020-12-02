#ifndef P1RV_MODELRENDERER_H
#define P1RV_MODELRENDERER_H

#include "MeshRenderer.h"
#include "Renderer.h"
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
    vector<MeshRenderer> meshes;
    string directory;

    void processNode(aiNode *node, const aiScene *scene);
    MeshRenderer processMesh(aiMesh *mesh, const aiScene *scene);
    Texture loadMaterialTextures(aiMaterial *mat, aiTextureType type);

public:

    ModelRenderer(string path);

    void render(Shader* shader) override;
};

#endif //P1RV_MODELRENDERER_H

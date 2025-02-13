#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"

class Model {
public:
	std::vector<Texture> loaded_textures;
	std::vector<Mesh> meshes;

	Model(char* path);
	void draw(Shader shader);

private:
	
	std::string directory;

	void load_model(std::string path);
	void process_node(aiNode* node, const aiScene* scene);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> load_material_textures(aiMaterial* material, aiTextureType type, int type_name);
	unsigned int texture_from_file(const char* path, const std::string& directory, int enum_type);
	// returns -1 if the texture has not been loaded, and the index of the texture in loaded_textures otherwise
	int index_of_loaded_texture(const char* path);
};
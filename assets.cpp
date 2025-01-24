#include "assets.hpp"



std::vector<const char*>ModelNames;
std::vector<Model>Models;

int AddModel(const char* ModelName) {
	for (int i = 0; i < ModelNames.size(); i++) {
		if(ModelNames[i] == ModelName) {
			return i;
	}	}
	ModelNames.push_back(ModelName);
	Models.push_back(LoadModel(ModelName));
	return Models.size() - 1;
}



std::vector<const char*>TextureNames;
std::vector<Texture>Textures;

int AddTexture(const char* TextureName) {
	for (int i = 0; i < TextureNames.size(); i++) {
		if (TextureNames[i] == TextureName) {
			return i;
	}	}
	TextureNames.push_back(TextureName);
	Textures.push_back(LoadTexture(TextureName));
	return Textures.size() - 1;
}
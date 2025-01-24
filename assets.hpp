#pragma once
#include "global.hpp"



extern std::vector<const char*>ModelNames;
extern std::vector<Model>Models;

int AddModel(const char* ModelName);



extern std::vector<const char*>TextureNames;
extern std::vector<Texture>Textures;

int AddTexture(const char* TextureName);
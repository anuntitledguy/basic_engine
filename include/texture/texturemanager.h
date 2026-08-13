#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <iostream>

#include "raylib.h"

class TextureManager
{
	public:
		TextureManager();
		virtual ~TextureManager();
		void Load(const std::string& id, const std::string& path);
		Texture2D& Get(const std::string& id);
		
		void Unload();
		void UnloadTextureFromManager(const std::string& id);
	
	private:
		std::map<std::string, Texture2D> m_textures;

};
#endif

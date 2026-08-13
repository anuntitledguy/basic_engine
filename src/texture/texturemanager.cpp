#include "texture/texturemanager.h"

TextureManager::TextureManager()
{
	std::cout<<"texture manager created"<<std::endl;
}

TextureManager::~TextureManager()
{

}

void TextureManager::Load(const std::string& id, const std::string& path)
{
	m_textures[id] = LoadTexture(path.c_str());
	std::cout<<"texture manager loaded"<<std::endl;
}

Texture2D& TextureManager::Get(const std::string& id)
{
	auto it = m_textures.find(id);

    if (it == m_textures.end())
    {
        throw std::runtime_error("Texture '" + id + "' not found.");
    }
    std::cout<<"texture charged"<<std::endl;
    return it->second;
}

void TextureManager::UnloadTextureFromManager(const std::string& id)
{
    auto it = m_textures.find(id);

    if (it == m_textures.end())
    {
        throw std::runtime_error("Texture '" + id + "' not found for unloading.");
    }
    
    else
    {
	UnloadTexture(it->second);
	m_textures.erase(it->first);
    }
}

void TextureManager::Unload()
{
	for (auto& [id, texture] : m_textures)
    {
        UnloadTexture(texture);
    }

    m_textures.clear();
}

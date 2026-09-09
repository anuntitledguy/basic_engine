#include "sound/soundmanager.h"

#include <iostream>

SoundManager::SoundManager()
{
	std::cout<<"sound manager created"<<std::endl;
}

SoundManager::~SoundManager()
{
	Unload();
}

void SoundManager::LoadSoundToManager(const std::string id, const std::string& path)
{
	auto it=m_sound.find(id);
	
	if(it==m_sound.end())
	{
		m_sound[id]=LoadSound(path.c_str());
	}
	
	else
	{
		throw std::runtime_error("Sound '" + id + "' already exists."); 
	}
}

Sound SoundManager::GetSound(const std::string id)
{
	auto it=m_sound.find(id);
	
	if(it==m_sound.end())
	{
		throw std::runtime_error("Sound '" + id + " doesn't exist.");
	}
	std::cout<<"sound charged"<<std::endl;
	return it->second;
}

void SoundManager::UnloadSoundFromManager(const std::string id)
{
	auto it=m_sound.find(id);
	
	if(it==m_sound.end())
	{
		throw std::runtime_error("Sound '" + id + "'doesn't exist.");
	}
	
	else
	{
		UnloadSound(it->second);
		m_sound.erase(it->first);
	}
}
		
void SoundManager::LoadMusicToManager(const std::string id, const std::string& path)
{
	auto it=m_music.find(id);
	
	if(it==m_music.end())
	{
		m_music[id]=LoadMusicStream(path.c_str());
	}
	
	else
	{
		throw std::runtime_error("Music '" + id + "' already exists");
	}
}

Music SoundManager::GetMusic(const std::string id)
{
	auto it=m_music.find(id);
	
	if(it==m_music.end())
	{
		throw std::runtime_error("Music '" + id +"' doesn't exist");
	}
		std::cout<<"music charged"<<std::endl;
		return it->second;
}

void SoundManager::UnloadMusicFromManager(const std::string id)
{
	auto it=m_music.find(id);
	
	if(it==m_music.end())
	{
		std::cout<<"Music '" + id + "' doesn't exist"<<std::endl;
	}
	
	else
	{
		UnloadMusicStream(it->second);
		m_music.erase(it->first);
	}
}
		
void SoundManager::Unload()
{
	for(auto& it : m_sound)
	{
		UnloadSound(it.second);
	}
	
	for(auto& it : m_music)
	{
		UnloadMusicStream(it.second);
	}
	
	m_sound.clear();
	m_music.clear();
}

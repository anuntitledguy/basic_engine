#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "raylib.h"

#include <string>
#include <map>

class SoundManager
{
	public:
		SoundManager();
		virtual ~SoundManager();
		void LoadSoundToManager(const std::string id, const std::string& path);
		Sound GetSound(const std::string id);
		void UnloadSoundFromManager(const std::string id);
		
		void LoadMusicToManager(const std::string id, const std::string& path);
		Music GetMusic(const std::string id);
		void UnloadMusicFromManager(const std::string id);
		
		void Unload();
	
	private:
		std::map<std::string,Sound> m_sound;
		std::map<std::string,Music> m_music;
};
#endif

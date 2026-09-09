#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

class SoundEmitter
{
	public:
		virtual ~SoundEmitter()=default;
		void Play(const std::string& id);
	
	private:
		SoundManager& m_soundManager;
	
};
#endif

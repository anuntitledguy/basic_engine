#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <map>
#include <string>
#include <memory>

class GameScene;
class TextureManager;
class SoundManager;
class InputHandler;

class SceneManager
	{
		public:
			SceneManager(TextureManager& textureManager, SoundManager& soundManager, InputHandler& inputHandler);
			virtual ~SceneManager();
			
			void LoadScene(const std::string scene_ID /*info pour construire la scene*/);
			void UnloadScene(const std::string scene_ID);
			
			void UnloadSceneManager();
						
			void ChangeScene(const std::string scene_ID);
			
			void Update(double dt);
			void Draw();
		
		private:
			std::map<std::string, std::unique_ptr<GameScene>> m_scene;
			std::string m_activeScene;
			
			TextureManager& m_textureManager;
			SoundManager& m_soundManager;
			InputHandler& m_inputHandler;
			
	};

#endif

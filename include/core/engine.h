#ifndef ENGINE_H
#define ENGINE_H

#define SCREENX 800
#define SCREENY 450

#include "core/scenemanager.h"
#include "input/inputhandler.h"
#include "texture/texturemanager.h"

#include <iostream>

class Engine
	{
		public:
			Engine();
			virtual ~Engine();
			
			void Init();
			void Run();
			void ShutDown();
			
			static constexpr double FPS = 60.0;
			static constexpr double MS_FPS = FPS/1000;
		
			
		private:
			TextureManager m_textureManager;
			InputHandler m_inputHandler;
			SceneManager m_sceneManager;
			
			//Gameloop parameter
			 
			 float m_deltaTime;
			 float m_previousTime;
			 float m_currentTime;
			  
			 //End Gameloop parameter
	};

#endif

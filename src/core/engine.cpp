#include "core/engine.h"

#include "raylib.h"

#include <iostream>

Engine::Engine()
:m_textureManager(),
m_inputHandler(),
m_sceneManager(m_textureManager,m_inputHandler)
{
	this->m_previousTime=0;
	this->m_currentTime=0;
	this->m_deltaTime=0;
}

Engine::~Engine()
{
	
}

void Engine::Init()
{
	InitWindow(SCREENX, SCREENY, "Raylib sur Raspberry Pi");
	
	this->m_previousTime=0;
	this->m_currentTime=GetTime();
	this->m_deltaTime=0;
	
	/*=============lOAD SCENE=============*/
	this->m_sceneManager.LoadScene("scene_test_1");
	//this->m_sceneManager.LoadScene("scene_test_2");
	this->m_sceneManager.ChangeScene("scene_test_1");
	
	/*=============END lOAD SCENE=============*/
}

void Engine::Run()
{
	this->m_previousTime=GetTime();
	
	while (!WindowShouldClose())
    {
		//Input
		this->m_inputHandler.HandleInput();
		
		this->m_currentTime=GetTime();
		double elapse=this->m_currentTime-this->m_previousTime;	
		
		this->m_previousTime=this->m_currentTime;
		this->m_deltaTime+=elapse;
		
		while(this->m_deltaTime>=MS_FPS)
		{
			this->m_sceneManager.Update(this->m_deltaTime);
			this->m_deltaTime-=MS_FPS;
		}
		
		this->m_sceneManager.Draw();
    }
}

void Engine::ShutDown()
{
	m_sceneManager.UnloadSceneManager();
	m_inputHandler.Unload();
	m_textureManager.Unload();
	CloseWindow();
}

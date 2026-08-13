#include "core/scenemanager.h"
#include "texture/texturemanager.h"
#include "core/gameScene.h"

#include <iostream>


SceneManager::SceneManager(TextureManager& textureManager, InputHandler& inputHandler)
:m_textureManager(textureManager),
m_inputHandler(inputHandler)
{
    std::cout << "sceneManager created\n";
}


SceneManager::~SceneManager()
{
 
}


void SceneManager::LoadScene(const std::string scene_ID)
{
    std::cout << "load scene\n";

    m_scene[scene_ID] = std::make_unique<GameScene>(m_textureManager, m_inputHandler);
    auto it = m_scene.find(scene_ID);

    if(it != m_scene.end())
    {
        m_scene[scene_ID]->Load();
    }
    
    else
    {
        std::cout << scene_ID<<" not loaded\n";
    }
}

void SceneManager::UnloadSceneManager()
{
    for(auto& scene : m_scene)
    {
        scene.second->Unload();
    }

    std::cout << "sceneManager destroy\n";
}

void SceneManager::UnloadScene(const std::string scene_ID)
{
    auto it = m_scene.find(scene_ID);

    if(it != m_scene.end())
    {
        it->second->Unload();
        m_scene.erase(it);
    }
}

void SceneManager::ChangeScene(const std::string scene_ID)
{
	//si besoin de mettre en pause la scene, ici
	m_activeScene=scene_ID;
}

void SceneManager::Update(double dt)
{
    auto it = m_scene.find(m_activeScene);

    if (it != m_scene.end())
    {
        it->second->Update(dt);
    }
    
    else
    {
        std::cout<<"scene Update impossible, unactive or inexistant"<<std::endl;
    }
}

void SceneManager::Draw()
{
    auto it = m_scene.find(m_activeScene);

    if (it != m_scene.end())
    {
        it->second->Draw();
    }
    
    else
    {
        std::cout<<"scene Draw impossible, unactive or inexistant"<<std::endl;
    }
}

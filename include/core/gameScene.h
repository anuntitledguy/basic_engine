#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "level/tilemap.h"
#include "object/gameobject.h"
#include "texture/texturemanager.h"
#include "level/mycamera.h"
#include "physic/collisionhandler.h"

#include "raylib.h"

#include <iostream>

class InputHandler;
class TextureManager;

class GameScene
{
	public:
		GameScene(TextureManager& textureManager, InputHandler& inputHandler);
		~GameScene();
		
		void Load();
		void Unload();
		
		void Update(double dt);
		void Draw();
		
		void CreateObject();
		void DestroyObject(std::string id);
		
	private:
		TextureManager& m_textureManager;
		InputHandler& m_inputHandler;
		
		std::string m_id;
		
		TileMap m_map;
		Mycamera m_camera;
		CollisionHandler m_collisionHandler;
		
		std::map<std::string, GameObject> m_object;
		
	
};
#endif

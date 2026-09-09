#include "core/gameScene.h"

#include "input/inputhandler.h"
#include "input/movecommand.h"
#include "input/action.h"
#include "input/direction.h"


#include "level/tilelayer.h"
#include "level/tileset.h"
#include "level/layer.h"

#include "texture/animelabel.h"

#include "sound/soundmanager.h"

#include "object/player.h"
#include "object/playeridlstate.h"
#include "object/playermovestate.h"



#include <memory>

GameScene::GameScene(TextureManager& textureManager, SoundManager& soundManager, InputHandler& inputHandler)
:m_textureManager(textureManager),
m_soundManager(soundManager),
m_inputHandler(inputHandler),
m_map("test")
{
    m_id="scene test";
    std::cout<<"GameScene created"<<std::endl;
}

GameScene::~GameScene()
{
	std::cout<<"GameScene destroyed"<<std::endl;
}

void GameScene::Load()
{
	std::cout<<"gamescene load"<<std::endl;
	
	/* =================== TEXTURE LOAD =================== */
	m_textureManager.Load("character_idle", "asset/texture//Enemies/MiniGolem/Idle.png");
	m_textureManager.Load("character_walk", "asset/texture//Enemies/MiniGolem/Chasing.png");
	
	m_textureManager.Load("floor", "asset/texture/Tileset/tile_set_top-down_test.png");
	m_textureManager.Load("decor", "asset/texture/Tileset/decor_top_down_test.png");
	/* =================== END TEXTURE LOAD =================== */
	
	/* =================== SOUND/MUSIC LOAD =================== */
	
	
	/* =================== END SOUND/MUSIC LOAD =================== */

	/* =================== MAP LOAD =================== */
	m_map.LoadLayer("scene_test_1_floor",m_textureManager.Get("floor"), LAYER::FLOOR,
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 26, 3, 3, 24, 32, 25, 3, 3, 3, 28, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 7, 7, 7, 7, 7, 8, 2, 21, 30, 3, 3, 28, 2, 31, 25, 3, 3, 28, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 2, 2, 2, 2, 2, 13, 2, 26, 3, 3, 3, 29, 23, 2, 26, 3, 3, 28, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 2, 2, 2, 2, 2, 13, 2, 31, 25, 3, 3, 3, 29, 22, 30, 3, 3, 28, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 2, 2, 2, 2, 2, 13, 2, 2, 26, 3, 3, 3, 3, 3, 3, 3, 24, 33, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 16, 17, 2, 2, 2, 17, 18, 2, 2, 31, 25, 3, 3, 3, 3, 3, 3, 28, 2, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 31, 25, 3, 3, 3, 3, 3, 28, 2, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 26, 3, 3, 3, 3, 24, 33, 2, 41, 42,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 31, 32, 25, 24, 32, 33, 2, 41, 50, 4,
            22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 30, 28, 2, 41, 42, 50, 4, 4,
            32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 2, 46, 4, 4, 4, 4,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 41, 42, 42, 42, 42, 43, 2, 2, 2, 2, 41, 42, 42, 50, 4, 4, 4, 4,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 41, 50, 4, 4, 4, 4, 49, 42, 43, 2, 41, 50, 4, 4, 4, 4, 4, 4, 4,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 41, 50, 4, 4, 4, 4, 4, 4, 4, 49, 42, 50, 4, 4, 4, 4, 4, 4, 4, 4,
            2, 2, 2, 2, 2, 2, 2, 2, 41, 42, 50, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            2, 2, 2, 2, 2, 2, 2, 2, 46, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            2, 2, 2, 2, 2, 2, 2, 2, 46, 4, 4, 4, 4, 44, 52, 45, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            2, 2, 2, 2, 2, 2, 41, 42, 50, 4, 4, 4, 44, 53, 2, 51, 52, 45, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            2, 2, 2, 2, 2, 2, 46, 4, 4, 4, 4, 44, 2, 21, 22, 22, 23, 51, 45, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            2, 2, 2, 2, 2, 2, 46, 4, 4, 4, 4, 48, 2, 26, 27, 27, 28, 2, 46, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
	    
	    30, 20, 16, 16, 5, 11,1);
	
	m_map.LoadLayer("scene_test_1_decor",m_textureManager.Get("decor"), LAYER::DECOR,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 82, 0, 0, 0, 0, 71, 0, 0, 0, 0, 86, 87, 88, 89,
            0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92, 93, 94, 95,
            0, 0, 0, 0, 0, 0, 81, 0, 0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 98, 99, 100, 101,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 74, 75, 0, 0, 0, 0, 0, 104, 105, 106, 107,
            0, 0, 0, 0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 111, 112, 113,
            0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 76, 0, 0, 81, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 76, 0, 0, 0, 77, 0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 70, 0, 81, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 82, 0, 81, 0, 0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 86, 87, 88, 89, 0, 0, 0, 0, 0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 92, 93, 94, 95, 0, 0, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 84, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 98, 99, 100, 101, 82, 0, 0, 0, 0, 0, 0, 0, 0, 58, 0, 0, 84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 104, 105, 106, 107, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 84, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 110, 111, 112, 113, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 84, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    
	    30, 20, 16, 16, 6, 10,56);
	    
	    m_map.LoadLayer("scene_test_1_collision",m_textureManager.Get("decor"), LAYER::COLLISION,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2,
            0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	    
	    30, 20, 16, 16, 6, 10,0);
	    
	/* =================== END MAP LOAD =================== */
	
	CreateObject();
	
	/* =================== INPUT CREATION =================== */
	m_inputHandler.BindCommand(Action::MoveRight, std::make_unique<MoveCommand>(*m_object.at("player"), Direction::RIGHT));
	m_inputHandler.BindCommand(Action::MoveLeft, std::make_unique<MoveCommand>(*m_object.at("player"), Direction::LEFT));
	m_inputHandler.BindCommand(Action::MoveUp, std::make_unique<MoveCommand>(*m_object.at("player"), Direction::UP));
	m_inputHandler.BindCommand(Action::MoveDown, std::make_unique<MoveCommand>(*m_object.at("player"), Direction::DOWN));
	/* =================== END INPUT CREATION =================== */
	
	m_camera.Initialize(*m_object.at("player"), (Vector2){ (float)(GetScreenWidth())/2.0f, (float)(GetScreenHeight())/2.0f }, 0, 1);
}

void GameScene::Unload()
{
    //GameObject
    
    m_map.Unload();
    
    m_inputHandler.UnloadCommand(Action::MoveRight);
    m_inputHandler.UnloadCommand(Action::MoveLeft);
    m_inputHandler.UnloadCommand(Action::MoveUp);
    m_inputHandler.UnloadCommand(Action::MoveDown);
    
    m_textureManager.UnloadTextureFromManager("character_idle");
    m_textureManager.UnloadTextureFromManager("character_walk");
    m_textureManager.UnloadTextureFromManager("floor");
}
		
void GameScene::Update(double dt)
{
    for(auto& object : m_object)
    {
	object.second->Update(dt);
    }
    
    /*===================== COLLISION SOLVER ====================*/
     
    //m_collisionHandler.CollisionSolverObj(m_object.at("player"),m_object.at("autre"), dt);
    m_collisionHandler.CollisionSolverMap(*m_object.at("player"),m_map, dt);
    
    /*===================== END COLLISION SOLVER ====================*/
    
    
    m_camera.Update();
}

void GameScene::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    m_camera.BeginDraw();

    m_map.Draw();
    
    for(auto& object : m_object)
    {
	object.second->Draw();
    }
    
    m_camera.EndDraw();
    EndDrawing();
}

void GameScene::CreateObject(/*id du fichier a parcer*/)
{
    m_object.emplace("player",std::make_unique<Player>("player",(Vector2){0.0f,100.0f}, 16, 16));
    m_object.at("player")->Init(m_textureManager);
    //m_object.emplace("autre",GameObject("autre",(Vector2){100.0f,100.0f}, 32, 32));
    
    //m_object.at("autre").AddAnimation(ANIMELABEL::NOANIMATION, "other_walkright", m_textureManager.Get("player"), 0, 0, 64, 64, 4, 2);
}

void GameScene::DestroyObject(std::string id)
{
    
}
		

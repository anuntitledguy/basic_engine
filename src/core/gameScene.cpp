#include "core/gameScene.h"

#include "input/inputhandler.h"
#include "input/movecommand.h"
#include "input/action.h"
#include "input/direction.h"


#include "level/tilelayer.h"
#include "level/tileset.h"
#include "level/layer.h"

#include "texture/animelabel.h"


#include <memory>

GameScene::GameScene(TextureManager& textureManager, InputHandler& inputHandler)
:m_textureManager(textureManager),
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
	m_textureManager.Load("player", "asset/texture_2/Char_001.png");
	m_textureManager.Load("layerDecor", "asset/texture/FloorTiles1.png");
	/* =================== END TEXTURE LOAD =================== */

	/* =================== MAP LOAD =================== */
	m_map.LoadMap("scene_test_1","asset/map/test_2.json",m_textureManager.Get("layerDecor"));
	/*m_map.LoadLayer("scene_test_1_decor", LAYER::DECOR, {13, 13, 29, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
            13, 13, 29, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
            13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
            13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
            13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
            13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
            2, 3, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 29,
            11, 33, 3, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 29, 32,
            11, 11, 33, 3, 13, 13, 13, 13, 13, 13, 13, 13, 13, 29, 32, 11,
            11, 11, 11, 33, 2, 2, 2, 2, 2, 2, 2, 2, 2, 32, 11, 11},16,10, m_textureManager.Get("layerDecor"),32,32,9,18);
	    
	m_map.LoadLayer("scene_test_1_collision", LAYER::COLLISION, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
            1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},16,10, m_textureManager.Get("layerDecor"),32,32,9,18);*/
	    
	/* =================== END MAP LOAD =================== */
	
	CreateObject();
	
	/* =================== INPUT CREATION =================== */
	m_inputHandler.BindCommand(Action::MoveRight, std::make_unique<MoveCommand>(m_object.at("player"), Direction::RIGHT));
	m_inputHandler.BindCommand(Action::MoveLeft, std::make_unique<MoveCommand>(m_object.at("player"), Direction::LEFT));
	m_inputHandler.BindCommand(Action::MoveUp, std::make_unique<MoveCommand>(m_object.at("player"), Direction::UP));
	m_inputHandler.BindCommand(Action::MoveDown, std::make_unique<MoveCommand>(m_object.at("player"), Direction::DOWN));
	/* =================== END INPUT CREATION =================== */
	
	m_camera.Initialize(m_object.at("player"), (Vector2){ (float)(GetScreenWidth())/2.0f, (float)(GetScreenHeight())/2.0f }, 0, 1);
}

void GameScene::Unload()
{
    //GameObject
    
    m_map.Unload();
    
    m_inputHandler.UnloadCommand(Action::MoveRight);
    m_inputHandler.UnloadCommand(Action::MoveLeft);
    m_inputHandler.UnloadCommand(Action::MoveUp);
    m_inputHandler.UnloadCommand(Action::MoveDown);
    
    m_textureManager.UnloadTextureFromManager("player");
    m_textureManager.UnloadTextureFromManager("layerDecor");
}
		
void GameScene::Update(double dt)
{
    for(auto& object : m_object)
    {
	object.second.Update(dt);
    }
    
    /*===================== COLLISION SOLVER ====================*/
     
    m_collisionHandler.CollisionSolverObj(m_object.at("player"),m_object.at("autre"), dt);
    m_collisionHandler.CollisionSolverMap(m_object.at("player"),m_map, dt);
    
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
	//object.second.Draw();
	DrawRectangle(object.second.GetPosX(),object.second.GetPosY(), 32, 32, BLUE);
    }
    
    m_camera.EndDraw();
    EndDrawing();
}

void GameScene::CreateObject(/*id du fichier a parcer*/)
{
    m_object.emplace("player",GameObject("player",(Vector2){0.0f,100.0f}, 32, 32));
    m_object.emplace("autre",GameObject("autre",(Vector2){100.0f,100.0f}, 32, 32));

    m_object.at("player").AddAnimation(ANIMELABEL::NOANIMATION, "player_walkright",m_textureManager.Get("player"), 0, 48, 24, 24, 4, 2);
    m_object.at("player").AddAnimation(ANIMELABEL::WALKRIGHT, "player_walkright",m_textureManager.Get("player"), 0, 48, 24, 24, 4, 2);
    m_object.at("player").AddAnimation(ANIMELABEL::WALKLEFT, "player_walkleft",m_textureManager.Get("player"), 0, 24, 24, 24, 4, 2);
    m_object.at("autre").AddAnimation(ANIMELABEL::NOANIMATION, "other_walkright", m_textureManager.Get("player"), 0, 0, 64, 64, 4, 2);
}

void GameScene::DestroyObject(std::string id)
{
    
}
		

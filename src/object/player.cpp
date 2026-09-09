#include "object/player.h"

#include "object/playeridlstate.h"
#include "object/playermovestate.h"

#include "texture/texturemanager.h"
#include "texture/animelabel.h"

#include "core/stateid.h"

#include <memory>

Player::Player(std::string ID, const Vector2 pos, const int width, const int height)
:GameObject(ID, pos, width, height),
m_state(this)
{
	m_state.CreateState(STATEID::IDL,std::make_unique<PlayerIdlState>(ANIMELABEL::IDL));
	m_state.CreateState(STATEID::MOVE,std::make_unique<PlayerMoveState>(ANIMELABEL::MOVE));
}

void Player::Init(TextureManager& texturemanager)
{
	AddAnimation(ANIMELABEL::IDL, "player_idl",texturemanager.Get("character_idle"), 0, 0, 16, 16, 4, 4);
    AddAnimation(ANIMELABEL::MOVE, "player_walk",texturemanager.Get("character_walk"), 0, 0, 16, 16, 4, 4);
	m_state.ChangeState(STATEID::IDL);
}


void Player::Update(double dt)
{
	this->m_state.Update(dt);
	
	
	m_sprite.at(m_currentAnimation)->Update(dt);
}

void Player::Draw()
{
	m_sprite.at(m_currentAnimation)->Draw(m_pos.x, m_pos.y, WHITE);
}

void Player::ChangeState(const STATEID newstate)
{
	m_state.ChangeState(newstate);
}

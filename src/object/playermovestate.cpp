#include "object/playermovestate.h"

#include "object/player.h"

PlayerMoveState::PlayerMoveState(const ANIMELABEL anime)
{
	m_animation=anime;
}

void PlayerMoveState::Update(Player* player, double dt)
{
	if(player->GetVelocity().x==0 && player->GetVelocity().y==0)
	{
		player->ChangeState(STATEID::IDL);
	}
}

void PlayerMoveState::Enter(Player* player)
{
	//Change animation
	player->ChangeAnimation(m_animation);
}

void PlayerMoveState::Exit(Player* player)
{
	std::cout<<"Exit from MoveState"<<std::endl;
}

void PlayerMoveState::Pause(Player* player)
{
	
}

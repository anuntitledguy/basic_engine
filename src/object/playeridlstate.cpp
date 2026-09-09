#include "object/playeridlstate.h"

#include "object/player.h"

PlayerIdlState::PlayerIdlState(const ANIMELABEL anime)
{
	m_animation=anime;
}

void PlayerIdlState::Update(Player* player, double dt)
{
	if(player->GetVelocity().x!=0 || player->GetVelocity().y!=0)
	{
		player->ChangeState(STATEID::MOVE);
	}	
}


void PlayerIdlState::Enter(Player* player)
{
	//Change animation
	player->ChangeAnimation(m_animation);
}

void PlayerIdlState::Exit(Player* player)
{
	std::cout<<"Exit from IdlState"<<std::endl;
}

void PlayerIdlState::Pause(Player* player)
{
	
}

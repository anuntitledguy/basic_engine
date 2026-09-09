#ifndef PLAYERMOVESTATE_H
#define PLAYERMOVESTATE_H

#include "core/state.h"
#include "object/player.h"

#include "texture/animelabel.h"

#include <memory>

class PlayerMoveState : public State<Player>
{
	public:
		PlayerMoveState(const ANIMELABEL animlabel);
		virtual ~PlayerMoveState()=default;
		
		void Update(Player* player, double dt) override;
		//void Draw(Player* player) override;
		
		void Enter(Player* player) override;
		void Exit(Player* player) override;
		void Pause(Player* player) override;
	
	private:
		ANIMELABEL m_animation;
	
};
#endif

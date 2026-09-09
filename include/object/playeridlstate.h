#ifndef PLAYERIDLSTATE_H
#define PLAYERIDLSTATE_H

#include "core/state.h"
#include "object/player.h"

#include "texture/animelabel.h"

#include <memory>

class PlayerIdlState : public State<Player>
{
	public:
		PlayerIdlState(const ANIMELABEL animlabel);
		virtual ~PlayerIdlState()=default;
		
		void Update(Player* player, double dt) override;
		//void Draw(Player* player) override;
		
		void Enter(Player* player) override;
		void Exit(Player* player) override;
		void Pause(Player* player) override;
	
	private:
		ANIMELABEL m_animation;
	
};
#endif

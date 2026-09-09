#ifndef PLAYER_H
#define PLAYER_H

#include "object/gameobject.h"
#include "core/statemachine.h"

enum class STATEID;

class TextureManager;

class Player : public GameObject
{
	public:
		Player(std::string ID, const Vector2 pos, const int width, const int height);
		virtual ~Player()=default;
		
		void Update(double dt) override;
		void Draw() override;
		
		virtual void Init(TextureManager& texturemanager) override;
		
		void ChangeState(const STATEID newstate);
	
	private:
		StateMachine<Player> m_state;	
};
#endif

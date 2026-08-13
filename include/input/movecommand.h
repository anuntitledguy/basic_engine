#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "input/command.h"

#include <iostream>

class GameObject;
enum class Direction;

class MoveCommand: public Command
{
	public:
		MoveCommand(GameObject& player, Direction dir);
		virtual ~MoveCommand()=default;
		
		void Execute() override;
		
	private:
		GameObject& m_player;
		Direction m_direction;
};
#endif

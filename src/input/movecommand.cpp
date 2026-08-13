#include "input/movecommand.h"

#include "object/gameobject.h"
#include "input/direction.h"

MoveCommand::MoveCommand(GameObject& player, Direction dir)
:m_player(player), m_direction(dir)
{
	
}


void MoveCommand::Execute()
{
	this->m_player.Move(m_direction);
}

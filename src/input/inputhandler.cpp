#include "input/inputhandler.h"

#include "input/movecommand.h"
#include "input/action.h"

#include "object/gameobject.h"

#include "raylib.h"

#include <iostream>


InputHandler::InputHandler()
{
    std::cout<<"inputHandler created"<<std::endl;
}

InputHandler::~InputHandler()
{

}

void InputHandler::BindCommand(Action id, std::unique_ptr<Command> command)
{
	auto it = m_input.find(id);

    if(it != m_input.end())
    {
        std::cout << "Command already exists\n";
        return;
    }

    m_input[id] = std::move(command);
}

void InputHandler::UnloadCommand(Action id)
{
    auto it = m_input.find(id);

    if(it != m_input.end())
    {
        m_input.erase(id);
        return;
    }
    
    else
    {
        std::cout << "Command doesn't exist\n";
        return;
    }
}

void InputHandler::Unload()
{
    m_input.clear();
}

void InputHandler::HandleInput()
{
	//tres sensible a la casse, utiliser un enum
    if (IsKeyDown(KEY_RIGHT))
    {
	auto it = m_input.find(Action::MoveRight);

        if(it != m_input.end())
            it->second->Execute();
    }

    if (IsKeyDown(KEY_LEFT))
    {
        auto it = m_input.find(Action::MoveLeft);

        if(it != m_input.end())
            it->second->Execute();
    }
    
    if (IsKeyDown(KEY_DOWN))
    {
	auto it = m_input.find(Action::MoveDown);

        if(it != m_input.end())
            it->second->Execute();
    }

    if (IsKeyDown(KEY_UP))
    {
        auto it = m_input.find(Action::MoveUp);

        if(it != m_input.end())
            it->second->Execute();
    }
}

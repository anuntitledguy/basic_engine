#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <map>
#include <memory>
#include <string>

class Command;
enum class Action;

class InputHandler
{
	public:
		InputHandler();
		virtual ~InputHandler();
		
		void Unload();
		
		void BindCommand(Action id, std::unique_ptr<Command> command);
		void UnloadCommand(Action id);
		void HandleInput();
		
	private:
		std::map<Action, std::unique_ptr<Command>> m_input;
			
};

#endif

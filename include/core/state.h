#ifndef STATE_H
#define STATE_H

#include <iostream>

template <typename T>

class State
{
	public:
		State()=default;
		
		~State()=default;
		virtual void Enter(T* owner)=0;
		virtual void Exit(T* owner)=0;
		virtual void Pause(T* owner)=0;
		
		virtual void Update(T* owner, double dt)=0;
		//virtual void Draw(T* owner)=0;

	
};
#endif

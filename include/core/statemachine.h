#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>

#include "core/state.h"
#include "core/stateid.h"

#include <memory>


template <typename T>
class StateMachine
{
	public:
		StateMachine(T* own):
		m_owner(own), 
		m_currentState(STATEID::DEFAULT) 
		{
			
		}
		
		virtual ~StateMachine() 
		{
			m_state.clear(); 
		}
		
		//creation de state dans la map
		void CreateState(STATEID id, std::unique_ptr<State<T>> newState)
		{
			if(m_state.find(id) != m_state.end())
			{
				std::cout << "State already exists\n";
				return;
			}
			m_state.emplace(id, std::move(newState));
		}
		
		void DeleteState(STATEID id)
		{
			auto it = m_state.find(id);
			if (it != m_state.end())
			{
				if (m_currentState == id) {
					m_state[m_currentState]->Exit(m_owner);
					m_currentState = STATEID::DEFAULT;
				}
				m_state.erase(it);
			}
			else
			{
				std::cout << "State doesn't exist\n";
			}
		}
		
		void ChangeState(STATEID newState)
		{
			if(m_state.find(m_currentState) != m_state.end() && m_state[m_currentState])
			{
				m_state[m_currentState]->Exit(m_owner);
			}
			
			m_currentState = newState;
			
			if(m_state.find(m_currentState) != m_state.end() && m_state[m_currentState])
			{
				m_state[m_currentState]->Enter(m_owner);
			}
		}
		
		//Mise a jour de la state actuelle
		void Update(double dt)
		{	
			if(m_state.find(m_currentState) != m_state.end() && m_state[m_currentState])
			{
				m_state[m_currentState]->Update(m_owner, dt);
			}
		}

		//Affichage de la state actuelle
		void Draw()
		{
			if(m_state.find(m_currentState) != m_state.end() && m_state[m_currentState])
			{
				m_state[m_currentState]->Draw(m_owner);
			}
		}
		
		State<T>* GetCurrentState() 
		{
			auto it = m_state.find(m_currentState);
			return (it != m_state.end()) ? it->second.get() : nullptr;
		}
    
    private:
    T* m_owner;
    std::map<STATEID, std::unique_ptr<State<T>>> m_state;
    STATEID m_currentState;
};
#endif

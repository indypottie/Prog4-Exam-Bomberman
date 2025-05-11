//---------------------------
// Include Files
//---------------------------
#include "PlayerStateMachine.h"

#include "States.h"


//---------------------------
// Member functions
//---------------------------

void PlayerStateMachine::SetState(std::unique_ptr<IPlayerState> newState, dae::GameObject& player)
{
	if (m_CurrentPlayerStatePtr)
	{
		m_CurrentPlayerStatePtr->Exit(player);
	}

	m_CurrentPlayerStatePtr = std::move(newState);

	if (m_CurrentPlayerStatePtr)
	{
		m_CurrentPlayerStatePtr->Enter(player);
	}
}

IPlayerState* PlayerStateMachine::GetCurrentState() const
{
	return m_CurrentPlayerStatePtr.get();
}

void PlayerStateMachine::Update(dae::GameObject& player)
{
	if (m_CurrentPlayerStatePtr)
	{
		m_CurrentPlayerStatePtr->Update(player);
	}
}

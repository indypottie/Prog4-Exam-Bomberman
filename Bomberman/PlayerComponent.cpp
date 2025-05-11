//---------------------------
// Include Files
//---------------------------
#include "PlayerComponent.h"

#include "PlayerStateMachine.h"

//---------------------------
// Constructor & Destructor
//---------------------------

//---------------------------
// Member functions
//---------------------------

PlayerComponent::PlayerComponent(dae::GameObject& owner, int playerIdx) : Component(owner), m_PlayerIdx(playerIdx)
{
	m_PlayerStateMachinePtr = std::make_unique<StateMachine<dae::GameObject, IPlayerState>>();
}

void PlayerComponent::Update()
{
	m_PlayerStateMachinePtr->Update(*GetOwner());
}

void PlayerComponent::SetState(std::unique_ptr<IPlayerState> newState)
{
	m_PlayerStateMachinePtr->SetState(std::move(newState), *GetOwner());
}

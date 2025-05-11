#pragma once


//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <memory>

#include "Component.h"
#include "States.h"
#include "StateMachine.h"

//-----------------------------------------------------
// PlayerComponent Class									 
//-----------------------------------------------------
class PlayerComponent final : public Component
{
public:
	 PlayerComponent(dae::GameObject& owner ,int playerIdx); // Constructor
	~PlayerComponent() override = default; // Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	PlayerComponent(const PlayerComponent& other)					= delete;
	PlayerComponent(PlayerComponent&& other) noexcept				= delete;
	PlayerComponent& operator=(const PlayerComponent& other)		= delete;
	PlayerComponent& operator=(PlayerComponent&& other) noexcept	= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	void Update() override;

	void SetState(std::unique_ptr<IPlayerState> newState);

	int GetPlayerIndex() const { return m_PlayerIdx; }

private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	int m_PlayerIdx{ 0 };

	std::unique_ptr<StateMachine<dae::GameObject, IPlayerState>> m_PlayerStateMachinePtr;
};

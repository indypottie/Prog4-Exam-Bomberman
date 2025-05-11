#pragma once
#include <memory>

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------


namespace dae
{
	class GameObject;
}

class IPlayerState;
//-----------------------------------------------------
// PlayerStateMachine Class									 
//-----------------------------------------------------
class PlayerStateMachine final
{
public:
	PlayerStateMachine() = default; // Constructor
	~PlayerStateMachine() = default; // Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	PlayerStateMachine(const PlayerStateMachine& other)						= delete;
	PlayerStateMachine(PlayerStateMachine&& other) noexcept					= delete;
	PlayerStateMachine& operator=(const PlayerStateMachine& other)			= delete;
	PlayerStateMachine& operator=(PlayerStateMachine&& other) noexcept		= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void SetState(std::unique_ptr<IPlayerState> newState, dae::GameObject& player);
	IPlayerState* GetCurrentState() const;

	void Update(dae::GameObject& player);


private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	std::unique_ptr<IPlayerState> m_CurrentPlayerStatePtr;
};

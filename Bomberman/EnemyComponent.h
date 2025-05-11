#pragma once
#include "Component.h"
#include "States.h"
#include "StateMachine.h"

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

enum class EnemyType
{
	Balloom,
	Oneal,
	Doll,
	Minvo
};

//-----------------------------------------------------
// EnemyComponent Class									 
//-----------------------------------------------------
class EnemyComponent final : public Component
{
public:
	EnemyComponent(dae::GameObject& owner, EnemyType enemyType); // Constructor
	~EnemyComponent() override = default; // Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	EnemyComponent(const EnemyComponent& other)						= delete;
	EnemyComponent(EnemyComponent&& other) noexcept					= delete;
	EnemyComponent& operator=(const EnemyComponent& other)			= delete;
	EnemyComponent& operator=(EnemyComponent&& other) noexcept		= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	void Update() override;

	void OnDeath();

	EnemyType GetType() const { return m_Type; }
	float GetSpeed() const { return m_Speed; }


	void SetState(std::unique_ptr<IEnemyState> newState);
	IEnemyState* GetCurrentState() const { return m_EnemyStateMachinePtr->GetCurrentState(); }

	bool SeesPlayer() const { return m_SeesPlayer; }

	dae::GameObject* GetPlayer() const { return m_PlayerPtr; }

private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	void InitializeEnemy();

	bool HasLineOfSightToPlayer();

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	EnemyType m_Type;
	float m_Speed;

	bool m_SeesPlayer{ false };

	std::unique_ptr<StateMachine<dae::GameObject, IEnemyState>> m_EnemyStateMachinePtr;

	dae::GameObject* m_PlayerPtr{ nullptr };
};

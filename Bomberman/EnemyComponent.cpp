//---------------------------
// Include Files
//---------------------------
#include "EnemyComponent.h"

#include "GameObject.h"
#include "GridComponent.h"
#include "LevelManager.h"
#include "Scene.h"
#include "SceneManager.h"

//---------------------------
// Constructor & Destructor
//---------------------------
EnemyComponent::EnemyComponent(dae::GameObject& owner, EnemyType enemyType) : Component(owner), m_Type(enemyType)
{
	m_EnemyStateMachinePtr = std::make_unique<StateMachine<dae::GameObject, IEnemyState>>();

	InitializeEnemy();
}


//---------------------------
// Member functions
//---------------------------

void EnemyComponent::Update()
{
	m_EnemyStateMachinePtr->Update(*GetOwner());

	// Skip if this enemy type doesn't chase the player
	if (m_Type == EnemyType::Balloom || m_Type == EnemyType::Doll)
		return;

	// Check if the enemy has line of sight to the player
	if (HasLineOfSightToPlayer())
	{
		m_SeesPlayer = true;

		// If not already chasing, switch to chase state
		if (auto* currentState = dynamic_cast<ChaseState*>(GetCurrentState()))
		{
			// Already in chase state, do nothing
			return;
		}
		else
		{
			SetState(std::make_unique<ChaseState>());
		}
	}
	else
	{
		m_SeesPlayer = false;

		// If currently chasing but lost sight, go back to wander state
		if (auto* currentState = dynamic_cast<ChaseState*>(GetCurrentState()))
		{
			SetState(std::make_unique<WanderState>());
		}
	}
}

void EnemyComponent::OnDeath()
{

}

void EnemyComponent::SetState(std::unique_ptr<IEnemyState> newState)
{
    m_EnemyStateMachinePtr->SetState(std::move(newState), *GetOwner());
}

void EnemyComponent::InitializeEnemy()
{
	switch (m_Type)
	{
    case EnemyType::Balloom:
        m_Speed = 50.f;
        break;

    case EnemyType::Oneal:
        m_Speed = 60.f;
        break;

    case EnemyType::Doll:
        m_Speed = 75.f;
        break;

    case EnemyType::Minvo:
        m_Speed = 90.f;
        break;
	}

    // set initial state
    m_EnemyStateMachinePtr->SetState(std::make_unique<WanderState>(), *GetOwner());
}

bool EnemyComponent::HasLineOfSightToPlayer()
{
	auto* grid = LevelManager::GetInstance().GetGrid();
	if (!grid) return false;

	if (!m_PlayerPtr)
	{
		m_PlayerPtr = dae::SceneManager::GetInstance().GetACtiveScene()->FindObjectByTag("Player");
		if (!m_PlayerPtr) return false;
	}

	const float cellSize = grid->GetCellSize();
	auto obj = GetOwner();

	glm::vec2 enemyPos = obj->GetPosition();
	glm::vec2 playerPos = m_PlayerPtr->GetPosition();

	int enemyRow = static_cast<int>(enemyPos.y / cellSize);
	int enemyCol = static_cast<int>(enemyPos.x / cellSize);
	int playerRow = static_cast<int>(playerPos.y / cellSize);
	int playerCol = static_cast<int>(playerPos.x / cellSize);

	if (enemyRow == playerRow)
	{
		int start = std::min(enemyCol, playerCol);
		int end = std::max(enemyCol, playerCol);
		for (int col = start + 1; col < end; ++col)
		{
			if (grid->GetTile(enemyRow, col) != TileType::Floor)
				return false;
		}
		return true;
	}
	else if (enemyCol == playerCol)
	{
		int start = std::min(enemyRow, playerRow);
		int end = std::max(enemyRow, playerRow);
		for (int row = start + 1; row < end; ++row)
		{
			if (grid->GetTile(row, enemyCol) != TileType::Floor)
				return false;
		}
		return true;
	}

	return false; // Not in straight line
}

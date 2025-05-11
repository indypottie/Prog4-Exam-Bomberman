#include "States.h"

#include <geometric.hpp>
#include <iostream>
#include <random>

#include "EnemyComponent.h"
#include "EngineTime.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "LevelManager.h"
#include "SpriteAnimatorComponent.h"


////////////////////////////
/// PLAYER STATES
////////////////////////////

void IdleState::Enter(dae::GameObject& obj)
{
	if (auto animator = obj.GetComponent<SpriteAnimatorComponent>())
		animator->Stop();
}

void IdleState::Update(dae::GameObject& /*obj*/)
{
}

void IdleState::Exit(dae::GameObject& /*obj*/)
{
}







////////////////////////////
/// ENEMY STATES
////////////////////////////

void WanderState::Enter(dae::GameObject& obj)
{
    if (m_Directions.empty())
    {
        m_Directions = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
    }

    m_TurnTimer = m_TurnCooldown;

    auto animator = obj.GetComponent<SpriteAnimatorComponent>();
    animator->Play("MoveLeft");

    std::cout << "WANDER STATE ENTERED\n";
}

void WanderState::Update(dae::GameObject& obj)
{
    const float deltaTime = EngineTime::GetInstance().GetDeltaTime();
    const float cellSize = LevelManager::GetInstance().GetGrid()->GetCellSize();
    const float speed = obj.GetComponent<EnemyComponent>()->GetSpeed();

    glm::vec2 pos = obj.GetPosition();
    glm::vec2 newPos = pos + m_CurrentDirection * speed * deltaTime;
    obj.SetPosition(newPos.x, newPos.y);

    m_TurnTimer -= deltaTime;

    if (m_TurnTimer <= 0.0f)
    {
        auto* grid = LevelManager::GetInstance().GetGrid();
        if (!grid) return;

        int row = static_cast<int>((newPos.y + cellSize / 2) / cellSize);
        int col = static_cast<int>((newPos.x + cellSize / 2) / cellSize);

        std::vector<glm::vec2> validDirs;
        for (auto& dir : m_Directions)
        {
            int testRow = row + dir.first;
            int testCol = col + dir.second;

            if (testRow >= 0 && testRow < grid->GetRows() &&
                testCol >= 0 && testCol < grid->GetCols())
            {
                if (grid->GetTile(testRow, testCol) == TileType::Floor)
                {
                    validDirs.emplace_back(dir.second, dir.first); // x = col, y = row
                }
            }
        }

        if (!validDirs.empty())
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::shuffle(validDirs.begin(), validDirs.end(), gen);

            for (const auto& dir : validDirs)
            {
                if (dir != -m_CurrentDirection)
                {
                    m_CurrentDirection = glm::normalize(dir);
                    break;
                }
            }

            m_TurnTimer = m_TurnCooldown;
        }
    }
}

void WanderState::Exit(dae::GameObject& /*obj*/)
{
    m_CurrentDirection = {}; // zero out direction
    m_TurnTimer = 0.0f;        //  reset timer
}


// chase
void ChaseState::Enter(dae::GameObject& /*obj*/)
{
    std::cout << "ENTERED CHASE STATE\n";
}

void ChaseState::Update(dae::GameObject& obj)
{
    auto* enemyComp = obj.GetComponent<EnemyComponent>();
    if (!enemyComp) return;

    // if no longer sees player return to wander
    if (!enemyComp->SeesPlayer())
    {
        enemyComp->SetState(std::make_unique<WanderState>());
        return;
    }

    auto* player = enemyComp->GetPlayer();
    if (!player) return;

    const float deltaTime = EngineTime::GetInstance().GetDeltaTime();
    const float speed = enemyComp->GetSpeed();

    glm::vec2 enemyPos = obj.GetPosition();
    glm::vec2 playerPos = player->GetPosition();

    glm::vec2 direction = playerPos - enemyPos;

    if (glm::length(direction) > 0.0001f) // avoid nans
        direction = glm::normalize(direction);

    glm::vec2 newPos = enemyPos + direction * speed * deltaTime;
    obj.SetPosition(newPos.x, newPos.y);

}

void ChaseState::Exit(dae::GameObject& /*obj*/)
{

}

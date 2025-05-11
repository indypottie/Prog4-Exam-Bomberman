#pragma once
#include <utility>
#include <vec2.hpp>
#include <vector>


namespace dae
{
	class GameObject;
}

// base player state interface class
class IPlayerState
{
public:
	virtual ~IPlayerState() = default;

	virtual void Enter(dae::GameObject& obj) = 0;
	virtual void Update(dae::GameObject& obj) = 0;
	virtual void Exit(dae::GameObject& obj) = 0;
};


class IdleState : public IPlayerState
{
	void Enter(dae::GameObject& obj) override;
	void Update(dae::GameObject& obj) override;
	void Exit(dae::GameObject& obj) override;
};




/// base enemy state interface class
class IEnemyState
{
public:
	virtual ~IEnemyState() = default;

	virtual void Enter(dae::GameObject& obj) = 0;
	virtual void Update(dae::GameObject& obj) = 0;
	virtual void Exit(dae::GameObject& obj) = 0;
};

// wander
class WanderState final : public IEnemyState
{
public:
	void Enter(dae::GameObject& obj) override;
	void Update(dae::GameObject& obj) override;
	void Exit(dae::GameObject& obj) override;

private:
	std::vector<std::pair<int, int>> m_Directions{
		{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } // up, down, left, right
	};

	glm::vec2 m_CurrentDirection{ 0.0f, 0.0f };

	float m_TurnCooldown = 1.0f;         // How long between possible turns
	float m_TurnTimer = 0.0f;            // Timer tracking how long since last turn
};

// chase player
class ChaseState : public IEnemyState
{
	void Enter(dae::GameObject& obj) override;
	void Update(dae::GameObject& obj) override;
	void Exit(dae::GameObject& obj) override;
};

// dead
class DeadState : public IEnemyState
{
	void Enter(dae::GameObject& obj) override;
	void Update(dae::GameObject& obj) override;
	void Exit(dae::GameObject& obj) override;
};
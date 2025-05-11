// file to store all commands this is cleaner than creating a new file for each command 

#pragma once
#include <iostream>

#include "Command.h"
#include "EngineCommands.h"
#include "GameObjectCommand.h"



class TakeDamage final : public GameObjectCommand
{
public:
	explicit TakeDamage(dae::GameObject& gameObject) : GameObjectCommand(gameObject) {}

	void Execute() override;
};


// temp command to play sound for testing the sound system
class PlaySoundCommand final : public Command
{
public:
	explicit PlaySoundCommand(std::string soundFile) : m_SoundFile(std::move(soundFile)) {}

	void Execute() override;

private:
	std::string m_SoundFile;
};



// movement command
class BombermanMoveCommand final : public GameObjectCommand
{
public:
	BombermanMoveCommand(dae::GameObject& gameObject, Direction direction, int playerIndex) : GameObjectCommand(gameObject), m_Direction(direction), m_PlayerIndex(playerIndex) {}

	void Execute() override;

	void SetPlayerSpeed(float speed) { m_Speed = speed; }
	float GetPlayerSpeed() const { return m_Speed; }

private:

	void MoveUp() const;
	void MoveDown() const;
	void MoveLeft() const;
	void MoveRight() const;

	void StopMovement() const;

	void Move(float dx, float dy) const;
	void PlayAnim(const std::string& animName) const;

	bool IsMyPlayer() const;

	Direction m_Direction;

	float m_Speed{ 1.5f };

	int m_PlayerIndex{ -1 };
};
//---------------------------
// Include Files
//---------------------------
#include "EngineCommands.h"


/// ----------------------------------
/// engine commands -- implementation
/// ----------------------------------


void MoveCommand::Execute()
{
	switch (m_Direction)
	{
	case Direction::Up:
		MoveUp();
		break;

	case Direction::Down:
		MoveDown();
		break;

	case Direction::Left:
		MoveLeft();
		break;

	case Direction::Right:
		MoveRight();
		break;
	}
}

void MoveCommand::MoveUp() const
{
	auto currentPos = GetGameObject()->GetPosition();

	auto newPosY = currentPos.y -= m_Speed;

	GetGameObject()->SetPosition(currentPos.x, newPosY);
}

void MoveCommand::MoveDown() const
{
	auto currentPos = GetGameObject()->GetPosition();

	auto newPosY = currentPos.y += m_Speed;

	GetGameObject()->SetPosition(currentPos.x, newPosY);
}

void MoveCommand::MoveLeft() const
{
	auto currentPos = GetGameObject()->GetPosition();

	auto newPosX = currentPos.x -= m_Speed;

	GetGameObject()->SetPosition(newPosX, currentPos.y);
}

void MoveCommand::MoveRight() const
{
	auto currentPos = GetGameObject()->GetPosition();

	auto newPosX = currentPos.x += m_Speed;

	GetGameObject()->SetPosition(newPosX, currentPos.y);
}

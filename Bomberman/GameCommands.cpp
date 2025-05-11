//---------------------------
// Include Files
//---------------------------
#include "GameCommands.h"

#include "HealthComponent.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"
#include "SpriteAnimatorComponent.h"

void TakeDamage::Execute()
{
	GetGameObject()->GetComponent<HealthComponent>()->TakeDamage(10);
}

void PlaySoundCommand::Execute()
{
    ServiceLocator::GetSoundSystem().QueueSound(m_SoundFile);
}



// movement command
void BombermanMoveCommand::Execute()
{
	if (!IsMyPlayer()) return;

	switch (m_Direction)
	{
	case Direction::Up:		MoveUp();		break;
	case Direction::Down:	MoveDown();		break;
	case Direction::Left:	MoveLeft();		break;
	case Direction::Right:	MoveRight();	break;
	case Direction::None:	StopMovement(); break;
	}
}

void BombermanMoveCommand::MoveUp()		const { Move(0, -m_Speed); PlayAnim("WalkUp");		}
void BombermanMoveCommand::MoveDown()	const { Move(0, +m_Speed); PlayAnim("WalkDown");		}
void BombermanMoveCommand::MoveLeft()	const { Move(-m_Speed, 0); PlayAnim("WalkLeft");		}
void BombermanMoveCommand::MoveRight()	const { Move(+m_Speed, 0); PlayAnim("WalkRight");		}


void BombermanMoveCommand::Move(float dx, float dy) const
{
	auto pos = GetGameObject()->GetPosition();
	GetGameObject()->SetPosition(pos.x + dx, pos.y + dy);
}

void BombermanMoveCommand::PlayAnim(const std::string& animName) const
{
	if (auto animator = GetGameObject()->GetComponent<SpriteAnimatorComponent>())
		animator->Play(animName);
}

void BombermanMoveCommand::StopMovement() const
{
	if (auto player = GetGameObject()->GetComponent<PlayerComponent>())
	{
		player->SetState(std::make_unique<IdleState>());
	}
}


bool BombermanMoveCommand::IsMyPlayer() const
{
	if (auto* pc = GetGameObject()->GetComponent<PlayerComponent>())
	{
		return pc->GetPlayerIndex() == m_PlayerIndex;
	}

	return false;
}

//---------------------------
// Include Files
//---------------------------
#include "GameCommands.h"

#include "HealthComponent.h"
#include "ServiceLocator.h"

void TakeDamage::Execute()
{
	GetGameObject()->GetComponent<HealthComponent>()->TakeDamage(10);
}

void PlaySoundCommand::Execute()
{
    ServiceLocator::GetSoundSystem().QueueSound(m_SoundFile);
}
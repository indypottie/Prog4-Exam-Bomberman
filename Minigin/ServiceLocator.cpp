#include "ServiceLocator.h"

void ServiceLocator::Init()
{
	RegisterSoundSystem(std::make_unique<SoundSystem>());
}

void ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem)
{
	if (soundSystem)
	{
		std::cout << "[ServiceLocator] Sound system registered.\n";
		GetInstance().m_SoundSystem = std::move(soundSystem);
	}
}

SoundSystem& ServiceLocator::GetSoundSystem()
{
	return *GetInstance().m_SoundSystem;
}
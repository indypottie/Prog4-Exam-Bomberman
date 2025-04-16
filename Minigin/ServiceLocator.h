#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <iostream>

#include "SoundSystem.h"
#include "Singleton.h"


//-----------------------------------------------------
// ServiceLocator Class									 
//-----------------------------------------------------
class ServiceLocator final : public dae::Singleton<ServiceLocator>
{
public:

	ServiceLocator() = default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	static void RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem)
	{
		if (soundSystem)
		{
			std::cout << "[ServiceLocator] Sound system registered.\n";
			GetInstance().m_SoundSystem = std::move(soundSystem);
		}
	}

	static SoundSystem& GetSoundSystem()
	{
		return *GetInstance().m_SoundSystem;
	}

private:
	friend class dae::Singleton<ServiceLocator>;

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	std::unique_ptr<SoundSystem> m_SoundSystem{ nullptr };
};

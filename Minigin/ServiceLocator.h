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

	void Init();

	static SoundSystem& GetSoundSystem();

private:
	friend class dae::Singleton<ServiceLocator>;

	static void RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem);

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	std::unique_ptr<SoundSystem> m_SoundSystem{ nullptr };
};

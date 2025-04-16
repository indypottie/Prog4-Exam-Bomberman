#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <memory>
#include <string>

//-----------------------------------------------------
// SoundSystem Class									 
//-----------------------------------------------------
class SoundSystem final
{
public:
	SoundSystem(); // Constructor
	~SoundSystem(); // Destructor

	SoundSystem(SoundSystem&&) noexcept;
	SoundSystem& operator=(SoundSystem&&) noexcept;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	void QueueSound(const std::string& soundFile);

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	class SoundSystemImpl;
	std::unique_ptr<SoundSystemImpl> m_Impl;
};
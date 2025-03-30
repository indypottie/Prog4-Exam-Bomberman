#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <chrono>

#include "Singleton.h"

//-----------------------------------------------------
// Time Class									 
//-----------------------------------------------------
class EngineTime final : public dae::Singleton<EngineTime>
{
public:

	// constant for fixed time step 
	static constexpr float FIXED_TIME_STEP{ 0.02f };


	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void UpdateDeltaTime();
	float GetDeltaTime()	const { return m_DeltaTime; }
	float GetElapsedTime()	const { return m_ElapsedTime; }

private:
	// friend class and constructor (default)
	friend class Singleton<EngineTime>; // allow singleton access to private constructor
	EngineTime() = default;

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	float m_DeltaTime{ 0.0f };
	float m_ElapsedTime{ 0.0f };
	std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime{ std::chrono::high_resolution_clock::now() };
};

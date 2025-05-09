﻿//---------------------------
// Include Files
//---------------------------
#include "EngineTime.h"

//---------------------------
// Member function
//---------------------------

void EngineTime::UpdateDeltaTime()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();

	m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
	m_LastTime = currentTime;
	m_ElapsedTime += m_DeltaTime;
}

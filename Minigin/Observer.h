#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Event.h"

namespace dae
{
	class GameObject;
}

//-----------------------------------------------------
// Observer Class									 
//-----------------------------------------------------
class Observer
{
public:

	virtual ~Observer() = default; // Destructor
	virtual void Notify(const Event& event, dae::GameObject* actor) = 0;
};
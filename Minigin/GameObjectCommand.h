#pragma once
#include "Command.h"
#include "GameObject.h"

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------


//-----------------------------------------------------
// GameActorCommand Class									 
//-----------------------------------------------------
class GameObjectCommand : public Command
{
public:
	GameObjectCommand(dae::GameObject& gameObject); // Constructor

protected:
	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	dae::GameObject* GetGameObject() const { return m_GameObjectPtr; }

private:
	dae::GameObject* m_GameObjectPtr;
};
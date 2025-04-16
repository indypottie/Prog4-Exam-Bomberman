#pragma once
#include "Command.h"
#include "GameObject.h"

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------


//-----------------------------------------------------
// GameActorCommand Class -> this command has an extra data member that is a game object 							 
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
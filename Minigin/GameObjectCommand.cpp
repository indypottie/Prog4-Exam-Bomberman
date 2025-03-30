//---------------------------
// Include Files
//---------------------------
#include "GameObjectCommand.h"

//---------------------------
// Constructor & Destructor
//---------------------------
GameObjectCommand::GameObjectCommand(dae::GameObject& gameObject) : m_GameObjectPtr{ &gameObject }
{
}
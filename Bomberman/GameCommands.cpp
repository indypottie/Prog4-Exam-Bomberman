//---------------------------
// Include Files
//---------------------------
#include "GameCommands.h"

#include "HealthComponent.h"

void TakeDamage::Execute()
{
	GetGameObject()->GetComponent<HealthComponent>()->TakeDamage(10);
}

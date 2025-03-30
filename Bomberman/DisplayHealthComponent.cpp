//---------------------------
// Include Files
//---------------------------
#include "DisplayHealthComponent.h"

#include <string>

#include "GameObject.h"
#include "HealthComponent.h"
#include "TextComponent.h"

//---------------------------
// Constructor & Destructor
//---------------------------
DisplayHealthComponent::DisplayHealthComponent(dae::GameObject& owner, TextComponent& textComponent) : Component(owner)
{
	m_TextComponentPtr = &textComponent;
}

//---------------------------
// Member functions
//---------------------------

void DisplayHealthComponent::Notify(const Event& event, dae::GameObject* actor)
{
	if (event.id == EventId::DAMAGE_TAKEN)
	{
		auto currentHealth = actor->GetComponent<HealthComponent>()->GetCurrentHealth();

		std::string updatedText = ("Health: " + std::to_string(currentHealth));

		m_TextComponentPtr->SetText(updatedText);
	}
}

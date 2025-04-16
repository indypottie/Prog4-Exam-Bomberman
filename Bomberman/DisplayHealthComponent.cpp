//---------------------------
// Include Files
//---------------------------
#include "DisplayHealthComponent.h"

#include <iostream>
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
	if (event.id == make_sdbm_hash("DamageTaken"))
	{
		auto currentHealth = actor->GetComponent<HealthComponent>()->GetCurrentHealth();

		std::string updatedText = ("Health: " + std::to_string(currentHealth));

		m_TextComponentPtr->SetText(updatedText);

		std::cout << "Damage Taken: " << event.args[0].Get<int>() << '\n';
	}
}
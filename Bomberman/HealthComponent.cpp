//---------------------------
// Include Files
//---------------------------
#include "HealthComponent.h"

#include "Event.h"
#include "Subject.h"

//---------------------------
// Constructor & Destructor
//---------------------------
HealthComponent::HealthComponent(dae::GameObject& owner, int maxHealth) : Component(owner), m_CurrentHealth(maxHealth), m_MaxHealth(maxHealth), m_SubjectPtr(std::make_unique<Subject>())
{
}

//---------------------------
// Member functions
//---------------------------

void HealthComponent::AddObserver(Observer* observer)
{
	m_SubjectPtr->AddObserver(observer);
}

void HealthComponent::RemoveObserver(Observer* observer)
{
	m_SubjectPtr->RemoveObserver(observer);
}

void HealthComponent::SetMaxHealth(int newMaxHealth)
{
	m_MaxHealth = newMaxHealth;
}

void HealthComponent::TakeDamage(int amount)
{
	if (m_CurrentHealth <= 0) return;

	if ((m_CurrentHealth - amount) <= 0)
	{
		m_CurrentHealth = 0;
	}
	else
	{
		m_CurrentHealth -= amount;
	}

	Event damageEvent(make_sdbm_hash("DamageTaken"), amount);
	m_SubjectPtr->NotifyObservers(damageEvent, GetOwner());
}
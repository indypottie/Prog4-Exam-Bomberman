#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Component.h"
#include "Observer.h"

class TextComponent;

//-----------------------------------------------------
// DisplayHealthComponent Class									 
//-----------------------------------------------------

// todo: create ui component that handles all the ui stuff instead of creating display X for every ui element
 
class DisplayHealthComponent final : public Component, public Observer
{
public:
	DisplayHealthComponent(dae::GameObject& owner, TextComponent& textComponent); // Constructor
	~DisplayHealthComponent() override = default; // Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	DisplayHealthComponent(const DisplayHealthComponent& other)					= delete;
	DisplayHealthComponent(DisplayHealthComponent&& other) noexcept				= delete;
	DisplayHealthComponent& operator=(const DisplayHealthComponent& other)		= delete;
	DisplayHealthComponent& operator=(DisplayHealthComponent&& other) noexcept	= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	void Notify(const Event& event, dae::GameObject* actor) override;

private:

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	TextComponent* m_TextComponentPtr;
};

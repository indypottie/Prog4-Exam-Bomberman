#pragma once

namespace dae
{
	class GameObject;
}
//-----------------------------------------------------
// Component Class									 
//-----------------------------------------------------
class Component
{
public:
	virtual ~Component() = default; // Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------
	Component(const Component& other)					= delete;
	Component(Component&& other)						= delete;
	Component& operator=(const Component& other)		= delete;
	Component& operator=(Component&& other) noexcept	= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	virtual void Update();
	virtual void Render() const;

	void MarkForDeletion() { m_IsMarkedForDeletion = true; }
	bool IsMarkedForDeletion() const { return m_IsMarkedForDeletion; }

protected:
	explicit Component(dae::GameObject& owner); // owner is set at creation and cannot be changed
	dae::GameObject* GetOwner() const;

private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	dae::GameObject* m_OwnerPtr{};

	bool m_IsMarkedForDeletion{ false };
};

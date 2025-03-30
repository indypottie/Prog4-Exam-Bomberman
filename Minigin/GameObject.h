#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vec3.hpp>

#include "Component.h"

class TransformComponent;

namespace dae
{
	class GameObject final
	{
	public:
		// constructor & destructor
		GameObject();
		~GameObject();

		// rule of 5
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// public member methods

		void Update();
		void Render() const;

		void SetPosition(float x, float y) const;
		glm::vec3 GetPosition() const;


		// scene graph methods
		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent() const;
		std::vector<GameObject*> GetChildren() const;
		TransformComponent* GetTransformComponent() const;

		int GetChildCount() const;
		GameObject* GetChildAt(size_t index) const;


		template<typename T, typename... Args>
		T* AddComponent(Args&&... args);

		template<typename T>
		void RemoveComponent();

		template<typename T>
		T* GetComponent() const;

		template<typename T>
		bool HasComponent() const;

		void MarkForDeletion() { m_IsMarkedForDeletion = true; }
		bool IsMarkedForDeletion() const { return m_IsMarkedForDeletion; }

		void CleanupComponents(); // Remove only marked components


	private:
		// private methods
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);

		// components
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components{};
		bool m_IsMarkedForDeletion{ false };

		TransformComponent* m_TransformComponent; // every game object is constructed with a transform 

		// sceneGraph variables
		GameObject* m_ParentPtr{ nullptr };
		std::vector<GameObject*> m_ChildrenPtrs;
	};


	/// templates

	// add component
	template <typename T, typename... Args>
	T* GameObject::AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

		auto typeId = std::type_index(typeid(T));
		if (!m_Components.contains(typeId))
		{
			auto component = std::make_unique<T>(*this, std::forward<Args>(args)...);
			T* rawPtr = component.get(); // Store raw pointer before moving
			m_Components[typeId] = std::move(component); // Store ownership
			return rawPtr;
		}

		return nullptr;
	}

	// remove component
	template <typename T>
	void GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

		auto typeId = std::type_index(typeid(T));
		auto it = m_Components.find(typeId);

		if (it != m_Components.end())
		{
			it->second->MarkForDeletion();
		}
	}


	// get component -> but does not give ownership
	template <typename T>
	T* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

		auto typeId = std::type_index(typeid(T));
		auto it = m_Components.find(typeId);

		if (it != m_Components.end())
		{
			return static_cast<T*>(it->second.get());
		}

		return nullptr;
	}

	// has component
	template <typename T>
	bool GameObject::HasComponent() const
	{
		static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

		return m_Components.contains(std::type_index(typeid(T)));
	}
}

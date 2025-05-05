#include "Scene.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(std::string name) : m_name(std::move(name))
{
}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject>& object)
{
	m_objects.emplace_back(std::move(object));
	object = nullptr;
}

void Scene::Remove(GameObject* object)
{
	auto it = std::ranges::find_if(m_objects, [object](const std::unique_ptr<GameObject>& ptr) {
		return ptr.get() == object;
		});

	if (it != m_objects.end())
	{
		m_objects.erase(it);
	}
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}

	m_objects.erase(std::ranges::remove_if(m_objects, [](const std::unique_ptr<GameObject>& obj)
	{
		return obj->IsMarkedForDeletion();
	}).begin(),

	m_objects.end());
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}


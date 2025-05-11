#pragma once
#include <memory>
#include <string>

namespace dae
{
	class GameObject;
	class Font;
}

class HealthComponent;

namespace Prefab
{
	std::unique_ptr<dae::GameObject> CreateBomberman(int playerIndex);

	std::unique_ptr<dae::GameObject> CreateBalloom();

	std::unique_ptr<dae::GameObject> CreateOneal();

	std::unique_ptr<dae::GameObject> CreateHealthUI(HealthComponent* observedHealth, dae::Font* font);

	std::unique_ptr<dae::GameObject> CreateLevel(const std::string& levelFilePath, int rows, int cols, float cellSize);



}

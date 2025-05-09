#include <SDL.h>

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "ControllerButtons.h"
#include "DisplayHealthComponent.h"
#include "EngineCommands.h"
#include "GameCommands.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backGroundObject = std::make_unique<dae::GameObject>();
	backGroundObject->AddComponent<TextureComponent>("Bomberman_Playfield.tga");
	//scene.Add(backGroundObject);


	auto bombermanObject = std::make_unique<dae::GameObject>();
	bombermanObject->AddComponent<TextureComponent>("bomberman-front.tga");
	bombermanObject->AddComponent<HealthComponent>();

	auto smallerFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto displayHealthObject = std::make_unique<dae::GameObject>();
	displayHealthObject->SetPosition(10.f, 210.f);
	displayHealthObject->AddComponent<TextComponent>("Health: 100", smallerFont);
	displayHealthObject->AddComponent<DisplayHealthComponent>(*displayHealthObject->GetComponent<TextComponent>());

	bombermanObject->GetComponent<HealthComponent>()->AddObserver(displayHealthObject->GetComponent<DisplayHealthComponent>());


	scene.Add(displayHealthObject);

	auto& input = dae::InputManager::GetInstance();
	input.BindControllerCommand(0, ControllerButton::DPAD_RIGHT, keyState::down, std::make_unique<MoveCommand>(*bombermanObject, Direction::Right));
	input.BindControllerCommand(0, ControllerButton::DPAD_LEFT,  keyState::down, std::make_unique<MoveCommand>(*bombermanObject, Direction::Left));
	input.BindControllerCommand(0, ControllerButton::DPAD_UP,    keyState::down, std::make_unique<MoveCommand>(*bombermanObject, Direction::Up));
	input.BindControllerCommand(0, ControllerButton::DPAD_DOWN,  keyState::down, std::make_unique<MoveCommand>(*bombermanObject, Direction::Down));

	input.BindControllerCommand(0, ControllerButton::BUTTON_X, keyState::released, std::make_unique<TakeDamage>(*bombermanObject));
	input.BindControllerCommand(0, ControllerButton::BUTTON_A, keyState::released, std::make_unique<PlaySoundCommand>("Resources/Audio/Bomberman_SFX_06.wav"));

	// keyboard
	input.BindKeyboardCommand(SDLK_w, keyState::down, std::make_unique<MoveCommand>(*bombermanObject, Direction::Up));
	input.BindKeyboardCommand(SDLK_a, keyState::down, std::make_unique<MoveCommand>(*bombermanObject, Direction::Left));
	input.BindKeyboardCommand(SDLK_s, keyState::down, std::make_unique<MoveCommand>(*bombermanObject, Direction::Down));
	input.BindKeyboardCommand(SDLK_d, keyState::down, std::make_unique<MoveCommand>(*bombermanObject, Direction::Right));


	auto gridObject = std::make_unique<dae::GameObject>();
	gridObject->SetPosition(0.f, 0.f); // top-left grid origin

	int rows = 13, cols = 31;
	float cellSize = 32.f;

	auto gridComponent = gridObject->AddComponent<GridComponent>(rows, cols, cellSize);

	// Example setup
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			if (row == 0 || col == 0 || row == rows - 1 || col == cols - 1 || (row % 2 == 0 && col % 2 == 0))
			{
				gridComponent->SetTile(row, col, TileType::IndestructibleWall);
			}
		}
	}

	bombermanObject->SetPosition(gridComponent->GetWorldPosition(1, 1).x, gridComponent->GetWorldPosition(1, 1).y);

	scene.Add(bombermanObject);
	scene.Add(gridObject);
}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
#include <SDL.h>

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "ControllerButtons.h"
#include "EngineCommands.h"
#include "GameCommands.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "Minigin.h"
#include "PrefabFactory.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto gridObject = Prefab::CreateLevel("../Data/Levels.json", 13, 31, 32.f);
	if (!gridObject) return; // if level loading fails stop game
	auto gridComponent = gridObject->GetComponent<GridComponent>();

	auto bombermanObject = Prefab::CreateBomberman(0);
	bombermanObject->SetPosition(gridComponent->GetWorldPosition(1, 1).x, gridComponent->GetWorldPosition(1, 1).y);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto healthUI = Prefab::CreateHealthUI(bombermanObject->GetComponent<HealthComponent>(), font);


	auto& input = dae::InputManager::GetInstance();
	input.BindControllerCommand(0, ControllerButton::DPAD_RIGHT, keyState::down, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::Right,	0));
	input.BindControllerCommand(0, ControllerButton::DPAD_LEFT,  keyState::down, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::Left,	0));
	input.BindControllerCommand(0, ControllerButton::DPAD_UP,    keyState::down, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::Up,		0));
	input.BindControllerCommand(0, ControllerButton::DPAD_DOWN,  keyState::down, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::Down,	0));

	input.BindControllerCommand(0, ControllerButton::DPAD_RIGHT, keyState::released, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::None, 0));
	input.BindControllerCommand(0, ControllerButton::DPAD_LEFT, keyState::released, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::None, 0));
	input.BindControllerCommand(0, ControllerButton::DPAD_UP, keyState::released, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::None, 0));
	input.BindControllerCommand(0, ControllerButton::DPAD_DOWN, keyState::released, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::None, 0));
	

	input.BindControllerCommand(0, ControllerButton::BUTTON_X, keyState::released, std::make_unique<TakeDamage>(*bombermanObject));
	input.BindControllerCommand(0, ControllerButton::BUTTON_A, keyState::released, std::make_unique<PlaySoundCommand>("Resources/Audio/Bomberman_SFX_06.wav"));

	// keyboard
	input.BindKeyboardCommand(SDLK_w, keyState::down, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::Up,		0));
	input.BindKeyboardCommand(SDLK_a, keyState::down, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::Left,		0));
	input.BindKeyboardCommand(SDLK_s, keyState::down, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::Down,		0));
	input.BindKeyboardCommand(SDLK_d, keyState::down, std::make_unique<BombermanMoveCommand>(*bombermanObject, Direction::Right,		0));


	auto balloomEnemy = Prefab::CreateBalloom();
	balloomEnemy->SetPosition(gridComponent->GetWorldPosition(5, 15).x, gridComponent->GetWorldPosition(5, 15).y);

	auto onealEnemy = Prefab::CreateOneal();
	onealEnemy->SetPosition(gridComponent->GetWorldPosition(8, 15).x, gridComponent->GetWorldPosition(8, 15).y);

	scene.Add(gridObject);
	scene.Add(bombermanObject);
	scene.Add(onealEnemy);
	scene.Add(balloomEnemy);
	scene.Add(healthUI);
}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
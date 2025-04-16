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

	auto backGroundObject = std::make_shared<dae::GameObject>();
	backGroundObject->AddComponent<TextureComponent>("background.tga");
	scene.Add(backGroundObject);

	auto logoObject = std::make_shared<dae::GameObject>();
	logoObject->AddComponent<TextureComponent>("logo.tga");
	logoObject->SetPosition(216.f, 180.f);
	scene.Add(logoObject);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto titleObject = std::make_shared<dae::GameObject>();
	titleObject->AddComponent<TextComponent>("Programming 4 engine", font);
	titleObject->SetPosition(80.f, 20.f);
	scene.Add(titleObject);



	auto bombermanObject = std::make_shared<dae::GameObject>();
	bombermanObject->SetPosition(250.f, 250.f);
	bombermanObject->AddComponent<TextureComponent>("bomberman-front.tga");
	bombermanObject->AddComponent<HealthComponent>();
	scene.Add(bombermanObject);

	auto smallerFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto displayHealthObject = std::make_shared<dae::GameObject>();
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
	input.BindControllerCommand(0, ControllerButton::BUTTON_A, keyState::released, std::make_unique<PlaySoundCommand>("Resources/Bomberman_SFX_06.wav"));


	/// controls
	auto bomberManControlsObject = std::make_shared<dae::GameObject>();
	bomberManControlsObject->SetPosition(10, 140.f);
	bomberManControlsObject->AddComponent<TextComponent>("Use the D-Pad to move BomberMan, X to inflict damage", smallerFont);
	scene.Add(bomberManControlsObject);

}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
#include "PrefabFactory.h"

// includes for the components

#include <iostream>

#include "BombermanLevelLoader.h"
#include "DisplayHealthComponent.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "HealthComponent.h"
#include "LevelManager.h"
#include "PlayerComponent.h"
#include "SpriteAnimatorComponent.h"
#include "TextureComponent.h"


std::unique_ptr<dae::GameObject> Prefab::CreateBomberman(int playerIndex)
{
	// create the bomberman object
	auto bomberman = std::make_unique<dae::GameObject>();

	// add related components
	bomberman->AddComponent<PlayerComponent>(playerIndex);
	bomberman->AddComponent<TextureComponent>("PlayerSpriteSheet.tga");
	bomberman->AddComponent<HealthComponent>();
	bomberman->AddComponent<SpriteAnimatorComponent>(32, 32);

	// set tag
	bomberman->SetTag("Player");

	// create the animator
	auto animator = bomberman->GetComponent<SpriteAnimatorComponent>();

	// create the animations
	Animation walkDown;
	walkDown.frames = { {3, 0}, {4, 0}, {5, 0} };
	walkDown.frameTime = 0.1f;
	walkDown.looping = true;

	Animation WalkLeft;
	WalkLeft.frames = { {0, 0}, {1, 0}, {2, 0} };
	WalkLeft.frameTime = 0.1f;
	WalkLeft.looping = true;

	Animation WalkRight;
	WalkRight.frames = { {0, 1}, {1, 1}, {2, 1} };
	WalkRight.frameTime = 0.1f;
	WalkRight.looping = true;

	Animation WalkUp;
	WalkUp.frames = { {3, 1}, {4, 1}, {5, 1} };
	WalkUp.frameTime = 0.1f;
	WalkUp.looping = true;


	// add animations to the animator
	animator->AddAnimation("WalkDown", walkDown);
	animator->AddAnimation("WalkLeft", WalkLeft);
	animator->AddAnimation("WalkRight", WalkRight);
	animator->AddAnimation("WalkUp", WalkUp);
	animator->SetDefaultFrame({ 4, 0 });

	return bomberman;
}

std::unique_ptr<dae::GameObject> Prefab::CreateBalloom()
{
	// create the balloom object
	auto balloomEnemy = std::make_unique<dae::GameObject>();

	// add related components

	balloomEnemy->AddComponent<TextureComponent>("BalloomSpriteSheet.tga");
	balloomEnemy->AddComponent<SpriteAnimatorComponent>(32, 32);

	// create the animator
	auto animator = balloomEnemy->GetComponent<SpriteAnimatorComponent>();

	//create the animations
	Animation floatLeft;
	floatLeft.frames = { {0, 1}, {1, 1}, {2, 1} };
	floatLeft.frameTime = 0.15f;
	floatLeft.looping = true;

	// add the anims to the animator
	animator->AddAnimation("MoveLeft", floatLeft);

	// add enemy comp
	balloomEnemy->AddComponent<EnemyComponent>(EnemyType::Balloom);

	return balloomEnemy;
}

std::unique_ptr<dae::GameObject> Prefab::CreateOneal()
{
	// create the oneal object
	auto onealEnemy = std::make_unique<dae::GameObject>();

	// add related components
	onealEnemy->AddComponent<TextureComponent>("OnealSpriteSheet.tga");
	onealEnemy->AddComponent<SpriteAnimatorComponent>(32, 32);

	// create the animator
	auto animator = onealEnemy->GetComponent<SpriteAnimatorComponent>();

	// create the animations
	Animation moveLeft;
	moveLeft.frames = { {3, 0}, {4, 0}, {5, 0} };
	moveLeft.frameTime = 0.15f;
	moveLeft.looping = true;

	// add the anims to the animator
	animator->AddAnimation("MoveLeft", moveLeft);

	// add enemy comp
	onealEnemy->AddComponent<EnemyComponent>(EnemyType::Oneal);

	return onealEnemy;
}


std::unique_ptr<dae::GameObject> Prefab::CreateHealthUI(HealthComponent* observedHealth, dae::Font* font)
{
	auto ui = std::make_unique<dae::GameObject>();
	ui->SetPosition(0.f, 0.f);

	auto text = ui->AddComponent<TextComponent>("Health: 100", font);
	ui->AddComponent<DisplayHealthComponent>(*text);

	if (observedHealth)
		observedHealth->AddObserver(ui->GetComponent<DisplayHealthComponent>());

	return ui;
}


std::unique_ptr<dae::GameObject> Prefab::CreateLevel(const std::string& levelFilePath, int rows, int cols, float cellSize)
{
	auto gridObject = std::make_unique<dae::GameObject>();
	gridObject->SetPosition(0.f, 0.f);

	auto gridComponent = gridObject->AddComponent<GridComponent>(rows, cols, cellSize);
	if (!BombermanLevelLoader::LoadLevelFromFile(levelFilePath, *gridComponent))
	{
		std::cerr << "Failed to load level from file: " << levelFilePath << '\n';
		return nullptr;
	}

	LevelManager::GetInstance().SetGrid(gridComponent);

	return gridObject;
}


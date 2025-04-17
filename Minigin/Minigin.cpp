#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Minigin.h"

#include <chrono>
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EngineTime.h"
#include "ServiceLocator.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_MIXER_VERSION(&version);
	printf("We compiled against SDL_mixer version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *Mix_Linked_Version();
	printf("We are linking against SDL_mixer version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string& dataPath)
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, // original 640 // bomberman base bg: 528
		480, // original 480 // bomberman base bg: 256
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	ServiceLocator::GetInstance().Init();

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);

}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = EngineTime::GetInstance();

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;


	while (doContinue)
	{
		// update delta time using the time singleton
		time.UpdateDeltaTime();
		const float deltaTime = time.GetDeltaTime();
		lag += deltaTime;

		doContinue = input.ProcessInput();

		float fixedTimeStep = EngineTime::FIXED_TIME_STEP;

		// fixed update logic
		while (lag >= fixedTimeStep)
		{
			FixedUpdate(fixedTimeStep);
			lag -= fixedTimeStep;
		}

		// update game logic
		sceneManager.Update();
		renderer.Render();

		// calculate sleep time
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto frameDuration = std::chrono::milliseconds(16); // 60 FPS cap (16.67 ms)
		auto sleepTime = frameDuration - std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime);

		// sleep for the remaining time
		if (sleepTime > std::chrono::milliseconds(0))
		{
			std::this_thread::sleep_for(sleepTime);
		}

		lastTime = std::chrono::high_resolution_clock::now();
	}
}

void dae::Minigin::FixedUpdate(float)
{
}

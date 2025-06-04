#include <SDL.h>
#include "InputManager.h"

#include <array>
#include <ext/scalar_uint_sized.hpp>

#include "Command.h"
#include "Controller.h"
#include "ControllerButtons.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

		// Refresh the keyboard state (process the latest input)
		SDL_PumpEvents();
		m_CurrentKeyState = SDL_GetKeyboardState(nullptr);

		// Execute commands for key held down (continuously while pressed)
		for (const auto& [key, command] : m_KeyCommandsDown)
		{
			if (m_CurrentKeyState[SDL_GetScancodeFromKey(key)])
			{
				command->Execute();  // Execute continuously while key is held down
			}
		}

		// Execute commands for key pressed (only the first time it is pressed)
		for (const auto& [key, command] : m_KeyCommandsPressed)
		{
			if (m_CurrentKeyState[SDL_GetScancodeFromKey(key)] && !m_PreviousKeyState[SDL_GetScancodeFromKey(key)])
			{
				command->Execute();  // Execute only once when key is pressed down for the first time
			}
		}

		// Execute commands for key released (only when key is released)
		for (const auto& [key, command] : m_KeyCommandsReleased)
		{
			if (!m_CurrentKeyState[SDL_GetScancodeFromKey(key)] && m_PreviousKeyState[SDL_GetScancodeFromKey(key)])
			{
				command->Execute();  // Execute only once when key is released
			}
		}

		// Store the current state as the previous state for the next frame
		memcpy(m_PreviousKeyState, m_CurrentKeyState, SDL_NUM_SCANCODES);
	


	for (auto& [index, controller] : m_Controllers)
	{
		controller->Update();

		for (const auto& [button, command] : m_ControllerCommandsDown[index])
		{
			if (controller->IsButtonDown(button))
			{
				command->Execute();
			}
		}

		for (const auto& [button, command] : m_ControllerCommandsPressed[index])
		{
			if (controller->IsButtonPressed(button))
			{
				command->Execute();
			}
		}

		for (const auto& [button, command] : m_ControllerCommandsReleased[index])
		{
			if (controller->IsButtonReleased(button))
			{
				command->Execute();
			}
		}

	}

	return true;
}

void dae::InputManager::BindControllerCommand(int controllerIndex, ControllerButton button, keyState state, std::unique_ptr<Command> command)
{
	// Check if the controller exists, and if not, create it
	if (!m_Controllers.contains(controllerIndex))
	{
		m_Controllers[controllerIndex] = std::make_unique<Controller>(controllerIndex);  // Initialize the controller
	}

	switch (state)
	{
	case keyState::down:
		m_ControllerCommandsDown[controllerIndex][button] = std::move(command);
		break;

	case keyState::pressed:
		m_ControllerCommandsPressed[controllerIndex][button] = std::move(command);
		break;

	case keyState::released:
		m_ControllerCommandsReleased[controllerIndex][button] = std::move(command);
		break;
	}
}

void dae::InputManager::BindKeyboardCommand(SDL_Keycode key, keyState state, std::unique_ptr<Command> command)
{
	switch (state)
	{
	case keyState::down:
		m_KeyCommandsDown[key] = std::move(command);
		break;
	case keyState::pressed:
		m_KeyCommandsPressed[key] = std::move(command);
		break;
	case keyState::released:
		m_KeyCommandsReleased[key] = std::move(command);
		break;
	}
}
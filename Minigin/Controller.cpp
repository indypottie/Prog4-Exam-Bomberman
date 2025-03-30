#include "Controller.h"
#include "ControllerButtons.h"
#include <SDL_syswm.h>
#include <Xinput.h>

// Define the ControllerImpl class
class Controller::ControllerImpl
{
public:
    explicit ControllerImpl(int controllerIndex);
    void Update();
    bool IsButtonDown(ControllerButton button) const;
    bool IsButtonPressed(ControllerButton button) const;
    bool IsButtonReleased(ControllerButton button) const;
    bool IsConnected() const;

private:
    int GamepadButtonMapping(ControllerButton button) const;

    int m_ControllerIndex;
    XINPUT_STATE m_PreviousState{};
    XINPUT_STATE m_CurrentState{};
    int m_ButtonPressedThisFrame{};
    int m_ButtonReleasedThisFrame{};
};

//---------------------------
// Implement ControllerImpl methods
//---------------------------
Controller::ControllerImpl::ControllerImpl(int controllerIndex) : m_ControllerIndex(controllerIndex) {}

void Controller::ControllerImpl::Update()
{
    CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
    ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

    if (XInputGetState(m_ControllerIndex, &m_CurrentState) != ERROR_SUCCESS)
    {
        ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE)); // Reset state if controller is disconnected
    }

    auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
    m_ButtonPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
    m_ButtonReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool Controller::ControllerImpl::IsButtonDown(ControllerButton button) const
{
    return (m_CurrentState.Gamepad.wButtons & GamepadButtonMapping(button)) != 0;
}

bool Controller::ControllerImpl::IsButtonPressed(ControllerButton button) const
{
    return (m_ButtonPressedThisFrame & GamepadButtonMapping(button)) != 0;
}

bool Controller::ControllerImpl::IsButtonReleased(ControllerButton button) const
{
    return (m_ButtonReleasedThisFrame & GamepadButtonMapping(button)) != 0;
}

bool Controller::ControllerImpl::IsConnected() const
{
    XINPUT_STATE state;
    return XInputGetState(m_ControllerIndex, &state) == ERROR_SUCCESS;
}

int Controller::ControllerImpl::GamepadButtonMapping(ControllerButton button) const
{
    switch (button)
    {
    case ControllerButton::DPAD_RIGHT:  return XINPUT_GAMEPAD_DPAD_RIGHT;
    case ControllerButton::DPAD_LEFT:   return XINPUT_GAMEPAD_DPAD_LEFT;
    case ControllerButton::DPAD_UP:     return XINPUT_GAMEPAD_DPAD_UP;
    case ControllerButton::DPAD_DOWN:   return XINPUT_GAMEPAD_DPAD_DOWN;
    case ControllerButton::BUTTON_A:    return XINPUT_GAMEPAD_A;
    case ControllerButton::BUTTON_X:    return XINPUT_GAMEPAD_X;
    case ControllerButton::BUTTON_B:    return XINPUT_GAMEPAD_B;
    case ControllerButton::BUTTON_Y:    return XINPUT_GAMEPAD_Y;
    default: return 0;
    }
}

//---------------------------
// Implement Controller methods
//---------------------------
Controller::Controller(int controllerIndex)
    : m_ControllerImpl(std::make_unique<ControllerImpl>(controllerIndex)) {
}

Controller::~Controller() = default;

// **Manually implemented move constructor**
Controller::Controller(Controller&& other) noexcept
    : m_ControllerImpl(std::move(other.m_ControllerImpl)) {
}

// **Manually implemented move assignment operator**
Controller& Controller::operator=(Controller&& other) noexcept
{
    if (this != &other)
    {
        m_ControllerImpl = std::move(other.m_ControllerImpl);
    }
    return *this;
}

void Controller::Update()
{
    m_ControllerImpl->Update();
}

bool Controller::IsButtonDown(ControllerButton button) const
{
    return m_ControllerImpl->IsButtonDown(button);
}

bool Controller::IsButtonPressed(ControllerButton button) const
{
    return m_ControllerImpl->IsButtonPressed(button);
}

bool Controller::IsButtonReleased(ControllerButton button) const
{
    return m_ControllerImpl->IsButtonReleased(button);
}

bool Controller::IsConnected() const
{
    return m_ControllerImpl->IsConnected();
}
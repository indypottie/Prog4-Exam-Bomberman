#pragma once
#include <memory>

//-----------------------------------------------------
// Forward Declarations
//-----------------------------------------------------
enum class ControllerButton : uint8_t;

class Controller final
{
public:
    explicit Controller(int controllerIndex);
    ~Controller();

    // Move constructor and move assignment operator (manually defined in .cpp)
    Controller(Controller&& other) noexcept;
    Controller& operator=(Controller&& other) noexcept;

    //-------------------------------------------------
    // Member functions                        
    //-------------------------------------------------
    void Update();

    bool IsButtonDown(ControllerButton button) const;
    bool IsButtonPressed(ControllerButton button) const;
    bool IsButtonReleased(ControllerButton button) const;

    bool IsConnected() const;

private:
    class ControllerImpl;
    std::unique_ptr<ControllerImpl> m_ControllerImpl;
};

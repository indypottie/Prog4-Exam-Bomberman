#pragma once
#include <memory>


template <typename OwnerType, typename StateType>
class StateMachine
{
public:
    void Update(OwnerType& owner)
    {
        if (m_pCurrentState)
            m_pCurrentState->Update(owner);
    }

    void SetState(std::unique_ptr<StateType> newState, OwnerType& owner)
    {
        if (m_pCurrentState)
            m_pCurrentState->Exit(owner);

        m_pCurrentState = std::move(newState);

        if (m_pCurrentState)
            m_pCurrentState->Enter(owner);
    }

    StateType* GetCurrentState() const
    {
        return m_pCurrentState.get();
    }

private:
    std::unique_ptr<StateType> m_pCurrentState{};
};

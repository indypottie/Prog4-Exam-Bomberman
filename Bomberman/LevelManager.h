#pragma once
#include "Singleton.h"

class GridComponent;

class LevelManager final : public dae::Singleton<LevelManager>
{
public:
    LevelManager() = default;

    void SetGrid(GridComponent* grid) { m_Grid = grid; }
    GridComponent* GetGrid() const { return m_Grid; }

private:
    friend class dae::Singleton<LevelManager>;

    GridComponent* m_Grid{ nullptr }; // Non-owning pointer, managed elsewhere
};

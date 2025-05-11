#pragma once
#include <memory>
#include <vec2.hpp>

#include "Component.h"
#include <vector>

namespace dae
{
	class Texture2D;
}

enum class TileType
{
    Floor,
    IndestructibleWall,
    DestructibleWall,
    Bomb,
    Explosion,

    Empty
};


class GridComponent : public Component
{
public:
    GridComponent(dae::GameObject& owner, int rows, int cols, float cellSize);

    void Initialize();
    void Render() const override;

    TileType GetTile(int row, int col) const;
    void SetTile(int row, int col, TileType type);

    int GetRows() const { return m_Rows; }
    int GetCols() const { return m_Cols; }
    float GetCellSize() const { return m_CellSize; }

    glm::vec2 GetWorldPosition(int row, int col) const;

private:

    void RenderTile(TileType type, float x, float y) const;



    int m_Rows;
	int m_Cols;

    float m_CellSize;
    std::vector<TileType> m_Grid;

    std::unique_ptr<dae::Texture2D> m_IndestructibleWallTexturePtr;
	std::unique_ptr<dae::Texture2D> m_DestructibleWallTexturePtr;
    std::unique_ptr<dae::Texture2D> m_FloorTexturePtr;
};

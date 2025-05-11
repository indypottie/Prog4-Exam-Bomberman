#include "GridComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <stdexcept>

#include "Texture2D.h"

GridComponent::GridComponent(dae::GameObject& owner, int rows, int cols, float cellSize)
    : Component(owner),
    m_Rows(rows), m_Cols(cols),
    m_CellSize(cellSize),
    m_Grid(static_cast<unsigned long long>(rows* cols), TileType::Empty)
{
    Initialize();
}

void GridComponent::Initialize()
{
    // load textures
    m_IndestructibleWallTexturePtr = std::make_unique<dae::Texture2D>("Resources/IndestructibleWall.tga");
	m_DestructibleWallTexturePtr = std::make_unique<dae::Texture2D>("Resources/DestructibleWall.tga");
	m_FloorTexturePtr = std::make_unique<dae::Texture2D>("Resources/Floor.tga");
}

TileType GridComponent::GetTile(int row, int col) const
{
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols)
        throw std::out_of_range("GridComponent::GetTile - index out of range");
    return m_Grid[row * m_Cols + col];
}

void GridComponent::SetTile(int row, int col, TileType type)
{
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols)
        throw std::out_of_range("GridComponent::SetTile - index out of range");
    m_Grid[row * m_Cols + col] = type;
}

glm::vec2 GridComponent::GetWorldPosition(int row, int col) const
{
    auto pos = GetOwner()->GetPosition();
    return { pos.x + static_cast<float>(col) * m_CellSize, pos.y + static_cast<float>(row) * m_CellSize };
}

void GridComponent::Render() const
{
    for (int row = 0; row < m_Rows; ++row)
    {
        for (int col = 0; col < m_Cols; ++col)
        {
            auto tile = m_Grid[row * m_Cols + col];
            auto pos = GetWorldPosition(row, col);
            RenderTile(tile, pos.x, pos.y);
        }
    }
}

void GridComponent::RenderTile(TileType type, float x, float y) const
{
    switch (type)
    {
    case TileType::Floor:
        dae::Renderer::GetInstance().RenderTexture(*m_FloorTexturePtr, x, y);
        //dae::Renderer::GetInstance().DrawRect(x, y, m_CellSize, m_CellSize, { 0, 255, 0, 255 });
        break;

    case TileType::IndestructibleWall:
        dae::Renderer::GetInstance().RenderTexture(*m_IndestructibleWallTexturePtr, x, y);
        //dae::Renderer::GetInstance().DrawRect(x, y, m_CellSize, m_CellSize, { 50, 50, 50, 255 });
        break;

    case TileType::DestructibleWall:
        dae::Renderer::GetInstance().RenderTexture(*m_DestructibleWallTexturePtr, x, y);
       // dae::Renderer::GetInstance().DrawRect(x, y, m_CellSize, m_CellSize, { 150, 75, 0, 255 });
        break;

    case TileType::Bomb:
        dae::Renderer::GetInstance().DrawRect(x, y, m_CellSize, m_CellSize, { 0, 0, 0, 255 });
        break;

    case TileType::Explosion:
        dae::Renderer::GetInstance().DrawRect(x, y, m_CellSize, m_CellSize, { 255, 0, 0, 255 });
        break;


    case TileType::Empty:
        break;
    }
}

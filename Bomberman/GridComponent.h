#pragma once


//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <cstdint>
#include <vector>

#include "Component.h"


// enums
enum class TileType : uint8_t
{
	Empty,
	Wall,
	Destructible,
	Bomb,
	Explosion,
	Powerup
};

//-----------------------------------------------------
// GridComponent Class									 
//-----------------------------------------------------
class GridComponent final : public Component
{
public:
	GridComponent(dae::GameObject& owner, int width = 10, int height = 10); // Constructor
	~GridComponent() override = default; // Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	GridComponent(const GridComponent& other)					= delete;
	GridComponent(GridComponent&& other) noexcept				= delete;
	GridComponent& operator=(const GridComponent& other)		= delete;
	GridComponent& operator=(GridComponent&& other) noexcept	= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	TileType GetTile(int x, int y) const;
	void SetTile(int x, int y, TileType type);

	bool IsWalkable(int x, int y) const;
	bool InBounds(int x, int y) const;

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	int Index(int x, int y) const;

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------


	int m_Width;
	int m_Height;

	std::vector<TileType> m_Tiles;
};

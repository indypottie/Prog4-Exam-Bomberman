//---------------------------
// Include Files
//---------------------------
#include "GridComponent.h"

//---------------------------
// Constructor & Destructor
//---------------------------
GridComponent::GridComponent(dae::GameObject& owner, int width, int height) : Component(owner),
m_Width(width),
m_Height(height),
m_Tiles(width * height, TileType::Empty)
{
	
}


//---------------------------
// Member functions
//---------------------------


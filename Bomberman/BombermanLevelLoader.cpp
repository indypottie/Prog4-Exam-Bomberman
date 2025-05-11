//---------------------------
// Include Files
//---------------------------
#include "BombermanLevelLoader.h"
#include "GridComponent.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

//---------------------------
// Member functions
//---------------------------

bool BombermanLevelLoader::LoadLevelFromFile(const std::string& filePath, GridComponent& grid)
{
	std::ifstream file(filePath);
	if (!file.is_open()) return false;

	json levelJson;
	file >> levelJson;

	if (!levelJson.contains("tiles")) return false;

	const auto& tiles = levelJson["tiles"];
	if (!tiles.is_array()) return false;

	int rows = static_cast<int>(tiles.size());
	int cols = static_cast<int>(tiles[0].size());

	if (rows != grid.GetRows() || cols != grid.GetCols())
	{
		std::cerr << "Grid size mismatch: expected " << grid.GetRows() << "x" << grid.GetCols() << ", but got " << rows << "x" << cols << '\n';
		return false;
	}

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			int tileValue = tiles[row][col];
			TileType type = static_cast<TileType>(tileValue);
			grid.SetTile(row, col, type);
		}
	}

	return true;
}


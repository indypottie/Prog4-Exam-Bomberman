#include <stdexcept>
#include <SDL_ttf.h>

#include "ResourceManager.h"

namespace fs = std::filesystem;

void dae::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

dae::Texture2D* dae::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = m_dataPath/file;
	const auto filename = fs::path(fullPath).filename().string();

	if (!m_loadedTextures.contains(filename))
	{
		m_loadedTextures[filename] = std::make_unique<Texture2D>(fullPath.string());
	}

	return m_loadedTextures[filename].get();
}

dae::Font* dae::ResourceManager::LoadFont(const std::string& file, uint8_t size)
{
	const auto fullPath = m_dataPath / file;
	const auto filename = fs::path(fullPath).filename().string();
	const auto key = std::pair<std::string, uint8_t>(filename, size);

	if (!m_loadedFonts.contains(key))
	{
		m_loadedFonts[key] = std::make_unique<Font>(fullPath.string(), size);
	}

	return m_loadedFonts[key].get();
}

void dae::ResourceManager::UnloadUnusedResources()
{

}

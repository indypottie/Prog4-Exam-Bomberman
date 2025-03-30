#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "Texture2D.h"

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------


//-----------------------------------------------------
// TextureComponent Class									 
//-----------------------------------------------------
class TextureComponent final : public Component
{
public:
	TextureComponent(dae::GameObject& owner, const std::string& fileName); // Constructor
	~TextureComponent() override = default; // Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	TextureComponent(const TextureComponent& other)					= delete;
	TextureComponent(TextureComponent&& other) noexcept				= delete;
	TextureComponent& operator=(const TextureComponent& other)		= delete;
	TextureComponent& operator=(TextureComponent&& other) noexcept	= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void SetTexture(const std::string& fileName);
	void Render() const override;

private:

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	dae::Texture2D* m_Texture{};
};

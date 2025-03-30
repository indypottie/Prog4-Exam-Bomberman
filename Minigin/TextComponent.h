#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <memory>
#include <string>
#include "Component.h"
#include "Font.h"
#include "Texture2D.h"

//-----------------------------------------------------
// TextComponent Class									 
//-----------------------------------------------------
class TextComponent final : public Component
{
public:
    TextComponent(dae::GameObject& owner, const std::string& text, dae::Font* font); // Constructor
    ~TextComponent() override = default; // Destructor

    // -------------------------
    // Copy/move constructors and assignment operators
    // -------------------------    
    TextComponent(const TextComponent& other) = delete;
    TextComponent(TextComponent&& other) noexcept = delete;
    TextComponent& operator=(const TextComponent& other) = delete;
    TextComponent& operator=(TextComponent&& other) noexcept = delete;

    //-------------------------------------------------
    // Member functions						
    //-------------------------------------------------
    void Update() override;
    void Render() const override;

    void SetText(const std::string& text);

private:
    //-------------------------------------------------
    // Datamembers											
    //-------------------------------------------------
    bool m_NeedsUpdate;
    std::string m_Text;
    dae::Font* m_Font;            // Raw pointer, managed by ResourceManager
    std::unique_ptr<dae::Texture2D> m_TextTexture; // Raw pointer, managed by ResourceManager
};

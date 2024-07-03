#include <stdexcept>
#include <SDL_ttf.h>

#include "implot.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture.h"

TextComponent::TextComponent(std::weak_ptr<GameObject> owner, const std::string& text, std::shared_ptr<Font> font) :
	Component{ owner },
	m_NeedsUpdate{ true }, 
	m_Text{ text }, 
	m_Font{ std::move(font) },
	m_Texture{ nullptr },
	m_Position{},
	m_SeperatePosition{ false }
{

}

TextComponent::TextComponent(std::weak_ptr<GameObject> owner, const std::string& text, std::shared_ptr<Font> font, glm::vec2 position) :
	Component{ owner },
	m_NeedsUpdate{ true },
	m_Text{ text },
	m_Font{ std::move(font) },
	m_Texture{ nullptr },
	m_Position{ position },
	m_SeperatePosition{ true }
{

}

void TextComponent::Update(std::chrono::milliseconds deltaTime)
{
	++deltaTime;

	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	deltaTime++;
}

void TextComponent::Render() const
{
	std::shared_ptr<GameObject> owner = m_Owner.lock();
	if ((owner != nullptr) and (m_Texture.get() != nullptr))
	{
		auto position{ (m_SeperatePosition) ? m_Position : owner->GetWorldTransform().GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_Texture.get(), position.x, position.y);
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

const std::shared_ptr<Texture> TextComponent::GetTexture() const
{
	return m_Texture;
}
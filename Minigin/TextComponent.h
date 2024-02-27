#ifndef TEXT_OBJECT
#define TEXT_OBJECT

#include <string>
#include <memory>
#include <chrono>

#include "Component.h"

class Font;
class GameObject;
class Texture;

class TextComponent final : public Component
{
public:

	TextComponent(std::shared_ptr<GameObject> owner, const std::string& text, std::shared_ptr<Font> font);
	virtual ~TextComponent() = default;

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;

	void SetText(const std::string& text);
	const std::shared_ptr<Texture> GetTexture() const;

private:

	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture> m_Texture;
};

#endif
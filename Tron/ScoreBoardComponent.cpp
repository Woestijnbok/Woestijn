#include "ScoreBoardComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"

const int ScoreboardComponent::m_LiveSize{ 30 };
const int ScoreboardComponent::m_LivesOffset{ 2 };
const int ScoreboardComponent::m_ScoreLivesOffset{ 2 };	

ScoreboardComponent::ScoreboardComponent(Minigin::GameObject* owner) :
	Component{ owner },
	m_ScoreText{ std::make_unique<Minigin::Text>("0", Minigin::ResourceManager::Instance()->LoadFont("Arcade.otf", 30)) },
	m_LiveTexture{ Minigin::ResourceManager::Instance()->LoadTexture("Hearth.png") },
	m_Score{},
	m_Lives{ 5 }
{
	
}

void ScoreboardComponent::UpdateScore(int score)
{
	m_Score = score;
	m_ScoreText->SetText(std::to_string(score));
}

void ScoreboardComponent::UpdateLives(int lives)
{
	m_Lives = lives;
}

void ScoreboardComponent::Render() const
{
	Minigin::Transform transform{ GetOwner()->GetWorldTransform() };

	// Render score
	m_ScoreText->Render(transform);	

	// Render lives
	const glm::ivec2 textSize{ m_ScoreText->GetSize() };	
	glm::ivec2 startPosition{};
	startPosition.x = transform.GetPosition().x - (((m_Lives * (m_LiveSize + m_LivesOffset)) - m_LivesOffset) / 2) + (m_LiveSize / 2);	
	startPosition.y = transform.GetPosition().y + textSize.y / 2 + m_LiveSize / 2 + m_ScoreLivesOffset;
	glm::vec2 scale{ float(m_LiveSize) / m_LiveTexture->GetSize().x, float(m_LiveSize) / m_LiveTexture->GetSize().y };	
	scale *= transform.GetScale();
	Minigin::Transform livesTransform{ startPosition, transform.GetRotation(), scale };

	for (int live{}; live < m_Lives; ++live)	
	{
		livesTransform.SetPosition(glm::ivec2{ startPosition.x + live * (m_LiveSize + m_LivesOffset), startPosition.y });	
		m_LiveTexture->Render(livesTransform);	
	}
}
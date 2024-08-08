#pragma once

#include <array>
#include <memory>
#include <utility>
#include <vec2.hpp>
#include <optional>

#include "Component.h"
#include "TileComponent.h"
#include "Texture.h"
#include "MoveCommand.h"
#include "TankComponent.h"
	
class BulletComponent;	

class TileManagerComponent final : public Minigin::Component
{
public:	
	explicit TileManagerComponent(Minigin::GameObject* owner, int tileSize);
	virtual ~TileManagerComponent() = default;

	TileManagerComponent(const TileManagerComponent&) = delete;
	TileManagerComponent(TileManagerComponent&&) noexcept = delete;
	TileManagerComponent& operator= (const TileManagerComponent&) = delete;
	TileManagerComponent& operator= (const TileManagerComponent&&) noexcept = delete;

	glm::ivec2 GetStartPosition() const;
	bool CanMove(TankComponent const * tank, MoveCommand::Direction direction) const;
	void CheckCollision(BulletComponent* bullet) const;	

private:
	std::array<std::array<TileComponent*, 8>, 8> m_Tiles;		
	const std::unique_ptr<Minigin::Texture> m_TileZero;		
	const std::unique_ptr<Minigin::Texture> m_TileOne;	
	const std::unique_ptr<Minigin::Texture> m_TileTwoCorner;	
	const std::unique_ptr<Minigin::Texture> m_TileTwoStraight;	
	const std::unique_ptr<Minigin::Texture> m_TileThree;	
	const std::unique_ptr<Minigin::Texture> m_TileFour;	
	const int m_TileSize;
	const int m_CollisionOffset;

	int GetRotation(TileComponent* tile) const;		
	glm::vec2 GetScale(TileComponent* tile) const;	
	void CreateTiles();	
	/*
	* @param point is the point that needs to be checked.
	* bottom is the bottom left point of the rectangle.
	* top is the top right point of the rectangle
	*/
	bool PointInsideRectangle(const glm::ivec2& point, const glm::ivec2& bottom, const glm::ivec2 top) const;
	/*
	* @return An optional point holding the intersection if it intersected.
	* Can use operator bool on std::optional to check if we intersected.
	*/
	std::optional<glm::ivec2> LinesIntersect(const glm::ivec2& a, const glm::ivec2& b, const glm::ivec2& c, const glm::ivec2& d) const;
	/*
	* @brief Checks and handles the bullet in case he is outside or hit the boundaries.
	* 
	* @param To check wether or not the bullet needs to be destroyed use removeBullet.
	* 
	* @return Will hold the intersection in tile manager space if empty there was no intersection with the boundaries.
	*/
	std::optional<glm::ivec2> CheckBounds(BulletComponent* bullet) const;	
	/*
	* @brief Checks and handles the bullet in case he is inside or hit the center collision zone of the current tile.
	*
	* @param To check wether or not the bullet needs to be destroyed use removeBullet.
	*
	* @return Will hold the intersection in tile manager space if empty there was no intersection.
	*/
	std::optional<glm::ivec2> CheckCenter(BulletComponent* bullet) const;
	/*
	* @brief Checks and handles the bullet in case he is inside the top collision zones of the current tile some tiles have this.
	*
	* @param To check wether or not the bullet needs to be destroyed use removeBullet.
	*
	* @return Will hold the intersection in tile manager space if empty there was no intersection.
	*/
	std::optional<glm::ivec2> CheckTop(BulletComponent* bullet) const;	
	std::optional<glm::ivec2> CheckRight(BulletComponent* bullet) const;	
	std::optional<glm::ivec2> CheckBottom(BulletComponent* bullet) const;	
	std::optional<glm::ivec2> CheckLeft(BulletComponent* bullet) const;	
};
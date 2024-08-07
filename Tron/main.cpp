#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <functional>

#include "Engine.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "SpriteComponent.h"
#include "MenuComponent.h"
#include "TileManagerComponent.h"
#include "TankComponent.h"
#include "AimCommand.h"
#include "BulletManagerComponent.h"
#include "FireCommand.h"
#include "ScoreBoardComponent.h"

void Load();
void CreateMainMenu();
void CreateFirstLevel();

using namespace Minigin;

void Load()
{
	CreateMainMenu();
	CreateFirstLevel();
}

void CreateMainMenu()
{
	auto scene{ SceneManager::Instance()->CreateScene("Main Menu") };	

	auto menuObject{ scene->CreateGameObject("Menu")};
	menuObject->CreateComponent<MenuComponent>(glm::ivec2{ 200, 50 }, 10);
}

void CreateFirstLevel()
{
	auto scene{ SceneManager::Instance()->CreateScene("First Level", false) };

	//auto fpsCounterObject{ scene->CreateGameObject("FPS Counter") };
	//fpsCounterObject->CreateComponent<FPSCounterComponent>();
	//fpsCounterObject->SetLocalPosition(glm::ivec2{ 60, 450 });

	auto manager{ scene->CreateGameObject("Manager")};
	auto tileManager = manager->CreateComponent<TileManagerComponent>(50);
	auto bulletManager = manager->CreateComponent<BulletManagerComponent>(tileManager);
	manager->SetLocalPosition(glm::ivec2{ 55, 55 });

	auto player{ scene->CreateGameObject("Player") };
	player->SetParent(manager); // logic requires this attachment (local space)	
	auto playerTank = player->CreateComponent<TankComponent>(tileManager, bulletManager, 100.0f);

	auto scoreboardObject{ scene->CreateGameObject("Scoreboard") };	
	auto scoreboard{ scoreboardObject->CreateComponent<ScoreboardComponent>() };
	scoreboardObject->SetLocalPosition(glm::ivec2{ 255, 550 });		
	playerTank->OnLiveChange().AddObserver(std::bind(&ScoreboardComponent::UpdateLives, scoreboard, std::placeholders::_1));	
	playerTank->OnScoreChange().AddObserver(std::bind(&ScoreboardComponent::UpdateScore, scoreboard, std::placeholders::_1));			

	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::W, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Up));			
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::D, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Right));				
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::S, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Down));				
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::A, InputAction::Trigger::Down, std::make_shared<MoveCommand>(playerTank, MoveCommand::Direction::Left));
	InputManager::Instance()->GetMouse().AddInputAction(Mouse::Action::Move, std::make_shared<AimCommand>(playerTank));	
	InputManager::Instance()->GetMouse().AddInputAction(Mouse::Action::RightClick, std::make_shared<FireCommand>(playerTank));		
}

int main(int, char*[])
{
	Engine::Initialize("Tron");
	Engine::Run(&Load);
	Engine::Destroy();

    return 0;
}
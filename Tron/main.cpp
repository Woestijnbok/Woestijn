#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>

#include "Engine.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "CustomCommands.h"
#include "TestObserver.h"
#include "SpriteComponent.h"
#include "MenuComponent.h"

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

	auto menuObject{ scene->CreateGameObject() };	
	menuObject->CreateComponent<MenuComponent>(glm::ivec2{ 200, 50 }, 10);
}

void CreateFirstLevel()
{
	auto scene{ SceneManager::Instance()->CreateScene("First Level", false) };	

	auto fpsCounterObject{ scene->CreateGameObject() };	
	fpsCounterObject->CreateComponent<FPSCounterComponent>();
}

int main(int, char*[]) 
{
	Engine::Initialize("Tron");
	Engine::Run(&Load);
	Engine::Destroy();

    return 0;
}
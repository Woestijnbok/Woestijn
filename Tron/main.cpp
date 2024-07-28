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

using namespace Minigin;

void loltester(int x, int y)
{
	std::cout << x << y << std::endl;
}

void load()
{
	auto scene{ SceneManager::Instance()->CreateScene("Demo") };
	
	auto font{ ResourceManager::Instance()->LoadFont("Lingua.otf", 36) };
	auto smallFont{ ResourceManager::Instance()->LoadFont("Lingua.otf", 15) };

	// Background game object
	auto background{ scene->CreateGameObject() };
	background->CreateComponent<ImageComponent>(ResourceManager::Instance()->LoadTexture("background.tga"));

	// Logo game object
	auto logo{ scene->CreateGameObject() };
	logo->CreateComponent<ImageComponent>(ResourceManager::Instance()->LoadTexture("logo.tga"));
	logo->SetLocalPosition(glm::ivec2{ 216, 180 });

	// Title game object
	auto title{ scene->CreateGameObject() };
	title->CreateComponent<TextComponent>("Programming 4 Assignment", font);
	title->SetLocalPosition(glm::ivec2{ 80, 20 });

	// FPS counter game object
	auto fpsCounter{ scene->CreateGameObject() };
	fpsCounter->CreateComponent<FPSCounterComponent>();
	fpsCounter->SetLocalPosition(glm::ivec2{ 0, 0 });

	// music explenation object
	auto music{ scene->CreateGameObject() };
	music->CreateComponent<TextComponent>("Use keys 1 and 2 to play differnt music.", smallFont);
	music->SetLocalPosition(glm::ivec2{ 0, 80 });

	// sound explenation object
	auto sound{ scene->CreateGameObject() };
	sound->CreateComponent<TextComponent>("Use keys 3 and 4 to play differnt sound effects.", smallFont);
	sound->SetLocalPosition(glm::ivec2{ 0, 100 });

	// sound action explenation object
	auto soundAction{ scene->CreateGameObject() };
	soundAction->CreateComponent<TextComponent>("Use P to stop the music and O (the letter) to stop all sounds.", smallFont);
	soundAction->SetLocalPosition(glm::ivec2{ 0, 120 });

	auto testSubject{ scene->CreateGameObject() };	
	testSubject->CreateComponent<TestObserverComponent>();
	testSubject->GetComponent<TestObserverComponent>()->GetTestSubject().AddObserver(loltester);

	std::shared_ptr<Sprite> spriteSheet1{ ResourceManager::Instance()->LoadSprite("TestSprite1.png", 4, 1, 4) };
	std::shared_ptr<Sprite> spriteSheet2{ ResourceManager::Instance()->LoadSprite("TestSprite2.png", 4, 1, 4) };
	auto testSprite{ scene->CreateGameObject() };
	auto spriteComponent = testSprite->CreateComponent<SpriteComponent>();	
	spriteComponent->AddSprite(spriteSheet1, std::chrono::milliseconds{ 100 }, "Running Forward");
	spriteComponent->AddSprite(spriteSheet2, std::chrono::milliseconds{ 5000 }, "Running Backwards");	
	spriteComponent->SetSprite("Running Forward");
	testSprite->SetLocalPosition(glm::ivec2{ 0, 0 });
	testSprite->SetLocalScale(glm::vec2{ 0.25f, 0.25f });
	
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::One, InputAction::Trigger::Pressed, new TestMusic1{});	
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::Two, InputAction::Trigger::Pressed, new TestMusic2{});	
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::Three, InputAction::Trigger::Pressed, new TestSoundEffect1{});	
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::Four, InputAction::Trigger::Pressed, new TestSoundEffect2{});
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::Five, InputAction::Trigger::Pressed, new TestLenAbi{ testSubject });	
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::P, InputAction::Trigger::Pressed, new StopMusic{});		
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::O, InputAction::Trigger::Pressed, new StopAll{});
	InputManager::Instance()->GetKeyboard().AddInputAction(Keyboard::Key::S, InputAction::Trigger::Pressed, new SpriteChange{ testSprite });

	InputManager::Instance()->AddController();	
	InputManager::Instance()->GetController(0).AddInputAction(Controller::Button::A, InputAction::Trigger::Pressed, new TestMusic1{});
}

int main(int, char*[]) 
{
	Engine::Initialize("Tron");
	Engine::Run(load);
	Engine::Destroy();

    return 0;
}
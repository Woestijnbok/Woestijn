#include <SDL.h>
#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#include <functional>

#if _DEBUG
	// ReSharper disable once CppUnusedIncludeDirective
	#if __has_include(<vld.h>)
	#include <vld.h>
	#endif
#endif

#include "EventManager.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
//#include "RotaterComponent.h"
//#include "TrashTheCacheComponent.h"
#include "Command.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "CustumCommands.h"
//#include "HealthComponent.h"
//#include "ScoreComponent.h"
//#include "ScoreBoardComponent.h"

void TestEventHandler(const Event& event)
{
	std::cout << event.GetNumberArguments().at(0) << std::endl;
}

void load()
{
	EventManager::GetInstance();
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	// Background game object
	auto background{ std::make_shared<GameObject>() };
	background->AddComponent<ImageComponent>(
		std::make_shared<ImageComponent>(background, ResourceManager::GetInstance().LoadTexture("background.tga"))
	);
	scene.Add(background);

	// Logo game object
	auto logo{ std::make_shared<GameObject>() };
	background->AddComponent<ImageComponent>(
		std::make_shared<ImageComponent>(logo, ResourceManager::GetInstance().LoadTexture("logo.tga"))
	);
	logo->SetLocalPosition(216, 180);
	scene.Add(logo);

	// Title game object
	auto title{ std::make_shared<GameObject>() };
	auto font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	auto smallFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 15) };
	title->AddComponent<TextComponent>(
		std::make_shared<TextComponent>(title, "Programming 4 Assignment", font)
	);
	title->SetLocalPosition(80.0f, 20.0f);
	scene.Add(title);

	// FPS counter game object
	auto fpsCounter{ std::make_shared<GameObject>() };
	fpsCounter->AddComponent<FPSCounterComponent>(
		std::make_shared<FPSCounterComponent>(fpsCounter)
	);
	fpsCounter->SetLocalPosition(0.0f, 0.0f);
	scene.Add(fpsCounter);

	// music explenation object
	auto music{ std::make_shared<GameObject>() };
	music->AddComponent<TextComponent>(
		std::make_shared<TextComponent>(music, "Use keys 1 and 2 to play differnt music.", smallFont, glm::vec2{ 0.0f, 80.0f })
	);
	music->SetLocalPosition(0.0f, 0.0f);
	scene.Add(music);

	// sound explenation object
	auto sound{ std::make_shared<GameObject>() };
	sound->AddComponent<TextComponent>(
		std::make_shared<TextComponent>(sound, "Use keys 3 and 4 to play differnt sound effects.", smallFont, glm::vec2{ 0.0f, 100.0f })
	);
	sound->SetLocalPosition(0.0f, 0.0f);
	scene.Add(sound);

	// sound action explenation object
	auto soundAction{ std::make_shared<GameObject>() };
	soundAction->AddComponent<TextComponent>(
		std::make_shared<TextComponent>(soundAction, "Use P to stop the music and O (the letter) to stop all sounds.", smallFont, glm::vec2{ 0.0f, 120.0f })
	);
	soundAction->SetLocalPosition(0.0f, 0.0f);
	scene.Add(soundAction);

	// Character A game object
	/*auto characterA{ std::make_shared<GameObject>() };
	characterA->AddComponent<ImageComponent>(
		std::make_shared<ImageComponent>(characterA, ResourceManager::GetInstance().LoadTexture("Character.tga"))
	);
	characterA->AddComponent<HealthComponent>(
		std::make_shared<HealthComponent>(characterA)
	);
	characterA->AddComponent<ScoreComponent>(
		std::make_shared<ScoreComponent>(characterA)
	);
	characterA->AddComponent<ScoreBoardComponent>(
		std::make_shared<ScoreBoardComponent>(characterA, glm::vec2{ 0.0f, 150.0f })
	);
	characterA->AddComponent<TextComponent>(
		std::make_shared<TextComponent>(characterA, "Use the WASD to move, x to kill yourself and f to get 100 points.", smallFont, glm::vec2{ 0.0f, 80.0f })
	);
	characterA->SetLocalPosition(100.0f, 300.0f);
	scene.Add(characterA);*/

	// Character B game object
	/*auto characterB{ std::make_shared<GameObject>() };
	characterB->AddComponent<ImageComponent>(
		std::make_shared<ImageComponent>(characterB, ResourceManager::GetInstance().LoadTexture("Character.tga"))
	);
	characterB->AddComponent<HealthComponent>(
		std::make_shared<HealthComponent>(characterB)
	);
	characterB->AddComponent<ScoreComponent>(
		std::make_shared<ScoreComponent>(characterB)
	);
	characterB->AddComponent<ScoreBoardComponent>(
		std::make_shared<ScoreBoardComponent>(characterB, glm::vec2{ 0.0f, 220.0f })
	);
	characterB->AddComponent<TextComponent>(
		std::make_shared<TextComponent>(characterB, "Use the D-pad to move, X to kill yourself and A to get 100 points.", smallFont, glm::vec2{ 0.0f, 100.0f })
	);
	characterB->SetLocalPosition(300.0f, 300.0f);
	scene.Add(characterB);*/

	//// Week 4
	//InputManager::GetInstance().AddInputMappingContext(characterA.get());
	//InputManager::GetInstance().GetInputMappingContext(characterA.get())->AddInputAction<MoveRight>(false, SDLK_d, InputTrigger::pressed);
	//InputManager::GetInstance().GetInputMappingContext(characterA.get())->AddInputAction<MoveLeft>(false, SDLK_a, InputTrigger::pressed);
	//InputManager::GetInstance().GetInputMappingContext(characterA.get())->AddInputAction<MoveUp>(false, SDLK_w, InputTrigger::pressed);
	//InputManager::GetInstance().GetInputMappingContext(characterA.get())->AddInputAction<MoveDown>(false, SDLK_s, InputTrigger::pressed);
	//InputManager::GetInstance().GetInputMappingContext(characterA.get())->AddInputAction<PlayerDie>(false, SDLK_x, InputTrigger::up);
	//InputManager::GetInstance().GetInputMappingContext(characterA.get())->AddInputAction<Add100Score>(false, SDLK_f, InputTrigger::up);

	/*InputManager::GetInstance().AddInputMappingContext(characterB.get());
	InputManager::GetInstance().GetInputMappingContext(characterB.get())->AddInputAction<MoveUp>(true, XINPUT_GAMEPAD_DPAD_UP, InputTrigger::pressed);
	InputManager::GetInstance().GetInputMappingContext(characterB.get())->AddInputAction<MoveDown>(true, XINPUT_GAMEPAD_DPAD_DOWN, InputTrigger::pressed);
	InputManager::GetInstance().GetInputMappingContext(characterB.get())->AddInputAction<MoveRight>(true, XINPUT_GAMEPAD_DPAD_RIGHT, InputTrigger::pressed);
	InputManager::GetInstance().GetInputMappingContext(characterB.get())->AddInputAction<MoveLeft>(true, XINPUT_GAMEPAD_DPAD_LEFT, InputTrigger::pressed);
	InputManager::GetInstance().GetInputMappingContext(characterB.get())->AddInputAction<PlayerDie>(true, XINPUT_GAMEPAD_X, InputTrigger::down);
	InputManager::GetInstance().GetInputMappingContext(characterB.get())->AddInputAction<Add100Score>(true, XINPUT_GAMEPAD_A, InputTrigger::down);*/

	// Sound
	InputManager::GetInstance().AddInputMappingContext(nullptr);
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<TestMusic1>(false, SDLK_1, InputTrigger::down);		
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<TestMusic2>(false, SDLK_2, InputTrigger::down);	
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<TestSoundEffect1>(false, SDLK_3, InputTrigger::down);	
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<TestSoundEffect2>(false, SDLK_4, InputTrigger::down);	
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<StopMusic>(false, SDLK_p, InputTrigger::down);	
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<StopAll>(false, SDLK_o, InputTrigger::down);	
}

int main(int, char*[]) {
	Minigin engine{ "../Data/" };
	engine.Run(load);
    return 0;
}
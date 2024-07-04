#include "Minigin.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "Command.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "CustumCommands.h"

void load()
{
	auto& scene{ SceneManager::GetInstance().CreateScene("Demo") };

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

	InputManager::GetInstance().AddInputMappingContext(nullptr);
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<TestMusic1>(false, SDLK_1, InputTrigger::down);		
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<TestMusic2>(false, SDLK_2, InputTrigger::down);	
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<TestSoundEffect1>(false, SDLK_3, InputTrigger::down);	
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<TestSoundEffect2>(false, SDLK_4, InputTrigger::down);	
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<StopMusic>(false, SDLK_p, InputTrigger::down);	
	InputManager::GetInstance().GetInputMappingContext(nullptr)->AddInputAction<StopAll>(false, SDLK_o, InputTrigger::down);	
}

int main(int, char*[]) 
{
	Minigin engine{ "Tron" };
	engine.Run(load);
    return 0;
}
#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Subject.h"
#include "Qbert.h"
#include "Command.h"
#include "SoundServiceLocator.h"
#include "SDL_SoundSystem.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	/*if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}*/
	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	ResourceManager::GetInstance().Init("../Data/");
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto back = std::make_shared<GameObject>();
	//back.get()->AddComponent(new RenderComponent("background.jpg", 0, 0), ComponentsID::RenderComp);
	////go->SetTexture("background.jpg");
	//scene.Add(back);

	//auto logo = std::make_shared<GameObject>();
	//logo.get()->AddComponent(new RenderComponent("logo.png", 216, 180), ComponentsID::RenderComp);
	///*go->SetTexture("logo.png");
	//go->SetPosition(216, 180);*/
	//scene.Add(logo);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	////auto text = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//auto text = std::make_shared<GameObject>();
	//text.get()->AddComponent(new TextComponent("Programming 4 Assignment", font , 85 , 20), ComponentsID::TextComp);
	////to->SetPosition(80, 20);
	//scene.Add(text);

	//auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	//auto fpsCounter = std::make_shared<GameObject>();
	//fpsCounter.get()->AddComponent(new FPSComponent("fps", font, 0, 20), ComponentsID::FPSComp);
	//scene.Add(fpsCounter);

	////Lives
	//auto lives = std::make_shared<GameObject>();
	//auto livesFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	//auto livesText = new TextComponent("Lives:", livesFont, 20, 100);

	//auto observe = new Observer();
	//auto subject = new Subject();
	//subject->Attach(observe);

	//auto score = std::make_shared<GameObject>();
	//auto scoreFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	//auto scoreText = new TextComponent("Score:", scoreFont, 20, 120);

	//auto observeScore = new Observer();
	//auto subjectScore = new Subject();
	//subjectScore->Attach(observeScore);

	//auto qBert = std::make_shared<GameObject>();
	////auto QBert = new Qbert(subject,subjectScore);

	//qBert.get()->AddComponent(QBert,ComponentsID::QbertComp);
	//qBert.get()->AddComponent(new LivesComponent(livesText,observe), ComponentsID::LivesComp);
	//qBert.get()->AddComponent(livesText, ComponentsID::TextComp);
	//scene.Add(qBert);

	//auto scoreGameObject = std::make_shared<GameObject>();
	//scoreGameObject.get()->AddComponent(scoreText, ComponentsID::TextComp);
	//scoreGameObject.get()->AddComponent(new ScoreComponent(scoreText, observeScore), ComponentsID::ScoreComp);
	//scene.Add(scoreGameObject);

	//Die* dieCommand = new Die(QBert);
	//m_pInputManager->AddCommand(dieCommand, ControllerButton::ButtonA);

	//Point25* pointCommand = new Point25(QBert);
	//m_pInputManager->AddCommand(pointCommand, ControllerButton::ButtonB);


	////part 2
	//auto lives2 = std::make_shared<GameObject>();
	//auto livesFont2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	//auto livesText2 = new TextComponent("Lives:", livesFont2, 80, 100);

	//auto observe2 = new Observer();
	//auto subject2 = new Subject();
	//subject2->Attach(observe2);

	//auto score2 = std::make_shared<GameObject>();
	//auto scoreFont2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	//auto scoreText2 = new TextComponent("Score:", scoreFont2, 80, 120);

	//auto observeScore2 = new Observer();
	//auto subjectScore2 = new Subject();
	//subjectScore2->Attach(observeScore2);

	//auto qBert2 = std::make_shared<GameObject>();
	//auto QBert2 = new Qbert(subject2, subjectScore2);

	//qBert2.get()->AddComponent(QBert2, ComponentsID::QbertComp);
	//qBert2.get()->AddComponent(new LivesComponent(livesText2, observe2), ComponentsID::LivesComp);
	//qBert2.get()->AddComponent(livesText2, ComponentsID::TextComp);
	//scene.Add(qBert2);

	//auto scoreGameObject2 = std::make_shared<GameObject>();
	//scoreGameObject2.get()->AddComponent(scoreText2, ComponentsID::TextComp);
	//scoreGameObject2.get()->AddComponent(new ScoreComponent(scoreText2, observeScore2), ComponentsID::ScoreComp);
	//scene.Add(scoreGameObject2);

	//Die* dieCommand2 = new Die(QBert2);
	//m_pInputManager->AddCommand(dieCommand2, ControllerButton::ButtonDPadUp);

	//Point25* pointCommand2 = new Point25(QBert2);
	//m_pInputManager->AddCommand(pointCommand2, ControllerButton::ButtonDPadDown);


	//// SOUND STUFF
	//SoundSystem* pSoundSystem = new SDL_SoundSystem();
	//SoundServiceLocator::SetSoundSystem(pSoundSystem);
	//
	//BasicSound* pSound = new BasicSound(pSoundSystem);
	//m_pInputManager->AddCommand(pSound,ControllerButton::ButtonDPadLeft);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	//Initialize();

	//// tell the resource manager where he can find the game data
	//ResourceManager::GetInstance().Init("../Data/");
	//
	//LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();

		const auto previousTime = high_resolution_clock::now();
		
		bool doContinue = true;
		
		auto lastTime = high_resolution_clock::now();
		while (doContinue)
		{
			auto current = high_resolution_clock::now();
			float elapsed = std::chrono::duration<float>(current - lastTime).count();
			//std::cout << elapsed << '\n';

			doContinue = InputManager::GetInstance().ProcessInput();

			sceneManager.Update(elapsed);
			renderer.Render();

			std::this_thread::sleep_for(duration_cast<duration<float>>(current + milliseconds(MsPerFrame) - high_resolution_clock::now()));
			lastTime = current;
		}
	}

	Cleanup();
}

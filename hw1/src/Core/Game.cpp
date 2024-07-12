#include "Game.h"
#include "Core/Actor.h"
#include "Renderer.h"
#include "Actor/FloorActor.h"
#include "Actor/CameraActor.h"
#include <Actor/MarryActor.h>
#include "Object/Light.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Actor/LightActor.h>
Game::Game()
	:mRenderer(nullptr)
	, mIsRunning(true)
	, mUpdatingActors(false)
{
}

Game::~Game()
{
}

bool Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mRenderer = new Renderer(this);
	if (!mRenderer->Init(1600, 900)) {
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		return false;
	}

	LoadData();
	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mGameState != EQuit)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Quit()
{
	UnloadData();
	if (mRenderer)
	{
		mRenderer->Shutdown();
	}
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	mTicksCount = SDL_GetTicks();

	if (mGameState == EGameplay) {
		mUpdatingActors = true;
		for (auto actor : mActors) {
			actor->Update(deltaTime);
		}
		mUpdatingActors = false;

		for (auto pending : mPendingActors) {
			pending->ComputeWorldTransform();
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();
	}
}

void Game::LoadData()
{
	GetRenderer()->LoadObj("assets/hw1/obj/floor/floor.obj");
	GetRenderer()->LoadObj("assets/hw1/obj/mary/Marry.obj");

	FloorActor* _floor = new FloorActor(this);
	MarryActor* _marry_big = new MarryActor(this);
	MarryActor* _marry_small = new MarryActor(this);
	_marry_small->SetPosition(glm::vec3(5.f, 0.f, 0.f));
	_marry_small->SetScale(glm::vec3(5.f, 5.f, 5.f));

	/*LightActor* light1 = new LightActor(this);*/
	


	DirectionLight* _dl = new DirectionLight(GetRenderer());
	_dl->mPosition = glm::vec3(-50.f, 50.f, 0.f);
	_dl->SetTargetAndUp(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	_dl->mIntensity = glm::vec3(100.f, 100.f, 100.f);
	GetRenderer()->AddLight(_dl);
	GetRenderer()->AddFrameBuffer(2048, 2048);


	DirectionLight* _dl2 = new DirectionLight(GetRenderer());
	_dl2->mPosition = glm::vec3(50.f, 45.f, 0.f);
	_dl2->SetTargetAndUp(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	_dl2->mIntensity = glm::vec3(100.f,100.f, 100.f);
	GetRenderer()->AddLight(_dl2);
	GetRenderer()->AddFrameBuffer(2048, 2048);

	DirectionLight* _dl3 = new DirectionLight(GetRenderer());
	_dl3->mPosition = glm::vec3(0.f, 40.f, 50.f);
	_dl3->SetTargetAndUp(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	_dl3->mIntensity = glm::vec3(100.f, 100.f, 100.f);
	GetRenderer()->AddLight(_dl3);
	GetRenderer()->AddFrameBuffer(2048, 2048);
}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	while (mRenderer)
	{
		mRenderer->UnloadData();
	}
}

void Game::ProcessInput()
{
	GetRenderer()->GetMainCamera()->Forward(0);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mGameState = EQuit;
			break;
		case SDL_MOUSEWHEEL:
			GetRenderer()->GetMainCamera()->Forward(event.wheel.y);
		default:
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (mGameState == EGameplay) {
		for (auto actor : mActors) {
			if (actor->GetState() == Actor::EActive) {
				actor->ProcessInput(state);
			}
		}
	}
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

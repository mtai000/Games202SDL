#include "Game.h"
#include "Core/Actor.h"
#include "Renderer.h"
#include "Actor/FloorActor.h"
#include "Actor/CameraActor.h"
#include <Actor/MarryActor.h>
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
	GetRenderer()->LoadObj("assets/hw0/obj/floor/floor.obj");
	GetRenderer()->LoadObj("assets/hw0/obj/mary/Marry.obj");

	FloorActor* _floor = new FloorActor(this);
	MarryActor* _marry_big = new MarryActor(this);
	MarryActor* _marry_small = new MarryActor(this);
	_marry_small->SetPosition(glm::vec3(5.f, 0.f, 0.f));
	_marry_small->SetScale(glm::vec3(5.f,5.f,5.f));
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
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mGameState = EQuit;
			break;

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

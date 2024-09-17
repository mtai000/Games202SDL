#pragma once
#include <vector>
#include "head.h"

class Game {
public:
	enum GameState
	{
		EGameplay,
		EPaused,
		EQuit
	};

	Game();
	~Game();
	bool Init();
	void RunLoop();
	void Quit();

	GameState GetState() const { return mGameState; }
	void SetState(GameState state) { mGameState = state; }

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() { return mRenderer; }
private:
	GameState mGameState;
	class Renderer* mRenderer;

	void UpdateGame();
	void LoadData ();
	void UnloadData();

	void ProcessInput();
	void GenerateOutput();

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	unsigned int mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;
};
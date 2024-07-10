#include "Core/Game.h"

int main() {
	Game game;
	game.Init();
	game.RunLoop();
	game.Quit();
	return 0;
}
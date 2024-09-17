#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Core/Game.h"

int main() {
	Game game;
	if(!game.Init())
		exit(0);
	game.RunLoop();
	game.Quit();
	return 0;
}
#include <time.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_ttf.h"

//#include "Game.h"
#include "SdlUtils.h"
#include "Engine.h"
#include "GameInfo.h"
#include "GameInitInfo.h"
#include "Renderer.h"

#define CAVE_WIDTH 40
#define CAVE_HEIGHT 22
#define INFO_HEIGHT 6

#undef main

int main(int argv, char* args)
{
	//zoom - 21px
	int zoom = 21;

	SdlUtils utils = SdlUtils();
	Engine game = Engine(utils);
	Renderer renderer = Renderer();

	srand(time(NULL));

	unsigned int* pixelBuffer = utils.SdlInit(CAVE_WIDTH * zoom, (INFO_HEIGHT + CAVE_HEIGHT) * zoom, "BD", 60);
	GameInfo gameStr = GameInitInfo().InitGame(0, 0);

	int fpsLimiter = 0;

	while (utils.SdlHandleEvents(pixelBuffer))
	{
		while (utils.SdlLimitFps(&fpsLimiter, 8))
		{
			game.Process(&gameStr);
			utils.SdlReleaseKeys();
		}

		renderer.RenderGame(gameStr, pixelBuffer, zoom);
	}

	utils.SdlClose();
	//delete utils;


	return 0;
}
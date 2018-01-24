#include "Game.h"
#include "PixelBuffer.h"

#include <time.h>


Game::Game(SdlUtils utils, Engine engine, Renderer renderer)
{
	this->utils = utils;
	this->engine = engine;
	this->renderer = renderer;
	this->gameLimiter = 0;
}


Game::~Game()
{
}

void Game::Run()
{
	//start rng
	srand(time(NULL));

	//create buffer
	PixelBuffer pixelBuffer = utils.SdlInit(CAVE_WIDTH * ZOOM, (INFO_HEIGHT + CAVE_HEIGHT) * ZOOM, "BD (based on Boulder Dash 2 from Commodore 64)", 60);
	//init game
	GameInfo gameInfo = GameInitInfo().InitGame(0, 0);

	while(utils.SdlHandleEvents((void*)pixelBuffer.GetBuffer()))
	{
		while (utils.SdlLimitFps(&gameLimiter))
		{
			engine.Process(&gameInfo);
		}

		renderer.RenderGame(gameInfo, pixelBuffer.GetBuffer(), ZOOM);
	}

	utils.SdlClose();
}

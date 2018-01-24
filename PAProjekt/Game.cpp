#include "Game.h"
#include "PixelBuffer.h"

#include <time.h>


Game::Game(Engine engine, Renderer renderer)
{
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

	GameInfo gameInfo = engine.InitGame();

	while (engine.HandleEvents())
	{
		while (engine.LimitFps(&gameLimiter))
		{
			engine.Process(&gameInfo);
		}
		renderer.RenderGame(gameInfo, engine.GetPixelBuffer(), ZOOM);
	}
	
	engine.Close();
}

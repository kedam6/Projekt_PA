#pragma once
#include "SdlUtils.h"
#include "Engine.h"
#include "Renderer.h"

class Game
{
private:
	SdlUtils utils;
	Engine engine;
	Renderer renderer;
	int gameLimiter;

public:
	Game(SdlUtils utils, Engine engine, Renderer renderer);
	~Game();

	void Run();
};


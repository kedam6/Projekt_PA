#pragma once
#include "SdlUtils.h"
#include "Engine.h"
#include "Renderer.h"

class Game
{
private:
	Engine engine;
	Renderer renderer;
	int gameLimiter;

public:
	Game(Engine engine, Renderer renderer);
	~Game();

	void Run();
};


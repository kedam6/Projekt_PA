#pragma once
#include "Game.h"
#include "IFactory.h"
#include "Engine.h"
#include "Renderer.h"

class GameFactory : public IFactory<Game>
{
private:
	Engine engine;
	Renderer renderer;
public:
	GameFactory();
	GameFactory(Engine engine, Renderer renderer);
	~GameFactory();

	Game Create() override;
};


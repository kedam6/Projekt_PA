#include "GameFactory.h"



GameFactory::GameFactory()
{
	//GlobalInstances::Instance();
}

GameFactory::GameFactory(Engine engine, Renderer renderer)
{
	this->engine = engine;
	this->renderer = renderer;
}


GameFactory::~GameFactory()
{
}

Game GameFactory::Create()
{
	Game game = Game
	(
		engine,
		renderer
	);
	return game;
}

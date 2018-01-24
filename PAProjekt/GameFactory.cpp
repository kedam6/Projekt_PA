#include "GameFactory.h"



GameFactory::GameFactory()
{
	//GlobalInstances::Instance();
}


GameFactory::~GameFactory()
{
}

Game GameFactory::Create()
{
	Game game = Game
	(
		GlobalInstances::Instance().GetItem<SdlUtils>(),
		GlobalInstances::Instance().GetItem<Engine>(),
		GlobalInstances::Instance().GetItem<Renderer>()
	);
	return game;
}

#pragma once
#include "Game.h"
#include "IFactory.h"
#include "GlobalInstances.h"

class GameFactory : public IFactory<Game>
{
//private:
	//GlobalInstances globalInstances;
public:
	GameFactory();
	~GameFactory();

	Game Create() override;
};


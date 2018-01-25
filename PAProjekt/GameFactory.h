#pragma once
#include "Game.h"
#include "IFactory.h"
#include "GlobalInstances.h"

class GameFactory : public IFactory<Game>
{
public:
	GameFactory();
	~GameFactory();

	Game Create() override;
};


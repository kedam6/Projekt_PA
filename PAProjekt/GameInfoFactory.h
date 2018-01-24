#pragma once
#include "IFactory.h"
#include "GameInfo.h"

class GameInfoFactory : public IFactory<GameInfo>
{
public:
	GameInfoFactory();
	~GameInfoFactory();

	GameInfo Create() override;
};


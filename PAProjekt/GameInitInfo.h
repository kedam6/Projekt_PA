#pragma once
#include "GameInfo.h"
#include "Graphics.h"
#include "Renderer.h"
#include "PositionChecker.h"
#include "GameEffects.h"
#include "GameSupport.h"

class GameInitInfo
{
private:
	Graphics graphics;
	Renderer renderer;
	PositionChecker positionChecker;
	GameEffects gameEffects;
	GameSupport support;

public:
	GameInitInfo();
	~GameInitInfo();

	GameInfo InitGame(int level, int difficulty);
};


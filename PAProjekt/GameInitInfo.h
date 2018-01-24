#pragma once
#include "GameInfo.h"
#include "Graphics.h"
#include "Renderer.h"
#include "PositionChecker.h"
#include "GameEffects.h"
#include "GameSupport.h"
#include "NoiseMaker.h"
#include "StageCreator.h"

class GameInitInfo
{
private:
	Graphics graphics;
	Renderer renderer;
	PositionChecker positionChecker;
	GameEffects gameEffects;
	GameSupport support;
	NoiseMaker noiseMaker;
	StageCreator stageCreator;

public:
	GameInitInfo();
	GameInitInfo(Graphics graphics, Renderer renderer, PositionChecker positionChecker, GameEffects gameEffects, GameSupport support, NoiseMaker noiseMaker, StageCreator stageCreator);
	~GameInitInfo();

	GameInfo InitGame(int level, int difficulty);
};


#pragma once
#include "GameInfo.h"
#include "GameInitInfo.h"
#include "Graphics.h"
#include "Renderer.h"
#include "PositionChecker.h"
#include "GameEffects.h"
#include "GameSupport.h"
#include "SdlUtils.h"


class Engine
{
private:
	GameInitInfo initializer;
	Graphics graphics;
	Renderer renderer;
	PositionChecker positionChecker;
	GameEffects gameEffects;
	GameSupport support;
	SdlUtils sdlUtils;

public:
	Engine(SdlUtils utils);
	~Engine();

	void Process(GameInfo* game);
};


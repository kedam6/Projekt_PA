#pragma once
#include "GameInfo.h"
#include "GameInitInfo.h"
#include "Graphics.h"
#include "Renderer.h"
#include "PositionChecker.h"
#include "GameEffects.h"
#include "GameSupport.h"
#include "SdlUtils.h"
#include "PixelBuffer.h"


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

	PixelBuffer buffer;

public:
	Engine(SdlUtils utils, GameInitInfo initializer, Renderer renderer, PositionChecker positionChecker, Graphics graphics, GameEffects gameEff, GameSupport gameSupport);
	Engine();
	~Engine();

	void Process(GameInfo* game);
	void Close();
	GameInfo InitGame();
	bool HandleEvents();
	bool LimitFps(int* limiter);
	PixelBuffer GetPixelBuffer();
};


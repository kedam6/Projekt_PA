#pragma once
#include "GameManager.h"
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
	GameManager manager;

	PixelBuffer buffer;

public:
	Engine(SdlUtils utils, GameInitInfo initializer, Renderer renderer, PositionChecker positionChecker, Graphics graphics, GameEffects gameEff, GameSupport gameSupport, GameManager gameManager);
	Engine();
	~Engine();

	void Process(GameInfo* game);
	void Close();
	GameInfo InitGame();
	bool HandleEvents();
	bool LimitFps(int* limiter);
	PixelBuffer GetPixelBuffer();
};


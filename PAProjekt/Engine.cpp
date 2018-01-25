#include "Engine.h"
#include "GlobalValues.h"
#include "GameObjects.h"
#include "GameInitInfo.h"
#include "PositionChecker.h"
#include <stdlib.h>


Engine::Engine(SdlUtils utils, GameInitInfo initializer, Renderer renderer, PositionChecker positionChecker, Graphics graphics, GameEffects gameEff, GameSupport gameSupport, GameManager gameManager)
{
	this->initializer = initializer;
	this->renderer = renderer;
	this->positionChecker = positionChecker;
	this->graphics = graphics;
	this->gameEffects = gameEff;
	this->support = gameSupport;
	this->sdlUtils = utils;
	this->manager = gameManager;
}
Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Process(GameInfo * game)
{
	manager.Process(game);
}

void Engine::Close()
{
	sdlUtils.SdlClose();
}

GameInfo Engine::InitGame()
{
	//create buffer
	PixelBuffer pixelBuffer = sdlUtils.SdlInit(CAVE_WIDTH * ZOOM, (INFO_HEIGHT + CAVE_HEIGHT) * ZOOM, "BD (based on Boulder Dash 2 from Commodore 64)", 60);
	this->buffer = pixelBuffer;
	//init game
	GameInfo ret = initializer.InitGame(0, 0);

	return ret;
}

bool Engine::HandleEvents()
{
	return sdlUtils.SdlHandleEvents((void*)buffer.GetBuffer());
}

bool Engine::LimitFps(int * limiter)
{
	return sdlUtils.SdlLimitFps(limiter);
}

PixelBuffer Engine::GetPixelBuffer()
{
	return buffer;
}

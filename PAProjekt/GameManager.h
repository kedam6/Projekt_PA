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
#include "GameObjects.h"
#include "MapHandler.h"
#include "ActionHandler.h"

class GameManager
{
private:
	GameInitInfo initializer;
	Graphics graphics;
	Renderer renderer;
	PositionChecker positionChecker;
	GameEffects gameEffects;
	GameSupport support;
	SdlUtils sdlUtils;
	MapHandler mapHandler;
	PixelBuffer buffer;
	ActionHandler actionHandler;

public:
	GameManager();
	GameManager(SdlUtils utils, GameInitInfo initializer, Renderer renderer, PositionChecker positionChecker, Graphics graphics, GameEffects gameEff, GameSupport gameSupport, ActionHandler actionHandler);
	~GameManager();

	void CheckForSecretDevKey(GameInfo * game);

	void StartNewGame(GameInfo* game, int cave, int difficulty);

	bool PlayerWon(GameInfo * game);

	bool PlayerLost(GameInfo * game);

	bool MoveToNextLevel(GameInfo * game);

	bool RestartLevel(GameInfo * game);

	void Process(GameInfo* game);
};


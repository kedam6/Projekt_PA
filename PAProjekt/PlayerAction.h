#pragma once
#include "Action.h"
#include "GameEffects.h"
#include "PositionChecker.h"

class PlayerAction :
	public Action
{
private:
	GameEffects gameEffects;
	PositionChecker positionChecker;
public:
	PlayerAction();
	PlayerAction(GameEffects gameEffects, PositionChecker positionChecker);
	~PlayerAction();

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};


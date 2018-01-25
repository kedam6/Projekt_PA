#pragma once
#include "Action.h"
#include "GameEffects.h"
#include "PositionChecker.h"
#include "InputHandler.h"
class RockfordAction :
	public Action
{
private:
	GameEffects gameEffects;
	PositionChecker positionChecker;
	InputHandler input;
public:
	RockfordAction(GameEffects gameEffects, PositionChecker positionChecker, InputHandler input);
	RockfordAction();
	~RockfordAction();

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};


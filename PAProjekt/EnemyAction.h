#pragma once
#include "Action.h"
#include "GameEffects.h"
#include "PositionChecker.h"

class EnemyAction :
	public Action
{
private:
	GameEffects gameEffects;
	PositionChecker positionChecker;
public:
	EnemyAction();
	EnemyAction(GameEffects gameEffects, PositionChecker positionChecker);
	~EnemyAction();

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};


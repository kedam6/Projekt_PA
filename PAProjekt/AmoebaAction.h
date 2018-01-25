#pragma once
#include "Action.h"
#include "PositionChecker.h"

class AmoebaAction : public Action
{
private:
	PositionChecker posChecker;

public:
	AmoebaAction();
	AmoebaAction(PositionChecker posChecker);

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};


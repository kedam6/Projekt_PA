#pragma once
#include "Action.h"
class ExplosionAction : public Action
{
public:
	ExplosionAction();

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};


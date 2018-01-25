#pragma once
#include "Action.h"
class DexplosionAction :
	public Action
{
public:
	DexplosionAction();
	~DexplosionAction();

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};


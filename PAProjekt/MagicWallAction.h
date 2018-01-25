#pragma once
#include "Action.h"
class MagicWallAction :
	public Action
{
public:
	MagicWallAction();
	~MagicWallAction();

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};


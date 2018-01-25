#pragma once
#include "Action.h"

class BlankAction : public Action
{
public:
	BlankAction();
	~BlankAction();

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};


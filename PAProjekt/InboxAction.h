#pragma once
#include "Action.h"
class InboxAction :
	public Action
{
public:
	InboxAction();

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};


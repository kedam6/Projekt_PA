#pragma once
#include "Cave.h"
#include "GameInfo.h"
#include "ActionContext.h"

class BaseAction
{
public:
	BaseAction();
	~BaseAction();

	virtual void PerformAction(GameInfo* game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext& context) = 0;
};

